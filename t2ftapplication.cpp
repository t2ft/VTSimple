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
// ---------------------------------------------------------------------------
// T2FTApplication is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// T2FTApplication is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with T2FTApplication.  If not, see <https://www.gnu.org/licenses/>.
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
