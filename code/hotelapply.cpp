#include "hotelapply.h"
#include "ui_hotelapply.h"
#include "data.h"
#include "hotel.h"

hotelapply::hotelapply(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hotelapply)
{
    ui->setupUi(this);
//界面美化
    this->setWindowIcon(QIcon(":Image/hotel.png"));
    QPixmap pixmap = QPixmap(":/Image/cloud2.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
    ui->city->setStyleSheet("QComboBox {border: 1px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;min-width: 9em;}"
                                "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 20px;\
                                border-left-width: 1px;border-left-color: darkgray;border-left-style: solid;border-top-right-radius: 3px;\
                                border-bottom-right-radius: 3px;}"
                                "QComboBox::down-arrow { image: url(:/Image/xiala.png);}");
    ui->area->setStyleSheet("QComboBox {border: 1px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;min-width: 9em;}"
                                "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 20px;\
                                border-left-width: 1px;border-left-color: darkgray;border-left-style: solid;border-top-right-radius: 3px;\
                                border-bottom-right-radius: 3px;}"
                                "QComboBox::down-arrow { image: url(:/Image/xiala.png);}");
}

hotelapply::~hotelapply()
{
    delete ui;
}

void hotelapply::on_cancel_clicked()
{
    this->close();
}
//重绘
void hotelapply::paintEvent(QPaintEvent *event)
{
    if(ui->city->currentText() == "北京" && Data::sign_num_6 == 0)
    {
        ui->area->clear();
        ui->area->addItem("海淀区");
        ui->area->addItem("朝阳区");
        Data::sign_num_6 = 1;
    }
    if(ui->city->currentText() == "上海" && Data::sign_num_6 == 1)
    {
        ui->area->clear();
        ui->area->addItem("浦东");
        ui->area->addItem("浦西");
        Data::sign_num_6 = 0;
    }
    QDialog::paintEvent(event);
}

void hotelapply::on_apply_clicked()
{
    Data::hotels[Data::hotels_num].set_hotelname(ui->hotelname->text());
    Data::hotels[Data::hotels_num].set_city(ui->city->currentText());
    Data::hotels[Data::hotels_num].set_area(ui->area->currentText());
    Data::hotels_num ++ ;
    Data::hotel_plat[Data::hotel_plat_num].set_hotelname(ui->hotelname->text());
    Data::hotel_plat[Data::hotel_plat_num].set_city(ui->city->currentText());
    Data::hotel_plat[Data::hotel_plat_num].set_area(ui->area->currentText());
    Data::hotel_plat[Data::hotel_plat_num].set_state("false");
    Data::hotel_plat_num++;
    close();
}
