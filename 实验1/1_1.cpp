#include<iostream>
#include<string>
using namespace std;
int main(void)
{
    //请求输入姓名
    cout << "Please enter your first name: ";
    string name;
    cin >> name;
    
    //问候字符串和空白行字符串
    const string greeting = "Hello, " + name + "!";
    
    //围住问候语的空白个数
    const int pad = 1;
    const string starLine(greeting.size() + pad*2 + 2, '*');
    const string spaceLine(greeting.size() + pad*2, ' ');
    
    //输出的行数和列数
    const int rows = pad*2 + 3;
    const string::size_type cols = greeting.size() + pad*2 + 2;
    
    cout << endl;
    
    //输出
    //循环不变式：目前我们已经输出了r行
    for(int r = 0; r < rows; r++)
    {
        string::size_type c = 0;
        //循环不变式：目前我们已经在当前行中输出了c个字符
        while(c < cols)
        {
            //输出问候语
            if(r == pad+1 && c == pad+1)
            {
                cout << greeting;
                c += greeting.size();
            }
            //输出*行,即为第一行和最后一行
            else if(r == 0 || r == rows-1)
            {
                cout << starLine;
                break;
            }
            //输出空白行左右的*
            else if(c == 0 || c == cols-1)
            {
                cout << '*';
                c++;
            }
            //输出问候语两边的空格
            else if(r == pad+1 && (c < pad+1 || c > greeting.size() + pad))
            {
                cout << ' ';
                c++;
            }
            else//输出空白行
            {
                cout << spaceLine;
                c += spaceLine.size();
            }
        }
        cout << endl;
    }
    return 0;
}