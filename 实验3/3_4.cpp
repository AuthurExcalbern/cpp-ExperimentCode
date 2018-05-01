#include<iostream>
#include<string>
#include<vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

void print_vector(vector<int> x)
{
    for(vector<int>::size_type i = 0; i < x.size(); i++)
        cout << " " << x[i];
}

int main(int argc, char* argv[])
{
    //书中的方法
    vector<int> u(0, 100);
    vector<int> v;
    std::copy(u.begin(), u.end(), v.begin());
    
    /*第一个改进的方法
    vector<int> u(0, 100);
    vector<int> v(u);
    */
    /*第二个改进的方法
    vector<int> u(0, 100);
    vector<int> v;
    v.assign(u.begin(), u.end());
    */
    /*第三个改进的方法
    vector<int> u(0, 100);
    vector<int> v;
    v.swap(u);
    */
    cout << "vector u 中的内容：" << endl;
    print_vector(u);
    
    cout << "vector v 中的内容：" << endl;
    print_vector(v);
    
    return 0;
}