#ifndef BOOL_ARR
#define BOOL_ARR

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


typedef struct vector_bool
{
    unsigned int *arr;
    unsigned int size;
    unsigned int capacity;
} vector_bool;

void initialize_vector(vector_bool *vb);
void destruct_vector(vector_bool *vb);

unsigned int get(const vector_bool vb, unsigned int index);
void set(vector_bool *vb, unsigned int index, unsigned int bool_value);

void push_back(vector_bool *vb, unsigned int bool);
void pop_back(vector_bool *vb);
#endif