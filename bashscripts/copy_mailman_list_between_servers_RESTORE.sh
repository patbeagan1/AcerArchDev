#!/bin/bash
# This script restores list archives created by mailman-interserver-send.sh
# Make sure that the archives are in /tmp/mailman-transfer before running.
# Also verify that the data, list, archives are in the /var/lib/mailman
# folder. this my be different depending on your configuration.

#####moving all the files to the correct folder
cd /tmp/mailman-transfer
if [ ! -e mmarchives ]; then
echo -e "\nMake sure that you back up files before attempting to restore.\n"
exit;
fi
cp mm* /var/lib/mailman

#####this next line should go to the directory which holds 
#####archives, lists and data for mailman
#####unzipping the archives
cd /var/lib/mailman
tar -xvf mmdata
tar -xvf mmarchives
tar -xvf mmlists
chown -R nobody:mailman .
chmod -R a+rx,g+ws .
rm mm*

#####for each list in the list folder, fix links
cd /var/lib/mailman/lists
for list in *; do
echo list $list
~mailman/bin/withlist -l -r fix_url $list -v
done
rm -r /tmp/mailman-transfer
echo -e "\n########updating the aliases file by appending"
cd /usr/lib/mailman/bin
echo -e "
#############
######$(date)
#############" >> /etc/aliases.mailman
./genaliases | tail --lines=+4 >> /etc/aliases.mailman
/usr/bin/newaliases
echo -e	"\nRestore complete\n"
