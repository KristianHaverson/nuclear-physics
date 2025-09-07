#include "MenuWindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFrame>
#include <QLabel>
#include <iostream>

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// Constructor: MenuWindow
MenuWindow::MenuWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Nuclear Physics Toolbox");
    resize(400, 300);

    rootProcess  = new QProcess(this);
    rootTermProcess  = new QProcess(this);
    geantProcess = new QProcess(this);
    srimProcess  = new QProcess(this);
    azureProcess = new QProcess(this);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // --- Row 0: Initialize Geant4 ---
    //QLabel *initLabel = new QLabel("<b>Initialise</b>");
    //layout->addWidget(initLabel);


    //QFrame *line1 = new QFrame();
    //line1->setFrameShape(QFrame::HLine);
    //line1->setFrameShadow(QFrame::Sunken);
    //layout->addWidget(line1);

    // --- Row 1: Test ROOT ---
    QLabel *rootLabel = new QLabel("<b>Test</b>");
    layout->addWidget(rootLabel);

    geantBtn = new QPushButton("Test Geant4");
    layout->addWidget(geantBtn);


    rootBtn = new QPushButton("Test ROOT");
    layout->addWidget(rootBtn);

    QFrame *line2 = new QFrame();
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);
    layout->addWidget(line2);

    // --- Row 2: Run SRIM ---
    QLabel *srimLabel = new QLabel("<b>Run</b>");
    layout->addWidget(srimLabel);

    srimBtn = new QPushButton("Run SRIM");
    layout->addWidget(srimBtn);

    //QFrame *line3 = new QFrame();
    //line3->setFrameShape(QFrame::HLine);
    //line3->setFrameShadow(QFrame::Sunken);
    //layout->addWidget(line3);

    // --- Row 3: Run AZURE2 ---

    AzureBtn = new QPushButton("Run AZURE2");
    layout->addWidget(AzureBtn);


    rootTermBtn = new QPushButton("Run ROOT");
    layout->addWidget(rootTermBtn);


    QFrame *line4 = new QFrame();
    line4->setFrameShape(QFrame::HLine);
    line4->setFrameShadow(QFrame::Sunken);
    layout->addWidget(line4);

    // --- Exit button ---
        QLabel *azureLabel = new QLabel("<b>Exit</b>");
    layout->addWidget(azureLabel);
    exitBtn = new QPushButton("Exit");
    layout->addWidget(exitBtn);

    // --- signal/slot connections ---
    connect(rootBtn,  &QPushButton::clicked, this, &MenuWindow::runRoot);
    connect(rootTermBtn,  &QPushButton::clicked, this, &MenuWindow::runRootTerm);
    connect(geantBtn, &QPushButton::clicked, this, &MenuWindow::runGeant4);
    connect(srimBtn,  &QPushButton::clicked, this, &MenuWindow::runSRIM);
    connect(AzureBtn, &QPushButton::clicked, this, &MenuWindow::runAZURE);
    connect(exitBtn,  &QPushButton::clicked, this, &MenuWindow::closeMenu);
}



////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

MenuWindow::~MenuWindow() {
    terminateProcesses();
}

