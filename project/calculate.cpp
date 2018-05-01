#include<algorithm>
#include<iomanip>
#include<ios>
#include<iostream>
#include<stdexcept>
#include<string>
#include<vector>
const int MAXN = 1024;

using std::cin;
using std::cout;
using std::setprecision;
using std::domain_error;
using std::endl;
using std::max;
using std::string;
using std::vector;
using std::istream;

//存储学生信息
struct stuInfo
{
    string name;//姓名
    vector<double> homework;//平时成绩+期中成绩+期末成绩
    double result;//总成绩
    
    /*//按结构体的总成绩从大到小进行排序
    bool operator<(const stuInfo & rhs)const
    {
        return result < rhs.result;
    }*/
};

//用于sort的第三个参数
bool compare(const stuInfo& a, const stuInfo& b)
{
    return a.result < b.result;
}

//得到期末成绩
double getFinal(vector<double>& homework)
{
    double Final = homework.back();
    homework.pop_back();
    
    return Final;
}

//得到期中成绩
double getMiddle(vector<double>& homework)
{
    double Middle = homework.back();
    homework.pop_back();
    
    return Middle;
}

//得到平时成绩
double getPeacetime(vector<double>& homework)
{
    std::sort(homework.begin(), homework.end());
    
    vector<double>::size_type mid = homework.size() / 2;
    
    return homework.size() % 2 == 0 ? (homework[mid] + homework[mid-1]) / 2 : homework[mid];
}

//得到总成绩
double getResult(stuInfo& s)
{
    double Final = getFinal(s.homework);
    double Middle = getMiddle(s.homework);
    double Peace = getPeacetime(s.homework);
    
    return Peace*0.4 + Middle*0.2 + Final*0.4;
}

//输出数据并保存
istream& readStu(istream& in, stuInfo& s)
{
    in >> s.name;
    
    //如果流出错则返回，例如遇到了EOF
    if(!in.good()) return in;
    
    //要先清理容器
    s.homework.clear();
    
    string hw;
    getline(in, hw);
    
    double temp = 0;
    for(int i = 0; i < hw.size(); i++)
    {
        if(hw[i] > '9' || hw[i] < '0')
        {
            //为方便而跳过，但如果存在成绩是0的情况就会出错
            if(temp==0) continue;
            
            s.homework.push_back(temp);
            temp = 0;
            continue;
        }
        else
        {
            temp = temp * 10 + (hw[i] - '0');
        }
    }
    //要压入最后一个数
    s.homework.push_back(temp);
    
    /*
    cout << s.name<<" ";
    for(int i = 0; i < s.homework.size(); i++)
        cout << s.homework[i] << " ";
    */
    
    s.result = getResult(s);
    
    //cout << s.result << endl;
    
    return in;
}

//得到平均分
double getAve(const vector<stuInfo>& s)
{
    double ans = 0;
    for(vector<stuInfo>::const_iterator i = s.begin(); i != s.end(); i++)
        ans += i->result;
    
    return ans / s.size();
}

//得到中位数
double getMid(const vector<stuInfo>& s)
{
    vector<stuInfo>::size_type mid = s.size() / 2;
    return  s.size() % 2 == 0 ? (s[mid].result + s[mid-1].result) / 2 : s[mid].result;
}

int main(int atgc, char * argv[])
{
    vector<stuInfo> stu;
    stuInfo record;
    
    int cnt = 0;
    while(readStu(cin, record))
    {
        stu.push_back(record);
        
    }
    cin.clear();
    
    std::sort(stu.begin(), stu.end(), compare);
    
    cout << "总成绩前五名：" << endl;
    for(vector<stuInfo>::size_type i = stu.size()-1; i > stu.size()-6; i--)
        cout << stu[i].name << " ";
    cout << endl;
    
    cout << "总成绩后五名：" << endl;
    for(vector<stuInfo>::size_type i = 0; i < 5; i++)
        cout << stu[i].name << " ";
    cout << endl;
    
    std::streamsize prec = cout.precision();
    cout << "总成绩的平均分：" << setprecision(3) << getAve(stu) << setprecision(prec) << endl;
    cout << "总成绩的中位数：" << setprecision(3) << getMid(stu) << setprecision(prec) << endl;
    
    return 0;
}