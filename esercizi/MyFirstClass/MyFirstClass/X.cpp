//
// Created by Danilo Ardagna on 23/09/21.
//

#include "X.h"


int X::mf1() {
    data = 0;
    return 0;
}

int X::mf2() {
    data = 1;
    int var1 = data;

    return var1 + mf1();
}
