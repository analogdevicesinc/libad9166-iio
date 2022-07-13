import pytest

import iio
import ad9166


@pytest.mark.iio_hardware(["ad9166"])
def test_set_calibrated_amplitude_frequency(iio_uri):
    ctx = iio.Context(iio_uri)
    dev = ctx.find_device("ad9166")

    ch = dev.find_channel("altvoltage0", True)

    ad9166.set_amplitude(dev, -10)
    ad9166.set_frequency(ch, 3000000000)

    data = ad9166.find_calibration_data(ctx, "cn0511")

    print(data.contents.Freqs.contents)

    ad9166.device_set_iofs(dev, data, 3000000000)
