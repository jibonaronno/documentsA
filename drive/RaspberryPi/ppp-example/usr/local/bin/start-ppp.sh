#!/bin/sh
if [ $# -lt 3 ]
then
	echo "Usage: $0 ppp-number ppp-username ppp-password apn"
	exit 1
fi	

chatPhoneNumber=$1
pppdUser=$2
pppdPassword=$3
pppdApnName=$4

echo 
echo "Phone# ${chatPhoneNumber} | PPP-Username = ${pppdUser} | PPP-Password = ${pppdPassword} | APN = ${pppdApnName}"
echo 


# Setup PPP Password files
umask 0066
echo "${pppdUser} * ${pppdPassword}" > /etc/ppp/chap-secrets
echo "${pppdUser} * ${pppdPassword}" > /etc/ppp/pap-secrets

# Dial out
rm -f /tmp/pppd_return_code
/usr/local/bin/dialout.sh ${chatPhoneNumber} ${pppdUser} ${pppdApnName} &


# Wait to see if it is successful
while true
do
	if [ -e /tmp/pppd_return_code ]
	then
		PPPD_CODE=$(cat /var/run/pppd_return_code)
                echo "*******************************************"
		echo "  Error: pppd returned ${PPPD_CODE}"
                echo "  See 'man pppd' for details" 
                echo "******************************************"
		exit ${PPPD_CODE}
		
	fi
	
	PPP_STR=$(/sbin/ifconfig | grep ppp0)
        if test -n "$PPP_STR"
	then
                echo "+++++++++++++++++++++++++++++++++++++++++++++++"
		echo "       PPP Link established"
                echo "+++++++++++++++++++++++++++++++++++++++++++++++"
		exit 0
	fi

	sleep 1
done
