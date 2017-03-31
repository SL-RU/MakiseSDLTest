#include "tests.h"

static MContainer *hs; //host

static MTabs tabs[1];
static MButton switch_b[1];
static MButton nextback_b[2];
static char* switch_t[] =
{
    "Left",
    "Up",
    "None"
};
static MTabs_Tab tabs_t[] =
{
    {"First tab"},
    {"Second tab"},
    {"Third tab"},
    {"Settings"},
};
static MLable lables[4];
static MSlider slider[1];
static int32_t sz = 30;
static int32_t stype = 0;

static MButton tst_b[4];
static MLable tst_l[4];

static void tst_b_0_click(MButton *b)
{
    tst_l[0].text = "You have click that button!!1";
}

static void recreate()
{
    MContainer *h = tabs->el.parent; //host
    if(h != 0)
	makise_g_cont_rem(&tabs->el);

    MTabs_Type t = MTabs_Type_Left;
    if(stype == 1)
	t = MTabs_Type_Up;
    else if(stype == 2)
	t = MTabs_Type_None;
    
    m_create_tabs(tabs, hs, mp_sall(0,0,0,30),
		  tabs_t, 4,
		  t, sz, &ts_tabs);
    {
	m_create_button(&tst_b[0], &tabs_t[0].cont,
			mp_shor(20,5,20,40),
			"First tab's button",
			&tst_b_0_click, 0, 0, &ts_button);
	m_create_lable(&tst_l[0],  &tabs_t[0].cont,
		       mp_shor(20,5,70,40),
		       "First tab's lable",
		       &ts_textfield);
    }
    {
	m_create_lable(&tst_l[1],  &tabs_t[1].cont,
		       mp_shor(20,5,70,40),
		       "This is second tab without any buttons",
		       &ts_textfield);
    }
    {
	m_create_lable(&tst_l[2],  &tabs_t[2].cont,
		       mp_shor(20,5,70,40),
			"This is third tab with slider",
		       &ts_textfield);
    }
    {
	m_create_button(&tst_b[3], &tabs_t[3].cont,
			mp_shor(20,5,20,40),
			"First button",
			&tst_b_0_click, 0, 0, &ts_button);
	m_create_button(&tst_b[3], &tabs_t[3].cont,
			mp_shor(20,5,20,40),
			"Second button",
			&tst_b_0_click, 0, 0, &ts_button);

	m_create_lable(&tst_l[3],  &tabs_t[3].cont,
		       mp_shor(20,5,70,40),
		       "Fours tab with two buttons",
		       &ts_textfield);
    }
}
static void onchange(MSlider *s, int32_t v) //when slider's value was changed
{
    recreate();
}
static void switch_click(MButton *b) //type button
{
    stype = (stype + 1) % 3;
    switch_b->text = switch_t[stype];
    recreate();
}
static void next_click(MButton *b)
{
    m_tabs_select_tab_next(tabs);
}
static void back_click(MButton *b)
{
    m_tabs_select_tab_back(tabs);
}

void tests_tabs_init(MHost *h)
{
    hs = h->host;
    //this slider will change size of header
    m_create_slider(slider, h->host,
		    mp_anc(0,0,100,30,MPositionAnchor_RighDown),
		    &sz, 5, 100, MSlider_Type_ReadWrite, &onchange, 0, &ts_slider);

    //that button will change header's type
    m_create_button(switch_b, h->host,
		    mp_anc(100,0,100,30,MPositionAnchor_RighDown),
		    "Up",
		    &switch_click, 0, 0, &ts_button);

    //next back
    m_create_button(nextback_b, h->host,
		    mp_anc(0,0,60,30,MPositionAnchor_LeftDown),
		    "Back",
		    &back_click, 0, 0, &ts_button);
    m_create_button(&nextback_b[2], h->host,
		    mp_anc(60,0,60,30,MPositionAnchor_LeftDown),
		    "Next",
		    &next_click, 0, 0, &ts_button);


    recreate();
}
