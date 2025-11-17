#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    QStringList colTitles;
    ui->tableWidget->setColumnCount(4);
}

MyWidget::~MyWidget()
{
    delete ui;
}
