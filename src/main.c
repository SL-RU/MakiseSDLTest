#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdint.h>
#include "makise.h"
#include "makise_gui.h"
#include "list_test.h"
#include "makise_sdl2.h"

SDL_Renderer *renderer;
SDL_Window *window;
MakiseGUI* mGui;
MHost *host;
MakiseGUI    Gu;
MakiseBuffer Bu;
MakiseDriver Dr;
MHost hs;
MContainer co;

uint32_t bufff[960000] = {0};

void start_m();

void mt_draw(MakiseGUI * g)
{
    for (uint32_t i = 0; i < 16; i++) {
	
	makise_d_rect_filled(mGui->buffer, i * 10, 0, 10, 10, 0xFFFF, 0xFFFF);
    }

//    makise_g_host_call(host, M_G_CALL_DRAW);
}
int main(void) {
    SDL_Event event;
    int i;

    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    start_m();
    while (1) {
	makise_g_host_call(host, M_G_CALL_PREDRAW);
	makise_g_host_call(host, M_G_CALL_DRAW);
	mt_draw(0);
	makise_sdl2_draw(mGui);
	SDL_RenderPresent(renderer);
	SDL_Delay(20);
        if(SDL_PollEvent(&event))
	{
	    switch(event.type)
	    {
	    case SDL_QUIT:
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_SUCCESS;
		break;
	    case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
		    if(makise_g_host_input
		       (host,
			(MInputData){M_KEY_LEFT, M_INPUT_CLICK, 100, 0})
		       == M_INPUT_NOT_HANDLED)
		    {
			makise_g_cont_focus_prev(host->host);
		    }
		    break;
		case SDLK_RIGHT:
		    if(makise_g_host_input
		       (host,
			(MInputData){M_KEY_RIGHT, M_INPUT_CLICK, 100, 0})
		       == M_INPUT_NOT_HANDLED)
		    {
			makise_g_cont_focus_next(host->host);
		    }
		    break;
		case SDLK_UP:
		    if(makise_g_host_input
		       (host,
			(MInputData){M_KEY_UP, M_INPUT_CLICK, 100, 0})
		       == M_INPUT_NOT_HANDLED)
		    {
			makise_g_cont_focus_prev(host->host);
		    }
		    break;
		case SDLK_DOWN:
		    if(makise_g_host_input
		       (host,
			(MInputData){M_KEY_DOWN, M_INPUT_CLICK, 100, 0})
		       == M_INPUT_NOT_HANDLED)
		    {
			makise_g_cont_focus_next(host->host);
		    }
		    break;
		case SDLK_TAB:
		    if(makise_g_host_input
		       (host,
			(MInputData){M_KEY_TAB_NEXT, M_INPUT_CLICK, 100, 0})
		       == M_INPUT_NOT_HANDLED)
		    {
			makise_g_cont_focus_next(host->host);
		    }
		    break;
		case SDLK_RETURN:
		    makise_g_host_input
			(host,
			 (MInputData){M_KEY_OK, M_INPUT_CLICK, 100, 0});
		      
		    break;
		case SDLK_ESCAPE:
		    SDL_DestroyRenderer(renderer);
		    SDL_DestroyWindow(window);
		    SDL_Quit();
		    return EXIT_SUCCESS;
		
		    break;
		}
	    }
	}
    }

}
void mt_predraw(MakiseGUI * g)
{
//    canv[0].el.position.x = (canv[0].el.position.x+1) %150;
//    makise_g_host_call(host, M_G_CALL_PREDRAW);
//    printf("p");
}

void start_m()
{
    MakiseGUI    * gu = &Gu;//malloc(sizeof(MakiseGUI));
    MakiseBuffer * bu = &Bu;//malloc(sizeof(MakiseBuffer));
    MakiseDriver * dr = &Dr;//malloc(sizeof(MakiseDriver));
    host = &hs;//malloc(sizeof(MHost));
    host->host = &co;//malloc(sizeof(MContainer));
    host->host->gui = gu;

    //init driver structure
    makise_sdl2_driver(dr, 800, 600, renderer);
    //malloc small buffer
    //dr->buffer = sb;//malloc(dr->size);
    //printf("%d\n", (uint32_t)(dr->size));
    //init gui struct

    uint32_t sz = makise_init(gu, dr, bu);
    //malloc big buffer
    bu->buffer = bufff;
    memset(bu->buffer, 0, sz);
    printf("%d\n", (uint32_t)(sz));


    at_list_init(gu, host);
    
    
    mGui = gu;
//    ili9340_init(gu);
    makise_start(gu);

    mGui->predraw = &mt_predraw;
    mGui->draw = &mt_draw;
    //makise_g_focus(&(butt[0].el), M_G_FOCUS_GET);

}
