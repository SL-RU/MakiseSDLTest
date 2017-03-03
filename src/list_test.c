#include "list_test.h"
#include "makise_gui.h"

MButton butt[4];
MCanvas canv[3];
MLable  labls[3];
MTextField tf[3];
MSList   list[3];
MSlider  slider[3];
MTabs tabs;

char* sample_string = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";


MakiseStyle button_style =
{
    MC_White,
    &F_Arial24,
    0,
    //bg       font     border   double_border
    {MC_Black, MC_Gray, MC_Gray, 0},  //unactive
    {MC_Black, MC_White, MC_White, 0},//normal
    {MC_White, MC_Green, MC_White, 0}, //focused
    {MC_Green, MC_White, MC_White, 0}, //active
};
MakiseStyle canvas_style =
{
    MC_White,
    &F_Arial24,
    0,
    //bg       font     border   double_border
    {MC_Black, MC_Gray, MC_Gray,    0},  //unactive
    {MC_Gray, MC_White, MC_White, 0},  //normal
    {MC_Black, MC_White, MC_White,   0},  //focused
    {MC_Black, MC_White, MC_White, 0},  //active
};
MakiseStyle lable_style =
{
    MC_White,
    &F_Arial15,
    0,
    //bg       font     border   double_border
    {MC_Gray, MC_Gray, MC_Gray, 0},  //unactive
    {MC_Black, MC_White, MC_Black, 0},//normal
    {MC_Green, MC_White, MC_Blue, 0}, //focused
    {MC_Black, MC_Green, MC_Black, 0}, //active
};
MakiseStyle text_style =
{
    MC_White,
    &F_Arial15,
    3,
    //bg       font     border   double_border
    {MC_Black, MC_White, MC_Gray, 0},  //unactive
    {MC_Black, MC_White, MC_Green, 0},  //unactive
    {0, 0, 0, 0}, //focused
    {0, 0, 0, 0}, //active
};
MakiseStyle slider_style =
{
    MC_White,
    &F_Arial15,
    3,
        //bg       font     border   double_border
    {MC_Gray, MC_Gray, MC_Gray, 0},  //unactive
    {MC_Black, MC_White, MC_Black, 0},//normal
    {MC_Blue, MC_White, MC_White, 0}, //focused
    {MC_Black, MC_Green, MC_Black, 0}, //active
};

char *t_ok = "OK",
    *t_canc = "Cancel",
    *t_add = "Add",
    *t_remove = "Remove";


char *t_list[] = {
    "Hello",
    "Тест",//({210, 229, 241, 242, 0}),
    "string",
    "method",
    "Русские буквы?",
    "GPS",
    "SD card",
    "Camera",
    "insert",
    "ВАУ!"
};
MSList_Item l_source[10] = {{0}};
MSList_Item l_dest[1024] = {{0}};
int32_t slider_val[3] = {0};

MTabs_Tab tabs_source[] =
{
    {"Start", {0}},
    {"Sliders", {0}},
    {"Text", {0}},
};

uint32_t s_i = 0;
void b_add(MButton *b)
{
    tabs.selected = 1;
    for (uint32_t i = 0; i < 10; i++) {
	if(l_source[i].value)
	{
	    l_dest[s_i].id = s_i;
	    l_dest[s_i].text = l_source[i].text;
	    m_slist_add(&list[1], &l_dest[s_i]);
	    s_i ++;
	    return;
	}
    }
}
void b_rem(MButton *b)
{
    tabs.selected = 2;
    MSList_Item *i = list[1].items, *n = 0;
    while (i != 0) {
	n = i->next;
	      
	if(i->value)
	    m_slist_remove(&list[1], i);
	i = n;
    }
}
void l_add(MSList *l, MSList_Item *i)
{
    
    /* l_dest[s_i].id = s_i; */
    /* l_dest[s_i].text = i->text; */
    /* m_slist_add(&list[1], &l_dest[s_i]); */
    /* s_i ++; */
}
void l_rem(MSList *l, MSList_Item *i)
{
    /* if(list[1].selected) */
    /* 	m_slist_remove(l, i); */
}
void l_onselection(MSList *l, MSList_Item *i)
{
}

char slider_text[100] = {0};
void s_onchange(MSlider* b, uint32_t val)
{
    sprintf(slider_text, "%02d %02d %03d", slider_val[0],
	    slider_val[1],
	    slider_val[2]);
}
    
void at_list_init(MakiseGUI *gui, MHost *host)
{
//    m_create_slist(&list[0], host->host, 3, 10, 156, 145, "lol", &l_onselection, &l_add, MSList_RadioButton, &canvas_style, &lable_style);

//    m_create_slist(&list[1], host->host, 160, 10, 156, 145, 0, &l_onselection, &l_rem, MSList_Checkbox, &canvas_style, &lable_style);

    m_create_tabs(&tabs, host->host,
		  0, 10, 320, 200,
		  tabs_source, 3,
		  MTabs_Type_Left, 75,
		  &canvas_style);
    
    m_create_button(&butt[0], &tabs_source[0].cont, 10, 103, 100, 35, t_add, &b_add, 0, 0, &button_style);
    m_create_button(&butt[1], host->host, 115, 183, 100, 35, t_remove, &b_rem, 0, 0, &button_style);

    m_create_text_field(tf, &tabs_source[2].cont,
			5, 0, 310, 150,
			sample_string,
			&text_style);

    m_create_slider(slider, &tabs_source[1].cont,
		    10, 5, 150, 40,
		    &slider_val[0],
		    10,
		    0,
		    &s_onchange, 0,
		    &slider_style);
    m_create_slider(&slider[1], &tabs_source[1].cont,
		    10, 50, 150, 12,
		    &slider_val[1],
		    10,
		    0,
		    &s_onchange, 0,
		    &slider_style);
    m_create_slider(&slider[2], &tabs_source[1].cont,
		    170, 5, 18, 150,
		    &slider_val[2],
		    100,
		    0,
		    &s_onchange, 0,
		    &slider_style);

    m_create_lable(labls, &tabs_source[1].cont,
		   10, 70, 150, 40,
		   slider_text,
		   &lable_style);
		   
		   

    for (uint32_t i = 0; i < 10; i++) {
	//l_source[i].text = t_list[i];
    }

    s_onchange(0, 0);
//    m_slist_set_array(list, l_source, 10);
//    m_slist_set_list(&list[1], 0);

    makise_g_focus(&butt[1].el, M_G_FOCUS_GET);
}






