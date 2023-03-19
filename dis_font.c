#include "project.h"

//初始化Lcd
struct LcdDevice *init_lcd(const char *device)
{
	//申请空间
	struct LcdDevice* lcd = malloc(sizeof(struct LcdDevice));
	if(lcd == NULL)
	{
		return NULL;
	} 

	//1打开设备
	lcd->fd = open(device, O_RDWR);
	if(lcd->fd < 0)
	{
		perror("open lcd fail");
		free(lcd);
		return NULL;
	}
	
	//映射
	lcd->mp = mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcd->fd,0);

	return lcd;
}

int dis_font(char *buf,int size,int fx,int fy,int bord_w,int bord_h)
{
	
    //初始化Lcd
	//struct LcdDevice* lcd = init_lcd("/dev/fb0");
			
	//打开字体	
	font *f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");
	  
	//字体大小的设置
	fontSetSize(f,size);  //字体大小20，可以人为修改
	
	
	//创建一个画板（点阵图）宽是200个像素，高是50个像素
	bitmap *bm = createBitmapWithInit(bord_w,bord_h,4,getColor(0,48,48,48)); //也可使用createBitmapWithInit函数，改变画板颜色
	//bitmap *bm = createBitmap(288, 100, 4);
	
	
	//将字体写到点阵图上 0,0表示汉字在画板的左上角显示          
	fontPrint(f,bm,0,0,buf,getColor(0,255,255,255),0);
	                             // A  B  G R
	
	
	//把字体框输出到LCD屏幕上  参数0,0表示画板显示的坐标位置
	show_font_to_lcd(P_C_I.mmap_start,fx,fy,bm);

	
	//关闭字体，关闭画板
	fontUnload(f);
	destroyBitmap(bm);
	
}
