#include "tests.h"


static char lable_text[30] = {0}; //lable's text
static char path_text[100] = {0}; //lable's text

static MLable lable[2]; //lable structure
static MSlider sliders[3];
static MButton button_invis[1]; //button structure

static MTextField textfield[1];
static char textfield_text[] = "MakiseGUI - library written on pure C. It implements primitives drawing methods, some drivers for displays and frameworks and full featured gui with many different elements, andvanced positioning, containers, input system and etc. It crated for embed platforms and can comfortably function even in 30kb of ram including two buffers. Main target is ARM MCUs. Main purpose of this GUI - to give developer simple control and development of reach gui. GUI supports pointer input as well as only keyboard.";
static MButton button[1];


static MCanvas canvas[2];

static MTabs tabs_e[1];

static MTabs_Tab tabs[] =
{
    {"style"},
    {"theme"},
    {"color"},
    {"font"},
    {"test"}
};

static MSList lists[4];
//items for choosing element
static MSList_Item list_elements[] =
{
    {"button", 0},
    {"slider"},
    {"lable", 0},
    {"textfield"},
    {"canvas"},
    {"tabs"},
    {"slist"},
    {"slist_item"}
};
//items for choosing
static MSList_Item list_theme[] =
{
    {"unactive", 0},
    {"normal", 0},
    {"focused", 0},
    {"active", 0},
};
//items for choosing color to change
static MSList_Item list_color[] =
{
    {"background", 0},
    {"font", 0},
    {"border", 0},
    {"double border"}
};
static MSList_Item list_font[] =
{
    {"Arial 12"},
    {"Arial 15"},
    {"Arial 16"},
    {"Arial 24"}
};

typedef enum
{
    s_button = 0,
    s_slider,
    s_lable,
    s_textfield,
    s_canvas,
    s_tabs,
    s_slist,
    s_slist_item,
    
} styles_el;

static MakiseStyle styles[10];

static MakiseStyleTheme *selected_theme = 0;
static MakiseStyle *selected_style = 0;
static uint32_t *selected_color = 0;

static void init_styles()
{
    styles[s_button] = ts_button;
    styles[s_slider] = ts_slider;
    styles[s_lable] = ts_lable;
    styles[s_lable].font = &F_Arial16;
    styles[s_textfield] = ts_textfield;
    styles[s_canvas] = ts_canvas;
    styles[s_tabs] = ts_tabs;
    styles[s_slist_item] = ts_slist_item;
    styles[s_slist] = ts_slist;
}

static int32_t cr = 0, cg = 0, cb = 0;

static void  invis_click(MButton* b) //b - button wich was clicked
{
    if(selected_color == 0)
	return;
    *selected_color = MC_Transparent;
}
static void onchange(MSlider* b, int32_t val)
{
    if(selected_color == 0)
	return;
    uint32_t c = (cr << 11) + (cg << 5) + cb;
    *selected_color = c;
    sprintf(lable_text, "r %02d g %02d b %02d", cr, cg, cb);
}

static void select_font(MSList *l, MSList_Item *selected)
{
    if(selected_style != 0)
    {
	switch (selected->id) {
	case 0:
	    selected_style->font = &F_Arial12;
	    break;
	case 1:
	    selected_style->font = &F_Arial15;
	    break;
	case 2:
	    selected_style->font = &F_Arial16;
	    break;
	case 3:
	    selected_style->font = &F_Arial24;
	    break;
	default:
	    break;
	}
    }
}
static void select(MSList *l, MSList_Item *selected)
{
    if(lists[0].selected == 0)
    {
	m_tabs_select_tab(tabs_e, 0);
	return;
    }
    if(lists[1].selected == 0)
    {
	m_tabs_select_tab(tabs_e, 1);
	return;
    }
    if(lists[2].selected == 0)
    {
	m_tabs_select_tab(tabs_e, 2);
	return;
    }
    
    
    selected_style = &styles[lists[0].selected->id];
    
    switch (lists[1].selected->id) {
    case 0:
	selected_theme = &selected_style->unactive;
	break;
    case 1:
	selected_theme = &selected_style->normal;
	break;
    case 2:
	selected_theme = &selected_style->focused;
	break;
    case 3:
	selected_theme = &selected_style->active;
	break;
    default:
	break;
    }
    switch (lists[2].selected->id) {
    case 0:
	selected_color = &selected_theme->bg_color;
	break;
    case 1:
	selected_color = &selected_theme->font_col;
	break;
    case 2:
	selected_color = &selected_theme->border_c;
	break;
    case 3:
	selected_theme->double_border = !selected_theme->double_border;
	break;
    default:
	break;
    }

    sprintf(path_text, "%s->%s->%s", list_elements[lists[0].selected->id].text,
	    list_theme[lists[1].selected->id].text,
	    list_color[lists[2].selected->id].text);

    cr = (*selected_color) >> 11;
    cg = ((*selected_color) >> 5) & 0b111111;
    cb = ((*selected_color)) & 0b11111;
    onchange(0, 0);

//    m_tabs_select_tab(tabs_e, 3);
}

