#include "manager_run.h"
#include "ui_manager_run.h"
#include "data.h"
#include "all_headers_nedded.h"
#include "managecheck.h"
#include <QDate>

manager_run::manager_run(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manager_run)
{
    ui->setupUi(this);
//界面美化
    this->setWindowIcon(QIcon(":Image/hotel.png"));
    QPixmap pixmap = QPixmap(":/Image/background.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
    ui->tableWidget->setStyleSheet("background-color: rgba(255,255,255,0)");
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgba(255,255,255,0);}");
    ui->tableWidget->verticalHeader()->setVisible(false);
//初始化表格
    int i;
    int j = 0;
    int temp = 0;
    for(i =0 ;i<Data::orders_num ;i++)
    {
        if(Data::orders[i].get_hotel() == Data::manager_hotel)
        temp++;
    }

    ui->tableWidget->setRowCount(temp);
    for(i=0;i<Data::orders_num;i++)
    {
        if(Data::orders[i].get_hotel() == Data::manager_hotel)
        {
            QTableWidgetItem * to1 = new QTableWidgetItem();
            to1->setText(Data::orders[i].get_cusphonenum());
            ui->tableWidget->setItem(j,0,to1);

            QTableWidgetItem * to2 = new QTableWidgetItem();
            QString rotype;
            if(Data::orders[i].get_room().get_type() == "singleroom")
                rotype = "单人间";
            if(Data::orders[i].get_room().get_type() == "doubleroom")
                rotype = "标准间";
            if(Data::orders[i].get_room().get_type() == "luxsingleroom")
                rotype = "豪华单人间";
            if(Data::orders[i].get_room().get_type() == "luxdoubleroom")
                rotype = "豪华标准间";
            if(Data::orders[i].get_room().get_type() == "familyroom")
                rotype = "家庭套房";
            if(Data::orders[i].get_room().get_type() == "presidentroom")
                rotype = "总统套房";
            to2->setText(rotype);
            ui->tableWidget->setItem(j,1,to2);

            QTableWidgetItem * to3 = new QTableWidgetItem();
            float dis;
            if(Data::orders[i].get_room().get_discount() == "无")
            dis = 1.0;
            if(Data::orders[i].get_room().get_discount() == "9折")
            dis = 0.9;
            if(Data::orders[i].get_room().get_discount() == "8折")
            dis = 0.8;
            if(Data::orders[i].get_room().get_discount() == "7折")
            dis = 0.7;
            if(Data::orders[i].get_room().get_discount() == "6折")
            dis = 0.6;
            if(Data::orders[i].get_room().get_discount() == "5折")
            dis = 0.5;
            QDate fromtime;
            fromtime = QDate::fromString(Data::orders[i].get_fromtime(),"yyyy/MM/dd");
            QDate totime = QDate::fromString(Data::orders[i].get_totime(),"yyyy/MM/dd");
            int days = fromtime.daysTo(totime);
            to3->setText(QString::number(dis*days*(Data::orders[i].get_room().get_price())*(Data::orders[i].get_roomnum())));
            ui->tableWidget->setItem(j,2,to3);

            QTableWidgetItem *checkBox_1 = new QTableWidgetItem();
            checkBox_1->setCheckState(Qt::Unchecked);
            ui->tableWidget->setItem(j,3, checkBox_1);

            j++;
        }
    }
    for(int a=0;a<ui->tableWidget->rowCount();a++)
    {
        for(int b=0;b<ui->tableWidget->columnCount();b++)
        {
                ui->tableWidget->item(a,b)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }
}

manager_run::~manager_run()
{
    delete ui;
}

void manager_run::on_back_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my_database.db");
    db.open();
    QSqlQuery query(db);

    query.exec("delete from orders where cusphonenum like '1%'");
    int i;
    for(i=0;i<Data::orders_num;i++)
    {
        query.prepare("insert into orders (num, hotel, roomtype, price, discount, picture, paystate, backmonstate, staystate, fromtime, totime,roomnum, roomcus, cusphonenum) values (?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        query.addBindValue(i);
        query.addBindValue(Data::orders[i].get_hotel());
        query.addBindValue(Data::orders[i].get_room().get_type());
        query.addBindValue(Data::orders[i].get_room().get_price());
        query.addBindValue(Data::orders[i].get_room().get_discount());
        query.addBindValue(Data::orders[i].get_room().get_picture());
        query.addBindValue(Data::orders[i].get_pay_state());
        query.addBindValue(Data::orders[i].get_backmon_state());
        query.addBindValue(Data::orders[i].get_stay_state());
        query.addBindValue(Data::orders[i].get_fromtime());
        query.addBindValue(Data::orders[i].get_totime());
        query.addBindValue(Data::orders[i].get_roomnum());
        query.addBindValue(Data::orders[i].get_roomcus());
        query.addBindValue(Data::orders[i].get_cusphonenum());
        query.exec();
    }

    query.exec("delete from room where hotelname like '%'");
    for(i = 0;i < Data::rooms_num;i++)
    {
        query.prepare("insert into room(ordernum,roomtype,lastnum,price,discount,picture,hotelname) values (?,?,?,?,?,?,?)");
        query.addBindValue(i);
        query.addBindValue(Data::rooms[i].get_type());
        query.addBindValue(Data::rooms[i].get_lastnum());
        query.addBindValue(Data::rooms[i].get_price());
        query.addBindValue(Data::rooms[i].get_discount());
        query.addBindValue(Data::rooms[i].get_picture());
        query.addBindValue(Data::rooms[i].get_hotelname());
        query.exec();
    }

    db.close();
    accept();
}
//重绘
void manager_run::paintEvent(QPaintEvent *event)
{
    int temp_row = 0;
    int i;
    int j;
    int sign = 0;
    temp_row = ui->tableWidget->rowCount();
    for(i=0;i<temp_row;i++)
    {
        if(ui->tableWidget->item (i,3)->checkState() == Qt::Unchecked)
        {
        sign = 0;
        }
        else
        {
         sign = 1;
         for(j=0;j<Data::orders_num;j++)
         {
             QString romtype;
             if(Data::orders[j].get_room().get_type() == "singleroom")
                 romtype = "单人间";
             if(Data::orders[j].get_room().get_type() == "doubleroom")
                 romtype = "标准间";
             if(Data::orders[j].get_room().get_type() == "luxsingleroom")
                 romtype = "豪华单人间";
             if(Data::orders[j].get_room().get_type() == "luxdoubleroom")
                 romtype = "豪华标准间";
             if(Data::orders[j].get_room().get_type() == "familyroom")
                 romtype = "家庭套房";
             if(Data::orders[j].get_room().get_type() == "presidentroom")
                 romtype = "总统套房";

             if(Data::orders[j].get_cusphonenum() == ui->tableWidget->item(i,0)->text() && romtype == ui->tableWidget->item(i,1)->text())
                 Data::row_check_6 = j;
         }
         break;
        }
    }
    if(sign == 0)
    {
        ui->look->setEnabled(false);
    }
    else
    {
        ui->look->setEnabled(true);
    }

    QDialog::paintEvent(event);
}

void manager_run::on_look_clicked()
{
    managecheck mgc;
    mgc.exec();
}
//关闭确认
void manager_run::closeEvent(QCloseEvent * event)
{
    int ret =
            QMessageBox::question(this,tr("关闭"),tr("关闭程序之后，未保存的数据将会损失，确认关闭吗？\n(保存数据请按返回键)"),QMessageBox::Yes,QMessageBox::No);
    if(ret == QMessageBox::Yes)
    {
        this->close();
    }
    else
    {
        event->ignore();
    }
}
