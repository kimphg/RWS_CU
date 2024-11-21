#include "dialogconfig.h"
#include "ui_dialogconfig.h"

DialogConfig::DialogConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfig)
{
    ui->setupUi(this);
    Reload();
    ui->pushButton_save->setEnabled(false);
}

DialogConfig::~DialogConfig()
{
    delete ui;
}
void DialogConfig::Reload()
{
    CConfig::readFile();
    int nItems = CConfig::mHashData.size();
    ui->tableWidget->setRowCount(nItems);
    int rowcount = 0;
    for(QHash<QString ,QString>::iterator i=CConfig::mHashData.begin();i!=CConfig::mHashData.end();++i)
    {
        QString id = i.key();
        QString value = i.value();
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(id));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(value));
        rowcount++;
    }
    ui->tableWidget->sortByColumn(0);
}
void DialogConfig::SaveConfig()
{
    int rowCount  = ui->tableWidget->rowCount();
    for (int i=0;i<rowCount;i++)
    {
        QString key =  ui->tableWidget->item(i,0)->text();
        QString value = ui->tableWidget->item(i,1)->text();
        CConfig::setValue(key,value);

    }
    CConfig::SaveAndSetConfigAsDefault();
}
void DialogConfig::on_pushButton_load_clicked()
{
    Reload();
}

void DialogConfig::on_pushButton_save_clicked()
{

    SaveConfig();
    this->accept();
}

void DialogConfig::on_lineEdit_textChanged(const QString &arg1)
{
    if(ui->lineEdit->text()=="4444")ui->pushButton_save->setEnabled(true);
}
