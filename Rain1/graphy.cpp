#include<graphics.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<pthread.h>   //���߳�
#include<stdlib.h>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"comctl32.lib")
#pragma comment(lib,"pthreadVC2.lib")  //ʹ�������ʱ����������
  


POINT point;           //windows�Զ���Ľṹ��  ��
HWND hwnd;             //���ھ��
int sleeptime;         //��������ʱ��


//������###�ӿڻ�ȫ�ֱ��###����λ�ã������ﶨ����ĸ���ȫ�ֲ���
//---------------------------------
#define MAX 500	   //��ε�����
#define STEP 70   //��εĲ���ֵ��ˢ��ʱ���������ǰ���ľ��룩
#define WID 1      //����ߵĿ�ȣ��������ң�
#define LEN  16    //����ߵĳ��ȣ��������£�
#define HZ  500   //���ƴ��׸��ʵ���ֵ����ֵԽ�󣬴��׵ĸ���Խ�ͣ�
int TAG = 0;       //��ʼ��һ��tag���ж����Ƿ��Ѿ���ʼ����
#define NUM 200  //ת������������Ƶ�֡������ֵԽ�󣬷���ı��Ƶ��Խ��
int direction = 1;     //��ʼ����Ľ��䷽�򣬼����ƫ�Ʒ���0,1,2��
//---------------------------------

//�����ǽṹ�嶨��λ��
//---------------------------------
typedef struct Rain { 
	COLORREF color;//��ε���ɫ 
	//��εĻ�������Ĳ��� 
	int left; 
	int top; 
	int right; 
	int bottom; 
	int Drop_tag;
	int CLEAN_TG;      //�ж��Ƿ�Ӧ�������   ����ʱ�Ǹ����ɣ��Ͳ��������
	int ID;            //�ж����������ʽ
	int times;         //�����ˮ���������Ĵ�С��������
	int direction;     //������䷽��ȡ��0�����㣬1��ֱ�£�2�����㣩
	int trans;         //���Ʊ�ǣ���Ǵ���λ��ƺ��´�λ���Ƿ�ת��
}Rain;
Rain graph[MAX];
typedef struct Leaf{
	int left;
	int top;
	int right;
	int bottom;
	int x1,y1,x2,y2,x3,y3,x4,y4;
	COLORREF fillcolor;
	COLORREF linecolor;
}Leaf;
typedef struct Thunder
{
    int x0, y0;//����λ��
    int x1, y1;
    int x2, y2;
    int x3, y3;
    int x4, y4;
    int x5, y5;
    int x6, y6;
    int x7, y7;
    int x8, y8;
    int x9, y9;
}Thunder;


//�������� 
void pool() 
{ 
	int R,G,B;
	R=0;
	G=0;
	B=108;
	setfillcolor(RGB(R,G,B));
	setcolor(RGB(R,G,B));
	fillrectangle(0, 650, 1000, 800);
}

//Rain
void InitRain(int i, int de ,int tr)
{
	int R,G,B;
	graph[i].left = rand()%1000;
	if(TAG==0)
	{	
		graph[i].top = rand()%(650-STEP);
	}
	else	
		graph[i].top = rand()%STEP;
	if(tr==1)
	{
		if(de == 0)
		{
			graph[i].right = graph[i].left;
			graph[i].direction = 1;
		}
		else if(de == 1)
		{
			graph[i].right = graph[i].left + LEN;
			graph[i].direction = 2;
		}
		else if(de == 2)
		{
			graph[i].right = graph[i].left - LEN;
			graph[i].direction = 0;
		}
	}
	else if(tr==0)
	{
		if(de == 0)
			graph[i].right = graph[i].left - LEN;
		else if(de == 1)
			graph[i].right = graph[i].left;
		else if(de == 2)
			graph[i].right = graph[i].left + LEN;
	}
	graph[i].bottom = graph[i].top + LEN;
	R = rand()%255;
	G = rand()%255;
	B = rand()%255;
	graph[i].color = RGB(R,G,B);
	graph[i].Drop_tag = 0;//�˱��˵����δ�������
}

