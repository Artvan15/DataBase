#include "choseworker.h"
#include "ui_choseworker.h"
#include <QMessageBox>
#include <memory>

choseWorker::choseWorker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choseWorker)
{
    ui->setupUi(this);
    this->setWindowTitle("Место работы");
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    ui->comboBox->addItems(QStringList{"Офис", "Склад", "Производство"});
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    this->show();
}

choseWorker::~choseWorker()
{
    delete ui;
}


void choseWorker::on_comboBox_currentIndexChanged(int index)
{
    if(!index)
        ui->lineEdit->setReadOnly(false);
    else{
        ui->lineEdit->clear();
        ui->lineEdit->setReadOnly(true);
    }
}

void choseWorker::on_okButton_clicked()
{
    if(ui->comboBox->currentIndex() == 1){
        emit okSklad();
        this->accept();
        return;
    }
    else if(ui->comboBox->currentIndex() == 2){
        emit okManufacture();
        this->accept();
        return;
    }
    else{
        if(ui->lineEdit->text() == password){
            emit okOffice();
            this->accept();
            return;
        }
        else{
            std::unique_ptr<QMessageBox> msg = std::make_unique<QMessageBox>();
            msg->setWindowTitle("Неправильный пароль!");
            msg->setText("Неправильный пароль!\n\tПопробуйте ещё раз");
            msg->exec();
        }
    }
}
