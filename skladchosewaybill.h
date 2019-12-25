#ifndef SKLADCHOSEWAYBILL_H
#define SKLADCHOSEWAYBILL_H

#include <QDialog>
#include <memory>
#include <QSqlDatabase>

namespace Ui {
class SkladChoseWaybill;
}

class SkladChoseWaybill : public QDialog
{
    Q_OBJECT

public:
    explicit SkladChoseWaybill(std::shared_ptr<QSqlDatabase>, QWidget *parent = nullptr);
    ~SkladChoseWaybill();

private slots:
    void on_lineEdit_textEdited(const QString &arg1);

    void on_okButton_clicked();

signals:
    void showWaybillSklad(QString);

private:
    Ui::SkladChoseWaybill *ui;
    std::shared_ptr<QSqlDatabase> database;

    bool checkIdWaybill();
};

#endif // SKLADCHOSEWAYBILL_H
