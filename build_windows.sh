#!/bin/sh
rm -rf _build_windows_x86
mkdir _build_windows_x86
cd _build_windows_x86
cmake -G"Visual Studio 14 2015" -DLUA_LIB_DIR=lua-prebuilt/lua-5.3/lib/windows/x86 ..
cmake --build . --config Release

cd ..

rm -rf _build_windows_x86_64
mkdir _build_windows_x86_64
cd _build_windows_x86_64
cmake -G"Visual Studio 14 2015 Win64" -DLUA_LIB_DIR=lua-prebuilt/lua-5.3/lib/windows/x86_64 ..
cmake --build . --config Release