//��ͬʱ�����λ�ú���
void Rain_quiet(int i)
{
	int width = 140-STEP;
	int midx,midy;   //����������ʱ���м�ֵ
	int st;
	// ����ԭ��
	if(graph[i].CLEAN_TG)
	{
		int de,tr;
		if(graph[i].Drop_tag==1)     //˵���ϸ������Ȧ
		{
			int x1,x2,y1,y2;
			setcolor(RGB(0,0,108));
			x1 = graph[i].right-6*graph[i].times;
			x2 = graph[i].right+6*graph[i].times;
			y1 = graph[i].bottom-3*graph[i].times;
			y2 = graph[i].bottom+3*graph[i].times;
			ellipse (x1,y1,x2,y2);
		}
		else                         //�ϸ��������,����ʱע��ֲ���
		{ 
			if(graph[i].ID==2)
			{
				int next;
				st = 649-graph[i].top;
				midy = 649;
				if(graph[i].direction==0)
				{
					midx = graph[i].left -st;
					next = midx-1;
				}
				else if(graph[i].direction == 1)
				{
					midx = graph[i].left;
				    next = midx;
				}
				else if(graph[i].direction == 2)
				{
					midx = graph[i].left + st;
					next = midx +1;
				}
				setcolor(0);
				line(graph[i].left,graph[i].top,midx,midy); 
				setcolor(RGB(0,0,108)); 
				line(next,midy+1,graph[i].right,graph[i].bottom);
			}
			else if(graph[i].ID==1)
			{
				setcolor(RGB(0,0,108));
				line(graph[i].left,graph[i].top,graph[i].right,graph[i].bottom);
			}
			else 
			{ 
				setcolor(0);
				line(graph[i].left,graph[i].top,graph[i].right,graph[i].bottom);
			}
		}
 
		// ������λ��
		if(graph[i].Drop_tag==1)
		{
			de = graph[i].direction;
			tr = graph[i].trans;
			InitRain(i,de,tr);
		}
		else if(graph[i].trans==1)
		{   
			if(graph[i].direction==0)
			{
				graph[i].right = graph[i].left;
				graph[i].direction = 1;
			}
			else if(graph[i].direction==1)
			{
				graph[i].right = graph[i].left + LEN;
				graph[i].direction = 2;
			}
			else if(graph[i].direction==2)
			{
				graph[i].right = graph[i].left - LEN;
				graph[i].direction = 0;
			}
		}
		else if(graph[i].trans == 0)
		{
			graph[i].top += STEP;
			graph[i].bottom += STEP;
			if(graph[i].direction == 0)
			{
				graph[i].left = graph[i].left-STEP;
				graph[i].right = graph[i].right-STEP;
			}
			else if(graph[i].direction == 2)
			{
				graph[i].left += STEP;
				graph[i].right += STEP;
			}	
		}
		

		if (graph[i].bottom >= 660+(rand()%width))   //�������λ�����
		{
			graph[i].Drop_tag = 1 ;  //���ñ�ǣ���ˮ���
		}
		if(graph[i].right<0)
		{
			graph[i].left += 1000;
			graph[i].right = graph[i].left - LEN;
		}
		else if(graph[i].right>1000)
		{
			graph[i].left += -1000;
			graph[i].right = graph[i].left + LEN;
		}
		if(graph[i].bottom>=650) // ����������߱��
		{
			if(graph[i].top<650) graph[i].ID=2;  //���������
			else if(graph[i].top>=650) graph[i].ID =1;  //ֻһ��������ó���ɫ���
			else graph[i].ID = 0;   //���������ȫ��,�ú�ɫ���
		}
		else graph[i].ID=0;
	}
	// ��new
	if(graph[i].Drop_tag==1)   //˵����ʱ����ˮ״̬����ԲȦ
	{
		int x1,x2,y1,y2;
		int times = rand()%3+1;
		graph[i].times = times;
		setcolor(graph[i].color);
		x1 = graph[i].right-6*times;
		x2 = graph[i].right+6*times;
		y1 = graph[i].bottom-3*times;
		y2 = graph[i].bottom+3*times;
		ellipse (x1,y1,x2,y2);
	}
	else
	{
		setfillcolor(graph[i].color);//��������ɫ(�����) 
		setlinecolor(graph[i].color);//��������ɫ(�����) 
		line(graph[i].left,graph[i].top,graph[i].right,graph[i].bottom);
	}
}

