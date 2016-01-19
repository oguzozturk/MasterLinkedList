# MasterLinkedList

This project is a programming assignment in C which builds a review-score list based on the user’s reviews collected from WWW.
These reviews are in some basic categories according to the scores they have. 
This program will let the user add, remove, update the review-score list

To hold the list of all review-scores, you will use a master-linked-list.
This linked list will exactly contain as many nodes as the number of different review-scores where each node i represents the score ai in the review-score list. 
The node i should contain the information of ai such as the review-score-number and the number of total reviews under the review-score number category. 
Each node i in this linked list will also contain a pointer field. 
This pointer will function as the header of a linked list LL(ai) that will list the reviews in the relevant review-score ai.  
The size of LL(ai) will depend upon the number of the reviews in ai. which differs from node to node that will list the reviews in the relevant review-score-number ai.  
The size of LL(ai) will depend upon the number of the reviews in ai. Each node i in  LL(ai)will consist of 
The id of the review 
 The length of the review (how many words are included in that review) 
 The text of the review
 The polarity of the review(if it is a positive review, negative review or a neutral review)

FUNCTIONALITIES

1. Add a new review-score node into the master-linked list.  
2. Add also some reviews into a specific review-score category. 
3. Show the average score of all of the reviews. 
4. Show the review id s and the total number of them in a specific polarity ( positive, negative or neutral ) 
5. List the id s of reviews which have a particular word. 
6. Remove the reviews between in a specific score-scope.
