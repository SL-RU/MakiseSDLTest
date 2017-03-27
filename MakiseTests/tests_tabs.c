#include "tests.h"

static MTabs tabs[1];
static MTabs_Tab tabs_t[] =
{
    {"First tab"},
    {"Second tab"},
    {"Third tab"},
    {"Settings"},
};
static MLable lables[4];
static MSlider slider[1];
static int32_t sz;

static void onchange(MSlider *s, int32_t v)
{
    tabs->size = sz;
}

void tests_tabs_init(MHost *h)
{
    m_create_tabs(tabs, h->host, mp_sall(0,0,0,0),
		  tabs_t, 4,
		  MTabs_Type_Up, 40, &ts_tabs);
    {
	
    }
    {
    }
    {
	m_create_slider(slider, &tabs_t[0].cont,
			mp_anc(0,0,100,30,MPositionAnchor_RighDown),
			&sz, 5, 40, MSlider_Type_ReadWrite, &onchange, 0, &ts_slider);
    }
}
