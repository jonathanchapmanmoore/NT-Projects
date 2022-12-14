/*
***************************************************************************
* This file comprises part of PDCurses. PDCurses is Public Domain software.
* You may use this code for whatever purposes you desire. This software
* is provided AS IS with NO WARRANTY whatsoever.
* Should this software be used in another application, an acknowledgement
* that PDCurses code is used would be appreciated, but is not mandatory.
*
* Any changes which you make to this software which may improve or enhance
* it, should be forwarded to the current maintainer for the benefit of 
* other users.
*
* The only restriction placed on this code is that no distribution of
* modified PDCurses code be made under the PDCurses name, by anyone
* other than the current maintainer.
* 
* See the file maintain.er for details of the current maintainer.
*
* This file is NOT public domain software.  It is Copyright, Mark Hessling
* 1994,1995.
***************************************************************************
*/
#define XtNlines         "lines"
#define XtCLines         "Lines"
#define XtNcols          "cols"
#define XtCCols          "Cols"

#define XtCNormalFont    "NormalFont"
#define XtNnormalFont    "normalFont"
#define XtCBoldFont      "BoldFont"
#define XtNboldFont      "boldFont"

#define XtCPointer       "Pointer"
#define XtNpointer       "pointer"

#define XtCShmmin        "Shmmin"
#define XtNshmmin        "shmmin"

#define XtCComposeKey    "ComposeKey"
#define XtNcomposeKey    "composeKey"

#define XtCDoubleClickPeriod   "DoubleClickPeriod"
#define XtNdoubleClickPeriod   "doubleClickPeriod"

#define XtCPointerForeColor "PointerForeColor"
#define XtNpointerForeColor "pointerForeColor"
#define XtCPointerBackColor "PointerBackColor"
#define XtNpointerBackColor "pointerBackColor"

#define XtNcursorColor   "cursorColor"
#define XtCCursorColor   "CursorColor"

#define XtNcolorBlack    "colorBlack"
#define XtCColorBlack    "ColorBlack"
#define XtNcolorRed      "colorRed"
#define XtCColorRed      "ColorRed"
#define XtNcolorGreen    "colorGreen"
#define XtCColorGreen    "ColorGreen"
#define XtNcolorYellow   "colorYellow"
#define XtCColorYellow   "ColorYellow"
#define XtNcolorBlue     "colorBlue"
#define XtCColorBlue     "ColorBlue"
#define XtNcolorMagenta  "colorMagenta"
#define XtCColorMagenta  "ColorMagenta"
#define XtNcolorCyan     "colorCyan"
#define XtCColorCyan     "ColorCyan"
#define XtNcolorWhite    "colorWhite"
#define XtCColorWhite    "ColorWhite"

#ifndef MAX_PATH
#  define MAX_PATH 256
#endif

typedef struct
{
 int lines;
 int cols;
 Pixel cursorColor;
 Pixel colorBlack;
 Pixel colorRed;
 Pixel colorGreen;
 Pixel colorYellow;
 Pixel colorBlue;
 Pixel colorMagenta;
 Pixel colorCyan;
 Pixel colorWhite;
 Pixel pointerForeColor;
 Pixel pointerBackColor;
 XFontStruct *normalfont;
 XFontStruct *boldfont;
 char *bitmapFile;
 char *composeKey;
 Cursor pointer;
 int shmmin;
 int borderWidth;
 int borderColor;
 int doubleClickPeriod;
} AppData;
AppData app_data;

#define XCURSESNORMALFONTINFO   app_data.normalfont
#define XCURSESBOLDFONTINFO     app_data.boldfont
#define XCURSESLINES            app_data.lines
#define XCURSESCOLS             app_data.cols
#define XCURSESBITMAPFILE       app_data.bitmapFile
#define XCURSESCOMPOSEKEY       app_data.composeKey
#define XCURSESPOINTER          app_data.pointer
#define XCURSESPOINTERFORECOLOR app_data.pointerForeColor
#define XCURSESPOINTERBACKCOLOR app_data.pointerBackColor
#define XCURSESCURSORCOLOR      app_data.cursorColor
#define XCURSESSHMMIN           app_data.shmmin
#define XCURSESBORDERWIDTH      app_data.borderWidth
#define XCURSESBORDERCOLOR      app_data.borderColor
#define XCURSESDOUBLECLICKPERIOD app_data.doubleClickPeriod

