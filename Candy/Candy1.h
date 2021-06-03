#pragma once
#include "Candy.h"
class Candy1 :
    public Candy
{
public:
    Candy1(int x) : Candy(x)
    {
    }
    int get_candyType() {
        return Candy::get_candyType();
    }

};

