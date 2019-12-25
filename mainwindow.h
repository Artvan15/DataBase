#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "connecttobd.h"
#include "choseworker.h"
#include "office.h"
#include "companies.h"
#include "allwaybills.h"
#include "chosecompany.h"
#include "deletewaybill.h"
#include "waybill.h"
#include "skladchosewaybill.h"
#include "waybillsklad.h"
#include <memory>

class MainWindow : public QObject
{
    Q_OBJECT

    std::shared_ptr<QSqlDatabase> database;
    std::unique_ptr<connectToBD> bd;
    std::unique_ptr<choseWorker> workerDialog;
    std::unique_ptr<office> officeDialog;
    std::unique_ptr<companies> companiesDialog;
    std::unique_ptr<AllWayBills> waybillsDialog;
    std::unique_ptr<choseCompany> choseCompanyDialog;
    std::unique_ptr<DeleteWaybill> deleteWaybillDialog;
    std::unique_ptr<waybill> editWaybillDialog;
    std::unique_ptr<SkladChoseWaybill> skladChoseWaybillDialog;
    std::unique_ptr<waybillSklad> waybillSkladDialog;
public:
    explicit MainWindow(QObject *parent = 0);

private slots:
    void showWorkerDialog(std::shared_ptr<QSqlDatabase>);
    void showOfficeDialog();
    void showCompaniesDialog();
    void showAllWaybillsDialog();
    void showChoseCompanyDialog(QString);
    void showDeleteWaybillDialog(QString);
    void showEditWaybillDialog(QString);
    void showSkladChoseWaybillDialog();
    void showWaybillSkladDialog(QString);
};

#endif // MAINWINODW_H

