#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<cctype>
using std::string;

int main(int argc, char* argv[])
{
    std::stack<string> Stack_little, Stack_first_big, Stack_big;
    string word;
    
    //读取单词
    while(std::cin >> word)
    {
        string::size_type len = word.size();
        
        if(len == 0) break;
        
        if(len == 1)
        {
            if(isupper(word[0]))
                Stack_big.push(word);
            else
                Stack_little.push(word);
        }
        else
        {
            if(isupper(word[0]))
            {
                if(isupper(word[1]))
                    Stack_big.push(word);
                else
                    Stack_first_big.push(word);
            }
            else
                Stack_little.push(word);
        }
    }
    
    std::cout << "小寫單詞：";
    while(!Stack_little.empty())
    {
        std::cout << Stack_little.top() << ' ';
        Stack_little.pop();
    }
    std::cout << std::endl;
    
    std::cout << "首字母大寫單詞：";
    while(!Stack_first_big.empty())
    {
        std::cout << Stack_first_big.top() << ' ';
        Stack_first_big.pop();
    }
    std::cout << std::endl;
    
    std::cout << "大寫單詞：";
    while(!Stack_big.empty())
    {
        std::cout << Stack_big.top() << ' ';
        Stack_big.pop();
    }
    std::cout << std::endl;
    
    return 0;
}