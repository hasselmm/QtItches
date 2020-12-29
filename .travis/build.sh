#!/bin/bash -ex

mkdir build
pushd build

"../5.15.2/${QT_TOOLCHAIN}/bin/qmake" ${QMAKE_FLAGS} ..

popd

if [ "${TRAVIS_PULL_REQUEST}" == "no" ]
then
    echo "Building top-level commit for branch ${TRAVIS_BRANCH}..."
    for target in ${MAKE_TARGETS}; do make -j2 -C build ${target}; done
else
    echo "Building each commit in pull request for branch ${TRAVIS_BRANCH}..."

    git describe --all
    git rebase --exec "for target in qmake_all ${MAKE_TARGETS}; do make -j2 -C build ${target}; done" "${TRAVIS_BRANCH}" HEAD
fi

