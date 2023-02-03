#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <queue>
#include <format.h>
#include <check.h>
#include <check.cpp>
#include <compression.cpp>
#include <minify.h>
#include <Xml_to_Json.h>
#include <xmlTojson.cpp>
#include <search.h>
#include <search.cpp>
#include <QInputDialog>
#include <netAnalysis.h>
#include <string.h>
#include <visualize.cpp>

#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <QDebug>
#include <QPixmap>
#include <fstream>
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
        ui->compressionButton->setMask(region);
//        QPixmap pix("Graph.png");
//        ui->photo->setPixmap(pix);
        ui->photo->setScaledContents(true);


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
    ui->photo->clear();
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
    Tree t = parse(Qin.toStdString());
    string sr =t.XMLToJson();
    ui->OutputText->setPlainText(QString::fromStdString(sr));
}

//Most Influnecer Button
void MainWindow::on_InfluencerButton_clicked()
{
    QString Qin = ui->InputText->toPlainText();
    if(!Qin.isEmpty()){
        string s = mostInfluencer(Qin.toStdString());
        ui->OutputText->setPlainText(QString::fromStdString(s));
    }
    else
        QMessageBox::warning(this,"Warning","Please enter a valid XML!");

}

// Most Active button
void MainWindow::on_ActiveButton_clicked()
{
    QString Qin = ui->InputText->toPlainText();
    if(!Qin.isEmpty()){
        string s = mostActive(Qin.toStdString());
        ui->OutputText->setPlainText(QString::fromStdString(s));
    }
    else
        QMessageBox::warning(this,"Warning","Please enter a valid XML!");
}

//Mutual Friends Button
void MainWindow::on_MutualButton_clicked()
{
    QString Qin = ui->InputText->toPlainText();
    bool ok;
    QString id1 = QInputDialog::getText(this, tr("Mutual friends"),
                                         tr("ID1:"), QLineEdit::Normal,
                                         "", &ok);
    QString id2 = QInputDialog::getText(this, tr("Mutual friends"),
                                         tr("ID2:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !id1.isEmpty() && !id2.isEmpty() && !Qin.isEmpty()){
        int ID1 = stoi(id1.toStdString());
        int ID2 = stoi(id2.toStdString());
        string s = mutualFriends(ID1,ID2,Qin.toStdString());
        ui->OutputText->setPlainText(QString::fromStdString(s));
    }
    else
        QMessageBox::warning(this,"Warning","Please enter a valid ID or XML!");
}

//Suggest Friends Button
void MainWindow::on_SuggesButton_clicked()
{
    QString Qin = ui->InputText->toPlainText();
    bool ok;
    QString id = QInputDialog::getText(this, tr("Suggest friends"),
                                         tr("ID:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !id.isEmpty() && !Qin.isEmpty()){
        int ID = stoi(id.toStdString());
        string s = suggestFriends(ID,Qin.toStdString());
        ui->OutputText->setPlainText(QString::fromStdString(s));
    }
    else
        QMessageBox::warning(this,"Warning","Please enter a valid ID or XML!");
}

//Post Search Button
void MainWindow::on_actionPost_triggered()
{
    QString Qin = ui->InputText->toPlainText();
    bool ok;
    QString id = QInputDialog::getText(this, tr("Post search"),
                                         tr("type here:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !id.isEmpty() && !Qin.isEmpty()){
        string QSin = Qin.toStdString();
        string keyword = id.toStdString();
        int count;
        vector<string> ans=convert(QSin);
        count =xmlprase(ans);
        string temp=  searchPosts(keyword,count);
        ui->OutputText->setPlainText(QString::fromStdString(temp));
    }
    else
        QMessageBox::warning(this,"Warning","Please enter a valid ID or XML!");
}

//Visualize Button
void MainWindow::on_VisualizeButton_clicked()
{
    remove ("D:/sho8l/Qt/projects/build-Project-Desktop_Qt_6_4_1_MinGW_64_bit-Debug/graph.dot.png");
    QString z =ui->InputText->toPlainText();
    string x=z.toStdString();
    QPixmap Result=Graph_present(x);
    ui->photo->setPixmap(Result);
}
