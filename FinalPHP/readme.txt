/*---------------------------------------------------------------------
 *                      README A2
 * Name: Brandon Gordon
 * Student ID: 0850874
 * Course: CIS2750 [F16]
 * Professor: David Calvert 
 *---------------------------------------------------------------------
 */

**************
COMPILE
**************
On a Linux Operating System (or Windows 8 or Mac) open a terminal and on the command line type: 	
[make] 	
Note: DO NOT include the '[' ']'. 

**************
EXECUTE
**************
On the commad line type:
[./a2 <filename>]
filename can have the an html extension or none. 
***NOTE: the python file has already undergone the [chmod +x] command to become an executable.
          
**************
BUGS/FAILURES
**************
1. 4 unfreed blocks of memory occurs because of failure to free the returnStruct content wherever
it is malloc'd.

2. After the program runs, the pipe named "q1" is not removed from directory. When valgrind is executed, sometimes
it will run through to completion, and other times (UNSURE WHY IT WORKS SOMETIMES AND NOT OTHERS, sorry), 
it will notify that there is no "q2" file and stop before valgrind is completed (press CNTRL+C to exit valgrind at 
this point).
