#include<iostream>
#include<vector>
#include<string>
#include<ios>
#include<iomanip>
#include<stdexcept>
#include<algorithm>
using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::sort;

//学生信息结构体
struct Student_info
{
    string name;
    double finalGrade;
};

//sort的第三个参数，按名字排序
bool compare(const Student_info& x, const Student_info& y)
{
    return x.name < y.name;
}

//求得平时成绩的中位数
double median(vector<double> vec)
{
    typedef vector<double>::size_type vec_sz;

    vec_sz size = vec.size();
    if(size == 0) throw std::domain_error("median of an empty vector");
    sort(vec.begin(), vec.end());
    vec_sz mid = size / 2;

    return size % 2 == 0 ? (vec[mid] + vec[mid-1]) / 2 : vec[mid];
}

//求得最终成绩
double grade(double mid, double fin, double hw)
{
    return 0.2*mid + 0.4*fin + 0.2*hw;
}

//读入平时成绩
std::istream& read_hw(std::istream& in, vector<double>& homework)
{
    string hw;
    getline(in, hw);
    
    double temp = 0;
    for(int i = 0; i < hw.size(); i++)
    {
        if(hw[i] > '9' || hw[i] < '0')
        {
            //为方便而跳过，但如果存在成绩是0的情况就会出错
            if(temp==0) continue;
            
            homework.push_back(temp);
            temp = 0;
            continue;
        }
        else
        {
            temp = temp * 10 + (hw[i] - '0');
        }
    }
    //要压入最后一个数
    homework.push_back(temp);
    
    /*
    for(int i = 0; i < homework.size(); i++)
        cout << homework[i] << " ";
    cout<<std::endl;
    */
    
    return in;
}

//读入学生信息
std::istream& read(std::istream& in, Student_info& s)
{
    in >> s.name;

    double Midterm, Final;
    vector<double> hw;

    in >> Midterm >> Final;
    read_hw(in, hw);
    double Homework = median(hw);

    s.finalGrade = grade(Midterm, Final, Homework);

    return in;
}

int main(int argc, char* argv[])
{
    vector<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;

    while(read(cin, record))
    {
        maxlen = std::max(maxlen, record.name.size());
	students.push_back(record);
    }

    std::sort(students.begin(), students.end(), compare);

    for(vector<Student_info>::size_type i = 0; i != students.size(); i++)
    {
        cout << students[i].name << string(maxlen+1-students[i].name.size(),' ');
        
        try{
            std::streamsize prec = cout.precision();
            cout << std::setprecision(3) << students[i].finalGrade << std::setprecision(prec);
        } catch(std::domain_error e) {
            cout << e.what();
        }
        cout << std::endl;
    }
    return 0;
}
