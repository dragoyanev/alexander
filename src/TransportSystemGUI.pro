QT      +=  gui widgets

TEMPLATE = app

HEADERS = Vehicle.h Route.h Schedule.h \
          VehicleTab.h \
          FileReader.h FileWriter.h \
          TransportSystemDlg.h

SOURCES = main.cpp \
          Vehicle.cpp Route.cpp Schedule.cpp \
          VehicleTab.cpp \
          FileReader.cpp FileWriter.cpp \
          TransportSystemDlg.cpp 


FORMS     =  ./ui/VehicleTab.ui \
            ./ui/TransportSystemDlg.ui

RESOURCES = ./ui/TransportSystemGUI.qrc

TARGET = transportsystem
unix:TARGET = $$join(TARGET,,,.bin)
DESTDIR = ../bin
