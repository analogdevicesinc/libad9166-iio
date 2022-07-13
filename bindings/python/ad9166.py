#!/usr/bin/env python
# SPDX-License-Identifier: LGPL-2.1-or-later
# Copyright (C) 2021 Analog Devices, Inc.
# Author: Antoniu Miclaus <antoniu.miclaus@analog.com>

from typing import List
import math

import iio
from iio import _ContextPtr, _DevicePtr, _ChannelPtr

# Imports from package ctypes are not grouped
# pylint: disable=ungrouped-imports
#
# The way the methods and classes are used, violate this, but there
#   isn't a good way to do things otherwise
# pylint: disable=protected-access
from ctypes import (
    byref,
    c_ubyte,
    c_double,
    c_int,
    c_char,
    c_longlong,
    c_ulonglong,
    c_short,
    c_uint,
    c_ulong,
    c_char_p,
    c_size_t,
    CDLL as _cdll,
    POINTER as _POINTER,
    Structure,
)
from ctypes.util import find_library
from os import strerror as _strerror
from platform import system as _system

if "Windows" in _system():
    from ctypes import get_last_error
else:
    from ctypes import get_errno
# pylint: enable=ungrouped-imports

# ctypes requires the errcheck to take three arguments, but we don't use them
# pylint: disable=unused-argument


def _check_negative(result, func, arguments):
    if result >= 0:
        return result
    raise OSError(-result, _strerror(-result))


if "Windows" in _system():
    _libad9166 = "libad9166.dll"
else:
    # Non-windows, possibly Posix system
    _libad9166 = "ad9166"

_lib = _cdll(find_library(_libad9166), use_errno=True, use_last_error=True)

class CalibrationParameters(Structure):
     _fields_ = [
        ("Freqs", _POINTER(c_double)),
        ("Offsets", _POINTER(c_double)),
        ("Gains", _POINTER(c_double)),
        ("Len", c_size_t),
    ]

_ad9166_context_find_calibration_data = _lib.ad9166_context_find_calibration_data
_ad9166_context_find_calibration_data.restype = c_int
_ad9166_context_find_calibration_data.argtypes = (_ContextPtr, _POINTER(c_char), _POINTER(_POINTER(CalibrationParameters)))
_ad9166_context_find_calibration_data.errcheck = _check_negative

_ad9166_device_set_amplitude = _lib.ad9166_device_set_amplitude
_ad9166_device_set_amplitude.restype = c_int
_ad9166_device_set_amplitude.argtypes = (_DevicePtr, c_longlong)
_ad9166_device_set_amplitude.errcheck = _check_negative

_ad9166_channel_set_frequency = _lib.ad9166_channel_set_freq
_ad9166_channel_set_frequency.restype = c_int
_ad9166_channel_set_frequency.argtypes = (_ChannelPtr, c_ulonglong)
_ad9166_channel_set_frequency.errcheck = _check_negative

_ad9166_device_set_iofs = _lib.ad9166_device_set_iofs
_ad9166_device_set_iofs.restype = c_int
_ad9166_device_set_iofs.argtypes = (_DevicePtr, _POINTER(CalibrationParameters), c_ulonglong)
_ad9166_device_set_iofs.errcheck = _check_negative


def find_calibration_data(ctx: iio.Context, name: str):
    """Calibration configuration.
    :param: iio.Context dev: IIO Context of AD9166 driver
    :param str name: Desired name of the device
    :return: CalibrationParameters: Calibration parameters
    """

    data = _POINTER(CalibrationParameters)()

    ret = _ad9166_context_find_calibration_data(
        ctx._context, c_char_p(str(name).encode("utf-8")), byref(data)
    )

    if ret != 0:
        raise Exception(f"Loading Calibration data failed. ERROR: {ret}")

    return data


def set_amplitude(dev: iio.Device, amplitude: int):
    """Amplitude configuration.
    :param: iio.Device dev: IIO Device object of AD9166 driver
    :param int amplitude: Desired amplitude between 0dB and -91dB
    """
    if math.trunc(amplitude) != amplitude:
        raise Exception("amplitude must be an integer")

    ret = _ad9166_device_set_amplitude(dev._device, c_longlong(int(amplitude)))

    if ret != 0:
        raise Exception(f"Setting amplitude failed. ERROR: {ret}")


def set_frequency(ch: iio.Channel, frequency: int):
    """Frequency configuration.
    :param: iio.Channel dev: IIO Channel object of AD9166 driver
    :param int frequency: Desired frequency
    """
    if math.trunc(frequency) != frequency:
        raise Exception("frequency must be an integer")

    ret = _ad9166_channel_set_frequency(ch._channel, c_ulonglong(int(frequency)))

    if ret != 0:
        raise Exception(f"Setting frequency failed. ERROR: {ret}")


def device_set_iofs(dev: iio.Device, data: CalibrationParameters, frequency: int):
    """IOFS configuration.
    :param: iio.Device dev: IIO Device object of AD9166 driver
    :param CalibrationParameters data: Calibration parameters
    :param int frequency: Desired frequency
    """
    if math.trunc(frequency) != frequency:
        raise Exception("frequency must be an integer")

    ret = _ad9166_device_set_iofs(dev._device, data, c_ulonglong(int(frequency)))
    if ret != 0:
        raise Exception(f"Setting IOFS failed. ERROR: {ret}")
