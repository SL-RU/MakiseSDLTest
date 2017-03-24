#include "tests.h"



static char text[] = "Select test:"; //lable's text

//MButton tests_selector_b; //button structure
//MLable tests_selector_lable; //lable structure

static MSList list; //list

//event when button was clicked
void ts_selector_click(MSList *l, MSList_Item *selected)
{
    if(selected != 0)
    {
	tests_run(selected->value);
    }
}

void tests_selector_init(MHost *h)
{
    m_create_slist(&list, h->host,
		   mp_sall(1,1,1,1), //position
		   text, //header
		   0, &ts_selector_click, //events
		   MSList_List,
		   &ts_canvas, &ts_button);

    m_slist_set_array(&list, tests_items, tests_items_len);

    makise_g_focus(&list.el, M_G_FOCUS_GET);
}
