#!/bin/bash
sudo pon rnet
sleep 2
pppstr=$(ifconfig | grep ppp0)
if [[ $pppstr == *"ppp0"* ]]; then
    IP=$(ifconfig ppp0 | grep inet | cut -d: -f2 |awk '{print $2}') #IP assigned post connected to ppp0 VPN
    #echo $IP  #echos ppp0 IP
    if [[ $IP == *"Device not found"* ]]; then
        echo "NA"
    else
        echo $IP
    fi
else
    echo "NA"
fi
