#!/bin/bash
if [[ -e /Volumes/CrashplanLGRC\ 1 ]]; then
    echo An extra directory was found
    VOL=$(ls -l /Volumes)
    printf "In the volumes folder, the following files were detected: \n\n$VOL. \n\nThe server will now attempt to reboot itself." > /tmp/CrashplanLGRC-report.txt
    mail -s 'CrashLGRC multiple volume error detected' rt_unix@server.com < /tmp/CrashplanLGRC-report.txt
    rm /tmp/CrashplanLGRC-report.txt
    sleep 10
    reboot
fi​
