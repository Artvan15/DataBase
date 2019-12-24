#ifndef CHOSEWORKER_H
#define CHOSEWORKER_H

#include <QWidget>
#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class choseWorker;
}

class choseWorker : public QDialog
{
    Q_OBJECT

public:
    explicit choseWorker(QWidget *parent = nullptr);
    ~choseWorker();

private slots:

    void on_comboBox_currentIndexChanged(int index);

    void on_okButton_clicked();

signals:
    void okOffice();

private:
    Ui::choseWorker *ui;
    QSqlDatabase bd;
    QString password = "12345";
};

#endif // CHOSEWORKER_H
