#!/bin/bash
# This script is used to transfer mailman lists between machines
# It operates in tandem with mailman-interserver-restore.sh
#####destination should stay at /tmp to match with restore script
dest=pbeagan@server.com:/tmp

#####if there are no arguments, assume moving all lists
if [ $# -eq 0 ]; then
mkdir /root/mailman-transfer
cd ~mailman
tar -cpvW -f /root/mailman-transfer/mmdata ./data
tar -cpvW -f /root/mailman-transfer/mmarchives ./archives
tar -cpvW -f /root/mailman-transfer/mmlists ./lists

#####if there is an agument (list) only move that list
else
mkdir /root/mailman-transfer
cd ~mailman
tar -cpvW -f /root/mailman-transfer/mmdata ./data
tar -cpvW -f /root/mailman-transfer/mmarchives ./archives/public/$1 ./archives/private/$1*
tar -cpvW -f /root/mailman-transfer/mmlists ./lists/$1
fi
echo $dest
scp -r /root/mailman-transfer $dest
read -p "Delete the temporary mailman-transfer folder?" yn
    case $yn in
        [Yy]* ) rm -r /root/mailman-transfer;;
        [Nn]* ) exit;;
        * ) echo "Yes or no.";;
    esac
