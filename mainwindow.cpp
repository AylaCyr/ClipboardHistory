#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QClipboard>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (!databaseManager.openDatabase())
    {
        ui->statusLabel->setText("状态：数据库打开失败");
    }
    else
    {
        const QStringList history = databaseManager.loadHistory();

        for (const QString& text : history)
        {
            ui->historyListWidget->addItem(text);
        }

        updateStatus();
    }

    QClipboard* clipboard = QApplication::clipboard();

    connect(clipboard, &QClipboard::dataChanged, this, [this, clipboard]()
    {
        QString text = clipboard->text();

        if (text.trimmed().isEmpty())
        {
            return;
        }

        if (!ui->historyListWidget->findItems(text, Qt::MatchExactly).isEmpty())
        {
            return;
        }

        if (!databaseManager.addHistory(text))
        {
            ui->statusLabel->setText("状态：历史记录保存失败");
            return;
        }

        ui->historyListWidget->insertItem(0, text);
        updateStatus();
    });

    connect(ui->deleteButton, &QPushButton::clicked, this, [this]()
    {
        int currentRow = ui->historyListWidget->currentRow();

        if (currentRow == -1)
        {
            return;
        }

        QListWidgetItem* item = ui->historyListWidget->item(currentRow);
        QString content = item->text();

        if (!databaseManager.deleteHistory(content))
        {
            ui->statusLabel->setText("状态：历史记录删除失败");
            return;
        }

        delete ui->historyListWidget->takeItem(currentRow);
        updateStatus();
    });

    connect(ui->clearButton, &QPushButton::clicked, this, [this]()
    {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "确认清空",
            "确定要清空所有剪贴板历史吗？",
            QMessageBox::Yes | QMessageBox::No);

        if (reply != QMessageBox::Yes)
        {
            return;
        }

        if (!databaseManager.clearHistory())
        {
            ui->statusLabel->setText("状态：历史记录清空失败");
            return;
        }

        ui->historyListWidget->clear();
        updateStatus();
    });

    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, [this](const QString& keyword)
    {
        for (int i = 0; i < ui->historyListWidget->count(); ++i)
        {
            QListWidgetItem* item = ui->historyListWidget->item(i);
            bool matches = item->text().contains(keyword, Qt::CaseInsensitive);
            item->setHidden(!matches);
        }
    });
}

void MainWindow::updateStatus()
{
    ui->statusLabel->setText(QString("状态：共 %1 条记录").arg(ui->historyListWidget->count()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
