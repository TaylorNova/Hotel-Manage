#include <iostream>
#include "Object.h"
#include "Room.h"
using namespace std;


Room::Room()
{

}

Room::Room(Room &ro1)
{
    type = ro1.type;
    discount = ro1.discount;
    price = ro1.price;
    lastnum = ro1.lastnum;
    picture = ro1.picture;
    hotelname = ro1.hotelname;
}

Room::~Room()
{

}

void Room::set_type(QString its_type)
{
    type = its_type;
}

void Room::set_discount(QString its_discount)
{
    discount = its_discount;
}

void Room::set_price(int its_price)
{
    price = its_price;
}

void Room::set_lastnum(int its_lastnum)
{
    lastnum = its_lastnum;
}

void Room::set_picture(QString its_picture)
{
    picture = its_picture;
}

void Room::set_hotelname(QString its_hotelname)
{
    hotelname = its_hotelname;
}

void Room::set_description(QString its_description)
{
    description = its_description;
}

QString Room::get_type() const
{
    return type;
}

QString Room::get_discount() const
{
    return discount;
}

int Room::get_price() const
{
    return price;
}

int Room::get_lastnum() const
{
    return lastnum;
}

QString Room::get_picture() const
{
    return picture;
}

QString Room::get_hotelname() const
{
    return hotelname;
}

QString Room::get_description() const
{
    return description;
}
