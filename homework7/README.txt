HOMEWORK 7: HALLOWEEN COSTUME MAPS


NAME:  < Devanshu Haldar >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 8 >



ORDER NOTATION ANALYSIS (ORIGINAL VERSION W/MAPS):
of each of the costume shop operations (please be concise!)
n= costumes in the shop
m= max copies of 1 costume
c= customers
add:O(1)
No functions were called. Just reads in 1 value and places it into inventory map
rent:O(logc) 
Used find and erase function both are logn. Used these functions on my customers map.
lookup:O(logn)
Used find for a specific costume in costume inventory map. logn is a find function.
print:O(c). This is not going to be the actual value of c. In fact, much smaller than that.
I used a for loop to go through the vector of customers that are currently wearing a specific costume.
Since we are given 3 variables to work with. I used the letter c. 
Just to reinsure, this is not a large running time and should not equal the actual amount of customers. Unless
all the customers are currently wearing 1 specific costume.


EXTRA CREDIT (W/O MAPS)
What alternate data structures did you use?  What is the order
notation of each operation without maps?  What is the expected
performance difference?  Summarize the results of your testing.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)






