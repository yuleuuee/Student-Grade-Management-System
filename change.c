#include <stdio.h>  //标准输入输出函数库
#include <stdlib.h> //标准库函数
#include <string.h> //字符串函数

void menu();  
void add();
void view();
void search();
void modify();
void deleterec();
void insert();
void totalrec();

typedef struct student
{
    char name[20];  //学生名
    int rollno;     //卷号
    float marks[3];  //数组保存有三门课的成绩
} st;


int main()
{
    printf("\n\n\n******************************************\n");
    printf("******************************************\n\n\n");
    printf("<=========================================>\n");
    printf("<=======::                       ::=======>\n\n");
    printf("              学生成绩管理系统            \n\n");
    printf("<=======::                       ::=======>\n");
    printf("<=========================================>\n\n");
    printf("           --- 欢迎大家 ---           \n\n");
    printf("       Press any key to continue.");
    fflush(stdin);
    getchar();
    printf("\n\n\n");
    menu();
    return 0;
}

//********************************************************************************************//

void menu()
{
    int choice;
    printf("<-----------::  MENU  ::----------->\n\n");
    printf("Enter appropriate number to perform following task.\n\n");
    printf("      1 : Add Record.( 录入信息 )\n");
    printf("      2 : View Record.( 浏览信息 )\n");
    printf("      3 : Search Record.( 搜索信息 )\n");
    printf("      4 : Modify Record.( 修改信息 )\n");
    printf("      5 : Delete Record.( 删除信息 )\n");
    printf("      6 : Insert Record.( 插入信息 )\n");
    printf("      7 : Total Record.(总信息)\n");
    printf("      8 : Exit.( 退出 )\n\n");
    printf("Enter your choice. : ");
    scanf("%d", &choice);
    printf("\n\n");

    switch (choice)
    {
    case 1:
        add();
        break;
    case 2:
        view();
        break;
    case 3:
        search();
        break;
    case 4:
        modify();
        break;
    case 5:
        deleterec();
        break;
    case 6:
        insert();
        break;
    case 7:
        totalrec();
        break;
    case 8:
        exit(1);
        break;
    default:
        printf("Invalid Choice.!!!\n\n");
    }
}

//******************* ADDING RECORDS ****************************//

void add()
{
    FILE *fp;
    struct student std;
    char another = 'y';
    fp = fopen("record.txt", "ab+");
    if (fp == NULL)
    {
        printf("Error opening file\n\n");
        exit(1);
    }
    fflush(stdin);
    while (another == 'y')
    {

        printf("\n\n<----------:: ADD RECORD ( 录入信息 ) ::---------->\n\n");
        printf("Enter details of student.\n\n");
        printf("Enter Name : ");
        gets(std.name);
        printf("Enter Roll No : ");
        scanf("%d", &std.rollno);
        fflush(stdin);
        printf("Enter Marks of Data Structure : ");
        scanf("%f", &std.marks[0]);
        printf("Enter marks of Math : ");
        scanf("%f", &std.marks[1]);
        printf("Enter marks of Java : ");
        scanf("%f", &std.marks[2]);
        fwrite(&std, sizeof(std), 1, fp);
        printf("\n\nAdded Sucessfully!!!\n\n");
        printf("Want to add of another record? Then press 'y' else 'n' : ");  //add another record?
        fflush(stdin);
        another = getchar();
        fflush(stdin);
    }
    fclose(fp);
    printf("\n\n");
    printf("Press any key to continue.");
    fflush(stdin);
    getchar();
    printf("\n\n\n");
    menu();
}

