#include<iostream>
#include<list>
#include<map>
#include<string>
#include<iterator>
#include<cstdlib>
#include<cctype>
#include<algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::list;

typedef list<string> Rule;
typedef list<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammar;

bool space(char c);
bool not_sapce(char c);
list<string> split(const string& str);

//从一个特定的输入流读入一个文法
Grammar read_grammar(std::istream& in);

//生成语句
list<string> gen_sentence(const Grammar& g);

//判断是否为语法
bool bracketed(const string& s);

//返回 [0, n) 中的一个随机整数
int nrand(int n);

//得到语句
void 
gen_aux(const Grammar& g, const string& word, list<string>& ret);

int main(void)
{
    //生成语句
    list<string> sentence = gen_sentence(read_grammar(cin));
    
    //输出第一个单词（如果存在
    list<string>::const_iterator iter = sentence.begin();
    if(!sentence.empty())
    {
        cout << *iter;
        ++iter;
    }
    
    //输出其余单词，每一个单词前都有一个空格
    while(iter != sentence.end())
    {
        cout << " " << *iter;
        ++iter;
    }
    
    cout << endl;
    
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

list<string> split(const string& str)
{
    typedef string::const_iterator iter;

    list<string> ret;
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

//从一个特定的输入流读入一个文法
Grammar read_grammar(std::istream& in)
{
    Grammar ret;
    string line;
    
    //读输入
    while(getline(in, line))
    {
        //将输入分割成单词
        list<string> entry = split(line);
        
        if(!entry.empty())
            ret[entry.front()].push_back(Rule(++entry.begin(), entry.end()));
    }
    
    return ret;
}

//生成语句
list<string> gen_sentence(const Grammar& g)
{
    list<string> ret;
    gen_aux(g, "<sentence>", ret);
    return ret;
}

//判断是否为语法
bool bracketed(const string& s)
{
    return s.size() > 1 && s[0] == '<' && s[s.size()-1] == '>';
}

//返回 [0, n) 中的一个随机整数
int nrand(int n)
{
    if(n <= 0 || n > RAND_MAX)
        cout << "超过随机范围。" << endl;//throw domain_error("");
    
    
    const int bucket_size = RAND_MAX / n;
    
    int r;
    do r = rand() / bucket_size;
    while(r >= n);
    
    return r;
}

//得到语句
void 
gen_aux(const Grammar& g, const string& word, list<string>& ret)
{
    if(!bracketed(word))
        ret.push_back(word);
    else
    {
        //为对应于word的规则定位
        Grammar::const_iterator iter = g.find(word);
        if(iter == g.end())
            cout << "empty rule." << endl;//throw logic_error();
        
        //获取可能的规则集合
        const Rule_collection& c = iter->second;
        
        //从规则集合中随机选择一条规则
        //const Rule& r = c[nrand(c.size())];
        int n = nrand(c.size());
        Rule_collection::const_iterator c_iter = c.begin();
        while(n--) c_iter++;
        const Rule& r = *c_iter;
        
        
        for(Rule::const_iterator i = r.begin(); i != r.end(); i++)
            gen_aux(g, *i, ret);
    }
}