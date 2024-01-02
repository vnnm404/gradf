#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "ad.h"

ad_float* __gradf_make(ad_float* a, ad_float* b, enum ad_op op) {
    ad_float* c;

    switch (op)
    {
        case AD_OP_ADD:
            c = __ad_add(a, b);
            break;
        case AD_OP_SUBTRACT:
            c = __ad_subtract(a, b);
            break;
        case AD_OP_MULTIPLY:
            c = __ad_multiply(a, b);
            break;
        case AD_OP_DIVIDE:
            c = __ad_divide(a, b);
            break;
    }

    return c;
}

ad_float* gradf(const char* format, ...) {
    if (format == NULL) return NULL;

    va_list args;
    va_start(args, format);

    printf("[start]\n");

    int n = 0;
    const char *end;
    for(end = format; *end != '\0'; end++) {
        if (*end == 'x') n++;
    }

    printf("[n] %d\n", n);

    __stack* s = __ad_stack();

    for(const char* f = format; *f != '\0'; f++) {
        if (*f == ' ') continue;

        if (*f == 'x') {
            printf("[arg]\n");
            ad_float* x = va_arg(args, ad_float*);

            if (!__ad_is_stack_empty(s)) {
                // operator on top
                enum ad_op op = __ad_pop_op(s);
                ad_float* r = __ad_pop(s);
                printf("[op] %d\n", op);
                x = __gradf_make(r, x, op);
            }

            printf("[pushed]\n");
            __ad_push(s, x);
        } else {
            switch (*f)
            {
                case '+': __ad_push_op(s, AD_OP_ADD); break;
                case '-': __ad_push_op(s, AD_OP_SUBTRACT); break;
                case '/': __ad_push_op(s, AD_OP_DIVIDE); break;
                case '*': __ad_push_op(s, AD_OP_MULTIPLY); break;
            }
        }
    }

    ad_float* r = __ad_pop(s);

    __ad_free_stack(s);
    va_end(args);
    return r;
}
