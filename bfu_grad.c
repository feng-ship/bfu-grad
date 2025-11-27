#include<stdio.h>
struct BirthDate{
    int year;
    int month;
    int day;
};
struct stu{
    char id[20];
    char name[50];
    char gender;
    struct BirthDate bd;
    int enroll_year;
    int graduation_year;
    char major[20];
    char employer[100];
    char job_major[50];


};
void menu(){
    printf("==========信息学院(人工智能学院)毕业生就业去向管理系统==========\n");
    

}