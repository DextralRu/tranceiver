#!/bin/bash
clear
MYPATH=/opt/avr-toolchain/bin
export PATH=$MYPATH:$PATH
echo $PATH
make $1