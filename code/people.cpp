#include <iostream>
#include "Object.h"
#include "People.h"
#include "all_headers_nedded.h"
#include <QtGlobal>
#include <QTime>

using namespace std;


People::People()
{

}

People::~People()
{

}

void People::set_identity(QString its_identity)
{
    identity = its_identity;
}

void People::set_password(QString its_password)
{
    password = its_password;
}

void People::set_phonenum(QString its_phonenum)
{
    phonenum = its_phonenum;
}

QString People::get_identity() const
{
    return identity;
}

QString People::get_password() const
{
    return password;
}

QString People::get_phonenum() const
{
    return phonenum;
}

void People::save_to_database_register()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my_database.db");
    db.open();
    QSqlQuery query(db);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int temp = qrand()%100;
    QString tem = QString::number(temp);
    query.prepare("insert into account(identity,phonenum,password) values (?,?,?)");
    query.addBindValue(identity + tem);
    query.addBindValue(phonenum);
    query.addBindValue(password);
    query.exec();
    query.exec("select * from account");
    while (query.next())
        {
            qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString();
        }
    db.close();
}

bool People::load_from_database()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.open();
    QSqlQuery query(db);
    query.exec("select identity,phonenum,password from account");
    if (query.next())
        {
            qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString();
            identity = query.value(0).toString();
            phonenum = query.value(1).toString();
            password = query.value(2).toString();
            db.close();
            return 1;
        }
    else
        {
            db.close();
            return 0;
        }
}
