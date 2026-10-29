#!/bin/bash

set -ex
uname -a
DEBIAN_FRONTEND=noninteractive apt install -y make libaio-dev \
	libavahi-client-dev libavahi-common-dev libusb-1.0-0-dev \
	rpm tar bzip2 gzip libserialport-dev python3-pip
dpkg -i /ci/build/*.deb
# refresh the loader cache so the just-installed libiio (its CPack .deb doesn't
# run ldconfig) is discoverable at runtime
ldconfig

pip_install() {
	python3 -m pip install "$@" --break-system-packages 2>/dev/null || python3 -m pip install "$@"
}

pip_install setuptools wheel
pip_install pylibiio

echo "$PWD"

mkdir -p build
cd build
cmake -DPYTHON_BINDINGS=ON -DENABLE_PACKAGING=ON -DDEB_DETECT_DEPENDENCIES=ON \
	-DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE:-Release}" -DCPACK_SYSTEM_NAME="${ARTIFACTNAME}" ..
make && make package && make test
make install
ldconfig
export LD_LIBRARY_PATH=/usr/local/lib:${LD_LIBRARY_PATH:-}
cd ../bindings/python
pip_install -r requirements_dev.txt
python3 -m pytest -vs --skip-scan
