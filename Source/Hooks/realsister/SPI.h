/*
   SPI import module base class
   Copyright (C) 1997 H.Mutsuki
   http://www2f.biglobe.ne.jp/~kana/spi_api/index.html
*/

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _INC_SPI
#define _INC_SPI	/* #defined if spi.h has been included */

#include <Windows.h>

/*****************************************************************
	SUSIEの内部依存構造体
*****************************************************************/
#pragma pack(push,1)
typedef struct
{
	LONG left,top;		// 画像を展開する位置
	LONG width;			// 画像の幅(pixel)
	LONG height;		// 画像の高さ(pixel)
	WORD x_density;		// 画素の水平方向密度
	WORD y_density;		// 画素の垂直方向密度
	SHORT colorDepth;	// １画素当たりのbit数
	HLOCAL hInfo;		// 画像内のテキスト情報
} TSpiPictureInfo;

typedef struct
{
	BYTE method[8];		// 圧縮法の種類
	DWORD position;		// ファイル上での位置
	DWORD compsize;		// 圧縮されたサイズ
	DWORD filesize;		// 元のファイルサイズ
	time_t timestamp;	// ファイルの更新日時
	char path[200];		// 相対パス
	char filename[200];	// ファイルネーム
	DWORD crc;			// CRC
}  TSpiArchiveInfo;
#pragma pack(pop)

// コールバック関数
typedef int (CALLBACK* PROGRESSCALLBACK)(int nNum, int nDenom, long lData);

// リザルトコード
// Struct Code
#define	SPI_OK					0		// 正常終了
#define	SPIERR_UNSUPPORTED		-1		// その機能はインプリメントされていない
#define	SPIERR_CANCELED			1		// コールバック関数が非0を返したので展開を中止した
#define	SPIERR_UNKNOWNFORMAT	2		// 未知のフォーマット
#define	SPIERR_INVALIDDATA		3		// データが壊れている
#define	SPIERR_OUTOFMEMORY		4		// メモリーが確保出来ない
#define	SPIERR_INVALIDMEMORY	5		// メモリーエラー（Lock出来ない、等）
#define	SPIERR_FILEREAD			6		// ファイルリードエラー
#define	SPIERR_RESERVED			7		// 予約
#define	SPIERR_INTERNAL			8		// 内部エラー

// flag
// 追加情報 「xxxx xxxx xxxx xSSS」(下位3bitが意味を持つ) SSSは入力の種類を意味する  
// 追加情報 「xxxx xDDD xxxx xSSS」(ビットフラグとして見る) 
//      SSS        0  Disk File
// (入力の形式)    1  Memroy Image  
//
//      DDD        0  Disk File
// (出力先の形式)  1  Memroy Image  

#define SPI_IN_MEM_FLAG         0x7
#define SPI_IN_DISK_FLAG        0x0
#define SPI_OUT_MEM_FLAG        0x700
#define SPI_OUT_DISK_FLAG       0x000
#define SPI_INPUT_DISK(x)      (BOOL)!((x) & SPI_IN_MEM_FLAG)
#define SPI_OUTPUT_DISK(x)     (BOOL)!((x) & SPI_OUT_MEM_FLAG)
#define SPI_INPUT_MEM(x)       (BOOL)((x) & SPI_IN_MEM_FLAG)
#define SPI_OUTPUT_MEM(x)      (BOOL)((x) & SPI_OUT_MEM_FLAG)

/*****************************************************************
	コールバックAPI
*****************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
// Plug-inに関する情報を得る
int WINAPI GetPluginInfo(int infono, LPSTR buf,int buflen);

// 展開可能な(対応している)ファイル形式か調べる。
int WINAPI IsSupported(LPSTR filename,DWORD dw);

// 画像ファイルに関する情報を得る
int WINAPI GetPictureInfo(LPSTR buf, LONG len, UINT flag, TSpiPictureInfo *lpInfo);

// 画像を展開する
int WINAPI GetPicture(LPSTR buf, LONG len, UINT flag,
			   HANDLE *pHBInfo, HANDLE *pHBm,
			   PROGRESSCALLBACK lpProgressCallback, LONG lData);

// プレビュー·カタログ表示用画像縮小展開ルーティン
int WINAPI GetPreview(LPSTR buf, LONG len, UINT flag,
			   HANDLE *pHBInfo, HANDLE *pHBm,
			   PROGRESSCALLBACK lpProgressCallback, LONG lData);

// アーカイブ内のすべてのファイルの情報を取得する
int WINAPI GetArchiveInfo(LPSTR buf, LONG len, UINT flag, HLOCAL *lphInf);

// アーカイブ内の指定したファイルの情報を取得する
int WINAPI GetFileInfo(LPSTR buf, LONG len, LPSTR filename,
				UINT flag, TSpiArchiveInfo *lpInfo);

// アーカイブ内のファイルを取得する
int WINAPI GetFile(LPSTR src, LONG len, LPSTR dest, UINT flag,
			PROGRESSCALLBACK progressCallback, LONG lData);

// 設定ダイアログを実行
int WINAPI ConfigurationDlg(HWND parent, int fnc);

#ifdef __cplusplus
}
#endif

/*****************************************************************
	SPI 基底クラス(単にスタブを提供する)
*****************************************************************/
class CSpi
{
public:
	CSpi();
	virtual ~CSpi();

protected:
	void InitObject();
	void DeleteObject();
public:
	void RecycleObject();

public:
	virtual int GetPluginInfo(int infono, LPSTR buf, int buflen) = 0;
	virtual int IsSupported(LPSTR filename,DWORD dw) = 0;
	virtual int GetPictureInfo(LPSTR buf, LONG len, UINT flag, TSpiPictureInfo *lpInfo);
	virtual int GetPicture(LPSTR buf, LONG len, UINT flag, HANDLE *pHBInfo, HANDLE *pHBm, PROGRESSCALLBACK lpProgressCallback, LONG lData);
	virtual int GetPreview(LPSTR buf, LONG len, UINT flag, HANDLE *pHBInfo, HANDLE *pHBm, PROGRESSCALLBACK lpProgressCallback, LONG lData);
	virtual int GetArchiveInfo(LPSTR buf, LONG len, UINT flag, HLOCAL *lphInf);
	virtual int GetFileInfo(LPSTR buf, LONG len, LPSTR filename, UINT flag, TSpiArchiveInfo *lpInfo);
	virtual int GetFile(LPSTR src, LONG len, LPSTR dest, UINT flag, PROGRESSCALLBACK lpProgressCallback, LONG lData);
	virtual int ConfigurationDlg(HWND parent, int fnc);
};

/*****************************************************************
*****************************************************************/

#endif  /* _INC_SPI */

/* Local Variables:					*/
/* tab-width:4						*/
/* c-indent-level:4					*/
/* c-label-offset:-4				*/
/* c-continued-statement-offset:4	*/
/* file-coding-system:*sjis*dos		*/
/* End:								*/
