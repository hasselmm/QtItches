#!/bin/bash -e

HOST="$1"
VERSION="$2"
PLATFORM="$3"

dirname="android-ndk-${VERSION}"
filename="android-ndk-${VERSION}-${HOST}.zip"

curl --fail --location --remote-name "https://dl.google.com/android/repository/${filename}"

unzip -o "${filename}" "${dirname}/build/*"
unzip -o "${filename}" "${dirname}/meta/*"
unzip -o "${filename}" "${dirname}/ndk-*"
unzip -o "${filename}" "${dirname}/platforms/android-19/arch-arm/*"
unzip -o "${filename}" "${dirname}/python-packages/*"
unzip -o "${filename}" "${dirname}/sysroot/*"
unzip -o "${filename}" "${dirname}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/*"

rm "${filename}"
