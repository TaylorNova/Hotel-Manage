#include <iostream>
#include "People.h"
#include "Order.h"
#include "Customer.h"
using namespace std;

Customer::Customer()
{

}

Customer::~Customer()
{

}

void Customer::set_myorder(Order &its_myorder)
{
    myorder = its_myorder;
}

Order & Customer::get_myorder()
{
    return myorder;
}
