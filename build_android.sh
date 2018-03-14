#!/bin/sh
rm -rf _build_android
mkdir _build_android
cd _build_android
export ANDROID_NDK="d:/opt/Android/sdk/ndk-bundle"
export CMAKE_MAKE_PROGRAM="$ANDROID_NDK/prebuilt/windows-x86_64/bin/make.exe"
export CMAKE_TOOLCHAIN_FILE="../cmake/android/android.toolchain.cmake"
export PROJECT_PATH=".."
cmake -G"MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=$CMAKE_TOOLCHAIN_FILE -DCMAKE_MAKE_PROGRAM=$CMAKE_MAKE_PROGRAM -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="armeabi-v7a" -DANDROID_NATIVE_API_LEVEL=android-15 -DLUA_LIB_DIR=lua-prebuilt/lua-5.3/lib/android/armeabi-v7a $PROJECT_PATH
cmake --build .
