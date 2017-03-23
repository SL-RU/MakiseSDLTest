#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdint.h>
#include "makise.h"
#include "makise_gui.h"
//#include "list_test.h"
#include "makise_sdl2.h"
#include "tests.h"

SDL_Renderer *renderer;
SDL_Window *window;
SDL_Surface *screen;

MakiseGUI* mGui;
MHost *host;
MakiseGUI    Gu;
MakiseBuffer Bu;
MakiseDriver Dr;
MHost hs;
MContainer co;

uint32_t bufff[960000] = {0};

void start_m();

int x = 0;
int y = 0;
char bu[100] = {0};

void mt_draw(MakiseGUI * g)
{
    for (uint32_t i = 0; i < 16; i++) {
	
//	makise_d_rect_filled(mGui->buffer, i * 10, 0, 10, 10, 0xFFFF, 0xFFFF);
    }
    sprintf(bu, "x: %d, y%d", x, y);
    //makise_d_string(mGui->buffer, bu, 100, 400, 400, MDTextPlacement_LeftUp, &F_Arial12, MC_Cyan);

    //at_list_u();
//    makise_g_host_call(host, M_G_CALL_DRAW);
}

MInputData inp_handler(MInputData d, MInputResultEnum res)
{
    if(d.event == M_INPUT_CLICK && res == M_INPUT_NOT_HANDLED)
    {
	printf("not h %d\n", d.key);
	if(d.key == M_KEY_LEFT)
	    makise_g_host_focus_prev(host);
	if(d.key == M_KEY_RIGHT)
	    makise_g_host_focus_next(host);
	if(d.key == M_KEY_UP)
	    makise_g_host_focus_prev(host);
	if(d.key == M_KEY_DOWN)
	    makise_g_host_focus_next(host);
	if(d.key == M_KEY_TAB_NEXT)
	    makise_g_host_focus_next(host);
	if(d.key == M_KEY_TAB_BACK)
	    makise_g_host_focus_prev(host);		    

    }
    return (MInputData){0};
}
uint8_t prsed = 0;
int main(void) {
    SDL_Event event;
    int i;

    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(320, 240, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    screen = SDL_GetWindowSurface(window);


    
    SDL_Surface *surface;
    
    surface = SDL_CreateRGBSurface(0, 320, 240, 16, 0b1111100000000000, 0b11111100000, 0b11111, 0b0);

    
    
    start_m();
    while (1) {
	makise_g_host_call(host, M_G_CALL_PREDRAW);
	makise_g_host_call(host, M_G_CALL_DRAW);
	mt_draw(0);
	makise_sdl2_draw(mGui);

	SDL_UpdateWindowSurface(window);

	
	//SDL_Delay(6);
	if(SDL_WaitEventTimeout(&event, 50))
	{
	    do
	    {
		x = event.motion.x;
		y = event.motion.y;

		if(prsed)
		{
		    MInputData d;
		    d.event = M_INPUT_PRESSING;
		    d.key = M_KEY_CURSOR;
		    d.time = 100;
		    d.cursor.x = x;
		    d.cursor.y = y;
		    makise_gui_input_send(host, d);
		}
		switch(event.type)
		{
		case SDL_QUIT:
		    SDL_DestroyRenderer(renderer);
		    SDL_DestroyWindow(window);
		    SDL_Quit();
		    return EXIT_SUCCESS;
		    break;
		case SDL_MOUSEBUTTONDOWN:
		    if(event.button.button == SDL_BUTTON_LEFT)
		    {
			printf("down\n");
			prsed = 1;
			MInputData d;
			d.event = M_INPUT_PRESSING;
			d.key = M_KEY_CURSOR;
			d.time = 100;
			d.cursor.x = x;
			d.cursor.y = y;
			makise_gui_input_send(host, d);
		    }
		    break;
		case SDL_MOUSEBUTTONUP:
		    if(event.button.button == SDL_BUTTON_LEFT &&
			prsed)
		    {
			printf("up\n");
			prsed = 0;
			MInputData d;
			d.event = M_INPUT_CLICK;
			d.key = M_KEY_CURSOR;
			d.time = 100;
			d.cursor.x = x;
			d.cursor.y = y;
			makise_gui_input_send(host, d);
		    }
		    break;
		case SDL_KEYDOWN:
		    switch (event.key.keysym.sym)
		    {
		    case SDLK_LEFT:
			makise_gui_input_send_button(host,
						     M_KEY_LEFT,
						     M_INPUT_CLICK, 100);
			break;
		    case SDLK_RIGHT:
			makise_gui_input_send_button(host,
						     M_KEY_RIGHT,
						     M_INPUT_CLICK, 100);
			break;
		    case SDLK_UP:
			makise_gui_input_send_button(host,
						     M_KEY_UP,
						     M_INPUT_CLICK, 100);
			break;
		    case SDLK_DOWN:
			makise_gui_input_send_button(host,
						     M_KEY_DOWN,
						     M_INPUT_CLICK, 100);
			break;
		    case SDLK_TAB:
			makise_gui_input_send_button(host,
						     M_KEY_TAB_NEXT,
						     M_INPUT_CLICK, 100);
			break;
		    case SDLK_RETURN:
			makise_gui_input_send_button(host,
						     M_KEY_OK,
						     M_INPUT_CLICK, 100);	      
			break;
		    case SDLK_ESCAPE:
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			return EXIT_SUCCESS;
			break;
		    case SDLK_EQUALS:
			makise_g_host_focus_next(host);
			break;
		    case SDLK_MINUS:
			makise_g_host_focus_prev(host);
			break;
		    }
		    
		}
	    }
	    while (SDL_PollEvent(&event));
	    makise_gui_input_perform(host);
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
    makise_gui_init(host);
    host->input.result_handler = inp_handler;
    
    //init driver structure
    makise_sdl2_driver(dr, 320, 240, screen);
    
    //malloc small buffer
    //dr->buffer = sb;//malloc(dr->size);
    //printf("%d\n", (uint32_t)(dr->size));
    //init gui struct

    uint32_t sz = makise_init(gu, dr, bu);
    //malloc big buffer
    bu->buffer = bufff;
    memset(bu->buffer, 0, sz);
    printf("%d\n", (uint32_t)(sz));


    //tests_hello_init(host);
    //tests_container_init(host);
    //tests_buttons_init(host);
    //tests_position_init(host);
    tests_slider_init(host);
    //tests_init(host);
    
    mGui = gu;
//    ili9340_init(gu);
    makise_start(gu);

    mGui->predraw = &mt_predraw;
    mGui->draw = &mt_draw;
    //makise_g_focus(&(butt[0].el), M_G_FOCUS_GET);

}
