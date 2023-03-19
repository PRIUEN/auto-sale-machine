//判断有没有旗子
#ifndef PROJECT_H_
#define PROJECT_H_ //插旗

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <dirent.h>
#include <string.h>
#include <pthread.h>
#include <linux/input.h>

#include "font.h"   //字库头文件

#define  LCD_DEV_PATH   "/dev/fb0"
#define  TOUCH_DEV_PATH "/dev/input/event0"
#define  FIFO_PATH      "/my_fifo"
#define  MAP_LEN        800*480*4
#define  MAP_PROT       PROT_READ | PROT_WRITE 
#define  MAP_OFFSET     0
#define  LEAVE          0



struct pro_common_inf
{
    int lcd;//fb0的标签
    int ts;// event0的标签
    int fifo_fd;
    int * mmap_start;
    int touch_x,touch_y; 
    char main_bc[800*480*3];          
}P_C_I; 

struct doublelist
{
    char com_name[512];//数据域
    float com_price;
    int com_amount;
    struct doublelist * prev,* next;
}*C_LL, *cart_LL;
//C_LL:商品库存链表,cart_LL:购物车链表

struct input_event touch;  //触摸屏结构体
struct doublelist *p[4];  //结构体指针数组，分别指向屏幕显示的4个商品
FILE * txt_file;
int flag[4] ;  //判断当前页面商品是否加入购物车的标志位

/*--------------------------------- main.c ---------------------------------*/
int main_ctrl();


/*---------------------------------  project_set.c ---------------------------------*/
int Pro_Init();
int Pro_Free();
int Show_Any_24_Bmp(const char * bmp_path,int zs_x,int zs_y);
int Get_Touch_X_Y();
int Clean_Lcd();
int Send_Cmd(char * cmd);


/*--------------------------------- list.c ---------------------------------*/
struct doublelist *list_init();
int list_insert_tail(struct doublelist *head,char *name,float price,int amount);
int list_delete(struct doublelist *head,char *name);
int list_show(struct doublelist *head);
int free_list(struct doublelist *p);
int clear_list(struct doublelist *list);

/*---------------------------------  insert_txt.c ---------------------------------*/
int read_txt(struct doublelist *list);
int insert_txt(struct doublelist *list);

/*---------------------------------  cart.c ---------------------------------*/
void plus_minus(struct doublelist *cart_head,struct doublelist *pos[4]);
void add_cart(struct doublelist *p);
void remove_cart(struct doublelist *p);
void plus_minus_touch();
void settlement();
void reduce_from_comm();

/*---------------------------------  dis_font.c ---------------------------------*/
struct LcdDevice *init_lcd(const char *device);
int dis_font(char *buf,int size,int fx,int fy,int bord_w,int bord_h);

/*---------------------------------  admin.c ---------------------------------*/
void login();
void Modify_inventory();
void add_dele_inventory();
void add_com();
void dele_com();

#endif