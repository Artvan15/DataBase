#include "waybillmanufacture.h"
#include "ui_waybillmanufacture.h"
#include <QSqlQuery>

waybillManufacture::waybillManufacture(std::shared_ptr<QSqlDatabase> db, QString id_w, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waybillManufacture),
    database(db), id_waybill(id_w)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    ui->waybillLabel->setText(id_waybill);

    model = new QSqlRelationalTableModel(this, *database);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setTable("manufacture");
    model->setFilter(QString("id_waybill = %1").arg(id_waybill));



    model->setRelation(model->fieldIndex("id_product"),
                       QSqlRelation("product", "id_product", "name"));
    model->setRelation(model->fieldIndex("id_style"),
                       QSqlRelation("style", "id_style", "code"));

    model->select();
    ui->tableView->setModel(model);
    for(size_t n = 1; n != 3; ++n)
        ui->tableView->setItemDelegateForColumn(n, new NotEditableDelegate(ui->tableView));
    ui->tableView->hideColumn(0);
    this->show();

}

waybillManufacture::~waybillManufacture()
{
    delete ui;
}

void waybillManufacture::on_submmitButton_clicked()
{
    int selectedRow = ui->tableView->currentIndex().row();
    std::unique_ptr<QSqlTableModel> product = std::make_unique<QSqlTableModel>(nullptr, *database);
    std::unique_ptr<QSqlTableModel> style = std::make_unique<QSqlTableModel>(nullptr, *database);

    product->setTable("product");
    product->setFilter(QString("name = '%1'").arg(ui->tableView->model()->index(selectedRow, 1).data().toString()));
    product->select();
    QString newIdProduct = product->index(0,0).data().toString();

    style->setTable("style");
    style->setFilter(QString("code = '%1'").arg(ui->tableView->model()->index(selectedRow, 2).data().toString()));
    style->select();
    QString newIdStyle = style->index(0,0).data().toString();

    QSqlQuery query(*database);
    query.exec(QString("UPDATE manufacture SET quantity = %1 WHERE (id_waybill = %2) and (id_product = %3) and (id_style = %4);").arg(ui->tableView->model()->index(selectedRow, 3).data().toString()).arg(id_waybill).arg(newIdProduct).arg(newIdStyle));
    model->select();
}

void waybillManufacture::on_revertButton_clicked()
{
    model->revertAll();
}
