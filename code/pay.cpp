#include "pay.h"
#include "ui_pay.h"
#include "all_headers_nedded.h"
#include "data.h"
#include <iostream>
using namespace std;

pay::pay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pay)
{
    ui->setupUi(this);
//界面美化
    this->setWindowIcon(QIcon(":Image/hotel.png"));
    QPixmap pixmap = QPixmap(":/Image/clouds.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
//初始化界面
    float dis;
    if(Data::rooms[Data::row_check_4].get_discount() == "无")
    dis = 1.0;
    if(Data::rooms[Data::row_check_4].get_discount() == "9折")
    dis = 0.9;
    if(Data::rooms[Data::row_check_4].get_discount() == "8折")
    dis = 0.8;
    if(Data::rooms[Data::row_check_4].get_discount() == "7折")
    dis = 0.7;
    if(Data::rooms[Data::row_check_4].get_discount() == "6折")
    dis = 0.6;
    if(Data::rooms[Data::row_check_4].get_discount() == "5折")
    dis = 0.5;
    ui->price->setText(QString::number(dis*(Data::choose_roomnum)*(Data::choose_day)*(Data::rooms[Data::row_check_4].get_price())));
}

pay::~pay()
{
    delete ui;
}

void pay::on_cancel_clicked()
{
    this->close();
}

void pay::on_confirm_clicked()
{
    int now_num;
    int now_num2;
    now_num = Data::rooms[Data::row_check_4].get_lastnum();
    now_num2 = Data::orders[Data::orders_num].get_roomnum();
    Data::orders[Data::orders_num].set_pay_state("已支付");
    Data::orders_num++;
    int tem_num;
    tem_num = now_num-now_num2;
    Data::rooms[Data::row_check_4].set_lastnum(tem_num);

    QMessageBox tip;
    tip.setWindowTitle(tr("提示"));
    tip.setText("支付成功");
    tip.setStyleSheet("color:rgb(0, 0, 0);font: 10pt");
    tip.setIcon(QMessageBox::Information);
    tip.addButton(tr("确定"),QMessageBox::ActionRole);
    tip.exec();

    Data::sign_num_14 = 1;

    this->close();
}
