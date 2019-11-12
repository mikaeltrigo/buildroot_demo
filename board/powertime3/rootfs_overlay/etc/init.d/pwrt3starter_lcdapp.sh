#!/bin/sh

LOGFILE=/root/logLCDapp.txt

date >> $LOGFILE
/usr/bin/pwrt3lcdapp >> $LOGFILE 2>&1




