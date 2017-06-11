#!/usr/bin/env bash
find . -iname "*.so" -exec rm -R {} \;
rm -rf obj
rm -rf build
rm -rf app/build
