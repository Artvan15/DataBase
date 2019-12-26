#ifndef MANUFACTURECONTROL_H
#define MANUFACTURECONTROL_H

#include <QDialog>
#include <memory>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>

namespace Ui {
class ManufactureControl;
}

class ManufactureControl : public QDialog
{
    Q_OBJECT

public:
    explicit ManufactureControl(std::shared_ptr<QSqlDatabase> database, QString id_w,QWidget *parent = nullptr);
    ~ManufactureControl();

private:
    Ui::ManufactureControl *ui;
    std::shared_ptr<QSqlDatabase> database;
    QString id_waybill;
    QSqlQueryModel *model;
    std::unique_ptr<QSqlQuery> query;
};

#endif // MANUFACTURECONTROL_H
