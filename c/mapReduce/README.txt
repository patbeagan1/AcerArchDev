Patrick Beagan
ID 27529823

For this project, I attempted to create 2 arrays of pthreads, one with size m for the mappers, and one with size n for the reducers.
The mapper pthreads parse the file name that they are supposed to acces, foox.txt, then they open the file.
Using this file, they read the file line by line into a buffer which is owned by one of the reducer threads.
        I was unable to create an adequate buffer to to my inexperience with c, but the mappers read from their own files correctly and independently.
The reducer threads then take from their respective buffer and use the word stored there to create an inverted list, which stores the locations by the word, instead of the words by location.
        In that I was also partly unsuccessful, since the buffer needs to be reliable to be able to take strings from it.

I ran into some computer trouble shortly before submitting; the cursor stopped refreshing, and since I'm using nano, that's disastrous.
I was experimenting with the strcmp(x,y) method right before that, which is causing the segfault, and if I was still able to type I'd have at least cleaned that up for you.


The biggest obstacle I had to overcome in this lab was keeping variables accessible to the threads.  When I tried to make a 2d array of strings in c, something I would definitely feel comfortable doing in java, the whole thing fell apart. Global variables were very tricky.
Synchronization works by having one thread block other threads while it is handling sensitive data.  If other threads are allowed to interfere, there could be a faulty representation of the data, especially when incrementing or decrementing - some iterations my be redoubled or skipped.  By making sure that only one thread can interact with shared data at a time, conflicts are kept to a minimum and the information stays accurate.


If I had more time I would solve the problem of stored buffers. That's the root of all the problems I've been having.
