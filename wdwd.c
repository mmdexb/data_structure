#include<stdio.h>
#include<string.h>
#include<windows.h>
void menu1();//定义主菜单函数
void add();//定义添加学生信息函数
void pre();//定义显示学生信息函数
void in();//定义插入函数
void del();//显示删除菜单
void did();//定义按照学号删除函数
void dname();//定义按照名字删除函数
void order();//按照成绩倒序输出
void all();//计算学生总分和平均分
void caverage();//计算每个班每门课平均分
void sid();//按照学号查找学生
void sname();//按照姓名查找学生
void search_s();//查找某门课最高/最低分
void sl();//查找某门课最高/最低分
void Average_();//查找平均分最高/最低学生
int n;
typedef struct student
{
   char name[20];
   int id, class, total;
   double av;
   int score[3];
}STUDENT;
STUDENT stu[1000];
int main()
{
    SetConsoleOutputCP(65001);
   int op;
   int number;
   char name[20];

   while(1)
   {
       menu1();//调用菜单函数显示
       printf("请选择您要进行的操作（请输入数字）：");
       scanf("%d", &op);
       switch (op)
       {
       case 1:printf("请输入将要添加学生的个数：");
              scanf("%d", &n);
              add(stu); break;//调用添加学生信息表函数
       case 2: pre(stu);  break;//调用显示学生信息函数
       case 3: while (1) {
           printf("-----查找菜单----\n请选择您的查找方式\n0 返回上一级菜单\n12 按照学号查找\n13 按照姓名查找\n14 查找平均分最高的学生信息\n15 查找平均分最低的学生信息\n16 查找某门课程的最高/最低成绩的学生信息\n");
           printf("请输入您的选择：");
           scanf("%d", &op);
           if (op == 0)
               break;
           switch (op)
           {
           case 12:printf("请输入您要查找学生的学号：");
               scanf("%d", &number);
               sid(stu, number); putchar('\n');break;
           case 13:sname(stu); break;
           case 14:Average_(stu, op);//查找平均分最高的学生信息
               break;
           case 15:Average_(stu, op);//查找平均分最低的学生信息
               break;
           case 16:search_s(stu); break;
           }
       }break; //调用查找学生信息函数
       case 4:in(stu); break;  //调用插入学生信息函数
       case 5:del(stu); break;//调用删除学生信息函数
       case 6: while (1) {
           printf("请选择您要进行的计算方式:\n0 返回上一级菜单\n11 计算总成绩和平均分\n33 计算每个班级每门课程的平均分\n");

           scanf("%d", &op);
           if (op == 0)
               break;
           switch (op)
           {
           case 11:all(stu); printf("-------总分和平均分计算已完成-------\n"); putchar('\n'); break;//计算总分和平均分
           case 33:caverage(stu); printf("-------计算已完成-------\n"); putchar('\n'); break;//计算每班每门课的平均分
           default:
               printf("\nIllegal digital.Try again\n"); break;
           }
       } break;//调用成绩计算函数
       case 7:order(stu); break;//调用成绩降序排序函数
       case 0:return 0;//退出
       default:
           printf("\nIllegal digital.Try again\n"); break;
       }
   }
   return 0;
}
void menu1()//显示菜单
{
   printf("--网安241-徐浩然-202401050813--\n");
   printf("-----成绩系统-----\n1 添加学生信息\n2 显示学生信息\n3 查找学生信息\n4 插入学生信息\n5 删除学生信息\n6 成绩计算\n7 按总分降序输出\n0 退出\n");
   printf("（注意：输入班级为1,2,3)\n");
}
void add(STUDENT *p)
{
   int i;
   for(i=0;i<n;i++)
   {
       printf("-------第%d名学生-------\n",i + 1);
       printf("姓名：");
       scanf("%s", p[i].name);
       printf("学号：");
       scanf("%d", &p[i].id);
       printf("班级：");
       scanf("%d", &p[i].class);
       printf("三门课成绩：");

       for(int j=0;j<3;j++)
       {
           scanf("%d",&p[i].score[j]);
       }
       putchar('\n');
   }
   printf("----添加%d名学生的信息成功！----\n", n);
   putchar('\n');
}
void pre(STUDENT* p)//显示学生信息
{
   int i, j;
   printf("学号\t姓名\t班级\t分数1\t分数2\t分数3\t\n");
       for(i=0;i<n;i++)
       {
           printf("%d\t",p[i].id);
           printf("%s\t", p[i].name);
           printf("%d\t", p[i].class);
           for(j=0;j<3;j++)
           {
               printf("%d\t", p[i].score[j]);
           }putchar('\n');
       }
       putchar('\n');
}
void Average_(STUDENT* p, int k)
{
   all(stu);
   STUDENT temp;
   int i, j;
   for(i=0;i<n-1;i++)
       for(j=0;j<n-1-i;j++)
       {if(p[j].av<p[j+1].av)
       {
           temp = p[j];
           p[j] = p[j + 1];
           p[j + 1] = temp;
       }
       }
       if(k==14)
       {
          printf("这是平均分最高学生的信息：\n");
          printf("学号\t姓名\t班级\t分数1\t分数2\t分数3\t平均分\t\n");
          printf("%d\t%s\t%d\t", p[0].id, p[0].name, p[0].class);
          for (j = 0; j < 3; j++)
          {
           printf("%d\t", p[0].score[j]);
          }
          printf("%.1f\t", p[0].av);
          putchar('\n');
        }
       if(k==15)
       {
           printf("这是平均分最低学生的信息：\n");
           printf("学号\t姓名\t班级\t分数1\t分数2\t分数3\t平均分\t\n");
           printf("%d\t%s\t%d\t", p[n-1].id, p[n-1].name, p[n-1].class);
           for (j = 0; j < 3; j++)
           {
               printf("%d\t", p[n-1].score[j]);
           }
           printf("%.1f\t", p[n-1].av);
           putchar('\n');
       }
       printf("------------------------------\n");
       putchar('\n');
}
void search_s(STUDENT* p)
{
   int k,q;
   printf("请输入您要查找的学科科目(输入1或2或3）：\n");
   scanf("%d", &k);
   printf("1.查找该科目最高分\n2.查找该科目最低分\n");
   scanf("%d", &q);
   sl(stu, k, q); printf(" \n");
}
void sl(STUDENT* p, int k,int q)//查找该科目最低或最高分
{
   int i, j;
   STUDENT temp;
   for (i = 0; i < n - 1; i++)
       for (j = 0; j < n - i - 1; j++)
       {
           if (p[j].score[k - 1] > p[j + 1].score[k - 1])
           {
               temp = p[j];
               p[j] = p[j + 1];
               p[j + 1] = temp;
           }
       }
   if (q == 2)
       printf("最低成绩为：%d", p[0].score[k - 1]);
   if (q == 1)
       printf("最高成绩为：%d", p[n-1].score[k - 1]);
   putchar('\n');
}
void sname(STUDENT* p)//按照名字查找学生信息
{
   int i,j,k=0;
   char name[20];
   printf("请输入您要查找学生的姓名：");
   scanf("%s", &name);
   for (i = 0; i < n; i++)
   {
       if (strcmp(name, p[i].name) == 0)
       {
           printf("这是你要查找学生的信息：\n");
           printf("学号\t姓名\t班级\t分数1\t分数2\t分数3\t\n");
           printf("%d\t%s\t%d\t", p[i].id, p[i].name, p[i].class);
           for (j = 0; j < 3; j++)
           {
               printf("%d\t", p[i].score[j]);
           }putchar('\n\n'); break;
       }
       if (strcmp(name, p[i].name) != 0)
       {
           k++;
       }
   }
   if (k == n)
       printf("---------------NOT FOUND--------------\n");
   putchar('\n');

}
void sid(STUDENT* p, int k)//按照学号查找学生信息
{
   int i, j;
   int t = 0;
   for (i = 0; i < n; i++)
   {
       if (p[i].id == k)
       {
           printf("这是该学生的信息：\n");
           printf("学号\t姓名\t班级\t分数1\t分数2\t分数3\t\n");
           printf("%d\t%s\t%d\t", p[i].id, p[i].name, p[i].class);
           for (j = 0; j < 3; j++)
           {
               printf("%d\t", p[i].score[j]);
           }
           putchar('\n'); break;
       }
       if (p[i].id != k)
       {
           t++;
       }
   }
   if (t == n)
       printf("----NOT FOUND----\n");

}
void in(STUDENT* p)//插入学生信息
{
   int i,j ;
   n = n + 1;
   STUDENT temp;
   printf("请输入学生姓名：" );
       scanf("%s", p[n-1].name);
       printf("学号：");
       scanf("%d", &p[n-1].id);
       printf("班级：");
       scanf("%d", &p[n-1].class);
       printf("三门课成绩：");
       for (int j = 0; j < 3; j++)
       {
           scanf("%d", &p[n-1].score[j]);
       }
   printf("----该学生信息输入成功！----\n");
   for (i = 0; i < n-1 ; i++)
   {
       for (j = 0; j < n - i-1 ; j++)
       {
           if (p[j].id < p[j + 1].id)
           {
               temp = p[j];
               p[j] = p[j + 1];
               p[j + 1] = temp;
           }
       }

   }
}
void del(STUDENT* p)
{
   int k;
   while (1)
   {
       printf("1 按照学生姓名删除学生信息\n2 按照学号删除学生信息\n0 返回主菜单\n");
       printf("请输入您的选择：");
       scanf("%d", &k);
       if (k == 0)
           break;
       switch (k)
       {
       case 1:dname(stu);  break;
       case 2:did(stu); break;
       default:
           printf("\nIllegal digital.Try again\n"); break;
       }
   }
}
void dname(STUDENT* p)
{
   int  i, j,k=0;
   char name[20];
   int op;
   printf("请输入您要删除的学生姓名：");
   scanf("%s", &name);
   for (i = 0; i < n; i++)
   {
       if (strcmp(name, p[i].name) == 0)
       {
           printf("这是该学生的信息：\n");
           printf("学号\t姓名\t班级\t分数1\t分数2\t分数3\t\n");
           printf("%d\t%s\t%d\t", p[i].id, p[i].name, p[i].class);
           for (j = 0; j < 3; j++)
           {
               printf("%d\t", p[i].score[j]);
           }
           putchar('\n');
           printf("您确定要删除该学生的信息吗？（1 YES/2 NO)\n");
           printf("请输入您要进行的操作:");
           scanf("%d", &op);
           if (op == 1)
           {
               p[i] = p[i + 1];
               n = n - 1;
               putchar('\n');
               for (j = i; i < n; i++)
               {
                   p[i] = p[i + 1];
               }
               printf("-----------已完成您的操作----------\n");
           }
           if (op == 2)
           {
               printf("-----------已撤销您的操作-----------\n");
           }

       }
       if (strcmp(name, p[i].name) != 0)
       {
           k++;
       }
   }
   if (k == n)
       printf("---------------NOT FOUND--------------\n");
   putchar('\n');
}
void did(STUDENT* p)//删除
{
   int k=0, i, j, number;
   int op;
   printf("请输入您要删除的学生的学号：");
       scanf("%d", &number);
   for (i = 0; i < n; i++)
   {
       if (p[i].id == number)
       {
           printf("这是该学生的信息：\n");
           printf("学号\t姓名\t班级\t分数1\t分数2\t分数3\t\n");
           printf("%d\t%s\t%d\t", p[i].id, p[i].name, p[i].class);
           for (j = 0; j < 3; j++)
           {
               printf("%d\t", p[i].score[j]);
           }
           putchar('\n');
           printf("您确定要删除该学生的信息吗？（1 YES/2 NO)\n");
           printf("请输入您要进行的操作:");
            scanf("%d", &op);
           if (op== 1)
           {
               p[i] = p[i + 1];
               n = n - 1;
               putchar('\n');
               for (j = i; i < n; i++)
               {
                   p[i] = p[i + 1];
               }
               printf("----已完成您的操作----\n");

           }
           if(op==2)
           {
               printf("----已撤销您的操作----\n");
           }

       }
       if (p[i].id != number)
       {
           k++;
       }
   }
   if (k == n)
       printf("----NOT FOUND----\n");
}void all(STUDENT* p)//计算总成绩
{
   int i, j;
   for (i = 0; i < n; i++)
   {
       p[i].total = 0;
       for (j = 0; j < 3; j++)
       {
           p[i].total += p[i].score[j];
       }
   }
   for(i=0;i<n;i++)
   {
       p[i].av = p[i].total / 3.0;
   }
}
#include <stdio.h>

