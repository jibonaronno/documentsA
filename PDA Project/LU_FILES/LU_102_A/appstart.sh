#!/bin/sh


echo "";
echo "";
echo "appstart script start!!!";
echo "";
echo "";


ifconfig eth0 192.168.10.102 up;
mount 192.168.10.12:nfs_resource nfs_client
#mount 192.168.10.15:nfs_resource nfs_resource