//Thunder
void thunder()
{
    int x = rand() % 700;// +20;
    int y = rand() % 60;//+10;
    int stepx = rand() % 2+1;
	int R,G,B;
    Thunder one;
    one.x0 = x + 0 * stepx; one.y0 = y + 0 * stepx;
    one.x1 = x + 120 * stepx; one.y1 = y + 80 * stepx;
    one.x2 = x + 100 * stepx; one.y2 = y + 120 * stepx;
    one.x3 = x + 140 * stepx; one.y3 = y + 160 * stepx;
    one.x4 = x + 100 * stepx; one.y4 = y + 200 * stepx;
    one.x5 = x + 160 * stepx; one.y5 = y + 280 * stepx;
    one.x6 = x + 80 * stepx; one.y6 = y + 200 * stepx;
    one.x7 = x + 100 * stepx; one.y7 = y + 160 * stepx;
    one.x8 = x + 60 * stepx; one.y8 = y + 140 * stepx;
    one.x9 = x + 80 * stepx; one.y9 = y + 80 * stepx;
    POINT thunder[] = {
        { one.x0,one.y0 },
        { one.x1,one.y1 },
        { one.x2,one.y2 },
        { one.x3,one.y3 },
        { one.x4,one.y4 },
        { one.x5,one.y5 },
        { one.x6,one.y6 },
        { one.x7,one.y7 },
        { one.x8,one.y8 },
        { one.x9,one.y9 },
    };
	
	R=255;                    //����ʱ��Ʊ�������
	G=255;
	B=255;
	setfillcolor(RGB(R,G,B));
	setcolor(RGB(R,G,B));
	fillrectangle(0,0,1000,650);
	R=0;                    //����ʱ��������
	G=206;
	B=209;
	setfillcolor(RGB(R,G,B));
	setcolor(RGB(R,G,B));
	fillrectangle(0,650,1000,800);

	setpolyfillmode(WINDING);
    setfillcolor(RGB(205,173,0));
    solidpolygon(thunder, 10);//����������ڻ����Ķ���Σ��ޱ߿򣩡�void solidpolygon( const POINT *points, int num);������points ÿ��������꣬����Ԫ�ظ���Ϊ num���ú������Զ����Ӷ������β��num����ζ���ĸ�����
	Sleep(100);
    clearpolygon(thunder, 10);
	clearrectangle(0,0,1000,650);
	R=0;                    //���׺�����ָ�
	G=0;
	B=108;
	setfillcolor(RGB(R,G,B));
	setcolor(RGB(R,G,B));
	fillrectangle(0,650,1000,800);
}


// ������
int main()
{
	int i,j;
	int times;
	srand((unsigned)time(NULL)); // �������
	initgraph(1000, 800);	// ��ͼ�δ���

	pool();   //Draw a pool......

	// ��ʼ������rain
	for(i=0; i<MAX; i++)
	{
		InitRain(i,0,1);
		graph[i].direction = direction;
	}
	TAG = 1;         //���������ε�һ�γ�ʼ������
	// ����rain����������˳�
	//PlaySound (TEXT("C:/Users/asus/Desktop/2798.wav"),NULL,SND_FILENAME | SND_ASYNC| SND_LOOP );
	PlaySound (TEXT("Materier/10379.wav"),NULL,SND_FILENAME | SND_ASYNC| SND_LOOP );     //This is rain sound         
	
	while(!kbhit())
	{
		for(j=0; j<NUM; j++)
		{  
			
			for(i=0; i<MAX; i++)  //����һ֡���ͼƬ
			{
				if (j == NUM-1)  //�����������·����ת�۵㣬��ʱ����һ�����Ƶײ�����ֻ����һ������ƫ����
					graph[i].trans = 1;
				else
					graph[i].trans = 0;
				Rain_quiet(i);     //���������Ƴ���
				graph[i].CLEAN_TG = 1;   //��ǿ��������
			}
				Sleep(20);
			if (rand()%HZ==1)  //�ж��Ƿ�Ӧ�ô���ʱ�����ʹ��׵ĸ���
			{
				thunder();
			}
			else if(rand()%HZ==2)  //�������� ���˷�����
			{ 
				thunder();
				thunder();
			}
			else if(rand()%HZ==3)  //������������
			{
				thunder();
				thunder();
				thunder();
			}
		}
	}
	closegraph();    // �ر�ͼ�δ���
	return 0;
}





