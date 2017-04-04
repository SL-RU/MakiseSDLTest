#include "tests.h"


static char button_text[][20] = {
    "Vertical",
    "Horizontal",
    "+", "-"
};      //button's text
static char lable_text[100] = ""; //lable's text

static MButton buttons[3]; //button structure
static MLable lable; //lable structure
static MSlider sliders[3];

static int32_t values[3] = {0};

static uint8_t vertical = 0;
//event when button was clicked
static void click(MButton* b) //b - button wich was clicked
{
    //create lable
    //remove button from the container
    //makise_g_cont_rem(&buttons.el);
    if(vertical)
    {
	for (int i = 0; i < 3; i++) {
	    sliders[i].el.position = mp_shor(10, 30, 40 + i * 50, 30);
	}
    }
    else
    {
	for (int i = 0; i < 3; i++) {
	    sliders[i].el.position = mp_sver(5 + 50 * i, 30, 40, 50);
	}

    }
    vertical = !vertical;
    buttons[0].text = button_text[vertical];
}
static void onchange(MSlider* b, int32_t val)
{
    sprintf(lable_text, "values: %d %d %d", values[0], values[1], values[2]);
}
static void click_p(MButton* b)
{
    if(values[2] < 10)
	values[2] ++;
    onchange(0, 0);
}
static void click_m(MButton* b)
{
    if(values[2] > 0)
	values[2] --;
    onchange(0, 0);
}

void tests_slider_init(MHost *h)
{
	m_create_button(&buttons[0], //pointer to the structure
			h->host, //container
			mp_rel(10, 5, //position(x,y)
			       120, 30), //width,height
			button_text[0],   //text
			//events:
			&click, //click event
			0, //event when key pressed on element
			0, //when focus recieved / loosed
			&ts_button); //style
	m_create_lable(&lable, //pointer to lable's structure
		       h->host, //parent container. We'll put lable to the same container, where is our button
		       mp_rel(140, 0, //position(x,y)
			      180, 30), //width, height
		       lable_text, //lable's text
		   &ts_lable); //style


	//SLIDERS
	//sliders which you can interact with
	m_create_slider(&sliders[0], h->host,
			mp_nil(), //zero position
			values, 0, -10, //pointer to the value, min value, max value
			MSlider_Type_ReadWrite, //type of slider
			&onchange, //event when slider's value was changed
			0, //event when focus was changed
			&ts_slider); //style
	m_create_slider(&sliders[1], h->host,
			mp_nil(),
			&values[1], 10, -10,
			MSlider_Type_ReadWrite,
			&onchange,
			0,
			&ts_slider);
	//display only slider
	m_create_slider(&sliders[2], h->host,
			mp_nil(),
			&values[2], 0, 10,
			MSlider_Type_Read,
			&onchange,
			0,
			&ts_slider);


	m_create_button(&buttons[1], //pointer to the structure
			h->host, //container
			mp_rel(10, 205, //position(x,y)
			       100, 30), //width,height
			button_text[2],   //text
			//events:
			&click_p, //click event
			0, //event when key pressed on element
			0, //when focus recieved / loosed
			&ts_button); //style
	m_create_button(&buttons[2], //pointer to the structure
			h->host, //container
			mp_rel(110, 205, //position(x,y)
			       100, 30), //width,height
			button_text[3],   //text
			//events:
			&click_m, //click event
			0, //event when key pressed on element
			0, //when focus recieved / loosed
			&ts_button); //style

	
	onchange(0, 0);
	click(0);
	
}
