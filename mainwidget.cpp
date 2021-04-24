#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "silentcall.h"
#include "vt4002.h"
#include <QDebug>
#include <QSettings>
#include <QSerialPort>
#include <QSerialPortInfo>

#define CFG_COMPORT     "ComPort"
#define CFG_DEVADDR     "DevAddr"
#define CFG_UPDATEINT   "UpdateIntervall"
#define CFG_SETTEMP     "SetTemperature"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VTSimple)
    , m_idUpdateTimer(0)
    , m_dev(nullptr)
{
    ui->setupUi(this);
    QSettings cfg;
    QString lastPort = cfg.value(CFG_COMPORT, "COM1").toString();
    qDebug() << "lastPort:" << lastPort;
    // detect serial ports and fill combo box
    qDebug() << "detected COM Ports:";
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    int inx=0;
    int portInx = 0;
    for (auto &port : ports) {
        QString name = port.portName();
        qDebug() << "    " << inx << ": "<< name;
        ui->comPort->addItem(name);
        ++inx;
        if (lastPort == name) {
            portInx = inx;
            qDebug() << "           -> that's it!";
        }
    }
    SilentCall(ui->comPort)->setCurrentIndex(portInx);
    int devAddr = cfg.value(CFG_DEVADDR, 0).toInt();
    qDebug() << "last device address:" << devAddr;
    SilentCall(ui->devAddr)->setValue(devAddr);
    double setTemp = cfg.value(CFG_UPDATEINT, 20.).toDouble();
    qDebug() << "last set temperature:"  << setTemp;
    SilentCall(ui->setTemp)->setValue(setTemp);
    int updateInt = cfg.value(CFG_UPDATEINT, 1).toInt();
    qDebug() << "last update intervall:" << updateInt;
    SilentCall(ui->updateInt)->setValue(updateInt);
    if (createDevice(lastPort, devAddr)) {
        m_idUpdateTimer = startTimer(updateInt*1000);
    }
}


MainWidget::~MainWidget()
{
    delete ui;
    delete m_dev;
}

bool MainWidget::createDevice()
{
    return createDevice(ui->comPort->currentText(), ui->devAddr->value());
}


bool MainWidget::createDevice(const QString &port)
{
    return createDevice(port, ui->devAddr->value());
}

bool MainWidget::createDevice(int addr)
{
    return createDevice(ui->comPort->currentText(), addr);
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
    if (createDevice(arg1)) {
        QSettings cfg;
        cfg.setValue(CFG_DEVADDR, arg1);
    }
}

void MainWidget::on_comPort_currentIndexChanged(int index)
{
    QString port = ui->comPort->itemText(index);
    if (createDevice(port)) {
        QSettings cfg;
        cfg.setValue(CFG_COMPORT, port);
    }
}

void MainWidget::on_updateInt_valueChanged(int arg1)
{
    killTimer(m_idUpdateTimer);
    m_idUpdateTimer = startTimer(arg1*1000);
    QSettings cfg;
    cfg.setValue(CFG_UPDATEINT, arg1);
}

void MainWidget::on_setTemp_valueChanged(double arg1)
{
    QSettings cfg;
    cfg.setValue(CFG_SETTEMP, arg1);
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
