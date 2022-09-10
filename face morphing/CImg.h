
/*
 #
 #  File            : CImg.h
 #                    ( C++ header file )
 #
 #  Description     : The C++ Template Image Processing Toolkit.
 #                    This file is the main component of the CImg Library project.
 #                    ( http://cimg.eu )
 #
 #  Project manager : David Tschumperle.
 #                    ( http://tschumperle.users.greyc.fr/ )
 #
 #                    A complete list of contributors is available in file 'README.txt'
 #                    distributed within the CImg package.
 #
 #  Licenses        : This file is 'dual-licensed', you have to choose one
 #                    of the two licenses below to apply.
 #
 #                    CeCILL-C
 #                    The CeCILL-C license is close to the GNU LGPL.
 #                    ( http://www.cecill.info/licences/Licence_CeCILL-C_V1-en.html )
 #
 #                or  CeCILL v2.1
 #                    The CeCILL license is compatible with the GNU GPL.
 #                    ( http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.html )
 #
 #  This software is governed either by the CeCILL or the CeCILL-C license
 #  under French law and abiding by the rules of distribution of free software.
 #  You can  use, modify and or redistribute the software under the terms of
 #  the CeCILL or CeCILL-C licenses as circulated by CEA, CNRS and INRIA
 #  at the following URL: "http://www.cecill.info".
 #
 #  As a counterpart to the access to the source code and  rights to copy,
 #  modify and redistribute granted by the license, users are provided only
 #  with a limited warranty  and the software's author,  the holder of the
 #  economic rights,  and the successive licensors  have only  limited
 #  liability.
 #
 #  In this respect, the user's attention is drawn to the risks associated
 #  with loading,  using,  modifying and/or developing or reproducing the
 #  software by the user in light of its specific status of free software,
 #  that may mean  that it is complicated to manipulate,  and  that  also
 #  therefore means  that it is reserved for developers  and  experienced
 #  professionals having in-depth computer knowledge. Users are therefore
 #  encouraged to load and test the software's suitability as regards their
 #  requirements in conditions enabling the security of their systems and/or
 #  data to be ensured and,  more generally, to use and operate it in the
 #  same conditions as regards security.
 #
 #  The fact that you are presently reading this means that you have had
 #  knowledge of the CeCILL and CeCILL-C licenses and that you accept its terms.
 #
*/

// Set version number of the library.
#ifndef cimg_version
#define cimg_version 240

/*-----------------------------------------------------------
 #
 # Test and possibly auto-set CImg configuration variables
 # and include required headers.
 #
 # If you find that the default configuration variables are
 # not adapted to your system, you can override their values
 # before including the header file "CImg.h"
 # (use the #define directive).
 #
 ------------------------------------------------------------*/

// Include standard C++ headers.
// This is the minimal set of required headers to make CImg-based codes compile.
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <cmath>
#include <cfloat>
#include <climits>
#include <ctime>
#include <exception>
#include <algorithm>

// Detect/configure OS variables.
//
// Define 'cimg_OS' to: '0' for an unknown OS (will try to minize library dependencies).
//                      '1' for a Unix-like OS (Linux, Solaris, BSD, MacOSX, Irix, ...).
//                      '2' for Microsoft Windows.
//                      (auto-detection is performed if 'cimg_OS' is not set by the user).
#ifndef cimg_OS
#if defined(unix)        || defined(__unix)      || defined(__unix__) \
 || defined(linux)       || defined(__linux)     || defined(__linux__) \
 || defined(sun)         || defined(__sun) \
 || defined(BSD)         || defined(__OpenBSD__) || defined(__NetBSD__) \
 || defined(__FreeBSD__) || defined (__DragonFly__) \
 || defined(sgi)         || defined(__sgi) \
 || defined(__MACOSX__)  || defined(__APPLE__) \
 || defined(__CYGWIN__)
#define cimg_OS 1
#elif defined(_MSC_VER) || defined(WIN32)  || defined(_WIN32) || defined(__WIN32__) \
   || defined(WIN64)    || defined(_WIN64) || defined(__WIN64__)
#define cimg_OS 2
#else
#define cimg_OS 0
#endif
#elif !(cimg_OS==0 || cimg_OS==1 || cimg_OS==2)
#error CImg Library: Invalid configuration variable 'cimg_OS'.
#error (correct values are '0 = unknown OS', '1 = Unix-like OS', '2 = Microsoft Windows').
#endif
#ifndef cimg_date
#define cimg_date __DATE__
#endif
#ifndef cimg_time
#define cimg_time __TIME__
#endif

// Disable silly warnings on some Microsoft VC++ compilers.
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4127)
#pragma warning(disable:4244)
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#pragma warning(disable:4319)
#pragma warning(disable:4512)
#pragma warning(disable:4571)
#pragma warning(disable:4640)
#pragma warning(disable:4706)
#pragma warning(disable:4710)
#pragma warning(disable:4800)
#pragma warning(disable:4804)
#pragma warning(disable:4820)
#pragma warning(disable:4996)

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE 1
#endif
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#endif
#ifndef _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE 1
#endif
#endif

// Define correct string functions for each compiler and OS.
#if cimg_OS==2 && defined(_MSC_VER)
#define cimg_sscanf std::sscanf
#define cimg_sprintf std::sprintf
#define cimg_snprintf cimg::_snprintf
#define cimg_vsnprintf cimg::_vsnprintf
#else
#include <stdio.h>
#if defined(__MACOSX__) || defined(__APPLE__)
#define cimg_sscanf cimg::_sscanf
#define cimg_sprintf cimg::_sprintf
#define cimg_snprintf cimg::_snprintf
#define cimg_vsnprintf cimg::_vsnprintf
#else
#define cimg_sscanf std::sscanf
#define cimg_sprintf std::sprintf
#define cimg_snprintf snprintf
#define cimg_vsnprintf vsnprintf
#endif
#endif

// Include OS-specific headers.
#if cimg_OS==1
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fnmatch.h>
#elif cimg_OS==2
#ifndef std_fopen
#define std_fopen cimg::win_fopen
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#ifndef _WIN32_IE
#define _WIN32_IE 0x0400
#endif
#include <shlobj.h>
#include <process.h>
#include <io.h>
#endif

// Look for C++11 features.
#ifndef cimg_use_cpp11
#if __cplusplus>201100
#define cimg_use_cpp11 1
#else
#define cimg_use_cpp11 0
#endif
#endif
#if cimg_use_cpp11==1
#include <initializer_list>
#include <utility>
#endif

// Convenient macro to define pragma
#ifdef _MSC_VER
#define cimg_pragma(x) __pragma(x)
#else
#define cimg_pragma(x) _Pragma(#x)
#endif

// Define own types 'cimg_long/ulong' and 'cimg_int64/uint64' to ensure portability.
// ( constrained to 'sizeof(cimg_ulong/cimg_long) = sizeof(void*)' and 'sizeof(cimg_int64/cimg_uint64)=8' ).
#if cimg_OS==2

#define cimg_uint64 unsigned __int64
#define cimg_int64 __int64
#define cimg_ulong UINT_PTR
#define cimg_long INT_PTR
#ifdef _MSC_VER
#define cimg_fuint64 "%I64u"
#define cimg_fint64 "%I64d"
#else
#define cimg_fuint64 "%llu"
#define cimg_fint64 "%lld"
#endif

#else

#if UINTPTR_MAX==0xffffffff || defined(__arm__) || defined(_M_ARM) || ((ULONG_MAX)==(UINT_MAX))
#define cimg_uint64 unsigned long long
#define cimg_int64 long long
#define cimg_fuint64 "%llu"
#define cimg_fint64 "%lld"
#else
#define cimg_uint64 unsigned long
#define cimg_int64 long
#define cimg_fuint64 "%lu"
#define cimg_fint64 "%ld"
#endif

#if defined(__arm__) || defined(_M_ARM)
#define cimg_ulong unsigned long long
#define cimg_long long long
#else
#define cimg_ulong unsigned long
#define cimg_long long
#endif

#endif

// Configure filename separator.
//
// Filename separator is set by default to '/', except for Windows where it is '\'.
#ifndef cimg_file_separator
#if cimg_OS==2
#define cimg_file_separator '\\'
#else
#define cimg_file_separator '/'
#endif
#endif

// Configure verbosity of output messages.
//
// Define 'cimg_verbosity' to: '0' to hide library messages (quiet mode).
//                             '1' to output library messages on the console.
//                             '2' to output library messages on a basic dialog window (default behavior).
//                             '3' to do as '1' + add extra warnings (may slow down the code!).
//                             '4' to do as '2' + add extra warnings (may slow down the code!).
//
// Define 'cimg_strict_warnings' to replace warning messages by exception throwns.
//
// Define 'cimg_use_vt100' to allow output of color messages on VT100-compatible terminals.
#ifndef cimg_verbosity
#if cimg_OS==2
#define cimg_verbosity 2
#else
#define cimg_verbosity 1
#endif
#elif !(cimg_verbosity==0 || cimg_verbosity==1 || cimg_verbosity==2 || cimg_verbosity==3 || cimg_verbosity==4)
#error CImg Library: Configuration variable 'cimg_verbosity' is badly defined.
#error (should be { 0=quiet | 1=console | 2=dialog | 3=console+warnings | 4=dialog+warnings }).
#endif

// Configure display framework.
//
// Define 'cimg_display' to: '0' to disable display capabilities.
//                           '1' to use the X-Window framework (X11).
//                           '2' to use the Microsoft GDI32 framework.
#ifndef cimg_display
#if cimg_OS==0
#define cimg_display 0
#elif cimg_OS==1
#define cimg_display 1
#elif cimg_OS==2
#define cimg_display 2
#endif
#elif !(cimg_display==0 || cimg_display==1 || cimg_display==2)
#error CImg Library: Configuration variable 'cimg_display' is badly defined.
#error (should be { 0=none | 1=X-Window (X11) | 2=Microsoft GDI32 }).
#endif

// Configure the 'abort' signal handler (does nothing by default).
// A typical signal handler can be defined in your own source like this:
// #define cimg_abort_test if (is_abort) throw CImgAbortException("")
//
// where 'is_abort' is a boolean variable defined somewhere in your code and reachable in the method.
// 'cimg_abort_test2' does the same but is called more often (in inner loops).
#if defined(cimg_abort_test) && defined(cimg_use_openmp)

// Define abort macros to be used with OpenMP.
#ifndef _cimg_abort_init_omp
#define _cimg_abort_init_omp bool _cimg_abort_go_omp = true; cimg::unused(_cimg_abort_go_omp)
#endif
#ifndef _cimg_abort_try_omp
#define _cimg_abort_try_omp if (_cimg_abort_go_omp) try
#endif
#ifndef _cimg_abort_catch_omp
#define _cimg_abort_catch_omp catch (CImgAbortException&) { cimg_pragma(omp atomic) _cimg_abort_go_omp&=false; }
#endif
#ifdef cimg_abort_test2
#ifndef _cimg_abort_try_omp2
#define _cimg_abort_try_omp2 _cimg_abort_try_omp
#endif
#ifndef _cimg_abort_catch_omp2
#define _cimg_abort_catch_omp2 _cimg_abort_catch_omp
#endif
#ifndef _cimg_abort_catch_fill_omp
#define _cimg_abort_catch_fill_omp \
  catch (CImgException& e) { cimg_pragma(omp critical(abort)) CImg<charT>::string(e._message).move_to(is_error); \
                             cimg_pragma(omp atomic) _cimg_abort_go_omp&=false; }
#endif
#endif
#endif

#ifndef _cimg_abort_init_omp
#define _cimg_abort_init_omp
#endif
#ifndef _cimg_abort_try_omp
#define _cimg_abort_try_omp
#endif
#ifndef _cimg_abort_catch_omp
#define _cimg_abort_catch_omp
#endif
#ifndef _cimg_abort_try_omp2
#define _cimg_abort_try_omp2
#endif
#ifndef _cimg_abort_catch_omp2
#define _cimg_abort_catch_omp2
#endif
#ifndef _cimg_abort_catch_fill_omp
#define _cimg_abort_catch_fill_omp
#endif
#ifndef cimg_abort_init
#define cimg_abort_init
#endif
#ifndef cimg_abort_test
#define cimg_abort_test
#endif
#ifndef cimg_abort_test2
#define cimg_abort_test2
#endif
#ifndef std_fopen
#define std_fopen std::fopen
#endif

// Include display-specific headers.
#if cimg_display==1
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <pthread.h>
#ifdef cimg_use_xshm
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#endif
#ifdef cimg_use_xrandr
#include <X11/extensions/Xrandr.h>
#endif
#endif
#ifndef cimg_appname
#define cimg_appname "CImg"
#endif

// Configure OpenMP support.
// (http://www.openmp.org)
//
// Define 'cimg_use_openmp' to enable OpenMP support.
//
// OpenMP directives may be used in a (very) few CImg functions to get
// advantages of multi-core CPUs.
#ifdef cimg_use_openmp
#include <omp.h>
#define cimg_pragma_openmp(p) cimg_pragma(omp p)
#else
#define cimg_pragma_openmp(p)
#endif

// Configure OpenCV support.
// (http://opencv.willowgarage.com/wiki/)
//
// Define 'cimg_use_opencv' to enable OpenCV support.
//
// OpenCV library may be used to access images from cameras
// (see method 'CImg<T>::load_camera()').
#ifdef cimg_use_opencv
#ifdef True
#undef True
#define _cimg_redefine_True
#endif
#ifdef False
#undef False
#define _cimg_redefine_False
#endif
#include <cstddef>
#include "cv.h"
#include "highgui.h"
#endif

// Configure LibPNG support.
// (http://www.libpng.org)
//
// Define 'cimg_use_png' to enable LibPNG support.
//
// PNG library may be used to get a native support of '.png' files.
// (see methods 'CImg<T>::{load,save}_png()'.
#ifdef cimg_use_png
extern "C" {
#include "png.h"
}
#endif

// Configure LibJPEG support.
// (http://en.wikipedia.org/wiki/Libjpeg)
//
// Define 'cimg_use_jpeg' to enable LibJPEG support.
//
// JPEG library may be used to get a native support of '.jpg' files.
// (see methods 'CImg<T>::{load,save}_jpeg()').
#ifdef cimg_use_jpeg
extern "C" {
#include "jpeglib.h"
#include "setjmp.h"
}
#endif

// Configure LibTIFF support.
// (http://www.libtiff.org)
//
// Define 'cimg_use_tiff' to enable LibTIFF support.
//
// TIFF library may be used to get a native support of '.tif' files.
// (see methods 'CImg[List]<T>::{load,save}_tiff()').
#ifdef cimg_use_tiff
extern "C" {
#define uint64 uint64_hack_
#define int64 int64_hack_
#include "tiffio.h"
#undef uint64
#undef int64
}
#endif

// Configure LibMINC2 support.
// (http://en.wikibooks.org/wiki/MINC/Reference/MINC2.0_File_Format_Reference)
//
// Define 'cimg_use_minc2' to enable LibMINC2 support.
//
// MINC2 library may be used to get a native support of '.mnc' files.
// (see methods 'CImg<T>::{load,save}_minc2()').
#ifdef cimg_use_minc2
#include "minc_io_simple_volume.h"
#include "minc_1_simple.h"
#include "minc_1_simple_rw.h"
#endif

// Configure Zlib support.
// (http://www.zlib.net)
//
// Define 'cimg_use_zlib' to enable Zlib support.
//
// Zlib library may be used to allow compressed data in '.cimgz' files
// (see methods 'CImg[List]<T>::{load,save}_cimg()').
#ifdef cimg_use_zlib
extern "C" {
#include "zlib.h"
}
#endif

// Configure libcurl support.
// (http://curl.haxx.se/libcurl/)
//
// Define 'cimg_use_curl' to enable libcurl support.
//
// Libcurl may be used to get a native support of file downloading from the network.
// (see method 'cimg::load_network()'.)
#ifdef cimg_use_curl
#include "curl/curl.h"
#endif

// Configure Magick++ support.
// (http://www.imagemagick.org/Magick++)
//
// Define 'cimg_use_magick' to enable Magick++ support.
//
// Magick++ library may be used to get a native support of various image file formats.
// (see methods 'CImg<T>::{load,save}()').
#ifdef cimg_use_magick
#include "Magick++.h"
#endif

// Configure FFTW3 support.
// (http://www.fftw.org)
//
// Define 'cimg_use_fftw3' to enable libFFTW3 support.
//
// FFTW3 library may be used to efficiently compute the Fast Fourier Transform
// of image data, without restriction on the image size.
// (see method 'CImg[List]<T>::FFT()').
#ifdef cimg_use_fftw3
extern "C" {
#include "fftw3.h"
}
#endif

// Configure LibBoard support.
// (http://libboard.sourceforge.net/)
//
// Define 'cimg_use_board' to enable Board support.
//
// Board library may be used to draw 3d objects in vector-graphics canvas
// that can be saved as '.ps' or '.svg' files afterwards.
// (see method 'CImg<T>::draw_object3d()').
#ifdef cimg_use_board
#include "Board.h"
#endif

// Configure OpenEXR support.
// (http://www.openexr.com/)
//
// Define 'cimg_use_openexr' to enable OpenEXR support.
//
// OpenEXR library may be used to get a native support of '.exr' files.
// (see methods 'CImg<T>::{load,save}_exr()').
#ifdef cimg_use_openexr
#include "ImfRgbaFile.h"
#include "ImfInputFile.h"
#include "ImfChannelList.h"
#include "ImfMatrixAttribute.h"
#include "ImfArray.h"
#endif

// Configure TinyEXR support.
// (https://github.com/syoyo/tinyexr)
//
// Define 'cimg_use_tinyexr' to enable TinyEXR support.
//
// TinyEXR is a small, single header-only library to load and save OpenEXR(.exr) images.
#ifdef cimg_use_tinyexr
#ifndef TINYEXR_IMPLEMENTATION
#define TINYEXR_IMPLEMENTATION
#endif
#include "tinyexr.h"
#endif

// Lapack configuration.
// (http://www.netlib.org/lapack)
//
// Define 'cimg_use_lapack' to enable LAPACK support.
//
// Lapack library may be used in several CImg methods to speed up
// matrix computations (eigenvalues, inverse, ...).
#ifdef cimg_use_lapack
extern "C" {
  extern void sgetrf_(int*, int*, float*, int*, int*, int*);
  extern void sgetri_(int*, float*, int*, int*, float*, int*, int*);
  extern void sgetrs_(char*, int*, int*, float*, int*, int*, float*, int*, int*);
  extern void sgesvd_(char*, char*, int*, int*, float*, int*, float*, float*, int*, float*, int*, float*, int*, int*);
  extern void ssyev_(char*, char*, int*, float*, int*, float*, float*, int*, int*);
  extern void dgetrf_(int*, int*, double*, int*, int*, int*);
  extern void dgetri_(int*, double*, int*, int*, double*, int*, int*);
  extern void dgetrs_(char*, int*, int*, double*, int*, int*, double*, int*, int*);
  extern void dgesvd_(char*, char*, int*, int*, double*, int*, double*, double*,
                      int*, double*, int*, double*, int*, int*);
  extern void dsyev_(char*, char*, int*, double*, int*, double*, double*, int*, int*);
  extern void dgels_(char*, int*,int*,int*,double*,int*,double*,int*,double*,int*,int*);
  extern void sgels_(char*, int*,int*,int*,float*,int*,float*,int*,float*,int*,int*);
}
#endif

// Check if min/max/PI macros are defined.
//
// CImg does not compile if macros 'min', 'max' or 'PI' are defined,
// because it redefines functions min(), max() and const variable PI in the cimg:: namespace.
// so it '#undef' these macros if necessary, and restore them to reasonable
// values at the end of this file.
#ifdef min
#undef min
#define _cimg_redefine_min
#endif
#ifdef max
#undef max
#define _cimg_redefine_max
#endif
#ifdef PI
#undef PI
#define _cimg_redefine_PI
#endif

// Define 'cimg_library' namespace suffix.
//
// You may want to add a suffix to the 'cimg_library' namespace, for instance if you need to work
// with several versions of the library at the same time.
#ifdef cimg_namespace_suffix
#define __cimg_library_suffixed(s) cimg_library_##s
#define _cimg_library_suffixed(s) __cimg_library_suffixed(s)
#define cimg_library_suffixed _cimg_library_suffixed(cimg_namespace_suffix)
#else
#define cimg_library_suffixed cimg_library
#endif

/*------------------------------------------------------------------------------
  #
  # Define user-friendly macros.
  #
  # These CImg macros are prefixed by 'cimg_' and can be used safely in your own
  # code. They are useful to parse command line options, or to write image loops.
  #
  ------------------------------------------------------------------------------*/

// Macros to define program usage, and retrieve command line arguments.
#define cimg_usage(usage) cimg_library_suffixed::cimg::option((char*)0,argc,argv,(char*)0,usage,false)
#define cimg_help(str) cimg_library_suffixed::cimg::option((char*)0,argc,argv,str,(char*)0)
#define cimg_option(name,defaut,usage) cimg_library_suffixed::cimg::option(name,argc,argv,defaut,usage)

// Macros to define and manipulate local neighborhoods.
#define CImg_2x2(I,T) T I[4]; \
                      T& I##cc = I[0]; T& I##nc = I[1]; \
                      T& I##cn = I[2]; T& I##nn = I[3]; \
                      I##cc = I##nc = \
                      I##cn = I##nn = 0

#define CImg_3x3(I,T) T I[9]; \
                      T& I##pp = I[0]; T& I##cp = I[1]; T& I##np = I[2]; \
                      T& I##pc = I[3]; T& I##cc = I[4]; T& I##nc = I[5]; \
                      T& I##pn = I[6]; T& I##cn = I[7]; T& I##nn = I[8]; \
                      I##pp = I##cp = I##np = \
                      I##pc = I##cc = I##nc = \
                      I##pn = I##cn = I##nn = 0

#define CImg_4x4(I,T) T I[16]; \
                      T& I##pp = I[0]; T& I##cp = I[1]; T& I##np = I[2]; T& I##ap = I[3]; \
                      T& I##pc = I[4]; T& I##cc = I[5]; T& I##nc = I[6]; T& I##ac = I[7]; \
                      T& I##pn = I[8]; T& I##cn = I[9]; T& I##nn = I[10]; T& I##an = I[11]; \
                      T& I##pa = I[12]; T& I##ca = I[13]; T& I##na = I[14]; T& I##aa = I[15]; \
                      I##pp = I##cp = I##np = I##ap = \
                      I##pc = I##cc = I##nc = I##ac = \
                      I##pn = I##cn = I##nn = I##an = \
                      I##pa = I##ca = I##na = I##aa = 0

#define CImg_5x5(I,T) T I[25]; \
                      T& I##bb = I[0]; T& I##pb = I[1]; T& I##cb = I[2]; T& I##nb = I[3]; T& I##ab = I[4]; \
                      T& I##bp = I[5]; T& I##pp = I[6]; T& I##cp = I[7]; T& I##np = I[8]; T& I##ap = I[9]; \
                      T& I##bc = I[10]; T& I##pc = I[11]; T& I##cc = I[12]; T& I##nc = I[13]; T& I##ac = I[14]; \
                      T& I##bn = I[15]; T& I##pn = I[16]; T& I##cn = I[17]; T& I##nn = I[18]; T& I##an = I[19]; \
                      T& I##ba = I[20]; T& I##pa = I[21]; T& I##ca = I[22]; T& I##na = I[23]; T& I##aa = I[24]; \
                      I##bb = I##pb = I##cb = I##nb = I##ab = \
                      I##bp = I##pp = I##cp = I##np = I##ap = \
                      I##bc = I##pc = I##cc = I##nc = I##ac = \
                      I##bn = I##pn = I##cn = I##nn = I##an = \
                      I##ba = I##pa = I##ca = I##na = I##aa = 0

#define CImg_2x2x2(I,T) T I[8]; \
                      T& I##ccc = I[0]; T& I##ncc = I[1]; \
                      T& I##cnc = I[2]; T& I##nnc = I[3]; \
                      T& I##ccn = I[4]; T& I##ncn = I[5]; \
                      T& I##cnn = I[6]; T& I##nnn = I[7]; \
                      I##ccc = I##ncc = \
                      I##cnc = I##nnc = \
                      I##ccn = I##ncn = \
                      I##cnn = I##nnn = 0

#define CImg_3x3x3(I,T) T I[27]; \
                      T& I##ppp = I[0]; T& I##cpp = I[1]; T& I##npp = I[2]; \
                      T& I##pcp = I[3]; T& I##ccp = I[4]; T& I##ncp = I[5]; \
                      T& I##pnp = I[6]; T& I##cnp = I[7]; T& I##nnp = I[8]; \
                      T& I##ppc = I[9]; T& I##cpc = I[10]; T& I##npc = I[11]; \
                      T& I##pcc = I[12]; T& I##ccc = I[13]; T& I##ncc = I[14]; \
                      T& I##pnc = I[15]; T& I##cnc = I[16]; T& I##nnc = I[17]; \
                      T& I##ppn = I[18]; T& I##cpn = I[19]; T& I##npn = I[20]; \
                      T& I##pcn = I[21]; T& I##ccn = I[22]; T& I##ncn = I[23]; \
                      T& I##pnn = I[24]; T& I##cnn = I[25]; T& I##nnn = I[26]; \
                      I##ppp = I##cpp = I##npp = \
                      I##pcp = I##ccp = I##ncp = \
                      I##pnp = I##cnp = I##nnp = \
                      I##ppc = I##cpc = I##npc = \
                      I##pcc = I##ccc = I##ncc = \
                      I##pnc = I##cnc = I##nnc = \
                      I##ppn = I##cpn = I##npn = \
                      I##pcn = I##ccn = I##ncn = \
                      I##pnn = I##cnn = I##nnn = 0

