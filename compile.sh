#! /bin/sh
make
./bin/run
python3 compare.py
code data.PNG