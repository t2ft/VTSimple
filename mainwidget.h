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
    void on_setTemp_valueChanged(double arg1);
    void on_doSet_clicked();

    void updateInfo(double nomTemp, double actTemp, bool isOn);

private:
    bool createDevice();
    bool createDevice(const QString &portName);
    bool createDevice(int addr);
    bool createDevice(const QString &portName, int addr);

    Ui::VTSimple *ui;
    int     m_idUpdateTimer;
    VT4002  *m_dev;
};
#endif // MAINWIDGET_H
