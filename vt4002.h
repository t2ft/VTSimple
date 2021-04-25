// ***************************************************************************
// Simple tool to set and read temperatures for a VT4002 climate chamber
// ---------------------------------------------------------------------------
// vt4002.h
// VT4002 serial device abstraction, header file
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
#ifndef VT4002_H
#define VT4002_H

#include <QObject>

class QSerialPort;

class VT4002 : public QObject
{
    Q_OBJECT
public:
    explicit VT4002(const QString &portName, int addr, QObject *parent = nullptr);
    void requestInfo();
    void setTemp(double t, bool on);
    bool isValid() const { return m_port != nullptr; }

signals:
    void info(double nomTemp, double actTemp, bool isOn);

private slots:
    void onNewData();

private:
    QSerialPort     *m_port;
    int             m_addr;

    QByteArray      m_buffer;
};

#endif // VT4002_H
