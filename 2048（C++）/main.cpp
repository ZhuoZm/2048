#include"data.h"



int main(int argc, char *argv[])
{


	
	Game game;
	game.init();
	game.start();
	//������Ⱦ��
	SDL_RenderPresent(pRenderer);

	SDL_Delay(3000);
	//�ͷ���Ⱦ��
	 SDL_DestroyRenderer(pRenderer);
    printf("��Ⱦ���ͷ�!\n");

    // �ͷŴ���
    SDL_DestroyWindow(pWindow);
    printf("�����ͷ�!\n");

    // �˳�SDL2.0��
    SDL_Quit();
    printf("SDL�����˳�!\n");
	
	return 0;
}