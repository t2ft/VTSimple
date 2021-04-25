// ***************************************************************************
// Simple tool to set and read temperatures for a VT4002 climate chamber
// ---------------------------------------------------------------------------
// mainwidget.h
// main application widget, header file
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
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class VTSimple; }
QT_END_NAMESPACE

class VT4002;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    void timerEvent(QTimerEvent *ev);

private slots:
    void on_devAddr_valueChanged(int arg1);
    void on_comPort_currentIndexChanged(int index);
    void on_updateInt_valueChanged(int arg1);
    void on_setTemp_editingFinished();
    void on_doSet_clicked();

    void updateInfo(double nomTemp, double actTemp, bool isOn);
    void updateComboIndex();


private:
    bool createDevice(const QString &portName, int addr);

    Ui::VTSimple *ui;
    int     m_idUpdateTimer;
    int     m_comportIndex;
    QString m_port;
    int     m_devAddr;
    int     m_updateInt;
    double  m_setTemp;
    VT4002  *m_dev;
};
#endif // MAINWIDGET_H
