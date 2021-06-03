#pragma once
#include "Candy.h"
class Candy3 :
    public Candy
{

public:
    Candy3(int x) : Candy(x)
    {
    }
    int get_candyType() {
        return Candy::get_candyType();
    }
};

