#include "tests.h"

static MTabs tabs;
static MTabs_Tab tabs_t[] =
{
    {"Simple"},
    {"Radio Button"},
    {"Check boxes"},
    {"Dynamic list"},
};
static char status_buf[100] = {0};

static MSList list[4];
static MLable labl[1];
static MButton butt[4];

static MSList_Item sample_1[] = {
    {"No proxy"},
    {"Auto-detect proxy settings"},
    {"Use system proxy settings"},
    {"Manual proxy configuration"},
    {"Automatic proxy configuration URL"}
};
static MSList_Item sample_2[] = {
    {"Milk"},
    {"Eggs"},
    {"Cup water"},
    {"Teaspun baking soda"},
    {"Cup butter"},
    {"Flour"}
};
static MSList_Item sample_3[40] = {};
static char *sample_words[] ={
    "tiger", "lion", "elephant", "zebra", "horse", 
    "camel", "deer", "crocodile", "rabbit", "cat"  };
static uint32_t sample_3_i = 0; //index 
static uint32_t sample_3_w = 0; //word index

//event when button was clicked
static void l_click(MSList *l, MSList_Item *selected)
{
    sprintf(status_buf, "Clicked %s", selected->text);
    printf(status_buf);
}
static void l_select(MSList *l, MSList_Item *selected)
{
    sprintf(status_buf, "Selected %s", selected->text);
}
static MSList_Item *lst;
static void add(MSList_Item * it, char* c)
{
    it->prev = 0;
    it->next = 0;
    it->text = c;

    m_slist_add(&list[3], it);
}

static void b_add(MButton *b)
{
    if(sample_3_i > 38)
	return;
    add(&sample_3[sample_3_i + 1], sample_words[sample_3_w]);
    sample_3_w = (sample_3_w + 1) % 10;
    sample_3_i ++;
}
static void b_remove(MButton *b)
{
    if(list[3].selected != 0)
	m_slist_remove(&list[3], list[3].selected);
}

void tests_slist_init(MHost *h) 
{
    m_create_tabs(&tabs, h->host, mp_sall(0,0,0,30),
		  tabs_t, 4, MTabs_Type_Up, 20, &ts_tabs);
    m_create_lable(labl, h->host,
		   mp_shor(0, 0, 210, 30),
		   status_buf, &ts_lable);
    {
	//Simple list
	m_create_slist(&list[0], &tabs_t[0].cont,
		       mp_sall(0,0,0,0), //position
		       "List:", //header
		       &l_select, &l_click, //events
		       MSList_List,
		       &ts_canvas, &ts_button);
	//set list of tests as sample source
	m_slist_set_array(&list[0], tests_items, tests_items_len);
    }
    {
	//Simple list
	m_create_slist(&list[1], &tabs_t[1].cont,
		       mp_sall(0,0,0,0), //position
		       "Select one:", //header
		       &l_select, &l_click, //events
		       MSList_RadioButton,
		       &ts_canvas, &ts_button);
	m_slist_set_array(&list[1], sample_1, 5);
    }
    {
	//Simple list
	m_create_slist(&list[2], &tabs_t[2].cont,
		       mp_sall(0,0,0,0), //position
		       "Select multiple elements:", //header
		       &l_select, &l_click, //events
		       MSList_Checkbox,
		       &ts_canvas, &ts_button);
	m_slist_set_array(&list[2], sample_2, 6);
    }
    {
	//Simple list
	m_create_slist(&list[3], &tabs_t[3].cont,
		       mp_sall(0,0,0,30), //position
		       "You can add or delete items:", //header
		       &l_select, &l_click, //events
		       MSList_List,
		       &ts_canvas, &ts_button);
	
	sample_3->next = 0;
	sample_3->prev = 0;
	sample_3->text = "animals";
	lst = sample_3;
	
	m_slist_set_list(&list[3], sample_3);
	
	m_create_button(&butt[0], &tabs_t[3].cont,
			mp_anc(0, 0, 70, 30, MPositionAnchor_LeftDown),
			"Add", 
			&b_add, 0, 0,
			&ts_button); 
	m_create_button(&butt[1], &tabs_t[3].cont,
			mp_anc(70, 0, 100, 30, MPositionAnchor_LeftDown),
			"Remove", 
			&b_remove, 0, 0,
			&ts_button); 

    }

//    makise_g_focus(&list.el, M_G_FOCUS_GET);
    /* m_create_canvas(canv, h->host, */
    /* 		    mp_cust(0, 0, 100, MPositionStretch_Right, */
    /* 			    0, 0, 0, MPositionStretch_UpDown), */
    /* 		    &ts_canvas); */
    /* m_create_button(&butt[0], &canv->cont, */
    /* 		    mp_shor(0, 0, 0, 30), */
    /* 		    "Type", */
    /* 		    &b_type, 0, 0, */
    /* 		    &ts_button); */
    /* m_create_button(&butt[1], &canv->cont, */
    /* 		    mp_shor(0, 0, 35, 30), */
    /* 		    "Source", */
    /* 		    &b_type, 0, 0, */
    /* 		    &ts_button); */
}
