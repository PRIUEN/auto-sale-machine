#include "project.h"

//显示加减号
//cart_head: 购物车链表头节点，pos:显示在屏幕的商品的结构体指针数组
void plus_minus(struct doublelist *cart_head,struct doublelist *pos[4])
{
    for(int k=0;k<4;k++)
        flag[k] = 0;
    int x[4] = {50,240,430,620};    //显示减号的坐标
    int y = 330;
    
    if(cart_head->next == NULL)
        return;
    
    
    struct doublelist *cart_p = cart_head->next;
    
    while(cart_p!=NULL)            //判断显示的四个商品有没有在购物车链表中
    {
        for(int i=0; pos[i]!=NULL&&i<4; i++)
        {
            if(strcmp(pos[i]->com_name,cart_p->com_name) == 0)  //在购物车中就显示加减号和选购数量
            {
                Show_Any_24_Bmp("/mnt/udisk/vending/bg_pic/minus.bmp",x[i],y);
                Show_Any_24_Bmp("/mnt/udisk/vending/bg_pic/plus.bmp",x[i]+80,y);
                char str[4] = {0};
                sprintf(str,"%d",cart_p->com_amount);
                dis_font(str,30,x[i]+50,y,30,50);
                flag[i] = 1;
            }
            if(pos[i]->com_amount == 0)
                 dis_font("库存不足",30,x[i],y,100,30);
        }
        cart_p = cart_p->next;
    }

}

//添加到购物车
void add_cart(struct doublelist *p)
{
   
    if(p->com_amount > 0)
    {    
        int f = 0;
        struct doublelist *q = cart_LL->next;
        while(q != NULL)
        {   //购物车已存在该商品则数量加一
            if(strcmp(q->com_name,p->com_name) == 0)
            { f++;   break; }   
            q = q->next;
        }
        if(f == 0)  //不存在则添加到购物车
            {list_insert_tail(cart_LL,p->com_name,p->com_price,1);}
        else if(q->com_amount == p->com_amount)
            printf("已达到最大数量！\n");
        else
            q->com_amount++;    
    }
    else
        printf("已售罄！");
}

//从购物车移除
void remove_cart(struct doublelist *pos)
{   
    struct doublelist *q = cart_LL->next;
    while(q != NULL)
    {
        if(strcmp(q->com_name,pos->com_name) == 0)
        { q->com_amount--;  break; }   
        q = q->next;
    }
    if(q->com_amount == 0)    //数量等于0时从购物车删除
    {
        list_delete(cart_LL,pos->com_name);
        Show_Any_24_Bmp("/mnt/udisk/vending/bg_pic/plus_minus.bmp",0,328);
        plus_minus(cart_LL,p);
    }    
  
}

//加减号触摸
void plus_minus_touch()
{
    if(flag[0] == 1)
    {
        if(P_C_I.touch_x>50 && P_C_I.touch_x<100 && P_C_I.touch_y>330 && P_C_I.touch_y<380)//1加减号
        {
            remove_cart(p[0]);printf("移除\n");
        }
        if(P_C_I.touch_x>130 && P_C_I.touch_x<160 && P_C_I.touch_y>330 && P_C_I.touch_y<380)
        {
            add_cart(p[0]);printf("添加\n");
        }
    }

    if(flag[1] == 1)
    {
        if(P_C_I.touch_x>240 && P_C_I.touch_x<290 && P_C_I.touch_y>330 && P_C_I.touch_y<380)//2加减号
        {
            remove_cart(p[1]);printf("移除\n");
        }
        if(P_C_I.touch_x>320 && P_C_I.touch_x<370 && P_C_I.touch_y>330 && P_C_I.touch_y<380)
        {
            add_cart(p[1]);printf("添加\n");
        }
    }

    if(flag[2] == 1)
    {
        if(P_C_I.touch_x>430 && P_C_I.touch_x<480 && P_C_I.touch_y>330 && P_C_I.touch_y<380)//3加减号
        {
            remove_cart(p[2]);printf("移除\n");
        }
        if(P_C_I.touch_x>510 && P_C_I.touch_x<560 && P_C_I.touch_y>330 && P_C_I.touch_y<380)
        {
            add_cart(p[2]);printf("添加\n");
        }
    }   

    if(flag[3] == 1)
    {
        if(P_C_I.touch_x>620 && P_C_I.touch_x<670 && P_C_I.touch_y>330 && P_C_I.touch_y<380)//4加减号
        {
            remove_cart(p[3]);printf("移除\n");
        }
        if(P_C_I.touch_x>700 && P_C_I.touch_x<750 && P_C_I.touch_y>330 && P_C_I.touch_y<380)
        {
            add_cart(p[3]);printf("添加\n");
        }
    }   
}

//结算界面
void settlement()
{
    Show_Any_24_Bmp("/mnt/udisk/vending/bg_pic/settlement.bmp",0,0);

    int ly[10] = {130,160,190,220,250,280,310,340,370,400};    //结算界面商品显示的y坐标
    float sum = 0;   
    struct doublelist *ptr = cart_LL->next;
    dis_font("已选择商品：",30,73,95,150,30);
    //循环按行显示已选购的商品数量信息
    for(int i=0; ptr != NULL&&i<10; i++)     
    {
        sum += ptr->com_amount * ptr->com_price;
        char buf[100] = {0};
        sprintf(buf,"%s    单价:%.1f    X%d",ptr->com_name,ptr->com_price,ptr->com_amount);
        dis_font(buf,30,73,ly[i],400,30);
        ptr = ptr->next;
    }
    //显示总价
    char buf2[16] = {0};
    sprintf(buf2,"总计:￥%.1f",sum);
    dis_font(buf2,40,532,310,250,40);
    while(1)
    {
        Get_Touch_X_Y();
        if(touch.type == EV_KEY && touch.code == BTN_TOUCH && touch.value == LEAVE)
        {
            if(P_C_I.touch_x>533 && P_C_I.touch_x<728 && P_C_I.touch_y>76 && P_C_I.touch_y<261) //二维码结算
            {
                reduce_from_comm();
                dis_font("结算成功！",50,300,215,200,50);
                sleep(2);
                clear_list(cart_LL);
                //显示主界面
                Show_Any_24_Bmp("/mnt/udisk/vending/bg_pic/main.bmp",0,0);
                return;
            }
            if(P_C_I.touch_x>73 && P_C_I.touch_x<160 && P_C_I.touch_y>20 && P_C_I.touch_y<75) //点击返回
            {
                Show_Any_24_Bmp("/mnt/udisk/vending/bg_pic/main.bmp",0,0);
                return;
            }
        }
    }
}

//从库存中减少与购物车选中相同商品的数量
void reduce_from_comm()
{
    struct doublelist *comm_p = C_LL->next;  //库存
    struct doublelist *cart_p = cart_LL->next;  //购物车

    while(cart_p != NULL)
    {
        while(comm_p != NULL)
        {
            if(strcmp(cart_p->com_name,comm_p->com_name) == 0)
            {
                comm_p->com_amount -= cart_p->com_amount;
                break;
            }
            comm_p = comm_p->next;
        }
        cart_p = cart_p->next;
    }
}

