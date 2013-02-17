#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/MERGE:.text=.Kaede /SECTION:.Kaede,EWR")
#pragma comment(linker, "/MERGE:.rdata=.Kaede")
#pragma comment(linker, "/MERGE:.data=.Kaede")

/* nwatowav : Visual Arts 系のゲームのデモで使われる nwa 形式の
**            ファイルを wav 形式に変換する
**
**     compile : gcc -O2 -o nwatowav nwatowav.cc
**     usage : nwatowav [nwa-file [outfile]]
**	       nwatowav [nwk-file [outfile]]
**     example : nwatowav HM06.nwa HM06.wav	# BGMファイル。HM06.wav に展開される
**		 nwatowav z2813.nwk z2813	# 音声ファイル。 z2813-100.wav などのファイル名で展開される
**		 nwatowav z0513.ovk z0513	# 音声ファイル。 z0513-100.ogg などのファイル名で展開される
**
**
** 2004.5.19 小松さん<s1100089@u-aizu.ac.jp> から CLANNAD の無圧縮nwa形式に対応する
**           パッチをいただいたので、適用しました。ありがとうございます。
** 2006.9.10 「智代アフター」の音声ファイル形式 (complevel = 5) をサポート
**	     .nwk という拡張子を持つファイルを受け取ると音声ファイルとして
**	     解釈、分割して展開するようにする
** 2007.7.28 「リトルバスターズ！」の音声ファイル形式 (*.ovk; ogg 連結型)
**		をサポート。.ovk という拡張子をもつファイルを受け取ると
**		音声ファイルとして解釈、分割して展開するようにする
**	     「リトルバスターズ！」のBGMファイルに多量のノイズが乗る問題も
**	     　解決（ランレングス圧縮の処理が不必要だった）
*/

/*
 * Copyright 2001-2007  jagarl / Kazunori Ueno <jagarl@creator.club.ne.jp>
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted.
 *
 * このプログラムの作者は jagarl です。
 *
 * このプログラム、及びコンパイルによって生成したバイナリは
 * プログラムを変更する、しないにかかわらず再配布可能です。
 * その際、上記 Copyright 表示を保持するなどの条件は課しま
 * せん。対応が面倒なのでバグ報告を除き、メールで連絡をする
 * などの必要もありません。ソースの一部を流用することを含め、
 * ご自由にお使いください。
 *
 * THIS SOFTWARE IS PROVIDED BY KAZUNORI 'jagarl' UENO ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL KAZUNORI UENO BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 * 
 */

