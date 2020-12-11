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
}