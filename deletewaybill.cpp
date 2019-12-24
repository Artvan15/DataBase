#include "deletewaybill.h"
#include "ui_deletewaybill.h"

DeleteWaybill::DeleteWaybill(std::shared_ptr<QSqlDatabase> db, QString id_w, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteWaybill),
    database(db), id_waybill(id_w)
{
    ui->setupUi(this);
    ui->labelWaybill->setText(id_w);
    this->show();
}

DeleteWaybill::~DeleteWaybill()
{
    delete ui;
}

void DeleteWaybill::on_pushButton_2_clicked()
{
    this->reject();
}

void DeleteWaybill::on_pushButton_clicked()
{
    QSqlQuery query(*database);
    query.exec(QString("DELETE FROM waybills WHERE (id_waybill = '%1');").arg(id_waybill));
    this->accept();
}
