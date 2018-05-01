#include<iostream>
#include<vector>
#include<string>
#include<cctype>
using std::cin;
using std::cout;
using std::vector;
using std::string;

bool is_up_line(string s)
{
    for(string::size_type i = 0; i < s.size(); i++)
    {
        if(s[i] == 'b' || s[i] == 'd' || s[i] == 'f' || s[i] == 'h' || s[i] == 'j' || s[i] == 'k' || s[i] == 'l')
            return true;
    }
    return false;
}

bool is_down_line(string s)
{
    for(string::size_type i = 0; i < s.size(); i++)
    {
        if(s[i] == 'g' || s[i] == 'j' || s[i] == 'p' || s[i] == 'q' || s[i] == 'y')
            return true;
    }
    return false;
}

int main(int argc, char* argv[])
{
    vector<string> str, str_up, str_down, str_maxlen;
    string str_temp;
    
    while(cin >> str_temp)
        str.push_back(str_temp);
    
    for(vector<string>::size_type i = 0; i < str.size(); i++)
    {
        if(is_up_line(str[i]))
            str_up.push_back(str[i]);
        if(is_down_line(str[i]))
            str_down.push_back(str[i]);
        
        if(!is_up_line(str[i]) && !is_down_line(str[i]))
            str_maxlen.push_back(str[i]);
    }
    
    cout << "含有上行字母的单词是：";
    for(vector<string>::size_type i = 0; i < str_up.size(); i++)
        cout << " " << str_up[i];
    cout << std::endl;
    
    cout << "含有下行字母的单词是：";
    for(vector<string>::size_type i = 0; i < str_down.size(); i++)
        cout << " " << str_down[i];
    cout << std::endl;
    
    string str_max;
    for(vector<string>::size_type i = 0; i < str_maxlen.size(); i++)
    {
        if(str_max.size() <= str_maxlen[i].size())
            str_max = str_maxlen[i];
    }
    cout << "既不包含上行字母也不包含下行字母的最长单词是：" << str_max << std::endl;
    
    return 0;
}