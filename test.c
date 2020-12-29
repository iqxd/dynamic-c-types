#include "tagptr.h"
int main()
{
    printf("hello micclib!\n");

    tagptr_t i1 = set_int(-3);
    tagptr_t f1 = set_float(-11.52);
    tagptr_t f2 = set_float(567.113456789);
    tagptr_t f3 = set_float(-0.0);
    tagptr_t s1 = set_str("12345678");
    tagptr_t s2 = set_str("I am going to take some good snacks");
}