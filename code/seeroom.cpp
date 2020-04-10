#include "seeroom.h"
#include "ui_seeroom.h"
#include "all_headers_nedded.h"
#include "data.h"
#include "orderroom.h"

seeroom::seeroom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::seeroom)
{
    ui->setupUi(this);
//界面美化
    this->setWindowIcon(QIcon(":Image/hotel.png"));
    QPixmap pixmap = QPixmap(":/Image/cloud1.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
    ui->view->setStyleSheet("background-color: rgba(255,255,255,0)");
    ui->view->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgba(255,255,255,0);}");
    ui->view->verticalHeader()->setVisible(false);
//初始化表格
    int i;
    int j = 0;
    int temp = 0;
    for(i=0;i<Data::rooms_num;i++)
    {
        if(Data::rooms[i].get_hotelname() == Data::choose_hotel)
        {
            Data::arr[temp] = i;
            temp++;
        }
    }

    ui->view->setRowCount(temp);

    for(i=0;i<Data::rooms_num;i++)
    {
        if(Data::rooms[i].get_hotelname() == Data::choose_hotel)
        {
            QTableWidgetItem * it1 = new QTableWidgetItem();
            QString rotype;
            if(Data::rooms[i].get_type() == "singleroom")
                rotype = "单人间";
            if(Data::rooms[i].get_type() == "doubleroom")
                rotype = "标准间";
            if(Data::rooms[i].get_type() == "luxsingleroom")
                rotype = "豪华单人间";
            if(Data::rooms[i].get_type() == "luxdoubleroom")
                rotype = "豪华标准间";
            if(Data::rooms[i].get_type() == "familyroom")
                rotype = "家庭套房";
            if(Data::rooms[i].get_type() == "presidentroom")
                rotype = "总统套房";
            it1->setText(rotype);
            ui->view->setItem(j,0,it1);

            QTableWidgetItem * it2 = new QTableWidgetItem();
            it2->setText(QString::number(Data::rooms[i].get_price()));
            ui->view->setItem(j,1,it2);

            QTableWidgetItem * it3 = new QTableWidgetItem();
            it3->setText(QString::number(Data::rooms[i].get_lastnum()));
            ui->view->setItem(j,2,it3);

            QLabel *lab = new QLabel("");
            lab->setPixmap(QPixmap(Data::rooms[i].get_picture()).scaled(100,60));
            ui->view->setCellWidget(j,3,lab);

            QTableWidgetItem *checkBox_1 = new QTableWidgetItem();
            checkBox_1->setCheckState(Qt::Unchecked);
            ui->view->setItem(j, 4, checkBox_1);

            j++;
        }
    }
}

seeroom::~seeroom()
{
    delete ui;
}

