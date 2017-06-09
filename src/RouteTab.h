//
// Route.h
//
// Copyright (C) 2017
//

#ifndef TRANSPORTSYSTEMGUI_ROUTETAB_H
#define TRANSPORTSYSTEMGUI_ROUTETAB_H

#include <QStandardItemModel>

#include "ui_RouteTab.h"
#include "Route.h"


namespace TransportSystemDlg {

class RouteTab : public QWidget, private Ui::RouteTab
{
    Q_OBJECT

public:
    explicit RouteTab(QWidget *parent = 0);

    const QList<Route> &routeData() const;
    void setRouteData(const QList<Route> &routeData);

private slots:
    void onNewButtonClicked();
    void onDeleteButtonClicked();

private:
    void updateTable();

private:
    QList<Route> mRouteData;
};

}   // namespace TransportSystemDlg

#endif // TRANSPORTSYSTEMGUI_ROUTETAB_H
