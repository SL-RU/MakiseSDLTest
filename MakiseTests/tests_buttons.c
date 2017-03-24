#include "tests.h"


static char text[][100] = {
    "makise",
    "gui", 
    "test",
    "wow click",
    "so button",
    "amaze",
    "excite"
};
static char labtext[][100] = {
    "clicked:",
    "on key:",
    "on focus:"
};
static char lbuffer[3][100] = {"", "", ""};
static char tg_text[] = "send click events";
static char about[] = "This sample shows how to create buttons and handle their events. ";
static MButton buttons[7];
static MLable lable[6];
static MToggle toggle[1];
static MTextField textfield;

static void click(MButton* b)
{
    lable[3].text = b->text;
}
static uint8_t onkey(MButton* b, MInputData data)
{
    sprintf(lbuffer[1], "%s key: %d event: %d",
	    b->text, data.key, data.event);
    //return 1 if you want click event be executed
    return toggle->state; //if send click events enabled
}
static void onfocus(MButton* b, MFocusEnum type)
{
    //when focus recieved or leaved
    sprintf(lbuffer[2], "%s type: %d",
	    b->text, type);

}
void tests_buttons_init(MHost *h)
{
    //description
    m_create_text_field(&textfield,  //pointer to the structure
			h->host, //container
			mp_rel(0, 0,    //position
			       320, 50), //width, height
			about,    //text
			&ts_textfield//style
	);

    //BUTTONS: 
    for (int i = 0; i < 3; i++) {
	m_create_button(&buttons[i], //pointer to the structure
			h->host, //container
			mp_rel(10 + 100*i, 53, //position
			       85, 30), //width,height
			text[i],   //text
			//events:
			&click, //click event
			&onkey, //event when key pressed on element
			&onfocus, //when focus recieved / loosed
			&ts_button //style
	    );
    }

    //lables
    //click
    m_create_lable(&lable[0], //pointer to the structure
		   h->host, //container
		   mp_rel(0, 210, 100, 30), //position + sizes
		   labtext[0], //text
		   &ts_lable //style
	);
    //onkey
    m_create_lable(&lable[1], h->host,
		   mp_rel(0, 180, 100, 30),
		   labtext[1], &ts_lable);
    //onfocus
    m_create_lable(&lable[2], h->host,
		   mp_rel(0, 150, 100, 30),
		   labtext[2], &ts_lable);
    ///output
    //click
    m_create_lable(&lable[3], h->host,
		   mp_rel(100, 210, 220, 30), //position + sizes
		   0, &ts_lable);
    //onkey
    m_create_lable(&lable[4], h->host,
		   mp_rel(80, 180, 240, 30), //position + sizes
		   lbuffer[1], &ts_lable);
    //onfocus
    m_create_lable(&lable[5], h->host,
		   mp_rel(100, 150, 220, 30), //position + sizes
		   lbuffer[2], &ts_lable);

    m_create_toggle(toggle, h->host,
		    mp_rel(10, 120, 220, 30),
		    tg_text,
		    0, &ts_button);
}
