#include <assert.h>
#include <stdio.h>
#include <iostream>

template<typename T>
T* AddArrayElement(T* array, int size, const T& element)
{
    // Create a new array with increased size
    int newSize = size + 1;
    T* newArray = new T[newSize];

    // Copy existing elements to the new array
    for (int i = 0; i < size; i++)
    {
        newArray[i] = array[i];
    }

    // Copy the new element
    newArray[size] = element;

    // Delete the old array if it was dynamically allocated
    delete[] array;


    return newArray;
}