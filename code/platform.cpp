#include "platform.h"
#include "ui_platform.h"
#include "data.h"
#include "hotel.h"
#include "all_headers_nedded.h"
#include "confirmpass.h"
#include "setstarlevel.h"

using namespace std;
platform::platform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::platform)
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
    ui->tableWidget_2->setStyleSheet("background-color: rgba(255,255,255,0)");
    ui->tableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgba(255,255,255,0);}");
    ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tabWidget->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background:  transparent; }");
//初始化表格
    int i;
    ui->tableWidget->setRowCount(Data::hotel_plat_num);
    for(i = 0;i<Data::hotel_plat_num;i++)
    {
        QTableWidgetItem * name1 = new QTableWidgetItem();
        name1->setText(Data::hotel_plat[i].get_hotelname());
        ui->tableWidget->setItem(i,0,name1);

        QTableWidgetItem * name2 = new QTableWidgetItem();
        name2->setText(Data::hotel_plat[i].get_city());
        ui->tableWidget->setItem(i,1,name2);

        QTableWidgetItem * name3 = new QTableWidgetItem();
        name3->setText(Data::hotel_plat[i].get_area());
        ui->tableWidget->setItem(i,2,name3);

        QTableWidgetItem * name4 = new QTableWidgetItem();
        if(Data::hotel_plat[i].get_state() == "false")
        name4->setText("未通过");
        if(Data::hotel_plat[i].get_state() == "true")
        name4->setText("通过");
        ui->tableWidget->setItem(i,3,name4);

        QTableWidgetItem *checkBox_1 = new QTableWidgetItem();
        checkBox_1->setCheckState(Qt::Unchecked);
        ui->tableWidget->setItem(i, 4, checkBox_1);
    }
    for(int a=0;a<ui->tableWidget->rowCount();a++)
    {
        for(int b=0;b<ui->tableWidget->columnCount();b++)
        {
                ui->tableWidget->item(a,b)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }

    ui->tableWidget_2->setRowCount(Data::hotel_plat_num);
    for(i = 0;i<Data::hotel_plat_num;i++)
    {
        QTableWidgetItem * name1 = new QTableWidgetItem();
        name1->setText(Data::hotel_plat[i].get_hotelname());
        ui->tableWidget_2->setItem(i,0,name1);

        QTableWidgetItem * name2 = new QTableWidgetItem();
        name2->setText(Data::hotel_plat[i].get_city());
        ui->tableWidget_2->setItem(i,1,name2);

        QTableWidgetItem * name3 = new QTableWidgetItem();
        name3->setText(Data::hotel_plat[i].get_area());
        ui->tableWidget_2->setItem(i,2,name3);

        QTableWidgetItem *checkBox_2 = new QTableWidgetItem();
        checkBox_2->setCheckState(Qt::Unchecked);
        ui->tableWidget_2->setItem(i, 3, checkBox_2);
    }
    for(int a=0;a<ui->tableWidget_2->rowCount();a++)
    {
        for(int b=0;b<ui->tableWidget_2->columnCount();b++)
        {
                ui->tableWidget_2->item(a,b)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }
}

platform::~platform()
{
    delete ui;
}

void platform::on_cancel_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my_database.db");
    db.open();
    QSqlQuery query(db);
    int i;
    query.exec("delete from hotel where city = '北京'");
    query.exec("delete from hotel where city = '上海'");

    for(i = 0;i < Data::hotel_plat_num;i++)
    {
        query.prepare("insert into hotel(hotelname,city,area,ho_phonenum,state,star) values (?,?,?,?,?,?)");
        query.addBindValue(Data::hotel_plat[i].get_hotelname());
        query.addBindValue(Data::hotel_plat[i].get_city());
        query.addBindValue(Data::hotel_plat[i].get_area());
        query.addBindValue(Data::hotel_plat[i].get_phonenum());
        query.addBindValue(Data::hotel_plat[i].get_state());
        query.addBindValue(Data::hotel_plat[i].get_star());
        query.exec();
    }
    db.close();
    accept();
}
//重绘
void platform::paintEvent(QPaintEvent *event)
{
    if(Data::sign_num_5 == 1)
    {
        int i ;
        ui->tableWidget->setRowCount(Data::hotel_plat_num);
        for(i = 0;i<Data::hotel_plat_num;i++)
        {
            QTableWidgetItem * name1 = new QTableWidgetItem();
            name1->setText(Data::hotel_plat[i].get_hotelname());
            ui->tableWidget->setItem(i,0,name1);

            QTableWidgetItem * name2 = new QTableWidgetItem();
            name2->setText(Data::hotel_plat[i].get_city());
            ui->tableWidget->setItem(i,1,name2);

            QTableWidgetItem * name3 = new QTableWidgetItem();
            name3->setText(Data::hotel_plat[i].get_area());
            ui->tableWidget->setItem(i,2,name3);

            QTableWidgetItem * name4 = new QTableWidgetItem();
            if(Data::hotel_plat[i].get_state() == "false")
            name4->setText("未通过");
            if(Data::hotel_plat[i].get_state() == "true")
            name4->setText("通过");
            ui->tableWidget->setItem(i,3,name4);

            QTableWidgetItem *checkBox_1 = new QTableWidgetItem();
            checkBox_1->setCheckState(Qt::Unchecked);
            ui->tableWidget->setItem(i, 4, checkBox_1);
        }
        for(int a=0;a<ui->tableWidget->rowCount();a++)
        {
            for(int b=0;b<ui->tableWidget->columnCount();b++)
            {
                    ui->tableWidget->item(a,b)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }
        }

        Data::sign_num_5 = 0;
    }

    int temp_row = 0;
    int i;
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
         Data::row_check_2 = i;
         break;
        }
    }
    if(sign == 0)
    {
        ui->pass->setEnabled(false);
    }
    else
    {
        ui->pass->setEnabled(true);
    }

    int temp_row_2 = 0;
    int j;
    int sign_2 = 0;
    temp_row_2 = ui->tableWidget_2->rowCount();
    for(j = 0; j < temp_row_2 ; j++)
    {
        if(ui->tableWidget_2->item (j,3)->checkState() == Qt::Unchecked)
        {
        sign_2 = 0;
        }
        else
        {
         sign_2 = 1;
         Data::row_check_3 = j;
         break;
        }
    }
    if(sign_2 == 0)
    {
        ui->sort->setEnabled(false);
    }
    else
    {
        ui->sort->setEnabled(true);
    }

    QDialog::paintEvent(event);
}


void platform::on_pass_clicked()
{
    confirmpass cof;
    cof.exec();
}

void platform::on_sort_clicked()
{
    setstarlevel ssl;
    ssl.exec();
}

void platform::on_cancel_2_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my_database.db");
    db.open();
    QSqlQuery query(db);
    int i;
    query.exec("delete from hotel where city = '北京'");
    query.exec("delete from hotel where city = '上海'");

    for(i = 0;i < Data::hotel_plat_num;i++)
    {
        query.prepare("insert into hotel(hotelname,city,area,ho_phonenum,state,star) values (?,?,?,?,?,?)");
        query.addBindValue(Data::hotel_plat[i].get_hotelname());
        query.addBindValue(Data::hotel_plat[i].get_city());
        query.addBindValue(Data::hotel_plat[i].get_area());
        query.addBindValue(Data::hotel_plat[i].get_phonenum());
        query.addBindValue(Data::hotel_plat[i].get_state());
        query.addBindValue(Data::hotel_plat[i].get_star());
        query.exec();
    }
    db.close();
    accept();
}
//关闭确认
void platform::closeEvent(QCloseEvent * event)
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
