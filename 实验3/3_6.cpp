#include<iostream>
#include<string>
#include<vector>
#include<numeric>

int main(void)
{
    std::vector<std::string> vec;
    std::string a = "HAHAHA  ";
    std::string b = "I AM ";
    std::string c = "king !!!";
    std::string ans;
    
    vec.push_back(a);
    vec.push_back(b);
    vec.push_back(c);
    
    ans = accumulate(vec.begin(), vec.end(), ans);
    
    std::cout << ans << std::endl;
    
    return 0;
}