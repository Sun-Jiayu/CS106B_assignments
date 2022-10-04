#include "console.h"
#include <iostream>
#include <cmath> //for pow operation
#include "testing/SimpleTest.h"
using namespace std;

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division.
 *
 * Note: long is a C++ type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    //introduce a bug
    //long total = 1;
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to sqrt(n), testing for a
 * zero remainder from the division. And the larger paired divisors will
 * be found by the smaller paired divisors rather than a loop iteration.
 */
long smarterSum(long n) {
        long total = 0;
        long pairedDivisor =1;
        //For loop is to obtain the sum of proper divisors
        //Note: the data type of sqrt() is double.
        for (long divisor = 1; divisor <= sqrt(n); divisor++) {
            if (n % divisor == 0) {
                total += divisor;
                pairedDivisor = (n/divisor);
                //if the pairedDivisor is not the number itself, do the sum
                if(divisor!=1){
                    total +=pairedDivisor;
                }
                //if the pairedDivisor equals the divisor,deduct it from the sum.
                if(divisor==pairedDivisor){
                    total -=pairedDivisor;
                }
            }
        }
        return total;
    }

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfectSmarter(long n) {
    return (n != 0) && (n == smarterSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfectsSmarter(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to sqrt(n), testing for a
 * zero remainder from the division. And the larger paired divisors will
 * be found by the smaller paired divisors rather than a loop iteration.
 */
long findNthPerfectEuclid(long n) {
    long m = 0;
    long perfectNthNumber = 0;
    long k = 2;//for the calculation of the Mersenne number
    for(int j = 1;j <= n; ){
     //Calculate the Mersenne number
     m = pow (2, k) - 1;
     //If the Mersenne number is a prime number,caculate the perfect number.
     if(divisorSum(m) == 1){
          perfectNthNumber=pow (2, k-1)*m;
          j++;
     }
     k++;
    }
    return perfectNthNumber;
}
/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */

PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(10000, findPerfects(10000));
    TIME_OPERATION(20000, findPerfects(20000));
    TIME_OPERATION(40000, findPerfects(40000));
}

/* * * * * * Test Cases * * * * * */
STUDENT_TEST("Confirm -12 and -98765 are not perfect") {
    EXPECT(!isPerfect(-12));
    EXPECT(!isPerfect(-98765));
}

STUDENT_TEST("Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(60000, findPerfects(60000));
    TIME_OPERATION(120000, findPerfects(120000));
}

STUDENT_TEST("Confirm divisorSum equals smarterSum") {
    EXPECT_EQUAL(divisorSum(25), smarterSum(25));
    EXPECT_EQUAL(divisorSum(49), smarterSum(49));
    EXPECT_EQUAL(divisorSum(120), smarterSum(120));
}

STUDENT_TEST("Time trials of findPerfectsSmarter on doubling input sizes") {
    TIME_OPERATION(960000, findPerfectsSmarter(960000));
    TIME_OPERATION(1920000, findPerfectsSmarter(1920000));
    TIME_OPERATION(3840000, findPerfectsSmarter(3840000));
    TIME_OPERATION(7680000, findPerfectsSmarter(7680000));
}

STUDENT_TEST("Confirm findNthPerfectEuclid equals NthPerfectNumber") {
    EXPECT_EQUAL(findNthPerfectEuclid(2), 28);
    EXPECT_EQUAL(findNthPerfectEuclid(3), 496);
    EXPECT_EQUAL(findNthPerfectEuclid(4), 8128);
    EXPECT_EQUAL(findNthPerfectEuclid(5), 33550336);
}

STUDENT_TEST("Time trials of findNthPerfectEuclid on doubling input sizes") {
    TIME_OPERATION(10, findPerfectsSmarter(10));
    TIME_OPERATION(20, findPerfectsSmarter(20));
    TIME_OPERATION(30, findPerfectsSmarter(30));
    TIME_OPERATION(40, findPerfectsSmarter(40));
}
