#include "hotel_run.h"
#include "ui_hotel_run.h"
#include "all_headers_nedded.h"
#include "addroom.h"
#include "data.h"
#include "changeroom.h"
#include <QtGlobal>
#include <QTime>

hotel_run::hotel_run(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hotel_run)
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
    int i ;
    int j ;
    int temp = 0;
    for(i = 0;i < Data::rooms_num ;i++)
    {
        if(Data::rooms[i].get_hotelname() == Data::current_user)
            temp++;
    }
    ui->tableWidget->setRowCount(temp);
    for(i=0,j=0;i<Data::rooms_num;i++)
    {
        if(Data::rooms[i].get_hotelname() == Data::current_user)
        {
        QTableWidgetItem * name1 = new QTableWidgetItem();
        if(Data::rooms[i].get_type() == "singleroom")
        name1->setText("单人间");
        if(Data::rooms[i].get_type() == "doubleroom")
        name1->setText("标准间");
        if(Data::rooms[i].get_type() == "luxsingleroom")
        name1->setText("豪华单人间");
        if(Data::rooms[i].get_type() == "luxdoubleroom")
        name1->setText("豪华标准间");
        if(Data::rooms[i].get_type() == "familyroom")
        name1->setText("家庭套房");
        if(Data::rooms[i].get_type() == "presidentroom")
        name1->setText("总统套房");
        ui->tableWidget->setItem(j,0,name1);

        QTableWidgetItem * name2 = new QTableWidgetItem();
        name2->setText(QString::number(Data::rooms[i].get_price()));
        ui->tableWidget->setItem(j,1,name2);

        QTableWidgetItem * name3 = new QTableWidgetItem();
        name3->setText(QString::number(Data::rooms[i].get_lastnum()));
        ui->tableWidget->setItem(j,2,name3);

        QTableWidgetItem *checkBox_1 = new QTableWidgetItem();
        checkBox_1->setCheckState(Qt::Unchecked);
        ui->tableWidget->setItem(j, 3, checkBox_1);
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

hotel_run::~hotel_run()
{
    delete ui;
}

void hotel_run::on_back_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("my_database.db");
    db.open();
    QSqlQuery query(db);

    int i;
    QString sql = QString("delete from room where hotelname = '%1'").arg(Data::current_user);
    query.exec(sql);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int temp = qrand()%10000;
    qDebug() << Data::current_user;
    for(i = 0;i < Data::rooms_num;i++)
    {
        if(Data::rooms[i].get_hotelname() == Data::current_user)
        {
        query.prepare("insert into room(ordernum,roomtype,lastnum,price,discount,picture,hotelname,description) values (?,?,?,?,?,?,?,?)");
        query.addBindValue(temp+i);
        query.addBindValue(Data::rooms[i].get_type());
        query.addBindValue(Data::rooms[i].get_lastnum());
        query.addBindValue(Data::rooms[i].get_price());
        query.addBindValue(Data::rooms[i].get_discount());
        query.addBindValue(Data::rooms[i].get_picture());
        query.addBindValue(Data::rooms[i].get_hotelname());
        query.addBindValue(Data::rooms[i].get_description());
        query.exec();
        }
    }
    db.close();
    Data::current_user = "";
    accept();
}

void hotel_run::on_add_clicked()
{
    addroom addr;
    addr.exec();
}
//重绘
void hotel_run::paintEvent(QPaintEvent *event)
{
    if(Data::sign_num == 1)
    {
        int i ;
        int j ;
        int temp = 0;
        for(i = 0;i < Data::rooms_num ;i++)
        {
            if(Data::rooms[i].get_hotelname() == Data::current_user)
                temp++;
        }
        ui->tableWidget->setRowCount(temp);
        for(i=0,j=0;i<Data::rooms_num;i++)
        {
            if(Data::rooms[i].get_hotelname() == Data::current_user)
            {
            QTableWidgetItem * name1 = new QTableWidgetItem();
            if(Data::rooms[i].get_type() == "singleroom")
            name1->setText("单人间");
            if(Data::rooms[i].get_type() == "doubleroom")
            name1->setText("标准间");
            if(Data::rooms[i].get_type() == "luxsingleroom")
            name1->setText("豪华单人间");
            if(Data::rooms[i].get_type() == "luxdoubleroom")
            name1->setText("豪华标准间");
            if(Data::rooms[i].get_type() == "familyroom")
            name1->setText("家庭套房");
            if(Data::rooms[i].get_type() == "presidentroom")
            name1->setText("总统套房");
            ui->tableWidget->setItem(j,0,name1);

            QTableWidgetItem * name2 = new QTableWidgetItem();
            name2->setText(QString::number(Data::rooms[i].get_price()));
            ui->tableWidget->setItem(j,1,name2);

            QTableWidgetItem * name3 = new QTableWidgetItem();
            name3->setText(QString::number(Data::rooms[i].get_lastnum()));
            ui->tableWidget->setItem(j,2,name3);

            QTableWidgetItem *checkBox_1 = new QTableWidgetItem();
            checkBox_1->setCheckState(Qt::Unchecked);
            ui->tableWidget->setItem(j, 3, checkBox_1);
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

        Data::sign_num = 0;
    }

    if(Data::sign_num_2 == 1)
    {
        int i ;
        int j ;
        int temp = 0;
        for(i = 0;i < Data::rooms_num ;i++)
        {
            if(Data::rooms[i].get_hotelname() == Data::current_user)
                temp++;
        }
        ui->tableWidget->setRowCount(temp);
        for(i=0,j=0;i<Data::rooms_num;i++)
        {
            if(Data::rooms[i].get_hotelname() == Data::current_user)
            {
            QTableWidgetItem * name1 = new QTableWidgetItem();
            if(Data::rooms[i].get_type() == "singleroom")
            name1->setText("单人间");
            if(Data::rooms[i].get_type() == "doubleroom")
            name1->setText("标准间");
            if(Data::rooms[i].get_type() == "luxsingleroom")
            name1->setText("豪华单人间");
            if(Data::rooms[i].get_type() == "luxdoubleroom")
            name1->setText("豪华标准间");
            if(Data::rooms[i].get_type() == "familyroom")
            name1->setText("家庭套房");
            if(Data::rooms[i].get_type() == "presidentroom")
            name1->setText("总统套房");
            ui->tableWidget->setItem(j,0,name1);

            QTableWidgetItem * name2 = new QTableWidgetItem();
            name2->setText(QString::number(Data::rooms[i].get_price()));
            ui->tableWidget->setItem(j,1,name2);

            QTableWidgetItem * name3 = new QTableWidgetItem();
            name3->setText(QString::number(Data::rooms[i].get_lastnum()));
            ui->tableWidget->setItem(j,2,name3);

            QTableWidgetItem *checkBox_1 = new QTableWidgetItem();
            checkBox_1->setCheckState(Qt::Unchecked);
            ui->tableWidget->setItem(j, 3, checkBox_1);
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

        Data::sign_num_2 = 0;
    }

        int temp_row = ui->tableWidget->rowCount();
        int i;
        int sign = 0;
        for(i=0;i<temp_row;i++)
        {
            if(ui->tableWidget->item (i,3)->checkState() == Qt::Unchecked)
            {
            sign = 0;
            }
            else
            {
             sign = 1;
             for(int j = 0;j<Data::rooms_num;j++)
             {
                 QString rotype;
                 if(Data::rooms[j].get_type() == "singleroom")
                     rotype = "单人间";
                 if(Data::rooms[j].get_type() == "doubleroom")
                     rotype = "标准间";
                 if(Data::rooms[j].get_type() == "luxsingleroom")
                     rotype = "豪华单人间";
                 if(Data::rooms[j].get_type() == "luxdoubleroom")
                     rotype = "豪华标准间";
                 if(Data::rooms[j].get_type() == "familyroom")
                     rotype = "家庭套房";
                 if(Data::rooms[j].get_type() == "presidentroom")
                     rotype = "总统套房";

                 if(Data::rooms[j].get_hotelname() == Data::current_user && rotype == ui->tableWidget->item(i,0)->text())
                    Data::row_check = j;
             }
             break;
            }
        }
        if(sign == 0)
        {
            ui->change->setEnabled(false);
        }
        else
        {
            ui->change->setEnabled(true);
        }

    QDialog::paintEvent(event);
}


void hotel_run::on_change_clicked()
{
    changeroom chr;
    chr.exec();
}
//关闭确认
void hotel_run::closeEvent(QCloseEvent * event)
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
