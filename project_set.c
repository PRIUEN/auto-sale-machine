#include "project.h"


int Pro_Init()
{
    printf("项目初始化成功！\n");
    C_LL = list_init();
    cart_LL = list_init();
    read_txt(C_LL);

    list_show(C_LL);
    
    P_C_I.lcd = open(LCD_DEV_PATH,O_RDWR);//打开fb0
    P_C_I.ts  = open(TOUCH_DEV_PATH,O_RDONLY);//打开event0
    P_C_I.mmap_start = mmap(NULL,MAP_LEN,MAP_PROT,MAP_SHARED,P_C_I.lcd,MAP_OFFSET);//映射内存
    if(P_C_I.lcd == -1 || P_C_I.ts == -1 || P_C_I.mmap_start == MAP_FAILED)
    {
        perror("项目初始化失败！\n");
        return -1;
    }
//判断管道存不存在
    if(access(FIFO_PATH,F_OK))
    {   
        umask(0000);
        mkfifo(FIFO_PATH,0777);
    }

    P_C_I.fifo_fd = open(FIFO_PATH,O_RDWR);
    if(P_C_I.fifo_fd == -1)
    {
        perror("打开管道失败！\n");
        return -1;
    }

    int bmp = open("/root/myuser/vending/bg_pic/main.bmp",O_RDONLY); //打开图片
    if(bmp == -1)
    {
        perror("打开图片失败!\n");
        return -1;
    }

   

    int w,h;
    lseek(bmp,18,SEEK_SET);
    read(bmp,&w,4);
    read(bmp,&h,4);

    printf("主界面的w:%d---h:%d\n",w,h);

    

    lseek(bmp,54,SEEK_SET);
    read(bmp,P_C_I.main_bc,w*h*3);

    Clean_Lcd();

    return 0;
}


int Show_Any_24_Bmp(const char * bmp_path,int zs_x,int zs_y)//可以显示任意一张图片
{
    int * new_p =  NULL;
    int bmp = open(bmp_path,O_RDONLY);
    if(bmp == -1)
    {
        perror("打开图片失败！\n");
        bmp = open("/mnt/udisk/vending/bg_pic/no_pic.bmp",O_RDONLY);
    }

    //先读图片的长和宽
    int w,h;

    lseek(bmp,18,SEEK_SET);
    
    read(bmp,&w,4);
    read(bmp,&h,4);
    //printf("图片的 w:%d---h:%d\n",w,h);

    char rgb[w*h*3];
    lseek(bmp,54,SEEK_SET);

    int ret = 4 - w*3 %4;
    if(ret == 4)
    {  
        read(bmp,rgb,w*h*3);
    }
    else
    {
        for(int i=0;i<h;i++)
        {
            read(bmp,&rgb[3*w*i],w*3);
            lseek(bmp,ret,SEEK_CUR);
        }
        
    }



    if(zs_x == -1 && zs_y == -1)
    {
        //局中显示
        new_p = P_C_I.mmap_start+ 800*(240-h/2)+(400-w/2);
    }
    
    else
    {
        new_p = P_C_I.mmap_start + 800*zs_y+zs_x;//保证指针变量的稳定性，要备用一个新的指针
    }



    int x,y,n;
    for(y=0,n=0; y<h; y++)
    {
        for(x=0; x<w; x++,n+=3)
        {
            *(new_p + 800*(h-1-y)+x) = rgb[n] <<0 | rgb[n+1] <<8 | rgb[n+2] <<16; 
        }
    }

    close(bmp);
    return 0;
}


int Get_Touch_X_Y()
{

    read(P_C_I.ts,&touch,sizeof(touch));//touch里面已经有x和y,touch比喻成🥚 = 蛋黄x+蛋白y

    //读取出来的x y 压力值等信息存放在哪里？ 输入子系统（系统里面的一份代码）

    //筛选 X
    if(touch.type == EV_ABS && touch.code == ABS_X)  P_C_I.touch_x = touch.value;
    if(touch.type == EV_ABS && touch.code == ABS_Y)  P_C_I.touch_y = touch.value;
    
    return 0;
}




int Clean_Lcd() //清屏
{
    int x,y;

    for(y=0; y<480; y++)
    {
        for(x=0; x<800; x++)
        {
            *(P_C_I.mmap_start+800*y+x) = 0x00000000;
        }
    }

    return 0;
}

int Pro_Free()
{
    printf("项目释放资源成功！\n");

    close(P_C_I.lcd);
    close(P_C_I.ts);
    munmap(P_C_I.mmap_start,MAP_LEN);

    return 0;
}

int Send_Cmd(char * cmd) //终端发送指令的函数
{
    write(P_C_I.fifo_fd,cmd,strlen(cmd));
    
    return 0;
}