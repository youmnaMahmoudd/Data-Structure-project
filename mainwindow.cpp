#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <queue>
#include <format.h>
#include <check.h>
#include <correct.cpp>
#include <compression.cpp>
#include <minify.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
        QRect rect(2,2,262,26);
        QRegion region(rect, QRegion::Ellipse);
//        ui->ClearButton->setMask(region);
//        ui->BrowseButton->setMask(region);
//        ui->SaveAsButton->setMask(region);
        ui->JSONButton->setMask(region);
        ui->CorrectButton->setMask(region);
        ui->CheckButton->setMask(region);
        ui->MinifyButton->setMask(region);
        ui->PretifyButton->setMask(region);
        ui->GraphButton->setMask(region);
        ui->compressionButton->setMask(region);
        QRect rect1(2,2,696,36);
        QRegion region1(rect1, QRegion::Ellipse);
        ui->GraphButton->setMask(region1);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionAdd_triggered()
{//ToolBar: adding file to input text

}


void MainWindow::on_actionSaveAs_triggered()
{
   //ToolBar: Save as
}

//ToolBar: clearing input text and output text
void MainWindow::on_actionactionClear_triggered()
{
    ui->InputText->setPlainText("");
    ui->OutputText->setPlainText("");
}



void MainWindow::on_CorrectButton_clicked()
{
//CorrectButton
}


void MainWindow::on_PretifyButton_clicked()
{
//PretifyButton
}

void MainWindow::on_CheckButton_clicked()
{
    //CheckButton
}

//Compression Button
bool flag=0;
void MainWindow::on_compressionButton_clicked()
{
    QString Qin = ui->InputText->toPlainText();
    QString Qout =ui->OutputText->toPlainText();
    string s = compress(Qin.toStdString());

    if(flag==0){
        s = compress(Qin.toStdString());
        flag=1;
    }
    else{
        s = decode(root1,Qout.toStdString());
        flag=0;
    }
    ui->OutputText->setPlainText(QString::fromStdString(s));

}


void MainWindow::on_MinifyButton_clicked()
{
    QString Qin = ui->InputText->toPlainText();
    QString Qout =ui->OutputText->toPlainText();
    string s;
    if(Qout==""){
        s=Qin.toStdString();
        s = clear(&s);
    }
    else{
        s=Qout.toStdString();
        s = clear(&s);
    }
    ui->OutputText->setPlainText(QString::fromStdString(s));
}

