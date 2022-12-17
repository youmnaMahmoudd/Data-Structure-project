#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionAdd_triggered();

    void on_CorrectButton_clicked();

    void on_PretifyButton_clicked();

    void on_CheckButton_clicked();

    void on_actionClear_triggered();

    void on_actionSaveAs_triggered();

    void on_compressionButton_clicked();

    void on_MinifyButton_clicked();

    void on_JSONButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
