#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<iterator>
#include<algorithm>
#include<cctype>
#include<regex>
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

vector<string> find_urls(const string& str);


int main(void)
{
    map<string, vector<int> > ret = xref(cin);
    map<string, vector<int> > ans;
    
    for(map<string, vector<int> >::const_iterator i = ret.begin(); i != ret.end(); i++)
    {
        vector<string> urls = find_urls(i->first);
        
        for(vector<string>::const_iterator j = urls.begin(); j != urls.end(); j++)
        {
            //cout << *j << endl;
            ans[*j] = i->second;
        }
        /*
        
        */
    }
    
    for(map<string, vector<int> >::const_iterator i = ret.begin(); i != ret.end(); i++)
    {
        cout << "[" << i->first << "]" << " occurs on line(s): ";
        
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

vector<string> find_urls(const string& str)
{
    vector<string> ret;
    
    static const string pattern = R"((https?|ftp|file)://[-A-Za-z0-9+&@#/%?=~_|!:,.;] + [-A-Za-z0-9+&@#/%=~_|])";
    
    std::regex URL_RegEx(pattern, std::regex::icase);
    
    auto url_begin = std::sregex_iterator(str.begin(), str.end(), URL_RegEx);
    auto url_end = std::sregex_iterator();
    
    std::transform(url_begin, url_end, back_inserter(ret), [](std::smatch m){return m.str(); });
    
    return ret;
}

/*
vector<string> find_urls(const string& s)
{
    vector<string> ret;  using CnstIter = string::const_iterator;
    CnstIter b = s.begin(), e = s.end();
    while (b != e) {
        // look for one or more letters followed by `://'
        b = url_beg(b, e);
        // if we found it
        if (b != e) {
            // get the rest of the URL
            CnstIter after = url_end(b, e);
            // remember the URL
            ret.push_back(string(b, after));
            // advance `b' and check for more URLs on this line
            b = after;
        }
    }
    return ret;
}

string::const_iterator
url_end(string::const_iterator b, string::const_iterator e)
{
	return std::find_if(b, e, not_url_char);
}

bool not_url_char(char c)
{
    // characters, in addition to alphanumerics, that can appear in a URL
    static const string url_ch = "~;/?:@=&$-_.+!*'(),";
    
    // see whether `c‘ can appear in a URL and return the negative
    return !(isalnum(c) || std::find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}
*/