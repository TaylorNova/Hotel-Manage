#include "findroom.h"
#include "ui_findroom.h"
#include "all_headers_nedded.h"
#include "data.h"
#include "seeroom.h"
#include "evalue.h"

int arr[100];

findroom::findroom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findroom)
{
    ui->setupUi(this);
//界面美化
    this->setWindowIcon(QIcon(":Image/hotel.png"));
    QPixmap pixmap = QPixmap(":/Image/cloudss.jpg").scaled(this->size());
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
    for(i=0;i<Data::hotel_plat_num;i++)
    {
        if (Data::hotel_plat[i].get_city() == Data::record[0].get_choose_city() && Data::hotel_plat[i].get_area() == Data::record[0].get_choose_area() && Data::hotel_plat[i].get_star() == Data::record[0].get_choose_star())
        {
            temp++;
        }
    }

    ui->tableWidget->setRowCount(temp);

    for(i=0;i<Data::hotel_plat_num;i++)
    {
        if (Data::hotel_plat[i].get_city() == Data::record[0].get_choose_city() && Data::hotel_plat[i].get_area() == Data::record[0].get_choose_area() && Data::hotel_plat[i].get_star() == Data::record[0].get_choose_star())
        {
            QTableWidgetItem * its1 = new QTableWidgetItem();
            its1->setText(Data::hotel_plat[i].get_hotelname());
            ui->tableWidget->setItem(j,0,its1);

            QTableWidgetItem * its2 = new QTableWidgetItem();
            its2->setText(Data::hotel_plat[i].get_city());
            ui->tableWidget->setItem(j,1,its2);

            QTableWidgetItem * its3 = new QTableWidgetItem();
            its3->setText(Data::hotel_plat[i].get_area());
            ui->tableWidget->setItem(j,2,its3);

            QTableWidgetItem * its4 = new QTableWidgetItem();
            its4->setText(Data::hotel_plat[i].get_star());
            ui->tableWidget->setItem(j,3,its4);

            float tem;
            for(int m = 0;m < Data::evalues_num;m++)
            {
                if(Data::evalues[m].get_hotelname() == Data::hotel_plat[i].get_hotelname())
                    tem = Data::evalues[m].get_score();
            }
            QTableWidgetItem * its5 = new QTableWidgetItem();
            its5->setText(QString::number(tem,'f',1));
            ui->tableWidget->setItem(j,4,its5);

            QTableWidgetItem *checkBox_1 = new QTableWidgetItem();
            checkBox_1->setCheckState(Qt::Unchecked);
            ui->tableWidget->setItem(j, 5, checkBox_1);
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

findroom::~findroom()
{
    delete ui;
}

void findroom::on_pushButton_2_clicked()
{
    this->close();
}
//重绘
void findroom::paintEvent(QPaintEvent *event)
{
    int temp_row = 0;
    int i;
    int sign = 0;
    temp_row = ui->tableWidget->rowCount();
    for(i=0;i<temp_row;i++)
    {
        if(ui->tableWidget->item (i,5)->checkState() == Qt::Unchecked)
        {
        sign = 0;
        }
        else
        {
         sign = 1;
         Data::choose_hotel = ui->tableWidget->item (i,0)->text();
         break;
        }
    }
    if(sign == 0)
    {
        ui->details->setEnabled(false);
    }
    else
    {
        ui->details->setEnabled(true);
    }

    if(Data::sign_num_13 == 1)
    {
        int i;
        int j = 0;
        int temp = 0;
        for(i=0;i<Data::hotel_plat_num;i++)
        {
            if (Data::hotel_plat[i].get_city() == Data::record[0].get_choose_city() && Data::hotel_plat[i].get_area() == Data::record[0].get_choose_area() && Data::hotel_plat[i].get_star() == Data::record[0].get_choose_star())
            {
                temp++;
            }
        }

        ui->tableWidget->setRowCount(temp);

        for(i=0;i<Data::hotel_plat_num;i++)
        {
            for(j=0;j<temp;j++)
            {
                if (i == arr[j])
                {
                    QTableWidgetItem * its1 = new QTableWidgetItem();
                    its1->setText(Data::hotel_plat[i].get_hotelname());
                    ui->tableWidget->setItem(j,0,its1);

                    QTableWidgetItem * its2 = new QTableWidgetItem();
                    its2->setText(Data::hotel_plat[i].get_city());
                    ui->tableWidget->setItem(j,1,its2);

                    QTableWidgetItem * its3 = new QTableWidgetItem();
                    its3->setText(Data::hotel_plat[i].get_area());
                    ui->tableWidget->setItem(j,2,its3);

                    QTableWidgetItem * its4 = new QTableWidgetItem();
                    its4->setText(Data::hotel_plat[i].get_star());
                    ui->tableWidget->setItem(j,3,its4);

                    float tem;
                    for(int m = 0;m < Data::evalues_num;m++)
                    {
                        if(Data::evalues[m].get_hotelname() == Data::hotel_plat[i].get_hotelname())
                            tem = Data::evalues[m].get_score();
                    }

                    QTableWidgetItem * its5 = new QTableWidgetItem();
                    its5->setText(QString::number(tem,'f',1));
                    ui->tableWidget->setItem(j,4,its5);

                    QTableWidgetItem *checkBox_1 = new QTableWidgetItem();
                    checkBox_1->setCheckState(Qt::Unchecked);
                    ui->tableWidget->setItem(j, 5, checkBox_1);
                }
            }
        }
        for(int a=0;a<ui->tableWidget->rowCount();a++)
        {
            for(int b=0;b<ui->tableWidget->columnCount();b++)
            {
                    ui->tableWidget->item(a,b)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }
        }

        Data::sign_num_13 = 0;
    }

    QDialog::paintEvent(event);
}

void findroom::on_details_clicked()
{
    seeroom ser;
    ser.exec();
}

void findroom::on_sort_clicked()
{
    int i;
    int tem_num = 0;
    int j = 0;

    for(i=0;i<Data::hotel_plat_num;i++)
    {
        if (Data::hotel_plat[i].get_city() == Data::record[0].get_choose_city() && Data::hotel_plat[i].get_area() == Data::record[0].get_choose_area() && Data::hotel_plat[i].get_star() == Data::record[0].get_choose_star())
        {
            tem_num++;
            arr[j] = i;
            j++;
        }
    }

    int te;
    for(i=0;i<tem_num-1;i++)
    {
        for(j=0;j < tem_num-1-i ;j++)
        {
            float sc1;
            float sc2;
            for(int m=0;m<Data::evalues_num;m++)
            {
                if(Data::evalues[m].get_hotelname() == Data::hotel_plat[arr[j]].get_hotelname())
                    sc1 = Data::evalues[m].get_score();
                if(Data::evalues[m].get_hotelname() == Data::hotel_plat[arr[j+1]].get_hotelname())
                    sc2 = Data::evalues[m].get_score();
            }

            if(sc1<sc2)
            {
                te = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = te;
            }
        }
    }

    Data::sign_num_13 = 1;
}
