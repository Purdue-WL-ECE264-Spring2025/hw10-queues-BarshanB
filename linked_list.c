#include "linked_list.h"
#include <stdlib.h>

struct list_node *create_list_node(size_t val) { 
    struct list_node *new = malloc(sizeof(struct list_node));
    if (new) {
        new->next_ptr = NULL;
        new->data = val;
    }
    return new;
}

void add_to_front(struct linked_list *lst, size_t val) {
    if (!lst) return;
    
    struct list_node *new = create_list_node(val);
    if (new) {
        new->next_ptr = lst->first;
        lst->first = new;
    }
}

void append_to_end(struct linked_list *lst, size_t val) {
    if (!lst) return;
    
    if (lst->first) {
        struct list_node *new = create_list_node(val);
        if (new) {
            struct list_node *current = lst->first;
            while (current->next_ptr) {
                current = current->next_ptr;
            }
            current->next_ptr = new;
        }
    } else {
        lst->first = create_list_node(val);
    }
}

size_t pop_front(struct linked_list *lst) {
    if (!lst || !lst->first) return 0;
    
    size_t result = lst->first->data;
    struct list_node *temp = lst->first;
    lst->first = temp->next_ptr;
    free(temp);
    
    return result;
}

size_t remove_from_end(struct linked_list *lst) {
    if (!lst || !lst->first) return 0;
    
    struct list_node *prev = NULL;
    struct list_node *curr = lst->first;
    
    while (curr->next_ptr) {
        prev = curr;
        curr = curr->next_ptr;
    }
    
    size_t result = curr->data;
    if (prev) {
        prev->next_ptr = NULL;
    } else {
        lst->first = NULL;
    }
    free(curr);
    
    return result;
}

void cleanup_list(struct linked_list lst) {
    struct list_node *current = lst.first;
    while (current) {
        struct list_node *next = current->next_ptr;
        free(current);
        current = next;
    }
}

void print_list(FILE *output, struct linked_list lst) {
    fprintf(output, "[ ");
    for (struct list_node *node = lst.first; node; node = node->next_ptr) {
        fprintf(output, "%zu ", node->data);
    }
    fprintf(output, "]\n");
}
