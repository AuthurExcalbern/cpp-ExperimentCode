#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::string;

int main(void)
{
    //围住的空白个数
    const int pad_UpDown = 1;
    const int pad_LeftRight = 2;
    const string starLine(31 + pad_LeftRight*2 + 2, '*');
    const string spaceLine(31 + pad_LeftRight*2, ' ');
    
    //输出的行数和列数
    const int rows = pad_UpDown*2 + 2 + 5;
    const string::size_type cols = 31 + pad_LeftRight*2 + 2;
    
    //输出
    //循环不变式：目前我们已经输出了r行
    for(int r = 0; r < rows; r++)
    {
        string::size_type c = 0;
        //循环不变式：目前我们已经在当前行中输出了c个字符
        while(c < cols)
        {
            //输出*行,即为第一行和最后一行
            if(r == 0 || r == rows-1)
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
            //输出空白行
            else if(r <= pad_UpDown || r >= rows-1-pad_UpDown)
            {
                cout << spaceLine;
                c += spaceLine.size();
            }
            //输出两边的空格
            else if((r >= pad_UpDown+1 && r <= pad_UpDown+1+4) && (c < pad_LeftRight+1 || c > 31 + pad_LeftRight))
            {
                cout << ' ';
                c++;
            }
            else if(r == pad_UpDown+1 && c == pad_LeftRight+1)
            {
                cout << "*******    *    ******* *******";
                c += 31;
            }
            else if(r == pad_UpDown+2 && c == pad_LeftRight+1)
            {
                cout << "*  *  * *******    *       *   ";
                c += 31;
            }
            else if(r == pad_UpDown+3 && c == pad_LeftRight+1)
            {
                cout << "******* *  *  *    ***     *   ";
                c += 31;
            }
            else if(r == pad_UpDown+4 && c == pad_LeftRight+1)
            {
                cout << "*  *  * *******  * *       * * ";
                c += 31;
            }
            else if(r == pad_UpDown+5 && c == pad_LeftRight+1)
            {
                cout << "*******    *    *******    *   ";
                c += 31;
            }
        }
        cout << std::endl;
    }
    return 0;
}