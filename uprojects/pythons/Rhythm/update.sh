#!/bin/bash
cd /home/pi/Rhythm
git reset --hard origin/v1.9.4
git pull origin v1.9.4
chmod 777 k2_rythm.py
chmod 777 log.txt
cp /home/pi/Rhythm/* /home/pi
