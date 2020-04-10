#include <iostream>
#include "People.h"
#include "Order.h"
#include "manager.h"
using namespace std;

Manager::Manager()
{

}

Manager::~Manager()
{

}

void Manager::set_order(Order its_ord[], int num)
{
    int i;
    for (i = 0; i<num; i++)
    {
        order[i] = its_ord[i];
    }
}

Order * Manager::get_order()
{
    return order;
}
