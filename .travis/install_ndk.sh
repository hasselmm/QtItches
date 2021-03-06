#!/bin/bash -e

HOST="$1"
VERSION="$2"
PLATFORM="$3"

dirname="android-ndk-${VERSION}"
filename="android-ndk-${VERSION}-${HOST}.zip"

curl --fail --location --remote-name "https://dl.google.com/android/repository/${filename}"

unzip -o "${filename}" \
    "${dirname}/build/**" \
    "${dirname}/meta/**" \
    "${dirname}/ndk-*" \
    "${dirname}/platforms/${PLATFORM}/arch-arm/**" \
    "${dirname}/python-packages/**" \
    "${dirname}/sources/cxx-stl/**" \
    "${dirname}/sysroot/**" \
    "${dirname}/toolchains/llvm/prebuilt/linux-x86_64/**"
rm "${filename}"
