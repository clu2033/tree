#include <iostream>
#include <string>
#include "TreeType.h"
using namespace std;

int main()
{
    TreeType t; 
    t.PutItem(4);
    t.PutItem(2);
    t.PutItem(3);
    t.PutItem(1);
    t.Print();
    t.LevelOrderPrint();
    return 0;
}
