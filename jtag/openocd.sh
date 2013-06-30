#!/bin/bash

if [ z$1 = z ]; then
  echo "Please specify jtag board type as first argument"
  exit 1
fi
openocd -f configs/$1.cfg -f configs/raspi.cfg
