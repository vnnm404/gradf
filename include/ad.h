#ifndef AD_H
#define AD_H

#include <stdbool.h>

enum ad_op {
    AD_OP_ADD,
    AD_OP_SUBTRACT,
    AD_OP_MULTIPLY,
    AD_OP_DIVIDE,
};

typedef struct ad_float {
    float data;
    float grad;
    
    struct ad_float* factor_a;
    struct ad_float* factor_b;
    enum ad_op op;
    bool visited;
} ad_float;

ad_float* __ad_make(
    float data,
    float grad,
    ad_float* factor_a,
    ad_float* factor_b,
    enum ad_op op
);
ad_float* ad(float data);
void del_compute_graph(ad_float* x);

ad_float* __ad_add(ad_float* a, ad_float* b);
ad_float* __ad_add_float(ad_float* a, float b);
ad_float* __ad_subtract(ad_float* a, ad_float* b);
ad_float* __ad_multiply(ad_float* a, ad_float* b);
ad_float* __ad_multiply_float(ad_float* a, float b);
ad_float* __ad_divide(ad_float* a, ad_float* b);

ad_float* gradf(const char* format, ...);
int zero_grad(ad_float* y);
int backward(ad_float* y);
int free_graph(ad_float* y);

typedef struct __node {
    ad_float* data;
    enum  ad_op op;
    struct __node* next;
} __node;

typedef struct __stack {
    __node* top;
    int size;
} __stack;

__stack* __ad_stack();
int __ad_is_stack_empty(__stack* s);
void __ad_push(__stack* s, ad_float* data);
void __ad_push_op(__stack* s, enum ad_op op);
ad_float* __ad_pop(__stack* s);
enum ad_op __ad_pop_op(__stack* s);
void __ad_free_stack(__stack* s);

#endif // AD_H