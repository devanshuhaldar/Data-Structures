HOMEWORK 10:  PERFORMANCE & BIG O NOTATION


NAME:  < Devanshu Haldar >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Office Hours >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 9 >



COMPLEXITY ANALYSIS
n = number of elements in the input
f = requested number of values in output (first sorted only)
l = maximum length of any string element

Neatly fill in the table below with the Big O Notation for running time.

------------------------------------------------------------------------------
|          |          | remove   |          | closest  | first f  | longest  |
|          | sort     | dups     | mode     | pair     | sorted   | substr   | 
------------------------------------------------------------------------------
|          |  nlog(n) |   n^2    |   nlogn  |   nlogn  |  f+nlogn |  l^3 n^2 |
| vector   |          |          |          |          |          |          |
------------------------------------------------------------------------------
|          |  nlog(n) |   n^2    |   nlogn  |   nlogn  |  f+nlogn |  l^3 n^2 |
| list     |          |          |          |          |          |          |
------------------------------------------------------------------------------
|          |  nlog(n) |   nlogn  |   nlogn  |   nlogn  |  fn      |  l^3 n^2 |
| bst      |          |          |          |          |          |          |
------------------------------------------------------------------------------
|          |  nlog(n) |     X    |   nlogn  |   nlogn  |  f+nlogn |    X     |
| pq       |          |          |          |          |          |          |
------------------------------------------------------------------------------
|          |    X     |   n      |   n      |     X    |    X     |  l^3 n^2 |
| hash     |          |          |          |          |          |          |
------------------------------------------------------------------------------



RESULTS
For each data type and each operation, run several sufficiently large
tests and collect the operation time output by the program. Organize
these timing measurements in your README.txt file and estimate the
coefficients for the dominant term of your Big ‘O’ Notation.

< insert your performance measurements and coefficient estimates >

Amount  String	String		String	Int		String(f = 5)   String  (Operation too long with previous sizes)
Vector:	Sort	Remove_Dup	Mode	Closest_Pair	First f string	Long Substr
10000	.5s	1.125s		.0156s	0s		0s  		100 strings: .0156s
100000	3.7s	86.437s		.0625s	.047s		.0625s		1000strings: .75s
1000000 37.42s  Too Long	.734s	.469s		.6875s		10000string: 72.39s

List:	Sort	Remove_Dup	Mode	Closest_Pair	First f string	Long Substr
10000	.359s	1.7s		.0156s	0s		.0156s		100 strings: 0s
100000	3.6s	136.422s	.109s	.0781s		.109s		1000strings: .7187s
1000000 36.57s	Too Long	1.67s	1.25s		1.42s		10000string: 71.75s

BST:	Sort	Remove_Dup	Mode	Closest_Pair	First f string	Long Substr
10000	.453s	.375s		.0156s 	0s		.0156s		100 strings: 0s
100000	3.54s	120.36s		.125s	.0781s		.0937s		1000strings: .75s
1000000 37.32s 	Too Long	1.953s	1.25s		1.765s		10000string: 74.84s

P_Que:	Sort	Remove_Dup	Mode	Closest_Pair	First f string	Long Substr
10000	.4s	X		.0156s	0s		.0156s		X
100000	4.17s	X		.125s	.0937s		.625s		X
1000000 42.82s	X		1.79s	.953s		.625s		X
	
Hash:	Sort	Remove_Dup	Mode	Closest_Pair	First f string	Long Substr
10000	X	.4s		.0165s	X		X		100 strings: .0156s
100000	X	129.456s	.078s	X		X		1000strings: .7343s
1000000 X	Too Long	1.015s  X		X		10000string: 74.78s



DISCUSSION
Do these measurements and the overall performance match your predicted
Big ‘O‘ Notation for the data type and operation? Did you update your
initial answers for the Big ‘O‘ Notation of any cell in the table?

Compare the relative coefficients for different data types that have
the same Big ‘O’ Notation for a specific operation. Do these match
your intuition? Are you surprised by any of the results? Will these
results impact your data structure choices for future programming
projects?

Use well-written, complete sentences.  Approximately 250-500 words.  


Initially most of my predictions on the Big O notation were incorrect. I updated most cells in the table from my previous table. 
This includes the X's in the wrong positions and the change in remove_duplicates and long substring.
I assumed that as the amounts get huge like one million the long substring would fail and take super long to work. Point was proven using 
4 of the 5 data structures as they all had approximately same times. I expected the first f sorted to not be expensive and my results prove that.
Sort was expected to be small, and become larger as values gain. I found the remove_duplicates to be shocking. I did not expect it to take so long to run
1 million amounts of data. But looking back it it makes sense. I also found that the closest pair and mode were to be of low memory and time usage as expected.
From the results of the data it is revealing that picking the correct data structure to use before entering a problem is vital to have a smooth memory and time experience.
Hash tables are very useful but lack in areas such as sorting. I also found priority queues to be quite useful and simple to use.
But from the experience in this assignment it is revealing to me that my favorite structure is most likely the set/maps. 
The automated sorting and choice to pick whether it be a set or map is very useful. Finally, although my predicitions were incorrect (mostly) I did learn 
the importance of running time and memory usage, and I realize how important it is to pick the correct data structure early on in an assignment.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!
