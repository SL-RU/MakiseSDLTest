#include "tests.h"


char tests_buttons_text[][100] = {
    "makise",
    "gui", 
    "test",
    "wow click",
    "so button",
    "amaze",
    "excite"
};
MButton tests_buttons_b[7];
MLable ts_buttons_lable[1];
MTextField ts_buttons_text;

void  ts_buttons_click(MButton* b)
{
    ts_buttons_lable->text = b->text;
}
void tests_buttons_init(MHost *h)
{
    m_create_text_field(&ts_buttons_text,  //pointer to the structure
			h->host, //container
			0, 0,    //position
			240, 50, //width, height
			"ff",    //text
			&ts_textfield//style
	);

    for (int i = 0; i < 3; i++) {
	m_create_button(&tests_buttons_b[i], //pointer to the structure
			h->host, //container
			10 + 100*i, 60, //position
			85, 30, //width,height
			tests_buttons_text[i],   //text
			&ts_buttons_click, //click event
			0, //event when key pressed on element
			0, //when focus recieved / loosed
			&ts_button //style
	    );
    }
    for (int i = 3; i < 7; i++) {
	//count width of the text
	uint16_t w = makise_d_string_width(tests_buttons_text[i], //text
					   MDTextAll, //len of text. MDTextAll = max len
					   ts_button.font); //width of text
	m_create_button(&tests_buttons_b[i], //pointer to the structure
			h->host, //container
			10, 5 + i*35, //position
			w + 10, 30, //width,height
			tests_buttons_text[i],   //text
			&ts_buttons_click, //click event
			0, //event when key pressed on element
			0, //when focus recieved / loosed
			&ts_button //style
	    );
    }
    m_create_lable(ts_buttons_lable, //pointer to the structure
		   h->host, //container
		   10, 270, 200, 30, //position + sizes
		   0, //text
		   &ts_lable //style
	);
}
