#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define MAXN 1024//最多只能有1024个学生

//存储学生信息
struct stu_data
{
    char name[10];//姓名
    int homework[100];//平时成绩+期中成绩+期末成绩
    double result;//总成绩
}stu[MAXN];

/* 此函数用于输出储存在结构体里的信息
 * 确保读取的数据无误
void put_data(int x)
{
    int i;
    printf("%s ", stu[x].name);
    for(i = 0; stu[x].homework[i+1] != 0; i++)
        printf("%d ", stu[x].homework[i]);
    printf("%d\n", stu[x].homework[i]);
}*/

//qsort：按结构体的总成绩从大到小进行排序
int cmp(const void * a, const void * b)
{
    struct stu_data *p1 = (struct stu_data *)a;
    struct stu_data *p2 = (struct stu_data *)b;
    
    return p2->result - p1->result;
}

int cmp_hw(const void * a, const void * b)
{
    return *(int *)a - *(int *)b;
}

//用于得到总成绩
void process_data(int num)
{
    int middle, final;
    double peacetime;
    int i, j;
    
    for(i = 0; i <= num; i++)
    {
        peacetime = middle = final = 0;
        
        for(j = 0; stu[i].homework[j+2] != 0; j++);
        middle = stu[i].homework[j];
        final = stu[i].homework[j+1];
        
        qsort(stu[i].homework, j, sizeof(stu[i].homework[0]), cmp_hw);
        if((j-1) % 2 == 0)
            peacetime = stu[i].homework[(j-1) / 2];
        else
            peacetime = (stu[i].homework[(j-1) / 2] + stu[i].homework[((j-1) / 2) + 1]) / 2;
        
        stu[i].result = peacetime*0.4 + middle*0.2 + final*0.4;
        
        printf("%s %lf\n", stu[i].name, stu[i].result);
    }
}

//得到平均成绩
double get_ave(int num)
{
    double ans, sum;
    int i;
    
    for(i = 0; i <= num; i++)
        sum = sum + stu[i].result;
    
    ans = sum / (num+1);
    
    return ans;
}

//得到中位数
double get_mid(int num)
{
    num++;
    if(num % 2 == 0)
        return (stu[num/2].result + stu[num/2+1].result) / 2;
    else
        return stu[num/2].result;
}

int main(void)
{
    freopen("0_0_in.txt", "r", stdin);
    freopen("0_0_out.txt", "w", stdout);
    
    char str[MAXN];
    int cnt_stu = -1, cnt_hw = 0;
    int i;
    double average, middle;
    
    //读取文件数据并保存在结构体
    while(scanf("%s", str) != EOF)
    {
        if(!isdigit(str[0]))
        {
            //if(cnt_stu >= 0) put_data(cnt_stu);
            cnt_stu++;
            cnt_hw = 0;
            strcpy(stu[cnt_stu].name, str);
        }
        else
        {
            stu[cnt_stu].homework[cnt_hw] = atoi(str);
            cnt_hw++;
        }
    }
    //put_data(cnt_stu);
    
    process_data(cnt_stu);
    qsort(stu, cnt_stu+1, sizeof(stu[0]), cmp);
    
    printf("总成绩前五名的同学姓名：\n");
    for(i = 0; i < 4; i++)
        printf("%s ", stu[i].name);
    printf("%s\n", stu[i].name);
    
    printf("总成绩后五名的同学姓名：\n");
    for(i = cnt_stu; i > cnt_stu-4; i--)
        printf("%s ", stu[i].name);
    printf("%s\n", stu[i].name);
    
    average = get_ave(cnt_stu);
    middle = get_mid(cnt_stu);
    
    printf("总成绩的平均分是：%lf\n", average);
    printf("总成绩的中位数是：%lf\n", middle);
    
    return 0;
}