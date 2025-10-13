#!/bin/bash

ffmpeg -re -f video4linux2 -i /dev/video0 -vcodec copy -an -r 30 -g 30 -bufsize 2000000 -pix_fmt yuv420p -f flv rtmp://live.justin.tv/app/live_605378794_tsTzwiBUXhzSKUNKtYISGFDZ21D6Ga

rtmp://a.rtmp.youtube.com/live2/hped-m8g1-ft48-zkfm-7h8b