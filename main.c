#include "project.h"


int main_ctrl()
{
    int n;
    int y = 100;
    int x[4] = {40,230,420,610};
    
    char path[100];
    //struct doublelist *p[4];
    //显示主界面
    Show_Any_24_Bmp("/mnt/udisk/vending/bg_pic/main.bmp",0,0);

    p[0]=C_LL->next;
lb:
    for(n=1; p[n-1]->next!=NULL && n<4;  n++)
    {
        p[n] = p[n-1]->next;
    }
    // for(int i=0;i<4;i++)
    //     printf("%s\n",p[i]->com_name);

    if(n != 4)
    {
        for(int j=n; j<4; j++)
            p[j] = NULL;
        Show_Any_24_Bmp("/mnt/udisk/vending/bg_pic/main.bmp",0,0);       
    }

    
    //显示商品图片与信息
    for(int i=0;i<n;i++)
    {
        sprintf(path,"/mnt/udisk/vending/commodity/%s.bmp",p[i]->com_name);
        Show_Any_24_Bmp(path,x[i],y);
        //显示商品名称
        dis_font(p[i]->com_name,20,x[i],250,150,20);
        //显示价格
        char str[4] = {0};
        sprintf(str,"￥%.1f",p[i]->com_price);
        dis_font(str,35,x[i],270,150,35);
        //显示剩余数量
        char str2[4] = {0};
        sprintf(str2,"剩余数量:%d",p[i]->com_amount);
        dis_font(str2,20,x[i],305,150,20);

        bzero(path,100);
    }

    
    while(1)
    {  
        Get_Touch_X_Y();
        plus_minus(cart_LL,p);
        //判断手是否离开触摸屏leave
        if(touch.type == EV_KEY && touch.code == BTN_TOUCH && touch.value == LEAVE)
        {
            
            if(P_C_I.touch_x>50 && P_C_I.touch_x<190 && P_C_I.touch_y>100 && P_C_I.touch_y<250)//第一个商品
            {
                if(p[0]!=NULL)
                    printf("你点的是%s \n",p[0]->com_name);
                add_cart(p[0]);
                             
            }
            if(P_C_I.touch_x>240 && P_C_I.touch_x<380 && P_C_I.touch_y>100 && P_C_I.touch_y<250)//第二个商品
            {
                if(p[1]!=NULL)
                    printf("你点的是%s \n",p[1]->com_name);
                add_cart(p[1]);
                
            }
            if(P_C_I.touch_x>430 && P_C_I.touch_x<570 && P_C_I.touch_y>100 && P_C_I.touch_y<250)//第三个商品
            {
                if(p[2]!=NULL)
                    printf("你点的是%s \n",p[2]->com_name);
                add_cart(p[2]);
                
            }
            if(P_C_I.touch_x>620 && P_C_I.touch_x<760 && P_C_I.touch_y>100 && P_C_I.touch_y<250)//第四个
            {
                if(p[3]!=NULL)
                    printf("你点的是%s \n",p[3]->com_name);
                add_cart(p[3]);
                
            }
            if(P_C_I.touch_x>0 && P_C_I.touch_x<150 && P_C_I.touch_y>400 && P_C_I.touch_y<480)//上一页
            {
                if(p[0]->prev->prev != NULL)
                {
                    p[0] = p[0]->prev->prev->prev->prev;
                    Show_Any_24_Bmp("/mnt/udisk/vending/bg_pic/plus_minus.bmp",0,328);
                    goto lb;
                }
                else
                    printf("没有上一页了！\n");
            }
            if(P_C_I.touch_x>650 && P_C_I.touch_x<800 && P_C_I.touch_y>400 && P_C_I.touch_y<480)//下一页
            {
                if(p[3] != NULL && p[3]->next != NULL)
                {
                    p[0] = p[3]->next;
                    Show_Any_24_Bmp("/mnt/udisk/vending/bg_pic/plus_minus.bmp",0,328);
                    goto lb;
                }
                else
                    printf("没有下一页了！\n");
            }           
            if(P_C_I.touch_x>710 && P_C_I.touch_x<800 && P_C_I.touch_y>0 && P_C_I.touch_y<80)//结算
            {
                list_show(cart_LL);
                settlement();
                goto lb;
            }
            if(P_C_I.touch_x>610 && P_C_I.touch_x<700 && P_C_I.touch_y>0 && P_C_I.touch_y<80)//清空
            {
                clear_list(cart_LL);
                Show_Any_24_Bmp("/mnt/udisk/vending/bg_pic/plus_minus.bmp",0,328);
                
            }

            if(P_C_I.touch_x>0 && P_C_I.touch_x<100 && P_C_I.touch_y>0 && P_C_I.touch_y<80)//管理员按钮
            {
                dis_font("进入管理员模式",100,0,0,800,480);
                login();
                p[0]=C_LL->next;
                goto lb;
            }
            plus_minus_touch();

        }
    }
}




int main()
{
    Pro_Init();
    main_ctrl();


     insert_txt(C_LL);
    Pro_Free();

    return 0;
}