/********************************************
**
**	nwa フォーマットについて
**
**		全体としては以下の構造を持つ
**		NWA Header
**		data offset index
**		data block<0>
**		data block<1>
**		...
**		data block<N>
**
**	NWA Header: ファイル先頭から 44 bytes
**		magic number などはないのでnwa ファイルかは
**		データの整合性から判断する必要がある
**		データは全て little endian で、
**		short(signed 2byte)または int(signed 4byte) である。
**
**		+00 short   channel 数(1/2)
**		+02 short   sample 一つあたりの bit 数(16)
**		+04 int     周波数(一秒あたりのデータ数)
**		+08 int     圧縮レベル：-1~5.2で最小のデータ、0で最大の復元度(-1は無圧縮rawデータとみなされる)
**		+12 int     ?
**		+16 int     ブロック数
**		+20 int     展開後のデータの大きさ(バイト単位)
**		+24 int     圧縮時のデータの大きさ(nwa ファイルの大きさ。バイト単位)
**		+28 int     サンプル数：展開後のデータ数(16bit dataなら short 単位==サンプル単位のデータの大きさ)
**		+32 int     データ１ブロックを展開した時のサンプル単位のデータ数
**		+36 int     最終ブロックを展開した時のサンプル単位のデータ数
**		+40 int     ?
**		
**	data offset index
**		全ブロック数 x 4 byte のデータ
**		それぞれ int のデータが全ブロック数続いている
**
**		データブロックの先頭を指すファイル先頭からの位置(オフセット)
**		が格納されている
**
**	data block
**		長さは可変。展開することで一定の大きさをもつデータに展開される。
**		データはDPCM形式。元 PCM データが a,b,c ならば (a),b-a, c-b と
**		いった差分データが、仮数3-5bit,指数3bitの形式で保存されている。
**		結果的に、16bit のデータが多くの場合 6-8bit で格納される。
**		仮数のビット数は圧縮レベル0で5bit、圧縮レベル2で3bitとなる。
**		以下、圧縮レベル2の場合について話を進める。
**		モノラルの場合：
**			+00 short  ブロック内の最初のデータ
**			+02- bit stream
**		ステレオの場合：
**			+00 short  左(?)チャンネルの最初のデータ
**			+02 short  右(?)チャンネルの最初のデータ
**			+04- bit stream
**
**		差分データの精度が高くないので各ブロックの先頭で
**		正確なデータにより補正される(？)
**
**	bit stream
**		little endian
**		+0 - +2 : 指数
**		+3 - +5 : 仮数
**		の形式。例えば a,b,c という8bitデータがあれば、
**		a&0x07 : データ１の指数
**		(a>>3)&0x07 : データ１の仮数(signed ; 
**		((b<<2)|(a>>6))&0x07 : データ２の指数
**		(b>>1)&0x07 : データ２の仮数
**		となる。
**		ただし、指数の値により仮数のbit数が変化することがある。
**		指数 = 1 - 6 の場合：
**			a=指数、b=仮数、p=前のデータとして、今回のデータd は
**			bの2bit目が立っている場合：
**				d = p - (b&3)<<(4+a)
**			立ってない場合：
**				d = p + (b&3)<<(4+a)
**		指数 = 0 の場合：仮数は存在しない(データは3bitとなる)
**			d = p
**			「智代アフター」の音声ファイル (complevel == 5) ではランレングス圧縮用に使われている。
**		指数 = 7
**			次の bit が立っている場合：
**				d = 0 (現在未使用)
**				(データは4bitとなる)
**			次の bit が立ってない場合：
**				complevel = 0,1,2:
**				   仮数 b = 6bit
**				   b の 5bit 目が立っている場合：
**					d = p - (b&0x1f)<<(4+7)
**				   立ってない場合：
**					d = p + (b&0x1f)<<(4+7)
**				   (データは10bitとなる)
**				complevel = 3,4,5:
**				   仮数 b = 8bit
**				   b の 7bit 目が立っている場合：
**					d = p - (b&0x7f)<<9
**				   立ってない場合：
**					d = p + (b&0x1f)<<9
**				   (データは10bitとなる)
**
**		圧縮レベルが異なる場合、たとえば圧縮レベル==0で
**			指数==1~6でdの最上位bitが立っている場合
**				d = p - (b&0x0f)<<(2+a)
**			指数==7でdの最上位bitが立っている場合
**				d = p - (b&0x7f)<<(2+7)
**				(b : 8bitなのでデータは12bitとなる)
**		のように、精度だけが変化するようになっている。
**
**	ヘッダ読み込みについてはNWAData::ReadHeader()参照
**	bit stream からのデータ展開については NWADecode()参照
**************************************************************
*/

// #define NDEBUG /* なぜか assertが入った方が速い、、、 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <direct.h>
#include <sys/stat.h>
#include <string.h>
#include "getmainargs.h"
#include "my_crtadd.h"

#ifdef WORDS_BIGENDIAN
#error Sorry, This program does not support BIG-ENDIAN system yet.
/* もし big endian のシステムに対応させる場合
** 以下の *_little_endian_* 及び
** getbits() 関数を変更する必要がある
*/
#endif

inline int read_little_endian_int(const char* buf) {
	return *(int*)buf;
}

inline int read_little_endian_short(const char* buf) {
	return *(short*)buf;
}

inline int write_little_endian_int(char* buf, int number) {
	int c = *(int*)buf; *(int*)buf = number; return c;
}

inline int write_little_endian_short(char* buf, int number) {
	int c = *(short*)buf; *(short*)buf = number; return c;
}
inline int getbits(const char*& data, int& shift, int bits) {
	if (shift > 8) { data++; shift-=8;}
	int ret = read_little_endian_short(data)>>shift;
	shift += bits;
	return ret & ((1<<bits)-1); /* mask */
}

