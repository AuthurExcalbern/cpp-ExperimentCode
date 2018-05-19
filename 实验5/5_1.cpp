#include<iostream>
#include<iomanip>
#include<ios>

#include<string>
#include<vector>
#include<algorithm>

#include<cstring>
#include<cstdlib>
#include<cstddef>

//声明学生类
class Student_info
{
//共有成员
public:
    //两种初始化方式
    Student_info(): mid(0), fi(0) {}
    Student_info(std::istream& in) { read(in); }
    
    //查询学生姓名
    std::string name() const { return stu_name; }
    
    //检查是否已经初始化
    bool valid() const { return !homework.empty(); }
    
    //读取数据进行初始化
    std::istream& read(std::istream&);
    
    //得到字符成绩
    std::string grade() const;

//私有成员
private:
    std::string stu_name;
    double mid, fi;
    std::vector<double> homework;
};

//读取学生信息
std::istream& Student_info::read(std::istream& in)
{
    in >> stu_name >> mid >> fi;
    //read_hw(in, homework);
    if(in)
    {
        homework.clear();
        
        double x;
        while(in >> x)
            homework.push_back(x);
        
        in.clear();
    }
    /*
    for(int i = 0; i < homework.size(); i++)
        std::cout << homework[i] << std::endl;
    */
    return in;
}

//得到数字成绩
double grade(double mid, double fi, double hw)
{
    return 0.2*mid + 0.4*fi + 0.4*hw;
}

//得到平时成绩的中位数
double median(std::vector<double> vec)
{
    typedef std::vector<double>::size_type vec_sz;
    
    vec_sz size = vec.size();
    std::sort(vec.begin(), vec.end());
    
    vec_sz mid = size / 2;
    
    return size % 2 == 0 ? (vec[mid]+vec[mid-1])/2 : vec[mid];
}

//得到数字成绩
double grade(double mid, double fi, std::vector<double> hw)
{
    if(hw.size() == 0)
    {
        std::cout<< "平时成绩为空！\n";
        exit(1);
    }
    
    return grade(mid, fi, median(hw));
}

//得到字符成绩
std::string Student_info::grade() const
{
    static const double numbers[] = {
        97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
    };
    
    static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);
    
    static const char* const letters[] = {
        "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"
    };
    
    double stu_grade = ::grade(mid, fi, homework);
    
    for(size_t i = 0; i < ngrades; i++)
        if(stu_grade >= numbers[i])
            return letters[i];
    
    return "??";
}

//使学生按姓名排序
bool comp(const Student_info a, const Student_info b)
{
    return a.name() > b.name();
}

int main(void)
{
    using namespace std;
    
    vector<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;
    
    //读取数据
    while(record.read(cin))
    {
        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }
    
    //按姓名排序
    sort(students.begin(), students.end(), comp);
    
    //输出我们得到是字符成绩
    for(vector<Student_info>::size_type i = 0; i != students.size(); i++)
    {
        cout << students[i].name() << string(maxlen+1-students[i].name().size(), ' ');
        
        string final_grade = students[i].grade();
        streamsize prec = cout.precision();
        cout << setprecision(3) << final_grade << setprecision(prec) << endl;
    }
    
    return 0;
}


