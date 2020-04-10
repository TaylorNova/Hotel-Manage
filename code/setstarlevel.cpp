#include "setstarlevel.h"
#include "ui_setstarlevel.h"
#include "data.h"
#include "all_headers_nedded.h"

setstarlevel::setstarlevel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setstarlevel)
{
    ui->setupUi(this);
//界面美化
    this->setWindowIcon(QIcon(":Image/hotel.png"));
    QPixmap pixmap = QPixmap(":/Image/cloudss.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
    ui->view->setStyleSheet("background-color: rgba(255,255,255,0)");
    ui->view->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgba(255,255,255,0);}");
    ui->view->verticalHeader()->setVisible(false);
    ui->comboBox->setStyleSheet("QComboBox {border: 1px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;min-width: 9em;}"
                                "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 20px;\
                                border-left-width: 1px;border-left-color: darkgray;border-left-style: solid;border-top-right-radius: 3px;\
                                border-bottom-right-radius: 3px;}"
                                "QComboBox::down-arrow { image: url(:/Image/xiala.png);}");
//初始化表格
    int i;
    int j = 0;
    int temp = 0;
    for(i=0;i<Data::rooms_num;i++)
    {
        if(Data::rooms[i].get_hotelname() == Data::hotel_plat[Data::row_check_3].get_hotelname())
        {
            temp++;
        }
    }
    ui->view->setRowCount(temp);
    for(i=0;i<Data::rooms_num;i++)
    {
        if(Data::rooms[i].get_hotelname() == Data::hotel_plat[Data::row_check_3].get_hotelname())
        {
            QTableWidgetItem * it1 = new QTableWidgetItem();
            QString rotype;
            if(Data::rooms[i].get_type() == "singleroom")
                rotype = "单人间";
            if(Data::rooms[i].get_type() == "doubleroom")
                rotype = "标准间";
            if(Data::rooms[i].get_type() == "luxsingleroom")
                rotype = "豪华单人间";
            if(Data::rooms[i].get_type() == "luxdoubleroom")
                rotype = "豪华标准间";
            if(Data::rooms[i].get_type() == "familyroom")
                rotype = "家庭套房";
            if(Data::rooms[i].get_type() == "presidentroom")
                rotype = "总统套房";
            it1->setText(rotype);
            ui->view->setItem(j,0,it1);

            QTableWidgetItem * it2 = new QTableWidgetItem();
            it2->setText(QString::number(Data::rooms[i].get_price()));
            ui->view->setItem(j,1,it2);

            QTableWidgetItem * it3 = new QTableWidgetItem();
            it3->setText(Data::rooms[i].get_discount());
            ui->view->setItem(j,2,it3);

            QLabel *lab = new QLabel("");
            lab->setPixmap(QPixmap(Data::rooms[i].get_picture()).scaled(100,60));
            ui->view->setCellWidget(j,3,lab);

            j++;
        }
    }
}

setstarlevel::~setstarlevel()
{
    delete ui;
}

void setstarlevel::on_cancel_clicked()
{
    this->close();
}

void setstarlevel::on_confirm_clicked()
{
    Data::hotel_plat[Data::row_check_3].set_star(ui->comboBox->currentText());
    QMessageBox tip;
    tip.setWindowTitle(tr("提示"));
    tip.setText("评定成功");
    tip.setStyleSheet("color:rgb(0, 0, 0);font: 10pt");
    tip.setIcon(QMessageBox::Information);
    tip.addButton(tr("确定"),QMessageBox::ActionRole);
    tip.exec();
    this->close();
}
