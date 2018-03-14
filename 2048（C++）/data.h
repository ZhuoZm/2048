#ifndef _DATA_H_
#define _DATA_H_


//使用的外部头文件
#include<iostream>
#include "SDL.h"
#include"SDL_image.h"
#include <time.h>

using namespace std;

/* 背景图片本地路径 */
#define BACKGROUND_1 "../images/bg.png" // 背景图片1
#define BACKGROUND_2 "../images/bg1.png" // 背景图片2
#define BACKGROUND_3 "../images/0.png" // 背景图片3

/*数字图片本地路径*/
#define NUMBER_2 "../images/2.png" // 数字2
#define NUMBER_4 "../images/4.png" // 数字4
#define NUMBER_8 "../images/8.png" // 数字8
#define NUMBER_16 "../images/16.png" // 数字16
#define NUMBER_32 "../images/32.png" // 数字32
#define NUMBER_64 "../images/64.png" // 数字64
#define NUMBER_128 "../images/128.png" // 数字128
#define NUMBER_256 "../images/256.png" // 数字256
#define NUMBER_512 "../images/512.png" // 数字512
#define NUMBER_1024 "../images/1024.png" // 数字1024
#define NUMBER_2048 "../images/2048.png" // 数字2048

//失败图片本地路径
#define OVER        "../images/over.png" // 图片失败
//成功图片本地路径
#define VICTORY        "../images/victory.png" // 图片成功
//窗口大小
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 600

/* 背景图片2位置 */
#define BACKGROUND_2_W   450
#define BACKGROUND_2_H   450
#define BACKGROUND_2_X   (SCREEN_WIDTH-450)/2
#define BACKGROUND_2_Y   130



extern SDL_Window * pWindow=NULL;
extern SDL_Renderer * pRenderer=NULL;
// //图片类
 class Picture
{
	public:
		//目标区域修改接口
		void setdstrect(int x,int y,int w,int h)
		{
			dstrect.x=x;
			dstrect.y=y;
			dstrect.w=w;
			dstrect.h=h;
		}
		//纹理修改接口
		void setpTexture(const char * path)
		{
			pTexture=IMG_LoadTexture(pRenderer, path);
			if(NULL ==pTexture)
			{
				 cout<<"图片创建失败："<< SDL_GetError()<<endl;
			 }
		}

		//修改图片地址
		void setpath(const char * spath)
		{
		
			path=spath;
		}
		//得到图片地址
		const char * getpath()
		{
			return path;
		}
		//得到纹理
		SDL_Texture* getpTexture()
		{
			return pTexture;
		}
		//得到目标区域
		SDL_Rect getdstrect()
		{
			return dstrect;
		}
		protected:
		const char * path;
		SDL_Texture  * pTexture;//纹理
		SDL_Rect  dstrect;//目标区域
};

//数字图片类
class PNumber :public Picture
{
	public:
		//初始化
		PNumber()
		{
			nlayer=0;
			number=0;
		}
		//得到层数
		int getnlayer()
		{
			return nlayer;
		}
		//修改层数
		void setNlayer(int n)
		{
			nlayer =n;
		}
		//得到数字
		int getnumber()
		{
			return number;
		}
		//修改数字
		void setnumber(int n)
		{
			number=n;
		}
	protected:
		
		int nlayer;//所属层数
		int number;//数字
		
};

//背景图片类
class Pbackground :public Picture
{
public:
	Pbackground(){}
	Pbackground(const char * path,int x,int y,int w,int h)
	{
		pTexture=IMG_LoadTexture(pRenderer, path);
		if(NULL ==pTexture)
		 {
       cout<<"图片创建失败："<< SDL_GetError()<<endl;
	   cout<<"bg错误"<<endl;
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
       cout<<"图片创建失败："<< SDL_GetError()<<endl;
	   cout<<"bg错误"<<endl;
		  }
			dstrect.x=x;
			dstrect.y=y;
			dstrect.w=w;
			dstrect.h=h;
		
	}
private:

};


//窗口类
 class Window
{
public:
		
	Window()
	{}
		//初始化窗口类
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
 
static PNumber N2048[4][4];//定义数字图片数组
 Window window;
 //游戏类
class Game
{
 