void tests_styletest_init(MHost *h)
{
    init_styles();
    
    m_create_canvas(canvas, h->host, mp_sver(0, 90, 0, 0), &styles[s_canvas]);
    //COLOR editor
    {
	//red
	m_create_slider(sliders, &canvas->cont, mp_sver(5, 20, 5, 41),
			&cr, 0, 31,
			MSlider_Type_ReadWrite,
			&onchange, 0,
			&styles[s_slider]);
	//blue
	m_create_slider(&sliders[1], &canvas->cont, mp_sver(35, 20, 5, 41),
			&cg, 0, 63,
			MSlider_Type_ReadWrite,
			&onchange, 0,
			&styles[s_slider]);
	//green
	m_create_slider(&sliders[2], &canvas->cont, mp_sver(65, 20, 5, 41),
			&cb, 0, 31,
			MSlider_Type_ReadWrite,
			&onchange, 0,
			&ts_slider);
	m_create_button(button_invis, &canvas->cont,
			mp_cust(0, 0, 0, MPositionStretch_LeftRight,
				0, 20, 20, MPositionStretch_Down),
			"transparent",
			&invis_click,
			0, //event when key pressed on element
			0, //when focus recieved / loosed
			&ts_button_small); //style
	m_create_lable(&lable[0], //pointer to the structure
		       &canvas->cont, //container
		       mp_cust(1, 1, 0, MPositionStretch_LeftRight,
			       0, 1, 20, MPositionStretch_Down),
		       lable_text, //text
		       &styles[s_lable] //style
	    );
    }

    m_create_canvas(&canvas[1], h->host, mp_sall(90, 0, 0, 0), &styles[s_canvas]);

    m_create_lable(&lable[1], //pointer to the structure
		   &canvas[1].cont, //container
		   mp_cust(1, 1, 0, MPositionStretch_LeftRight,
			   0, 1, 20, MPositionStretch_Down),
		   path_text, //text
		   &styles[s_lable] //style
	);
    m_create_tabs(tabs_e, &canvas[1].cont, mp_sall(0,0,0,20),
		  tabs, 5,
		  MTabs_Type_Up, 20,
		  &styles[s_tabs]);
    {
	//ELEMENT SELECTOR
	{
	    m_create_slist(&lists[0], &tabs[0].cont, mp_sall(0,0,0,0), "select element:",
			   0, &select,
			   MSList_List,
			   &styles[s_slist], &styles[s_slist_item]);

	    m_slist_set_array(&lists[0], list_elements, 8);
	}
	//THEME
	{
	    m_create_slist(&lists[1], &tabs[1].cont, mp_sall(0,0,0,0), "select theme:",
			   0, &select,
			   MSList_List,
			   &styles[s_slist], &styles[s_slist_item]);

	    m_slist_set_array(&lists[1], list_theme, 4);
	}
	//COLOR
	{
	    m_create_slist(&lists[2], &tabs[2].cont, mp_sall(0,0,0,0), "select color:",
			   0, &select, //events
			   MSList_List,
			   &styles[s_slist], &styles[s_slist_item]);

	    m_slist_set_array(&lists[2], list_color, 4);
	}
	//Font
	{
	    m_create_slist(&lists[3], &tabs[3].cont, mp_sall(0,0,0,0), "select font:",
			   0, &select_font, //events
			   MSList_List,
			   &styles[s_slist], &styles[s_slist_item]);

	    m_slist_set_array(&lists[3], list_font, 4);
	}
	//TEST ELEMENTS
	{
	    m_create_text_field(textfield, &tabs[4].cont, mp_sall(0,0,0,35),
				textfield_text,
				&styles[s_textfield]);
	    m_create_button(button, &tabs[4].cont,
			    mp_cust(10,40, 0, MPositionStretch_LeftRight,
				    0, 3, 30, MPositionStretch_Down),
			    "Button",
			    0,0, 0,
			    &styles[s_button]);
	}
    }
}
