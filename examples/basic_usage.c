#include <stdio.h>
#include <stdlib.h>
#include "ad.h"

int main() {
    ad_float* a = ad(2);
    ad_float* b = __ad_add_float(a, 1);
    ad_float* c = ad(1);
    ad_float* d = __ad_divide(c, b);
    backward(d);

    printf("data: %f %f %f %f\n", a->data, b->data, c->data, d->data);
    printf("grad: %f %f %f %f\n", a->grad, b->grad, c->grad, d->grad);

    free(c), free(b), free(a);
}