static XtResource app_resources[] =
{
 {
  XtNlines,
  XtCLines,
  XtRInt,
  sizeof(int),
  XtOffsetOf(AppData,lines),
  XtRImmediate,
  (XtPointer)24,
 },
 {
  XtNcols,
  XtCCols,
  XtRInt,
  sizeof(int),
  XtOffsetOf(AppData,cols),
  XtRImmediate,
  (XtPointer)80,
 },
 {
  XtNcursorColor,
  XtCCursorColor,
  XtRPixel,
  sizeof(Pixel),
  XtOffsetOf(AppData,cursorColor),
  XtRString,
  (XtPointer)"Red",
 },
 {
  XtNcolorBlack,
  XtCColorBlack,
  XtRPixel,
  sizeof(Pixel),
  XtOffsetOf(AppData,colorBlack),
  XtRString,
  (XtPointer)"Black",
 },
 {
  XtNcolorRed,
  XtCColorRed,
  XtRPixel,
  sizeof(Pixel),
  XtOffsetOf(AppData,colorRed),
  XtRString,
  (XtPointer)"Red",
 },
 {
  XtNcolorGreen,
  XtCColorGreen,
  XtRPixel,
  sizeof(Pixel),
  XtOffsetOf(AppData,colorGreen),
  XtRString,
  (XtPointer)"Green",
 },
 {
  XtNcolorYellow,
  XtCColorYellow,
  XtRPixel,
  sizeof(Pixel),
  XtOffsetOf(AppData,colorYellow),
  XtRString,
  (XtPointer)"Yellow",
 },
 {
  XtNcolorBlue,
  XtCColorBlue,
  XtRPixel,
  sizeof(Pixel),
  XtOffsetOf(AppData,colorBlue),
  XtRString,
  (XtPointer)"Blue",
 },
 {
  XtNcolorMagenta,
  XtCColorMagenta,
  XtRPixel,
  sizeof(Pixel),
  XtOffsetOf(AppData,colorMagenta),
  XtRString,
  (XtPointer)"Magenta",
 },
 {
  XtNcolorCyan,
  XtCColorCyan,
  XtRPixel,
  sizeof(Pixel),
  XtOffsetOf(AppData,colorCyan),
  XtRString,
  (XtPointer)"Cyan",
 },
 {
  XtNcolorWhite,
  XtCColorWhite,
  XtRPixel,
  sizeof(Pixel),
  XtOffsetOf(AppData,colorWhite),
  XtRString,
  (XtPointer)"White",
 },
 {
  XtNnormalFont,
  XtCNormalFont,
  XtRFontStruct,
  sizeof(XFontStruct),
  XtOffsetOf(AppData,normalfont),
  XtRString,
  (XtPointer)"7x13",
 },
 {
  XtNboldFont,
  XtCBoldFont,
  XtRFontStruct,
  sizeof(XFontStruct),
  XtOffsetOf(AppData,boldfont),
  XtRString,
  (XtPointer)"7x13bold",
 },
 {
  XtNbitmap,
  XtCBitmap,
  XtRString,
  MAX_PATH,
  XtOffsetOf(AppData,bitmapFile),
  XtRString,
  (XtPointer)"",
 },
 {
  XtNcomposeKey,
  XtCComposeKey,
  XtRString,
  MAX_PATH,
  XtOffsetOf(AppData,composeKey),
  XtRString,
  (XtPointer)"",
 },
 {
  XtNpointer,
  XtCPointer,
  XtRCursor,
  sizeof(Cursor),
  XtOffsetOf(AppData,pointer),
  XtRString,
  (XtPointer)"xterm",
 },
 {
  XtNpointerForeColor,
  XtCPointerForeColor,
  XtRPixel,
  sizeof(Pixel),
  XtOffsetOf(AppData,pointerForeColor),
  XtRString,
  (XtPointer)"Black",
 },
 {
  XtNpointerBackColor,
  XtCPointerBackColor,
  XtRPixel,
  sizeof(Pixel),
  XtOffsetOf(AppData,pointerBackColor),
  XtRString,
  (XtPointer)"White",
 },
 {
  XtNshmmin,
  XtCShmmin,
  XtRInt,
  sizeof(int),
  XtOffsetOf(AppData,shmmin),
  XtRImmediate,
  (XtPointer)0,
 },
 {
  XtNborderWidth,
  XtCBorderWidth,
  XtRInt,
  sizeof(int),
  XtOffsetOf(AppData,borderWidth),
  XtRImmediate,
  (XtPointer)0,
 },
 {
  XtNborderColor,
  XtCBorderColor,
  XtRPixel,
  sizeof(Pixel),
  XtOffsetOf(AppData,borderColor),
  XtRString,
  (XtPointer)"Black",
 },
 {
  XtNdoubleClickPeriod,
  XtCDoubleClickPeriod,
  XtRInt,
  sizeof(int),
  XtOffsetOf(AppData,doubleClickPeriod),
  XtRImmediate,
  (XtPointer)200,
 },
};

