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
#include "Schedule.h"
#include "ScheduleTab.h"

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
    void initSchedules();

    void saveFileVehicles();
    void saveFileRoutes();
    void saveFileSchedules();

private:
    QList<Vehicle> mVehicles;
    QList<Route> mRoutes;
    QList<Schedule> mSchedules;

    VehicleTab *mVehicleTab;
    RouteTab *mRouteTab;
    ScheduleTab *mScheduleTab;
};

}   // namespace TransportSystemDlg

#endif //TRANSPORTSYSTEMGUI_TRANSPORTSYSTEMDLG_H
