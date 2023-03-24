#include"bool_arr.h"

typedef unsigned int uint;
void initialize_vector(vector_bool *vb)
{
    vb->arr = calloc(1, sizeof(*vb->arr));
    vb->size = vb->capacity = 0;

    if(!vb->arr)
        fprintf(stderr, "Failed to allocate bool vector");

    vb->capacity = sizeof(*vb->arr);
}

void destruct_vector(vector_bool *vb)
{
    vb->capacity = vb->size = 0;

    if(!vb->arr)
        return;

    free(vb->arr);
    vb->arr = NULL;
}

// Returns pointer to the an element in the array the index should point to
uint *get_byte_ptr(vector_bool vb, uint index)
{
    uint arr_idx = index / sizeof(*vb.arr);

    // Safe due to shallow copy
    return &vb.arr[arr_idx];
}

// Get bit-index value based on data type size(uint)
uint get_bit_index(vector_bool vb, uint index)
{
    return index % sizeof(*vb.arr);
}

uint get(const vector_bool vb, uint index)
{
    uint *byte_ind = get_byte_ptr(vb, index);
    uint bit_idx = get_bit_index(vb, index);

    // (*a & (1 << b)) gets wheteher the bit is on or off
    // (above expr) >> b shifts the bit to the Least significant position to yield either 0 or 1
    return ((*byte_ind & (1 << bit_idx)) >> bit_idx);
}

// credit: https://stackoverflow.com/questions/47981/how-do-i-set-clear-and-toggle-a-single-bit
void clear_bit(uint *number, uint position)
{
    *number &= ~(1UL << position);
}

void set(vector_bool *vb, uint index, uint bool_value)
{
    uint *elem = get_byte_ptr(*vb, index);
    uint bit_idx = get_bit_index(*vb, index);

    // Generalise bool value to 0 or 1
    if(bool_value)
        bool_value = 1;

    // Avoid hassle with setting bit, simply clear and then set
    clear_bit(elem, bit_idx);

    // Toggle bit to 1 if bool value is true
    if(bool_value)
        *elem ^= 1UL << bit_idx;
}

void expand(vector_bool *vb)
{
    if(!vb->arr)
    {
        initialize_vector(vb);
        return;
    }

    uint arr_count = vb->capacity / sizeof(vb->capacity);
    uint *new_arr = realloc(vb->arr, (arr_count + 1) * sizeof(*new_arr));

    if(!new_arr)
    {
        fprintf(stderr, "Allocation failed. Could not push back value.");
        return;
    }

    vb->capacity += sizeof(vb->capacity);
    vb->arr = new_arr;
    vb->arr[arr_count] = 0ULL;
}

void push_back(vector_bool *vb, uint bool)
{
    // Resize vector if full
    if(vb->size == vb->capacity)
        expand(vb);

    set(vb, vb->size, bool);
    ++vb->size;
}

void shrink(vector_bool *vb)
{
    if(vb->size == 0)
    {
        destruct_vector(vb);
        return;
    }

    uint arr_count = vb->capacity / sizeof(*vb->arr);
    uint *new_arr = realloc(vb->arr, (arr_count - 1) * sizeof(*new_arr));

    if(!new_arr)
    {
        printf("Deallocation failed. Could not shrink vector.");
        return;
    }

    vb->arr = new_arr;
    vb->capacity -= sizeof(vb->capacity);
}

void pop_back(vector_bool *vb)
{
    if(vb->size == 0)
        return;

    --vb->size;

    if(vb->capacity - vb->size == sizeof(*vb->arr))
        shrink(vb);
}