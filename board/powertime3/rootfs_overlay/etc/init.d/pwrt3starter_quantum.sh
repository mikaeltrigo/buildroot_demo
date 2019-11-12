#!/bin/sh

LOGFILE=/root/logQuantum.txt
printf "make fifo\n"
mkfifo /tmp/rxQuantum
mkfifo /tmp/txQuantum
mkfifo /tmp/printerQuantum
mkfifo /tmp/gpsQuantum
mkfifo /tmp/RT1
date >> $LOGFILE
/usr/bin/Quantum >> $LOGFILE 2>&1




