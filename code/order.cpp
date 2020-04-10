#include "Order.h"
#include <iostream>
using namespace std;


Order::Order()
{

}

Order::~Order()
{

}

Order::Order(Order &ord1)
{
    pay_state = ord1.pay_state;
    backmon_state = ord1.backmon_state;
    stay_state = ord1.stay_state;
    room = ord1.room;
    fromtime = ord1.fromtime;
    totime = ord1.totime;
    roomcus = ord1.roomcus;
}

void Order::set_pay_state(QString its_pay_state)
{
    pay_state = its_pay_state;
}

void Order::set_backmon_state(QString its_backmon_state)
{
    backmon_state = its_backmon_state;
}

void Order::set_stay_state(QString its_stay_state)
{
    stay_state = its_stay_state;
}

void Order::set_room(Room its_room)
{
    room = its_room;
}

void Order::set_fromtime(QString its_fromtime)
{
    fromtime = its_fromtime;
}

void Order::set_totime(QString its_totime)
{
    totime = its_totime;
}

void Order::set_roomcus(QString its_roomcus)
{
    roomcus = its_roomcus;
}

void Order::set_cusphonenum(QString its_cusphonenum)
{
    cusphonenum = its_cusphonenum;
}

void Order::set_hotel(QString its_hotel)
{
    hotel = its_hotel;
}

void Order::set_roomnum(int its_roomnum)
{
    roomnum = its_roomnum;
}

QString Order::get_pay_state() const
{
    return pay_state;
}

QString Order::get_backmon_state() const
{
    return backmon_state;
}

QString Order::get_stay_state() const
{
    return stay_state;
}

Room & Order::get_room()
{
    return room;
}

QString Order::get_fromtime() const
{
    return fromtime;
}

QString Order::get_totime() const
{
    return totime;
}

QString Order::get_roomcus() const
{
    return roomcus;
}

QString Order::get_cusphonenum() const
{
    return cusphonenum;
}

QString Order::get_hotel() const
{
    return hotel;
}

int Order::get_roomnum() const
{
    return roomnum;
}
