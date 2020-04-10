#include "confirmpass.h"
#include "ui_confirmpass.h"
#include "data.h"

confirmpass::confirmpass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirmpass)
{
    ui->setupUi(this);
//界面美化
    this->setWindowIcon(QIcon(":Image/hotel.png"));
    QPixmap pixmap = QPixmap(":/Image/clouds.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
}

confirmpass::~confirmpass()
{
    delete ui;
}

void confirmpass::on_cancel_clicked()
{
    this->close();
}

void confirmpass::on_confirm_clicked()
{
    Data::hotel_plat[Data::row_check_2].set_state("true");
    Data::sign_num_5 = 1;
    this->close();
}
