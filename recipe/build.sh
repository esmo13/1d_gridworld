#!/bin/bash
mkdir build
cd build

cmake -DCMAKE_INSTALL_PREFIX=$PREFIX \
      -DCMAKE_BUILD_TYPE=RELEASE \
      ..
make -j${CPU_COUNT}
make install