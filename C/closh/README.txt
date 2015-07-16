Patrick Beagan
ID 27529823

Changes made to skeleton code:

handler method added before the parsing logic
	used to kill processes when it gets an alarm signal
signal set up to go to handler on SIGALRM
fork once for each process in count

#time.h included
#difftime logic taken out in favor of alarms

if sequential, each parent waits for child process to finish before continuing

if we are in a child process, start an alarm and replace with the correct program

finally, at the end of the while loop wait for all processes 
other than closh to finish, to prevent prompt for appearing preemptively


creates a process for each number in count, fills each process with
correct program.  If sequential, waits for each to finish in order.
if alarm goes off before process completes, it goes to handler
and is killed. At the end of the while loop, all processes are
waited for to avoid closh accepting the next command preemptively

/*
SOURCES
https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_chapter/libc_21.htm$
stackexchange on wait(NULL)
man page for alarm()
stackexchange on time.h
*/
