Linked Lists
------------
Pros:
+ Insertions and Deletions (constant time)

Cons:
- Random Access (linear scaling)

Applications:
Underlying structure for other structures, such as a list of stacks o queues.


Compare to vector list:
Adding an item in the list or removing an item in the list would require shifting
all other items over. (scales linearly with number of items requiring shift)


Linked Lists contain nodes, with each node having all of the information
associated with an item. (1 item can have a name, picture, etc.)
Each item also has a link which points to the next node in the list.
(links are pointers)

-Independent of where actual addresses are located.

Mechanism for end of the list:
-Final link has a terminating value of null or 0 (language dependent)

Adding an item only requires changing one existing link and adding one link in
the new item. (scales linearly with number of items added + 1)

Obtaining an index value of an item (element) number, we must follow linked list
up to that index. (Most searches are rendered useless, e.g. binary search)

Typically have a "node class" and a "linked list class", with all linked list
operations encapsulated in one class.

Doubly Linked List
------------------
links point in both directions.



