#!/bin/bash
trans=`./script008.sh $1 $2`
rsync -rvz -e 'ssh -p 3231' --progress $trans
#rsync -rvz -e 'ssh -p 3231' --progress $trans

#	Here in Line:2 trans is assigned with the commands, $1 is the first argument and $2 is the second argument.
#	Example : [ ./xfr.sh links.list scripts_commands ] . links.list is a file where source and destination are
#	saved and "scripts_commands" is the header text of the information row in that file. 
