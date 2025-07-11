/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *username;
    QLabel *first_name;
    QLabel *last_name;
    QLabel *password;
    QLabel *category;
    QLabel *dob;
    QLineEdit *lEusername;
    QLineEdit *LEpassword;
    QLineEdit *LElastname;
    QLineEdit *LEfirstname;
    QLineEdit *LEcategory;
    QLineEdit *LEdob;
    QPushButton *okay;
    QPushButton *clear;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 808);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        username = new QLabel(centralwidget);
        username->setObjectName("username");
        username->setGeometry(QRect(10, 50, 81, 19));
        first_name = new QLabel(centralwidget);
        first_name->setObjectName("first_name");
        first_name->setGeometry(QRect(10, 200, 81, 19));
        last_name = new QLabel(centralwidget);
        last_name->setObjectName("last_name");
        last_name->setGeometry(QRect(10, 150, 81, 19));
        password = new QLabel(centralwidget);
        password->setObjectName("password");
        password->setGeometry(QRect(10, 100, 71, 19));
        category = new QLabel(centralwidget);
        category->setObjectName("category");
        category->setGeometry(QRect(10, 250, 70, 19));
        dob = new QLabel(centralwidget);
        dob->setObjectName("dob");
        dob->setGeometry(QRect(10, 300, 101, 19));
        lEusername = new QLineEdit(centralwidget);
        lEusername->setObjectName("lEusername");
        lEusername->setGeometry(QRect(120, 50, 113, 27));
        LEpassword = new QLineEdit(centralwidget);
        LEpassword->setObjectName("LEpassword");
        LEpassword->setGeometry(QRect(120, 100, 113, 27));
        LElastname = new QLineEdit(centralwidget);
        LElastname->setObjectName("LElastname");
        LElastname->setGeometry(QRect(120, 150, 113, 27));
        LEfirstname = new QLineEdit(centralwidget);
        LEfirstname->setObjectName("LEfirstname");
        LEfirstname->setGeometry(QRect(120, 200, 113, 27));
        LEcategory = new QLineEdit(centralwidget);
        LEcategory->setObjectName("LEcategory");
        LEcategory->setGeometry(QRect(120, 250, 113, 27));
        LEdob = new QLineEdit(centralwidget);
        LEdob->setObjectName("LEdob");
        LEdob->setGeometry(QRect(120, 300, 113, 27));
        okay = new QPushButton(centralwidget);
        okay->setObjectName("okay");
        okay->setGeometry(QRect(0, 390, 96, 27));
        clear = new QPushButton(centralwidget);
        clear->setObjectName("clear");
        clear->setGeometry(QRect(230, 390, 96, 27));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        username->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        first_name->setText(QCoreApplication::translate("MainWindow", "First Name", nullptr));
        last_name->setText(QCoreApplication::translate("MainWindow", "Last Name", nullptr));
        password->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        category->setText(QCoreApplication::translate("MainWindow", "Category", nullptr));
        dob->setText(QCoreApplication::translate("MainWindow", "Date Of Birth", nullptr));
        okay->setText(QCoreApplication::translate("MainWindow", "Okay", nullptr));
        clear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
