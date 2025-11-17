#include "mywidget.h"
#include "ui_mywidget.h"

#include <QFile>
#include <QDebug>
#include <QFileDialog>
QString mFilename = "c:/Users/user/Desktop/EX/contackbook.txt";
void Write (QString Filename, QString str)
{
    QFile mFile (Filename);
    if(!mFile.open(QFile::WriteOnly | QFile:: Text)) {
        qDebug() <<"Could not open file for writing";
        return;
    }
    QTextStream out (&mFile);
    out<<str;
    mFile.flush();
    mFile.close();
}
MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    QStringList colTitles;
    ui->tableWidget->setColumnCount(4);

    colTitles << QStringLiteral("學號")<< QStringLiteral("班級")<< QStringLiteral("姓名")<< QStringLiteral("電話");
    ui->tableWidget->setHorizontalHeaderLabels(colTitles);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked()
{
    QTableWidgetItem *inputRow1, *inputRow2, *inputRow3, *inputRow4;
    inputRow1 = new QTableWidgetItem(QString(ui->lineEdit->text()));
    inputRow2 = new QTableWidgetItem(QString(ui->lineEdit_2->text()));
    inputRow3 = new QTableWidgetItem(QString(ui->lineEdit_3->text()));
    inputRow4 = new QTableWidgetItem(QString(ui->lineEdit_4->text()));

    ui->tableWidget->insertRow (ui->tableWidget->rowCount());

    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,inputRow1);
    ui->tableWidget->setItem (ui->tableWidget->rowCount()-1,1,inputRow2);
    ui->tableWidget->setItem (ui->tableWidget->rowCount()-1,2, inputRow3);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,inputRow4);
}



void MyWidget::on_pushButton_2_clicked()
{
    QString saveFile="";
    int rc, cc;
    rc=ui->tableWidget->rowCount();
    cc=ui->tableWidget->columnCount();
    mFilename=QFileDialog::getSaveFileName(this, "匯出存檔", ".");
    for(int i=0; i< rc; i++)
    {
        for(int j=0; j<cc;j++)
            saveFile += ui->tableWidget->item(i,j)->text()+",";
        saveFile+="\n";
    }
    Write(mFilename, saveFile);

}

void MyWidget::on_pushButton_3_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "匯入檔案", ".", "Text Files (*.txt);;CSV Files (*.csv);;All Files (*)");

    QFile file(filename);
    if (filename.isEmpty()) {
        qDebug() << "取消選擇檔案";
        return;
    }
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "無法開啟檔案";
        return;
    }

    QTextStream in(&file);
    QString line;
    int row = 0;

    ui->tableWidget->setRowCount(0);

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList fields = line.split(",");
        ui->tableWidget->insertRow(row);
        for (int i = 0; i < fields.size(); ++i) {
            ui->tableWidget->setItem(row, i, new QTableWidgetItem(fields.at(i)));
        }
        row++;
    }
    file.close();
}


void MyWidget::on_pushButton_4_clicked()
{
    close();
}


