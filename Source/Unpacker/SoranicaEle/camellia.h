
#ifndef _CAMELLIA_H_
#define _CAMELLIA_H_

#define CAM_VERSION "2.7.0 : Bastille ($Rev: 270 $)"


#include <stdlib.h>
#include "my_headers.h"

typedef PInt32 KEY_TABLE_TYPE;

_MY_C_HEAD_

void Camellia_Ekeygen(const int keyBitLength, const Byte *rawKey, KEY_TABLE_TYPE keyTable);
void Camellia_DecryptBlock(const int keyBitLength, const Byte ciphertext[], const KEY_TABLE_TYPE keyTable, Byte plaintext[]);
void Camellia_EncryptBlock(const int keyBitLength, const Byte plaintext[], const KEY_TABLE_TYPE keyTable, Byte ciphertext[]);

_MY_C_TAIL_

/*******************************************
 * Compilation options :                   *
 */
// Pixel definition
#define CAM_PIXEL unsigned char
#define CAM_SIGNED_PIXEL signed char

// Max image size
#define CAM_MAX_SCANLINE 1280
#define CAM_MAX_FRAME_HEIGHT 1024

// 64-bit processor or memory bandwidth?
#define CAM_64BITS

// Pentium4 optimizations?
#define CAM_OPT_P4

// Big endian architecture?
//#define CAM_BIG_ENDIAN

// Generate 8 AND 16 bits pixel size code
#define CAM_GENERATE_FULL_CODE

/*                                         *
 *******************************************/ 
#ifdef _WIN32
#define CAM_INT64 __int64
#define CAM_UINT64 unsigned __int64
#else
#define CAM_INT64 long long
#define CAM_UINT64 unsigned long long
#endif

#ifdef __INTEL_COMPILER
#define CAM_ALIGN16 __declspec(align(16))
#else
#define CAM_ALIGN16
#endif

#define CAM_FIXED_POINT signed long
#define CAM_FLOAT2FIXED(x,dot_pos) ((CAM_FIXED_POINT)((x)*(1<<dot_pos)))

#define CAM_DEPTH_SIGN 0x80000000               
#define CAM_DEPTH_MASK 0x7FFFFFFF               

#define CAM_DEPTH_1U     1
#define CAM_DEPTH_8U     8
#define CAM_DEPTH_10U   10
#define CAM_DEPTH_12U   12
#define CAM_DEPTH_16U   16
#define CAM_DEPTH_32U   32

#define CAM_DEPTH_8S  (CAM_DEPTH_SIGN| 8)
#define CAM_DEPTH_10S (CAM_DEPTH_SIGN|10)
#define CAM_DEPTH_12S (CAM_DEPTH_SIGN|12)
#define CAM_DEPTH_16S (CAM_DEPTH_SIGN|16)
#define CAM_DEPTH_32S (CAM_DEPTH_SIGN|32)

#define CAM_DATA_ORDER_PIXEL  0
#define CAM_DATA_ORDER_PLANE  1

#define CAM_ORIGIN_TL 0

#define CAM_ALIGN_4BYTES   4
#define CAM_ALIGN_8BYTES   8
#define CAM_ALIGN_16BYTES 16
#define CAM_ALIGN_32BYTES 32

#define CAM_ALIGN_DWORD   CAM_ALIGN_4BYTES
#define CAM_ALIGN_QWORD   CAM_ALIGN_8BYTES
 
#define CAM_BORDER_CONSTANT   0
#define CAM_BORDER_REPLICATE  1

/*---  Indexes to access IplImage.BorderMode[],IplImage.BorderConst[]  ----*/
#define CAM_SIDE_TOP_INDEX    0
#define CAM_SIDE_BOTTOM_INDEX 1
#define CAM_SIDE_LEFT_INDEX   2
#define CAM_SIDE_RIGHT_INDEX  3

/*----------  values of argument of iplSetBorderMode(,,border,)  ----------*/
#define CAM_SIDE_TOP        (1<<CAM_SIDE_TOP_INDEX)
#define CAM_SIDE_BOTTOM     (1<<CAM_SIDE_BOTTOM_INDEX)
#define CAM_SIDE_LEFT       (1<<CAM_SIDE_LEFT_INDEX)
#define CAM_SIDE_RIGHT      (1<<CAM_SIDE_RIGHT_INDEX)
#define CAM_SIDE_ALL        (CAM_SIDE_RIGHT | CAM_SIDE_TOP | CAM_SIDE_LEFT | CAM_SIDE_BOTTOM)

#ifdef CAM_BIG_ENDIAN
#define CAM_FC( ch0, ch1, ch2, ch3 ) \
    ((int)(ch3)|((int)(ch2)<<8)|((int)(ch1)<<16)|((int)(ch0)<<24))
#else
#define CAM_FC( ch0, ch1, ch2, ch3 ) \
    ((int)(ch0)|((int)(ch1)<<8)|((int)(ch2)<<16)|((int)(ch3)<<24))
#endif

#ifndef SWIG
#define CAM_COLORMODEL_RGB   CAM_FC('R','G','B',000)
#define CAM_COLORMODEL_RGBA  CAM_FC('R','G','B','A')
#define CAM_COLORMODEL_YUV   CAM_FC('Y','U','V',000)
#define CAM_COLORMODEL_GREY  CAM_FC('G',000,000,000)
#define CAM_CHANNELSEQ_RGB   CAM_FC('R','G','B',000)
#define CAM_CHANNELSEQ_RGBA  CAM_FC('R','G','B','A')
#define CAM_CHANNELSEQ_YUV   CAM_FC('Y','U','V',000)
#define CAM_CHANNELSEQ_GREY  CAM_FC('G',000,000,000)
#define CAM_CHANNELSEQ_BGR   CAM_FC('B','G','R',000)
#define CAM_CHANNELSEQ_BGRA  CAM_FC('B','G','R','A')
#endif // SWIG

#define CAM_HEADER_ONLY (1<<29)

#ifdef __cplusplus
struct CamImage;
struct CamTableOfBasins;
struct CamBitmapFont;
struct CamKeypoints;
struct CamKeypoint;

struct CamROI {
#else
typedef struct {
#endif

    int             coi;                
    int             xOffset;            
    int             yOffset;            
    int             width;              
    int             height;             
    
    // C++ Wrapping
#ifdef __cplusplus
    CamROI() {coi=0; xOffset=0; yOffset=0; width=0; height=0;}
    CamROI(int _coi, int _xOffset, int _yOffset, int _width, int _height) {
        coi=_coi; xOffset=_xOffset; yOffset=_yOffset; width=_width; height=_height;
    }
    CamROI(const CamImage &image, int _coi=0);
    ~CamROI() {};
    CamROI intersect(const CamROI &roi) const; 
    bool clip(CamImage &image);
    bool reduce(int i);
    bool enlarge(int i);
};

struct CamLinearFilterKernel;
struct CamMorphoMathsKernel;
struct CamRLEImage;
struct CamTable;
struct CamMeasuresResults;
struct CamSepFilterKernel;
struct CamAffineTransform;

struct CamPoint {
    int x; 
    int y; 
    
    CamPoint apply_affine_transform(const CamAffineTransform &t) const;
    CamPoint(int xp, int yp) {x = xp; y = yp;}
    CamPoint() {x = 0; y = 0;}
};
#else
} CamROI;

