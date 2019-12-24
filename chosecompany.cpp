#include "chosecompany.h"
#include "ui_chosecompany.h"
#include <QMessageBox>
#include <QDateTime>

choseCompany::choseCompany(std::shared_ptr<QSqlDatabase> db, QString id_w, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choseCompany),
    database(db), id_waybill(id_w)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    this->show();
}

choseCompany::~choseCompany()
{
    delete ui;
}

void choseCompany::on_pushButton_2_clicked()
{
    emit showCompanies();
}

void choseCompany::on_pushButton_clicked()
{
    if(checkCompanyId())
        createWaybill();
    else{
        std::unique_ptr<QMessageBox> msg = std::make_unique<QMessageBox>();
        msg->setWindowTitle("Error");
        msg->setText("Нет компании с таким ID");
        msg->exec();
    }
}
bool choseCompany::checkCompanyId(){
    QSqlQuery query(*database);
    query.exec("SELECT id_company FROM companies");
    while(query.next())
        if(query.value(0).toString() == ui->lineEdit->text())
            return true;
    return false;
}

void choseCompany::createWaybill(){
    QSqlQuery query(*database);
    QDateTime dt = QDateTime::currentDateTime();
    QString datetime = dt.toString("yyyy-MM-dd hh:mm:ss");
    query.exec(QString("INSERT INTO waybills (id_waybill, id_company, datetime, cost) VALUES ('%1', '%2', '%3', '0');").arg(id_waybill).arg(ui->lineEdit->text()).arg(datetime));
    emit showEditWaybill(id_waybill);
    accept();
}