void MenuWindow::runRoot() {
    if(rootProcess->state() == QProcess::NotRunning) {

    auto attachOutput = [](QProcess* process) {
        QObject::connect(process, &QProcess::readyReadStandardOutput, [process]() {
            std::cout << process->readAllStandardOutput().toStdString();
        });
        QObject::connect(process, &QProcess::readyReadStandardError, [process]() {
            std::cerr << process->readAllStandardError().toStdString();
        });
    };

    attachOutput(rootProcess); // attach stdout/stderr



    rootProcess->start("root", QStringList() << "-l" << "/nuclear-physics/containerScripts/root_test.C");
        if (!rootProcess->waitForStarted(3000)) {
            QMessageBox::warning(this, "ROOT", "Failed to start ROOT process.");
        }
    } else {
        QMessageBox::information(this, "ROOT", "ROOT is already running.");
    }

    //if (rootProcess->state() != QProcess::NotRunning) {
    //    rootProcess->kill();      // force terminate any lingering process
    //    rootProcess->waitForFinished(1000);
    //}

}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void MenuWindow::runRootTerm() {
    if (rootTermProcess->state() != QProcess::NotRunning) {
        QMessageBox::information(this, "ROOT", "ROOT is already running.");
        return;
    }

    auto attachOutput = [](QProcess* process) {
        QObject::connect(process, &QProcess::readyReadStandardOutput, [process]() {
            std::cout << process->readAllStandardOutput().toStdString();
        });
        QObject::connect(process, &QProcess::readyReadStandardError, [process]() {
            std::cerr << process->readAllStandardError().toStdString();
        });
    };
    attachOutput(rootTermProcess); // attach stdout/stderr
    

    QString program = "xterm";
    QStringList args;
    args << "-hold" << "-e" << "root";
    rootTermProcess->start(program, args);


    if (!rootTermProcess->waitForStarted(3000)) {
        QMessageBox::warning(this, "ROOT", "Failed to start ROOT terminal process.");
    }
}





void MenuWindow::runSRIM() {
    if(srimProcess->state() == QProcess::NotRunning) {
        srimProcess->setWorkingDirectory("/opt/software/SRIM");
        srimProcess->start("wine", QStringList() << "SRIM.exe");
        if (!srimProcess->waitForStarted(3000)) {
            QMessageBox::warning(this, "SRIM", "Failed to start SRIM process. Make sure Wine and SRIM are installed.");
        }
    } else {
        QMessageBox::information(this, "SRIM", "SRIM is already running.");
    }
}
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


void MenuWindow::runGeant4() {
    if (geantProcess->state() != QProcess::NotRunning) {
        QMessageBox::information(this, "Geant4", "Geant4 example is already running.");
        return;
    }

    auto attachOutput = [](QProcess* process) {
        QObject::connect(process, &QProcess::readyReadStandardOutput, [process]() {
            std::cout << process->readAllStandardOutput().toStdString();
        });
        QObject::connect(process, &QProcess::readyReadStandardError, [process]() {
            std::cerr << process->readAllStandardError().toStdString();
        });
    };

    attachOutput(geantProcess); // attach stdout/stderr

    geantProcess->start("/bin/bash", QStringList() << "-c"
                                   << "/nuclear-physics/containerScripts/runGeantRadioactive.sh");

    if (!geantProcess->waitForStarted(3000)) {
        QMessageBox::warning(this, "Geant4", "Failed to start Geant4 rdecay01 example.\n");
    } else {
        QMessageBox::information(this, "Geant4", "Geant4 rdecay01 example is being built and launched.\n");
    }
}


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////






void MenuWindow::runAZURE() {
    if (azureProcess->state() == QProcess::NotRunning) {
        azureProcess->start("/bin/bash", QStringList() << "-c" << "AZURE2");

        if (!azureProcess->waitForStarted(3000)) {
            QMessageBox::warning(this, "AZURE2",
                                 "Failed to start AZURE2.\n");
        } 
    } else {
        QMessageBox::information(this, "AZURE2", "AZURE2 is already running.");
    }
}




////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void MenuWindow::closeMenu() {
    close();
}

void MenuWindow::terminateProcesses() {

    if(rootProcess && rootProcess->state() != QProcess::NotRunning) {
        rootProcess->terminate();
        if (!rootProcess->waitForFinished(5000)) {
            rootProcess->kill();
        }
    }

    if(srimProcess && srimProcess->state() != QProcess::NotRunning) {
        srimProcess->terminate();
        if (!srimProcess->waitForFinished(5000)) {
            srimProcess->kill();
        }
    }

    if(geantProcess && geantProcess->state() != QProcess::NotRunning) {
        geantProcess->terminate();
        if (!geantProcess->waitForFinished(5000)) {
            geantProcess->kill();
        }
    }

}