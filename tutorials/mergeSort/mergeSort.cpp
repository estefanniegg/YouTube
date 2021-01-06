/* Mergesort example.
 *
 * This program creates an array of ten elements and sorts
 * the list using a mergesort algorithm. See the comments in the code
 * for a detailed explanation. Have fun =)
 *
 * This file is part of the Estefannie Explains It All repo.
 *
 * (c) Estefannie Explains It All <estefannieexplainsitall@gmail.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

#include <iostream>
#include <array>

using namespace std;

void merge(int array[], int startIndex, int endIndex)
{
    int arraySize = (endIndex - startIndex) + 1;

    //We create a new array, the reason it is a pointer
    //is so that it is a dynamic array. i.e. the size is a variable.
    int *tempArray = new int [arraySize]();

    int i = startIndex;
    int middle = (startIndex + endIndex)/2;
    int counter = 0;
    int j = middle + 1;

    /*
     * This while loop checks if the i is less than the middle of the array
     * and if the element is less than j. If it is then it Moves the i index
     * and saves that element in the tempArray. Else, it moves the j index
     * and saves that element in the tempArray.
     *
     * FIRST ITERATION:
     *
     * numbers = {2, 5, 6, 4, 7, 1, 8, 3, 9, 10}
     * counter = 0
     * i = 0, so the element is 2
     * j = 5, so the element is 1
     * 2 is not less than 1.
     * Go to else and place 1 in tempArray at 0, increment j
     * tempArray = {1}
     *
     * SECOND ITERATION:
     *
     * numbers = {2, 5, 6, 4, 7, 1, 8, 3, 9, 10}
     * counter = 1
     * i = 0, so the element is 2
     * j = 6, so the element is 8
     * 2 is less than 8.
     * Go to if, and place 2 in tempArray at 1, increment i
     * tempArray = {1,2}
     *
     * And so on..
     *
     */

    while (counter < arraySize)
    {
        if((i <= middle) && (array[i] < array[j]))
        {
            tempArray[counter++] = array[i++];
        }
        else
        {
            tempArray[counter++] = array[j++];
        }
    }

    //This loop puts the elements of our tempArray into numbers
    for(int i=0; i < arraySize; i++)
    {
        array[startIndex+i] = tempArray[i];
    }

    //delete tempArray to clean up memory
    delete []tempArray;
}

void mergeSort(int numbers[], int startIndex, int endIndex)
{
    //This means you are done with your array, so you return.
    if (startIndex >= endIndex)
    {
        return;
    }

    //First, we find the middle of the array
    int midIndex = (startIndex + endIndex)/2;

    //First recursive call
    //this is what splits my array on the left until you have one
    mergeSort(numbers, startIndex, midIndex);

    //Second recursive call
    //this is what splits my array on the right until you have one
    mergeSort(numbers, midIndex+1, endIndex);

    //The merge function
    //This is where we do the sorting. The recursive calls above are
    //the ones changing your start and end indeces.
    merge(numbers, startIndex, endIndex);
}

int main()
{
    int numbers[10] = {2,5,6,4,7,1,8,3,9,10};

    mergeSort(numbers, 0, 9);

    //printing the sorted array :)
    for(int i=0; i < 10; i++)
    {
        cout << numbers[i] << ", ";
    }

    return 0;
}



