#include<iostream>
#include<vector>
#include<string>
using std::cin;
using std::cout;
using std::string;

struct data_struct
{
    string str;
    int cnt;
    
    data_struct(string data)
    {
        str = data;
        cnt = 1;
    }
};

std::istream& get_data(std::istream& in, std::vector<data_struct>& s)
{
    string data;
    
    if(in)
    {
        while(in >> data)
        {
            bool j = true;
        
            std::vector<data_struct>::iterator it;
            for(it = s.begin(); it != s.end(); it++)
            {
                if(data == it->str)
                {
                    it->cnt++;
                    j = false;
                    break;
                }
            }
            
            if(j)
            {
                data_struct n(data);
                
                s.push_back(n);
            }
        }
        in.clear();
    }
    
    return in;
}

int main(void)
{
    std::vector<data_struct> s;
    
    get_data(cin, s);
    
    cout << "Number: " << s.size() << std::endl;
    cout << "The times:" << std::endl;
    
    std::vector<data_struct>::iterator i;
    for(i = s.begin(); i != s.end(); i++)
        cout << "Word: " << i->str << " Times: " << i->cnt << std::endl;
    
    return 0;
}