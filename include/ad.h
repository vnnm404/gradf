#ifndef AD_H
#define AD_H

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

ad_float* gradf(const char *format, ...);
int zero_grad(ad_float* y);
int backward(ad_float* y);

#endif // AD_H