/* 指定された形式のヘッダをつくる */
const char* make_wavheader(int size, int channels, int bps, int freq) {
	static char wavheader[0x2c] = {
		'R','I','F','F',
		0,0,0,0, /* +0x04: riff size*/
		'W','A','V','E',
		'f','m','t',' ',
		16,0,0,0, /* +0x10 : fmt size=0x10 */
		1, 0,    /* +0x14 : tag : pcm = 1 */
		2, 0,    /* +0x16 : channels */
		0,0,0,0, /* +0x18 : samples per second */
		0,0,0,0, /* +0x1c : average bytes per second */
		0,0,     /* +0x20 : block alignment */
		0,0,     /* +0x22 : bits per sample */
		'd','a','t','a',
		0,0,0,0};/* +0x28 : data size */
	write_little_endian_int(wavheader+0x04, size+0x24);
	write_little_endian_int(wavheader+0x28, size);
	write_little_endian_short(wavheader+0x16, channels);
	write_little_endian_short(wavheader+0x22, bps);
	write_little_endian_int(wavheader+0x18, freq);
	int byps = (bps+7)>>3;
	write_little_endian_int(wavheader+0x1c, freq*byps*channels);
	write_little_endian_short(wavheader+0x20, byps*channels);
	return wavheader;
}

/* NWA の bitstream展開に必要となる情報 */
class NWAInfo {
	int channels;
	int bps;
	int complevel;
	bool use_runlength;
public:
	NWAInfo(int c,int b,int cl) {
		channels=c;
		bps=b;
		complevel=cl;
		use_runlength = false;
		if (cl == 5) {
			use_runlength = true; // Tomoyo After (.nwk koe file)
			if (channels == 2) use_runlength = false; // BGM*.nwa in Little Busters!
		}
	}
	int Channels(void) const{return channels;}
	int Bps(void) const { return bps;}
	int CompLevel(void) const { return complevel;}
	int UseRunLength(void) const { return use_runlength; }
};

template<class NWAI> void NWADecode(const NWAI& info,const char* data, char* outdata, int datasize, int outdatasize) {
	int d[2];
	int i;
	int shift = 0;
	const char* dataend = data+datasize;
	/* 最初のデータを読み込む */
	if (info.Bps() == 8) {d[0] = *data++; datasize--;}
	else /* info.Bps() == 16 */ {d[0] = read_little_endian_short(data); data+=2; datasize-=2;}
	if (info.Channels() == 2) {
		if (info.Bps() == 8) {d[1] = *data++; datasize--;}
		else /* info.Bps() == 16 */ {d[1] = read_little_endian_short(data); data+=2; datasize-=2;}
	}
	int dsize = outdatasize / (info.Bps()/8);
	int flip_flag = 0; /* stereo 用 */
	int runlength = 0;
	for (i=0; i<dsize; i++) {
		if (data >= dataend) break;
		if (runlength == 0) { // コピーループ中でないならデータ読み込み
			int type = getbits(data, shift, 3);
			/* type により分岐：0, 1-6, 7 */
			if (type == 7) {
				/* 7 : 大きな差分 */
				/* RunLength() 有効時（CompLevel==5, 音声ファイル) では無効 */
				if (getbits(data, shift, 1) == 1) {
					d[flip_flag] = 0; /* 未使用 */
				} else {
					int BITS, SHIFT;
					if (info.CompLevel() >= 3) {
						BITS = 8;
						SHIFT = 9;
					} else {
						BITS = 8-info.CompLevel();
						SHIFT = 2+7+info.CompLevel();
					}
					const int MASK1 = (1<<(BITS-1));
					const int MASK2 = (1<<(BITS-1))-1;
					int b = getbits(data, shift, BITS);
					if (b&MASK1)
						d[flip_flag] -= (b&MASK2)<<SHIFT;
					else
						d[flip_flag] += (b&MASK2)<<SHIFT;
				}
			} else if (type != 0) {
				/* 1-6 : 通常の差分 */
				int BITS, SHIFT;
				if (info.CompLevel() >= 3) {
					BITS = info.CompLevel()+3;
					SHIFT = 1+type;
				} else {
					BITS = 5-info.CompLevel();
					SHIFT = 2+type+info.CompLevel();
				}
				const int MASK1 = (1<<(BITS-1));
				const int MASK2 = (1<<(BITS-1))-1;
				int b = getbits(data, shift, BITS);
				if (b&MASK1)
					d[flip_flag] -= (b&MASK2)<<SHIFT;
				else
					d[flip_flag] += (b&MASK2)<<SHIFT;
			} else { /* type == 0 */
				/* ランレングス圧縮なしの場合はなにもしない */
				if (info.UseRunLength() == 1) {
					/* ランレングス圧縮ありの場合 */
					runlength = getbits(data,shift,1);
					if (runlength==1) {
						runlength = getbits(data,shift,2);
						if (runlength == 3) {
							runlength = getbits(data, shift, 8);
						}
					}
				}
			}
		} else {
			runlength--;
		}
		if (info.Bps() == 8) {
			*outdata++ = d[flip_flag];
		} else {
			write_little_endian_short(outdata, d[flip_flag]);
			outdata += 2;
		}
		if (info.Channels() == 2) flip_flag ^= 1; /* channel 切り替え */
	}
	return;
};

