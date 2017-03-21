#ifndef tests_h
#define tests_h 1
#include <stdio.h>

#include "makise.h"
#include "makise_gui.h"
#include "makise_e.h"

#include "tests_styles.h"

MHost** tests_init();


typedef struct
{
    char* name;
    MHost host;
    MSList_Item item;
} tests_struct;

void tests_hello_init(MHost *h);
void tests_buttons_init(MHost *h);
void tests_container_init(MHost *h);
void tests_text_init(MHost *h);
void tests_sliders_init(MHost *h);
void tests_list_init(MHost *h);


#endif
