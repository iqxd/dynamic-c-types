#include "micc.h"
int main()
{
    printf("hello micclib!\n");

    scoped_var_t i1 = NewValue(-3);
    scoped_var_t f1 = NewValue(-11.52);
    scoped_var_t f2 = NewValue(567.113456789);
    scoped_var_t f3 = NewValue(-0.0);
    scoped_var_t s1 = NewValue("12345678");
    scoped_var_t s2 = NewValue("I am going to take some good snacks");
    
    Print(i1); Print(f1); Print(f2); Print(f3); Print(s1); Print(s2);

    size_t n1 = Size(i1), n2 = Size(f1), n3 = Size(f3), n4 = Size(s1), n5 = Size(s2);
    printf("n1 = %zu, n2 = %zu, n3 = %zu, n4 = %zu, n5 = %zu\n", n1, n2, n3, n4, n5);
    
    scoped_var_t i2 = Clone(i1);
    scoped_var_t f4 = Clone(f1);
    scoped_var_t s3 = Clone(s2);
    scoped_var_t s4 = Clone(s3);
    Print(s4);
    scoped_var_t null0 = VAR_NULL;
    Print(null0);
    scoped_var_t i4 = NewValue(-78);
    scoped_var_t i5 = NewValue(0.2);
    scoped_var_t s5 = NewValue("ssst");
    scoped_var_t s6 = NewValue("seeing is believing, let me investigate");
    scoped_var_t l1 = set_empty_list();
    scoped_var_t l2 = set_list((var_t[]) { i4, i5, s5, s6 }, 4);
    Print(l1); Print(l2);
    scoped_var_t l3 = clone_list(l2);
    Print(l3);
    printf("size s6 = %zu , size l3 = %zu\n", Size(s6), Size(l3));
    scoped_var_t l4 = clone_list(l2);
    list_update(l4, 1, l2);
    Print(l4);
    
    list_remove(l2, 2);
    Print(l2);
    if (!list_empty(l2))
        list_clear(l2);
    Print(l2);
    scoped_var_t v1 = list_get(l3, 1);
    scoped_var_t v2 = list_pop(l3);
    list_add(l1, VAR_NULL);
    Print(v1); Print(v2);Print(l1);
 
    scoped_var_t s7 = NewValue("my name is Jerry , i am 20 years old");
    
#ifdef _MSC_VER
    Delete(&i1);  
    Delete(&f1);
    Delete(&f4);
    Delete(&s1);
    Delete(&s3);
    Delete(&s4);
    Delete(&s2);
    Delete(&l4);
    Delete(&v2);
    Delete(&l1);
    Delete(&l2);
    Delete(&l3);
    Delete(&s5);
    Delete(&s6);
#endif
    
    
#ifdef LEAK_DEBUG
    _CrtDumpMemoryLeaks();
#endif
}
