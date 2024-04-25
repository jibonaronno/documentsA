#!/bin/bash
#
# ntpd        This shell script takes care of starting and stopping ntpd.
#
# chkconfig: - 58 74
# description: ntpd is the NTP daemon. It synchronizes the system clock \
#              with remote NTP servers.
# processname: ntpd

# Source function library.
# . /etc/init.d/functions

# Source networking configuration.
# . /etc/sysconfig/network

# 

# Check that networking is up.
[ ${NETWORKING} = "no" ] && exit 0

[ -x /usr/sbin/ntpd ] || exit 0

RETVAL=0
prog="ntpd"

start() {
    echo -n $"Starting $prog: "
    daemon $prog -u ntp:ntp
    RETVAL=$?
    echo
    [ $RETVAL -eq 0 ] && touch /var/lock/subsys/$prog
    return $RETVAL
}

stop() {
    echo -n $"Stopping $prog: "
    killproc $prog
    RETVAL=$?
    echo
    [ $RETVAL -eq 0 ] && rm -f /var/lock/subsys/$prog
    return $RETVAL
}

reload() {
    echo -n $"Reloading $prog: "
    killproc $prog -HUP
    RETVAL=$?
    echo
    return $RETVAL
}

case "$1" in
    start)
        start
        ;;
    stop)
        stop
        ;;
    restart|reload)
        stop
        start
        RETVAL=$?
        ;;
    *)
        echo $"Usage: $0 {start|stop|restart|reload}"
        exit 1
esac

exit $RETVAL