#define cimg_get2x2(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(x,y,z,c), I[1] = (T)(img)(_n1##x,y,z,c), I[2] = (T)(img)(x,_n1##y,z,c), \
  I[3] = (T)(img)(_n1##x,_n1##y,z,c)

#define cimg_get3x3(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(_p1##x,_p1##y,z,c), I[1] = (T)(img)(x,_p1##y,z,c), I[2] = (T)(img)(_n1##x,_p1##y,z,c), \
  I[3] = (T)(img)(_p1##x,y,z,c), I[4] = (T)(img)(x,y,z,c), I[5] = (T)(img)(_n1##x,y,z,c), \
  I[6] = (T)(img)(_p1##x,_n1##y,z,c), I[7] = (T)(img)(x,_n1##y,z,c), I[8] = (T)(img)(_n1##x,_n1##y,z,c)

#define cimg_get4x4(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(_p1##x,_p1##y,z,c), I[1] = (T)(img)(x,_p1##y,z,c), I[2] = (T)(img)(_n1##x,_p1##y,z,c), \
  I[3] = (T)(img)(_n2##x,_p1##y,z,c), I[4] = (T)(img)(_p1##x,y,z,c), I[5] = (T)(img)(x,y,z,c), \
  I[6] = (T)(img)(_n1##x,y,z,c), I[7] = (T)(img)(_n2##x,y,z,c), I[8] = (T)(img)(_p1##x,_n1##y,z,c), \
  I[9] = (T)(img)(x,_n1##y,z,c), I[10] = (T)(img)(_n1##x,_n1##y,z,c), I[11] = (T)(img)(_n2##x,_n1##y,z,c), \
  I[12] = (T)(img)(_p1##x,_n2##y,z,c), I[13] = (T)(img)(x,_n2##y,z,c), I[14] = (T)(img)(_n1##x,_n2##y,z,c), \
  I[15] = (T)(img)(_n2##x,_n2##y,z,c)

#define cimg_get5x5(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(_p2##x,_p2##y,z,c), I[1] = (T)(img)(_p1##x,_p2##y,z,c), I[2] = (T)(img)(x,_p2##y,z,c), \
  I[3] = (T)(img)(_n1##x,_p2##y,z,c), I[4] = (T)(img)(_n2##x,_p2##y,z,c), I[5] = (T)(img)(_p2##x,_p1##y,z,c), \
  I[6] = (T)(img)(_p1##x,_p1##y,z,c), I[7] = (T)(img)(x,_p1##y,z,c), I[8] = (T)(img)(_n1##x,_p1##y,z,c), \
  I[9] = (T)(img)(_n2##x,_p1##y,z,c), I[10] = (T)(img)(_p2##x,y,z,c), I[11] = (T)(img)(_p1##x,y,z,c), \
  I[12] = (T)(img)(x,y,z,c), I[13] = (T)(img)(_n1##x,y,z,c), I[14] = (T)(img)(_n2##x,y,z,c), \
  I[15] = (T)(img)(_p2##x,_n1##y,z,c), I[16] = (T)(img)(_p1##x,_n1##y,z,c), I[17] = (T)(img)(x,_n1##y,z,c), \
  I[18] = (T)(img)(_n1##x,_n1##y,z,c), I[19] = (T)(img)(_n2##x,_n1##y,z,c), I[20] = (T)(img)(_p2##x,_n2##y,z,c), \
  I[21] = (T)(img)(_p1##x,_n2##y,z,c), I[22] = (T)(img)(x,_n2##y,z,c), I[23] = (T)(img)(_n1##x,_n2##y,z,c), \
  I[24] = (T)(img)(_n2##x,_n2##y,z,c)

#define cimg_get6x6(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(_p2##x,_p2##y,z,c), I[1] = (T)(img)(_p1##x,_p2##y,z,c), I[2] = (T)(img)(x,_p2##y,z,c), \
  I[3] = (T)(img)(_n1##x,_p2##y,z,c), I[4] = (T)(img)(_n2##x,_p2##y,z,c), I[5] = (T)(img)(_n3##x,_p2##y,z,c), \
  I[6] = (T)(img)(_p2##x,_p1##y,z,c), I[7] = (T)(img)(_p1##x,_p1##y,z,c), I[8] = (T)(img)(x,_p1##y,z,c), \
  I[9] = (T)(img)(_n1##x,_p1##y,z,c), I[10] = (T)(img)(_n2##x,_p1##y,z,c), I[11] = (T)(img)(_n3##x,_p1##y,z,c), \
  I[12] = (T)(img)(_p2##x,y,z,c), I[13] = (T)(img)(_p1##x,y,z,c), I[14] = (T)(img)(x,y,z,c), \
  I[15] = (T)(img)(_n1##x,y,z,c), I[16] = (T)(img)(_n2##x,y,z,c), I[17] = (T)(img)(_n3##x,y,z,c), \
  I[18] = (T)(img)(_p2##x,_n1##y,z,c), I[19] = (T)(img)(_p1##x,_n1##y,z,c), I[20] = (T)(img)(x,_n1##y,z,c), \
  I[21] = (T)(img)(_n1##x,_n1##y,z,c), I[22] = (T)(img)(_n2##x,_n1##y,z,c), I[23] = (T)(img)(_n3##x,_n1##y,z,c), \
  I[24] = (T)(img)(_p2##x,_n2##y,z,c), I[25] = (T)(img)(_p1##x,_n2##y,z,c), I[26] = (T)(img)(x,_n2##y,z,c), \
  I[27] = (T)(img)(_n1##x,_n2##y,z,c), I[28] = (T)(img)(_n2##x,_n2##y,z,c), I[29] = (T)(img)(_n3##x,_n2##y,z,c), \
  I[30] = (T)(img)(_p2##x,_n3##y,z,c), I[31] = (T)(img)(_p1##x,_n3##y,z,c), I[32] = (T)(img)(x,_n3##y,z,c), \
  I[33] = (T)(img)(_n1##x,_n3##y,z,c), I[34] = (T)(img)(_n2##x,_n3##y,z,c), I[35] = (T)(img)(_n3##x,_n3##y,z,c)

#define cimg_get7x7(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(_p3##x,_p3##y,z,c), I[1] = (T)(img)(_p2##x,_p3##y,z,c), I[2] = (T)(img)(_p1##x,_p3##y,z,c), \
  I[3] = (T)(img)(x,_p3##y,z,c), I[4] = (T)(img)(_n1##x,_p3##y,z,c), I[5] = (T)(img)(_n2##x,_p3##y,z,c), \
  I[6] = (T)(img)(_n3##x,_p3##y,z,c), I[7] = (T)(img)(_p3##x,_p2##y,z,c), I[8] = (T)(img)(_p2##x,_p2##y,z,c), \
  I[9] = (T)(img)(_p1##x,_p2##y,z,c), I[10] = (T)(img)(x,_p2##y,z,c), I[11] = (T)(img)(_n1##x,_p2##y,z,c), \
  I[12] = (T)(img)(_n2##x,_p2##y,z,c), I[13] = (T)(img)(_n3##x,_p2##y,z,c), I[14] = (T)(img)(_p3##x,_p1##y,z,c), \
  I[15] = (T)(img)(_p2##x,_p1##y,z,c), I[16] = (T)(img)(_p1##x,_p1##y,z,c), I[17] = (T)(img)(x,_p1##y,z,c), \
  I[18] = (T)(img)(_n1##x,_p1##y,z,c), I[19] = (T)(img)(_n2##x,_p1##y,z,c), I[20] = (T)(img)(_n3##x,_p1##y,z,c), \
  I[21] = (T)(img)(_p3##x,y,z,c), I[22] = (T)(img)(_p2##x,y,z,c), I[23] = (T)(img)(_p1##x,y,z,c), \
  I[24] = (T)(img)(x,y,z,c), I[25] = (T)(img)(_n1##x,y,z,c), I[26] = (T)(img)(_n2##x,y,z,c), \
  I[27] = (T)(img)(_n3##x,y,z,c), I[28] = (T)(img)(_p3##x,_n1##y,z,c), I[29] = (T)(img)(_p2##x,_n1##y,z,c), \
  I[30] = (T)(img)(_p1##x,_n1##y,z,c), I[31] = (T)(img)(x,_n1##y,z,c), I[32] = (T)(img)(_n1##x,_n1##y,z,c), \
  I[33] = (T)(img)(_n2##x,_n1##y,z,c), I[34] = (T)(img)(_n3##x,_n1##y,z,c), I[35] = (T)(img)(_p3##x,_n2##y,z,c), \
  I[36] = (T)(img)(_p2##x,_n2##y,z,c), I[37] = (T)(img)(_p1##x,_n2##y,z,c), I[38] = (T)(img)(x,_n2##y,z,c), \
  I[39] = (T)(img)(_n1##x,_n2##y,z,c), I[40] = (T)(img)(_n2##x,_n2##y,z,c), I[41] = (T)(img)(_n3##x,_n2##y,z,c), \
  I[42] = (T)(img)(_p3##x,_n3##y,z,c), I[43] = (T)(img)(_p2##x,_n3##y,z,c), I[44] = (T)(img)(_p1##x,_n3##y,z,c), \
  I[45] = (T)(img)(x,_n3##y,z,c), I[46] = (T)(img)(_n1##x,_n3##y,z,c), I[47] = (T)(img)(_n2##x,_n3##y,z,c), \
  I[48] = (T)(img)(_n3##x,_n3##y,z,c)

#define cimg_get8x8(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(_p3##x,_p3##y,z,c), I[1] = (T)(img)(_p2##x,_p3##y,z,c), I[2] = (T)(img)(_p1##x,_p3##y,z,c), \
  I[3] = (T)(img)(x,_p3##y,z,c), I[4] = (T)(img)(_n1##x,_p3##y,z,c), I[5] = (T)(img)(_n2##x,_p3##y,z,c), \
  I[6] = (T)(img)(_n3##x,_p3##y,z,c), I[7] = (T)(img)(_n4##x,_p3##y,z,c), I[8] = (T)(img)(_p3##x,_p2##y,z,c), \
  I[9] = (T)(img)(_p2##x,_p2##y,z,c), I[10] = (T)(img)(_p1##x,_p2##y,z,c), I[11] = (T)(img)(x,_p2##y,z,c), \
  I[12] = (T)(img)(_n1##x,_p2##y,z,c), I[13] = (T)(img)(_n2##x,_p2##y,z,c), I[14] = (T)(img)(_n3##x,_p2##y,z,c), \
  I[15] = (T)(img)(_n4##x,_p2##y,z,c), I[16] = (T)(img)(_p3##x,_p1##y,z,c), I[17] = (T)(img)(_p2##x,_p1##y,z,c), \
  I[18] = (T)(img)(_p1##x,_p1##y,z,c), I[19] = (T)(img)(x,_p1##y,z,c), I[20] = (T)(img)(_n1##x,_p1##y,z,c), \
  I[21] = (T)(img)(_n2##x,_p1##y,z,c), I[22] = (T)(img)(_n3##x,_p1##y,z,c), I[23] = (T)(img)(_n4##x,_p1##y,z,c), \
  I[24] = (T)(img)(_p3##x,y,z,c), I[25] = (T)(img)(_p2##x,y,z,c), I[26] = (T)(img)(_p1##x,y,z,c), \
  I[27] = (T)(img)(x,y,z,c), I[28] = (T)(img)(_n1##x,y,z,c), I[29] = (T)(img)(_n2##x,y,z,c), \
  I[30] = (T)(img)(_n3##x,y,z,c), I[31] = (T)(img)(_n4##x,y,z,c), I[32] = (T)(img)(_p3##x,_n1##y,z,c), \
  I[33] = (T)(img)(_p2##x,_n1##y,z,c), I[34] = (T)(img)(_p1##x,_n1##y,z,c), I[35] = (T)(img)(x,_n1##y,z,c), \
  I[36] = (T)(img)(_n1##x,_n1##y,z,c), I[37] = (T)(img)(_n2##x,_n1##y,z,c), I[38] = (T)(img)(_n3##x,_n1##y,z,c), \
  I[39] = (T)(img)(_n4##x,_n1##y,z,c), I[40] = (T)(img)(_p3##x,_n2##y,z,c), I[41] = (T)(img)(_p2##x,_n2##y,z,c), \
  I[42] = (T)(img)(_p1##x,_n2##y,z,c), I[43] = (T)(img)(x,_n2##y,z,c), I[44] = (T)(img)(_n1##x,_n2##y,z,c), \
  I[45] = (T)(img)(_n2##x,_n2##y,z,c), I[46] = (T)(img)(_n3##x,_n2##y,z,c), I[47] = (T)(img)(_n4##x,_n2##y,z,c), \
  I[48] = (T)(img)(_p3##x,_n3##y,z,c), I[49] = (T)(img)(_p2##x,_n3##y,z,c), I[50] = (T)(img)(_p1##x,_n3##y,z,c), \
  I[51] = (T)(img)(x,_n3##y,z,c), I[52] = (T)(img)(_n1##x,_n3##y,z,c), I[53] = (T)(img)(_n2##x,_n3##y,z,c), \
  I[54] = (T)(img)(_n3##x,_n3##y,z,c), I[55] = (T)(img)(_n4##x,_n3##y,z,c), I[56] = (T)(img)(_p3##x,_n4##y,z,c), \
  I[57] = (T)(img)(_p2##x,_n4##y,z,c), I[58] = (T)(img)(_p1##x,_n4##y,z,c), I[59] = (T)(img)(x,_n4##y,z,c), \
  I[60] = (T)(img)(_n1##x,_n4##y,z,c), I[61] = (T)(img)(_n2##x,_n4##y,z,c), I[62] = (T)(img)(_n3##x,_n4##y,z,c), \
  I[63] = (T)(img)(_n4##x,_n4##y,z,c);

#define cimg_get9x9(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(_p4##x,_p4##y,z,c), I[1] = (T)(img)(_p3##x,_p4##y,z,c), I[2] = (T)(img)(_p2##x,_p4##y,z,c), \
  I[3] = (T)(img)(_p1##x,_p4##y,z,c), I[4] = (T)(img)(x,_p4##y,z,c), I[5] = (T)(img)(_n1##x,_p4##y,z,c), \
  I[6] = (T)(img)(_n2##x,_p4##y,z,c), I[7] = (T)(img)(_n3##x,_p4##y,z,c), I[8] = (T)(img)(_n4##x,_p4##y,z,c), \
  I[9] = (T)(img)(_p4##x,_p3##y,z,c), I[10] = (T)(img)(_p3##x,_p3##y,z,c), I[11] = (T)(img)(_p2##x,_p3##y,z,c), \
  I[12] = (T)(img)(_p1##x,_p3##y,z,c), I[13] = (T)(img)(x,_p3##y,z,c), I[14] = (T)(img)(_n1##x,_p3##y,z,c), \
  I[15] = (T)(img)(_n2##x,_p3##y,z,c), I[16] = (T)(img)(_n3##x,_p3##y,z,c), I[17] = (T)(img)(_n4##x,_p3##y,z,c), \
  I[18] = (T)(img)(_p4##x,_p2##y,z,c), I[19] = (T)(img)(_p3##x,_p2##y,z,c), I[20] = (T)(img)(_p2##x,_p2##y,z,c), \
  I[21] = (T)(img)(_p1##x,_p2##y,z,c), I[22] = (T)(img)(x,_p2##y,z,c), I[23] = (T)(img)(_n1##x,_p2##y,z,c), \
  I[24] = (T)(img)(_n2##x,_p2##y,z,c), I[25] = (T)(img)(_n3##x,_p2##y,z,c), I[26] = (T)(img)(_n4##x,_p2##y,z,c), \
  I[27] = (T)(img)(_p4##x,_p1##y,z,c), I[28] = (T)(img)(_p3##x,_p1##y,z,c), I[29] = (T)(img)(_p2##x,_p1##y,z,c), \
  I[30] = (T)(img)(_p1##x,_p1##y,z,c), I[31] = (T)(img)(x,_p1##y,z,c), I[32] = (T)(img)(_n1##x,_p1##y,z,c), \
  I[33] = (T)(img)(_n2##x,_p1##y,z,c), I[34] = (T)(img)(_n3##x,_p1##y,z,c), I[35] = (T)(img)(_n4##x,_p1##y,z,c), \
  I[36] = (T)(img)(_p4##x,y,z,c), I[37] = (T)(img)(_p3##x,y,z,c), I[38] = (T)(img)(_p2##x,y,z,c), \
  I[39] = (T)(img)(_p1##x,y,z,c), I[40] = (T)(img)(x,y,z,c), I[41] = (T)(img)(_n1##x,y,z,c), \
  I[42] = (T)(img)(_n2##x,y,z,c), I[43] = (T)(img)(_n3##x,y,z,c), I[44] = (T)(img)(_n4##x,y,z,c), \
  I[45] = (T)(img)(_p4##x,_n1##y,z,c), I[46] = (T)(img)(_p3##x,_n1##y,z,c), I[47] = (T)(img)(_p2##x,_n1##y,z,c), \
  I[48] = (T)(img)(_p1##x,_n1##y,z,c), I[49] = (T)(img)(x,_n1##y,z,c), I[50] = (T)(img)(_n1##x,_n1##y,z,c), \
  I[51] = (T)(img)(_n2##x,_n1##y,z,c), I[52] = (T)(img)(_n3##x,_n1##y,z,c), I[53] = (T)(img)(_n4##x,_n1##y,z,c), \
  I[54] = (T)(img)(_p4##x,_n2##y,z,c), I[55] = (T)(img)(_p3##x,_n2##y,z,c), I[56] = (T)(img)(_p2##x,_n2##y,z,c), \
  I[57] = (T)(img)(_p1##x,_n2##y,z,c), I[58] = (T)(img)(x,_n2##y,z,c), I[59] = (T)(img)(_n1##x,_n2##y,z,c), \
  I[60] = (T)(img)(_n2##x,_n2##y,z,c), I[61] = (T)(img)(_n3##x,_n2##y,z,c), I[62] = (T)(img)(_n4##x,_n2##y,z,c), \
  I[63] = (T)(img)(_p4##x,_n3##y,z,c), I[64] = (T)(img)(_p3##x,_n3##y,z,c), I[65] = (T)(img)(_p2##x,_n3##y,z,c), \
  I[66] = (T)(img)(_p1##x,_n3##y,z,c), I[67] = (T)(img)(x,_n3##y,z,c), I[68] = (T)(img)(_n1##x,_n3##y,z,c), \
  I[69] = (T)(img)(_n2##x,_n3##y,z,c), I[70] = (T)(img)(_n3##x,_n3##y,z,c), I[71] = (T)(img)(_n4##x,_n3##y,z,c), \
  I[72] = (T)(img)(_p4##x,_n4##y,z,c), I[73] = (T)(img)(_p3##x,_n4##y,z,c), I[74] = (T)(img)(_p2##x,_n4##y,z,c), \
  I[75] = (T)(img)(_p1##x,_n4##y,z,c), I[76] = (T)(img)(x,_n4##y,z,c), I[77] = (T)(img)(_n1##x,_n4##y,z,c), \
  I[78] = (T)(img)(_n2##x,_n4##y,z,c), I[79] = (T)(img)(_n3##x,_n4##y,z,c), I[80] = (T)(img)(_n4##x,_n4##y,z,c)

#define cimg_get2x2x2(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(x,y,z,c), I[1] = (T)(img)(_n1##x,y,z,c), I[2] = (T)(img)(x,_n1##y,z,c), \
  I[3] = (T)(img)(_n1##x,_n1##y,z,c), I[4] = (T)(img)(x,y,_n1##z,c), I[5] = (T)(img)(_n1##x,y,_n1##z,c), \
  I[6] = (T)(img)(x,_n1##y,_n1##z,c), I[7] = (T)(img)(_n1##x,_n1##y,_n1##z,c)

#define cimg_get3x3x3(img,x,y,z,c,I,T) \
  I[0] = (T)(img)(_p1##x,_p1##y,_p1##z,c), I[1] = (T)(img)(x,_p1##y,_p1##z,c), \
  I[2] = (T)(img)(_n1##x,_p1##y,_p1##z,c), I[3] = (T)(img)(_p1##x,y,_p1##z,c), I[4] = (T)(img)(x,y,_p1##z,c), \
  I[5] = (T)(img)(_n1##x,y,_p1##z,c), I[6] = (T)(img)(_p1##x,_n1##y,_p1##z,c), I[7] = (T)(img)(x,_n1##y,_p1##z,c), \
  I[8] = (T)(img)(_n1##x,_n1##y,_p1##z,c), I[9] = (T)(img)(_p1##x,_p1##y,z,c), I[10] = (T)(img)(x,_p1##y,z,c), \
  I[11] = (T)(img)(_n1##x,_p1##y,z,c), I[12] = (T)(img)(_p1##x,y,z,c), I[13] = (T)(img)(x,y,z,c), \
  I[14] = (T)(img)(_n1##x,y,z,c), I[15] = (T)(img)(_p1##x,_n1##y,z,c), I[16] = (T)(img)(x,_n1##y,z,c), \
  I[17] = (T)(img)(_n1##x,_n1##y,z,c), I[18] = (T)(img)(_p1##x,_p1##y,_n1##z,c), I[19] = (T)(img)(x,_p1##y,_n1##z,c), \
  I[20] = (T)(img)(_n1##x,_p1##y,_n1##z,c), I[21] = (T)(img)(_p1##x,y,_n1##z,c), I[22] = (T)(img)(x,y,_n1##z,c), \
  I[23] = (T)(img)(_n1##x,y,_n1##z,c), I[24] = (T)(img)(_p1##x,_n1##y,_n1##z,c), I[25] = (T)(img)(x,_n1##y,_n1##z,c), \
  I[26] = (T)(img)(_n1##x,_n1##y,_n1##z,c)

// Macros to perform various image loops.
//
// These macros are simpler to use than loops with C++ iterators.
#define cimg_for(img,ptrs,T_ptrs) \
  for (T_ptrs *ptrs = (img)._data, *_max##ptrs = (img)._data + (img).size(); ptrs<_max##ptrs; ++ptrs)
#define cimg_rof(img,ptrs,T_ptrs) for (T_ptrs *ptrs = (img)._data + (img).size() - 1; ptrs>=(img)._data; --ptrs)
#define cimg_foroff(img,off) for (cimg_ulong off = 0, _max##off = (img).size(); off<_max##off; ++off)

#define cimg_for1(bound,i) for (int i = 0; i<(int)(bound); ++i)
#define cimg_forX(img,x) cimg_for1((img)._width,x)
#define cimg_forY(img,y) cimg_for1((img)._height,y)
#define cimg_forZ(img,z) cimg_for1((img)._depth,z)
#define cimg_forC(img,c) cimg_for1((img)._spectrum,c)
#define cimg_forXY(img,x,y) cimg_forY(img,y) cimg_forX(img,x)
#define cimg_forXZ(img,x,z) cimg_forZ(img,z) cimg_forX(img,x)
#define cimg_forYZ(img,y,z) cimg_forZ(img,z) cimg_forY(img,y)
#define cimg_forXC(img,x,c) cimg_forC(img,c) cimg_forX(img,x)
#define cimg_forYC(img,y,c) cimg_forC(img,c) cimg_forY(img,y)
#define cimg_forZC(img,z,c) cimg_forC(img,c) cimg_forZ(img,z)
#define cimg_forXYZ(img,x,y,z) cimg_forZ(img,z) cimg_forXY(img,x,y)
#define cimg_forXYC(img,x,y,c) cimg_forC(img,c) cimg_forXY(img,x,y)
#define cimg_forXZC(img,x,z,c) cimg_forC(img,c) cimg_forXZ(img,x,z)
#define cimg_forYZC(img,y,z,c) cimg_forC(img,c) cimg_forYZ(img,y,z)
#define cimg_forXYZC(img,x,y,z,c) cimg_forC(img,c) cimg_forXYZ(img,x,y,z)

#define cimg_rof1(bound,i) for (int i = (int)(bound) - 1; i>=0; --i)
#define cimg_rofX(img,x) cimg_rof1((img)._width,x)
#define cimg_rofY(img,y) cimg_rof1((img)._height,y)
#define cimg_rofZ(img,z) cimg_rof1((img)._depth,z)
#define cimg_rofC(img,c) cimg_rof1((img)._spectrum,c)
#define cimg_rofXY(img,x,y) cimg_rofY(img,y) cimg_rofX(img,x)
#define cimg_rofXZ(img,x,z) cimg_rofZ(img,z) cimg_rofX(img,x)
#define cimg_rofYZ(img,y,z) cimg_rofZ(img,z) cimg_rofY(img,y)
#define cimg_rofXC(img,x,c) cimg_rofC(img,c) cimg_rofX(img,x)
#define cimg_rofYC(img,y,c) cimg_rofC(img,c) cimg_rofY(img,y)
#define cimg_rofZC(img,z,c) cimg_rofC(img,c) cimg_rofZ(img,z)
#define cimg_rofXYZ(img,x,y,z) cimg_rofZ(img,z) cimg_rofXY(img,x,y)
#define cimg_rofXYC(img,x,y,c) cimg_rofC(img,c) cimg_rofXY(img,x,y)
#define cimg_rofXZC(img,x,z,c) cimg_rofC(img,c) cimg_rofXZ(img,x,z)
#define cimg_rofYZC(img,y,z,c) cimg_rofC(img,c) cimg_rofYZ(img,y,z)
#define cimg_rofXYZC(img,x,y,z,c) cimg_rofC(img,c) cimg_rofXYZ(img,x,y,z)

#define cimg_for_in1(bound,i0,i1,i) \
 for (int i = (int)(i0)<0?0:(int)(i0), _max##i = (int)(i1)<(int)(bound)?(int)(i1):(int)(bound) - 1; i<=_max##i; ++i)
#define cimg_for_inX(img,x0,x1,x) cimg_for_in1((img)._width,x0,x1,x)
#define cimg_for_inY(img,y0,y1,y) cimg_for_in1((img)._height,y0,y1,y)
#define cimg_for_inZ(img,z0,z1,z) cimg_for_in1((img)._depth,z0,z1,z)
#define cimg_for_inC(img,c0,c1,c) cimg_for_in1((img)._spectrum,c0,c1,c)
#define cimg_for_inXY(img,x0,y0,x1,y1,x,y) cimg_for_inY(img,y0,y1,y) cimg_for_inX(img,x0,x1,x)
#define cimg_for_inXZ(img,x0,z0,x1,z1,x,z) cimg_for_inZ(img,z0,z1,z) cimg_for_inX(img,x0,x1,x)
#define cimg_for_inXC(img,x0,c0,x1,c1,x,c) cimg_for_inC(img,c0,c1,c) cimg_for_inX(img,x0,x1,x)
#define cimg_for_inYZ(img,y0,z0,y1,z1,y,z) cimg_for_inZ(img,x0,z1,z) cimg_for_inY(img,y0,y1,y)
#define cimg_for_inYC(img,y0,c0,y1,c1,y,c) cimg_for_inC(img,c0,c1,c) cimg_for_inY(img,y0,y1,y)
#define cimg_for_inZC(img,z0,c0,z1,c1,z,c) cimg_for_inC(img,c0,c1,c) cimg_for_inZ(img,z0,z1,z)
#define cimg_for_inXYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_inZ(img,z0,z1,z) cimg_for_inXY(img,x0,y0,x1,y1,x,y)
#define cimg_for_inXYC(img,x0,y0,c0,x1,y1,c1,x,y,c) cimg_for_inC(img,c0,c1,c) cimg_for_inXY(img,x0,y0,x1,y1,x,y)
#define cimg_for_inXZC(img,x0,z0,c0,x1,z1,c1,x,z,c) cimg_for_inC(img,c0,c1,c) cimg_for_inXZ(img,x0,z0,x1,z1,x,z)
#define cimg_for_inYZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_inC(img,c0,c1,c) cimg_for_inYZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_inXYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_inC(img,c0,c1,c) cimg_for_inXYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)
#define cimg_for_insideX(img,x,n) cimg_for_inX(img,n,(img)._width - 1 - (n),x)
#define cimg_for_insideY(img,y,n) cimg_for_inY(img,n,(img)._height - 1 - (n),y)
#define cimg_for_insideZ(img,z,n) cimg_for_inZ(img,n,(img)._depth  - 1 - (n),z)
#define cimg_for_insideC(img,c,n) cimg_for_inC(img,n,(img)._spectrum - 1 - (n),c)
#define cimg_for_insideXY(img,x,y,n) cimg_for_inXY(img,n,n,(img)._width - 1 - (n),(img)._height - 1 - (n),x,y)
#define cimg_for_insideXYZ(img,x,y,z,n) \
  cimg_for_inXYZ(img,n,n,n,(img)._width - 1 - (n),(img)._height - 1 - (n),(img)._depth - 1 - (n),x,y,z)
#define cimg_for_insideXYZC(img,x,y,z,c,n) \
  cimg_for_inXYZ(img,n,n,n,(img)._width - 1 - (n),(img)._height - 1 - (n),(img)._depth - 1 - (n),x,y,z)

#define cimg_for_out1(boundi,i0,i1,i) \
 for (int i = (int)(i0)>0?0:(int)(i1) + 1; i<(int)(boundi); ++i, i = i==(int)(i0)?(int)(i1) + 1:i)
#define cimg_for_out2(boundi,boundj,i0,j0,i1,j1,i,j) \
 for (int j = 0; j<(int)(boundj); ++j) \
 for (int _n1j = (int)(j<(int)(j0) || j>(int)(j1)), i = _n1j?0:(int)(i0)>0?0:(int)(i1) + 1; i<(int)(boundi); \
  ++i, i = _n1j?i:(i==(int)(i0)?(int)(i1) + 1:i))
#define cimg_for_out3(boundi,boundj,boundk,i0,j0,k0,i1,j1,k1,i,j,k) \
 for (int k = 0; k<(int)(boundk); ++k) \
 for (int _n1k = (int)(k<(int)(k0) || k>(int)(k1)), j = 0; j<(int)(boundj); ++j) \
 for (int _n1j = (int)(j<(int)(j0) || j>(int)(j1)), i = _n1j || _n1k?0:(int)(i0)>0?0:(int)(i1) + 1; i<(int)(boundi); \
  ++i, i = _n1j || _n1k?i:(i==(int)(i0)?(int)(i1) + 1:i))
#define cimg_for_out4(boundi,boundj,boundk,boundl,i0,j0,k0,l0,i1,j1,k1,l1,i,j,k,l) \
 for (int l = 0; l<(int)(boundl); ++l) \
 for (int _n1l = (int)(l<(int)(l0) || l>(int)(l1)), k = 0; k<(int)(boundk); ++k) \
 for (int _n1k = (int)(k<(int)(k0) || k>(int)(k1)), j = 0; j<(int)(boundj); ++j) \
 for (int _n1j = (int)(j<(int)(j0) || j>(int)(j1)), i = _n1j || _n1k || _n1l?0:(int)(i0)>0?0:(int)(i1) + 1; \
  i<(int)(boundi); ++i, i = _n1j || _n1k || _n1l?i:(i==(int)(i0)?(int)(i1) + 1:i))
#define cimg_for_outX(img,x0,x1,x) cimg_for_out1((img)._width,x0,x1,x)
#define cimg_for_outY(img,y0,y1,y) cimg_for_out1((img)._height,y0,y1,y)
#define cimg_for_outZ(img,z0,z1,z) cimg_for_out1((img)._depth,z0,z1,z)
#define cimg_for_outC(img,c0,c1,c) cimg_for_out1((img)._spectrum,c0,c1,c)
#define cimg_for_outXY(img,x0,y0,x1,y1,x,y) cimg_for_out2((img)._width,(img)._height,x0,y0,x1,y1,x,y)
#define cimg_for_outXZ(img,x0,z0,x1,z1,x,z) cimg_for_out2((img)._width,(img)._depth,x0,z0,x1,z1,x,z)
#define cimg_for_outXC(img,x0,c0,x1,c1,x,c) cimg_for_out2((img)._width,(img)._spectrum,x0,c0,x1,c1,x,c)
#define cimg_for_outYZ(img,y0,z0,y1,z1,y,z) cimg_for_out2((img)._height,(img)._depth,y0,z0,y1,z1,y,z)
#define cimg_for_outYC(img,y0,c0,y1,c1,y,c) cimg_for_out2((img)._height,(img)._spectrum,y0,c0,y1,c1,y,c)
#define cimg_for_outZC(img,z0,c0,z1,c1,z,c) cimg_for_out2((img)._depth,(img)._spectrum,z0,c0,z1,c1,z,c)
#define cimg_for_outXYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) \
  cimg_for_out3((img)._width,(img)._height,(img)._depth,x0,y0,z0,x1,y1,z1,x,y,z)
#define cimg_for_outXYC(img,x0,y0,c0,x1,y1,c1,x,y,c) \
  cimg_for_out3((img)._width,(img)._height,(img)._spectrum,x0,y0,c0,x1,y1,c1,x,y,c)
#define cimg_for_outXZC(img,x0,z0,c0,x1,z1,c1,x,z,c) \
  cimg_for_out3((img)._width,(img)._depth,(img)._spectrum,x0,z0,c0,x1,z1,c1,x,z,c)
#define cimg_for_outYZC(img,y0,z0,c0,y1,z1,c1,y,z,c) \
  cimg_for_out3((img)._height,(img)._depth,(img)._spectrum,y0,z0,c0,y1,z1,c1,y,z,c)
#define cimg_for_outXYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
 cimg_for_out4((img)._width,(img)._height,(img)._depth,(img)._spectrum,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c)
#define cimg_for_borderX(img,x,n) cimg_for_outX(img,n,(img)._width - 1 - (n),x)
#define cimg_for_borderY(img,y,n) cimg_for_outY(img,n,(img)._height - 1 - (n),y)
#define cimg_for_borderZ(img,z,n) cimg_for_outZ(img,n,(img)._depth - 1 - (n),z)
#define cimg_for_borderC(img,c,n) cimg_for_outC(img,n,(img)._spectrum - 1 - (n),c)
#define cimg_for_borderXY(img,x,y,n) cimg_for_outXY(img,n,n,(img)._width - 1 - (n),(img)._height - 1 - (n),x,y)
#define cimg_for_borderXYZ(img,x,y,z,n) \
  cimg_for_outXYZ(img,n,n,n,(img)._width - 1 - (n),(img)._height - 1 - (n),(img)._depth - 1 - (n),x,y,z)
#define cimg_for_borderXYZC(img,x,y,z,c,n) \
 cimg_for_outXYZC(img,n,n,n,n,(img)._width - 1 - (n),(img)._height - 1 - (n), \
                  (img)._depth - 1 - (n),(img)._spectrum - 1 - (n),x,y,z,c)

#define cimg_for_spiralXY(img,x,y) \
 for (int x = 0, y = 0, _n1##x = 1, _n1##y = (img).width()*(img).height(); _n1##y; \
      --_n1##y, _n1##x+=(_n1##x>>2) - ((!(_n1##x&3)?--y:((_n1##x&3)==1?(img)._width - 1 - ++x:\
      ((_n1##x&3)==2?(img)._height - 1 - ++y:--x))))?0:1)

#define cimg_for_lineXY(x,y,x0,y0,x1,y1) \
 for (int x = (int)(x0), y = (int)(y0), _sx = 1, _sy = 1, _steep = 0, \
      _dx=(x1)>(x0)?(int)(x1) - (int)(x0):(_sx=-1,(int)(x0) - (int)(x1)), \
      _dy=(y1)>(y0)?(int)(y1) - (int)(y0):(_sy=-1,(int)(y0) - (int)(y1)), \
      _counter = _dx, \
      _err = _dx>_dy?(_dy>>1):((_steep=1),(_counter=_dy),(_dx>>1)); \
      _counter>=0; \
      --_counter, x+=_steep? \
      (y+=_sy,(_err-=_dx)<0?_err+=_dy,_sx:0): \
      (y+=(_err-=_dy)<0?_err+=_dx,_sy:0,_sx))

#define cimg_for2(bound,i) \
 for (int i = 0, _n1##i = 1>=(bound)?(int)(bound) - 1:1; \
      _n1##i<(int)(bound) || i==--_n1##i; \
      ++i, ++_n1##i)
#define cimg_for2X(img,x) cimg_for2((img)._width,x)
#define cimg_for2Y(img,y) cimg_for2((img)._height,y)
#define cimg_for2Z(img,z) cimg_for2((img)._depth,z)
#define cimg_for2C(img,c) cimg_for2((img)._spectrum,c)
#define cimg_for2XY(img,x,y) cimg_for2Y(img,y) cimg_for2X(img,x)
#define cimg_for2XZ(img,x,z) cimg_for2Z(img,z) cimg_for2X(img,x)
#define cimg_for2XC(img,x,c) cimg_for2C(img,c) cimg_for2X(img,x)
#define cimg_for2YZ(img,y,z) cimg_for2Z(img,z) cimg_for2Y(img,y)
#define cimg_for2YC(img,y,c) cimg_for2C(img,c) cimg_for2Y(img,y)
#define cimg_for2ZC(img,z,c) cimg_for2C(img,c) cimg_for2Z(img,z)
#define cimg_for2XYZ(img,x,y,z) cimg_for2Z(img,z) cimg_for2XY(img,x,y)
#define cimg_for2XZC(img,x,z,c) cimg_for2C(img,c) cimg_for2XZ(img,x,z)
#define cimg_for2YZC(img,y,z,c) cimg_for2C(img,c) cimg_for2YZ(img,y,z)
#define cimg_for2XYZC(img,x,y,z,c) cimg_for2C(img,c) cimg_for2XYZ(img,x,y,z)

#define cimg_for_in2(bound,i0,i1,i) \
 for (int i = (int)(i0)<0?0:(int)(i0), \
      _n1##i = i + 1>=(int)(bound)?(int)(bound) - 1:i + 1; \
      i<=(int)(i1) && (_n1##i<(int)(bound) || i==--_n1##i); \
      ++i, ++_n1##i)
#define cimg_for_in2X(img,x0,x1,x) cimg_for_in2((img)._width,x0,x1,x)
#define cimg_for_in2Y(img,y0,y1,y) cimg_for_in2((img)._height,y0,y1,y)
#define cimg_for_in2Z(img,z0,z1,z) cimg_for_in2((img)._depth,z0,z1,z)
#define cimg_for_in2C(img,c0,c1,c) cimg_for_in2((img)._spectrum,c0,c1,c)
#define cimg_for_in2XY(img,x0,y0,x1,y1,x,y) cimg_for_in2Y(img,y0,y1,y) cimg_for_in2X(img,x0,x1,x)
#define cimg_for_in2XZ(img,x0,z0,x1,z1,x,z) cimg_for_in2Z(img,z0,z1,z) cimg_for_in2X(img,x0,x1,x)
#define cimg_for_in2XC(img,x0,c0,x1,c1,x,c) cimg_for_in2C(img,c0,c1,c) cimg_for_in2X(img,x0,x1,x)
#define cimg_for_in2YZ(img,y0,z0,y1,z1,y,z) cimg_for_in2Z(img,z0,z1,z) cimg_for_in2Y(img,y0,y1,y)
#define cimg_for_in2YC(img,y0,c0,y1,c1,y,c) cimg_for_in2C(img,c0,c1,c) cimg_for_in2Y(img,y0,y1,y)
#define cimg_for_in2ZC(img,z0,c0,z1,c1,z,c) cimg_for_in2C(img,c0,c1,c) cimg_for_in2Z(img,z0,z1,z)
#define cimg_for_in2XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_in2Z(img,z0,z1,z) cimg_for_in2XY(img,x0,y0,x1,y1,x,y)
#define cimg_for_in2XZC(img,x0,z0,c0,x1,y1,c1,x,z,c) cimg_for_in2C(img,c0,c1,c) cimg_for_in2XZ(img,x0,y0,x1,y1,x,z)
#define cimg_for_in2YZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_in2C(img,c0,c1,c) cimg_for_in2YZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_in2XYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_in2C(img,c0,c1,c) cimg_for_in2XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)

#define cimg_for3(bound,i) \
 for (int i = 0, _p1##i = 0, \
      _n1##i = 1>=(bound)?(int)(bound) - 1:1; \
      _n1##i<(int)(bound) || i==--_n1##i; \
      _p1##i = i++, ++_n1##i)
#define cimg_for3X(img,x) cimg_for3((img)._width,x)
#define cimg_for3Y(img,y) cimg_for3((img)._height,y)
#define cimg_for3Z(img,z) cimg_for3((img)._depth,z)
#define cimg_for3C(img,c) cimg_for3((img)._spectrum,c)
#define cimg_for3XY(img,x,y) cimg_for3Y(img,y) cimg_for3X(img,x)
#define cimg_for3XZ(img,x,z) cimg_for3Z(img,z) cimg_for3X(img,x)
#define cimg_for3XC(img,x,c) cimg_for3C(img,c) cimg_for3X(img,x)
#define cimg_for3YZ(img,y,z) cimg_for3Z(img,z) cimg_for3Y(img,y)
#define cimg_for3YC(img,y,c) cimg_for3C(img,c) cimg_for3Y(img,y)
#define cimg_for3ZC(img,z,c) cimg_for3C(img,c) cimg_for3Z(img,z)
#define cimg_for3XYZ(img,x,y,z) cimg_for3Z(img,z) cimg_for3XY(img,x,y)
#define cimg_for3XZC(img,x,z,c) cimg_for3C(img,c) cimg_for3XZ(img,x,z)
#define cimg_for3YZC(img,y,z,c) cimg_for3C(img,c) cimg_for3YZ(img,y,z)
#define cimg_for3XYZC(img,x,y,z,c) cimg_for3C(img,c) cimg_for3XYZ(img,x,y,z)

#define cimg_for_in3(bound,i0,i1,i) \
 for (int i = (int)(i0)<0?0:(int)(i0), \
      _p1##i = i - 1<0?0:i - 1, \
      _n1##i = i + 1>=(int)(bound)?(int)(bound) - 1:i + 1; \
      i<=(int)(i1) && (_n1##i<(int)(bound) || i==--_n1##i); \
      _p1##i = i++, ++_n1##i)
#define cimg_for_in3X(img,x0,x1,x) cimg_for_in3((img)._width,x0,x1,x)
#define cimg_for_in3Y(img,y0,y1,y) cimg_for_in3((img)._height,y0,y1,y)
#define cimg_for_in3Z(img,z0,z1,z) cimg_for_in3((img)._depth,z0,z1,z)
#define cimg_for_in3C(img,c0,c1,c) cimg_for_in3((img)._spectrum,c0,c1,c)
#define cimg_for_in3XY(img,x0,y0,x1,y1,x,y) cimg_for_in3Y(img,y0,y1,y) cimg_for_in3X(img,x0,x1,x)
#define cimg_for_in3XZ(img,x0,z0,x1,z1,x,z) cimg_for_in3Z(img,z0,z1,z) cimg_for_in3X(img,x0,x1,x)
#define cimg_for_in3XC(img,x0,c0,x1,c1,x,c) cimg_for_in3C(img,c0,c1,c) cimg_for_in3X(img,x0,x1,x)
#define cimg_for_in3YZ(img,y0,z0,y1,z1,y,z) cimg_for_in3Z(img,z0,z1,z) cimg_for_in3Y(img,y0,y1,y)
#define cimg_for_in3YC(img,y0,c0,y1,c1,y,c) cimg_for_in3C(img,c0,c1,c) cimg_for_in3Y(img,y0,y1,y)
#define cimg_for_in3ZC(img,z0,c0,z1,c1,z,c) cimg_for_in3C(img,c0,c1,c) cimg_for_in3Z(img,z0,z1,z)
#define cimg_for_in3XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_in3Z(img,z0,z1,z) cimg_for_in3XY(img,x0,y0,x1,y1,x,y)
#define cimg_for_in3XZC(img,x0,z0,c0,x1,y1,c1,x,z,c) cimg_for_in3C(img,c0,c1,c) cimg_for_in3XZ(img,x0,y0,x1,y1,x,z)
#define cimg_for_in3YZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_in3C(img,c0,c1,c) cimg_for_in3YZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_in3XYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_in3C(img,c0,c1,c) cimg_for_in3XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)

#define cimg_for4(bound,i) \
 for (int i = 0, _p1##i = 0, _n1##i = 1>=(bound)?(int)(bound) - 1:1, \
      _n2##i = 2>=(bound)?(int)(bound) - 1:2; \
      _n2##i<(int)(bound) || _n1##i==--_n2##i || i==(_n2##i = --_n1##i); \
      _p1##i = i++, ++_n1##i, ++_n2##i)
#define cimg_for4X(img,x) cimg_for4((img)._width,x)
#define cimg_for4Y(img,y) cimg_for4((img)._height,y)
#define cimg_for4Z(img,z) cimg_for4((img)._depth,z)
#define cimg_for4C(img,c) cimg_for4((img)._spectrum,c)
#define cimg_for4XY(img,x,y) cimg_for4Y(img,y) cimg_for4X(img,x)
#define cimg_for4XZ(img,x,z) cimg_for4Z(img,z) cimg_for4X(img,x)
#define cimg_for4XC(img,x,c) cimg_for4C(img,c) cimg_for4X(img,x)
#define cimg_for4YZ(img,y,z) cimg_for4Z(img,z) cimg_for4Y(img,y)
#define cimg_for4YC(img,y,c) cimg_for4C(img,c) cimg_for4Y(img,y)
#define cimg_for4ZC(img,z,c) cimg_for4C(img,c) cimg_for4Z(img,z)
#define cimg_for4XYZ(img,x,y,z) cimg_for4Z(img,z) cimg_for4XY(img,x,y)
#define cimg_for4XZC(img,x,z,c) cimg_for4C(img,c) cimg_for4XZ(img,x,z)
#define cimg_for4YZC(img,y,z,c) cimg_for4C(img,c) cimg_for4YZ(img,y,z)
#define cimg_for4XYZC(img,x,y,z,c) cimg_for4C(img,c) cimg_for4XYZ(img,x,y,z)

#define cimg_for_in4(bound,i0,i1,i) \
 for (int i = (int)(i0)<0?0:(int)(i0), \
      _p1##i = i - 1<0?0:i - 1, \
      _n1##i = i + 1>=(int)(bound)?(int)(bound) - 1:i + 1, \
      _n2##i = i + 2>=(int)(bound)?(int)(bound) - 1:i + 2; \
      i<=(int)(i1) && (_n2##i<(int)(bound) || _n1##i==--_n2##i || i==(_n2##i = --_n1##i)); \
      _p1##i = i++, ++_n1##i, ++_n2##i)
#define cimg_for_in4X(img,x0,x1,x) cimg_for_in4((img)._width,x0,x1,x)
#define cimg_for_in4Y(img,y0,y1,y) cimg_for_in4((img)._height,y0,y1,y)
#define cimg_for_in4Z(img,z0,z1,z) cimg_for_in4((img)._depth,z0,z1,z)
#define cimg_for_in4C(img,c0,c1,c) cimg_for_in4((img)._spectrum,c0,c1,c)
#define cimg_for_in4XY(img,x0,y0,x1,y1,x,y) cimg_for_in4Y(img,y0,y1,y) cimg_for_in4X(img,x0,x1,x)
#define cimg_for_in4XZ(img,x0,z0,x1,z1,x,z) cimg_for_in4Z(img,z0,z1,z) cimg_for_in4X(img,x0,x1,x)
#define cimg_for_in4XC(img,x0,c0,x1,c1,x,c) cimg_for_in4C(img,c0,c1,c) cimg_for_in4X(img,x0,x1,x)
#define cimg_for_in4YZ(img,y0,z0,y1,z1,y,z) cimg_for_in4Z(img,z0,z1,z) cimg_for_in4Y(img,y0,y1,y)
#define cimg_for_in4YC(img,y0,c0,y1,c1,y,c) cimg_for_in4C(img,c0,c1,c) cimg_for_in4Y(img,y0,y1,y)
#define cimg_for_in4ZC(img,z0,c0,z1,c1,z,c) cimg_for_in4C(img,c0,c1,c) cimg_for_in4Z(img,z0,z1,z)
#define cimg_for_in4XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_in4Z(img,z0,z1,z) cimg_for_in4XY(img,x0,y0,x1,y1,x,y)
#define cimg_for_in4XZC(img,x0,z0,c0,x1,y1,c1,x,z,c) cimg_for_in4C(img,c0,c1,c) cimg_for_in4XZ(img,x0,y0,x1,y1,x,z)
#define cimg_for_in4YZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_in4C(img,c0,c1,c) cimg_for_in4YZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_in4XYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_in4C(img,c0,c1,c) cimg_for_in4XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)

#define cimg_for5(bound,i) \
 for (int i = 0, _p2##i = 0, _p1##i = 0, \
      _n1##i = 1>=(bound)?(int)(bound) - 1:1, \
      _n2##i = 2>=(bound)?(int)(bound) - 1:2; \
      _n2##i<(int)(bound) || _n1##i==--_n2##i || i==(_n2##i = --_n1##i); \
      _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i)
#define cimg_for5X(img,x) cimg_for5((img)._width,x)
#define cimg_for5Y(img,y) cimg_for5((img)._height,y)
#define cimg_for5Z(img,z) cimg_for5((img)._depth,z)
#define cimg_for5C(img,c) cimg_for5((img)._spectrum,c)
#define cimg_for5XY(img,x,y) cimg_for5Y(img,y) cimg_for5X(img,x)
#define cimg_for5XZ(img,x,z) cimg_for5Z(img,z) cimg_for5X(img,x)
#define cimg_for5XC(img,x,c) cimg_for5C(img,c) cimg_for5X(img,x)
#define cimg_for5YZ(img,y,z) cimg_for5Z(img,z) cimg_for5Y(img,y)
#define cimg_for5YC(img,y,c) cimg_for5C(img,c) cimg_for5Y(img,y)
#define cimg_for5ZC(img,z,c) cimg_for5C(img,c) cimg_for5Z(img,z)
#define cimg_for5XYZ(img,x,y,z) cimg_for5Z(img,z) cimg_for5XY(img,x,y)
#define cimg_for5XZC(img,x,z,c) cimg_for5C(img,c) cimg_for5XZ(img,x,z)
#define cimg_for5YZC(img,y,z,c) cimg_for5C(img,c) cimg_for5YZ(img,y,z)
#define cimg_for5XYZC(img,x,y,z,c) cimg_for5C(img,c) cimg_for5XYZ(img,x,y,z)

#define cimg_for_in5(bound,i0,i1,i) \
 for (int i = (int)(i0)<0?0:(int)(i0), \
      _p2##i = i - 2<0?0:i - 2, \
      _p1##i = i - 1<0?0:i - 1, \
      _n1##i = i + 1>=(int)(bound)?(int)(bound) - 1:i + 1, \
      _n2##i = i + 2>=(int)(bound)?(int)(bound) - 1:i + 2; \
      i<=(int)(i1) && (_n2##i<(int)(bound) || _n1##i==--_n2##i || i==(_n2##i = --_n1##i)); \
      _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i)
#define cimg_for_in5X(img,x0,x1,x) cimg_for_in5((img)._width,x0,x1,x)
#define cimg_for_in5Y(img,y0,y1,y) cimg_for_in5((img)._height,y0,y1,y)
#define cimg_for_in5Z(img,z0,z1,z) cimg_for_in5((img)._depth,z0,z1,z)
#define cimg_for_in5C(img,c0,c1,c) cimg_for_in5((img)._spectrum,c0,c1,c)
#define cimg_for_in5XY(img,x0,y0,x1,y1,x,y) cimg_for_in5Y(img,y0,y1,y) cimg_for_in5X(img,x0,x1,x)
#define cimg_for_in5XZ(img,x0,z0,x1,z1,x,z) cimg_for_in5Z(img,z0,z1,z) cimg_for_in5X(img,x0,x1,x)
#define cimg_for_in5XC(img,x0,c0,x1,c1,x,c) cimg_for_in5C(img,c0,c1,c) cimg_for_in5X(img,x0,x1,x)
#define cimg_for_in5YZ(img,y0,z0,y1,z1,y,z) cimg_for_in5Z(img,z0,z1,z) cimg_for_in5Y(img,y0,y1,y)
#define cimg_for_in5YC(img,y0,c0,y1,c1,y,c) cimg_for_in5C(img,c0,c1,c) cimg_for_in5Y(img,y0,y1,y)
#define cimg_for_in5ZC(img,z0,c0,z1,c1,z,c) cimg_for_in5C(img,c0,c1,c) cimg_for_in5Z(img,z0,z1,z)
#define cimg_for_in5XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_in5Z(img,z0,z1,z) cimg_for_in5XY(img,x0,y0,x1,y1,x,y)
#define cimg_for_in5XZC(img,x0,z0,c0,x1,y1,c1,x,z,c) cimg_for_in5C(img,c0,c1,c) cimg_for_in5XZ(img,x0,y0,x1,y1,x,z)
#define cimg_for_in5YZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_in5C(img,c0,c1,c) cimg_for_in5YZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_in5XYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_in5C(img,c0,c1,c) cimg_for_in5XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)

#define cimg_for6(bound,i) \
 for (int i = 0, _p2##i = 0, _p1##i = 0, \
      _n1##i = 1>=(bound)?(int)(bound) - 1:1, \
      _n2##i = 2>=(bound)?(int)(bound) - 1:2, \
      _n3##i = 3>=(bound)?(int)(bound) - 1:3; \
      _n3##i<(int)(bound) || _n2##i==--_n3##i || _n1##i==--_n2##i || i==(_n3##i = _n2##i = --_n1##i); \
      _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i, ++_n3##i)
#define cimg_for6X(img,x) cimg_for6((img)._width,x)
#define cimg_for6Y(img,y) cimg_for6((img)._height,y)
#define cimg_for6Z(img,z) cimg_for6((img)._depth,z)
#define cimg_for6C(img,c) cimg_for6((img)._spectrum,c)
#define cimg_for6XY(img,x,y) cimg_for6Y(img,y) cimg_for6X(img,x)
#define cimg_for6XZ(img,x,z) cimg_for6Z(img,z) cimg_for6X(img,x)
#define cimg_for6XC(img,x,c) cimg_for6C(img,c) cimg_for6X(img,x)
#define cimg_for6YZ(img,y,z) cimg_for6Z(img,z) cimg_for6Y(img,y)
#define cimg_for6YC(img,y,c) cimg_for6C(img,c) cimg_for6Y(img,y)
#define cimg_for6ZC(img,z,c) cimg_for6C(img,c) cimg_for6Z(img,z)
#define cimg_for6XYZ(img,x,y,z) cimg_for6Z(img,z) cimg_for6XY(img,x,y)
#define cimg_for6XZC(img,x,z,c) cimg_for6C(img,c) cimg_for6XZ(img,x,z)
#define cimg_for6YZC(img,y,z,c) cimg_for6C(img,c) cimg_for6YZ(img,y,z)
#define cimg_for6XYZC(img,x,y,z,c) cimg_for6C(img,c) cimg_for6XYZ(img,x,y,z)

#define cimg_for_in6(bound,i0,i1,i) \
 for (int i = (int)(i0)<0?0:(int)(i0), \
      _p2##i = i - 2<0?0:i - 2, \
      _p1##i = i - 1<0?0:i - 1, \
      _n1##i = i + 1>=(int)(bound)?(int)(bound) - 1:i + 1, \
      _n2##i = i + 2>=(int)(bound)?(int)(bound) - 1:i + 2, \
      _n3##i = i + 3>=(int)(bound)?(int)(bound) - 1:i + 3; \
      i<=(int)(i1) && \
      (_n3##i<(int)(bound) || _n2##i==--_n3##i || _n1##i==--_n2##i || i==(_n3##i = _n2##i = --_n1##i)); \
      _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i, ++_n3##i)
#define cimg_for_in6X(img,x0,x1,x) cimg_for_in6((img)._width,x0,x1,x)
#define cimg_for_in6Y(img,y0,y1,y) cimg_for_in6((img)._height,y0,y1,y)
#define cimg_for_in6Z(img,z0,z1,z) cimg_for_in6((img)._depth,z0,z1,z)
#define cimg_for_in6C(img,c0,c1,c) cimg_for_in6((img)._spectrum,c0,c1,c)
#define cimg_for_in6XY(img,x0,y0,x1,y1,x,y) cimg_for_in6Y(img,y0,y1,y) cimg_for_in6X(img,x0,x1,x)
#define cimg_for_in6XZ(img,x0,z0,x1,z1,x,z) cimg_for_in6Z(img,z0,z1,z) cimg_for_in6X(img,x0,x1,x)
#define cimg_for_in6XC(img,x0,c0,x1,c1,x,c) cimg_for_in6C(img,c0,c1,c) cimg_for_in6X(img,x0,x1,x)
#define cimg_for_in6YZ(img,y0,z0,y1,z1,y,z) cimg_for_in6Z(img,z0,z1,z) cimg_for_in6Y(img,y0,y1,y)
#define cimg_for_in6YC(img,y0,c0,y1,c1,y,c) cimg_for_in6C(img,c0,c1,c) cimg_for_in6Y(img,y0,y1,y)
#define cimg_for_in6ZC(img,z0,c0,z1,c1,z,c) cimg_for_in6C(img,c0,c1,c) cimg_for_in6Z(img,z0,z1,z)
#define cimg_for_in6XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_in6Z(img,z0,z1,z) cimg_for_in6XY(img,x0,y0,x1,y1,x,y)
#define cimg_for_in6XZC(img,x0,z0,c0,x1,y1,c1,x,z,c) cimg_for_in6C(img,c0,c1,c) cimg_for_in6XZ(img,x0,y0,x1,y1,x,z)
#define cimg_for_in6YZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_in6C(img,c0,c1,c) cimg_for_in6YZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_in6XYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_in6C(img,c0,c1,c) cimg_for_in6XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)

#define cimg_for7(bound,i) \
 for (int i = 0, _p3##i = 0, _p2##i = 0, _p1##i = 0, \
      _n1##i = 1>=(bound)?(int)(bound) - 1:1, \
      _n2##i = 2>=(bound)?(int)(bound) - 1:2, \
      _n3##i = 3>=(bound)?(int)(bound) - 1:3; \
      _n3##i<(int)(bound) || _n2##i==--_n3##i || _n1##i==--_n2##i || i==(_n3##i = _n2##i = --_n1##i); \
      _p3##i = _p2##i, _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i, ++_n3##i)
#define cimg_for7X(img,x) cimg_for7((img)._width,x)
#define cimg_for7Y(img,y) cimg_for7((img)._height,y)
#define cimg_for7Z(img,z) cimg_for7((img)._depth,z)
#define cimg_for7C(img,c) cimg_for7((img)._spectrum,c)
#define cimg_for7XY(img,x,y) cimg_for7Y(img,y) cimg_for7X(img,x)
#define cimg_for7XZ(img,x,z) cimg_for7Z(img,z) cimg_for7X(img,x)
#define cimg_for7XC(img,x,c) cimg_for7C(img,c) cimg_for7X(img,x)
#define cimg_for7YZ(img,y,z) cimg_for7Z(img,z) cimg_for7Y(img,y)
#define cimg_for7YC(img,y,c) cimg_for7C(img,c) cimg_for7Y(img,y)
#define cimg_for7ZC(img,z,c) cimg_for7C(img,c) cimg_for7Z(img,z)
#define cimg_for7XYZ(img,x,y,z) cimg_for7Z(img,z) cimg_for7XY(img,x,y)
#define cimg_for7XZC(img,x,z,c) cimg_for7C(img,c) cimg_for7XZ(img,x,z)
#define cimg_for7YZC(img,y,z,c) cimg_for7C(img,c) cimg_for7YZ(img,y,z)
#define cimg_for7XYZC(img,x,y,z,c) cimg_for7C(img,c) cimg_for7XYZ(img,x,y,z)

#define cimg_for_in7(bound,i0,i1,i) \
 for (int i = (int)(i0)<0?0:(int)(i0), \
      _p3##i = i - 3<0?0:i - 3, \
      _p2##i = i - 2<0?0:i - 2, \
      _p1##i = i - 1<0?0:i - 1, \
      _n1##i = i + 1>=(int)(bound)?(int)(bound) - 1:i + 1, \
      _n2##i = i + 2>=(int)(bound)?(int)(bound) - 1:i + 2, \
      _n3##i = i + 3>=(int)(bound)?(int)(bound) - 1:i + 3; \
      i<=(int)(i1) && \
      (_n3##i<(int)(bound) || _n2##i==--_n3##i || _n1##i==--_n2##i || i==(_n3##i = _n2##i = --_n1##i)); \
      _p3##i = _p2##i, _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i, ++_n3##i)
#define cimg_for_in7X(img,x0,x1,x) cimg_for_in7((img)._width,x0,x1,x)
#define cimg_for_in7Y(img,y0,y1,y) cimg_for_in7((img)._height,y0,y1,y)
#define cimg_for_in7Z(img,z0,z1,z) cimg_for_in7((img)._depth,z0,z1,z)
#define cimg_for_in7C(img,c0,c1,c) cimg_for_in7((img)._spectrum,c0,c1,c)
#define cimg_for_in7XY(img,x0,y0,x1,y1,x,y) cimg_for_in7Y(img,y0,y1,y) cimg_for_in7X(img,x0,x1,x)
#define cimg_for_in7XZ(img,x0,z0,x1,z1,x,z) cimg_for_in7Z(img,z0,z1,z) cimg_for_in7X(img,x0,x1,x)
#define cimg_for_in7XC(img,x0,c0,x1,c1,x,c) cimg_for_in7C(img,c0,c1,c) cimg_for_in7X(img,x0,x1,x)
#define cimg_for_in7YZ(img,y0,z0,y1,z1,y,z) cimg_for_in7Z(img,z0,z1,z) cimg_for_in7Y(img,y0,y1,y)
#define cimg_for_in7YC(img,y0,c0,y1,c1,y,c) cimg_for_in7C(img,c0,c1,c) cimg_for_in7Y(img,y0,y1,y)
#define cimg_for_in7ZC(img,z0,c0,z1,c1,z,c) cimg_for_in7C(img,c0,c1,c) cimg_for_in7Z(img,z0,z1,z)
#define cimg_for_in7XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_in7Z(img,z0,z1,z) cimg_for_in7XY(img,x0,y0,x1,y1,x,y)
#define cimg_for_in7XZC(img,x0,z0,c0,x1,y1,c1,x,z,c) cimg_for_in7C(img,c0,c1,c) cimg_for_in7XZ(img,x0,y0,x1,y1,x,z)
#define cimg_for_in7YZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_in7C(img,c0,c1,c) cimg_for_in7YZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_in7XYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_in7C(img,c0,c1,c) cimg_for_in7XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)

#define cimg_for8(bound,i) \
 for (int i = 0, _p3##i = 0, _p2##i = 0, _p1##i = 0, \
      _n1##i = 1>=(bound)?(int)(bound) - 1:1, \
      _n2##i = 2>=(bound)?(int)(bound) - 1:2, \
      _n3##i = 3>=(bound)?(int)(bound) - 1:3, \
      _n4##i = 4>=(bound)?(int)(bound) - 1:4; \
      _n4##i<(int)(bound) || _n3##i==--_n4##i || _n2##i==--_n3##i || _n1##i==--_n2##i || \
      i==(_n4##i = _n3##i = _n2##i = --_n1##i); \
      _p3##i = _p2##i, _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i, ++_n3##i, ++_n4##i)
#define cimg_for8X(img,x) cimg_for8((img)._width,x)
#define cimg_for8Y(img,y) cimg_for8((img)._height,y)
#define cimg_for8Z(img,z) cimg_for8((img)._depth,z)
#define cimg_for8C(img,c) cimg_for8((img)._spectrum,c)
#define cimg_for8XY(img,x,y) cimg_for8Y(img,y) cimg_for8X(img,x)
#define cimg_for8XZ(img,x,z) cimg_for8Z(img,z) cimg_for8X(img,x)
#define cimg_for8XC(img,x,c) cimg_for8C(img,c) cimg_for8X(img,x)
#define cimg_for8YZ(img,y,z) cimg_for8Z(img,z) cimg_for8Y(img,y)
#define cimg_for8YC(img,y,c) cimg_for8C(img,c) cimg_for8Y(img,y)
#define cimg_for8ZC(img,z,c) cimg_for8C(img,c) cimg_for8Z(img,z)
#define cimg_for8XYZ(img,x,y,z) cimg_for8Z(img,z) cimg_for8XY(img,x,y)
#define cimg_for8XZC(img,x,z,c) cimg_for8C(img,c) cimg_for8XZ(img,x,z)
#define cimg_for8YZC(img,y,z,c) cimg_for8C(img,c) cimg_for8YZ(img,y,z)
#define cimg_for8XYZC(img,x,y,z,c) cimg_for8C(img,c) cimg_for8XYZ(img,x,y,z)

#define cimg_for_in8(bound,i0,i1,i) \
 for (int i = (int)(i0)<0?0:(int)(i0), \
      _p3##i = i - 3<0?0:i - 3, \
      _p2##i = i - 2<0?0:i - 2, \
      _p1##i = i - 1<0?0:i - 1, \
      _n1##i = i + 1>=(int)(bound)?(int)(bound) - 1:i + 1, \
      _n2##i = i + 2>=(int)(bound)?(int)(bound) - 1:i + 2, \
      _n3##i = i + 3>=(int)(bound)?(int)(bound) - 1:i + 3, \
      _n4##i = i + 4>=(int)(bound)?(int)(bound) - 1:i + 4; \
      i<=(int)(i1) && (_n4##i<(int)(bound) || _n3##i==--_n4##i || _n2##i==--_n3##i || _n1##i==--_n2##i || \
      i==(_n4##i = _n3##i = _n2##i = --_n1##i)); \
      _p3##i = _p2##i, _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i, ++_n3##i, ++_n4##i)
#define cimg_for_in8X(img,x0,x1,x) cimg_for_in8((img)._width,x0,x1,x)
#define cimg_for_in8Y(img,y0,y1,y) cimg_for_in8((img)._height,y0,y1,y)
#define cimg_for_in8Z(img,z0,z1,z) cimg_for_in8((img)._depth,z0,z1,z)
#define cimg_for_in8C(img,c0,c1,c) cimg_for_in8((img)._spectrum,c0,c1,c)
#define cimg_for_in8XY(img,x0,y0,x1,y1,x,y) cimg_for_in8Y(img,y0,y1,y) cimg_for_in8X(img,x0,x1,x)
#define cimg_for_in8XZ(img,x0,z0,x1,z1,x,z) cimg_for_in8Z(img,z0,z1,z) cimg_for_in8X(img,x0,x1,x)
#define cimg_for_in8XC(img,x0,c0,x1,c1,x,c) cimg_for_in8C(img,c0,c1,c) cimg_for_in8X(img,x0,x1,x)
#define cimg_for_in8YZ(img,y0,z0,y1,z1,y,z) cimg_for_in8Z(img,z0,z1,z) cimg_for_in8Y(img,y0,y1,y)
#define cimg_for_in8YC(img,y0,c0,y1,c1,y,c) cimg_for_in8C(img,c0,c1,c) cimg_for_in8Y(img,y0,y1,y)
#define cimg_for_in8ZC(img,z0,c0,z1,c1,z,c) cimg_for_in8C(img,c0,c1,c) cimg_for_in8Z(img,z0,z1,z)
#define cimg_for_in8XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_in8Z(img,z0,z1,z) cimg_for_in8XY(img,x0,y0,x1,y1,x,y)
#define cimg_for_in8XZC(img,x0,z0,c0,x1,y1,c1,x,z,c) cimg_for_in8C(img,c0,c1,c) cimg_for_in8XZ(img,x0,y0,x1,y1,x,z)
#define cimg_for_in8YZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_in8C(img,c0,c1,c) cimg_for_in8YZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_in8XYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_in8C(img,c0,c1,c) cimg_for_in8XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)

#define cimg_for9(bound,i) \
  for (int i = 0, _p4##i = 0, _p3##i = 0, _p2##i = 0, _p1##i = 0, \
       _n1##i = 1>=(int)(bound)?(int)(bound) - 1:1, \
       _n2##i = 2>=(int)(bound)?(int)(bound) - 1:2, \
       _n3##i = 3>=(int)(bound)?(int)(bound) - 1:3, \
       _n4##i = 4>=(int)(bound)?(int)(bound) - 1:4; \
       _n4##i<(int)(bound) || _n3##i==--_n4##i || _n2##i==--_n3##i || _n1##i==--_n2##i || \
       i==(_n4##i = _n3##i = _n2##i = --_n1##i); \
       _p4##i = _p3##i, _p3##i = _p2##i, _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i, ++_n3##i, ++_n4##i)
#define cimg_for9X(img,x) cimg_for9((img)._width,x)
#define cimg_for9Y(img,y) cimg_for9((img)._height,y)
#define cimg_for9Z(img,z) cimg_for9((img)._depth,z)
#define cimg_for9C(img,c) cimg_for9((img)._spectrum,c)
#define cimg_for9XY(img,x,y) cimg_for9Y(img,y) cimg_for9X(img,x)
#define cimg_for9XZ(img,x,z) cimg_for9Z(img,z) cimg_for9X(img,x)
#define cimg_for9XC(img,x,c) cimg_for9C(img,c) cimg_for9X(img,x)
#define cimg_for9YZ(img,y,z) cimg_for9Z(img,z) cimg_for9Y(img,y)
#define cimg_for9YC(img,y,c) cimg_for9C(img,c) cimg_for9Y(img,y)
#define cimg_for9ZC(img,z,c) cimg_for9C(img,c) cimg_for9Z(img,z)
#define cimg_for9XYZ(img,x,y,z) cimg_for9Z(img,z) cimg_for9XY(img,x,y)
#define cimg_for9XZC(img,x,z,c) cimg_for9C(img,c) cimg_for9XZ(img,x,z)
#define cimg_for9YZC(img,y,z,c) cimg_for9C(img,c) cimg_for9YZ(img,y,z)
#define cimg_for9XYZC(img,x,y,z,c) cimg_for9C(img,c) cimg_for9XYZ(img,x,y,z)

#define cimg_for_in9(bound,i0,i1,i) \
  for (int i = (int)(i0)<0?0:(int)(i0), \
       _p4##i = i - 4<0?0:i - 4, \
       _p3##i = i - 3<0?0:i - 3, \
       _p2##i = i - 2<0?0:i - 2, \
       _p1##i = i - 1<0?0:i - 1, \
       _n1##i = i + 1>=(int)(bound)?(int)(bound) - 1:i + 1, \
       _n2##i = i + 2>=(int)(bound)?(int)(bound) - 1:i + 2, \
       _n3##i = i + 3>=(int)(bound)?(int)(bound) - 1:i + 3, \
       _n4##i = i + 4>=(int)(bound)?(int)(bound) - 1:i + 4; \
       i<=(int)(i1) && (_n4##i<(int)(bound) || _n3##i==--_n4##i || _n2##i==--_n3##i || _n1##i==--_n2##i || \
       i==(_n4##i = _n3##i = _n2##i = --_n1##i)); \
       _p4##i = _p3##i, _p3##i = _p2##i, _p2##i = _p1##i, _p1##i = i++, ++_n1##i, ++_n2##i, ++_n3##i, ++_n4##i)
#define cimg_for_in9X(img,x0,x1,x) cimg_for_in9((img)._width,x0,x1,x)
#define cimg_for_in9Y(img,y0,y1,y) cimg_for_in9((img)._height,y0,y1,y)
#define cimg_for_in9Z(img,z0,z1,z) cimg_for_in9((img)._depth,z0,z1,z)
#define cimg_for_in9C(img,c0,c1,c) cimg_for_in9((img)._spectrum,c0,c1,c)
#define cimg_for_in9XY(img,x0,y0,x1,y1,x,y) cimg_for_in9Y(img,y0,y1,y) cimg_for_in9X(img,x0,x1,x)
#define cimg_for_in9XZ(img,x0,z0,x1,z1,x,z) cimg_for_in9Z(img,z0,z1,z) cimg_for_in9X(img,x0,x1,x)
#define cimg_for_in9XC(img,x0,c0,x1,c1,x,c) cimg_for_in9C(img,c0,c1,c) cimg_for_in9X(img,x0,x1,x)
#define cimg_for_in9YZ(img,y0,z0,y1,z1,y,z) cimg_for_in9Z(img,z0,z1,z) cimg_for_in9Y(img,y0,y1,y)
#define cimg_for_in9YC(img,y0,c0,y1,c1,y,c) cimg_for_in9C(img,c0,c1,c) cimg_for_in9Y(img,y0,y1,y)
#define cimg_for_in9ZC(img,z0,c0,z1,c1,z,c) cimg_for_in9C(img,c0,c1,c) cimg_for_in9Z(img,z0,z1,z)
#define cimg_for_in9XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z) cimg_for_in9Z(img,z0,z1,z) cimg_for_in9XY(img,x0,y0,x1,y1,x,y)
#define cimg_for_in9XZC(img,x0,z0,c0,x1,y1,c1,x,z,c) cimg_for_in9C(img,c0,c1,c) cimg_for_in9XZ(img,x0,y0,x1,y1,x,z)
#define cimg_for_in9YZC(img,y0,z0,c0,y1,z1,c1,y,z,c) cimg_for_in9C(img,c0,c1,c) cimg_for_in9YZ(img,y0,z0,y1,z1,y,z)
#define cimg_for_in9XYZC(img,x0,y0,z0,c0,x1,y1,z1,c1,x,y,z,c) \
  cimg_for_in9C(img,c0,c1,c) cimg_for_in9XYZ(img,x0,y0,z0,x1,y1,z1,x,y,z)

#define cimg_for2x2(img,x,y,z,c,I,T) \
  cimg_for2((img)._height,y) for (int x = 0, \
   _n1##x = (int)( \
   (I[0] = (T)(img)(0,y,z,c)), \
   (I[2] = (T)(img)(0,_n1##y,z,c)), \
   1>=(img)._width?(img).width() - 1:1);  \
   (_n1##x<(img).width() && ( \
   (I[1] = (T)(img)(_n1##x,y,z,c)), \
   (I[3] = (T)(img)(_n1##x,_n1##y,z,c)),1)) || \
   x==--_n1##x; \
   I[0] = I[1], \
   I[2] = I[3], \
   ++x, ++_n1##x)

#define cimg_for_in2x2(img,x0,y0,x1,y1,x,y,z,c,I,T) \
  cimg_for_in2((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _n1##x = (int)( \
   (I[0] = (T)(img)(x,y,z,c)), \
   (I[2] = (T)(img)(x,_n1##y,z,c)), \
   x + 1>=(int)(img)._width?(img).width() - 1:x + 1); \
   x<=(int)(x1) && ((_n1##x<(img).width() && (  \
   (I[1] = (T)(img)(_n1##x,y,z,c)), \
   (I[3] = (T)(img)(_n1##x,_n1##y,z,c)),1)) || \
   x==--_n1##x); \
   I[0] = I[1], \
   I[2] = I[3], \
   ++x, ++_n1##x)

#define cimg_for3x3(img,x,y,z,c,I,T) \
  cimg_for3((img)._height,y) for (int x = 0, \
   _p1##x = 0, \
   _n1##x = (int)( \
   (I[0] = I[1] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[3] = I[4] = (T)(img)(0,y,z,c)), \
   (I[6] = I[7] = (T)(img)(0,_n1##y,z,c)), \
   1>=(img)._width?(img).width() - 1:1); \
   (_n1##x<(img).width() && ( \
   (I[2] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[5] = (T)(img)(_n1##x,y,z,c)), \
   (I[8] = (T)(img)(_n1##x,_n1##y,z,c)),1)) || \
   x==--_n1##x; \
   I[0] = I[1], I[1] = I[2], \
   I[3] = I[4], I[4] = I[5], \
   I[6] = I[7], I[7] = I[8], \
   _p1##x = x++, ++_n1##x)

#define cimg_for_in3x3(img,x0,y0,x1,y1,x,y,z,c,I,T) \
  cimg_for_in3((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _p1##x = x - 1<0?0:x - 1, \
   _n1##x = (int)( \
   (I[0] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[3] = (T)(img)(_p1##x,y,z,c)), \
   (I[6] = (T)(img)(_p1##x,_n1##y,z,c)), \
   (I[1] = (T)(img)(x,_p1##y,z,c)), \
   (I[4] = (T)(img)(x,y,z,c)), \
   (I[7] = (T)(img)(x,_n1##y,z,c)), \
   x + 1>=(int)(img)._width?(img).width() - 1:x + 1); \
   x<=(int)(x1) && ((_n1##x<(img).width() && ( \
   (I[2] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[5] = (T)(img)(_n1##x,y,z,c)), \
   (I[8] = (T)(img)(_n1##x,_n1##y,z,c)),1)) || \
   x==--_n1##x);            \
   I[0] = I[1], I[1] = I[2], \
   I[3] = I[4], I[4] = I[5], \
   I[6] = I[7], I[7] = I[8], \
   _p1##x = x++, ++_n1##x)

#define cimg_for4x4(img,x,y,z,c,I,T) \
  cimg_for4((img)._height,y) for (int x = 0, \
   _p1##x = 0, \
   _n1##x = 1>=(img)._width?(img).width() - 1:1, \
   _n2##x = (int)( \
   (I[0] = I[1] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[4] = I[5] = (T)(img)(0,y,z,c)), \
   (I[8] = I[9] = (T)(img)(0,_n1##y,z,c)), \
   (I[12] = I[13] = (T)(img)(0,_n2##y,z,c)), \
   (I[2] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[6] = (T)(img)(_n1##x,y,z,c)), \
   (I[10] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[14] = (T)(img)(_n1##x,_n2##y,z,c)), \
   2>=(img)._width?(img).width() - 1:2); \
   (_n2##x<(img).width() && ( \
   (I[3] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[7] = (T)(img)(_n2##x,y,z,c)), \
   (I[11] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[15] = (T)(img)(_n2##x,_n2##y,z,c)),1)) || \
   _n1##x==--_n2##x || x==(_n2##x = --_n1##x); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], \
   I[4] = I[5], I[5] = I[6], I[6] = I[7], \
   I[8] = I[9], I[9] = I[10], I[10] = I[11], \
   I[12] = I[13], I[13] = I[14], I[14] = I[15], \
   _p1##x = x++, ++_n1##x, ++_n2##x)

#define cimg_for_in4x4(img,x0,y0,x1,y1,x,y,z,c,I,T) \
  cimg_for_in4((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _p1##x = x - 1<0?0:x - 1, \
   _n1##x = x + 1>=(int)(img)._width?(img).width() - 1:x + 1, \
   _n2##x = (int)( \
   (I[0] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[4] = (T)(img)(_p1##x,y,z,c)), \
   (I[8] = (T)(img)(_p1##x,_n1##y,z,c)), \
   (I[12] = (T)(img)(_p1##x,_n2##y,z,c)), \
   (I[1] = (T)(img)(x,_p1##y,z,c)), \
   (I[5] = (T)(img)(x,y,z,c)), \
   (I[9] = (T)(img)(x,_n1##y,z,c)), \
   (I[13] = (T)(img)(x,_n2##y,z,c)), \
   (I[2] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[6] = (T)(img)(_n1##x,y,z,c)), \
   (I[10] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[14] = (T)(img)(_n1##x,_n2##y,z,c)), \
   x + 2>=(int)(img)._width?(img).width() - 1:x + 2); \
   x<=(int)(x1) && ((_n2##x<(img).width() && ( \
   (I[3] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[7] = (T)(img)(_n2##x,y,z,c)), \
   (I[11] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[15] = (T)(img)(_n2##x,_n2##y,z,c)),1)) || \
   _n1##x==--_n2##x || x==(_n2##x = --_n1##x)); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], \
   I[4] = I[5], I[5] = I[6], I[6] = I[7], \
   I[8] = I[9], I[9] = I[10], I[10] = I[11], \
   I[12] = I[13], I[13] = I[14], I[14] = I[15], \
   _p1##x = x++, ++_n1##x, ++_n2##x)

#define cimg_for5x5(img,x,y,z,c,I,T) \
 cimg_for5((img)._height,y) for (int x = 0, \
   _p2##x = 0, _p1##x = 0, \
   _n1##x = 1>=(img)._width?(img).width() - 1:1, \
   _n2##x = (int)( \
   (I[0] = I[1] = I[2] = (T)(img)(_p2##x,_p2##y,z,c)), \
   (I[5] = I[6] = I[7] = (T)(img)(0,_p1##y,z,c)), \
   (I[10] = I[11] = I[12] = (T)(img)(0,y,z,c)), \
   (I[15] = I[16] = I[17] = (T)(img)(0,_n1##y,z,c)), \
   (I[20] = I[21] = I[22] = (T)(img)(0,_n2##y,z,c)), \
   (I[3] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[8] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[13] = (T)(img)(_n1##x,y,z,c)), \
   (I[18] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[23] = (T)(img)(_n1##x,_n2##y,z,c)),  \
   2>=(img)._width?(img).width() - 1:2); \
   (_n2##x<(img).width() && ( \
   (I[4] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[9] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[14] = (T)(img)(_n2##x,y,z,c)), \
   (I[19] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[24] = (T)(img)(_n2##x,_n2##y,z,c)),1)) || \
   _n1##x==--_n2##x || x==(_n2##x = --_n1##x); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], \
   I[5] = I[6], I[6] = I[7], I[7] = I[8], I[8] = I[9], \
   I[10] = I[11], I[11] = I[12], I[12] = I[13], I[13] = I[14], \
   I[15] = I[16], I[16] = I[17], I[17] = I[18], I[18] = I[19], \
   I[20] = I[21], I[21] = I[22], I[22] = I[23], I[23] = I[24], \
   _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x)

#define cimg_for_in5x5(img,x0,y0,x1,y1,x,y,z,c,I,T) \
 cimg_for_in5((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _p2##x = x - 2<0?0:x - 2, \
   _p1##x = x - 1<0?0:x - 1, \
   _n1##x = x + 1>=(int)(img)._width?(img).width() - 1:x + 1, \
   _n2##x = (int)( \
   (I[0] = (T)(img)(_p2##x,_p2##y,z,c)), \
   (I[5] = (T)(img)(_p2##x,_p1##y,z,c)), \
   (I[10] = (T)(img)(_p2##x,y,z,c)), \
   (I[15] = (T)(img)(_p2##x,_n1##y,z,c)), \
   (I[20] = (T)(img)(_p2##x,_n2##y,z,c)), \
   (I[1] = (T)(img)(_p1##x,_p2##y,z,c)), \
   (I[6] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[11] = (T)(img)(_p1##x,y,z,c)), \
   (I[16] = (T)(img)(_p1##x,_n1##y,z,c)), \
   (I[21] = (T)(img)(_p1##x,_n2##y,z,c)), \
   (I[2] = (T)(img)(x,_p2##y,z,c)), \
   (I[7] = (T)(img)(x,_p1##y,z,c)), \
   (I[12] = (T)(img)(x,y,z,c)), \
   (I[17] = (T)(img)(x,_n1##y,z,c)), \
   (I[22] = (T)(img)(x,_n2##y,z,c)), \
   (I[3] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[8] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[13] = (T)(img)(_n1##x,y,z,c)), \
   (I[18] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[23] = (T)(img)(_n1##x,_n2##y,z,c)), \
   x + 2>=(int)(img)._width?(img).width() - 1:x + 2); \
   x<=(int)(x1) && ((_n2##x<(img).width() && ( \
   (I[4] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[9] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[14] = (T)(img)(_n2##x,y,z,c)), \
   (I[19] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[24] = (T)(img)(_n2##x,_n2##y,z,c)),1)) || \
   _n1##x==--_n2##x || x==(_n2##x = --_n1##x)); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], \
   I[5] = I[6], I[6] = I[7], I[7] = I[8], I[8] = I[9], \
   I[10] = I[11], I[11] = I[12], I[12] = I[13], I[13] = I[14], \
   I[15] = I[16], I[16] = I[17], I[17] = I[18], I[18] = I[19], \
   I[20] = I[21], I[21] = I[22], I[22] = I[23], I[23] = I[24], \
   _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x)

#define cimg_for6x6(img,x,y,z,c,I,T) \
 cimg_for6((img)._height,y) for (int x = 0, \
   _p2##x = 0, _p1##x = 0, \
   _n1##x = 1>=(img)._width?(img).width() - 1:1, \
   _n2##x = 2>=(img)._width?(img).width() - 1:2, \
   _n3##x = (int)( \
   (I[0] = I[1] = I[2] = (T)(img)(_p2##x,_p2##y,z,c)), \
   (I[6] = I[7] = I[8] = (T)(img)(0,_p1##y,z,c)), \
   (I[12] = I[13] = I[14] = (T)(img)(0,y,z,c)), \
   (I[18] = I[19] = I[20] = (T)(img)(0,_n1##y,z,c)), \
   (I[24] = I[25] = I[26] = (T)(img)(0,_n2##y,z,c)), \
   (I[30] = I[31] = I[32] = (T)(img)(0,_n3##y,z,c)), \
   (I[3] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[9] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[15] = (T)(img)(_n1##x,y,z,c)), \
   (I[21] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[27] = (T)(img)(_n1##x,_n2##y,z,c)), \
   (I[33] = (T)(img)(_n1##x,_n3##y,z,c)), \
   (I[4] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[10] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[16] = (T)(img)(_n2##x,y,z,c)), \
   (I[22] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[28] = (T)(img)(_n2##x,_n2##y,z,c)), \
   (I[34] = (T)(img)(_n2##x,_n3##y,z,c)), \
   3>=(img)._width?(img).width() - 1:3); \
   (_n3##x<(img).width() && ( \
   (I[5] = (T)(img)(_n3##x,_p2##y,z,c)), \
   (I[11] = (T)(img)(_n3##x,_p1##y,z,c)), \
   (I[17] = (T)(img)(_n3##x,y,z,c)), \
   (I[23] = (T)(img)(_n3##x,_n1##y,z,c)), \
   (I[29] = (T)(img)(_n3##x,_n2##y,z,c)), \
   (I[35] = (T)(img)(_n3##x,_n3##y,z,c)),1)) || \
   _n2##x==--_n3##x || _n1##x==--_n2##x || x==(_n3## x = _n2##x = --_n1##x); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], I[4] = I[5], \
   I[6] = I[7], I[7] = I[8], I[8] = I[9], I[9] = I[10], I[10] = I[11], \
   I[12] = I[13], I[13] = I[14], I[14] = I[15], I[15] = I[16], I[16] = I[17], \
   I[18] = I[19], I[19] = I[20], I[20] = I[21], I[21] = I[22], I[22] = I[23], \
   I[24] = I[25], I[25] = I[26], I[26] = I[27], I[27] = I[28], I[28] = I[29], \
   I[30] = I[31], I[31] = I[32], I[32] = I[33], I[33] = I[34], I[34] = I[35], \
   _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x, ++_n3##x)

#define cimg_for_in6x6(img,x0,y0,x1,y1,x,y,z,c,I,T) \
  cimg_for_in6((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)x0, \
   _p2##x = x - 2<0?0:x - 2, \
   _p1##x = x - 1<0?0:x - 1, \
   _n1##x = x + 1>=(int)(img)._width?(img).width() - 1:x + 1, \
   _n2##x = x + 2>=(int)(img)._width?(img).width() - 1:x + 2, \
   _n3##x = (int)( \
   (I[0] = (T)(img)(_p2##x,_p2##y,z,c)), \
   (I[6] = (T)(img)(_p2##x,_p1##y,z,c)), \
   (I[12] = (T)(img)(_p2##x,y,z,c)), \
   (I[18] = (T)(img)(_p2##x,_n1##y,z,c)), \
   (I[24] = (T)(img)(_p2##x,_n2##y,z,c)), \
   (I[30] = (T)(img)(_p2##x,_n3##y,z,c)), \
   (I[1] = (T)(img)(_p1##x,_p2##y,z,c)), \
   (I[7] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[13] = (T)(img)(_p1##x,y,z,c)), \
   (I[19] = (T)(img)(_p1##x,_n1##y,z,c)), \
   (I[25] = (T)(img)(_p1##x,_n2##y,z,c)), \
   (I[31] = (T)(img)(_p1##x,_n3##y,z,c)), \
   (I[2] = (T)(img)(x,_p2##y,z,c)), \
   (I[8] = (T)(img)(x,_p1##y,z,c)), \
   (I[14] = (T)(img)(x,y,z,c)), \
   (I[20] = (T)(img)(x,_n1##y,z,c)), \
   (I[26] = (T)(img)(x,_n2##y,z,c)), \
   (I[32] = (T)(img)(x,_n3##y,z,c)), \
   (I[3] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[9] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[15] = (T)(img)(_n1##x,y,z,c)), \
   (I[21] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[27] = (T)(img)(_n1##x,_n2##y,z,c)), \
   (I[33] = (T)(img)(_n1##x,_n3##y,z,c)), \
   (I[4] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[10] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[16] = (T)(img)(_n2##x,y,z,c)), \
   (I[22] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[28] = (T)(img)(_n2##x,_n2##y,z,c)), \
   (I[34] = (T)(img)(_n2##x,_n3##y,z,c)), \
   x + 3>=(int)(img)._width?(img).width() - 1:x + 3); \
   x<=(int)(x1) && ((_n3##x<(img).width() && ( \
   (I[5] = (T)(img)(_n3##x,_p2##y,z,c)), \
   (I[11] = (T)(img)(_n3##x,_p1##y,z,c)), \
   (I[17] = (T)(img)(_n3##x,y,z,c)), \
   (I[23] = (T)(img)(_n3##x,_n1##y,z,c)), \
   (I[29] = (T)(img)(_n3##x,_n2##y,z,c)), \
   (I[35] = (T)(img)(_n3##x,_n3##y,z,c)),1)) || \
   _n2##x==--_n3##x || _n1##x==--_n2##x || x==(_n3## x = _n2##x = --_n1##x)); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], I[4] = I[5], \
   I[6] = I[7], I[7] = I[8], I[8] = I[9], I[9] = I[10], I[10] = I[11], \
   I[12] = I[13], I[13] = I[14], I[14] = I[15], I[15] = I[16], I[16] = I[17], \
   I[18] = I[19], I[19] = I[20], I[20] = I[21], I[21] = I[22], I[22] = I[23], \
   I[24] = I[25], I[25] = I[26], I[26] = I[27], I[27] = I[28], I[28] = I[29], \
   I[30] = I[31], I[31] = I[32], I[32] = I[33], I[33] = I[34], I[34] = I[35], \
   _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x, ++_n3##x)

#define cimg_for7x7(img,x,y,z,c,I,T) \
  cimg_for7((img)._height,y) for (int x = 0, \
   _p3##x = 0, _p2##x = 0, _p1##x = 0, \
   _n1##x = 1>=(img)._width?(img).width() - 1:1, \
   _n2##x = 2>=(img)._width?(img).width() - 1:2, \
   _n3##x = (int)( \
   (I[0] = I[1] = I[2] = I[3] = (T)(img)(_p3##x,_p3##y,z,c)), \
   (I[7] = I[8] = I[9] = I[10] = (T)(img)(0,_p2##y,z,c)), \
   (I[14] = I[15] = I[16] = I[17] = (T)(img)(0,_p1##y,z,c)), \
   (I[21] = I[22] = I[23] = I[24] = (T)(img)(0,y,z,c)), \
   (I[28] = I[29] = I[30] = I[31] = (T)(img)(0,_n1##y,z,c)), \
   (I[35] = I[36] = I[37] = I[38] = (T)(img)(0,_n2##y,z,c)), \
   (I[42] = I[43] = I[44] = I[45] = (T)(img)(0,_n3##y,z,c)), \
   (I[4] = (T)(img)(_n1##x,_p3##y,z,c)), \
   (I[11] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[18] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[25] = (T)(img)(_n1##x,y,z,c)), \
   (I[32] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[39] = (T)(img)(_n1##x,_n2##y,z,c)), \
   (I[46] = (T)(img)(_n1##x,_n3##y,z,c)), \
   (I[5] = (T)(img)(_n2##x,_p3##y,z,c)), \
   (I[12] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[19] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[26] = (T)(img)(_n2##x,y,z,c)), \
   (I[33] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[40] = (T)(img)(_n2##x,_n2##y,z,c)), \
   (I[47] = (T)(img)(_n2##x,_n3##y,z,c)), \
   3>=(img)._width?(img).width() - 1:3); \
   (_n3##x<(img).width() && ( \
   (I[6] = (T)(img)(_n3##x,_p3##y,z,c)), \
   (I[13] = (T)(img)(_n3##x,_p2##y,z,c)), \
   (I[20] = (T)(img)(_n3##x,_p1##y,z,c)), \
   (I[27] = (T)(img)(_n3##x,y,z,c)), \
   (I[34] = (T)(img)(_n3##x,_n1##y,z,c)), \
   (I[41] = (T)(img)(_n3##x,_n2##y,z,c)), \
   (I[48] = (T)(img)(_n3##x,_n3##y,z,c)),1)) || \
   _n2##x==--_n3##x || _n1##x==--_n2##x || x==(_n3##x = _n2##x = --_n1##x); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], I[4] = I[5], I[5] = I[6], \
   I[7] = I[8], I[8] = I[9], I[9] = I[10], I[10] = I[11], I[11] = I[12], I[12] = I[13], \
   I[14] = I[15], I[15] = I[16], I[16] = I[17], I[17] = I[18], I[18] = I[19], I[19] = I[20], \
   I[21] = I[22], I[22] = I[23], I[23] = I[24], I[24] = I[25], I[25] = I[26], I[26] = I[27], \
   I[28] = I[29], I[29] = I[30], I[30] = I[31], I[31] = I[32], I[32] = I[33], I[33] = I[34], \
   I[35] = I[36], I[36] = I[37], I[37] = I[38], I[38] = I[39], I[39] = I[40], I[40] = I[41], \
   I[42] = I[43], I[43] = I[44], I[44] = I[45], I[45] = I[46], I[46] = I[47], I[47] = I[48], \
   _p3##x = _p2##x, _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x, ++_n3##x)

#define cimg_for_in7x7(img,x0,y0,x1,y1,x,y,z,c,I,T) \
  cimg_for_in7((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _p3##x = x - 3<0?0:x - 3, \
   _p2##x = x - 2<0?0:x - 2, \
   _p1##x = x - 1<0?0:x - 1, \
   _n1##x = x + 1>=(int)(img)._width?(img).width() - 1:x + 1, \
   _n2##x = x + 2>=(int)(img)._width?(img).width() - 1:x + 2, \
   _n3##x = (int)( \
   (I[0] = (T)(img)(_p3##x,_p3##y,z,c)), \
   (I[7] = (T)(img)(_p3##x,_p2##y,z,c)), \
   (I[14] = (T)(img)(_p3##x,_p1##y,z,c)), \
   (I[21] = (T)(img)(_p3##x,y,z,c)), \
   (I[28] = (T)(img)(_p3##x,_n1##y,z,c)), \
   (I[35] = (T)(img)(_p3##x,_n2##y,z,c)), \
   (I[42] = (T)(img)(_p3##x,_n3##y,z,c)), \
   (I[1] = (T)(img)(_p2##x,_p3##y,z,c)), \
   (I[8] = (T)(img)(_p2##x,_p2##y,z,c)), \
   (I[15] = (T)(img)(_p2##x,_p1##y,z,c)), \
   (I[22] = (T)(img)(_p2##x,y,z,c)), \
   (I[29] = (T)(img)(_p2##x,_n1##y,z,c)), \
   (I[36] = (T)(img)(_p2##x,_n2##y,z,c)), \
   (I[43] = (T)(img)(_p2##x,_n3##y,z,c)), \
   (I[2] = (T)(img)(_p1##x,_p3##y,z,c)), \
   (I[9] = (T)(img)(_p1##x,_p2##y,z,c)), \
   (I[16] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[23] = (T)(img)(_p1##x,y,z,c)), \
   (I[30] = (T)(img)(_p1##x,_n1##y,z,c)), \
   (I[37] = (T)(img)(_p1##x,_n2##y,z,c)), \
   (I[44] = (T)(img)(_p1##x,_n3##y,z,c)), \
   (I[3] = (T)(img)(x,_p3##y,z,c)), \
   (I[10] = (T)(img)(x,_p2##y,z,c)), \
   (I[17] = (T)(img)(x,_p1##y,z,c)), \
   (I[24] = (T)(img)(x,y,z,c)), \
   (I[31] = (T)(img)(x,_n1##y,z,c)), \
   (I[38] = (T)(img)(x,_n2##y,z,c)), \
   (I[45] = (T)(img)(x,_n3##y,z,c)), \
   (I[4] = (T)(img)(_n1##x,_p3##y,z,c)), \
   (I[11] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[18] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[25] = (T)(img)(_n1##x,y,z,c)), \
   (I[32] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[39] = (T)(img)(_n1##x,_n2##y,z,c)), \
   (I[46] = (T)(img)(_n1##x,_n3##y,z,c)), \
   (I[5] = (T)(img)(_n2##x,_p3##y,z,c)), \
   (I[12] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[19] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[26] = (T)(img)(_n2##x,y,z,c)), \
   (I[33] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[40] = (T)(img)(_n2##x,_n2##y,z,c)), \
   (I[47] = (T)(img)(_n2##x,_n3##y,z,c)), \
   x + 3>=(int)(img)._width?(img).width() - 1:x + 3); \
   x<=(int)(x1) && ((_n3##x<(img).width() && ( \
   (I[6] = (T)(img)(_n3##x,_p3##y,z,c)), \
   (I[13] = (T)(img)(_n3##x,_p2##y,z,c)), \
   (I[20] = (T)(img)(_n3##x,_p1##y,z,c)), \
   (I[27] = (T)(img)(_n3##x,y,z,c)), \
   (I[34] = (T)(img)(_n3##x,_n1##y,z,c)), \
   (I[41] = (T)(img)(_n3##x,_n2##y,z,c)), \
   (I[48] = (T)(img)(_n3##x,_n3##y,z,c)),1)) || \
   _n2##x==--_n3##x || _n1##x==--_n2##x || x==(_n3##x = _n2##x = --_n1##x)); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], I[4] = I[5], I[5] = I[6], \
   I[7] = I[8], I[8] = I[9], I[9] = I[10], I[10] = I[11], I[11] = I[12], I[12] = I[13], \
   I[14] = I[15], I[15] = I[16], I[16] = I[17], I[17] = I[18], I[18] = I[19], I[19] = I[20], \
   I[21] = I[22], I[22] = I[23], I[23] = I[24], I[24] = I[25], I[25] = I[26], I[26] = I[27], \
   I[28] = I[29], I[29] = I[30], I[30] = I[31], I[31] = I[32], I[32] = I[33], I[33] = I[34], \
   I[35] = I[36], I[36] = I[37], I[37] = I[38], I[38] = I[39], I[39] = I[40], I[40] = I[41], \
   I[42] = I[43], I[43] = I[44], I[44] = I[45], I[45] = I[46], I[46] = I[47], I[47] = I[48], \
   _p3##x = _p2##x, _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x, ++_n3##x)

#define cimg_for8x8(img,x,y,z,c,I,T) \
  cimg_for8((img)._height,y) for (int x = 0, \
   _p3##x = 0, _p2##x = 0, _p1##x = 0, \
   _n1##x = 1>=((img)._width)?(img).width() - 1:1, \
   _n2##x = 2>=((img)._width)?(img).width() - 1:2, \
   _n3##x = 3>=((img)._width)?(img).width() - 1:3, \
   _n4##x = (int)( \
   (I[0] = I[1] = I[2] = I[3] = (T)(img)(_p3##x,_p3##y,z,c)), \
   (I[8] = I[9] = I[10] = I[11] = (T)(img)(0,_p2##y,z,c)), \
   (I[16] = I[17] = I[18] = I[19] = (T)(img)(0,_p1##y,z,c)), \
   (I[24] = I[25] = I[26] = I[27] = (T)(img)(0,y,z,c)), \
   (I[32] = I[33] = I[34] = I[35] = (T)(img)(0,_n1##y,z,c)), \
   (I[40] = I[41] = I[42] = I[43] = (T)(img)(0,_n2##y,z,c)), \
   (I[48] = I[49] = I[50] = I[51] = (T)(img)(0,_n3##y,z,c)), \
   (I[56] = I[57] = I[58] = I[59] = (T)(img)(0,_n4##y,z,c)), \
   (I[4] = (T)(img)(_n1##x,_p3##y,z,c)), \
   (I[12] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[20] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[28] = (T)(img)(_n1##x,y,z,c)), \
   (I[36] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[44] = (T)(img)(_n1##x,_n2##y,z,c)), \
   (I[52] = (T)(img)(_n1##x,_n3##y,z,c)), \
   (I[60] = (T)(img)(_n1##x,_n4##y,z,c)), \
   (I[5] = (T)(img)(_n2##x,_p3##y,z,c)), \
   (I[13] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[21] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[29] = (T)(img)(_n2##x,y,z,c)), \
   (I[37] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[45] = (T)(img)(_n2##x,_n2##y,z,c)), \
   (I[53] = (T)(img)(_n2##x,_n3##y,z,c)), \
   (I[61] = (T)(img)(_n2##x,_n4##y,z,c)), \
   (I[6] = (T)(img)(_n3##x,_p3##y,z,c)), \
   (I[14] = (T)(img)(_n3##x,_p2##y,z,c)), \
   (I[22] = (T)(img)(_n3##x,_p1##y,z,c)), \
   (I[30] = (T)(img)(_n3##x,y,z,c)), \
   (I[38] = (T)(img)(_n3##x,_n1##y,z,c)), \
   (I[46] = (T)(img)(_n3##x,_n2##y,z,c)), \
   (I[54] = (T)(img)(_n3##x,_n3##y,z,c)), \
   (I[62] = (T)(img)(_n3##x,_n4##y,z,c)), \
   4>=((img)._width)?(img).width() - 1:4); \
   (_n4##x<(img).width() && ( \
   (I[7] = (T)(img)(_n4##x,_p3##y,z,c)), \
   (I[15] = (T)(img)(_n4##x,_p2##y,z,c)), \
   (I[23] = (T)(img)(_n4##x,_p1##y,z,c)), \
   (I[31] = (T)(img)(_n4##x,y,z,c)), \
   (I[39] = (T)(img)(_n4##x,_n1##y,z,c)), \
   (I[47] = (T)(img)(_n4##x,_n2##y,z,c)), \
   (I[55] = (T)(img)(_n4##x,_n3##y,z,c)), \
   (I[63] = (T)(img)(_n4##x,_n4##y,z,c)),1)) || \
   _n3##x==--_n4##x || _n2##x==--_n3##x || _n1##x==--_n2##x || x==(_n4##x = _n3##x = _n2##x = --_n1##x); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], I[4] = I[5], I[5] = I[6], I[6] = I[7], \
   I[8] = I[9], I[9] = I[10], I[10] = I[11], I[11] = I[12], I[12] = I[13], I[13] = I[14], I[14] = I[15], \
   I[16] = I[17], I[17] = I[18], I[18] = I[19], I[19] = I[20], I[20] = I[21], I[21] = I[22], I[22] = I[23], \
   I[24] = I[25], I[25] = I[26], I[26] = I[27], I[27] = I[28], I[28] = I[29], I[29] = I[30], I[30] = I[31], \
   I[32] = I[33], I[33] = I[34], I[34] = I[35], I[35] = I[36], I[36] = I[37], I[37] = I[38], I[38] = I[39], \
   I[40] = I[41], I[41] = I[42], I[42] = I[43], I[43] = I[44], I[44] = I[45], I[45] = I[46], I[46] = I[47], \
   I[48] = I[49], I[49] = I[50], I[50] = I[51], I[51] = I[52], I[52] = I[53], I[53] = I[54], I[54] = I[55], \
   I[56] = I[57], I[57] = I[58], I[58] = I[59], I[59] = I[60], I[60] = I[61], I[61] = I[62], I[62] = I[63], \
   _p3##x = _p2##x, _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x, ++_n3##x, ++_n4##x)

#define cimg_for_in8x8(img,x0,y0,x1,y1,x,y,z,c,I,T) \
  cimg_for_in8((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _p3##x = x - 3<0?0:x - 3, \
   _p2##x = x - 2<0?0:x - 2, \
   _p1##x = x - 1<0?0:x - 1, \
   _n1##x = x + 1>=(img).width()?(img).width() - 1:x + 1, \
   _n2##x = x + 2>=(img).width()?(img).width() - 1:x + 2, \
   _n3##x = x + 3>=(img).width()?(img).width() - 1:x + 3, \
   _n4##x = (int)( \
   (I[0] = (T)(img)(_p3##x,_p3##y,z,c)), \
   (I[8] = (T)(img)(_p3##x,_p2##y,z,c)), \
   (I[16] = (T)(img)(_p3##x,_p1##y,z,c)), \
   (I[24] = (T)(img)(_p3##x,y,z,c)), \
   (I[32] = (T)(img)(_p3##x,_n1##y,z,c)), \
   (I[40] = (T)(img)(_p3##x,_n2##y,z,c)), \
   (I[48] = (T)(img)(_p3##x,_n3##y,z,c)), \
   (I[56] = (T)(img)(_p3##x,_n4##y,z,c)), \
   (I[1] = (T)(img)(_p2##x,_p3##y,z,c)), \
   (I[9] = (T)(img)(_p2##x,_p2##y,z,c)), \
   (I[17] = (T)(img)(_p2##x,_p1##y,z,c)), \
   (I[25] = (T)(img)(_p2##x,y,z,c)), \
   (I[33] = (T)(img)(_p2##x,_n1##y,z,c)), \
   (I[41] = (T)(img)(_p2##x,_n2##y,z,c)), \
   (I[49] = (T)(img)(_p2##x,_n3##y,z,c)), \
   (I[57] = (T)(img)(_p2##x,_n4##y,z,c)), \
   (I[2] = (T)(img)(_p1##x,_p3##y,z,c)), \
   (I[10] = (T)(img)(_p1##x,_p2##y,z,c)), \
   (I[18] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[26] = (T)(img)(_p1##x,y,z,c)), \
   (I[34] = (T)(img)(_p1##x,_n1##y,z,c)), \
   (I[42] = (T)(img)(_p1##x,_n2##y,z,c)), \
   (I[50] = (T)(img)(_p1##x,_n3##y,z,c)), \
   (I[58] = (T)(img)(_p1##x,_n4##y,z,c)), \
   (I[3] = (T)(img)(x,_p3##y,z,c)), \
   (I[11] = (T)(img)(x,_p2##y,z,c)), \
   (I[19] = (T)(img)(x,_p1##y,z,c)), \
   (I[27] = (T)(img)(x,y,z,c)), \
   (I[35] = (T)(img)(x,_n1##y,z,c)), \
   (I[43] = (T)(img)(x,_n2##y,z,c)), \
   (I[51] = (T)(img)(x,_n3##y,z,c)), \
   (I[59] = (T)(img)(x,_n4##y,z,c)), \
   (I[4] = (T)(img)(_n1##x,_p3##y,z,c)), \
   (I[12] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[20] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[28] = (T)(img)(_n1##x,y,z,c)), \
   (I[36] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[44] = (T)(img)(_n1##x,_n2##y,z,c)), \
   (I[52] = (T)(img)(_n1##x,_n3##y,z,c)), \
   (I[60] = (T)(img)(_n1##x,_n4##y,z,c)), \
   (I[5] = (T)(img)(_n2##x,_p3##y,z,c)), \
   (I[13] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[21] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[29] = (T)(img)(_n2##x,y,z,c)), \
   (I[37] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[45] = (T)(img)(_n2##x,_n2##y,z,c)), \
   (I[53] = (T)(img)(_n2##x,_n3##y,z,c)), \
   (I[61] = (T)(img)(_n2##x,_n4##y,z,c)), \
   (I[6] = (T)(img)(_n3##x,_p3##y,z,c)), \
   (I[14] = (T)(img)(_n3##x,_p2##y,z,c)), \
   (I[22] = (T)(img)(_n3##x,_p1##y,z,c)), \
   (I[30] = (T)(img)(_n3##x,y,z,c)), \
   (I[38] = (T)(img)(_n3##x,_n1##y,z,c)), \
   (I[46] = (T)(img)(_n3##x,_n2##y,z,c)), \
   (I[54] = (T)(img)(_n3##x,_n3##y,z,c)), \
   (I[62] = (T)(img)(_n3##x,_n4##y,z,c)), \
   x + 4>=(img).width()?(img).width() - 1:x + 4); \
   x<=(int)(x1) && ((_n4##x<(img).width() && ( \
   (I[7] = (T)(img)(_n4##x,_p3##y,z,c)), \
   (I[15] = (T)(img)(_n4##x,_p2##y,z,c)), \
   (I[23] = (T)(img)(_n4##x,_p1##y,z,c)), \
   (I[31] = (T)(img)(_n4##x,y,z,c)), \
   (I[39] = (T)(img)(_n4##x,_n1##y,z,c)), \
   (I[47] = (T)(img)(_n4##x,_n2##y,z,c)), \
   (I[55] = (T)(img)(_n4##x,_n3##y,z,c)), \
   (I[63] = (T)(img)(_n4##x,_n4##y,z,c)),1)) || \
   _n3##x==--_n4##x || _n2##x==--_n3##x || _n1##x==--_n2##x || x==(_n4##x = _n3##x = _n2##x = --_n1##x)); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], I[4] = I[5], I[5] = I[6], I[6] = I[7], \
   I[8] = I[9], I[9] = I[10], I[10] = I[11], I[11] = I[12], I[12] = I[13], I[13] = I[14], I[14] = I[15], \
   I[16] = I[17], I[17] = I[18], I[18] = I[19], I[19] = I[20], I[20] = I[21], I[21] = I[22], I[22] = I[23], \
   I[24] = I[25], I[25] = I[26], I[26] = I[27], I[27] = I[28], I[28] = I[29], I[29] = I[30], I[30] = I[31], \
   I[32] = I[33], I[33] = I[34], I[34] = I[35], I[35] = I[36], I[36] = I[37], I[37] = I[38], I[38] = I[39], \
   I[40] = I[41], I[41] = I[42], I[42] = I[43], I[43] = I[44], I[44] = I[45], I[45] = I[46], I[46] = I[47], \
   I[48] = I[49], I[49] = I[50], I[50] = I[51], I[51] = I[52], I[52] = I[53], I[53] = I[54], I[54] = I[55], \
   I[56] = I[57], I[57] = I[58], I[58] = I[59], I[59] = I[60], I[60] = I[61], I[61] = I[62], I[62] = I[63], \
   _p3##x = _p2##x, _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x, ++_n3##x, ++_n4##x)

#define cimg_for9x9(img,x,y,z,c,I,T) \
  cimg_for9((img)._height,y) for (int x = 0, \
   _p4##x = 0, _p3##x = 0, _p2##x = 0, _p1##x = 0, \
   _n1##x = 1>=((img)._width)?(img).width() - 1:1, \
   _n2##x = 2>=((img)._width)?(img).width() - 1:2, \
   _n3##x = 3>=((img)._width)?(img).width() - 1:3, \
   _n4##x = (int)( \
   (I[0] = I[1] = I[2] = I[3] = I[4] = (T)(img)(_p4##x,_p4##y,z,c)), \
   (I[9] = I[10] = I[11] = I[12] = I[13] = (T)(img)(0,_p3##y,z,c)), \
   (I[18] = I[19] = I[20] = I[21] = I[22] = (T)(img)(0,_p2##y,z,c)), \
   (I[27] = I[28] = I[29] = I[30] = I[31] = (T)(img)(0,_p1##y,z,c)), \
   (I[36] = I[37] = I[38] = I[39] = I[40] = (T)(img)(0,y,z,c)), \
   (I[45] = I[46] = I[47] = I[48] = I[49] = (T)(img)(0,_n1##y,z,c)), \
   (I[54] = I[55] = I[56] = I[57] = I[58] = (T)(img)(0,_n2##y,z,c)), \
   (I[63] = I[64] = I[65] = I[66] = I[67] = (T)(img)(0,_n3##y,z,c)), \
   (I[72] = I[73] = I[74] = I[75] = I[76] = (T)(img)(0,_n4##y,z,c)), \
   (I[5] = (T)(img)(_n1##x,_p4##y,z,c)), \
   (I[14] = (T)(img)(_n1##x,_p3##y,z,c)), \
   (I[23] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[32] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[41] = (T)(img)(_n1##x,y,z,c)), \
   (I[50] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[59] = (T)(img)(_n1##x,_n2##y,z,c)), \
   (I[68] = (T)(img)(_n1##x,_n3##y,z,c)), \
   (I[77] = (T)(img)(_n1##x,_n4##y,z,c)), \
   (I[6] = (T)(img)(_n2##x,_p4##y,z,c)), \
   (I[15] = (T)(img)(_n2##x,_p3##y,z,c)), \
   (I[24] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[33] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[42] = (T)(img)(_n2##x,y,z,c)), \
   (I[51] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[60] = (T)(img)(_n2##x,_n2##y,z,c)), \
   (I[69] = (T)(img)(_n2##x,_n3##y,z,c)), \
   (I[78] = (T)(img)(_n2##x,_n4##y,z,c)), \
   (I[7] = (T)(img)(_n3##x,_p4##y,z,c)), \
   (I[16] = (T)(img)(_n3##x,_p3##y,z,c)), \
   (I[25] = (T)(img)(_n3##x,_p2##y,z,c)), \
   (I[34] = (T)(img)(_n3##x,_p1##y,z,c)), \
   (I[43] = (T)(img)(_n3##x,y,z,c)), \
   (I[52] = (T)(img)(_n3##x,_n1##y,z,c)), \
   (I[61] = (T)(img)(_n3##x,_n2##y,z,c)), \
   (I[70] = (T)(img)(_n3##x,_n3##y,z,c)), \
   (I[79] = (T)(img)(_n3##x,_n4##y,z,c)), \
   4>=((img)._width)?(img).width() - 1:4); \
   (_n4##x<(img).width() && ( \
   (I[8] = (T)(img)(_n4##x,_p4##y,z,c)), \
   (I[17] = (T)(img)(_n4##x,_p3##y,z,c)), \
   (I[26] = (T)(img)(_n4##x,_p2##y,z,c)), \
   (I[35] = (T)(img)(_n4##x,_p1##y,z,c)), \
   (I[44] = (T)(img)(_n4##x,y,z,c)), \
   (I[53] = (T)(img)(_n4##x,_n1##y,z,c)), \
   (I[62] = (T)(img)(_n4##x,_n2##y,z,c)), \
   (I[71] = (T)(img)(_n4##x,_n3##y,z,c)), \
   (I[80] = (T)(img)(_n4##x,_n4##y,z,c)),1)) || \
   _n3##x==--_n4##x || _n2##x==--_n3##x || _n1##x==--_n2##x || x==(_n4##x = _n3##x = _n2##x = --_n1##x); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], I[4] = I[5], I[5] = I[6], I[6] = I[7], I[7] = I[8], \
   I[9] = I[10], I[10] = I[11], I[11] = I[12], I[12] = I[13], I[13] = I[14], I[14] = I[15], I[15] = I[16], \
   I[16] = I[17], I[18] = I[19], I[19] = I[20], I[20] = I[21], I[21] = I[22], I[22] = I[23], I[23] = I[24], \
   I[24] = I[25], I[25] = I[26], I[27] = I[28], I[28] = I[29], I[29] = I[30], I[30] = I[31], I[31] = I[32], \
   I[32] = I[33], I[33] = I[34], I[34] = I[35], I[36] = I[37], I[37] = I[38], I[38] = I[39], I[39] = I[40], \
   I[40] = I[41], I[41] = I[42], I[42] = I[43], I[43] = I[44], I[45] = I[46], I[46] = I[47], I[47] = I[48], \
   I[48] = I[49], I[49] = I[50], I[50] = I[51], I[51] = I[52], I[52] = I[53], I[54] = I[55], I[55] = I[56], \
   I[56] = I[57], I[57] = I[58], I[58] = I[59], I[59] = I[60], I[60] = I[61], I[61] = I[62], I[63] = I[64], \
   I[64] = I[65], I[65] = I[66], I[66] = I[67], I[67] = I[68], I[68] = I[69], I[69] = I[70], I[70] = I[71], \
   I[72] = I[73], I[73] = I[74], I[74] = I[75], I[75] = I[76], I[76] = I[77], I[77] = I[78], I[78] = I[79], \
   I[79] = I[80], \
   _p4##x = _p3##x, _p3##x = _p2##x, _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x, ++_n3##x, ++_n4##x)

#define cimg_for_in9x9(img,x0,y0,x1,y1,x,y,z,c,I,T) \
  cimg_for_in9((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _p4##x = x - 4<0?0:x - 4, \
   _p3##x = x - 3<0?0:x - 3, \
   _p2##x = x - 2<0?0:x - 2, \
   _p1##x = x - 1<0?0:x - 1, \
   _n1##x = x + 1>=(img).width()?(img).width() - 1:x + 1, \
   _n2##x = x + 2>=(img).width()?(img).width() - 1:x + 2, \
   _n3##x = x + 3>=(img).width()?(img).width() - 1:x + 3, \
   _n4##x = (int)( \
   (I[0] = (T)(img)(_p4##x,_p4##y,z,c)), \
   (I[9] = (T)(img)(_p4##x,_p3##y,z,c)), \
   (I[18] = (T)(img)(_p4##x,_p2##y,z,c)), \
   (I[27] = (T)(img)(_p4##x,_p1##y,z,c)), \
   (I[36] = (T)(img)(_p4##x,y,z,c)), \
   (I[45] = (T)(img)(_p4##x,_n1##y,z,c)), \
   (I[54] = (T)(img)(_p4##x,_n2##y,z,c)), \
   (I[63] = (T)(img)(_p4##x,_n3##y,z,c)), \
   (I[72] = (T)(img)(_p4##x,_n4##y,z,c)), \
   (I[1] = (T)(img)(_p3##x,_p4##y,z,c)), \
   (I[10] = (T)(img)(_p3##x,_p3##y,z,c)), \
   (I[19] = (T)(img)(_p3##x,_p2##y,z,c)), \
   (I[28] = (T)(img)(_p3##x,_p1##y,z,c)), \
   (I[37] = (T)(img)(_p3##x,y,z,c)), \
   (I[46] = (T)(img)(_p3##x,_n1##y,z,c)), \
   (I[55] = (T)(img)(_p3##x,_n2##y,z,c)), \
   (I[64] = (T)(img)(_p3##x,_n3##y,z,c)), \
   (I[73] = (T)(img)(_p3##x,_n4##y,z,c)), \
   (I[2] = (T)(img)(_p2##x,_p4##y,z,c)), \
   (I[11] = (T)(img)(_p2##x,_p3##y,z,c)), \
   (I[20] = (T)(img)(_p2##x,_p2##y,z,c)), \
   (I[29] = (T)(img)(_p2##x,_p1##y,z,c)), \
   (I[38] = (T)(img)(_p2##x,y,z,c)), \
   (I[47] = (T)(img)(_p2##x,_n1##y,z,c)), \
   (I[56] = (T)(img)(_p2##x,_n2##y,z,c)), \
   (I[65] = (T)(img)(_p2##x,_n3##y,z,c)), \
   (I[74] = (T)(img)(_p2##x,_n4##y,z,c)), \
   (I[3] = (T)(img)(_p1##x,_p4##y,z,c)), \
   (I[12] = (T)(img)(_p1##x,_p3##y,z,c)), \
   (I[21] = (T)(img)(_p1##x,_p2##y,z,c)), \
   (I[30] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[39] = (T)(img)(_p1##x,y,z,c)), \
   (I[48] = (T)(img)(_p1##x,_n1##y,z,c)), \
   (I[57] = (T)(img)(_p1##x,_n2##y,z,c)), \
   (I[66] = (T)(img)(_p1##x,_n3##y,z,c)), \
   (I[75] = (T)(img)(_p1##x,_n4##y,z,c)), \
   (I[4] = (T)(img)(x,_p4##y,z,c)), \
   (I[13] = (T)(img)(x,_p3##y,z,c)), \
   (I[22] = (T)(img)(x,_p2##y,z,c)), \
   (I[31] = (T)(img)(x,_p1##y,z,c)), \
   (I[40] = (T)(img)(x,y,z,c)), \
   (I[49] = (T)(img)(x,_n1##y,z,c)), \
   (I[58] = (T)(img)(x,_n2##y,z,c)), \
   (I[67] = (T)(img)(x,_n3##y,z,c)), \
   (I[76] = (T)(img)(x,_n4##y,z,c)), \
   (I[5] = (T)(img)(_n1##x,_p4##y,z,c)), \
   (I[14] = (T)(img)(_n1##x,_p3##y,z,c)), \
   (I[23] = (T)(img)(_n1##x,_p2##y,z,c)), \
   (I[32] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[41] = (T)(img)(_n1##x,y,z,c)), \
   (I[50] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[59] = (T)(img)(_n1##x,_n2##y,z,c)), \
   (I[68] = (T)(img)(_n1##x,_n3##y,z,c)), \
   (I[77] = (T)(img)(_n1##x,_n4##y,z,c)), \
   (I[6] = (T)(img)(_n2##x,_p4##y,z,c)), \
   (I[15] = (T)(img)(_n2##x,_p3##y,z,c)), \
   (I[24] = (T)(img)(_n2##x,_p2##y,z,c)), \
   (I[33] = (T)(img)(_n2##x,_p1##y,z,c)), \
   (I[42] = (T)(img)(_n2##x,y,z,c)), \
   (I[51] = (T)(img)(_n2##x,_n1##y,z,c)), \
   (I[60] = (T)(img)(_n2##x,_n2##y,z,c)), \
   (I[69] = (T)(img)(_n2##x,_n3##y,z,c)), \
   (I[78] = (T)(img)(_n2##x,_n4##y,z,c)), \
   (I[7] = (T)(img)(_n3##x,_p4##y,z,c)), \
   (I[16] = (T)(img)(_n3##x,_p3##y,z,c)), \
   (I[25] = (T)(img)(_n3##x,_p2##y,z,c)), \
   (I[34] = (T)(img)(_n3##x,_p1##y,z,c)), \
   (I[43] = (T)(img)(_n3##x,y,z,c)), \
   (I[52] = (T)(img)(_n3##x,_n1##y,z,c)), \
   (I[61] = (T)(img)(_n3##x,_n2##y,z,c)), \
   (I[70] = (T)(img)(_n3##x,_n3##y,z,c)), \
   (I[79] = (T)(img)(_n3##x,_n4##y,z,c)), \
   x + 4>=(img).width()?(img).width() - 1:x + 4); \
   x<=(int)(x1) && ((_n4##x<(img).width() && ( \
   (I[8] = (T)(img)(_n4##x,_p4##y,z,c)), \
   (I[17] = (T)(img)(_n4##x,_p3##y,z,c)), \
   (I[26] = (T)(img)(_n4##x,_p2##y,z,c)), \
   (I[35] = (T)(img)(_n4##x,_p1##y,z,c)), \
   (I[44] = (T)(img)(_n4##x,y,z,c)), \
   (I[53] = (T)(img)(_n4##x,_n1##y,z,c)), \
   (I[62] = (T)(img)(_n4##x,_n2##y,z,c)), \
   (I[71] = (T)(img)(_n4##x,_n3##y,z,c)), \
   (I[80] = (T)(img)(_n4##x,_n4##y,z,c)),1)) || \
   _n3##x==--_n4##x || _n2##x==--_n3##x || _n1##x==--_n2##x || x==(_n4##x = _n3##x = _n2##x = --_n1##x)); \
   I[0] = I[1], I[1] = I[2], I[2] = I[3], I[3] = I[4], I[4] = I[5], I[5] = I[6], I[6] = I[7], I[7] = I[8], \
   I[9] = I[10], I[10] = I[11], I[11] = I[12], I[12] = I[13], I[13] = I[14], I[14] = I[15], I[15] = I[16], \
   I[16] = I[17], I[18] = I[19], I[19] = I[20], I[20] = I[21], I[21] = I[22], I[22] = I[23], I[23] = I[24], \
   I[24] = I[25], I[25] = I[26], I[27] = I[28], I[28] = I[29], I[29] = I[30], I[30] = I[31], I[31] = I[32], \
   I[32] = I[33], I[33] = I[34], I[34] = I[35], I[36] = I[37], I[37] = I[38], I[38] = I[39], I[39] = I[40], \
   I[40] = I[41], I[41] = I[42], I[42] = I[43], I[43] = I[44], I[45] = I[46], I[46] = I[47], I[47] = I[48], \
   I[48] = I[49], I[49] = I[50], I[50] = I[51], I[51] = I[52], I[52] = I[53], I[54] = I[55], I[55] = I[56], \
   I[56] = I[57], I[57] = I[58], I[58] = I[59], I[59] = I[60], I[60] = I[61], I[61] = I[62], I[63] = I[64], \
   I[64] = I[65], I[65] = I[66], I[66] = I[67], I[67] = I[68], I[68] = I[69], I[69] = I[70], I[70] = I[71], \
   I[72] = I[73], I[73] = I[74], I[74] = I[75], I[75] = I[76], I[76] = I[77], I[77] = I[78], I[78] = I[79], \
   I[79] = I[80], \
   _p4##x = _p3##x, _p3##x = _p2##x, _p2##x = _p1##x, _p1##x = x++, ++_n1##x, ++_n2##x, ++_n3##x, ++_n4##x)

#define cimg_for2x2x2(img,x,y,z,c,I,T) \
 cimg_for2((img)._depth,z) cimg_for2((img)._height,y) for (int x = 0, \
   _n1##x = (int)( \
   (I[0] = (T)(img)(0,y,z,c)), \
   (I[2] = (T)(img)(0,_n1##y,z,c)), \
   (I[4] = (T)(img)(0,y,_n1##z,c)), \
   (I[6] = (T)(img)(0,_n1##y,_n1##z,c)), \
   1>=(img)._width?(img).width() - 1:1); \
   (_n1##x<(img).width() && ( \
   (I[1] = (T)(img)(_n1##x,y,z,c)), \
   (I[3] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[5] = (T)(img)(_n1##x,y,_n1##z,c)), \
   (I[7] = (T)(img)(_n1##x,_n1##y,_n1##z,c)),1)) || \
   x==--_n1##x; \
   I[0] = I[1], I[2] = I[3], I[4] = I[5], I[6] = I[7], \
   ++x, ++_n1##x)

#define cimg_for_in2x2x2(img,x0,y0,z0,x1,y1,z1,x,y,z,c,I,T) \
 cimg_for_in2((img)._depth,z0,z1,z) cimg_for_in2((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _n1##x = (int)( \
   (I[0] = (T)(img)(x,y,z,c)), \
   (I[2] = (T)(img)(x,_n1##y,z,c)), \
   (I[4] = (T)(img)(x,y,_n1##z,c)), \
   (I[6] = (T)(img)(x,_n1##y,_n1##z,c)), \
   x + 1>=(int)(img)._width?(img).width() - 1:x + 1); \
   x<=(int)(x1) && ((_n1##x<(img).width() && ( \
   (I[1] = (T)(img)(_n1##x,y,z,c)), \
   (I[3] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[5] = (T)(img)(_n1##x,y,_n1##z,c)), \
   (I[7] = (T)(img)(_n1##x,_n1##y,_n1##z,c)),1)) || \
   x==--_n1##x); \
   I[0] = I[1], I[2] = I[3], I[4] = I[5], I[6] = I[7], \
   ++x, ++_n1##x)

#define cimg_for3x3x3(img,x,y,z,c,I,T) \
 cimg_for3((img)._depth,z) cimg_for3((img)._height,y) for (int x = 0, \
   _p1##x = 0, \
   _n1##x = (int)( \
   (I[0] = I[1] = (T)(img)(_p1##x,_p1##y,_p1##z,c)), \
   (I[3] = I[4] = (T)(img)(0,y,_p1##z,c)),  \
   (I[6] = I[7] = (T)(img)(0,_n1##y,_p1##z,c)), \
   (I[9] = I[10] = (T)(img)(0,_p1##y,z,c)), \
   (I[12] = I[13] = (T)(img)(0,y,z,c)), \
   (I[15] = I[16] = (T)(img)(0,_n1##y,z,c)), \
   (I[18] = I[19] = (T)(img)(0,_p1##y,_n1##z,c)), \
   (I[21] = I[22] = (T)(img)(0,y,_n1##z,c)), \
   (I[24] = I[25] = (T)(img)(0,_n1##y,_n1##z,c)), \
   1>=(img)._width?(img).width() - 1:1); \
   (_n1##x<(img).width() && ( \
   (I[2] = (T)(img)(_n1##x,_p1##y,_p1##z,c)), \
   (I[5] = (T)(img)(_n1##x,y,_p1##z,c)), \
   (I[8] = (T)(img)(_n1##x,_n1##y,_p1##z,c)), \
   (I[11] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[14] = (T)(img)(_n1##x,y,z,c)), \
   (I[17] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[20] = (T)(img)(_n1##x,_p1##y,_n1##z,c)), \
   (I[23] = (T)(img)(_n1##x,y,_n1##z,c)), \
   (I[26] = (T)(img)(_n1##x,_n1##y,_n1##z,c)),1)) || \
   x==--_n1##x; \
   I[0] = I[1], I[1] = I[2], I[3] = I[4], I[4] = I[5], I[6] = I[7], I[7] = I[8], \
   I[9] = I[10], I[10] = I[11], I[12] = I[13], I[13] = I[14], I[15] = I[16], I[16] = I[17], \
   I[18] = I[19], I[19] = I[20], I[21] = I[22], I[22] = I[23], I[24] = I[25], I[25] = I[26], \
   _p1##x = x++, ++_n1##x)

#define cimg_for_in3x3x3(img,x0,y0,z0,x1,y1,z1,x,y,z,c,I,T) \
 cimg_for_in3((img)._depth,z0,z1,z) cimg_for_in3((img)._height,y0,y1,y) for (int x = (int)(x0)<0?0:(int)(x0), \
   _p1##x = x - 1<0?0:x - 1, \
   _n1##x = (int)( \
   (I[0] = (T)(img)(_p1##x,_p1##y,_p1##z,c)), \
   (I[3] = (T)(img)(_p1##x,y,_p1##z,c)),  \
   (I[6] = (T)(img)(_p1##x,_n1##y,_p1##z,c)), \
   (I[9] = (T)(img)(_p1##x,_p1##y,z,c)), \
   (I[12] = (T)(img)(_p1##x,y,z,c)), \
   (I[15] = (T)(img)(_p1##x,_n1##y,z,c)), \
   (I[18] = (T)(img)(_p1##x,_p1##y,_n1##z,c)), \
   (I[21] = (T)(img)(_p1##x,y,_n1##z,c)), \
   (I[24] = (T)(img)(_p1##x,_n1##y,_n1##z,c)), \
   (I[1] = (T)(img)(x,_p1##y,_p1##z,c)), \
   (I[4] = (T)(img)(x,y,_p1##z,c)),  \
   (I[7] = (T)(img)(x,_n1##y,_p1##z,c)), \
   (I[10] = (T)(img)(x,_p1##y,z,c)), \
   (I[13] = (T)(img)(x,y,z,c)), \
   (I[16] = (T)(img)(x,_n1##y,z,c)), \
   (I[19] = (T)(img)(x,_p1##y,_n1##z,c)), \
   (I[22] = (T)(img)(x,y,_n1##z,c)), \
   (I[25] = (T)(img)(x,_n1##y,_n1##z,c)), \
   x + 1>=(int)(img)._width?(img).width() - 1:x + 1); \
   x<=(int)(x1) && ((_n1##x<(img).width() && ( \
   (I[2] = (T)(img)(_n1##x,_p1##y,_p1##z,c)), \
   (I[5] = (T)(img)(_n1##x,y,_p1##z,c)), \
   (I[8] = (T)(img)(_n1##x,_n1##y,_p1##z,c)), \
   (I[11] = (T)(img)(_n1##x,_p1##y,z,c)), \
   (I[14] = (T)(img)(_n1##x,y,z,c)), \
   (I[17] = (T)(img)(_n1##x,_n1##y,z,c)), \
   (I[20] = (T)(img)(_n1##x,_p1##y,_n1##z,c)), \
   (I[23] = (T)(img)(_n1##x,y,_n1##z,c)), \
   (I[26] = (T)(img)(_n1##x,_n1##y,_n1##z,c)),1)) || \
   x==--_n1##x); \
   I[0] = I[1], I[1] = I[2], I[3] = I[4], I[4] = I[5], I[6] = I[7], I[7] = I[8], \
   I[9] = I[10], I[10] = I[11], I[12] = I[13], I[13] = I[14], I[15] = I[16], I[16] = I[17], \
   I[18] = I[19], I[19] = I[20], I[21] = I[22], I[22] = I[23], I[24] = I[25], I[25] = I[26], \
   _p1##x = x++, ++_n1##x)

#define cimglist_for(list,l) for (int l = 0; l<(int)(list)._width; ++l)
#define cimglist_for_in(list,l0,l1,l) \
  for (int l = (int)(l0)<0?0:(int)(l0), _max##l = (unsigned int)l1<(list)._width?(int)(l1):(int)(list)._width - 1; \
  l<=_max##l; ++l)

#define cimglist_apply(list,fn) cimglist_for(list,__##fn) (list)[__##fn].fn

// Macros used to display error messages when exceptions are thrown.
// You should not use these macros is your own code.
#define _cimgdisplay_instance "[instance(%u,%u,%u,%c%s%c)] CImgDisplay::"
#define cimgdisplay_instance _width,_height,_normalization,_title?'\"':'[',_title?_title:"untitled",_title?'\"':']'
#define _cimg_instance "[instance(%u,%u,%u,%u,%p,%sshared)] CImg<%s>::"
#define cimg_instance _width,_height,_depth,_spectrum,_data,_is_shared?"":"non-",pixel_type()
#define _cimglist_instance "[instance(%u,%u,%p)] CImgList<%s>::"
#define cimglist_instance _width,_allocated_width,_data,pixel_type()

/*------------------------------------------------
 #
 #
 #  Define cimg_library:: namespace
 #
 #
 -------------------------------------------------*/
//! Contains <i>all classes and functions</i> of the \CImg library.
/**
   This namespace is defined to avoid functions and class names collisions
   that could happen with the inclusion of other C++ header files.
   Anyway, it should not happen often and you should reasonnably start most of your
   \CImg-based programs with
   \code
   #include "CImg.h"
   using namespace cimg_library;
   \endcode
   to simplify the declaration of \CImg Library objects afterwards.
**/
namespace cimg_library_suffixed {

  // Declare the four classes of the CImg Library.
  template<typename T=float> struct CImg;
  template<typename T=float> struct CImgList;
  struct CImgDisplay;
  struct CImgException;

  // Declare cimg:: namespace.
  // This is an uncomplete namespace definition here. It only contains some
  // necessary stuff to ensure a correct declaration order of the classes and functions
  // defined afterwards.
  namespace cimg {

    // Define ascii sequences for colored terminal output.
#ifdef cimg_use_vt100
    static const char t_normal[] = { 0x1b, '[', '0', ';', '0', ';', '0', 'm', 0 };
    static const char t_black[] = { 0x1b, '[', '0', ';', '3', '0', ';', '5', '9', 'm', 0 };
    static const char t_red[] = { 0x1b, '[', '0', ';', '3', '1', ';', '5', '9', 'm', 0 };
    static const char t_green[] = { 0x1b, '[', '0', ';', '3', '2', ';', '5', '9', 'm', 0 };
    static const char t_yellow[] = { 0x1b, '[', '0', ';', '3', '3', ';', '5', '9', 'm', 0 };
    static const char t_blue[] = { 0x1b, '[', '0', ';', '3', '4', ';', '5', '9', 'm', 0 };
    static const char t_magenta[] = { 0x1b, '[', '0', ';', '3', '5', ';', '5', '9', 'm', 0 };
    static const char t_cyan[] = { 0x1b, '[', '0', ';', '3', '6', ';', '5', '9', 'm', 0 };
    static const char t_white[] = { 0x1b, '[', '0', ';', '3', '7', ';', '5', '9', 'm', 0 };
    static const char t_bold[] = { 0x1b, '[', '1', 'm', 0 };
    static const char t_underscore[] = { 0x1b, '[', '4', 'm', 0 };
#else
    static const char t_normal[] = { 0 };
    static const char *const t_black = cimg::t_normal,
      *const t_red = cimg::t_normal,
      *const t_green = cimg::t_normal,
      *const t_yellow = cimg::t_normal,
      *const t_blue = cimg::t_normal,
      *const t_magenta = cimg::t_normal,
      *const t_cyan = cimg::t_normal,
      *const t_white = cimg::t_normal,
      *const t_bold = cimg::t_normal,
      *const t_underscore = cimg::t_normal;
#endif

    inline std::FILE* output(std::FILE *file=0);
    inline void info();

    //! Avoid warning messages due to unused parameters. Do nothing actually.
    template<typename T>
    inline void unused(const T&, ...) {}

    // [internal] Lock/unlock a mutex for managing concurrent threads.
    // 'lock_mode' can be { 0=unlock | 1=lock | 2=trylock }.
    // 'n' can be in [0,31] but mutex range [0,15] is reserved by CImg.
    inline int mutex(const unsigned int n, const int lock_mode=1);

    inline unsigned int& _exception_mode(const unsigned int value, const bool is_set) {
      static unsigned int mode = cimg_verbosity;
      if (is_set) { cimg::mutex(0); mode = value<4?value:4; cimg::mutex(0,0); }
      return mode;
    }

    // Functions to return standard streams 'stdin', 'stdout' and 'stderr'.
    inline FILE* _stdin(const bool throw_exception=true);
    inline FILE* _stdout(const bool throw_exception=true);
    inline FILE* _stderr(const bool throw_exception=true);

    // Mandatory because Microsoft's _snprintf() and _vsnprintf() do not add the '\0' character
    // at the end of the string.
#if cimg_OS==2 && defined(_MSC_VER)
    inline int _snprintf(char *const s, const size_t size, const char *const format, ...) {
      va_list ap;
      va_start(ap,format);
      const int result = _vsnprintf(s,size,format,ap);
      va_end(ap);
      return result;
    }

    inline int _vsnprintf(char *const s, const size_t size, const char *const format, va_list ap) {
      int result = -1;
      cimg::mutex(6);
      if (size) result = _vsnprintf_s(s,size,_TRUNCATE,format,ap);
      if (result==-1) result = _vscprintf(format,ap);
      cimg::mutex(6,0);
      return result;
    }

    // Mutex-protected version of sscanf, sprintf and snprintf.
    // Used only MacOSX, as it seems those functions are not re-entrant on MacOSX.
#elif defined(__MACOSX__) || defined(__APPLE__)
    inline int _sscanf(const char *const s, const char *const format, ...) {
      cimg::mutex(6);
      va_list args;
      va_start(args,format);
      const int result = std::vsscanf(s,format,args);
      va_end(args);
      cimg::mutex(6,0);
      return result;
    }

    inline int _sprintf(char *const s, const char *const format, ...) {
      cimg::mutex(6);
      va_list args;
      va_start(args,format);
      const int result = std::vsprintf(s,format,args);
      va_end(args);
      cimg::mutex(6,0);
      return result;
    }

    inline int _snprintf(char *const s, const size_t n, const char *const format, ...) {
      cimg::mutex(6);
      va_list args;
      va_start(args,format);
      const int result = std::vsnprintf(s,n,format,args);
      va_end(args);
      cimg::mutex(6,0);
      return result;
    }

    inline int _vsnprintf(char *const s, const size_t size, const char* format, va_list ap) {
      cimg::mutex(6);
      const int result = std::vsnprintf(s,size,format,ap);
      cimg::mutex(6,0);
      return result;
    }
#endif

    //! Set current \CImg exception mode.
    /**
       The way error messages are handled by \CImg can be changed dynamically, using this function.
       \param mode Desired exception mode. Possible values are:
       - \c 0: Hide library messages (quiet mode).
       - \c 1: Print library messages on the console.
       - \c 2: Display library messages on a dialog window.
       - \c 3: Do as \c 1 + add extra debug warnings (slow down the code!).
       - \c 4: Do as \c 2 + add extra debug warnings (slow down the code!).
     **/
    inline unsigned int& exception_mode(const unsigned int mode) {
      return _exception_mode(mode,true);
    }

    //! Return current \CImg exception mode.
    /**
       \note By default, return the value of configuration macro \c cimg_verbosity
    **/
    inline unsigned int& exception_mode() {
      return _exception_mode(0,false);
    }

    //! Set current \CImg openmp mode.
    /**
       The way openmp-based methods are handled by \CImg can be changed dynamically, using this function.
       \param mode Desired openmp mode. Possible values are:
       - \c 0: Never parallelize.
       - \c 1: Always parallelize.
       - \c 2: Adaptive parallelization mode (default behavior).
     **/
    inline unsigned int& _openmp_mode(const unsigned int value, const bool is_set) {
      static unsigned int mode = 2;
      if (is_set)  { cimg::mutex(0); mode = value<2?value:2; cimg::mutex(0,0); }
      return mode;
    }

    inline unsigned int& openmp_mode(const unsigned int mode) {
      return _openmp_mode(mode,true);
    }

    //! Return current \CImg openmp mode.
    inline unsigned int& openmp_mode() {
      return _openmp_mode(0,false);
    }

#define cimg_openmp_if(cond) if (cimg::openmp_mode()==1 || (cimg::openmp_mode()>1 && (cond)))

    // Display a simple dialog box, and wait for the user's response.
    inline int dialog(const char *const title, const char *const msg, const char *const button1_label="OK",
                      const char *const button2_label=0, const char *const button3_label=0,
                      const char *const button4_label=0, const char *const button5_label=0,
                      const char *const button6_label=0, const bool centering=false);

    // Evaluate math expression.
    inline double eval(const char *const expression,
                       const double x=0, const double y=0, const double z=0, const double c=0);

  }

  /*---------------------------------------
    #
    # Define the CImgException structures
    #
    --------------------------------------*/
  //! Instances of \c CImgException are thrown when errors are encountered in a \CImg function call.
  /**
     \par Overview

      CImgException is the base class of all exceptions thrown by \CImg (except \b CImgAbortException).
      CImgException is never thrown itself. Derived classes that specify the type of errord are thrown instead.
      These classes can be:

      - \b CImgAbortException: Thrown when a computationally-intensive function is aborted by an external signal.
        This is the only \c non-derived exception class.

      - \b CImgArgumentException: Thrown when one argument of a called \CImg function is invalid.
      This is probably one of the most thrown exception by \CImg.
      For instance, the following example throws a \c CImgArgumentException:
      \code
      CImg<float> img(100,100,1,3); // Define a 100x100 color image with float-valued pixels.
      img.mirror('e');              // Try to mirror image along the (non-existing) 'e'-axis.
      \endcode

      - \b CImgDisplayException: Thrown when something went wrong during the display of images in CImgDisplay instances.

      - \b CImgInstanceException: Thrown when an instance associated to a called \CImg method does not fit
      the function requirements. For instance, the following example throws a \c CImgInstanceException:
      \code
      const CImg<float> img;           // Define an empty image.
      const float value = img.at(0);   // Try to read first pixel value (does not exist).
      \endcode

      - \b CImgIOException: Thrown when an error occured when trying to load or save image files.
      This happens when trying to read files that do not exist or with invalid formats.
      For instance, the following example throws a \c CImgIOException:
      \code
      const CImg<float> img("missing_file.jpg");  // Try to load a file that does not exist.
      \endcode

      - \b CImgWarningException: Thrown only if configuration macro \c cimg_strict_warnings is set, and
      when a \CImg function has to display a warning message (see cimg::warn()).

      It is not recommended to throw CImgException instances by yourself,
      since they are expected to be thrown only by \CImg.
      When an error occurs in a library function call, \CImg may display error messages on the screen or on the
      standard output, depending on the current \CImg exception mode.
      The \CImg exception mode can be get and set by functions cimg::exception_mode() and
      cimg::exception_mode(unsigned int).

      \par Exceptions handling

      In all cases, when an error occurs in \CImg, an instance of the corresponding exception class is thrown.
      This may lead the program to break (this is the default behavior), but you can bypass this behavior by
      handling the exceptions by yourself,
      using a usual <tt>try { ... } catch () { ... }</tt> bloc, as in the following example:
      \code
      #define "CImg.h"
      using namespace cimg_library;
      int main() {
        cimg::exception_mode(0);                                    // Enable quiet exception mode.
        try {
          ...                                                       // Here, do what you want to stress CImg.
        } catch (CImgException& e) {                                // You succeeded: something went wrong!
          std::fprintf(stderr,"CImg Library Error: %s",e.what());   // Display your custom error message.
          ...                                                       // Do what you want now to save the ship!
          }
        }
      \endcode
  **/
  struct CImgException : public std::exception {
#define _cimg_exception_err(etype,disp_flag) \
  std::va_list ap, ap2; \
  va_start(ap,format); va_start(ap2,format); \
  int size = cimg_vsnprintf(0,0,format,ap2); \
  if (size++>=0) { \
    delete[] _message; \
    _message = new char[size]; \
    cimg_vsnprintf(_message,size,format,ap); \
    if (cimg::exception_mode()) { \
      std::fprintf(cimg::output(),"\n%s[CImg] *** %s ***%s %s\n",cimg::t_red,etype,cimg::t_normal,_message); \
      if (cimg_display && disp_flag && !(cimg::exception_mode()%2)) try { cimg::dialog(etype,_message,"Abort"); } \
      catch (CImgException&) {} \
      if (cimg::exception_mode()>=3) cimg_library_suffixed::cimg::info(); \
    } \
  } \
  va_end(ap); va_end(ap2); \

    char *_message;
    CImgException() { _message = new char[1]; *_message = 0; }
    CImgException(const char *const format, ...):_message(0) { _cimg_exception_err("CImgException",true); }
    CImgException(const CImgException& e):std::exception(e) {
      const size_t size = std::strlen(e._message);
      _message = new char[size + 1];
      std::strncpy(_message,e._message,size);
      _message[size] = 0;
    }
    ~CImgException() throw() { delete[] _message; }
    CImgException& operator=(const CImgException& e) {
      const size_t size = std::strlen(e._message);
      _message = new char[size + 1];
      std::strncpy(_message,e._message,size);
      _message[size] = 0;
      return *this;
    }
    //! Return a C-string containing the error message associated to the thrown exception.
    const char *what() const throw() { return _message; }
  };

  // The CImgAbortException class is used to throw an exception when
  // a computationally-intensive function has been aborted by an external signal.
  struct CImgAbortException : public std::exception {
    char *_message;
    CImgAbortException() { _message = new char[1]; *_message = 0; }
    CImgAbortException(const char *const format, ...):_message(0) { _cimg_exception_err("CImgAbortException",true); }
    CImgAbortException(const CImgAbortException& e):std::exception(e) {
      const size_t size = std::strlen(e._message);
      _message = new char[size + 1];
      std::strncpy(_message,e._message,size);
      _message[size] = 0;
    }
    ~CImgAbortException() throw() { delete[] _message; }
    CImgAbortException& operator=(const CImgAbortException& e) {
      const size_t size = std::strlen(e._message);
      _message = new char[size + 1];
      std::strncpy(_message,e._message,size);
      _message[size] = 0;
      return *this;
    }
    //! Return a C-string containing the error message associated to the thrown exception.
    const char *what() const throw() { return _message; }
  };

  // The CImgArgumentException class is used to throw an exception related
  // to invalid arguments encountered in a library function call.
  struct CImgArgumentException : public CImgException {
    CImgArgumentException(const char *const format, ...) { _cimg_exception_err("CImgArgumentException",true); }
  };

  // The CImgDisplayException class is used to throw an exception related
  // to display problems encountered in a library function call.
  struct CImgDisplayException : public CImgException {
    CImgDisplayException(const char *const format, ...) { _cimg_exception_err("CImgDisplayException",false); }
  };

  // The CImgInstanceException class is used to throw an exception related
  // to an invalid instance encountered in a library function call.
  struct CImgInstanceException : public CImgException {
    CImgInstanceException(const char *const format, ...) { _cimg_exception_err("CImgInstanceException",true); }
  };

  // The CImgIOException class is used to throw an exception related
  // to input/output file problems encountered in a library function call.
  struct CImgIOException : public CImgException {
    CImgIOException(const char *const format, ...) { _cimg_exception_err("CImgIOException",true); }
  };

  // The CImgWarningException class is used to throw an exception for warnings
  // encountered in a library function call.
  struct CImgWarningException : public CImgException {
    CImgWarningException(const char *const format, ...) { _cimg_exception_err("CImgWarningException",false); }
  };

  /*-------------------------------------
    #
    # Define cimg:: namespace
    #
    -----------------------------------*/
  //! Contains \a low-level functions and variables of the \CImg Library.
  /**
     Most of the functions and variables within this namespace are used by the \CImg library for low-level operations.
     You may use them to access specific const values or environment variables internally used by \CImg.
     \warning Never write <tt>using namespace cimg_library::cimg;</tt> in your source code. Lot of functions in the
     <tt>cimg:: namespace</tt> have the same names as standard C functions that may be defined in the global
     namespace <tt>::</tt>.
  **/
  namespace cimg {

    // Define traits that will be used to determine the best data type to work in CImg functions.
    //
    template<typename T> struct type {
      static const char* string() {
        static const char* s[] = { "unknown",   "unknown8",   "unknown16",  "unknown24",
                                   "unknown32", "unknown40",  "unknown48",  "unknown56",
                                   "unknown64", "unknown72",  "unknown80",  "unknown88",
                                   "unknown96", "unknown104", "unknown112", "unknown120",
                                   "unknown128" };
        return s[(sizeof(T)<17)?sizeof(T):0];
      }
      static bool is_float() { return false; }
      static bool is_inf(const T) { return false; }
      static bool is_nan(const T) { return false; }
      static T min() { return ~max(); }
      static T max() { return (T)1<<(8*sizeof(T) - 1); }
      static T inf() { return max(); }
      static T cut(const double val) { return val<(double)min()?min():val>(double)max()?max():(T)val; }
      static const char* format() { return "%s"; }
      static const char* format_s() { return "%s"; }
      static const char* format(const T& val) { static const char *const s = "unknown"; cimg::unused(val); return s; }
    };

    template<> struct type<bool> {
      static const char* string() { static const char *const s = "bool"; return s; }
      static bool is_float() { return false; }
      static bool is_inf(const bool) { return false; }
      static bool is_nan(const bool) { return false; }
      static bool min() { return false; }
      static bool max() { return true; }
      static bool inf() { return max(); }
      static bool is_inf() { return false; }
      static bool cut(const double val) { return val<(double)min()?min():val>(double)max()?max():(bool)val; }
      static const char* format() { return "%s"; }
      static const char* format_s() { return "%s"; }
      static const char* format(const bool val) { static const char* s[] = { "false", "true" }; return s[val?1:0]; }
    };

    template<> struct type<unsigned char> {
      static const char* string() { static const char *const s = "unsigned char"; return s; }
      static bool is_float() { return false; }
      static bool is_inf(const unsigned char) { return false; }
      static bool is_nan(const unsigned char) { return false; }
      static unsigned char min() { return 0; }
      static unsigned char max() { return (unsigned char)-1; }
      static unsigned char inf() { return max(); }
      static unsigned char cut(const double val) {
        return val<(double)min()?min():val>(double)max()?max():(unsigned char)val; }
      static const char* format() { return "%u"; }
      static const char* format_s() { return "%u"; }
      static unsigned int format(const unsigned char val) { return (unsigned int)val; }
    };

#if defined(CHAR_MAX) && CHAR_MAX==255
    template<> struct type<char> {
      static const char* string() { static const char *const s = "char"; return s; }
      static bool is_float() { return false; }
      static bool is_inf(const char) { return false; }
      static bool is_nan(const char) { return false; }
      static char min() { return 0; }
      static char max() { return (char)-1; }
      static char inf() { return max(); }
      static char cut(const double val) {
        return val<(double)min()?min():val>(double)max()?max():(unsigned char)val; }
      static const char* format() { return "%u"; }
      static const char* format_s() { return "%u"; }
      static unsigned int format(const char val) { return (unsigned int)val; }
    };
#else
    template<> struct type<char> {
      static const char* string() { static const char *const s = "char"; return s; }
      static bool is_float() { return false; }
      static bool is_inf(const char) { return false; }
      static bool is_nan(const char) { return false; }
      static char min() { return ~max(); }
      static char max() { return (char)((unsigned char)-1>>1); }
      static char inf() { return max(); }
      static char cut(const double val) { return val<(double)min()?min():val>(double)max()?max():(char)val; }
      static const char* format() { return "%d"; }
      static const char* format_s() { return "%d"; }
      static int format(const char val) { return (int)val; }
    };
#endif

    template<> struct type<signed char> {
      static const char* string() { static const char *const s = "signed char"; return s; }
      static bool is_float() { return false; }
      static bool is_inf(const signed char) { return false; }
      static bool is_nan(const signed char) { return false; }
      static signed char min() { return ~max(); }
      static signed char max() { return (signed char)((unsigned char)-1>>1); }
      static signed char inf() { return max(); }
      static signed char cut(const double val) {
        return val<(double)min()?min():val>(double)max()?max():(signed char)val; }
      static const char* format() { return "%d"; }
      static const char* format_s() { return "%d"; }
      static int format(const signed char val) { return (int)val; }
    };

    template<> struct type<unsigned short> {
      static const char* string() { static const char *const s = "unsigned short"; return s; }
      static bool is_float() { return false; }
      static bool is_inf(const unsigned short) { return false; }
      static bool is_nan(const unsigned short) { return false; }
      static unsigned short min() { return 0; }
      static unsigned short max() { return (unsigned short)-1; }
      static unsigned short inf() { return max(); }
      static unsigned short cut(const double val) {
        return val<(double)min()?min():val>(double)max()?max():(unsigned short)val; }
      static const char* format() { return "%u"; }
      static const char* format_s() { return "%u"; }
      static unsigned int format(const unsigned short val) { return (unsigned int)val; }
    };

    template<> struct type<short> {
      static const char* string() { static const char *const s = "short"; return s; }
      static bool is_float() { return false; }
      static bool is_inf(const short) { return false; }
      static bool is_nan(const short) { return false; }
      static short min() { return ~max(); }
      static short max() { return (short)((unsigned short)-1>>1); }
      static short inf() { return max(); }
      static short cut(const double val) { return val<(double)min()?min():val>(double)max()?max():(short)val; }
      static const char* format() { return "%d"; }
      static const char* format_s() { return "%d"; }
      static int format(const short val) { return (int)val; }
    };

    template<> struct type<unsigned int> {
      static const char* string() { static const char *const s = "unsigned int"; return s; }
      static bool is_float() { return false; }
      static bool is_inf(const unsigned int) { return false; }
      static bool is_nan(const unsigned int) { return false; }
      static unsigned int min() { return 0; }
      static unsigned int max() { return (unsigned int)-1; }
      static unsigned int inf() { return max(); }
      static unsigned int cut(const double val) {
        return val<(double)min()?min():val>(double)max()?max():(unsigned int)val; }
      static const char* format() { return "%u"; }
      static const char* format_s() { return "%u"; }
      static unsigned int format(const unsigned int val) { return val; }
    };

    template<> struct type<int> {
      static const char* string() { static const char *const s = "int"; return s; }
      static bool is_float() { return false; }
      static bool is_inf(const int) { return false; }
      static bool is_nan(const int) { return false; }
      static int min() { return ~max(); }
      static int max() { return (int)((unsigned int)-1>>1); }
      static int inf() { return max(); }
      static int cut(const double val) { return val<(double)min()?min():val>(double)max()?max():(int)val; }
      static const char* format() { return "%d"; }
      static const char* format_s() { return "%d"; }
      static int format(const int val) { return val; }
    };

    template<> struct type<cimg_uint64> {
      static const char* string() { static const char *const s = "unsigned int64"; return s; }
      static bool is_float() { return false; }
      static bool is_inf(const cimg_uint64) { return false; }
      static bool is_nan(const cimg_uint64) { return false; }
      static cimg_uint64 min() { return 0; }
      static cimg_uint64 max() { return (cimg_uint64)-1; }
      static cimg_uint64 inf() { return max(); }
      static cimg_uint64 cut(const double val) {
        return val<(double)min()?min():val>(double)max()?max():(cimg_uint64)val; }
      static const char* format() { return cimg_fuint64; }
      static const char* format_s() { return cimg_fuint64; }
      static unsigned long format(const cimg_uint64 val) { return (unsigned long)val; }
    };

    template<> struct type<cimg_int64> {
      static const char* string() { static const char *const s = "int64"; return s; }
      static bool is_float() { return false; }
      static bool is_inf(const cimg_int64) { return false; }
      static bool is_nan(const cimg_int64) { return false; }
      static cimg_int64 min() { return ~max(); }
      static cimg_int64 max() { return (cimg_int64)((cimg_uint64)-1>>1); }
      static cimg_int64 inf() { return max(); }
      static cimg_int64 cut(const double val) {
        return val<(double)min()?min():val>(double)max()?max():(cimg_int64)val;
      }
      static const char* format() { return cimg_fint64; }
      static const char* format_s() { return cimg_fint64; }
      static long format(const long val) { return (long)val; }
    };

    template<> struct type<double> {
      static const char* string() { static const char *const s = "double"; return s; }
      static bool is_float() { return true; }
      static bool is_inf(const double val) {
#ifdef isinf
        return (bool)isinf(val);
#else
        return !is_nan(val) && (val<cimg::type<double>::min() || val>cimg::type<double>::max());
#endif
      }
      static bool is_nan(const double val) { // Custom version that works with '-ffast-math'
        if (sizeof(double)==8) {
          cimg_uint64 u;
          std::memcpy(&u,&val,sizeof(double));
          return ((unsigned int)(u>>32)&0x7fffffff) + ((unsigned int)u!=0)>0x7ff00000;
        }
#ifdef isnan
        return (bool)isnan(val);
#else
        return !(val==val);
#endif
      }
      static double min() { return -DBL_MAX; }
      static double max() { return DBL_MAX; }
      static double inf() {
#ifdef INFINITY
        return (double)INFINITY;
#else
        return max()*max();
#endif
      }
      static double nan() {
#ifdef NAN
        return (double)NAN;
#else
        const double val_nan = -std::sqrt(-1.0); return val_nan;
#endif
      }
      static double cut(const double val) { return val; }
      static const char* format() { return "%.17g"; }
      static const char* format_s() { return "%g"; }
      static double format(const double val) { return val; }
    };

    template<> struct type<float> {
      static const char* string() { static const char *const s = "float"; return s; }
      static bool is_float() { return true; }
      static bool is_inf(const float val) {
#ifdef isinf
        return (bool)isinf(val);
#else
        return !is_nan(val) && (val<cimg::type<float>::min() || val>cimg::type<float>::max());
#endif
      }
      static bool is_nan(const float val) { // Custom version that works with '-ffast-math'
        if (sizeof(float)==4) {
          unsigned int u;
          std::memcpy(&u,&val,sizeof(float));
          return (u&0x7fffffff)>0x7f800000;
        }
#ifdef isnan
        return (bool)isnan(val);
#else
        return !(val==val);
#endif
      }
      static float min() { return -FLT_MAX; }
      static float max() { return FLT_MAX; }
      static float inf() { return (float)cimg::type<double>::inf(); }
      static float nan() { return (float)cimg::type<double>::nan(); }
      static float cut(const double val) { return (float)val; }
      static float cut(const float val) { return (float)val; }
      static const char* format() { return "%.9g"; }
      static const char* format_s() { return "%g"; }
      static double format(const float val) { return (double)val; }
    };

    template<> struct type<long double> {
      static const char* string() { static const char *const s = "long double"; return s; }
      static bool is_float() { return true; }
      static bool is_inf(const long double val) {
#ifdef isinf
        return (bool)isinf(val);
#else
        return !is_nan(val) && (val<cimg::type<long double>::min() || val>cimg::type<long double>::max());
#endif
      }
      static bool is_nan(const long double val) {
#ifdef isnan
        return (bool)isnan(val);
#else
        return !(val==val);
#endif
      }
      static long double min() { return -LDBL_MAX; }
      static long double max() { return LDBL_MAX; }
      static long double inf() { return max()*max(); }
      static long double nan() { const long double val_nan = -std::sqrt(-1.0L); return val_nan; }
      static long double cut(const long double val) { return val; }
      static const char* format() { return "%.17g"; }
      static const char* format_s() { return "%g"; }
      static double format(const long double val) { return (double)val; }
    };

#ifdef cimg_use_half
    template<> struct type<half> {
      static const char* string() { static const char *const s = "half"; return s; }
      static bool is_float() { return true; }
      static bool is_inf(const long double val) {
#ifdef isinf
        return (bool)isinf(val);
#else
        return !is_nan(val) && (val<cimg::type<half>::min() || val>cimg::type<half>::max());
#endif
      }
      static bool is_nan(const half val) { // Custom version that works with '-ffast-math'
        if (sizeof(half)==2) {
          short u;
          std::memcpy(&u,&val,sizeof(short));
          return (bool)((u&0x7fff)>0x7c00);
        }
        return cimg::type<float>::is_nan((float)val);
      }
      static half min() { return (half)-65504; }
      static half max() { return (half)65504; }
      static half inf() { return max()*max(); }
      static half nan() { const half val_nan = (half)-std::sqrt(-1.0); return val_nan; }
      static half cut(const double val) { return (half)val; }
      static const char* format() { return "%.9g"; }
      static const char* format_s() { return "%g"; }
      static double format(const half val) { return (double)val; }
    };
#endif

    template<typename T, typename t> struct superset { typedef T type; };
    template<> struct superset<bool,unsigned char> { typedef unsigned char type; };
    template<> struct superset<bool,char> { typedef char type; };
    template<> struct superset<bool,signed char> { typedef signed char type; };
    template<> struct superset<bool,unsigned short> { typedef unsigned short type; };
    template<> struct superset<bool,short> { typedef short type; };
    template<> struct superset<bool,unsigned int> { typedef unsigned int type; };
    template<> struct superset<bool,int> { typedef int type; };
    template<> struct superset<bool,cimg_uint64> { typedef cimg_uint64 type; };
    template<> struct superset<bool,cimg_int64> { typedef cimg_int64 type; };
    template<> struct superset<bool,float> { typedef float type; };
    template<> struct superset<bool,double> { typedef double type; };
    template<> struct superset<unsigned char,char> { typedef short type; };
    template<> struct superset<unsigned char,signed char> { typedef short type; };
    template<> struct superset<unsigned char,unsigned short> { typedef unsigned short type; };
    template<> struct superset<unsigned char,short> { typedef short type; };
    template<> struct superset<unsigned char,unsigned int> { typedef unsigned int type; };
    template<> struct superset<unsigned char,int> { typedef int type; };
    template<> struct superset<unsigned char,cimg_uint64> { typedef cimg_uint64 type; };
    template<> struct superset<unsigned char,cimg_int64> { typedef cimg_int64 type; };
    template<> struct superset<unsigned char,float> { typedef float type; };
    template<> struct superset<unsigned char,double> { typedef double type; };
    template<> struct superset<signed char,unsigned char> { typedef short type; };
    template<> struct superset<signed char,char> { typedef short type; };
    template<> struct superset<signed char,unsigned short> { typedef int type; };
    template<> struct superset<signed char,short> { typedef short type; };
    template<> struct superset<signed char,unsigned int> { typedef cimg_int64 type; };
    template<> struct superset<signed char,int> { typedef int type; };
    template<> struct superset<signed char,cimg_uint64> { typedef cimg_int64 type; };
    template<> struct superset<signed char,cimg_int64> { typedef cimg_int64 type; };
    template<> struct superset<signed char,float> { typedef float type; };
    template<> struct superset<signed char,double> { typedef double type; };
    template<> struct superset<char,unsigned char> { typedef short type; };
    template<> struct superset<char,signed char> { typedef short type; };
    template<> struct superset<char,unsigned short> { typedef int type; };
    template<> struct superset<char,short> { typedef short type; };
    template<> struct superset<char,unsigned int> { typedef cimg_int64 type; };
    template<> struct superset<char,int> { typedef int type; };
    template<> struct superset<char,cimg_uint64> { typedef cimg_int64 type; };
    template<> struct superset<char,cimg_int64> { typedef cimg_int64 type; };
    template<> struct superset<char,float> { typedef float type; };
    template<> struct superset<char,double> { typedef double type; };
    template<> struct superset<unsigned short,char> { typedef int type; };
    template<> struct superset<unsigned short,signed char> { typedef int type; };
    template<> struct superset<unsigned short,short> { typedef int type; };
    template<> struct superset<unsigned short,unsigned int> { typedef unsigned int type; };
    template<> struct superset<unsigned short,int> { typedef int type; };
    template<> struct superset<unsigned short,cimg_uint64> { typedef cimg_uint64 type; };
    template<> struct superset<unsigned short,cimg_int64> { typedef cimg_int64 type; };
    template<> struct superset<unsigned short,float> { typedef float type; };
    template<> struct superset<unsigned short,double> { typedef double type; };
    template<> struct superset<short,unsigned short> { typedef int type; };
    template<> struct superset<short,unsigned int> { typedef cimg_int64 type; };
    template<> struct superset<short,int> { typedef int type; };
    template<> struct superset<short,cimg_uint64> { typedef cimg_int64 type; };
    template<> struct superset<short,cimg_int64> { typedef cimg_int64 type; };
    template<> struct superset<short,float> { typedef float type; };
    template<> struct superset<short,double> { typedef double type; };
    template<> struct superset<unsigned int,char> { typedef cimg_int64 type; };
    template<> struct superset<unsigned int,signed char> { typedef cimg_int64 type; };
    template<> struct superset<unsigned int,short> { typedef cimg_int64 type; };
    template<> struct superset<unsigned int,int> { typedef cimg_int64 type; };
    template<> struct superset<unsigned int,cimg_uint64> { typedef cimg_uint64 type; };
    template<> struct superset<unsigned int,cimg_int64> { typedef cimg_int64 type; };
    template<> struct superset<unsigned int,float> { typedef float type; };
    template<> struct superset<unsigned int,double> { typedef double type; };
    template<> struct superset<int,unsigned int> { typedef cimg_int64 type; };
    template<> struct superset<int,cimg_uint64> { typedef cimg_int64 type; };
    template<> struct superset<int,cimg_int64> { typedef cimg_int64 type; };
    template<> struct superset<int,float> { typedef float type; };
    template<> struct superset<int,double> { typedef double type; };
    template<> struct superset<cimg_uint64,char> { typedef cimg_int64 type; };
    template<> struct superset<cimg_uint64,signed char> { typedef cimg_int64 type; };
    template<> struct superset<cimg_uint64,short> { typedef cimg_int64 type; };
    template<> struct superset<cimg_uint64,int> { typedef cimg_int64 type; };
    template<> struct superset<cimg_uint64,cimg_int64> { typedef cimg_int64 type; };
    template<> struct superset<cimg_uint64,float> { typedef double type; };
    template<> struct superset<cimg_uint64,double> { typedef double type; };
    template<> struct superset<cimg_int64,float> { typedef double type; };
    template<> struct superset<cimg_int64,double> { typedef double type; };
    template<> struct superset<float,double> { typedef double type; };
#ifdef cimg_use_half
    template<> struct superset<half,unsigned short> { typedef float type; };
    template<> struct superset<half,short> { typedef float type; };
    template<> struct superset<half,unsigned int> { typedef float type; };
    template<> struct superset<half,int> { typedef float type; };
    template<> struct superset<half,cimg_uint64> { typedef float type; };
    template<> struct superset<half,cimg_int64> { typedef float type; };
    template<> struct superset<half,float> { typedef float type; };
    template<> struct superset<half,double> { typedef double type; };
#endif

    template<typename t1, typename t2, typename t3> struct superset2 {
      typedef typename superset<t1, typename superset<t2,t3>::type>::type type;
    };

    template<typename t1, typename t2, typename t3, typename t4> struct superset3 {
      typedef typename superset<t1, typename superset2<t2,t3,t4>::type>::type type;
    };

    template<typename t1, typename t2> struct last { typedef t2 type; };

#define _cimg_Tt typename cimg::superset<T,t>::type
#define _cimg_Tfloat typename cimg::superset<T,float>::type
#define _cimg_Ttfloat typename cimg::superset2<T,t,float>::type
#define _cimg_Ttdouble typename cimg::superset2<T,t,double>::type

    // Define variables used internally by CImg.
#if cimg_display==1
    struct X11_info {
      unsigned int nb_wins;
      pthread_t *events_thread;
      pthread_cond_t wait_event;
      pthread_mutex_t wait_event_mutex;
      CImgDisplay **wins;
      Display *display;
      unsigned int nb_bits;
      bool is_blue_first;
      bool is_shm_enabled;
      bool byte_order;
#ifdef cimg_use_xrandr
      XRRScreenSize *resolutions;
      Rotation curr_rotation;
      unsigned int curr_resolution;
      unsigned int nb_resolutions;
#endif
      X11_info():nb_wins(0),events_thread(0),display(0),
                 nb_bits(0),is_blue_first(false),is_shm_enabled(false),byte_order(false) {
#ifdef __FreeBSD__
        XInitThreads();
#endif
        wins = new CImgDisplay*[1024];
        pthread_mutex_init(&wait_event_mutex,0);
        pthread_cond_init(&wait_event,0);
#ifdef cimg_use_xrandr
        resolutions = 0;
        curr_rotation = 0;
        curr_resolution = nb_resolutions = 0;
#endif
      }

      ~X11_info() {
        delete[] wins;
        /*
          if (events_thread) {
          pthread_cancel(*events_thread);
          delete events_thread;
          }
          if (display) { } // XCloseDisplay(display); }
          pthread_cond_destroy(&wait_event);
          pthread_mutex_unlock(&wait_event_mutex);
          pthread_mutex_destroy(&wait_event_mutex);
        */
      }
    };
#if defined(cimg_module)
    X11_info& X11_attr();
#elif defined(cimg_main)
    X11_info& X11_attr() { static X11_info val; return val; }
#else
    inline X11_info& X11_attr() { static X11_info val; return val; }
#endif
#define cimg_lock_display() cimg::mutex(15)
#define cimg_unlock_display() cimg::mutex(15,0)

#elif cimg_display==2
    struct Win32_info {
      HANDLE wait_event;
      Win32_info() { wait_event = CreateEvent(0,FALSE,FALSE,0); }
    };
#if defined(cimg_module)
    Win32_info& Win32_attr();
#elif defined(cimg_main)
    Win32_info& Win32_attr() { static Win32_info val; return val; }
#else
    inline Win32_info& Win32_attr() { static Win32_info val; return val; }
#endif
#endif

    struct Mutex_info {
#if cimg_OS==2
      HANDLE mutex[32];
      Mutex_info() { for (unsigned int i = 0; i<32; ++i) mutex[i] = CreateMutex(0,FALSE,0); }
      void lock(const unsigned int n) { WaitForSingleObject(mutex[n],INFINITE); }
      void unlock(const unsigned int n) { ReleaseMutex(mutex[n]); }
      int trylock(const unsigned int) { return 0; }
#elif defined(_PTHREAD_H)
      pthread_mutex_t mutex[32];
      Mutex_info() { for (unsigned int i = 0; i<32; ++i) pthread_mutex_init(&mutex[i],0); }
      void lock(const unsigned int n) { pthread_mutex_lock(&mutex[n]); }
      void unlock(const unsigned int n) { pthread_mutex_unlock(&mutex[n]); }
      int trylock(const unsigned int n) { return pthread_mutex_trylock(&mutex[n]); }
#else
      Mutex_info() {}
      void lock(const unsigned int) {}
      void unlock(const unsigned int) {}
      int trylock(const unsigned int) { return 0; }
#endif
    };
#if defined(cimg_module)
    Mutex_info& Mutex_attr();
#elif defined(cimg_main)
    Mutex_info& Mutex_attr() { static Mutex_info val; return val; }
#else
    inline Mutex_info& Mutex_attr() { static Mutex_info val; return val; }
#endif

#if defined(cimg_use_magick)
    static struct Magick_info {
      Magick_info() {
        Magick::InitializeMagick("");
      }
    } _Magick_info;
#endif

#if cimg_display==1
    // Define keycodes for X11-based graphical systems.
    const unsigned int keyESC        = XK_Escape;
    const unsigned int keyF1         = XK_F1;
    const unsigned int keyF2         = XK_F2;
    const unsigned int keyF3         = XK_F3;
    const unsigned int keyF4         = XK_F4;
    const unsigned int keyF5         = XK_F5;
    const unsigned int keyF6         = XK_F6;
    const unsigned int keyF7         = XK_F7;
    const unsigned int keyF8         = XK_F8;
    const unsigned int keyF9         = XK_F9;
    const unsigned int keyF10        = XK_F10;
    const unsigned int keyF11        = XK_F11;
    const unsigned int keyF12        = XK_F12;
    const unsigned int keyPAUSE      = XK_Pause;
    const unsigned int key1          = XK_1;
    const unsigned int key2          = XK_2;
    const unsigned int key3          = XK_3;
    const unsigned int key4          = XK_4;
    const unsigned int key5          = XK_5;
    const unsigned int key6          = XK_6;
    const unsigned int key7          = XK_7;
    const unsigned int key8          = XK_8;
    const unsigned int key9          = XK_9;
    const unsigned int key0          = XK_0;
    const unsigned int keyBACKSPACE  = XK_BackSpace;
    const unsigned int keyINSERT     = XK_Insert;
    const unsigned int keyHOME       = XK_Home;
    const unsigned int keyPAGEUP     = XK_Page_Up;
    const unsigned int keyTAB        = XK_Tab;
    const unsigned int keyQ          = XK_q;
    const unsigned int keyW          = XK_w;
    const unsigned int keyE          = XK_e;
    const unsigned int keyR          = XK_r;
    const unsigned int keyT          = XK_t;
    const unsigned int keyY          = XK_y;
    const unsigned int keyU          = XK_u;
    const unsigned int keyI          = XK_i;
    const unsigned int keyO          = XK_o;
    const unsigned int keyP          = XK_p;
    const unsigned int keyDELETE     = XK_Delete;
    const unsigned int keyEND        = XK_End;
    const unsigned int keyPAGEDOWN   = XK_Page_Down;
    const unsigned int keyCAPSLOCK   = XK_Caps_Lock;
    const unsigned int keyA          = XK_a;
    const unsigned int keyS          = XK_s;
    const unsigned int keyD          = XK_d;
    const unsigned int keyF          = XK_f;
    const unsigned int keyG          = XK_g;
    const unsigned int keyH          = XK_h;
    const unsigned int keyJ          = XK_j;
    const unsigned int keyK          = XK_k;
    const unsigned int keyL          = XK_l;
    const unsigned int keyENTER      = XK_Return;
    const unsigned int keySHIFTLEFT  = XK_Shift_L;
    const unsigned int keyZ          = XK_z;
    const unsigned int keyX          = XK_x;
    const unsigned int keyC          = XK_c;
    const unsigned int keyV          = XK_v;
    const unsigned int keyB          = XK_b;
    const unsigned int keyN          = XK_n;
    const unsigned int keyM          = XK_m;
    const unsigned int keySHIFTRIGHT = XK_Shift_R;
    const unsigned int keyARROWUP    = XK_Up;
    const unsigned int keyCTRLLEFT   = XK_Control_L;
    const unsigned int keyAPPLEFT    = XK_Super_L;
    const unsigned int keyALT        = XK_Alt_L;
    const unsigned int keySPACE      = XK_space;
    const unsigned int keyALTGR      = XK_Alt_R;
    const unsigned int keyAPPRIGHT   = XK_Super_R;
    const unsigned int keyMENU       = XK_Menu;
    const unsigned int keyCTRLRIGHT  = XK_Control_R;
    const unsigned int keyARROWLEFT  = XK_Left;
    const unsigned int keyARROWDOWN  = XK_Down;
    const unsigned int keyARROWRIGHT = XK_Right;
    const unsigned int keyPAD0       = XK_KP_0;
    const unsigned int keyPAD1       = XK_KP_1;
    const unsigned int keyPAD2       = XK_KP_2;
    const unsigned int keyPAD3       = XK_KP_3;
    const unsigned int keyPAD4       = XK_KP_4;
    const unsigned int keyPAD5       = XK_KP_5;
    const unsigned int keyPAD6       = XK_KP_6;
    const unsigned int keyPAD7       = XK_KP_7;
    const unsigned int keyPAD8       = XK_KP_8;
    const unsigned int keyPAD9       = XK_KP_9;
    const unsigned int keyPADADD     = XK_KP_Add;
    const unsigned int keyPADSUB     = XK_KP_Subtract;
    const unsigned int keyPADMUL     = XK_KP_Multiply;
    const unsigned int keyPADDIV     = XK_KP_Divide;

#elif cimg_display==2
    // Define keycodes for Windows.
    const unsigned int keyESC        = VK_ESCAPE;
    const unsigned int keyF1         = VK_F1;
    const unsigned int keyF2         = VK_F2;
    const unsigned int keyF3         = VK_F3;
    const unsigned int keyF4         = VK_F4;
    const unsigned int keyF5         = VK_F5;
    const unsigned int keyF6         = VK_F6;
    const unsigned int keyF7         = VK_F7;
    const unsigned int keyF8         = VK_F8;
    const unsigned int keyF9         = VK_F9;
    const unsigned int keyF10        = VK_F10;
    const unsigned int keyF11        = VK_F11;
    const unsigned int keyF12        = VK_F12;
    const unsigned int keyPAUSE      = VK_PAUSE;
    const unsigned int key1          = '1';
    const unsigned int key2          = '2';
    const unsigned int key3          = '3';
    const unsigned int key4          = '4';
    const unsigned int key5          = '5';
    const unsigned int key6          = '6';
    const unsigned int key7          = '7';
    const unsigned int key8          = '8';
    const unsigned int key9          = '9';
    const unsigned int key0          = '0';
    const unsigned int keyBACKSPACE  = VK_BACK;
    const unsigned int keyINSERT     = VK_INSERT;
    const unsigned int keyHOME       = VK_HOME;
    const unsigned int keyPAGEUP     = VK_PRIOR;
    const unsigned int keyTAB        = VK_TAB;
    const unsigned int keyQ          = 'Q';
    const unsigned int keyW          = 'W';
    const unsigned int keyE          = 'E';
    const unsigned int keyR          = 'R';
    const unsigned int keyT          = 'T';
    const unsigned int keyY          = 'Y';
    const unsigned int keyU          = 'U';
    const unsigned int keyI          = 'I';
    const unsigned int keyO          = 'O';
    const unsigned int keyP          = 'P';
    const unsigned int keyDELETE     = VK_DELETE;
    const unsigned int keyEND        = VK_END;
    const unsigned int keyPAGEDOWN   = VK_NEXT;
    const unsigned int keyCAPSLOCK   = VK_CAPITAL;
    const unsigned int keyA          = 'A';
    const unsigned int keyS          = 'S';
    const unsigned int keyD          = 'D';
    const unsigned int keyF          = 'F';
    const unsigned int keyG          = 'G';
    const unsigned int keyH          = 'H';
    const unsigned int keyJ          = 'J';
    const unsigned int keyK          = 'K';
    const unsigned int keyL          = 'L';
    const unsigned int keyENTER      = VK_RETURN;
    const unsigned int keySHIFTLEFT  = VK_SHIFT;
    const unsigned int keyZ          = 'Z';
    const unsigned int keyX          = 'X';
    const unsigned int keyC          = 'C';
    const unsigned int keyV          = 'V';
    const unsigned int keyB          = 'B';
    const unsigned int keyN          = 'N';
    const unsigned int keyM          = 'M';
    const unsigned int keySHIFTRIGHT = VK_SHIFT;
    const unsigned int keyARROWUP    = VK_UP;
    const unsigned int keyCTRLLEFT   = VK_CONTROL;
    const unsigned int keyAPPLEFT    = VK_LWIN;
    const unsigned int keyALT        = VK_LMENU;
    const unsigned int keySPACE      = VK_SPACE;
    const unsigned int keyALTGR      = VK_CONTROL;
    const unsigned int keyAPPRIGHT   = VK_RWIN;
    const unsigned int keyMENU       = VK_APPS;
    const unsigned int keyCTRLRIGHT  = VK_CONTROL;
    const unsigned int keyARROWLEFT  = VK_LEFT;
    const unsigned int keyARROWDOWN  = VK_DOWN;
    const unsigned int keyARROWRIGHT = VK_RIGHT;
    const unsigned int keyPAD0       = 0x60;
    const unsigned int keyPAD1       = 0x61;
    const unsigned int keyPAD2       = 0x62;
    const unsigned int keyPAD3       = 0x63;
    const unsigned int keyPAD4       = 0x64;
    const unsigned int keyPAD5       = 0x65;
    const unsigned int keyPAD6       = 0x66;
    const unsigned int keyPAD7       = 0x67;
    const unsigned int keyPAD8       = 0x68;
    const unsigned int keyPAD9       = 0x69;
    const unsigned int keyPADADD     = VK_ADD;
    const unsigned int keyPADSUB     = VK_SUBTRACT;
    const unsigned int keyPADMUL     = VK_MULTIPLY;
    const unsigned int keyPADDIV     = VK_DIVIDE;

#else
    // Define random keycodes when no display is available.
    // (should rarely be used then!).
    const unsigned int keyESC        = 1U;   //!< Keycode for the \c ESC key (architecture-dependent).
    const unsigned int keyF1         = 2U;   //!< Keycode for the \c F1 key (architecture-dependent).
    const unsigned int keyF2         = 3U;   //!< Keycode for the \c F2 key (architecture-dependent).
    const unsigned int keyF3         = 4U;   //!< Keycode for the \c F3 key (architecture-dependent).
    const unsigned int keyF4         = 5U;   //!< Keycode for the \c F4 key (architecture-dependent).
    const unsigned int keyF5         = 6U;   //!< Keycode for the \c F5 key (architecture-dependent).
    const unsigned int keyF6         = 7U;   //!< Keycode for the \c F6 key (architecture-dependent).
    const unsigned int keyF7         = 8U;   //!< Keycode for the \c F7 key (architecture-dependent).
    const unsigned int keyF8         = 9U;   //!< Keycode for the \c F8 key (architecture-dependent).
    const unsigned int keyF9         = 10U;  //!< Keycode for the \c F9 key (architecture-dependent).
    const unsigned int keyF10        = 11U;  //!< Keycode for the \c F10 key (architecture-dependent).
    const unsigned int keyF11        = 12U;  //!< Keycode for the \c F11 key (architecture-dependent).
    const unsigned int keyF12        = 13U;  //!< Keycode for the \c F12 key (architecture-dependent).
    const unsigned int keyPAUSE      = 14U;  //!< Keycode for the \c PAUSE key (architecture-dependent).
    const unsigned int key1          = 15U;  //!< Keycode for the \c 1 key (architecture-dependent).
    const unsigned int key2          = 16U;  //!< Keycode for the \c 2 key (architecture-dependent).
    const unsigned int key3          = 17U;  //!< Keycode for the \c 3 key (architecture-dependent).
    const unsigned int key4          = 18U;  //!< Keycode for the \c 4 key (architecture-dependent).
    const unsigned int key5          = 19U;  //!< Keycode for the \c 5 key (architecture-dependent).
    const unsigned int key6          = 20U;  //!< Keycode for the \c 6 key (architecture-dependent).
    const unsigned int key7          = 21U;  //!< Keycode for the \c 7 key (architecture-dependent).
    const unsigned int key8          = 22U;  //!< Keycode for the \c 8 key (architecture-dependent).
    const unsigned int key9          = 23U;  //!< Keycode for the \c 9 key (architecture-dependent).
    const unsigned int key0          = 24U;  //!< Keycode for the \c 0 key (architecture-dependent).
    const unsigned int keyBACKSPACE  = 25U;  //!< Keycode for the \c BACKSPACE key (architecture-dependent).
    const unsigned int keyINSERT     = 26U;  //!< Keycode for the \c INSERT key (architecture-dependent).
    const unsigned int keyHOME       = 27U;  //!< Keycode for the \c HOME key (architecture-dependent).
    const unsigned int keyPAGEUP     = 28U;  //!< Keycode for the \c PAGEUP key (architecture-dependent).
    const unsigned int keyTAB        = 29U;  //!< Keycode for the \c TAB key (architecture-dependent).
    const unsigned int keyQ          = 30U;  //!< Keycode for the \c Q key (architecture-dependent).
    const unsigned int keyW          = 31U;  //!< Keycode for the \c W key (architecture-dependent).
    const unsigned int keyE          = 32U;  //!< Keycode for the \c E key (architecture-dependent).
    const unsigned int keyR          = 33U;  //!< Keycode for the \c R key (architecture-dependent).
    const unsigned int keyT          = 34U;  //!< Keycode for the \c T key (architecture-dependent).
    const unsigned int keyY          = 35U;  //!< Keycode for the \c Y key (architecture-dependent).
    const unsigned int keyU          = 36U;  //!< Keycode for the \c U key (architecture-dependent).
    const unsigned int keyI          = 37U;  //!< Keycode for the \c I key (architecture-dependent).
    const unsigned int keyO          = 38U;  //!< Keycode for the \c O key (architecture-dependent).
    const unsigned int keyP          = 39U;  //!< Keycode for the \c P key (architecture-dependent).
    const unsigned int keyDELETE     = 40U;  //!< Keycode for the \c DELETE key (architecture-dependent).
    const unsigned int keyEND        = 41U;  //!< Keycode for the \c END key (architecture-dependent).
    const unsigned int keyPAGEDOWN   = 42U;  //!< Keycode for the \c PAGEDOWN key (architecture-dependent).
    const unsigned int keyCAPSLOCK   = 43U;  //!< Keycode for the \c CAPSLOCK key (architecture-dependent).
    const unsigned int keyA          = 44U;  //!< Keycode for the \c A key (architecture-dependent).
    const unsigned int keyS          = 45U;  //!< Keycode for the \c S key (architecture-dependent).
    const unsigned int keyD          = 46U;  //!< Keycode for the \c D key (architecture-dependent).
    const unsigned int keyF          = 47U;  //!< Keycode for the \c F key (architecture-dependent).
    const unsigned int keyG          = 48U;  //!< Keycode for the \c G key (architecture-dependent).
    const unsigned int keyH          = 49U;  //!< Keycode for the \c H key (architecture-dependent).
    const unsigned int keyJ          = 50U;  //!< Keycode for the \c J key (architecture-dependent).
    const unsigned int keyK          = 51U;  //!< Keycode for the \c K key (architecture-dependent).
    const unsigned int keyL          = 52U;  //!< Keycode for the \c L key (architecture-dependent).
    const unsigned int keyENTER      = 53U;  //!< Keycode for the \c ENTER key (architecture-dependent).
    const unsigned int keySHIFTLEFT  = 54U;  //!< Keycode for the \c SHIFTLEFT key (architecture-dependent).
    const unsigned int keyZ          = 55U;  //!< Keycode for the \c Z key (architecture-dependent).
    const unsigned int keyX          = 56U;  //!< Keycode for the \c X key (architecture-dependent).
    const unsigned int keyC          = 57U;  //!< Keycode for the \c C key (architecture-dependent).
    const unsigned int keyV          = 58U;  //!< Keycode for the \c V key (architecture-dependent).
    const unsigned int keyB          = 59U;  //!< Keycode for the \c B key (architecture-dependent).
    const unsigned int keyN          = 60U;  //!< Keycode for the \c N key (architecture-dependent).
    const unsigned int keyM          = 61U;  //!< Keycode for the \c M key (architecture-dependent).
    const unsigned int keySHIFTRIGHT = 62U;  //!< Keycode for the \c SHIFTRIGHT key (architecture-dependent).
    const unsigned int keyARROWUP    = 63U;  //!< Keycode for the \c ARROWUP key (architecture-dependent).
    const unsigned int keyCTRLLEFT   = 64U;  //!< Keycode for the \c CTRLLEFT key (architecture-dependent).
    const unsigned int keyAPPLEFT    = 65U;  //!< Keycode for the \c APPLEFT key (architecture-dependent).
    const unsigned int keyALT        = 66U;  //!< Keycode for the \c ALT key (architecture-dependent).
    const unsigned int keySPACE      = 67U;  //!< Keycode for the \c SPACE key (architecture-dependent).
    const unsigned int keyALTGR      = 68U;  //!< Keycode for the \c ALTGR key (architecture-dependent).
    const unsigned int keyAPPRIGHT   = 69U;  //!< Keycode for the \c APPRIGHT key (architecture-dependent).
    const unsigned int keyMENU       = 70U;  //!< Keycode for the \c MENU key (architecture-dependent).
    const unsigned int keyCTRLRIGHT  = 71U;  //!< Keycode for the \c CTRLRIGHT key (architecture-dependent).
    const unsigned int keyARROWLEFT  = 72U;  //!< Keycode for the \c ARROWLEFT key (architecture-dependent).
    const unsigned int keyARROWDOWN  = 73U;  //!< Keycode for the \c ARROWDOWN key (architecture-dependent).
    const unsigned int keyARROWRIGHT = 74U;  //!< Keycode for the \c ARROWRIGHT key (architecture-dependent).
    const unsigned int keyPAD0       = 75U;  //!< Keycode for the \c PAD0 key (architecture-dependent).
    const unsigned int keyPAD1       = 76U;  //!< Keycode for the \c PAD1 key (architecture-dependent).
    const unsigned int keyPAD2       = 77U;  //!< Keycode for the \c PAD2 key (architecture-dependent).
    const unsigned int keyPAD3       = 78U;  //!< Keycode for the \c PAD3 key (architecture-dependent).
    const unsigned int keyPAD4       = 79U;  //!< Keycode for the \c PAD4 key (architecture-dependent).
    const unsigned int keyPAD5       = 80U;  //!< Keycode for the \c PAD5 key (architecture-dependent).
    const unsigned int keyPAD6       = 81U;  //!< Keycode for the \c PAD6 key (architecture-dependent).
    const unsigned int keyPAD7       = 82U;  //!< Keycode for the \c PAD7 key (architecture-dependent).
    const unsigned int keyPAD8       = 83U;  //!< Keycode for the \c PAD8 key (architecture-dependent).
    const unsigned int keyPAD9       = 84U;  //!< Keycode for the \c PAD9 key (architecture-dependent).
    const unsigned int keyPADADD     = 85U;  //!< Keycode for the \c PADADD key (architecture-dependent).
    const unsigned int keyPADSUB     = 86U;  //!< Keycode for the \c PADSUB key (architecture-dependent).
    const unsigned int keyPADMUL     = 87U;  //!< Keycode for the \c PADMUL key (architecture-dependent).
    const unsigned int keyPADDIV     = 88U;  //!< Keycode for the \c PADDDIV key (architecture-dependent).
#endif

    const double PI = 3.14159265358979323846;   //!< Value of the mathematical constant PI

    // Define a 12x13 font (small size).
    static const char *const data_font12x13 =
      "                          .wjwlwmyuw>wjwkwbwjwkwRxuwmwjwkwmyuwJwjwlx`w      Fw                      "
      "   mwlwlwuwnwuynwuwmyTwlwkwuwmwuwnwlwkwuwmwuw_wuxlwlwkwuwnwuynwuwTwlwlwtwnwtwnw my     Qw   +wlw   b"
      "{ \\w  Wx`xTw_w[wbxawSwkw  nynwky<x1w `y    ,w  Xwuw   CxlwiwlwmyuwbwuwUwiwlwbwiwrwqw^wuwmxuwnwiwlwmy"
      "uwJwiwlw^wnwEymymymymy1w^wkxnxtxnw<| gybwkwuwjwtwowmxswnxnwkxlxkw:wlymxlymykwn{myo{nymy2ykwqwqwm{myo"
      "zn{o{mzpwrwpwkwkwswowkwqwqxswnyozlyozmzp}pwrwqwqwqwswswsxsxqwqwp}qwlwiwjybw`w[wcw_wkwkwkwkw mw\"wlwiw"
      "=wtw`xIw awuwlwm{o{mylwn|pwtwtwoy`w_w_wbwiwkxcwqwpwkznwuwjzpyGzqymyaxlylw_zWxkxaxrwqxrwqyswowkwkwkwk"
      "wkwkwk}qyo{o{o{o{owkwkwkwkznxswnymymymymyayuwqwrwpwrwpwrwpwrwqwqwpwkwtwlwkwlwuwnwuynwuwmyTwkwlwuwmwu"
      "wnwkwlwuwmwuwkxlwuxmwkwlwuwnwuynwuwTwkwlwuwmwuwlwmwkwtwUwuwuwowswowswowswowsw;wqwtw_ymzp~py>w bwswcw"
      "kwuwjwuwozpwtwuwnwtwowkwjwmwuwuwkwIxmxuxowuwmwswowswmxnwjwhwowswowsw0wmwowswuwnwrwowswpwswowkwjwrwqw"
      "rwpwkwkwtwnwkxsxqxswowswpwswnwswpwswowrwnwmwrwqwqwqwswswrwswowswjwpwlxjwkxuxLw[wcw_wSwkw mw\"wlwiw=wt"
      "wmxlwFw cwswnwuwnwkwjwswo{pwrwpwtwtwpwswby`w`yUwlwtwpwqwpwswowlw\\wrwrxuwHwrwfwuwjwlwlwTyuwVwlwtwawsw"
      "owswowswcwuwmwuwmwuwmwuwmwuwlwkwuwnwswpwkwkwkwkwkwkwkwkwswoxswowswowswowswowswowswowrwpwswpwrwpwrwpw"
      "rwpwrwpwswoznwtw  Ww (wGwtwtwqwqwqwuwuwuwqwswuwqwqw=wqxtw`{nzp~q{ozowrwnxmwtwow bzawkwuwl}rwuwnwtwuw"
      "nwtwowkwjwlyjwIwlwswmwiwkwnwuwnwkwhwnwswowswowkwewewixnwsytwswuwnwrwpwkwrwpwkwkwkwrwpwkwkwuwmwkxsxqw"
      "uwtwpwqwqwswowqwqwswowiwmwrwpwswowtwtwpwuwmwuwjwowkwjwlxsxXynzmymznyozlzoznwkwkwtwnwkzuyrzmynzmzowux"
      "myozmwswpwrwowtwtwrwrwpwrwp{mwlwiwHyuwpwtwkwmxlynzoxswmwmwswnwswowtxq|owtwtwpym{p{owswnwuwmwlwkwqwqx"
      "uwuxqwrwpwtwtwqwqwowlwuwuwkwmwlwtwowuwuwdwjznwl{nwuwnwkx_wtxtwswtwlwtwWwuytwgyjwmwjwawswoyuwVwlwtwnw"
      "twmwtwnwtwmwuwmwlwuwmwuwmwuwmwuwmwuwmwuwmxuwowkwkwkwkwkwkwkwkwkwrwpwuwtwpwqwqwqwqwqwqwqwqwqwowtwpwsw"
      "uwqwrwpwrwpwrwpwrwowuwnwswowuwlymymymymymymyuyqymymymymynwkwkwkwjynzmymymymymykwmzowswowswowswowswpw"
      "rwozowrwW}q}qwtwtwqwtwtwqwtwtwA}rwuw_{p~r~r}pwtwowrwnxmwtwow aw_w]wtwpwuwmxuwmybwjwlyjwIwlwswmwiwnyn"
      "wtwnznzkwmynwswTyp}pylwmwtwtwtwswuwn{owkwrwp{o{owk|pwkwkxlwkwuwuwuwqwuwtwpwqwqwswowqwqwswoykwmwrwpws"
      "wowuwuwuwowkwjwnwkwjwDwowswowkwswowswowkwswowswowkwkwuwmwkwswswswswowswowswowswoxlwswowkwswpwrwowtwt"
      "wqwtwowrwlwoxkwhxVxuxpwtypwuwjwnwtwnwkwswowtxnxmwswowqwqwtwuxqwtwnwtwtwqwswowswmwm{nwuwlxnwkwqwqwtwt"
      "wqwrwpwtwtwqwuyuwpwiwhwnwmwrwnwbwkwuwlwlwswoxuxowlwtw`wuwrwszmwtwo}dwuwtwuw[}qymx`wswoyuwow_ylxlwtwo"
      "yuwoyuwoyuwmwlwuwmwuwmwuwmwuwmwuwmwuwmwt{swk{o{o{o{owkwkwkwlztwpwuwtwpwqwqwqwqwqwqwqwqwqwnxowtwtwqwr"
      "wpwrwpwrwpwrwnwmwswowuwiwkwkwkwkwkwkwswswkwswowswowswowswowkwkwkwkwswowswowswowswowswowswowswcwtxows"
      "wowswowswowswpwrwowswpwrwWwtwtwqwqwqwuwuwuwqwuwswqwqw>wowuw`}q~q|q}qwrwpwrwowtwnwtwo~ izaw]wtwoykwux"
      "qwtwswfwjwmwuwuwn}eyaxlwswmwjwjwpwswjwowswmwmwswnzWy]ypwlwtwtwuwswswowrwpwkwrwpwkwkwsyqwrwpwkwkwuwmw"
      "kwuwuwuwqwtwuwpwqwqznwqwqzkynwmwrwowuwnwuwuwuwowkwjwnwkxkwGzowswowkwswo{owkwswowswowkwkxlwkwswswswsw"
      "owswowswowswowjxmwkwswowtwnwuwuwuwpxmwtwlwlwlwiwlytwewtwtwqwswowtxoznwswnxmwswnwuwmwuwnwswowtwtwqwtw"
      "twqwtwnwtwtwqwswowswmwmwswowswmwmwkwqwqwtwtwqwrwowuwuwpwuyuwq~own~own~owbwkwuwmznwswmwbwswawuwrwgwtw"
      "hwdwuytwXwJwswnxuw=wtwmwswowtxowswqxmwswowswowswowswowswowswnwtwowkwkwkwkwkwkwkwkwkwrwpwtwuwpwqwqwqw"
      "qwqwqwqwqwqwnxowtwtwqwrwpwrwpwrwpwrwnwmwswowtwmznznznznznzn~swk{o{o{o{owkwkwkwkwswowswowswowswowswow"
      "swowswo}qwuwuwowswowswowswowswowtwnwswowtwUwuwuwowswowswowswowsw@}qx`}q~pzo{pwrwpwrwowtwnwtwow aw_w_"
      "}owuwmwuwtwrwswuwewjwkwiwJwkwswmwkwiwp|kwowswmwmwswkwWym}mypwlwszr{owrwpwkwrwpwkwkwqwqwrwpwkwkwtwnwk"
      "wtwtwqwtwuwpwqwqwkwqwqwtwiwnwmwrwowuwnwuwuwuwpwuwlwkwmwjwkwHwswowswowkwswowkwkwswowswowkwkwuwmwkwsws"
      "wswswowswowswowswowhwnwkwswowtwnwuwuwuwpxmwtwmwkwlwiwmwtydwtwtwqwswowswowtwnwswowkwswnwuwnwtwnwswowt"
      "wtwqwtwtwqwtwnwtwtwqwswowswmwmwswowswnwlwkwqwqxuwuxqwrwnyowqwpwiwhwpwuwuwowrwpwuwuwdwkwuwlwlwswo{owk"
      "xuwawtxtwszmwtwiwdwuwtwuwXwJwswmwuwKzmwtwlwtxowrwpwtxrxl{o{o{o{o{o{o{owkwkwkwkwkwkwkwkwkwrwpwtwuwpwq"
      "wqwqwqwqwqwqwqwqwowtwpwuwswqwrwpwrwpwrwpwrwnwmznwswowswowswowswowswowswowswowswowkwkwkwkwkwkwkwkwkws"
      "wowswowswowswowswowswowswcwuwuwowswowswowswowswowtwnwswowtwTymymymymy=wmw^wuwuwmxlxmyowrwowtwnwtwmxm"
      "w bwswIwuwmwuwmwuwtwrxswdwjw]wJwkxuxmwlwlwswlwjwowswmwmwswlwSycyawlwswowrwowswpwswowkwjwrwqwrwpwkwkw"
      "swowkwqwqwsxowswpwjwswpwswowrwnwmxtxnwlwswpwswmwlwlwjwkwHwswowswowkwswowswowkwswowswowkwkwtwnwkwswsw"
      "swswowswowswowswowkwswowkwswnxlwswpwtwmxmwjwlwiwTxuxpwtxowswowtwnwswowkwswnynwtwnwswowtwtwqxuwuxqwtw"
      "nwtwtwqwswowswmwlwuwnwswowkwjwswo{pwrwmwmwswnwjwiwnymwtwnycwkwuwlwl{mwmwiw_wrwdwtwVwrw*wswmwuw?wtwlw"
      "tzqwrwpwtzswkwswowswowswowswowswowswowswnwswpwkwkwkwkwkwkwkwkwswowsxowswowswowswowswowswowrwpwswpxtx"
      "pxtxpxtxpxtxnwmwkwswowswowswowswowswowswowswowtxowkwswowswowswowswowkwkwkwkwswowswowswowswowswowswow"
      "swlwnxtwowswowswowswowswnxmwswnx >wlw\\wkx`wnwrwoznwtwmxl| gybw^wtwozmwsxpzuxfxlx]wnw_wlxjyn{o{nykwnz"
      "mymwkynymwkwewewjwjwrwswqwp{myozn{owizpwrwpwkwkwrwp{owqwqwsxnyowiyowrwozmwlzmwlwswqxsxnwm}qwjxlwGzoz"
      "mymznynwjzowswowkwkwswowkwswswswswnynzmzowjymxlznxlwswqwrwnwm{mwlwiwHxuxpzmxlymynwswmwnwrwozmxuxo{pw"
      "txn{pzmykwmyo}p{owkyuynwnwrwmwly`w_w_wbwjzo{pwqwnwmwhw_z>zY}M|nwuw2wqwqwryrwqwqyowqwqwqwqwqwqwqwqwqw"
      "qwqwqwr{qyo{o{o{o{owkwkwkwkznwsxnymymymymycwuynznznznzmwmwkwuynznznznznznznyuzrymymymymynwkwkwkwjynw"
      "swnymymymymybzmznznznznwlzmw     hwHwlwSwTw <w8z ]x tx Zxjwmx RwWw/wgw pw_ynwky=wCwmwaw\\w_wnw  1wIwl"
      "z 'wiwuwaw  mw    Pw   swlwjw     hw        f| pyWx/wgw rxSw/wCwmwaw\\w_wnw  1w  AwRx  nw    Pw   txk"
      "wlxm";

    // Define a 20x23 font (normal size).
    static const char *const data_font20x23 =
      "                                                9q\\q^r_rnp`qnq`plp7q\\q^q_qmqbq\\q^q_qmqHqmp_q\\q^r_rnp"
      "`qnq7q\\q^q_qmq_q \"r                                                       Mq^q^qnq`pnr`qnq`plp6q^q^p"
      "mp`qmqaq^q^pmp`qmqIpmq]q^q^qnq`pnr`qnq6q^q^pmp`qmq`q \"plp         'q     5qmq               Vq      "
      "               Xq    [plp      3qYq_p^rnpLplp8qYq_qNqYq_q4rmpaqYq_q_rmp%qYq^pGq  Irc|!pKp]raqjq`p   "
      "HtNq_qmq\\plqbp_shpdscq[q^q[p [q]s_r`uau]rbv`tcxbuat LsZucrav_udwcxdw`udqiqeq]q]qjreq]sksgrjqbtcv_tcv"
      "aud{eqiqgqfqgqjsjqlrjrhrirfzfs`q[sZqMqJqCqNsLq]q]q]q]q   .scq]s \\sKt%r  [s^raxdxat_qazgqlqlqctJqIqIq"
      "LqHsOqiqOtaqmq\\uft nufu`sLs`t\\qKv<r\\rLrepirepitgpeq]r^r^r^r^r^r^{gudxdxdxdxdq]q]q]q]wcrjqbt`t`t`t`tL"
      "tlpgqiqeqiqeqiqeqiqgrireq[s_q[q_pnp_pnr`qnq`plp7q[q_s`qmqcq[q_s`qmq]pkpbpmr`q[q_s`pmraqmq8q[q^pnp_qn"
      "q^qaq\\qnq !pnqd{!pJp^tdunucr _y  dvOq_qmq\\plpap_pmpipdudq[p\\p_plplp _q^ubtawcw^rbvavdxcwcw Ou]yerawb"
      "xeyexdwbxeqiqeq]q]qkrdq]sksgrjqdxewbxewcwe{eqiqfqhqfqjsjqkqjqfqiqezfs`q[s[sMpJqCqOtLq]q]q]q]q  q 1tc"
      "q]t ^vaq_w&r  \\u_raxdxcxcuczgqlqlqexMsJqJsMq[p^uPqiqdq]uaqmq]qkqcq!qkqguaqmqNpkp\\p]pKtmp:p]plpKpfpfp"
      "fpcpipdq]r^r^r^r^r^r^{ixexdxdxdxdq]q]q]q]yerjqdxdxdxdxdxPwnpfqiqeqiqeqiqeqiqfqiqdq\\u_p[p^pnpKqnq_r5p"
      "[p^pmp`qmqbp[p^pmp`qmq]tKp[p^pmpLqmq7p[p]pnp_qnq^p`q\\qnq5uauauauaucq`qhq4p]pKr_ueunucr `q  \\rkpOq_qm"
      "q\\plpctbqmqkqerlpdq\\q\\q_qnpnq\\q%q^qkqcqnqapjrdpjr`sbq]rkp^qcrkrerkq Oplr`sirgtbqkrdripeqjsfq]q]ripeq"
      "iqeq]q]qlrcq]sksgskqerjrfqkrdrjrfqkrerjp`q`qiqfqhqeqkskqiqlqdqkq\\qeq]qZq\\qmqNqKqCqOqIq5q]q  q 1q`qZq"
      " _rlqbtaqjp$q  ^qkqatbr^q]rjrewdqhqgqlqlqfrjrOuKqKu8p_rlpOqkqcq]qFpgpcp\"pgpTpkp\\q^p\\p^qLump:p^pjpLpg"
      "pepgpbpjpPt`t`t`t`t`qnq_qnqcripeq]q]q]q]q]q]q]q]qjsfskqerjrfrjrfrjrfrjrfrjrRrjrfqiqeqiqeqiqeqiqeqkqc"
      "vbrlq`q]q_plp Iq]q_qmqNq]q_qmqKtIq]q_qmq ^q]q^plpKq`q mqkqcqkqcqkqcqkqcqkqdq`qhq5q^qLt`ueunudtasbqip"
      "`q`pipcq  [qIq_qmq`{gvcqmqkpdq_q\\q\\q]rZq%q_rkraqZq]qaqnqbq]qXqcqiqeqiq1pSpXq`qfrhqnqbqjqdq]qhqfq]q]q"
      "]qiqeq]q]qmrbq]qnqmqnqgskqeqhqfqjqdqhqfqjqeqYq`qiqfrjreqkskqirnrdrmr]qdq]qZq]qkq)qCqOqIq5q]q  q 1q`q"
      "Zq _qkq_qaq mq  ^qkqaqnqar_q]qhqfrnqnreqhqgqlqlqfqhqPwLqLw9p_q_phqdqkqcq]qGplslpiu#pmtlpUpkp\\q_q_r8u"
      "mp:p^pjpLpgpepgperipcq^qnq`qnq`qnq`qnq`qnq`qnq`qmqcq]q]q]q]q]q]q]q]q]qhqfskqeqhqfqhqfqhqfqhqfqhqdphp"
      "fqirfqiqeqiqeqiqeqiqermrcwcqkq    [q 3qZp Oq nqmqmqeqiqeqiqeqiqeqiqeq_piq4q^pLvatd|evdvcqipasaqkqdq "
      " [qHq_qmq`{hrnpmpcqmqlpcq_q\\pZp]rZq%q_qiqaqZq]qapmqbq^qWqcqiqeqiqdq]qUsSs[qaqdqhqnqbqjqeq\\qgqgq]q^q\\"
      "qiqeq]q]qnraq]qnqmqnqgqnqlqfqfqgqjqeqfqgqjqeqYq`qiqeqjqdqlqmqlqhqnqbqmq]rdq]qZq^pgp=taqns`s`snqatdv_"
      "snqcqnsbq]q]qkqcq]qnsmshqns`saqnsasnqcqnr`tbvaqjqeqiqdqkqkqjrkreqiqdw`q`qZq#tnreqkq^qatauaqnsdqiq`ra"
      "qjqdqiqdpmrcxdqmqmqatbxfyeqiqbqnq`r`q^qfqhrmqmrfqhqgqlqlqgqfqep[pnqnp[p`q`pipbpnqnpNq]taq^qnqnqbqmqb"
      "q\\qIqmpkpmqkqkp$qmpkpmqVqmq\\q`q[pLqjqeump:p^pjpLphpdphpapkpbq^qnq`qnq`qnq`qnq`qnq`qnq`qmqdq\\q]q]q]q]"
      "q]q]q]q]qgqgqnqlqfqfqhqfqhqfqhqfqhqfqfrjrhqiqnqgqiqeqiqeqiqeqiqdqmqbqkrdqmsbt`t`t`t`t`t`tlsfs_t`t`t`"
      "tbq]q]q]q[tbqns`s_s_s_s_s\\q`smpdqjqdqjqdqjqdqjqeqiqdqnscqiq;qlqlqgqgqgqnqmqnqgqjqnqgqgqfq_qjq<{fpjpL"
      "vatd|fxeqkqdqipasaqkqdp  \\yNqGplqeqmp`qmqmqcrLqZq`qnpnq\\q%q_qiqaqZq^rbqmqbubqms^qaqkqdqiqdq]qXuf{fu_"
      "q`qlrnqlqjqlqcqkreq\\qgqgq]q^q\\qiqeq]q]t`q]qnqmqnqgqnqlqfqfqgqkreqfqgqkres[q`qiqeqjqdqlqmqlqhs`s]rcq]"
      "qZq#vbwcvbwcwev`wcwcq]q]qlqbq]vnthwcwcwcwcubwcvaqjqdqkqcqkqkqiqkqdqiqdw`q`qZq7smsfxdqlr^qavdvawdqkq_"
      "raqjqdpgpeqntdxdqmqmqcwdyfyeqiqcqlq`raq^qfqhqlqlqfqhqgqlqlqgqfqfrZqZraqarkraqLq^vbq^wbqmqbq]tKpmpfpk"
      "pjp_plp9plpkplpUs[qaqZpLqjqeump:p^pjpaplp_piqdpiqaplqbq_qlqbqlqbqlqbqlqbqlqbqlqbrmqdq\\q]q]q]q]q]q]q]"
      "q]qgqgqnqlqfqfqhqfqhqfqhqfqhqfqerlrgqjqmqgqiqeqiqeqiqeqiqcsaqjqdqnq`vbvbvbvbvbvbvnuivbwcwcwcwcq]q]q]"
      "q]wcwcwcwcwcwcwOwcqjqdqjqdqjqdqjqeqiqdwdqiq;pkqkpgpepgpmumpgpjrmpgpepfq_qkq;{hrkpLxdxf|fxepipdqipas`"
      "pkpcp  ZqHqGplpdt_pmplpmshsMqZqaplplp]q&q^qiqaq[qat`plqbvcx_q`ucrkr:uc{cucq`qlvlqjqlqcwdq\\qgqgxdvcqj"
      "tfyeq]q]s_q]qmsmqgqmqmqfqfqgwdqfqgwcv_q`qiqdqlqbqmqmqmqfr`s]qbq\\q[q#pjqcrlrdqkpcrlrcqkrdq^rlrcrlrdq]"
      "q]qmqaq]rlrlqirlrdqkqcrlrerlrcr_qjpbq]qjqdqkqcqlslqhqmqbqkq^q_q`qZq_tjpSqmsmpgrlsdqnsaqmqbqkqdq\\rlrd"
      "qlq_raqjqeqgqgrnqnrdqlqcqmqmqcqkqerkq`qaycqlq_rbq^qfqhqlqlqfqhqgqlqlqgqnvnqgrYqYrbqbrirbqLq_rnpmpdwa"
      "qmqcydq^qlqLpmpfpkpkq`plpa{RpltkpB{gpXpLqjqdtmpcqHp]plp_plp`pipjpipipmsfplpjphr_qlqbqlqbqlqbqlqbqlqb"
      "qlqbqlxkq\\xdxdxdxdq]q]q]q_vjqgqmqmqfqfqhqfqhqfqhqfqhqfqdrnrfqkqlqgqiqeqiqeqiqeqiqcsaqjqdqnq`pjqcpjqc"
      "pjqcpjqcpjqcpjqcpjrlrjqkpbqkrdqkrdqkrdqkrdq]q]q]q]qkrdrlrdqkqcqkqcqkqcqkqcqkqOqkqcqjqdqjqdqjqdqjqdqk"
      "qcrlrdqkq:pnwnpgpnwnpgplslpgpkrlpgpkqkpfq^qlq6qaqlpMzfzfzfzgqipdqipbqmp`qmqc|  fqHqHqlpcuasmplpmpiul"
      "qSqZq]p^{+q^qiqaq\\q`ubqlqbpkrdrkrarawcx<tEteq`qlqlqlqjqlqcwdq\\qgqgxdvcqjtfyeq]q]t`q]qmsmqgqmqmqfqfqg"
      "vcqfqgv_t`q`qiqdqlqbqmqmqmqgs_q]qaq\\q[q\"vcqjqeq]qjqdqiqdq^qjqcqjqdq]q]qnq`q]qkqkqiqjqeqiqdqjqeqjqcq^"
      "s^q]qjqdqkqbqmsmqgqmqbqkq_qas_qYsc{Spkqkphqkrcqntcvcqiqeq\\qjqdqmr`tbqjqeqgqgqmqmqdqlqcqmqmqdqiqfqiqa"
      "qaycqlq_qaq^qfqhqlqlqfqhqfqmqmqfqnvnqh}cqc}cqc}cqLq_qmpawbqkqasaq^qkqMpmpfpjsnpaplp`{RplpmqkpB{huatK"
      "qjqbrmpcqJt^r]plpctlpjqktlpmpkpltlpjqhq^qlqbqlqbqlqbqlqbqlqcrlrcqlxkq\\xdxdxdxdq]q]q]q_vjqgqmqmqfqfqh"
      "qfqhqfqhqfqhqfqcteqlqkqgqiqeqiqeqiqeqiqbq`qkrdqmravbvbvbvbvbvbvjqkq]qiqeqiqeqiqeqiqdq]q]q]q^qiqdqjqe"
      "qiqeqiqeqiqeqiqeqiqd{hqkpnqdqjqdqjqdqjqdqjqdqkqcqjqdqkq:pnwnpgpnwnpgplslpgplrkpgpkqkpfq^qlq6qaqmqMzg"
      "|fxdxfqipdqipbqmqaqmqcp  \\wLqK{dt]qmqmqkrmrnrSqZqK{TtKq^qiqaq]r\\rdqkq\\qdqiqaqarkrcsmq<tEtfq_qlqlqlqk"
      "qjqdqjqeq\\qgqgq]q^qgqfqiqeq]q]qnraq]qmsmqgqlqnqfqfqgq^qfqgqkq]raq`qiqdqlqbqnqkqnqgt`q^raq\\q[q#wcqjqe"
      "q]qjqdydq^qjqcqjqdq]q]s_q]qkqkqiqjqeqiqdqjqeqjqcq]uaq]qjqcqmqaqmpmpmqfs`qmq_ras_qYscpjtRpkqkphqkrcqk"
      "reqlrcqiqcr_qjqdqmq_qnqbqjqeqlqlqgqmqmqdqlqcqmqmqdqiqfqiqaqaqiqdqjqaq`q^qfqhqlqlqfqhqfrnqnrfqfqh}cqc"
      "}cqc}cqLq_qmp_q^qkq`qMrlqMpmpfpWplpUqRplplqlp=q&qjq`pmp _plp]qkpnpdqhpeqkpnpiq^qjqdqjqdqjqdqjqdqjqdq"
      "jqdqkqdq\\q]q]q]q]q]q]q]q]qgqgqlqnqfqfqhqfqhqfqhqfqhqfqbrdqmqjqgqiqeqiqeqiqeqiqbq`wcqlrcwcwcwcwcwcwc~"
      "kq]yeyeyeydq]q]q]q^qiqdqjqeqiqeqiqeqiqeqiqeqiqd{hqlpmqdqjqdqjqdqjqdqjqcqmqbqjqcqmq9pkqkpgpepgpmumpgp"
      "mrjpgpepfq]pmq:{epmpLzg|evbveqipdqipbqmqaqmpbq  [qHqK{cpmq^plqmqkqktRqZqFqOtKq^qiqaq^rZqdy^qdqiqaqaq"
      "iq]q:uc{cudq_qlqlqmqjxdqiqfq\\qgqgq]q^qgqfqiqeq]q]qmrbq]qlqlqgqlqnqfqfqgq^qfqgqkr]qaq`qiqcqnqaqnqkqnq"
      "hrnq`q_r`q\\q[q$qjqcqjqeq]qjqdydq^qjqcqjqdq]q]s_q]qkqkqiqjqeqiqdqjqeqjqcqZsbq]qjqcqmqaqnqmqnqfs`qmq`r"
      "^r`qZr9pkqkphqkrcqjqeqkqcqiqet_qjqcqnq`rnqbqjqeqlqlqgqmqmqdqlqcqmqmqdqiqfqiqaqaqiqdqjqbr`q]qhqgrmqmr"
      "fqhqeweqfqgrYqYrdpnqnpdrirdpnqnpNq_qmp_q]qmqcyPrmqMqmpkpmqkvaplpVqRqmpkpmq=q&qjq`pmp(v_plp\\pkpmpdphq"
      "epkpmpjq]xdxdxdxdxdxdwdq\\q]q]q]q]q]q]q]q]qgqgqlqnqfqfqhqfqhqfqhqfqhqfqcteqnqiqgqiqeqiqeqiqeqiqbq`vbq"
      "jqeqjqdqjqdqjqdqjqdqjqdqjqdqjxkq]yeyeyeydq]q]q]q^qiqdqjqeqiqeqiqeqiqeqiqeqiqQqmplqdqjqdqjqdqjqdqjqcq"
      "mqbqjqcqmq9qlqlqgqgqgqnqmqnqgqnqjqgqgqfq]qnq:{eqnpLzg|dt`tdqipcpipbpkp`sbq  Zq plq`pmq_pkqmqkqjrQqZq"
      "Fq'q]rkraq_rYqdy^qdqiqbq`qiq^q6uf{fuaq_qlyjzeqiqeq]qhqfq]q]qhqfqiqeq]q]qlrcq]qlqlqgqkseqhqfq]qhqfqjq"
      "]qaq`qiqcqnq`skshrmraq_q_q[q\\q$qjqcqjqeq]qjqdq\\q^qjqcqjqdq]q]qnq`q]qkqkqiqjqeqiqdqjqeqjqcqXqbq]qjqcq"
      "mqaqnqmqnqgqmq`s_q\\q`qZq7pmpnqmpgqkrcqjqeqkpbqiqeq\\qjqcs_qlqcqjqeqlqlqgqmqmqdqlqcqmqmqdqiqfqiqaq`qkq"
      "drjrdr_q]riqfrnqnreqhqducqhqerZqZrdwdrkrdwOq_qmp_q^w`q`q[sKplslpTplpWqQpmpkqnp<q&qjq`pmp aplp\\pkplpe"
      "phqepkplpjq^zfzfzfzfzfzfxcq]q]q]q]q]q]q]q]q]qhqfqkseqhqfqhqfqhqfqhqfqhqcrnreriqfqiqeqiqeqiqeqiqbq`q]"
      "qjqeqjqdqjqdqjqdqjqdqjqdqjqdqjqdq]q]q]q]q\\q]q]q]q^qiqdqjqeqiqeqiqeqiqeqiqeqiqQqnpkqdqjqdqjqdqjqdqjqb"
      "saqjqbs7qmqmqeqiqeqiqeqiqeqiqeq]qnp7q]rJrnpnresnpnsct_rcqipcqkqcqkqasaq  [rkp&plpcplpnr`qkqmqkrltRqZ"
      "qFq'q\\qkq`q`r_pjr^qcpjrcqkrbq`rkrdpkr3sSsLrlrnrhqhqeqjreripeqjsfq]q]riqfqiqeq]q]qkrdq]qgqgqkserjrfq]"
      "rjrfqjrfpiraq_qkqbt`skshqkqaq`q^q[q\\q$qkrcrlrdqkpcrlrcqipdq^rlrcqjqdq]q]qmqaq]qkqkqiqjqdqkqcrlrerlrc"
      "q^pjqbq]rlrbs_rkrfqmq`s`r\\q`qZq6qlrfrmscrlrepkqbrkqdqkpaqjqcs`rlqcrlrernsnrgrnqnrdqlqcrnqnrdrkqdqkra"
      "q`qkqdqhqer^q\\rkqdwdqhqbqarjrdpYqYpbubpipbuNq_rnpmpbq^qnqnq`q`qZqIpgpRplp7pgp;q&rlr`pmp bplp[pkufpiq"
      "dpkukrlpcqhqfqhqfqhqfqhqfqhqfqhqfqjqcripeq]q]q]q]q]q]q]q]qjsfqkserjrfrjrfrjrfrjrfrjrdrlrfrjreqkqcqkq"
      "cqkqcqkqaq`q]qnplqeqkrdqkrdqkrdqkrdqkrdqkrdqksjpjqkpbqipdqipdqipdqipdq]q]q]q]qkqcqjqdqkqcqkqcqkqcqkq"
      "cqkq^qbqkqcrlrdrlrdrlrdrlrbsarlrbs6qkqcqkqcqkqcqkqcqkqdq\\r7q\\qFp\\p]r^rcqipcvbqkqas`r  \\vOqIqlpcw_pip"
      "mpivnrRpZpEqbqIq^q[ubwdxdw]qcwbwaq_wcvbq]qRpSp[q^q^qhqexcxeyexdq\\xeqiqeq]q]qjrexdqgqgqjrdxeq\\xeqiqfx"
      "`q_war_ririqiqbqazfq[q\\q$xcwcvbwcxdq]wcqjqdq]q]qlqbq]qkqkqiqjqdwcwcwcq^wbu`wbs_rkrgqkq`q`w`q`qZq$yew"
      "dqmq`wdvaqjqbr`qkqcyeyewcqlsdwcxdw`sauczexdq^umteucqhqbq`xLqJsKsMq^vdxdpgpaq`qYqIqkq bqkq?{+yapmp Jp"
      "fpfpipcpfpiucqhqfqhqfqhqfqhqfqhqfqhqfqjxixexdxdxdxdq]q]q]q]yeqjrdxdxdxdxdxdrjrgpnwdwcwcwcwaq`q]qnuex"
      "dxdxdxdxdxdvnwjvbxdxdxdxdq]q]q]q]wcqjqdwcwcwcwcw^qbwbwcwcwcwaq`w`q4uauauauaucq\\r7p[qFp\\p\\p\\pbqipasap"
      "ip`q^y  ctNqIqmqbu_phsgslrSq\\qEqbqIq^qZsawdxcu\\qbt^taq]uataq]q q]qgpiqfqfw`udwcxdqZudqiqeq]q]qirfxdq"
      "gqgqjrbtcqZtcqirfv_q]s_r_rirjrircqazfq[q\\q#tnqcqns`s`snqaucq\\snqcqjqdq]q]qkqcq]qkqkqiqjqbsaqnsasnqcq"
      "]t_t_snqaq^rkrhrkraq`w`q`qZq#smrevbs^t`s`qjqbq`qiqdqnrmqdrmrcubqkrcubqntat^r`sc|fxdq^umtcqaqhqbq^tJq"
      "IqIqLq]tcxLq`qYqHu `u>{+qnrmqapmp Kpepgpiuhpephscqfqhqfqhqfqhqfqhqfqhqfqhqixgudxdxdxdxdq]q]q]q]wcqjr"
      "bt`t`t`t`taphpgplt`s_s_s_s_q`q]qmsctnqctnqctnqctnqctnqctnqbsktgs_uauauaucq]q]q]q[saqjqbs_s_s_s_sNpms"
      "_snqbsnqbsnqbsnqaq`qns_q !p Zp      jp#q\\q6q7q   lq [sjq  Qq -q  OqZq]q  Cq;q HqWq $rIq`qZq _q iqbqK"
      "qFqIq`q     hp$q]u   JqYpmpLp   .p        jp    ]p Xr`q[r !p       Tp\"p\\p6q6q   mq Yx  Qr -r  Ps\\q_s"
      "  Ipkq:q HqWq $qHq`qZq _q iqbqKqFqIq`q     hp$q]t   IqYpmpLq   /q        kq     Fq_q[q #s       Tp\"q"
      "^q6p   1p Vu  Rs    YsJsMy &v<s HqWq &sHtcq]t _q iqbqKqFqIq`q     hp$q   2q2q   /q        kq     Hs_"
      "q]s \"q                (r     Xy %t;r GqWq &rFscq]s ^q iqbqKqFqIq`q         ,q4r   0r        lr     G"
      "r^q                               *q                                                                "
      "                   kr               i";

    // Define a 47x53 font (extra-large size).
    static const char *const data_font47x53 =
      "                                                                                          "
      "                                                                    9])]2_2]T\\8^U^3]  E])]"
      "2`4^U^>])]2_4^U^ 6^T\\5])]1_2]T\\8^U^  K])]2`4^V^3]                                         "
      "                                                                                          "
      "                                                        U]*\\2a4`V\\8^U^5a  F]*\\1\\X\\4^U^=]*\\"
      "2a5^U^ 7aV\\4]*\\1a4`V\\8^U^  J]*\\1\\X\\4^V^3\\                                                 "
      "                                                                                          "
      "                                                S],\\1\\W\\5g8^U^6c  F],\\1\\V\\5^U^<],\\2]W]6^U^"
      " 8h3],\\0\\W\\5g8^U^  I],\\1\\V\\5^V^4\\      ;]                                                 "
      "                                                                                          "
      "                                         :\\-]2\\U\\6\\V`7^U^7]U]  F\\-]2\\T\\6^U^;\\-]3]U]7^U^ 8\\"
      "Va1\\-]1\\U\\6\\V`7^U^  H\\-]2\\T\\6^V^5]      =a                                J]              "
      "                                                                                          "
      "                                            N\\/]2\\S\\7\\T]6^U^7\\S\\  E\\/]2\\R\\7^U^:\\/]3]S]8^U^"
      " 8\\T^/\\/]1\\S\\7\\T]6^U^  G\\/]2\\R\\7^V^6]      =c                                L^           "
      "                                                         *^                            U` "
      "                                        O^             )\\S\\                     !^$^3\\  E]"
      "U\\  K^$^4^ G^$^4]   J^$^3\\   #^$^3\\ 4^            B[                                      "
      "                              &^                            Xe                            "
      "             S^             (\\S\\               )Z      Q^&^3^2]S\\ A\\S\\  K^&^3^ F^&^4_  >]S"
      "\\9^&^3^2]S\\   W^&^3^ 6^        Q]    M[               ?`   ![1^H]?` =]4](\\    %` >b4c  Bb "
      "?`2a    .a   Ib   Pb      Aa <a @b      Fb =b  F^ :] '] Da A].].].].]            <_:]._   "
      " Xh ?c   W^       @`   La   Pa        Sa   Va5^U^ @`   \"f4_ >`0`*^   $^.` <^F]F^F]G`G]    "
      " F\\S\\ ;b        %a2a2a2a2a <bR\\     D`4^(^3`4`U\\8^V^6\\S\\  J^(^3`4^U^@^(^3_4^U^/^/`U\\8^(^3`"
      "4`U\\8^V^  K^(^3`4^V^1^9]+^V^      ?`    O\\  D\\6]M]            We D]1]T] 9[3bJ\\@e<])]2])\\  "
      "  T]0d3_7h9i/_;k5f?n:f7e    3g :_8i3h@h9n?l5iB]H]C].].]J^B].`I`H_J]<g?g1g?g4hAuB]H]G]C]F]K"
      "_K]S^J^F^G^CrBb7]*b'_ D] :] '] Fc A].].].].]            >a:].a   !^T_ Bg   `       Dd2_8n?"
      "m7g3]:rD]P]P]@g <] 8] 8] B] 3e J^K^ If7^U^+b@d   Fb@f5a Ad4e-] :f  Ra0d AaF\\HaF\\HeJ\\?]._0_"
      "0_0_0_2\\U\\0tHh@n?n?n?n?].].].]-h:_J]<g8g8g8g8g BhV]G]H]C]H]C]H]C]H]G^G^B]*d5](]2\\X\\4aW]8^V"
      "^6\\S\\  I](]3]X]5^U^?](]3\\W\\5^U^.^R[9aW]7](]2\\X\\4aW]8^V^  J](]2\\X\\4^V^1]8]+^V^      ?a>w   "
      "P[ 9[/a:aQa7[    Wl      \"h E]1]T]+\\R\\;[4dL]Ag=])]2])\\    U^1f8c8k;j1`;k7h?n;h9g    5i*b:_"
      "8k6kBl=n?l7mD]H]C].].]L_A].`I`H`K]>kAj6kAj9kBuB]H]F]E]E^L_L^R^L^D^I^BrBb7^+b(a D] ;] '] Gd"
      " A].].].].]      ;]     (b:].b   #^Q] Dj  !a       Ff3_8n?m8i4]:rD]P]P]Bk ?_ 9] 9_ C]&[0f "
      "I]K]=]0g7^U^-fC\\S]   IfBf6c B[S]5[S].] <i  R\\W\\1]T] B\\W\\G]H\\W\\G]H[S]K]?]._0_0_0_0_2c1uIkBn"
      "?n?n?n?].].].]-l>`K]>k<k<k<k<k EoF]H]C]H]C]H]C]H]F^I^A],h6]*]2\\V\\6]Wa7^V^6\\S\\  H]*]2\\V]6^U"
      "^>]*]3]W]6^U^._V_;]Wa5]*]2\\V\\6]Wa7^V^  I]*]2\\V\\5^V^2]7]+^V^      @]W\\=v   P[ 9\\1c<cSd:]   "
      "\"o      #_S^ F]1]T],]S];[5^V^N]A_T]=]*]0]*\\    U]1^T^;e8`S_<^R_2`;k8^R]?n<_T_;^S^    6^S_."
      "i>_8m:`R`Cn?n?l9`QaE]H]C].].]M_@].aKaH`K]?`S`Bk8`S`Bk;_R_BuB]H]F]E]D]MaM]P]L]B^K^ArB]1]&])"
      "c D] <] '] G] :].].].].]      ;]     (^6]*^   #]P^ E^P\\   V^       H^T^4_8n?m:`S`6]:rD]P]P"
      "]C`S` Aa :] :a D]&[1^S\\ I^M^=]0^R[7^U^/^R^EZO\\   L^R^ N]U] :],\\0] <j  M\\2]R] >\\H]B\\H]=\\M]>"
      "]._0_0_0_0_0_/uK`R`Cn?n?n?n?].].].]-n@`K]?`S`>`S`>`S`>`S`>`S` H`ScE]H]C]H]C]H]C]H]E^K^@],^"
      "T^5],]1\\V\\6\\U`7^V^6]U\\  F],]2\\T\\6^U^=],]2\\U\\6^U^-e9\\U`4],]1\\V\\6\\U`7^V^  H],]1\\V\\5^V^3]6]+^"
      "V^  B`1`1`1`1`6]W]>u   P[ 9]2e>eUf;^   %q      $^O\\ F]1]T],]S];[5]T]N\\@]P[=]*]0]2ZR\\RZ   $"
      "]2]P]<_W]8]N]<ZL^4a;]+]MZ/]<^P^=^Q^    7\\O]1nAa9]N_<_M]C]NaA].]+_L^E]H]C].].]N_?].aKaHaL]@"
      "^M^C]P_:^M^C]P_=^M\\6]6]H]F^G^D]MaM]P^N^B^K^-^B]1]&]*e D] =] '] H] 9].].].].]      ;]     )"
      "^5])^   %^O]8^3]LZ   U]       I^R^6a9_0]+^M^7]:]H]D]P]P]D^M^ Cc ;] ;c E]&[2^PZ H]M]<]1^-^U"
      "^1]L];[   N]L] Q]S] :\\,\\1] <dU\\  M\\2\\P\\ >\\H\\A\\H\\<\\M\\=]/a2a2a2a2a1_/]V];_M]C].].].].].].].]"
      "-]ObBaL]@^M^@^M^@^M^@^M^@^M^ J^N`D]H]C]H]C]H]C]H]E^K^@]-^Q]5].]1\\T\\7\\S]6^V^5c  E].]2]S\\7^U"
      "^<].]2\\S\\7^U^,a6\\S]2].]1\\T\\7\\S]6^V^  G].]1\\T\\6^V^4]5]+^V^  De6e6e6e6e9\\U\\>u   P[ :_3f@gVf<"
      "_   &r      $]M[ F]1]T],\\R]>d<^T^P]A^OZ=]+].]4]T\\T]   &^3^P^=[S]8[K].]4\\X];],]!]<]N]>^O^  "
      "  8ZM^3`P`Ba9]M^=^J\\C]K_B].],^H\\E]H]C].].]O_>].aKaHaL]A^K^D]N^<^K^D]N^>]JZ6]6]H]E]G]C]MaM]"
      "O^P^@^M^-^A]1]&]+_W_ D] >] '] H] 9]  B].]      ;]     )]4](]   %]N]:c6]   G]       J^P^7a8"
      "_1],^K^;c=]H]D]P]P]E^K^ Ee <] <e F]&[2] =^O^<]1] 0\\H\\<\\   P\\H\\ R\\Q\\+]3\\,\\2] <eU\\  M\\3]P\\ >"
      "\\I]A\\I]<\\N]=]/a2a2a2a2a2a1]U]<^J\\C].].].].].].].]-]K_CaL]A^K^B^K^B^K^B^K^B^K^ K]K^D]H]C]H]"
      "C]H]C]H]D^M^?]-]P]4]0]1\\R\\  Ha  C]0]2]R] E]0]2\\Q\\ 9c 9]0]1\\R\\   !]0]1\\R\\ ?]4]   Di:i:i:i:i"
      ";\\6]G]   P\\ :`5g@gWh>a   (_       J]KZ F]1]T],\\R\\?h>]R]P\\@]1]+].]3^V\\V^.]   T]2]N]5]8ZJ]-]"
      "6]X];]-]!^=]L]?]M]    *]5_J_Ec:]L^>]H[C]I^C].],]F[E]H]C].].]P_=].]X]M]X]HbM]A]I]D]M]<]I]D]"
      "M]?]%]6]H]E]G]C^NaN^N]Q^>^O^-^@]0]'],_U_  &] '] H] 9]  B].]      ;]     )]4](]   %]N]:d7] "
      "  F]       K]N]8c8^1],]I]>i@]H]D]P]P]E]I] Fg =] =g G]&[2] <]O];]1] 1\\F\\=\\   Q\\F\\ S\\Q\\+]3\\."
      "]  IeU\\  M\\3\\N\\ ?\\I\\@\\I\\=]M\\<]0c4c4c4c4c3a1]U]<]H[C].].].].].].].]-]J_DbM]A]I]B]I]B]I]B]I]"
      "B]I] L]J_E]H]C]H]C]H]C]H]C^O^>].]N]    .]        '`X_           I]   FbWa=bWa=bWa=bWa=bWa<"
      "\\6^I^  ?Z2[ :a5gAiXh?c   *^       H] 7]1]T]-]S]Aj>]R]Q]@]1],],\\1^X\\X^,]   T]3]L]6]'].]7]W]"
      ";]-]!]<]L]?]M^    +]6^F^F]W]:]K]?]FZC]H^D].]-]DZE]H]C].].]Q_<].]X]M]X]H]X]M]B]G]E]M^>]G]E]"
      "M^@]%]6]H]E^I^B]O^X]O]M^R^=]O^-^@]0]']-_S_  '] '] H] 9]  B].]      ;]     )]4](]   %]N]:e8"
      "_   H]       L]M]8]W]7^2]-]G]AmB]H]D]P]P]F]G] Hi >] >i  J[3] ;^Q^;]1] 2\\RbT\\Ge   R\\VdR\\ T\\"
      "Q\\+]4\\2a  IfU\\  M\\3\\N\\ ?\\J\\?\\J\\AaM\\ G]W]4]W]4]W]4]W]4]W]4c3^U]=]FZC].].].].].].].]-]H]D]X]"
      "M]B]G]D]G]D]G]D]G]D]G]A[H[B]J`E]H]C]H]C]H]C]H]B]O^>g8]N]             1]T_      3[    9]   "
      "G_O^?_O^?_O^?_O^?_O^=\\5]I^  @\\3[ ;c6gAy?d7`8]L]7^7]L]>^       H] 6]1]T]-]S]B_W[U]>]R]R]?]1"
      "],],]0d*]   T]3]L]6]'].]7\\V];].] ]<]L]@]K]  7Z PZ X]7^D^G]W]:]K]?]/]G]D].]-]/]H]C].].]R_;]"
      ".]X^O^X]H]X^N]B]G]E]L]>]G]E]L]@]%]6]H]D]I]A]O]W]O]L^T^<^Q^-^?]0]'].^O^  Sb7]U`2b4`U]8a8])`"
      "7]T_  M].]%_O_@_2`0`3`/_3c9]     )]4](]   N_6]N]3^7a/c0_ <^  D[U^  Ga  N]L]9]W]6^3]-]G]B`W"
      "]W`C]H]D]P]P]F]G] I_X]X_ ?] ?_X]X_  Nb7]2ZFZ=]Q]:]0] 3[SfU[Ig   R[UfS[ T\\Q\\+]5]2a  IfU\\  M"
      "\\3\\N\\ ?\\K]?\\K]AaN] G]W]4]W]4]W]4]W]4]W]4]W]3]T]=]/].].].].].].].]-]G]E]X^N]B]G]D]G]D]G]D]G"
      "]D]G]B]J]C]KbF]H]C]H]C]H]C]H]B^Q^=j;]P_9b3b3b3b3b3b3bN`Bb3a2a2a2a    V_2_2`1`1`1`1` ;aU]  "
      "  :]U`   S^T]U^A^L^A^L^A^L^A^L^?]5]I]  @^5\\ <e7gAy@f;e:]L]8`8^N^?^       G] 6]1]T]-\\R\\A]U["
      "RZ>]R]R\\>]1],],].`(]   U^3]L]6]'].]8]V];].]!^<]L]@]K]  :] P]#^8^A]I^W^;]K]@].]G^E].].].]H]"
      "C].].]S_:].]W]O]W]H]W]N]C]E]F]L]?]E]F]L]@]%]6]H]D]J^A]O]W]O]L^U^:^S^-^>]0^(]/^M^  Wh:]Wd6f"
      "8dW]:e>h2dW]?]Vd<].].]O_>].]WdScK]Vd8f;]Wd7dW]?]Wa6h>h6]L]B]I]A]P`P]K^L^B^K^@l4]4](]   PdU"
      "]A]N]2^8e5g;]Vd?^J^8]6]L] E]V`>pA]S]S]:e6kDo>]L]:^W^6^4].]E]D_U]U_D]H]D]P]P]G]E] K_W]W_ @]"
      " @_W]W_  Qf9]3\\H\\>^S^:]0_ 6[ThT[K]Q\\   S[T\\R]S[ U]S]+]6],] ?]L]@fU\\  M\\3\\N\\ ?\\K\\>\\K\\;]O\\ G"
      "^W^6^W^6^W^6^W^6^W^5]W]4^T]>].].].].].].].].]-]G^F]W]N]C]E]F]E]F]E]F]E]F]E]D_L_E]K]W]F]H]C"
      "]H]C]H]C]H]A^S^<k<]Ra<h9h9h9h9h9h9hTeFf7e6e6e6e;].].].]\"^;]Vd8f7f7f7f7f/^6eX]@]L]?]L]?]L]?"
      "]L]B^K^?]Wd>^K^  O]S]S]B]I]B]I]B]I]B]I]@]5^K^  @]4[ ;f8gAyAg<h<]L]8`7]N]>]       F] 6]1]T]"
      "-\\R\\B]T[6]R]S]>^2]-]*\\.`(]   U]2]L]6]'].]9]U];].]!];]L]@]K]  =` P`'^7]?\\I]U];]K]@].]F]E].]"
      ".].]H]C].].]T_9].]W]O]W]H]W^O]C]E]F]L]?]E]F]L]@]%]6]H]C]K]@^P]W]P^K^V^9]S]-^=]/](]0^K^  Xi"
      ";]Xf9h9fX]<h?h3fX]?]Xg=].].]P_=].]XfVfL]Xg:h<]Xf9fX]?]Xb7i>h6]L]A]K]@^Q`Q^J^N^@]K]?l4]4](]"
      "   QfW^A]O^1]6f9h;]Xg@_K]7]6]L]=]G]C^Wc@pA]S]S]<h9mDo>]L]:]U]5^5].]E]E^S]S^E]H]D]P]P]G]E]@"
      "Z+]V]V^-Z4]5ZKZ:]V]V^  Sh9]4^J^>]S]9]._ 8[U_Q[T[L]P\\   S[T\\Q]T[ T]U]*]7]*] @]L]@fU\\  M\\3\\N"
      "\\ ?\\L]>\\L]:]Q]:]1]U]6]U]6]U]6]U]6]U]6^W^5]S]>].].].].].].].].]-]F]F]W^O]C]E]F]E]F]E]F]E]F]"
      "E]C_N_D]L^W]F]H]C]H]C]H]C]H]@]S];]P_=]S^8i:i:i:i:i:i:iVgIh9h9h9h9h<].].].]'d<]Xg:h9h9h9h9h"
      "0^8k?]L]?]L]?]L]?]L]A]K]>]Xf>]K]  O]R]R]D]G]D]VZOZV]D]KZV]D]G]A]4]K]  @]3[ <g7fAyBi>j=]L]8"
      "`7]N]?]       F^ 6]1]T]5uI]T[6]R]S\\<^3]-]*]1d*]   U]3]J]7]'].]9\\T];].\\Ua-^;]L]@]K^?].] Uc "
      "Pc+_8]>]J]U];]K]@].]F]E].].].]H]C].].]U_8].]W^Q^W]H]V]O]C]E]F]L]?]E]F]L]@^&]6]H]C]K]?]Q^V]"
      "Q]I^X^8^U^.^<]/](]1^I^  ]R_<aT_;_R\\:^Tb=_S^@h4_Ub?bT^=].].]Q_<].aT_X]T^LbT^;_T_=aT_;^Tb?aT"
      "Z8_R]>h6]L]A]K]?]Q`Q]H^P^?]K]?l4]4](]   R^U^W]@]O]0^7g;_S];bT^@`L]8_7]L]>]E]E^W]V]@pA]S]S]"
      "=_T_<oDo?]K^;]U]5_6].\\D]E]R]R]E]H]D]P]P]G]E]A\\+[U]U\\,\\6]6\\L\\;[U]U\\  S_W[V\\9]3^V`V^=^U^9]/a"
      " :[T]G[M\\O\\1ZQZ  M[S\\P\\S[ Ud)]8](\\ @]L]@fU\\  M\\3\\N\\9ZQZ0\\L\\=\\L\\8\\Q\\9]1]U]6]U]6]U]6]U]6]U]6"
      "]U]5]S]>].].].].].].].].]-]F]F]V]O]C]E]F]E]F]E]F]E]F]E]B_P_C]L]V^G]H]C]H]C]H]C]H]@^U^;]N^>"
      "]T]6]R_;]R_;]R_;]R_;]R_;]R_;]R_X_T^K_R\\:_S^;_S^;_S^;_S^=].].].]*h=bT^;_T_;_T_;_T_;_T_;_T_1"
      "^9_T`>]L]?]L]?]L]?]L]A]K]>aT_?]K]  P]Q]R]E]F]E]V\\Q\\W]E]K\\W]E]F]A]4^L]  A^@ZN\\ =i8e@yCk?^R^"
      "=]L]9b8]O^?]       Im B]1]T]5uI]T[6]S^T]<^3]-]*]3^X\\X^,]   V^3]J]7](^/]9]T];e7]We/]9]N]?]K"
      "^?].] Wd Nd._8]O`U\\T\\K]S]<]L^A]-]F^F].]/]-]H]C].].]V_7].]V]Q]V]H]V^P]D]C]G]L]@]C]G]L]?^']6"
      "]H]C^M^?]Q]U]Q]Ic6^W^._<]/^)]2^G^ !ZM^=`Q^=^NZ;^Q`>^P^=].^Q`?`Q^>].].]R_;].`R^X\\R^M`Q^=^P^"
      ">`Q^=^Q`?`1]MZ;].]L]A^M^?]Q`Q]G^R^>^M^1^4]4](]  D]P^A]R^X]@]P^/]9^Vb=^NZ;`Q^AaN^8_7]L]>]E]"
      "F^V]U]>]P]>]S]S]>^P^>`T`7]6]J]<]S]5^6]/]C]G]Q]Q]F]H]D]P]P]H]C]C^&]TZ,^7]7^N^6]TZ H]/^U[TZ9"
      "]2n;]U]8]0d <[U]F[M\\P]2[R[  M[S\\P\\S[ Tb(]9]'\\ @]L]@fU\\  M\\3]P]9[R[1\\M\\<\\M\\7\\R\\8]2]S]8]S]8]"
      "S]8]S]8]S]7]U]6]R]?]-].].].].].].].]-]F]F]V^P]D]C]H]C]H]C]H]C]H]C]B_R_C]L]T]G]H]C]H]C]H]C]"
      "H]?^W^:]M]>]U^6ZM^<ZM^<ZM^<ZM^<ZM^<ZM^<ZMbP]M^NZ;^P^=^P^=^P^=^P^>].].].]+i=`Q^=^P^=^P^=^P^"
      "=^P^=^P^2^:^P^>]L]?]L]?]L]?]L]A^M^>`Q^@^M^  P]Q]Q]F]E]F]W^S^W]F]L^W]F]E]B]3]M^  B^B^O[ =k8"
      "d?xClA^P^>]L]9]X]8^P]>\\       Hl A] 9uI]T[5]T]T]:^ =]*]5^V\\V^.]   V]2]J]7](]/^:]S];h:]Xg0]"
      "9^P^?]K^?].]!e Je2_7\\PdW\\S\\L]S]<]M^@]-]E]F].]/]-]H]C].].]X_5].]V]Q]V]H]U^Q]D]C]G]L]@]C]G]M"
      "^?`)]6]H]B]M]>]Q]U]Q]Hb5c-^;].])]   B]=_O]=].]O_>]N^>].]O_?_O]>].].]S_:]._P`P]M_O]=]N]>_O]"
      "=]O_?_1]-].]L]@]M]>]RbR]G^R^=]M]1^3]4](]  FaSaD^Qa?]R_.]9]R`>]._O]>^N]8`7]L]>]E]G^U]U^?]P]"
      ">]S]S]>]N]>^P^7]6]J]<]S]4^7]/]C]G]Q]Q]F]H]D]P]P]H]C]D_&]&_8]8_N_7] B]/]T[3]1l:^W^8]1]W` >\\"
      "U\\E\\N\\P]3\\S\\  N\\S\\P\\S\\ S_']:]&\\ @]L]@fU\\  M\\2\\P\\8\\S\\2\\N]<\\N]7\\S]8]2]S]8]S]8]S]8]S]8]S]8]S]"
      "7]R]?]-].].].].].].].]-]E]G]U^Q]D]C]H]C]H]C]H]C]H]C]A_T_B]M]S]G]H]C]H]C]H]C]H]>c9]M^?]U]']"
      ".].].].].].`O^N].]N^>]N^>]N^>]N^?].].].],_R^>_O]=]N]=]N]=]N]=]N]=]N]2^:]O_?]L]?]L]?]L]?]L]"
      "@]M]=_O]?]M]  O\\P]Q]F\\D]F\\U^U^V]F\\L^V]F\\D]B]3]M]  RuJ`O[ >m9c>wCmA]N]>]L]9]X]7]P]?]       "
      "Im A] 2\\R\\A]T[5^V^T\\:` ?](\\6]T\\T]/]   V]2]J]7])^1_9]S];i;bS^2^8^S_>]K^?].]$e@u@e6_7]QfX\\S\\"
      "M^S^=]N^?]-]E]F].]/]-]H]C].].c4].]U]S]U]H]T]Q]D]C]G]M^@]C]G]M]=c-]6]H]B]M]>^R]U]R^G`4c.^:]"
      ".])]   B]=^M]?^/]M^?]L]>]/]M^?^N^?].].]T_9].^O_O^N^N^?]M^?^M]?]M^?^0]-].]L]@]M]>^S]X]S^F^T"
      "^<^O^2_3]4](]  GcUcE]Pa?]Vb-]:]O_?].^N^>]O^8a8]L]?]C]H]T]T]?]P]>]S]S]?]L]@^N^8]6]J]=^S^4^8"
      "]/]C]H^Q]Q^G]H]D]P]P]H]C]E_%]%_9]9_L_8] B]0^T[3]0_T_>cWc=]1]U_ ?[U\\C[N]R^4]T]  N[R\\Q]R[ 'u"
      "G]&] @]L]?eU\\  M\\2]R]8]T]3\\N\\;\\N\\7]S\\7]3^S^:^S^:^S^:^S^:^S^9]S]8^R]?]-].].].].].].].]-]E]G"
      "]T]Q]D]C]H]C]H]C]H]C]H]C]@_V_A]N]R]G]H]C]H]C]H]C]H]>c9]L]?]U]'].].].].].]._M]O^/]L]?]L]?]L"
      "]?]L]?].].].]-^O]>^N^?]M^?]M^?]M^?]M^?]M^ I]O`?]L]?]L]?]L]?]L]@^O^=^M]@^O^  P]P]P\\G]C\\G]T^"
      "W^T\\G]M^T\\G]C\\B]3^O^  RuJ[X]P[ >o=\\XaX]BwDoC]L\\>]L]:^X^8]P]?]       E] 5] 3]S]A^U[4dT];b @"
      "](]6ZR\\RZ.]   V]2]J]7]*^7d8]R];]R_<aQ^3]5f<^M_?].]'e=u=e:_6\\Q^S`S]N]Q]=l>]-]E]Fm>k=]-rC].]"
      ".b3].]U]S]U]H]T^R]D]C]G]M]?]C]G]N^<f1]6]H]B^O^=]S^U^S]F_2a.^9].])]   A]>^M]?].]M^?]L]>]/]M"
      "^?^M]?].].]U_8].^N^N]N^M]?]L]?^M]?]M^?^0]-].]L]@^O^=]S]X]S]D^V^:]O]2_2]4](]  H\\U^W]U\\E]Pa?"
      "]Vb-];]M^?].^M]>^P]7a8]L]?]C]H]T]T]?]P]>]S]S]?]L]@]L]8]6p=]Q]3^9]/]C]H]P]P]G]H]C]Q]Q]G]ViV"
      "]F_$]$_:]:_J_9] B]0]S[3]0]P]>o=]2]S_ @[U\\C[M]T_5^U^;u O[R\\R]Q[ 'uH]/ZQ] ?]L]?eU\\  M\\1]T]7^"
      "U^4\\O]O]I\\O]T`MZQ]S]O]E]3]Q]:]Q]:]Q]:]Q]:]Q]:^S^9]QmO]-m>m>m>m>].].].]1hL]G]T^R]D]C]H]C]H]"
      "C]H]C]H]C]?_X_@]O]Q]G]H]C]H]C]H]C]H]=a8]L]?]U]&].].].].].].^M]O].]L]?]L]?]L]?]L]?].].].].^"
      "M]?^M]?]L]?]L]?]L]?]L]?]L] I]Pa?]L]?]L]?]L]?]L]?]O]<^M]?]O]  O]P]P\\G]C\\G]ScS\\G]N^S\\G]P]P\\B"