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
#define MAX 300	   //��ε�����
#define STEP 70   //��εĲ���ֵ��ˢ��ʱ���������ǰ���ľ��룩
#define WID 1      //����ߵĿ�ȣ��������ң�
#define LEN  30    //����ߵĳ��ȣ��������£�
#define HZ  50    //���ƴ��׸��ʵ���ֵ����ֵԽ�󣬴��׵ĸ���Խ�ͣ�
int TAG = 0;       //��ʼ��һ��tag���ж����Ƿ��Ѿ���ʼ����
//---------------------------------

//�����ǽṹ�嶨��λ��
//---------------------------------
typedef struct Rain {
	int x0, y0;//��ε���ʼλ�� 
	int x, y;//��ε���ֹλ�� 
	int step;//���� 
	COLORREF color;//��ε���ɫ 
	//��εĻ�������Ĳ��� 
	int left; 
	int top; 
	int right; 
	int bottom; 
	double stangle; 
	double endangle;
	int Drop_tag;
	int CLEAN_TG;      //�ж��Ƿ�Ӧ�������   ����ʱ�Ǹ����ɣ��Ͳ��������
	int ID;            //�ж����������ʽ
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


//��Ҷ���� 
void draw_leaf(int left, int top, int right, int bottom, COLORREF fillcolor, COLORREF linecolor) 
{ 
	//����Ҷ����Բ���� 
	setfillcolor(fillcolor); 
	setcolor(fillcolor); 
	fillellipse(left, top, right, bottom); 
	//����Ҷ�е��������� 
	setlinecolor(linecolor); 
	setlinestyle(PS_SOLID, 2); 
	int ox = (left + right) / 2; 
	int oy = (top + bottom) / 2; 
	line(ox - 20, oy - 10, ox + 20, oy + 10); 
	line(ox - 20, oy + 10, ox + 20, oy - 10); 
	setlinecolor(linecolor); 
}


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
	//���Ƴ����еĺ�Ҷ 
	/*
	draw_leaf(450, 700, 550, 750, GREEN, BLACK);
	draw_leaf(380, 720, 480, 770, GREEN, BLACK); 
	*/
}

//Rain
void InitRain(int i)
{
	int R,G,B;
	graph[i].x0 = rand()%1000;
	if(TAG==0)
	{	
		graph[i].y0 = rand()%(650-STEP);
	}
	else	
		graph[i].y0 = rand()%STEP;
	graph[i].left = graph[i].x0;
	graph[i].top = graph[i].y0;
	graph[i].right = graph[i].left + WID;
	graph[i].bottom = graph[i].top + LEN;
	graph[i].stangle = 4.28;
	graph[i].endangle = 5.22;
	graph[i].step = STEP;
	R = rand()%255;
	G = rand()%255;
	B = rand()%255;
	graph[i].color = RGB(R,G,B);
	graph[i].Drop_tag = 0;//�˱��˵����δ�������
}

//��ͬʱ�����λ�ú���
void Rain_quiet(int i)
{
	int width = 150-STEP;

	// ����ԭ��
	if(graph[i].CLEAN_TG)
	{
		if(graph[i].Drop_tag==1)     //˵���ϸ������Ȧ
		{
			int x1,x2,y1,y2;
			setcolor(RGB(0,0,108));
			x1 = graph[i].left-10;
			x2 = graph[i].left+10;
			y1 = graph[i].bottom-5;
			y2 = graph[i].bottom+5;
			ellipse (x1,y1,x2,y2);
		}
		else                         //�ϸ��������,����ʱע��ֲ���
		{ 
			if(graph[i].ID==2)
			{
				setfillcolor(0);//��������ɫ(�����) 
				setlinecolor(0);//��������ɫ(�����) 
				fillpie(graph[i].left,graph[i].top,graph[i].right,651,graph[i].stangle,graph[i].endangle);
				setfillcolor(RGB(0,0,108));//��������ɫ(�����) 
				setlinecolor(RGB(0,0,108));//��������ɫ(�����) 
				fillpie(graph[i].left,650,graph[i].right,graph[i].bottom,graph[i].stangle,graph[i].endangle);
			}
			else if(graph[i].ID==1)
			{
				setfillcolor(RGB(0,0,108));//��������ɫ(�����) 
				setlinecolor(RGB(0,0,108));//��������ɫ(�����) 
				fillpie(graph[i].left,graph[i].top,graph[i].right,graph[i].bottom,graph[i].stangle,graph[i].endangle);
			}
			else 
			{
				setfillcolor(0);//��������ɫ(�����) 
				setlinecolor(0);//��������ɫ(�����) 
				fillpie(graph[i].left,graph[i].top,graph[i].right,graph[i].bottom,graph[i].stangle,graph[i].endangle);
			}
		}
 
		// ������λ��
		if(graph[i].Drop_tag==1)
		{
			InitRain(i);
		}
		else
		{
			graph[i].top += graph[i].step;
			graph[i].bottom += graph[i].step;
		}
		

		if (graph[i].bottom >= 650+(rand()%width))   //�������λ�����
		{
			graph[i].Drop_tag = 1 ;  //���ñ�ǣ���ˮ���
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
		setcolor(graph[i].color);
		x1 = graph[i].left-10;
		x2 = graph[i].left+10;
		y1 = graph[i].bottom-5;
		y2 = graph[i].bottom+5;
		ellipse (x1,y1,x2,y2);
	}
	else
	{
		setfillcolor(graph[i].color);//��������ɫ(�����) 
		setlinecolor(graph[i].color);//��������ɫ(�����) 
		fillpie(graph[i].left,graph[i].top,graph[i].right,graph[i].bottom,graph[i].stangle,graph[i].endangle);//�������
	}
}

//Thunder
void thunder()
{
    int x = rand() % 500;// +20;
    int y = rand() % 100;//+10;
    int stepx = rand() % 2;
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
	Sleep(200);
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
	int i;

	srand((unsigned)time(NULL)); // �������
	initgraph(1000, 800);	// ��ͼ�δ���

	pool();   //Draw a pool......

	// ��ʼ������rain
	for(i=0; i<MAX; i++)
	{
		InitRain(i);
	}
	TAG = 1;         //���������ε�һ�γ�ʼ������
	// ����rain����������˳�
	//PlaySound (TEXT("C:/Users/asus/Desktop/2798.wav"),NULL,SND_FILENAME | SND_ASYNC| SND_LOOP );
	PlaySound (TEXT("Materier/10379.wav"),NULL,SND_FILENAME | SND_ASYNC| SND_LOOP );     //This is rain sound         

	while(!kbhit())
	{
		for(i=0; i<MAX; i++)  //����һ֡���ͼƬ
		{
			Rain_quiet(i);
			graph[i].CLEAN_TG = 1;   //��ǿ��������
		}
		Sleep(30);
		if (rand()%HZ==1)  //�ж��Ƿ�Ӧ�ô���ʱ�����ʹ��׵ĸ���
		{
			thunder();
		}
		else if(rand()%HZ==2)  //�������� ���˷�����
		{ 
			thunder();
			thunder();
		}
	
	}
	closegraph();    // �ر�ͼ�δ���
	return 0;
}





