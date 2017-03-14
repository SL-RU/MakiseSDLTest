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
char ts_buttons_labt[][100] = {
    "clicked:",
    "on key:",
    "on focus:"
};
char ts_buttons_about[] = "This sample shows how to create buttons and handle their events. ";
MButton tests_buttons_b[7];
MLable ts_buttons_lable[6];
MTextField ts_buttons_text;

void  ts_buttons_click(MButton* b)
{
    ts_buttons_lable[3].text = b->text;
}
uint8_t ts_buttons_onkey(MButton* b, MInputData data)
{
    return 1;
}
void ts_buttons_onfocus(MButton* b, MFocusEnum type)
{
    
}
void tests_buttons_init(MHost *h)
{
    m_create_text_field(&ts_buttons_text,  //pointer to the structure
			h->host, //container
			mp_rel(0, 0,    //position
			       320, 50), //width, height
			ts_buttons_about,    //text
			&ts_textfield//style
	);

    for (int i = 0; i < 3; i++) {
	m_create_button(&tests_buttons_b[i], //pointer to the structure
			h->host, //container
			mp_rel(10 + 100*i, 53, //position
			       85, 30), //width,height
			tests_buttons_text[i],   //text
			&ts_buttons_click, //click event
			&ts_buttons_onkey, //event when key pressed on element
			&ts_buttons_onfocus, //when focus recieved / loosed
			&ts_button //style
	    );
    }
    /* for (int i = 3; i < 7; i++) { */
    /* 	//count width of the text */
    /* 	uint16_t w = makise_d_string_width(tests_buttons_text[i], //text */
    /* 					   MDTextAll, //len of text. MDTextAll = max len */
    /* 					   ts_button.font); //width of text */
    /* 	m_create_button(&tests_buttons_b[i], //pointer to the structure */
    /* 			h->host, //container */
    /* 			10, 5 + i*35, //position */
    /* 			w + 10, 30, //width,height */
    /* 			tests_buttons_text[i],   //text */
    /* 			&ts_buttons_click, //click event */
    /* 			0, //event when key pressed on element */
    /* 			0, //when focus recieved / loosed */
    /* 			&ts_button //style */
    /* 	    ); */
    /* } */

    //lables
    //click
    m_create_lable(&ts_buttons_lable[0], //pointer to the structure
		   h->host, //container
		   mp_rel(0, 210, 100, 30), //position + sizes
		   ts_buttons_labt[0], //text
		   &ts_lable //style
	);
    //onkey
    m_create_lable(&ts_buttons_lable[1], h->host,
		   mp_rel(0, 180, 100, 30),
		   ts_buttons_labt[1], &ts_lable);
    //onfocus
    m_create_lable(&ts_buttons_lable[2], h->host,
		   mp_rel(0, 150, 100, 30),
		   ts_buttons_labt[2], &ts_lable);
    ///output
    //click
    m_create_lable(&ts_buttons_lable[3], h->host,
		   mp_rel(100, 210, 220, 30), //position + sizes
		   0, &ts_lable);
    //onkey
    m_create_lable(&ts_buttons_lable[4], h->host,
		   mp_rel(100, 210, 220, 30), //position + sizes
		   0, &ts_lable);
    //onfocus
    m_create_lable(&ts_buttons_lable[5], h->host,
		   mp_rel(100, 210, 220, 30), //position + sizes
		   0, &ts_lable);
}
