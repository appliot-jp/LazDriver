#! /bin/bash

make clean
make
../test/phyTeset.rb
sleep 1
dmesg > log
vi log

