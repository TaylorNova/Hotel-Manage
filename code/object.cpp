#include <iostream>
#include "Object.h"
using namespace std;

Object::Object()
{

}

Object::~Object()
{

}

void Object::set_name(QString &its_name)
{
    name = its_name;
}

void Object::set_id(int its_id)
{
    id = its_id;
}

QString Object::get_name() const
{
    return name;
}

int Object::get_id() const
{
    return id;
}
