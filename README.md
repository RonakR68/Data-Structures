# C++ Data Structures

This repository includes C++ implementations for various associative containers, providing data structures such as unordered_map, ordered_map, treap, priority queue, and trie.


## Deque:

### Operations:
1. deque() - initialize an empty deque.
2. deque(n) - initialize a deque of length n with all values as default value of T.
3. deque(n, x) - Initialize a deque of length n with all values as x.
4. bool push_back(x) - append data x at the end. Return true if operation is performed successfully, else return false.
5. bool pop_back() - erase data at the end. Return true if operation is performed successfully, else return false.
6. bool push_front(x) - append data x at the beginning. Return true if operation is performed successfully, else return false.
7. bool pop_front() - erase an element from the beginning. Return true if operation is performed successfully, else return false.
8. T front() - returns the first element(value) in the deque. If the first element is not present, return the default value of T.
9. T back() - returns the last element(value) in the deque. If the last element is not present, return the default value.
10. T D[n] - returns the nth element of the deque. You need to overload the [ ] operator. If nth element is not present return default value of T.
11. bool empty() - returns true if deque is empty else returns false.
12. int size() - returns the current size of deque.
13. void resize(n) - change the size dynamically to new size n. If the new size n is greater than the current size of the deque, then insert new elements with the default value of T at the end of the queue. If the new size n is smaller than the current size, then keep n elements from the beginning of the deque.
14. void resize(n, d) - change the size dynamically to new size n. If the new size n is greater than the current size of the deque, then insert new elements with value d at the end of the queue. If the new size n is smaller than the current size, then keep n elements from the beginning of the deque.
15. void reserve(n) : change the capacity of deque to n, if n > current capacity; otherwise do nothing.
16. void shrink_to_fit() - reduce the capacity of the deque to current size.
17. void clear() - remove all elements of deque.
18. int capacity() - return the current capacity of deque.

## Priority_Queue:

### Operations:

1. priority_queue() - initialize an empty priority queue. 0: Min Heap. 1: Max Heap.
2. int size() - returns the current size of the priority queue.
3. void push(int el) - insert an element el in the priority queue.
4. int top() - returns the top (highest or lowest priority) element in the priority queue.
5. void pop() - remove the top element of the priority queue.
6. bool empty() - returns true if the priority queue is empty else returns false.

## Trie:

### Features:

1. Spell Check: Check if the input string is present in the dictionary.
2. Autocomplete: Find all the words in the dictionary which begin with the given input.
3. Autocorrect: Find all the words in the dictionary which are at an edit distance(Levenshtein distance) of at most 3 from the given input.

## Unordered Map:

### Operations:

1. bool insert(T1 key, T2 value):Inserts ‘value’ in the map with key = ‘key’ if ‘key’ was not present and returns whether insertion took place.
2. bool erase(T1 key):Deletes ‘key’ and its value from the map if ‘key’ was present and
returns true, otherwise false.
3. bool contains(T1 key):Returns true if the key exists in map otherwise returns false.
4. T2& operator[ ](T1 key):Inserts default value of T2 with key = ‘key’ if ‘key’ was not present
in the map. Returns the T2 value by reference.
5. void clear():Clears the map and releases the allocated memory
6. int size():Returns the size of the map
7. bool empty():Returns whether the map is empty or not.
8. std::vector<T1> keys():Returns a vector of keys.

## Ordered Map:

- underlying implementation is based on AVL Tree.

### Operations:

1. bool empty():Returns whether the map is empty or not.
2. int size():Returns the size of the map
3. bool contains(T1 key):Returns whether ‘key’ is present in the map or not.
4. bool insert(T1 key, T2 value):Inserts ‘value’ in the map with key = ‘key’ if ‘key’ was not present and returns whether insertion took place.
5. bool erase(T1 key):Deletes ‘key’ and its value from the map if ‘key’ was present and returns whether deletion took place.
6. T2& operator[](T1 key):Inserts default value of T2 with key = ‘key’ if ‘key’ was not present
in the map. Returns the T2 value by reference.
7. void clear():Clears the map and releases the allocated memory
8. std::vector<T1> keys():Returns vector of keys in sorted order
9. std::pair<bool, T1> lower_bound(T1 key):Returns a pair of true, first (when ordered using comparator) key ‘lb’that fails the comparator std::less<T1>(‘key’, ‘lb’), if exists, otherwise a pair of false, default value of T1.
10. std::pair<bool, T1> upper_bound(T1 key):Returns a pair of true, first (when ordered using comparator) key ‘ub’ that fails the comparator std::less<T1>(‘key’, ‘ub’) and std::equal_to<T1>(‘key’, ‘ub’), if exists, otherwise a pair of false, default value of T1.

## Implicit Treap:

- A treap is a self-balancing data structure that combines the features of a binary search tree (BST) and a heap, using randomized priorities to maintain both ordering and prioritization of elements. It efficiently supports operations such as insertion, deletion, and search.

### Operations:

1. bool empty(): Returns if the treap is empty or not
2. int size():Returns the size of the treap
3. void clear():Releases all acquired memory and clears the treap
4. int insert(T val):Inserts `val` into the treap and returns the index
5. bool erase(int index):Deletes the value at given index and returns true if the index
was valid else returns false
6. int indexOf(T val):Returns the index of val if exists, otherwise returns -1
7. T atIndex(int index):Returns the value at given index if valid, otherwise returns the
default value of T
8. treap<T>* merge(treap<T> *t2):Merges t1 and t2 when called as t1->merge(t2), where t1 and
t2 are treap<T> pointers. (assume that all the values
in t1 will be less than or equal to all the values in t2).Returns the pointer to the new merged treap.
9. std::pair<treap<T>*, treap<T>*> split(int index):Splits the treap at given index such that the elements before the given index are in the first treap and the elements from the index(and afterwards) are in the second treap.Returns the pair of pointers to the new treaps
10. bool erase(int first, int last):Deletes the values between given indices (inclusive) and
returns true if the whole index range was valid (completely
inside the treap) else returns false
11. treap<T>* slice(int first, int last):Returns a pointer to the new treap consisting of values
between given indices (inclusive) if the index range was valid else returns nullptr.
12. int lower_bound(T val):Returns the number of elements strictly less than `val`
13. int upper_bound(T val):Returns the number of elements less than or equal to `val`
14. int count(T val): Returns the number of elements equal to `val`
15. std::vector<T> to_array: Returns the vector of values in the sorted order


