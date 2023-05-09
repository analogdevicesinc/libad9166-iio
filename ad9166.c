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
