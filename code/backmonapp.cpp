#include "backmonapp.h"
#include "ui_backmonapp.h"
#include "all_headers_nedded.h"
#include "data.h"

backmonapp::backmonapp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::backmonapp)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":Image/hotel.png"));
    QPixmap pixmap = QPixmap(":/Image/clouds.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );

    ui->cusphonenum->setText(Data::orders[Data::row_check_5].get_cusphonenum());
    ui->totalmoney->setText(QString::number(Data::total_money));
}

backmonapp::~backmonapp()
{
    delete ui;
}

void backmonapp::on_confirm_clicked()
{
    Data::orders[Data::row_check_5].set_backmon_state("退款正在受理");
    Data::sign_num_12 = 1;

    QMessageBox tip;
    tip.setWindowTitle(tr("提示"));
    tip.setText("退款申请已提交");
    tip.setStyleSheet("color:rgb(0, 0, 0);font: 10pt");
    tip.setIcon(QMessageBox::Information);
    tip.addButton(tr("确定"),QMessageBox::ActionRole);
    tip.exec();

    this->close();
}

void backmonapp::on_cancel_clicked()
{
    this->close();
}
