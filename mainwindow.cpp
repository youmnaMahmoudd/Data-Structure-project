#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <queue>
#include <format.h>
//#include <check.h>
#include <correct.cpp>
#include <compression.cpp>
#include <minify.h>
#include <check.cpp>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
        QRect rect(2,2,262,26);
        QRegion region(rect, QRegion::Ellipse);
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


//ToolBar: adding file to input text
void MainWindow::on_actionAdd_triggered()
{
    QString fileName;
    fileName=QFileDialog::getOpenFileName(this,"open the XML file");
       QFile file(fileName);

       if(!file.open(QFile::ReadOnly | QFile::Text)){
           QMessageBox::warning(this,"Error", "Invalid file" );
           return;
       }

       QTextStream in(&file);
       QString text=in.readAll();
       ui->InputText->setPlainText(text);
       file.close();
}

//ToolBar: Save as
void MainWindow::on_actionSaveAs_triggered()
{

    QString fileName=QFileDialog::getSaveFileName(this,"Save as");
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"Warning","Can't Open File: "+file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text=ui->OutputText->toPlainText();
    out<<text;
    file.close();
}

//ToolBar: clearing input text and output text
void MainWindow::on_actionClear_triggered()
{
    ui->InputText->setPlainText("");
    ui->OutputText->setPlainText("");
}


//CorrectButton
void MainWindow::on_CorrectButton_clicked()
{
    QString Qin = ui->InputText->toPlainText();
    string s = correct(Qin.toStdString());
    ui->OutputText->setPlainText(QString::fromStdString(s));
}

//PretifyButton
void MainWindow::on_PretifyButton_clicked()
{
    QString Qin = ui->InputText->toPlainText();
    QString Qout =ui->OutputText->toPlainText();
    string s;
    if(Qout==""){
        s = format(Qin.toStdString());
    }
    else{
        s = format(Qout.toStdString());
    }
    if(s=="Correct the errors")
        QMessageBox::information(this,"ERROR","Correct the errors");
    else
        ui->OutputText->setPlainText(QString::fromStdString(format(s)));
}

//CheckButton
void MainWindow::on_CheckButton_clicked()
{
    QString Qin = ui->InputText->toPlainText();
    QString Qout =ui->OutputText->toPlainText();
    string s;
    if(Qout==""){
        s = check_error(Qin.toStdString());
    }
    else{
        s = check_error(Qout.toStdString());
    }
    QMessageBox::information(this,"ERROR",QString::fromStdString(s));
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

//Minify Button
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

//XML to Json Button
void MainWindow::on_JSONButton_clicked()
{
    QString Qin = ui->InputText->toPlainText();
//    Tree t = parse(xml);
//    string sr =t.XMLToJson();
//    ui->OutputText->setPlainText(QString::fromStdString(sr));
}

