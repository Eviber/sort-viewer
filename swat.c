#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>

#define WIN_H 1000
#define WIN_W 1000
#define TABSIZE 100

int		init(SDL_Window **win, SDL_Renderer **render)
{
	srand(time(NULL));
	if(SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "Error while initializing SDL: %s\n", SDL_GetError());
		return (1);
	}
	*win = SDL_CreateWindow("lolelo",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WIN_W, WIN_H, SDL_WINDOW_INPUT_GRABBED);
	if (!*win)
	{
		fprintf(stderr, "Error while creating window: %s\n", SDL_GetError());
		return (2);
	}
	*render = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED);
	if (!*render)
	{
		fprintf(stderr, "Error while creating renderer: %s\n", SDL_GetError());
		return (3);
	}
	return (0);
}

void	disptab(int *tab, SDL_Renderer *render, int sel)
{
	SDL_Rect	rect;
	int			i;

	SDL_SetRenderDrawColor(render, 103, 91, 194, 255);
	SDL_RenderClear(render);
	rect.w = WIN_W / TABSIZE;
	i = 0;
	while (i < TABSIZE)
	{
		rect.x = rect.w * i;
		rect.h = WIN_H / TABSIZE * tab[i] + rect.w;
		rect.y = WIN_H - rect.h;
		SDL_SetRenderDrawColor(render, 193, 102, 90, 255);
		if (i == sel)
			SDL_SetRenderDrawColor(render, 213, 122, 110, 255);
		SDL_RenderFillRect(render, &rect);
		rect.h = rect.w;
		if (i != sel)
		{
			SDL_SetRenderDrawColor(render, 91, 194, 103, 255);
			SDL_RenderFillRect(render, &rect);
		}
		i++;
	}
	SDL_RenderPresent(render);
}

int		bubble(int *tab, SDL_Renderer *render)
{
	int	i;
	int	tmp;
	static int stop = TABSIZE;

	i = 0;
	tmp = -1;
	while (i < stop - 1)
	{
		i++;
		if (tab[i] < tab[i - 1])
		{
			tmp = tab[i - 1];
			tab[i - 1] = tab[i];
			tab[i] = tmp;
		}
		disptab(tab, render, i);
	}
	stop--;
	return (tmp != -1);
}

int		quicksort(int *tab, int start, int end)
{
	int		pivot;
	int		val;

	return (0);
}

int		main(void)
{
	SDL_Window		*win;
	SDL_Renderer	*render;
	int				i;
	int				tmp;
	int				tab[TABSIZE];

	if((i = init(&win, &render)))
		return (i);
	i = 0;
	memset(tab, 0, TABSIZE * sizeof(int));
	while (i < TABSIZE)
	{
		tmp = rand() % TABSIZE;
		if (!tab[tmp])
			tab[tmp] = i++;
	}
	disptab(tab, render, -1);
	SDL_Delay(3000);
	while (bubble(tab, render));
	disptab(tab, render, -1);
	SDL_Delay(2000);
	SDL_Quit();
	return (0);
}
