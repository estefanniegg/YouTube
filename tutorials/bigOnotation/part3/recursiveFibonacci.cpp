
/* The Big Oh Part 3, Example 1 O(2^n).
 *
 * This program takes a number (n) and calls jimmydoesthefibonacci(n) recursively
 * to output the nth number in the fibonacci sequence. I added a loop in main to
 * output the sequence for you to see it :) Have fun!
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

int jimmydoesthefibonacci(int number)
{
    if(number <= 1)
    {
        return number;
    }

    int output = jimmydoesthefibonacci(number -2) + jimmydoesthefibonacci(number -1);

    return output;
}

int main()
{
    int number;

    cout << "Please enter the number that you'd like to fibonacci: ";

    cin >> number;

    //This was added for you to see the sequence <-- not in the video
    cout << "Sequence: ";
    for(int i = 1; i < number; i++)
    {
        cout << jimmydoesthefibonacci(i) << ", ";
    }

    int result = jimmydoesthefibonacci(number);

    cout << result << endl;

    cout << "Fibonnacied: " << result << endl;

    cout << endl;

    return 0;
}


