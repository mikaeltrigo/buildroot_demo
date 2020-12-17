#!/bin/bash

CONFIG_FILE=""
ECS="/opt/powertime/lua/main/pwrt.lua"
ECS_PID="/var/run/pwrt.pid"
ECS_OPTS=""

start_lua_script()
{
    prog=$1
    pid=$2
    args=$3
    cd $(dirname $1)
    lua $prog $args &
    echo $! > $pid
}

case $1 in
start)
	printf "force speed to 100 Mbps "	
	ethtool -s eth1 speed 100 duplex full  autoneg on  
	#printf "set speed cpu t0 333334 Hz "
	#echo 333334  > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed 	
	start_lua_script $ECS $ECS_PID $ECS_OPTS
    	;;

stop)
    start-stop-daemon -K -p $ECS_PID
    ;;

restart)
    $0 stop
    sleep 1
    $0 start
    ;;
*)
    echo "Usage: $0 {start|stop|restart}"
    exit 1
esac

