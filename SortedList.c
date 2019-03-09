#include "SortedList.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
/**
 * SortedList_insert ... insert an element into a sorted list
 *
 *    The specified element will be inserted in to
 *    the specified list, which will be kept sorted
 *    in ascending order based on associated keys
 *
 * @param SortedList_t *list ... header for the list
 * @param SortedListElement_t *element ... element to be added to the list
 */
void SortedList_insert(SortedList_t *list, SortedListElement_t *element) {
    if (element == NULL || list == NULL) {
        return;
    }
    if (list->key != NULL) {
        return;
    }
    SortedList_t *previous, *current;
    if (opt_yield & INSERT_YIELD) {
        sched_yield();
    }
    previous = list;
    current = list->next;
    
    while (current != list) {
        if (strcmp(current->key, element->key) < 0 ) {
            break;
        }
        previous = current;
        current = current->next;
    }
    
    element->next = previous->next;
    element->prev = previous;
    previous->next = element;
    element->next->prev = element;
}

/**
 * SortedList_delete ... remove an element from a sorted list
 *
 *    The specified element will be removed from whatever
 *    list it is currently in.
 *
 *    Before doing the deletion, we check to make sure that
 *    next->prev and prev->next both point to this node
 *
 * @param SortedListElement_t *element ... element to be removed
 *
 * @return 0: element deleted successfully, 1: corrtuped prev/next pointers
 *
 */
int SortedList_delete( SortedListElement_t *element) {
    //Check for corruption first:
    if (element == NULL || element->prev->next != element || element->next->prev != element) {
        fprintf(stderr, "List is corrupted! Exiting with exit code 1...\n");
        return 1;
    }
    
    if (opt_yield & DELETE_YIELD) {
        sched_yield();
    }
    
    // List is not corrupt, proceed to delete element
    element->prev->next = element->next;
    element->next->prev = element->prev;
    return 0;
}

/**
 * SortedList_lookup ... search sorted list for a key
 *
 *    The specified list will be searched for an
 *    element with the specified key.
 *
 * @param SortedList_t *list ... header for the list
 * @param const char * key ... the desired key
 *
 * @return pointer to matching element, or NULL if none is found
 */
SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key) {
    
    if (list == NULL || list->key != NULL) {
        return NULL;
    }
    
    SortedList_t *current = list->next;
    
    while (current != list) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        if (opt_yield & LOOKUP_YIELD) {
            sched_yield();
        }
        current = current->next;
    }
    return NULL;
}

/**
 * SortedList_length ... count elements in a sorted list
 *    While enumeratign list, it checks all prev/next pointers
 *
 * @param SortedList_t *list ... header for the list
 *
 * @return int number of elements in list (excluding head)
 *       -1 if the list is corrupted
 */
int SortedList_length(SortedList_t *list) {
    if (list == NULL || list->key != NULL) {
        return -1;
    }
    
    int list_len = 0;
    SortedList_t *current = list->next;
    while (current != list) {
        if (current->prev->next != current || current->next->prev != current) {
            return -1;
        }
        list_len++;
        if (opt_yield & LOOKUP_YIELD) {
            sched_yield();
        }
        current = current->next;
    }
    return list_len;
}

