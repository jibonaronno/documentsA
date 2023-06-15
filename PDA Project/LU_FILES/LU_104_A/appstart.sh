#!/bin/sh


echo "";
echo "";
echo "appstart script start!!!";
echo "";
echo "";

### QT Environment Variables ###
export SSL_CERT_FILE=/etc/ssl/certs/ca-certificates.crt
export LD_LIBRARY_PATH="/lib:/apps:/usr/tslib/lib";
export QT_PLUGIN_PATH=/usr/lib/qt5/plugins;
export QT_QPA_PLATFORM=linuxfb;
export QT_QPA_PLUGIN="tslib";
export QT_QPA_FB_TSLIB="1";
export QT_QPA_FONTDIR="/usr/share/fonts/ttf";
export QT_QPA_GENERIC_PLUGINS=tslib:/dev/input/event0;
export QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS=/dev/input/event0;
export QWS_DISPLAY="LinuxFB:mmWidth=800:mmHeight=480";
export QWS_MOUSE_PROTO=tslib:$TSLIB_TSDEVICE
export LANG="ko_KR.UTF-8";


fbset -g 800 480 800 480 32;

### TSLIB Env Setting ####
export PS1="\u@\h:\w\$ "
export TSLIB_TSDEVICE=/dev/input/event0
export TSLIB_CONFFILE=/usr/tslib/etc/ts.conf
export TSLIB_CALIBFILE=/data/pointercal
export TSLIB_PLUGINDIR=/usr/tslib/lib/ts
export TSLIB_TSEVENTTYPE='INPUT'
export TSLIB_FBDEVICE='/dev/fb0'

#ethtool -s eth0 autoneg on speed 100 duplex full;
sleep 2;
ifconfig eth0 192.168.10.104 up;


cd /apps;
#./LU_MPU_FW;


#/bin/login -f root
/bin/sh
