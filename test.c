#include "tagptr.h"
int main()
{
    printf("hello micclib!\n");

    tagptr_t tg1 = set_int(-3);
    printf("%16.16p\n", (void*)tg1);
    
    int iv1 = get_int(tg1);
    tag_t tt1 = get_tag(tg1);
    printf("%d %d\n", iv1, tt1);
    
    tagptr_t tg2 = set_float(-11.52);
    void *dv1 = get_ref(tg2);
    tag_t tt2 = get_tag(tg2);
    printf("%f %d\n", get_float(tg2), tt2);
    free(dv1);
    
    tagptr_t pf1 = set_float(567.113456789);
    tag_t ptag1 = get_tag(pf1);
    printf("%.16f %d\n", get_float(pf1), ptag1);
    
    tagptr_t p3 = set_float(-0.0);
    printf("p3 = %.16f\n", get_float(p3));
    
    tagptr_t tstr1 = set_str("12345678");
    printf("short: %s\n", get_str(tstr1));
    tagptr_t tstr2 = set_str("I am going to take some good snacks");
    printf("long: %s\n", get_str(tstr2));
}