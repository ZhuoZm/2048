#ifndef _DATA_H_
#define _DATA_H_


//ʹ�õ��ⲿͷ�ļ�
#include<iostream>
#include "SDL.h"
#include"SDL_image.h"
#include <time.h>

using namespace std;

/* ����ͼƬ����·�� */
#define BACKGROUND_1 "../images/bg.png" // ����ͼƬ1
#define BACKGROUND_2 "../images/bg1.png" // ����ͼƬ2
#define BACKGROUND_3 "../images/0.png" // ����ͼƬ3

/*����ͼƬ����·��*/
#define NUMBER_2 "../images/2.png" // ����2
#define NUMBER_4 "../images/4.png" // ����4
#define NUMBER_8 "../images/8.png" // ����8
#define NUMBER_16 "../images/16.png" // ����16
#define NUMBER_32 "../images/32.png" // ����32
#define NUMBER_64 "../images/64.png" // ����64
#define NUMBER_128 "../images/128.png" // ����128
#define NUMBER_256 "../images/256.png" // ����256
#define NUMBER_512 "../images/512.png" // ����512
#define NUMBER_1024 "../images/1024.png" // ����1024
#define NUMBER_2048 "../images/2048.png" // ����2048

//ʧ��ͼƬ����·��
#define OVER        "../images/over.png" // ͼƬʧ��
//�ɹ�ͼƬ����·��
#define VICTORY        "../images/victory.png" // ͼƬ�ɹ�
//���ڴ�С
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 600

/* ����ͼƬ2λ�� */
#define BACKGROUND_2_W   450
#define BACKGROUND_2_H   450
#define BACKGROUND_2_X   (SCREEN_WIDTH-450)/2
#define BACKGROUND_2_Y   130



extern SDL_Window * pWindow=NULL;
extern SDL_Renderer * pRenderer=NULL;
// //ͼƬ��
 class Picture
{
	public:
		//Ŀ�������޸Ľӿ�
		void setdstrect(int x,int y,int w,int h)
		{
			dstrect.x=x;
			dstrect.y=y;
			dstrect.w=w;
			dstrect.h=h;
		}
		//�����޸Ľӿ�
		void setpTexture(const char * path)
		{
			pTexture=IMG_LoadTexture(pRenderer, path);
			if(NULL ==pTexture)
			{
				 cout<<"ͼƬ����ʧ�ܣ�"<< SDL_GetError()<<endl;
			 }
		}

		//�޸�ͼƬ��ַ
		void setpath(const char * spath)
		{
		
			path=spath;
		}
		//�õ�ͼƬ��ַ
		const char * getpath()
		{
			return path;
		}
		//�õ�����
		SDL_Texture* getpTexture()
		{
			return pTexture;
		}
		//�õ�Ŀ������
		SDL_Rect getdstrect()
		{
			return dstrect;
		}
		protected:
		const char * path;
		SDL_Texture  * pTexture;//����
		SDL_Rect  dstrect;//Ŀ������
};

//����ͼƬ��
class PNumber :public Picture
{
	public:
		//��ʼ��
		PNumber()
		{
			nlayer=0;
			number=0;
		}
		//�õ�����
		int getnlayer()
		{
			return nlayer;
		}
		//�޸Ĳ���
		void setNlayer(int n)
		{
			nlayer =n;
		}
		//�õ�����
		int getnumber()
		{
			return number;
		}
		//�޸�����
		void setnumber(int n)
		{
			number=n;
		}
	protected:
		
		int nlayer;//��������
		int number;//����
		
};

//����ͼƬ��
class Pbackground :public Picture
{
public:
	Pbackground(){}
	Pbackground(const char * path,int x,int y,int w,int h)
	{
		pTexture=IMG_LoadTexture(pRenderer, path);
		if(NULL ==pTexture)
		 {
       cout<<"ͼƬ����ʧ�ܣ�"<< SDL_GetError()<<endl;
	   cout<<"bg����"<<endl;
		  }
			dstrect.x=x;
			dstrect.y=y;
			dstrect.w=w;
			dstrect.h=h;
	}
	void initbackgroung(const char * path,int x,int y,int w,int h)
	{
		pTexture=IMG_LoadTexture(pRenderer, path);
		if(NULL ==pTexture)
		 {
       cout<<"ͼƬ����ʧ�ܣ�"<< SDL_GetError()<<endl;
	   cout<<"bg����"<<endl;
		  }
			dstrect.x=x;
			dstrect.y=y;
			dstrect.w=w;
			dstrect.h=h;
		
	}
private:

};


