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
enum SearchChoice{
    search_id=1,
    search_name
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
void view_data(struct Student arr[],int count){
    printf("==========浏览毕业生就业信息==========\n");
    if(count==0){
        printf("【提示】当前无数据可浏览,请先导入或添加数据!\n");
        return;
    }
    for(int i=0;i<count;i++){
        printf("%-12s %-8s %-4s %-12s %-8s %-8s %-6s %-12s %-12s %-20s %-12s\n",
       "学号", "姓名", "性别", "出生日期",
       "入学年", "毕业年", "学历", "专业",
       "就业去向", "单位名称", "从事专业");
        printf("%-12s %-8s %-4s %04d/%02d/%02d %-8d %-8d %-6s %-12s %-12s %-20s %-12s\n ",
            arr[i].id,
            arr[i].name,
            arr[i].gender==F?"女":"男",
            arr[i].bd.year,arr[i].bd.month,arr[i].bd.day,
            arr[i].enroll_year,
            arr[i].graduation_year,
            arr[i].degree==本科生?"本科生":arr[i].degree==硕士研究生?"硕士研究生":"博士研究生",
            arr[i].major,
            arr[i].career==直接工作?"直接工作":arr[i].career==公务员?"公务员":arr[i].career==国内读硕?"国内读硕":arr[i].career==出国读硕?"出国读硕":arr[i].career==国内读博?"国内读博":arr[i].career==国外读博?"国外读博":arr[i].career==二战?"二战":arr[i].career==二学位?"二学位":arr[i].career==未就业?"未就业":"其他",
            arr[i].employer,
            arr[i].job_major
        );
    }
}
struct Student* search_by_id(struct Student arr[],int count,const char* id_to_search){
    for(int i=0;i<count;i++){
        if(strcmp(arr[i].id,id_to_search)==0){
            return &arr[i];
        }
    }
    return NULL;
}
struct Student* search_by_name(struct Student arr[],int count,const char* name_to_search){
    for(int i=0;i<count;i++){
        if(strcmp(arr[i].id,name_to_search)==0){
            return &arr[i];
        }
    }
    return NULL;
}
void search_data(struct Student arr[],int count){
    printf("==========查询毕业生就业信息==========\n");
    printf("%d.按学号查询\n",search_id);
    printf("%d.按姓名查询\n",search_name);
    printf("请选择查询方式:\n");
    int search_choice=0;
    scanf("%d",&search_choice);
    switch(search_choice){
        case search_id:{
            char id_to_search[20];
            printf("请输入要查询的学号:\n");
            scanf("%s",id_to_search);
            struct Student* result=search_by_id(arr,count,id_to_search);
            if(result!=NULL){
                printf("【成功】找到该毕业生信息:\n");
                printf("%-12s %-8s %-4s %-12s %-8s %-8s %-6s %-12s %-12s %-20s %-12s\n",
               "学号", "姓名", "性别", "出生日期",
               "入学年份", "毕业年份", "学历", "专业",
               "就业去向", "单位名称", "从事专业");
                printf("%-12s %-8s %-4s %04d/%02d/%02d %-8d %-8d %-6s %-12s %-12s %-20s %-12s\n ",
                    result->id,
                    result->name,result->gender==F?"女":"男",
                    result->bd.year,result->bd.month,result->bd.day,
                    result->enroll_year,
                    result->graduation_year,
                    result->degree==本科生?"本科生":result->degree==硕士研究生?"硕士研究生":"博士研究生",
                    result->major,
                    result->career==直接工作?"直接工作":result->career==公务员?"公务员":result->career==国内读硕?"国内读硕":result->career==出国读硕?"出国读硕":result->career==国内读博?"国内读博":result->career==国外读博?"国外读博":result->career==二战?"二战":result->career==二学位?"二学位":result->career==未就业?"未就业":"其他",
                    result->employer,
                    result->job_major
                );
            }else{
                printf("【失败】未找到该学号对应的毕业生信息!\n");
            }
            break;
        }
        case search_name:{
            char name_to_search[50];
            printf("请输入要查询的姓名:\n");
            scanf("%s",name_to_search);
            struct Student* result2=search_by_name(arr,count,name_to_search);
            if(result2!=NULL){
                printf("【成功】找到该毕业生信息:\n");
                printf("%-12s %-8s %-4s %-12s %-8s %-8s %-6s %-12s %-12s %-20s %-12s\n",
               "学号", "姓名", "性别", "出生日期",
               "入学年份", "毕业年份", "学历", "专业",
               "就业去向", "单位名称", "从事专业");
                printf("%-12s %-8s %-4s %04d/%02d/%02d %-8d %-8d %-6s %-12s %-12s %-20s %-12s\n ",
                    result2->id,
                    result2->name,result2->gender==F?"女":"男",
                    result2->bd.year,result2->bd.month,result2->bd.day,
                    result2->enroll_year,
                    result2->graduation_year,
                    result2->degree==本科生?"本科生":result2->degree==硕士研究生?"硕士研究生":"博士研究生",
                    result2->major,
                    result2->career==直接工作?"直接工作":result2->career==公务员?"公务员":result2->career==国内读硕?"国内读硕":result2->career==出国读硕?"出国读硕":result2->career==国内读博?"国内读博":result2->career==国外读博?"国外读博":result2->career==二战?"二战":result2->career==二学位?"二学位":result2->career==未就业?"未就业":"其他",
                    result2->employer,
                    result2->job_major
                );
            }else{
                printf("【失败】未找到该学号对应的毕业生信息!\n");
            }
            break;
        }
        default:
            printf("【警告】无效的查询选项!\n");
            break;
    }
}
void add_data(struct Student arr[],int *count){
    if(*count>=MAXN){
        printf("【警告】已达到最大容量,停止导入!\n");
    }
    printf("==========增录毕业生就业信息==========\n");
    printf("请按照输入示例的格式输入一条毕业生信息:\n");
    printf("输入示例：251002125,张小寒,女,2006/12/10,2025,2029,本科生,计算机科学与技术,国内读博,北京大学,软件工程\n");
    struct Student new_student;
    char line[512];
    char temp_id[20];
    char temp_gender[10];
    char temp_degree[20];
    char temp_career[20];
    if(fgets(line,sizeof(line),stdin)!=NULL){
        int n=sscanf("%19[^,],%49[^,],%9[^,],%d/%d/%d,%d,%d,%19[^,],%19[^,],%19[^,],%99[^,],%49[^\n]",
        new_student.id,
        new_student.name,
        temp_gender,
        &new_student.bd.year,&new_student.bd.month,&new_student.bd.day,
        &new_student.enroll_year,
        &new_student.graduation_year,
        temp_degree,
        new_student.major,
        temp_career,
        new_student.employer,
        new_student.job_major);
        if(n!=13){
            printf("【警告】数据格式错误，跳过该条记录: %s",line);
            return;
        }
        if(check_dulicate(arr,*count,temp_id)){
            printf("【警告】学号%s已存在，请重新输入",temp_id);
            return;
        }
        strcpy(arr[*count].id,temp_id);
        if(str_to_enum_gender(temp_gender)!=-1&&str_to_enum_degree(temp_degree)!=-1&&str_to_enum_career(temp_career)!=-1){
            arr[*count].gender=str_to_enum_gender(temp_gender);
            arr[*count].degree=str_to_enum_degree(temp_degree);
            arr[*count].career=str_to_enum_career(temp_career); 
        }
        else{
            printf("【警告】数据内容错误，跳过该条记录: %s",line);
            return;
        }
        *count+=1;
        FILE *out;
        if(*count>0){
        if((out=fopen("students.dat","wb"))==NULL){
            printf("【警告】无法打开文件!\n");
            exit(0);
        }
        size_t write_count=fwrite(&new_student,sizeof(struct Student),1,out);
        if(write_count==1){
            printf("【成功】完整导入一条数据,生成数据文件students.dat!\n");
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
    }else{
        printf("【警告】输入错误，操作取消!\n");
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
        case view:
        view_data(stu,current_count);
        break;
        case search:
        search_data(stu,current_count);
        break;
        case add:
        add_data(stu,&current_count);
        break;
    }
    return 0;

}