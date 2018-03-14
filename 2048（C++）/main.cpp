#include"data.h"



int main(int argc, char *argv[])
{


	
	Game game;
	game.init();
	game.start();
	//更新渲染器
	SDL_RenderPresent(pRenderer);

	SDL_Delay(3000);
	//释放渲染器
	 SDL_DestroyRenderer(pRenderer);
    printf("渲染器释放!\n");

    // 释放窗口
    SDL_DestroyWindow(pWindow);
    printf("窗口释放!\n");

    // 退出SDL2.0库
    SDL_Quit();
    printf("SDL库已退出!\n");
	
	return 0;
}