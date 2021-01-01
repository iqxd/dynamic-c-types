#include "micc.h"
int main()
{
    printf("hello micclib!\n");

    var_t i1 = NewValue(-3);
    var_t f1 = NewValue(-11.52);
    var_t f2 = NewValue(567.113456789);
    var_t f3 = NewValue(-0.0);
    var_t s1 = NewValue("12345678");
    var_t s2 = NewValue("I am going to take some good snacks");
    
    Print(i1); Print(f1); Print(f2); Print(f3); Print(s1); Print(s2);

    size_t n1 = Size(i1), n2 = Size(f1), n3 = Size(f3), n4 = Size(s1), n5 = Size(s2);
    printf("n1 = %zu, n2 = %zu, n3 = %zu, n4 = %zu, n5 = %zu\n", n1, n2, n3, n4, n5);
    
    var_t i2 = Clone(i1);
    Delete(&i1);
    var_t f4 = Clone(f1);
    Delete(&f1);
    Delete(&f4);
    Delete(&s1);
    var_t s3 = Clone(s2);
    var_t s4 = Clone(s3);
    Print(s4);
    Delete(&s3);
    Delete(&s4);
    Delete(&s2);
    var_t null0 = VAR_NULL;
    Print(null0);
#ifdef LEAK_DEBUG
    _CrtDumpMemoryLeaks();
#endif
}