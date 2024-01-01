#include <stdio.h>
#include <stdlib.h>
#include "ad.h"

int main() {
    ad_float* a = ad(1);
    ad_float* b = __ad_add(a, a);
    ad_float* c = __ad_multiply(b, b);
    ad_float* d = __ad_add(b, c);

    backward(d);

    printf("data: %f %f %f %f\n", a->data, b->data, c->data, d->data);
    printf("grad: %f %f %f %f\n", a->grad, b->grad, c->grad, d->grad);

    free_graph(d);
}