#include "register.h"
#include "ui_register.h"
#include <iostream>
#include "data.h"
#include "people.h"
#include "customer.h"
#include "manager.h"
#include "hotel.h"
#include <QPaintEvent>
#include "hotelapply.h"

using namespace std;

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    QPixmap pixmap = QPixmap(":/Image/hotela.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
    this->setWindowIcon(QIcon(":Image/hotel.png"));
    ui->comboBox->setStyleSheet("QComboBox {border: 1px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;min-width: 9em;}"
                                "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 20px;\
                                border-left-width: 1px;border-left-color: darkgray;border-left-style: solid;border-top-right-radius: 3px;\
                                border-bottom-right-radius: 3px;}"
                                "QComboBox::down-arrow { image: url(:/Image/xiala.png);}");

    //使得手机号输入框只能输入数字 正则表达式
    QRegExp regx("[1-9][0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->phonenum);
    ui->phonenum->setValidator(validator);
    //使得密码输入框只能输入密码 正则表达式
    QRegExp regx_pwd("^[A-Za-z0-9]+$");
    QValidator *validator_pwd = new QRegExpValidator(regx_pwd, ui->password);
    ui->password->setValidator(validator_pwd);
    //使得密码输入框只能输入密码 正则表达式
    QValidator *validator_pwd_ag = new QRegExpValidator(regx_pwd, ui->passwordcon);
    ui->passwordcon->setValidator(validator_pwd_ag);

    ui->label_p->hide();
    ui->label_rw->hide();
    ui->label_w->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->manager_hotel->hide();
}

Register::~Register()
{
    delete ui;
}

void Register::on_confirm_clicked()
{
    int sign;
    if(ui->comboBox->currentText() == "顾客")
        sign=1;
    if(ui->comboBox->currentText() == "管理员")
        sign=2;
    if(ui->comboBox->currentText() == "酒店")
        sign=3;
    QString the_phonum = ui->phonenum->text();
    if (login_re_reg(the_phonum))
    {
        QMessageBox::warning(this, tr("警告"), tr("该手机号已被注册！"), QMessageBox::Yes);
    }
    else if (judge_valid_phonenum(ui->phonenum->text()) && ui->password->text() == ui->passwordcon->text() && judge_blank_pwd(ui->password->text()))
    {
        if(sign == 1)
        {
        Customer te_cus;
        te_cus.set_phonenum(ui->phonenum->text());
        te_cus.set_password(ui->password->text());
        te_cus.set_identity("customer");
        te_cus.save_to_database_register();
        Data::customers[Data::customers_num].set_phonenum(ui->phonenum->text());
        Data::customers[Data::customers_num].set_password(ui->password->text());
        Data::customers[Data::customers_num].set_identity("customer");
        Data::customers_num++;
        }
        if(sign == 2)
        {
        Manager te_man;
        te_man.set_phonenum(ui->phonenum->text());
        te_man.set_password(ui->password->text());
        te_man.set_identity("manager");
        te_man.save_to_database_register();
        Data::managers[Data::managers_num].set_phonenum(ui->phonenum->text());
        Data::managers[Data::managers_num].set_password(ui->password->text());
        Data::managers[Data::managers_num].set_identity("manager");
        Data::managers_num++;
        Data::matchs[Data::matchs_num].set_hotelname(ui->manager_hotel->text());
        Data::matchs[Data::matchs_num].set_manager(te_man.get_phonenum());
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("my_database.db");
        db.open();
        QSqlQuery query(db);
        query.exec("insert into matchs (hotelname,manager) values (?,?)");
        query.addBindValue(Data::matchs[Data::matchs_num].get_hotelname());
        query.addBindValue(Data::matchs[Data::matchs_num].get_manager());
        query.exec();
        db.close();
        Data::matchs_num++;
        }
        if(sign == 3)
        {
        Hotel te_hot;
        te_hot.set_phonenum(ui->phonenum->text());
        te_hot.set_password(ui->password->text());
        te_hot.set_identity("hotel");
        te_hot.save_to_database_register();
        Data::hotels[Data::hotels_num].set_phonenum(ui->phonenum->text());
        Data::hotels[Data::hotels_num].set_password(ui->password->text());
        Data::hotels[Data::hotels_num].set_identity("hotel");
        Data::hotel_plat[Data::hotel_plat_num].set_phonenum(ui->phonenum->text());
        hotelapply hol;
        hol.exec();
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("my_database.db");
        db.open();
        QSqlQuery query(db);
        query.prepare("insert into hotel(hotelname,city,area,ho_phonenum,state) values (?,?,?,?,?)");
        query.addBindValue(Data::hotels[Data::hotels_num-1].get_hotelname());
        query.addBindValue(Data::hotels[Data::hotels_num-1].get_city());
        query.addBindValue(Data::hotels[Data::hotels_num-1].get_area());
        query.addBindValue(Data::hotels[Data::hotels_num-1].get_phonenum());
        query.addBindValue("false");
        query.exec();
        db.close();
        }
        QMessageBox confir;
        confir.setWindowTitle(tr("提示"));
        confir.setText("注册成功");
        confir.setStyleSheet("color:rgb(0, 0, 0);font: 10pt");
        confir.setIcon(QMessageBox::Information);
        confir.addButton(tr("确定"),QMessageBox::ActionRole);
        confir.exec();
        accept();
    }
    else if (!judge_valid_phonenum(ui->phonenum->text()))
        {
            QMessageBox::warning(this, tr("警告"), tr("手机号不规范！"), QMessageBox::Yes);
            this->ui->phonenum->clear();
            this->ui->phonenum->setFocus();
        }
   else if (!judge_blank_pwd(ui->password->text()))
        {
            QMessageBox::warning(this, tr("警告"), tr("密码不能为空！"), QMessageBox::Yes);
            this->ui->password->setFocus();
        }
   else
        {
            QMessageBox::warning(this, tr("警告"), tr("两次输入的密码不一致！"), QMessageBox::Yes);
            this->ui->password->clear();
            this->ui->passwordcon->clear();
            this->ui->password->setFocus();
        }
}
//判断是否重复注册
bool Register::login_re_reg(const QString the_phonenum)
{
    int i;
    for(i=0;i<Data::customers_num;i++)
    {
        if(Data::customers[i].phonenum == the_phonenum)
            return true;
    }
    for(i=0;i<Data::managers_num;i++)
    {
        if(Data::managers[i].phonenum == the_phonenum)
            return true;
    }
    for(i=0;i<Data::hotels_num;i++)
    {
        if(Data::hotels[i].phonenum == the_phonenum)
            return true;
    }
    return false;
}
//判断手机号是否合理
bool Register::judge_valid_phonenum(const QString &the_phonenum)
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
//判断密码是否为空
bool Register::judge_blank_pwd(const QString &pwd)
{
    if (pwd.size() == 0)
    {
        return 0;
    }
    else return 1;
}
//重绘

void Register::paintEvent(QPaintEvent *event)
{
    if (ui->phonenum->text().size() < 11 && ui->phonenum->text().size() > 0)
    {
        ui->label_p->show();
        ui->label_p->setText("请输入11位手机号");
        ui->label_phone->hide();
    }
    else if (ui->phonenum->text().size() == 11)
    {
        if (login_re_reg(ui->phonenum->text()))
        {
            ui->label_p->show();
            ui->label_p->setText("该账号已被注册");
            ui->label_phone->hide();
        }
        else if (judge_valid_phonenum(ui->phonenum->text()))
        {
            ui->label_phone->show();
            //形状设置(缺)
            ui->label_p->hide();
        }
    }
    else if (ui->phonenum->text().size() > 11)
    {
        ui->label_phone->hide();
        ui->label_p->show();
        ui->label_p->setText("请输入11位手机号");
    }

    if (ui->password->text().size() < 7 && ui->password->text().size() > 0)
    {
        ui->label_w->show();
        ui->label_w->setText("长度不小于7位");
        ui->label_password->hide();
    }
    else if (ui->password->text().size() >= 7)
    {
        ui->label_password->show();
        //形状设置(缺)
        ui->label_w->hide();
    }

    if (ui->passwordcon->text().size() > 0 && ui->passwordcon->text() != ui->password->text())
    {
        ui->label_rw->show();
        ui->label_rw->setText("两次密码不一致");
        ui->label_passwordcon->hide();
    }
    else if (ui->passwordcon->text() == ui->password->text() && ui->passwordcon->text().size() > 0)
    {
        ui->label_passwordcon->show();
        //形状设置(缺)
        ui->label_rw->hide();
    }

    if(ui->comboBox->currentText() == "管理员")
    {
        ui->label_5->show();
        ui->label_6->show();
        ui->manager_hotel->show();
    }
    if(ui->comboBox->currentText() == "顾客")
    {
        ui->label_5->hide();
        ui->label_6->hide();
        ui->manager_hotel->hide();
    }
    if(ui->comboBox->currentText() == "酒店")
    {
        ui->label_5->hide();
        ui->label_6->hide();
        ui->manager_hotel->hide();
    }

    QDialog::paintEvent(event);

}
