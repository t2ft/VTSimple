// ***************************************************************************
// General Support Classes
// ---------------------------------------------------------------------------
// t2ftapplication.h
// QApplication with additional features
// ---------------------------------------------------------------------------
// Copyright (C) 2020 by t2ft - Thomas Thanner
// Waldstraße 15, 86399 Bobingen, Germany
// ---------------------------------------------------------------------------
// 2020-3-23  tt  Initial version created
// ***************************************************************************
#ifndef T2FTAPPLICATION_H
#define T2FTAPPLICATION_H

#include <QApplication>

class T2FTApplication : public QApplication
{
    Q_OBJECT
public:
    T2FTApplication(int &argc, char **argv, const QString &name, const QString &version);
};

#endif // T2FTAPPLICATION_H
