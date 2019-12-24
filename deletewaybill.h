#ifndef DELETEWAYBILL_H
#define DELETEWAYBILL_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <memory>

namespace Ui {
class DeleteWaybill;
}

class DeleteWaybill : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteWaybill(std::shared_ptr<QSqlDatabase>, QString, QWidget *parent = nullptr);
    ~DeleteWaybill();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::DeleteWaybill *ui;
    std::shared_ptr<QSqlDatabase> database;
    QString id_waybill;
};

#endif // DELETEWAYBILL_H
