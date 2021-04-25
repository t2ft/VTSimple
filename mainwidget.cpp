#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "silentcall.h"
#include "vt4002.h"
#include <QDebug>
#include <QSettings>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

#define CFG_COMPORT     "ComPort"
#define CFG_DEVADDR     "DevAddr"
#define CFG_UPDATEINT   "UpdateIntervall"
#define CFG_SETTEMP     "SetTemperature"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VTSimple)
    , m_idUpdateTimer(0)
    , m_comportIndex(0)
    , m_port("COM1")
    , m_devAddr(0)
    , m_updateInt(1)
    , m_setTemp(20.)
    , m_dev(nullptr)
{
    ui->setupUi(this);
    QSettings cfg;
    m_port = cfg.value(CFG_COMPORT, m_port).toString();
    qDebug() << "lastPort:" << m_port;
    // detect serial ports and fill combo box
    qDebug() << "detected COM Ports:";
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    int inx=0;
    for (auto &port : ports) {
        QString name = port.portName();
        qDebug() << "    " << inx << ": "<< name;
        SilentCall(ui->comPort)->addItem(name);
        if (m_port == name) {
            m_comportIndex = inx;
            qDebug() << "           -> that's it!";
        }
        ++inx;
    }
    m_devAddr = cfg.value(CFG_DEVADDR, m_devAddr).toInt();
    m_setTemp = cfg.value(CFG_SETTEMP, m_setTemp).toDouble();
    m_updateInt = cfg.value(CFG_UPDATEINT, m_updateInt).toInt();
    qDebug() << "last device address:" << m_devAddr;
    qDebug() << "last set temperature:"  << m_setTemp;
    qDebug() << "last update intervall:" << m_updateInt;
    QTimer::singleShot(0, this, SLOT(updateComboIndex()));
    SilentCall(ui->devAddr)->setValue(m_devAddr);
    SilentCall(ui->setTemp)->setValue(m_setTemp);
    SilentCall(ui->updateInt)->setValue(m_updateInt);
    m_idUpdateTimer = startTimer(m_updateInt*1000);
}


MainWidget::~MainWidget()
{
    delete ui;
    delete m_dev;
}

bool MainWidget::createDevice(const QString &port, int addr)
{
    qDebug() << "creating Device at port" << port << "with address" << addr;
    delete m_dev;
    m_dev = nullptr;
    ui->nominalTemp->setText("-/-");
    ui->actualTemp->setText("-/-");
    ui->devStatus->setText("-/-");
    m_dev = new VT4002(port, addr);
    if (m_dev != nullptr) {
        if (m_dev->isValid()) {
            connect(m_dev, &VT4002::info, this, &MainWidget::updateInfo);
            m_dev->requestInfo();
            qDebug() << "device created successfully";
            return true;
        } else {
            delete m_dev;
            m_dev = nullptr;
        }
    }
    qDebug() << "device creation failed";
    return false;
}


void MainWidget::timerEvent(QTimerEvent *ev)
{
    if (ev->timerId()==m_idUpdateTimer) {
        if (m_dev != nullptr)
            m_dev->requestInfo();
    }
}


void MainWidget::on_devAddr_valueChanged(int arg1)
{
    if (arg1 != m_devAddr) {
        m_devAddr = arg1;
        if (createDevice(m_port, m_devAddr)) {
            QSettings cfg;
            cfg.setValue(CFG_DEVADDR, m_devAddr);
            qDebug() << "new device address:" << m_devAddr;
        }
    }
}

void MainWidget::on_comPort_currentIndexChanged(int index)
{
    if (m_comportIndex != index) {
        m_comportIndex = index;
        m_port = ui->comPort->itemText(index);
        if (createDevice(m_port, m_devAddr)) {
            QSettings cfg;
            cfg.setValue(CFG_COMPORT, m_port);
            qDebug() << "new COM-Port:" << m_port << "(" << m_comportIndex << ")";
        }
    }
}

void MainWidget::on_updateInt_valueChanged(int arg1)
{
    if (m_updateInt != arg1) {
        m_updateInt = arg1;
        if (m_idUpdateTimer != 0)
            killTimer(m_idUpdateTimer);
        m_idUpdateTimer = startTimer(m_updateInt*1000);
        QSettings cfg;
        cfg.setValue(CFG_UPDATEINT, m_updateInt);
        qDebug() << "new update intervall:" << m_updateInt;
    }
}

void MainWidget::on_setTemp_editingFinished()
{
    double arg1 = ui->setTemp->value();
    if (m_setTemp != arg1) {
        m_setTemp = arg1;
        QSettings cfg;
        cfg.setValue(CFG_SETTEMP, m_setTemp);
        qDebug() << "new set temperature:" << m_setTemp;
    }
}

void MainWidget::on_doSet_clicked()
{
    if (m_dev) {
        m_dev->setTemp(ui->setTemp->value(), ui->devOn->isChecked());
    }
}

void MainWidget::updateInfo(double nomTemp, double actTemp, bool isOn)
{
    ui->nominalTemp->setText(QString("%1 °C").arg(nomTemp, 0, 'f', 1));
    ui->actualTemp->setText(QString("%1 °C").arg(actTemp, 0, 'f', 1));
    ui->devStatus->setText(isOn ? "On" : "Off");
}

void MainWidget::updateComboIndex()
{
    qDebug() << "updateComboIndex to" << m_comportIndex;
    SilentCall(ui->comPort)->setCurrentIndex(m_comportIndex);
}

