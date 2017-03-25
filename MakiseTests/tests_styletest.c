#include "tests.h"


static char text[] = "Click!";      //button's text
static char lable_text[] = ""; //lable's text

static MButton button; //button structure
static MLable lable[2]; //lable structure
static MSlider sliders[3];

static MCanvas canvas[2];

static MakiseStyle button_s =
{
    MC_White,
    &F_Arial24,
    0,
    //bg       font     border   double_border
    {MC_Black, MC_Gray, MC_Gray, 0},  //unactive
    {MC_Black, MC_White, MC_White, 0},//normal
    {MC_White, MC_Green, MC_White, 0}, //focused
    {MC_Green, MC_White, MC_White, 0}, //active
};

static MTabs tabs_e[1];
static MTabs_Tab tabs[] =
{
    {"element"},
    {"color"},
    {"test"}
};

static MSList lists[2];
static MSList_Item list_elements[] =
{
    {"button", 1},
    {"lable", 2},
    
};

//event when button was clicked
static void  click(MButton* b) //b - button wich was clicked
{

}
static int32_t cr = 0, cg = 0, cb = 0;

static void onchange(MSlider* b, uint32_t val)
{
    uint32_t c = (cr << 11) + (cg << 5) + cb;
    button_s.normal.bg_color = c;
    sprintf(lable_text, "r %02d g %02d b %02d", cr, cg, cb);
}


void tests_styletest_init(MHost *h)
{
    m_create_canvas(canvas, h->host, mp_sver(0, 90, 0, 0), &ts_canvas);
    {
	//red
	m_create_slider(sliders, &canvas->cont, mp_sver(5, 20, 5, 35),
			&cr, 0, 31,
			MSlider_Type_ReadWrite,
			&onchange, 0,
			&ts_slider);
	//blue
	m_create_slider(&sliders[1], &canvas->cont, mp_sver(35, 20, 5, 35),
			&cg, 0, 63,
			MSlider_Type_ReadWrite,
			&onchange, 0,
			&ts_slider);
	//green
	m_create_slider(&sliders[2], &canvas->cont, mp_sver(65, 20, 5, 35),
			&cb, 0, 31,
			MSlider_Type_ReadWrite,
			&onchange, 0,
			&ts_slider);
	m_create_lable(&lable[0], //pointer to the structure
		       &canvas->cont, //container
		       mp_cust(0, 0, 0, MPositionStretch_LeftRight,
			       0, 0, 20, MPositionStretch_Down),
		       lable_text, //text
		       &ts_textfield //style
	    );
    }

    m_create_canvas(&canvas[1], h->host, mp_sall(90, 0, 0, 0), &ts_canvas);

    m_create_tabs(tabs_e, &canvas[1].cont, mp_sall(0,0,0,0),
		  tabs, 3,
		  MTabs_Type_Up, 20,
		  &ts_canvas);
	
    m_create_button(&button, &tabs[1].cont,
		    mp_rel(30, 53, 85, 30), text,
		    &click, 
		    0, //event when key pressed on element
		    0, //when focus recieved / loosed
		    &button_s); //style

}
