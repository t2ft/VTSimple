#include "vt4002.h"
#include <QSerialPort>
#include <QDebug>

VT4002::VT4002(const QString &portName, int addr, QObject *parent) : QObject(parent)
  , m_port(new QSerialPort(portName, this))
  , m_addr(addr)
{
    m_port->setBaudRate(QSerialPort::Baud9600);
    m_port->setStopBits(QSerialPort::OneStop);
    m_port->setParity(QSerialPort::NoParity);
    if (m_port->open(QSerialPort::ReadWrite)) {
        qDebug() << "serial port is open";
        connect(m_port, &QSerialPort::readyRead, this, &VT4002::onNewData);
    } else {
        qDebug() << "failed to open serial port";
        delete m_port;
        m_port = nullptr;
    }

}

void VT4002::requestInfo()
{
    if (isValid()) {
        QString s = QString("$%1I\r").arg(m_addr, 2, 10, QLatin1Char('0'));
        //qDebug() << "requestInfo ->" << s;
        m_port->write(s.toLatin1());
    }
}

void VT4002::setTemp(double t, bool on)
{
    if (isValid()) {
        QString s = QString("$%1E %2 0000.0 0000.0 0000.0 0000.0 0000.0 0000.0 0%3000000000000000000000000000000\r")
                .arg(m_addr, 2, 10, QLatin1Char('0'))
                .arg(t, 6, 'f', 1, QLatin1Char('0'))
                .arg(on ? '1':'0');
        qDebug() << "setTemp ->" << s;
        m_port->write(s.toLatin1());
    }
}

void VT4002::onNewData()
{
    QByteArray data = m_port->readAll();
    int i = data.indexOf('\r');
    if (i<0) {
        m_buffer.append(data);
    } else {
        m_buffer.append(data.left(i));
        //qDebug() << "complete data (" << m_buffer.length() << "bytes ) =" << QString(m_buffer);
        if (m_buffer.length() == 130) {
            double nomTemp = m_buffer.left(6).toDouble();
            double actTemp = m_buffer.mid(7, 6).toDouble();
            bool isOn = (m_buffer.mid(99 , 1) == "1");
            emit info(nomTemp, actTemp, isOn);

        }
        m_buffer.clear();
    }
}
