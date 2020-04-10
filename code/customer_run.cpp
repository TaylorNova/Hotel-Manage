#include "customer_run.h"
#include "ui_customer_run.h"
#include "all_headers_nedded.h"
#include "data.h"
#include "findroom.h"
#include "checkorder.h"

customer_run::customer_run(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::customer_run)
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
    ui->tabWidget->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background:  transparent; }");

    ui->city->setStyleSheet("QComboBox {border: 1px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;min-width: 9em;}"
                            "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 20px;\
                             border-left-width: 1px;border-left-color: darkgray;border-left-style: solid; border-top-right-radius: 3px;\
                             border-bottom-right-radius: 3px;}"
                            "QComboBox::down-arrow { image: url(:/Image/xiala.png);}");
    ui->area->setStyleSheet("QComboBox {border: 1px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;min-width: 9em;}"
                            "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 20px;\
                             border-left-width: 1px;border-left-color: darkgray;border-left-style: solid; border-top-right-radius: 3px;\
                             border-bottom-right-radius: 3px;}"
                            "QComboBox::down-arrow { image: url(:/Image/xiala.png);}");
    ui->star->setStyleSheet("QComboBox {border: 1px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;min-width: 9em;}"
                            "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 20px;\
                            border-left-width: 1px;border-left-color: darkgray;border-left-style: solid; border-top-right-radius: 3px;\
                            border-bottom-right-radius: 3px;}"
                            "QComboBox::down-arrow { image: url(:/Image/xiala.png);}");
//初始化表格
    int i;
    int j = 0;
    int temp = 0;
    for(i=0;i<Data::orders_num;i++)
    {
        if(Data::orders[i].get_cusphonenum() == Data::current_user)
        temp++;
    }

    ui->tableWidget->setRowCount(temp);
    for(i=0;i<Data::orders_num;i++)
    {
        if(Data::orders[i].get_cusphonenum() == Data::current_user)
        {
        QTableWidgetItem * the1 = new QTableWidgetItem();
        the1->setText(Data::orders[i].get_hotel());
        ui->tableWidget->setItem(j,0,the1);

        QTableWidgetItem * the2 = new QTableWidgetItem();
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
        the2->setText(rotype);
        ui->tableWidget->setItem(j,1,the2);

        QTableWidgetItem * the3 = new QTableWidgetItem();
        the3->setText(QString::number(Data::orders[i].get_room().get_price()));
        ui->tableWidget->setItem(j,2,the3);

        QTableWidgetItem * the4 = new QTableWidgetItem();
        if(Data::orders[i].get_pay_state() == "已评价")
        the4->setText("已评价");
        if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_stay_state() == "未入住")
        the4->setText("已支付");
        if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_stay_state() == "已入住")
        the4->setText("已入住");
        if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_stay_state() == "已退房")
        the4->setText("可评价");
        if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_backmon_state() == "未退款" && Data::orders[i].get_stay_state() == "未入住")
        the4->setText("已支付");
        if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_backmon_state() == "退款正在受理")
        the4->setText("退款正在受理");
        if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_backmon_state() == "退款已完成")
        the4->setText("退款已完成");
        ui->tableWidget->setItem(j,3,the4);

        QTableWidgetItem *checkBox_1 = new QTableWidgetItem();
        checkBox_1->setCheckState(Qt::Unchecked);
        ui->tableWidget->setItem(j, 4, checkBox_1);

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

customer_run::~customer_run()
{
    delete ui;
}

