//
// main.cpp
//
// Copyright (C) 2017
//

#include <QApplication>
#include <QDate>

#include "TransportSystemDlg.h"

namespace TransportSystemDlg {

static int main(int argc, char *argv[])
try {
    qRegisterMetaType<QMessageBox::Icon>("QMessageBox::Icon");

    QApplication::setApplicationName("TransportSystem");
    QApplication app(argc, argv);


    TransportSystemDlg dlg;
    dlg.show();
    return app.exec();
} catch (const std::exception &e) {
    qWarning("%s", e.what());
    return 1;
} catch (...) {
    qWarning("Unknown exception");
    return 1;
}

}   // namespace TransportSystemDlg

int main(int argc, char *argv[])
{
    return TransportSystemDlg::main(argc, argv);
}
