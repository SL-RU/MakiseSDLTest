#include "tests.h"


char tests_slider_button_text[][20] = {
    "Vertical",
    "Horizontal"
};      //button's text
char tests_slider_lable_text[100] = ""; //lable's text

MButton tests_slider_b; //button structure
MLable tests_slider_lable; //lable structure
MSlider tests_slider_s[3];

int32_t lll[3] = {0};

uint8_t k = 0;
//event when button was clicked
void  ts_slider_click(MButton* b) //b - button wich was clicked
{
    //create lable
    //remove button from the container
    //makise_g_cont_rem(&tests_slider_b.el);
    if(k)
    {
	for (int i = 0; i < 3; i++) {
	    tests_slider_s[i].el.position = mp_rel(10, 40 + i * 50, 200, 30);
	}
    }
    else
    {
	for (int i = 0; i < 3; i++) {
	    tests_slider_s[i].el.position = mp_rel(5 + 50*i,
						   40, 40, 190);
	}

    }
    k = !k;
}
void onchange(MSlider* b, uint32_t val)
{
    sprintf(tests_slider_lable_text, "lol %d %d %d", lll[0], lll[1], lll[2]);
}

void tests_slider_init(MHost *h)
{
	m_create_button(&tests_slider_b, //pointer to the structure
			h->host, //container
			mp_rel(10, 5, //position(x,y)
			       100, 30), //width,height
			tests_slider_button_text[0],   //text
			//events:
			&ts_slider_click, //click event
			0, //event when key pressed on element
			0, //when focus recieved / loosed
			&ts_button); //style
	m_create_lable(&tests_slider_lable, //pointer to lable's structure
		       h->host, //parent container. We'll put lable to the same container, where is our button
		       mp_rel(150, 0, //position(x,y)
			      170, 30), //width, height
		       tests_slider_lable_text, //lable's text
		   &ts_lable); //style
	m_create_slider(&tests_slider_s[0], h->host,
			mp_rel(5, 40, 30, 190),
			lll, 10, 0,
			&onchange,
			0,
			&ts_button);
	m_create_slider(&tests_slider_s[1], h->host,
			mp_rel(50, 40, 30, 190),
			&lll[1], 10, -10,
			&onchange,
			0,
			&ts_button);
	m_create_slider(&tests_slider_s[2], h->host,
			mp_rel(100, 40, 30, 190),
			&lll[2], 0, -10,
			&onchange,
			0,
			&ts_button);

}
