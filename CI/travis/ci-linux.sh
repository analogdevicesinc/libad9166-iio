#!/bin/bash

set -x

handle_centos() {
	local package=$1

	yum -y install yum-utils gcc
	yum config-manager --set-enabled powertools

	pwd

	cd /opt
	wget https://www.python.org/ftp/python/3.5.1/Python-3.5.1.tgz
	tar xzf Python-3.5.1.tgz
	cd Python-3.5.1
	./configure
	make altinstall
	cd /ci

	ls -al /usr/local/lib

	yum -y install epel-release

	yum -y install bzip2 gzip

	yum localinstall -y $package

	python3.5 -m pip install pylibiio --no-binary :all:

	# Build project
	sudo ln -fs /usr/bin/python3.5 /usr/bin/python
	python3.5 -m ensurepip
	mkdir -p build
	cd build
	cmake -DPYTHON_BINDINGS=ON -DENABLE_PACKAGING=ON ..
	sudo make && sudo make package && make test
	sudo make install
	ldconfig
	cd ..
	cd bindings/python
	pip install -r requirements_dev.txt
	export LD_LIBRARY_PATH=/usr/local/lib/
	python3.5 -m pip install pytest
	python3.5 -m pytest -vs --skip-scan
}

handle_default() {
	local package=$1

	DEBIAN_FRONTEND=noninteractive apt-get install -y rpm

	sudo dpkg -i $package

	python3 -m pip install pylibiio --no-binary :all:

	# Build project
	mkdir -p build
	cd build
	sudo cmake -DPYTHON_BINDINGS=ON -DENABLE_PACKAGING=ON -DDEB_DETECT_DEPENDENCIES=ON ..
	sudo make && make package && make test
	sudo make install
	ldconfig
	cd ..
	cd bindings/python
	pip3 install -r requirements_dev.txt
	python3 -m pytest -vs --skip-scan
}

handle_"$1" "$2"
