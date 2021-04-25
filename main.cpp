// ***************************************************************************
// Simple tool to set and read temperatures for a VT4002 climate chamber
// ---------------------------------------------------------------------------
// main.cpp
// main application entry point
// ---------------------------------------------------------------------------
// Copyright (C) 2021 by t2ft - Thomas Thanner
// Waldstraße 15, 86399 Bobingen, Germany
// ---------------------------------------------------------------------------
// 2021-04-24  tt  Initial version created
// ---------------------------------------------------------------------------
// VTSimple is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// VTSimple is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with VTSimple.  If not, see <https://www.gnu.org/licenses/>.
// ***************************************************************************
#include "mainwidget.h"

#include "t2ftapplication.h"

int main(int argc, char *argv[])
{
    T2FTApplication a(argc, argv, "VTSimple", "1.0.0");
    MainWidget w;
    w.show();
    return a.exec();
}
