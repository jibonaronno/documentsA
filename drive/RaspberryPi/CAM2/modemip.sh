#!/bin/bash
pppstr=$(ifconfig | grep wlan0)
if [[ $pppstr == *"wlan0"* ]]; then
    IP=$(ifconfig wlan0 | grep inet | cut -d: -f2 |awk '{print $2}') #IP assigned post connected to ppp0 VPN
    #echo $IP  #echos ppp0 IP
    if [[ $IP == *"Device not found"* ]]; then
        echo "NA"
    else
        echo $IP
    fi
else
    echo "NA"
fi
