#include<iostream>
#include<string>
#include<algorithm>
#include<cstring>
using std::cin;
using std::cout;
using std::string;

int main(void)
{
    string str, temp;
    string ans1, ans2;
    while(cin >> str)
    {
        ans1 += str + ' ';

        temp = str;
        transform(temp.begin(), temp.end(), temp.begin(), tolower);
        if(temp.compare("bullshit") == 0)
        {
            str.assign("bush");
            ans2 += str + ' ';
            continue;
        }
        
        for(int i = 0; i < str.size(); i++)
        {
            if(islower(str[i])) str[i] = toupper(str[i]);
            else str[i] = tolower(str[i]);
        }
        ans2 += str + ' ';
    }
    cout << ans1 << std::endl;
    cout << ans2 << std::endl;
    return 0;
}