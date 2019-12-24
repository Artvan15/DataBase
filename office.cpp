#include "office.h"
#include "ui_office.h"
#include <QSqlQuery>
#include <QMessageBox>

office::office(std::shared_ptr<QSqlDatabase> db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::office),
    database(db)
{
    ui->setupUi(this);
    this->setWindowTitle("Офис");
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    ui->comboBox->addItems(QStringList{"Создать", "Редактировать", "Удалить"});
    ui->okButton->setEnabled(false);
    this->show();
}

office::~office()
{
    delete ui;
}

void office::on_addCompanyButton_clicked()
{
    emit showCompanies();
}

void office::on_showWaybillsButton_clicked()
{
    emit showWaybills();
}

void office::on_okButton_clicked()
{
    auto errorMsg = [&](QString str){
        std::unique_ptr<QMessageBox> msg = std::make_unique<QMessageBox>();
        msg->setWindowTitle("Error");
        msg->setText(str);
        msg->exec();
    };

    if(!ui->comboBox->currentIndex()){
        if(!checkIdWaybill())
            emit showChoseCompany(ui->lineEdit->text());
        else
            errorMsg("Уже есть накладная с таким ID");
    }
    else if(ui->comboBox->currentIndex() == 1){
        if(checkIdWaybill())
            emit showEditWaybill(ui->lineEdit->text());
        else
            errorMsg("Нет накладной с таким ID");
    }
    else if(ui->comboBox->currentIndex() == 2){
        if(checkIdWaybill())
            emit showDeleteWaybill(ui->lineEdit->text());
        else
            errorMsg("Нет накладной с таким ID");
    }

}
bool office::checkIdWaybill(){
    QSqlQuery query(*database);
    query.exec("SELECT id_waybill FROM waybills;");
    while(query.next())
        if(query.value(0).toString() == ui->lineEdit->text())
            return true;
    return false;
}



void office::on_lineEdit_textEdited(const QString &arg1)
{
    if(!arg1.isEmpty())
        ui->okButton->setEnabled(true);
    else
        ui->okButton->setEnabled(false);
}
