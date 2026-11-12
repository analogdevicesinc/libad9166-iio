# https://docs.microsoft.com/en-us/powershell/module/microsoft.powershell.core/about/about_preference_variables?view=powershell-7.2#erroractionpreference
$ErrorActionPreference = "Stop"
$ErrorView = "NormalView"

$src_dir=$pwd

# VS2022 redist; the version and VC14x.CRT folders shift with the runner toolset, so glob for the newest.
cd (Get-ChildItem 'C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Redist\MSVC\*\x64\Microsoft.VC*.CRT' -Directory | Sort-Object FullName -Descending | Select-Object -First 1).FullName
cp .\msvcp140.dll $env:BUILD_ARTIFACTSTAGINGDIRECTORY
cp .\vcruntime140.dll $env:BUILD_ARTIFACTSTAGINGDIRECTORY

cd $src_dir

cp .\build\libxml2.dll $env:BUILD_ARTIFACTSTAGINGDIRECTORY
cp .\build\libserialport-0.dll $env:BUILD_ARTIFACTSTAGINGDIRECTORY
cp .\build\libusb-1.0.dll $env:BUILD_ARTIFACTSTAGINGDIRECTORY
