#include <stdio.h>
#include <stdlib.h>
#include "ad.h"

__stack* __ad_stack() {
    __stack* s = (__stack*)malloc(sizeof(__stack));
    s->top = NULL;
    s->size = 0;
    return s;
}

int __ad_is_stack_empty(__stack* s) {
    return s->size == 0;
}

void __ad_push(__stack* s, ad_float* data) {
    __node* node = (__node*)malloc(sizeof(__node));
    node->data = data;
    node->next = s->top;
    s->top = node;
    s->size++;
}

void __ad_push_op(__stack* s, enum ad_op op) {
    __node* node = (__node*)malloc(sizeof(__node));
    node->data = NULL;
    node->op = op;
    node->next = s->top;
    s->top = node;
    s->size++;
}

ad_float* __ad_pop(__stack* s) {
    if (__ad_is_stack_empty(s)) {
        return NULL;
    }

    __node* temp = s->top;
    ad_float* data = temp->data;
    s->top = temp->next;
    free(temp);
    s->size--;

    return data;
}

enum ad_op __ad_pop_op(__stack* s) {
    if (__ad_is_stack_empty(s)) {
        return -1;
    }

    __node* temp = s->top;
    enum ad_op data = temp->op;
    s->top = temp->next;
    free(temp);
    s->size--;

    return data;
}

void __ad_free_stack(__stack* s) {
    while (!__ad_is_stack_empty(s)) {
        __ad_pop(s);
    }

    free(s);
}
