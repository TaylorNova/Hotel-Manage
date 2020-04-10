#include "mainwindow.h"
#include "all_headers_nedded.h"
#include <QApplication>
#include "register.h"
#include "data.h"
#include "customer_run.h"
#include "manager_run.h"
#include "hotel_run.h"
#include "addroom.h"
#include "room.h"
#include "platform.h"
//创建数据库
void create_database()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my_database.db");
    db.open();
    QSqlQuery query(db);
    query.exec("create table account (identity varchar primary key, phonenum varchar, password varchar)");
    db.close();
}
//初始化
void initialize()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my_database.db");
    db.open();
    QSqlQuery query(db);
    int i;
    query.exec("select * from account where identity like 'customer%'");
    i = 0;
    while (query.next())
    {
        Data::customers[i].set_identity("customer");
        Data::customers[i].set_phonenum(query.value(1).toString());
        Data::customers[i].set_password(query.value(2).toString());
        i++;
    }
    Data::customers_num = i;

    query.exec("select * from account where identity like 'manager%'");
    i = 0;
    while (query.next())
    {
        Data::managers[i].set_identity("manager");
        Data::managers[i].set_phonenum(query.value(1).toString());
        Data::managers[i].set_password(query.value(2).toString());
        i++;
    }
    Data::managers_num = i;

    query.exec("select * from account where identity like 'hotel%'");
    i = 0;
    while (query.next())
    {
        Data::hotels[i].set_identity("hotel");
        Data::hotels[i].set_phonenum(query.value(1).toString());
        Data::hotels[i].set_password(query.value(2).toString());
        i++;
    }
    Data::hotels_num = i;

    query.exec("select * from account where identity = 'platform'");
    query.next();
    Data::platform[0].set_identity("platform");
    Data::platform[0].set_phonenum(query.value(1).toString());
    Data::platform[0].set_password(query.value(2).toString());

    query.exec("select * from hotel");
    i = 0;
    while (query.next())
    {
        Data::hotel_plat[i].set_hotelname(query.value(0).toString());
        Data::hotel_plat[i].set_city(query.value(1).toString());
        Data::hotel_plat[i].set_area(query.value(2).toString());
        Data::hotel_plat[i].set_phonenum(query.value(3).toString());
        Data::hotel_plat[i].set_state(query.value(4).toString());
        Data::hotel_plat[i].set_star(query.value(5).toString());
        i++;
    }
    Data::hotel_plat_num = i;

    query.exec("select * from room");
    i = 0;
    while (query.next())
    {
        Data::rooms[i].set_type(query.value(1).toString());
        Data::rooms[i].set_lastnum(query.value(2).toInt());
        Data::rooms[i].set_price(query.value(3).toInt());
        Data::rooms[i].set_discount(query.value(4).toString());
        Data::rooms[i].set_picture(query.value(5).toString());
        Data::rooms[i].set_hotelname(query.value(6).toString());
        Data::rooms[i].set_description(query.value(7).toString());
        i++;
    }
    Data::rooms_num = i;

    query.exec("select * from orders");
    i = 0;
    while (query.next())
    {
        Data::orders[i].set_hotel(query.value(1).toString());
        Room tem_room;
        tem_room.set_type(query.value(2).toString());
        tem_room.set_price(query.value(3).toInt());
        tem_room.set_discount(query.value(4).toString());
        tem_room.set_picture(query.value(5).toString());
        Data::orders[i].set_room(tem_room);
        Data::orders[i].set_pay_state(query.value(6).toString());
        Data::orders[i].set_backmon_state(query.value(7).toString());
        Data::orders[i].set_stay_state(query.value(8).toString());
        Data::orders[i].set_fromtime(query.value(9).toString());
        Data::orders[i].set_totime(query.value(10).toString());
        Data::orders[i].set_roomnum(query.value(11).toInt());
        Data::orders[i].set_roomcus(query.value(12).toString());
        Data::orders[i].set_cusphonenum(query.value(13).toString());
        i++;
    }
    Data::orders_num = i;

    query.exec("select * from matchs");
    i = 0;
    while (query.next())
    {
        Data::matchs[i].set_hotelname(query.value(0).toString());
        Data::matchs[i].set_manager(query.value(1).toString());
        i++;
    }
    Data::matchs_num = i;

    query.exec("select * from evalues");
    i = 0;
    while (query.next())
    {
        Data::evalues[i].set_hotelname(query.value(0).toString());
        Data::evalues[i].set_score(query.value(1).toFloat());
        Data::evalues[i].set_number(query.value(2).toInt());
        i++;
    }
    Data::evalues_num = i;

    db.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Register reg;
    customer_run cur;
    manager_run mar;
    hotel_run hor;
    platform plf;
    addroom adr;
    create_database();
    initialize();
    return a.exec();
}
