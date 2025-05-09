#include "linked_list.h"

#include <stdlib.h>

struct list_node* new_node(size_t value) {
    struct list_node* node = malloc(sizeof(struct list_node));
    node->value = value;
    node->next = NULL;
    return node;
}

void insert_at_head(struct linked_list* list, size_t value) {
    struct list_node* newHead = new_node(value);
    newHead->next = list->head;
    list->head = newHead;
}

void insert_at_tail(struct linked_list* list, size_t value) {
    struct list_node* node = list->head;
    // length 0 or 1
    if (node == NULL || node->next == NULL) {
        insert_at_head(list, value);
        return;
    }

    while (node->next != NULL) {
        node = node->next;
    }
    node->next = new_node(value);
}

size_t remove_from_head(struct linked_list* list) {
    struct list_node* oldHead = list->head;
    size_t value = oldHead->value;
    list->head = oldHead->next;

    free(oldHead);
    return value;
}

size_t remove_from_tail(struct linked_list* list) {
    struct list_node* node = list->head;
    // list has length 1
    if (node->next == NULL) {
        return remove_from_head(list);
    }

    // list has length >= 2
    while (node->next->next != NULL) {
        node = node->next;
    }
    struct list_node* tail = node->next;
    size_t value = tail->value;
    node->next = NULL;

    free(tail);
    return value;
}

void free_list(struct linked_list list) {
    struct list_node* node = list.head;
    while (node != NULL) {
        struct list_node* nextNode = node->next;
        free(node);
        node = nextNode;
    }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE* fp, struct linked_list list) {
    fprintf(fp, "[ ");
    for (struct list_node* cur = list.head; cur != NULL; cur = cur->next) {
        fprintf(fp, "%zu ", cur->value);
    }
    fprintf(fp, "]\n");
}
