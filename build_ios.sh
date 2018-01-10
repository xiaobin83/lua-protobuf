#!/bin/sh
CMAKE=/Applications/CMake.app/Contents/bin/cmake
rm -rf _build_ios
mkdir _build_ios
cd _build_ios
$CMAKE -G"Xcode" -DCMAKE_TOOLCHAIN_FILE=../cmake/ios/toolchain/iOS.cmake -DBUILD_SHARED_LIBS=Off -DUSE_PORTABLE_ENDIAN=On -DLUA_LIB_DIR=prebuilt/lua-5.3/lib/ios ..
$CMAKE --build . --config Release