void customer_run::on_back_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my_database.db");
    db.open();
    QSqlQuery query(db);
    query.exec("delete from orders where cusphonenum like '1%'");
    for(int i = 0 ;i<Data::orders_num; i++)
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
    int i;
    for(i = 0;i < Data::rooms_num;i++)
    {
        query.prepare("insert into room(ordernum,roomtype,lastnum,price,discount,picture,hotelname,description) values (?,?,?,?,?,?,?,?)");
        query.addBindValue(i);
        query.addBindValue(Data::rooms[i].get_type());
        query.addBindValue(Data::rooms[i].get_lastnum());
        query.addBindValue(Data::rooms[i].get_price());
        query.addBindValue(Data::rooms[i].get_discount());
        query.addBindValue(Data::rooms[i].get_picture());
        query.addBindValue(Data::rooms[i].get_hotelname());
        query.addBindValue(Data::rooms[i].get_description());
        query.exec();
    }

    db.close();

    accept();
}
//重绘
void customer_run::paintEvent(QPaintEvent *event)
{
    if(ui->city->currentText() == "北京" && Data::sign_num_7 == 0)
    {
        ui->area->clear();
        ui->area->addItem(" ");
        ui->area->addItem("海淀区");
        ui->area->addItem("朝阳区");
        Data::sign_num_7 = 1;
    }
    if(ui->city->currentText() == "上海" && Data::sign_num_7 == 1)
    {
        ui->area->clear();
        ui->area->addItem(" ");
        ui->area->addItem("浦东");
        ui->area->addItem("浦西");
        Data::sign_num_7 = 0;
    }

    if(Data::sign_num_10 == 1)
    {
        int i;
        int j = 0;
        int temp = 0;
        for(i=0;i<Data::orders_num;i++)
        {
            if(Data::orders[i].get_cusphonenum() == Data::current_user)
            temp++;
        }

        ui->tableWidget->setRowCount(temp);
        for(i=0;i<Data::orders_num;i++)
        {
            if(Data::orders[i].get_cusphonenum() == Data::current_user)
            {
            QTableWidgetItem * the1 = new QTableWidgetItem();
            the1->setText(Data::orders[i].get_hotel());
            ui->tableWidget->setItem(j,0,the1);

            QTableWidgetItem * the2 = new QTableWidgetItem();
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
            the2->setText(rotype);
            ui->tableWidget->setItem(j,1,the2);

            QTableWidgetItem * the3 = new QTableWidgetItem();
            the3->setText(QString::number(Data::orders[i].get_room().get_price()));
            ui->tableWidget->setItem(j,2,the3);

            QTableWidgetItem * the4 = new QTableWidgetItem();
            if(Data::orders[i].get_pay_state() == "已评价")
            the4->setText("已评价");
            if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_stay_state() == "未入住")
            the4->setText("已支付");
            if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_stay_state() == "已入住")
            the4->setText("已入住");
            if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_stay_state() == "已退房")
            the4->setText("可评价");
            if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_backmon_state() == "未退款" && Data::orders[i].get_stay_state() == "未入住")
            the4->setText("已支付");
            if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_backmon_state() == "退款正在受理")
            the4->setText("退款正在受理");
            if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_backmon_state() == "退款已完成")
            the4->setText("退款已完成");
            ui->tableWidget->setItem(j,3,the4);

            QTableWidgetItem *checkBox_1 = new QTableWidgetItem();
            checkBox_1->setCheckState(Qt::Unchecked);
            ui->tableWidget->setItem(j, 4, checkBox_1);

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

        Data::sign_num_10 = 0;
    }

    if(Data::sign_num_16 == 1)
    {
        int i;
        int j = 0;
        int temp = 0;
        for(i=0;i<Data::orders_num;i++)
        {
            if(Data::orders[i].get_cusphonenum() == Data::current_user)
            temp++;
        }

        ui->tableWidget->setRowCount(temp);
        for(i=0;i<Data::orders_num;i++)
        {
            if(Data::orders[i].get_cusphonenum() == Data::current_user)
            {
            QTableWidgetItem * the1 = new QTableWidgetItem();
            the1->setText(Data::orders[i].get_hotel());
            ui->tableWidget->setItem(j,0,the1);

            QTableWidgetItem * the2 = new QTableWidgetItem();
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
            the2->setText(rotype);
            ui->tableWidget->setItem(j,1,the2);

            QTableWidgetItem * the3 = new QTableWidgetItem();
            the3->setText(QString::number(Data::orders[i].get_room().get_price()));
            ui->tableWidget->setItem(j,2,the3);

            QTableWidgetItem * the4 = new QTableWidgetItem();
            if(Data::orders[i].get_pay_state() == "已评价")
            the4->setText("已评价");
            if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_stay_state() == "未入住")
            the4->setText("已支付");
            if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_stay_state() == "已入住")
            the4->setText("已入住");
            if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_stay_state() == "已退房")
            the4->setText("可评价");
            if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_backmon_state() == "未退款" && Data::orders[i].get_stay_state() == "未入住")
            the4->setText("已支付");
            if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_backmon_state() == "退款正在受理")
            the4->setText("退款正在受理");
            if(Data::orders[i].get_pay_state() == "已支付" && Data::orders[i].get_backmon_state() == "退款已完成")
            the4->setText("退款已完成");
            ui->tableWidget->setItem(j,3,the4);

            QTableWidgetItem *checkBox_1 = new QTableWidgetItem();
            checkBox_1->setCheckState(Qt::Unchecked);
            ui->tableWidget->setItem(j, 4, checkBox_1);

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

        Data::sign_num_16 = 0;
    }

    int temp_row = 0;
    int i;
    int j;
    int sign = 0;
    temp_row = ui->tableWidget->rowCount();
    for(i=0;i<temp_row;i++)
    {
        if(ui->tableWidget->item (i,4)->checkState() == Qt::Unchecked)
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

             if(romtype == ui->tableWidget->item(i,1)->text() && Data::orders[j].get_hotel() == ui->tableWidget->item(i,0)->text() && Data::orders[j].get_cusphonenum() == Data::current_user)
                Data::row_check_5 = j;
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

void customer_run::on_find_clicked()
{
    Data::record[0].set_choose_city(ui->city->currentText());
    Data::record[0].set_choose_area(ui->area->currentText());
    Data::record[0].set_choose_star(ui->star->currentText());
    findroom fdr;
    fdr.exec();
}

void customer_run::on_fresh_clicked()
{
    Data::sign_num_10 = 1;
}

void customer_run::on_look_clicked()
{
    checkorder cor;
    cor.exec();
}

void customer_run::on_back_2_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my_database.db");
    db.open();
    QSqlQuery query(db);
    query.exec("delete from orders where cusphonenum like '1%'");
    for(int i = 0 ;i<Data::orders_num; i++)
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

    query.exec("delete from evalues where hotelname like '%'");
    for(int j = 0; j < Data::evalues_num; j++)
    {
        query.prepare("insert into evalues (hotelname, score, number) values (?,?,?)");
        query.addBindValue(Data::evalues[j].get_hotelname());
        query.addBindValue(Data::evalues[j].get_score());
        query.addBindValue(Data::evalues[j].get_number());
        query.exec();
    }

    db.close();

    accept();
}

void customer_run::closeEvent(QCloseEvent * event)
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
