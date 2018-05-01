#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
#include<iterator>
#include<algorithm>
#include<ctime>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::list;
using std::iterator;

//储存学生姓名和成绩
struct Student_info
{
    string name;
    int grade;
};

//读取学生成绩
std::istream& read_stu_grade(std::istream& in, struct Student_info& stu);

bool fgrade(Student_info stu);

//5.1.1
vector<Student_info> first_extract_fails(vector<Student_info>& stu);

//5.5
list<Student_info> second_extract_fails(list<Student_info>& stu);

//5-6
vector<Student_info> thrid_extract_fails(vector<Student_info>& stu);

int main(int argc, char* argv[])
{
    std::ifstream stu_file;
    struct Student_info stu;
    vector<Student_info> vector_all_stu;
    list<Student_info> list_all_stu;
    
    stu_file.open(argv[1]);
    while(read_stu_grade(stu_file, stu))
    {
        vector_all_stu.push_back(stu);
        list_all_stu.push_back(stu);
    }
    
    clock_t start, finish;
    double duration;
    start = clock();
    
    //vector<Student_info> fail = first_extract_fails(vector_all_stu);
    //list<Student_info> fail = second_extract_fails(list_all_stu);
    vector<Student_info> fail = thrid_extract_fails(vector_all_stu);
    
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << duration << endl;
    
    return 0;
}


//读取学生成绩
std::istream& read_stu_grade(std::istream& in, struct Student_info& stu)
{
    in >> stu.name;
    
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
    
    stu.grade = grade_temp[3];
    //cout<< stu.name<<" "<<stu.grade<<endl;
    
    return in;
}

bool fgrade(Student_info stu)
{
    if(stu.grade >= 60)
        return false;
    else
        return true;
}

//5.1.1
vector<Student_info> first_extract_fails(vector<Student_info>& stu)
{
    vector<Student_info> fail;
    vector<Student_info>::size_type i = 0;
    
    while(i != stu.size())
    {
        if(fgrade(stu[i]))
        {
            fail.push_back(stu[i]);
            stu.erase(stu.begin() + i);
        }
        else
            i++;
    }
    
    return fail;
}

//5.5
list<Student_info> second_extract_fails(list<Student_info>& stu)
{
    list<Student_info> fail;
    list<Student_info>::iterator iter = stu.begin();
    
    while(iter != stu.end())
    {
        if(fgrade(*iter))
        {
            fail.push_back(*iter);
            iter = stu.erase(iter);
        }
        else
            iter++;
    }
    
    return fail;
}

//5-6
vector<Student_info> thrid_extract_fails(vector<Student_info>& stu)
{
    vector<Student_info> fail;
    vector<Student_info>::size_type i = stu.size()-1, cnt = stu.size();
    
    while(cnt != 0)
    {
        if(fgrade(stu[i]))
        {
            fail.push_back(stu[i]);
            i--;
        }
        else
            stu.insert(stu.begin(), 1, stu[i]);
        stu.resize(i+1);    
        cnt--;
    }
    
    return fail;
}