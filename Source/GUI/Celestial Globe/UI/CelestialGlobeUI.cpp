#include "CelestialGlobeUI.h"
#include "../Internal/CG_GUID.c"

CCGUI::
CCGUI(
    QWidget        *pParent /* = 0 */,
    Qt::WFlags      Flags /* = 0 */
) :
    QMainWindow(pParent, Flags)
{
    LOGFONTW lf;

    ui.setupUi(this);

    setWindowTitle(QString::fromUtf16(L"ÐÇ³½Ö®¼ä"));

    SystemParametersInfoW(SPI_GETICONTITLELOGFONT, sizeof(lf), &lf, 0);
    QFont font(QApplication::font());

    font.setWeight(QFont::Normal);
    font.setStyleStrategy(QFont::PreferQuality);
    font.setFamily(QString::fromUtf16(lf.lfFaceName));

    QApplication::setFont(font);

    AllocConsole();

    BOOL b;

    connect(ui.actionFileExit, SIGNAL(triggered()), this, SLOT(close()));
    b = connect(ui.MenuAbout, SIGNAL(aboutToShow()), this, SLOT(About()));

    PrintConsoleW(L"%d\n", b);
}

CCGUI::~CCGUI()
{
}

void CCGUI::About()
{
    MessageBoxW((HWND)this->winId(), L"About", NULL, 64);
}


//////////////////////////////////////////////////////////////////////////

CCGUICtrl::
CCGUICtrl(
    interface ICGCoreBase   *pCore,
    ICGUnknown              *pUnknownOuter,
    LONG                     ArgumentCount /* = 0 */,
    LPSTR                   *ArgumentValue /* = NULL */
) :
    m_Application(*(PINT)&ArgumentCount, ArgumentValue),
    CCGUnknownImpl<CCGUICtrl>(pUnknownOuter)
{
    m_Core = pCore;
    m_UI.setAttribute(Qt::WA_DeleteOnClose, FALSE);
}

CGSTATUS CCGUICtrl::QueryInterface0(REFIID iid, PVOID *ppvObject)
{
    PVOID pvObject;

    if (iid == IID_UIMain)
    {
        pvObject = (ICGUIMain *)this;
    }
    else if (iid == IID_IUnknown)
    {
        pvObject = (ICGNonDelegatingUnknown *)this;
    }
    else
    {
        return STATUS_NOINTERFACE;
    }

    ((ICGUnknown *)pvObject)->AddRef();
    *ppvObject = pvObject;

    return STATUS_SUCCESS;
}

CGSTATUS CCGUICtrl::Create(ULONG X, ULONG Y, ULONG Width, ULONG Height)
{
    BOOL bCenter = (X == -1 && Y == -1);

    if (Width != 0 && Height != 0)
    {
        m_UI.setGeometry(X, Y, Width, Height);
    }
    else
    {
        RECT rcDesktop;

        if (SystemParametersInfoW(SPI_GETWORKAREA, 0, &rcDesktop, 0))
        {
            Width   = rcDesktop.right - rcDesktop.left;
            Height  = rcDesktop.bottom - rcDesktop.top;

            Width   = Width * 8 / 10;
            Height  = Height * 75 / 100;

            X = (rcDesktop.right - rcDesktop.left - Width) / 2;
            Y = (rcDesktop.bottom - rcDesktop.top - Height) / 2;

            m_UI.setGeometry(X, Y, Width, Height);
        }
    }

    if (bCenter)
        m_UI.centralWidget();

    m_UI.setMinimumSize(m_UI.size());

    return STATUS_SUCCESS;
}

CGSTATUS CCGUICtrl::Show()
{
    m_UI.show();
    return STATUS_SUCCESS;
}

CGSTATUS CCGUICtrl::Execute()
{
    m_Application.exec();
    return STATUS_SUCCESS;
}

CGSTATUS CCGUICtrl::Destroy()
{
    m_UI.destroy(TRUE, TRUE);
    return STATUS_SUCCESS;
}