class NWAData {
public:
	int channels;
	int bps; /* bits per sample */
	int freq; /* samples per second */
private:
	int complevel; /* compression level */
	int dummy; /* ? : 0x00 */
public:
	int blocks; /* block count */
	int datasize; /* all data size */
private:
	int compdatasize; /* compressed data size */
	int samplecount; /* all samples */
	int blocksize; /* samples per block */
	int restsize; /* samples of the last block */
	int dummy2; /* ? : 0x89 */
	int curblock;
	int* offsets;
	int offset_start;
	int filesize;
	char* tmpdata;
public:
	void ReadHeader(FILE* in, int file_size=-1);
	int CheckHeader(void); /* false: invalid true: valid */
	NWAData(void) {
		offsets = 0;
		tmpdata = 0;
	}
	~NWAData(void) {
		if (offsets) free(offsets);
		if (tmpdata) free(tmpdata);
	}
	int BlockLength(void) {
		if (complevel != -1) {
			if (offsets == 0) return false;
			if (tmpdata == 0) return false;
		}
		return blocksize * (bps/8);
	}
	/* data は BlockLength 以上の長さを持つこと
	** 返り値は作成したデータの長さ。終了時は 0。
	** エラー時は -1
	*/
	int Decode(FILE* in, char* data, int& skip_count);
	void Rewind(FILE* in);
};

