#include <stdio.h>
#include <stdlib.h>
#include "ad.h"

int main() {
    ad_float* a = ad(2);
    ad_float* b = ad(2);

    printf("[before]\n");

    ad_float* c = gradf("x + x*x", b, b, a);
    backward(c);

    printf("data: %f %f %f\n", a->data, b->data, c->data);
    printf("grad: %f %f %f\n", a->grad, b->grad, c->grad);

    free_graph(c);
}