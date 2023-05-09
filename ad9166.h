// SPDX-License-Identifier: LGPL-2.1-or-later

 /** @file ad9166.h
  * @brief Public interface */

#ifndef __AD9166_H__
#define __AD9166_H__

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup FLAGS MCS Flags
 *
 * @{
 */
/** @} */

#ifdef _WIN32
#   ifdef LIBAD9166_EXPORTS
#	define __api __declspec(dllexport)
#   else
#	define __api __declspec(dllimport)
#   endif
#elif __GNUC__ >= 4 && !defined(MATLAB_MEX_FILE) && !defined(MATLAB_LOADLIBRARY)
#   define __api __attribute__((visibility ("default")))
#else
#   define __api
#endif

struct iio_context;
struct iio_device;
struct iio_channel;

struct ad9166_calibration_data {
	double *freqs;
	double *offsets;
	double *gains;
	size_t len;
	bool calibrated;
};

/* ---------------------------------------------------------------------------*/
/* ------------------------- Top-level functions -----------------------------*/
/** @defgroup TopLevel Top-level functions
 * @{ */

__api int ad9166_context_find_calibration_data(struct iio_context *ctx,
					       const char *name,
					       struct ad9166_calibration_data **data);

__api int ad9166_channel_set_freq(struct iio_channel *ch,
				  unsigned long long int freq);

__api int ad9166_device_set_amplitude(struct iio_device *dev,
				      long long amplitude);

__api int ad9166_device_set_iofs(struct iio_device *dev,
				 struct ad9166_calibration_data *data,
				 unsigned long long int freq);

__api bool ad9166_device_is_calibrated(struct ad9166_calibration_data *data);

/** @} */

#ifdef __cplusplus
}
#endif

#undef __api

#endif /* __AD9166_H__ */
