#!/bin/sh
MOUNTPOINT=~/projects/_pi
mkdir -p $MOUNTPOINT
sshfs pi@192.168.0.197:/home/pi $MOUNTPOINT

