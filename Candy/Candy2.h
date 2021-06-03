#pragma once
#include "Candy.h"
class Candy2 :
    public Candy
{
public:
    Candy2(int x) : Candy(x)
    {
    }
    int get_candyType() {
        return Candy::get_candyType();
    }
};

