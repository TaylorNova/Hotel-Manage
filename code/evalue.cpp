#include "evalue.h"
#include "all_headers_nedded.h"
#include <iostream>

using namespace std;

Evalue::Evalue()
{

}

Evalue::~Evalue()
{

}

void Evalue::set_hotelname(QString its_hotelname)
{
    hotelname = its_hotelname;
}

void Evalue::set_score(float its_score)
{
    score = its_score;
}

void Evalue::set_number(int its_number)
{
    number = its_number;
}

QString Evalue::get_hotelname() const
{
    return hotelname;
}

float Evalue::get_score() const
{
    return score;
}

int Evalue::get_number() const
{
    return number;
}

void Evalue::renew_score(float new_score)
{
    score=(score*number+new_score)/(number+1);
    number++;
}
