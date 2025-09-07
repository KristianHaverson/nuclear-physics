#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QProcess>

class MenuWindow : public QWidget {
    Q_OBJECT

public:
    MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow(); 

public slots:
    void terminateProcesses(); 

private slots:
    void runRoot();
    void runAZURE();
    void runGeant4();
    void runSRIM();
    void closeMenu();

private:
    QPushButton *rootBtn;
    QPushButton *geantBtn;
    QPushButton *srimBtn;
    QPushButton *AzureBtn;
    QPushButton *exitBtn;
    
    QProcess *rootProcess; 
    QProcess *geantProcess;
    QProcess *srimProcess;
    QProcess *azureProcess;
};

#endif // MENUWINDOW_H