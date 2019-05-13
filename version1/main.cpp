#include <stdio.h>

#include "foo1.h"
#include "foo2.h"

int main() {
    printf("Hello World\n");
    printf("foo1: %d\n", foo1(5, 5));
    printf("foo2: %d\n", foo2(5, 5));
    return 0;
}