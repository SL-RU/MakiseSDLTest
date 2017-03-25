#include "tests.h"

MSList_Item tests_items[tests_items_len] = {
    {"hello world", 0},
    {"buttons", 1},
    {"positioning", 2},
    {"container", 3},
    {"sliders", 4},
    {"styles", 5},
};

MHost *tests_host;

void tests_init(MHost *h)
{
    tests_host = h;
    tests_selector_init(h);
}

void tests_run(uint8_t id)
{
    makise_g_cont_clear(tests_host->host);
    switch (id) {
    case 0:
	tests_hello_init(tests_host);
	break;
    case 1:
	tests_buttons_init(tests_host);
	break;
    case 2:
	tests_position_init(tests_host);
	break;
    case 3:
	tests_container_init(tests_host);
	break;
    case 4:
	tests_slider_init(tests_host);
	break;
    case 5:
	tests_styletest_init(tests_host);
    default:
	break;
    }
}

void tests_exit()
{
    makise_g_cont_clear(tests_host->host);
    tests_selector_init(tests_host);
}
