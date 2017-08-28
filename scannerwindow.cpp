#include "scannerwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QRegExp>
#include <QtNetwork/QNetworkConfiguration>
#include <QEvent>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QList>
#include <QMessageBox>
#include <QListWidgetItem>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QProcess sh;
    sh.start("killall wpa_supplicant" );

    sh.closeWriteChannel();
    sh.waitForFinished();

    sh.close();

    QProcess flerp;
    flerp.start("wpa_supplicant -Dnl80211 -iwlan0 -c/etc/wpa_thing.conf -B");

    flerp.closeWriteChannel();
    flerp.waitForFinished();

    flerp.close();

    QProcess derp;
    derp.start("wpa_cli scan" );

    derp.closeWriteChannel();
    derp.waitForFinished();

    derp.close();

    ui->setupUi(this);

    pswindow = new PsWindow();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_scanbtn_clicked()
{
    ui->wifiList->clear();
    scan_wpacli();
}
void MainWindow::scan_wpacli()
{
    QProcess ps;
    ps.start("wpa_cli scan_results" );

    ps.closeWriteChannel();
    ps.waitForFinished();

    QString line = ps.readLine();
    line = ps.readLine(); //to remove first line
    line = ps.readLine(); //to remove second line

    while (!line.isNull()) {
        QStringList strList = line.split(QRegExp("\\s+"));//, QString::KeepEmptyParts);

        if(strList.count()>=5)
        {
            ui->wifiList->addItem(strList.at(4) + "");
        }

        line = ps.readLine();
    };

    ps.close();
}

void MainWindow::on_wifiList_itemDoubleClicked(QListWidgetItem *item)
{
    QMessageBox msgBox;

    QString str = item->text();

    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setText("Do you want to connect to " + str);
    msgBox.exec();

    if(msgBox.result()==QMessageBox::Yes)
    {
        //QProcess flerp;
        //flerp.start("wpa_cli identity 0 " + str );

//        flerp.start("wpa_cli set_network 0 ssid " + str );

//        flerp.closeWriteChannel();
//        flerp.waitForFinished();

        //QString feedback = flerp.readAll();
        //ui->wifiList->clear();
        //ui->wifiList->addItem(feedback);

        //flerp.close();
        pswindow->SetSSID(str);
        pswindow->show();

        this->close();
    }


}
