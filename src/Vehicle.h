//
// Vehicle.h
//
// Copyright (C) 2017
//

#ifndef TRANSPORTSYSTEMGUI_VEHICLE_H
#define TRANSPORTSYSTEMGUI_VEHICLE_H

#include <QString>
#include <QDebug>

namespace TransportSystemDlg {

class Vehicle
{
public:
    static const unsigned MIN_VEHICLE_YEAR;
    static const unsigned MAX_VEHICLE_PASSENGERS;
    static const unsigned MAX_VEHICLE_LOAD_CAPACITY;
    static const double MIN_VEHICLE_FUEL_CONSUMPTION;
    static const double MAX_VEHICLE_FUEL_CONSUMPTION;

    static const QString VEHICLE_REGULAR_EXPRESSION_VALID;
    static const QString VEHICLE_REGULAR_EXPRESSION_INVALID;

public:
    Vehicle();
    Vehicle(QString brand, QString model,
            unsigned year, unsigned passengers,
            unsigned load, double fuel);
    ~Vehicle();

    QString brand() const;
    void setBrand(QString brand);

    QString model() const;
    void setModel(QString model);

    unsigned year() const;
    void setYear(unsigned year);

    unsigned passengers() const;
    void setPassengers(unsigned passengers);

    unsigned loadCapacity() const;
    void setLoadCapacity(unsigned loadCapacity);

    double fuelConsumption() const;
    void setFuelConsumption(double fuelConsumption);

private:
    bool brandValid(QString brand);
    bool modelValid(QString model);
    bool yearValid(unsigned year);
    bool passengersValid(unsigned passengers);
    bool loadCapacityValid(unsigned loadCapacity);
    bool fuelConsumptionValid(double fuelConsumption);

private:
    QString mBrand;
    QString mModel;
    unsigned mYear;
    unsigned mPassengers;
    unsigned mLoadCapacity;     // [kg]
    double mFuelConsumption;    // [liters/100 km]
};

QDebug operator<<(QDebug debug, const Vehicle &vehicle);

}   // namespace TransportSystemDlg

#endif //TRANSPORTSYSTEMGUI_VEHICLE_H