//������
 class Window
{
public:
		
	Window()
	{}
		//��ʼ��������
		void initWindow()
		{
			 bg.initbackgroung(BACKGROUND_1,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
			 SDL_RenderCopy(pRenderer,bg.getpTexture(),NULL,&(bg.getdstrect()));
			 bg1.initbackgroung(BACKGROUND_2,BACKGROUND_2_X,BACKGROUND_2_Y,BACKGROUND_2_W,BACKGROUND_2_H);
			 SDL_RenderCopy(pRenderer,bg1.getpTexture(),NULL,&(bg1.getdstrect()));
		 }
			
	
protected:
	 Pbackground bg;
	 Pbackground bg1;
		
};
 
static PNumber N2048[4][4];//��������ͼƬ����
 Window window;
 //��Ϸ��
class Game
{
 
 public:
//======================================================
// ������int initSDL(void)
// ���ã���ʼ��SDL�⼰���ڡ���Ⱦ�� 
// ���أ�0 ��ʾ��ʼ���ɹ�����0��ʼ��ʧ��
//======================================================
	int init()
{
		 //��ʼ��SDL2.0��
			if(0 != SDL_Init(SDL_INIT_EVERYTHING))
		{
        cout<<"SDL2.0��ʼ��ʧ�ܣ�"<<SDL_GetError()<<endl;
        return -1;
		 }
	 cout<<"SDL2.0��ʼ���ɹ���"<<endl;

    // ��������
    pWindow = SDL_CreateWindow("2048Game", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        SCREEN_WIDTH,SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN);
	    if(NULL == pWindow)
    {
        printf("���ڴ���ʧ�ܣ�%s\n", SDL_GetError());
        return -2;
    }
	//������Ⱦ��
		 pRenderer = SDL_CreateRenderer(pWindow,
        -1, SDL_RENDERER_ACCELERATED);
    if(NULL == pRenderer)
    {
       cout<<"��Ⱦ������ʧ��"<<SDL_GetError()<<endl;
        return -3;
    }
	//�������ڶ����Ҽ��ر���ͼƬ
		window.initWindow();
	//��������ͼƬ��Ŀ������
		int i,j;
			 for(i=0;i<4;i++)
			{
				for( j=0;j<4;j++)
				{
					N2048[i][j].setpTexture(BACKGROUND_3);
					N2048[i][j].setpath(BACKGROUND_3);
					if(NULL ==N2048[i][j].getpTexture())
						{
						cout<<"ͼƬ����ʧ�ܣ�"<< SDL_GetError()<<endl;
						 }
					N2048[i][j].setdstrect((SCREEN_WIDTH-450)/2+(j%4+1)*13+(j%4)*96,135+(i%4)*100+(i%4+1)*7,100,96);
					SDL_RenderCopy(pRenderer,N2048[i][j].getpTexture(),NULL,&(N2048[i][j].getdstrect()));
				}
			}
    return 0;

}


//======================================================
// ������void choice(int i,int j)
// ���ã�ѡ��
// ����������������
//======================================================
void choice (int i,int j)
{
						if(N2048[i][j].getnumber()==2)
					{
						N2048[i][j].setpTexture(NUMBER_2);
						SDL_RenderCopy(pRenderer,N2048[i][j].getpTexture(),NULL,&(N2048[i][j].getdstrect()));
					}
							else if(N2048[i][j].getnumber()==4)
					{
						N2048[i][j].setpTexture(NUMBER_4);
						
						SDL_RenderCopy(pRenderer,N2048[i][j].getpTexture(),NULL,&(N2048[i][j].getdstrect()));
					}
							else if(N2048[i][j].getnumber()==8)
					{
						N2048[i][j].setpTexture(NUMBER_8);
						
						SDL_RenderCopy(pRenderer,N2048[i][j].getpTexture(),NULL,&(N2048[i][j].getdstrect()));
					}
								else if(N2048[i][j].getnumber()==16)
					{
						N2048[i][j].setpTexture(NUMBER_16);
						
						SDL_RenderCopy(pRenderer,N2048[i][j].getpTexture(),NULL,&(N2048[i][j].getdstrect()));
					}
								else if(N2048[i][j].getnumber()==32)
					{
						N2048[i][j].setpTexture(NUMBER_32);
						
						SDL_RenderCopy(pRenderer,N2048[i][j].getpTexture(),NULL,&(N2048[i][j].getdstrect()));
					}
									else if(N2048[i][j].getnumber()==64)
					{
						N2048[i][j].setpTexture(NUMBER_64);
						
						SDL_RenderCopy(pRenderer,N2048[i][j].getpTexture(),NULL,&(N2048[i][j].getdstrect()));
					}
									else if(N2048[i][j].getnumber()==128)
					{
						N2048[i][j].setpTexture(NUMBER_128);
						
						SDL_RenderCopy(pRenderer,N2048[i][j].getpTexture(),NULL,&(N2048[i][j].getdstrect()));
					}
										else if(N2048[i][j].getnumber()==256)
					{
						N2048[i][j].setpTexture(NUMBER_256);
						
						SDL_RenderCopy(pRenderer,N2048[i][j].getpTexture(),NULL,&(N2048[i][j].getdstrect()));
					}
										else if(N2048[i][j].getnumber()==512)
					{
						N2048[i][j].setpTexture(NUMBER_512);
						
						SDL_RenderCopy(pRenderer,N2048[i][j].getpTexture(),NULL,&(N2048[i][j].getdstrect()));
					}
											else if(N2048[i][j].getnumber()==1024)
					{
						N2048[i][j].setpTexture(NUMBER_1024);
						
						SDL_RenderCopy(pRenderer,N2048[i][j].getpTexture(),NULL,&(N2048[i][j].getdstrect()));
					}
											else if(N2048[i][j].getnumber()==2048)
					{
						N2048[i][j].setpTexture(NUMBER_2048);
						SDL_RenderCopy(pRenderer,N2048[i][j].getpTexture(),NULL,&(N2048[i][j].getdstrect()));
					}
}
//======================================================
// ������void swap(PNumber a,PNumber b)
// ���ã�����
// ����������ͼƬ�����
//======================================================
void swap(PNumber &a,PNumber &b)
{
	            //�޸�b����Ϣ
	b.setnumber(a.getnumber());//�޸�����ֵ
	if(b.getnumber()==2)
		b.setpTexture(NUMBER_2);//�޸�����
	else if(b.getnumber()==4)
		b.setpTexture(NUMBER_4);
	else if(b.getnumber()==8)
		b.setpTexture(NUMBER_8);
	else if(b.getnumber()==16)
		b.setpTexture(NUMBER_16);
	else if(b.getnumber()==32)
		b.setpTexture(NUMBER_32);
	else if(b.getnumber()==64)
		b.setpTexture(NUMBER_64);
	else if(b.getnumber()==128)
		b.setpTexture(NUMBER_128);
	else if(b.getnumber()==256)
		b.setpTexture(NUMBER_256);
	else if(b.getnumber()==512)
		b.setpTexture(NUMBER_512);
	else if(b.getnumber()==1024)
		b.setpTexture(NUMBER_1024);
	else if(b.getnumber()==2048)
		b.setpTexture(NUMBER_2048);
		SDL_RenderCopy(pRenderer,b.getpTexture(),NULL,&(b.getdstrect()));//������������Ⱦ��
			//�޸�a����Ϣ
		a.setnumber(0);//�޸�����ֵ
		a.setpTexture(BACKGROUND_3);//�޸�����
		SDL_RenderCopy(pRenderer,a.getpTexture(),NULL,&(a.getdstrect()));//������������Ⱦ�� 	
}
//======================================================
// ������void remove_blank()
// ���ã��Ƴ��ո�
//======================================================
void up_remove_blank()
{
	int i,j,k;
    for(j=0;j<4;j++)
	{  
        for(i=1;i<4;i++)
		{  
            k=i;  
            while(k-1>=0&&N2048[k-1][j].getnumber()==0&&N2048[k][j].getnumber()!=0) //������Ǹ�Ϊ��  
			{                                   
			swap(N2048[k][j],N2048[k-1][j]);
                k--;  
				
            }  
        }  
    }  
	
	
}
void down_remove_blank()
{  
   int i,j,k;
    for(j=0;j<4;j++)
	{  
        for(i=2;i>=0;i--)
		{  
            k=i;  
            while(k+1<=3&&N2048[k+1][j].getnumber()==0) //������Ǹ�Ϊ��  
			{                                   
			swap(N2048[k][j],N2048[k+1][j]);
                k++;      
            }  
        }  
    }  
}  
void left_remove_blank(){  
   int i,j,k;
    for(i=0;i<4;i++)
	{  
        for(j=1;j<4;j++)
		{  
            k=j;  
            while(k-1>=0&&N2048[i][k-1].getnumber()==0) //������Ǹ�Ϊ��  
			{                                   
			swap(N2048[i][k],N2048[i][k-1]);
                k--;      
            }  
        }  
    }  
}   
void right_remove_blank(){  
    int i,j,k;  
    for(i=0;i<4;i++){  
        for(j=2;j>=0;j--){  
            k=j;  
            while(k+1<=3&&N2048[i][k+1].getnumber()==0){//������Ǹ�Ϊ��   
                swap(N2048[i][k],N2048[i][k+1]);  
                k++;      
            }     
        }  
    }     
}  
//======================================================
// ������void up()
// ���ã�������¼�
//======================================================
	void  up(const SDL_Event * pEvent)
{
	int i,j;
	up_remove_blank();
		cout<<SDL_GetKeyName(pEvent->key.keysym.sym)<<endl;
		
		for(j=0;j<4;j++)//ÿһ��
		{   
			for(i=0;i<3;i++)
			{  
				if(N2048[i][j].getnumber()==N2048[i+1][j].getnumber()&&N2048[i][j].getnumber()!=0)//�ϲ���������
				{  
					N2048[i][j].setnumber(N2048[i][j].getnumber()+N2048[i+1][j].getnumber()); 
					choice(i,j);
					//�²���Ϊ��
					N2048[i+1][j].setnumber(0);  
					N2048[i+1][j].setpTexture(BACKGROUND_3);
					SDL_RenderCopy(pRenderer,N2048[i+1][j].getpTexture(),NULL,&(N2048[i+1][j].getdstrect()));
            
					up_remove_blank();   //�Ƴ��ո�  
				 }
				
			}  

		 }  
			SDL_RenderPresent(pRenderer);
		
}
	void down(const SDL_Event * pEvent)
	{
	down_remove_blank();
		cout<<SDL_GetKeyName(pEvent->key.keysym.sym)<<endl;
		int i,j;
		//ÿһ��
		for(j=0;j<4;j++){   
			for(i=3;i>=1;i--){  
					if(N2048[i][j].getnumber()==N2048[i-1][j].getnumber())//�²���������
				{  
					N2048[i][j].setnumber(N2048[i][j].getnumber()+N2048[i-1][j].getnumber()); 
					choice(i,j);
					//�²���Ϊ��
					N2048[i-1][j].setnumber(0);  
					N2048[i-1][j].setpTexture(BACKGROUND_3);
					SDL_RenderCopy(pRenderer,N2048[i-1][j].getpTexture(),NULL,&(N2048[i-1][j].getdstrect()));
            
					down_remove_blank(); //�Ƴ��ո�  
				}  
			}   
		}  
		SDL_RenderPresent(pRenderer);
	}
	void left(const SDL_Event * pEvent)
	{
		left_remove_blank();
		cout<<SDL_GetKeyName(pEvent->key.keysym.sym)<<endl;
		int i,j;
		for(i=0;i<4;i++)//ÿһ��
		{   
			for(j=0;j<3;j++)
			{  
				if(N2048[i][j].getnumber()==N2048[i][j+1].getnumber())//�ϲ���������
				{  
					N2048[i][j].setnumber(N2048[i][j].getnumber()+N2048[i][j+1].getnumber()); 
					choice(i,j);
					//�²���Ϊ��
					N2048[i][j+1].setnumber(0);  
					N2048[i][j+1].setpTexture(BACKGROUND_3);
					SDL_RenderCopy(pRenderer,N2048[i][j+1].getpTexture(),NULL,&(N2048[i][j+1].getdstrect()));
            
					left_remove_blank();   //�Ƴ��ո�  
				 }  
			}   
		 }  
			SDL_RenderPresent(pRenderer);
		}
	void right(const SDL_Event * pEvent)
	{
		right_remove_blank();
		cout<<SDL_GetKeyName(pEvent->key.keysym.sym)<<endl;
		int i,j;
		//ÿһ��
		for(i=0;i<4;i++){   
			for(j=3;j>=1;j--){  
					if(N2048[i][j].getnumber()==N2048[i][j-1].getnumber())//�²���������
				{  
					N2048[i][j].setnumber(N2048[i][j].getnumber()+N2048[i][j-1].getnumber()); 
					choice(i,j);
					//�²���Ϊ��
					N2048[i][j-1].setnumber(0);  
					N2048[i][j-1].setpTexture(BACKGROUND_3);
					SDL_RenderCopy(pRenderer,N2048[i][j-1].getpTexture(),NULL,&(N2048[i][j-1].getdstrect()));
            
					right_remove_blank(); //�Ƴ��ո�  
				}  
			}   
		}  
		SDL_RenderPresent(pRenderer);
	
	}
//======================================================
// ������void keyBoardEvent(const SDL_Event * pEvent)
// ���ã�������̵���¼�
// �������¼�����ָ��
//======================================================
int  keyBoardEvent(const SDL_Event * pEvent)
{
	
	  if(pEvent->key.keysym.sym==SDLK_UP)
	{
		up(pEvent);
		
	}

	else if(pEvent->key.keysym.sym==SDLK_DOWN)
	{
		down(pEvent);
	}
	
	else if(pEvent->key.keysym.sym==SDLK_LEFT)
	{
				left(pEvent);
		}
	
	else if(pEvent->key.keysym.sym==SDLK_RIGHT)
	{
		right(pEvent);
	}
	
	return 0;
}
// ======================================================
// ������void logicStart(void)
// ���ã���Ϸ��ʼ����Ӷ�ʱ�����Լ��¼�ѭ����
//======================================================
void start()
{
	 SDL_Event event;    // �¼����ͱ���
	 Pbackground over;   //ʧ��ͼƬ
	  Pbackground victory;   //�ɹ�ͼƬ
	  int nQuit = 0;      // �˳���ʶ,0ѭ��,��0�˳�ѭ��
		 srand((unsigned int)time(0));//���Ӻ��� Ϊrand����������
		 int sj;
		 SDL_Keycode str=SDLK_UP;
		//��Ϸ��ʼ��ʼ����������
		int nLay = rand()%4;
		int nJay =rand()%4;
		int nNum= rand()%4;
		 cout<<nLay<<endl;
		 cout<<nJay<<endl;
						//�ı�����
							if(nNum==0||nNum==1||nNum==2)
								N2048[nLay][nJay].setnumber(2);
							if(nNum==3)
								N2048[nLay][nJay].setnumber(4);
						//��������
						if(nNum==0||nNum==1||nNum==2)
						{
							N2048[nLay][nJay].setpTexture(NUMBER_2);
							N2048[nLay][nJay].setdstrect((SCREEN_WIDTH-450)/2+(nJay%4+1)*13+(nJay%4)*96,135+(nLay%4)*100+(nLay%4+1)*7,100,96);
							SDL_RenderCopy(pRenderer,N2048[nLay][nJay].getpTexture(),NULL,&(N2048[nLay][nJay].getdstrect()));
							
						}
						else if(nNum==3)
						{
							N2048[nLay][nJay].setpTexture(NUMBER_4);
							N2048[nLay][nJay].setdstrect((SCREEN_WIDTH-450)/2+(nJay%4+1)*13+(nJay%4)*96,135+(nLay%4)*100+(nLay%4+1)*7,100,96);
							SDL_RenderCopy(pRenderer,N2048[nLay][nJay].getpTexture(),NULL,&(N2048[nLay][nJay].getdstrect()));
							
						}

	  do
	  {
		sj=0;
		while(sj==0)
		{
		 nLay = rand()%4;
		 nJay =rand()%4;
		 nNum= rand()%4;
					 cout<<nLay<<endl;
					 cout<<nJay<<endl;
					if(N2048[nLay][nJay].getnumber()==0)
					{
						sj++;
						//�ı�����
						if(nNum==0||nNum==1||nNum==2)
								N2048[nLay][nJay].setnumber(2);
							if(nNum==3)
								N2048[nLay][nJay].setnumber(4);
						//����������ˢ����Ⱦ��
						if(nNum==0||nNum==1||nNum==2)
						{
							N2048[nLay][nJay].setpTexture(NUMBER_2);
							
							N2048[nLay][nJay].setdstrect((SCREEN_WIDTH-450)/2+(nJay%4+1)*13+(nJay%4)*96,135+(nLay%4)*100+(nLay%4+1)*7,100,96);
							SDL_RenderCopy(pRenderer,N2048[nLay][nJay].getpTexture(),NULL,&(N2048[nLay][nJay].getdstrect()));
							SDL_RenderPresent(pRenderer);
								
						}
						else if(nNum==3)
						{
							N2048[nLay][nJay].setpTexture(NUMBER_4);
							
							N2048[nLay][nJay].setdstrect((SCREEN_WIDTH-450)/2+(nJay%4+1)*13+(nJay%4)*96,135+(nLay%4)*100+(nLay%4+1)*7,100,96);
							SDL_RenderCopy(pRenderer,N2048[nLay][nJay].getpTexture(),NULL,&(N2048[nLay][nJay].getdstrect()));
							SDL_RenderPresent(pRenderer);
							
							
						}
						
					}
			}
				

			   // ��ȡ�¼�
			while(SDL_WaitEvent(&event))
			 {
				 switch(event.type)  // �¼������0
				 {
					case SDL_QUIT:      // �˳��¼�
						{
							nQuit=1;
							cout<<"����Ҫ�رգ���"<<endl;
						
						} // �û������˳��¼�,����ѭ��
						break;
						// ���̵���¼�
					case SDL_KEYDOWN:   
						keyBoardEvent(&event);
					break;
                 }
				 if(event.type==SDL_QUIT)
				break;
				 if(event.type==SDL_KEYDOWN)
					 break;
			}
			//��������
				//�ɹ�����
			int i,j,n=0;
					for(i=0;i<4;i++)
					{
						for(j=0;j<4;j++)
						{
							if(N2048[i][j].getnumber()==2048)
							{
								nQuit=1;//�ɹ�����
								cout<<"��ϲ�����2048������"<<endl;
									victory.setpTexture(OVER);
							
							victory.setdstrect(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-56,300,192);
							SDL_RenderCopy(pRenderer,victory.getpTexture(),NULL,&(victory.getdstrect()));
							SDL_RenderPresent(pRenderer);

							}
						}
					}
				//ʧ�ܽ���
					for(i=0;i<4;i++)
					{
						for(j=0;j<4;j++)
						{
							if(N2048[i][j].getnumber()!=0)
							{
									n++;
							}
						}
					}
					if(n==16)
						{nQuit=1;//�ɹ�����
							cout<<"��Ϸ����!!!!"<<endl;
							over.setpTexture(OVER);
							
							over.setdstrect(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-56,300,192);
							SDL_RenderCopy(pRenderer,over.getpTexture(),NULL,&(over.getdstrect()));
							SDL_RenderPresent(pRenderer);
					}
					n=0;
	  }while(nQuit==0);
		
	} 
 };
#endif  _DATA_H_