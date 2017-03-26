#include "tests_styles.h"

MakiseStyle ts_button =
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
MakiseStyle ts_button_small =
{
    MC_White,
    &F_Arial12,
    0,
    //bg       font     border   double_border
    {MC_Black, MC_Gray, MC_Gray, 0},  //unactive
    {MC_Black, MC_White, MC_White, 0},//normal
    {MC_White, MC_Green, MC_White, 0}, //focused
    {MC_Green, MC_White, MC_White, 0}, //active
};


MakiseStyle ts_slider =
{
    MC_White,
    &F_Arial24,
    0,
    //bg       font     border   double_border
    {0, 0,  0, 0},  //unactive
    {MC_Black, MC_Gray, MC_Gray, 0},//normal
    {MC_Black, MC_White, MC_White, 0}, //focused
    {MC_Green, MC_White, MC_White, 0}, //active
};
MakiseStyle ts_lable =
{
    MC_White,
    &F_Arial24,
    0,
    //bg       font     border   double_border
    {0, 0, 0, 0},  //unactive
    {MC_Black, MC_White, MC_Black, 0},//normal
    {0, 0, 0, 0}, //focused
    {0, 0, 0, 0}, //active
};
MakiseStyle ts_lable_small =
{
    MC_White,
    &F_Arial16,
    0,
    //bg       font     border   double_border
    {0, 0, 0, 0},  //unactive
    {MC_Black, MC_White, MC_Black, 0},//normal
    {0, 0, 0, 0}, //focused
    {0, 0, 0, 0}, //active
};


MakiseStyle ts_textfield =
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

MakiseStyle ts_canvas =
{
    MC_White,
    &F_Arial16,
    0,
    //bg       font     border   double_border
    {MC_Black, MC_Gray, MC_Gray,    0},  //unactive
    {MC_Black, MC_Gray, MC_White, 0},  //normal
    {MC_Black, MC_Gray, MC_White,   0},  //focused
    {MC_Black, MC_White, MC_White, 0},  //active
};

MakiseStyle ts_tabs =
{
    MC_White,
    &F_Arial16,
    0,
    //bg       font     border   double_border
    {MC_Black, MC_Gray, MC_Gray,    0},  //unactive
    {MC_Gray, MC_Gray, MC_White, 0},  //normal
    {MC_Black, MC_Gray, MC_White,   0},  //focused
    {MC_Black, MC_White, MC_White, 0},  //active
};

MakiseStyle ts_slist_item =
{
    MC_White,
    &F_Arial16,
    0,
    //bg       font     border   double_border
    {MC_Black, MC_Gray, MC_Gray,    0},  //unactive
    {MC_Black, MC_Gray, MC_White, 0},  //normal
    {MC_White, MC_Green, MC_White,   0},  //focused
    {MC_Black, MC_White, MC_White, 0},  //active
};
MakiseStyle ts_slist =
{
    MC_White,
    &F_Arial16,
    0,
    //bg       font     border   double_border
    {MC_Black, MC_Gray, MC_Gray,    0},  //unactive
    {MC_Black, MC_Gray, MC_Gray, 0},  //normal
    {MC_Black, MC_White, MC_White,   0},  //focused
    {MC_Black, MC_White, MC_White, 0},  //active
};

