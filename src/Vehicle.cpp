//
// Vehicle.cpp
//
// Copyright (C) 2017
//

#include <QRegularExpression>
#include <QDate>

#include "Vehicle.h"

namespace TransportSystemDlg {

const unsigned Vehicle::MIN_VEHICLE_YEAR = 1980;
const unsigned Vehicle::MAX_VEHICLE_PASSENGERS = 200;
const unsigned Vehicle::MAX_VEHICLE_LOAD_CAPACITY = 10000;
const double Vehicle::MIN_VEHICLE_FUEL_CONSUMPTION = 0.1;
const double Vehicle::MAX_VEHICLE_FUEL_CONSUMPTION = 200.0;

const QString Vehicle::VEHICLE_REGULAR_EXPRESSION_VALID = "([a-zA-Z0-9 ]*)";
const QString Vehicle::VEHICLE_REGULAR_EXPRESSION_INVALID = "([^a-zA-Z0-9 ]+)";


Vehicle::Vehicle()
{
    mBrand = "";
    mModel = "";
    mYear = 1900;
    mPassengers = 1;
    mLoadCapacity = 0;
    mFuelConsumption = 1.0;
}

Vehicle::Vehicle(QString brand, QString model,
                 unsigned year, unsigned passengers,
                 unsigned load, double fuel)
{
    setBrand(brand);
    setModel(model);
    setYear(year);
    setPassengers(passengers);
    setLoadCapacity(load);
    setFuelConsumption(fuel);
}

Vehicle::~Vehicle()
{
}

QString Vehicle::brand() const
{
    return mBrand;
}

void Vehicle::setBrand(QString brand)
{
    if (brandValid(brand))
        mBrand = brand;
    else {
        mBrand = QString();
        qDebug("Invalid brand=%s",qPrintable(brand));
    }
}

QString Vehicle::model() const
{
    return mModel;
}

void Vehicle::setModel(QString model)
{
    if (modelValid(model))
        mModel = model;
    else {
        mModel = QString();
        qDebug("Invalid model=%s",qPrintable(model));
    }
}

unsigned Vehicle::year() const
{
    return mYear;
}

void Vehicle::setYear(unsigned year)
{
    if (yearValid(year))
        mYear = year;
    else {
        mYear = 1900;
        qDebug("Invalid year=%s",qPrintable(QString("%1").arg(year)));
    }
}

unsigned Vehicle::passengers() const
{
    return mPassengers;
}

void Vehicle::setPassengers(unsigned passengers)
{
    if (passengersValid(passengers))
        mPassengers = passengers;
    else {
        mPassengers = 1;
        qDebug("Invalid passengers=%s",qPrintable(QString("%1").arg(passengers)));
    }
}

unsigned Vehicle::loadCapacity() const
{
    return mLoadCapacity;
}

void Vehicle::setLoadCapacity(unsigned loadCapacity)
{
    if (loadCapacityValid(loadCapacity))
        mLoadCapacity = loadCapacity;
    else {
        mLoadCapacity = 0;
        qDebug("Invalid loadCapacity=%s",qPrintable(QString("%1").arg(loadCapacity)));
    }
}

double Vehicle::fuelConsumption() const
{
    return mFuelConsumption;
}

void Vehicle::setFuelConsumption(double fuelConsumption)
{
    if (fuelConsumptionValid(fuelConsumption))
        mFuelConsumption = fuelConsumption;
    else {
        mFuelConsumption = 1.0;
        qDebug("Invalid fuelConsumption=%s",qPrintable(QString("%1").arg(fuelConsumption)));
    }
}

bool Vehicle::brandValid(QString brand)
{
    QRegularExpression re(VEHICLE_REGULAR_EXPRESSION_INVALID);

    return !brand.contains(re);
}

bool Vehicle::modelValid(QString model)
{
    QRegularExpression re(VEHICLE_REGULAR_EXPRESSION_INVALID);

    return !model.contains(re);
}

bool Vehicle::yearValid(unsigned year)
{
    return year >= MIN_VEHICLE_YEAR && year <= (unsigned)QDate().currentDate().year();
}

bool Vehicle::passengersValid(unsigned passengers)
{
    return passengers <= MAX_VEHICLE_PASSENGERS;
}

bool Vehicle::loadCapacityValid(unsigned loadCapacity)
{
  return loadCapacity <= MAX_VEHICLE_LOAD_CAPACITY;
}

bool Vehicle::fuelConsumptionValid(double fuelConsumption)
{
    return fuelConsumption >= MIN_VEHICLE_FUEL_CONSUMPTION && fuelConsumption <= MAX_VEHICLE_FUEL_CONSUMPTION;
}

QDebug operator<<(QDebug debug, const Vehicle &vehicle) {
    QString str;
    str += vehicle.brand() + " ";
    str += vehicle.model() + " ";
    str += QString("%1 ").arg(vehicle.year());
    str += QString("%1 ").arg(vehicle.passengers());
    str += QString("%1 ").arg(vehicle.loadCapacity());
    str += QString("%1 ").arg(vehicle.fuelConsumption());
    debug << str;
    return debug;
}

}   // namespace TransportSystemDlg


