#!/bin/bash

set -ex
uname -a
DEBIAN_FRONTEND=noninteractive apt install -y make graphviz libaio-dev \
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
# build the libiio binding from source (v0/Azure behavior). pylibiio's setup.py
# hardcodes the x86_64 multiarch path for its libiio check; DESTDIR=/usr/lib (scoped
# to this command, not exported, so it can't affect `make install` below) redirects
# that check to the real multiarch dir, so it also finds libiio on arm/ppc64le/s390x.
DESTDIR=/usr/lib pip_install pylibiio --no-binary :all:
# WITH_DOC defaults ON when Doxygen is present; the python bindings doc build
# needs sphinx + the rtd theme (cmake FATAL_ERRORs otherwise). Matches v0/Azure.
pip_install sphinx sphinx-rtd-theme

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
