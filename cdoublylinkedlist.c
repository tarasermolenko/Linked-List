#include <stdio.h>
#include <stdlib.h>
// Taras Ermolenko 
// Doubly linked list implementation 2021-08-27


// List element: a list is a chain of these
typedef struct element 
{
    int val;
    struct element* next;
    struct element* prev;

} element_t;


// List header: keep track of the first and last list elements
typedef struct list 
{
    element_t* head;
    element_t* tail;
} list_t;


list_t* list_create(void) 
{
    list_t * list = malloc(sizeof(list_t));
    
    // creates and empty list object that does not point to anything
    if (list != NULL) 
    {
        list->head = NULL;
        list->tail = NULL;
    }
    return list;
}


void list_destroy(list_t* list) 
{
    // assigns temp current pointer to what list heads points to
    element_t* curr = list->head;
    // temp next pointer will be used to store next element
    element_t* next;

    // goes through each node starting from head and frees it
    while (curr != NULL) 
    {
        // assigns temp next pointer to point to current values next pointer
        next = curr->next;
        
        // frees current node memory
        free(curr);

        //sets current element to next element
        curr = next;
    }

    // frees list struct at the end after all nodes are freed.
    free(list);    
}


element_t* element_create(int i) 
{
    // creates a "node"
    element_t* e = malloc(sizeof(element_t));

    // assings given value and points to null
    if (e != NULL) 
    {
        e->val = i;
        e->next = NULL;
        e->prev = NULL;
    }

    return e;
}


int list_append(list_t* list, int i) 
{
    element_t* e = element_create(i);

    if (e == NULL)
    {
        return 1;
    }

    // only if list is emppty this runs
    // since new this is the first element in list
    if (list->head == NULL) 
    {
        list->head = e;
    }
    // else only tail changed
    else 
    {
        list->tail->next = e;
        e->prev = list->tail;
    }

    list->tail = e;
    
    return 0;
}


int list_prepend(list_t* list, int i) 
{
    element_t* e = element_create(i);

    if (e == NULL)
    {
        return 1;
    }

    if (list->head == NULL) 
    {
        list->tail = e;
    } 
    else 
    {
        e->next = list->head;
        list->head->prev = e;
    }
    list->head = e;
    return 0;
}


void list_print(list_t* list) 
{
    printf("{");

    for (element_t* e = list->head; e != NULL; e = e->next) 
    {
        printf(" %d", e->val);
    }

    printf(" }\n");
}


void list_reverse_print(list_t* list) 
{
    printf("{");

    for (element_t* e = list->tail; e != NULL; e = e->prev) 
    {
        printf(" %d", e->val);
    }
    
    printf(" }\n");
}


void list_add_at(list_t* list, int pos, int data) 
{
    element_t* e = element_create(data);

    if (e == NULL)
    {
        return;
    }

    // Empty List Case
    if (list->head == NULL) 
    {
        list->head = e;
        list->tail = e;
        return;
    }

    int idx = 0;

    element_t *prev = NULL;
    element_t *cur = list->head;

    // walk through list until pos or end is reached
    while (cur != NULL && idx != pos) 
    {
        idx++;
        prev = cur;
        cur = cur->next;
    }

    // insertion point reached

    // beginning, includes head update
    if (idx == 0) 
    {
        list->head = e;
        e->next = cur;
        cur->prev = e;
        return;
    }

    // end
    if (cur == NULL) {
        prev->next = e;
        e->prev = prev;
        list->tail = e;
        return;
    }

    // middle
    prev->next = e;
    e->prev = prev;
    e->next = cur;
    cur->prev = e;
}


void list_remove_first_element(list_t* list)
{
    element_t *cur = list->head;

    if (cur->next == NULL) 
    {
        // only item case
        list->head = NULL;
        list->tail = NULL;
    } else
    {
        // more items case
        list->head = cur->next;
        list->head->prev = NULL;
    }

    free(cur);
    return;
}


void list_remove_last_element(list_t* list)
{
    element_t *cur = list->tail;

    cur->prev->next = NULL;
    list->tail = cur->prev;

    free(cur);
    return;
    
}

element_t* list_index(list_t* list, unsigned int i) 
{
    element_t* curr = list->head;

    unsigned int i_curr = 0;
    
    while (curr != NULL) 
    {
        if (i_curr == i)
        {
            return curr;
        }

        i_curr++;
        curr = curr->next;
    }

    return NULL;
}

void list_remove_by_index(list_t* list, int i)
{
    // goes to given index
    element_t *cur = list_index(list, i);

    if (cur == NULL) 
    {
        return;
    }

    // handle first node case
    if (cur->prev == NULL) 
    {
        if (cur->next == NULL) 
        {
            // only node case
            list->head = NULL;
            list->tail = NULL;
        } else {
            // more ndoes case
            list->head = cur->next;
            list->head->prev = NULL;
        }

        free(cur);
        return;
    }

    // handle last node
    if (cur->next == NULL) 
    {
        cur->prev->next = NULL;
        list->tail = cur->prev;

        free(cur);
        return;
    }

    // handle middle node
    if (cur->prev != NULL && cur->next != NULL) 
    {
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;

        free(cur);
        return;
    }
}

// if duplicate value exist it will only remove one it encounters first
void list_remove_by_val(list_t* list, int data) {

    element_t *cur = list->head;

    while (cur != NULL && cur->val != data) 
    {
        cur = cur->next;
    }

    // null cur means no match, do nothing
    if (cur == NULL) 
    {
        return;
    }

    // handle first node
    if (cur->prev == NULL) 
    {
        if (cur->next == NULL) 
        {
            // only node
            list->head = NULL;
            list->tail = NULL;
        } else {
            // more nodes
            list->head = cur->next;
            list->head->prev = NULL;
        }

        free(cur);
        return;
    }

    // handle last node
    if (cur->next == NULL) 
    {
        cur->prev->next = NULL;
        list->tail = cur->prev;

        free(cur);
        return;
    }

    // handle middle node
    if (cur->prev != NULL && cur->next != NULL) 
    {
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;

        free(cur);
        return;
    }
}


int main() {
    // test list_create()
    list_t* list = list_create();

    // check to see if the create function did everything it was supposed to
    if (list == NULL) {
        printf("list_create(): create failed to malloc\n");
        return 1;
    }
    if (list->head != NULL) {
        printf("list_create(): head is not null!\n");
        return 1;
    }
    if (list->tail != NULL) {
        printf("list_create(): tail is not null!\n");
        return 1;
    }
   
    list_remove_by_val(list, 9);
    list_print(list);
    list_remove_by_val(list, 9);
    list_print(list);
    list_remove_by_val(list, 3);
    list_print(list);
    list_reverse_print(list);
    list_add_at(list,0, 1);
    list_print(list);

    list_remove_by_index(list, 1); 
    list_print(list);
    list_remove_by_index(list, 0); 
    list_print(list);
    list_remove_by_index(list, 3); 
    list_print(list);

    list_remove_first_element(list);
    list_print(list);
    list_remove_last_element(list);
    list_print(list);

    list_destroy(list); 
    
    return 0; // tests pass
}

