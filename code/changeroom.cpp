#include "changeroom.h"
#include "ui_changeroom.h"
#include "all_headers_nedded.h"
#include "room.h"
#include "data.h"
#include <QFileDialog>

using namespace std;
changeroom::changeroom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeroom)
{
    ui->setupUi(this);
//界面美化
    this->setWindowIcon(QIcon(":Image/hotel.png"));
    QPixmap pixmap = QPixmap(":/Image/cloud2.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
    ui->discount->setStyleSheet("QComboBox {border: 1px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;min-width: 9em;}"
                                "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 20px;\
                                border-left-width: 1px;border-left-color: darkgray;border-left-style: solid;border-top-right-radius: 3px;\
                                border-bottom-right-radius: 3px;}"
                                "QComboBox::down-arrow { image: url(:/Image/xiala.png);}");
//正则表达式约束输入
    QRegExp regx("^[0-9]*[1-9][0-9]*$");
    QValidator *validator = new QRegExpValidator(regx, ui->price);
    ui->price->setValidator(validator);
//初始化显示
    if(Data::rooms[Data::row_check].get_type() == "singleroom")
    ui->roomtype->setText("单人间");
    if(Data::rooms[Data::row_check].get_type() == "doubleroom")
    ui->roomtype->setText("标准间");
    if(Data::rooms[Data::row_check].get_type() == "luxsingleroom")
    ui->roomtype->setText("豪华单人间");
    if(Data::rooms[Data::row_check].get_type() == "luxdoubleroom")
    ui->roomtype->setText("豪华标准间");
    if(Data::rooms[Data::row_check].get_type() == "familyroom")
    ui->roomtype->setText("家庭套房");
    if(Data::rooms[Data::row_check].get_type() == "presidentroom")
    ui->roomtype->setText("总统套房");
    ui->price->setText(QString::number(Data::rooms[Data::row_check].get_price()));
    ui->discount->setCurrentText(Data::rooms[Data::row_check].get_discount());
    ui->lastnum->setValue(Data::rooms[Data::row_check].get_lastnum());
    ui->picture->setPixmap(QPixmap(Data::rooms[Data::row_check].get_picture()));
    ui->description->setText(Data::rooms[Data::row_check].get_description());
}

changeroom::~changeroom()
{
    delete ui;
}

void changeroom::on_cancel_clicked()
{
    this->close();
}

void changeroom::on_confirm_clicked()
{
    Data::rooms[Data::row_check].set_price(ui->price->text().toInt());
    Data::rooms[Data::row_check].set_discount(ui->discount->currentText());
    Data::rooms[Data::row_check].set_lastnum(ui->lastnum->value());
    Data::rooms[Data::row_check].set_description(ui->description->text());
    if(Data::sign_num_4 == 1)
    Data::rooms[Data::row_check].set_picture(Data::file_name_2);

    Data::sign_num_2 = 1;
    this->close();
}

void changeroom::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("选择图片"),"D:",tr("图片文件(* png * jpg)"));
    Data::file_name_2 = filename;
    Data::sign_num_4 = 1;
}
//重绘
void changeroom::paintEvent(QPaintEvent *event)
{
    if (Data::sign_num_4 == 1)
    {
        ui->picture->setPixmap(QPixmap(Data::file_name_2));
        Data::sign_num_4 = 0;
    }
    QDialog::paintEvent(event);
}
