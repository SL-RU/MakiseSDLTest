#include "tests.h"


char tests_margin_button_text[] = "Click!";      //button's text
char tests_margin_lable_text[] = "Margin world!"; //lable's text

MButton tests_margin_b; //button structure
MLable tests_margin_lable; //lable structure


//event when button was clicked
void  ts_margin_click(MButton* b) //b - button wich was clicked
{
    //create lable
    m_create_lable(&tests_margin_lable, //pointer to lable's structure
		   b->el.parent, //parent container. We'll put lable to the same container, where is our button
		   mp_rel(100, 150, //position(x,y)
			  220, 30), //width, height
		   tests_margin_lable_text, //lable's text
		   &ts_lable); //style

    //remove button from the container
    makise_g_cont_rem(&tests_margin_b.el);
    
}

void tests_margin_init(MHost *h)
{
	m_create_button(&tests_margin_b, //pointer to the structure
			h->host, //container
			mp_rel(10 + 100, 53, //position(x,y)
			       85, 30), //width,height
			tests_margin_button_text,   //text
			//events:
			&ts_margin_click, //click event
			0, //event when key pressed on element
			0, //when focus recieved / loosed
			&ts_button); //style
}
