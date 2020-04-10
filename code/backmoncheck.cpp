#include "backmoncheck.h"
#include "ui_backmoncheck.h"
#include "all_headers_nedded.h"
#include "data.h"

using namespace std;
backmoncheck::backmoncheck(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::backmoncheck)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":Image/hotel.png"));
    QPixmap pixmap = QPixmap(":/Image/clouds.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );

    ui->cusphonenum->setText(Data::orders[Data::row_check_6].get_cusphonenum());
    ui->totalmoney->setText(QString::number(Data::total_money));
}

backmoncheck::~backmoncheck()
{
    delete ui;
}

void backmoncheck::on_cancel_clicked()
{
    this->close();
}

void backmoncheck::on_confirm_clicked()
{
    Data::orders[Data::row_check_6].set_backmon_state("退款已完成");
    Data::sign_num_11 = 1;
    int i;
    for(i=0;i<Data::rooms_num;i++)
    {
        if(Data::orders[Data::row_check_6].get_hotel() == Data::rooms[i].get_hotelname() && Data::orders[Data::row_check_6].get_room().get_type() == Data::rooms[i].get_type())
        {
            int now_num;
            now_num = Data::rooms[i].get_lastnum();
            Data::rooms[i].set_lastnum(now_num+Data::orders[Data::row_check_6].get_roomnum());
        }
    }

    QMessageBox tip;
    tip.setWindowTitle(tr("提示"));
    tip.setText("退款已完成");
    tip.setStyleSheet("color:rgb(0, 0, 0);font: 10pt");
    tip.setIcon(QMessageBox::Information);
    tip.addButton(tr("确定"),QMessageBox::ActionRole);
    tip.exec();

    this->close();
}
