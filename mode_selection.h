#ifndef MODE_SELECTION_H
#define MODE_SELECTION_H

#include <QMainWindow>

#include <server.h>
#include <client.h>
#include <settings.h>

QT_BEGIN_NAMESPACE
namespace Ui { class mode_selection; }
QT_END_NAMESPACE

class mode_selection : public QMainWindow
{
    Q_OBJECT

public:
    mode_selection(QWidget *parent = nullptr);
    ~mode_selection();

private slots:
    void on_pushButton_clicked();

private:
    Ui::mode_selection *ui;
};
#endif // MODE_SELECTION_H
