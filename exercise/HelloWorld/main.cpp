/**
 * This program prints "Hello World" in the terminal.
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

int main()
{
    //buggy version
    //cout<<"Hello,"+"World!"<<endl;
    string s0 ("Hello,");
    cout<<s0+"World!"<<endl;
    return 0;
}
