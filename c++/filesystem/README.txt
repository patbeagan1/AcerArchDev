Patrick Beagan
cs377 OPS
----------------

For this project, I worked in this order:
	renaming functions to get around "delete" keyword
	being able to open the input file
	being able to open the disk
	being able to exec into create_fs
	being able to create a file on the disk
	being able to delete that file
	error checking on create and delete functions
	checking persistence 
	being able to list files already on disk
	being able to reformat a disk from the input doc
	being able to print the full contents of disk
	being able to write to a file on disk
	being able to read from that file on disk
	error checking on write and read
	cleaning up output
	commenting code
	
	I used arrays for all of my data structures.
	
Problems:
	For some reason the string "lab1.jav" is seen as 2 different strings by the program.
	It shows up separately as "lab1.jav" and "lab1.jav[box char]" when I apply cout
	What's particularly confusing is that "lab2.jav" works perfectly, even though it is almost equiv.
	I'm assuming this is a problem with strcpy in creater(*). All strings except that one work perfectly.
	I got around the problem by renaming "lab1.jav" to "lab1.ja" in the input, which solved all the problems, though it is an imperfect fix.
	
	Given more time, I would like to make the dummy array be an actual enterable value instead of hardcoded, because I like this project a lot and would like to expand upon it.
