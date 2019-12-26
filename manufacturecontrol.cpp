#include "manufacturecontrol.h"
#include "ui_manufacturecontrol.h"

ManufactureControl::ManufactureControl(std::shared_ptr<QSqlDatabase> db, QString id_w, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManufactureControl),
    database(db), id_waybill(id_w)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    ui->waybillLabel->setText(id_waybill);

    model = new QSqlQueryModel(this);

    query = std::make_unique<QSqlQuery>(*database);
    query->exec(QString("create or replace view temp as select product.name, style.code, quantity from waybill_content inner join product using(id_product) inner join style using(id_style) where (id_waybill = %1);").arg(id_waybill));
    query->exec("drop table if exists manufacturecontrol");
    query->exec("create temporary table manufacturecontrol select * from temp;");

    query->exec("call manufacturecon()");
    query->exec("select * from manufacturecontrol;");
    model->setQuery(*query);
    ui->tableView->setModel(model);
    this->show();

}

ManufactureControl::~ManufactureControl()
{
    delete ui;
}
