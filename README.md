# libad9166-iio

This is a simple library used for userspace,
 - which applies calibration gain and offset for a user-given frequency
 
**Docs**

Doxygen-based documentation is available at: http://analogdevicesinc.github.io/libad9166-iio/


License : [![License](https://img.shields.io/badge/license-LGPL2-blue.svg)](https://github.com/analogdevicesinc/libad9166-iio/blob/libad9166-iio-v0/LICENSE)
Latest Release : [![GitHub release](https://img.shields.io/github/release/analogdevicesinc/libad9166-iio.svg)](https://github.com/analogdevicesinc/libad9166-iio/releases/latest)
Downloads :  [![Github All Releases](https://img.shields.io/github/downloads/analogdevicesinc/libad9166-iio/total.svg)](https://github.com/analogdevicesinc/libad9166-iio/releases/latest)

Build : [![Build and Deploy](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml)
Issues : [![open bugs](https://img.shields.io/github/issues/analogdevicesinc/libad9166-iio.svg)](https://github.com/analogdevicesinc/libad9166-iio/issues)

As with many open source packages, we use [GitHub](https://github.com/analogdevicesinc/libad9166-iio) to develop and maintain the source, and [GitHub Actions](https://github.com/analogdevicesinc/libad9166-iio/actions) for continuous integration.
  - If you want to just use libad9166-iio, we suggest using the [latest release](https://github.com/analogdevicesinc/libad9166-iio/releases/latest).
  - If you think you have found a bug in the release, or need a feature which isn't in the release, try the latest **untested** binaries built by [GitHub Actions](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml). We provide builds for a few operating systems. If you need something else, we can most likely add that -- just ask.

## Latest Builds

Each [GitHub Actions run](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) attaches the per-platform packages as downloadable artifacts.

| Operating System | Status | Version | Installer Package |
|:----------------:|:------:|:-------:|:-----------------:|
| Windows | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Windows-64 (VS 2022) | [![Windows-64](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/win_box.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| macOS | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | macOS 15 (arm64) | [![macOS 15 (arm64)](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/osx_box.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | macOS 15 (x64) | [![macOS 15 (x64)](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/osx_box.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | macOS 26 (arm64) | [![macOS 26 (arm64)](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/osx_box.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | macOS 26 (x64) | [![macOS 26 (x64)](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/osx_box.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | macOS 27 (arm64) | [![macOS 27 (arm64)](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/osx_box.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| Linux | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Ubuntu 22.04 (Jammy)<sup>1</sup> | [![Ubuntu 22.04](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/deb.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Ubuntu 24.04 (Noble)<sup>1</sup> | [![Ubuntu 24.04](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/deb.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Ubuntu 26.04<sup>1</sup> | [![Ubuntu 26.04](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/deb.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Debian 12 (Bookworm) | [![Debian 12](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/deb.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Debian 13 (Trixie) | [![Debian 13](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/deb.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Fedora 42 | [![Fedora 42](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/rpm.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Fedora 44 | [![Fedora 44](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/rpm.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | openSUSE Leap 15.6 | [![openSUSE 15.6](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/rpm.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | openSUSE Leap 16.0 | [![openSUSE 16.0](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/rpm.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| ARM | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Ubuntu 22.04 arm64v8 | [![Ubuntu 22.04 arm64v8](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/deb.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Ubuntu 22.04 arm32v7 | [![Ubuntu 22.04 arm32v7](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/deb.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Ubuntu 26.04 arm64v8 | [![Ubuntu 26.04 arm64v8](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/deb.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Ubuntu 26.04 arm32v7 | [![Ubuntu 26.04 arm32v7](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/deb.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Ubuntu 22.04 ppc64le | [![Ubuntu 22.04 ppc64le](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/deb.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Ubuntu 22.04 s390x | [![Ubuntu 22.04 s390x](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/deb.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Ubuntu 26.04 ppc64le | [![Ubuntu 26.04 ppc64le](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/deb.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Ubuntu 26.04 s390x | [![Ubuntu 26.04 s390x](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/deb.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Debian 12 arm64 | [![Debian 12 arm64](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/deb.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Debian 12 armhf | [![Debian 12 armhf](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/deb.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Debian 13 arm64 | [![Debian 13 arm64](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/deb.png)](https://cloudsmith.io/~adi/repos/external/packages) |
| | [![Build Status](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml/badge.svg?branch=libad9166-iio-v0)](https://github.com/analogdevicesinc/libad9166-iio/actions/workflows/build.yml) | Debian 13 armhf | [![Debian 13 armhf](https://raw.githubusercontent.com/wiki/analogdevicesinc/libiio/img/deb.png)](https://cloudsmith.io/~adi/repos/external/packages) |

1. The Ubuntu packages are known to work on their Debian counterpart releases.

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
