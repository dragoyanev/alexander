//
// Vehicle.h
//
// Copyright (C) 2017
//

#ifndef TRANSPORTSYSTEMGUI_VEHICLETAB_H
#define TRANSPORTSYSTEMGUI_VEHICLETAB_H

#include <QStandardItemModel>

#include "ui_VehicleTab.h"
#include "Vehicle.h"


namespace TransportSystemDlg {

class VehicleTab : public QWidget, private Ui::VehicleTab
{
    Q_OBJECT

public:
    explicit VehicleTab(QWidget *parent = 0);

    const QList<Vehicle> &vehicleData() const;
    void setVehicleData(const QList<Vehicle> &vehicleData);

signals:
    void vehicleRowDeleted(unsigned currRow);
    void vehicleRowAdded(const QList<Vehicle> &vehicleData);

private slots:
    void onNewButtonClicked();
    void onDeleteButtonClicked();

private:
    void updateTable();

private:
    QList<Vehicle> mVehicleData;
};

}   // namespace TransportSystemDlg

#endif // TRANSPORTSYSTEMGUI_VEHICLETAB_H
