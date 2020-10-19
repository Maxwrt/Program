#include "widget.h"
#include "ui_widget.h"
#include "xlsxworkbook.h"
#include "xlsxdocument.h"
#include <QFont>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QTableWidgetItem>
#include <QTextStream>
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <QMessageBox>
#include <QTextStream>
#include <QStyle>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    ui = new Ui::Widget;
    ui->setupUi(this);
    this->setWindowTitle(u8"计算代码");
    this->setWindowIcon(QIcon(":/icon.png"));
    mheadList << u8"文件名" << u8"类型" << u8"大小" << u8"总行数" << u8"代码行数" << u8"注释行数" << u8"空白行数" << u8"文件路径";
    mcolumnWidth << "100" << "80" << "80" << "90" << "100" << "100" << "100" << "150";
    mfileFilter = QStringLiteral("*.h *.cpp *.c *.java *.cs *.lua");

    connect(ui->pushButton_openfile, &QPushButton::clicked, this, [=]{
        QStringList files = QFileDialog::getOpenFileNames(this, u8"打开文件", QDir::currentPath(), "*.*;;*.h;;*.cpp;;*.c;;*.java;;*.cs;;*.lua");
        qDebug() << files.size();
        if (files.size() > 0)
        {
            foreach(auto file, files)
            {
                QFileInfo fileinfo(file);
                if (CheckFile(fileinfo.fileName()))
                {
                    mlistFiles.push_back(fileinfo.filePath());
                }
                else
                {
                    QMessageBox::information(this, u8"提示", u8"所选文件不是代码文件", u8"确定", u8"取消");
                }
            }
            if (mlistFiles.size() > 0)
            {
                qDebug() << files;
                CountCode(mlistFiles, OpType::openfile);
            }
        }
    });

    QStyle::SP_TrashIcon;
    connect(ui->pushButton_opendir, &QPushButton::clicked, this, [=]{
        QString dir = QFileDialog::getExistingDirectory(this, u8"打开文件", QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if (!dir.isEmpty())
        {
            qDebug() << dir;
            ui->lineEdit_dirname->setText(dir);
            CountCode(dir);
            CountCode(mlistFiles, OpType::opendir, dir);
        }
    });

    QString str = "wrt";
    str = str % "   0318" % u8" 王瑞亭" % u8"  三月十八";
    qDebug() << str;
}

Widget::~Widget()
{
    delete ui;
}


void WriteAllInfo(QXlsx::Worksheet *sheet, const QStringList& list)
{
    if (sheet)
    {
        int row = sheet->dimension().rowCount()+2;
        sheet->writeString(row, 1, u8"文件数:");
        sheet->writeString(row+1, 1, u8"字节数:");
        sheet->writeString(row+2, 1, u8"总行数:");
        sheet->writeString(row+3, 1, u8"代码行数:");
        sheet->writeString(row+4, 1, u8"注释行数:");
        sheet->writeString(row+5, 1, u8"空白行数:");

        for (int i=0; i<list.count(); i++)
            sheet->writeString(row+i, 2, list.at(i));
    }
}

void Widget::on_pushButton_exportfile_clicked()
{
    QHash<int, QStringList> datahash;
    if(ui->tableWidget->rowCount()>0)
    {
        QStringList rowlist;
        for (int i=0; i<ui->tableWidget->rowCount(); i++)
        {
            rowlist.clear();
            for (int j=0; j<ui->tableWidget->columnCount(); j++)
            {
                rowlist.push_back(ui->tableWidget->item(i ,j)->data(Qt::DisplayRole).toString());
            }
            datahash.insert(i, rowlist);
        }
    }
    if (datahash.count() > 0)
    {
        if (QFile::exists(QStringLiteral("代码信息工作簿.xlsx")))
        {
            QFile::remove(QStringLiteral("代码信息工作簿.xlsx"));
        }
        QXlsx::Document doc(QStringLiteral("代码信息工作簿.xlsx"));
        doc.addSheet(QStringLiteral("代码信息工作表"));

        QXlsx::Worksheet *infosheet = (QXlsx::Worksheet*)doc.sheet(QStringLiteral("代码信息工作表"));

        if (infosheet == nullptr)
        {
            qDebug(u8"创建工作表失败");
            return;
        }


        QXlsx::Format formate;
        formate.setTextWrap(true);
        formate.setHorizontalAlignment(QXlsx::Format::AlignHCenter);

        QHash<int, int> columnWidth;
        for (int i=0; i<mheadList.count(); i++)
        {
            infosheet->write(1, i+1, mheadList.at(i), formate);
            columnWidth.insert(i, QString(mheadList.at(i)).length());
        }

        QTextStream(stdout) << "\n";
        for(int i=0; i<datahash.count(); i++)
        {
            auto item = datahash.value(i);
            for(int j=0; j<item.count(); j++)
            {
                infosheet->write(i+2, j+1, item.at(j), formate);
                if (QString(item.at(j)).length() > columnWidth.value(j))
                {
                    columnWidth.insert(j, QString(item.at(j)).length());
                }
            }
        }

        QStringList otherdata;
        otherdata << ui->lineEdit_filenum->text();
        otherdata << ui->lineEdit_bytenum->text();
        otherdata << ui->lineEdit_totalline->text();
        otherdata << ui->lineEdit_codeline->text();
        otherdata << ui->lineEdit_commentnum->text();
        otherdata << ui->lineEdit_blanknum->text();

        WriteAllInfo(infosheet, otherdata);
        for (int i=0; i<mheadList.count(); i++)
        {
            if (columnWidth.value(i) <= 4 )
            {
                infosheet->setColumnWidth(i+1, i+1, columnWidth.value(i) * 4.00);
                continue;
            }
            infosheet->setColumnWidth(i+1, i+1, columnWidth.value(i) * 2.00);
        }

        doc.save();
        QMessageBox::information(this, u8"提示", u8"导出成功", u8"确定", u8"取消");
        return;
    }
    QMessageBox::information(this, u8"提示", u8"表格中没有数据", u8"确定", u8"取消");
}

