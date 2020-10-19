#include "dlgitem.h"
#include "ui_dlgitem.h"
#include "basefunction.h"
#include <QDebug>
#include <QCloseEvent>
DlgItem::DlgItem(PCustomer item,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgItem)
{
    ui->setupUi(this);

    initCombo();
    QFont font(QStringLiteral("Microsoft YaHei"), 10, 75);
    ui->labelTip->setFont(font);
    ui->labelTip->setStyleSheet(QStringLiteral("QLabel{color:red;}"));

    headerList<<tr("contact")<<tr("job")<<tr("tel")<<tr("tax")<<tr("email")<<tr("old");
    ui->tableWidget->setRowCount(20);
    ui->tableWidget->setColumnCount(headerList.count());
    ui->tableWidget->setHorizontalHeaderLabels(headerList);
    for(int i=0;i<20;i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(""));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(""));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(""));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(""));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(""));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(""));
    }

    mItem = item;
    if(mItem)
    {
        //修改
        ui->btnAdd->setText(tr("edit"));

        ui->edit1->setText(mItem->name);
        ui->combo1->setCurrentIndex(mItem->type);
        ui->combo2->setCurrentIndex(mItem->area);
        on_combo2_currentTextChanged(ui->combo2->currentText());
        ui->combo3->setCurrentText(Province2String(mItem->province));
        ui->edit2->setText(mItem->city);
        ui->edit3->setText(mItem->address);
        ui->edit4->setText(mItem->site);
        ui->textEdit->setText(mItem->buy);
        ui->textEdit2->setText(mItem->research);
        ui->textEdit3->setText(mItem->remark);

        QStringList all = mItem->contact.split(";");
        for(int i=0;i<all.size();i++)
        {
            QStringList row = all[i].split(",");
            if(row.size() >= 6)
            {
                //bool bRed = !row[5].isEmpty();
                ui->tableWidget->item(i,0)->setText(row[0]);
                ui->tableWidget->item(i,1)->setText(row[1]);
                ui->tableWidget->item(i,2)->setText(row[2]);
                ui->tableWidget->item(i,3)->setText(row[3]);
                ui->tableWidget->item(i,4)->setText(row[4]);
                ui->tableWidget->item(i,5)->setText(row[5]);
                if(!row[5].isEmpty())
                {
                    ui->tableWidget->item(i,0)->setBackground(Qt::red);
                    ui->tableWidget->item(i,1)->setBackground(Qt::red);
                    ui->tableWidget->item(i,2)->setBackground(Qt::red);
                    ui->tableWidget->item(i,3)->setBackground(Qt::red);
                    ui->tableWidget->item(i,4)->setBackground(Qt::red);
                    ui->tableWidget->item(i,5)->setBackground(Qt::red);
                }
            }
        }
    }
}

void DlgItem::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    accept();
}
DlgItem::~DlgItem()
{
    qDebug()<<u8"回收DlgItem";
    delete ui;
}

void DlgItem::initCombo()
{
    mAllTypeList<<tr("Alltype")<<tr("Enterprise")<<tr("Collage")<<tr("Search")<<tr("Proxy")<<tr("ForeignCompany")<<tr("Government")<<tr("Army")<<tr("ThirdParty");
    mAllAreaList<<tr("AllArea")<<tr("East")<<tr("South")<<tr("Middle")<<tr("North")<<tr("Other")<<tr("OutSide");
    mAllProvinceList<<tr("ShangDong")<<tr("ZheJiang")<<tr("JiangSu")<<tr("AnHui")<<tr("ShangHai")<<tr("FuJian")
                    <<tr("GuangDong")<<tr("GuangXi")<<tr("HaiNan")
                    <<tr("HuBei")<<tr("HuNan")<<tr("HeNan")<<tr("JiangXi")
                    <<tr("BeiJing")<<tr("TianJing")<<tr("HeBei")<<tr("ShangXi")<<tr("NeiMeng")
                    <<tr("NingXia")<<tr("XinJiang")<<tr("QingHai")<<tr("ShanXi")<<tr("GanSu")<<tr("SiChuan")<<tr("YunNan")
                    <<tr("GuiZhou")<<tr("XiZang")<<tr("ChongQin")<<tr("LiaoNing")<<tr("JiLin")<<tr("HeiLongJiang");

    ui->combo1->addItems(mAllTypeList);
    ui->combo2->addItems(mAllAreaList);
    ui->combo3->addItems(mAllProvinceList);

    ui->combo1->setCurrentIndex(0);
    ui->combo2->setCurrentIndex(0);
    ui->combo3->setCurrentIndex(0);
}

