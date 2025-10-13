ffmpeg -i vid.mp4 -vcodec copy -an -r 10 -g 20 -bufsize 8000000 -pix_fmt yuv420p -f flv rtmp://live.justin.tv/app/live_605378794_tsTzwiBUXhzSKUNKtYISGFDZ21D6Ga

ffmpeg -i vid.mp4 -vcodec copy -f flv rtmp://live.justin.tv/app/live_605378794_tsTzwiBUXhzSKUNKtYISGFDZ21D6Ga

rtmp://a.rtmp.youtube.com/live2/abr2-eykk-ea6j-bpyg-6rt0

ffmpeg -i vid.mp4 -vcodec copy -c:v:1 libx264 -f flv rtmp://a.rtmp.youtube.com/live2/abr2-eykk-ea6j-bpyg-6rt0

ffmpeg -f video4linux2 -r 25 -s 640x480 -i /dev/video0 - | ffmpeg -i - -vcodec copy -c:v:1 libx264 -f flv rtmp://a.rtmp.youtube.com/live2/abr2-eykk-ea6j-bpyg-6rt0

#not working
ffmpeg -f video4linux2 -r 30 -i /dev/video0 -b:v 350k -f flv rtmp://a.rtmp.youtube.com/live2/abr2-eykk-ea6j-bpyg-6rt0