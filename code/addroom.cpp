#include "addroom.h"
#include "ui_addroom.h"
#include "data.h"
#include "room.h"
#include "all_headers_nedded.h"
#include <QFileDialog>

using namespace std;
addroom::addroom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addroom)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":Image/hotel.png"));

    QPixmap pixmap = QPixmap(":/Image/cloud2.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
    ui->type->setStyleSheet("QComboBox {border: 1px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;min-width: 9em;}"
                                "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 20px;\
                                border-left-width: 1px;border-left-color: darkgray;border-left-style: solid;border-top-right-radius: 3px;\
                                border-bottom-right-radius: 3px;}"
                                "QComboBox::down-arrow { image: url(:/Image/xiala.png);}");
    ui->discount->setStyleSheet("QComboBox {border: 1px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;min-width: 9em;}"
                                "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 20px;\
                                border-left-width: 1px;border-left-color: darkgray;border-left-style: solid;border-top-right-radius: 3px;\
                                border-bottom-right-radius: 3px;}"
                                "QComboBox::down-arrow { image: url(:/Image/xiala.png);}");

    QRegExp regx("^[0-9]*[1-9][0-9]*$");
    QValidator *validator = new QRegExpValidator(regx, ui->price);
    ui->price->setValidator(validator);
}

addroom::~addroom()
{
    delete ui;
}
//确认添加
void addroom::on_confirm_clicked()
{
    QString rotype;
    if(ui->type->currentText() == "单人间")
        rotype = "singleroom";
    if(ui->type->currentText() == "标准间")
        rotype = "doubleroom";
    if(ui->type->currentText() == "豪华单人间")
        rotype = "luxsingleroom";
    if(ui->type->currentText() == "豪华标准间")
        rotype = "luxdoubleroom";
    if(ui->type->currentText() == "家庭套房")
        rotype = "familyroom";
    if(ui->type->currentText() == "总统套房")
        rotype = "presidentroom";
    int tem_price;
    QString te_price;
    te_price = ui->price->text();
    tem_price = te_price.toInt();
    Data::rooms[Data::rooms_num].set_type(rotype);
    Data::rooms[Data::rooms_num].set_price(tem_price);
    Data::rooms[Data::rooms_num].set_discount(ui->discount->currentText());
    Data::rooms[Data::rooms_num].set_description(ui->description->text());
    Data::rooms[Data::rooms_num].set_lastnum(ui->lastnum->value());
    Data::rooms[Data::rooms_num].set_picture(Data::file_name);
    Data::rooms[Data::rooms_num].set_hotelname(Data::current_user);
    Data::rooms_num++;
    Data::sign_num = 1;
    close();
}

void addroom::on_cancel_clicked()
{
    this->close();
}
//选择图片
void addroom::on_choosepic_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("选择图片"),"D:",tr("图片文件(* png * jpg)"));
    Data::file_name = filename;
    Data::sign_num_3 = 1;
}
//重绘
void addroom::paintEvent(QPaintEvent *event)
{
    if (Data::sign_num_3 == 1)
    {
        ui->picture->setPixmap(QPixmap(Data::file_name));
        Data::sign_num_3 = 0;
    }
    QDialog::paintEvent(event);
}