void NWAData::ReadHeader(FILE* in, int _file_size) {
	char header[0x2c];
	struct _stat sb;
	int i;
	if (offsets) free(offsets);
	if (tmpdata) free(tmpdata);
	offsets = 0;
	tmpdata = 0;
	filesize = 0;
	offset_start = ftell(in);
	if (offset_start == -1) offset_start = 0;
	if (_file_size != -1) filesize = _file_size;
	curblock = -1;
	/* header 読み込み */
	if (in == 0 || feof(in) || ferror(in)) {
		fprintf(stderr,"invalid stream\n");
		return;
	}
	fread(header, 0x2c, 1, in);
	if (feof(in) || ferror(in)) {
		fprintf(stderr,"invalid stream\n");
		return;
	}
	channels = read_little_endian_short(header+0x00);
	bps = read_little_endian_short(header+0x02);
	freq = read_little_endian_int(header+0x04);
	complevel = read_little_endian_int(header+0x08);
	dummy = read_little_endian_int(header+0x0c);
	blocks = read_little_endian_int(header+0x10);
	datasize = read_little_endian_int(header+0x14);
	compdatasize = read_little_endian_int(header+0x18);
	samplecount = read_little_endian_int(header+0x1c);
	blocksize = read_little_endian_int(header+0x20);
	restsize = read_little_endian_int(header+0x24);
	dummy2 = read_little_endian_int(header+0x28);
	if (complevel == -1) {	/* 無圧縮rawデータ */
		/* 適当に決め打ちする */
		blocksize = 65536;
		restsize = (datasize % (blocksize * (bps/8))) / (bps/8);
		blocks = datasize / (blocksize * (bps/8)) + (restsize > 0 ? 1 : 0);
	}
	if (blocks <= 0 || blocks > 1000000) {
		/* １時間を超える曲ってのはないでしょ*/
		fprintf(stderr,"too large blocks : %d\n",blocks);
		return;
	}
	/* regular file なら filesize 読み込み */
	if (filesize == 0 && _fstat(fileno(in), &sb)==0 && (sb.st_mode&S_IFMT) == S_IFREG) {
		int pos = ftell(in);
		fseek(in, 0, 2);
		filesize = ftell(in);
		fseek(in, pos, 0);
		if (pos+blocks*4 >= filesize) {
			fprintf(stderr,"offset block is not exist\n");
			return;
		}
	}
	if (complevel == -1) return;
	/* offset index 読み込み */
    offsets = (int *)malloc(blocks * sizeof(*offsets));
	fread(offsets, blocks, 4, in);
	for (i=0; i<blocks; i++) {
		offsets[i] = read_little_endian_int((char*)(offsets+i));
	}
	if (feof(in) || ferror(in)) {
		fprintf(stderr,"invalid stream\n");
		free(offsets);
		offsets = 0;
		return;
	}
	return;
}
void NWAData::Rewind(FILE* in) {
	curblock = -1;
	fseek(in, 0x2c, 0);
	if (offsets) fseek(in, blocks*4, 0);
}
int NWAData::CheckHeader(void) {
	if (complevel != -1 && offsets == 0) return false;
	/* データそのもののチェック */
	if (channels != 1 && channels != 2) {
		fprintf(stderr,"This program only supports mono / stereo data : data have %d channels.\n",channels);
		return false;
	}
	if (bps != 8 && bps != 16) {
		fprintf(stderr,"This program only supports 8 / 16bit data : data is %d bits\n",bps);
		return false;
	}
	if (complevel == -1) {
		int byps = bps/8; /* bytes per sample */
		if (datasize != samplecount*byps) {
			fprintf(stderr,"invalid datasize : datasize %d != samplecount %d * samplesize %d\n",datasize,samplecount,byps);
			return false;
		}
		if (samplecount != (blocks-1)*blocksize+restsize ) {
			fprintf(stderr,"total sample count is invalid : samplecount %d != %d*%d+%d(block*blocksize+lastblocksize).\n",samplecount,blocks-1,blocksize,restsize);
			return false;
		}
		else
			return true;
	}
	//if (complevel < 0 || complevel > 2) {
	if (complevel < 0 || complevel > 5) {
		fprintf(stderr,"This program only supports -1,0,1,2 compression level : the level of data is %d\n",complevel);
		return false;
	}
	/* 整合性チェック */
	if (filesize != 0 && filesize != compdatasize) {
		fprintf(stderr,"file size is invalid : %d != %d\n",filesize,compdatasize);
		return false;
	}
	if (offsets[blocks-1] >= compdatasize) {
		fprintf(stderr,"the last offset overruns the file.\n");
		return false;
	}
	int byps = bps/8; /* bytes per sample */
	if (datasize != samplecount*byps) {
		fprintf(stderr,"invalid datasize : datasize %d != samplecount %d * samplesize %d\n",datasize,samplecount,byps);
		return false;
	}
	if (samplecount != (blocks-1)*blocksize+restsize ) {
		fprintf(stderr,"total sample count is invalid : samplecount %d != %d*%d+%d(block*blocksize+lastblocksize).\n",samplecount,blocks-1,blocksize,restsize);
		return false;
	}
    tmpdata = (char *)malloc(blocksize * byps * 2); /* これ以上の大きさはないだろう、、、 */
	return true;
}

