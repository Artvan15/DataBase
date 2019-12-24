#ifndef ALLWAYBILLS_H
#define ALLWAYBILLS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <memory>

namespace Ui {
class AllWayBills;
}

class AllWayBills : public QDialog
{
    Q_OBJECT

public:
    explicit AllWayBills(std::shared_ptr<QSqlDatabase>, QWidget *parent = nullptr);
    ~AllWayBills();

private slots:
    void on_deleteButton_clicked();

    void on_editButton_clicked();

signals:
    void showEditWaybill(QString);

private:
    Ui::AllWayBills *ui;
    std::shared_ptr<QSqlDatabase> database;
    QSqlQueryModel *model;
    std::unique_ptr<QSqlQuery> query;
};

#endif // ALLWAYBILLS_H
