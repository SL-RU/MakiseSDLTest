#include "tests.h"

char tests_position_button_text[][100] =
{
    "Size",
    "Position",
    "Type"
};      //button's text
char tests_position_mode_text[][150] =
{
    "mp_sall - stretch in all directions",
    "shor - stretch only in horizontal",
    "sver - stretch only in vertical",
    "rel - simple relative position. Anchor is left up corner",
    "anc - simple relative position. Anchor is custom. In this sample RightDown is choosen.",
    "cust - fully customizable. You can select stretch type or anchor, margins and size. In this sample choosen vertical stretch and anchor was right side"
};

MButton tests_position_b[3]; //button structure
MLable tests_position_lable; //lable structure

MCanvas tests_position_c; //parent container for test text field
MTextField tests_position_t; //test text
char *tests_position_tt = "This is example of positioning your elements.\n\n- If focused \"Size\" button then arrow buttons are changing size of parent container\n- Focused \"Position\" will move parent container\n- Click on\"Type\" will change current positioning type.\n\nClick \"Type\" to start"; //test text

uint32_t ts_position_mode = 0;
void  ts_position_upd() //update text on textfield
{
    tests_position_t.text = tests_position_mode_text[ts_position_mode];
}
void ts_position_set(uint8_t t) //set position mode
{
    ts_position_mode = t = t % 6;
    switch (t) {
    case 0:
	//stretch in all directions
	tests_position_t.el.position = mp_sall(30, 30, 30, 30);
	break;
    case 1:
	//stretch only in horizontal
	tests_position_t.el.position = mp_shor(10, 10, 10, 100);
	break;
    case 2:
	//"sver - stretch only in vertical
	tests_position_t.el.position = mp_sver(10, 180, 10, 10);
	break;	
    case 3:
	//rel - simple relative position. Anchor is left up corner
	tests_position_t.el.position = mp_rel(10, 10, 180, 130);
	break;
    case 4:
	//anc - simple relative position. Anchor is custom. In this sample RightDown is choosen.
	tests_position_t.el.position = mp_anc(10, 10, 200, 100, MPositionAnchor_RighDown);
	break;
    case 5:
	//cust - fully customizable. You can select stretch type or anchor, positions and size. In this sample choosen vertical stretch and anchor was right side
	tests_position_t.el.position = mp_cust(0, 30, 170, MPositionStretch_Right,
					     20, 20, 0, MPositionStretch_UpDown);
	break;
    }
    ts_position_upd();
}
//event when button was clicked
void  ts_position_click(MButton* b) //b - button wich was clicked
{
    ts_position_set(ts_position_mode+1);
}
uint8_t ts_position_onkey(MButton* b, MInputData d) //b - button wich was clicked
{
    int x = 0, y = 0;
    if(d.event == M_INPUT_CLICK)
    {
	switch (d.key) {
	case M_KEY_LEFT:
	    x --;
	    break;
	case M_KEY_RIGHT:
	    x ++;
	    break;
	case M_KEY_UP:
	    y --;
	    break;
	case M_KEY_DOWN:
	    y ++;
	    break;
	default:
	    return 0;
	}
    }
    if(b == &tests_position_b[0])
    {
	if((int32_t)(tests_position_c.el.position.width) > -x)
	    tests_position_c.el.position.width += x;
	if((int32_t)(tests_position_c.el.position.height) > -y)
	    tests_position_c.el.position.height += y;
	return 2;
    } else if(b == &tests_position_b[1])
    {
	tests_position_c.el.position.left += x;
	tests_position_c.el.position.up += y;
	return 2;
    }
    return 1;
}

void tests_position_init(MHost *h)
{
	m_create_button(&tests_position_b[0], //pointer to the structure
			h->host, //container
			mp_rel(5, 5, //position(x,y)
			       90, 30), //width,height
			tests_position_button_text[0],   //text
			//events:
			&ts_position_click, //click event
			&ts_position_onkey, //event when key pressed on element
			0, //when focus recieved / loosed
			&ts_button); //style	
	m_create_button(&tests_position_b[1], //pointer to the structure
			h->host, //container
			mp_rel(105, 5, //position(x,y)
			       90, 30), //width,height
			tests_position_button_text[1],   //text
			//events:
			&ts_position_click, //click event
			&ts_position_onkey, //event when key pressed on element
			0, //when focus recieved / loosed
			&ts_button); //style
	m_create_button(&tests_position_b[2], //pointer to the structure
			h->host, //container
			mp_rel(205, 5, //position(x,y)
			       90, 30), //width,height
			tests_position_button_text[2],   //text
			//events:
			&ts_position_click, //click event
			0, //event when key pressed on element
			0, //when focus recieved / loosed
			&ts_button); //style

	m_create_canvas(&tests_position_c,
			h->host,
			mp_rel(10, 40, 300, 180),
			&ts_button);
	m_create_text_field(&tests_position_t, &tests_position_c.cont,
			    mp_sall(10,10,10,10),
			    tests_position_tt,
			    &ts_textfield);
	//ts_position_set(0);
}
