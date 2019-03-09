# SortedList

### Introduction
This repository contains code I wrote for Lab 2 of COM SCI 111 (Winter 2019). 
This contains my implementation of a circular doubly linked list, where the data in each node is a unique 5-bit string of characters. 

### Data Structures
```C
/* Each element of the SortedList */
struct SortedListElement {
    struct SortedListElement *prev;
    struct SortedListElement *next;
    const char *key;
};

typedef struct SortedListElement SortedList_t;
typedef struct SortedListElement SortedListElement_t;
```

### Files

0. README.md  
This very file

1. SortedList.h (courtesy Professor Mark Kampe)  
This header file contains function declarations for various operations on the list

2. SortedList.c  
This file contains my implementations of the functions in `SortedList.h`  
    * `void SortedList_insert(SortedList_t *list, SortedListElement_t *element)`  
        Inserts an element into the list, which is kept sorted in ascending order of keys

    * `int SortedList_delete( SortedListElement_t *element)`  
Removes the given element from the specified list. Returns 0 on success and 1 on failure  
    * `SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key)`  
Searches the specified sorted list for the specified key. Returns a pointer to the specified element if found, or `NULL` if not found.  
    * `int SortedList_length(SortedList_t *list)`  
Returns the length of the specified sorted list. 
