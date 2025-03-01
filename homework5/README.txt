HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  < Devanshu Haldar >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< None (Took some stuff from example .cpp's on calendar) >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 17 >



TESTING & DEBUGGING STRATEGY:
Please be concise!  

MoreTests():
Copy constructor->
Tested the assignment operator to see if the contents in b would be the same as a. They were. size and elements in each position.

Assignment operator->
Tested the assignment operator to see if the contents in b would be the same as a. They were. size and elements in each position.

Iterator testing->
I created an iterator and started from the beginning to the end printing out each value at each position. The values were correct and compared exactly
to the contents that were in the array.

Different types->
I used a string type as an example to see if other types other than integers work. The test cases show me that they do.

The functions were tested previously in the student and instructor cases. Passed those aswell.

ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 

UNROLLEDLL
FUNCTIONS:

Size=> O(1). Just returns a variable size_. That is kept track of the entire time. It is a member variable.

Front=> O(1). Returns first position value, in the first node. 

Back=> O(1). Returns last position value, in last node. 

Push_back=> O(1). Adds an element in the last position.  Doesn't go through the entire loop. 

Pop_back=> O(n). Had to re make the array. So used a for loop to copy number of elements. Obviously, in this instance
n will equal 6 per for loop if worst case scenario. So it's not that big of a deal and is very close to O(1)

Push_front=>O(n). Remake the array, pushing elements to the right. Same explanation as pop_back.

Pop_front=> O(n). Same as pop_back.

Erase=>O(n). Number of elements worst case in this assignment is n=6 per for loop. So not large.

Insert=>O(n). Same as erase.

Destroy_list=> O(n). Depends on number of nodes.

Copy_list=> O(n). Depends on number of nodes. Shouldn't have to worry about copying arrays by another for loop. 
Because you can just set the array in the node to be that array(O(1)).

Differences Between UNROLLEDLL, DSLIST, and STL:

In the UnrolledLL the erase function specifically is stronger than the STL erase. It is more efficient and less expensive.
And avoids a worst case scenario. This is because we leave space in the array in the node if we erase an element from it. 
Also, the UnrolledLL and dslist is very similar in many ways and has the same order notation on most functions.
Functions like insert,erase,push (front & back), pop (front&back) are different because for example, instead of just deleting the node
every time the erase is called like in the dslist. In the unrolledll I need to check if there are more elements leftover.
Which is a very slight change and shouldn't change the O(n). They should practically be the same.
The STL class is different because it contains way more nodes and as said previously the erase is less efficient.

UnrolledLL is inefficient in its worst case when there is 1 element in most of the nodes (Avg number of elements per node is 1(worst case)). Therefore, you are not taking advantage 
of the erase function and it is just the same as the dslist. Another worst case for the push functions is when all the arrays in each node are always full.
So you will constantly have to keep creating new nodes and placing elements in them. Recopying and replacing the arrays takes a lot of loops and work and
it ends up being inefficient.

EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.
N/A


MISC. COMMENTS TO GRADER:  
Optional, please be concise!


