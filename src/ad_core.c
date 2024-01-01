#include <stdio.h>
#include <stdlib.h>
#include "ad.h"

ad_float* __ad_make(
    float data,
    float grad,
    ad_float* factor_a,
    ad_float* factor_b,
    enum ad_op op
) {
    ad_float* x = (ad_float*) malloc(sizeof(ad_float));
    if (x == NULL) return NULL;

    x->data = data;
    x->grad = grad;
    x->factor_a = factor_a;
    x->factor_b = factor_b;
    x->op = op;
    x->visited = false;

    return x;
}

ad_float* ad(float data) {
    ad_float* x = __ad_make(data, 0, NULL, NULL, 0);
    return x;
}

int zero_grad(ad_float* y) {
    if (y == NULL) return 0;
    
    y->grad = 0;
    y->visited = false;
    if (y->factor_a) zero_grad(y->factor_a);
    if (y->factor_b) zero_grad(y->factor_b);
    return 0;
}

int __ad_update(ad_float* y) {
    if (y->factor_a == NULL || y->factor_b == NULL) return 0;

    float grad = y->grad;
    float a = y->factor_a->data;
    float b = y->factor_b->data;

    switch (y->op)
    {
        case AD_OP_ADD: {
            y->factor_a->grad += grad;
            y->factor_b->grad += grad;
            break;
        }

        case AD_OP_SUBTRACT: {
            y->factor_a->grad += grad;
            y->factor_b->grad += -1 * grad;
            break;
        }

        case AD_OP_MULTIPLY: {
            y->factor_a->grad += grad * b;
            y->factor_b->grad += grad * a;
            break;
        }

        case AD_OP_DIVIDE: {
            y->factor_a->grad += grad / b;
            y->factor_b->grad += grad * (-1 * a / (b * b));
            break;
        }
        
        default: {
            break;
        }
    }
    return 0;
}

void __ad_dfs(ad_float* y, __stack* s) {
    if (y == NULL || y->visited) return;

    y->visited = true;

    __ad_dfs(y->factor_a, s);
    __ad_dfs(y->factor_b, s);

    __ad_push(s, y);
}

int backward(ad_float* y) {
    if (y == NULL) return 0;

    __stack* s = __ad_stack();

    zero_grad(y);
    y->grad = 1;

    __ad_dfs(y, s);

    while (!__ad_is_stack_empty(s)) {
        ad_float* x = __ad_pop(s);
        __ad_update(x);
    }

    __ad_free_stack(s);
    return 0;
}

int free_graph(ad_float* y) {
    if (y == NULL) return 0;

    __stack* s = __ad_stack();

    zero_grad(y);
    __ad_dfs(y, s);

    while (!__ad_is_stack_empty(s)) {
        ad_float* x = __ad_pop(s);
        free(x);
    }

    __ad_free_stack(s);

    return 0;
}