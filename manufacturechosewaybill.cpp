#include "manufacturechosewaybill.h"
#include "ui_manufacturechosewaybill.h"
#include <QSqlQuery>
#include <QMessageBox>

manufactureChoseWaybill::manufactureChoseWaybill(std::shared_ptr<QSqlDatabase> db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manufactureChoseWaybill),
    database(db)
{
    ui->setupUi(this);
    this->setWindowTitle("Введите накладную");
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    ui->comboBox->addItems(QStringList{"Редактировать", "Контроль"});
    ui->okButton->setEnabled(false);
    this->show();

}

manufactureChoseWaybill::~manufactureChoseWaybill()
{
    delete ui;
}

void manufactureChoseWaybill::on_okButton_clicked()
{
    if(!checkIdWaybill()){
        std::unique_ptr<QMessageBox> msg = std::make_unique<QMessageBox>();
        msg->setWindowTitle("Error");
        msg->setText("Нет накладной с таким ID");
        msg->exec();
    }
    else{
        if(!ui->comboBox->currentIndex())
            emit showWaybillManufacture(ui->lineEdit->text());
        else
            emit showControlManufacture(ui->lineEdit->text());
    }
}

bool manufactureChoseWaybill::checkIdWaybill(){
    QSqlQuery query(*database);
    query.exec("SELECT id_waybill FROM waybills;");
    while(query.next())
        if(query.value(0).toString() == ui->lineEdit->text())
            return true;
    return false;
}

void manufactureChoseWaybill::on_lineEdit_textEdited(const QString &arg1)
{
    if(!arg1.isEmpty())
        ui->okButton->setEnabled(true);
    else
        ui->okButton->setEnabled(false);
}