typedef struct {
    int x; 
    int y; 
} CamPoint;
#endif

#define CAM_POINT   1
#define CAM_CROSS   2
#define CAM_CIRCLE  4


#ifdef __cplusplus
struct CamImage {
#else
typedef struct {
#endif
#ifdef SWIG
%immutable;
#endif
    int             nSize;              
    int             id;                 
    int             nChannels;          
    int             alphaChannel;       
    

    int             depth;              
    char            colorModel[4];      
    

    char            channelSeq[4];              
    int             dataOrder;          
    int             origin;             
    int             align;              
    int             width;              
    int             height;             
 
#ifdef SWIG
%mutable;
#endif

    CamROI         *roi;
#ifdef SWIG
%immutable;
#endif


    void           *mask;               
    

    void           *imageId;            
    
    void           *misc;               
    int             imageSize;          
    unsigned char  *imageData;          
    int             widthStep;          
    int             borderMode[4];      
    int             borderConst[4];     
    unsigned char  *imageDataOrigin;    

    // C++ Wrapping

#ifdef __cplusplus
    CamImage() {nSize=sizeof(CamImage); imageData=NULL; roi=NULL; imageSize=0; mask=NULL; imageDataOrigin=NULL; depth=CAM_DEPTH_8U; nChannels=1; } 
    CamImage(int width, int height, int depth=CAM_DEPTH_8U, int channelseq=0); 
    CamImage(const CamImage& image);                    
    ~CamImage();                                        

#ifndef SWIG
    CamImage& operator=(const CamImage &image);         
#endif
    CamImage* clone() const;                            
    CamImage* copy() const;                             
    bool copy(CamImage &dest) const;                    
    bool allocated() const {return (imageData)?true:false;} 
    bool alloc(int width, int height, int depth=CAM_DEPTH_8U, int channelseq=0); 
    bool fill_header(int width, int height, int depth=CAM_DEPTH_8U, int channelseq=0); 
    bool deallocate();                                  
    bool free() {return deallocate();}
    bool alloc_rgb(int width, int height);              
    bool alloc_rgba(int width, int height);             
    bool alloc_bgr(int width, int height);              
    bool alloc_bgra(int width, int height);             
    bool alloc_yuv(int width, int height);              
    bool alloc_hls(int width, int height);              
    bool load_pgm(const char *filename);                
    bool save_pgm(const char *filename) const;          
    bool save_raw_pgm(const char *filename) const;      
    bool load_bmp(const char *filename);                
    bool save_bmp(const char *filename) const;          
    bool set_roi(const CamROI &roi);                    
    void get_pixels(char **result, int *len) const;     
    bool set_pixels(const char *pixels, int sz);        
    void inspect(char **result, int *len) const;        
    bool view() const;                                  
    bool set(int color);                                
    bool alpha_composite(const CamImage& source2, CamImage& dest) const; 

    int erode_square3();                                
    int erode_square3(CamImage &dest) const;            
    int erode_circle5();                                
    int erode_circle5(CamImage &dest) const;            
    int erode_circle7();                                
    int erode_circle7(CamImage &dest) const;            
    int dilate_square3();                               
    int dilate_square3(CamImage &dest) const;           
    int dilate_circle5();                               
    int dilate_circle5(CamImage &dest) const;           
    int dilate_circle7();                               
    int dilate_circle7(CamImage &dest) const;           
    int morpho_gradient_square3();                      
    int morpho_gradient_square3(CamImage &dest) const;  
    int morpho_gradient_circle5();                      
    int morpho_gradient_circle5(CamImage &dest) const;  
    int morpho_gradient_circle7();                      
    int morpho_gradient_circle7(CamImage &dest) const;  

    int morpho_maths(const CamMorphoMathsKernel &ker);                                  
    int morpho_maths(CamImage &dest, const CamMorphoMathsKernel &ker) const;            
    int erode_3x3(const CamMorphoMathsKernel &ker);                                     
    int erode_3x3(CamImage &dest, const CamMorphoMathsKernel &ker) const;               
    int dilate_3x3(const CamMorphoMathsKernel &ker);                                    
    int dilate_3x3(CamImage &dest, const CamMorphoMathsKernel &ker) const;              
    int erode_5x5(const CamMorphoMathsKernel &ker);                                     
    int erode_5x5(CamImage &dest, const CamMorphoMathsKernel &ker) const;               
    int dilate_5x5(const CamMorphoMathsKernel &ker);                                    
    int dilate_5x5(CamImage &dest, const CamMorphoMathsKernel &ker) const;              
    int erode_7x7(const CamMorphoMathsKernel &ker);                                     
    int erode_7x7(CamImage &dest, const CamMorphoMathsKernel &ker) const;               
    int dilate_7x7(const CamMorphoMathsKernel &ker);                                    
    int dilate_7x7(CamImage &dest, const CamMorphoMathsKernel &ker) const;              

    int linear_filter_3x3(const CamLinearFilterKernel &ker);                            
    int linear_filter_3x3(CamImage &dest, const CamLinearFilterKernel &k) const;        
    int linear_filter_5x5(const CamLinearFilterKernel &ker);                            
    int linear_filter_5x5(CamImage &dest, const CamLinearFilterKernel &k) const;        
    int linear_filter_abs_3x3(const CamLinearFilterKernel &ker);                        
    int linear_filter_abs_3x3(CamImage &dest, const CamLinearFilterKernel &k) const;    
    int linear_filter_abs_5x5(const CamLinearFilterKernel &ker);                        
    int linear_filter_abs_5x5(CamImage &dest, const CamLinearFilterKernel &k) const;    
    bool sobel_v();                                                                     
    bool sobel_h();                                                                     
    bool sobel_v_abs();                                                                 
    bool sobel_h_abs();                                                                 
    bool sobel_v(CamImage &dest) const;                                                 
    bool sobel_h(CamImage &dest) const;                                                 
    bool sobel_v_abs(CamImage &dest) const;                                             
    bool sobel_h_abs(CamImage &dest) const;                                             
    int sep_filter_3x3(const CamSepFilterKernel &ker);                                  
    int sep_filter_3x3(CamImage &dest, const CamSepFilterKernel &k) const;              
    int sep_filter_5x5(const CamSepFilterKernel &ker);                                  
    int sep_filter_5x5(CamImage &dest, const CamSepFilterKernel &k) const;              
    int sep_filter_7x7(const CamSepFilterKernel &ker);                                  
    int sep_filter_7x7(CamImage &dest, const CamSepFilterKernel &k) const;              
    int sep_filter_abs_3x3(const CamSepFilterKernel &ker);                              
    int sep_filter_abs_3x3(CamImage &dest, const CamSepFilterKernel &k) const;          
    int sep_filter_abs_5x5(const CamSepFilterKernel &ker);                              
    int sep_filter_abs_5x5(CamImage &dest, const CamSepFilterKernel &k) const;          
    int sep_filter_abs_7x7(const CamSepFilterKernel &ker);                              
    int sep_filter_abs_7x7(CamImage &dest, const CamSepFilterKernel &k) const;          
    bool fixed_filter(CamImage &dest, int filter) const;                                
    bool fixed_filter(int filter);                                                      

    bool draw_line(int x1, int y1, int x2, int y2, int color);                          
    bool accumulate_line(int x1, int y1, int x2, int y2, int acc);                      
    bool draw_rectangle(int x1, int y1, int x2, int y2, int color);                     
    bool draw_text_16s(const char *text, int x, int y, int cwidth, int cheight, int orientation, int color); 
    bool draw_text_bitmap(const char *text, int x, int y, const CamBitmapFont &font);   
    bool draw_circle(int x, int y, int r, int color);                                   
    bool draw_ellipse(int x, int y, int rx, int ry, int color);                         
    bool plot(int x, int y, int color, int kind=CAM_POINT);                             
    int fill_color(int x, int y, int fillcolor, int tolerance=-1);                      

    bool warping(CamImage &dest, int interpolation_method, bool perspective, const CamPoint &ul, const CamPoint &ur, const CamPoint &lr, const CamPoint &ll) const; 
    bool scale(CamImage &dest) const;                                                   
    bool set_mask(const CamRLEImage &mask);                                             
    bool set_mask(const CamImage &mask);                                                
    bool apply_lut(const CamTable &lut);                                                
    bool apply_lut(CamImage &dest, const CamTable &lut) const;                          

    CamImage *to_yuv() const;                                                           
    bool to_yuv(CamImage &dest) const;                                                  
    CamImage *to_y() const;                                                             
    bool to_y(CamImage &dest) const;                                                    
    CamImage *to_rgb() const;                                                           
    bool to_rgb(CamImage &dest) const;                                                  
    CamImage *to_hls() const;                                                           
    bool to_hls(CamImage &dest) const;                                                  

    CamRLEImage* encode() const;                                                        
    CamRLEImage* encode_lut(const CamTable &LUT)  const;                                
    CamRLEImage* encode_threshold(int threshold) const;                                 
    CamRLEImage* encode_threshold_inv(int threshold) const;                             
    CamRLEImage* encode_color(const CamTable &clusters) const;                          
    bool encode(CamRLEImage& dest) const;                                               
    bool encode_lut(CamRLEImage& dest, const CamTable &LUT)  const;                     
    bool encode_threshold(CamRLEImage& dest, int threshold) const;                      
    bool encode_threshold_inv(CamRLEImage& dest, int threshold) const;                  

    int threshold(CamImage &dest,int threshold) const;                                  
    int threshold_inv(CamImage &dest,int threshold) const;                              
    int abs(CamImage &dest) const;                                                      
    int threshold(int threshold);                                                       
    int threshold_inv(int threshold);                                                   
    int abs();                                                                          

    int arithm(int operation, int c1=0, int c2=0, int c3=0);                            
    int arithm(CamImage& dest, int operation, int c1=0, int c2=0, int c3=0) const;      
    int arithm(const CamImage& source2, CamImage& dest, int operation, int c1=0, int c2=0, int c3=0, int c4=0) const; 

    CamMeasuresResults measures() const;                                                
    float average_deviation(int average=0) const;                                       

    bool sum_hv(CamTable& hsum, CamTable &vsum) const;                                  
    bool sum_h(CamTable& sum) const;                                                    
    bool sum_v(CamTable& sum) const;                                                    

    int histogram(CamTable& histo) const;                                               
    bool histogram_equalization(CamImage &dest, const CamTable &src_histo, int option=0, CamImage *work=NULL); 
    bool histogram_2_channels(int ch1, int ch2, CamImage &result, int size=1) const;    
    int find_threshold(int percent) const;                                              

    int hough_circle(int percent, int rmin, int rmax, int &xc, int &yc, int &rc) const; 

    int hierarchical_watershed(CamImage &watershed, CamTableOfBasins &tob) const;       
    int hierarchical_watershed_contours(CamImage &ws, CamTableOfBasins &tob) const;     
    int hierarchical_watershed_regions(const CamTableOfBasins &tob);                    

    bool draw_keypoints(const CamKeypoints &points, int color = 255);           
    bool draw_keypoint(const CamKeypoint &point, int color = 255);              
    bool harris(CamKeypoints &points, int k = 41) const;                                
    bool integral_image(CamImage &dest) const;                                          
    CamImage *integral_image() const;                                                   
    bool fast_hessian_detector(CamKeypoints &points, int threshold, int options = 0) const; 
};

inline CamROI::CamROI(const CamImage &image, int _coi) { coi=_coi; xOffset=0; yOffset=0; width=image.width; height=image.height; }

#else
} CamImage;
#endif

