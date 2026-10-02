
$COMPILER=$Env:COMPILER
$ARCH=$Env:ARCH
$BUILD_TYPE=$Env:CMAKE_BUILD_TYPE
if (!$BUILD_TYPE) { $BUILD_TYPE = "Release" }

$src_dir=$pwd

if (!(Test-Path build)) {
	mkdir build
}

cp .\libad9166-iio.iss.cmakein .\build

cd build

cmake -G "$COMPILER" -A "$ARCH" `
        -DLIBIIO_LIBRARIES:FILEPATH=$pwd\libiio.lib `
        -DLIBIIO_INCLUDEDIR:PATH=$pwd `
        -DCMAKE_CONFIGURATION_TYPES=$BUILD_TYPE `
	..

cmake --build . --config $BUILD_TYPE

cp .\libad9166-iio.iss $env:BUILD_ARTIFACTSTAGINGDIRECTORY
