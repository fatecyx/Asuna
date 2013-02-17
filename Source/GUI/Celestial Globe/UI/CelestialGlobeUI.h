#ifndef CELESTIALGLOBEUI_H
#define CELESTIALGLOBEUI_H

#pragma warning(push, 3)

#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include "ui_CelestialGlobeUI.h"

#pragma warning(pop)

#include "../Internal/CG_Core.h"
#include "../Internal/CG_UI.h"
#include "../Internal/CG_Interface.h"

class CCGUICtrl;

class CCGUI : public QMainWindow
{
    Q_OBJECT

    friend CCGUICtrl;

public:
    CCGUI(QWidget *pParent = 0, Qt::WFlags Flags = 0);
    ~CCGUI();

protected slots:
    void About();

private:
    Ui::CCelestialGlobeUIClass ui;
};

class CCGUICtrl : public CCGUnknownImpl<CCGUICtrl>, public ICGUIMain
{
protected:
    QApplication    m_Application;
    CCGUI           m_UI;
    ICGCoreBase    *m_Core;

public:
    CCGUICtrl(
        interface ICGCoreBase   *pCore,
        ICGUnknown              *pUnknownOuter,
        LONG                     ArgumentCount = 0,
        LPSTR                   *ArgumentValue = NULL
    );

    CGSTATUS CG_METHOD_CALLTYPE Create(ULONG X, ULONG Y, ULONG Width, ULONG Height);
    CGSTATUS CG_METHOD_CALLTYPE Show();
    CGSTATUS CG_METHOD_CALLTYPE Execute();
    CGSTATUS CG_METHOD_CALLTYPE Destroy();

    CGSTATUS CG_METHOD_CALLTYPE QueryInterface0(REFIID iid, PVOID *ppvObject);

    CG_IUNKNOWN_IMPLEMENT(CCGUICtrl);
};

#endif // CELESTIALGLOBEUI_H
