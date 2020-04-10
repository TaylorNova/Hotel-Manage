#include "evaluate.h"
#include "ui_evaluate.h"
#include "data.h"
float tem_score;

evaluate::evaluate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::evaluate)
{
    ui->setupUi(this);
//界面美化
    this->setWindowIcon(QIcon(":Image/hotel.png"));
    QPixmap pixmap = QPixmap(":/Image/clouds.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );

    ui->star1->setStyleSheet("background:transparent");
    ui->star2->setStyleSheet("background:transparent");
    ui->star3->setStyleSheet("background:transparent");
    ui->star4->setStyleSheet("background:transparent");
    ui->star5->setStyleSheet("background:transparent");

    ui->star1->setIcon(QPixmap(":/Image/star1.png"));
    ui->star1->setIconSize(QSize(30,30));
    ui->star2->setIcon(QPixmap(":/Image/star1.png"));
    ui->star2->setIconSize(QSize(30,30));
    ui->star3->setIcon(QPixmap(":/Image/star1.png"));
    ui->star3->setIconSize(QSize(30,30));
    ui->star4->setIcon(QPixmap(":/Image/star1.png"));
    ui->star4->setIconSize(QSize(30,30));
    ui->star5->setIcon(QPixmap(":/Image/star1.png"));
    ui->star5->setIconSize(QSize(30,30));
}

evaluate::~evaluate()
{
    delete ui;
}

void evaluate::on_cancel_clicked()
{
    this->close();
}

void evaluate::on_star1_clicked()
{
    tem_score = 1.0;
    ui->star1->setIcon(QPixmap(":/Image/star.png"));
    ui->star1->setIconSize(QSize(30,30));
    ui->star2->setIcon(QPixmap(":/Image/star1.png"));
    ui->star2->setIconSize(QSize(30,30));
    ui->star3->setIcon(QPixmap(":/Image/star1.png"));
    ui->star3->setIconSize(QSize(30,30));
    ui->star4->setIcon(QPixmap(":/Image/star1.png"));
    ui->star4->setIconSize(QSize(30,30));
    ui->star5->setIcon(QPixmap(":/Image/star1.png"));
    ui->star5->setIconSize(QSize(30,30));
}

void evaluate::on_star2_clicked()
{
    tem_score = 2.0;
    ui->star1->setIcon(QPixmap(":/Image/star.png"));
    ui->star1->setIconSize(QSize(30,30));
    ui->star2->setIcon(QPixmap(":/Image/star.png"));
    ui->star2->setIconSize(QSize(30,30));
    ui->star3->setIcon(QPixmap(":/Image/star1.png"));
    ui->star3->setIconSize(QSize(30,30));
    ui->star4->setIcon(QPixmap(":/Image/star1.png"));
    ui->star4->setIconSize(QSize(30,30));
    ui->star5->setIcon(QPixmap(":/Image/star1.png"));
    ui->star5->setIconSize(QSize(30,30));
}

void evaluate::on_star3_clicked()
{
    tem_score = 3.0;
    ui->star1->setIcon(QPixmap(":/Image/star.png"));
    ui->star1->setIconSize(QSize(30,30));
    ui->star2->setIcon(QPixmap(":/Image/star.png"));
    ui->star2->setIconSize(QSize(30,30));
    ui->star3->setIcon(QPixmap(":/Image/star.png"));
    ui->star3->setIconSize(QSize(30,30));
    ui->star4->setIcon(QPixmap(":/Image/star1.png"));
    ui->star4->setIconSize(QSize(30,30));
    ui->star5->setIcon(QPixmap(":/Image/star1.png"));
    ui->star5->setIconSize(QSize(30,30));
}

void evaluate::on_star4_clicked()
{
    tem_score = 4.0;
    ui->star1->setIcon(QPixmap(":/Image/star.png"));
    ui->star1->setIconSize(QSize(30,30));
    ui->star2->setIcon(QPixmap(":/Image/star.png"));
    ui->star2->setIconSize(QSize(30,30));
    ui->star3->setIcon(QPixmap(":/Image/star.png"));
    ui->star3->setIconSize(QSize(30,30));
    ui->star4->setIcon(QPixmap(":/Image/star.png"));
    ui->star4->setIconSize(QSize(30,30));
    ui->star5->setIcon(QPixmap(":/Image/star1.png"));
    ui->star5->setIconSize(QSize(30,30));
}

void evaluate::on_star5_clicked()
{
    tem_score = 5.0;
    ui->star1->setIcon(QPixmap(":/Image/star.png"));
    ui->star1->setIconSize(QSize(30,30));
    ui->star2->setIcon(QPixmap(":/Image/star.png"));
    ui->star2->setIconSize(QSize(30,30));
    ui->star3->setIcon(QPixmap(":/Image/star.png"));
    ui->star3->setIconSize(QSize(30,30));
    ui->star4->setIcon(QPixmap(":/Image/star.png"));
    ui->star4->setIconSize(QSize(30,30));
    ui->star5->setIcon(QPixmap(":/Image/star.png"));
    ui->star5->setIconSize(QSize(30,30));
}

void evaluate::on_confirm_clicked()
{
    int i;
    for(i=0;i<Data::evalues_num;i++)
    {
        if(Data::evalues[i].get_hotelname() == Data::orders[Data::row_check_5].get_hotel())
            Data::evalues[i].renew_score(tem_score);
    }

    Data::orders[Data::row_check_5].set_pay_state("已评价");
    Data::sign_num_10 = 1;

    QMessageBox tip;
    tip.setWindowTitle(tr("提示"));
    tip.setText("评价成功");
    tip.setStyleSheet("color:rgb(0, 0, 0);font: 10pt");
    tip.setIcon(QMessageBox::Information);
    tip.addButton(tr("确定"),QMessageBox::ActionRole);
    tip.exec();

    this->close();
}
