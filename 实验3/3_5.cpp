#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iterator>
#include<algorithm>
#include<ctime>
#include<numeric>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::iterator;

const int HOMEWORK_NUM = 5;

//储存学生姓名和成绩
struct Student_info
{
    string name;
    string sex;
    vector<int> homework;
};

//读取学生成绩
std::istream& read_stu_grade(std::istream& in, struct Student_info& stu);

bool fgrade(Student_info stu);

vector<Student_info> extract_not_did_all(vector<Student_info>& stu);

bool did_all_hw(const Student_info& s);

void write_analysis(std::ostream& out, const string& name, double analysis(const vector<Student_info>&), const vector<Student_info>& did, const vector<Student_info>& didnt );

double median_analysis(const vector<Student_info>& students);

double grade_mid(const Student_info& s);

double stu_average_analysis(const vector<Student_info>& students);

double stu_average(const vector<double>& v);

double optimistic_median_analysis(const vector<Student_info>& students);

double median(const vector<double>& grades);

int main(int argc, char* argv[])
{
    std::ifstream stu_file;
    struct Student_info stu;
    vector<Student_info> girl_stu, boy_stu;
    
    
    stu_file.open(argv[1]);
    while(read_stu_grade(stu_file, stu))
    {
        if(stu.sex == "男") boy_stu.push_back(stu);
        else girl_stu.push_back(stu);
    }
    
    vector<Student_info> boy_notall = extract_not_did_all(boy_stu);
    vector<Student_info> girl_notall = extract_not_did_all(girl_stu);
    
    write_analysis(cout, "boy_median_analysis: ", median_analysis, boy_stu, boy_notall);
    write_analysis(cout, "girl_median_analysis: ", median_analysis, girl_stu, girl_notall);
    
    write_analysis(cout, "boy_stu_average_analysis: ", stu_average_analysis, boy_stu, boy_notall);
    write_analysis(cout, "girl_stu_average_analysis: ", stu_average_analysis, girl_stu, girl_notall);
    
    write_analysis(cout, "boy_optimistic_median_analysis: ", optimistic_median_analysis, boy_stu, boy_notall);
    write_analysis(cout, "girl_optimistic_median_analysis: ", optimistic_median_analysis, girl_stu, girl_notall);
    
    return 0;
}


//读取学生成绩,对于分数为0的成绩不读入
std::istream& read_stu_grade(std::istream& in, struct Student_info& stu)
{
    in >> stu.name >> stu.sex;
    
    if(!in.good()) return in;
    
    vector<int> grade_temp;
    
    string grade;
    getline(in, grade);
    
    int temp = 0;
    for(int i = 0; i < grade.size(); i++)
    {
        if(grade[i] > '9' || grade[i] < '0')
        {
            //为方便而跳过，但如果存在成绩是0的情况就会出错
            if(temp==0) continue;
            
            grade_temp.push_back(temp);
            temp = 0;
            continue;
        }
        else
        {
            temp = temp * 10 + (grade[i] - '0');
        }
    }
    //要压入最后一个数
    grade_temp.push_back(temp);
    
    std::sort(grade_temp.begin(), grade_temp.end());
    
    stu.homework = grade_temp;
    //cout<< stu.name<<" "<<stu.grade<<endl;
    
    return in;
}

vector<Student_info> extract_not_did_all(vector<Student_info>& stu)
{
    vector<Student_info> fail;
    vector<Student_info>::iterator iter = stu.begin();
    
    while(iter != stu.end())
    {
        if(did_all_hw(*iter))
        {
            fail.push_back(*iter);
            iter = stu.erase(iter);
        }
        else
            iter++;
    }
    
    return fail;
}

bool did_all_hw(const Student_info& s)
{
    return s.homework.size() == HOMEWORK_NUM;
}

void write_analysis(std::ostream& out, const string& name, double analysis(const vector<Student_info>&), const vector<Student_info>& did, const vector<Student_info>& didnt )
{
    out << name << ": did = " << analysis(did) << ", didnt = " << analysis(didnt) << endl;
}

double median_analysis(const vector<Student_info>& students)
{
    vector<double> grades;
    std::transform(students.begin(), students.end(), back_inserter(grades), grade_mid);
    return median(grades);
}

double grade_mid(const Student_info& s)
{
    return s.homework[0];
}

double stu_average_analysis(const vector<Student_info>& students)
{
    vector<double> grades;
    
    std::transform(students.begin(), students.end(), back_inserter(grades), stu_average);
    
    return median(grades);
}

double stu_average(const Student_info& v)
{
    return accumulate(v.homework.begin(), v.homework.end(), 0.0) / v.homework.size();
}

double optimistic_median_analysis(const Student_info& students)
{
    vector<double> grades;
    
    //std::transform(students.begin(), students.end(),back_inserter(grades), optimistic_median);
    
    return 0;//stu_average_analysis(students);//median(grades);
}

double median(const vector<double>& grades)
{
    int mid = grades.size() / 2;
    return grades.size() % 2 == 0 ? (grades[mid]+grades[mid-1])/2 : grades[mid];
}