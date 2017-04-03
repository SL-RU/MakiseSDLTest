#include "tests.h"

static char* l_type[] =
{
    "List",
    "Radio buttons",
    "Checkbox"
};

static MSList list;
static MLable labl[1];
static MButton butt[4];

static MCanvas canv[1];

//event when button was clicked
static void l_click(MSList *l, MSList_Item *selected)
{
    labl->text = "click";
}
static void l_select(MSList *l, MSList_Item *selected)
{
    labl->text = "select";
}
static void b_type(MButton *b)
{
    list.type = (list.type + 1) % 3;
}

void tests_slist_init(MHost *h)
{
    m_create_slist(&list, h->host,
		   mp_sall(1,100,1,40), //position
		   "List:", //header
		   &l_select, &l_click, //events
		   MSList_RadioButton,
		   &ts_canvas, &ts_button);

    m_create_lable(labl, h->host,
		   mp_shor(0, 0, 205, 30),
		   "LOL", &ts_lable);
    
    m_slist_set_array(&list, tests_items, tests_items_len);

//    makise_g_focus(&list.el, M_G_FOCUS_GET);
    m_create_canvas(canv, h->host,
		    mp_cust(0, 0, 100, MPositionStretch_Right,
			    0, 0, 0, MPositionStretch_UpDown),
		    &ts_canvas);
    m_create_button(&butt[0], &canv->cont,
		    mp_shor(0, 0, 0, 30),
		    "Type",
		    &b_type, 0, 0,
		    &ts_button);
    m_create_button(&butt[1], &canv->cont,
		    mp_shor(0, 0, 35, 30),
		    "Source",
		    &b_type, 0, 0,
		    &ts_button);
}
