#include "micc.h"
#include "tagptr.h"
int main()
{
    printf("hello micclib!\n");

    puts("\n*** num_t test ***");
    num_t n1 = new_num(11);
    num_t n2 = new_num(3.14159);
    num_t n3 = new_num(-202);
    num_t n4 = new_num(false);
    uint8_t i1 = 137;
    int i2 = -1001;
    print(n1);
    print(n2);
    print(n3);
    print(n4);
    print(new_num(i1));
    print(new_num(i2));

    puts("\n*** str_t test ***");
    str_t s1 = new_str("abcdedf");
    char c1[] = "listen to me, it's very important";
    print(s1);
    print(new_str(c1));
    
    puts("\n*** list_t test ***");
    num_t nn1 = new_num(201);
    num_t nn2 = new_num(100.1);
    str_t ss1 = new_str("hello world");
    str_t ss2 = new_str("everyone should work hard for our future"); 
    num_t nn3 = new_num(99999999);
    
    list_t* l1 = new_list((var_t * []) {(var_t*)&nn1,(var_t*)&nn2,(var_t*)&ss1}, 3);
    list_t* l2 = new_list((var_t * []) {(var_t*)&ss2,(var_t*)l1,(var_t*)&nn3}, 3);
    list_t* l3 = (list_t*)clone(l2);
    list_t* l4 = new_list(NULL, 0);
    list_add(l4, (var_t*)&nn1);
    list_add(l4, (var_t*)l1);
    list_add(l4, (var_t*)&ss1);
    
    print(l1);
    print(l2);
    print(l3);
    print(l4);
    
    delete(l1);
    delete(l2);
    delete(l3);
    delete(l4);
    
    tagptr_t tg1 = new_int(-3);
    printf("0x%16.16p\n", (void*)tg1);
    
    int iv1 = get_int(tg1);
    tag_t tt1 = get_tag(tg1);
    printf("%d %d\n", iv1, tt1);
    
    tagptr_t tg2 = new_float(-11.52);
    void *dv1 = get_ref(tg2);
    tag_t tt2 = get_tag(tg2);
    printf("%f %d\n", *((double*)dv1), tt2);
    free(dv1);
}