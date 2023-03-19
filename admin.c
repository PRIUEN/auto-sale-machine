#include "project.h"

//主界面
void login()
{   
    
    int f = 0;
    char pass[32] = {0};
    printf("请输入密码:");
    scanf("%s",pass);
    printf("%s",pass);
    if(strcmp(pass,"123456") == 0)
    {
        printf("密码正确！进入管理员系统\n");
        f = 1;
    }
        
    else
        printf("密码错误！管理员系统进入失败\n");
        Show_Any_24_Bmp("/mnt/udisk/vending/bg_pic/main.bmp",0,0); 
 
    if(f == 1)
    {
        
        while(1)
        {
            int a = 0;
            printf("=================================\n");
            printf("==============主菜单=============\n");
            printf("=           请输入数字          =\n");
            printf("=           1.显示库存          =\n");
            printf("=           2.修改库存          =\n");
            printf("=           3.添加或下架商品    =\n");
            printf("=           4.退出并保存        =\n");
            scanf("%d",&a);

            switch (a)
            {
            case 1 : list_show(C_LL);
                break;
            case 2 : Modify_inventory();
                break;
            case 3 : add_dele_inventory();
                break;
            case 4 : Show_Any_24_Bmp("/mnt/udisk/vending/bg_pic/main.bmp",0,0); 
                     printf("退出管理员模式\n");
                return;

            default: printf("输入错误！请重新输入：\n");
                break;
            }
        }
    }
    
}


//修改商品
void Modify_inventory()
{
    int f2 = 0;
    char namebuf[100];
    printf("=================================\n");
    printf("请输入需要修改的商品名称：\n");
    scanf("%s",namebuf);

    char *ret;
    struct doublelist *bp = C_LL->next;
    while(bp != NULL)
    {
        ret = strstr(bp->com_name,namebuf);
        if(ret == NULL)
            bp = bp->next;
        else
        {
            printf("商品为：%s\n",bp->com_name);
            printf("请输入修改后的价格和数量：\n");
            scanf("%f %d",&bp->com_price,&bp->com_amount);
            f2 = 1;
            printf("修改成功！\n"); break;
        }
    }
    if(f2 == 0)
        printf("没有该商品\n");
    
}

//添加下架商品界面
void add_dele_inventory()
{
    while(1)
    {
        printf("=================================\n");
        printf("==========添加或下架商品=========\n");
        printf("=           请输入数字          =\n");
        printf("=           1.显示库存          =\n");
        printf("=           2.添加商品          =\n");
        printf("=           3.下架商品          =\n");
        printf("=           4.退出              =\n");

        int a2;
        scanf("%d",&a2);
        switch (a2)
        {
        case 1 : list_show(C_LL);
            break;
        case 2 : add_com();
            break;
        case 3 : dele_com();
            break;
        case 4 : insert_txt(C_LL);
            return;
        default: printf("输入错误！请重新输入：\n");
            break;
        }
    }
}


//添加商品
void add_com()
{
    char namebuf3[100];
    float price;
    int am;
    printf("=================================\n");
    printf("请输入需要添加的商品名称：\n");
    scanf("%s",namebuf3);getchar();
    printf("请输入需要添加的商品单价：\n");
    scanf("%f",&price);getchar();
    printf("请输入需要添加的商品数量：\n");
    scanf("%d",&am);getchar();

    list_insert_tail(C_LL,namebuf3,price,am);
    
    printf("添加成功！\n");

}



//下架商品
void dele_com()
{
    int f3 = 0;
    char namebuf2[100];
    printf("=================================\n");
    printf("请输入需要下架的商品名称：\n");
    scanf("%s",namebuf2);

    char *ret2;
    struct doublelist *bp2 = C_LL->next;
    while(bp2 != NULL)
    {
        ret2 = strstr(bp2->com_name,namebuf2);
        if(ret2 == NULL)
            bp2 = bp2->next;
        else
        {
            f3 = 1;
            int b;
            printf("=================================\n");
            printf("商品为：%s\n",bp2->com_name);
            printf("输入1确认下架，输入2取消\n");
            scanf("%d",&b);
            if(b==1)
            {   
                list_delete(C_LL,bp2->com_name);
                break;
            }
            else
                break;
        }
    }
    if(f3 == 0)
        printf("没有该商品\n");
    
}

