#include<iostream>
#include<string>
#include<algorithm>
#include<cctype>

class String_list
{
public:
    String_list(std::string in_str)
    {
        split(in_str);
    }
    
    std::string iter();
    std::string riter();
    void free();
private:
    struct point
    {
        std::string val;
        struct point *next;
        struct point *previous;
    
        point(std::string str): val(str), next(nullptr), previous(nullptr) {}
    };
    
    struct point first_point = point("***");
    
    void split(const std::string& str);
};

bool space(char c)
{
    return isspace(c);
}

bool not_sapce(char c)
{
    return !isspace(c);
}

//分割储存字符串
void String_list::split(const std::string& str)
{
    typedef std::string::const_iterator str_iter;
    
    str_iter i = str.begin();
    while(i != str.end())
    {
        i = std::find_if(i, str.end(), not_sapce);
        str_iter j = std::find_if(i, str.end(), space);
        
        if(i != str.end())
        {
            struct point *newpoint = new point(std::string(i, j));
            
            if(first_point.previous != nullptr)
            {
                newpoint->next = &first_point;
                newpoint->previous = first_point.previous;
                
                first_point.previous->next = newpoint;
                first_point.previous = newpoint;
            }
            else
            {
                first_point.next = newpoint;
                first_point.previous = newpoint;
                
                newpoint->next = &first_point;
                newpoint->previous = &first_point;
            }
        }
        
        i = j;
    }
}

//正向迭代器
std::string String_list::iter()
{
    std::string ret;
    
    struct point *temp = first_point.next;
    
    while(temp != &first_point)
    {
        ret += (*temp).val + ' ';
        temp = (*temp).next;
    }
    
    return ret;
}

//反向迭代器
std::string String_list::riter()
{
    std::string ret;
    
    struct point *temp = first_point.previous;
    
    while(temp != &first_point)
    {
        ret += (*temp).val + ' ';
        temp = (*temp).previous;
    }
    
    return ret;
}

//释放内存，防止内存泄漏
void String_list::free()
{
    struct point *cnt = first_point.next;
    struct point *temp;
    
    if(cnt == nullptr)
        return;
    
    while(cnt->next != &first_point)
    {
        temp = cnt;
        cnt = cnt->next;
        
        delete temp;
    }
    
    first_point.next = first_point.previous = nullptr;
    
    return;
}

int main(void)
{
    //读入字符串
    std::string in_str;
    getline(std::cin, in_str);
    
    //分割储存在链表里
    String_list list_str(in_str);
    
    //正向和反向迭代器输出
    std::cout << list_str.iter() << std::endl;
    std::cout << list_str.riter() << std::endl;
    
    //释放内存，防止内存泄漏
    list_str.free();
    
    return 0;
}