/********************************************************************************
** Form generated from reading UI file 'CelestialGlobeUI.ui'
**
** Created: Wed Oct 26 11:29:30 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CELESTIALGLOBEUI_H
#define UI_CELESTIALGLOBEUI_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CCelestialGlobeUIClass
{
public:
    QAction *actionFileScriptList;
    QAction *actionFileExit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QTreeView *treeView;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *BtnPlay;
    QPushButton *BtnStop;
    QPushButton *BtnPause;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *BtnPrevFrame;
    QPushButton *BtnNextFrame;
    QPushButton *BtnRGB;
    QPushButton *BtnAlpha;
    QPushButton *BtnExtractOne;
    QPushButton *BtnExtractAll;
    QPushButton *BtnPluginList;
    QComboBox *ComboBoxExtractType;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *MenuFile;
    QMenu *MenuAbout;
    QMenu *MenuSettings;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CCelestialGlobeUIClass)
    {
        if (CCelestialGlobeUIClass->objectName().isEmpty())
            CCelestialGlobeUIClass->setObjectName(QString::fromUtf8("CCelestialGlobeUIClass"));
        CCelestialGlobeUIClass->resize(895, 638);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(9);
        CCelestialGlobeUIClass->setFont(font);
        CCelestialGlobeUIClass->setCursor(QCursor(Qt::ArrowCursor));
        CCelestialGlobeUIClass->setLocale(QLocale(QLocale::Chinese, QLocale::China));
        actionFileScriptList = new QAction(CCelestialGlobeUIClass);
        actionFileScriptList->setObjectName(QString::fromUtf8("actionFileScriptList"));
        actionFileScriptList->setFont(font);
        actionFileExit = new QAction(CCelestialGlobeUIClass);
        actionFileExit->setObjectName(QString::fromUtf8("actionFileExit"));
        actionFileExit->setFont(font);
        centralWidget = new QWidget(CCelestialGlobeUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        treeView = new QTreeView(centralWidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout_4->addWidget(treeView);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        BtnPlay = new QPushButton(centralWidget);
        BtnPlay->setObjectName(QString::fromUtf8("BtnPlay"));

        horizontalLayout_5->addWidget(BtnPlay);

        BtnStop = new QPushButton(centralWidget);
        BtnStop->setObjectName(QString::fromUtf8("BtnStop"));

        horizontalLayout_5->addWidget(BtnStop);

        BtnPause = new QPushButton(centralWidget);
        BtnPause->setObjectName(QString::fromUtf8("BtnPause"));

        horizontalLayout_5->addWidget(BtnPause);


        verticalLayout_4->addLayout(horizontalLayout_5);

        checkBox_3 = new QCheckBox(centralWidget);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        verticalLayout_4->addWidget(checkBox_3);

        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout_4->addWidget(checkBox);

        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        verticalLayout_4->addWidget(checkBox_2);


        horizontalLayout_6->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        BtnPrevFrame = new QPushButton(centralWidget);
        BtnPrevFrame->setObjectName(QString::fromUtf8("BtnPrevFrame"));

        horizontalLayout_3->addWidget(BtnPrevFrame);

        BtnNextFrame = new QPushButton(centralWidget);
        BtnNextFrame->setObjectName(QString::fromUtf8("BtnNextFrame"));

        horizontalLayout_3->addWidget(BtnNextFrame);

        BtnRGB = new QPushButton(centralWidget);
        BtnRGB->setObjectName(QString::fromUtf8("BtnRGB"));

        horizontalLayout_3->addWidget(BtnRGB);

        BtnAlpha = new QPushButton(centralWidget);
        BtnAlpha->setObjectName(QString::fromUtf8("BtnAlpha"));

        horizontalLayout_3->addWidget(BtnAlpha);

        BtnExtractOne = new QPushButton(centralWidget);
        BtnExtractOne->setObjectName(QString::fromUtf8("BtnExtractOne"));

        horizontalLayout_3->addWidget(BtnExtractOne);

        BtnExtractAll = new QPushButton(centralWidget);
        BtnExtractAll->setObjectName(QString::fromUtf8("BtnExtractAll"));

        horizontalLayout_3->addWidget(BtnExtractAll);

        BtnPluginList = new QPushButton(centralWidget);
        BtnPluginList->setObjectName(QString::fromUtf8("BtnPluginList"));

        horizontalLayout_3->addWidget(BtnPluginList);

        ComboBoxExtractType = new QComboBox(centralWidget);
        ComboBoxExtractType->setObjectName(QString::fromUtf8("ComboBoxExtractType"));

        horizontalLayout_3->addWidget(ComboBoxExtractType);


        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_6->addLayout(verticalLayout_3);

        horizontalLayout_6->setStretch(0, 10);
        horizontalLayout_6->setStretch(1, 33);

        gridLayout->addLayout(horizontalLayout_6, 0, 0, 1, 1);

        CCelestialGlobeUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CCelestialGlobeUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 895, 23));
        menuBar->setFont(font);
        MenuFile = new QMenu(menuBar);
        MenuFile->setObjectName(QString::fromUtf8("MenuFile"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Tahoma"));
        font1.setPointSize(10);
        MenuFile->setFont(font1);
        MenuAbout = new QMenu(menuBar);
        MenuAbout->setObjectName(QString::fromUtf8("MenuAbout"));
        MenuAbout->setFont(font1);
        MenuAbout->setLocale(QLocale(QLocale::Chinese, QLocale::China));
        MenuSettings = new QMenu(menuBar);
        MenuSettings->setObjectName(QString::fromUtf8("MenuSettings"));
        MenuSettings->setFont(font1);
        CCelestialGlobeUIClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(CCelestialGlobeUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Tahoma"));
        statusBar->setFont(font2);
        CCelestialGlobeUIClass->setStatusBar(statusBar);

        menuBar->addAction(MenuFile->menuAction());
        menuBar->addAction(MenuSettings->menuAction());
        menuBar->addAction(MenuAbout->menuAction());
        MenuFile->addAction(actionFileScriptList);
        MenuFile->addSeparator();
        MenuFile->addAction(actionFileExit);

        retranslateUi(CCelestialGlobeUIClass);

        QMetaObject::connectSlotsByName(CCelestialGlobeUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *CCelestialGlobeUIClass)
    {
        CCelestialGlobeUIClass->setWindowTitle(QApplication::translate("CCelestialGlobeUIClass", "CCelestialGlobeUI", 0, QApplication::UnicodeUTF8));
        actionFileScriptList->setText(QApplication::translate("CCelestialGlobeUIClass", "\350\204\232\346\234\254\345\210\227\350\241\250(&I)", 0, QApplication::UnicodeUTF8));
        actionFileScriptList->setIconText(QApplication::translate("CCelestialGlobeUIClass", "\350\204\232\346\234\254\345\210\227\350\241\250(I)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionFileScriptList->setToolTip(QApplication::translate("CCelestialGlobeUIClass", "\350\204\232\346\234\254\345\210\227\350\241\250(I)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionFileScriptList->setShortcut(QApplication::translate("CCelestialGlobeUIClass", "Ctrl+I", 0, QApplication::UnicodeUTF8));
        actionFileExit->setText(QApplication::translate("CCelestialGlobeUIClass", "\351\200\200\345\207\272(&X)", 0, QApplication::UnicodeUTF8));
        actionFileExit->setShortcut(QApplication::translate("CCelestialGlobeUIClass", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        BtnPlay->setText(QApplication::translate("CCelestialGlobeUIClass", "\346\222\255\346\224\276(&5)", 0, QApplication::UnicodeUTF8));
        BtnStop->setText(QApplication::translate("CCelestialGlobeUIClass", "\345\201\234\346\255\242(&6)", 0, QApplication::UnicodeUTF8));
        BtnPause->setText(QApplication::translate("CCelestialGlobeUIClass", "\346\232\202\345\201\234(&7)", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("CCelestialGlobeUIClass", "CheckBox", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("CCelestialGlobeUIClass", "CheckBox", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("CCelestialGlobeUIClass", "CheckBox", 0, QApplication::UnicodeUTF8));
        BtnPrevFrame->setText(QApplication::translate("CCelestialGlobeUIClass", "\344\270\212\344\270\200\345\270\247(&1)", 0, QApplication::UnicodeUTF8));
        BtnNextFrame->setText(QApplication::translate("CCelestialGlobeUIClass", "\344\270\213\344\270\200\345\270\247(&2)", 0, QApplication::UnicodeUTF8));
        BtnRGB->setText(QApplication::translate("CCelestialGlobeUIClass", "RBG(&3)", 0, QApplication::UnicodeUTF8));
        BtnAlpha->setText(QApplication::translate("CCelestialGlobeUIClass", "Alpha(&4)", 0, QApplication::UnicodeUTF8));
        BtnExtractOne->setText(QApplication::translate("CCelestialGlobeUIClass", "\345\257\274\345\207\272\346\226\207\344\273\266(&E)", 0, QApplication::UnicodeUTF8));
        BtnExtractAll->setText(QApplication::translate("CCelestialGlobeUIClass", "\345\205\250\351\203\250\345\257\274\345\207\272(&U)", 0, QApplication::UnicodeUTF8));
        BtnPluginList->setText(QApplication::translate("CCelestialGlobeUIClass", "\346\217\222\344\273\266\345\210\227\350\241\250(&P)", 0, QApplication::UnicodeUTF8));
        ComboBoxExtractType->clear();
        ComboBoxExtractType->insertItems(0, QStringList()
         << QApplication::translate("CCelestialGlobeUIClass", "BMP", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CCelestialGlobeUIClass", "PNG", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CCelestialGlobeUIClass", "JPG", 0, QApplication::UnicodeUTF8)
        );
        MenuFile->setTitle(QApplication::translate("CCelestialGlobeUIClass", "\346\226\207\344\273\266(&F)", 0, QApplication::UnicodeUTF8));
        MenuAbout->setTitle(QApplication::translate("CCelestialGlobeUIClass", "\345\205\263\344\272\216(&A)", 0, QApplication::UnicodeUTF8));
        MenuSettings->setTitle(QApplication::translate("CCelestialGlobeUIClass", "\350\256\276\347\275\256(&S)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CCelestialGlobeUIClass: public Ui_CCelestialGlobeUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CELESTIALGLOBEUI_H
