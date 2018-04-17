#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <stdio.h>

int main()
{
	// Game things
	bool gameRunning = true;
	bool quit = false;
	bool win = false;
	int windowWidth = 640;
	int windowHeight = 480;
	// Player things
	int playerImageSize = 32;
	int playerSpeed = 7;
	int wallLimit = 5;
	// Obstacule things
	int obsWidth = 30;
	int obsHeight = 300;
	int obsSpeed = 3;
	bool changeDirection = true;
	// Messages things
	int msWidth = 240;
	int msHeight = 120;

	SDL_SetMainReady();

	SDL_Window *window;                    // Declare a pointer

	SDL_Init(SDL_INIT_VIDEO);			   // Initialize SDL2

	window = SDL_CreateWindow(
		"An SDL2 window",                  // window title
		SDL_WINDOWPOS_CENTERED,            // initial x position
		SDL_WINDOWPOS_CENTERED,            // initial y position
		windowWidth,                       // width, in pixels
		windowHeight,                      // height, in pixels
		0								   // flags - see below
	);

	// Check that the window was successfully created
	if (window == NULL) { return 1; }
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	// Player
	SDL_Surface* player = SDL_LoadBMP("player.bmp");
	SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, player);
	SDL_Rect playerDstrect = { wallLimit + playerSpeed, windowHeight / 2, playerImageSize, playerImageSize };
	// Obstacule 1
	SDL_Surface* obs1 = SDL_LoadBMP("obstacule.bmp");
	SDL_Texture* obs1Texture = SDL_CreateTextureFromSurface(renderer, obs1);
	SDL_Rect obs1Dstrect = { 200, -120, obsWidth, obsHeight };
	// Obstacule 2
	SDL_Surface* obs2 = SDL_LoadBMP("obstacule.bmp");
	SDL_Texture* obs2Texture = SDL_CreateTextureFromSurface(renderer, obs2);
	SDL_Rect obs2Dstrect = { 200, 255, obsWidth, obsHeight };
	// Obstacule 3
	SDL_Surface* obs3 = SDL_LoadBMP("obstacule.bmp");
	SDL_Texture* obs3Texture = SDL_CreateTextureFromSurface(renderer, obs3);
	SDL_Rect obs3Dstrect = { 400, -40, obsWidth, obsHeight };
	// Obstacule 4
	SDL_Surface* obs4 = SDL_LoadBMP("obstacule.bmp");
	SDL_Texture* obs4Texture = SDL_CreateTextureFromSurface(renderer, obs4);
	SDL_Rect obs4Dstrect = { 400, 335, obsWidth, obsHeight };
	// Finish
	SDL_Surface* finish = SDL_LoadBMP("finish.bmp");
	SDL_Texture* finishTexture = SDL_CreateTextureFromSurface(renderer, finish);
	SDL_Rect finishDstrect = { 610, 0, obsWidth, windowHeight };
	
	Uint8 *SDL_GetKeyState(int *numkeys);
	Uint8 *keystate;

	// Game Loop
	while (gameRunning)
	{
		SDL_Event event;
		if (SDL_PollEvent(&event)) 
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				quit = true;
				break;
			default:
				break;
			}
			// Player Movement
			if (event.type == SDL_KEYDOWN)
				switch (event.key.keysym.sym) {
				case SDLK_LEFT: {
					// PlayerMoves
					if (playerDstrect.x > playerSpeed + 1)
						playerDstrect.x -= playerSpeed;

					// ObsMoves
					if (changeDirection)
					{
						obs1Dstrect.y += obsSpeed;
						obs2Dstrect.y += obsSpeed;
						obs3Dstrect.y += obsSpeed;
						obs4Dstrect.y += obsSpeed;
					}
					else
					{
						obs1Dstrect.y -= obsSpeed;
						obs2Dstrect.y -= obsSpeed;
						obs3Dstrect.y -= obsSpeed;
						obs4Dstrect.y -= obsSpeed;
					}
					break;
				}
				case SDLK_RIGHT: {
					// PlayerMoves
					if (playerDstrect.x < windowWidth - playerImageSize - wallLimit - playerSpeed - 1)
						playerDstrect.x += playerSpeed;

					// ObsMoves
					if (changeDirection)
					{
						obs1Dstrect.y += obsSpeed;
						obs2Dstrect.y += obsSpeed;
						obs3Dstrect.y += obsSpeed;
						obs4Dstrect.y += obsSpeed;
					}
					else
					{
						obs1Dstrect.y -= obsSpeed;
						obs2Dstrect.y -= obsSpeed;
						obs3Dstrect.y -= obsSpeed;
						obs4Dstrect.y -= obsSpeed;
					}
					break;
				}
				case SDLK_UP: {
					// PlayerMoves
					if (playerDstrect.y > wallLimit + playerSpeed + 1)
						playerDstrect.y -= playerSpeed;

					// ObsMoves
					if (changeDirection)
					{
						obs1Dstrect.y += obsSpeed;
						obs2Dstrect.y += obsSpeed;
						obs3Dstrect.y += obsSpeed;
						obs4Dstrect.y += obsSpeed;
					}
					else
					{
						obs1Dstrect.y -= obsSpeed;
						obs2Dstrect.y -= obsSpeed;
						obs3Dstrect.y -= obsSpeed;
						obs4Dstrect.y -= obsSpeed;
					}
					break;
				}
				case SDLK_DOWN: {
					// PlayerMoves
					if (playerDstrect.y < windowHeight - playerImageSize - wallLimit - playerSpeed - 1)
						playerDstrect.y += playerSpeed;
					// ObsMoves
					if (changeDirection)
					{
						obs1Dstrect.y += obsSpeed;
						obs2Dstrect.y += obsSpeed;
						obs3Dstrect.y += obsSpeed;
						obs4Dstrect.y += obsSpeed;
					}
					else
					{
						obs1Dstrect.y -= obsSpeed;
						obs2Dstrect.y -= obsSpeed;
						obs3Dstrect.y -= obsSpeed;
						obs4Dstrect.y -= obsSpeed;
					}
					break;
				}
				}

			// Collision Player-Obs
			if (playerDstrect.x + playerImageSize >= obs1Dstrect.x 
			 && playerDstrect.x <= obs1Dstrect.x + obsWidth - 2) 
			{
				if (playerDstrect.y <= obs1Dstrect.y + obsHeight
					|| playerDstrect.y + playerImageSize >= obs2Dstrect.y + 2) {
					gameRunning = false;
				}
			}
			else if (playerDstrect.x + playerImageSize >= obs3Dstrect.x
				&& playerDstrect.x <= obs3Dstrect.x + obsWidth - 2)
			{
				if (playerDstrect.y <= obs3Dstrect.y + obsHeight
					|| playerDstrect.y + playerImageSize >= obs4Dstrect.y + 2) {
					gameRunning = false;
				}
			}
			// Collision Player-Finish
			if (playerDstrect.x + playerImageSize >= finishDstrect.x) 
			{
				gameRunning = false;
				win = true;
			}

			// Obs moving direction
			if (changeDirection)
			{
				if (obs1Dstrect.y > -100)
					changeDirection = !changeDirection;
			} else 
			{
				if (obs1Dstrect.y < -140)
					changeDirection = !changeDirection;
			}
		}
		// Win? Lose?
		if(!gameRunning && !quit)
			if (!win) 
			{
				SDL_Surface* lose = SDL_LoadBMP("loseMessage.bmp");
				SDL_Texture* loseTexture = SDL_CreateTextureFromSurface(renderer, lose);
				SDL_Rect loseDstrect = { windowWidth / 2 - msWidth / 2,
										 windowHeight / 2 - msHeight / 2,
										 msWidth, 
										 msHeight };

				SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, loseTexture, NULL, &loseDstrect);
				SDL_RenderPresent(renderer);
				SDL_Delay(1200);
				SDL_DestroyTexture(loseTexture);
				SDL_FreeSurface(lose);

				playerDstrect.x = wallLimit + playerSpeed;
				playerDstrect.y = windowHeight / 2;
				gameRunning = gameRunning = true;
			}


		SDL_RenderClear(renderer);
		

		if (win) 
		{
			SDL_Surface* win = SDL_LoadBMP("winMessage.bmp");
			SDL_Texture* winTexture = SDL_CreateTextureFromSurface(renderer, win);
			SDL_Rect winDstrect = { windowWidth / 2 - msWidth / 2,
				windowHeight / 2 - msHeight / 2,
				msWidth,
				msHeight };

			SDL_RenderCopy(renderer, winTexture, NULL, &winDstrect);
			SDL_RenderPresent(renderer);
			SDL_Delay(4000);
		}
		else 
		{
			SDL_RenderCopy(renderer, playerTexture, NULL, &playerDstrect);
			SDL_RenderCopy(renderer, obs1Texture, NULL, &obs1Dstrect);
			SDL_RenderCopy(renderer, obs2Texture, NULL, &obs2Dstrect);
			SDL_RenderCopy(renderer, obs3Texture, NULL, &obs3Dstrect);
			SDL_RenderCopy(renderer, obs4Texture, NULL, &obs4Dstrect);
			SDL_RenderCopy(renderer, finishTexture, NULL, &finishDstrect);
			SDL_RenderPresent(renderer);
		}
	}
	// To clean up every resource that we initialise.
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(obs1Texture);
	SDL_DestroyTexture(obs2Texture);
	SDL_DestroyTexture(obs3Texture);
	SDL_DestroyTexture(obs4Texture);
	SDL_DestroyTexture(finishTexture);
	SDL_FreeSurface(player);
	SDL_FreeSurface(obs1);
	SDL_FreeSurface(obs2);
	SDL_FreeSurface(obs3);
	SDL_FreeSurface(obs4);
	SDL_FreeSurface(finish);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}