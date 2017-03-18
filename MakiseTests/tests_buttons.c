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
char ts_buttons_tg_lbuffer[3][100] = {"", "", ""};
char ts_buttons_tg_text[] = "send click events";
char ts_buttons_about[] = "This sample shows how to create buttons and handle their events. ";
MButton tests_buttons_b[7];
MLable ts_buttons_lable[6];
MToggle ts_buttons_tg[1];
MTextField ts_buttons_text;

void  ts_buttons_click(MButton* b)
{
    ts_buttons_lable[3].text = b->text;
}
uint8_t ts_buttons_onkey(MButton* b, MInputData data)
{
    sprintf(ts_buttons_tg_lbuffer[1], "%s key: %d event: %d",
	    b->text, data.key, data.event);
    //return 1 if you want click event be executed
    return ts_buttons_tg->state; //if send click events enabled
}
void ts_buttons_onfocus(MButton* b, MFocusEnum type)
{
    //when focus recieved or leaved
    sprintf(ts_buttons_tg_lbuffer[2], "%s type: %d",
	    b->text, type);

}
void tests_buttons_init(MHost *h)
{
    //description
    m_create_text_field(&ts_buttons_text,  //pointer to the structure
			h->host, //container
			mp_rel(0, 0,    //position
			       320, 50), //width, height
			ts_buttons_about,    //text
			&ts_textfield//style
	);

    //BUTTONS: 
    for (int i = 0; i < 3; i++) {
	m_create_button(&tests_buttons_b[i], //pointer to the structure
			h->host, //container
			mp_rel(10 + 100*i, 53, //position
			       85, 30), //width,height
			tests_buttons_text[i],   //text
			//events:
			&ts_buttons_click, //click event
			&ts_buttons_onkey, //event when key pressed on element
			&ts_buttons_onfocus, //when focus recieved / loosed
			&ts_button //style
	    );
    }

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
		   mp_rel(80, 180, 240, 30), //position + sizes
		   ts_buttons_tg_lbuffer[1], &ts_lable);
    //onfocus
    m_create_lable(&ts_buttons_lable[5], h->host,
		   mp_rel(100, 150, 220, 30), //position + sizes
		   ts_buttons_tg_lbuffer[2], &ts_lable);

    m_create_toggle(ts_buttons_tg, h->host,
		    mp_rel(10, 120, 220, 30),
		    ts_buttons_tg_text,
		    0, &ts_button);
}
