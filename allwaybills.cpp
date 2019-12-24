#include "allwaybills.h"
#include "ui_allwaybills.h"
#include <QSqlRecord>

AllWayBills::AllWayBills(std::shared_ptr<QSqlDatabase> db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllWayBills),
    database(db)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    model = new QSqlQueryModel(this);

    query = std::make_unique<QSqlQuery>(*database);
    query->prepare("select waybills.id_waybill, companies.name, waybills.datetime, waybills.cost from waybills inner join companies using(id_company);");
    query->exec();

    model->setQuery(*query);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setModel(model);

    this->show();

}

AllWayBills::~AllWayBills()
{
    delete ui;
}

void AllWayBills::on_deleteButton_clicked()
{
    QModelIndex ind(ui->tableView->currentIndex()); ind = ind.model()->index(ui->tableView->currentIndex().row(),0);
    QString str = ui->tableView->model()->data(ind).toString();
    query->exec(QString("DELETE FROM waybills WHERE(id_waybill = %1);").arg(str));
    query->exec("select waybills.id_waybill, companies.name, waybills.datetime, waybills.cost from waybills inner join companies using(id_company);");
    model->setQuery(*query);
}

void AllWayBills::on_editButton_clicked()
{
    emit showEditWaybill(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0).data().toString());
    accept();
}
