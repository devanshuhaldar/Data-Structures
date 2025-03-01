HOMEWORK 3: JAGGED ARRAY


NAME:  < Devanshu Haldar >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< used several webpages of stack overflow to explain some valgrind
errors that I was receiving. Such as: "Invalid size of 8", "Invalid
size of 4". I also used a lot of office hours. >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 17 hrs >



ORDER NOTATION:
For each function, for each version (packed vs. unpacked).  
b = the number of bins
e = the number of elements
k = the number of elements in the largest bin

NOTE: I was unclear on the instructions for explaining our Big O notation. So 
I pretended that e, b, and k were variables like n in O(n). So O(n^2) is equal
to O(b*e) depending on my for loops. Also, O(1) when there are no for or while loops and
when you are just reterning specific values in specific locations.

numElements
 unpacked:O(e)
 packed:O(e)

numBins
 unpacked:O(b)
 packed:O(b)

numElementsInBin
 unpacked: If in largest bin: O(k) or O(1)
 packed: If in largest bin: O(k) or O(1). 
Should be same because I am taking the value from counts_[position] No for loops or functions with higher order.

getElement
 unpacked:O(1). One if statement
 packed:O(1). Two if statements.

isPacked
 unpacked: O(1) returns bool true or false.
 packed: O(1) returns bool true or false. Only 1 if statement.

clear
 unpacked: O(b) 1 for loop of length number of bins
 packed: O(b) 1 for loop of length number of bins

addElement
 unpacked:O(e) 1 for loop going through number of elements in bins. Worst case: O(k)
 packed:N/A

removeElement
 unpacked:O(e) 1 for loop of length number of elements in bin. Worst case: O(k)
 packed:N/A

pack
 unpacked:N/a
 packed: Had 3 for loops. so O(b*(e^2)). 1 for loop length of number bins, 2 others with elements in specific bin.
Worst case scenario: O(b*(k^2)).

unpack
 unpacked: Had 2 for loops. so O(b*e). 1 for length of number of bins, 1 other for element in specifc bin. 
Worst case scenario: O(b*k);
 packed:N/a

print 
 unpacked:O(n*e). 1 for loop number of bins other for number of elements in bin. Worst case: O(n*k)
 packed: O(n). 1 for loop number of bins

constructor w/ integer argument
 unpacked: O(b). 1 for loop of number of bins
 packed: n/a starts unpacked

copy constructor
 unpacked: O(n*e), worst case: O(n*k). 
 packed: O(n). Highest order for loop in packed part of copy. 

destructor
 unpacked:n/a
 packed:n/a
 1 for loop of number of bins. O(b). 

assignment operator
 unpacked: O(1)
 packed: O(1) 
Just delete operators and 1 if statement.




MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
Did not know how to test the medium 7 test case. So was unable to complete.
Also, Was unclear on the instructions for explaining our Big O notation. So 
I pretended that e, b, and k were variables like n in O(n). So O(n^2) is equal
to O(b*e) depending on my for loops. Also, O(1) when there are no for or while loops and
when you are just reterning specific values in specific locations.



