#include<iostream>
#include<iomanip>
#include<ios>

#include<fstream>

#include<vector>
#include<string>
#include<algorithm>

#include<cstring>
#include<cstdlib>
#include<cstddef>

class Student_info
{
public:
    Student_info(): mid(0), fi(0) {}
    Student_info(std::istream& in) { read(in); }
    
    //查询学生姓名
    std::string name() const { return stu_name; }
    
    //读取数据进行初始化
    std::istream& read(std::istream&);
    
    //得到字符成绩
    std::string grade() const;

private:
    std::string stu_name;
    double mid, fi;
};

//读取学生信息
std::istream& Student_info::read(std::istream& in)
{
    in >> stu_name >> mid >> fi;
    
    return in;
}

//得到数字成绩
double grade(double mid, double fi)
{
    return mid * 0.5 + fi * 0.5;
}

//得到字符成绩
std::string Student_info::grade() const
{
    static const double numbers = 60;
    
    double stu_grade = ::grade(mid, fi);
    
    if(stu_grade >= numbers)
        return "P";
    else
        return "F";
}

//使学生按姓名排序
bool comp(const Student_info a, const Student_info b)
{
    return a.name() < b.name();
}

int main(void)
{
    using namespace std;
    
    ofstream report1, report2;
    
    report1.open("report1");
    report2.open("report2");
    
    vector<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;
    
    vector<Student_info> pass_stu, fail_stu;
    
    //读取数据
    while(record.read(cin))
    {
        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }
    
    //按姓名排序
    sort(students.begin(), students.end(), comp);
    
    //输出我们report1
    for(vector<Student_info>::size_type i = 0; i != students.size(); i++)
    {
        report1 << students[i].name() << string((maxlen-students[i].name().size())/3 * 2 + 1, ' ');
        
        string final_grade = students[i].grade();
        streamsize prec = cout.precision();
        report1 << setprecision(3) << final_grade << setprecision(prec) << endl;
        
        if(final_grade == "P")
            pass_stu.push_back(students[i]);
        else
            fail_stu.push_back(students[i]);
    }
    
    for(vector<Student_info>::size_type i = 0; i != pass_stu.size(); i++)
    {
        report2 << pass_stu[i].name() << string((maxlen-pass_stu[i].name().size())/3 * 2 + 1, ' ');
        
        string final_grade = pass_stu[i].grade();
        streamsize prec = cout.precision();
        report2 << setprecision(3) << final_grade << setprecision(prec) << endl;
    }
    
    for(vector<Student_info>::size_type i = 0; i != fail_stu.size(); i++)
    {
        report2 << fail_stu[i].name() << string((maxlen-fail_stu[i].name().size())/3 * 2 + 1, ' ');
        
        string final_grade = fail_stu[i].grade();
        streamsize prec = cout.precision();
        report2 << setprecision(3) << final_grade << setprecision(prec) << endl;
    }
    
    return 0;
}