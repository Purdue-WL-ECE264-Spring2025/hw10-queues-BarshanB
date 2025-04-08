#include "linked_list.h"
#include <stdlib.h>

struct list_node *create_node(size_t val) {
    struct list_node *node = malloc(sizeof(struct list_node));
    if (node) {
        node->next = NULL;
        node->value = val;
    }
    return node;
}

void prepend_node(struct linked_list *list, size_t val) {
    if (!list) return;
    
    struct list_node *node = create_node(val);
    if (node) {
        node->next = list->head;
        list->head = node;
    }
}

void append_node(struct linked_list *list, size_t val) {
    if (!list) return;
    
    if (list->head) {
        struct list_node *node = create_node(val);
        if (node) {
            struct list_node *current = list->head;
            while (current->next) {
                current = current->next;
            }
            current->next = node;
        }
    } else {
        list->head = create_node(val);
    }
}

size_t remove_first(struct linked_list *list) {
    if (!list || !list->head) return 0;
    
    size_t val = list->head->value;
    struct list_node *temp = list->head;
    list->head = temp->next;
    free(temp);
    
    return val;
}

size_t remove_last(struct linked_list *list) {
    if (!list || !list->head) return 0;
    
    struct list_node *prev = NULL;
    struct list_node *curr = list->head;
    
    while (curr->next) {
        prev = curr;
        curr = curr->next;
    }
    
    size_t val = curr->value;
    if (prev) {
        prev->next = NULL;
    } else {
        list->head = NULL;
    }
    free(curr);
    
    return val;
}

void destroy_list(struct linked_list list) {
    struct list_node *current = list.head;
    while (current) {
        struct list_node *next = current->next;
        free(current);
        current = next;
    }
}

void print_list(FILE *fp, struct linked_list list) {
    fprintf(fp, "[ ");
    for (struct list_node *node = list.head; node; node = node->next) {
        fprintf(fp, "%zu ", node->value);
    }
    fprintf(fp, "]\n");
}
