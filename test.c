#include "micc.h"
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
    num_t* np1 = malloc(sizeof(num_t));
    *np1 = new_num(201);
    num_t* np2 = malloc(sizeof(num_t));
    *np2 = new_num(100.1);
    str_t* sp1 = malloc(sizeof(str_t));
    *sp1 = new_str("hello world");
    
    str_t* sp2 = malloc(sizeof(str_t));
    *sp2 = new_str("everyone should work hard for our future");
    num_t* np3 = malloc(sizeof(num_t));
    *np3 = new_num(99999999);
    
    list_t* l1 = new_list((var_t * []) {(var_t*)np1,(var_t*)np2,(var_t*)sp1}, 3);
    list_t* l2 = new_list((var_t * []) {(var_t*)sp2,(var_t*)l1,(var_t*)np3}, 3);
    
    print(l1);
    print(l2);

    delete(l2);
}