void Widget::on_pushButton_clear_clicked()
{
    ui->tableWidget->setRowCount(0);
    ui->lineEdit_filenum->clear();
    ui->lineEdit_bytenum->clear();
    ui->lineEdit_totalline->clear();
    ui->lineEdit_codeline->clear();
    ui->lineEdit_commentnum->clear();
    ui->lineEdit_blanknum->clear();
    ui->label_blanklineper->clear();
    ui->label_codelineper->clear();
    ui->label_commentper->clear();
    ui->lineEdit_filename->clear();
    ui->lineEdit_dirname->clear();
}


void Widget::ShowWidget()
{
    Init();
    showNormal();
}

void Widget::Init()
{
    qDebug(u8"初始化开始");
    InitTableWidget();
    InitOtherWidget();
    qDebug(u8"初始化结束");
}

void Widget::InitTableWidget()
{
    ui->tableWidget->setColumnCount(mheadList.count());
    ui->tableWidget->setHorizontalHeaderLabels(mheadList);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(20);
    ui->tableWidget->verticalHeader()->setHighlightSections(false);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setHighlightSections(false);

    for(int i=0; i<mcolumnWidth.count(); i++)
    {
        ui->tableWidget->setColumnWidth(i, QString(mcolumnWidth.at(i)).toInt());
    }
}

void Widget::InitOtherWidget()
{
    ui->lineEdit_filenum->setStyleSheet("color:#17A086;");
    ui->lineEdit_bytenum->setStyleSheet("color:#CA5AA6;");
    ui->lineEdit_totalline->setStyleSheet("color:#CD1B19;");

    ui->lineEdit_codeline->setStyleSheet("color:#22A3A9;");
    ui->lineEdit_commentnum->setStyleSheet("color:#D64D54");
    ui->lineEdit_blanknum->setStyleSheet("color:#A279C5;");

    QFont font;
    font.setBold(true);
    if (font.pointSize() > 0)
    {
        font.setPointSize(font.pointSize() + 1);
    }
    else
    {
        font.setPixelSize(font.pixelSize() + 2);
    }

    ui->lineEdit_filenum->setFont(font);
    ui->lineEdit_bytenum->setFont(font);
    ui->lineEdit_totalline->setFont(font);

    ui->lineEdit_codeline->setFont(font);
    ui->lineEdit_commentnum->setFont(font);
    ui->lineEdit_blanknum->setFont(font);

    ui->lineEdit_filter->setPlaceholderText(mfileFilter);
}

bool Widget::CheckFile(const QString& filename)
{
    if (filename.startsWith("moc_") || filename.startsWith("qrc_") || filename.startsWith("ui_"))
    {
        return false;
    }

    QFileInfo fileinfo(filename);
    return mfileFilter.split(' ').contains(QString("*.") + fileinfo.suffix());
}

void Widget::CountCode(const QString& filename)
{
    if (filename.isEmpty())
    {
        qDebug(u8"字符串为空");
        return;
    }

    QDir dir(filename);
    for(auto file : dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot))
    {
        if (file.isFile())
        {
            if (CheckFile(file.fileName()))
            {
                mlistFiles.push_back(file.filePath());
            }
        }

        if (file.isDir())
        {
            CountCode(file.filePath());
        }
    }
}

