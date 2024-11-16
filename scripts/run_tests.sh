#!/bin/bash

cd test/
make clean
make

if [ -f udf_test ]; then
  ./udf_test
else
  echo "udf_test executable not found."
fi
