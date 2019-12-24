#ifndef OFFICEDIALOG_H
#define OFFICEDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <memory>

namespace Ui {
class office;
}

class office : public QDialog
{
    Q_OBJECT

public:
    explicit office(std::shared_ptr<QSqlDatabase>, QWidget *parent = nullptr);
    ~office();

private slots:
    void on_addCompanyButton_clicked();

    void on_showWaybillsButton_clicked();

    void on_okButton_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

signals:
    void showCompanies();
    void showWaybills();
    void showChoseCompany(QString);
    void showEditWaybill(QString);
    void showDeleteWaybill(QString);

private:
    Ui::office *ui;
    std::shared_ptr<QSqlDatabase> database;

    bool checkIdWaybill();
};

#endif // OFFICEDIALOG_H
