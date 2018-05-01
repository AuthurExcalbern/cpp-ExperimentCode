#include<iostream>
#include<iomanip>
using std::cin;
using std::cout;

int main(void)
{
    cout << "Please input I:";
    
    double I;
    cin >> I;
    
    int cnt, temp = I*I;
    for(cnt = 0; temp != 0; cnt++)
        temp /= 10;
    for(double i = 1; i <= I; i++)
        cout << std::left << std::setw(cnt+5)<< i << std::setw(cnt+5) << i*i << std::endl;
    
    return 0;
}