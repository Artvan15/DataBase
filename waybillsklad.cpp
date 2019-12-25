#include "waybillsklad.h"
#include "ui_waybillsklad.h"

waybillSklad::waybillSklad(std::shared_ptr<QSqlDatabase> db, QString id_w, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waybillSklad),
    database(db), id_waybill(id_w)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    model = new QSqlQueryModel(this);

    query = std::make_unique<QSqlQuery>(*database);
    query->exec(QString("create or replace view sklad as\
                        select material.name, composition.quantity from composition inner join waybill_content on waybill_content.id_product = composition.id_product and waybill_content.id_style = composition.id_style inner join material using(id_material)  where waybill_content.id_waybill = %1;").arg(id_waybill));
    query->exec("select sklad.name, sum(sklad.quantity) from sklad group by name;");

    model->setQuery(*query);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    model->setHeaderData(0, Qt::Horizontal, tr("Материал"));
    model->setHeaderData(1, Qt::Horizontal, tr("Общее количество"));

    ui->tableView->setModel(model);
    ui->label_2->setText(id_waybill);
    this->show();

}

waybillSklad::~waybillSklad()
{
    delete ui;
}