//********************** VIEWING ALL RECORD *************************//
void view()
{
    FILE *fp;
    int i = 1;
    struct student std;
    printf("<----------:: VIEW RECORD ( 浏览信息 ) ::---------->\n\n");
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("S.No |  Name of Student   |  Roll No |  DataStr. |  Math  |  Java  | Total |  Percent |  Grade   \n");
    printf("-------------------------------------------------------------------------------------------------\n");
    fp = fopen("record.txt", "rb+");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    while (fread(&std, sizeof(std), 1, fp) == 1)
    {
        float totalMarks = std.marks[0] + std.marks[1] + std.marks[2];   //总分
        float per = (totalMarks / 300) * 100;      //百分比
        char grade;        //成绩

        if (per >= 90)                                                   
        {
            grade = 'A';
        }
        else if (per >= 70)
        {
            grade = 'B';
        }
        else if (per >= 50)
        {
            grade = 'C';
        }
        else
        {
            grade = 'D';
        }

        printf("%-7d %-22s %-9d %-9.2f %-6.2f %8.2f %8.2f %8.2f %7c\n", i, std.name, std.rollno, std.marks[0], std.marks[1], std.marks[2], totalMarks, per, grade);
        i++;
    }
    fclose(fp);
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("\n\n");
    printf("Press any key to continue.");
    fflush(stdin);
    getchar();
    printf("\n\n\n");
    menu();
}

//********************** SEARCHING A PARTICULAR RECORD *************************//

void search()
{
    FILE *fp;
    struct student std;
    char stname[20];
    int found = 0;
    printf("<----------:: SEARCH RECORD ( 搜索信息 ) ::---------->\n\n");
    printf("Enter name of student : ");
    fflush(stdin);
    gets(stname);
    fp = fopen("record.txt", "rb+");
    if (fp == NULL)
    {
        printf("Error opening file\n\n");
        exit(1);
    }
    while (fread(&std, sizeof(std), 1, fp) == 1)
    {
        if (strcmp(stname, std.name) == 0)
        {

            found = 1;

            float totalMarks = std.marks[0] + std.marks[1] + std.marks[2];
            float per = (totalMarks / 300) * 100;
            char grade;

            if (per >= 90)
            {
                grade = 'A';
            }
            else if (per >= 70)
            {
                grade = 'B';
            }
            else if (per >= 50)
            {
                grade = 'C';
            }
            else
            {
                grade = 'D';
            }

            printf("\n\n      Name : %s\n", std.name);
            printf("      Roll No : %d\n", std.rollno);
            printf("      Marks of Data Structure : %.2f\n", std.marks[0]);
            printf("      Marks of Math : %.2f\n", std.marks[1]);
            printf("      Marks of Java : %.2f\n", std.marks[2]);
            printf("      Total Marks : %.2f\n", totalMarks);
            printf("      Percentage : %.2f\n", per);
            printf("      Grade : %c\n", grade);
        };
    }

    // if no such name
    if (!found)
    {
        printf("\n\nNo such Name Available!!\n\n");
    }
    fclose(fp);
    printf("\n\n");
    printf("Press any key to continue.");
    fflush(stdin);
    getchar();
    printf("\n\n\n");
    menu();
}

//******************** MODIFYING A PARTICULAR RECORD ***************************//

void modify()
{
    char stname[20];
    FILE *fp;
    struct student std;
    int found = 0;
    printf("<----------:: MODIFY RECORD ( 修改信息 ) ::---------->\n\n");
    printf("Enter name of student to modify : ");
    fflush(stdin);
    gets(stname);
    printf("\n\n");
    fp = fopen("record.txt", "rb+");
    if (fp == NULL)
    {
        printf("Error opening file!!!\n\n");
        exit(1);
    }
    rewind(fp);
    fflush(stdin);
    while (fread(&std, sizeof(std), 1, fp) == 1)
    {
        if (strcmp(stname, std.name) == 0)
        {
            found = 1;
            printf("Enter New name: ");
            gets(std.name);
            printf("Enter New roll no : ");
            scanf("%d", &std.rollno);
            printf("Enter New marks of Data Structure : ");
            scanf("%f", &std.marks[0]);
            printf("Enter New marks of Math : ");
            scanf("%f", &std.marks[1]);
            printf("Enter New marks of Java : ");
            scanf("%f", &std.marks[2]);
            fseek(fp, -sizeof(std), SEEK_CUR);
            fwrite(&std, sizeof(std), 1, fp);
            break;
        }
    }
    if (!found)
    {
        printf("\n\nNo such Name Available!!\n\n");
    }
    else
    {
        printf("\n\nModified Succesfully!!\n\n");
    }
    fclose(fp);
    printf("\n\n");
    printf("Press any key to continue.");
    fflush(stdin);
    getchar();
    printf("\n\n\n");
    menu();
}

