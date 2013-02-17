// FontsViewDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
int CALLBACK MyEnumFontProc(ENUMLOGFONTEX* lpelf,NEWTEXTMETRICEX* lpntm,DWORD nFontType,long lParam);



// CFontsViewDlg 对话框
class CFontsViewDlg : public CDialog
{
// 构造
public:
	CFontsViewDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FONTSVIEW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strEntered;
	CListBox m_ctlFontList;
	CString m_strFontName;
	CStatic m_ctlDisplay;
	afx_msg void OnBnClickedBexit();
private:
	void FillFontList(void);
public:
	afx_msg void OnEnChangeEentered();
private:
	void SetMyFont(void);
public:
	afx_msg void OnLbnSelchangeLfonts();
	CSliderCtrl m_slider_height;
	CSliderCtrl m_slider_bold;
	CSliderCtrl m_slider_angle;
	int m_intBold;
	int m_intAngle;
	BOOL m_bCheckItalic;
	BOOL m_bCheckReverse;
	int charLineW;
	int m_intScrollHPos,m_intScrollVPos;
	LPBITMAPINFO pbmpinfo;
	LPBITMAPFILEHEADER pfileinfo;
	LPBYTE pBuf;
    
	afx_msg void OnNMReleasedcaptureSliderBold(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMThemeChangedSliderBold(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderAngle(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_ctlCheckItalic;
	afx_msg void OnBnClickedCheckItalic();
	int m_intHeight;
	afx_msg void OnNMReleasedcaptureSliderHeight(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnStnClickedDisplay();
	afx_msg void OnClose();
	void FormBitmapInfo(int nWidth, int nHeight, int nBits);
	int m_intPixX;
	int m_intPixY;
	int m_intBits;
	void FormFileHeader(int nWidth, int nHeight,int nBits);
	afx_msg void OnBnClickedButtonSave();
	void ShowFontChar(CDC* pdc);
	CButton m_ctlBtnReverse;
	afx_msg void OnBnClickedCheckReverse();
	CScrollBar m_ctlScrollH;
	CScrollBar m_ctlScrollV;
	void ShowVHScrollBar(void);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CComboBox m_ctlComboNbits;
	afx_msg void OnCbnSelchangeComboNbits();
	afx_msg void OnEnChangeEditHeight();
	afx_msg void OnEnChangeEditBold();
	afx_msg void OnEnChangeEditAngle();
	CString m_strStatus;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEnChangeEditPixx();
};
