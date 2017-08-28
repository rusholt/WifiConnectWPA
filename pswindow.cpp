#include "pswindow.h"
#include "ui_pswindow.h"
#include <QTimer>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


PsWindow::PsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PsWindow)
{
    ui->setupUi(this);
}

PsWindow::~PsWindow()
{
    delete ui;
}
QString psw = "";
QString c = "";
QString ssid = "";

void PsWindow::SetSSID(QString ssidStr)
{
    ssid = ssidStr;
    ui->lbSSID->setText(ssid);
}


void PsWindow::on_dial_sliderMoved(int position)
{
    c = (QString)position;
    ui->label->setText((QString)position);
}

void PsWindow::on_pushButton_2_clicked()
{
    psw.append(c);
    ui->lineEdit->setText(psw);
}

void PsWindow::on_conncectBtn_clicked()
{
    if(psw.length()>=8)
    {
        QProcess sh;
        sh.start("killall wpa_supplicant" );

        sh.closeWriteChannel();
        sh.waitForFinished();

        sh.close();


        QProcess cli0;
        cli0.start("rm /etc/wpa_thing.conf");

        cli0.closeWriteChannel();
        cli0.waitForFinished();

        QString feedback0 = cli0.readAll();
        ui->textEdit->append(feedback0);

        cli0.close();


        QString filename = "/etc/wpa_thing.conf";
        QFile file(filename);
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            stream << "ctrl_interface=/var/run/wpa_supplicant \n \
ctrl_interface_group=0 \n \
update_config=1 \n \
\n \
network={  \n \
    ssid=\""+ ssid + "\" \n \
    psk=\""+ psw + "\" \n \
}" << endl;
        }

            QProcess flerp;
            flerp.start("wpa_supplicant -Dnl80211 -iwlan0 -c/etc/wpa_thing.conf -B");

            flerp.closeWriteChannel();
            flerp.waitForFinished();

            flerp.close();


            QProcess cli5;
            cli5.start("udhcpc -i wlan0");

            cli5.closeWriteChannel();
            cli5.waitForFinished();

            QString feedback5 = cli5.readAll();
            ui->textEdit->append(feedback5);

            cli5.close();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Passphrase has to be more than 8 characters");
        msgBox.exec();
    }

}


