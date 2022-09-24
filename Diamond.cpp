/**
 * This program prints some special figures in the terminal.
 */
#include <iostream>
#include <string>
#include "console.h"
#include <cmath>
using namespace std;

void outputStar(int layer)
{
    for(int i=0;i<layer;i++){
        for(int j=0;j<=i+layer-1;j++){
            if((i+j)%2!=0 && (i+j)>=(layer-1)){
                cout<<"*";
            }
            else {
                 cout<<" ";
            }
        }
        cout<<endl;
    }
}
void outputEmptyStar(int layer)
{
    for(int i=0;i<layer;i++){
        for(int j=0;j<=i+layer-1;j++){
            //非末尾行
            if(((i+j)==(layer-1) || j==(i+layer-1)) && i!=(layer-1)){
                cout<<"*";
                //cout<<i+1;
            }
            //末尾行
            else if((layer+i+j)%2 && (i+j)>=(layer-1) && (i==(layer-1)))
            {
                cout<<"*";
                //cout<<i+1;
            }
            else {
                 cout<<" ";
            }
        }
        cout<<endl;
    }
}
void outputEmptyNumber(int layer)
{
    for(int i=0;i<layer;i++){
        for(int j=0;j<=i+layer-1;j++){
            //非末尾行
            if(((i+j)==(layer-1) || j==(i+layer-1)) && i!=(layer-1)){
                cout<<i+1;
            }
            //末尾行
            else if((layer+i+j)%2 && (i+j)>=(layer-1) && (i==(layer-1)))
            {
                cout<<i+1;
            }
            else {
                 cout<<" ";
            }
        }
        cout<<endl;
    }
}
int main()
{
    int layer=0;
    cout<<"Please input layer:"<<endl;
    cin>>layer;
    outputStar(layer);
    outputEmptyStar(layer);
    outputEmptyNumber(layer);
    return 0;
}