/* Camellia C functions headers
 */

#ifndef SWIG

#define CAM_PIXEL_ACCESS(ptr,y,x) \
    ((CAM_PIXEL*)((char*)ptr+y*ptr##widthstep)+x)

#define CAM_MAX(a,b) (((a)>(b))?(a):(b))
#define CAM_MIN(a,b) (((a)<(b))?(a):(b))

#define CAM_RGBA(r,g,b,a) ((r)|((g)<<8)|((b)<<16)|((a)<<24))

#define CAM_RGB(r,g,b) ((r)|((g)<<8)|((b)<<16))

#endif // SWIG

/* General purpose structures
 */

/* Monadic and Dyadic Arithmetic Operators kernel
 */

#define CAM_ARITHM_ABS              0
#define CAM_ARITHM_INVERSE          1
#define CAM_ARITHM_SELECT           2
#define CAM_ARITHM_THRESHOLD        3 
#define CAM_ARITHM_DOUBLE_THRESHOLD 4

#define CAM_ARITHM_ADD              0
#define CAM_ARITHM_SUM              0
#define CAM_ARITHM_SUB              1
#define CAM_ARITHM_MUL              2
#define CAM_ARITHM_ABSDIFF          3
#define CAM_ARITHM_WEIGHTED_SUM     4
#define CAM_ARITHM_INF              5
#define CAM_ARITHM_SUP              6
#define CAM_ARITHM_COMP_INF         7
#define CAM_ARITHM_COMP_EQUAL       8
#define CAM_ARITHM_COMP_SUP         9
#define CAM_ARITHM_AND              10
#define CAM_ARITHM_OR               11

// Shorter constants
#define CAM_ABS                     0
#define CAM_INVERSE                 1
#define CAM_SELECT                  2
#define CAM_THRESHOLD               3 
#define CAM_DOUBLE_THRESHOLD        4

#define CAM_ADD                     0
#define CAM_SUM                     0
#define CAM_SUB                     1
#define CAM_ABSDIFF                 2
#define CAM_WEIGHTED_SUM            3
#define CAM_INF                     4
#define CAM_SUP                     5
#define CAM_COMP_INF                6
#define CAM_COMP_EQUAL              7
#define CAM_COMP_SUP                8
#define CAM_AND                     9
#define CAM_OR                      10

#ifndef SWIG


typedef struct {
    int operation;   
    int c1; 
    int c2; 
    int c3; 
    int c4; 
} CamArithmParams;

#endif // SWIG

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SWIG


int camMonadicArithm(CamImage *source, CamImage *dest, CamArithmParams *params);


int camDyadicArithm(CamImage *source1, CamImage *source2, CamImage *dest, CamArithmParams *params);


int camAdd(CamImage *source1, CamImage *source2, CamImage *dest);


int camMul(CamImage *source1, CamImage *source2, CamImage *dest);


int camSub(CamImage *source1, CamImage *source2, CamImage *dest);


int camThreshold(CamImage *source, CamImage *dest, int threshold);


int camThresholdInv(CamImage *source, CamImage *dest, int threshold);

int camAbs(CamImage *source, CamImage *dest);

/* Apply-a-LUT-on-image Kernel
 */

// 12 bits maximum LUT management
#define CAM_TABLE_SIZE 4096

#define CamLUT CamTable
#define CamHisto CamTable

#ifdef __cplusplus
struct CamTable {
#else
typedef struct {
#endif
    int t[CAM_TABLE_SIZE]; 
    int size;              
#ifdef __cplusplus    
    CamTable(int s=0) {size=s;}
    int &operator[](int n);
    bool set(const int* const array, int sz) { if (sz<CAM_TABLE_SIZE) { size=sz; for (int i=0;i<sz;i++) t[i]=array[i]; return true;} return false;} 
};
#else
} CamTable;
#endif

int camApplyLUT(CamImage *source, CamImage *dest, CamTable *LUT);

#endif // SWIG

/* Fundamental Morphological Mathematics Algorithms' kernel
 */
#define CAM_MM_NEIGHB           7

#define CAM_MM_DILATED          0
#define CAM_MM_ERODED           1
#define CAM_MM_ORIGINAL         2

#define CAM_MM_SUBSTRACTION     0
#define CAM_MM_MULTIPLEX        1
#define CAM_MM_THINNING         2
#define CAM_MM_THICKENING       3


#ifdef __cplusplus
struct CamMorphoMathsKernel {
#else
typedef struct {
#endif
    // Structural elements
#ifndef SWIG
    int dilationStructElt[CAM_MM_NEIGHB][CAM_MM_NEIGHB]; 
    int erosionStructElt[CAM_MM_NEIGHB][CAM_MM_NEIGHB];  
#endif
    int source1;            
    int source2;            
    int operation;          
#ifdef __cplusplus
    CamMorphoMathsKernel() {
        for (int i=0;i<CAM_MM_NEIGHB;i++) {
            for (int j=0;j<CAM_MM_NEIGHB;j++) {
                dilationStructElt[i][j]=0;
                erosionStructElt[i][j]=0;
            }
        }
        source1=CAM_MM_ORIGINAL;
        source2=CAM_MM_ORIGINAL;
        operation=CAM_MM_MULTIPLEX;
    }       
    bool set_dilate(int x, int y, int val) {
        if ((x>=0)&&(x<CAM_MM_NEIGHB)&&(y>=0)&&(y<CAM_MM_NEIGHB)) {
            dilationStructElt[x][y]=val; return true;
        } else return false;
    }
    int get_dilate(int x,int y) {
        if ((x>=0)&&(x<CAM_MM_NEIGHB)&&(y>=0)&&(y<CAM_MM_NEIGHB)) {
            return dilationStructElt[x][y];
        } else return 0;
    }
    bool set_erode(int x, int y, int val) {
        if ((x>=0)&&(x<CAM_MM_NEIGHB)&&(y>=0)&&(y<CAM_MM_NEIGHB)) {
            erosionStructElt[x][y]=val; return true;
        } else return false;
    }
    int get_erode(int x,int y) {
        if ((x>=0)&&(x<CAM_MM_NEIGHB)&&(y>=0)&&(y<CAM_MM_NEIGHB)) {
            return erosionStructElt[x][y];
        } else return 0;
    }
};
#else
} CamMorphoMathsKernel;
#endif

#ifndef SWIG



int camMorphoMaths(CamImage *source, CamImage *dest, CamMorphoMathsKernel *kernel);

// These are specific functions able to compute only erosion or dilation, on 3x3, 5x5 or 7x7 neighbourhood

int camErode3x3(CamImage *source, CamImage *dest, CamMorphoMathsKernel *kernel); 

int camErode5x5(CamImage *source, CamImage *dest, CamMorphoMathsKernel *kernel); 

int camErode7x7(CamImage *source, CamImage *dest, CamMorphoMathsKernel *kernel); 

int camDilate3x3(CamImage *source, CamImage *dest, CamMorphoMathsKernel *kernel); 

int camDilate5x5(CamImage *source, CamImage *dest, CamMorphoMathsKernel *kernel); 

int camDilate7x7(CamImage *source, CamImage *dest, CamMorphoMathsKernel *kernel); 

int camMorphoGradientCircle5(CamImage *source, CamImage *dest); 

int camErodeCircle5(CamImage *source, CamImage *dest); 

int camDilateCircle5(CamImage *source, CamImage *dest);  

int camMorphoGradientCircle7(CamImage *source, CamImage *dest); 

int camErodeCircle7(CamImage *source, CamImage *dest); 

int camDilateCircle7(CamImage *source, CamImage *dest);  

int camMorphoGradientSquare3(CamImage *source, CamImage *dest); 

int camErodeSquare3(CamImage *source, CamImage *dest); 

int camDilateSquare3(CamImage *source, CamImage *dest); 


/* Labeling kernel
 */
#define CamLabellingResults CamLabelingResults
#define camLabelling camLabeling
#define camLabelling2ndScan camLabeling2ndScan
#define camRLELabelling camRLELabeling

#define CAM_LABEL_MAX_BLOBS 1024
#define CAM_LABEL_PIXEL unsigned short

#define CAM_LABEL_PIXEL_ACCESS(ptr,y,x) \
    ((CAM_LABEL_PIXEL*)((char*)ptr+y*ptr##widthstep)+x)

typedef struct {
    int nbLabels;                   
    int equiv[CAM_LABEL_MAX_BLOBS]; 
} CamLabelingResults;


int camLabeling(CamImage *source, CamImage *dest, CamLabelingResults *results); 
                                                                                  
int camLabeling2ndScan(CamImage *image, CamLabelingResults *results); 

/* Blob analysis Kernel
 * C code */

#endif // SWIG

#define CAM_RLE_INT_TYPE unsigned short


typedef struct {
    CAM_RLE_INT_TYPE value;     
    CAM_RLE_INT_TYPE length;    
    CAM_RLE_INT_TYPE blob;      
    CAM_RLE_INT_TYPE line;      
} CamRun;

#ifndef SWIG

typedef struct {
    int id;
    int left;           
    int top;            
    int width;          
    int height;         
    int surface;        
    int cx;             
    int cy;             
    int value;          
    int min;            
    int max;            
    CamRun *first;      
    CamRun *last;       
    void *misc;         
} CamBlobInfo;

#define CamBlobAnalysisResults CamBlobs // For compatibility with previous versions

#ifdef __cplusplus
struct CamBlobs {
    int nbBlobs;                                
    CamBlobInfo blobInfo[CAM_LABEL_MAX_BLOBS];  
    CamBlobs() {nbBlobs=0;}                     
    CamBlobInfo& operator[](int index);
};
#else
typedef struct {
    int nbBlobs;                                
    CamBlobInfo blobInfo[CAM_LABEL_MAX_BLOBS];  
} CamBlobs;
#endif

int camBlobAnalysis1stScan(CamImage *blobImage, CamImage *original, CamLabelingResults *info, CamBlobs *results); 


int camBlobAnalysisRefinement(CamImage *blobImage, CamImage *original, CamBlobs *results);

/* RLE Labeling kernel
 * New : v1.4 of LLAs
 * Updated v1.6 and v1.9, v2.0 of LLAs
 */


#ifdef __cplusplus
struct CamRLEImage {
#else
typedef struct {
#endif
    int nSize;          
    int id;             
    int height;         
    int width;          
    int nbRuns;         
    int allocated;      
    CamRun *runs;       

#ifdef __cplusplus
    CamRLEImage() {nSize=sizeof(CamRLEImage); allocated=0; runs=NULL; nbRuns=0;} 
    CamRLEImage(int nbruns);                            
    CamRLEImage(const CamRLEImage &image);              
    ~CamRLEImage();                                     

    CamRLEImage& operator=(const CamRLEImage &image);   
    CamRLEImage* clone() const;                         
    bool alloc(int nbruns);                             
    bool realloc(int nbruns);                           

    bool encode(const CamImage &image);                             
    bool encode_lut(const CamImage &image, const CamTable &LUT);    
    bool encode_threshold(const CamImage &image, int threshold);    
    bool encode_threshold_inv(const CamImage &image, int threshold);
    bool encode_color(const CamImage &image, const CamTable &clusters); 
    CamBlobs* labeling();                                           
    bool labeling(CamBlobs &results);                               
    bool blob_analysis(CamBlobs &results) const;                    
    bool apply_lut(const CamTable &LUT);                            
    bool apply_lut(CamRLEImage &dest, const CamTable &LUT) const;   
    bool decode(CamImage &dest) const;                              
    bool decode(CamImage &dest, const CamTable &LUT) const;         
    bool decode_blobs(CamImage &dest) const;                        
    bool decode_blobs(CamImage &dest, const CamTable &LUT) const;   
    bool inverse();                                                 
    bool erode_cross(CamRLEImage &dest) const;                      
    CamRLEImage *erode_cross() const;                               
    bool erode_3x3(CamRLEImage &dest) const;                        
    CamRLEImage *erode_3x3() const;                                 
    bool erode_3x2(CamRLEImage &dest) const;                        
    CamRLEImage *erode_3x2() const;                                 
};
#else
} CamRLEImage;
#endif


int camRLEAllocate(CamRLEImage *rle, int max_runs);


int camRLEDeallocate(CamRLEImage *rle);

int camRLEFree(CamRLEImage *rle);


int camRLEReallocate(CamRLEImage *rle, int new_max_runs);


int camRLEClone(CamRLEImage *source, CamRLEImage *dest);


int camRLEEncode(CamImage *src, CamRLEImage *dest);


int camRLEEncodeLUT(CamImage *src, CamRLEImage *dest, CamTable *LUT);


int camRLEEncodeThreshold(CamImage *src, CamRLEImage *dest, int threshold);


int camRLEEncodeThresholdInv(CamImage *src, CamRLEImage *dest, int threshold);

int camRLEEncodeColor(CamImage *source, CamRLEImage *dest, CamTable *clusters);


int camRLELabeling(CamRLEImage *src, CamBlobs *results);


int camRLEBlobAnalysis(CamRLEImage *src, CamBlobs *results);


int camRLEApplyLUT(CamRLEImage *src, CamRLEImage *dest, CamTable *LUT);


int camRLEDecode(CamRLEImage *src, CamImage *dest, CamTable *LUT);


int camRLEDecodeBlobs(CamRLEImage *src, CamImage *dest, CamTable *LUT);


int camRLEInverse(CamRLEImage *image);

int camRLEBlobSides(CamBlobInfo *blob, int *left, int *top, int *right, int *bottom);

int camRLEBlobROIIntersect(CamBlobInfo *blob, CamROI *roi);

int camRLEBlobMeasures(CamBlobInfo *blob, CamImage *original);


int camRLEErodeCross(CamRLEImage *image, CamRLEImage *result);


int camRLEErode3x3(CamRLEImage *image, CamRLEImage *result);


int camRLEErode3x2(CamRLEImage *image, CamRLEImage *result);




int camHistogram(CamImage *image, CamTable *histo);

#define CAM_EQUAL_PERFECT 0
#define CAM_EQUAL_FAST    1


int camHistogramEqualization(CamImage *src, CamImage *dest, CamTable *src_histo, int option, CamImage *work);


int camHistogram2Channels(CamImage *image, int ch1, int ch2, CamImage *result, int size);

int camFindThreshold(CamTable *histo, int percent);

/* Horizontal and vertical summing
 */


int camSumHV(CamImage *image, CamTable *hsum, CamTable *vsum);


int camSumV(CamImage *image, CamTable *results);


int camSumH(CamImage *image, CamTable *results);

#endif // SWIG

/* Measures in an image : min, max, average computation
 */
#ifdef __cplusplus
struct CamMeasuresResults {
#else
typedef struct {
#endif
    int min, xmin, ymin;        
    int max, xmax, ymax;        
    int average;                
    int sum;                    
#ifdef __cplusplus
    CamMeasuresResults() {min=0;xmin=0;ymin=0;max=0;xmax=0;ymax=0;average=0;sum=0;}
};
#else
} CamMeasuresResults;
#endif

#ifndef SWIG

int camSumOfPixels(CamImage *image);


int camMeasures(CamImage *image, CamMeasuresResults *results);


float camMeasureAverageDeviation(CamImage *image, int average);



#ifdef CAM_VOLBERG_ORIGINAL
void volbergfvd(double f[], int in[] , int out[] , int inlen, int outlen);
#else
void camVolbergFwdScanline(CAM_PIXEL *in, int inlen, CAM_PIXEL *out, int outlen, double f[]);
#endif

typedef struct {
    void (*hfwd)(int x, int y, double *xp); 
    void (*vfwd)(int x, int y, double *yp); 
} CamVolbergFwdParams;


void camVolbergFwd(CamImage *source, CamImage *dest, CamVolbergFwdParams *params);

/* Backward warping
 */

#endif // SWIG

#define CAM_NN_INTERPOLATION 0
#define CAM_BILINEAR_INTERPOLATION 1

#ifndef SWIG

typedef struct {
    int interpolation;  
    int perspective;    
    

    CamPoint p[4];
} CamWarpingParams;


int camWarping(CamImage *source, CamImage *dest, CamWarpingParams *params);


int camScale(CamImage *source, CamImage *dest);

int camWarpingSuperSampling(CamImage *source, CamImage *dest, CamWarpingParams *params);


int camIntersectionSegments(CamPoint p[4], CamPoint *res);


// For compatibility with older versions
#define CamSobel3x3 camSobel
#define CamSobelAbs3x3 camSobelAbs

#define CAM_LINEAR_FILTER_KERNEL_MAX_SIZE 7

#endif //SWIG

#ifdef __cplusplus
struct CamLinearFilterKernel {
#else
typedef struct {
#endif
#ifndef SWIG
    int kernel[CAM_LINEAR_FILTER_KERNEL_MAX_SIZE][CAM_LINEAR_FILTER_KERNEL_MAX_SIZE]; 
#endif
    int coeff1;         
    int coeff2;         
#ifdef __cplusplus
    CamLinearFilterKernel() {
        for (int i=0;i<CAM_LINEAR_FILTER_KERNEL_MAX_SIZE;i++) {
            for (int j=0;j<CAM_LINEAR_FILTER_KERNEL_MAX_SIZE;j++) {
                kernel[i][j]=0;
            }
        }
        coeff1=1;
        coeff2=0;
    }       
    bool set(int x, int y, int val) {
        if ((x>=0)&&(x<CAM_LINEAR_FILTER_KERNEL_MAX_SIZE)&&(y>=0)&&(y<CAM_LINEAR_FILTER_KERNEL_MAX_SIZE)) {
            kernel[x][y]=val; return true;
        } else return false;
    }
    int get(int x,int y) {
        if ((x>=0)&&(x<CAM_LINEAR_FILTER_KERNEL_MAX_SIZE)&&(y>=0)&&(y<CAM_LINEAR_FILTER_KERNEL_MAX_SIZE)) {
            return kernel[x][y];
        } else return 0;
    }
};
#else
} CamLinearFilterKernel;
#endif

#ifndef SWIG


int camLinearFilter3x3(CamImage *source, CamImage *dest, CamLinearFilterKernel *params);


int camLinearFilter5x5(CamImage *source, CamImage *dest, CamLinearFilterKernel *params);


int camLinearFilterAbs3x3(CamImage *source, CamImage *dest, CamLinearFilterKernel *params);


int camLinearFilterAbs5x5(CamImage *source, CamImage *dest, CamLinearFilterKernel *params);

/* Obsolete
 * int camSobel(CamImage *source, CamImage *dest, int vert_edges);
 * int camSobelAbs(CamImage *source, CamImage *dest, int vert_edges);
 */

#endif //SWIG

#ifdef __cplusplus
struct CamSepFilterKernel {
#else
typedef struct {
#endif
#ifndef SWIG
    int x[CAM_LINEAR_FILTER_KERNEL_MAX_SIZE]; 
    int y[CAM_LINEAR_FILTER_KERNEL_MAX_SIZE]; 
#endif
    int coeff1;         
    int coeff2;         
#ifdef __cplusplus
    CamSepFilterKernel() {
        for (int i=0;i<CAM_LINEAR_FILTER_KERNEL_MAX_SIZE;i++) {
            x[i]=0; y[i]=0;
        }
        coeff1=1;
        coeff2=0;
    }       
    bool set_x(int y, int val) {
        if ((y>=0)&&(y<CAM_LINEAR_FILTER_KERNEL_MAX_SIZE)) {
            x[y]=val; return true;
        } else return false;
    }
    bool set_y(int x, int val) {
        if ((x>=0)&&(x<CAM_LINEAR_FILTER_KERNEL_MAX_SIZE)) {
            y[x]=val; return true;
        } else return false;
    }
    int get_x(int y) {
        if ((y>=0)&&(y<CAM_LINEAR_FILTER_KERNEL_MAX_SIZE)) {
            return x[y];
        } else return 0;
    }
    int get_y(int x) {
        if ((x>=0)&&(x<CAM_LINEAR_FILTER_KERNEL_MAX_SIZE)) {
            return y[x];
        } else return 0;
    }
};
#else
} CamSepFilterKernel;
#endif

#define CAM_SOBEL_H         1
#define CAM_SOBEL_V         2
#define CAM_GAUSSIAN_3x3    3
#define CAM_GAUSSIAN_5x5    4
#define CAM_GAUSSIAN_7x7    5
#define CAM_SCHARR_H        6
#define CAM_SCHARR_V        7

#ifndef SWIG


int camSepFilter3x3(CamImage *source, CamImage *dest, CamSepFilterKernel *kernel);


int camSepFilterAbs3x3(CamImage *source, CamImage *dest, CamSepFilterKernel *kernel);


int camSepFilter5x5(CamImage *source, CamImage *dest, CamSepFilterKernel *kernel);


int camSepFilterAbs5x5(CamImage *source, CamImage *dest, CamSepFilterKernel *kernel);


int camSepFilter7x7(CamImage *source, CamImage *dest, CamSepFilterKernel *kernel);


int camSepFilterAbs7x7(CamImage *source, CamImage *dest, CamSepFilterKernel *kernel);


int camSobelH(CamImage *source, CamImage *dest);


int camSobelHAbs(CamImage *source, CamImage *dest);


int camSobelV(CamImage *source, CamImage *dest);


int camSobelVAbs(CamImage *source, CamImage *dest);


int camFixedFilter(CamImage *source, CamImage *dest, int filter);

int camScharrH(CamImage *source, CamImage *dest);
int camScharrV(CamImage *source, CamImage *dest);
int camScharrHAbs(CamImage *source, CamImage *dest);
int camScharrVAbs(CamImage *source, CamImage *dest);



#define camMedianFiltering3x3 camMedianFilter3x3
#define camMedianFiltering5x5 camMedianFilter5x5


int camMedianFilter3x3(CamImage *source, CamImage *dest);


int camMedianFilter5x5(CamImage *source, CamImage *dest);



int camWatershed1D(int *input, int size, int *results);
#else
%immutable;
#endif // SWIG

typedef struct 
{
   int dynamics;        
   int minimum;         
   int flooded;         
   int surface;         
   int accsurface;      
   unsigned short x,y;  
} CamBasin;

#define CAM_NOT_COMPUTED 65536

#ifndef SWIG
#ifdef __cplusplus
struct CamTableOfBasins {
    int sizeMax;
    int nbBasins;
    CamBasin *tab;
    CamBasin& operator[](int index) {return tab[index];}
    void get_rid_of(CamBasin &basin) {basin.surface=0;}
    CamTableOfBasins() {tab=NULL;sizeMax=0;nbBasins=0;}
    ~CamTableOfBasins();
};
#else
typedef struct
{
   int sizeMax;
   int nbBasins;
   CamBasin *tab;
} CamTableOfBasins;
#endif

void camFreeTableOfBasins(CamTableOfBasins *t);


int camHierarchicalWatershed(CamImage *source, CamImage *dest, CamTableOfBasins *tob);


int camHierarchicalWatershedContours(CamImage *source, CamImage *dest, CamTableOfBasins *tob);


int camHierarchicalWatershedRegions(CamImage *watershed, CamTableOfBasins *tob);



int camHoughCircle(CamImage *image, int percent, int rmin, int rmax, int *xc, int *yc, int *rc);

struct _CamKeypoints;

#endif // SWIG 


#ifdef __cplusplus
#ifdef SWIG
    %mutable;
#endif

struct CamKeypoint {
#else
typedef struct {
#endif // __cplusplus
    int descriptor[128];    
    int x;                  
    int y;                  
    int scale;              
    int angle;              
    int value;              
#ifdef SWIG
    %immutable;
#endif
    int size;               
    void *internal;         
#ifdef __cplusplus
    CamKeypoints *set;
    bool draw(CamImage &image, int color = 255) const;   
    bool set_descriptor(const int* const array, int sz); 
    CamKeypoint() { x = 0; y = 0; scale = 0; angle = 0; value = 0; size = 0; internal = NULL; set = NULL; }
};
#else
    struct _CamKeypoints *set;
} CamKeypoint;
#endif

typedef struct {
    CamKeypoint *p1;
    CamKeypoint *p2;
    int mark;
    int error;
} CamKeypointsMatch;

#define CAM_MAX_NB_MATCHES 2048

#ifdef __cplusplus
struct CamAffineTransform {
    double m[6];
};

struct CamKeypointsMatches {
#else

typedef struct {
    double m[6];
} CamAffineTransform;

typedef struct {
#endif //__cplusplus
    int nbMatches;
    int nbOutliers;
    int allocated;
    CamKeypointsMatch *pairs;
#ifdef __cplusplus
    CamKeypointsMatches(int size = CAM_MAX_NB_MATCHES);             
    ~CamKeypointsMatches();                                         
    CamAffineTransform find_affine_transform(int *error) const;     
    CamAffineTransform find_affine_transform2(int *error) const;    
};
#else
} CamKeypointsMatches;
#endif

#ifdef __cplusplus
struct CamKeypointsKdTree;

#ifdef SWIG
    %mutable;
#endif
struct CamKeypoints {
#else
typedef struct _CamKeypoints {
#endif
    int width, height;              
    int cx, cy;                     
    int id;                         
#ifdef SWIG
    %immutable;
#endif
    int allocated;
    int nbPoints;                   
    CamKeypoint **keypoint; 
    CamKeypoint *bag;       
#ifdef __cplusplus
    CamKeypoints() {allocated = 0; nbPoints = 0; keypoint = NULL; bag = NULL; cx = 0; cy = 0;} 
    CamKeypoints(int nbPoints);                 
#ifndef SWIG
    CamKeypoint& operator[](int index);
#endif
    ~CamKeypoints();                                

    bool add(CamKeypoint &p);
    CamKeypoints& operator<<(CamKeypoint &p) { add(p); return *this; }
    bool draw(CamImage &image, int color = 255) const;  
    int matching(const CamKeypoints **models, int nbModels, CamKeypointsMatches &matches) const;  
    int matching2(const CamKeypoints &points, CamKeypointsMatches &matches) const;                
    int matchingKdTree(const CamKeypointsKdTree &kdTree, CamKeypointsMatches &matches, int explore = 100) const; 

    bool alloc(int nbPoints);                           
    bool realloc(int nbPoints);                         
};
#else
} CamKeypoints;
#endif

#define CAM_UPRIGHT 1

int camKeypointsSetParameters(int patchSize, int sigma, int threshGradient);

#ifndef SWIG

int camAllocateKeypoints(CamKeypoints *fpoints, int nbPoints);

int camReallocateKeypoints(CamKeypoints *fpoints, int nbPoints);

int camFreeKeypoints(CamKeypoints *fpoints);

int camDrawKeypoints(CamKeypoints *points, CamImage *dest, int color);

int camDrawKeypoint(CamKeypoint *point, CamImage *dest, int color);


int camHarris(CamImage *source, CamKeypoints *points, int k);

int camFindLocalMaximaCircle7(CamImage *source, CamKeypoints *points, int threshold);

int camFindLocalMaximaCircle5(CamImage *source, CamKeypoints *points, int threshold);

int camFindLocalMaximaCircle3(CamImage *source, CamKeypoints *points, int threshold);

int camIntegralImage(CamImage *src, CamImage *dest);

int camFastHessianDetectorFixedScale(CamImage *integral, CamImage *dest, int scale);

int camFastHessianDetector(CamImage *source, CamKeypoints *points, int threshold, int options);

CamKeypoint* camFindKeypoint(CamKeypoint *point, CamKeypoints *points, int *dist1, int *dist2);

int camAllocateKeypointsMatches(CamKeypointsMatches *matches, int nbpairs);

void camFreeKeypointsMatches(CamKeypointsMatches *matches);

int camKeypointsMatching(CamKeypoints *target, CamKeypoints **models, int nbModels, CamKeypointsMatches *matches);
int camKeypointsMatching2(CamKeypoints *points1, CamKeypoints *points2, CamKeypointsMatches *matches);

int camFindAffineTransform(CamKeypointsMatches *matches, CamAffineTransform *t, int *error);
int camFindAffineTransform2(CamKeypointsMatches *matches, CamAffineTransform *t, int *error);

void camApplyAffineTransform(CamPoint *xy, CamPoint *uv, CamAffineTransform *t);

typedef struct _CamFPKdTreeNode {
    int i;
    int m;
    struct _CamFPKdTreeNode *right;
} CamFPKdTreeNode;

int camKeypointsMatchingKdTree(CamKeypoints *target, CamFPKdTreeNode *kdTreeRoot, CamKeypointsMatches *matches, int explore);

CamFPKdTreeNode *camKeypointsCompileKdTree(CamKeypoints **models, int nbModels);

CamKeypoint *camFindKeypointKdTree(CamKeypoint *point, CamFPKdTreeNode *kdTreeRoot, int explore, int *dist1, int *dist2);

#endif // SWIG

#ifdef __cplusplus
struct CamKeypointsKdTree {
    CamFPKdTreeNode *root;

    void compile(const CamKeypoints **models, int nbModels) {root = camKeypointsCompileKdTree((CamKeypoints**)models, nbModels);}
    CamKeypoint *find(const CamKeypoint *point, int explore = 100, int *dist1 = NULL, int *dist2 = NULL) const; // C++ Wrapper for camFindKeypointKdTree function

    CamKeypointsKdTree(const CamKeypoints **models = NULL, int nbModels = 0) { if (nbModels != 0) compile(models, nbModels); else root = NULL;};
    ~CamKeypointsKdTree() {if (root) free(root);}       
};
#endif // __cplusplus



/* Image allocation utility routines
 */

#ifndef SWIG

int camAllocateImage(CamImage *image, int width, int height, int depth);
int camAllocateImageEx(CamImage *image, int width, int height, int depth, int color_seq);
int camFillImageHeader(CamImage *image, int width, int height, int depth, int channelseq);
int camAllocateYUVImage(CamImage *image, int width, int height);
int camAllocateHLSImage(CamImage *image, int width, int height);
int camAllocateRGBImage(CamImage *image, int width, int height);
int camAllocateRGBAImage(CamImage *image, int width, int height);
int camAllocateBGRImage(CamImage *image, int width, int height);
int camAllocateBGRAImage(CamImage *image, int width, int height);
int camDeallocateImage(CamImage *image);
int camFreeImage(CamImage *image);

/* Other useful functions
 */
int camSetROI(CamROI *roi, int coi, int xOffset, int yOffset, int width, int height);
int camSetMaxROI(CamROI *roi, CamImage *image);
int camReduceROI(CamROI *roi, int pixels);
int camEnlargeROI(CamROI *roi, int pixels);
int camZoom2x(CamImage *src, CamImage *dst);
int camDecimateNN(CamImage *src, CamImage *dest, int factor);
int camSetRLEMask(CamImage *image, CamRLEImage *mask);
int camSetMask(CamImage *image, CamImage *mask);

#define camDownScaling2x2 camDownscaling2x2
int camDownScaling2x2(CamImage *src, CamImage *dest);

int camCopy(CamImage *source, CamImage *dest);

int camClone(CamImage *source, CamImage *dest);

int camRefCopy(CamImage *source, CamImage *dest);
int camSet(CamImage *image, int fillValue);

int camAlphaComposite(CamImage *source1, CamImage *source2, CamImage *dest);

int camSetBorder(CamImage *image, int borderValue);
int camClipROI(CamImage *image);
int camClip(CamROI *roi, CamImage *image);
int camROIIntersect(CamROI *roi1, CamROI *roi2, CamROI *dest);

#endif //SWIG
int camSetImageViewer(char *s);
#ifndef SWIG

int camView(CamImage *image);
const char *camVersion();

/* Drawing functions
 */
int camDrawLine(CamImage *image, int x1, int y1, int x2, int y2, int color);
int camAccumulateLine(CamImage *image, int x1, int y1, int x2, int y2, int acc);
int camDrawRectangle(CamImage *image, int x1, int y1, int x2, int y2, int color);
int camDrawText16s(CamImage *image, char *text, int x, int y, int cwidth, int cheight, int orientation, int color);
int camDrawCircle(CamImage *image, int x, int y, int r, int color);
int camDrawEllipse(CamImage *image, int x, int y, int rx, int ry, int color);

int camPlot(CamImage *image, int x, int y, int color, int kind);

int camFillColor(CamImage *image, int x, int y, int fillcolor, int tolerance);

#endif // SWIG

#ifdef __cplusplus
struct CamBitmapFont {
#else
typedef struct {
#endif
    int first_char;
    int nb_chars;
    int height;
    CamRLEImage *masks;
    CamImage *letters;
#ifdef __cplusplus
    CamBitmapFont() {first_char=33; nb_chars=0; masks=NULL; letters=NULL;}
    CamBitmapFont(const char *filename);
    ~CamBitmapFont();
    bool load(const char *filename);
};
#else
} CamBitmapFont;
#endif

#ifndef SWIG
int camLoadBitmapFont(CamBitmapFont *font, char *filename);
int camFreeBitmapFont(CamBitmapFont *font);
int camDrawTextBitmap(CamImage *image, char *text, int x, int y, CamBitmapFont *font);
#endif // SWIG


int camRGB(int r, int g, int b);

int camRGBA(int r, int g, int b, int a);

#ifndef SWIG

/* Load and save PGM images
 */
int camLoadPGM(CamImage *image, char *fn);
int camSavePGM(CamImage *image, char *filename);
int camSaveRawPGM(CamImage *image, char *filename);

/* Load and save BMP images
 */
int camLoadBMP(CamImage *image, char *fn);
int camSaveBMP(CamImage *image, char *filename);

/* Load config files
 */
#define CAM_CONFIG_MAX_ENTRIES 256
typedef struct {
    int nbEntries;
    char parameter[CAM_CONFIG_MAX_ENTRIES][128];
    char value[CAM_CONFIG_MAX_ENTRIES][128];
} CamConfig;

int camLoadConfig(const char *filename, CamConfig *config);
int camConfigInt(const CamConfig *config, const char *entry);
float camConfigFloat(const CamConfig *config, const char *entry);
const char *camConfigString(const CamConfig *config, const char *entry);

/* Image capture functions
 */
void* camCaptureInit(int options);
int camCapture(void *handle, CamImage *image);
int camCaptureOver(void *handle);

#endif

#define CAM_CAPTURE_AUTO_SOURCE 1
#define CAM_CAPTURE_DISPLAY     2
#define CAM_CAPTURE_USE_READ    4

#ifdef __cplusplus
class CamCapture {
    void *handle;
public:
    bool capture(CamImage &capture);
    bool ready() {return (handle)?true:false;}
    CamCapture(int options=0);
    ~CamCapture();
};
#endif

#ifndef SWIG

void camError(char *module, char *error);
typedef void (*camErrorFunct)(char *,char*);
void camSetErrorFunct(camErrorFunct funct);

int camYUV2RGB(CamImage* source, CamImage *dest); 
int camRGB2YUV(CamImage* source, CamImage *dest); 
int camRGB2Y(CamImage *source, CamImage *dest);   
int camRGB2HLS(CamImage* source, CamImage *dest); 


/*
 * Computes the Sum of Absolute Values between two 8x8 blocks
 *
 * This function takes into account the blocks lying partially outside the image.
 * MMX optimized if <DFN>CAM_OPT_MMX</DFN> compilation option is set (requires Intel C++ compiler).
 *
 *
 * \param image1    Current image
 * \param image2    Previous image
 * \param bleft     The x coordinate of the current block
 * \param btop      The y coordinate of the current block
 * \param dx        The x offset to reach the candidate block
 * \param dy        The y offset to reach the candidate block
 *
 * \return The SAD value between the given two blocks
 */
int camSAD8x8(CamImage *image1, CamImage *image2, int bleft, int btop, int dx, int dy);

/*
 * Computes the Sum of Absolute Values between two 16x16 blocks
 *
 * This function takes into account the blocks lying partially outside the image.
 * MMX optimized if <DFN>CAM_OPT_MMX</DFN> compilation option is set (requires Intel C++ compiler).
 *
 *
 * \param image1    Current image
 * \param image2    Previous image
 * \param bleft     The x coordinate of the current block
 * \param btop      The y coordinate of the current block
 * \param dx        The x offset to reach the candidate block
 * \param dy        The y offset to reach the candidate block
 *
 * \return The SAD value between the given two blocks
 */
int camSAD16x16(CamImage *image1, CamImage *image2, int bleft, int btop, int dx, int dy);

typedef struct {
    int niter;          
    int seed;           
    int lsearch;        
    int rsearch;        
    int blockSize;      
    int scans;          
    int candidates;     
    int test0;          
} CamMotionEstimation3DRSParams;

typedef struct {
    int vx[CAM_MAX_SCANLINE/8][CAM_MAX_FRAME_HEIGHT/8];   
    int vy[CAM_MAX_SCANLINE/8][CAM_MAX_FRAME_HEIGHT/8];   
    int SAD[CAM_MAX_SCANLINE/8][CAM_MAX_FRAME_HEIGHT/8];  
} CamMotionEstimation3DRSResults;

int camMotionEstimation3DRSInit(CamMotionEstimation3DRSParams *params, int seed, int lsearch, int rsearch, int bs, int scans, int candidates, int test0);
int camMotionEstimation3DRS(CamImage *current, CamImage *previous, CamMotionEstimation3DRSParams *params, CamMotionEstimation3DRSResults *results);


void camProject(const double extr[4][4], const double fc[2], const double cc[2], double x, double y, double z, int *xp, int *yp);

void camBackproject(const double extr[4][4], const double fc[2], const double cc[2], int xp, int yp, double z, double *x, double *y);

int camUndistort(CamImage *source, CamImage *dest,
                 const float* intrinsic_matrix,
                 const float* dist_coeffs);
int camUndistortFixed(CamImage *source, CamImage *dest,
                      const CAM_FIXED_POINT* intrinsic_matrix,
                      const CAM_FIXED_POINT* dist_coeffs);
int camUndistortBuildLUT(CamImage *source,
                         const float* intrinsic_matrix,
                         const float* dist_coeffs,
                         CamImage *LUTX, CamImage *LUTY);
int camUndistortLUT(CamImage *source, CamImage *dest,
                    CamImage *LUTX, CamImage *LUTY);


#endif // SWIG

#ifdef __cplusplus
}
#endif

#endif
