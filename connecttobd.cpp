#include "connecttobd.h"
#include "ui_connecttobd.h"
#include <QMessageBox>
#include <memory>

connectToBD::connectToBD(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::connectToBD)
{  
    ui->setupUi(this);
    this->setWindowTitle("Подключение к БД");
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    ui->okButton->setEnabled(false);
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    this->show();
}

connectToBD::~connectToBD()
{
    delete ui;
}

void connectToBD::on_closeButton_clicked()
{
    this->reject();
}
void connectToBD::on_nameEdit_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty() && !ui->passwordEdit->text().isEmpty())
        ui->okButton->setEnabled(true);
    else
        ui->okButton->setEnabled(false);
}

void connectToBD::on_passwordEdit_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty() && !ui->nameEdit->text().isEmpty())
        ui->okButton->setEnabled(true);
    else
        ui->okButton->setEnabled(false);
}


void connectToBD::on_okButton_clicked()
{
    db = std::make_shared<QSqlDatabase>();
    *db = QSqlDatabase::addDatabase("QMYSQL");
    db->setHostName("127.0.0.1");
    db->setDatabaseName("department");
    db->setUserName(ui->nameEdit->text());
    db->setPassword(ui->passwordEdit->text());
    if(!db->open()){
        std::unique_ptr<QMessageBox> msg = std::make_unique<QMessageBox>();
        msg->setWindowTitle("Error connection");
        msg->setText(db->lastError().text());
        msg->exec();
        db->close();
    }
    else{
        emit openWorkerDialog(db);
        this->accept();
    }
}