void caverage(STUDENT *p) {
    int class_count[3] = {0, 0, 0}; // 每个班级的学生数
    int sum[3][3] = {0};            // 每个班级每门课的总分
    double average[3][3] = {0.0};   // 每个班级每门课的平均分

    for (int i = 0; i < n; i++) {
        if (p[i].class >= 1 && p[i].class <= 3) { // 确保班级编号有效
            int class_index = p[i].class - 1;    // 班级索引(0对应班级1)
            for (int j = 0; j < 3; j++) {        // 遍历3门课程
                sum[class_index][j] += p[i].score[j];
            }
            class_count[class_index]++;
        }
    }

    for (int c = 0; c < 3; c++) {
        if (class_count[c] > 0) { // 确保有学生数据
            for (int j = 0; j < 3; j++) {
                average[c][j] = (double)sum[c][j] / class_count[c];
            }
        }
    }

    // 输出每班每门课的平均分
    for (int c = 0; c < 3; c++) {
        printf("Class %d:\n", c + 1);
        for (int j = 0; j < 3; j++) {
            printf("  Subject %d average: %.2f\n", j + 1, average[c][j]);
        }
    }
    putchar('\n');
}

void order(STUDENT* p)//按总分降序输出
{
   
   int i, j;
   STUDENT temp;
   all(stu);
   for(i=0;i<n-1;i++)
   {
       for (j = 0; j < n - i - 1; j++)
       {
           if (p[j].total < p[j + 1].total)
           {
               temp = p[j];
               p[j] = p[j + 1];
               p[j + 1] = temp;
           }
       }
   }
   printf("学号\t姓名\t班级\t分数1\t分数2\t分数3\t\n");
   for (i = 0; i < n; i++)
   {
       printf("%d\t", p[i].id);
       printf("%s\t", p[i].name);
       printf("%d\t", p[i].class);
       for (j = 0; j < 3; j++)
       {
           printf("%d\t", p[i].score[j]);
       }
       putchar('\n');
   }
   printf("----------------------------\n");
}
