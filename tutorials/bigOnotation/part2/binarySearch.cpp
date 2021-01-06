
/* The Big Oh Part 2, Example 1 O(logn).
* https://www.youtube.com/watch?v=5kBP1Kmye10
*
* This program takes a number (n) and calls binarySearch(n, array, arraySize)
* to search that number in the array. In the while loop, we cut the array in half,
* check the number in the middle of the array, and if it does not match our number,
* we determine which half we continue to search in. We repeat until we find our
* number. This gives us the logarithmic complexity of O(logn).
*
* I added a loop in main to output the list for you to see it. We are not taking
* this loop's complexity into account ;) Have fun!
*
* This file is part of the Estefannie Explains It All repo.
*
* (c) Estefannie Explains It All <estefannieexplainsitall@gmail.com>
*
* For the full copyright and license information, please view the LICENSE
* file that was distributed with this source code.
*/

#include <iostream>

using namespace std;

int steps = 1;

bool binarySearch(int target, int nums[], int length) {

   int floorIndex = -1;
   int ceilingIndex = length;

   // This while loop cuts the list in half and checks the
   // target number with the number in the middle of the list
   // (guessValue). Since we cut in half until we find the one,
   // we get a complexity of O(logn).
   while (floorIndex + 1 < ceilingIndex)
   {
       int distance = ceilingIndex - floorIndex;
       int halfDistance = distance / 2;
       int guessIndex = floorIndex + halfDistance;

       int guessValue = nums[guessIndex];

       cout << "Comparing your number with: ";
       cout << guessValue << endl;

       if (guessValue == target)
       {
           return true;
       }
       if (guessValue > target)
       {
           ceilingIndex = guessIndex;
       }
       else
       {
           floorIndex = guessIndex;
       }

       steps++;
   }
   return false;
}


int main()
{
   int target;
   int nums[] = {0, 2, 4, 6, 7, 21, 35, 45, 54, 67, 79, 82, 96, 101};
   int length = sizeof(nums) / sizeof(nums[0]);

   cout << "Enter a number you'd like to search from my list." << endl;
   cout << "My list: ";

   // This loop was added for you to see the list and it is not in the video
   // We are not taking the time complexity of this loop into account.
   for (int i = 0; i < length; i++)
   {
       cout << nums[i] << " ";
   }

   cout << "\n\nSearch for: ";
   cin >>target;

   bool found = binarySearch(target, nums, length);

   if(found == true)
   {
       cout << "\nYour number was found in " << steps << " steps!\n\n";
   }
   else
   {
       cout << "\nWe searched through our list "  << steps << " times. Your number is not in my list.\n\n";
   }

   return 0;
}


