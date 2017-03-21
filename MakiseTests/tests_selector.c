#include "tests.h"



char tests_selector_tt[] = "Select test!"; //lable's text

//MButton tests_selector_b; //button structure
//MLable tests_selector_lable; //lable structure

MSList tests_selector_l; //list

//event when button was clicked
void ts_selector_click(MSList *l, MSList_Item *selected)
{
    
}

void tests_selector_init(MHost *h)
{
    m_create_slist(&tests_selector_l, h->host,
		   mp_sall(0,0,0,0), //position
		   tests_selector_tt, //header
		   0, &ts_selector_click, //events
		   MSList_List,
		   &ts_canvas, &ts_button);

    m_slist_set_array(&tests_selector_l, tests_items, tests_items_len);
}
