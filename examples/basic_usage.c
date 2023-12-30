#include <stdio.h>
#include "ad.h"

int main() {
    float x = 3.0f;
    float y = 4.0f;
    float result = ad_add(x, y);
    printf("The sum of %f and %f is %f\n", x, y, result);
    return 0;
}