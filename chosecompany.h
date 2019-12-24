#ifndef CHOSECOMPANY_H
#define CHOSECOMPANY_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <memory>

namespace Ui {
class choseCompany;
}

class choseCompany : public QDialog
{
    Q_OBJECT

public:
    explicit choseCompany(std::shared_ptr<QSqlDatabase>, QString, QWidget *parent = nullptr);
    ~choseCompany();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

signals:
    void showCompanies();
    void showEditWaybill(QString);

private:
    Ui::choseCompany *ui;
    std::shared_ptr<QSqlDatabase> database;
    QString id_waybill;

    bool checkCompanyId();
    void createWaybill();
};

#endif // CHOSECOMPANY_H
