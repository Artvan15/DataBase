#ifndef WAYBILL_H
#define WAYBILL_H

#include <QDialog>
#include <memory>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlQuery>

namespace Ui {
class waybill;
}

class waybill : public QDialog
{
    Q_OBJECT

public:
    explicit waybill(std::shared_ptr<QSqlDatabase>, QString, QWidget *parent = nullptr);
    ~waybill();

private slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_commitButton_3_clicked();

    void on_revertButton_clicked();

    void on_selectButton_clicked();

private:
    Ui::waybill *ui;
    std::shared_ptr<QSqlDatabase> database;
    std::unique_ptr<QSqlQuery> query;
    QSqlRelationalTableModel *model;
    QString id_waybill;
    bool addRow = false;

};

#endif // WAYBLILL_H
