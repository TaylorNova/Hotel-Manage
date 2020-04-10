#include "match.h"

Match::Match()
{

}

Match::~Match()
{

}

void Match::set_hotelname(QString its_hotelname)
{
    hotelname = its_hotelname;
}


void Match::set_manager(QString its_manager)
{
    manager = its_manager;
}

QString Match::get_hotelname() const
{
    return hotelname;
}

QString Match::get_manager() const
{
    return manager;
}
