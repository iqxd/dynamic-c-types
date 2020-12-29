#include "tagptr.h"
int main()
{
    printf("hello micclib!\n");

    var_t i1 = set_int(-3);
    var_t f1 = set_float(-11.52);
    var_t f2 = set_float(567.113456789);
    var_t f3 = set_float(-0.0);
    var_t s1 = set_str("12345678");
    var_t s2 = set_str("I am going to take some good snacks");
    
    Print(i1); Print(f1); Print(f2); Print(f3); Print(s1); Print(s2);

    size_t n1 = Size(i1), n2 = Size(f1), n3 = Size(f3), n4 = Size(s1), n5 = Size(s2);
    printf("n1 = %zu, n2 = %zu, n3 = %zu, n4 = %zu, n5 = %zu\n", n1, n2, n3, n4, n5);
    
    var_t i2 = Clone(i1);
    Delete(&i1);
    var_t f4 = Clone(f1);
    Delete(&f4);
    var_t s3 = Clone(s2);
    var_t s4 = Clone(s3);
    Print(s4);
    Delete(&s3);
    Delete(&s4);
    Delete(&s2);
}