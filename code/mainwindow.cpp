 #include "mainwindow.h"
#include "ui_mainwindow.h"
#include "register.h"
#include "data.h"
#include "people.h"
#include "customer.h"
#include "customer_run.h"
#include "manager_run.h"
#include "hotel_run.h"
#include "platform.h"
#include "all_headers_nedded.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//界面美化
    this->setWindowIcon(QIcon(":Image/hotel.png"));
    ui->comboBox->setStyleSheet("QComboBox {border: 1px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;min-width: 9em;}"
                                "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 20px;\
                                border-left-width: 1px;border-left-color: darkgray;border-left-style: solid;border-top-right-radius: 3px;\
                                border-bottom-right-radius: 3px;}"
                                "QComboBox::down-arrow { image: url(:/Image/xiala.png);}");

    QPixmap pixmap = QPixmap(":/Image/hotel.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );

    QRegExp regx("^[A-Za-z0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->lineEdit_psw);
    ui->lineEdit_psw->setValidator(validator);

    QRegExp regx1("[1-9][0-9]+$");
    QValidator *validator1 = new QRegExpValidator(regx1, ui->lineEdit_phnum);
    ui->lineEdit_phnum->setValidator(validator1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_registering_clicked()
{
    close();
    Register reg1;
    if(reg1.exec() == QDialog::Accepted)
    show();
}
//获取用户类型
QString MainWindow::kind_of_user()
{
    if(ui->comboBox->currentText() == "顾客")
        return "customer";
    else if(ui->comboBox->currentText() == "管理员")
        return "manager";
    else if(ui->comboBox->currentText() == "酒店")
        return "hotel";
    else if(ui->comboBox->currentText() == "平台")
        return "platform";
    else return 0;
}
//判断账户是否存在
bool MainWindow::judge_exist(People &the_person)
{
    int i = 0;
    if(the_person.get_identity() == "customer")
    {
        for(i=0;i<Data::customers_num;i++)
        {
            if(the_person.get_phonenum() == Data::customers[i].get_phonenum() && the_person.get_password() == Data::customers[i].get_password())
            {
            Data::current_user = the_person.get_phonenum();
            return true;
            }
        }
        return false;
    }
    if(the_person.get_identity() == "manager")
    {
        for(i=0;i<Data::managers_num;i++)
        {
            if(the_person.get_phonenum() == Data::managers[i].get_phonenum() && the_person.get_password() == Data::managers[i].get_password())
            {
                for(int j = 0;j < Data::matchs_num;j++)
                {
                    if(Data::matchs[i].get_manager() == the_person.get_phonenum())
                    {
                        Data::manager_hotel = Data::matchs[i].get_hotelname();
                        break;
                    }
                }
                Data::current_user = the_person.get_phonenum();
                return true;
            }
        }
        return false;
    }
    if(the_person.get_identity() == "hotel")
    {
        for(i=0;i<Data::hotels_num;i++)
        {
            int j;
            for(j = 0;j<Data::hotel_plat_num ;j++)
            {
                if(Data::hotel_plat[j].get_phonenum() == the_person.get_phonenum())
                break;
            }
            if(the_person.get_phonenum() == Data::hotels[i].get_phonenum() && the_person.get_password() == Data::hotels[i].get_password() && Data::hotel_plat[j].get_state() == "true")
            {
                Data::current_user = Data::hotel_plat[j].get_hotelname();
                return true;
            }
        }
        return false;
    }
    if(the_person.get_identity() == "platform")
    {
            if(the_person.get_phonenum() == Data::platform[0].get_phonenum() && the_person.get_password() == Data::platform[0].get_password())
            {
                return true;
            }
        return false;
    }
    else return false;
}

void MainWindow::on_login_clicked()
{
   now_user.set_identity(kind_of_user());
   now_user.set_phonenum(ui->lineEdit_phnum->text());
   now_user.set_password(ui->lineEdit_psw->text());
   if(judge_exist(now_user))
    {
        if(kind_of_user() == "customer")
        {
            close();
            customer_run cur1;
            if(cur1.exec() == QDialog::Accepted)
            show();
        }
        if(kind_of_user() == "manager")
        {
            close();
            manager_run mar1;
            if(mar1.exec() == QDialog::Accepted)
            show();
        }
        if(kind_of_user() == "hotel")
        {
            close();
            hotel_run hor1;
            if(hor1.exec() == QDialog::Accepted)
            show();
        }
        if(kind_of_user() == "platform")
        {
            close();
            platform plf1;
            if(plf1.exec() == QDialog::Accepted)
            show();
        }
    }
    else
   {
        QMessageBox err_warn;
        err_warn.setWindowTitle(tr("提示"));
        err_warn.setText("登录失败\n可能原因：用户名或密码错误，酒店未注册");
        err_warn.setStyleSheet("color:rgb(0, 0, 0);font: 10pt");
        err_warn.setIcon(QMessageBox::Information);
        err_warn.addButton(tr("确定"),QMessageBox::ActionRole);
        err_warn.exec();
    }
}

void MainWindow::on_cancel_clicked()
{
    this->close();
}