void DlgItem::on_btnAdd_clicked()
{
    if(ui->edit1->text().isEmpty())
    {
        ui->labelTip->setText(tr("companyname cannot be empty"));
        BaseFunction::delay(1);
        ui->labelTip->clear();
        return;
    }
    PCustomer p = new Customer;
    p->name = ui->edit1->text();
    p->type = ui->combo1->currentIndex();
    p->area = ui->combo2->currentIndex();
    p->province = String2Province(ui->combo3->currentText());
    p->city = ui->edit2->text();
    p->address = ui->edit3->text();
    p->site = ui->edit4->text();
    p->buy = ui->textEdit->toPlainText();
    p->research = ui->textEdit2->toPlainText();
    p->remark = ui->textEdit3->toPlainText();

    QString sAll = "";
    QString s = "";
    int columns = ui->tableWidget->columnCount();
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        if(ui->tableWidget->item(i,0)->text().isEmpty())
        {
            continue;
        }
        for(int j=0;j<columns;j++)
        {
            //,和;是用来分隔的标记，禁止用户输入这2个符号，如果不小心输了，程序也替换成空格
            s = ui->tableWidget->item(i,j)->text();
            s.replace(","," ");
            s.replace(";"," ");
            sAll += s;
            if(j == columns-1)
            {
                sAll += ";";
            }
            else
            {
                sAll += ",";
            }
        }
    }
    p->contact = sAll;

    if(mItem)
    {
        //修改
        mItem->name = p->name;
        mItem->type = p->type;
        mItem->area = p->area;
        mItem->province = p->province;
        mItem->city = p->city;
        mItem->address = p->address;
        mItem->site = p->site;
        mItem->contact = p->contact;
        mItem->buy = p->buy;
        mItem->research = p->research;
        mItem->remark = p->remark;
        accept();
    }
    else
    {
        //新增
        emit sigAddItem(p);
        qDebug().noquote()<<u8"信号返回，继续执行后续程序";
        ui->edit1->setText("");
        ui->edit2->setText("");
        ui->edit3->setText("");
        ui->edit4->setText("");
        ui->textEdit->setText("");
        ui->textEdit2->setText("");
        ui->textEdit3->setText("");
        for(int i=0;i<20;i++)
        {
            ui->tableWidget->item(i,0)->setText("");
            ui->tableWidget->item(i,1)->setText("");
            ui->tableWidget->item(i,2)->setText("");
            ui->tableWidget->item(i,3)->setText("");
            ui->tableWidget->item(i,4)->setText("");
            ui->tableWidget->item(i,5)->setText("");
        }
        ui->edit1->setFocus();
        ui->labelTip->setText(tr("insert success!"));
    }
    BaseFunction::delay(1);
    ui->labelTip->clear();
    return;
}

void DlgItem::on_btnCancel_clicked()
{
    reject();
}

int DlgItem::String2Province(QString s)
{
    return mAllProvinceList.indexOf(s);
}


QString DlgItem::Province2String(int n)
{
    if(n>=0 && n<mAllProvinceList.size())
    {
        return mAllProvinceList.at(n);
    }
    return "";
}


void DlgItem::on_combo2_currentTextChanged(const QString &text)
{
    ui->combo3->clear();
    if(text == tr("East"))
    {
        ui->combo3->addItems(QStringList()<<tr("ShangDong")<<tr("ZheJiang")<<tr("JiangSu")<<tr("AnHui")<<tr("ShangHai")<<tr("FuJian"));
    }
    else if(text == tr("South"))
    {
        ui->combo3->addItems(QStringList()<<tr("GuangDong")<<tr("GuangXi")<<tr("HaiNan"));
    }
    else if(text == tr("Middle"))
    {
        ui->combo3->addItems(QStringList()<<tr("HuBei")<<tr("HuNan")<<tr("HeNan")<<tr("JiangXi"));
    }
    else if(text == tr("North"))
    {
        ui->combo3->addItems(QStringList()<<tr("BeiJing")<<tr("TianJing")<<tr("HeBei")<<tr("ShangXi")<<tr("NeiMeng"));
    }
    else if(text == tr("Other"))
    {
        ui->combo3->addItems(QStringList()<<tr("NingXia")<<tr("XinJiang")<<tr("QingHai")<<tr("ShanXi")<<tr("GanSu")<<tr("SiChuan")<<tr("YunNan")
                             <<tr("GuiZhou")<<tr("XiZang")<<tr("ChongQin")<<tr("LiaoNing")<<tr("JiLin")<<tr("HeiLongJiang"));
    }
    else if(text == tr("AllArea"))
    {
        ui->combo3->addItems(mAllProvinceList);
    }
    return;
}
