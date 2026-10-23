## :warning: Important note

The main branch of this repository now depends on [libiio](https://github.com/analogdevicesinc/libiio) v1.0.0, which features a brand new API that is incompatible with libiio v0.26 and older.

If you need to build libad9166-iio against the old v0.x API of libiio, please use the [libad9166-iio-v0](https://github.com/analogdevicesinc/libad9166-iio/tree/libad9166-iio-v0) branch, which will continue to exist and receive bug fixes, though it will not receive new features. The corresponding v0.x API of libiio can be found on the [libiio-v0](https://github.com/analogdevicesinc/libiio/tree/libiio-v0) branch, or as packages on the release section of the libiio repository.

# libad9166-iio

This is a simple library used for userspace,
 - which applies calibration gain and offset for a user-given frequency

**Dependencies**

 - [libiio IIO interface library (Version 1.0.0 or greater)](https://github.com/analogdevicesinc/libiio)

**Docs**

Doxygen-based documentation is available at: http://analogdevicesinc.github.io/libad9166-iio/


License : [![License](https://img.shields.io/badge/license-LGPL2-blue.svg)](https://github.com/analogdevicesinc/libad9166-iio/blob/master/COPYING.txt)
Latest Release : [![GitHub release](https://img.shields.io/github/release/analogdevicesinc/libad9166-iio.svg)](https://github.com/analogdevicesinc/libad9166-iio/releases/latest)
Downloads :  [![Github All Releases](https://img.shields.io/github/downloads/analogdevicesinc/libad9166-iio/total.svg)](https://github.com/analogdevicesinc/libad9166-iio/releases/latest)

As with many open source packages, we use [GitHub](https://github.com/analogdevicesinc/libad9166-iio) to do develop and maintain the source, and [Azure Pipelines](https://azure.microsoft.com/en-gb/services/devops/pipelines/) for continuous integration.
  - If you want to just use libad9166-iio, we suggest using the [latest release](https://github.com/analogdevicesinc/libad9166-iio/releases/latest).
  - If you think you have found a bug in the release, or need a feature which isn't in the release, try the latest **untested** binaries from the master branch. We provide builds for a few operating systems. If you need something else, we can most likely add that -- just ask.


If you use it, and like it - please let us know. If you use it, and hate it - please let us know that too. The goal of the project is to try to make Linux IIO devices easier to use on a variety of platforms. If we aren't doing that - we will try to make it better.


## Building & Installing libad9166 on LINUX

```
cd libad9166-iio/
sudo cmake ./CMakeLists.txt
sudo make
sudo make install
```

## Building & Installing python bindings on LINUX
```
cd bindings/python
sudo pip install -r requirements_dev.txt
cmake ./CMakeLists.txt
sudo make
sudo make install
```
