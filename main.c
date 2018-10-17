#include<stdio.h>
#include<stdlib.h>
#include"all.h"
stu *s;
kc *k;
int main()
{
    printf("\n--------------------------------欢迎使用选课系统！---------------------------------\n");
    int flag;
    printf("\n*****请选择登陆类型 [1]学生    [2]管理员   [3]显示帮助   [0]退出系统: ");
    while(1)
    {
        scanf("%d",&flag);
        if(flag == 0 || flag == 1 || flag == 2) break;
        else printf("error input, please input again\n");
    }
    getchar();
    while(flag)
    {
        if(flag == 1) //学生登录
        {
            s = stu_read();
            k = kc_read();
            char str[15] = {0};
            printf("*****请输入学号: ");
            gets(str);
            int f = found_stu(str);
            int menu;
            if(f) menu = stu_menu();
            else 
            {
                menu = 0;
                printf("not fount %s\n",str);
            }
            while(menu)
            {
                switch(menu)
                {
                    case 1:showall(str); break;
                    case 2:search_cource(); break;
                    case 3:delete_cource(str); break;
                    case 4:add_cource(str); break;
                }
                menu = stu_menu();
            }
            stu_write();
            kc_write();
        }
        else
        {
            s = stu_read();
            k = kc_read();
            char s[11] = {0};
            printf("*****请输入管理员密码：");
            gets(s);
            int status = manager_login(s);
            if(status)
            {
                printf("\n--------------------------------管理员登录成功！---------------------------------\n");
                int menu = manager_menu();
                while(menu)
                {
                    switch(menu)
                    {
                        case 1: add_stu(); break;
                        case 2: delete_stu(); break;
                        case 3: modify_stu(); break;
                        case 4: add_kc(); break;
                        case 5: delete_kc(); break;
                        case 6: modify_kc(); break;
                        case 7: showall_stu_kc(); break;
                        case 8: modify_password(); break;
                    }
                    menu = manager_menu();
                }
                stu_write();
                kc_write();
            }
        }
        printf("\n*****请选择登陆类型 [1]学生    [2]管理员   [3]显示帮助   [0]退出系统: ");
        while(1)
        {
            scanf("%d",&flag);
            if(flag == 0 || flag == 1 || flag == 2) break;
            else printf("error input, please input again\n");
        }
        getchar();
    }
    return 0;
}
