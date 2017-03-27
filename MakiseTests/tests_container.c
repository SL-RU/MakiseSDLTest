#include "tests.h"

static MHost *host;
static char text[][100] = {
    "add",
    "remove",
    "tree",
    "insert",
    "replace",
};
static char labt[2][100] = {"selected:", ""}; //label
static char about[] = "This sample shows how to control elements in the containers. Button's text - index in the container's list. From index in list depends focus & draw order.";

static MButton button_cont[6]; //control buttons
static MButton buttons[6];      //buttons for tests
static char buttons_text[10][100]; //text for buttons

static MCanvas cont[6];   //test container
static MTextField lable[2];   //lables
static MTextField textield; //about


static MElement *selected[2];      //selected element

static void upd() //update test button's text
{
    for (int i = 0; i < 6; i++) {
	sprintf(buttons_text[i], "%d",
		//get index of element in parent container
		makise_g_cont_index(&buttons[i].el)); 
    }
}
static void clear() //clear selections
{
    selected[0] = 0;
    selected[1] = 0;
    sprintf(labt[0], "selected: ");
}

static void add(MButton*b)
{
    //find first button which isn't in the container yet
    for (int i = 0; i < 6; i++) {
	if(buttons[i].el.parent == 0)
	{
	    //add that button in the container
	    makise_g_cont_add(&cont->cont,
			      &buttons[i].el);
	    
	    upd();
	    break;
	}
    }
}
static void rem(MButton*b)
{
    //remove element from it's parent container
    makise_g_cont_rem(selected[0]);
    
    upd();
    clear();
}
static void replace(MButton*b)
{
    if(selected[0] != 0 &&
       selected[1] != 0)
    {
	//replace first and last selected elements in container list
	//it means - they will exchange their indexes
	makise_g_cont_replace(selected[0], selected[1]);
	
	upd();
	clear();
    }
}
static void insert(MButton*b)
{
    if(selected[0] != 0)
    {
	//get index of selected element
	uint32_t d = makise_g_cont_index(selected[0]);
	//find first button which isn't in the container yet
	for (int i = 0; i < 6; i++) {
	    if(buttons[i].el.parent == 0)
	    {
		//insert element in selected element's index
		makise_g_cont_insert(&cont[0].cont,
				     &buttons[i].el,
				     d);
		
		upd();
		clear();
		return;
	    }
	}
    }
}
static void tree(MButton*b)
{
    //print elements tree in console
    makise_g_print_tree(host);
}
static void select(MButton*b)
{
    //select button
    if(selected[0] == 0)
    {
	selected[0] = &b->el;
	sprintf(labt[0], "selected id: %d",
		selected[0]->id);
    }
    else if(selected[1] == 0 &&
	selected[1] != &b->el)
    {
	selected[1] = &b->el;
	sprintf(labt[0], "selected id: %d && %d",
		selected[0]->id,
		selected[1]->id);
    }
    else
    {	
	selected[0] = &b->el;
	selected[1] = 0;
	sprintf(labt[0], "selected id: %d",
		selected[0]->id);
    }
}

void tests_container_init(MHost *h)
{
    host = h;
    //description
    m_create_text_field(&textield,  //pointer to the structure
			h->host, //container
			mp_rel(0, 0,    //position
			       320, 52), //width, height
			about,    //text
			&ts_textfield//style
	);


    //TEST ELEMENTS:
    
    //container for the test buttons
    m_create_canvas(cont, h->host,
		    mp_rel(0, 50, 320, 100),
		    &ts_canvas);
    //get canvas's container
    MContainer *c = &cont->cont;

    //create test buttons without parent
    for (int i = 0; i < 6; i++) {
	m_create_button(&buttons[i],
			0, //zero parent
			mp_rel((160 * (i % 2)) + 30,
			       (i / 2) * 32 + 2,
			       100, 30),
			buttons_text[i],   //text
			//events:
			&select, 0, 0,
			&ts_button); //style
    }

    buttons[2].el.position.up -= 20;
    
    //ADD NEW ELEMENT to container. Add two first buttons to the canvas
    makise_g_cont_add(c, &buttons[0].el);
    makise_g_cont_add(c, &buttons[1].el);
    //update text on the buttons
    upd();




    //CONTROL ELEMENTS:
    
    //lable displaing selected elements
    m_create_text_field(&lable[0], h->host,
			mp_rel(0, 150, 220, 20), //position + sizes
			labt[0], &ts_lable_small);

    //container for control buttons
    m_create_canvas(&cont[1], h->host,
		    mp_rel(0, 170, 320, 89),
		    &ts_canvas);
    c = &cont[1].cont;

    //add
    m_create_button(&button_cont[0], c,
    		    mp_rel(10, 0, 90, 30),
    		    text[0],
    		    //events:
    		    &add, 0, 0,
    		    &ts_button //style
    	);
    //remove
    m_create_button(&button_cont[1], c,
    		    mp_rel(110, 0, 90, 30),
    		    text[1],
    		    //events:
    		    &rem, 0, 0,
    		    &ts_button //style
    	);
    //tree
    m_create_button(&button_cont[2], c,
    		    mp_rel(210, 0, 90, 30),
    		    text[2],
    		    //events:
    		    &tree, 0, 0,
    		    &ts_button //style
    	);
    //insert
    m_create_button(&button_cont[3], c,
    		    mp_rel(10, 35, 90, 30),
    		    text[3],
    		    //events:
    		    &insert, 0, 0,
    		    &ts_button //style
    	);
    /* //replace */
    m_create_button(&button_cont[4], c,
    		    mp_rel(110, 35, 90, 30),
    		    text[4],
    		    //events:
    		    &replace, 0, 0,
    		    &ts_button //style
    	);
    

}
