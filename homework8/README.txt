HOMEWORK 8: B+ TREES


NAME:  < Devanshu Haldar >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Ta Office Hours, Matt Sweet >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 >


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your implementation?

I used print debugging, valgrind, and very little of gdb to test my cases. To fully understand the problem and see what I needed to do 
I looked at the given B+ tree visualization website and played with it a lot. To be honest, it took a while for me to even start this assignment, because
I simply did not know where to even begin. I finally was able to begin working on the code highlight and unhighlighting each assertion given in the cpp file
Some of the corner cases were using the commas, or when you had children of size 2 instead of 3. In these  cases I created specialized if statements for 
those corner cases. Another corner case that I found late, was when to place the <= or >= with a children of size 2 vs >2. That is when I seperated the two
and created an if statement for each of those cases.

So basically, the main debugging of my code was valgrind for memory errors and the rest was pretty much print debugging. I went through the entire .cpp file
given and tested all cases. I even added some extra print sideways in the earlier cases to see if the b+ tree looked how it was supposed to.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

