// ***************************************************************************
// General Support Classes
// ---------------------------------------------------------------------------
// t2ftapplication.cpp
// QApplication with additional features
// ---------------------------------------------------------------------------
// Copyright (C) 2020 by t2ft - Thomas Thanner
// Waldstraße 15, 86399 Bobingen, Germany
// ---------------------------------------------------------------------------
// 2020-3-23  tt  Initial version created
// ***************************************************************************
#include "t2ftapplication.h"

T2FTApplication::T2FTApplication(int &argc, char **argv, const QString &name, const QString &version)
    : QApplication(argc, argv)
{
    setOrganizationName("t2ft-ThomasThanner");
    setOrganizationDomain("t2ft.de");
    setApplicationVersion(version);
    setApplicationName(name);
    setApplicationDisplayName(name + "-V" + version);
#ifdef QT_DEBUG
    setApplicationDisplayName(applicationDisplayName() + " (DEBUG)");
#endif
}
