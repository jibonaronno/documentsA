#!/bin/sh
chatPhoneNumber=$1
pppdUser=$2
pppdApnName=$3

if [ $# -lt 2 ]
then
	echo "Usage: $0 dialout-number ppp-username apn-name"
	exit 1
fi

pppd debug nodetach \
           connect "chat -T ${chatPhoneNumber} -U ${pppdApnName} -E -v -f /etc/ppp/gprs-connect-chat" \
           disconnect "chat -v -f /etc/ppp/hangup-chat " \
           user ${pppdUser}
PPPD_EXIT_CODE=$?

echo $PPPD_EXIT_CODE > /tmp/pppd_return_code

