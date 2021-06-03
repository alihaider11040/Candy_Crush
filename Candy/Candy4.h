#pragma once
#include "Candy.h"
class Candy4 :
    public Candy
{
public:
    Candy4(int x) : Candy(x)
    {
    }
    int get_candyType() {
        return Candy::get_candyType();
    }
};

