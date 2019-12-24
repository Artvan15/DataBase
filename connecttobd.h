#ifndef CONNECTTOBD_H
#define CONNECTTOBD_H

#include <QWidget>
#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class connectToBD; }
QT_END_NAMESPACE

class connectToBD : public QDialog
{
    Q_OBJECT

public:
    connectToBD(QWidget *parent = nullptr);
    ~connectToBD();

private slots:

    void on_closeButton_clicked();

    void on_okButton_clicked();

    void on_nameEdit_textChanged(const QString &arg1);

    void on_passwordEdit_textChanged(const QString &arg1);

signals:
    void openWorkerDialog(std::shared_ptr<QSqlDatabase>);

private:
    Ui::connectToBD *ui;
    std::shared_ptr<QSqlDatabase> db;
};
#endif // CONNECTTOBD_H
