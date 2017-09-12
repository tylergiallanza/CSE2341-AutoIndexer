I decided to use a self-balancing binary search tree instead of a hash table for a few reasons.
1. Unknown number of search terms means wasted space in hash table or an additional query of input file
2. Results need to be returned as ordered which means the hash table would need a sorted vector of keys anyway
3. Collision chaining means worst case O(n) insertion for hash table vs O(log n) for self-balancing BST
4. Less memory overhead - Hash table is an array of linked lists of linked lists with a vector of sorted keys, which is a lot of unecessary memory utilization

I chose to implement a red-black tree instead of an AVL tree because it doesn't require storing the height of the tree at every node.