void Widget::CountCode(const QStringList& filelist, OpType type, QString dir)
{
    if (filelist.isEmpty())
    {
        qDebug(u8"文件列表为空");
        return;
    }

    int sumbyte = 0;
    int sumline = 0;
    int sumcode = 0;
    int sumblank = 0;
    int sumcomment = 0;

    on_pushButton_clear_clicked();
    ui->tableWidget->setRowCount(filelist.size());

    switch(type)
    {
    case OpType::openfile:
        ui->lineEdit_filename->setText(filelist.join('~'));
        break;
    case OpType::opendir:
        ui->lineEdit_dirname->setText(dir);
    }
    for(int i=0; i<filelist.size(); i++)
    {
        auto filename = filelist.at(i);
        QFileInfo fileinfo(filename);
        int codeline = 0;
        int commentline = 0;
        int blankline = 0;


        CountCode(filename, codeline, commentline, blankline);

        QList<QTableWidgetItem*> list;

        list.clear();
        QTableWidgetItem *filenameItem = new QTableWidgetItem;
        filenameItem->setText(fileinfo.baseName());
        filenameItem->setTextAlignment(Qt::AlignCenter);
        list.push_back(filenameItem);


        QTableWidgetItem *filetypeItem = new QTableWidgetItem;
        filetypeItem->setText("." + fileinfo.suffix());
        filetypeItem->setTextAlignment(Qt::AlignCenter);
        list.push_back(filetypeItem);

        QTableWidgetItem *filesizeItem = new QTableWidgetItem;
        filesizeItem->setText(QString::number(fileinfo.size()));
        filesizeItem->setTextAlignment(Qt::AlignCenter);
        list.push_back(filesizeItem);

        QTableWidgetItem *totallineItem = new QTableWidgetItem;
        totallineItem->setText(QString::number(codeline + commentline + blankline));
        totallineItem->setTextAlignment(Qt::AlignCenter);
        list.push_back(totallineItem);

        QTableWidgetItem *codelineItem = new QTableWidgetItem;
        codelineItem->setText(QString::number(codeline));
        codelineItem->setTextAlignment(Qt::AlignCenter);
        list.push_back(codelineItem);

        QTableWidgetItem *commentlineItem = new QTableWidgetItem;
        commentlineItem->setText(QString::number(commentline));
        commentlineItem->setTextAlignment(Qt::AlignCenter);
        list.push_back(commentlineItem);

        QTableWidgetItem *blanklineItem = new QTableWidgetItem;
        blanklineItem->setText(QString::number(blankline));
        blanklineItem->setTextAlignment(Qt::AlignCenter);
        list.push_back(blanklineItem);

        QTableWidgetItem *fileptahItem = new QTableWidgetItem;
        fileptahItem->setText(fileinfo.path());
        fileptahItem->setTextAlignment(Qt::AlignCenter);
        list.push_back(fileptahItem);

        for (int j=0; j<list.size(); j++)
        {
            auto item = list.at(j);
            ui->tableWidget->setItem(i, j, item);
        }

        sumbyte += fileinfo.size();
        sumcode += codeline;
        sumcomment += commentline;
        sumblank += blankline;
        sumline +=  codeline + commentline + blankline;
    }

    ui->lineEdit_filenum->setText(QString::number(filelist.size()));
    ui->lineEdit_bytenum->setText(QString::number(sumbyte));
    ui->lineEdit_totalline->setText(QString::number(sumline));

    ui->lineEdit_codeline->setText(QString::number(sumcode));
    ui->lineEdit_commentnum->setText(QString::number(sumcomment));
    ui->lineEdit_blanknum->setText(QString::number(sumblank));

    if (sumcode > 0 && sumline > 0 && sumcode <= sumline)
    {
        double percent = 0.0;

        percent = (double)sumcode/sumline * 100;
        ui->label_codelineper->setText(QString("%1%").arg(percent, 5, 'f', 2));

        percent = (double)sumblank/sumline * 100;
        ui->label_blanklineper->setText(QString("%1%").arg(percent, 5, 'f', 2));

        percent = (double)sumcomment/sumline * 100;
        ui->label_commentper->setText(QString("%1%").arg(percent, 5, 'f', 2));
    }
    mlistFiles.clear();
}

void Widget::CountCode(const QString& filename, int &codeline, int &commentline, int &blankline)
{
    if (filename.isEmpty())
    {
        qDebug(u8"文件名为空");
        return;
    }

    if (!QFile::exists(filename))
    {
        qDebug() << u8"文件不存在" << filename;
        return;
    }

    QFile file(filename);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream read(&file);

        while(!read.atEnd())
        {
            QString linecontent = read.readLine();
            linecontent = linecontent.trimmed();

            bool flag = false;
            if (linecontent.startsWith("/*") || linecontent.startsWith("--[["))
            {
                flag = true;
            }
            if (!flag)
            {
                if (linecontent.startsWith("//") || linecontent.startsWith("--"))
                {
                    commentline++;
                }
                else if (linecontent.isEmpty())
                {
                    blankline++;
                }
                else
                {
                    codeline++;
                }
            }
            else
            {
                commentline++;
            }

            if (linecontent.endsWith("*/") || linecontent.endsWith("]]--"))
            {
                flag = false;
            }
        }
    }
    else
    {
        qDebug(u8"打开文件失败");
    }
    file.close();
}
