import iio
import ad9166

ctx = iio.Context("local:")
dev = ctx.find_device("ad9166")
ch = dev.find_channel("altvoltage0", True)

ad9166.set_amplitude(dev, -10)
ad9166.set_frequency(ch, 3000000000)

data = ad9166._POINTER(ad9166.CalibrationParameters)()

ad9166.find_calibration_data(ctx, "cn0511", data)

print(data.contents.Freqs.contents)

ad9166.device_set_iofs(dev, data, 3000000000)
