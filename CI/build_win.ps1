
$COMPILER=$Env:COMPILER
$ARCH=$Env:ARCH
$BUILD_TYPE=if ($Env:CMAKE_BUILD_TYPE) { $Env:CMAKE_BUILD_TYPE } else { "Release" }

$src_dir=$pwd

if (!(Test-Path build)) {
	mkdir build
}

cd build

cmake -G "$COMPILER" -A "$ARCH" `
        -DLIBIIO_LIBRARIES:FILEPATH=$pwd\libiio.lib `
        -DLIBIIO_INCLUDEDIR:PATH=$pwd `
	..

cmake --build . --config $BUILD_TYPE

if ( $LASTEXITCODE -ne 0 ) {
	throw "[*] cmake build failure"
}

cp .\libad9166-iio.iss $env:BUILD_ARTIFACTSTAGINGDIRECTORY
