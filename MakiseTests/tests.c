#include "tests.h"

MSList_Item tests_items[4] = {
    {"hello world", 0},
    {"buttons", 1},
    {"positioning", 2},
    {"container", 3}
};

MHost *tests_host;

void tests_init(MHost *h)
{
    tests_host = h;
    tests_selector_init(h);
}

void tests_run(uint8_t id)
{
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
    default:
	break;
    }
}
