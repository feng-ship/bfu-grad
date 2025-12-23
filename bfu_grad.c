#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <wchar.h>
#include <locale.h>
#define MAXN 1000
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
int is_int(double x){
    return x==(int)x;
}
int check_birthday_is_int(double year,double month,double day){
    return(is_int(year)&&is_int(month)&&is_int(day));
}
int is_runnian(int year){
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
int check_birthday(struct BirthDate s[],int n){
    if(s[n].month>12||s[n].month<1||s[n].day<1||s[n].day>31){
        return 0;
    }
    if(s[n].month==1||s[n].month==3||s[n].month==5||s[n].month==7||s[n].month==8||s[n].month==10||s[n].month==12){
        if(s[n].day>31) return 0;
    }
    if(s[n].month==4||s[n].month==6||s[n].month==9||s[n].month==11){
        if(s[n].day>30) return 0;
    }
    if(!is_runnian(s[n].year)){
        if(s[n].month==2){
            if(s[n].day>28) return 0;
        }
    }else{
        if(s[n].month==2){
            if(s[n].day>29) return 0;
        }
    }
    return 1;
}
int check_enroll_grad(int enroll,int grad){
    return (enroll<grad||enroll==grad);
}
void import_data_from_txt(struct Student arr[],int *count){
    struct Student temp[MAXN];
    FILE *in;
    if((in=fopen("students.txt","r"))==NULL){
        printf("【警告】无法打开文件!\n");
        return;
    }
    char line[512];
    double temp_year,temp_month,temp_day;
    double enroll_year,graduation_year;
    char temp_gender[16];
    char temp_degree[32];
    char temp_career[32];
    while(fgets(line,sizeof(line),in)){
        line[strcspn(line,"\n")]=0;
        if(strlen(line)==0) continue;
        int scanned_items = sscanf(line,"%31[^,],%63[^,],%15[^,],%lf/%lf/%lf,%lf,%lf,%31[^,],%127[^,],%31[^,],%127[^,],%63[^,\n]",
            temp[*count].id,
            temp[*count].name,
            temp_gender,
            &temp_year,&temp_month,&temp_day,
            &enroll_year,
            &graduation_year,
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
        if(check_dulicate_by_id(arr,*count, temp[*count].id)){
            printf("【警告】毕业生学号%s已存在,跳过此毕业生!\n",temp[*count].id);
            continue;
        }
        if(*count>=MAXN){
            printf("【警告】已达到最大容量,停止导入!\n");
            continue;
        }
        if(!is_int(enroll_year)){
            printf("【警告】入学年不为整数,与实际不符,跳过该条记录:%s!\n",line);
            continue;
        }
        if(!is_int(graduation_year)){
            printf("【警告】毕业年不为整数,与实际不符,跳过该条记录:%s!\n",line);
            continue;
        }
        temp[*count].enroll_year=(int)enroll_year;
        temp[*count].graduation_year=(int)graduation_year;
        if(!check_enroll_grad(temp[*count].enroll_year,temp[*count].graduation_year)){
            printf("【警告】入学年大于毕业年,与实际不符,跳过该条记录:%s!\n",line);
            continue;
        }
        if(!check_birthday_is_int(temp_year,temp_month,temp_day)){
            printf("【警告】日期不为整数,跳过该条记录:%s!\n",line);
            continue;
        }else{
            temp[*count].bd.year=(int)temp_year;
            temp[*count].bd.month=(int)temp_month;
            temp[*count].bd.day=(int)temp_day;
        }
        if(!check_birthday(&temp[*count].bd,*count)){
            printf("【警告】日期不合法,跳过该条记录:%s!\n",line);
            continue;
        }
        if(!str_to_enum_gender(temp_gender,&temp[*count].gender)||!str_to_enum_degree(temp_degree,&temp[*count].degree)||!str_to_enum_career(temp_career,&temp[*count].career)){
            printf("【警告】性别/学历/就业去向数据内容错误，跳过该条记录: %s",line);
            continue;
        }
        arr[*count]=temp[*count];
        (*count)++;
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
int display_width(const char *s){
    int w = 0;
    while (*s){
        unsigned char c = *s;
        if (c >= 0x80){
            w += 2;      // 中文显示宽度=2
            s += 3;      // UTF-8 中文占 3 字节
        } else {
            w += 1;
            s++;
        }
    }
    return w;
}
void print_cell(const char *s, int width){
    int w = display_width(s);
    printf("%s", s);
    for(int i = 0; i < width - w; i++){
        putchar(' ');
    }
}
void view_table_simple(struct Student arr[], int count){
    const char* headers[] = {
        "学号","姓名","性别","出生日期","入学年","毕业年",
        "学历","专业","就业去向","单位名称","从事专业"
    };

    const int cols = 11;
    int widths[cols] = {0};

    // 初始：列宽 = 表头宽度
    for(int i = 0; i < cols; i++){
        widths[i] = display_width(headers[i]);
    }

    char buf[128];

    // 扫描所有数据，取最大宽度
    for(int i = 0; i < count; i++){
        int w;

        // 学号
        w = display_width(arr[i].id);
        if(w > widths[0]) widths[0] = w;

        // 姓名
        w = display_width(arr[i].name);
        if(w > widths[1]) widths[1] = w;

        // 性别
        w = display_width(arr[i].gender==F?"女":"男");
        if(w > widths[2]) widths[2] = w;

        // 出生日期
        sprintf(buf,"%04d/%02d/%02d",arr[i].bd.year,arr[i].bd.month,arr[i].bd.day);
        w = display_width(buf);
        if(w > widths[3]) widths[3] = w;

        // 入学年与毕业年
        sprintf(buf,"%d",arr[i].enroll_year);
        if(display_width(buf) > widths[4]) widths[4] = display_width(buf);

        sprintf(buf,"%d",arr[i].graduation_year);
        if(display_width(buf) > widths[5]) widths[5] = display_width(buf);

        // 学历
        const char* deg = arr[i].degree==本科生?"本科生":
                          arr[i].degree==硕士研究生?"硕士研究生":
                          "博士研究生";
        if(display_width(deg) > widths[6]) widths[6] = display_width(deg);

        // 专业
        if(display_width(arr[i].major) > widths[7]) widths[7] = display_width(arr[i].major);

        // 就业去向
        const char* car = arr[i].career==直接工作?"直接工作":
                          arr[i].career==公务员?"公务员":
                          arr[i].career==国内读硕?"国内读硕":
                          arr[i].career==出国读硕?"出国读硕":
                          arr[i].career==国内读博?"国内读博":
                          arr[i].career==国外读博?"国外读博":
                          arr[i].career==二战?"二战":
                          arr[i].career==二学位?"二学位":
                          arr[i].career==未就业?"未就业":"其他";
        if(display_width(car) > widths[8]) widths[8] = display_width(car);

        // 单位名称
        if(display_width(arr[i].employer) > widths[9]) widths[9] = display_width(arr[i].employer);

        // 从事专业
        if(display_width(arr[i].job_major) > widths[10]) widths[10] = display_width(arr[i].job_major);
    }

    // 多加一点空格看起来更舒服
    for(int i = 0; i < cols; i++) widths[i] += 2;

    // 计算整行总宽度（输出框线）
    int total = 0;
    for(int i = 0; i < cols; i++) total += widths[i];
    
    // 顶部框线
    for(int i = 0; i < total; i++) putchar('=');
    putchar('\n');

    // 表头
    for(int i = 0; i < cols; i++){
        print_cell(headers[i], widths[i]);
    }
    putchar('\n');

    // 分隔线
    for(int i = 0; i < total; i++) putchar('-');
    putchar('\n');

    // 数据行
    for(int i = 0; i < count; i++){

        sprintf(buf,"%s", arr[i].id);
        print_cell(buf, widths[0]);

        print_cell(arr[i].name, widths[1]);
        print_cell(arr[i].gender==F?"女":"男", widths[2]);

        sprintf(buf,"%04d/%02d/%02d",arr[i].bd.year,arr[i].bd.month,arr[i].bd.day);
        print_cell(buf, widths[3]);

        sprintf(buf,"%d",arr[i].enroll_year);
        print_cell(buf, widths[4]);

        sprintf(buf,"%d",arr[i].graduation_year);
        print_cell(buf, widths[5]);

        const char* deg = arr[i].degree==本科生?"本科生":
                          arr[i].degree==硕士研究生?"硕士研究生":"博士研究生";
        print_cell(deg, widths[6]);

        print_cell(arr[i].major, widths[7]);

        const char* car = arr[i].career==直接工作?"直接工作":
                          arr[i].career==公务员?"公务员":
                          arr[i].career==国内读硕?"国内读硕":
                          arr[i].career==出国读硕?"出国读硕":
                          arr[i].career==国内读博?"国内读博":
                          arr[i].career==国外读博?"国外读博":
                          arr[i].career==二战?"二战":
                          arr[i].career==二学位?"二学位":
                          arr[i].career==未就业?"未就业":"其他";
        print_cell(car, widths[8]);

        print_cell(arr[i].employer, widths[9]);
        print_cell(arr[i].job_major, widths[10]);

        putchar('\n');
    }

    // 底部框线
    for(int i = 0; i < total; i++) putchar('=');
    putchar('\n');
}
void view_data(struct Student arr[],int count){
    printf("==========浏览毕业生就业信息==========\n");
    if(count==0){
        printf("【提示】当前无数据可浏览,请先导入或添加数据!\n");
        return;
    }
    view_table_simple(arr,count);
}
void show_student_row(struct Student s){
    printf("===============================================================================================================================\n");
    printf("| %-10s | %-6s | %-2s | %04d/%02d/%02d | %-4d | %-4d | %-6s | %-12s | %-10s | %-15s | %-15s |\n",
        s.id,
        s.name,
        s.gender==F?"女":"男",
        s.bd.year, s.bd.month, s.bd.day,
        s.enroll_year,
        s.graduation_year,
        s.degree==本科生?"本科":
        s.degree==硕士研究生?"硕士":"博士",
        s.major,
        s.career==直接工作?"工作":
        s.career==公务员?"公务员":
        s.career==国内读硕?"国内读硕":
        s.career==出国读硕?"出国读硕":
        s.career==国内读博?"国内读博":
        s.career==国外读博?"国外读博":
        s.career==二战?"二战":
        s.career==二学位?"二学位":
        s.career==未就业?"未就业":"其他",
        s.employer,
        s.job_major
    );
    printf("===============================================================================================================================\n");
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
                show_student_row(*result);
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
                show_student_row(*result2);
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
    struct Student temp[MAXN];
    printf("==========增录毕业生就业信息==========\n");
    while(1){
        printf("请输入学号:\n");
        scanf("%s",temp[*count].id);
        if(check_dulicate_by_id(arr,*count,temp[*count].id)) {
            printf("【警告】学号%s已存在，请重新输入!\n",temp[*count].id);
            continue;
        }else break;
    }
    printf("请输入姓名:\n");
    scanf("%s",temp[*count].name);
    char gender[16];
    while(1){
        printf("请输入性别(男/女):\n");
        scanf("%s",gender);
        if(!str_to_enum_gender(gender,&temp[*count].gender)){
            printf("【警告】性别数据内容错误，请重新输入!\n");
            continue;
        }else break;
    }
    double y,m,d;
    double enroll_year,graduation_year;
    while(1){
        printf("请输入出生日期:\n");
        scanf("%lf%lf%lf",&y,&m,&d);
        if(!check_birthday_is_int(y,m,d)){
            printf("【警告】日期不为整数,请重新输入!\n");
            continue;
        }else{
            temp[*count].bd.year=(int)y;
            temp[*count].bd.month=(int)m;
            temp[*count].bd.day=(int)d;
        }
        if(!check_birthday(&temp[*count].bd,*count)){
            printf("【警告】日期不合法,请重新输入!\n");
            continue;
        }else break;
    }
    while(1){
        printf("请输入入学年:\n");
        scanf("%lf",&enroll_year);
        printf("请输入毕业年:\n");
        scanf("%lf",&graduation_year);
        if(!is_int(enroll_year)||!is_int(graduation_year)){
            printf("【警告】入学年/毕业年不为整数,请重新输入!\n");
            continue;
        }else{
            temp[*count].enroll_year=(int)enroll_year;
            temp[*count].graduation_year=(int)graduation_year;
        }
    }
    char degree[32];
    while(1){
        printf("请输入学历（本科生/硕士研究生/博士研究生）:\n");
        scanf("%s",degree);
        if(!str_to_enum_degree(degree,&temp[*count].degree)){
            printf("【警告】学历数据内容错误，请重新输入!\n");
            continue;
        }else break;
    }
    printf("请输入毕业专业:\n");
    scanf("%s",temp[*count].major);
    char career[32];
    while(1){
        printf("请输入就业方向（直接工作/公务员/国内读硕/出国读硕/国内读博/国外读博/二战/二学位/未就业/其他）:\n");
        scanf("%s",career);
        if(!str_to_enum_career(career,&temp[*count].career)){
            printf("【警告】学历数据内容错误，请重新输入!\n");
            continue;
        }else break;
    }
    printf("请输入就业或升学单位:\n");
    scanf("%s",temp[*count].employer);
    printf("请输入毕业后所从事的专业:\n");
    scanf("%s",temp[*count].job_major);
    // 放入内存数组
    arr[*count] = temp[*count];
    (*count)++;

    // 追加到文件
    FILE *out = fopen("students.dat", "ab");
    if (!out) {
        printf("【警告】无法打开文件 students.dat 以写入！\n");
        return;
    }
    size_t written = fwrite(&temp, sizeof(struct Student), 1, out);
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
        show_student_row(arr[idx]);
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
void modify_student(struct Student stu[], int current_count){
    printf("==========修改毕业生就业信息==========\n");
    printf("请输入需要修改的毕业生学号:\n");
    char modify_id[32];
    scanf("%s", modify_id);
    getchar();
    // 查找
    int i = -1;
    for(int k=0;k<current_count;k++){
        if(strcmp(stu[k].id, modify_id) == 0){
            i = k;
            break;
        }
    }
    if(i == -1){
        printf("【失败】未找到该学号对应的毕业生就业信息!\n");
        return;
    }
    // 展示当前信息
    printf("\n【提示】该毕业生就业信息如下：\n");
    show_student_row(stu[i]);
    // 字段菜单
    printf("\n请选择需要修改的字段编号：\n");
    printf("1. 姓名\n");
    printf("2. 性别\n");
    printf("3. 出生日期\n");
    printf("4. 入学年\n");
    printf("5. 毕业年\n");
    printf("6. 学历\n");
    printf("7. 专业\n");
    printf("8. 就业去向\n");
    printf("9. 单位名称\n");
    printf("10. 从事专业\n");
    printf("0. 返回上级\n");
    printf("请输入：");
    int choice;
    scanf("%d", &choice);
    getchar();
    if(choice == 0) return;
    struct Student temp[MAXN];
    switch(choice){
        case 1:
            {
                char name[64];
                scanf("%s",name);
                strcpy(stu[i].name,name);
            }
            break;
        case 2:
            {
                char gender[16];
                while(1){
                    printf("请输入性别(男/女):\n");
                    scanf("%s",gender);
                    if(!str_to_enum_gender(gender,&temp[i].gender)){
                        printf("【警告】性别数据内容错误，请重新输入!\n");
                        continue;
                    }else break;
                }
                stu[i].gender=temp[i].gender;
            }
            break;
        case 3:
            {
                while(1){
                    double y,m,d;
                    printf("请输入出生日期:\n");
                    scanf("%lf%lf%lf",&y,&m,&d);
                    if(!check_birthday_is_int(y,m,d)){
                        printf("【警告】日期不为整数,请重新输入!\n");
                        continue;
                    }else{
                        temp[i].bd.year=(int)y;
                        temp[i].bd.month=(int)m;
                        temp[i].bd.day=(int)d;
                    }
                    if(!check_birthday(&temp[i].bd,i)){
                    printf("【警告】日期不合法,请重新输入!\n");
                    continue;
                    }else break;
                }
                stu[i].bd=temp[i].bd;
            }
            break;
        case 4:
            {
                double enroll_year;
                while(1){
                    printf("请输入入学年:\n");
                    scanf("%lf",&enroll_year);
                    if(!is_int(enroll_year)){
                        printf("【警告】入学年不为整数,请重新输入!\n");
                        continue;
                    }else{
                        temp[i].enroll_year=(int)enroll_year;
                        break;
                    }
                }
                stu[i].enroll_year=temp[i].enroll_year;
            }
            break;
        case 5:
            {
                double graduation_year;
                while(1){
                    printf("请输入毕业年:\n");
                    scanf("%lf",&graduation_year);
                    if(!is_int(graduation_year)){
                        printf("【警告】毕业年不为整数,请重新输入!\n");
                        continue;
                    }else{
                        temp[i].graduation_year=(int)graduation_year;
                        break;
                    }
                }
                stu[i].graduation_year=temp[i].graduation_year;
            }
            break;
        case 6:
            {
                char degree[32];
                while(1){
                    printf("请输入学历（本科生/硕士研究生/博士研究生）:\n");
                    scanf("%s",degree);
                    if(!str_to_enum_degree(degree,&temp[i].degree)){
                        printf("【警告】无效的学历选项,请重新输入!\n");
                        continue;
                    }else break;
                }
                stu[i].degree=temp[i].degree;
            }
            break;
        case 7:
            {
                printf("请输入毕业专业:\n");
                scanf("%s",temp[i].major);
            }
            break;
        case 8:
            {
                char career[32];
                while(1){
                    printf("请输入就业方向（直接工作/公务员/国内读硕/出国读硕/国内读博/国外读博/二战/二学位/未就业/其他）:\n");
                    scanf("%s",career);
                    if(!str_to_enum_career(career,&temp[i].career)){
                        printf("【警告】无效的就业去向选项，请重新输入!\n");
                        continue;
                    }else break;
                }
                stu[i].career=temp[i].career;
            }
            break;
        case 9:
            {
                printf("请输入就业或升学单位:\n");
                scanf("%s",stu[i].employer);
            }
            break;
        case 10:
            {
                printf("请输入毕业后所从事的专业:\n");
                scanf("%s",stu[i].job_major);
            }
            break;
        default:
            printf("【警告】无效的选项！\n");
            break;
    }
    // 写回文件
    FILE *out = fopen("students.dat","wb");
    if(!out){
        printf("【警告】无法打开文件写回!\n");
        return;
    }
    fwrite(stu, sizeof(struct Student), current_count, out);
    fclose(out);
    printf("【成功】修改完成，数据已写回 students.dat！\n");
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
void printf_data_degree(const char *label,int employed,int total,double *rate){
    if(total==0){
        printf("%s:无数据(%d人)\n",label,total);
    }else{
        *rate=employed*100.0/total;
        printf("%s:%d/%d(%lf)\n",label,employed,total,*rate);
    }
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
    printf("【成功】%d年就业率:\n",year);
    printf_data_degree("本科生",point[0],count,&ans[0]);
    printf_data_degree("硕士研究生",point[1],count,&ans[1]);
    printf_data_degree("博士研究生",point[2],count,&ans[2]);
}
int is_employed(enum Career c){
    return !(c==未就业||c==其他||c==二战);
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
            ma[m_count].total=0;
            ma[m_count].employed=0;
            idx=m_count;
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
            j[job_count].total=0;
            idx=job_count;
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
                int year1=0;
                while(1){
                    printf("请输入要统计的年份:\n");
                    scanf("%d",&year1);
                    if(!is_int(year1)){
                        printf("【警告】年份不为整数，请重新输入!\n");
                        continue;
                    }else {
                        break;
                    }
                }
                count_data_by_year(arr,count,year1);
            }
            break;
            case count_degree:{
                int year1=0;
                while(1){
                    printf("请输入要统计的年份:\n");
                    scanf("%d",&year1);
                    if(!is_int(year1)){
                        printf("【警告】年份不为整数，请重新输入!\n");
                        continue;
                    }else {
                        break;
                    }
                }
                count_by_degree(arr,count,year1);
            }
            break;
            case count_major:{
                int year1=0;
                while(1){
                    printf("请输入要统计的年份:\n");
                    scanf("%d",&year1);
                    if(!is_int(year1)){
                        printf("【警告】年份不为整数，请重新输入!\n");
                        continue;
                    }else {
                        break;
                    }
                }
                count_by_major(arr,count,year1);
            }
            break;
            case count_directions:{
                int year1=0;
                while(1){
                    printf("请输入要统计的年份:\n");
                    scanf("%d",&year1);
                    if(!is_int(year1)){
                        printf("【警告】年份不为整数，请重新输入!\n");
                        continue;
                    }else {
                        break;
                    }
                }
                count_by_career(arr,count,year1);
            }
            break;
            case count_job_major:{
                int year1=0;
                while(1){
                    printf("请输入要统计的年份:\n");
                    scanf("%d",&year1);
                    if(!is_int(year1)){
                        printf("【警告】年份不为整数，请重新输入!\n");
                        continue;
                    }else {
                        break;
                    }
                }
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
                modify_student(stu,current_count);
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