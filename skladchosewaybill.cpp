#include "skladchosewaybill.h"
#include "ui_skladchosewaybill.h"
#include <QSqlQuery>
#include <QMessageBox>

SkladChoseWaybill::SkladChoseWaybill(std::shared_ptr<QSqlDatabase> db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SkladChoseWaybill),
    database(db)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    ui->okButton->setEnabled(false);
    this->show();

}

SkladChoseWaybill::~SkladChoseWaybill()
{
    delete ui;
}

void SkladChoseWaybill::on_lineEdit_textEdited(const QString &arg1)
{
    if(!arg1.isEmpty())
        ui->okButton->setEnabled(true);
    else
        ui->okButton->setEnabled(false);
}

void SkladChoseWaybill::on_okButton_clicked()
{
    if(checkIdWaybill()){
        emit showWaybillSklad(ui->lineEdit->text());
    }
    else{
        std::unique_ptr<QMessageBox> msg = std::make_unique<QMessageBox>();
        msg->setWindowTitle("Error");
        msg->setText("Нет накладной с таким ID");
        msg->exec();
    }
}
bool SkladChoseWaybill::checkIdWaybill(){
    QSqlQuery query(*database);
    query.exec("SELECT id_waybill FROM waybills;");
    while(query.next())
        if(query.value(0).toString() == ui->lineEdit->text())
            return true;
    return false;
}
