//
// TransportSystemDlg.h
//
// Copyright (C) 2017
//

#ifndef TRANSPORTSYSTEMGUI_TRANSPORTSYSTEMDLG_H
#define TRANSPORTSYSTEMGUI_TRANSPORTSYSTEMDLG_H

#include <QDialog>
#include <QMessageBox>

#include "Vehicle.h"
#include "VehicleTab.h"
#include "Route.h"
#include "RouteTab.h"

#include "ui_TransportSystemDlg.h"

namespace TransportSystemDlg {

class TransportSystemDlg : public QDialog, private Ui::TransportSystemDlgUI
{
    Q_OBJECT

public:
    explicit TransportSystemDlg(QWidget *parent = 0);
    ~TransportSystemDlg();


private slots:
    void printDebugLog();
    void saveFiles();

private:
    void buildUI();

    void connections();

    void initVehicles();
    void initRoutes();

    void saveFileVehicles();
    void saveFileRoutes();


private:
    QList<Vehicle> mVehicles;
    QList<Route> mRoutes;

    VehicleTab *mVehicleTab;
    RouteTab *mRouteTab;

};

}   // namespace TransportSystemDlg

#endif //TRANSPORTSYSTEMGUI_TRANSPORTSYSTEMDLG_H
