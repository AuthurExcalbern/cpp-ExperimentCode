#include<iostream>
#include<iomanip>
#include<ios>

#include<string>
#include<vector>
#include<list>
#include<algorithm>
#include<iterator>

#include<cstring>
#include<cstdlib>
#include<cstddef>

template <class input>
double median(input begin, input end)
{
    std::vector<double> temp;
    
    while(begin != end)
    {
        temp.push_back(*begin);
        begin++;
    }
    
    std::sort(temp.begin(), temp.end());
    
    std::vector<double>::size_type mid = temp.size() / 2;
    
    return temp.size() % 2 == 0 ? (temp[mid]+temp[mid-1])/2 : temp[mid];
}

int main(void)
{
    int a[] = {0, 2, 1, 4};
    
    std::vector<int> vec(a, a+4);
    std::list<int> lis(a, a+ 4);
    
    std::cout << "测试数组：" << std::endl;
    std::cout << "数组所有元素：";
    for(int i = 0; i < 4; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;
    std::cout << "median   " << median(a, a+4) << std::endl;
    std::cout << "数组所有元素：";
    for(int i = 0; i < 4; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;
    
    std::cout << std::endl;
    
    std::cout << "测试vector：" << std::endl;
    std::cout << "vector所有元素：";
    for(int i = 0; i < 4; i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
    std::cout << "median   " << median(vec.begin(), vec.end()) << std::endl;
    std::cout << "vector所有元素：";
    for(int i = 0; i < 4; i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
    
    std::cout << std::endl;
    
    std::cout << "测试list：" << std::endl;
    std::cout << "list所有元素：";
    std::list<int>::iterator j = lis.begin();
    for(int i = 0; i < 4; i++)
    {
        std::cout << *j << " ";
        j++;
    }
    std::cout << std::endl;
    std::cout << "median   " << median(lis.begin(), lis.end()) << std::endl;
    std::cout << "list所有元素：";
    j = lis.begin();
    for(int i = 0; i < 4; i++)
    {
        std::cout << *j << " ";
        j++;
    }
    std::cout << std::endl;
    
    return 0;
}