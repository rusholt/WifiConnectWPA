#ifndef PSWINDOW_H
#define PSWINDOW_H

#include <QWidget>

namespace Ui {
class PsWindow;
}

class PsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PsWindow(QWidget *parent = 0);
    ~PsWindow();
    void SetSSID(QString ssidStr);

private slots:

    void on_dial_sliderMoved(int position);

    void on_pushButton_2_clicked();

    void on_conncectBtn_clicked();


private:
    Ui::PsWindow *ui;
};

#endif // PSWINDOW_H
