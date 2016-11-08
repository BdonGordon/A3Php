/*---------------------------------------------------------------------
 *                      README A3
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
[./a3 <filename>]
filename can have the an html extension or none. 
***NOTE: the python file has already undergone the [chmod +x] command to become an executable.
          
**************
BUGS/FAILURES
**************
1. When running Valgrind, the first execution says that 'q2' does not exist. That's where you press
CNTRL+C . When you execute valgrind immediately after the first time, valgrind will executre fully with
no leaks.

2. When the Convert is executed, the process on the web browser to execute the .c and .py may take up 
to 20 seconds to finish executing. After that time period, it works perfectly fine. 