/***************************************************************************/
/* Default icons for XCurses applications.                                 */
/***************************************************************************/
#define BIG_ICON_WIDTH 64
#define BIG_ICON_HEIGHT 64
static unsigned char big_icon_bitmap_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
   0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x00, 0xc0, 0x00, 0x00,
   0x00, 0x00, 0xfc, 0x03, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x07,
   0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x07, 0x00, 0x18, 0x00, 0x00,
   0x00, 0x00, 0xf0, 0x0f, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1f,
   0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x3f, 0x00, 0x06, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0x3f, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x7f,
   0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfe, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe,
   0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x33, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xf8, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0,
   0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0e, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x60, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb0,
   0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x7f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x98, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
   0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xfe, 0x01, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x03, 0xfc, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01,
   0xfc, 0x03, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0xf8, 0x07, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
   0xe0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0xe0, 0x1f, 0x00, 0x00,
   0x00, 0x00, 0x18, 0x00, 0xc0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00,
   0x80, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0xff, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x23, 0x50, 0x1e,
   0x7c, 0xf0, 0xe0, 0x03, 0x60, 0x26, 0x50, 0x33, 0xc6, 0x98, 0x31, 0x06,
   0x30, 0x2c, 0xd0, 0x61, 0x83, 0x0d, 0x1b, 0x0c, 0x10, 0x28, 0xd0, 0x40,
   0x01, 0x05, 0x0a, 0x08, 0x10, 0x20, 0x50, 0x00, 0x01, 0x05, 0x0a, 0x08,
   0x10, 0x20, 0x50, 0x00, 0x03, 0x04, 0x1a, 0x00, 0x10, 0x20, 0x50, 0x00,
   0x06, 0x04, 0x32, 0x00, 0x10, 0x20, 0x50, 0x00, 0x7c, 0xfc, 0xe3, 0x03,
   0x10, 0x20, 0x50, 0x00, 0xc0, 0x04, 0x00, 0x06, 0x10, 0x20, 0x50, 0x00,
   0x80, 0x05, 0x00, 0x0c, 0x10, 0x20, 0x50, 0x00, 0x01, 0x05, 0x0a, 0x08,
   0x10, 0x28, 0x50, 0x00, 0x01, 0x05, 0x0a, 0x08, 0x30, 0x6c, 0x58, 0x00,
   0x83, 0x0d, 0x1b, 0x0c, 0x60, 0xc6, 0x4c, 0x00, 0xc6, 0x98, 0x31, 0x06,
   0xc0, 0x83, 0x47, 0x00, 0x7c, 0xf0, 0xe0, 0x03, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#define LITTLE_ICON_WIDTH 32
#define LITTLE_ICON_HEIGHT 32
static unsigned char little_icon_bitmap_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x80, 0x07, 0x00, 0x01, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x1e, 0x40, 0x00,
   0x00, 0x3c, 0x20, 0x00, 0x00, 0x78, 0x10, 0x00, 0x00, 0xf0, 0x08, 0x00,
   0x00, 0xe0, 0x05, 0x00, 0x00, 0xc0, 0x06, 0x00, 0x00, 0x40, 0x07, 0x00,
   0x00, 0x20, 0x0f, 0x00, 0x00, 0x10, 0x1e, 0x00, 0x00, 0x08, 0x3c, 0x00,
   0x00, 0x04, 0x78, 0x00, 0x00, 0x02, 0xf0, 0x00, 0x00, 0x01, 0xe0, 0x01,
   0x80, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x4c, 0x2a, 0xc6, 0x18, 0x52, 0x5a, 0x29, 0x25, 0x42, 0x0a, 0x29, 0x25,
   0x42, 0x0a, 0xe2, 0x09, 0x42, 0x0a, 0x24, 0x10, 0x42, 0x0a, 0x29, 0x20,
   0x52, 0x0a, 0x29, 0x25, 0x8c, 0x09, 0xc6, 0x18, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
