#include <stdio.h>
#include <errno.h>

#include <iio/iio.h>

#include "ad9166.h"

int main(int argc, char *argv[])
{
	int ret;
	const char *uri;

	if (argc < 2){
		// try retrieving URI from environment variables first
		uri = getenv("URI_AD9166");
		if (uri == NULL)
			uri = "local:";
	}else{
		uri = argv[1];
	}

	struct iio_context *ctx = iio_create_context(NULL, uri);
	if (!ctx) {
		fprintf(stderr, "Cannot find iio context\n");
		return 0;
	}

	struct iio_device *dev = iio_context_find_device(ctx, "ad9166");
	if (!dev) {
		fprintf(stderr, "Cannot find iio device\n");
		return 0;
	}

	struct ad9166_calibration_data *data;
	const struct iio_attr *attr;

	ret = ad9166_context_find_calibration_data(ctx, "cn0511", &data);
	if (ret)
		return ret;

	printf("Freqs: ");
	unsigned int i;
	for (i = 0; i < data->len; i++) {
		printf("%g\n", data->freqs[i]);
	}
	printf("\n");

	printf("Offsets: ");
	for (i = 0; i < data->len; i++) {
		printf("%g\n", data->offsets[i]);
	}
	printf("\n");

	printf("Gains: ");
	for (i = 0; i < data->len; i++) {
		printf("%g\n", data->gains[i]);
	}
	printf("\n");

	attr = iio_device_find_attr(dev, "sampling_frequency");
	if (attr)
		ret = iio_attr_write(attr, "6000000000");
	else
		ret = -ENOENT;
	if (ret < 0)
		return ret;

	attr = iio_device_find_attr(dev, "fir85_enable");
	if (attr)
		ret = iio_attr_write(attr, "1");
	else
		ret = -ENOENT;
	if (ret < 0)
		return ret;

	struct iio_channel *ch = iio_device_find_channel(dev, "altvoltage0", true);
	unsigned long long int freq = 4500000000;

	ret = ad9166_channel_set_freq(ch, freq);
	if (ret)
		return ret;

	ret = ad9166_device_set_amplitude(dev, 0);
	if (ret)
		return ret;

	ret = ad9166_device_set_iofs(dev, data, freq);
	if (ret)
		return ret;

	return 0;
}
