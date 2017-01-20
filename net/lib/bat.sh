#! /bin/bash

make clean
make
../test/phyTeset.rb
sleep 1
#../test/phyTeset.rb
#dmesg > zz
#vi zz