void seeroom::on_cancel_clicked()
{
    this->close();
}
//重绘
void seeroom::paintEvent(QPaintEvent *event)
{
    if(Data::sign_num_15 == 1)
    {
        int i;
        int j = 0;
        int temp = 0;
        for(i=0;i<Data::rooms_num;i++)
        {
            if(Data::rooms[i].get_hotelname() == Data::choose_hotel)
            {
                Data::arr[temp] = i;
                temp++;
            }
        }

        ui->view->setRowCount(temp);

        for(i=0;i<Data::rooms_num;i++)
        {
            if(Data::rooms[i].get_hotelname() == Data::choose_hotel)
            {
                QTableWidgetItem * it1 = new QTableWidgetItem();
                QString rotype;
                if(Data::rooms[i].get_type() == "singleroom")
                    rotype = "单人间";
                if(Data::rooms[i].get_type() == "doubleroom")
                    rotype = "标准间";
                if(Data::rooms[i].get_type() == "luxsingleroom")
                    rotype = "豪华单人间";
                if(Data::rooms[i].get_type() == "luxdoubleroom")
                    rotype = "豪华标准间";
                if(Data::rooms[i].get_type() == "familyroom")
                    rotype = "家庭套房";
                if(Data::rooms[i].get_type() == "presidentroom")
                    rotype = "总统套房";
                it1->setText(rotype);
                ui->view->setItem(j,0,it1);

                QTableWidgetItem * it2 = new QTableWidgetItem();
                it2->setText(QString::number(Data::rooms[i].get_price()));
                ui->view->setItem(j,1,it2);

                QTableWidgetItem * it3 = new QTableWidgetItem();
                it3->setText(QString::number(Data::rooms[i].get_lastnum()));
                ui->view->setItem(j,2,it3);

                QLabel *lab = new QLabel("");
                lab->setPixmap(QPixmap(Data::rooms[i].get_picture()).scaled(100,60));
                ui->view->setCellWidget(j,3,lab);

                QTableWidgetItem *checkBox_1 = new QTableWidgetItem();
                checkBox_1->setCheckState(Qt::Unchecked);
                ui->view->setItem(j, 4, checkBox_1);

                j++;
            }
        }
     Data::sign_num_15 = 0;
     Data::sign_num_16 = 1;
    }

    if(Data::sign_num_8 == 1)
    {
        int i;
        int j = 0;
        int temp = 0;
        for(i=0;i<Data::rooms_num;i++)
        {
            if(Data::rooms[i].get_hotelname() == Data::choose_hotel)
            {
                temp++;
            }
        }

        ui->view->setRowCount(temp);

        for(j=0;j<temp;j++)
        {
            for(i=0;i<Data::rooms_num;i++)
            {
                if(i == Data::arr[j])
                {
                    QTableWidgetItem * it1 = new QTableWidgetItem();
                    QString rotype;
                    if(Data::rooms[i].get_type() == "singleroom")
                        rotype = "单人间";
                    if(Data::rooms[i].get_type() == "doubleroom")
                        rotype = "标准间";
                    if(Data::rooms[i].get_type() == "luxsingleroom")
                        rotype = "豪华单人间";
                    if(Data::rooms[i].get_type() == "luxdoubleroom")
                        rotype = "豪华标准间";
                    if(Data::rooms[i].get_type() == "familyroom")
                        rotype = "家庭套房";
                    if(Data::rooms[i].get_type() == "presidentroom")
                        rotype = "总统套房";
                    it1->setText(rotype);
                    ui->view->setItem(j,0,it1);

                    QTableWidgetItem * it2 = new QTableWidgetItem();
                    it2->setText(QString::number(Data::rooms[i].get_price()));
                    ui->view->setItem(j,1,it2);

                    QTableWidgetItem * it3 = new QTableWidgetItem();
                    it3->setText(QString::number(Data::rooms[i].get_lastnum()));
                    ui->view->setItem(j,2,it3);

                    QLabel *lab = new QLabel("");
                    lab->setPixmap(QPixmap(Data::rooms[i].get_picture()).scaled(100,60));
                    ui->view->setCellWidget(j,3,lab);

                    QTableWidgetItem *checkBox_1 = new QTableWidgetItem();
                    checkBox_1->setCheckState(Qt::Unchecked);
                    ui->view->setItem(j, 4, checkBox_1);

                }
            }
        }
        Data::sign_num_8 = 0;
    }

    if(Data::sign_num_9 == 1)
    {
        int i;
        int j = 0;
        int temp = 0;
        for(i=0;i<Data::rooms_num;i++)
        {
            if(Data::rooms[i].get_hotelname() == Data::choose_hotel)
            {
                temp++;
            }
        }

        ui->view->setRowCount(temp);

        for(j=0;j<temp;j++)
        {
            for(i=0;i<Data::rooms_num;i++)
            {
                if(i == Data::arr[j])
                {
                    QTableWidgetItem * it1 = new QTableWidgetItem();
                    QString rotype;
                    if(Data::rooms[i].get_type() == "singleroom")
                        rotype = "单人间";
                    if(Data::rooms[i].get_type() == "doubleroom")
                        rotype = "标准间";
                    if(Data::rooms[i].get_type() == "luxsingleroom")
                        rotype = "豪华单人间";
                    if(Data::rooms[i].get_type() == "luxdoubleroom")
                        rotype = "豪华标准间";
                    if(Data::rooms[i].get_type() == "familyroom")
                        rotype = "家庭套房";
                    if(Data::rooms[i].get_type() == "presidentroom")
                        rotype = "总统套房";
                    it1->setText(rotype);
                    ui->view->setItem(j,0,it1);

                    QTableWidgetItem * it2 = new QTableWidgetItem();
                    it2->setText(QString::number(Data::rooms[i].get_price()));
                    ui->view->setItem(j,1,it2);

                    QTableWidgetItem * it3 = new QTableWidgetItem();
                    it3->setText(QString::number(Data::rooms[i].get_lastnum()));
                    ui->view->setItem(j,2,it3);

                    QLabel *lab = new QLabel("");
                    lab->setPixmap(QPixmap(Data::rooms[i].get_picture()).scaled(100,60));
                    ui->view->setCellWidget(j,3,lab);

                    QTableWidgetItem *checkBox_1 = new QTableWidgetItem();
                    checkBox_1->setCheckState(Qt::Unchecked);
                    ui->view->setItem(j, 4, checkBox_1);

                }
            }
        }

        Data::sign_num_9 = 0;
    }

    int temp_row = 0;
    int i;
    int sign = 0;
    temp_row = ui->view->rowCount();
    for(i=0;i<temp_row;i++)
    {
        if(ui->view->item (i,4)->checkState() == Qt::Unchecked)
        {
        sign = 0;
        }
        else
        {
         sign = 1;
         Data::row_check_4 = Data::arr[i];
         break;
        }
    }
    if(sign == 0)
    {
        ui->order->setEnabled(false);
    }
    else
    {
        ui->order->setEnabled(true);
    }

    QDialog::paintEvent(event);
}
//按价格高低排序（降序）
void seeroom::on_sort_up_clicked()
{
    int i;
    int tem_num = 0;
    int j = 0;
    for(i=0;i<Data::rooms_num;i++)
    {
        if(Data::rooms[i].get_hotelname() == Data::choose_hotel)
        {
            tem_num++;
            Data::arr[j] = i;
            j++;
        }
    }

    int te;
    for(i=0;i<tem_num-1;i++)
    {
        for(j=0;j < tem_num-1-i ;j++)
        {
            if(Data::rooms[Data::arr[j]].get_price() < Data::rooms[Data::arr[j+1]].get_price())
            {
                te = Data::arr[j+1];
                Data::arr[j+1] = Data::arr[j];
                Data::arr[j] = te;
            }
        }
    }
    Data::sign_num_9 = 1;
}
//按价格高低排序（升序）
void seeroom::on_sort_down_clicked()
{
    int i;
    int tem_num = 0;
    int j = 0;
    for(i=0;i<Data::rooms_num;i++)
    {
        if(Data::rooms[i].get_hotelname() == Data::choose_hotel)
        {
            tem_num++;
            Data::arr[j] = i;
            j++;
        }
    }

    int te;
    for(i=0;i<tem_num-1;i++)
    {
        for(j=0;j < tem_num-1-i ;j++)
        {
            if(Data::rooms[Data::arr[j]].get_price() > Data::rooms[Data::arr[j+1]].get_price())
            {
                te = Data::arr[j+1];
                Data::arr[j+1] = Data::arr[j];
                Data::arr[j] = te;
            }
        }
    }
    Data::sign_num_8 = 1;
}

void seeroom::on_order_clicked()
{
    orderroom odr;
    odr.exec();
}
