#!/bin/bash
if [ $# -ne 1 ]; then
  echo "Usage: $0 <udf_source_file.cpp>"
  exit 1
fi

UDF_SOURCE=$1
UDF_LIB=$(basename "$UDF_SOURCE" .cpp).so

g++ -shared -fPIC -o "$UDF_LIB" "$UDF_SOURCE" -I../src/include
