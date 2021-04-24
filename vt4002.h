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
