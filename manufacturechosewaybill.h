#ifndef MANUFACTURECHOSEWAYBILL_H
#define MANUFACTURECHOSEWAYBILL_H

#include <QDialog>
#include <memory>
#include <QSqlDatabase>

namespace Ui {
class manufactureChoseWaybill;
}

class manufactureChoseWaybill : public QDialog
{
    Q_OBJECT

public:
    explicit manufactureChoseWaybill(std::shared_ptr<QSqlDatabase>, QWidget *parent = nullptr);
    ~manufactureChoseWaybill();

private slots:
    void on_okButton_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

signals:
    void showWaybillManufacture(QString);
    void showControlManufacture(QString);

private:
    Ui::manufactureChoseWaybill *ui;
    std::shared_ptr<QSqlDatabase> database;

    bool checkIdWaybill();
};

#endif // MANUFACTURECHOSEWAYBILL_H
