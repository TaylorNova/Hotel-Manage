#include "managecheck.h"
#include "ui_managecheck.h"
#include "data.h"
#include "backmoncheck.h"
#include <QDate>

managecheck::managecheck(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::managecheck)
{
    ui->setupUi(this);
//界面美化
    this->setWindowIcon(QIcon(":Image/hotel.png"));
    QPixmap pixmap = QPixmap(":/Image/paper1.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
    ui->comboBox->setStyleSheet("QComboBox {border: 1px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;min-width: 9em;}"
                                "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 20px;\
                                border-left-width: 1px;border-left-color: darkgray;border-left-style: solid;border-top-right-radius: 3px;\
                                border-bottom-right-radius: 3px;}"
                                "QComboBox::down-arrow { image: url(:/Image/xiala.png);}");
//初始化界面
    ui->bamoncon->hide();
    ui->cusphonenum->setText(Data::orders[Data::row_check_6].get_cusphonenum());
    ui->price->setText(QString::number(Data::orders[Data::row_check_6].get_room().get_price()));
    ui->roomnum->setText(QString::number(Data::orders[Data::row_check_6].get_roomnum()));
    ui->fromtime->setText(Data::orders[Data::row_check_6].get_fromtime());
    ui->totime->setText(Data::orders[Data::row_check_6].get_totime());
    QString romtype;
    if(Data::orders[Data::row_check_6].get_room().get_type() == "singleroom")
        romtype = "单人间";
    if(Data::orders[Data::row_check_6].get_room().get_type() == "doubleroom")
        romtype = "标准间";
    if(Data::orders[Data::row_check_6].get_room().get_type() == "luxsingleroom")
        romtype = "豪华单人间";
    if(Data::orders[Data::row_check_6].get_room().get_type() == "luxdoubleroom")
        romtype = "豪华标准间";
    if(Data::orders[Data::row_check_6].get_room().get_type() == "familyroom")
        romtype = "家庭套房";
    if(Data::orders[Data::row_check_6].get_room().get_type() == "presidentroom")
        romtype = "总统套房";
    ui->roomtype->setText(romtype);
    ui->picture->setPixmap(QPixmap(Data::orders[Data::row_check_6].get_room().get_picture()));

    float dis;
    if(Data::orders[Data::row_check_6].get_room().get_discount() == "无")
    dis = 1.0;
    if(Data::orders[Data::row_check_6].get_room().get_discount() == "9折")
    dis = 0.9;
    if(Data::orders[Data::row_check_6].get_room().get_discount() == "8折")
    dis = 0.8;
    if(Data::orders[Data::row_check_6].get_room().get_discount() == "7折")
    dis = 0.7;
    if(Data::orders[Data::row_check_6].get_room().get_discount() == "6折")
    dis = 0.6;
    if(Data::orders[Data::row_check_6].get_room().get_discount() == "5折")
    dis = 0.5;
    QDate fromtime;
    fromtime = QDate::fromString(Data::orders[Data::row_check_6].get_fromtime(),"yyyy/MM/dd");
    QDate totime = QDate::fromString(Data::orders[Data::row_check_6].get_totime(),"yyyy/MM/dd");
    int days = fromtime.daysTo(totime);
    ui->totalmoney->setText(QString::number(dis*days*(Data::orders[Data::row_check_6].get_room().get_price())*(Data::orders[Data::row_check_6].get_roomnum())));
    Data::total_money = dis*days*(Data::orders[Data::row_check_6].get_room().get_price())*(Data::orders[Data::row_check_6].get_roomnum());
    ui->paystate->setText(Data::orders[Data::row_check_6].get_pay_state());
    ui->staystate->setText(Data::orders[Data::row_check_6].get_stay_state());
    if(Data::orders[Data::row_check_6].get_backmon_state() == "未退款")
    {
        ui->backmonstate->setText("未退款");
    }
    if(Data::orders[Data::row_check_6].get_backmon_state() == "退款正在受理")
    {
        ui->backmonstate->setText("退款正在受理");
        ui->bamoncon->show();
    }
    if(Data::orders[Data::row_check_6].get_backmon_state() == "退款已完成")
    {
        ui->backmonstate->setText("退款已完成");
    }
}

managecheck::~managecheck()
{
    delete ui;
}

void managecheck::on_back_clicked()
{
    this->close();
}

void managecheck::on_bamoncon_clicked()
{
    backmoncheck bck;
    bck.exec();
}

void managecheck::on_constaystate_clicked()
{
    Data::orders[Data::row_check_6].set_stay_state(ui->comboBox->currentText());
    ui->staystate->setText(Data::orders[Data::row_check_6].get_stay_state());
}
//重绘
void managecheck::paintEvent(QPaintEvent *event)
{
    if(Data::sign_num_11 == 1)
    {
        ui->backmonstate->setText("退款已完成");
        Data::sign_num_11 = 0;
    }

    QDialog::paintEvent(event);
}
