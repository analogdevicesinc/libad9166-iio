// SPDX-License-Identifier: LGPL-2.1-or-later

#include "ad9166.h"
#include "utilities.h"

#include <errno.h>
#include <iio.h>
#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <time.h>
#endif

#define MAX_ATTR_NAME		128
#define MAX_CALIB_LENGTH	32
#define ARRAY_DELIM " [,]"

double default_calibration_freqs[32] = {100000000, 430000000, 510000000, 850000000, 1240000000, 2250000000, 2790000000, 3040000000, 3140000000, 3220000000, 3360000000, 3460000000, 3560000000, 3630000000, 3720000000, 3810000000, 3850000000, 3950000000, 4000000000, 4070000000, 4120000000, 4180000000, 4260000000, 4360000000, 4440000000, 4730000000, 4860000000, 5010000000, 5110000000, 5670000000, 5730000000, 5860000000};
double default_calibration_offsets[32] = {260, 293, 321, 288, 291, 345, 407, 474, 443, 491, 516, 493, 534, 642, 557, 606, 598, 645, 614, 627, 614, 655, 647, 682, 645, 714, 688, 763, 749, 874, 917, 899};
double default_calibration_gains[32] = {1.2565445026178007e-07, 3.3544921875e-07, -1.0769329565887484e-07, 1.4522821576763486e-08, 5.306764986122042e-08, 1.0081510081510082e-07, 2.5736040609137073e-07, -3.1037234042553216e-07, 5.852272727272726e-07, 2.305418719211822e-07, -2.2881355932203387e-07, 3.6219512195121936e-07, 1.3952119309262202e-06, -9.388185654008449e-07, 5.782520325203256e-07, -2.974137931034482e-07, 4.2547169811320736e-07, -5.426751592356699e-07, 1.4285714285714287e-07, -1.454545454545454e-07, 9.879807692307702e-07, -1.220930232558139e-07, 5.582608695652176e-07, -4.986979166666671e-07, 2.2954699121027734e-07, -1.391025641025642e-07, 4.4178082191780847e-07, -1.272727272727272e-07, 2.0280612244898007e-07, 7.956521739130434e-07, -4.520917678812415e-08, 8.961038961038966e-07};

struct ad9166_calibration_data default_calibration_data = {
    .freqs = default_calibration_freqs,
    .offsets = default_calibration_offsets,
    .gains = default_calibration_gains,
	.len = 32,
	.calibrated = false,
};

static int parse_array(const char *value, double **arr, size_t *len)
{
	char *value_dup = util_strdup(value);
	int ret = 0;

	*arr = calloc(MAX_CALIB_LENGTH, sizeof(double));
	*len = 0;

	char *tk = strtok(value_dup, ARRAY_DELIM);
	while (tk) {
		double n;

		ret = util_read_double(tk, &n);
		if (ret)
			goto err;

		(*arr)[(*len)++] = n;

		tk = strtok(NULL, ARRAY_DELIM);
	}

err:
	free(value_dup);

	return ret;
}

int ad9166_context_find_calibration_data(struct iio_context *ctx,
					 const char *name,
					 struct ad9166_calibration_data **data)
{
	char freq_attr_name[MAX_ATTR_NAME];
	char offset_attr_name[MAX_ATTR_NAME];
	char gain_attr_name[MAX_ATTR_NAME];
	int ret;

	snprintf(freq_attr_name, sizeof(freq_attr_name), "%s%s", name, "_freq");
	snprintf(offset_attr_name, sizeof(offset_attr_name), "%s%s", name, "_offset");
	snprintf(gain_attr_name, sizeof(gain_attr_name), "%s%s", name, "_gain");

	const char *freq_attr = iio_context_get_attr_value(ctx, freq_attr_name);
	const char *offset_attr = iio_context_get_attr_value(ctx, offset_attr_name);
	const char *gain_attr = iio_context_get_attr_value(ctx, gain_attr_name);

	size_t freqs_len, offsets_len, gains_len;
	double *freqs, *offsets, *gains;

	if (!freq_attr || !offset_attr || !gain_attr) {
		*data = &default_calibration_data;
		return 0;
	}

	ret = parse_array(freq_attr, &freqs, &freqs_len);
	if (ret)
		return ret;

	ret = parse_array(offset_attr, &offsets, &offsets_len);
	if (ret)
		return ret;

	ret = parse_array(gain_attr, &gains, &gains_len);
	if (ret)
		return ret;

	if (freqs_len != offsets_len || offsets_len != gains_len)
		return -EINVAL;

	*data = malloc(sizeof(**data));
	(*data)->freqs = freqs;
	(*data)->offsets = offsets;
	(*data)->gains = gains;
	(*data)->len = freqs_len;
	(*data)->calibrated = true;

	return 0;
}

int ad9166_channel_set_freq(struct iio_channel *ch,
			    unsigned long long int freq)
{
	int ret;

	ret = iio_channel_attr_write_longlong(ch, "nco_frequency", freq);
	if (ret < 0)
		return ret;

	return 0;
}

int ad9166_device_set_amplitude(struct iio_device *dev, long long amplitude)
{
	int ret;

	unsigned int reg_amplitude_dec = pow(10, amplitude / 20.0) * 0x7FFF;
	ret = iio_device_reg_write(dev, 0x14E, reg_amplitude_dec >> 8);
	if (ret)
		return ret;

	ret = iio_device_reg_write(dev, 0x14F, reg_amplitude_dec & 0xFF);
	if (ret)
		return ret;

	return 0;
}

int ad9166_device_set_iofs(struct iio_device *dev,
			   struct ad9166_calibration_data *data,
			   unsigned long long int freq)
{
	int ret;

	if (!data)
		return -EINVAL;

	if (data->len < 1)
		return -EINVAL;

	unsigned int iofs;

	if (freq < 1000000000)
		iofs = data->offsets[0];

	for (unsigned int i = 0; i < data->len; i++) {
		if (i == data->len - 1
		    || freq >= data->freqs[i] && freq < data->freqs[i + 1]) {
			iofs = data->offsets[i] +  data->gains[i]
			       * (freq - data->freqs[i]);
			break;
		}
	}

	if (iofs > 1023)
		iofs = 1023;

	ret = iio_device_reg_write(dev, 0x42, iofs >> 2);
	if (ret)
		return ret;

	ret = iio_device_reg_write(dev, 0x41, iofs & 0x3);
	if (ret)
		return ret;

	return 0;
}

bool ad9166_device_is_calibrated(struct ad9166_calibration_data *data)
{
	return (data->calibrated);
}
