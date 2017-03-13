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

