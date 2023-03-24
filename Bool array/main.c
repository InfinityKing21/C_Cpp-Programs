#include<stdio.h>
#include"bool_arr.h"

void print(vector_bool vb)
{
    for(int i = 0; i < vb.size; ++i)
        printf("%u\n", get(vb, i));

    printf("\n");
}

int main(void)
{
    vector_bool vb;
    initialize_vector(&vb);

    push_back(&vb, 0);
    push_back(&vb, 0);
    push_back(&vb, 0);
    push_back(&vb, 0);
    push_back(&vb, 0);

    printf("Size of array: %u\n", vb.size);

    print(vb);

    set(&vb, 0, 0);
    set(&vb, 1, 1);
    set(&vb, 2, 0);
    set(&vb, 3, 1);
    set(&vb, 4, 0);

    print(vb);

    set(&vb, 0, 1);
    set(&vb, 1, 1);
    set(&vb, 2, 1);
    set(&vb, 3, 1);
    set(&vb, 4, 1);

    print(vb);

    set(&vb, 0, 0);
    set(&vb, 1, 0);
    set(&vb, 2, 0);
    set(&vb, 3, 0);
    set(&vb, 4, 0);

    print(vb);

    set(&vb, 0, 1);
    set(&vb, 1, 1);
    set(&vb, 2, 0);
    set(&vb, 3, 1);
    set(&vb, 4, 0);

    print(vb);

    push_back(&vb, 0);
    push_back(&vb, 1);
    push_back(&vb, 0);
    push_back(&vb, 1);
    push_back(&vb, 0);

    print(vb);

    pop_back(&vb);

    print(vb);

    pop_back(&vb);
    pop_back(&vb);
    pop_back(&vb);
    pop_back(&vb);
    pop_back(&vb);
    pop_back(&vb);

    print(vb);
    printf("%u %u", vb.size, vb.capacity);

    return 0;
}