#include <assert.h>
#include <stdio.h>
#include <iostream>

template<typename T>
T* AddArrayElement(T* array, int size, T element)
{
    // Create a new array with increased size
    int newSize = size + 1;
    T* newArray = (T*)malloc(newSize * sizeof(T));

    // Copy existing elements to the new array
    for (int i = 0; i < size; i++)
    {
        newArray[i] = array[i];
    }

    // Append the new element
    newArray[size] = element;

    // Free the memory of the old array
    free(array);

    return newArray;
}