#!/bin/bash -e

QT_HOST="$1"
QT_TARGET="$2"
QT_TOOLCHAIN="$3"
QT_VERSION="$4"
QT_EDITION="OpenSource"
QT_REPOSITORY="http://download.qt.io/online/qtsdkrepository/"

shift 4

print_usage() {
    echo "Usage: $(basename "$0") HOST TARGET TOOLCHAIN VERSION"
    echo "$1"
}

download() {
    echo "Downloading '$1'..."
    curl --fail --silent --show-error --location --remote-name "$1" || { echo "Could not download '$1'" >&2; exit 1; }
}

case "${QT_HOST}" in
linux_x64|linux_x86|mac_x64|windows_x86);;
*) print_usage "Invalid SDK host" >&2; exit 2;;
esac

case "${QT_TARGET}" in
android|desktop|ios|winrt);;
*) print_usage "Invalid SDK target" >&2; exit 2;;
esac

case "${QT_TOOLCHAIN}" in
android_armv7|android_x86|gcc|gcc_64|win32_mingw*|win32_msvc*|ioswin64_msvc2015_winrt_armv|7win64_msvc2015_winrt_x64|win64_msvc2017_winrt_x86);;
*) print_usage "Invalid SDK toolchain" >&2; exit 2;;
esac

case "${QT_VERSION}" in
[0-9]*\.[0-9]*\.[0-9]*);;
*) print_usage "Invalid SDK version" >&2; exit 2;;
esac

QT_VERSION_CODE="${QT_VERSION//./}"
QT_BASEURL="${QT_REPOSITORY}${QT_HOST}/${QT_TARGET}/qt5_${QT_VERSION_CODE}/"

download "${QT_BASEURL}Updates.xml"

package_folder="qt.qt5.${QT_VERSION_CODE}.${QT_TOOLCHAIN}"
package_node="/Updates/PackageUpdate[Name/text() = '${package_folder}' and position() = 1]"
package_prefix=$(xmllint Updates.xml --xpath "${package_node}/Version/text()")

if [ -z "${package_prefix}" ]
then
    echo "Could not find update information for '${package_folder}'" >&2
    exit 1
fi

for package_name in "$@"
do
    package_suffix=$(xmllint Updates.xml --xpath "substring-before(substring-after(concat(${package_node}/DownloadableArchives/text(), ','), '${package_name}-'), ',')")
    package_filename="${package_prefix}${package_name}-${package_suffix}"
    download "${QT_BASEURL}${package_folder}/${package_filename}"
    p7zip -d "${package_filename}"
done

sed -ie "s/^\(QT_EDITION\\s*=\\s*\).*/\1${QT_EDITION}/" "${QT_VERSION}/${QT_TOOLCHAIN}/mkspecs/qconfig.pri"
cp "$(dirname "$0")/qt.conf" "${QT_VERSION}/${QT_TOOLCHAIN}/bin/"
