#include<iostream>
#include<string>
using std::cin;
using std::cout;

int main(void)
{
    std::string s;
    std::string::size_type the_min, the_max;
    bool first = true;
    
    while(cin >> s)
    {
        std::string::size_type len = s.size();
        
        if(first)
        {
            the_max = the_min = len;
            first = false;
        }
        
        if(len > the_max) the_max = len;
        if(len < the_min) the_min = len;
    }
    
    cout << "The max len: " << the_max << std::endl;
    cout << "The min len: " << the_min << std::endl;
    
    return 0;
}