#include<iostream>
#include<vector>
#include<string>
#include<iterator>
#include<algorithm>
#include<list>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::iterator;
using std::list;

template <class input_iter>
input_iter mysearch(input_iter str_begin, input_iter str_end, input_iter search_str_begin, input_iter search_str_end);

template <class input_iter, class find_judge>
input_iter myfind_if(input_iter begin, input_iter end, find_judge judge);

template <class input_iter, class out_iter, class find_judge>
out_iter mycopy_if(input_iter begin, input_iter end, out_iter out, find_judge judge);

template <class input_iter, class find_judge>
input_iter myremove_if(input_iter begin, input_iter end, find_judge judge);

template <class input_iter, class out_iter, class operator_iter>
out_iter mytransform(input_iter in_begin, input_iter in_end, out_iter out, operator_iter op);

template <class input_iter, class pred_iter>
input_iter mypartition(input_iter begin, input_iter end, pred_iter pred);

int main(void)
{
    vector<int> vec_temp1, vec_temp2;
    list<int> list_temp1, list_temp2;
    
    for(int i = 0; i < 10; i++)
    {
        vec_temp1.push_back(i);
        list_temp1.push_back(i);
    }
    
    for(int i = 3; i < 8; i++)
    {
        vec_temp2.push_back(i);
        list_temp2.push_back(i);
    }
    
    cout << "测试 search :" << endl;
    mysearch(vec_temp1.begin(), vec_temp1.end(), vec_temp2.begin(), vec_temp2.end());
    mysearch(list_temp1.begin(), list_temp1.end(), list_temp2.begin(), list_temp2.end());
    cout << endl;
    
    cout << "测试 find_if :" << endl;
    myfind_if(vec_temp1.begin(), vec_temp1.end(), [](int i){ return i == 5; });
    myfind_if(list_temp1.begin(), list_temp1.end(), [](int i){ return i == 5; });
    cout << endl;
    
    vector<int> vec_temp;
    list<int> list_temp;
    
    cout << "测试 copy_if :" << endl;
    mycopy_if(vec_temp1.begin(), vec_temp1.end(), back_inserter(vec_temp), [](int i){ return i  > 1 && i < 8; });
    mycopy_if(list_temp1.begin(), list_temp1.end(), back_inserter(list_temp), [](int i){ return i  > 1 && i < 8; });
    cout << endl;
    
    cout << "测试 remove_if :" << endl;
    myremove_if(vec_temp1.begin(), vec_temp1.end(), [](int i){ return i == 5; });
    myremove_if(list_temp1.begin(), list_temp1.end(), [](int i){ return i == 5; });
    cout << endl;
    
    cout << "测试 transform :" << endl;
    mytransform(vec_temp1.begin(), vec_temp1.end(), back_inserter(vec_temp), [](int i){ return i + 1; });
    mytransform(list_temp1.begin(), list_temp1.end(), back_inserter(list_temp), [](int i){ return i + 1; });
    cout << endl;
    
    cout << "测试 partition :" << endl;
    mypartition(vec_temp1.begin(), vec_temp1.end(), [](int i){ return i  > 1 && i < 8; });
    mypartition(list_temp1.begin(), list_temp1.end(), [](int i){ return i  > 1 && i < 8; });
    cout << endl;
    
    return 0;
}
    

template <class input_iter>
input_iter mysearch(input_iter str_begin, input_iter str_end, input_iter search_str_begin, input_iter search_str_end)
{
    for(input_iter i = str_begin; i != str_end; i++)
    {
        input_iter temp = i;
        input_iter j;
        
        for(j = search_str_begin; j != search_str_end; j++)
        {
            if(temp != str_end && temp == j)
                temp++;
            else
                break;
        }
        
        if(j == search_str_end)
            return i;
        else
            continue;
    }
    
    return str_end;
}

template <class input_iter, class find_judge>
input_iter myfind_if(input_iter begin, input_iter end, find_judge judge)
{
    for(input_iter i = begin; i != end; i++)
    {
        if(judge(*i))
            return i;
    }
    
    return end;
}

template <class input_iter, class out_iter, class find_judge>
out_iter mycopy_if(input_iter begin, input_iter end, out_iter out, find_judge judge)
{
    for(input_iter i = begin; i != end; i++)
    {
        if(judge(*i))
        {
            *out = *i;
            out++;
        }
    }
    
    return out;
}

template <class input_iter, class find_judge>
input_iter myremove_if(input_iter begin, input_iter end, find_judge judge)
{
    input_iter result = begin;
    
    for(input_iter i = begin; i != end; i++)
    {
        if(!judge(*i))
        {
            *result = *i;
            result++;
        }
    }
    
    return result;
}

template <class input_iter, class out_iter, class operator_iter>
out_iter mytransform(input_iter in_begin, input_iter in_end, out_iter out, operator_iter op)
{
    for(input_iter i = in_begin; i != in_end; i++)
    {
        (*out) = op(*i);
        ++out;
    }
    
    return out;
}

template <class input_iter, class pred_iter>
input_iter mypartition(input_iter begin, input_iter end, pred_iter pred)
{
    while(begin != end)
    {
        while(pred(*begin))
        {
            begin++;
            if(begin == end)
                return begin;
        }
        
        do
        {
            end--;
            if(begin == end)
                return begin;
        } while(!pred(*end));
        
        std::swap(*begin, *end);
        begin++;
    }
    
    return begin;
}