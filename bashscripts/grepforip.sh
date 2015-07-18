grep -B1 '1 received' results.log | sed /.*1\ received/d | sed s/-//g | sed '/^$/d' | sed s/\ ping\ statistics\ //
