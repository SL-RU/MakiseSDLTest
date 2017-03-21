#include "tests.h"

MHost *tests_container_h;
char tests_container_text[][100] = {
    "add",
    "remove",
    "tree",
    "insert",
    "replace",
};
char ts_container_labt[2][100] = {"selected:", ""}; //label
char ts_container_about[] = "This sample shows how to control elements in the containers. Button's text - index in the container's list. From index in list depends focus & draw order.";

MButton ts_container_b_cont[6]; //control buttons
MButton ts_container_b[6];      //buttons for tests
char tests_container_bt[10][100]; //text for buttons

MCanvas ts_container_cont[6];   //test container
MTextField ts_container_lable[2];   //lables
MTextField ts_container_text; //about


MElement *ts_container_sel[2];      //selected element

void tests_container_upd() //update test button's text
{
    for (int i = 0; i < 6; i++) {
	sprintf(tests_container_bt[i], "%d",
		//get index of element in parent container
		makise_g_cont_index(&ts_container_b[i].el)); 
    }
}
void tests_container_clear() //clear selections
{
    ts_container_sel[0] = 0;
    ts_container_sel[1] = 0;
    sprintf(ts_container_labt[0], "selected: ");
}

void tests_container_add(MButton*b)
{
    //find first button which isn't in the container yet
    for (int i = 0; i < 6; i++) {
	if(ts_container_b[i].el.parent == 0)
	{
	    //add that button in the container
	    makise_g_cont_add(&ts_container_cont->cont,
			      &ts_container_b[i].el);
	    
	    tests_container_upd();
	    break;
	}
    }
}
void tests_container_rem(MButton*b)
{
    //remove element from it's parent container
    makise_g_cont_rem(ts_container_sel[0]);
    
    tests_container_upd();
    tests_container_clear();
}
void tests_container_replace(MButton*b)
{
    if(ts_container_sel[0] != 0 &&
       ts_container_sel[1] != 0)
    {
	//replace first and last selected elements in container list
	//it means - they will exchange their indexes
	makise_g_cont_replace(ts_container_sel[0], ts_container_sel[1]);
	
	tests_container_upd();
	tests_container_clear();
    }
}
void tests_container_insert(MButton*b)
{
    if(ts_container_sel[0] != 0)
    {
	//get index of selected element
	uint32_t d = makise_g_cont_index(ts_container_sel[0]);
	//find first button which isn't in the container yet
	for (int i = 0; i < 6; i++) {
	    if(ts_container_b[i].el.parent == 0)
	    {
		//insert element in selected element's index
		makise_g_cont_insert(&ts_container_cont[0].cont,
				     &ts_container_b[i].el,
				     d);
		
		tests_container_upd();
		tests_container_clear();
		return;
	    }
	}
    }
}
void tests_container_tree(MButton*b)
{
    //print elements tree in console
    makise_g_print_tree(tests_container_h);
}
void tests_container_select(MButton*b)
{
    //select button
    if(ts_container_sel[0] == 0)
    {
	ts_container_sel[0] = &b->el;
	sprintf(ts_container_labt[0], "selected id: %d",
		ts_container_sel[0]->id);
    }
    else if(ts_container_sel[1] == 0 &&
	ts_container_sel[1] != &b->el)
    {
	ts_container_sel[1] = &b->el;
	sprintf(ts_container_labt[0], "selected id: %d && %d",
		ts_container_sel[0]->id,
		ts_container_sel[1]->id);
    }
    else
    {	
	ts_container_sel[0] = &b->el;
	ts_container_sel[1] = 0;
	sprintf(ts_container_labt[0], "selected id: %d",
		ts_container_sel[0]->id);
    }
}

void tests_container_init(MHost *h)
{
    tests_container_h = h;
    //description
    m_create_text_field(&ts_container_text,  //pointer to the structure
			h->host, //container
			mp_rel(0, 0,    //position
			       320, 52), //width, height
			ts_container_about,    //text
			&ts_textfield//style
	);


    //TEST ELEMENTS:
    
    //container for the test buttons
    m_create_canvas(ts_container_cont, h->host,
		    mp_rel(0, 50, 320, 100),
		    &ts_canvas);
    //get canvas's container
    MContainer *c = &ts_container_cont->cont;

    //create test buttons without parent
    for (int i = 0; i < 6; i++) {
	m_create_button(&ts_container_b[i],
			0, //zero parent
			mp_rel((160 * (i % 2)) + 30,
			       (i / 2) * 32 + 2,
			       100, 30),
			tests_container_bt[i],   //text
			//events:
			&tests_container_select, 0, 0,
			&ts_button); //style
    }
    //ADD NEW ELEMENT to container. Add two first buttons to the canvas
    makise_g_cont_add(c, &ts_container_b[0].el);
    makise_g_cont_add(c, &ts_container_b[1].el);
    //update text on the buttons
    tests_container_upd();




    //CONTROL ELEMENTS:
    
    //lable displaing selected elements
    m_create_text_field(&ts_container_lable[0], h->host,
			mp_rel(0, 150, 220, 20), //position + sizes
			ts_container_labt[0], &ts_lable_small);

    //container for control buttons
    m_create_canvas(&ts_container_cont[1], h->host,
		    mp_rel(0, 170, 320, 89),
		    &ts_canvas);
    c = &ts_container_cont[1].cont;

    //add
    m_create_button(&ts_container_b_cont[0], c,
    		    mp_rel(10, 0, 90, 30),
    		    tests_container_text[0],
    		    //events:
    		    &tests_container_add, 0, 0,
    		    &ts_button //style
    	);
    //remove
    m_create_button(&ts_container_b_cont[1], c,
    		    mp_rel(110, 0, 90, 30),
    		    tests_container_text[1],
    		    //events:
    		    &tests_container_rem, 0, 0,
    		    &ts_button //style
    	);
    //tree
    m_create_button(&ts_container_b_cont[2], c,
    		    mp_rel(210, 0, 90, 30),
    		    tests_container_text[2],
    		    //events:
    		    &tests_container_tree, 0, 0,
    		    &ts_button //style
    	);
    //insert
    m_create_button(&ts_container_b_cont[3], c,
    		    mp_rel(10, 35, 90, 30),
    		    tests_container_text[3],
    		    //events:
    		    &tests_container_insert, 0, 0,
    		    &ts_button //style
    	);
    /* //replace */
    m_create_button(&ts_container_b_cont[4], c,
    		    mp_rel(110, 35, 90, 30),
    		    tests_container_text[4],
    		    //events:
    		    &tests_container_replace, 0, 0,
    		    &ts_button //style
    	);
    

}