 public:
//======================================================
// 函数：int initSDL(void)
// 作用：初始化SDL库及窗口、渲染器 
// 返回：0 表示初始化成功，非0初始化失败
//======================================================
	int init()
{
		 //初始化SDL2.0库
			if(0 != SDL_Init(SDL_INIT_EVERYTHING))
		{
        cout<<"SDL2.0初始化失败："<<SDL_GetError()<<endl;
        return -1;
		 }
	 cout<<"SDL2.0初始化成功！"<<endl;

    // 创建窗口
    pWindow = SDL_CreateWindow("2048Game", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        SCREEN_WIDTH,SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN);
	    if(NULL == pWindow)
    {
        printf("窗口创建失败：%s\n", SDL_GetError());
        return -2;
    }
	//创建渲染器
		 pRenderer = SDL_CreateRenderer(pWindow,
        -1, SDL_RENDERER_ACCELERATED);
    if(NULL == pRenderer)
    {
       cout<<"渲染器创建失败"<<SDL_GetError()<<endl;
        return -3;
    }
	//创建窗口对象并且加载背景图片
		window.initWindow();
	//设置数字图片的目标区域
		int i,j;
			 for(i=0;i<4;i++)
			{
				for( j=0;j<4;j++)
				{
					N2048[i][j].setpTexture(BACKGROUND_3);
					N2048[i][j].setpath(BACKGROUND_3);
					if(NULL ==N2048[i][j].getpTexture())
						{
						cout<<"图片创建失败："<< SDL_GetError()<<endl;
						 }
					N2048[i][j].setdstrect((SCREEN_WIDTH-450)/2+(j%4+1)*13+(j%4)*96,135+(i%4)*100+(i%4+1)*7,100,96);
					SDL_RenderCopy(pRenderer,N2048[i][j].getpTexture(),NULL,&(N2048[i][j].getdstrect()));
				}
			}
    return 0;

}


//======================================================
// 函数：void choice(int i,int j)
// 作用：选择
// 参数：行数，列数
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
// 函数：void swap(PNumber a,PNumber b)
// 作用：交换
// 参数：数字图片类对象
//======================================================
void swap(PNumber &a,PNumber &b)
{
	            //修改b的信息
	b.setnumber(a.getnumber());//修改数字值
	if(b.getnumber()==2)
		b.setpTexture(NUMBER_2);//修改纹理
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
		SDL_RenderCopy(pRenderer,b.getpTexture(),NULL,&(b.getdstrect()));//将纹理拷贝到渲染器
			//修改a的信息
		a.setnumber(0);//修改数字值
		a.setpTexture(BACKGROUND_3);//修改纹理
		SDL_RenderCopy(pRenderer,a.getpTexture(),NULL,&(a.getdstrect()));//将纹理拷贝到渲染器 	
}
//======================================================
// 函数：void remove_blank()
// 作用：移除空格
//======================================================
void up_remove_blank()
{
	int i,j,k;
    for(j=0;j<4;j++)
	{  
        for(i=1;i<4;i++)
		{  
            k=i;  
            while(k-1>=0&&N2048[k-1][j].getnumber()==0&&N2048[k][j].getnumber()!=0) //上面的那个为空  
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
            while(k+1<=3&&N2048[k+1][j].getnumber()==0) //上面的那个为空  
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
            while(k-1>=0&&N2048[i][k-1].getnumber()==0) //上面的那个为空  
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
            while(k+1<=3&&N2048[i][k+1].getnumber()==0){//上面的那个为空   
                swap(N2048[i][k],N2048[i][k+1]);  
                k++;      
            }     
        }  
    }     
}  
//======================================================
// 函数：void up()
// 作用：方向键事件
//======================================================
	void  up(const SDL_Event * pEvent)
{
	int i,j;
	up_remove_blank();
		cout<<SDL_GetKeyName(pEvent->key.keysym.sym)<<endl;
		
		for(j=0;j<4;j++)//每一列
		{   
			for(i=0;i<3;i++)
			{  
				if(N2048[i][j].getnumber()==N2048[i+1][j].getnumber()&&N2048[i][j].getnumber()!=0)//上层相等则相加
				{  
					N2048[i][j].setnumber(N2048[i][j].getnumber()+N2048[i+1][j].getnumber()); 
					choice(i,j);
					//下层设为空
					N2048[i+1][j].setnumber(0);  
					N2048[i+1][j].setpTexture(BACKGROUND_3);
					SDL_RenderCopy(pRenderer,N2048[i+1][j].getpTexture(),NULL,&(N2048[i+1][j].getdstrect()));
            
					up_remove_blank();   //移除空格  
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
		//每一列
		for(j=0;j<4;j++){   
			for(i=3;i>=1;i--){  
					if(N2048[i][j].getnumber()==N2048[i-1][j].getnumber())//下层相等则相加
				{  
					N2048[i][j].setnumber(N2048[i][j].getnumber()+N2048[i-1][j].getnumber()); 
					choice(i,j);
					//下层设为空
					N2048[i-1][j].setnumber(0);  
					N2048[i-1][j].setpTexture(BACKGROUND_3);
					SDL_RenderCopy(pRenderer,N2048[i-1][j].getpTexture(),NULL,&(N2048[i-1][j].getdstrect()));
            
					down_remove_blank(); //移除空格  
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
		for(i=0;i<4;i++)//每一列
		{   
			for(j=0;j<3;j++)
			{  
				if(N2048[i][j].getnumber()==N2048[i][j+1].getnumber())//上层相等则相加
				{  
					N2048[i][j].setnumber(N2048[i][j].getnumber()+N2048[i][j+1].getnumber()); 
					choice(i,j);
					//下层设为空
					N2048[i][j+1].setnumber(0);  
					N2048[i][j+1].setpTexture(BACKGROUND_3);
					SDL_RenderCopy(pRenderer,N2048[i][j+1].getpTexture(),NULL,&(N2048[i][j+1].getdstrect()));
            
					left_remove_blank();   //移除空格  
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
		//每一列
		for(i=0;i<4;i++){   
			for(j=3;j>=1;j--){  
					if(N2048[i][j].getnumber()==N2048[i][j-1].getnumber())//下层相等则相加
				{  
					N2048[i][j].setnumber(N2048[i][j].getnumber()+N2048[i][j-1].getnumber()); 
					choice(i,j);
					//下层设为空
					N2048[i][j-1].setnumber(0);  
					N2048[i][j-1].setpTexture(BACKGROUND_3);
					SDL_RenderCopy(pRenderer,N2048[i][j-1].getpTexture(),NULL,&(N2048[i][j-1].getdstrect()));
            
					right_remove_blank(); //移除空格  
				}  
			}   
		}  
		SDL_RenderPresent(pRenderer);
	
	}
//======================================================
// 函数：void keyBoardEvent(const SDL_Event * pEvent)
// 作用：处理键盘点击事件
// 参数：事件类型指针
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
// 函数：void logicStart(void)
// 作用：游戏开始（添加定时器，以及事件循环）
//======================================================
void start()
{
	 SDL_Event event;    // 事件类型变量
	 Pbackground over;   //失败图片
	  Pbackground victory;   //成功图片
	  int nQuit = 0;      // 退出标识,0循环,非0退出循环
		 srand((unsigned int)time(0));//种子函数 为rand函数做种子
		 int sj;
		 SDL_Keycode str=SDLK_UP;
		//游戏开始初始化两个数字
		int nLay = rand()%4;
		int nJay =rand()%4;
		int nNum= rand()%4;
		 cout<<nLay<<endl;
		 cout<<nJay<<endl;
						//改变数字
							if(nNum==0||nNum==1||nNum==2)
								N2048[nLay][nJay].setnumber(2);
							if(nNum==3)
								N2048[nLay][nJay].setnumber(4);
						//设置纹理
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
						//改变数字
						if(nNum==0||nNum==1||nNum==2)
								N2048[nLay][nJay].setnumber(2);
							if(nNum==3)
								N2048[nLay][nJay].setnumber(4);
						//设置纹理并且刷新渲染器
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
				

			   // 获取事件
			while(SDL_WaitEvent(&event))
			 {
				 switch(event.type)  // 事件的类别0
				 {
					case SDL_QUIT:      // 退出事件
						{
							nQuit=1;
							cout<<"程序将要关闭！！"<<endl;
						
						} // 用户激活退出事件,跳出循环
						break;
						// 键盘点击事件
					case SDL_KEYDOWN:   
						keyBoardEvent(&event);
					break;
                 }
				 if(event.type==SDL_QUIT)
				break;
				 if(event.type==SDL_KEYDOWN)
					 break;
			}
			//结束条件
				//成功结束
			int i,j,n=0;
					for(i=0;i<4;i++)
					{
						for(j=0;j<4;j++)
						{
							if(N2048[i][j].getnumber()==2048)
							{
								nQuit=1;//成功结束
								cout<<"恭喜你完成2048！！！"<<endl;
									victory.setpTexture(OVER);
							
							victory.setdstrect(SCREEN_WIDTH/2-150,SCREEN_HEIGHT/2-56,300,192);
							SDL_RenderCopy(pRenderer,victory.getpTexture(),NULL,&(victory.getdstrect()));
							SDL_RenderPresent(pRenderer);

							}
						}
					}
				//失败结束
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
						{nQuit=1;//成功结束
							cout<<"游戏结束!!!!"<<endl;
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