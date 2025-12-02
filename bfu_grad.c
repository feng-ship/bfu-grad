#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 100
enum Gender{F,M};
enum Degree{本科生=1,硕士研究生=2,博士研究生=3};
enum Career{直接工作=1,公务员=2,国内读硕,出国读硕,国内读博,国外读博,二战,二学位,未就业,其他};
enum Choice{
    import=1,
    view,
    search,
    add,
    delete,
    modify,
    count,
    quit=0
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
    printf("%d.退出\n",quit);
    printf("请选择功能编号:\n");
}
void menu_count(){
    printf("==========信息学院(人工智能学院)毕业生就业去向管理系统-统计功能==========\n");
    printf("%d.统计某一年份就业率\n",count_year);
    printf("%d.统计某一年份不同学历就业率\n",count_degree);
    printf("%d.统计某一年份不同专业就业率\n",count_major);
    printf("%d.统计某一年份不同就业方向人数和比例\n",count_directions);
    printf("%d.统计某一年份从事不同专业的人数和比例\n",count_job_major);
    printf("%d.返回上级菜单\n",count_return);
    printf("请选择功能编号:\n");
}
enum Gender str_to_enum_gender(const char* arr){
    if(strcmp(arr,"女")==0){
        return F;
    }
    else if(strcmp(arr,"男")==0){
        return M;
    }
    else{
        return (enum Gender)-1;
    }
}
enum Degree str_to_enum_degree(const char* arr){
    if(strcmp(arr,"本科生")==0){
        return 本科生;
    }
    else if(strcmp(arr,"硕士研究生")==0){
        return 硕士研究生;
    }
    else if(strcmp(arr,"博士研究生")==0){
        return 博士研究生;
    }
    else{
        return (enum Degree)-1;
    }
}
enum Career str_to_enum_career(const char* arr){
    if(strcmp(arr,"直接工作")==0){
        return 直接工作;
    }
    else if(strcmp(arr,"公务员")==0){
        return 公务员;
    }
    else if(strcmp(arr,"国内读硕")==0){
        return 国内读硕;
    }
    else if(strcmp(arr,"出国读硕")==0){
        return 出国读硕;
    }
    else if(strcmp(arr,"国内读博")==0){
        return 国内读博;
    }
    else if(strcmp(arr,"国外读博")==0){
        return 国外读博;
    }
    else if(strcmp(arr,"二战")==0){
        return 二战;
    }
    else if(strcmp(arr,"二学位")==0){
        return 二学位;
    }
    else if(strcmp(arr,"未就业")==0){
        return 未就业;
    }
    else if(strcmp(arr,"其他")==0){
        return 其他;
    }
    else{
        return (enum Career)-1;
    }
}
int check_dulicate(struct Student arr[],int count,const char* id_to_check){
    for(int i=0;i<count;i++){
        if(strcmp(arr[i].id,id_to_check)==0){
            return 1;
        }
    }
    return 0;
}
void import_data(struct Student arr[],int *count){
    printf("==========批量导入毕业生就业信息==========\n");
    FILE *in,*out;
    char line[256];
    char temp_id[20];
    char temp_gender[10];
    char temp_degree[20];
    char temp_career[20];
    if((in=fopen("students.txt","r"))==NULL){
        printf("【警告】无法打开文件!\n");
        exit(0);
    }
    int success_count=0;
    while(fgets(line,sizeof(line),in)){
        int scanned_items=sscanf(line,"%19[^,],%49[^,],%9[^,],%d/%d/%d,%d,%d,%19[^,],%19[^,],%19[^,],%99[^,],%49[^\n]",
            temp_id,
            arr[*count].name,
            temp_gender,
            &arr[*count].bd.year,&arr[*count].bd.month,&arr[*count].bd.day,
            &arr[*count].enroll_year,
            &arr[*count].graduation_year,
            temp_degree,
            arr[*count].major,
            temp_career,
            arr[*count].employer,
            arr[*count].job_major
        );
        if(scanned_items!=13){
            printf("【警告】数据格式错误，跳过该条记录: %s",line);
            continue;
        }
        if(check_dulicate(arr,*count,temp_id)){
            printf("【警告】毕业生学号%s已存在,跳过此毕业生!",temp_id);
            continue;
        }
        strcpy(arr[*count].id,temp_id);
        if(str_to_enum_gender(temp_gender)!=-1&&str_to_enum_degree(temp_degree)!=-1&&str_to_enum_career(temp_career)!=-1){
            arr[*count].gender=str_to_enum_gender(temp_gender);
            arr[*count].degree=str_to_enum_degree(temp_degree);
            arr[*count].career=str_to_enum_career(temp_career); 
        }
        else{
            printf("【警告】数据内容错误，跳过该条记录: %s",line);
            continue;
        }
        *count+=1;
        success_count++;
    }
    if(*count>=MAXN){
        printf("【警告】已达到最大容量,停止导入!\n");
    }
    fclose(in);   
    if(*count>0){
        if((out=fopen("students.dat","wb"))==NULL){
        printf("【警告】无法打开文件!\n");
        exit(0);
        }
        size_t write_count=fwrite(arr,sizeof(struct Student),*count,out);
        if(write_count==(size_t)*count){
            printf("【成功】完整导入%d条数据,生成数据文件students.dat!\n",success_count);
            return;
        }else{
            printf("【警告】导入数据文件时出错!\n");
            return;
        }
        fclose(out);
    }else{
        printf("【警告】没有有效数据导入,不生成数据文件!\n");
        return;
    }
}
int main(){
    struct Student stu[MAXN];
    int current_count=0;
    menu_main();
    int number1=0;
    scanf("%d",&number1);
    switch(number1){
        case import:
        import_data(stu,&current_count);
        break;
    }

}