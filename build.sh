#!/bin/bash -e

function make_dir() {
  rm -rf $1
  mkdir -p $1
}

if [[ $(uname) == 'Darwin' ]]; then
  echo $(uname)
  BUILD_DIR="mac_out"
  PLATFORM="mac"
elif [[ $(uname) == 'Linux' ]]; then
  BUILD_DIR="linux_out"
  PLATFORM="linux"
fi

make_dir $BUILD_DIR

cd $BUILD_DIR

cmake -DPAG_BUILD_SHARED=ON -DCMAKE_BUILD_TYPE=Release ../

RETURN_CODE=$?
if [ "$RETURN_CODE" -eq "0" ]
then
  echo "cmake success"
else
  echo "cmake failed"
  exit 1
fi

cmake --build . --target pag -- -j 12
RETURN_CODE=$?
if [ "$RETURN_CODE" -eq "0" ]
then
  echo "compile success"
else
  echo "compile failed"
  exit 1
fi

cd ..

make_dir lib/include
cp -a include/* lib/include

make_dir lib/x64
if [[ $(uname) == 'Darwin' ]]; then
make_dir linux/vendor/pag/$PLATFORM/x64
cp -a $BUILD_DIR/libpag.dylib lib/x64
elif [[ $(uname) == 'Linux' ]]; then
make_dir linux/vendor/pag/$PLATFORM/x64
cp -a $BUILD_DIR/libpag.a linux/vendor/pag/$PLATFORM/x64
fi

#rm -rf $BUILD_DIR


