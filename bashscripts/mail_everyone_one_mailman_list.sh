#!/bin/bash
cd /nfs/loki/staff1/MD/majordomo/lists
#cd ~majordom/lists
file=$(ls *.config   |grep -v old | sed -e 's/[^ ]*old[^ ]*//g' | sed "s/.config/.info/g" )
owners=$(ls *.config |grep -v old | sed -e 's/[^ ]*old[^ ]*//g' | sed "s/.config//g" )    
#echo $owners
tmp=0
array=(${owners//\ / })
for word in $file;
do
#  echo owner-${array[$tmp]}@server.com
     bounce=$(grep -s ^owner-${array[$tmp]}: /etc/aliases)
     if [ -n "${bounce}" ]; then
#       echo "list $word $bounce"
        email=owner-${array[$tmp]}@server.com
if [[ $bounce == *"deptbounce"* ]]; then
        	email=admin@server.com
fi
lastdate=$(ls -l ${array[$tmp]} | awk '{ print $6, $7, $8 }')
echo "
To the owner of the $(echo ${array[$tmp]})@server.com email list,
The company is currently in the process of moving our list services from majordomo to mailman. 
Do you still need this majordomo list? If you do not, we can leave it out of the process. 
This will help us to streamline our efforts. Thank you for your cooperation. 
Date of last modification of the mailing list: ${lastdate}
Extracted from info file:
--------------------
$(grep . $word | head -2)
--------------------
-company" | mail -s "Email List Migration: $(echo ${array[$tmp]})@server.com" $email -- -f admin@server.com
        # echo "Subject: Email List Migration: $(echo ${array[$tmp]})@server.com "
        # echo "To: $email"
        #echo
#echo
#echo
#echo
#echo
echo
     fi # list exists
tmp=$tmp+1
done

