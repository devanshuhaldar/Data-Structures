HOMEWORK 6: CROSSWORD BLACKOUT


NAME:  <Devanshu Haldar >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< I talked with 2 TA's forgot their names. Went into office hours: Monday night, tuesday night, thursday afternoon. >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(running time order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of words in the dictionary (d)? 
The total number of spaces with a letter (l)?
The total number of blacked out spaces (b)? 
The number of constraints (c)? 
Number of solutions (m)? //added
Etc. 

The running time on this assignment will be very high. The highest order notation I have had is of O(n^6)
More specifically O(w*h*b*d*c*l). This is because I have 3 for loops in the beginning going through each row,
each column,and then an int that starts off equaling col. As the line develops I need to check if the word exists in the dictionary (O(d)),
if it does I need to find it in the constraints.
Again I am calling the find() function, which is O(n) (variable depending on what searching). And if it is in the constraints 
I make sure to print the word when printing the grid.Lastly to make sure the word is printed I made a copy bool grid. 
That I will set each position of the word to false to ensure that the printing will use a hashtag if the boolean is true. 
My last for loop goes through my vector that contains 
all the positions of the word in the grid. Lastly, in my print_solve() it is O(n^6) aswell, Just added O(m) and removed O(c).

DESCRIPTION OF YOUR ADDTIONAL PUZZLES/DICTIONARIES:
Briefly explain the design of the puzzles or dictionaries and what
makes them "interesting" test cases (or why they aren't interesting).
Puzzle 1:
I was interested to see how the grid will look if all of the words are used.
And I was testing to see if any # were printed. Correctly they did not. 

Puzzle 2:
This is non interesting one. I saw on submitty there was a test case that was focused on corner words.
I thought this might be something interesting to make sure the grid prints correctly if there is a word
on every side. But no words in the middle.

I also wanted to test an addition of a word that creates more words in the grid. But that was already covered
in the submitty tests so I did not bother.

SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES AND 
ON YOUR ADDITIONAL PUZZLES/DICTIONARIES:
# of solutions & approximate wall clock running time for different
puzzles / dictionaries for a single solution or all solutions. Be
specific about which puzzle/dictionary/parameters you were timing.
The Order notation as discussed before is poor on this assignment. It takes too long to print and find the answer
with large/medium test cases. So large/medium dictionary, grids, or constraints causes the computer to take a long time to print.
I found that with these large/medium test cases it took several minutes before it prints. For small cases it printed almost immediately. 
So there was a significant difference in running time between the size of the grid,dictionary, and constraints. As expected.


MISC. COMMENTS TO GRADER:  
On the homework pdf file, it is stated that the constraints file is in such order: !Comment, +Constraints, Grid. With this order
my program worked correctly. However, with the hiddent test cases(sporcle) the order was: !Comment, Grid, +Constraints. I tried to reset
the istr >> operator but I could not figure out how to bring the cursor to the top. I spoke to several TA's and both were not able to find
an answer to this file. I emailed the professor to make sure that with these submitty test cases I dont recieve 0 on all. Because when i switched 
the constraints and grid, it worked fine. Just the ordering needs to be as stated in the homework and my program should be fine. 


