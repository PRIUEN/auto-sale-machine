#include "project.h"

    
//写入txt文件
int insert_txt(struct doublelist *list)
{
    txt_file= fopen("/mnt/udisk/vending/info.txt","w+");   
    if (txt_file==NULL)
    {
        perror("打开txt文件失败！\n");
        return -1;
    }

    struct doublelist *p = list->next;
    while(p != NULL)
    {
        fprintf(txt_file,"%s #%.1f #%d\n",p->com_name,p->com_price,p->com_amount);
        p = p->next;
    }
    fclose(txt_file);
    return 0;
}

//从txt文件中读取
int read_txt(struct doublelist *list)
{
    txt_file= fopen("/mnt/udisk/vending/info.txt","r+");   
    if (txt_file==NULL)
    {
        perror("打开txt文件失败！\n");
        return -1;
    }


    struct doublelist *p = list;
    char buf[50];

    while(fgets(buf,50,txt_file) != NULL)
    {
        list_insert_tail(list,"0",0,0);
        p = p->next;
        sscanf(buf,"%s #%f #%d",p->com_name,&(p->com_price),&(p->com_amount));  //格式化读取
        bzero(buf,50);
        
    }

    fclose(txt_file);
    return 0;
}