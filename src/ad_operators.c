#include <stdlib.h>
#include "ad.h"

ad_float* __ad_add(ad_float* a, ad_float* b) {
    if (a == NULL || b == NULL) return NULL;

    ad_float* y = __ad_make(
        a->data + b->data,
        0,
        a,
        b,
        AD_OP_ADD
    );

    return y;
}

ad_float* __ad_add_float(ad_float* a, float b) {
    if (a == NULL) return NULL;

    ad_float* node_b = ad(b);

    ad_float* y = __ad_make(
        a->data + b,
        0,
        a,
        node_b,
        AD_OP_ADD
    );

    return y;
}

ad_float* __ad_subtract(ad_float* a, ad_float* b) {
    if (a == NULL || b == NULL) return NULL;

    ad_float* y = __ad_make(
        a->data - b->data,
        0,
        a,
        b,
        AD_OP_SUBTRACT
    );

    return y;
}

ad_float* __ad_multiply(ad_float* a, ad_float* b) {
    if (a == NULL || b == NULL) return NULL;

    ad_float* y = __ad_make(
        a->data * b->data,
        0,
        a,
        b,
        AD_OP_MULTIPLY
    );

    return y;
}

ad_float* __ad_multiply_float(ad_float* a, float b) {
    if (a == NULL) return NULL;

    ad_float* node_b = ad(b);

    ad_float* y = __ad_make(
        a->data * b,
        0,
        a,
        node_b,
        AD_OP_MULTIPLY
    );

    return y;
}

ad_float* __ad_divide(ad_float* a, ad_float* b) {
    if (a == NULL || b == NULL) return NULL;

    ad_float* y = __ad_make(
        a->data / b->data,
        0,
        a,
        b,
        AD_OP_DIVIDE
    );

    return y;
}
