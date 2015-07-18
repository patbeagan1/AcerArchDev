#!/bin/bash
#
# Detect status changes on cluster nodes
EMAIL="admin@server.com"
LOGDIR="/usr/local/etc/node.logs"
source /etc/profile.d/rocks-binaries.sh
CLUSTER=$(rocks list attr | awk '/^Info_ClusterName:/ {print $2}')
NODES=$(rocks run host compute frontend command='echo' x11=false collate=true)
DOWN=$(echo "$NODES" | awk -F: '/: down$/')
UP=$(echo "$NODES" | awk -F: '/: $/')
TRUEDOWN=$(echo "$DOWN" | awk '{ if ((substr( $1, length($1)-2, length($1)-1 )) >= "13:") print $1 }')
if [ "$TRUEDOWN" ]; then
    cat << EOF | mail -s "${CLUSTER}: nodes that are down (on $(hostname -s))" $EMAIL
Skuld: compute 0-12 are down by design - 32bit systems
${TRUEDOWN}
EOF
fi
[ -d "$LOGDIR" ] || mkdir -p "$LOGDIR"
for i in $UP; do
    LOG="${LOGDIR}/${i}.log"
    rocks run host $i command='ipmitool sel elist' x11=false | tr -d '\r' > "${LOG}.new"
    if [ "$(<${LOG}.new)" ]; then
        if ! cmp "$LOG" "${LOG}.new" &> /dev/null; then
            mail -s "${CLUSTER}: SEL change on $i" $EMAIL < "${LOG}.new"
        fi
        mv -f "${LOG}.new" "$LOG"
    else
        rm -f "${LOG}.new"
    fi
done
