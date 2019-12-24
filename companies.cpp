#include "companies.h"
#include "ui_companies.h"
#include <QMessageBox>
#include <QSqlError>

companies::companies(std::shared_ptr<QSqlDatabase> db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::companies),
    database(db)
{
    ui->setupUi(this);
    this->setWindowTitle("Компании");
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    model = new QSqlTableModel(this, *database);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("companies");
    model->select();
    ui->tableView->setModel(model);
    this->show();
}

companies::~companies()
{
    delete ui;
}

void companies::on_submmitButton_clicked()
{
    if(!model->submitAll()){
        std::unique_ptr<QMessageBox> msg = std::make_unique<QMessageBox>();
        msg->setWindowTitle("Error");
        msg->setText("Заполнены не все поля или некоректный ввод");
        msg->exec();
    }
}

void companies::on_revertButton_clicked()
{
    model->revertAll();
}

void companies::on_selectButton_clicked()
{
    model->select();
}

void companies::on_addButton_clicked()
{
    model->insertRow(model->rowCount());
}

void companies::on_deleteButton_clicked()
{
    int selectedRow = ui->tableView->currentIndex().row();
    if(selectedRow >= 0)
        model->removeRow(selectedRow);
}
