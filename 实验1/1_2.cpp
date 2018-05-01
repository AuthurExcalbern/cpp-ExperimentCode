#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::string;

int main(void)
{
    //请求输入姓名
    cout << "Please enter your first name: ";
    string name;
    cin >> name;
    
    //问候字符串和空白行字符串
    const string greeting = "Hello, " + name + "!";
    
    //请求围住问候语的空白个数
    int pad_left, pad_right, pad_up, pad_down;
    cout << "Please enter pad_left, pad_right, pad_up, pad_down:";
    cin >> pad_left >> pad_right >> pad_up >> pad_down;
    
    //计算空白个数
    const string starLine(greeting.size() + pad_left + pad_right + 2, '*');
    const string spaceLine(greeting.size() + pad_left + pad_right, ' ');
    
    //输出的行数和列数
    const int rows = pad_up + pad_down + 3;
    const string::size_type cols = greeting.size() + pad_left + pad_right + 2;
    
    cout << std::endl;
    
    //输出
    //循环不变式：目前我们已经输出了r行
    for(int r = 0; r < rows; r++)
    {
        string::size_type c = 0;
        //循环不变式：目前我们已经在当前行中输出了c个字符
        while(c < cols)
        {
            //输出问候语
            if(r == pad_up+1 && c == pad_left+1)
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
            else if(r == pad_up+1 && (c < pad_left+1 || c > greeting.size() + pad_left))
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
        cout << std::endl;
    }
    return 0;
}