//******************** DELETING A PARTICULAR RECORD ***************************//

void deleterec()
{
    char stname[20];
    FILE *fp, *ft;
    struct student std;
    printf("<----------:: DELETE RECORD ( 删除信息 ) ::---------->\n\n");
    printf("Enter name of student to delete record : ");
    fflush(stdin);
    gets(stname);
    fp = fopen("record.txt", "rb+");
    if (fp == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    ft = fopen("temp.txt", "wb+");
    if (ft == NULL)
    {
        printf("Error opening file\n\n");
        exit(1);
    }
    while (fread(&std, sizeof(std), 1, fp) == 1)
    {
        if (strcmp(stname, std.name) != 0)
        {
            fwrite(&std, sizeof(std), 1, ft);
        }
    }
    fclose(fp);
    fclose(ft);
    remove("record.txt");
    rename("temp.txt", "record.txt");
    printf("\n\n");
    printf("Compleated!!!\n\n");
    printf("Press any key to continue.");
    fflush(stdin);
    getchar();
    printf("\n\n\n");
    menu();
}

//******************* INSERTING RECORD ****************************//

void insert()
{
    char stname[20];
    FILE *fp, *ft;
    struct student std;
    int found = 0;
    printf("<----------:: INSERT RECORD ( 插入信息 ) ::---------->\n\n");
    printf("Enter name of student After which you want to insert : ");
    fflush(stdin);
    gets(stname);
    fp = fopen("record.txt", "rb+");
    if (fp == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    ft = fopen("temp.txt", "wb+");
    if (ft == NULL)
    {
        printf("Error opening file\n\n");
        exit(1);
    }
    while (fread(&std, sizeof(std), 1, fp) == 1)
    {
        fwrite(&std, sizeof(std), 1, ft);
        if (strcmp(stname, std.name) == 0) //if the name matches then
        {
            found = 1;
            // new record
            char another = 'y';
            while (another == 'y')
            {
                printf("Enter details of student.\n\n");
                printf("Enter Name : ");
                gets(std.name);
                printf("Enter Roll No : ");
                scanf("%d", &std.rollno);
                fflush(stdin);
                printf("Enter marks of Data Structure : ");
                scanf("%f", &std.marks[0]);
                printf("Enter marks of Math : ");
                scanf("%f", &std.marks[1]);
                printf("Enter marks of Java : ");
                scanf("%f", &std.marks[2]);
                fwrite(&std, sizeof(std), 1, ft);
                printf("Want to add of another record? Then press 'y' else 'n' : ");
                fflush(stdin);
                another = getchar();
                fflush(stdin);
            }
        }
    }
    fclose(fp);
    fclose(ft);
    remove("record.txt");
    rename("temp.txt", "record.txt");
    printf("\n\n");

    if (found)
    {
        printf("Inserted Successfully !!\n\n");
    }
    else
    {
        printf("\n\nNo such Name Available!!\n\n");
    }

    printf("Press any key to continue.");
    fflush(stdin);
    getchar();
    printf("\n\n\n");
    menu();
}

//*********************** TOTAL RECORD ************************//

void totalrec()
{
    st s1;
    FILE *fp;
    fp = fopen("record.txt", "rb+");
    fseek(fp, 0, SEEK_END);  //将光标置于末尾
    int n = ftell(fp) / sizeof(st); //ftell(fp) 给出光标的位置
    printf("<----------:: TOTAL RECORD ( 总信息 ) ::--------->\n\n");
    printf("Total Number of Records : %d", n);
    fclose(fp);
    printf("\n\n");
    printf("Press any key to continue.");
    fflush(stdin);
    getchar();
    printf("\n\n\n");
    menu();
}

