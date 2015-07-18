#!/bin/bash

results=results.log
ip1=128
ip2=118
ip3=0
ip4=0
ip=$ip1.$ip2.$ip3.$ip4
count=0

while true; do
	echo "$count | $ip"
	ping -a -c1 -W500 $ip >> $results &

	ip4=$((ip4+1))
	if [ $ip4 -ge 256 ]; then ip3=$((ip3+1)); ip4=0; fi
	if [ $ip3 -ge 256 ]; then ip2=$((ip2+1)); ip3=0; fi
	if [ $ip2 -ge 256 ]; then ip1=$((ip1+1)); ip2=0; fi
	if [ $ip1 -ge 256 ]; then echo "scan complete."; exit 0; fi
	count=$((count+1))
	ip=$ip1.$ip2.$ip3.$ip4
	sleep 0.05
done
