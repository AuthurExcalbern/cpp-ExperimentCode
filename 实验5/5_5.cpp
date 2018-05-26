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
long long int cnt = 0;
class Student_info
{
public:
    Student_info(): mid(0), fi(0) {cnt++;}
    Student_info(std::istream& in) { cnt++;read(in); }
    
    ~Student_info() { cnt++; }
    
    Student_info& operator=(const Student_info& rhs)
    {
        cnt++;
        /*
        if(&rhs != this)
        {
            this
        */
        return *this;
    }
    
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

bool fgrade(const Student_info& s) { return s.grade() == "F"; }

bool pgrade(const Student_info& s) { return !fgrade(s); }

std::vector<Student_info>
extract_fails_I(std::vector<Student_info>& students)
{
    using namespace std;
    
    vector<Student_info> fail;
    
    remove_copy_if(students.begin(), students.end(),  back_inserter(fail), pgrade);
    
    students.erase(remove_if(students.begin(), students.end(), fgrade), students.end());
    
    return fail;
}

std::vector<Student_info>
extract_fails_II(std::vector<Student_info>& students)
{
    using namespace std;
    
    vector<Student_info>::iterator iter = stable_partition(students.begin(), students.end(), pgrade);
    
    vector<Student_info> fail(iter, students.end());
    
    students.erase(iter, students.end());
    
    return fail;
}

int main(void)
{
    using namespace std;
    
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
    
    vector<Student_info> temp = students;
    
    cnt = 0;
    
    fail_stu = extract_fails_I(temp);
    pass_stu = temp;
    
    cout << cnt << endl;
    
    cnt = 0;
    
    fail_stu = extract_fails_II(students);
    pass_stu = students;
    
    cout << cnt << endl;
    
    return 0;
}