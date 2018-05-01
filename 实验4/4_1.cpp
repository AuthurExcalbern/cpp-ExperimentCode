#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<iterator>
#include<algorithm>
#include<cctype>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::map;

bool space(char c);

bool not_sapce(char c);

vector<string> split(const string& str);

map<string, vector<int> > xref(std::istream& in, vector<string> find_words(const string&) = split);



int main(void)
{
    map<string, vector<int> > ret = xref(cin);
    
    for(map<string, vector<int> >::const_iterator i = ret.begin(); i != ret.end(); i++)
    {
        cout << i->first << " occurs on line(s): ";
        
        vector<int>::const_iterator line_i = i->second.begin();
        cout << *line_i;
        
        ++line_i;
        while(line_i != i->second.end())
        {
            cout << "," << *line_i;
            ++line_i;
        }
        
        cout << endl;
    }
    
    return 0;
}

bool space(char c)
{
    return isspace(c);
}

bool not_sapce(char c)
{
    return !isspace(c);
}

vector<string> split(const string& str)
{
    typedef string::const_iterator iter;
    
    vector<string> ret;
    iter i = str.begin();
    while(i != str.end())
    {
        i = std::find_if(i, str.end(), not_sapce);
        iter j = std::find_if(i, str.end(), space);
        
        if(i != str.end())
            ret.push_back(string(i, j));
        
        i = j;
    }
    
    return ret;
}

map<string, vector<int> >
xref(std::istream& in, vector<string> find_words(const string&) )
{
    string line;
    int line_num = 0;
    
    map<string, vector<int> > ret;
    
    while(getline(in, line))
    {
        ++line_num;
        
        vector<string> words = find_words(line);
        
        for(vector<string>::const_iterator i = words.begin(); i != words.end(); i++)
        {
            if(ret[*i].empty())
            {
                ret[*i].push_back(line_num);
                continue;
            }
            
            if(ret[*i].back() == line_num)
                continue;
            else
                ret[*i].push_back(line_num);
        }
    }
    
    return ret;
}