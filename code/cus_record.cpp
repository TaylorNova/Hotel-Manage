#include "cus_record.h"
#include "all_headers_nedded.h"

Record::Record()
{

}

Record::~Record()
{

}

void Record::set_choose_city(QString its_choose_city)
{
    choose_city = its_choose_city;
}

void Record::set_choose_area(QString its_choose_area)
{
    choose_area = its_choose_area;
}

void Record::set_choose_star(QString its_choose_star)
{
    choose_star = its_choose_star;
}

QString Record::get_choose_city() const
{
    return choose_city;
}

QString Record::get_choose_area() const
{
    return choose_area;
}

QString Record::get_choose_star() const
{
    return choose_star;
}
