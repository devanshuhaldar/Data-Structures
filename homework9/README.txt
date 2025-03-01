HOMEWORK 9: MINIBLAST


NAME:  < Devanshu Haldar >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< lecture notes and office hours. Forgot names of TA's, I think one of them was Dru. (Not 100% sure) >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 >


HASH FUNCTION DESCRIPTION:

Since the genome sequence contains only 4 unique letters.
I gave each letter a special multiplication factor and multiplied
the value again by the position in the sequence. I made this
on my own and I am pretty sure for this assignment specifically
it is a good hash function.


HASH TABLE IMPLEMENTATION:
For my hash table I did the basic constructors and size() function.
Along with my insert and find, I added a couple different functions
such as: setOccupancy (which allows me to use the occupancy variable for 
my insert function, incase I need to resize table), a getPositions function 
(that returns the vector<int> of all positions of a specific sequence found
in the genome). My insert is a simple bool, find returns an int of the position
in the hash table. I added a print function just for debugging. And lastly, the 
resize_table was basically the same from the ds_hashset.

Lastly to clarify, when I set my occupancy that is where I compare it to the capacity
of the hash table that is filled (in the insert function). If the capacity is higher than or
equal to the occupancy I call the resize table function.




ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)
The performance of my algorithim has the potential to be very good. The issue is the 
forced default table size if not given in the file. Because this will require a lot 
of calling the resize table function. And the O(n) in the resize table is not as efficient as it can be.
I would prefer setting the hash table size to a accurate size which allows me to rarely ever call the
resize, making everything mostly O(1)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the hash table data structure require (order notation for memory use)?
The hash table memory usage around: O(L*p)
I am inputting the seed of each genome sequence in the entire genome file. 
So I am assuming the memory usage is quite high.

Since my hash table is a vector of pair<string, vector<int> >,
I will be containing every seed, in each pair in the vector and in that pair
I will contain the p(dif locations) in the vector<int>


What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?
Insert:Should be O(1), can be longer if linear probing is required, and how filled the hash table is.
Find: Same with insert should be O(1), however can depend on linear probing
Resize: This should be O(n). N is the size of the old table. Because I am going through
the entire old table and copying the old data


EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


