#include "orderroom.h"
#include "ui_orderroom.h"
#include "data.h"
#include "pay.h"

orderroom::orderroom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::orderroom)
{
    ui->setupUi(this);
//界面美化
    this->setWindowIcon(QIcon(":Image/hotel.png"));
    QPixmap pixmap = QPixmap(":/Image/cloud2.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );

    QRegExp regx1("[1-9][0-9]+$");
    QValidator *validator1 = new QRegExpValidator(regx1, ui->phonenum);
    ui->phonenum->setValidator(validator1);
//初始化界面
    ui->tip->hide();

    QString rotype;
    if(Data::rooms[Data::row_check_4].get_type() == "singleroom")
        rotype = "单人间";
    if(Data::rooms[Data::row_check_4].get_type() == "doubleroom")
        rotype = "标准间";
    if(Data::rooms[Data::row_check_4].get_type() == "luxsingleroom")
        rotype = "豪华单人间";
    if(Data::rooms[Data::row_check_4].get_type() == "luxdoubleroom")
        rotype = "豪华标准间";
    if(Data::rooms[Data::row_check_4].get_type() == "familyroom")
        rotype = "家庭套房";
    if(Data::rooms[Data::row_check_4].get_type() == "presidentroom")
        rotype = "总统套房";
    ui->type->setText(rotype);
    ui->price->setText(QString::number(Data::rooms[Data::row_check_4].get_price()));
    ui->discount->setText(Data::rooms[Data::row_check_4].get_discount());
    ui->picture->setPixmap(QPixmap(Data::rooms[Data::row_check_4].get_picture()));
    ui->lastnum->setText(QString::number(Data::rooms[Data::row_check_4].get_lastnum()));
    ui->roomnum->setRange(0,Data::rooms[Data::row_check_4].get_lastnum());
    ui->description->setText(Data::rooms[Data::row_check_4].get_description());

    ui->calendarWidget->hide();
    ui->calendarWidget_2->hide();

    QDate date_1 = ui->calendarWidget->selectedDate();
    QString datestr1 = date_1.toString("yyyy/MM/dd");
    ui->from->setText(datestr1);

    QDate date_2 = ui->calendarWidget_2->selectedDate();
    QString datestr2 = date_2.toString("yyyy/MM/dd");
    ui->to->setText(datestr2);

    connect(ui->calendarWidget,SIGNAL(selectionChanged()),this,SLOT(settime_1()));
    connect(ui->calendarWidget_2,SIGNAL(selectionChanged()),this,SLOT(settime_2()));
}

orderroom::~orderroom()
{
    delete ui;
}

void orderroom::on_opentime_clicked()
{
    ui->calendarWidget->show();
}

void orderroom::on_opentime_2_clicked()
{
    ui->calendarWidget_2->show();
}
//设置时间
void orderroom::settime_1()
{
    QDate date = ui->calendarWidget->selectedDate();
    QString datestr = date.toString("yyyy/MM/dd");
    if(ui->to->text() <= datestr)
        ui->from->setText("");
    else
    ui->from->setText(datestr);
    ui->calendarWidget->hide();
}
//设置时间
void orderroom::settime_2()
{
    QDate date = ui->calendarWidget_2->selectedDate();
    QString datestr = date.toString("yyyy/MM/dd");
    if(ui->from->text() >= datestr)
        ui->to->setText("");
    else
    ui->to->setText(datestr);
    ui->calendarWidget_2->hide();
}

void orderroom::on_cancel_clicked()
{
    this->close();
}

void orderroom::on_confirm_clicked()
{
    Data::orders[Data::orders_num].set_roomnum(ui->roomnum->value());
    Data::orders[Data::orders_num].set_fromtime(ui->from->text());
    Data::orders[Data::orders_num].set_totime(ui->to->text());
    Room tem_room = Data::rooms[Data::row_check_4];
    Data::orders[Data::orders_num].set_room(tem_room);
    Data::orders[Data::orders_num].set_hotel(Data::choose_hotel);
    Data::orders[Data::orders_num].set_pay_state("");
    Data::orders[Data::orders_num].set_backmon_state("未退款");
    Data::orders[Data::orders_num].set_stay_state("未入住");
    Data::orders[Data::orders_num].set_roomcus(ui->people->text());
    Data::orders[Data::orders_num].set_cusphonenum(ui->phonenum->text());
    Data::choose_day = ui->calendarWidget->selectedDate().daysTo(ui->calendarWidget_2->selectedDate());
    Data::choose_roomnum = ui->roomnum->value();
    pay p1;
    p1.exec();
}
//判断手机号是否合理
bool orderroom::judge_valid_phonenum(QString the_phonenum)
{
    if (the_phonenum.size() != 11)
    {
        return 0;
    }
    if (the_phonenum[0] != '1')
    {
        return 0;
    }
    for (int i = 1; i<11; i++)
    {
        if (the_phonenum[i]<'0' || the_phonenum[i]>'9')
        {
            return 0;
        }
    }
    return 1;
}
//重绘
void orderroom::paintEvent(QPaintEvent *event)
{
    if(judge_valid_phonenum(ui->phonenum->text()))
    {
        ui->confirm->setEnabled(true);
        ui->tip->hide();
    }
    else
    {
        ui->tip->show();
        ui->confirm->setEnabled(false);
    }

    if(Data::sign_num_14 == 1)
    {
        ui->lastnum->setText(QString::number(Data::rooms[Data::row_check_4].get_lastnum()));
        Data::sign_num_14 = 0;
        Data::sign_num_15 = 1;
    }

    QDialog::paintEvent(event);
}
