#!/bin/sh
CMAKE=/Applications/CMake.app/Contents/bin/cmake
rm -rf _build_ios
mkdir _build_ios
cd _build_ios
$CMAKE -G"Xcode" -DCMAKE_TOOLCHAIN_FILE=../cmake/ios/toolchain/iOS.cmake -DIPHONEOS_DEPLOYMENT_TARGET="9.3" -DBUILD_SHARED_LIBS=Off -DLUA_LIB_DIR=lua-prebuilt/lua-5.3/lib/ios ..
$CMAKE --build . --config Release


