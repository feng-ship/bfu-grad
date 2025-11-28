#include<stdio.h>
enum Gender{F,M};
enum Degree{本科生,硕士研究生,博士研究生};
enum Career{直接工作,公务员,国内读硕,出国读硕,国内读博,国外读博,二战,二学位,未就业,其他};
enum Choice{
    import=1,
    view,
    search,
    add,
    delete,
    modify,
    count,
    exit=0
};
enum CountChoice{
    count_year=1,
    count_degree,
    count_major,
    count_directions,
    count_job_major,
    count_return=0
};
struct BirthDate{
    int year;
    int month;
    int day;
};
struct Student{
    char id[20];
    char name[50];
    enum Gender gender;
    struct BirthDate bd;
    int enroll_year;
    int graduation_year;
    enum Degree degree;
    char major[20];
    enum Career career;
    char employer[100];
    char job_major[50];
};
void menu_main(){
    printf("==========信息学院(人工智能学院)毕业生就业去向管理系统==========\n");
    printf("%d.批量导入就业数据\n",import);
    printf("%d.浏览就业数据\n",view);
    printf("%d.查询就业数据\n",search);
    printf("%d.增录就业数据\n",add);
    printf("%d.删除就业数据\n",delete);
    printf("%d.修改就业数据\n",modify); 
    printf("%d.统计就业数据\n",count);
    printf("%d.退出\n",exit);
}
void menu_count(){
    printf("==========信息学院(人工智能学院)毕业生就业去向管理系统-统计功能==========\n");
    printf("%d.统计某一年份就业率\n",count_year);
    printf("%d.统计某一年份不同学历就业率\n",count_degree);
    printf("%d.统计某一年份不同专业就业率\n",count_major);
    printf("%d.统计某一年份不同就业方向人数和比例\n",count_directions);
    printf("%d.统计某一年份从事不同专业的人数和比例\n",count_job_major);
    printf("%d.返回上级菜单\n",count_return);
}
void import_data(struct Student arr[]){
    

}
int main(){
    menu_main();
    struct Student stu[100];

}