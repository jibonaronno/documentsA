raspivid -t 0 -fps 25 -hf -b 2000000 -o - | ffmpeg -i - -vcodec copy -an -r 30 -g 30 -bufsize 2000000 -pix_fmt yuv420p -f flv rtmp://live.justin.tv/app/live_605378794_tsTzwiBUXhzSKUNKtYISGFDZ21D6Ga

ffmpeg -f video4linux2 -r 25 -s 640x480 -i /dev/video0 -f flv -| ffmpeg -i - -vcodec copy -f flv rtmp://live.justin.tv/app/live_605378794_tsTzwiBUXhzSKUNKtYISGFDZ21D6Ga