class NWAInfo_sw2 {
public:
	int Channels(void) const{return 2;}
	int Bps(void) const { return 16;}
	int CompLevel(void) const { return 2;}
	int UseRunLength(void) const { return false; }
};
int NWAData::Decode(FILE* in, char* data, int& skip_count) {
	if (complevel == -1) {		/* 無圧縮時の処理 */
		if (feof(in) || ferror(in)) return -1;
		if (curblock == -1) {
			/* 最初のブロックなら、wave header 出力 */
			memcpy(data, make_wavheader(datasize, channels, bps, freq), 0x2c);
			curblock++;
			fseek(in, offset_start + 0x2c, SEEK_SET);
			return 0x2c;
		}
		if (skip_count > blocksize/channels) {
			skip_count -= blocksize/channels;
			fseek(in, blocksize*(bps/8), SEEK_CUR);
			curblock++;
			return -2;
		}
		if (curblock < blocks) {
			int readsize = blocksize;
			if (skip_count) {
				fseek(in, skip_count*channels*(bps/8), SEEK_CUR);
				readsize -= skip_count * channels;
				skip_count = 0;
			}
			int err = fread(data, 1, readsize * (bps/8), in);
			curblock++;
			return err;
		}
		return -1;
	}
	if (offsets == 0 || tmpdata == 0) return -1;
	if (blocks == curblock) return 0;
	if (feof(in) || ferror(in)) return -1;
	if (curblock == -1) {
		/* 最初のブロックなら、wave header 出力 */
		memcpy(data, make_wavheader(datasize, channels, bps, freq), 0x2c);
		curblock++;
		return 0x2c;
	}
	/* 今回読み込む／デコードするデータの大きさを得る */
	int curblocksize, curcompsize;
	if (curblock != blocks-1) {
		curblocksize = blocksize * (bps/8);
		curcompsize = offsets[curblock+1] - offsets[curblock];
		if (curblocksize >= blocksize*(bps/8)*2) return -1; // Fatal error
	} else {
		curblocksize = restsize * (bps/8);
		curcompsize = blocksize*(bps/8)*2;
	}
	if (skip_count > blocksize/channels) {
		skip_count -= blocksize/channels;
		fseek(in, curcompsize, SEEK_CUR);
		curblock++;
		return -2;
	}
	/* データ読み込み */
	fread(tmpdata, 1, curcompsize, in);
	/* 展開 */
	if (channels == 2 && bps == 16 && complevel == 2) {
		NWAInfo_sw2 info;
		NWADecode(info, tmpdata, data, curcompsize, curblocksize);
	} else {
		NWAInfo info(channels, bps, complevel);
		NWADecode(info, tmpdata, data, curcompsize, curblocksize);
	}
	int retsize = curblocksize;
	if (skip_count) {
		int skip_c = skip_count * channels * (bps/8);
		retsize -= skip_c;
		memmove(data, data+skip_c, skip_c);
		skip_count = 0;
	}
	curblock++;
	return retsize;
}

