#ifndef WAYBILLSKLAD_H
#define WAYBILLSKLAD_H

#include <QDialog>
#include <memory>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class waybillSklad;
}

class waybillSklad : public QDialog
{
    Q_OBJECT

public:
    explicit waybillSklad(std::shared_ptr<QSqlDatabase>, QString, QWidget *parent = nullptr);
    ~waybillSklad();

private:
    Ui::waybillSklad *ui;
    QSqlQueryModel *model;
    std::shared_ptr<QSqlDatabase> database;
    QString id_waybill;
    std::unique_ptr<QSqlQuery> query;

};

#endif // WAYBILLSKLAD_H
