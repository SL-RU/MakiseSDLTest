#include "tests.h"


static MButton button; //button structure
static MLable lable; //lable structure


//event when button was clicked
static void  click(MButton* b) //b - button wich was clicked
{
    //create lable
    m_create_lable(&lable, //pointer to lable's structure
		   b->el.parent, //parent container. We'll put lable to the same container, where is our button
		   mp_rel(100, 150, //position(x,y)
			  220, 30), //width, height
		   "Hello world!", //lable's text
		   &ts_lable); //style

    //remove button from the container
    makise_g_cont_rem(&button.el);
    
}

void tests_hello_init(MHost *h)
{
	m_create_button(&button, //pointer to the structure
			h->host, //container
			mp_rel(10 + 100, 53, //position(x,y)
			       85, 30), //width,height
			"Click!",   //text
			//events:
			&click, //click event
			0, //event when key pressed on element
			0, //when focus recieved / loosed
			&ts_button); //style
}
