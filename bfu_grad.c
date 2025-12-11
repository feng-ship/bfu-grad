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
    char id[32];
    char name[64];
    enum Gender gender;
    struct BirthDate bd;
    int enroll_year;
    int graduation_year;
    enum Degree degree;
    char major[128];
    enum Career career;
    char employer[128];
    char job_major[128];
};
struct Major{
    char major[128];
    int total;
    int employed;
};
struct Job{
    char job_major[128];
    int total;
};
void load_data(struct Student arr[],int *count){
    FILE *in;
    if((in=fopen("students.dat","rb"))==NULL){
        printf("【警告】无法打开文件!\n");
        return;
    }
    size_t read_count=fread(arr,sizeof(struct Student),MAXN,in);
    *count=read_count;
    fclose(in);
}
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
int str_to_enum_gender(const char* arr,enum Gender *gender){
    if(strcmp(arr,"女")==0){
        *gender=F;
        return 1;
    }
    else if(strcmp(arr,"男")==0){
        *gender=M;
        return 1;
    }
    return 0;
}
int str_to_enum_degree(const char* arr,enum Degree *degree){
    if(strcmp(arr,"本科生")==0){
        *degree=本科生;
        return 1;
    }
    else if(strcmp(arr,"硕士研究生")==0){
        *degree=硕士研究生;
        return 1;
    }
    else if(strcmp(arr,"博士研究生")==0){
        *degree=博士研究生;
        return 1;
    }
    return 0;
}
int str_to_enum_career(const char* arr,enum Career *career){
    if(strcmp(arr,"直接工作")==0){
        *career=直接工作;
        return 1;
    }
    else if(strcmp(arr,"公务员")==0){
        *career=公务员;
        return 1;
    }
    else if(strcmp(arr,"国内读硕")==0){
        *career=国内读硕;
        return 1;
    }
    else if(strcmp(arr,"出国读硕")==0){
        *career=出国读硕;
        return 1;
    }
    else if(strcmp(arr,"国内读博")==0){
        *career=国内读博;
        return 1;
    }
    else if(strcmp(arr,"国外读博")==0){
        *career=国外读博;
        return 1;
    }
    else if(strcmp(arr,"二战")==0){
        *career=二战;
        return 1;
    }
    else if(strcmp(arr,"二学位")==0){
        *career=二学位;
        return 1;
    }
    else if(strcmp(arr,"未就业")==0){
        *career=未就业;
        return 1;
    }
    else if(strcmp(arr,"其他")==0){
        *career=其他;
        return 1;
    }
    return 0;
}
int check_dulicate_by_id(struct Student arr[],int count,const char* id_to_check){
    for(int i=0;i<count;i++){
        if(strcmp(arr[i].id,id_to_check)==0){
            return 1;
        }
    }
    return 0;
}
void import_data_from_txt(struct Student arr[],int *count){
    struct Student temp[MAXN];
    FILE *in;
    if((in=fopen("students.txt","r"))==NULL){
        printf("【警告】无法打开文件!\n");
        return;
    }
    char line[512];
    char temp_id[32];
    char temp_gender[16];
    char temp_degree[32];
    char temp_career[32];
    while(fgets(line,sizeof(line),in)){
        line[strcspn(line,"\n")]=0;
        if(strlen(line)==0) continue;
        int scanned_items = sscanf(line,"%31[^,],%63[^,],%15[^,],%d/%d/%d,%d,%d,%31[^,],%127[^,],%31[^,],%127[^,],%63[^\n]",
            temp_id,
            temp[*count].name,
            temp_gender,
            &temp[*count].bd.year,&temp[*count].bd.month,&temp[*count].bd.day,
            &temp[*count].enroll_year,
            &temp[*count].graduation_year,
            temp_degree,
            temp[*count].major,
            temp_career,
            temp[*count].employer,
            temp[*count].job_major
        );
        if(scanned_items!=13){
            printf("【警告】数据格式错误，跳过该条记录: %s\n",line);
            continue;
        }
        if(check_dulicate_by_id(arr,*count,temp_id)){
            printf("【警告】毕业生学号%s已存在,跳过此毕业生!\n",temp_id);
            continue;
        }
        if(*count>=MAXN){
            printf("【警告】已达到最大容量,停止导入!\n");
            continue;
        }
        strcpy(arr[*count].id,temp_id);
        strcpy(arr[*count].name,temp[*count].name);
        arr[*count].bd.year=temp[*count].bd.year;
        arr[*count].bd.month=temp[*count].bd.month;
        arr[*count].bd.day=temp[*count].bd.day;
        arr[*count].enroll_year=temp[*count].enroll_year;
        arr[*count].graduation_year=temp[*count].graduation_year;
        strcpy(arr[*count].major,temp[*count].major);
        strcpy(arr[*count].employer,temp[*count].employer);
        strcpy(arr[*count].job_major,temp[*count].job_major);
        if(str_to_enum_gender(temp_gender,&arr[*count].gender)&&str_to_enum_degree(temp_degree,&arr[*count].degree)&&str_to_enum_career(temp_career,&arr[*count].career)){
            *count+=1;
        }
        else{
            printf("【警告】数据内容错误，跳过该条记录: %s",line);
            continue;
        }
    }
    fclose(in);
}
void save_data_to_dat(struct Student arr[],int count){
    FILE *out;
    if(count>0){
        if((out=fopen("students.dat","wb"))==NULL){
            printf("【警告】无法打开文件!\n");
            exit(0);
        }
        size_t write_count=fwrite(arr,sizeof(struct Student),count,out);
        if(write_count==(size_t)count){
            printf("【成功】数据已保存，共%d条数据,生成数据文件students.dat!\n",count);
            return;
        }else{
            printf("【警告】导入数据文件时出错!\n");
            return;
        }
        fclose(out);
    }else{
        printf("【警告】没有有效数据保存,不生成数据文件!\n");
        return;
    }
}
void view_data(struct Student arr[],int count){
    printf("==========浏览毕业生就业信息==========\n");
    if(count==0){
        printf("【提示】当前无数据可浏览,请先导入或添加数据!\n");
        return;
    }
    printf("%-12s %-8s %-4s %-12s %-8s %-8s %-10s %-18s %-18s %-20s %-18s\n",
       "学号","姓名","性别","出生日期","入学年","毕业年",
       "学历","专业","就业去向","单位名称","从事专业");
    for(int i=0;i<count;i++){
        printf("%-12s %-8s %-4s %04d/%02d/%02d %-8d %-8d %-12s %-16s %-16s %-16s %-16s\n",
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
        if(strcmp(arr[i].name,name_to_search)==0){
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
                printf("%-12s %-8s %-4s %-12s %-8s %-8s %-10s %-18s %-18s %-20s %-18s\n",
       "学号","姓名","性别","出生日期","入学年","毕业年",
       "学历","专业","就业去向","单位名称","从事专业");
                printf("%-12s %-8s %-4s %04d/%02d/%02d %-8d %-8d %-12s %-16s %-16s %-16s %-16s\n",
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
                printf("%-12s %-8s %-4s %-12s %-8s %-8s %-10s %-18s %-18s %-20s %-18s\n",
                    "学号","姓名","性别","出生日期","入学年","毕业年",
                    "学历","专业","就业去向","单位名称","从事专业");
                printf("%-12s %-8s %-4s %04d/%02d/%02d %-8d %-8d %-12s %-16s %-16s %-16s %-16s\n",
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
                printf("【失败】未找到该姓名对应的毕业生信息!\n");
            }
            break;
        }
        default:
            printf("【警告】无效的查询选项!\n");
            break;
    }
}
void add_data(struct Student arr[], int *count) {
    if (*count >= MAXN) {
        printf("【警告】已达到最大容量,停止导入!\n");
        return;
    }

    // 清掉 stdin 中残留的换行或多余字符（如果之前用了 scanf）
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}

    printf("==========增录毕业生就业信息==========\n");
    printf("请按照输入示例的格式输入一条毕业生信息:\n");
    printf("输入示例：251002125,张小寒,女,2006/12/10,2025,2029,本科生,计算机科学与技术,国内读博,北京大学,软件工程\n");

    char line[512];
    if (!fgets(line, sizeof(line), stdin)) {
        printf("【警告】没有有效输入，操作取消！\n");
        return;
    }
    // 去掉末尾换行
    size_t L = strlen(line);
    if (L > 0 && line[L-1] == '\n') line[L-1] = '\0';

    // 临时缓冲（大小必须 >= sscanf 中指定的最大长度 +1）
    char temp_id[32];
    char temp_name[64];
    char temp_gender[16];
    int y, m, d;
    int enroll, grad;
    char temp_degree[32];
    char temp_major[128];
    char temp_career[32];
    char temp_employer[128];
    char temp_job_major[64];

    // 注意：这里的数字要与上面缓冲大小匹配（比如 %63 -> temp_name[64]）
    int n = sscanf(line,
        "%31[^,],%63[^,],%15[^,],%d/%d/%d,%d,%d,%31[^,],%127[^,],%31[^,],%127[^,],%63[^\n]",
        temp_id, temp_name, temp_gender,
        &y, &m, &d, &enroll, &grad,
        temp_degree, temp_major, temp_career, temp_employer, temp_job_major
    );

    if (n != 13) {
        printf("【警告】数据格式错误（解析字段 %d/13），跳过该条记录: %s\n", n, line);
        return;
    }

    // 重复学号检查（确保 check_dulicate 的签名为 check_dulicate(arr,count,id)）
    if (check_dulicate_by_id(arr, *count, temp_id)) {
        printf("【警告】学号 %s 已存在，请重新输入\n", temp_id);
        return;
    }

    // 枚举解析（假定这些函数返回 0 表示无效）
    int g = str_to_enum_gender(temp_gender,&arr[*count].gender);
    int deg = str_to_enum_degree(temp_degree,&arr[*count].degree);
    int car = str_to_enum_career(temp_career,&arr[*count].career);
    if (g == 0 || deg == 0 || car == 0) {
        printf("【警告】枚举字段内容错误，跳过该条记录: %s\n", line);
        return;
    }

    // 填充结构体（注意不会越界）
    struct Student new_student;
    memset(&new_student, 0, sizeof(new_student));
    strncpy(new_student.id, temp_id, sizeof(new_student.id)-1);
    strncpy(new_student.name, temp_name, sizeof(new_student.name)-1);
    new_student.gender = g;
    new_student.bd.year = y; new_student.bd.month = m; new_student.bd.day = d;
    new_student.enroll_year = enroll;
    new_student.graduation_year = grad;
    new_student.degree = deg;
    strncpy(new_student.major, temp_major, sizeof(new_student.major)-1);
    new_student.career = car;
    strncpy(new_student.employer, temp_employer, sizeof(new_student.employer)-1);
    strncpy(new_student.job_major, temp_job_major, sizeof(new_student.job_major)-1);

    // 放入内存数组
    arr[*count] = new_student;
    (*count)++;

    // 追加到文件
    FILE *out = fopen("students.dat", "ab");
    if (!out) {
        printf("【警告】无法打开文件 students.dat 以写入！\n");
        return;
    }
    size_t written = fwrite(&new_student, sizeof(struct Student), 1, out);
    fclose(out);

    if (written == 1) {
        printf("【成功】完整导入一条数据，已追加到 students.dat\n");
    } else {
        printf("【警告】写入文件时出错！\n");
    }
}
int check_dulicate_by_name(struct Student arr[],int count,const char*name_to_check){
    int flag=0;
    for(int i=0;i<count;i++){
        if(strcmp(arr[i].name,name_to_check)==0){
            flag++;
        }
    }
    return flag;
}
int delete_data(struct Student arr[], int *count,int delete_choice,const char *delete_key) {
    int idx=-1;
    for(int i=0;i<*count;i++){
        if(delete_choice==1){
            if(strcmp(arr[i].id,delete_key)==0){
                idx=i;
                break;
            }
        }else if(delete_choice==2){
            if(strcmp(arr[i].name,delete_key)==0){
                idx=i;
                break;
            }
        }
    }
    if(idx==-1) return 0;
    else{
        printf("【提示】该毕业生信息:\n");
        printf("%-12s %-8s %-4s %-12s %-8s %-8s %-10s %-18s %-18s %-20s %-18s\n",
       "学号","姓名","性别","出生日期","入学年","毕业年",
       "学历","专业","就业去向","单位名称","从事专业");
        printf("%-12s %-8s %-4s %04d/%02d/%02d %-8d %-8d %-12s %-16s %-16s %-16s %-16s\n",
            arr[idx].id,
            arr[idx].name,arr[idx].gender==F?"女":"男",
            arr[idx].bd.year,arr[idx].bd.month,arr[idx].bd.day,
            arr[idx].enroll_year,
            arr[idx].graduation_year,
            arr[idx].degree==本科生?"本科生":arr[idx].degree==硕士研究生?"硕士研究生":"博士研究生",
            arr[idx].major,
            arr[idx].career==直接工作?"直接工作":arr[idx].career==公务员?"公务员":arr[idx].career==国内读硕?"国内读硕":arr[idx].career==出国读硕?"出国读硕":arr[idx].career==国内读博?"国内读博":arr[idx].career==国外读博?"国外读博":arr[idx].career==二战?"二战":arr[idx].career==二学位?"二学位":arr[idx].career==未就业?"未就业":"其他",
            arr[idx].employer,
            arr[idx].job_major
            );
        printf("【提示】确定要删除该毕业生信息吗？(是/否)\n");
        char confirm[10];
        scanf("%s",confirm);
        while(strcmp(confirm,"是")!=0&&strcmp(confirm,"否")!=0){
            printf("【警告】无效的确认选项!重新输入!\n");
            scanf("%s",confirm);
        }
        if(strcmp(confirm,"否")==0){
            return 0;
        }
        for(int j=idx;j<*count-1;j++){
            arr[j]=arr[j+1];
        }
        (*count)--;
        FILE *out = fopen("students.dat", "wb");
        if(!out){
            printf("【警告】无法打开文件!\n");
            return 0;
        }
        size_t write_count=fwrite(arr,sizeof(struct Student),*count,out);
        fclose(out);
        if(write_count==(size_t)*count) return 1;
        else return 0;
    }
    return 0;
}
void count_menu(){
    printf("==========信息学院(人工智能学院)毕业生就业去向管理系统-统计功能==========\n");
    printf("%d.统计某一年份就业率\n",count_year);
    printf("%d.统计某一年份不同学历就业率\n",count_degree);
    printf("%d.统计某一年份不同毕业专业就业率\n",count_major);
    printf("%d.统计某一年份不同就业方向人数和比例\n",count_directions);
    printf("%d.统计某一年份从事不同专业的人数和比例\n",count_job_major);
    printf("%d.返回上级菜单\n",count_return);
    printf("请选择功能编号:\n");
}
void count_data_by_year(struct Student arr[], int count, int year) {
    int point=0;
    double ans=0;
    for(int i=0;i<count;i++){
        if(arr[i].graduation_year==year&&arr[i].career!=未就业&&arr[i].career!=其他&&arr[i].career!=二战){
            point++;
        }
    }
    ans=(double)point/count*100.0;
    printf("【成功】%d年就业率:%.4f%%\n",year,ans);
}
void count_by_degree(struct Student arr[],int count,int year){
    int point[4]={0};
    double ans[4];
    for(int i=0;i<count;i++){
        if(arr[i].graduation_year==year&&arr[i].career!=未就业&&arr[i].career!=其他&&arr[i].career!=二战){
            if(arr[i].degree==本科生) point[0]++;
            else if(arr[i].degree==硕士研究生) point[1]++;
            else if(arr[i].degree==博士研究生) point[2]++;
        }
    }
    ans[0]=(double)point[0]/count*100.0;
    ans[1]=(double)point[1]/count*100.0;
    ans[2]=(double)point[2]/count*100.0;
    printf("【成功】%d年就业率:\n",year);
    printf("本科:%.4f%%\n",ans[0]);
    printf("硕士:%.4f%%\n",ans[1]);
    printf("博士:%.4f%%\n",ans[2]);
}
int is_employed(enum Career c){
    return !(c==未就业&&c!=其他&&c!=二战);
}
int find_major(const char* major,struct Major m[],int n){
    for(int i=0;i<n;i++){
        if(strcmp(m[i].major,major)==0){
            return i;
        }
    }
    return -1;
}
void count_by_major(struct Student arr[],int count,int year){
    struct Major ma[MAXN];
    int m_count=0;
    for(int i=0;i<count;i++){
        if(arr[i].graduation_year!=year) continue;
        int idx=find_major(arr[i].major,ma,m_count);
        if(idx==-1){
            strcpy(ma[m_count].major,arr[i].major);
            ma[m_count].total=1;
            ma[m_count].employed=is_employed(arr[i].career);
            m_count++;
        }
        ma[idx].total++;
        if(is_employed(arr[i].career)) ma[idx].employed++;
    }
    printf("====== %d 年不同专业就业率 ======\n",year);
    for(int i=0;i<m_count;i++){
        double ans=(double)ma[i].employed*100.0/ma[i].total;
        printf("专业:%-20s  就业率:%.4f%%\n",ma[i].major,ans);
    }
}
void count_by_career(struct Student arr[],int count,int year){
    int point[11]={0};
    double ans[11];
    for(int i=0;i<count;i++){
        if(arr[i].graduation_year==year&&arr[i].career!=未就业&&arr[i].career!=其他&&arr[i].career!=二战){
            if(arr[i].career==直接工作) point[0]++;
            else if(arr[i].career==公务员) point[1]++;
            else if(arr[i].career==国内读硕) point[2]++;
            else if(arr[i].career==出国读硕) point[3]++;
            else if(arr[i].career==国内读博) point[4]++;
            else if(arr[i].career==国外读博) point[5]++;
            else if(arr[i].career==二学位) point[6]++;
            else if(arr[i].career==未就业) point[7]++;
            else if(arr[i].career==其他) point[8]++;
        }
    }
    ans[0]=(double)point[0]/count*100.0;
    ans[1]=(double)point[1]/count*100.0;
    ans[2]=(double)point[2]/count*100.0;
    ans[3]=(double)point[3]/count*100.0;
    ans[4]=(double)point[4]/count*100.0;
    ans[5]=(double)point[5]/count*100.0;
    ans[6]=(double)point[6]/count*100.0;
    ans[7]=(double)point[7]/count*100.0;
    ans[8]=(double)point[8]/count*100.0;
    printf("【成功】%d年不同就业方向人数和比例:\n",year);
    printf("直接工作:人数:%d 比例:%.4f%%\n",point[0],ans[0]);
    printf("公务员:人数:%d 比例:%.4f%%\n",point[1],ans[1]);
    printf("国内读硕:人数:%d 比例:%.4f%%\n",point[2],ans[2]);
    printf("出国读硕:人数:%d 比例:%.4f%%\n",point[3],ans[3]);
    printf("国内读博:人数:%d 比例:%.4f%%\n",point[4],ans[4]);
    printf("国外读博:人数:%d 比例:%.4f%%\n",point[5],ans[5]);
    printf("二战:人数:%d 比例:%.4f%%\n",point[5],ans[5]);
    printf("二学位:人数:%d 比例:%.4f%%\n",point[6],ans[6]);
    printf("未就业:人数:%d 比例:%.4f%%\n",point[7],ans[7]);
    printf("其他:人数:%d 比例:%.4f%%\n",point[8],ans[8]);
}
int find_job_major(const char* j_major,struct Job j[],int n){
    for(int i=0;i<n;i++){
        if(strcmp(j[i].job_major,j_major)==0) {
            return i;
        }
    }
    return -1;
}
void count_by_job_major(struct Student arr[],int count,int year){
    struct Job j[100];
    int job_count=0;
    for(int i=0;i<count;i++){
        if(arr[i].graduation_year!=year) continue;
        int idx=find_job_major(arr[i].job_major,j,job_count);
        if(idx==-1){
            strcpy(j[job_count].job_major,arr[i].job_major);
            j[job_count].total++;
            job_count++;
        }
        j[idx].total++;
    }
    printf("====== %d 年从事不同专业的人数和比例 ======\n",year);
    for(int i=0;i<job_count;i++){
        printf("专业:%-20s 人数:%d 比例:%.4f%%\n",j[i].job_major,j[i].total,j[i].total*100.0/count);
    }
}
void count_menu_loop(struct Student arr[],int count){
    int number2;
    while(1){
        count_menu();
        if(scanf("%d",&number2)!=1){
            int ch;
            while((ch=getchar())!=EOF&&ch!='\n');
            printf("【警告】输入不是数字，请重试。\n");
            continue;
        }
        switch(number2){
            case count_year:{
                printf("请输入要统计的年份:\n");
                int year1=0;
                scanf("%d",&year1);
                count_data_by_year(arr,count,year1);
            }
            break;
            case count_degree:{
                printf("请输入要统计的年份:\n");
                int year1=0;
                scanf("%d",&year1);
                count_by_degree(arr,count,year1);
            }
            break;
            case count_major:{
                printf("请输入要统计的年份:\n");
                int year1=0;
                scanf("%d",&year1);
                count_by_major(arr,count,year1);
            }
            break;
            case count_directions:{
                printf("请输入要统计的年份:\n");
                int year1=0;
                scanf("%d",&year1);
                count_by_career(arr,count,year1);
            }
            break;
            case count_job_major:{
                printf("请输入要统计的年份:\n");
                int year1=0;
                scanf("%d",&year1);
                count_by_job_major(arr,count,year1);
            }
            break;
            case count_return:{
                return;
            }
            break;
            default:printf("【警告】无效的选项!\n");
        }
        printf("\n按回车继续...\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {} 
        getchar();
    }
}
int main(){
    int current_count=0;
    struct Student stu[MAXN];
    load_data(stu,&current_count);
    if(current_count==0){
        import_data_from_txt(stu,&current_count);
        save_data_to_dat(stu,current_count);
    }else{
        printf("【提示】当前已存在%d条数据!\n",current_count);
    }
    while(1){
        menu_main();
        int number1=0;
        scanf("%d",&number1);
        getchar();
        switch(number1){
            case import:
            import_data_from_txt(stu,&current_count);
            save_data_to_dat(stu,current_count);
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
            case delete:{
                printf("==========删除毕业生就业信息==========\n");
                printf("1.按学号删除\n");
                printf("2.按姓名删除\n");
                printf("请选择删除方式:\n");
                int delete_choice = 0;
                scanf("%d", &delete_choice);
                getchar();
                while(delete_choice!=1&&delete_choice!=2){
                    printf("【警告】无效的删除选项!重新输入!\n");
                    printf("1.按学号删除\n");
                    printf("2.按姓名删除\n");
                    printf("请选择删除方式:\n");
                    scanf("%d", &delete_choice);
                    getchar();
                }
                printf("请输入要删除的关键字:\n");
                char key[64];
                scanf("%s", key);
                if(delete_choice==2){
                    while(check_dulicate_by_name(stu,current_count,key)==0){
                        printf("【警告】未找到该姓名对应的毕业生信息,请重新输入!\n");
                        scanf("%s", key);
                    }
                    if(check_dulicate_by_name(stu,current_count,key)>1){
                        printf("【警告】找到多个该姓名的毕业生信息,请重新输入学号进行删除!\n");
                        scanf("%s", key);
                        delete_choice=1;
                    }
                }
                int delete_result=-1;
                if(delete_choice==1){
                    delete_result=delete_data(stu,&current_count,1,key);
                }
                else if(delete_choice==2){
                    delete_result=delete_data(stu,&current_count,2,key);
                }
                if(delete_result==1){
                    printf("【成功】删除该毕业生信息!\n");
                }else{
                    printf("【失败】删除失败!\n");
                }
            }
            break;
            case modify:{
                printf("==========修改毕业生就业信息==========\n");
                printf("请输入需要修改的毕业生学号:\n");
                char modify_id[32];
                scanf("%s",modify_id);
                getchar();
                for(int i=0;i<current_count;i++){
                    if(strcmp(stu[i].id,modify_id)==0){
                        printf("【提示】该毕业生就业信息:\n");
                        printf("%-12s %-8s %-4s %-12s %-8s %-8s %-10s %-18s %-18s %-20s %-18s\n",
                           "学号","姓名","性别","出生日期","入学年","毕业年",
                           "学历","专业","就业去向","单位名称","从事专业");
                        printf("%-12s %-8s %-4s %04d/%02d/%02d %-8d %-8d %-12s %-16s %-16s %-16s %-16s\n",
                            stu[i].id,
                            stu[i].name,stu[i].gender==F?"女":"男",
                            stu[i].bd.year,stu[i].bd.month,stu[i].bd.day,
                            stu[i].enroll_year,
                            stu[i].graduation_year,
                            stu[i].degree==本科生?"本科生":stu[i].degree==硕士研究生?"硕士研究生":"博士研究生",
                            stu[i].major,
                            stu[i].career==直接工作?"直接工作":stu[i].career==公务员?"公务员":stu[i].career==国内读硕?"国内读硕":stu[i].career==出国读硕?"出国读硕":stu[i].career==国内读博?"国内读博":stu[i].career==国外读博?"国外读博":stu[i].career==二战?"二战":stu[i].career==二学位?"二学位":stu[i].career==未就业?"未就业":"其他",
                            stu[i].employer,
                            stu[i].job_major
                        );
                        printf("请输入需要修改的关键字(姓名/性别/出生日期/入学年/毕业年/学历/专业/就业去向/单位名称/从事专业):\n");
                        char modify_key[64];
                        scanf("%s",modify_key);
                        getchar();
                        printf("请输入新的值:\n");
                        char modify_value[64];
                        scanf("%s",modify_value);
                        getchar();
                        if(strcmp(modify_key,"姓名")==0){
                            strcpy(stu[i].name,modify_value);
                        }
                        else if(strcmp(modify_key,"性别")==0){
                            if(!str_to_enum_gender(modify_value,&stu[i].gender)){
                                printf("【警告】无效的性别选项:%s\n",modify_value);
                            }
                        }
                        else if(strcmp(modify_key,"出生日期")==0){
                            sscanf(modify_value,"%d/%d/%d",&stu[i].bd.year,&stu[i].bd.month,&stu[i].bd.day);
                        }
                        else if(strcmp(modify_key,"入学年")==0){
                            stu[i].enroll_year=atoi(modify_value);
                        }
                        else if(strcmp(modify_key,"毕业年")==0){
                            stu[i].graduation_year=atoi(modify_value);
                        }
                        else if(strcmp(modify_key,"学历")==0){
                            if(!str_to_enum_degree(modify_value,&stu[i].degree)){
                                printf("【警告】无效的学历选项:%s\n",modify_value);
                            }
                        }
                        else if(strcmp(modify_key,"专业")==0){
                            strcpy(stu[i].major,modify_value);
                        }
                        else if(strcmp(modify_key,"就业去向")==0){
                            if(!str_to_enum_career(modify_value,&stu[i].career)){
                                printf("【警告】无效的就业去向选项:%s\n",modify_value);
                            }
                        }
                        else if(strcmp(modify_key,"单位名称")==0){
                            strcpy(stu[i].employer,modify_value);
                        }
                        else if(strcmp(modify_key,"从事专业")==0){
                            strcpy(stu[i].job_major,modify_value);
                        }else{
                            printf("【警告】无效的修改选项!\n");
                        }
                        printf("【成功】修改该毕业生就业信息!\n");
                    }else{
                        printf("【失败】未找到该学号对应的毕业生就业信息!\n");
                    }
                }
                FILE *out=fopen("students.dat","wb");
                if(out==NULL){
                    printf("【警告】无法打开文件写回!\n");
                    break;
                }
                size_t write_count=fwrite(stu,sizeof(struct Student),current_count,out);
                if(write_count!=(size_t)current_count){
                    printf("【警告】写入文件时出错!\n");
                }else{
                    printf("【成功】修改成功，已更新数据文件students.dat!\n");
                }
                fclose(out);
            }
            break;
            case count:{
                count_menu_loop(stu,current_count);
            }break;
            case quit:{
                printf("==========退出系统==========\n");
                return 0;
            }
            break;
            default:printf("【警告】无效的选项!\n");
        };
    }
}