void conv(FILE* in, FILE* out, int skip_count, int in_size = -1) {
	NWAData h;
	h.ReadHeader(in, in_size);
	h.CheckHeader();
	int bs = h.BlockLength();
	char* d = (char *)malloc(bs);
	int err;
	while( (err=h.Decode(in, d, skip_count)) != 0) {
		if (err == -1) break;
		if (err == -2) continue;
		fwrite(d, err, 1, out);
	}
    free(d);
	return;
}
__forceinline int main2(int argc, char** argv) {
	int skip_count = 0;

	if (argc > 2 && strcmp(argv[1], "--skip") == 0) {
		skip_count = atoi(argv[2]);
		argc -= 2;
		argv[1] = argv[3];
		argv[2] = argv[4];
	}
	if (argc != 2 && argc != 3) {
		fprintf(stderr,"usage : nwatowav [inputfile [outputfile]]\n");
		return -1;
	}
	if (strstr(argv[1], ".nwk") != 0 || strstr(argv[1], ".ovk") != 0) {
		bool is_ovk;
		int headblk_sz;
		char* out_ext;

        char* outpath = (char *)malloc(strlen(argv[1]) + 10);
		char buf[1024];
		memset(buf, 0, 1024);
		FILE* in = fopen(argv[1], "rb");
		if (in == 0) {
            free(outpath);
			fprintf(stderr,"Cannot open file : %s\n",argv[1]);
			return -1;
		}
		if (strstr(argv[1], ".ovk") != 0) {
			is_ovk = true;
			headblk_sz = 16; 
			out_ext = "ogg";
		} else {
			is_ovk = false;
			headblk_sz = 12;
			out_ext = "wav";
		}
		fread(buf, 1, 4, in);
		int index = read_little_endian_int(buf);
		if (index <= 0) { 
			if (is_ovk)
				fprintf(stderr,"Invalid Ogg-ovk file : %s : index = %d\n",argv[1],index);
			else
				fprintf(stderr,"Invalid Koe-nwk file : %s : index = %d\n",argv[1],index);
            free(outpath);
			return -1;
		}
        char *pExt;
		int* tbl_off = (int *)malloc(index * sizeof(int));
		int* tbl_siz = (int *)malloc(index * sizeof(int));
		int* tbl_cnt = (int *)malloc(index * sizeof(int));
		int* tbl_origsiz = (int *)malloc(index * sizeof(int));
		int i;
		for (i=0; i<index; i++) {
			fread(buf, 1, headblk_sz, in);
			tbl_siz[i] = read_little_endian_int(buf);
			tbl_off[i] = read_little_endian_int(buf+4);
			tbl_cnt[i] = read_little_endian_int(buf+8);
			tbl_origsiz[i] = read_little_endian_int(buf+12);
		}
        pExt = findext(argv[1]);
        if (pExt) *pExt = 0;
        pExt = findname(argv[1]);
        mkdir(argv[1]);
        chdir(argv[1]);
		fseek(in, 0, 2);
		int fsize = ftell(in);
		for (i=0; i<index; i++) {
			if (tbl_off[i] <= 0 || tbl_siz[i] <= 0 || tbl_off[i]+tbl_siz[i] > fsize) {
				fprintf(stderr,"Invalid table[%d] : cnt %d off %d size %d / %d\n",i,tbl_cnt[i],tbl_off[i],tbl_siz[i],fsize);
				continue;
			}
			if (argc == 2)
				sprintf(outpath, "%s%05u.%s", pExt, tbl_cnt[i],out_ext);
			else
				sprintf(outpath, "%s%05u.%s", pExt, tbl_cnt[i],out_ext);
			FILE* out = fopen(outpath, "wb");
			if (out == 0) {
				fprintf(stderr,"Cannot open output file %s\n",outpath);
				continue;
			}
			fprintf(stderr,"Writing file %s...\n",outpath);
			fseek(in, tbl_off[i], 0);
			if (is_ovk) { // copy file
				int sz = tbl_siz[i];
				char buf[32*1024];
				while(sz > 32*1024) {
					fread(buf, 32*1024, 1, in);
					fwrite(buf, 32*1024, 1, out);
					sz -= 1024*32;
				}
				if (sz > 0) {
					fread(buf, sz, 1, in);
					fwrite(buf, sz, 1, out);
				}
			} else { // .nwk
				conv(in, out, 0, tbl_siz[i]);
			}
			fclose(out);
		}
        free(outpath);
		return 0;
	}
	FILE* in = fopen(argv[1],"rb");
	if (in == 0) {
		fprintf(stderr,"Cannot open file : %s\n",argv[1]);
		return -1;
	}
	FILE* out;
	char *pExt, outpath[MAX_PATH];
    pExt = findext(argv[1]);
    if (pExt) *pExt = 0;
	sprintf(outpath, "%s.wav",argv[1]);
	if (argc == 3) outpath = argv[2];
	out = fopen(outpath, "wb");
	if (out == 0) {
		fprintf(stderr,"Cannot open file : %s\n",outpath);
        free(outpath);
		return -1;
	}
    conv(in, out, skip_count);
	return 0;
}

void __cdecl main(int argc, char **argv)
{
    getargs(&argc, &argv);
    main2(argc, argv);
    exit(0);
}