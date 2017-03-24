#include "tests.h"

static char button_text[][100] =
{
    "Size",
    "Position",
    "Type"
};      //button's text
static char mode_text[][150] =
{
    "mp_sall - stretch in all directions",
    "shor - stretch only in horizontal",
    "sver - stretch only in vertical",
    "rel - simple relative position. Anchor is left up corner",
    "anc - simple relative position. Anchor is custom. In this sample RightDown is choosen.",
    "cust - fully customizable. You can select stretch type or anchor, margins and size. In this sample choosen vertical stretch and anchor is the right side"
};

static MButton button[3]; //button structure

static MCanvas canvas; //parent container for test text field
static MTextField text; //test text
static char *testtext = "This is example of positioning your elements.\n\n- If focused \"Size\" button then arrow buttons will change size of parent container\n- Focused \"Position\" will move parent container\n- Click on\"Type\" will change current positioning type.\n\nClick \"Type\" to start"; //test text

static uint32_t mode = 0;
void  ts_position_upd() //update text on textfield
{
    text.text = mode_text[mode];
}
void ts_position_set(uint8_t t) //set position mode
{
    mode = t = t % 6;
    switch (t) {
    case 0:
	//stretch in all directions
	text.el.position = mp_sall(30, 30, 30, 30);
	break;
    case 1:
	//stretch only in horizontal
	text.el.position = mp_shor(10, 10, 10, 100);
	break;
    case 2:
	//"sver - stretch only in vertical
	text.el.position = mp_sver(10, 180, 10, 10);
	break;	
    case 3:
	//rel - simple relative position. Anchor is left up corner
	text.el.position = mp_rel(10, 10, 180, 130);
	break;
    case 4:
	//anc - simple relative position. Anchor is custom. In this sample RightDown is choosen.
	text.el.position = mp_anc(10, 10, 200, 100, MPositionAnchor_RighDown);
	break;
    case 5:
	//cust - fully customizable. You can select stretch type or anchor, positions and size. In this sample choosen vertical stretch and anchor was right side
	text.el.position = mp_cust(0, 30, 170, MPositionStretch_Right,
					       20, 20, 0, MPositionStretch_UpDown);
	break;
    }
    ts_position_upd();
}

//event when button was clicked
void  ts_position_click(MButton* b) //button - button wich was clicked
{
    ts_position_set(mode+1);
}
uint8_t ts_position_onkey(MButton* b, MInputData d) //button - button wich was clicked
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
    if(b == &button[0])
    {
	if((int32_t)(canvas.el.position.width) > -x)
	    canvas.el.position.width += x;
	if((int32_t)(canvas.el.position.height) > -y)
	    canvas.el.position.height += y;
	return 2;
    } else if(b == &button[1])
    {
	canvas.el.position.left += x;
	canvas.el.position.up += y;
	return 2;
    }
    return 1;
}

void tests_position_init(MHost *h)
{
    m_create_button(&button[0], //pointer to the structure
		    h->host, //container
		    mp_rel(5, 5, //position(x,y)
			   90, 30), //width,height
		    button_text[0],   //text
		    //events:
		    &ts_position_click, //click event
		    &ts_position_onkey, //event when key pressed on element
		    0, //when focus recieved / loosed
		    &ts_button); //style	
    m_create_button(&button[1], //pointer to the structure
		    h->host, //container
		    mp_rel(105, 5, //position(x,y)
			   90, 30), //width,height
		    button_text[1],   //text
		    //events:
		    &ts_position_click, //click event
		    &ts_position_onkey, //event when key pressed on element
		    0, //when focus recieved / loosed
		    &ts_button); //style
    m_create_button(&button[2], //pointer to the structure
		    h->host, //container
		    mp_rel(205, 5, //position(x,y)
			   90, 30), //width,height
		    button_text[2],   //text
		    //events:
		    &ts_position_click, //click event
		    0, //event when key pressed on element
		    0, //when focus recieved / loosed
		    &ts_button); //style

    m_create_canvas(&canvas,
		    h->host,
		    mp_rel(10, 40, 300, 180),
		    &ts_button);
    m_create_text_field(&text, &canvas.cont,
			mp_sall(10,10,10,10),
			testtext,
			&ts_textfield);
    //ts_position_set(0);
}
