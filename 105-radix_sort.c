#include <stdio.h>
#include <stdlib.h>

void print_array(int *array, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%d", array[i]);
        if (i < size - 1)
            printf(", ");
    }
    printf("\n");
}

/**
 * get_max - Returns the largest number in an array
 * @array: Array of integers
 * @size: Size of the array
 * Return: The largest integer in the array
 */
int get_max(int *array, size_t size)
{
    int max = array[0];

    for (size_t i = 1; i < size; i++)
    {
        if (array[i] > max)
            max = array[i];
    }

    return max;
}

/**
 * counting_sort - A function to perform stable counting sort based on a specific digit
 * @array: The array to be sorted
 * @size: The size of the array
 * @exp: The current exponent (digit to sort by)
 */
void counting_sort(int *array, size_t size, int exp)
{
    int *output = malloc(size * sizeof(int));  // Output array to store sorted values
    int count[10] = {0};  // Initialize counting array for digits 0-9

    // Store count of occurrences in count[]
    for (size_t i = 0; i < size; i++)
    {
        count[(array[i] / exp) % 10]++;
    }

    // Change count[i] so that it now contains the actual position of this digit in output[]
    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    // Build the output array using the count positions
    for (size_t i = size; i > 0; i--)
    {
        output[count[(array[i - 1] / exp) % 10] - 1] = array[i - 1];
        count[(array[i - 1] / exp) % 10]--;
    }

    // Copy the sorted numbers into the original array
    for (size_t i = 0; i < size; i++)
    {
        array[i] = output[i];
    }

    free(output);

    // Print array after sorting by current digit
    print_array(array, size);
}

/**
 * radix_sort - The main function to implement LSD radix sort
 * @array: The array to be sorted
 * @size: The size of the array
 */
void radix_sort(int *array, size_t size)
{
    // Find the maximum number to figure out the number of digits
    int max = get_max(array, size);

    // Perform counting sort for every digit (starting from the least significant digit)
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        counting_sort(array, size, exp);
    }
}

