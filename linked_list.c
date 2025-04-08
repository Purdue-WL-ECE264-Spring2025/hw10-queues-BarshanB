#include "linked_list.h"
#include <stdlib.h>

struct list_node *new_node(size_t value) {
    struct list_node *node = malloc(sizeof(struct list_node));
    if (node) {
        node->value = value;
        node->next = NULL;
    }
    return node;
}

void insert_at_head(struct linked_list *list, size_t value) {
    struct list_node *node = new_node(value);
    if (node) {
        node->next = list->head;
        list->head = node;
    }
}

void insert_at_tail(struct linked_list *list, size_t value) {
    struct list_node *node = new_node(value);
    if (!node) return;

    if (list->head == NULL) {
        list->head = node;
    } else {
        struct list_node *curr = list->head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = node;
    }
}

size_t remove_from_head(struct linked_list *list) {
    if (!list->head) return 0;

    struct list_node *temp = list->head;
    size_t val = temp->value;
    list->head = temp->next;
    free(temp);
    return val;
}

size_t remove_from_tail(struct linked_list *list) {
    if (!list->head) return 0;

    struct list_node *prev = NULL;
    struct list_node *curr = list->head;

    while (curr->next != NULL) {
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

void free_list(struct linked_list list) {
    struct list_node *curr = list.head;
    while (curr) {
        struct list_node *next = curr->next;
        free(curr);
        curr = next;
    }
}

// Debug utility - do not modify
void dump_list(FILE *fp, struct linked_list list) {
    fprintf(fp, "[ ");
    for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
        fprintf(fp, "%zu ", cur->value);
    }
    fprintf(fp, "]\n");
}
