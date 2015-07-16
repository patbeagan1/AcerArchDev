Patrick Beagan
cs377
------------------

This program was a challenge to create because I initially made the other program not allow fragmentation.
When a new file was created, it would place each new block on the next free block in the list

After writing in a fragmentation option to teh filesystem code, I decided that the best solution would be to go down the whole list and check each inode each time to see if it contained a block which was to the right of the current, empty block.
if the inode did have a block which was to the right of the current, empty block, the two would switch their blocks, reflecting the change on the fbl and on the actual system.

7 and 9 were included to make it easier to see what was going where.

I believe that this code will work on a filesystem which is set up differently than mine.
The defragmenter works, it just misses some blocks because I would regularly change where the inodes were pointing in the filesystem program.
If a filesystem were set up which incorporates fragmentation as a default, it should not miss pointers, and the whole thing should defrag.


