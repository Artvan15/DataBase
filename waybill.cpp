#include "waybill.h"
#include "ui_waybill.h"

waybill::waybill(std::shared_ptr<QSqlDatabase> db, QString id_w,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waybill), database(db), id_waybill(id_w)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(), this->geometry().height());
    ui->waybillLabel->setText(id_waybill);

    model = new QSqlRelationalTableModel(this, *database);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    query = std::make_unique<QSqlQuery>(*database);

    model->setTable("waybill_content");
    model->setFilter(QString("id_waybill = %1").arg(id_waybill));
    model->removeColumns(0, 1);
    model->setRelation(model->fieldIndex("id_product"),
                       QSqlRelation("product", "id_product", "name"));
    model->setRelation(model->fieldIndex("id_style"),
                       QSqlRelation("style", "id_style", "code"));

    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    model->select();

    ui->tableView->setModel(model);
    this->show();


    query->exec(QString("CREATE OR REPLACE VIEW temp AS\
                        SELECT product.name, style.code, quantity FROM waybill_content INNER JOIN product USING(id_product) INNER JOIN style USING(id_style) WHERE(id_waybill = %1);").arg(id_waybill));
}

waybill::~waybill()
{
    delete ui;
}

void waybill::on_addButton_clicked()
{
    model->insertRow(model->rowCount());
    addRow = true;
}

void waybill::on_deleteButton_clicked()
{
        query->exec("CREATE OR REPLACE VIEW reverstemp AS\
                    SELECT id_product, id_style, quantity FROM temp INNER JOIN product USING(name) INNER JOIN style USING(code);");
        int selectedRow = ui->tableView->currentIndex().row();
        std::unique_ptr<QSqlTableModel> reverse = std::make_unique<QSqlTableModel>(nullptr, *database);
        reverse->setTable("reverstemp");
        reverse->select();
        QString id_product = reverse->index(selectedRow, 0).data().toString();
        QString id_style = reverse->index(selectedRow, 1).data().toString();
        query->exec(QString("DELETE FROM waybill_content WHERE (id_waybill = %1) and (id_product = %2) and (id_style = %3);").arg(id_waybill).arg(id_product).arg(id_style));
        model->select();

}

void waybill::on_commitButton_3_clicked()
{
    int selectedRow = ui->tableView->currentIndex().row();
    std::unique_ptr<QSqlTableModel> product = std::make_unique<QSqlTableModel>(nullptr, *database);
    std::unique_ptr<QSqlTableModel> style = std::make_unique<QSqlTableModel>(nullptr, *database);

    product->setTable("product");
    product->setFilter(QString("name = '%1'").arg(ui->tableView->model()->index(selectedRow, 0).data().toString()));
    product->select();
    QString newIdProduct = product->index(0,0).data().toString();

    style->setTable("style");
    style->setFilter(QString("code = '%1'").arg(ui->tableView->model()->index(selectedRow, 1).data().toString()));
    style->select();
    QString newIdStyle = style->index(0,0).data().toString();

    if(!addRow){
        query->exec("CREATE OR REPLACE VIEW reverstemp AS\
                    SELECT id_product, id_style, quantity FROM temp INNER JOIN product USING(name) INNER JOIN style USING(code);");

        std::unique_ptr<QSqlTableModel> reverse = std::make_unique<QSqlTableModel>(nullptr, *database);


        reverse->setTable("reverstemp");
        reverse->select();
        QString id_product = reverse->index(selectedRow, 0).data().toString();
        QString id_style = reverse->index(selectedRow, 1).data().toString();

        query->exec(QString("UPDATE waybill_content SET id_product = %1, id_style = %2, quantity = %3 WHERE (id_waybill = %4) and (id_product = %5) and (id_style = %6);").arg(newIdProduct).arg(newIdStyle).arg(ui->tableView->model()->index(selectedRow, 2).data().toString()).arg(id_waybill).arg(id_product).arg(id_style));
        model->select();
    }
    else{
        query->exec(QString("INSERT INTO waybill_content (id_waybill, id_product, id_style, quantity)VALUES('%1', '%2', '%3', '%4');").arg(id_waybill).arg(newIdProduct).arg(newIdStyle).arg(ui->tableView->model()->index(selectedRow, 2).data().toString()));
        model->select();
        addRow = false;
    }

}

void waybill::on_revertButton_clicked()
{
    model->revertAll();
}

void waybill::on_selectButton_clicked()
{
    model->select();
}
