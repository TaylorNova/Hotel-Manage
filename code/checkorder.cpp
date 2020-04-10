#include "checkorder.h"
#include "ui_checkorder.h"
#include "all_headers_nedded.h"
#include "data.h"
#include "backmonapp.h"
#include "evaluate.h"
#include <QDate>

checkorder::checkorder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::checkorder)
{
    ui->setupUi(this);
//界面美化
    this->setWindowIcon(QIcon(":Image/hotel.png"));
    QPixmap pixmap = QPixmap(":/Image/paper1.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
//初始化显示
    ui->evaluate->hide();
    QString rotype;
    if(Data::orders[Data::row_check_5].get_room().get_type() == "singleroom")
        rotype = "单人间";
    if(Data::orders[Data::row_check_5].get_room().get_type() == "doubleroom")
        rotype = "标准间";
    if(Data::orders[Data::row_check_5].get_room().get_type() == "luxsingleroom")
        rotype = "豪华单人间";
    if(Data::orders[Data::row_check_5].get_room().get_type() == "luxdoubleroom")
        rotype = "豪华标准间";
    if(Data::orders[Data::row_check_5].get_room().get_type() == "familyroom")
        rotype = "家庭套房";
    if(Data::orders[Data::row_check_5].get_room().get_type() == "presidentroom")
        rotype = "总统套房";
    ui->type->setText(rotype);
    ui->price->setText(QString::number(Data::orders[Data::row_check_5].get_room().get_price()));
    ui->discount->setText(Data::orders[Data::row_check_5].get_room().get_discount());
    ui->picture->setPixmap(QPixmap(Data::orders[Data::row_check_5].get_room().get_picture()));
    ui->roomnum->setText(QString::number(Data::orders[Data::row_check_5].get_roomnum()));
    ui->fromtime->setText(Data::orders[Data::row_check_5].get_fromtime());
    ui->totime->setText(Data::orders[Data::row_check_5].get_totime());
    ui->paystate->setText(Data::orders[Data::row_check_5].get_pay_state());
    ui->backmonstate->setText(Data::orders[Data::row_check_5].get_backmon_state());
    ui->staystate->setText(Data::orders[Data::row_check_5].get_stay_state());
    float dis;
    if(Data::orders[Data::row_check_5].get_room().get_discount() == "无")
    dis = 1.0;
    if(Data::orders[Data::row_check_5].get_room().get_discount() == "9折")
    dis = 0.9;
    if(Data::orders[Data::row_check_5].get_room().get_discount() == "8折")
    dis = 0.8;
    if(Data::orders[Data::row_check_5].get_room().get_discount() == "7折")
    dis = 0.7;
    if(Data::orders[Data::row_check_5].get_room().get_discount() == "6折")
    dis = 0.6;
    if(Data::orders[Data::row_check_5].get_room().get_discount() == "5折")
    dis = 0.5;
    QDate fromtime;
    fromtime = QDate::fromString(Data::orders[Data::row_check_5].get_fromtime(),"yyyy/MM/dd");
    QDate totime = QDate::fromString(Data::orders[Data::row_check_5].get_totime(),"yyyy/MM/dd");
    int days = fromtime.daysTo(totime);
    ui->totalmoney->setText(QString::number(dis*(Data::orders[Data::row_check_5].get_room().get_price())*(Data::orders[Data::row_check_5].get_roomnum())*days));
    Data::total_money = dis*(Data::orders[Data::row_check_5].get_room().get_price())*(Data::orders[Data::row_check_5].get_roomnum())*days;
}

checkorder::~checkorder()
{
    delete ui;
}

void checkorder::on_back_clicked()
{
    this->close();
}

void checkorder::on_backmonapply_clicked()
{
    backmonapp bmp;
    bmp.exec();
}
//重绘
void checkorder::paintEvent(QPaintEvent *event)
{
    if(Data::sign_num_12 == 1)
    {
        ui->backmonstate->setText("退款正在受理");
        Data::sign_num_12 = 0;
    }

    if(ui->staystate->text() == "已退房" && ui->paystate->text() == "已支付" && ui->backmonstate->text() == "未退款")
    {
        ui->evaluate->show();
    }

    QDialog::paintEvent(event);
}

void checkorder::on_evaluate_clicked()
{
    evaluate evt;
    evt.exec();
}
