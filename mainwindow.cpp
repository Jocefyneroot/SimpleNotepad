#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_save_clicked()
{
    QString filepath = QFileDialog::getSaveFileName(this, "Save File", QDir::homePath(), "Text Files (*.txt);;AllFiles (*)" );

    if (!filepath.isEmpty())
    {
        QFile file (filepath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream << ui->textEdit->toPlainText();
            file.close();

            QMessageBox::information(this, "Success", "File Saved successfully!");
        }else{
            QMessageBox::critical(this, "Error", "Unable to save the file.");
        }
    }

}


void MainWindow::on_open_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath(), "Text Files (*.txt);;All Files (*)");

    if (!filepath.isEmpty())
    {
        QFile file(filepath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            ui->textEdit->setPlainText(stream.readAll());
            file.close();

            QMessageBox::information(this, "Success", "FIle Opened Successfully!");
        } else
        {
            QMessageBox::critical(this, "Error", "Unable to open the file.");
        }
    }
}

