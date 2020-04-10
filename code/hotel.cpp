#include <iostream>
#include "Object.h"
#include "Room.h"
#include "Hotel.h"
#include "people.h"
using namespace std;

Hotel::Hotel()
{

}

Hotel::~Hotel()
{

}

void Hotel::set_myroom(Room its_myroom[], int num)
{
    int i;
    for (i = 0; i < num; i++)
    {
        myroom[i] = its_myroom[i];
    }
}

Room * Hotel::get_myroom()
{
    return myroom;
}


void Hotel::set_city(QString its_city)
{
    city = its_city;
}

void Hotel::set_area(QString its_area)
{
    area = its_area;
}

void Hotel::set_hotelname(QString its_hotelname)
{
    hotelname = its_hotelname;;
}

void Hotel::set_state(QString its_state)
{
    state = its_state;
}

void Hotel::set_star(QString its_star)
{
    star = its_star;
}

QString Hotel::get_city() const
{
    return city;
}

QString Hotel::get_area() const
{
    return area;
}

QString Hotel::get_hotelname() const
{
    return hotelname;
}

QString Hotel::get_state() const
{
    return state;
}

QString Hotel::get_star() const
{
    return star;
}

