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
 #                or  CeCILL v2.0
 #                    The CeCILL license is compatible with the GNU GPL.
 #                    ( http://www.cecill.info/licences/Licence_CeCILL_V2-en.html )
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
#define cimg_version 171

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

// Disable silly warnings on some Microsoft VC++ compilers.
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4127)
#pragma warning(disable:4244)
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#pragma warning(disable:4512)
#pragma warning(disable:4571)
#pragma warning(disable:4640)
#pragma warning(disable:4706)
#pragma warning(disable:4710)
#pragma warning(disable:4800)
#pragma warning(disable:4804)
#pragma warning(disable:4820)
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_DEPRECATE 1
#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_NONSTDC_NO_DEPRECATE 1
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
#if !defined(cimg_use_cpp11) && __cplusplus>201100
#define cimg_use_cpp11 1
#endif
#if defined(cimg_use_cpp11) && cimg_use_cpp11!=0
#include <initializer_list>
#include <utility>
#endif

// Define own types 'cimg_long/ulong' and 'cimg_int64/uint64' to ensure portability.
// ( constrained to 'sizeof(cimg_ulong/cimg_long) = sizeof(void*)' and 'sizeof(cimg_int64/cimg_uint64)=8' ).
#if cimg_OS==2
#define cimg_uint64 unsigned __int64
#define cimg_int64 __int64
#define cimg_ulong UINT_PTR
#define cimg_long INT_PTR
#else
#if UINTPTR_MAX==0xffffffff
#define cimg_uint64 unsigned long long
#define cimg_int64 long long
#else
#define cimg_uint64 unsigned long
#define cimg_int64 long
#endif
#define cimg_ulong unsigned long
#define cimg_long long
#endif

// Configure the 'abort' signal handler (does nothing by default).
// A typical signal handler can be defined in your own source like this:
// Without OpenMP support: #define cimg_test_abort() if (is_abort) throw CImgAbortException("")
//
// or
//
// With OpenMP support: #define cimg_test_abort() if (!omp_get_thread_num() && is_abort) throw CImgAbortException("")
//
// where 'is_abort' is a boolean variable.
#ifndef cimg_test_abort
#define cimg_test_abort()
#endif
#ifndef cimg_test_abort2
#define cimg_test_abort2()
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
#ifdef None
#undef None
#define _cimg_redefine_None
#endif
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
       - \c 2: Display library messages on a dialog window (default behavior).
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
       - \c 0: Never parallelize (quiet mode).
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
        } catch (CImgException &e) {                                // You succeeded: something went wrong!
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
      static const char* format() { return "%lu"; }
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
      static cimg_int64 cut(const double val) { return val<(double)min()?min():val>(double)max()?max():(cimg_int64)val; }
      static const char* format() { return "%ld"; }
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
      static bool is_nan(const double val) {
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
      static double cut(const double val) { return val<min()?min():val>max()?max():val; }
      static const char* format() { return "%.16g"; }
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
      static bool is_nan(const float val) {
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
      static float cut(const double val) { return val<(double)min()?min():val>(double)max()?max():(float)val; }
      static const char* format() { return "%.16g"; }
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
      static long double cut(const long double val) { return val<min()?min():val>max()?max():val; }
      static const char* format() { return "%.16g"; }
      static double format(const long double val) { return (double)val; }
    };

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
"                          .wjwlwmyuw>wjwkwbwjwkwRxuwmwjwkwmyuwJwjwlx`w      Fw                         mwlwlwuwnwuynwuwmyTwlwkwuwmwuwnwlwkwuwmwuw_wuxl"
"wlwkwuwnwuynwuwTwlwlwtwnwtwnw my     Qw   +wlw   b{ \\w  Wx`xTw_w[wbxawSwkw  nynwky<x1w `y    ,w  Xwuw   CxlwiwlwmyuwbwuwUwiwlwbwiwrwqw^wuwmxuwnwiwlwmy"
"uwJwiwlw^wnwEymymymymy1w^wkxnxtxnw<| gybwkwuwjwtwowmxswnxnwkxlxkw:wlymxlymykwn{myo{nymy2ykwqwqwm{myozn{o{mzpwrwpwkwkwswowkwqwqxswnyozlyozmzp}pwrwqwqwq"
"wswswsxsxqwqwp}qwlwiwjybw`w[wcw_wkwkwkwkw mw\"wlwiw=wtw`xIw awuwlwm{o{mylwn|pwtwtwoy`w_w_wbwiwkxcwqwpwkznwuwjzpyGzqymyaxlylw_zWxkxaxrwqxrwqyswowkwkwkwk"
"wkwkwk}qyo{o{o{o{owkwkwkwkznxswnymymymymyayuwqwrwpwrwpwrwpwrwqwqwpwkwtwlwkwlwuwnwuynwuwmyTwkwlwuwmwuwnwkwlwuwmwuwkxlwuxmwkwlwuwnwuynwuwTwkwlwuwmwuwlwm"
"wkwtwUwuwuwowswowswowswowsw;wqwtw_ymzp~py>w bwswcwkwuwjwuwozpwtwuwnwtwowkwjwmwuwuwkwIxmxuxowuwmwswowswmxnwjwhwowswowsw0wmwowswuwnwrwowswpwswowkwjwrwqw"
"rwpwkwkwtwnwkxsxqxswowswpwswnwswpwswowrwnwmwrwqwqwqwswswrwswowswjwpwlxjwkxuxLw[wcw_wSwkw mw\"wlwiw=wtwmxlwFw cwswnwuwnwkwjwswo{pwrwpwtwtwpwswby`w`yUwlw"
"twpwqwpwswowlw\\wrwrxuwHwrwfwuwjwlwlwTyuwVwlwtwawswowswowswcwuwmwuwmwuwmwuwmwuwlwkwuwnwswpwkwkwkwkwkwkwkwkwswoxswowswowswowswowswowswowrwpwswpwrwpwrwpw"
"rwpwrwpwswoznwtw  Ww (wGwtwtwqwqwqwuwuwuwqwswuwqwqw=wqxtw`{nzp~q{ozowrwnxmwtwow bzawkwuwl}rwuwnwtwuwnwtwowkwjwlyjwIwlwswmwiwkwnwuwnwkwhwnwswowswowkwew"
"ewixnwsytwswuwnwrwpwkwrwpwkwkwkwrwpwkwkwuwmwkxsxqwuwtwpwqwqwswowqwqwswowiwmwrwpwswowtwtwpwuwmwuwjwowkwjwlxsxXynzmymznyozlzoznwkwkwtwnwkzuyrzmynzmzowux"
"myozmwswpwrwowtwtwrwrwpwrwp{mwlwiwHyuwpwtwkwmxlynzoxswmwmwswnwswowtxq|owtwtwpym{p{owswnwuwmwlwkwqwqxuwuxqwrwpwtwtwqwqwowlwuwuwkwmwlwtwowuwuwdwjznwl{nw"
"uwnwkx_wtxtwswtwlwtwWwuytwgyjwmwjwawswoyuwVwlwtwnwtwmwtwnwtwmwuwmwlwuwmwuwmwuwmwuwmwuwmwuwmxuwowkwkwkwkwkwkwkwkwkwrwpwuwtwpwqwqwqwqwqwqwqwqwqwowtwpwsw"
"uwqwrwpwrwpwrwpwrwowuwnwswowuwlymymymymymymyuyqymymymymynwkwkwkwjynzmymymymymykwmzowswowswowswowswpwrwozowrwW}q}qwtwtwqwtwtwqwtwtwA}rwuw_{p~r~r}pwtwow"
"rwnxmwtwow aw_w]wtwpwuwmxuwmybwjwlyjwIwlwswmwiwnynwtwnznzkwmynwswTyp}pylwmwtwtwtwswuwn{owkwrwp{o{owk|pwkwkxlwkwuwuwuwqwuwtwpwqwqwswowqwqwswoykwmwrwpws"
"wowuwuwuwowkwjwnwkwjwDwowswowkwswowswowkwswowswowkwkwuwmwkwswswswswowswowswowswoxlwswowkwswpwrwowtwtwqwtwowrwlwoxkwhxVxuxpwtypwuwjwnwtwnwkwswowtxnxmws"
"wowqwqwtwuxqwtwnwtwtwqwswowswmwm{nwuwlxnwkwqwqwtwtwqwrwpwtwtwqwuyuwpwiwhwnwmwrwnwbwkwuwlwlwswoxuxowlwtw`wuwrwszmwtwo}dwuwtwuw[}qymx`wswoyuwow_ylxlwtwo"
"yuwoyuwoyuwmwlwuwmwuwmwuwmwuwmwuwmwuwmwt{swk{o{o{o{owkwkwkwlztwpwuwtwpwqwqwqwqwqwqwqwqwqwnxowtwtwqwrwpwrwpwrwpwrwnwmwswowuwiwkwkwkwkwkwkwswswkwswowswo"
"wswowswowkwkwkwkwswowswowswowswowswowswowswcwtxowswowswowswowswpwrwowswpwrwWwtwtwqwqwqwuwuwuwqwuwswqwqw>wowuw`}q~q|q}qwrwpwrwowtwnwtwo~ izaw]wtwoykwux"
"qwtwswfwjwmwuwuwn}eyaxlwswmwjwjwpwswjwowswmwmwswnzWy]ypwlwtwtwuwswswowrwpwkwrwpwkwkwsyqwrwpwkwkwuwmwkwuwuwuwqwtwuwpwqwqznwqwqzkynwmwrwowuwnwuwuwuwowkw"
"jwnwkxkwGzowswowkwswo{owkwswowswowkwkxlwkwswswswswowswowswowswowjxmwkwswowtwnwuwuwuwpxmwtwlwlwlwiwlytwewtwtwqwswowtxoznwswnxmwswnwuwmwuwnwswowtwtwqwtw"
"twqwtwnwtwtwqwswowswmwmwswowswmwmwkwqwqwtwtwqwrwowuwuwpwuyuwq~own~own~owbwkwuwmznwswmwbwswawuwrwgwtwhwdwuytwXwJwswnxuw=wtwmwswowtxowswqxmwswowswowswow"
"swowswowswnwtwowkwkwkwkwkwkwkwkwkwrwpwtwuwpwqwqwqwqwqwqwqwqwqwnxowtwtwqwrwpwrwpwrwpwrwnwmwswowtwmznznznznznzn~swk{o{o{o{owkwkwkwkwswowswowswowswowswow"
"swowswo}qwuwuwowswowswowswowswowtwnwswowtwUwuwuwowswowswowswowsw@}qx`}q~pzo{pwrwpwrwowtwnwtwow aw_w_}owuwmwuwtwrwswuwewjwkwiwJwkwswmwkwiwp|kwowswmwmws"
"wkwWym}mypwlwszr{owrwpwkwrwpwkwkwqwqwrwpwkwkwtwnwkwtwtwqwtwuwpwqwqwkwqwqwtwiwnwmwrwowuwnwuwuwuwpwuwlwkwmwjwkwHwswowswowkwswowkwkwswowswowkwkwuwmwkwsws"
"wswswowswowswowswowhwnwkwswowtwnwuwuwuwpxmwtwmwkwlwiwmwtydwtwtwqwswowswowtwnwswowkwswnwuwnwtwnwswowtwtwqwtwtwqwtwnwtwtwqwswowswmwmwswowswnwlwkwqwqxuwu"
"xqwrwnyowqwpwiwhwpwuwuwowrwpwuwuwdwkwuwlwlwswo{owkxuwawtxtwszmwtwiwdwuwtwuwXwJwswmwuwKzmwtwlwtxowrwpwtxrxl{o{o{o{o{o{o{owkwkwkwkwkwkwkwkwkwrwpwtwuwpwq"
"wqwqwqwqwqwqwqwqwowtwpwuwswqwrwpwrwpwrwpwrwnwmznwswowswowswowswowswowswowswowswowkwkwkwkwkwkwkwkwkwswowswowswowswowswowswowswcwuwuwowswowswowswowswowt"
"wnwswowtwTymymymymy=wmw^wuwuwmxlxmyowrwowtwnwtwmxmw bwswIwuwmwuwmwuwtwrxswdwjw]wJwkxuxmwlwlwswlwjwowswmwmwswlwSycyawlwswowrwowswpwswowkwjwrwqwrwpwkwkw"
"swowkwqwqwsxowswpwjwswpwswowrwnwmxtxnwlwswpwswmwlwlwjwkwHwswowswowkwswowswowkwswowswowkwkwtwnwkwswswswswowswowswowswowkwswowkwswnxlwswpwtwmxmwjwlwiwTx"
"uxpwtxowswowtwnwswowkwswnynwtwnwswowtwtwqxuwuxqwtwnwtwtwqwswowswmwlwuwnwswowkwjwswo{pwrwmwmwswnwjwiwnymwtwnycwkwuwlwl{mwmwiw_wrwdwtwVwrw*wswmwuw?wtwlw"
"tzqwrwpwtzswkwswowswowswowswowswowswowswnwswpwkwkwkwkwkwkwkwkwswowsxowswowswowswowswowswowrwpwswpxtxpxtxpxtxpxtxnwmwkwswowswowswowswowswowswowswowtxow"
"kwswowswowswowswowkwkwkwkwswowswowswowswowswowswowswlwnxtwowswowswowswowswnxmwswnx >wlw\\wkx`wnwrwoznwtwmxl| gybw^wtwozmwsxpzuxfxlx]wnw_wlxjyn{o{nykwnz"
"mymwkynymwkwewewjwjwrwswqwp{myozn{owizpwrwpwkwkwrwp{owqwqwsxnyowiyowrwozmwlzmwlwswqxsxnwm}qwjxlwGzozmymznynwjzowswowkwkwswowkwswswswswnynzmzowjymxlznx"
"lwswqwrwnwm{mwlwiwHxuxpzmxlymynwswmwnwrwozmxuxo{pwtxn{pzmykwmyo}p{owkyuynwnwrwmwly`w_w_wbwjzo{pwqwnwmwhw_z>zY}M|nwuw2wqwqwryrwqwqyowqwqwqwqwqwqwqwqwqw"
"qwqwqwr{qyo{o{o{o{owkwkwkwkznwsxnymymymymycwuynznznznzmwmwkwuynznznznznznznyuzrymymymymynwkwkwkwjynwswnymymymymybzmznznznznwlzmw     hwHwlwSwTw <w8z ]"
"x tx Zxjwmx RwWw/wgw pw_ynwky=wCwmwaw\\w_wnw  1wIwlz 'wiwuwaw  mw    Pw   swlwjw     hw        f| pyWx/wgw rxSw/wCwmwaw\\w_wnw  1w  AwRx  nw    Pw   txk"
"wlxm";

    // Define a 20x23 font (normal size).
    static const char *const data_font20x23 =
"                                                9q\\q^r_rnp`qnq`plp7q\\q^q_qmqbq\\q^q_qmqHqmp_q\\q^r_rnp`qnq7q\\q^q_qmq_q \"r                               "
"                        Mq^q^qnq`pnr`qnq`plp6q^q^pmp`qmqaq^q^pmp`qmqIpmq]q^q^qnq`pnr`qnq6q^q^pmp`qmq`q \"plp         'q     5qmq               Vq      "
"               Xq    [plp      3qYq_p^rnpLplp8qYq_qNqYq_q4rmpaqYq_q_rmp%qYq^pGq  Irc|!pKp]raqjq`p   HtNq_qmq\\plqbp_shpdscq[q^q[p [q]s_r`uau]rbv`tcxbua"
"t LsZucrav_udwcxdw`udqiqeq]q]qjreq]sksgrjqbtcv_tcvaud{eqiqgqfqgqjsjqlrjrhrirfzfs`q[sZqMqJqCqNsLq]q]q]q]q   .scq]s \\sKt%r  [s^raxdxat_qazgqlqlqctJqIqIq"
"LqHsOqiqOtaqmq\\uft nufu`sLs`t\\qKv<r\\rLrepirepitgpeq]r^r^r^r^r^r^{gudxdxdxdxdq]q]q]q]wcrjqbt`t`t`t`tLtlpgqiqeqiqeqiqeqiqgrireq[s_q[q_pnp_pnr`qnq`plp7q["
"q_s`qmqcq[q_s`qmq]pkpbpmr`q[q_s`pmraqmq8q[q^pnp_qnq^qaq\\qnq !pnqd{!pJp^tdunucr _y  dvOq_qmq\\plpap_pmpipdudq[p\\p_plplp _q^ubtawcw^rbvavdxcwcw Ou]yerawb"
"xeyexdwbxeqiqeq]q]qkrdq]sksgrjqdxewbxewcwe{eqiqfqhqfqjsjqkqjqfqiqezfs`q[s[sMpJqCqOtLq]q]q]q]q  q 1tcq]t ^vaq_w&r  \\u_raxdxcxcuczgqlqlqexMsJqJsMq[p^uPq"
"iqdq]uaqmq]qkqcq!qkqguaqmqNpkp\\p]pKtmp:p]plpKpfpfpfpcpipdq]r^r^r^r^r^r^{ixexdxdxdxdq]q]q]q]yerjqdxdxdxdxdxPwnpfqiqeqiqeqiqeqiqfqiqdq\\u_p[p^pnpKqnq_r5p"
"[p^pmp`qmqbp[p^pmp`qmq]tKp[p^pmpLqmq7p[p]pnp_qnq^p`q\\qnq5uauauauaucq`qhq4p]pKr_ueunucr `q  \\rkpOq_qmq\\plpctbqmqkqerlpdq\\q\\q_qnpnq\\q%q^qkqcqnqapjrdpjr`"
"sbq]rkp^qcrkrerkq Oplr`sirgtbqkrdripeqjsfq]q]ripeqiqeq]q]qlrcq]sksgskqerjrfqkrdrjrfqkrerjp`q`qiqfqhqeqkskqiqlqdqkq\\qeq]qZq\\qmqNqKqCqOqIq5q]q  q 1q`qZq"
" _rlqbtaqjp$q  ^qkqatbr^q]rjrewdqhqgqlqlqfrjrOuKqKu8p_rlpOqkqcq]qFpgpcp\"pgpTpkp\\q^p\\p^qLump:p^pjpLpgpepgpbpjpPt`t`t`t`t`qnq_qnqcripeq]q]q]q]q]q]q]q]qj"
"sfskqerjrfrjrfrjrfrjrfrjrRrjrfqiqeqiqeqiqeqiqeqkqcvbrlq`q]q_plp Iq]q_qmqNq]q_qmqKtIq]q_qmq ^q]q^plpKq`q mqkqcqkqcqkqcqkqcqkqdq`qhq5q^qLt`ueunudtasbqip"
"`q`pipcq  [qIq_qmq`{gvcqmqkpdq_q\\q\\q]rZq%q_rkraqZq]qaqnqbq]qXqcqiqeqiq1pSpXq`qfrhqnqbqjqdq]qhqfq]q]q]qiqeq]q]qmrbq]qnqmqnqgskqeqhqfqjqdqhqfqjqeqYq`qiq"
"frjreqkskqirnrdrmr]qdq]qZq]qkq)qCqOqIq5q]q  q 1q`qZq _qkq_qaq mq  ^qkqaqnqar_q]qhqfrnqnreqhqgqlqlqfqhqPwLqLw9p_q_phqdqkqcq]qGplslpiu#pmtlpUpkp\\q_q_r8u"
"mp:p^pjpLpgpepgperipcq^qnq`qnq`qnq`qnq`qnq`qnq`qmqcq]q]q]q]q]q]q]q]q]qhqfskqeqhqfqhqfqhqfqhqfqhqdphpfqirfqiqeqiqeqiqeqiqermrcwcqkq    [q 3qZp Oq nqmqm"
"qeqiqeqiqeqiqeqiqeq_piq4q^pLvatd|evdvcqipasaqkqdq  [qHq_qmq`{hrnpmpcqmqlpcq_q\\pZp]rZq%q_qiqaqZq]qapmqbq^qWqcqiqeqiqdq]qUsSs[qaqdqhqnqbqjqeq\\qgqgq]q^q\\"
"qiqeq]q]qnraq]qnqmqnqgqnqlqfqfqgqjqeqfqgqjqeqYq`qiqeqjqdqlqmqlqhqnqbqmq]rdq]qZq^pgp=taqns`s`snqatdv_snqcqnsbq]q]qkqcq]qnsmshqns`saqnsasnqcqnr`tbvaqjqe"
"qiqdqkqkqjrkreqiqdw`q`qZq#tnreqkq^qatauaqnsdqiq`raqjqdqiqdpmrcxdqmqmqatbxfyeqiqbqnq`r`q^qfqhrmqmrfqhqgqlqlqgqfqep[pnqnp[p`q`pipbpnqnpNq]taq^qnqnqbqmqb"
"q\\qIqmpkpmqkqkp$qmpkpmqVqmq\\q`q[pLqjqeump:p^pjpLphpdphpapkpbq^qnq`qnq`qnq`qnq`qnq`qnq`qmqdq\\q]q]q]q]q]q]q]q]qgqgqnqlqfqfqhqfqhqfqhqfqhqfqfrjrhqiqnqgqi"
"qeqiqeqiqeqiqdqmqbqkrdqmsbt`t`t`t`t`t`tlsfs_t`t`t`tbq]q]q]q[tbqns`s_s_s_s_s\\q`smpdqjqdqjqdqjqdqjqeqiqdqnscqiq;qlqlqgqgqgqnqmqnqgqjqnqgqgqfq_qjq<{fpjpL"
"vatd|fxeqkqdqipasaqkqdp  \\yNqGplqeqmp`qmqmqcrLqZq`qnpnq\\q%q_qiqaqZq^rbqmqbubqms^qaqkqdqiqdq]qXuf{fu_q`qlrnqlqjqlqcqkreq\\qgqgq]q^q\\qiqeq]q]t`q]qnqmqnqg"
"qnqlqfqfqgqkreqfqgqkres[q`qiqeqjqdqlqmqlqhs`s]rcq]qZq#vbwcvbwcwev`wcwcq]q]qlqbq]vnthwcwcwcwcubwcvaqjqdqkqcqkqkqiqkqdqiqdw`q`qZq7smsfxdqlr^qavdvawdqkq_"
"raqjqdpgpeqntdxdqmqmqcwdyfyeqiqcqlq`raq^qfqhqlqlqfqhqgqlqlqgqfqfrZqZraqarkraqLq^vbq^wbqmqbq]tKpmpfpkpjp_plp9plpkplpUs[qaqZpLqjqeump:p^pjpaplp_piqdpiqa"
"plqbq_qlqbqlqbqlqbqlqbqlqbqlqbrmqdq\\q]q]q]q]q]q]q]q]qgqgqnqlqfqfqhqfqhqfqhqfqhqfqerlrgqjqmqgqiqeqiqeqiqeqiqcsaqjqdqnq`vbvbvbvbvbvbvnuivbwcwcwcwcq]q]q]"
"q]wcwcwcwcwcwcwOwcqjqdqjqdqjqdqjqeqiqdwdqiq;pkqkpgpepgpmumpgpjrmpgpepfq_qkq;{hrkpLxdxf|fxepipdqipas`pkpcp  ZqHqGplpdt_pmplpmshsMqZqaplplp]q&q^qiqaq[qa"
"t`plqbvcx_q`ucrkr:uc{cucq`qlvlqjqlqcwdq\\qgqgxdvcqjtfyeq]q]s_q]qmsmqgqmqmqfqfqgwdqfqgwcv_q`qiqdqlqbqmqmqmqfr`s]qbq\\q[q#pjqcrlrdqkpcrlrcqkrdq^rlrcrlrdq]"
"q]qmqaq]rlrlqirlrdqkqcrlrerlrcr_qjpbq]qjqdqkqcqlslqhqmqbqkq^q_q`qZq_tjpSqmsmpgrlsdqnsaqmqbqkqdq\\rlrdqlq_raqjqeqgqgrnqnrdqlqcqmqmqcqkqerkq`qaycqlq_rbq^"
"qfqhqlqlqfqhqgqlqlqgqnvnqgrYqYrbqbrirbqLq_rnpmpdwaqmqcydq^qlqLpmpfpkpkq`plpa{RpltkpB{gpXpLqjqdtmpcqHp]plp_plp`pipjpipipmsfplpjphr_qlqbqlqbqlqbqlqbqlqb"
"qlqbqlxkq\\xdxdxdxdq]q]q]q_vjqgqmqmqfqfqhqfqhqfqhqfqhqfqdrnrfqkqlqgqiqeqiqeqiqeqiqcsaqjqdqnq`pjqcpjqcpjqcpjqcpjqcpjqcpjrlrjqkpbqkrdqkrdqkrdqkrdq]q]q]q]"
"qkrdrlrdqkqcqkqcqkqcqkqcqkqOqkqcqjqdqjqdqjqdqjqdqkqcrlrdqkq:pnwnpgpnwnpgplslpgpkrlpgpkqkpfq^qlq6qaqlpMzfzfzfzgqipdqipbqmp`qmqc|  fqHqHqlpcuasmplpmpiul"
"qSqZq]p^{+q^qiqaq\\q`ubqlqbpkrdrkrarawcx<tEteq`qlqlqlqjqlqcwdq\\qgqgxdvcqjtfyeq]q]t`q]qmsmqgqmqmqfqfqgvcqfqgv_t`q`qiqdqlqbqmqmqmqgs_q]qaq\\q[q\"vcqjqeq]qj"
"qdqiqdq^qjqcqjqdq]q]qnq`q]qkqkqiqjqeqiqdqjqeqjqcq^s^q]qjqdqkqbqmsmqgqmqbqkq_qas_qYsc{Spkqkphqkrcqntcvcqiqeq\\qjqdqmr`tbqjqeqgqgqmqmqdqlqcqmqmqdqiqfqiqa"
"qaycqlq_qaq^qfqhqlqlqfqhqfqmqmqfqnvnqh}cqc}cqc}cqLq_qmpawbqkqasaq^qkqMpmpfpjsnpaplp`{RplpmqkpB{huatKqjqbrmpcqJt^r]plpctlpjqktlpmpkpltlpjqhq^qlqbqlqbql"
"qbqlqbqlqcrlrcqlxkq\\xdxdxdxdq]q]q]q_vjqgqmqmqfqfqhqfqhqfqhqfqhqfqcteqlqkqgqiqeqiqeqiqeqiqbq`qkrdqmravbvbvbvbvbvbvjqkq]qiqeqiqeqiqeqiqdq]q]q]q^qiqdqjqe"
"qiqeqiqeqiqeqiqeqiqd{hqkpnqdqjqdqjqdqjqdqjqdqkqcqjqdqkq:pnwnpgpnwnpgplslpgplrkpgpkqkpfq^qlq6qaqmqMzg|fxdxfqipdqipbqmqaqmqcp  \\wLqK{dt]qmqmqkrmrnrSqZqK"
"{TtKq^qiqaq]r\\rdqkq\\qdqiqaqarkrcsmq<tEtfq_qlqlqlqkqjqdqjqeq\\qgqgq]q^qgqfqiqeq]q]qnraq]qmsmqgqlqnqfqfqgq^qfqgqkq]raq`qiqdqlqbqnqkqnqgt`q^raq\\q[q#wcqjqe"
"q]qjqdydq^qjqcqjqdq]q]s_q]qkqkqiqjqeqiqdqjqeqjqcq]uaq]qjqcqmqaqmpmpmqfs`qmq_ras_qYscpjtRpkqkphqkrcqkreqlrcqiqcr_qjqdqmq_qnqbqjqeqlqlqgqmqmqdqlqcqmqmqd"
"qiqfqiqaqaqiqdqjqaq`q^qfqhqlqlqfqhqfrnqnrfqfqh}cqc}cqc}cqLq_qmp_q^qkq`qMrlqMpmpfpWplpUqRplplqlp=q&qjq`pmp _plp]qkpnpdqhpeqkpnpiq^qjqdqjqdqjqdqjqdqjqdq"
"jqdqkqdq\\q]q]q]q]q]q]q]q]qgqgqlqnqfqfqhqfqhqfqhqfqhqfqbrdqmqjqgqiqeqiqeqiqeqiqbq`wcqlrcwcwcwcwcwcwc~kq]yeyeyeydq]q]q]q^qiqdqjqeqiqeqiqeqiqeqiqeqiqd{hq"
"lpmqdqjqdqjqdqjqdqjqcqmqbqjqcqmq9pkqkpgpepgpmumpgpmrjpgpepfq]pmq:{epmpLzg|evbveqipdqipbqmqaqmpbq  [qHqK{cpmq^plqmqkqktRqZqFqOtKq^qiqaq^rZqdy^qdqiqaqaq"
"iq]q:uc{cudq_qlqlqmqjxdqiqfq\\qgqgq]q^qgqfqiqeq]q]qmrbq]qlqlqgqlqnqfqfqgq^qfqgqkr]qaq`qiqcqnqaqnqkqnqhrnq`q_r`q\\q[q$qjqcqjqeq]qjqdydq^qjqcqjqdq]q]s_q]q"
"kqkqiqjqeqiqdqjqeqjqcqZsbq]qjqcqmqaqnqmqnqfs`qmq`r^r`qZr9pkqkphqkrcqjqeqkqcqiqet_qjqcqnq`rnqbqjqeqlqlqgqmqmqdqlqcqmqmqdqiqfqiqaqaqiqdqjqbr`q]qhqgrmqmr"
"fqhqeweqfqgrYqYrdpnqnpdrirdpnqnpNq_qmp_q]qmqcyPrmqMqmpkpmqkvaplpVqRqmpkpmq=q&qjq`pmp(v_plp\\pkpmpdphqepkpmpjq]xdxdxdxdxdxdwdq\\q]q]q]q]q]q]q]q]qgqgqlqnq"
"fqfqhqfqhqfqhqfqhqfqcteqnqiqgqiqeqiqeqiqeqiqbq`vbqjqeqjqdqjqdqjqdqjqdqjqdqjqdqjxkq]yeyeyeydq]q]q]q^qiqdqjqeqiqeqiqeqiqeqiqeqiqQqmplqdqjqdqjqdqjqdqjqcq"
"mqbqjqcqmq9qlqlqgqgqgqnqmqnqgqnqjqgqgqfq]qnq:{eqnpLzg|dt`tdqipcpipbpkp`sbq  Zq plq`pmq_pkqmqkqjrQqZqFq'q]rkraq_rYqdy^qdqiqbq`qiq^q6uf{fuaq_qlyjzeqiqeq"
"]qhqfq]q]qhqfqiqeq]q]qlrcq]qlqlqgqkseqhqfq]qhqfqjq]qaq`qiqcqnq`skshrmraq_q_q[q\\q$qjqcqjqeq]qjqdq\\q^qjqcqjqdq]q]qnq`q]qkqkqiqjqeqiqdqjqeqjqcqXqbq]qjqcq"
"mqaqnqmqnqgqmq`s_q\\q`qZq7pmpnqmpgqkrcqjqeqkpbqiqeq\\qjqcs_qlqcqjqeqlqlqgqmqmqdqlqcqmqmqdqiqfqiqaq`qkqdrjrdr_q]riqfrnqnreqhqducqhqerZqZrdwdrkrdwOq_qmp_q"
"^w`q`q[sKplslpTplpWqQpmpkqnp<q&qjq`pmp aplp\\pkplpephqepkplpjq^zfzfzfzfzfzfxcq]q]q]q]q]q]q]q]q]qhqfqkseqhqfqhqfqhqfqhqfqhqcrnreriqfqiqeqiqeqiqeqiqbq`q]"
"qjqeqjqdqjqdqjqdqjqdqjqdqjqdqjqdq]q]q]q]q\\q]q]q]q^qiqdqjqeqiqeqiqeqiqeqiqeqiqQqnpkqdqjqdqjqdqjqdqjqbsaqjqbs7qmqmqeqiqeqiqeqiqeqiqeq]qnp7q]rJrnpnresnpn"
"sct_rcqipcqkqcqkqasaq  [rkp&plpcplpnr`qkqmqkrltRqZqFq'q\\qkq`q`r_pjr^qcpjrcqkrbq`rkrdpkr3sSsLrlrnrhqhqeqjreripeqjsfq]q]riqfqiqeq]q]qkrdq]qgqgqkserjrfq]"
"rjrfqjrfpiraq_qkqbt`skshqkqaq`q^q[q\\q$qkrcrlrdqkpcrlrcqipdq^rlrcqjqdq]q]qmqaq]qkqkqiqjqdqkqcrlrerlrcq^pjqbq]rlrbs_rkrfqmq`s`r\\q`qZq6qlrfrmscrlrepkqbrk"
"qdqkpaqjqcs`rlqcrlrernsnrgrnqnrdqlqcrnqnrdrkqdqkraq`qkqdqhqer^q\\rkqdwdqhqbqarjrdpYqYpbubpipbuNq_rnpmpbq^qnqnq`q`qZqIpgpRplp7pgp;q&rlr`pmp bplp[pkufpiq"
"dpkukrlpcqhqfqhqfqhqfqhqfqhqfqhqfqjqcripeq]q]q]q]q]q]q]q]qjsfqkserjrfrjrfrjrfrjrfrjrdrlrfrjreqkqcqkqcqkqcqkqaq`q]qnplqeqkrdqkrdqkrdqkrdqkrdqkrdqksjpjq"
"kpbqipdqipdqipdqipdq]q]q]q]qkqcqjqdqkqcqkqcqkqcqkqcqkq^qbqkqcrlrdrlrdrlrdrlrbsarlrbs6qkqcqkqcqkqcqkqcqkqdq\\r7q\\qFp\\p]r^rcqipcvbqkqas`r  \\vOqIqlpcw_pip"
"mpivnrRpZpEqbqIq^q[ubwdxdw]qcwbwaq_wcvbq]qRpSp[q^q^qhqexcxeyexdq\\xeqiqeq]q]qjrexdqgqgqjrdxeq\\xeqiqfx`q_war_ririqiqbqazfq[q\\q$xcwcvbwcxdq]wcqjqdq]q]qlq"
"bq]qkqkqiqjqdwcwcwcq^wbu`wbs_rkrgqkq`q`w`q`qZq$yewdqmq`wdvaqjqbr`qkqcyeyewcqlsdwcxdw`sauczexdq^umteucqhqbq`xLqJsKsMq^vdxdpgpaq`qYqIqkq bqkq?{+yapmp Jp"
"fpfpipcpfpiucqhqfqhqfqhqfqhqfqhqfqhqfqjxixexdxdxdxdq]q]q]q]yeqjrdxdxdxdxdxdrjrgpnwdwcwcwcwaq`q]qnuexdxdxdxdxdxdvnwjvbxdxdxdxdq]q]q]q]wcqjqdwcwcwcwcw^q"
"bwbwcwcwcwaq`w`q4uauauauaucq\\r7p[qFp\\p\\p\\pbqipasapip`q^y  ctNqIqmqbu_phsgslrSq\\qEqbqIq^qZsawdxcu\\qbt^taq]uataq]q q]qgpiqfqfw`udwcxdqZudqiqeq]q]qirfxdq"
"gqgqjrbtcqZtcqirfv_q]s_r_rirjrircqazfq[q\\q#tnqcqns`s`snqaucq\\snqcqjqdq]q]qkqcq]qkqkqiqjqbsaqnsasnqcq]t_t_snqaq^rkrhrkraq`w`q`qZq#smrevbs^t`s`qjqbq`qiq"
"dqnrmqdrmrcubqkrcubqntat^r`sc|fxdq^umtcqaqhqbq^tJqIqIqLq]tcxLq`qYqHu `u>{+qnrmqapmp Kpepgpiuhpephscqfqhqfqhqfqhqfqhqfqhqfqhqixgudxdxdxdxdq]q]q]q]wcqjr"
"bt`t`t`t`taphpgplt`s_s_s_s_q`q]qmsctnqctnqctnqctnqctnqctnqbsktgs_uauauaucq]q]q]q[saqjqbs_s_s_s_sNpms_snqbsnqbsnqbsnqaq`qns_q !p Zp      jp#q\\q6q7q   l"
"q [sjq  Qq -q  OqZq]q  Cq;q HqWq $rIq`qZq _q iqbqKqFqIq`q     hp$q]u   JqYpmpLp   .p        jp    ]p Xr`q[r !p       Tp\"p\\p6q6q   mq Yx  Qr -r  Ps\\q_s"
"  Ipkq:q HqWq $qHq`qZq _q iqbqKqFqIq`q     hp$q]t   IqYpmpLq   /q        kq     Fq_q[q #s       Tp\"q^q6p   1p Vu  Rs    YsJsMy &v<s HqWq &sHtcq]t _q i"
"qbqKqFqIq`q     hp$q   2q2q   /q        kq     Hs_q]s \"q                (r     Xy %t;r GqWq &rFscq]s ^q iqbqKqFqIq`q         ,q4r   0r        lr     G"
"r^q                               *q                                                                                   kr               i";

    // Define a 47x53 font (extra-large size).
    static const char *const data_font47x53 =
"                                                                                                                                                      "
"        9])]2_2]T\\8^U^3]  E])]2`4^U^>])]2_4^U^ 6^T\\5])]1_2]T\\8^U^  K])]2`4^V^3]                                                                       "
"                                                                                                                    U]*\\2a4`V\\8^U^5a  F]*\\1\\X\\4^U^=]*\\"
"2a5^U^ 7aV\\4]*\\1a4`V\\8^U^  J]*\\1\\X\\4^V^3\\                                                                                                             "
"                                                                              S],\\1\\W\\5g8^U^6c  F],\\1\\V\\5^U^<],\\2]W]6^U^ 8h3],\\0\\W\\5g8^U^  I],\\1\\V\\5^V"
"^4\\      ;]                                                                                                                                           "
"                                         :\\-]2\\U\\6\\V`7^U^7]U]  F\\-]2\\T\\6^U^;\\-]3]U]7^U^ 8\\Va1\\-]1\\U\\6\\V`7^U^  H\\-]2\\T\\6^V^5]      =a                  "
"              J]                                                                                                                                      "
"              N\\/]2\\S\\7\\T]6^U^7\\S\\  E\\/]2\\R\\7^U^:\\/]3]S]8^U^ 8\\T^/\\/]1\\S\\7\\T]6^U^  G\\/]2\\R\\7^V^6]      =c                                L^           "
"                                                         *^                            U`                                         O^             )\\S\\ "
"                    !^$^3\\  E]U\\  K^$^4^ G^$^4]   J^$^3\\   #^$^3\\ 4^            B[                                                                    "
"&^                            Xe                                         S^             (\\S\\               )Z      Q^&^3^2]S\\ A\\S\\  K^&^3^ F^&^4_  >]S"
"\\9^&^3^2]S\\   W^&^3^ 6^        Q]    M[               ?`   ![1^H]?` =]4](\\    %` >b4c  Bb ?`2a    .a   Ib   Pb      Aa <a @b      Fb =b  F^ :] '] Da A"
"].].].].]            <_:]._    Xh ?c   W^       @`   La   Pa        Sa   Va5^U^ @`   \"f4_ >`0`*^   $^.` <^F]F^F]G`G]     F\\S\\ ;b        %a2a2a2a2a <bR"
"\\     D`4^(^3`4`U\\8^V^6\\S\\  J^(^3`4^U^@^(^3_4^U^/^/`U\\8^(^3`4`U\\8^V^  K^(^3`4^V^1^9]+^V^      ?`    O\\  D\\6]M]            We D]1]T] 9[3bJ\\@e<])]2])\\  "
"  T]0d3_7h9i/_;k5f?n:f7e    3g :_8i3h@h9n?l5iB]H]C].].]J^B].`I`H_J]<g?g1g?g4hAuB]H]G]C]F]K_K]S^J^F^G^CrBb7]*b'_ D] :] '] Fc A].].].].]            >a:]"
".a   !^T_ Bg   `       Dd2_8n?m7g3]:rD]P]P]@g <] 8] 8] B] 3e J^K^ If7^U^+b@d   Fb@f5a Ad4e-] :f  Ra0d AaF\\HaF\\HeJ\\?]._0_0_0_0_2\\U\\0tHh@n?n?n?n?].].].]"
"-h:_J]<g8g8g8g8g BhV]G]H]C]H]C]H]C]H]G^G^B]*d5](]2\\X\\4aW]8^V^6\\S\\  I](]3]X]5^U^?](]3\\W\\5^U^.^R[9aW]7](]2\\X\\4aW]8^V^  J](]2\\X\\4^V^1]8]+^V^      ?a>w   "
"P[ 9[/a:aQa7[    Wl      \"h E]1]T]+\\R\\;[4dL]Ag=])]2])\\    U^1f8c8k;j1`;k7h?n;h9g    5i*b:_8k6kBl=n?l7mD]H]C].].]L_A].`I`H`K]>kAj6kAj9kBuB]H]F]E]E^L_L^"
"R^L^D^I^BrBb7^+b(a D] ;] '] Gd A].].].].]      ;]     (b:].b   #^Q] Dj  !a       Ff3_8n?m8i4]:rD]P]P]Bk ?_ 9] 9_ C]&[0f I]K]=]0g7^U^-fC\\S]   IfBf6c B["
"S]5[S].] <i  R\\W\\1]T] B\\W\\G]H\\W\\G]H[S]K]?]._0_0_0_0_2c1uIkBn?n?n?n?].].].]-l>`K]>k<k<k<k<k EoF]H]C]H]C]H]C]H]F^I^A],h6]*]2\\V\\6]Wa7^V^6\\S\\  H]*]2\\V]6^U"
"^>]*]3]W]6^U^._V_;]Wa5]*]2\\V\\6]Wa7^V^  I]*]2\\V\\5^V^2]7]+^V^      @]W\\=v   P[ 9\\1c<cSd:]   \"o      #_S^ F]1]T],]S];[5^V^N]A_T]=]*]0]*\\    U]1^T^;e8`S_<"
"^R_2`;k8^R]?n<_T_;^S^    6^S_.i>_8m:`R`Cn?n?l9`QaE]H]C].].]M_@].aKaH`K]?`S`Bk8`S`Bk;_R_BuB]H]F]E]D]MaM]P]L]B^K^ArB]1]&])c D] <] '] G] :].].].].]      "
";]     (^6]*^   #]P^ E^P\\   V^       H^T^4_8n?m:`S`6]:rD]P]P]C`S` Aa :] :a D]&[1^S\\ I^M^=]0^R[7^U^/^R^EZO\\   L^R^ N]U] :],\\0] <j  M\\2]R] >\\H]B\\H]=\\M]>"
"]._0_0_0_0_0_/uK`R`Cn?n?n?n?].].].]-n@`K]?`S`>`S`>`S`>`S`>`S` H`ScE]H]C]H]C]H]C]H]E^K^@],^T^5],]1\\V\\6\\U`7^V^6]U\\  F],]2\\T\\6^U^=],]2\\U\\6^U^-e9\\U`4],]1\\"
"V\\6\\U`7^V^  H],]1\\V\\5^V^3]6]+^V^  B`1`1`1`1`6]W]>u   P[ 9]2e>eUf;^   %q      $^O\\ F]1]T],]S];[5]T]N\\@]P[=]*]0]2ZR\\RZ   $]2]P]<_W]8]N]<ZL^4a;]+]MZ/]<^P"
"^=^Q^    7\\O]1nAa9]N_<_M]C]NaA].]+_L^E]H]C].].]N_?].aKaHaL]@^M^C]P_:^M^C]P_=^M\\6]6]H]F^G^D]MaM]P^N^B^K^-^B]1]&]*e D] =] '] H] 9].].].].]      ;]     )"
"^5])^   %^O]8^3]LZ   U]       I^R^6a9_0]+^M^7]:]H]D]P]P]D^M^ Cc ;] ;c E]&[2^PZ H]M]<]1^-^U^1]L];[   N]L] Q]S] :\\,\\1] <dU\\  M\\2\\P\\ >\\H\\A\\H\\<\\M\\=]/a2a2a"
"2a2a1_/]V];_M]C].].].].].].].]-]ObBaL]@^M^@^M^@^M^@^M^@^M^ J^N`D]H]C]H]C]H]C]H]E^K^@]-^Q]5].]1\\T\\7\\S]6^V^5c  E].]2]S\\7^U^<].]2\\S\\7^U^,a6\\S]2].]1\\T\\7\\S"
"]6^V^  G].]1\\T\\6^V^4]5]+^V^  De6e6e6e6e9\\U\\>u   P[ :_3f@gVf<_   &r      $]M[ F]1]T],\\R]>d<^T^P]A^OZ=]+].]4]T\\T]   &^3^P^=[S]8[K].]4\\X];],]!]<]N]>^O^  "
"  8ZM^3`P`Ba9]M^=^J\\C]K_B].],^H\\E]H]C].].]O_>].aKaHaL]A^K^D]N^<^K^D]N^>]JZ6]6]H]E]G]C]MaM]O^P^@^M^-^A]1]&]+_W_ D] >] '] H] 9]  B].]      ;]     )]4](]"
"   %]N]:c6]   G]       J^P^7a8_1],^K^;c=]H]D]P]P]E^K^ Ee <] <e F]&[2] =^O^<]1] 0\\H\\<\\   P\\H\\ R\\Q\\+]3\\,\\2] <eU\\  M\\3]P\\ >\\I]A\\I]<\\N]=]/a2a2a2a2a2a1]U]<"
"^J\\C].].].].].].].]-]K_CaL]A^K^B^K^B^K^B^K^B^K^ K]K^D]H]C]H]C]H]C]H]D^M^?]-]P]4]0]1\\R\\  Ha  C]0]2]R] E]0]2\\Q\\ 9c 9]0]1\\R\\   !]0]1\\R\\ ?]4]   Di:i:i:i:i"
";\\6]G]   P\\ :`5g@gWh>a   (_       J]KZ F]1]T],\\R\\?h>]R]P\\@]1]+].]3^V\\V^.]   T]2]N]5]8ZJ]-]6]X];]-]!^=]L]?]M]    *]5_J_Ec:]L^>]H[C]I^C].],]F[E]H]C].].]"
"P_=].]X]M]X]HbM]A]I]D]M]<]I]D]M]?]%]6]H]E]G]C^NaN^N]Q^>^O^-^@]0]'],_U_  &] '] H] 9]  B].]      ;]     )]4](]   %]N]:d7]   F]       K]N]8c8^1],]I]>i@]H"
"]D]P]P]E]I] Fg =] =g G]&[2] <]O];]1] 1\\F\\=\\   Q\\F\\ S\\Q\\+]3\\.]  IeU\\  M\\3\\N\\ ?\\I\\@\\I\\=]M\\<]0c4c4c4c4c3a1]U]<]H[C].].].].].].].]-]J_DbM]A]I]B]I]B]I]B]I]"
"B]I] L]J_E]H]C]H]C]H]C]H]C^O^>].]N]    .]        '`X_           I]   FbWa=bWa=bWa=bWa=bWa<\\6^I^  ?Z2[ :a5gAiXh?c   *^       H] 7]1]T]-]S]Aj>]R]Q]@]1],"
"],\\1^X\\X^,]   T]3]L]6]'].]7]W];]-]!]<]L]?]M^    +]6^F^F]W]:]K]?]FZC]H^D].]-]DZE]H]C].].]Q_<].]X]M]X]H]X]M]B]G]E]M^>]G]E]M^@]%]6]H]E^I^B]O^X]O]M^R^=]O^"
"-^@]0]']-_S_  '] '] H] 9]  B].]      ;]     )]4](]   %]N]:e8_   H]       L]M]8]W]7^2]-]G]AmB]H]D]P]P]F]G] Hi >] >i  J[3] ;^Q^;]1] 2\\RbT\\Ge   R\\VdR\\ T\\"
"Q\\+]4\\2a  IfU\\  M\\3\\N\\ ?\\J\\?\\J\\AaM\\ G]W]4]W]4]W]4]W]4]W]4c3^U]=]FZC].].].].].].].]-]H]D]X]M]B]G]D]G]D]G]D]G]D]G]A[H[B]J`E]H]C]H]C]H]C]H]B]O^>g8]N]    "
"         1]T_      3[    9]   G_O^?_O^?_O^?_O^?_O^=\\5]I^  @\\3[ ;c6gAy?d7`8]L]7^7]L]>^       H] 6]1]T]-]S]B_W[U]>]R]R]?]1],],]0d*]   T]3]L]6]'].]7\\V];]"
".] ]<]L]@]K]  7Z PZ X]7^D^G]W]:]K]?]/]G]D].]-]/]H]C].].]R_;].]X^O^X]H]X^N]B]G]E]L]>]G]E]L]@]%]6]H]D]I]A]O]W]O]L^T^<^Q^-^?]0]'].^O^  Sb7]U`2b4`U]8a8])`"
"7]T_  M].]%_O_@_2`0`3`/_3c9]     )]4](]   N_6]N]3^7a/c0_ <^  D[U^  Ga  N]L]9]W]6^3]-]G]B`W]W`C]H]D]P]P]F]G] I_X]X_ ?] ?_X]X_  Nb7]2ZFZ=]Q]:]0] 3[SfU[I"
"g   R[UfS[ T\\Q\\+]5]2a  IfU\\  M\\3\\N\\ ?\\K]?\\K]AaN] G]W]4]W]4]W]4]W]4]W]4]W]3]T]=]/].].].].].].].]-]G]E]X^N]B]G]D]G]D]G]D]G]D]G]B]J]C]KbF]H]C]H]C]H]C]H]B"
"^Q^=j;]P_9b3b3b3b3b3b3bN`Bb3a2a2a2a    V_2_2`1`1`1`1` ;aU]    :]U`   S^T]U^A^L^A^L^A^L^A^L^?]5]I]  @^5\\ <e7gAy@f;e:]L]8`8^N^?^       G] 6]1]T]-\\R\\A]U["
"RZ>]R]R\\>]1],],].`(]   U^3]L]6]'].]8]V];].]!^<]L]@]K]  :] P]#^8^A]I^W^;]K]@].]G^E].].].]H]C].].]S_:].]W]O]W]H]W]N]C]E]F]L]?]E]F]L]@]%]6]H]D]J^A]O]W]O]"
"L^U^:^S^-^>]0^(]/^M^  Wh:]Wd6f8dW]:e>h2dW]?]Vd<].].]O_>].]WdScK]Vd8f;]Wd7dW]?]Wa6h>h6]L]B]I]A]P`P]K^L^B^K^@l4]4](]   PdU]A]N]2^8e5g;]Vd?^J^8]6]L] E]V`"
">pA]S]S]:e6kDo>]L]:^W^6^4].]E]D_U]U_D]H]D]P]P]G]E] K_W]W_ @] @_W]W_  Qf9]3\\H\\>^S^:]0_ 6[ThT[K]Q\\   S[T\\R]S[ U]S]+]6],] ?]L]@fU\\  M\\3\\N\\ ?\\K\\>\\K\\;]O\\ G"
"^W^6^W^6^W^6^W^6^W^5]W]4^T]>].].].].].].].].]-]G^F]W]N]C]E]F]E]F]E]F]E]F]E]D_L_E]K]W]F]H]C]H]C]H]C]H]A^S^<k<]Ra<h9h9h9h9h9h9hTeFf7e6e6e6e;].].].]\"^;]V"
"d8f7f7f7f7f/^6eX]@]L]?]L]?]L]?]L]B^K^?]Wd>^K^  O]S]S]B]I]B]I]B]I]B]I]@]5^K^  @]4[ ;f8gAyAg<h<]L]8`7]N]>]       F] 6]1]T]-\\R\\B]T[6]R]S]>^2]-]*\\.`(]   U"
"]2]L]6]'].]9]U];].]!];]L]@]K]  =` P`'^7]?\\I]U];]K]@].]F]E].].].]H]C].].]T_9].]W]O]W]H]W^O]C]E]F]L]?]E]F]L]@]%]6]H]C]K]@^P]W]P^K^V^9]S]-^=]/](]0^K^  Xi"
";]Xf9h9fX]<h?h3fX]?]Xg=].].]P_=].]XfVfL]Xg:h<]Xf9fX]?]Xb7i>h6]L]A]K]@^Q`Q^J^N^@]K]?l4]4](]   QfW^A]O^1]6f9h;]Xg@_K]7]6]L]=]G]C^Wc@pA]S]S]<h9mDo>]L]:]U"
"]5^5].]E]E^S]S^E]H]D]P]P]G]E]@Z+]V]V^-Z4]5ZKZ:]V]V^  Sh9]4^J^>]S]9]._ 8[U_Q[T[L]P\\   S[T\\Q]T[ T]U]*]7]*] @]L]@fU\\  M\\3\\N\\ ?\\L]>\\L]:]Q]:]1]U]6]U]6]U]6]"
"U]6]U]6^W^5]S]>].].].].].].].].]-]F]F]W^O]C]E]F]E]F]E]F]E]F]E]C_N_D]L^W]F]H]C]H]C]H]C]H]@]S];]P_=]S^8i:i:i:i:i:i:iVgIh9h9h9h9h<].].].]'d<]Xg:h9h9h9h9h"
"0^8k?]L]?]L]?]L]?]L]A]K]>]Xf>]K]  O]R]R]D]G]D]VZOZV]D]KZV]D]G]A]4]K]  @]3[ <g7fAyBi>j=]L]8`7]N]?]       F^ 6]1]T]5uI]T[6]R]S\\<^3]-]*]1d*]   U]3]J]7]']"
".]9\\T];].\\Ua-^;]L]@]K^?].] Uc Pc+_8]>]J]U];]K]@].]F]E].].].]H]C].].]U_8].]W^Q^W]H]V]O]C]E]F]L]?]E]F]L]@^&]6]H]C]K]?]Q^V]Q]I^X^8^U^.^<]/](]1^I^  ]R_<aT"
"_;_R\\:^Tb=_S^@h4_Ub?bT^=].].]Q_<].aT_X]T^LbT^;_T_=aT_;^Tb?aTZ8_R]>h6]L]A]K]?]Q`Q]H^P^?]K]?l4]4](]   R^U^W]@]O]0^7g;_S];bT^@`L]8_7]L]>]E]E^W]V]@pA]S]S]"
"=_T_<oDo?]K^;]U]5_6].\\D]E]R]R]E]H]D]P]P]G]E]A\\+[U]U\\,\\6]6\\L\\;[U]U\\  S_W[V\\9]3^V`V^=^U^9]/a :[T]G[M\\O\\1ZQZ  M[S\\P\\S[ Ud)]8](\\ @]L]@fU\\  M\\3\\N\\9ZQZ0\\L\\="
"\\L\\8\\Q\\9]1]U]6]U]6]U]6]U]6]U]6]U]5]S]>].].].].].].].].]-]F]F]V]O]C]E]F]E]F]E]F]E]F]E]B_P_C]L]V^G]H]C]H]C]H]C]H]@^U^;]N^>]T]6]R_;]R_;]R_;]R_;]R_;]R_;]R"
"_X_T^K_R\\:_S^;_S^;_S^;_S^=].].].]*h=bT^;_T_;_T_;_T_;_T_;_T_1^9_T`>]L]?]L]?]L]?]L]A]K]>aT_?]K]  P]Q]R]E]F]E]V\\Q\\W]E]K\\W]E]F]A]4^L]  A^@ZN\\ =i8e@yCk?^R^"
"=]L]9b8]O^?]       Im B]1]T]5uI]T[6]S^T]<^3]-]*]3^X\\X^,]   V^3]J]7](^/]9]T];e7]We/]9]N]?]K^?].] Wd Nd._8]O`U\\T\\K]S]<]L^A]-]F^F].]/]-]H]C].].]V_7].]V]Q"
"]V]H]V^P]D]C]G]L]@]C]G]L]?^']6]H]C^M^?]Q]U]Q]Ic6^W^._<]/^)]2^G^ !ZM^=`Q^=^NZ;^Q`>^P^=].^Q`?`Q^>].].]R_;].`R^X\\R^M`Q^=^P^>`Q^=^Q`?`1]MZ;].]L]A^M^?]Q`Q]"
"G^R^>^M^1^4]4](]  D]P^A]R^X]@]P^/]9^Vb=^NZ;`Q^AaN^8_7]L]>]E]F^V]U]>]P]>]S]S]>^P^>`T`7]6]J]<]S]5^6]/]C]G]Q]Q]F]H]D]P]P]H]C]C^&]TZ,^7]7^N^6]TZ H]/^U[TZ9"
"]2n;]U]8]0d <[U]F[M\\P]2[R[  M[S\\P\\S[ Tb(]9]'\\ @]L]@fU\\  M\\3]P]9[R[1\\M\\<\\M\\7\\R\\8]2]S]8]S]8]S]8]S]8]S]7]U]6]R]?]-].].].].].].].]-]F]F]V^P]D]C]H]C]H]C]H]"
"C]H]C]B_R_C]L]T]G]H]C]H]C]H]C]H]?^W^:]M]>]U^6ZM^<ZM^<ZM^<ZM^<ZM^<ZM^<ZMbP]M^NZ;^P^=^P^=^P^=^P^>].].].]+i=`Q^=^P^=^P^=^P^=^P^=^P^2^:^P^>]L]?]L]?]L]?]L]"
"A^M^>`Q^@^M^  P]Q]Q]F]E]F]W^S^W]F]L^W]F]E]B]3]M^  B^B^O[ =k8d?xClA^P^>]L]9]X]8^P]>\\       Hl A] 9uI]T[5]T]T]:^ =]*]5^V\\V^.]   V]2]J]7](]/^:]S];h:]Xg0]"
"9^P^?]K^?].]!e Je2_7\\PdW\\S\\L]S]<]M^@]-]E]F].]/]-]H]C].].]X_5].]V]Q]V]H]U^Q]D]C]G]L]@]C]G]M^?`)]6]H]B]M]>]Q]U]Q]Hb5c-^;].])]   B]=_O]=].]O_>]N^>].]O_?_"
"O]>].].]S_:]._P`P]M_O]=]N]>_O]=]O_?_1]-].]L]@]M]>]RbR]G^R^=]M]1^3]4](]  FaSaD^Qa?]R_.]9]R`>]._O]>^N]8`7]L]>]E]G^U]U^?]P]>]S]S]>]N]>^P^7]6]J]<]S]4^7]/]"
"C]G]Q]Q]F]H]D]P]P]H]C]D_&]&_8]8_N_7] B]/]T[3]1l:^W^8]1]W` >\\U\\E\\N\\P]3\\S\\  N\\S\\P\\S\\ S_']:]&\\ @]L]@fU\\  M\\2\\P\\8\\S\\2\\N]<\\N]7\\S]8]2]S]8]S]8]S]8]S]8]S]8]S]"
"7]R]?]-].].].].].].].]-]E]G]U^Q]D]C]H]C]H]C]H]C]H]C]A_T_B]M]S]G]H]C]H]C]H]C]H]>c9]M^?]U]'].].].].].].`O^N].]N^>]N^>]N^>]N^?].].].],_R^>_O]=]N]=]N]=]N]"
"=]N]=]N]2^:]O_?]L]?]L]?]L]?]L]@]M]=_O]?]M]  O\\P]Q]F\\D]F\\U^U^V]F\\L^V]F\\D]B]3]M]  RuJ`O[ >m9c>wCmA]N]>]L]9]X]7]P]?]       Im A] 2\\R\\A]T[5^V^T\\:` ?](\\6]T"
"\\T]/]   V]2]J]7])^1_9]S];i;bS^2^8^S_>]K^?].]$e@u@e6_7]QfX\\S\\M^S^=]N^?]-]E]F].]/]-]H]C].].c4].]U]S]U]H]T]Q]D]C]G]M^@]C]G]M]=c-]6]H]B]M]>^R]U]R^G`4c.^:]"
".])]   B]=^M]?^/]M^?]L]>]/]M^?^N^?].].]T_9].^O_O^N^N^?]M^?^M]?]M^?^0]-].]L]@]M]>^S]X]S^F^T^<^O^2_3]4](]  GcUcE]Pa?]Vb-]:]O_?].^N^>]O^8a8]L]?]C]H]T]T]?"
"]P]>]S]S]?]L]@^N^8]6]J]=^S^4^8]/]C]H^Q]Q^G]H]D]P]P]H]C]E_%]%_9]9_L_8] B]0^T[3]0_T_>cWc=]1]U_ ?[U\\C[N]R^4]T]  N[R\\Q]R[ 'uG]&] @]L]?eU\\  M\\2]R]8]T]3\\N\\;"
"\\N\\7]S\\7]3^S^:^S^:^S^:^S^:^S^9]S]8^R]?]-].].].].].].].]-]E]G]T]Q]D]C]H]C]H]C]H]C]H]C]@_V_A]N]R]G]H]C]H]C]H]C]H]>c9]L]?]U]'].].].].].]._M]O^/]L]?]L]?]L"
"]?]L]?].].].]-^O]>^N^?]M^?]M^?]M^?]M^?]M^ I]O`?]L]?]L]?]L]?]L]@^O^=^M]@^O^  P]P]P\\G]C\\G]T^W^T\\G]M^T\\G]C\\B]3^O^  RuJ[X]P[ >o=\\XaX]BwDoC]L\\>]L]:^X^8]P]?"
"]       E] 5] 3]S]A^U[4dT];b @](]6ZR\\RZ.]   V]2]J]7]*^7d8]R];]R_<aQ^3]5f<^M_?].]'e=u=e:_6\\Q^S`S]N]Q]=l>]-]E]Fm>k=]-rC].].b3].]U]S]U]H]T^R]D]C]G]M]?]C]"
"G]N^<f1]6]H]B^O^=]S^U^S]F_2a.^9].])]   A]>^M]?].]M^?]L]>]/]M^?^M]?].].]U_8].^N^N]N^M]?]L]?^M]?]M^?^0]-].]L]@^O^=]S]X]S]D^V^:]O]2_2]4](]  H\\U^W]U\\E]Pa?"
"]Vb-];]M^?].^M]>^P]7a8]L]?]C]H]T]T]?]P]>]S]S]?]L]@]L]8]6p=]Q]3^9]/]C]H]P]P]G]H]C]Q]Q]G]ViV]F_$]$_:]:_J_9] B]0]S[3]0]P]>o=]2]S_ @[U\\C[M]T_5^U^;u O[R\\R]"
"Q[ 'uH]/ZQ] ?]L]?eU\\  M\\1]T]7^U^4\\O]O]I\\O]T`MZQ]S]O]E]3]Q]:]Q]:]Q]:]Q]:]Q]:^S^9]QmO]-m>m>m>m>].].].]1hL]G]T^R]D]C]H]C]H]C]H]C]H]C]?_X_@]O]Q]G]H]C]H]C]"
"H]C]H]=a8]L]?]U]&].].].].].].^M]O].]L]?]L]?]L]?]L]?].].].].^M]?^M]?]L]?]L]?]L]?]L]?]L] I]Pa?]L]?]L]?]L]?]L]?]O]<^M]?]O]  O]P]P\\G]C\\G]ScS\\G]N^S\\G]P]P\\B"
"]2]O]  QuF]Q[ >oAqDuDqD]L]?]L]:^X^8^R^?\\       D] 5] 3]S]@`X[3bS\\R^G]W^N] P](].\\&]   W]1]J]7]*^7c8]Q];ZM^=`O^4]4d:]M_?].])d:u:d=_5\\R]O^R\\N]Q]=j<]-]E]F"
"m>k=]-rC].].a2].]U^U^U]H]S]R]D]C]G]N^?]C]G]P_:g3]6]H]A]O]<]S]S]S]E^1_.^8]-]*]   A]>^M]?]/^M^?]K]?]0^M^?]L]?].].]V_7].]M]M]N]L]@^L]?^M]@^M^?]/]-].]L]?]"
"O]<]S]X]S]C^X^9]O]2^1]4](]0_IZ O[R\\X]S\\G^O_>]Vd9_U];]L]?].]L]=]P]8]X^9]L]?]C]I^T]S]@]P]>]S]S]?]L]@]L^9]6p=]Q]3^9]/]C]H]P]P]G]H]C]Q]Q]G]ViV]G_#]#_;];_H"
"_:] B]0]S[3]0\\N\\>o=]2]Q^ A[U\\C[LcX\\6]T]9u O[RfP[ 'uIf7e >]L]>dU\\<] :f5d4]T]:fT\\O^NfT\\UdOeR\\O^F^3]Q]:]Q]:]Q]:]Q]:]Q]:]Q]:^QmO]-m>m>m>m>].].].]1hL]G]S]R"
"]D]C]H]C]H]C]H]C]H]C]>d?]P^Q]G]H]C]H]C]H]C]H]<_7]L]?]U^'].].].].].].^L]P].]K]@]K]@]K]@]K]@].].].].]L]?]L]@^L]@^L]@^L]@^L]@^L] I]Q]X^@]L]?]L]?]L]?]L]?]"
"O]<^M]?]O]  O\\WmX]H\\WmX]H\\QaR]H\\N^R]H\\O]P]C]2]O]  QuF]R\\ ?qCsDtDrE]L]?]L]:]V]7]R]>x      '] 5] 3\\R\\?e3^R\\SbJ^V^O] P](].\\&]   W]1]J]7]+^6e:]Q]-^>_M]5^6"
"h<^O`  Qe8u8e@^5]R\\M]R\\O^Q^>m?]-]E]Fm>k=]KdFrC].].b3].]T]U]T]H]S^S]D]C]G]P_>]C]Gk6f5]6]H]A^Q^<]S]S]S]F_1_/_8]-]*]   A]>]K]A].]K]@]J]?]0]K]?]L]?].].]W_"
"6].]M]M]N]L]@]J]@]K]A]K]?]/^.].]L]?]O]<]T^W]T]C^X^9^Q^3^1]3]']3dN\\ P\\R`Q[G]N_>]Q`;bW];\\K^?]/]L]=]Q^8]W]9]L]?]C]I]S]S]@]P]>]S]S]@]J]B^L^9]6p>^Q^4^9]/]C"
"]H]P]P]G]H]C]Q]Q]G]ViV]H_\"]\"_<]<_F_;] B]1]R[3]1]N]8a6]2]P^ B[U\\C[K`V\\7]T]8u O[RdN[ 'uIf5a <]L]=cU\\<] :f3`1]T];fU\\N^NfU\\T[S]NaQ\\N^G^3^Q^<^Q^<^Q^<^Q^<^Q"
"^;]Q]:]PmO]-m>m>m>m>].].].]1hL]G]S^S]D]C]H]C]H]C]H]C]H]C]=b>]P]P]G]H]C]H]C]H]C]H]<_7]L]?]U_(].].].].].].]K]Q].]J]A]J]A]J]A]J]@].].].].]L]?]L]@]J]A]J]A"
"]J]A]J]A]J] K]P\\V]@]L]?]L]?]L]?]L]?^Q^<]K]@^Q^  O\\WmX]H\\WmX]H\\P_Q]H\\O^Q]H\\O]P]C]2^Q^  D^<]R[ >qDuEsCqD]L]?]L]:]V]7]R]>x      '] 5] 3\\R\\=f+]TdL^T^P] P]"
"(].\\2u  *]1]J]7],^-_=]P],]>_M]5]7_R^<^Qa  Sd .dC^4\\R]M]R\\O]O]>]N_@]-]E]F].]/]KdF]H]C].].]X^4].]T]U]T]H]R]S]D]C]Gk=]C]Gj1c6]6]H]@]Q];^T]S]T^Ga1].^7]-]*"
"]   Lh>]K]A].]K]@]J]?]0]K]?]L]?].].]X_5].]M]M]N]L]@]J]@]K]A]K]?]._0].]L]>]Q];^U]V]U^Bb7]Q]3^1^3]'^6iS^ P[P^P[G]N_>]N^=dX]<]J]>^1]L]=^R]8^W]9]L]@]A]J]S"
"]S]@]P]>]S]S]@]J]B]J]9]6]J]>]O]5^8]/]C]H]P]P]G]H]B]R]R]F]C]Iz<]<z=]=z<] B]1]R[7j:\\L\\7_5]2]P^ B[U\\C[ V]T]7u O[R\\U^O[  T]   ]L];aU\\<]   I]T],]O[X\\>]K]@]"
"O[X\\I`3]O]<]O]<]O]<]O]<]O]<]O];]P]?]-].].].].].].].]-]E]G]R]S]D]C]H]C]H]C]H]C]H]C]<`=]Q]O]G]H]C]H]C]H]C]H];]6]L]?]T_4h9h9h9h9h9h9hK]Q].]J]A]J]A]J]A]J]"
"@].].].]/]J]@]L]@]J]A]J]A]J]A]J]A]J]?tG]Q\\U]@]L]?]L]?]L]?]L]>]Q];]K]?]Q]  N\\WmX]H\\WmX]H\\P_Q]H\\P^P]H\\O]P]C]1]Q]  C]:]S[ ?sEvEqAoC]L]?]L];^V^8^T^>x     "
" '] 5] 4]S]<g-\\T^V^M]S_Q\\ O](].\\2u Se =^1]J]7]-^*^?]O],^?^K]7^7]N]<^Sb  Sa (aC]3\\R\\K\\R\\P^O^?]L^A]-]E]F].]/]KdF]H]C].].]W^5].]T^W^T]H]R^T]D]C]Gj<]C]Gj-"
"`7]6]H]@]Q]:]U^S^U]Fb2]/^6]-^+]   Nj>]K]A].]K]@p?]0]K]?]L]?].].b3].]M]M]N]L]@]J]@]K]A]K]?].c4].]L]>]Q]:]U]V]U]@`6^S^4^5b2]&b<u P[O]P\\H]N^=]M]>^Ua<]J]="
"c7]L]<]S^8]V^:]L]@]A]J]S]S]@]P]>]S]S]@]J]B]J]9]6]J]?^O^7^7]/]C]H]P]P]G]H]B]R]R]F]C]Iz<]<z=]=z<] B]1]R[7j:\\L\\7_ C^P] B[U\\C[ W]T] W] O[R\\T^P[  T]   ]L]7"
"]U\\<]   H]T]-\\O\\X\\>\\I\\@\\O\\X\\J`3^O^>^O^>^O^>^O^>^O^=]O]<^P]?]-].].].].].].].]-]E]G]R^T]D]C]H]C]H]C]H]C]H]C];^<]R]N]G]H]C]H]C]H]C]H];]6]L]?]S`8j;j;j;j;j"
";j;|Q].pApApAp@].].].]/]J]@]L]@]J]A]J]A]J]A]J]A]J]?tG]R]U]@]L]?]L]?]L]?]L]>^S^;]K]?^S^  N\\WmX]H\\WmX]H\\QaR]H\\Q^O]H\\O]P]C]1^S^  D]9]T\\ ?sFwDo?nC]L]?]L];"
"]T]7]T]=]       Hj ?] 4]S]8d/]T]T]N^R_R\\ O](] =u Se =]0]J]7].^(]?]O]+]?^K]7]7]L]<gX]  Sa (aC]3\\R\\K\\R\\P]M]?]K]A]-]E]F].]/]D]F]H]C].].]V^6].]S]W]S]H]Q]T"
"]D]C]Gg9]C]G]Q_,^7]6]H]@^S^:]U]Q]U]G^X]2]0^5],]+]   Pl>]K]A].]K]@p?]0]K]?]L]?].].a2].]M]M]N]L]@]J]@]K]A]K]?]-f8].]L]>^S^:]U]V]U]?^4]S]4^4`0]$`<^Si O[O"
"\\O\\H]N^=]M^@^S`<]J]=c7]L]<]S]8^U]:]L]@]O]O]J]S]S]@]P]>]S]S]@]J]B]J]9]6]J]?]M]7]6]/^E^H]P]P]G]H]A]S]S]E]C]Iz<]<z=]=z<] B]1]R[7j:\\L\\6] A^Q] B[U\\C[Ni:]T]"
" V] O[R\\S]P[  T]   ]L]6\\U\\<]  Dh2]T]/]P\\W\\?]I\\A]P\\W\\K`2]M]>]M]>]M]>]M]>]M]>^O^=]O]?]-].].].].].].].]-]E]G]Q]T]D]C]H]C]H]C]H]C]H]C]<`=]S]M]G]H]C]H]C]H]"
"C]H];]6]M^?]R`;l=l=l=l=l=l=~Q].pApApAp@].].].]/]J]@]L]@]J]A]J]A]J]A]J]A]J]?tG]S]T]@]L]?]L]?]L]?]L]=]S]:]K]>]S]  M]P]P\\G]C\\G]ScS\\G]S^N\\G]P]P\\B]0]S]  D]"
"7\\T[ >sFwCn?mB]L]?]L];]T]7]T]=]       Hi >] 4]S]7[Xa1]T^T^O]P_T] O](] =u Se =]0]J]7]/^'^A]N]+]?^K]7]8^L^<eW]  Sd .dC]3\\R\\K\\R\\P]M]?]K]A]-]E]F].]/]D]F]H"
"]C].].]U^7].]ScS]H]Q^U]D]C]G]/]C]G]O^,^8]6]H]?]S]9]U]Q]U]H^W^3]1^4],]+]   Q`P]>]K]A].]K]@p?]0]K]?]L]?].].b3].]M]M]N]L]@]J]@]K]A]K]?]+e9].]L]=]S]9]V]T]"
"V]@_4]S]5_4b2]&b<\\Nd M[O]P\\H]N^=]L]@]Q_<]J]?e7]L];]T]8]T]:]L]@]O]O]J]S]S]@]P]>]S]S]@]J]B]J]9]6]J]?]M]8^6].]E]G]P]Q^G]H]A^T]T^E]C]Iz<]<z=]=z<] B]1]R[3]"
"1\\L\\6] A_R] B\\U\\E\\Ni:]T] V] O\\S\\R]R\\  T]   ]L]6\\U\\<]  Dh2]T]/\\O[V\\?\\H\\A\\O[V\\L`1]M]>]M]>]M]>]M]>]M]>]M]>^O]?]-].].].].].].].]-]E]G]Q^U]D]C]H]C]H]C]H]C]"
"H]C]=b>]T]L]G]H]C]H]C]H]C]H];]6]M]>]Qa>`P]>`P]>`P]>`P]>`P]>`P]>`PoQ].pApApAp@].].].]/]J]@]L]@]J]A]J]A]J]A]J]A]J]?tG]T]S]@]L]?]L]?]L]?]L]=]S]:]K]>]S]  "
"L\\P]P\\F\\C\\F\\T^W^T\\F\\T^M\\F\\C\\B]0]S]  E^7]U[ >sFwBl=kA]L]?]L]<^T^8^V^=]       Ij >] <u=[U^1\\S]R]O]O_U\\ N](] 1] Ge =]0]J]7]0_&]A]N]+]?^K]8^8]J]:aU\\  Pe 4"
"eA]3\\R\\K\\R\\Qo@]J]A].]F^F].].]E]F]H]C].].]T^8].]RaR]H]P]U]C]E]F].]E]F]N^,]8]6]H]?]S]9^V]Q]V^H^V^4]2_4],]+]   Q]M]>]K]A].]K]@],]0]K]?]L]?].].c4].]M]M]N]"
"L]@]J]@]K]A]K]?](d;].]L]=]S]9^W]T]W^@`5^U^5^/_3]'_8ZJ` K[O]P\\H]N^=]L]@]P];]J]@_0]L];]U^9^T^;]L]@]O]O]J]S]S]@]P]>]S]S]@]J]B]J]9]6]J]@^M^:^5].]E]F]Q]Q]F"
"]H]@^U]U^C]E]G_\"]\"_BZT]TZB_F_;] B]1]R[3]1\\L\\?o I_S] A[U]F[ V]T] W] N[S\\R]R[  S]   ]L]6\\U\\   ']T]/\\O\\V\\@\\H\\A\\O\\V\\M_0o@o@o@o@o?m>l>].].].].].].].].]-]F^"
"G]P]U]C]E]F]E]F]E]F]E]F]E]=d?^V]L]F]H]C]H]C]H]C]H];]6]N^>]O`?]M]>]M]>]M]>]M]>]M]>]M]>]M]?].].].].]-].].].]/]J]@]L]@]J]A]J]A]J]A]J]A]J] K]U]R]@]L]?]L]?"
"]L]?]L]=^U^:]K]>^U^  L\\P]Q]F\\D]F\\U^U^V]F\\U^M]F\\D]B\\/^U^  OuD]V[ =sFwBk;i@]L]?]L]<]R]7]V];]       F^   Nu=[T^3]S]R]O]N_V\\ N](] 1]   ].]L]6]1_%]Aq0]>]K]"
"8]7]J]/]  Md:u:d>]3\\R\\K\\S\\Po@]J]A].]F]E].].]E]F]H]C].].]S^9].]RaR]H]P^V]C]E]F].]E]F]M],]8]6]H]>]U^8]W^Q^W]H^U^4]2^3]+],]   R^M]>]K]A].]K]@],]0]K]?]L]?"
"].].]X_5].]M]M]N]L]@]J]@]K]A]K]?]$`;].]L]=^U^8]W]T]W]@b5]U]5^,]3]']  J\\Q_Q[G]N^=]L]A]O];]J]@].]L];]U]8]R];]L]@]O]O]J]S]S]@]P]>]S]S]@]J]B]J]9]5]L]?]K];"
"^4].^G^F]Q]Q]F]H]?_W]W_B]E]F_#]#_B\\U]U\\B_H_A\\U]U[ H]1]R[3]1]N]?o H`V] @[T]G[ U]T] X] N[S\\Q]S[  S]   ]L]6\\U\\   (]T]/]P\\U\\A]I]B]P\\U\\M^/o@o@o@o@o@o@m>].]"
".].].].].].].]-]F]F]P^V]C]E]F]E]F]E]F]E]F]E]>_X_?]W^L]F]H]C]H]C]H]C]H];]6]P_=]M^@^M]?^M]?^M]?^M]?^M]?^M]?^M]?].].].].]-].].].]/]J]@]L]@]J]A]J]A]J]A]J]"
"A]J] K]U\\Q]@]L]?]L]?]L]?]L]<]U]9]K]=]U]  K]Q]Q]F]E]F]W^S^W]F]W^L]F]E]B\\.]U]  NuC\\V[ =eXZXdFgXhAi9h@]L]?]L]<]R]7]V];]       E]   Nu=[S]3\\R]R]O]M_X\\ M]("
"] 1]   ].]L]6]2_$]Aq0]>]K]8]7]J]/]  Ke=u=e<]3\\R\\K\\S\\Po@]J]A].]F]E].].]E]F]H]C].].]R^:].]RaR]H]O^W]C]E]F].]E]F]M^-]8]6]H]>]U]7]W]O]W]I^S^5]3^2]+],]   R"
"]L]>]K]A].]K]@],]0]K]?]L]?].].]W_6].]M]M]N]L]@]J]@]K]A]K]?]\"_<].]L]<]U]7]W]T]W]Ac5^W^6^+^4](]  H[R\\X]S\\G]N^=]L]A]O];]J]A^.]L]:]W^9^R];]L]@]O]O]J]S]S]@"
"]P]>]S]S]@]J]B]J]9]5]L]?]K];^4]-]G]D]R]R]E]H]>kA]E]E_$]$_B^V]V^B_J_A^V]V] I]1]R[3]0\\N\\>o G`X] ?\\U_Q[T\\ T]T] ] N\\T\\Q]T\\  S]   ]L]6\\U\\   )]T].\\P\\T\\A\\I]A"
"\\P\\T\\N^.o@o@o@o@o@o@m>].].].].].].].].]-]F]F]O^W]C]E]F]E]F]E]F]E]F]E]?_V_@]W]K]F]H]C]H]C]H]C]H];]6k<]L^A]L]?]L]?]L]?]L]?]L]?]L]?]L]?].].].].]-].].].]/"
"]J]@]L]@]J]A]J]A]J]A]J]A]J] K]V\\P]@]L]?]L]?]L]?]L]<^W^9]K]=^W^  J]R]R]D]G]D]W\\Q\\W]D]W\\L]D]G]A\\.^V]  NuC]W[ <cWZXdEfXh@g8g?]L]?]L]=^R^8^X^:]       F]  "
" G\\R\\5[S]4]R]R]O]Lb M](\\ 0]   ].]L]6]3_#]Aq0]>]K]9]6]J]/]  He@u@e H\\R]M]T]Q^J]A]J]@]/]G^E].]-]F]F]H]C].].]Q^;].]Q_Q]H]N]W]B]G]E]-]G^F]L]-]8]6]I^>^W^7]"
"W]O]W]I^R^6]4^1]+],]   R]M^>^M^@]/^M^?]-]0^M^?]L]?].].]V_7].]M]M]N]L]@^L]?^M^A^M^?] ]<].]L]<]U]7]X]R]X]B^W^5]W]6^)]4](]  H\\T]W]U\\F]O_=]L]A]P^;^L^A]-]L"
"]:]W]8]P]<]L]@]O]O]J^T]T]?]P]>]S]S]@^L]A^L]8]5]L]@^J]=^3]-^I^D^S]S^E]H]<g>]G]C_%]%_A_W]W_A_L_@_W]W_ J]0]S[3]0]P]5]4],b =[ThT[ R]T]!] M[T\\P]U[  R]   ]L"
"]6\\U\\   *]T].]P[S\\B]J]A]P[S\\N].^J]B^J]B^J]B^J]B^J]B^K^A]M]=]/].].].].].].].]-]G^F]N]W]B]G]D]G]D]G]D]G]D]G]?_T_AbK]E]I^C]I^C]I^C]I^;]6j;]K]A]M^?]M^?]M^"
"?]M^?]M^?]M^?]M_?].].].].].].].].]/]J]@]L]@^L]@^L]@^L]@^L]@^L] J^X]Q]?]L]?]L]?]L]?]L];]W]8^M^<]W]  I]R]S]C]H]C]VZOZW]C]VZL]C]H]@\\-]W]  MuC]X[ ;cWZWbDe"
"WZXe>e6e>]L]?]L]=]P]8^X^:]       F^   H\\R\\5[S]5]Q]R]O^L` K]*] 0]  !^.]L]6]4_\"]2],^>^M]8]6]J]0]  DeCuCe E]R\\M]T\\P]I]A]J]@]/]G]D].]-]F]F]H]C].].]P^<].]Q"
"_Q]H]N^X]B]G]E]-]G]E]L^.]8]5]J]<]W]6^X]O]X^J^Q^6]5^0]+^-]   R]M^>^M]?].]M^?]-]/]M^?]L]?].].]U_8].]M]M]N]L]?]L]?^M]?]M^?] ]<].]M^<^W^6aRbB^V^6]W]7^(]4]"
"(]  GcUcE]P_=]L]A]P]9]L]@]-]L]:^X]9^P]<]M^@]P^O]I]T]T]?]P]>]S]S]@^L]@]L]8]5]M]?]I]>^2],]I]B_U]U_D]H]:c<]G]B_&]&_?_X]X_?_N_>_X]X_ I]0]S[3]0_T_5]4]+` ;["
"SfU[ P^U^#] L[U\\P]V[  Q]   ]M^6\\U\\   ,^U^-\\P\\S\\B\\J]@\\P\\S\\N].]I]B]I]B]I]B]I]B]I]B]I]B^M]=]/].].].].].].].]-]G]E]N^X]B]G]D]G]D]G]D]G]D]G]@_R_A`J]D]J]A]J"
"]A]J]A]J]:]6g8]K]A]M^?]M^?]M^?]M^?]M^?]M^?]M_?].].].].].].].].].]L]?]L]?]L]?]L]?]L]?]L]?]L]3^;aP]?]M^?]M^?]M^?]M^;]W]8^M];]W]  H]S]T^B]J^B]J^B]J^B]J^@"
"\\-]W]  G^1_ :aW[V`BcW[Wc<d5c=]L]>]N]<]P]7]X]8]       F]KZ   X]S]5[S]5\\P]R]N]K_ K]*] 0]  !],]N]5]5_\"]1],]<]M]9^6^L^0]  Ad Nd A\\R]O^U\\P^I^B]K^?]H[C]H^D]"
".],]G]F]H]C].].]O^=].]P^Q]H]M]X]A]I]D],]I^E]K]AZH^8]5]J]<]W]5bObJ^O^7]6_0]*]-]   R]M^>^M]?^/]M^?^.]/]M^?]L]?].].]T_9].]M]M]N]L]?]L]?^M]?]M^?] ]<].]M^;"
"]W]5aRaB^U^6c8_(]4](]  FaSaD]P_=]M]@]P]9]L]@]-]L]9b9]O^=^N^?\\P_Q]H]T]T]?]P]=]T]T]?^L]@]L]8]4]N]@^I^?]1],^K^A`W]W`C]H]7]8]I]@^&]&^=i=^N^<i H]0^T[3]1l6]"
"4])_ <\\RbT\\ O]T]#] L\\V\\O]X\\     M^N^6\\U\\   ,]T]-\\OhF\\J]@\\OhQ]/^I^D^I^D^I^D^I^D^I^C]I]B]L]<]H[C].].].].].].].]-]H]D]M]X]A]I]B]I]B]I]B]I]B]I]@_P_B_J]C]J"
"]A]J]A]J]A]J]:]6].]K]A]M^?]M^?]M^?]M^?]M^?]M^?]M_?^/^/^/^/^/].].].].]L]?]L]?]L]?]L]?]L]?]L]?]L]3^;`O]?]M^?]M^?]M^?]M^;c8^M];c  G^U]U^@^M^@^M^@^M^@^M^?"
"\\-c  H^0_ 9^U[U^@aV[Va:b3a<]L]>^P^=^P]7]X]8_       H^M[ F] 6]S]>ZQ[T^6]P]S^N^K^ K]*] 0]:] 8]0],]O^5]6_2ZI]1]-^<^O^9]4]L]0]<].] Uc Pc1]2\\Q^S`W^P]G]B]K]"
">^J\\C]I^C].],^H]F]H]C].].]N^>].]C]H]MbA^K^D],^K^D]K^B[I]7]5^L^<c5aMaJ^N]7]6^/]*]-]   R^O_>_O]=].]O_>].].]O_?]L]?].].]S_:].]M]M]N]L]>]N]>_O]=]O_?] ]<]-"
"]O_;]X^5aRaC^S^6a8_']4](]  D]P^B^Ra>^N]@]Q]7]N]?^.]L]9a8]N]=^N^?]Q_Q]G]U]U]>]P]=]T]T]?_N]>]N]7]4^P^@]G]@^1]+^M^?mB]H]7]8^K^?\\%]%\\;g;\\L\\:g G]/]T[3]2n7]"
"4]'^ <\\F\\ M\\S\\  J\\F\\     L^N^6\\U\\   ,\\S\\-]OhG]K]@]OhQ]LZ=]G]D]G]D]G]D]G]D]G]D]G]D^L]<^J\\C].].].].].].].]-]J_D]MbA^K^B^K^B^K^B^K^B^K^A_N_B^K]B^L^A^L^A^"
"L^A^L^:]6].]K]A^O_?^O_?^O_?^O_?^O_?^O_?^Oa?].].].].]/].].].]-]N]>]L]>]N]=]N]=]N]=]N]=]N]2^;_O]=]O_>]O_>]O_>]O_:a7_O]9a  E^P_>^P_>^P_>^P_>^P_>\\,a  H^.]"
" /[5]T[S\\8a1`<]L]=^R^<]O^8b7_       H^O\\ F] 6\\R\\=[R[U^5\\N]T]L^M` L]*] 0]:] 8]1^+]P]4]7_1[L_1]<ZL^:^Q^8]4^N^>ZM];].] R` P`.]2]QfXaN]G]B]L^=^L]C]K_B].]+"
"_J]F]H]C].].]M^?].]C]H]La@^M^C]+^M^C]J]B]L^7]4^N^:a4aMaK^M^8]7^.]*^.]   Q]P`>`Q^=^NZ;^Q`>_LZ>].^Q`?]L]?].].]Q^;].]M]M]N]L]>^P^>`Q^=^Q`?]/ZL];]-^Q`:a4`"
"P`D^Q^7a8^&]4](]   S]Sb>_P^@]R^7^P^>^MZ<]L]9a9]M]=_P`XZB]Q_Q]G^V]V^>]P]=^U]U^?`P^>^P^6]4]Q^?]G]A^0]*^O^<i@]H]7]7^M^=Z$]%Z8e9ZKZ7e F]/^U[TZ9]3^V`V^8]4]"
"&^ <\\H\\ K[R[  I\\H\\     K_P`XZ9\\U\\   ,[R[,\\E\\D\\K]?\\E\\M]O\\=]G]D]G]D]G]D]G]D]G]D]G]D]K];^L]C].].].].].].].]-]K_C]La@^M^@^M^@^M^@^M^@^M^A_L_C`N^A^N^?^N^?^"
"N^?^N^9]6].]L]?]P`>]P`>]P`>]P`>]P`>]P`>]P]X^LZN^NZ;_LZ>_LZ>_LZ>_LZ?].].].]-^P^>]L]>^P^=^P^=^P^=^P^=^P^2^:^P^=^Q`>^Q`>^Q`>^Q`:a7`Q^9a  Dk<k<k<k<k>],a  "
"H]-] /[,[._0_;]L]=j<]N]7`5a       J_S^ F] 6\\R\\=^U[W_5]N^V^K_Rd L],] /]:] 8]1])^T^3]8_0^Q`0]<]Q_8^S^8^3_R_=]R^:].] O] P]+]1\\PdW`N^G^C]N_;`R`C]NaA].]*`O"
"`F]H]C].].]L^@].]C]H]La?`S`B]*`S`B]J]B`Q_6]3_R_9a4aMaL^K^9]8^-])].]   Q_Tb>aS^;_R\\:^Sa=`Q]>]-^Sa?]L]?].].]P^<].]M]M]N]L]=_T_=aS^;^Sa?]/^R_:]-^Sa:a3_P_"
"C^P^7_8^%]4](]   S_V^X^?aS^>]T^5_T_=`R]<]L]8_8]M^>`SdA]SaS]E^W]W^=]P^=_W]W_>]X]T_<_T_5^4^T^?^G^C^/])^Q^8c=]H]7]6`S` ?] ;c >c E]._W[V\\9]4^J^9]4]%] ;]L]"
" IZQZ  H]L] !u  ,`Sd9\\U\\   ,ZQZ,]E\\E]L]?]E\\M_S^>^G^F^G^F^G^F^G^F^G^F^G^F^K]:`R`C].].].].].].].]-]ObB]La?`S`>`S`>`S`>`S`>`S`?]J]CcS`?_R_=_R_=_R_=_R_8]6"
"].]V[R^?_Tb>_Tb>_Tb>_Tb>_Tb>_Tb>_T^V_Q]M_R\\:`Q]=`Q]=`Q]=`Q]?].].].],_T_=]L]=_T_;_T_;_T_;_T_;_T_1^:`T_;^Sa=^Sa=^Sa=^Sa9_6aS^7_  Bi:i:i:i:i=]+`  I],] /["
",[-].]:]L]<h;]N]7`3q      \"h E] 7]S]=k5]LdIjW^ M],] /]:] 8]1](f9k?n?l/]<j6g7]1j<h9].] LZ PZ(]1]O`U]K]E]Cm8kBn?n?](nE]H]C].].]K^Am>]C]H]K`>kA])kA]J^Cm5"
"]2j7_2`M`K^J]9]8tC])].]   PgX]>]Xf9h9fX]<k>],fX]?]L]?].].]O^=].]M]M]N]L]<h<]Xf9fX]?]/j9d4gX]:a3_P_D^O^7_8m4]4](]   RfXaBk=^V^3h;j<]L]8_9^L]>qA^U]W]U^D"
"i<]O`?k=]Xg:h3a7f>uCn?]/eSe;]:]H]7]5k >] :a <a D]-h>n?\\H\\8]4]%] 9^R^   *^R^  Xu  ,q9\\U\\    /]D\\F]LfH]D\\Li>]E]F]E]F]E]F]E]F]E]F]E]F]JnIkBn?n?n?n?].].]."
"]-n@]K`>k<k<k<k<k=[H[Co<j;j;j;j7]6].]Vf=gX]=gX]=gX]=gX]=gX]=gX]=gTjLh9k<k<k<k?].].].]+h<]L]<h9h9h9h9h Fk:gX]=gX]=gX]=gX]9_6]Xf6_  @e6e6e6e6e;]+_  G\\+["
" /].]-[,[9]L];e:^N^8`2p       e D] 7]S]<i4\\JbGgT^ M\\,\\ .]:] 8]1]'d8k?n>i-]<i4e6]0h;g8].]   I]0]3]E]Cl6h@l=n?]&jC]H]C].].]J^Bm>]C]H]K`<g?]'g?]I]Bj3]1h6"
"_2_K_L^I^:]8tC])].]   OdV]>]Wd6f8dW]:i>]+dW]?]L]?].].]N^>].]M]M]N]L];f;]Wd7dW]?]/i7c3dV]9_2_P_E^M^8_8m4]4](]   QdV`B]Xe;d1f8h<]L]8_9]K]>]XdW_@eWeBg;]O"
"`=g;]Vd8f1`6d=uCn?]/eSe;]:]H]7]3g <] 9_ :_ C]+f>n>ZFZ7]4]%] 7f   &f  Vu  ,]XdW_9\\U\\    /\\C\\F\\KfH\\C\\Kg=]E]F]E]F]E]F]E]F]E]F]E]F]JnHh@n?n?n?n?].].].]-l>"
"]K`<g8g8g8g8g J]Vh:h9h9h9h6]6].]Ve;dV]<dV]<dV]<dV]<dV]<dV]<eRiJf7i:i:i:i?].].].]*f;]L];f7f7f7f7f F]Xe7dV]<dV]<dV]<dV]9_6]Wd5_  <\\-\\-\\-\\-\\6]+_  FZ*[ /]"
".],Z+Z9]L]8`8]L]7^.m       W` A] 7\\R\\7b2]H^BaP_ O].] .]:\\ 7]2^%`6k?n:b*]9c/a5],b6b5].\\   H]/\\4]C]Di0b=h9n?]#c?]H]C].].]I_Dm>]C]H]J_9a<]$d?]I^?c0].b3_2"
"_K_M^G^;]8tC](]/]   M`T]>]U`2b4`U]7c;])`U]?]L]?].].]M^?].]M]M]N]L]8`8]U`3`U]?],c2a0_T]9_2^N^F^K^8]7m4]4](]   O`R^B]Va8b-`3d:]L]7]9^J]?]V`T]>cUc?c9]N_:"
"a8]T`3`-_4`<wDn?]/eSe;]:]H]7]0a 9] 8] 8] B])b<n @]4]&^ 5b   \"b  Tu  ,]V`T]8\\U\\    0].].]0b;]C]H]C]H]C]H]C]H]C]H^E^H^JnEb=n?n?n?n?].].].]-h:]J_9a2a2a2a"
"2a G\\Rb4b3b3b3b3]6].]Vc7`T]:`T]:`T]:`T]:`T]:`T]:aMcEb2c4c4c4c<].].].]'`8]L]8`1`1`1`1` D]Ua2_T]9_T]9_T]9_T]8]5]U`2]      =]                       &[   "
"O].]  E]  E]         ']    S]        R]      ^       (](]/]        C]  S]    '] V]      F^ 7]4](]   %])[  4]7] @])_Q_:] 9]6]                6[   S]0[R"
"^           H]%\\U\\ A\\            @\\             /Z            <\\             ,[    M^5](^      =]                       &[   N]0]  D\\  D]         '\\  "
"  Q^DZ       1]      _       )](]/]        D^  S]    '] V]      F] 6]4](]   %]   ;]7] @] /] 9]6]                6[   S]0g           H]%\\U\\ @\\         "
"   @\\                          J\\                  X]4](]      <]                       &[   N]0]  D\\  E^         '\\    P^G]       2]      X^       )]"
"(^0]        D]  R]    '] V]      G^ 6]4](]   %]   ;]7] @] /] 9]6]                6[   S]0e           F]%\\U\\ ?[            ?[                          "
"I[                  ^4])^      @ZV]                       &[   M]2]  D]  E]         ']    O_K_       3]      V^       *b,]5b        E^  R]    '] V]   "
"   G^ 6^5])^   %]   ;]7] @] /] 9]6]                6[   S].a           D]%\\U\\ ?\\            @\\                          J\\                 !^4])^     "
" B\\V]                       &[   M]2]  D\\            G\\    L`P`       2]      U^       +b =b        RZN^  R^    '] V]      H^ 4^6]*^   $]   ;]7] @] /]"
" 9]6]                6[   S]            J]  :\\            @\\                          J\\                 \"^3]*^      A\\V\\                       %[   L"
"]4]                   Vm       2^      S^       ,b =b        R\\Q_  R]    &] V]      I^ 3b:].b   $]   ;]7] @] /] 9]6]                6[   S]           "
" J]  @ZU]            FZU]                          PZU]                 #^2]+^      @b                       %[                       Si       4b     "
"                  %i  Ua    &] V]      Mb 2a:].a   #]   ;]7] @] /] 9]6]                   .]            J]  @b            Fb                          "
"Pb                 'b2]       E`                                               Qb       1a                       $g  S`    %] V]      Ma /_:]._   !]  "
" ;]7] @] /] 9]6]                   .]            J]  @a            Ea                          Oa                 &a1]       D^                       "
"                                X^                 Ip      Fc  Q^    #] V]      M_  A]    )]   ;]7] @] /] 9]6]                                T]  @`  "
"          D`                          N`                 %_/]       BZ                                                                        Ap      "
"                 6]                                                                                                                                   "
"                                                        p                       6]                                                                    "
"                                                                                                                                                      "
"                                                F]']2]    +]']2^ D]']3_   E]']1]   \"]']2^ 8]                             H";

    // Define a 90x103 font (huge size).
    static const char *const _data_font90x103[] = {  // Defined as an array to avoid MS compiler limit about constant string (65Kb).
      // Start of first string.
"                                                                                                                                                      "
"                                                                                                                                                      "
"                                                                        HX     4V         >X       IX           *W             FW                     "
"                                                                                                                                                      "
"                                                                                                                                                      "
"                                                                                                                     HX  W 4Z 3VCT   <Z     >X  W 4Z  "
" HX  W 4Z     'VCT ;X  W 3Y 2UCT       KX  W 3Y   0W                                                                                                  "
"                                                                                                                                                      "
"                                                                                                                                                      "
"                                    @W !W 4\\ 5YET ?XHX 8]     >W !W 4\\ 7XGX KW !W 4\\ 7XHX   +YET :W !W 3[ 5ZFT ?XGX     EW !W 3[ 7XGX 5W              "
"                                                                                                                                                      "
"                                                                                                                                                      "
"                                                                                                                        >W \"V 3\\ 7]HU ?XHX 9`     ?W \""
"V 3\\ 7XGX JW \"V 3\\ 7XHX   -]HU 9W \"V 3] 7]HT ?XGX     DW \"V 3] 8XGX 5V                                                                                "
"                                                                                                                                                      "
"                                                                                                                                                      "
"                                                      <W $V 3VNV 8_KV ?XHX 9`     >W $V 3VNV 8XGX IW $V 3VNV 8XHX   -_KV 8W $V 2] 7_KU ?XGX     CW $V "
"2] 8XGX 6V                                                                                                                                            "
"                                                                                                                                                      "
"                                                                                                                                                :W &W "
"4VLV :j >XHX :VJV     >W &W 4VLV 9XGX HW &W 4VLV 9XHX   .j 6W &W 3VMV 9i >XGX     BW &W 3VMV 9XGX 7W               MW                                 "
"                                                                                                                                                      "
"                                                                                                                                                      "
"                                                                                      CV 'W 4VJV ;j >XHX ;UGV     >V 'W 4VJV :XGX GV 'W 4VJV :XHX   .j"
" 5V 'W 3VKV :i >XGX     AV 'W 3VKV :XGX 8W               N[                                                                                           "
"                                                                                                                                                      "
"                                                                                                                                                      "
"                            DV )W 4VHU <VK_ =XHX ;TEU     =V )W 4VHU :XGX FV )W 4VHU :XHX   /VK_ 3V )W 3VIV <UK_ =XGX     @V )W 3VIV ;XGX 9W          "
"     N]                                                                                                                                               "
"                                                                                                                                                      "
"                                                                                                                              DV *V 3UFU =UH\\ <XHX <UD"
"T     <V *V 3UFU ;XGX EV *V 3UFU ;XHX   /UH\\ 1V *V 2UGU <TH] =XGX     ?V *V 2UGU ;XGX 9V               a                                              "
"                                                                                                                                                      "
"                                                                                                                                                      "
"                                                                         EV ,V 3UDU >TEY ;XHX <TBT     <V ,V 3UDU <XGX DV ,V 3UDU <XHX   /TEY /V ,V 2U"
"EU =TFZ <XGX     >V ,V 2UEU <XGX :V               Na                                                                                                  "
"                                                                                                                                                      "
"                                                                                                                                                      "
"                     DU -V 3VDV ?TCV :XHX <TBT     ;U -V 3VDV =XGX CU -V 3VDV =XHX   /TCV -U -V 2UCU >TCU :XGX     =U -V 2UCU =XGX ;V               NV"
"IV                                                                          \"W                                                                        "
"                                                                                                                                                      "
"                                                                                                                          JU /V 3VBV     ETBT     :U /"
"V 3VBV   FU /V 3VBV       (U /V 2UAU         DU /V 2UAU   @V               NVGV                                                                       "
"   $X                                                                                                                                                 "
"              *X                                                                                                                                      "
"                           JX                                GTBT                                                   MX  GX 7V     :UEU     DX  GX 7V  "
" JX  GX 7W       4X  GX 6V         GX  GX 5V   (X                            &X                                                                       "
"                                                                                        )X                                                     8V     "
"                                                                                                      ;X                                FTBT          "
"                                         LX  IX 7X     <UCU     DX  IX 7X   JX  IX 6W       3X  IX 6X         GX  IX 5X   *X                          "
"  &Y                                                                                                                                                  "
"             (X                                                     9V                                                                                "
"                           <X                                ETBT                                                   KX  KX 6X 1TBT   BTAT     CX  KX 6"
"Y   JX  KX 6Y     (TBT BX  KX 5X 1TBT       LX  KX 4X   +X                            %T                                                    #W 9W     "
"                                                                                          3a   :a     <W   2W    >W   E\\   AW ,W ,W ,W ,W             "
"                HY GV +Y         4Z           NX                 @X                                                                  %W               "
"                 DUDU                                                 =Y 7W  KW 6Z 4XDT   BTAT     BW  KW 6Z   IW  KW 6[   ,Y )XDT AW  KW 5Z 4XDT     "
"  KW  KW 4Z   ,W BW                 8V         (S                                             <S       9V 7V                                          "
"                                                     3a   :a     ;W   3W    >W   H_   AW ,W ,W ,W ,W                             L] GV +]         ;a  "
"        #[                 F^                                           8XGX                      +W                                BTEU              "
"                      *R            9a :W  MW 6\\ 6ZET ?XHX <TAT     AW  MW 6\\ 7XGX LW  MW 5[ 7XGX .Y +ZET @W  MW 5\\ 6ZET ?XHX     DW  MW 4\\ 7XHX 0W AW"
" &XHX               MZ         +T                                   $Y         BS 1W,V MY   8W 7W  T           9X   5Z /[     0Z   8Z /Y           GY "
"      .\\       <\\               [   4[   :\\              -a   :a     :W   4W    >W   Ja   AW ,W ,W ,W ,W                             N_ GV +_         "
"?e   8]       J]                 Jb       8[       <[                  $Y       FY 7XGX   =Z         Di 5W   8Z .Y !W         FW *Y   4W)V*W)V-Y(V    "
"        <UFU   3\\                    +[ 0[ 0[ 0[ 0[   4[=T            <e ;W  W 5\\ 7\\FT ?XHX <TAT     @W  W 6^ 8XGX KW  W 5] 8XGX .Z@R ?\\FT ?W  W 4\\ 7\\"
"FT ?XHX     CW  W 3\\ 7XHX 1W @W &XHX               N\\         ,T     :U :U5U                            `   EX 2VFV   .S 4]0W\"b DV  V 5V  T         7W"
" .` 3[ 7c 8d )Z Dq 8b Hy Bb 7`           Na   /Z @k .d Kj ?x Mt 7f MX/X'X -X -X2Z&X -]0]0[3X Dc Ii -c Ij 4f N~W$X/X.X&X.X4Y4XDY/Y/Y,Y'~S%a >W $a  MY  "
" EW   5W    >W   Kb   AW ,W ,W ,W ,W                            !a GV +a         Ch   =f       ^                 Mf 2Z @x Mx <c 3X C~Q)X?X?X Kc   2T  "
" .V   .T   CX   $a  !W.W   N` ;XGX ![ Lb       &Z Mi 7[   >a 5a &W   0g    #\\ -_   <\\*V.\\*V0a-V\"X )Z /Z /Z /Z /Z 4WJV 1~U+d Kx Mx Mx Mx MX -X -X -X ,j"
" @[3X Dc 8c 8c 8c 8c   <cBV.X/X'X/X'X/X'X/X/Y,Y$X &h ;W \"W 5VNV 8]HU ?XHX <TAT     ?W \"W 5VNV 8XGX JW \"W 5VMV 9XGX -ZDV @]HU >W \"W 4VNV 8]HU ?XHX     "
"BW \"W 3VNV 8XHX 2W ?W &XHX               ^ K~\\       >S   3Q +[ @[;[ ;Q                          ;e   HX 2VFV #VBV FS 6`1V#g GV !V 3V !T         7W 0d"
" :` ;j ?k -[ Dq :g Ky Df ;d          $f   1Z @o 5j Np Ex Mt :m\"X/X'X -X -X3Z%X -]0]0\\4X Gi Lm 4i Ln ;m#~W$X/X-X(X-X4Y4XCY1Y-Y.Y&~S%a >W $a  N[   EV   "
"5W    >W   Lc   AW ,W ,W ,W ,W                            \"b GV +a         Dk   Aj      \"_                 h 3Z @x Mx ?i 6X C~Q)X?X?X Ni   6V   /V   /"
"V   DX   &f  #W0W   e >XGX %c#e       +b\"i 9_   Be 9d 'V   3k    %^ /c   @^*V0^*V2d.V\"X )Z /Z /Z /Z /Z 3b 1~U.j Nx Mx Mx Mx MX -X -X -X ,p F\\4X Gi >i "
">i >i >i   BiEV.X/X'X/X'X/X'X/X.Y.Y#X 'j ;V \"V 5VLV :_IT >XHX <TAT     >V \"V 5VLV 9XGX IV \"V 4VMV 9XGX ,ZHY A_IT <V \"V 4VLV :_IT >XHX     AV \"V 3VLV 9"
"XHX 2V >W &XHX              !_ K~[       >T   4R -_ D_?_ >S         =t                Fh   IX 2VFV #VBV FS 7c4V#i HV \"W 3V !T         7V 0f @e >o Co 0"
"\\ Dq <j Ly Fj ?h          (i  \\ ?Z @r :o\"s Hx Mt <q$X/X'X -X -X4Z$X -]0]0\\4X Im Np 9m Np ?q%~W$X/X-X(X,W5[6XAX1X+X.X%~S%a =V $a  ]   EV   6W    >W   M"
"d   AW ,W ,W ,W ,W               HW             1b GV +b         Fm   Dm      #`                \"j 4Z @x Mx Am 8X C~Q)X?X?X!m   9X   0V   0X   EX   'h"
"  $W0W  \"h ?XGX 'g%g       0h%i :a   Cf :f *V   4m    %^ 0e   A^+V/^+V1f1V!X )Z /Z /Z /Z /Z 2` 1~V0o\"x Mx Mx Mx MX -X -X -X ,t J\\4X Im Bm Bm Bm Bm   F"
"mHV-X/X'X/X'X/X'X/X-X.X\"X (l ;V $V 4UJU :ULXLU >XHX <UCU     =V $V 5VJV :XGX HV $V 4VKV :XGX +ZL\\ AULXLU ;V $V 3UJU :ULXLU >XHX     @V $V 2UJU 9XHX 3V"
" =W &XHX              !` K~Z       >T   4S /a FaAa @T         @w                Hl   KX 2VFV $WCV ES 8e5V$j HV \"V 1V \"T         7V 2j Eh ?q Dp 1\\ Dq >"
"l Ly Hn Bj          +l %e E\\ At >s$v Kx Mt >u&X/X'X -X -X5Z#X -^2^0]5X Jo q ;o r Br%~W$X/X-X(X,X6[6XAY3Y+Y0Y%~S%W 3V  IW !_   FW   7W    >W   Md   AW "
",W ,W ,W ,W               HW             2[ ?V #[         Hn   En      #`                #l 6\\ Ax Mx Cp 9X C~Q)X?X?X\"o   ;Z   1V   1Z   FX  KS 0i  #W2"
"W LV ,i ?XGX *l'h       3l'i ;c   Dg ;g ,W   6o    %^ 1g   B^,V.^,V0g3V X *\\ 1\\ 1\\ 1\\ 1\\ 2^ 0~V2s$x Mx Mx Mx MX -X -X -X ,v L]5X Jo Do Do Do Do   HpKW"
"-X/X'X/X'X/X'X/X-Y0Y\"X )n <W &W 5VJV ;TI_ >XHX ;UEU     <W &W 5VIV ;XGX HW &W 5VIV ;XGX *g ?TI_ ;W &W 4VJV ;TI_ >XHX     @W &W 3VJV :XHX 4W =W &XHX   "
"  1\\ 1\\ 1\\ 1\\ 1\\ =XMV K~Y       =S   4U 1c IdCc AU         Dz                In   LX 2VFV $VBV ES 9g7V$k HV #W 1W #T         8W 3l Fh ?r Eq 3] Dq ?m L"
"y Ip Em          -n )k H\\ Au Av%x Mx Mt ?x(X/X'X -X -X6Z\"X -^2^0]5X Ls\"s ?s\"s Et%~W$X/X,X*X+X6[6X@Y5Y)Y2Y$~S%W 3W  JW \"a   FW   8W    >W   NZ   6W ,W "
",W ,W ,W               HW             2X <V  X         H[G[   Go       KZ                %[H[ 7\\ Ax Mx Ds ;X C~Q)X?X?X$s   >\\   2V   2\\   GX  KS 1j  #"
"W2W LV -j ?XGX +ZEZ)VGY       5ZDZ)i <e   EUFY <UFX -W   7q    %VMU 2YIY   CVMU,V.VMU,V0UFX3V X *\\ 1\\ 1\\ 1\\ 1\\ 1\\ 0~W4v%x Mx Mx Mx MX -X -X -X ,x N]5X"
" Ls Hs Hs Hs Hs   LsMW,X/X'X/X'X/X'X/X,Y2Y!X *\\G[ <W (W 4UHU <UH] =XHX ;VGV     ;W (W 5VHV ;XGX GW (W 4UGU ;XGX )c =UH] 9W (W 3UHU <UH] =XHX     ?W (W"
" 2UHU :XHX 5W <W &XHX     5c 8c 8c 8c 8c @WKU J~X       >T   5V 2e KfEe CW         G|                Jp   MX 2VFV $VBV ES 9XIX8V$l HV #V /V #T        "
" 8V 3n Gh ?s Fr 5^ Dq @n Lx Ir Go          .o -q L^ Bv Cx&z x Mt A{)X/X'X -X -X7Z!X -^2^0^6X Mu#t Au#t Gu%~W$X/X,X*X+X6[6X?X5X'X2X#~S%W 2V  JW #c   FW"
"   9W    >W   NX   4W ,W ,W ,W ,W               HW             2W ;V  NW         IZCY   Hp       JY                &ZDZ 9^ Bx Mx Eu <X C~Q)X?X?X%u   @"
"^   3V   3^   HX  KS 2k  \"W4W KV -ZGW ?XGX -X=X+R@W       8X<X  .XIX   FQ@W <Q@W /W   7dGU    %QHU 3XEX   DQHU-V-QHU-V/Q@W5V NX +^ 3^ 3^ 3^ 3^ 2\\ 0~W5"
"x&x Mx Mx Mx MX -X -X -X ,z!^6X Mu Ju Ju Ju Ju   N}+X/X'X/X'X/X'X/X+X2X X +ZBY ;W *W 4UFU =TF\\ =XHX :VIV     9W *W 5VFV <XGX FW *W 4VGV <XGX (_ :TF\\ 8"
"W *W 3UFU =TF\\ =XHX     >W *W 2UFU ;XHX 6W ;W &XHX     7h =h =h =h =h DWJV K~X       >T   5W 4g MgFg EY         J~                K]FZ   MX 2VFV $VBV "
"ES :XGX9V%\\GX HV $W /W 3PATAP         GV 3[H[ Gh ?]F] GZE^ 6^ Dq A]FX Lx I\\F\\ G\\G[          /[H] 0u N^ Bw E_D^&{!x Mt B`C_)X/X'X -X -X8Z X -_4_0_7X N^"
"E^$u C^E^$u H^E\\%~W$X/X,Y,Y*W7]8X>Y7Y'Y4Y#~S%W 2V  JW $e   FV   9W    >W   NW   3W ,W ,W ,W ,W               HW             2W ;V  NW         IY@X >X "
"4[AV       IX                &X@X 9^ Bx Mx F^E^ =X C~Q)X?X?X&^E^   B`   4V   4`   IX  KS 3\\GW  \"W4W KV .YBT ?XGX .V7V,P=W       :W8W  /VEV   3V +V /V "
"  7eGU     KU 3WCW   ;U-V$U-V LV5V NX +^ 3^ 3^ 3^ 3^ 3^ 1~W6_D^&x Mx Mx Mx MX -X -X -X ,{\"_7X N^E^ L^E^ L^E^ L^E^ L^E^  !^Ed*X/X'X/X'X/X'X/X+Y4Y X +Y?"
"X ;V *V 4UDU >TEZ <XHX 9a     7V *V 4UDV =XGX EV *V 4VEV =XGX )] 7TEZ 6V *V 3UDU >TEZ <XHX     =V *V 2UDU <XHX 6V :W &XHX     9k @k @k @k @k EWJV K~W "
"      >T   5Y 5g MhHi G[         M~Q                L\\AW   MX 2VFV $VCV DS :WEW:V%ZAU HV $V -V 3RCTCR         HW 4ZDZ H\\LX ?Y?[ HV>\\ 8_ DX )[?T -Y J[B"
"[ I[CZ          0WAZ 2x ^ BX>^ G]=Z&X=b#X -X '];[)X/X'X -X -X:[ NX -_4_0_7X \\?\\%X@^ E\\?\\%X?] J[=X =X <X/X+X,X)X8]8X=Y9Y%Y6Y )Y$W 2W  KW %ZMZ   FV   :W"
"    >W   X   3W     4W ,W               HW             3X ;V  NX         KY?X Ca 9Y:R       HX                (X>X :VNV BZ /X '\\?\\ A^ FX0X)X?X?X'\\?\\  "
" Db   5V   5b   JX  KS 3ZBT  !W6W JV .X?R   4V4U HV       ;V4V  1VCV   4V *U 0V   7fGU     KU 4WAW   <U.V#U.V JU6V MX +^ 3^ 3^ 3^ 3^ 3^ 2XIX F]=Z&X -X"
" -X -X -X -X -X -X ,X=b$_7X \\?\\ N\\?\\ N\\?\\ N\\?\\ N\\?\\  #\\?`)X/X'X/X'X/X'X/X*Y6Y NX ,Y=W :V ,V 3UDU >TDX   ;a     6V ,V 4UBU   GV ,V 3UCU   0` 6TDX 4V ,V"
" 2UDU >TDX       >V ,V 1UDU   :V 9W       (o Do Do Do Do GWIU J~V       >T   6Z 6i jIj I\\         N~R                M[=U   MX 2VFV %VBV H] AWCW;V%Y=R"
" HV %W -V 4UETEU         IV 4ZBZ IWGX ?V;[ IS9Z 9VNX DX *Z;R -X JZ>Y JZ?Y          1U>Z 5`C_#` CX;[ H[7W&X9_$X -X (\\6X)X/X'X -X -X;[ MX -_4_0`8X![;[&X"
"=[ F[;[&X<[ LZ8U =X <X/X+X,X)X8]8X<X9X#X6X )Z$W 1V  KW &ZKZ   FV   ;W    >W   W   2W     4W ,W               HW             3W :V  MW         KX=W Cc "
";X7P       HX                (W<W ;WNW BY /X ([;[ Gg JX0X)X?X?X([;[   Fd   6V   6d   KX  KS 4Y>R  !X8X JV /X<P   6V1U IV       <U0U  2UAU   3U *U 1V  "
" 6fGU     KU 4V?V   <U/V\"U/V IU7V LX ,` 5` 5` 5` 5` 5` 3XIX G[7W&X -X -X -X -X -X -X -X ,X9_%`8X![;[![;[![;[![;[![;[  %[;](X/X'X/X'X/X'X/X)X6X MX ,X;W"
" :V .V 3UBU ?TBT   7]     3V .V 4VAU   GV .V 3UAU   4d 7TBT 1V .V 2UBU ?TBT       ;V .V 1UBU   <V 8W       )r Gr Gr Gr Gr IVHR GX+W       =S   5[ 7i!k"
"Jk I]        !^                )Y:T   MX 2VFV %VBV Le EVAV<V$X:P HV %W -W 6WFTFV         IV 4X?Y IRBX ?T7Y IP5Z :VNX DX +Z8P .Y JY<Y KY=X          1S;"
"Y 6];\\$WNW CX9Z J[4U&X6]%X -X )[2V)X/X'X -X -X<[ LX -XNV6VNX0`8X\"Z7Z'X;Z HZ7Z'X;Z LY4R =X <X/X*X.X(X8]8X<Y;Y#Y8Y *Z#W 1V  KW 'ZIZ   FV   <W    >W   W "
"  2W     4W ,W               HW             3W :V  MW         KW<X Dd <W       -W                )W;X <WNW AY 0X )Z7Z Jl MX0X)X?X?X)Z7Z   Hf   7V   7f"
"   LX  KS 4X;P   W8W IV /W   \"V.U JV       >U.U  4VAV &V 5U *U 2V   6gGU     KU 5W?W   =U/V\"U/V IU7V LX ,WNW 5WNW 5WNW 5WNW 5WNW 5WNW 4XHX H[4U&X -X -"
"X -X -X -X -X -X ,X6]&`8X\"Z7Z#Z7Z#Z7Z#Z7Z#Z7Z  'Z8['X/X'X/X'X/X'X/X)Y8Y MX ,W:W 9V 0V 3U@U     ?[     1V 0V 3U@V   GV 0V 3U?U   8h   1V 0V 2U@U       "
"  CV 0V 1U@U   >V 7W       *`L` I`L` I`L` I`L` I`L` JV =X,X       >T   6] 9k\"lKl K_        #\\                'Y8S   MX 2VFV %VBV Nk IVAV=V$X 1V %V +V "
"6YHTHY -V       EW 5Y>Y :X ?R5Z .Y ;VMX DX +Y  DX IY<Y LY;X          2Q8Y 8[5[&WNW CX8Y KZ1T&X4\\&X -X *Z.T)X/X'X -X -X=[ KX -XNV6VNX0a9X#Z5Z(X:Y IZ5Z("
"X:Z NY1P =X <X/X*X.X'W9WNV:X:Y=Y!Y:Y *Z\"W 1W  LW (ZGZ      -W    >W   W   2W     4W ,W               HW             3W :V  MW         KW;W De =W      "
" -X                *W:W <VLV @Y 1X *Z5Z Mp X0X)X?X?X*Z5Z   Jh   8V   8h   MX  KS 5Y   :X:X IV /W   #U+T JV       ?U+T  5U?U &V 5U +V     AgGU     KU 5"
"V=V   =U0V!U0V IV8V KX ,WNW 5WNW 5WNW 5WNW 5WNW 5WNW 4XHX IZ1T&X -X -X -X -X -X -X -X ,X4\\'a9X#Z5Z%Z5Z%Z5Z%Z5Z%Z5Z  )Z5Z(X/X'X/X'X/X'X/X(Y:Y LX -X:W  "
"        !W                    2\\LZ                          EW       +[@[ K[@[ K[@[ K[@[ K[@[ KV <X-X     /P 0T   7^ 9k\"lLm La        %Z              "
"  %Z6Q   MX 2VFV %VCV n KWAW>V$X 1V &W +W 5XITIX +V       EV 4X<X :X ?P2Y -X <WMX DX ,Y  CX JY:Y MX9W          2P7Y :Z0Z(WLW DX7X KY.R&X2Z&X -X *Y+R)X"
"/X'X -X -X>[ JX -XNW8WNX0a9X#Y3Y(X9Y JY3Y(X9Y NX  LX <X/X*X.X'X:VMV:X9X=X NX:X *Z!W 0V  LW )ZEZ      .W    >W   W   2W     4W ,W               HW     "
"        3W :V  MW         LX;W Df >W       ,W                +W8W >WLW @Y 2X +Z3Z!t\"X0X)X?X?X*Y3Y   Kj   9V   9j     AS 5X   8W:W HV /W   #T)T KV     "
"  @T(T  6U?U &V 5T +V     AhGU     KU 5V=V   =U0V!U0V JV7V   WLW 7WLW 7WLW 7WLW 7WLW 7XNX 6XGX IY.R&X -X -X -X -X -X -X -X ,X2Z'a9X#Y3Y%Y3Y%Y3Y%Y3Y%Y3"
"Y  )Y3Z)X/X'X/X'X/X'X/X'X:X Ki >W8V                               *XHZ                          FW       ,Z<Z MZ<Z MZ<Z MZ<Z MZ<Z LV <X.X     .R 2S   "
"7` :k#nMm Mb        &Z                $Y4P   MX 2VFV &VBV!o KV?V?V#W 0V &V )V 3XKTKX )V       EV 5X:X ;X  X -Y =VLX DX -Y  CY JY:Y NY9X           HX ;"
"Z-Y)WLW DX7Y MY,Q&X1Z'X -X +Y)Q)X/X'X -X -X?[ IX -XMV8VMX0XNX:X$Y1Y)X9Y KY1Y)X8X NX  LX <X/X)X0X&X:VMV:X9Y?Y NY<Y *Y W 0V  LW *ZCZ      /W    >W   W  "
" 2W     4W ,W               HW             3W :V  MW         LW:W Dg ?W       ,X                ,W8W >WLW ?Y 3X +Y1Y\"v#X0X)X?X?X+Y1Y   MYNVNY   :V   :"
"YNVNY     BS 5X   8X<X HV /W   $T?ZBT*c       AT&T  7U?U &V 6U -W     @hGU     KU 6V;V   >U1V U1V KW7V   NWLW 7WLW 7WLW 7WLW 7WLW 7WLW 6XGX JY,Q&X -X "
"-X -X -X -X -X -X ,X1Z(XNX:X$Y1Y'Y1Y'Y1Y'Y1Y'Y1Y P)P$Y3[)X/X'X/X'X/X'X/X'Y<Y Km BW8W                               +UDZ               7P          1W  "
"     -Y8Y Y8Y Y8Y Y8Y Y8Y MV ;W.X     /T 4T   7a ;k#nMn Nc 6P :W4W ?Z ?X6X KY                #Y   0X 2VFV &VBV\"p KV?V?V#W 0V 'W )W 2XMTMX 'V       FW "
"5X:X ;X  Y -X >VKX DX -X  BX IX8X NX7W      KP  1P  =X <Y)X+XLX EX6X NY*P&X0Z(X -X ,Y'P)X/X'X -X -X@Z GX -XMV8VMX0XNX:X%Y/Y*X8X LY/Y*X8Y!X  KX <X/X)X0"
"X&X:VMV:X8YAY LY>Y *Z W 0W  MW +ZAZ      0W    >W   W   2W     4W ,W               HW             3W :V  MW         LW:W DSF[ @X       -X             "
"   -X8W ?WJW ?Y 4X ,Y/Y%z%X0X)X?X?X,Y/Y   YMVMY   ;V   ;YMVMY     CS 5X 5P*Q JW<W GV /W   %TBbET/g       BTGb?T  8U?U &V 7U 5_     ?hGU     KU 6V;V   "
">U2V NU2V$_7V   NXLX 9XLX 9XLX 9XLX 9XLX 8WLW 6XGX KY*P&X -X -X -X -X -X -X -X ,X0Z)XNX:X%Y/Y)Y/Y)Y/Y)Y/Y)Y/Y\"R+R&Y3]*X/X'X/X'X/X'X/X&Y>Y Jp EW:Y     "
"                          +R@Y               7Q          2W       .XEVFY\"X5Y\"X5Y\"X5Y\"X5Y NV ;X/X     0V 5T   8c <k#nNo e >^ AW4W ?Z >W6W KY           "
"     \"Y   0X 2VFV &VCW#[LSKZ KV?V@V\"W 0V 'W )W 1XNTNX &V       FW 6Y:Y <X  NX -X ?WKX DX .Y  CY IX8X NX7W      NS  1S  @X =X&X,WJW EX6X NY /X/Y(X -X ,"
"Y /X/X'X -X -XAZ FX -XMW:WMX0XMX;X%Y/Y*X8Y MY/Y*X8Y!X  KX <X/X)Y1X%W;WMW;W6XAX JX>X *Z NW 0W  MW ,Z?Z      1W    >W   W   2W     4W ,W               H"
"W             3W :V  MW         LW:W DPAY ?Y       .W                -W6W @WJW >Y 5X ,X-X&_MXM_&X0X)X?X?X,Y/Y  !YLVLY   <V   <YLVLY     DS 6Y 6R,R JX>"
"W FV /X   'TCfFT2i       CUGfBT  9U?U &V 7U 5]     >iGU     KU 6V;V   >U2V NU2V$]5V   NWJW 9WJW 9WJW 9WJW 9WJW 9WJW 8XFX KY /X -X -X -X -X -X -X -X ,X"
"/Y)XMX;X%Y/Y)Y/Y)Y/Y)Y/Y)Y/Y#T-T'Y3]*X/X'X/X'X/X'X/X%X>X Ir GW=\\                                GY               9S          3W       /XDVDX$X2X$X2X$X"
"2X$X2X V ;X0X     0X 7T   8d <k#~`!g Bd DW4W ?[ ?X7W LY                !X   /X 2VFV &VCV#ZJSGV KV?VAV!W 0V 'V 'V /d $V       FV 5X8X <X  NX -X ?VJX DX"
" .X  BX HX8X Y7X     #V  1V  CX >X$X-WJW EX6X Y .X.Y)X -X -Y .X/X'X -X -XBZ EX -XLV:VLX0XMX;X&Y-Y+X7X NY-Y+X7X!X  KX <X/X(X2X$X<VKV<X6YCY JY@Y +Z MW /"
"V  MW -Y;Y    \"Z ;WDX 0Z 2XDW >Z <W !X :WDY     IW ,W  HX8X MY 3Z *X 3X &X 7] <W             3W :V  MW       ;X :W:W 4Y @[ )\\ (Y   6X     8QEV     :[ "
"    JW6W @VIW =Y 6X -Y-Y(]JXJ]'X0X)X?X?X-Y-Y  #YKVKY   =V   =YKVKY     IZ 9X 6T.T JW>W FV .X   (TDgFT3j       CTFhDT  9U?U &V 8U 4\\     =iGU     KU 6V"
";V   >U3V MU3V#\\5V   MWJW 9WJW 9WJW 9WJW 9WJW 9WJW 8XFX LY .X -X -X -X -X -X -X -X ,X.Y*XMX;X&Y-Y+Y-Y+Y-Y+Y-Y+Y-Y%V/V)Y3_+X/X'X/X'X/X'X/X%Y@Y Is HW?^ "
"?Z /Z /Z /Z /Z /Z /Z6Y NZ 0Z /Z /Z /Z         8Y 1Y 3Z /Z /Z /Z /Z   3ZCV          5WDX       DXCVCW%X0W%X0W%X0W%X0W V :X1X     0X 7T   9f =k#~`\"h Cf "
"EW4W @\\ ?X8X LX                !Y   /X 2VFV 'VBV#XHSET KV?VAV!W 0V (W 'W .` \"V       GW 5X8X <X  NX -X @VIX DX .X  BX HX8X X5W     &Y  1Y  FX >W\"W.XJX"
" FX6X X -X.Y)X -X -X -X/X'X -X -XCZ DX -XLV:VLX0XLX<X&X+X+X7X NX+X+X7X!X  KX <X/X(X2X$X<VKV<X5YEY HYBY +Z LW /W  NW .Y9Y    'b ?WG^ 7b 9^GW A` Gl 2_GW"
" MWG_ DW ,W ,W8Y MW ,WG^>^4WG_ 9` @WG^ 9^GW MWG\\ ;f Gm <W6W#X2X#W;X;W5Y7Y#W1X\"u 6W :V  MW       >^BV\"W:W 3X ?^ 0e AWG_ KV.X ?X <W6W   HTG[ K}!WCWCW Ca"
" 7p&{ NW6W AWHW >Z 7X -X+X)\\HXH\\(X0X)X?X?X-X+X  $YJVJY   >V   >YJVJY     Ma =X 7V0V JW@W EV .Y   *TEiET5k       DTEiDT  :VAV &V 9U 3_   ;W6W NiGU     "
"KU 6V;V   >U3V MU3V#_8V   NXJX ;XJX ;XJX ;XJX ;XJX ;XJX :XEX LX -X -X -X -X -X -X -X -X ,X.Y*XLX<X&X+X+X+X+X+X+X+X+X+X&X1X*X3`+X/X'X/X'X/X'X/X$YBY Ht "
"IW@_ Cb 7b 7b 7b 7b 7b 7b>a'b 7` 5` 5` 5` AW ,W ,W ,W  DY EWG_ 9` 5` 5` 5` 5` (Z <`GV W6W MW6W MW6W MW6W#W1X NWG^ HW1X     NWBVBW&W.W&WJP:PJW&W4PJW&W."
"W!V :X2X     0X 6S   8g >k#~`#j Fj GW4W @\\ >W8W LX                 X   .X 2VFV 'VBV$XGSCR KV?VBV X 1V (W 'W ,\\  V       GW 5X8X <X  NX -X AWIX DX /X  "
"BY HX8X X5W     ([  1[  HX ?W W/WHW FX6X!Y -X-Y*X -X .Y -X/X'X -X -XDZ CX -XLW<WLX0XKW<X'Y+X+X7X Y+X+X7X!X  KX <X/X'X4X#X<VKV<X4XFY FXBX *Y KW /W  NW "
"/Y7Y    +g AWIb ;f =bIW De Il 3bIW MWIc FW ,W ,W9Y LW ,WIbBb6WIc >f CWIb =bIW MWI^ =j Im <W6W\"W2W\"W<Z<W4X7X!W2W!u 6W :V  MW       @bEW\"W:W 2X @c 8j CW"
"Ic MX0W =W <W6W IW/W\"VI^ L}!WCWCW Ee =t&{ W4W BWHW =Y 7X .X*Y*ZFXFZ(X0X)X?X?X.Y+X  #WIVIW   =V   =WIVIW     f ?X 8X2X KW@W EV .Z   +SE[GVDS6ZDV       "
"DSDVDXDS  9UAU %V :U 2`   <W6W NiGU     KU 6V;V   >U4V LU4V\"`:V GX /WHW ;WHW ;WHW ;WHW ;WHW ;WHW :XEX MY -X -X -X -X -X -X -X -X ,X-Y+XKW<X'Y+X,Y+X,Y+"
"X,Y+X,Y+X'Z3Z,Y4WNY,X/X'X/X'X/X'X/X#XBX Gu JWB\\ Ag <g <g <g <g <g <gBe+f <e :e :e :e CW ,W ,W ,W  Mc FWIc >f ;f ;f ;f ;f +Z >eJU NW6W MW6W MW6W MW6W\"W"
"2W MWIb IW2W     NWAVAW(W,W(WJR<RJW(W4RJW(W,W\"V 9W2X     1X 6T   9i ?k#~`#k Hl HW4W @] ?X9W LW                 NX   .X 2VFV 'VCW$WFSAP KV?VBV NW 1V (V"
" &W *X  MV       GV 5X6X =X  NX -X AVHX DX /X  BX GX8X X5X     ,^  1^  LX ?W MW0WHW FX6X!X ,X-Y*X -X .X ,X/X'X -X -XEZ BX -XKV<VKX0XKX=X'Y+Y,X7X Y+Y,X"
"7X!X  KX <X/X'X4X\"W=WKV<W3YGY FYDY +Z KW .V  NW 0Y5Y    /l CWJe ?j AeJW Eh Kl 5eJW MWJe GW ,W ,W:Y KW ,WJdDd7WJe @h DWJe AeJW MWJ_ ?l Im <W6W\"W2W!W=Z="
"W2X9X W2W!u 6W :V  MW       BeFV!W;X 1W ?f =k CWJe NY2X =X =W6W JW-W$WI` N}!WCWCW Gi Av&{ W4W BVGW <Y 8X .X)X+ZEXEZ)X0X)X?X?X.Y+Y  #UHVHU   <V   <UHVH"
"U    !j AX 9Z4Z KWBW DV -Z   -TFY@RDT8XAV       ETDVBWET  :VCV %V ;V )X   =W6W NiGU     KU 6V;V   >U5V KU5V GX<V FX /WHW ;WHW ;WHW ;WHW ;WHW ;WHW :WDX"
" MX ,X -X -X -X -X -X -X -X ,X-Y+XKX=X'Y+Y-Y+Y-Y+Y-Y+Y-Y+Y'Z5Z+Y5WMY,X/X'X/X'X/X'X/X#YDY GX@^ KWCZ Al Al Al Al Al Al AlFh.j ?h =h =h =h EW ,W ,W ,W !g"
" GWJe @h =h =h =h =h ,Z @hLV NW6W MW6W MW6W MW6W\"W2W MWJe KW2W     W@VAW)W+W)WJT>TKW)W4TKW)W+W\"V 9X3X     2X 5T   :k ?i\"~`$m Jn IW4W A^ ?X:X MW       "
"          NY   .X 2VFV 7~X2XFS <V?VCV MX 2V )W %W +X  MV       GV 5X6X =X  NX -X BVGX DX /X  BX GX8X X5X LX -X  7a  1a  X @W KW2XHX GX6X!X ,X,X*X -X ."
"X ,X/X'X -X -XFZ AX -XKV<VKX0XJW=X'X)X,X7X X)X,X7X!X  KX <X/X'X4X\"X>VIV>X2YIY DYFY +Z JW .V  NW 1Y3Y    1n DWLh Bm ChLW Gk Ll 6hLW MWKg HW ,W ,W;Y JW "
",WKfGg8WKg Cl FWLh ChLW MWK` @m Im <W6W\"X4X!W=Z=W1X;X NW3X!u 6W :V  MW       CgGV!W;W 0X ?g Am CWKg [4X >Y =W6W JW-W&YJb }!WCWCW Hk Dx&{ W4W CWFW <Y 9"
"X /Y)X,ZDXDZ*X0X)X?X?X.X)X P #SGVGS %P 7V 9P0P CSGVGS    !l BX 8ZGWFZ JWCX DV ,Z   .SEW<PCS8V?V .P>P     JSCVAVDS  :WEV $V <V &W   >W6W NiGU     KU 6V"
";V BP>P /U5V KU5V EW=V FX 0XHX =XHX =XHX =XHX =XHX =XHX <XDX MX ,X -X -X -X -X -X -X -X ,X,X+XJW=X'X)X-X)X-X)X-X)X-X)X&Z7Z*X5WKX,X/X'X/X'X/X'X/X\"YFY F"
"X=[ KWDY @n Cn Cn Cn Cn Cn CnHj1m Bk @k @k @k FW ,W ,W ,W $j GWKg Cl Al Al Al Al .Z Bs MW6W MW6W MW6W MW6W\"W3X MWLh LW3X     V?V@W*V)W*VJV@VKW*V4VKW*V"
")W#V 9X4X     2X 4S   :l ?i\"~`%o Lp JW4W A^ >W:X MW                 NX   -X 2VFV 7~X2WES <V?VDV LX 2V )W %W -\\  V       HW 5X6X =X  NX .X BWGX DX 0X  "
"BY FX:X NX5X LX -X  :d  1d $Y @V IV2WFW GX6X\"Y ,X,Y+X -X /Y ,X/X'X -X -XH[ @X -XKW>WKX0XJX>X(Y)X,X7X!Y)X,X7X!Y  LX <X/X&X6X!X>VIV>X1YKY BXFX +Z IW .W "
" W 2Y1Y    2o EWMj Dn DjMW Hn Nl 7jMW MWLi IW ,W ,W<Y IW ,WLhIi9WLi En GWMj EjMW MWLa An Im <W6W!W4W W=Z=W1Y=Y MW4W u 6W :V  MW       DiIV W;W /W =g C"
"m CWLi![4W =Y =W6W KW+W(ZKd!}!WCWCW Im Fy&{ W4W CWFW ;Y :X /X'X-YCXCY*X0X)X?X?X/Y)X!R #QFVFQ $R 9V :R1R DQFVFQ    \"n BX 7ZJ\\JZ HWDW CV +[   1TFW.T:W?V"
" /Q?Q     KTCVAWET  :XIX $V =V #U   >W6W NiGU     KU 6V;V BQ?Q 0U6V JU6V BU>V EX 0WFW =WFW =WFW =WFW =WFW =WFW <XDX NY ,X -X -X -X -X -X -X -X ,X,Y,XJ"
"X>X(Y)X.Y)X.Y)X.Y)X.Y)X%Z9Z*Y6WJX,X/X'X/X'X/X'X/X!XFX EX;Z LWDX ?o Do Do Do Do Do DoKn4n Cn Cn Cn Cn HW ,W ,W ,W %l HWLi En Cn Cn Cn Cn /Z Cs LW6W MW6"
"W MW6W MW6W!W4W LWMj LW4W     W?V?V+W(V+WKXBXKV+W5XKV+W(V$W 8W4X     2X 5T   ;n ?g!~_%p LZDZ JW4W A^ >W:W MW                 MX   -X 2VFV 7~X2WES <WAW"
"DV KX 3V )W %W /` \"V       HV 4X6X =X  Y .X BVFX DX 0X  BX EX:X NX5X LX -X  <e  /e 'Y @V GV4XFX HX7X!X +X+X+X -X /X +X/X'X -X -XI[ ?X -XJV>VJX0XIW>X(X"
"'X-X7X!X'X-X7X!Y  LX <X/X&X6X!X>VIV>X1YKY AXHX +Z HW -V  W 3Y/Y    3p FWMk Fo EkMW Io Nl 8kMW MWMk JW ,W ,W=Y HW ,WMjJj:WMk Gp HWMk GkMW MWMb Bo Im <W"
"6W!W4W W>\\>W0X=X LW5X u 6W :V  MW       EkJV W<X /W >j Fn CWMk\"\\6X =Z >W6W KW+W)[Ke\"}!WCWCW Jo Hz&{ W4W DWDW ;Y ;X /X'X.YBXBY+X0X)X?X?X/X'X#T  HV  IT "
":V ;T3T :V   CV +o BX 6ZM`MZ GXFX CV *\\   3SFW,S:V>V 0R@R     KSBV@VDS  9e #V ?W \"V   ?W6W NiGU     KU 6V;V BR@R 1U6V JU6V BV?V EX 1XFX ?XFX ?XFX ?XFX"
" ?XFX ?XFW =XCX NX +X -X -X -X -X -X -X -X ,X+X,XIW>X(X'X/X'X/X'X/X'X/X'X%Z;Z)X5VHX-X/X'X/X'X/X'X/X XHX DX:Y LWEX >p Ep Ep Ep Ep Ep EpMp6o Do Do Do Do"
" HW ,W ,W ,W 'o IWMk Gp Ep Ep Ep Ep 0Z Ds KW6W MW6W MW6W MW6W!W5X LWMk MW5X     V>V?W,V'W,VKZDYKW,V5YKW,V'W%W 8X5W     2X 4T   ;o @g ~^%q NY@Y KW4W B`"
" ?X<X MV                 LX   -X 2VFV 7~X2WES ;VAVDV JY 4V )V $W 1d $V       HV 4X6X =X  X .Y CWFX DXLY =XEX 'Y EY<X MX5X LX -X  ?e  )e +Y ?V:X6V4WDW "
"HX7X!X +X+X+X -X /X +X/X'X -X -XJ[ >X -XJW@WJX0XIX?X(X'X-X7X!X'X-X8Y Y  MX <X/X%W6X W?WIV>W/YMY @YJY +Y GW -V  W 4X+X    4YE\\ FWNXG\\ H]EX F\\GXNW J\\F[ "
"GW ,\\GXNW MWNXG[ JW ,W ,W?Z GW ,WNXH[KXH[:WNXG[ H]H] IWNXG\\ I\\GXNW MWNXFQ C\\CW CW ,W6W!X6X NW?\\?W.X?X JW6W 1X 6W :V  MW     9X=X\"[IZKW W=Y /W @m H]DV "
"CWNXG[\"\\6W =[ >W6W LW)W*ZJWKY\"}!WCWCW K\\H] J{&{ V3W DWDW :Y <X /X'X.XAXAX+X0X)X?X?X/X'X$V  IV  JV ;V <V5V ;V   CV ,^MSKW BX 5x EWFW BV ,_   5TFW,S:V?W"
" 1SAS     LTBV@VDS  9d \"V @W  U   ?W6W NiGU     KU 5V=V ASAS 2U7V IU7V @U@V DX 1WDW ?WDW ?WDW ?WDW ?WDW ?XFX >XCX NX +X -X -X -X -X -X -X -X ,X+X,XIX?"
"X(X'X/X'X/X'X/X'X/X'X$Z=Z(X6WHX-X/X'X/X'X/X'X/X YJY DX9Y MWEW =YE\\ EYE\\ EYE\\ EYE\\ EYE\\ EYE\\ EYE]N\\G[7]EX E\\F[ F\\F[ F\\F[ F\\F[ IW ,W ,W ,W (p IWNXG[ H]H"
"] G]H] G]H] G]H] G]H] 1Z E]H^ JW6W MW6W MW6W MW6W W6W KWNXG\\ MW6W     NV>V>V,V&V,VJZFYIV,V6YIV,V&V%W 7W6X     3X LR:T   ;q @e N~^&s!Y>Y LW4W B` >W<X N"
"W                $x   FX 2VFV 7~X2WES ;VAVEW IY 5V *W #W 4XNTNX &V       IW 5X5X =X  X .X CWEX Di AXH_ +X CX<X MX5X LX -X  Be  #e /Z @V<^IUDV5WDW HX8Y"
"!X +X+X+X -X /X +X/X'X -X -XK[ =X -XIV@VIX0XHW?X(X'X-X7X!X'X-X8X NZ  NX <X/X%X8X NX@VGV@X.c >XJX +Z GW -W !W 5X)X    5U>Z G_CZ I[>T FZC_ KZAZ HW -ZB_ "
"M^BZ KW ,W ,W@Z FW ,^CZMVCZ;^BZ IZBZ I_CZ IZC_ M^ 5Y<S CW ,W6W W6W MW?\\?W.YAY JW6W 2Y 6W :V  MW     ;\\A\\%YDYLV NW>Y .W AXJa IZ<Q C^BZ MX8X =\\ ?W6W LW)"
"W+YIXJY LW=W JWCWCW LZBZ K]F] ;W >W2W EWDW 9Y =X /X'X/YAXAY,X0X)X?X?X/X'X%X  JV  KX <V =X7X <V   CV -\\JSHT BX 4v DXHX BV -b   7SEV*S;V?W 2TBT     LSAV"
"@VCS  9b !V AV  MU   ?W6W MhGU     KU 5V=V ATBT 3U8V HU8V ?UAV CX 1WDW ?WDW ?WDW ?WDW ?WDW ?WDW ?XBX NX +X -X -X -X -X -X -X -X ,X+X,XHW?X(X'X/X'X/X'X"
"/X'X/X'X#Z?Z'X7WGX-X/X'X/X'X/X'X/X NXJX CX9Y MWFW <U>Z FU>Z FU>Z FU>Z FU>Z FU>Z FU>eBZ9[>T FZAZ HZAZ HZAZ HZAZ JW ,W ,W ,W )r J^BZ IZBZ GZBZ GZBZ GZBZ"
" GZBZ 1Z EZB[ JW6W MW6W MW6W MW6W W6W K_CZ MW6W     V=V>V-V%V-VHZHYHV-V6YHV-V%V%W 7X7X     4X NU:T   <s Ae N~^'u\"X<X LW4W BWNW >W<W MW                "
"$w   EX   2~X2WES ;WCWEV GY   9W #W 5XMTMX 'V       IV 4X4X >X !Y 0Y BVDX Dk CXJc -X BX>X LX5Y MX -X  Ee   Le 3Z ?U=bKUCU6XDX IX9Y X +X+X+X -X /X +X/X"
"'X -X -XL[ <X -XIV@VIX0XHX@X(X'X-X8Y!X'X-X8X N[  X <X/X%X8X NX@VGV@X.c =XLX +Z FW ,V !W       AR9Y H]?Y KZ:R GY?] LY=Y IW -Y?] M]@Y KW ,W ,WAY DW ,]@X"
"NV@X;]@Y JY>Y J]?Y KY?] M] 4X8P CW ,W6W X8X MW?\\?W-XAX IW7X 3Y 5W :V  MW     =_C_(YBXLV NW?Z -W CXC\\ KY ,]@Y LW8X >] ?W6W LW)W,YHWHY MW=W JWCWCW MY>Y "
"L[B[ ;W >W2W FWBW 9Y >X 0X%X0X@X@X,X0X)X?X?X/X'X&Y  JV  KY =V >Y7Y =V   CV .[HSFR BX 3t BWHW AV .WN\\   9SFV)S;V?W 3UCU     LSAV@VCS  7_  V BV  LU   ?W"
"6W MhGU     KU 5W?W AUCU 4U8V HU8V ?UAV CX 2XDX AXDX AXDX AXDX AXDX AXDX @XBX NX +X -X -X -X -X -X -X -X ,X+X,XHX@X(X'X/X'X/X'X/X'X/X'X\"ZAZ&X8WFX-X/X'"
"X/X'X/X'X/X MXLX BX8X MWFW <R9Y GR9Y GR9Y GR9Y GR9Y GR9Y GR9a>Y;Z:R GY=Y JY=Y JY=Y JY=Y KW ,W ,W ,W *]E[ J]@Y JY>Y IY>Y IY>Y IY>Y IY>Y 2Z FY>Y JW6W MW"
"6W MW6W MW6W W7X K]?Y NW7X     V=V=U-V$U-VGZJYFU-V7YFU-V$U%W 7X8X    &~X/X:T   =t @c L~\\'v\"W:W LW4W CXNX ?X>X MV                $x   EX   2~X2WES :VDW"
"EV FZ   :W #W 7XKTKX )V       IV 4X4X >X !X 0Y BWDX Dm FXKf /Y AYBY KX5Y MX -X  Gd ~X d 5Y ?V>dLUCU6WBW IX;Z Y +X+Y,X -X 0Y +X/X'X -X -XM[ ;X -XIWBWIX"
"0XGW@X)Y'Y.X8X!Y'Y.X9Y M] #X <X/X$X:X MX@VGV@X-a <YNY ,Z EW ,V !W       AP6X H\\=Y LY7P HY=\\ LX;X IW .Y=\\ M[=X KW ,W ,WBY CW ,[=]=W;[=X KY<Y K\\=Y MY=\\ "
"M\\ 4X *W ,W6W NW8X MW@VNV@W,XCX GW8W 3Y 4W :V  MW     >aEa)X@XNW NWA[ ,W DW?[ LX +[=X KW:X =] ?W6W MW'W-XGWGX MW=W JWCWCW MX<Y NZ>Z <W >W2W FWBW 9Z ?X"
" 0X%X0X@X@X,X0X(X@X@X/Y'Y(Y  IV  JY >V ?Y5Y >V   CV .YFSDP BX 2q @XJX AV /WK[   :SFV)S;V@X 4VDV     LSAV@VCS  6\\  MV CV  KU   ?W6W MhGU     KU 4V?V @V"
"DV 5U9V GU9V >UBV BX 2WBW AWBW AWBW AWBW AWBW AXDX @XBX Y +X -X -X -X -X -X -X -X ,X+Y-XGW@X)Y'Y1Y'Y1Y'Y1Y'Y1Y'Y\"ZCZ&Y9WEY.X/X'X/X'X/X'X/X MYNY BX8Y N"
"WFW <P6X GP6X GP6X GP6X GP6X GP6X GP6_<X;Y7P GX;X JX;X JX;X JX;X KW ,W ,W ,W *Z?Y K[=X KY<Y KY<Y KY<Y KY<Y KY<Y 3Z GY<Y KW6W MW6W MW6W MW6W NW8W J\\=Y "
"NW8W     NV=V=V.V$V.VFZLYEV.V8YEV.V$V&W 6W8X    &~X2\\<T   =v Ab K~\\(x$W8W MW4W CXNX ?X>X NW                $w   DX   $VBV#XFS :WFXEV H]   ;W #W 9XITIX"
" +V       JW 4X4X >X \"Y 3[ BWCX Dn GXLi 1X ?ZFZ JY7Z MX -X  Je M~X Me 9Y >U?gMUCV7WBW IX>\\ NX *X*X,X -X 0X *X/X'X -X -XNZ 9X -XHVBVHX0XGXAX)X%X.X9Y!X%"
"X.X:Y La 'X <X/X$X:X LWAWGV@W+_ :XNX ,Z DW ,W \"W       &W H[;X MY .X;[ MX9X JW .X;[ M[<X LW ,W ,WCY BW ,Z<\\<X<[<X LX:X K[;X MX;[ M[ 3W )W ,W6W NW8W KW"
"AVNVAW*XEX FW9X 4Y 3W :V  MW     ?cGc+Y?WNV MWD] +W DV=Z LX +Z;X LW:X >_ @W6W MW'W.YGWFX NW=W JWCWCW NX:X NY<Y <W >W2W FWBW 8Z @X 0X%X0X@X@X,X0X(X@X@X"
"/X%X)Y  HV  IY ?V @Y3Y ?V   CV /YES 6X 1\\H[ JcJc LV 0WI\\   =TFV)S;WAX 5WEW     MTAVAWCS  3W 4~W.W  KV   ?W6W LgGU     KU 4WAW @WEW 6U9V GU9V ?VBV BX 2"
"WBW AWBW AWBW AWBW AWBW AWBW AXAX X *X -X -X -X -X -X -X -X ,X*X-XGXAX)X%X1X%X1X%X1X%X1X%X!ZEZ%X9WCX.X/X'X/X'X/X'X/X LXNX AX7X NWFW !W ,W ,W ,W ,W ,W "
",]:X=Y .X9X LX9X LX9X LX9X LW ,W ,W ,W +Z=X K[<X LX:X KX:X KX:X KX:X KX:X 3Z GX<Z KW6W MW6W MW6W MW6W NW9X J[;X NW9X     NU<V=V.U#V.UDZNYDV.U8YDV.U#V&"
"V 5X9W    %~X3]<T   >x A` J~\\(y%W8W MW4W CXMW >W>W MV                $x   DX   $VCV\"XFS 9XIXEV H_   <W #W ;YHTHY -V       JV 3X4X >X #Y ?g AVBX Do HXM"
"k 3Y >l HX7Z MX -X  Me J~X Je =Y >V?hNUBU8XBX Ju MX *X*X,w Lq IX *~R'X -X -c 8X -XHVBVHX0XFWAX)X%X.X9Y!X%X.X;Z Ke ,X <X/X$X:X LXBVEVBX+_ 9` +Y CW +V \""
"W       %W IZ9X NX .X9Z MW7W JW /X9Z MZ;X LW ,W ,WDY AW ,Z;[;W<Z;X MY:Y LZ9X X9Z MZ 2W )W ,W6W NX:X KWAVNVAW*YGY EW:W 4Z 3W :V  MW     ?XMYIe,X>WNV MW"
"Ib +W EW;Y MW *Z;X KV:W =_ @W6W NW%W/XFWFX NW=W JWCWCW NW8X!Y:Y =W >| GW@W 8Y @X 0X%X1Y@X@Y-X0X(X@X@X/XImIX*Y  GV  HY @V AY1Y @V   CV /XDS 6X 0YDY JdL"
"d LV 1WF[   >SFV'S<WBY 6XFX     MS@VAVAS    @~W/W  JU   >W6W LgGU     KU 3WCW ?XFX 7U:V FU:V >UBV AX 3XBX CXBX CXBX CXBX CXBX CXBX BXAw?X *w Lw Lw Lw "
"LX -X -X -X ,X*X-XFWAX)X%X1X%X1X%X1X%X1X%X ZGZ$X:WBX.X/X'X/X'X/X'X/X K` @X7X NWFW  W ,W ,W ,W ,W ,W ,[8W=X -W7W LW7W LW7W LW7W LW ,W ,W ,W ,Y:X LZ;X M"
"Y:Y MY:Y MY:Y MY:Y MY:Y  \"Y=\\ LW6W MW6W MW6W MW6W MW:W IZ9X NW:W     NV<V=V/V#V/VCcCV/V9YCV/V=X>V&V 4W:X    %~X2TNV<S   =y KWM^LW$~Z({&W7V MW4W CWLX ?"
"X?W MV                 KX   ,X   %VBV!XGS 9gFV Ha   >W \"W ;WFTFW -V       JV 3X4X >X #Y ?f AWBX Dp IXNm 4X <j GX7Z MX -X !e G~X Ge AY =U?ZH^BU8W@W Jt "
"LX *X*X,w Lq IX *~R'X -X -b 7X -XHWDWHX0XFXBX)X%X.X:Y X%X.X<Z Ih 0X <X/X#X<X KXBVEVBX*] 8` ,Z CW +V \"W       %W IZ9X X -X9Z NX7X KW /X9Z MY9W LW ,W ,W"
"EY @W ,Y:Z:W<Y9W MX8X LZ9X X9Z MY 1W )W ,W6W MW:W JWAVNVAW)XGX DW:W 4Y 3X :V  MW     @VHXKWGV,W<^ MWIa *W FW9Y NW *Y9W KW<X >` @W6W NW%W/WEWEW NW=W JW"
"CWCW X8X!X8X =W >| GW@W 7Y AX 0X%X1X?X?X-X0X(X@X@X/XImIX+Y  FV  GY AV BY/Y AV   DX 1XCS 6X 0W@X KdLd LV 1VCZ   ?SFV'S;WE[ 7XFX G~X  .S@VBWAS    @~W0W "
".P>W   >W6W KfGU     KU 3XEX >XFX 8U;V:W3U;VCZ9P>WCV:W/Y 3W@W CW@W CW@W CW@W CW@W CXBX CX@w?X *w Lw Lw Lw LX -X -X -X 5p9X-XFXBX)X%X1X%X1X%X1X%X1X%X N"
"ZIZ#X:VAX.X/X'X/X'X/X'X/X K` @X7X NWFW  W ,W ,W ,W ,W ,W ,[8X?X -X7X NX7X NX7X NX7X MW ,W ,W ,W ,X9X LY9W MX8X MX8X MX8X MX8X MX8X  \"X=] LW6W MW6W MW6"
"W MW6W MW:W IZ9X NW:W     NVLuKU/VLuKU/VBaAU/V:YAU/V=X=U&V 4X;X    %~X2RLW>T   >{!z'~Z)}(W6W NW4W DXLX ?X@X MV                 KX   ,X   %VBV!YHS 8eEV"
" Ic   ?W !W ;UETEU ,V       KW 3X4X >X $Y >c ?WAX DWD^ JbG] 5X 9d DY9[ MX -X #d D~X Dd DY <U@YD\\BU9X@X Kq IX *X*X,w Lq IX *~R'X -X -a 6X -XGVDVGX0XEWB"
"X)X%X.X;Z X%X.X?\\ Gk 4X <X/X#X<X KXBVEVBX)[ 6^ ,Z BW +W #W       %W IY7W X -W7Y NW5W KW 0X7Y MY9W LW ,W ,WFY ?W ,Y:Z:W<Y9W MW6W LY7W W7Y MY 1W )W ,W6W"
" MW:W JWBVLVBW(XIX CW;X 5Y 2X :V  MX     BUDVKVDU.X<] LWI_ :WEW FV7X NW *Y9W JV<X >a AW6W NW%W0XEWEX W=W JWCWCW W6W!X8X =W >| HX@X 7Y BX 0X%X1X?X?X-X0"
"X(X@X@X/XImIX,Y  EV  FY BV CY-Y BV   DX 1XCS 6X 1W>W KeNe LV 1VB[   ASFV'S;YI] 9YGY F~X  .S@VDX@S    @~W1V ,TEZ   >W6W JeGU IX   +U 2YIY <YGY :U;V:W3U"
";VGa<TEZCV:W/X 3X@X EX@X EX@X EX@X EX@X EX@X DX@w?X *w Lw Lw Lw LX -X -X -X 5p9X-XEWBX)X%X1X%X1X%X1X%X1X%X MZKZ\"X;WAX.X/X'X/X'X/X'X/X J^ ?X7X NWFX !W "
",W ,W ,W ,W ,W ,Z6W?X -W5W NW5W NW5W NW5W MW ,W ,W ,W -X7W LY9W MW6W MW6W MW6W MW6W MW6W  \"W=^ LW6W MW6W MW6W MW6W MW;X IY7W NW;X     NVLuKU/VLuKU/VA_"
"@U/V;Y@U/V=X=U&V 4X<X    $~X,W>T   ?|\"}(~X)~(W6W NW4W DXKW >W@X MV                 KX   ,X   %VBV!ZIS 7cEV IYNZ8W  0W !W :RCTCR +V       KW 3X4X >X %Y"
" =b >V@X DS=\\ K`C[ 6Y 8b BX9[     Nd A~X Ad HY <VAX@ZBV:X?W Kq IX *X*X,w Lq IX *~R'X -X -a 6X -XGVDVGX0XEXCX)X%X.X=[ NX%X.u Fl 6X <X/X\"W<W IWCWEVBW([ "
"5\\ ,Z AW +W #W       $V IY7X\"X -X7Y NW5W KW 0X7Y MX8X MW ,W ,WHZ >W ,X8X8W=X8X X6X MY7X\"X7Y MX 0W )W ,W6W MX<X IWCVLVCW&XKX AW<W 5Y 1W 9V  LW  4P  /TB"
"VMVBT.X;\\ LWI` =\\HW GW7X NW *X8X KV=X >XMW AW6W NW%W0XEWDW W=W JWCWCW!X6X#X6X >W >| HW>W 6Y CX 0X%X1X?X?X-X0X'XAXAX.XImIX-Y  DV  EY CV DY+Y CV   DX 2X"
"BS 6X 1V<V KeNe LV 2V?Y   ASFV'S:dNV :XFY E~X  .S@i?S    @~W2i >h   =W6W JeGU IX   4g :g :YFX DgEV:X<gEVHe>hCV:X/X 3X?W EX?W EX?W EX?W EX?W EX@X EX?w?"
"X *w Lw Lw Lw LX -X -X -X 5p9X-XEXCX)X%X1X%X1X%X1X%X1X%X LZMZ!X<W@X.X/X'X/X'X/X'X/X I\\ >X7X NWFY !V +V +V +V +V +V +Y6W@X ,W5W NW5W NW5W NW5W MW ,W ,W"
" ,W -X7X MX8X X6X X6X X6X X6X X6X  $X=_ MW6W MW6W MW6W MW6W LW<W HY7X NW<W     MVLuKU/VLuKU/V@]?U/V<Y?U/V=X=U&V 3W<X    $~X+V>S   >}%~R)~V(~P)W6W NW4W"
" DWJX ?XAW L~^               $X   ,X   %VCV N\\LS 6aDVAW0XLZ9W  0W !W :PATAP +V       KV 2X4X >X &Z =e BW@X DP8[ L^?Z 7X :h EY;\\    \"d >~X ?e LY ;U@W>Y"
"AU:W>W Ks KX *X*X,w Lq IX6f+~R'X -X -b 7X -XGWFWGX0XDWCX)X%X.X@^ NX%X.s Bl 8X <X/X\"X>X IXDVCVDX)[ 4\\ -Z @W *V #W       $W JX5W\"X -W5X W4W KW 0W5X MX7W"
" MW ,W ,WIZ =W ,X8X8W=X7W W4W MX5W\"W5X MX 0X *W ,W6W LW<W HWCVLVCW&YMY AW=X 6Y 1X 9V  LX 1X.Q  /TA]AU/W:\\ LWIb A`JW GV5X NW +X7W KW>X >XMX BW6W W#W1WD"
"WDW W=W JWCWCW!W4W#X6X >W >| HW>W 7Y BX 0X%X1X?X?X-X0X'XAXAX.XImIX.Y  CV  DY DV EY)Y DV   DX 2XBS 6X 2W<W =^ =V 2V>Y   BSFV'S9bMV ;XFY D~X  .S@h>S    "
"@~W2i >g   <W6W HcGU IX   4g 9e 8YFX EgEV;Y<gEVHf?gBV;Y0Y 3W>W EW>W EW>W EW>W EW>W EW>W EX?w?X *w Lw Lw Lw LX -X -X -X 5p9X-XDWCX)X%X1X%X1X%X1X%X1X%X "
"Ke X=W?X.X/X'X/X'X/X'X/X I\\ >X7X NWEY \"W ,W ,W ,W ,W ,W ,X5W@X -W4W W4W W4W W4W MW ,W ,W ,W -W6X MX7W W4W W4W W4W W4W W4W  $W=VMW MW6W MW6W MW6W MW6W "
"LW=X HX5W NW=X     MVLuKU/VLuKU/V?[>U/V=Y>U/V=X=U&V 3X=W     7X FW@T   ?~&~T*~V)~R*W5V NW4W EXJX ?XBX L~^               $X   ,X   &VBV Mb 4]CVC]4XJZ:W"
"  0W !W +T  KV       KV 2X4X >X 'Z <g EW?X +Z L]=Z 9Y <l GZ=]    %e    e!Y :UAW<XAU;X>X Lu MX *X*X,w Lq IX6f+~R'X -X -c 8X -XFVFVFX0XDXDX)X%X.u MX%X.r"
" ?l :X <X/X\"X>X IXDVCVDX)\\ 4Z ,Y ?W *V #W       $W JX5W\"W ,W5X W3W LW 0W5X MX7W MW ,W ,WJY ;W ,X8X8W=X7W W4W MX5W\"W5X MX 0X *W ,W6W LW<W HWCVKUCW%XMX "
"?W>W 6Y 0X 9V  LX 5`3R  0T?[?T/W:[ KWId DbKW HW5X NW +X7W JV>W =WLX BW6W W#W1WDWDW W=W JWCWCW!W4W#W4W >W >| IX>X 9Y AX 0X%X1X?X?X-X0X'XAXAX.XImIX/Y  B"
"V  CY EV FY'Y EV   DX 2WAS ?r CV:V =^ =V 2V=Y   CSFV'S8`LV <XFX B~X  .S@e;S    @~W2i >e   :W6W GbGU IX   4g 8c 5XFX FgFV:Y<gFVGg@eAV:Y1Y 3X>X GX>X GX>"
"X GX>X GX>X GX>X FX?w?X *w Lw Lw Lw LX -X -X -X 5p9X-XDXDX)X%X1X%X1X%X1X%X1X%X Jc NX>W>X.X/X'X/X'X/X'X/X HZ =X7X NWEZ #W ,W ,W ,W ,W ,W ,X4WAW ,W3W!W3"
"W!W3W!W3W NW ,W ,W ,W .X5W MX7W W4W W4W W4W W4W W4W  $W>VLW MW6W MW6W MW6W MW6W KW>W GX5W MW>W     LVLuKU/VLuKU/V>Z>U/V>Y=U/V=X=U&V 2W>X     8Y FW@T  "
" ?~P(~V*~T(~Q)V4V NW4W EXJX >WBX L~^               $X   ,X   &VBV Ld 4WAVD`6XHZ;W  0W !W +T  KV       LW 2X4X >X 'Y ;i GV>X *Z M\\;Y 9X =p HZ?^    'd  "
"  Id$Y 9UAW<XAU;W<W Lw X *X*X,w Lq IX6f+~R'X -X -d 9X -XFVFVFX0XCWDX)X%X.t LX%X.p ;k ;X <X/X!X@X HXDVCVDX*^ 4X ,Z ?W *W $W       $W JX5W\"W ,W5X W3W LW"
" 0W5X MW6W MW ,W ,WKY :W ,W7W7W=W6W W4W MX5W\"W5X MX /Y ,W ,W6W LX>X GWEVJVEW#a >W>W 7Y 1Y 8V  KY 9e8T  0T?Z>T0X:[ KWIf GdLW HW4W MW ,W6W JV?X >XKW BW6"
"W W#W2XDWDX!W=W JWCWCW!W4W#W4W >W >| IW<W :Y @X 0X%X1X?X?X-X0X&XBXBX-XImIX0Y  AV  BY FV GY%Y FV   DX 2WAS ?r DW:W =\\ <V 2V;W   CSFV'S7]JV =XFX A~X  .S"
"@d:S    (V Ii <a   8W6W FaGU IX   4g 6_ 2XFX GgGV:Z<gGVFUFY?a@V:Z2Y 2W<W GW<W GW<W GW<W GW<W GX>X GX>w?X *w Lw Lw Lw LX -X -X -X 5p9X-XCWDX)X%X1X%X1X%",
// Start of second string.
"X1X%X1X%X Ia MX?W=X.X/X'X/X'X/X'X/X GX <X7X NWDZ $W ,W ,W ,W ,W ,W ,X4WAW ,W3W!W3W!W3W!W3W NW ,W ,W ,W .W4W MW6W W4W W4W W4W W4W W4W  $W?VKW MW6W MW6W"
" MW6W MW6W KW>W GX5W MW>W     LVLuKU/VLuKU/V?\\?U/V?Y<U/V=X=U&V 2W>X     8X DWBT   ?~Q)~W)~R&~(V4V NW4W EWHW >WBW K~^               $X   ,X   &VBV Kg \""
"VEc8WFZ=W  /W !W +T 4~W      5V 1X4X >X (Y -] IW>X )Y M[9X 9X >\\F\\ H[C`    'a    Ca$Y 9UAV:WAU;W<W LX<\\!X *X*X,X -X 0X6f+X/X'X -X -XN[ :X -XEVHVEX0XCX"
"EX)X%X.s KX%X.o 6h <X <X/X!X@X GWDVCVDW*_ 4X -Z >W )V $W       6i JX5X$X -X5X V2W LW 1W3W MW6W MW ,W ,WLY 9W ,W7W7W=W6W!X4X NX5X$X5X MW .[ .W ,W6W KW>"
"W FWEVJVEW#a >W?X 8Z 4\\ 8V  K[ =i<V  0S=Y=S0X:[ KW@^ IfMW HW4W MY .W6W JW@W =XKX CW6W W#W2WCWCW!W=W JWCWCW\"X4X%X4X ?W >W2W IW<W :Y @X 0X%X1X?X?X-X0X&X"
"BXBX-X%X1~` GV H~` GV H~` GV   DX 3XAS ?r DV8V =\\ <V 2V;X   DSFV'S4W /XFX @~X  .S@VIX;S    (V Ii 8Z   5W6W D_GU IX   4g 3Y .XFX HgGV;TNU<gGVFQ@W;Z=V;T"
"NU3Y 1W<W GW<W GW<W GW<W GW<W GW<W GX>X X *X -X -X -X -X -X -X -X ,X*X-XCXEX)X%X1X%X1X%X1X%X1X%X H_ LX@W<X.X/X'X/X'X/X'X/X GX <X7X NWD\\ 8i >i >i >i >i"
" >i >i3WBX ,V2W!V2W!V2W!V2W NW ,W ,W ,W .W4W MW6W!X4X\"X4X\"X4X\"X4X\"X4X M~Y2X@VIW NW6W MW6W MW6W MW6W KW?X GX5X NW?X     LVLuKU/VLuKU/V@^@U/V@Y;U/V=X=U&"
"V 2X?W     8X CWBT   ?~R*~X)~Q%}(V4W W4W FXHX ?XDX K~^               $X   ,X   'WCV Ii &VEe:XEZ>W  /W !W +T 4~W      5V 1X4X >X )Y )[ KW=X (Y N[9Y ;Y "
"?Z@Z I]Gb    '^    =^$X 9U@V:WAU<X<X MX9Z\"X *X*X,X -X 0X6f+X/X'X -X -XM[ ;X -XEVHVEX0XBWEX)X%X.r JX%X.q 4e =X <X/X!X@X GXFVAVFX*` 5X .Z =W )V $W      "
" :m JW3W$W ,W3W!W2W LW 1W3W MW6W MW ,W ,WMY 8W ,W7W7W=W6W!W2W NW3W$W3W MW -^ 2W ,W6W KX@X FWEVJVEW\"_ <W@W 7Y :b 7V  Jb FmAX  0S<W<S0W8Y JW<[ KYHVMV GV"
"3X MZ 0W6W IVAX >XIW CW6W!W!W3WCWCW!W=W JWCWCW\"W2W%W3X ?W >W2W JW;X <Y ?X 0X&Y1X?X?X-X0X&YCXCY-X%X2~a GV H~a HV I~b HV   DX 3W@S ?r DV8V <Z ;V 2W;W   "
"DSFV'S  <XFX  =V  .S@VGW<S    (V      \"W6W A\\GU IX       2XFX *V;TMU LV2V V;TMU4Z 2X<X IX<X IX<X IX<X IX<X IX<X IX=X X *X -X -X -X -X -X -X -X ,X*X-XB"
"WEX)X%X1X%X1X%X1X%X1X%X G] KX@V;X.X/X'X/X'X/X'X/X GX <X8Y NWC\\ =m Bm Bm Bm Bm Bm Bm3WBW ,W2W\"W2W\"W2W\"W2W NW ,W ,W ,W /X4X NW6W!W2W\"W2W\"W2W\"W2W\"W2W M~Y"
"2W@VHW NW6W MW6W MW6W MW6W JW@W FW3W MW@W     KVLuKU/VLuKU/VA`AU/VAY:U/V=X=U&V 1W@X     9X BWBS   >~R+~Z*~P#{'V4W W4W FXHX ?XDX K~^               $X  "
" ,X   'VBV Gi (VFg;WCZ?W  /W !W +T 4~W      6W 1X4X >X *Y &Z LW=X (Y NZ7X ;X ?Z>Z ImNX    '[    8\\%Y 9UAW:WAU<W:W MX7Y#X *X*X,X -X 0X6f+X/X'X -X -XL[ "
"<X -XEWJWEX0XBXFX)X%X.p HX%X.r 0a >X <X/X XBX FXFVAVFX+b 6X /Z <W )W %W       =p JW3W$W ,W3W!| LW 1W3W MW6W MW ,W ,WNY 7W ,W7W7W=W6W!W2W NW3W$W3W MW -"
"b 6W ,W6W JW@W EWFVHVFW!] ;WAX 8Y 9` 5V  H` HrG[  0S<W<S0W8Y JW:Y KXF^ HW2W Kc ;W6W IVAX >XIW CW6W!W!W3WCWCW!W=W JWCWCW\"W2W%W2W ?W >W2W JW:W =Y >X 0Y'"
"X0X?X?X-X0X%XCXCX,X%X2~a GV H~a HV I~b HV   DX 3W@S ?r DV8V <Z   FW;W   DSFV'S  =XFX  <V  .S@VFW=S    (V      \"W6W <WGU IX       1XFX +V;SLU LV2V V;SL"
"U5Z 1W:W IW:W IW:W IW:W IW:W IX<X IX=X X *X -X -X -X -X -X -X -X ,X*X-XBXFX)X%X1X%X1X%X1X%X1X%X F[ JXAW;X.X/X'X/X'X/X'X/X GX <X8X MWB] Bp Ep Ep Ep Ep "
"Ep E~eBW ,|\"|\"|\"| NW ,W ,W ,W /W2W NW6W!W2W\"W2W\"W2W\"W2W\"W2W M~Y2WAWHW NW6W MW6W MW6W MW6W JWAX FW3W MWAX     KV<V=V/V#V/VBbCV/VBY:V/V=X>V&V 1XAW     9"
"X @WDT   ?~S+~Z)}!y'W4W W4W FWFW >WDW J~^               *r   ?V   &VBV Eh *VEXIX<XBZ@W  /W !W +T 4~W  5f   8V 0X4X >X +Y $Z NW<X 'X NZ7X ;X ?X:X HkMX "
"   '[    7[%X 8UAV8VAU=X:X NX6X#X *X*X,X -X 0X6f+X/X'X -X -XK[ =X -XDVJVDX0XAWFX)X%X.m EX%X.XA\\ -^ ?X <X/X XBX FXFVAVFX,c 6X /Y ;W (V %W       ?r JW3W"
"$W ,W3W!| LW 1W3W MW6W MW ,W ,a 6W ,W7W7W=W6W!W2W NW3W$W3W MW ,e :W ,W6W JW@W DWGVHVGW N[ 9WBW 8Y 8^ 3V  F^ I~X  0S;U;T1W8Y JW8X MXC\\ HW2W Ia ;W6W IWB"
"W >XHX DW6W!W<W<W3WCWCW!W=W JWCWCW\"W2W%W2W ?W >W2W KX:X ?Y =X /X'X0Y@X@Y-X0X%YDXDY,X%X2~a GV H~a HV I~b HV   DX 3W@S ?r DV8V ;X   DW;V   DSFV'S  >XFX "
" ;V  .S@VFW=S    (V      \"W6W :UGU IX       0XFX -V;TLU MV0U!V;TLU6Y 0X:X KX:X KX:X KX:X KX:X KX:X JW<X X *X -X -X -X -X -X -X -X ,X*X-XAWFX)X%X1X%X1X"
"%X1X%X1X%X F[ JXBW:X.X/X'X/X'X/X'X/X GX <X9Y MWA] Er Gr Gr Gr Gr Gr G~gBW ,|\"|\"|\"| NW ,W ,W ,W /W2W NW6W!W2W\"W2W\"W2W\"W2W\"W2W M~Y2WBWGW NW6W MW6W MW6W "
"MW6W IWBW EW3W LWBW     IU<V=V.U#V.UCdDV.UCY9V.U=X>V&V 1XBX     :X ?WDT   ?~S,~[({ x&W4W W4W FWFX ?XFX JV                \"q   >V   &VBV Af -VEXGX=W@ZB"
"W  .W !W +T 4~W  5f   8V 0X4X >X ,Y \"Y W;X 'X NZ7X <Y @Y:Y HiLX    '^    =^%X 8UAV8VAU=X:X NX5X$X *X*X,X -X 0X(X+X/X'X -X -XJ[ >X -XDVJVDX0XAXGX)X%X.i"
" AX%X.X>Z ,\\ ?X <X/X NWBW DWFVAVFW+XMY 7X 0Z ;W (V %W       @s JW3W$W ,W3W!| LW 1W3W MW6W MW ,W ,` 5W ,W7W7W=W6W!W2W NW3W$W3W MW +g =W ,W6W JXBX DWGVH"
"VGW N[ 9WBW 9Y 7^ 3V  F^ I[Gr  /S;U;T1W8X IW7X NWA[ HW2W F^ ;W6W HVCX >XGW DW6W!W<W<W3WCWCW!W=W JWCWCW\"W2W%W2W ?W >W2W KW9X ?Y =X /X'X/X@X@X,X0X$YEXEY"
"+X%X2~a GV H~a HV I~b HV   DX 3W@S 6X 3V8V ;X   DX<V   DTFV)T  >WEW  :V  .TAVEW?T    (V      \"W6W :UGU IX       /WEW .V;TKU NV/U\"V;TKU7Y /X:X KX:X KX:"
"X KX:X KX:X KX:X KX<X X *X -X -X -X -X -X -X -X ,X*X-XAXGX)X%X1X%X1X%X1X%X1X%X G] KXCW9X.X/X'X/X'X/X'X/X GX <X9Y MW?] Hs Hs Hs Hs Hs Hs H~hBW ,|\"|\"|\"|"
" NW ,W ,W ,W /W2W NW6W!W2W\"W2W\"W2W\"W2W\"W2W M~Y2WBVFW NW6W MW6W MW6W MW6W IWBW EW3W LWBW     IU<V=V.U#V.UDYMZEV.UDY8V.U#V&V 0WBX     ;X >WDS   >~T-~\\(y"
" Mw&W4W W4W GXFX ?XFX JV                #r   >V   'WCV <c .VEWEW=W?ZCW  .W !W   :~W  5f   9W 0X4X >X -Y  Y!W;X 'Y Y5X =X @Y8Y HgKX    'a    Ca%X 8UAV8"
"VAU=W8W NX4X%X *X+Y,X -X 0X(X+X/X'X -X -XI[ ?X -XDWLWDX0X@WGX)X&Y.X 0X&Y.X=Y *[ @X <X/X NXDX DXHW@VHX,YMZ 8X 1Z :W (W &W       At JW3W$W ,W3W!| LW 1W3"
"W MW6W MW ,W ,` 5W ,W7W7W=W6W!W2W NW3W$W3W MW )g ?W ,W6W IWBW CWGVHVGW MY 8WCX :Y 6` 5V  H` IW@m  -S;V<T1W8X IW7X W@[ HW2W Ia ;W6W HVCW >XFX EW6W!W<W<"
"W3WCWCW!W=W JWCWCW\"W2W%W2W ?W >W2W KW8W @Y <X /X'X/X@X@X,X0X#YFXFY*X&Y2~a GV H~a HV I~b HV   DX 3W@S 6X 3V8V ;X   CX=V   CSFV)S  =WEW  :V  -SAVDW@S   "
" 'V      \"W6W :UGU IX       /WEW .V<TJU NV/U\"V<TJU8Z /W8W KW8W KW8W KW8W KW8W KX:X KX<X X *X -X -X -X -X -X -X -X ,X+Y-X@WGX)X&Y1X&Y1X&Y1X&Y1X&Y H_ LX"
"DW9Y.X/X'X/X'X/X'X/X GX <X:Y LW>] Jt It It It It It I~iBW ,|\"|\"|\"| NW ,W ,W ,W /W2W NW6W!W2W\"W2W\"W2W\"W2W\"W2W M~Y2WCVEW NW6W MW6W MW6W MW6W IWCX EW3W L"
"WCX     IV=V=V.V$V.VFYKZFV.VFY7V.V$V&V 0XCW     ;Y =WFT   >~T-~\\'w Ku%W4W W4W GXEW >WFW IV                #q   =V   6~X JSN^ /VEWCW?W=ZDW  .W !W   :~W"
"  5f   9V /X4X >X .Y  MX\"W:X &X Y5X >Y @X6X FcJX    &d    Id%X 8UAV8VAU>X8X X4X$X +X+X+X -X /X)X+X/X'X -X -XH[ @X -XCVLVCX0X@XHX(X'X-X /X'X-X<Y *Z @X "
"<X/X NXDX DXHV?VHX-YKY 8X 2Z 9W 'V &W       B]?W JW3W$W ,W3W!| LW 1W3W MW6W MW ,W ,a 6W ,W7W7W=W6W!W2W NW3W$W3W MW 'g AW ,W6W IWBW CWHVFVHW NZ 7WDW :Z"
" 6a 6V  Jb IU;i  ,S;V<S0W7W IW6W W?Z HW2W Kc ;W6W HWEX >XFX EW6W!W<W<W3WCWCW!W=W JWCWCW\"W2W%W2W ?W =V2V KX8X BY ;X /Y)Y/X@X@X,X0X#YFXGZ)X'X0~` GV H~` "
"GV H~` GV   DX 3W@S 6X 3V8V M|  &Z?V   CSFV)S:m AXFX  ;V  -SAVDW@S    'V      \"W6W :UGU      *m 5XFX /V;SIU V.T\"V;SIU9Z /X8X MX8X MX8X MX8X MX8X MX8X "
"MX;X NX +X -X -X -X -X -X -X -X ,X+X,X@XHX(X'X/X'X/X'X/X'X/X'X Ha LXFW8X-X/X'X/X'X/X'X/X GX <X;Z LW<\\ L]?W J]?W J]?W J]?W J]?W J]?W J]?{BW ,|\"|\"|\"| NW"
" ,W ,W ,W /W2W NW6W!W2W\"W2W\"W2W\"W2W\"W2W M~Y2WDVDW NW6W MW6W MW6W MW6W HWDW DW3W KWDW     HV=V>V-V%V-VGYIZHV-VGY7V-V%V%V /WDX     ;X <WFT   >~T-~\\'v Is"
"$W4W W4W GWDX ?XGW HV                %r   =V   6~X JSJ[ 0VEVAV?W<ZFW  -W !W   \"V   Lf   9V /X5X =X /Z  MX\"V9X &X NX5X >X ?X6X D`IX    $d    Ne#X 8UAV8"
"VBU=x X4X$X +X+X+X -X /X)X+X/X'X -X -XG[ AX -XCVLVCX0X?WHX(X'X-X /X'X-X;Y *Y @X <X/X MXFX CXHV?VHX-XIY 9X 3Z 8W 'V &W       CZ;W JW3W$W ,W3W!| LW 1W3W"
" MW6W MW ,W ,b 7W ,W7W7W=W6W!W2W NW3W$W3W MW %f BW ,W6W IXDX BWIVFVIW N\\ 8WEX :Y .[ 7V  K\\ BT8e  *S<X=S0W7V HW6X\"W=X GW2W Me ;W6W GVEX >WDW EW6W!W<W<W"
"3WCWCW!W=W JWCWCW\"W2W%W2W ?W =W4W KW6W CY :X .X)X.YAXAY,X0X\"ZHXHZ(X'X/Y  AV  BY FV GY%Y FV   DX 3W@S 6X 2V:V L|  %ZAV   BSEV*S:m @XFX  <V  -SAVCWAS   "
" 'V      \"W6W :UGU      *m 6XFX .V<TIU V/U\"V<TIU9Y .x Mx Mx Mx Mx Mx Mu NX +X -X -X -X -X -X -X -X ,X+X,X?WHX(X'X/X'X/X'X/X'X/X'X Ic MXGW7X-X/X'X/X'X/"
"X'X/X GX <X=[ KW:[ NZ;W KZ;W KZ;W KZ;W KZ;W KZ;W KZ;{BW ,|\"|\"|\"| NW ,W ,W ,W /W2W NW6W!W2W\"W2W\"W2W\"W2W\"W2W  &WEVCW NW6W MW6W MW6W MW6W HWEX DW3W KWEX "
"    GV>V>V,V&V,VIYGZIV,VIY6V,V&V&W /XEW     N~X'VGT   =~T-~\\&u Ir#W4W NV4W HXDX ?XHX HV                 KX   ,V   6~X JSHZ 2VDVAV?W;ZGW  -W !W   \"V   "
"Lf   :W .X6X =X 0Z  LY#~ /X NX5X >X @X5Y AYFX    !d >~X >d X 8UAV8VBU>z!X3X%X +X+X+X -X /X)X+X/X'X -X -XF[ BX -XCWNWCX0X?XIX(X'X-X /X'X-X:X )Y AX <X/X"
" MXFX BWHV?VHW-YIY 9X 3Y 7W 'W 'W       CX9W JW3W$W ,W3W!W 'W 1W3W MW6W MW ,W ,WNZ 8W ,W7W7W=W6W!W2W NW3W$W3W MW !c CW ,W6W HWDW AWIVFVIW N] 8WFW :Y *"
"Y 8V  KY ?R3`  (S<X=S0W7V HW5W\"W=X GW2W N[ 0W6W GWFW >XDX FW6W!W<W<W3WCWCW!W=W JWCWCW\"W2W%W2W ?W =W4W LX6X DY :X .X)X-XAXAX+X0X!ZIXIZ'X'X.Y  BV  CY EV"
" FY'Y EV   DX 3W@S 6X 2V:V L|  $[CV   BTFW,T:m ?XFX  =V  -TBVBVBT    'V      \"W6W :UGU      *m 7XFX .V<THU!V/U\"V<THU:Y .z z z z z Nx Nv NX +X -X -X -X"
" -X -X -X -X ,X+X,X?XIX(X'X/X'X/X'X/X'X/X'X Je NXGV6X-X/X'X/X'X/X'X/X GX <X@^ KW9[ X9W KX9W KX9W KX9W KX9W KX9W KX9W MW ,W ,W ,W ,W )W ,W ,W ,W /W2W N"
"W6W!W2W\"W2W\"W2W\"W2W\"W2W  &WFVBW NW6W MW6W MW6W MW6W GWFW CW3W JWFW     FV>V?W,V'W,VJYEZKW,VJY6W,V'W&W /XFX     N~X'WHT   =~T-~\\%s Gp\"W4W NV4V GXCW >WH"
"X HW                 LX   ,V   6~X JSGY 3VDWAW@W:ZIW  ,W !W   \"V   Lf   :W .X6X =X 1Z  JX#~ /X NX5X ?Y @X4X .X     Md A~X Ad LX 8UAV8VBU>z!X3X%X +X+X+"
"X -X /X)X+X/X'X -X -XE[ CX -XBVNVBX0X>WIX(X'X-X /X'X-X9X *Y AX <X/X MXFX BXJW?WJX.YGY :X 4Z 7W 'W 'W       DX8W JW3W$W ,W3W!W 'W 1W3W MW6W MW ,W ,WLY "
"9W ,W7W7W=W6W!W2W NW3W$W3W MW  K_ DW ,W6W HXFX AWIVFVIW ^ 8WFW ;Y (Y 9V  LY >Q.X  $T>Z?T0W8W HW5W\"W<W GW2W Y -W6W GWGX >WCX FW6W!W<W<W3WCWCW!W=W JWCWC"
"W\"W2W%W2W ?W =W4W LX6X EY 9X .Y+Y-YBXBY+X0X ZJXJZ&X'X-Y  CV  DY DV EY)Y DV   DX 3W@S 6X 2W<W L|  #\\FW   ASFW,S9m >XFX  >V  ,SBVBWCS    &V      \"W6W :U"
"GU      *m 8XFX .V<TGU\"V.U#V<TGU;Y -z z z z z z v NX +X -X -X -X -X -X -X -X ,X+X,X>WIX(X'X/X'X/X'X/X'X/X'X KZMZ XHW6X-X/X'X/X'X/X'X/X GX <u JW7Y!X8W "
"LX8W LX8W LX8W LX8W LX8W LX8W MW ,W ,W ,W ,W )W ,W ,W ,W /W2W NW6W!W2W\"W2W\"W2W\"W2W\"W2W  &WGWBW NW6W MW6W MW6W MW6W GWFW CW3W JWFW     FW?V?V+W(V+WKXCY"
"KV+WKX5V+W(V%W .WFX     N~X'WHT   =~T-~\\$q Eo\"W4W NV4V GWBW >XIW GW                 LX       ;~X JSFX 3VDV?V@W9ZJW  +V \"W   !V       V -X6X =X 2Z  IX#"
"~ /X NX5X ?X ?X4X .X     Jd D~X Dd IX 8UAV8VCV>z!X3X%Y ,X,Y+X -X /Y*X+X/X'X -X -XD[ DX -XBVNVBX0X>XJX(Y)X,X /Y)X,X9Y *X AX <X/X LXHX AXJV=VJX.XEY ;X 5"
"Z 6W &V 'W       DW7W JW3W$W ,W3W!W 'W 1W3W MW6W MW ,W ,WKY :W ,W7W7W=W6W!W2W NW3W$W3W MW  H\\ DW ,W6W GWFW @WJVDVJW!` 9WGX <Y &X 9V  LX =P   (T?\\@T0W8"
"X IW5W\"W<W GW2W X ,W6W FVGW >XBW FW6W!W<W<W3WCWCW!W=W JWCWCW\"W2W%W2W ?W =W4W LW4W FY 8X -X+X+YCXCY*X0X N\\MXM\\%Y)X+Y  DV  EY NQFVFQ Y+Y CV   DX 3W@S 6X"
" 1V<V K|  ![HW   @TFW.T9m =XFX  ?V  ,TCVAVDT    &V      \"W6W :UGU      *m 9XFX -V<SFU\"V/U\"V<SFU;X ,z z z z z z v NY ,X -X -X -X -X -X -X -X ,X,Y,X>XJX"
"(Y)X.Y)X.Y)X.Y)X.Y)X KZKZ!YJW6X,X/X'X/X'X/X'X/X GX <t IW6Y\"W7W LW7W LW7W LW7W LW7W LW7W LW7W MW ,W ,W ,W ,W )W ,W ,W ,W /W2W NW6W!W2W\"W2W\"W2W\"W2W\"W2W "
" &WHWAW NW6W MW6W MW6W MW6W GWGX CW3W JWGX     EV?V@W*V)W*VJVAWKW*VJV5W*V)W%W .XGW     M~X&WJT   <~S,kNn#o Cm!W4W NV4V HXBX ?XJX FW                 MY"
"       <~X JSEX 5VCV?V@W8ZLW  *W #W   !V       V -X6X =X 3Z  HX#~ /X NX5X @Y ?X4X /X     Ge G~X Ge GX 8UAV9WCU>|\"X3X$X ,X,X*X -X .X*X+X/X'X -X -XC[ EX"
" -XA\\AX0X=WJX'X)X,X .X)X,X8X *X AX <X/X LXHX AXJV=VJX/YEY ;X 6Z 5W &V 'W       DW7W JW3W$W ,W3W!W 'W 1W3W MW6W MW ,W ,WJY ;W ,W7W7W=W6W!W2W NW3W$W3W M"
"W  EZ EW ,W6W GWFW ?WKVDVKW!b 9WHW <Y $W 9V  LW     BTAVNUAT/W8X IW5W#W;V FW2W!X +W6W FWIX >XBX GW6W!W<W<W3WCWCW!W=W JWCWCW\"W2W%W2W ?W =W4W MX4X HY 7X"
" -Y-Y+ZDXDZ*X0X Mt#X)X*Y  EV  FY NSGVGS Y-Y MQFVFQ   X 3W@S 6X 1W>W 9X   =\\KW   >SEW<PCS  6XFX  @V  +SCVAWES    %V      \"W6W :UGU        &XFX -V<TFU#V"
"/U\"V<TFU<X ,|\"|\"|\"|\"|\"|\"w MX ,X -X -X -X -X -X -X -X ,X,X+X=WJX'X)X-X)X-X)X-X)X-X)X LZIZ!XKW5X,X/X'X/X'X/X'X/X GX <s HW5X\"W7W LW7W LW7W LW7W LW7W LW7W"
" LW7W MW ,W ,W ,W ,W )W ,W ,W ,W /W2W NW6W!W2W\"W2W\"W2W\"W2W\"W2W  &WIW@W NW6W MW6W MW6W MW6W FWHW BW3W IWHW     DW@VAW)W+W)WJT?UKW)WJT5W)W+W$W -WHX     "
"M~X&WJT   ;eMQMe+jNQNj!m Bl W4W NW6W HXBX >WJX FW                 LX       <~X JSEX 6WCV?V@W7ZMW  *W #W   !V      !W -X6X =X 4Z  GX#~ /X NX5X @X >X4X "
"/X     De J~X Je DX 8U@V:WDV>|\"X3X$X ,X-Y*X -X .X*X+X/X'X -X -XB[ FX -XA\\AX0X=XKX'X*Y,X .X*Y,X8Y +X AX <Y1Y KWHW ?WJV=VJW/YCY <X 7Z 4W &W (W       EW6"
"W JX5X$X -X5X!X (W 0W5X MW6W MW ,W ,WIY <W ,W7W7W=W6W!X4X NX5X$X5X MW  CX EW ,W6W GXHX ?WKVDVKW!XNY :WIX =Y #X :V  MX     BUCVMVBT/W9Y IW5W#W<W FW3X!W"
" *W6W EVIX ?X@W GW6W!W=Y=W3XDWDX!W=W JWCWCW\"X4X%X4W >W <W6W LX4X HY 7X ,X-X)ZEXEZ)X0X Lr\"X)X)Y  FV  GY NUHVHU Y/Y MSGVGS  !X 3XAS 6X 0W@W 8X   ;\\NW   "
"=TEX@RDT  5XFY  BV  +TDV@WGT    %V      \"W6W :UGU        (YFX ,V=TEU#V0U!V=TEU<X ,|\"|\"|\"|\"|\"|\"w MX ,X -X -X -X -X -X -X -X ,X-Y+X=XKX'X*Y-X*Y-X*Y-X*Y-"
"X*Y MZGZ\"XLW5Y,Y1Y'Y1Y'Y1Y'Y1Y GX <r GW4X$W6W MW6W MW6W MW6W MW6W MW6W MW6X NX -X -X -X -X *W ,W ,W ,W /W2W NW6W!X4X\"X4X\"X4X\"X4X\"X4X  &WIV@X NW6W MW6W"
" MW6W MW6W FWIX BX5X IWIX     CWAVAW(W,W(WJR=SJW(WJR4W(W,W$W -XIX     M~X&WJS   :dLQLd+iMQNj!l @j NW4W NW6W HW@W >WJW DW                 MX       .VCV"
" :SDW 6VBV?V@W6b  )W #W   !V      !V +X8X <X 5Z  FX#~ /X MW5X @X >X4X /X     Ad L~X Ld AX 8VAV:WDU=|\"X3X$Y -X-Y*X -X .Y+X+X/X'X -X -XA[ GX -XA\\AX0X<WK"
"X'Y+X+X .Y+Y,X7X +X AX ;X1X JXJX ?XLW=WLX/XAY =X 7Y 3W %V (W       EW7X JX5W\"W ,W5X W (W 0W5X MW6W MW ,W ,WHY =W ,W7W7W=W6W W4W MX5W\"W5X MW  BX FW ,W6"
"W FWHW >WKVDVKW\"XLX 9WJW =Z #X :V  MX     AUEVKVDU/X:Y IW5W#W<W EW4W!X *W6W EVJX >X@W GW6W!W=Y=W2WDWDW W=W JWCWCW\"X4W#W4W >W <W6W LW2W IY 6X ,Y/Y(ZFXF"
"Z(X0X Kp!Y+X'Y  GV  HY NWIVIW Y1Y MUHVHU  \"X 2WAS 6X 0YDY 8X   :c   <TE[FUDS  3XFY  CV  *SDV@WGS    $V      \"W6W :UGU        )YFX ,V=TDU$V0V\"V=TDU=X +"
"|\"|\"|\"|\"|\"|#x MY -X -X -X -X -X -X -X -X ,X-Y+X<WKX'Y+X,Y+X,Y+X,Y+X,Y+X MZEZ#YNW4X*X1X%X1X%X1X%X1X FX <p EW4X$W7X MW7X MW7X MW7X MW7X MW7X MW7Y MW ,W "
",W ,W ,W *W ,W ,W ,W .W4W MW6W W4W W4W W4W W4W W4W  $WKV?W MW6W MW6W MW6W MW6W EWJW AX5W GWJW     BXBVBW'X.W'XJP;QJW'XJP4W'X.W#V ,XIW     L~X%WLT   :d"
"LQLc*iMQMi k ?i NW4W NW6W IX@X ?XLX DW                 MY       0VBV :SDW 7VAV?V@X6a  )W #W   !V      !V +X8X <X 6Z  EX#~ 0Y MW5X AY >X4X 0X     =d ~X"
" d   LUAW<XEV>X2X#X3X#X -X.Y)X -X -X+X+X/X'X -X -X@[ HX -X@Z@X0X<XLX&X+X+X -X+X+X7Y ,X AX ;X1X JXJX ?XLV;VLX0YAY =X 8Z 3W %V (W       EW7X JX5W\"W ,W5X"
" W (W 0W5X MW6W MW ,W ,WGY >W ,W7W7W=W6W W4W MX5W\"W5X MW  BX FW ,W7X FWHW >WLVBVLW#YKX :WJW =Y !W :V  MW     @VHXJWHV-W:Y IW5W#W<W EW4W!W )W6W EWKX ?X"
"?X HW6W!X>Y>W1WDWDW W=W JWCWCW\"X4W#W4W >W <W6W MX2X KY 5X +Y1Y'[GXH\\(X0X Jn NX+X&Y  HV  IY NYJVJY Y3Y MWIVIW  #X 2WAS 6X 0[H[ 8X :V %`   :TEiET  2YGY "
" DV  *TEV?WIT    $V      \"W6W :UGU        *YGY ,V<SCU%V0V\"V<SCU=X ,X2X$X2X$X2X$X2X$X2X$X2X$X8X LX -X -X -X -X -X -X -X -X ,X.Y*X<XLX&X+X+X+X+X+X+X+X+X"
"+X NZCZ#`3X*X1X%X1X%X1X%X1X FX <m BW3W$W7X MW7X MW7X MW7X MW7X MW7X MW7Y MW ,W ,W ,W ,W *W ,W ,W ,W .W4W MW6W W4W W4W W4W W4W W4W 5Z IWLV>W MW7X MW7X "
"MW7X MW7X EWJW AX5W GWJW     AXCVCW%X0W%X0W%X0W%X0W\"V +WJX     ?X 2WLT   9bKQKb)gLQMh Mi =g MW4W MV6W IX@X ?XLX CW                 MX       0VBV :SDW "
"7VAV?V@X5_  (W #W   !V      \"W +X8X <X 7Z  DX 5X 'X LX7X @X =X4X 0X     ;e   Le   JUAW<XFV=X1W#X3X#Y .X.Y)X -X -Y,X+X/X'X -X -X?[ IX -X@Z@X0X;XMX&Y-Y+"
"X -Y-Y+X6X ,X AX ;X1X IXLX >XLV;VLX1Y?Y >X 9Z 2W %W )W       EW7X JX5W\"X -W5X X )W 0X7Y MW6W MW ,W ,WFY ?W ,W7W7W=W6W W4W MX5W\"W5X MW  AW FW ,W7X FXJX"
" =WMVBVMW#YJY ;WKX >Y  W :V  MW     ?dId,W;Z IW5W#W=W DW4W!W )W6W DVKW >X>W HW6W W>Y>W1WDWDW W=W JWCWDX\"X4W#W4W >W ;V7W LX2X LY 4X *X1X%]JXJ]'X0X Hj L"
"Y-Y%Y  IV  JY LYKVKY MY5Y MYJVJY  $X 2XBS 6X 2q 9X :V #\\   7TDgFT  /XFX  EV  )TFV>VJT    #V      \"W6W :UGU        +XFX *V=TCU%V1V!V=TCU=X ,X1W$X1W$X1W"
"$X1W$X1W$X2X%X7X LY .X -X -X -X -X -X -X -X ,X.Y*X;XMX&Y-Y+Y-Y+Y-Y+Y-Y+Y-Y ZAZ$_3Y*X1X%X1X%X1X%X1X FX <i >W3W$W7X MW7X MW7X MW7X MW7X MW7X MW7Z NX -X "
"-X -X -X +W ,W ,W ,W .W4W MW6W W4W W4W W4W W4W W4W 5Z IWMV=W MW7X MW7X MW7X MW7X EWKX AX5W GWKX     @XDVDX$X2X$X2X$X2X$X2X\"V +XKW     ?X 1WMT   7`JQKa"
"'fLQLf Kg <f LW4W MW8W HW>W >WLW BX                 NY       1VBV :SDW 8V@V?V?W4]  &V $W    V      \"V *Y:Y <X 8Z  DY 5X 'X KW7X @X =X5Y 1Y     8e  #e "
"  GU@W>YGW>X0X$X4Y\"Y /X/Y(X -X ,Y-X+X/X'X -X -X>[ JX -X@Z@X0X;XMX%Y/Y*X ,Y/Y*X6Y -X AX ;Y3Y IXLX =WLV;VLW0X=Y ?X :Z 1W $V )W       EW8Y JY7X\"X -X7Y X "
")W 0X7Y MW6W MW ,W ,WEY @W ,W7W7W=W6W X6X MY7X\"X7Y MW  AW FW ,X8X EWJW <WMVBVMW#XHX :WLW >Y  NW :V  MW     >bGc,W;[ JW6X#W=W DX6X!W )W6W DVLX >W=X IW7"
"X W>Y>W1XEWEX W=W IWDWDW!Y6X#X6X >W ;W8W MX0X MY 4X *Y3Y$^LXL^&X0X Ff IY/Y#Y  JV  KY JYLVLY KY7Y KYKVKY  #X 2XBS 6X 3t ;X :V ![   8TCfFT  .XFX  FV  )U"
"GV>WKT            MW7X :UGU        ,XFX *V=TBU&V2W!V=TBU=X -X0X&X0X&X0X&X0X&X0X&X0W%X7X KY /X -X -X -X -X -X -X -X ,X/Y)X;XMX%Y/Y)Y/Y)Y/Y)Y/Y)Y/Y Z?Z$"
"^4Y)Y3Y%Y3Y%Y3Y%Y3Y FX <X -W3W$W8Y MW8Y MW8Y MW8Y MW8Y MW8Y MW8[ NX -X -X -X -X +W ,W ,W ,W .X6X MW6W X6X X6X X6X X6X X6X 5Z I_=X MX8X MX8X MX8X MX8X "
"DWLW @Y7X FWLW     >XEVFY\"X5Y\"X5Y\"X5Y\"X5Y!V *WLX     @X /WNT   7`JQJ_&eKQKe Je :d KW4W MW8W HW>X ?XNX AX                 Y       1VCV 9SDW 9V?V?V?X4\\ "
" &W %W    V      \"V )X:X ;X 9Z  CX 4X (Y KW7X AX <Y6Y 1X     4e  )e   DVAX@ZHW=X0X$X4Y\"Y*P&X0Z(X -X ,Y-X+X/X'X -X -X=[ KX -X?X?X0X:XNX%Y/Y*X ,Y/Y*X5X "
".Y AX :X3X HXLX =XNW;WNX1Y=Y ?X ;Z 0W $V )W       EW8Y JY7W W ,W7Y NX *W /W8Z MW6W MW ,W ,WDY AW ,W7W7W=W6W NW6W LY7W W7Y MW  AW FW ,X9Y EWJW <WMVBVMW"
"$XFX ;WMX ?Y  MW :V  MW     =`Ea+X<[ JW6W\"W>W BW6W W )W6W DWMX ?X=X IX8X W?[?W0WEWEW NW=W IWDWDW!Y6W!W6W =W ;W8W MX0X NY 3X )Y5Y\"z%X0X C` FY/Y\"X  JV  "
"KX HYMVMY IX7X IYLVLY  \"X 1XCS 6X 4v <X :V  [   8TBbET  ,WEW  FV  (T$T            LX8X :UGU        ,WEW )V=m,V3W V=mCX -X0X&X0X&X0X&X0X&X0X&X0X&X7X KY"
"*P&X -X -X -X -X -X -X -X ,X0Z)X:XNX%Y/Y)Y/Y)Y/Y)Y/Y)Y/Y!Z=Z%]3Y(X3X#X3X#X3X#X3X EX <X -W3W$W8Y MW8Y MW8Y MW8Y MW8Y MW8Y MW8[ MW ,X -X -X -X ,W ,W ,W "
",W -W6W LW6W NW6W MW6W MW6W MW6W MW6W 4Z H^=W LX9Y MX9Y MX9Y MX9Y DWMX @Y7W EWMX     =Y8Y Y8Y Y8Y Y8Y Y8Y V *WLX     AX .WNT   6^IQI]$cKRJc Id 8c KW4W"
" MX:X IX>X ?XNX AY                 Y4P       VBV 9SDW 9V?V?V?Y4Z  %W %W    V      #W )X:X ;X :Z  CY 4X (Y KX9Y AX ;X6X 1Y     1e  /e   @U@XB[JX<X/W$X4"
"X Y,Q&X1Z'X -X +Y.X+X/X'X -X -X<[ LX -X?X?X0X:XNX$Y1Y)X +Y1Y)X5Y /X @X :X4Y GXNX <XNV9VNX2Y;Y @X ;Y /W $W *W       EW9Z JZ9X X -X9Z NX *W /X9Z MW6W MW"
" ,W ,WCY BW ,W7W7W=W6W NX8X LZ9X X9Z MW  AW FW +W9Y EXLX <WNV@VNW%YEX ;WNW ?Y  LW :V  MW     <^C_)W=\\ JX7W\"W>W BX8X W )W6W CVNX >W;W IX8X X@[@X0XFWEW "
"NW=W IWDWEX!Z8X!X8X =W :W:W LX0X Y 2X (Y7Y Nv#X0X ?X AY1Y V  IV  JV FYNVNY GV5V GYMVMY  !X 1XCS 6X 5x =X :V  MZ   8T?ZBT  *VDV  FV  'T&T            KX"
"8X :UGU        ,VDV )V<m-V3V NV<mCX -X/W&X/W&X/W&X/W&X/W&X0X'X6X JY,Q&X -X -X -X -X -X -X -X ,X1Z(X:XNX$Y1Y'Y1Y'Y1Y'Y1Y'Y1Y!Z;Z%[3Y'X4Y#X4Y#X4Y#X4Y EX"
" <X -W3W$W9Z MW9Z MW9Z MW9Z MW9Z MW9Z MW9] NX -X -X -X -X ,W ,W ,W ,W -X8X LW6W NX8X MX8X MX8X MX8X MX8X 4Z H]=X KW9Y LW9Y LW9Y LW9Y CWNW ?Z9X DWNW   "
"  ;Y;Z MY;Z MY;Z MY;Z MY;Z NV *XMW     AY -[   3ZHRH[\"aJRI` Fb 6a JW4W LW:W HX=W >WNX @Y                !Z6Q       VBV KP>SEW 9V>WAW>X3Z  &W %W    V  "
"    #V 'X<X :X ;Z  BY 4X )Y IW9X AY ;Y8Y 2Y     .d  1d   >U?ZH^MZ<X.X%X5Y NY.R&X2Z&X -X *Y/X+X/X'X -X -X;[ MX -X&X0X9a$Z3Y(X *Y3Y(X4X$P-Y @X :Y5Y GXNX"
" <XNV9VNX2X9Y AX <Z /W #V *W       EX:Z JZ9X NX .X9Z MX +W .X;[ MW6W MW ,W ,WBY CW ,W7W7W=W6W NX9Y LZ9X X9Z MW  AW FW +W:Z DWLW :^@^$XDY <WNW @Z  LW :"
"V  MW     ;\\@['X>\\ JX8X\"W?W AX9Y X *W6W CVNX ?X;X JX9Y NW@[@W/XFWFX NW=W IXEWEX!Z8X!X8W ;W ;W;X MX.X\"Y 1X 'Y9Y Lt\"X0X ?X @Y3Y MT  HV  IT Dj ET3T EYNVN"
"Y   X 0XDS 6X 6ZM`LY >X :V  LY   7T)T  (UCU     ET(T            JX9Y :UGU        ,UCU )V;m.V3V NV;mCY7P HX.X(X.X(X.X(X.X(X.X(X.X(X6X IY.R&X -X -X -X -"
"X -X -X -X ,X2Z'X9a$Z3Y&Z3Y&Z3Y&Z3Y&Z3Y!Z9Z&Z3Y&Y5Y#Y5Y#Y5Y#Y5Y EX <X -W3W$X:Z MX:Z MX:Z MX:Z MX:Z MX:Z MX:^ NX -X -X -X -X -W ,W ,W ,W -X8X LW6W NX9Y"
" MX9Y MX9Y MX9Y MX9Y 4Z H\\=Y KW:Z LW:Z LW:Z LW:Z CWNW ?Z9X DWNW     :[@[ K[@[ K[@[ K[@[ K[@[ MV )WNX     AX ,[   1WGRFW N_IRH^ Da 5_ IW4W LX<X HW<W >`"
" >Y                !Y8S   MX   +VBV KQ?SFX 9V=VAV=Y6]  &V &W    NV BX   1X 1V 'Y>Y :X <Z  BY 3X GP3Z IX;Y AX :Y9Z 2X GX -X  7a  1a .X 6V@iNa;X.X%X6Z N"
"Z1T&X4\\&X -X *Z0X+X/X'X -X -X:[ NX -X&X0X9a#Z5Z(X *Z5Z(X4Y%R/Y @X 9Y7Y EWNW :WNV9VNW2Y9Y AX =Z .W #V *W       EX;[ J[;X MY .X;[ MY2P JW .Y=\\ MW6W MW ,"
"W ,WAY DW ,W7W7W=W6W MX:X K[;X MX;[ MW /P4X FX ,X<[ DXNX :^@^%XBX <` @Y  KW :V  MW     8V;W%X?^ KY9X!V@X @X:X NX *W6W C_ >X:W JY;Z NXB]BX.XGWGX MW=W H"
"XFWFX [:X NX:X ;W :W<W LX.X\"Y 1X &Y;Y Ip X0X ?X @Z5Z LR  GV  HR Bh CR1R Cj   NX 0YES 6X 7ZJ\\IY ?X :V  KY   8U+U  'TBT     DU+T            IY;Z :UGU   "
"     ,TBT (V;m.V4V MV;mCY8Q HX.X(X.X(X.X(X.X(X.X(X.X)X5X IZ1T&X -X -X -X -X -X -X -X ,X4\\'X9a#Z5Z%Z5Z%Z5Z%Z5Z%Z5Z\"Z7Z&Z5Z%Y7Y!Y7Y!Y7Y!Y7Y DX <X -W4X$X"
";[ MX;[ MX;[ MX;[ MX;[ MX;[ MX;`3P=Y .Y2P LY2P LY2P LY2P LW ,W ,W ,W ,X:X KW6W MX:X KX:X KX:X KX:X KX:X 3Z GZ<X JX<[ LX<[ LX<[ LX<[ C` ?[;X C`     9_J"
"_ I_J_ I_J_ I_J_ I_J_ LV )`     AX +Z    S <[GRFZ A_ 4^ HW4W KX>X HX<X ?` =Z                \"Y:T   MX   +VCV JSASFX :V<VAV<Y8_  'W 'W    NV BX   1X 2W"
" &X>X 9X =Z 1P2Z 3X GQ5Z GX=Y @X 9Y:Y KP8Z GX -X  4^  1^ +X 5U?gM_9W,W%X7Z L[4U&X6]%X -X )[2X+X/X'X -X -X9[ X -X&X0X8`\"Z7Z'X )Z7Z'X3X%T2Y ?X 9Z9Z E` :"
"_9_3Y7Y BX >Z -W #W +W       DX=\\ J\\=Y LY7P HY=\\ LY5R JW -Y?] MW6W MW ,W ,W@Y EW ,W7W7W=W6W MY<Y K\\=Y MY=\\ MW /R6W DW ,Y=[ CWNW 9^@^&X@X <^ @Y  JW :V "
" MW       HXA` LZ;X V@W ?Y<Y MX +W6W B^ ?X9W JZ<Z NXB]BX.YHWHY MW=W HYGWGY \\<Y NY<X :W :X>X LX.X#Y 0X %Y=Z Gl MX0X ?X ?Z7Z JP  FV  GP @f AP/P Ah   MX "
"/YFSDP BX 8ZFVEY @X :V  JX   7V.U  %SAS     CU.U            HZ<Z :UGU        ,SAS (V:m/V5W MV:mBY;S HW,W(W,W(W,W(W,W(W,W(X.X)X5X H[4U&X -X -X -X -X -X"
" -X -X ,X6]&X8`\"Z7Z#Z7Z#Z7Z#Z7Z#Z7Z\"Z5Z&[8Z$Z9Z!Z9Z!Z9Z!Z9Z DX <X -W4W\"X=\\ LX=\\ LX=\\ LX=\\ LX=\\ LX=\\ LX=b6R<Y7P GY5R KY5R KY5R KY5R LW ,W ,W ,W ,Y<Y KW"
"6W MY<Y KY<Y KY<Y KY<Y KY<Y 3Z GY<Y JY=[ LY=[ LY=[ LY=[ B^ >\\=Y B^     7r Gr Gr Gr Gr KV (_     BX )Y    S 8RBSCR <] 2\\ GW4W KZBZ HX;W >_ <[          "
"      $[=U   MX   ,VBV JUCSHY :V;WCW<[<b  (W 'W    NV BX   1X 2W &Y@Y 9X >Z 0R5Z 2X GT9[ GY?Z AY 9[>[ KR;Z FX -X  1[  1[ (X 5V>dL^9X,X&X9[ J[7W&X9_$X "
"-X (\\6Z+X/X'X -X -X8[!X -X&X0X8`![;[&X ([;[&X3Y&W7[ ?X 8Z;Z D` :^7^3X5Y CX ?Z ,W #W +W       DY?] J]?Y KZ:R GY?] LZ8T JW -ZA^ MW6W MW ,W ,W?Y FW ,W7W7"
"W=W6W LY>Y J]?Y KY?] MW /T9X DX ,Y@] CWNW 9]>]'Y@Y =^ AY  IW :V  MW       HYCXNW L\\>Y VAX >Y>Y LY ,W6W B] >X9X K[>[ MXDVMVDX,YIWIY LW=W GYHWHY N]>Y LY"
">Y :X :X@X LX,X%Y /X $ZAZ Ch KX0X ?X >[;[   ?V   6d   >f   LX /[HSFR BX 9Z3Y AX :V  IX   7V1V  #R@R     BU0U            G[>[ :UGU        ,R@R 'V(U)V6W"
" LV(U<Z>U IX,X*X,X*X,X*X,X*X,X*X,X*W4X G[7W&X -X -X -X -X -X -X -X ,X9_%X8`![;[![;[![;[![;[![;[\"Z3Z(];[\"Z;Z NZ;Z NZ;Z NZ;Z CX <X -WJP;X\"Y?] LY?] LY?] "
"LY?] LY?] LY?] LY?XNZ9T<Z:R GZ8T KZ8T KZ8T KZ8T LW ,W ,W ,W +Y>Y JW6W LY>Y IY>Y IY>Y IY>Y IY>Y 2Z FY>Y HY@] KY@] KY@] KY@] B^ >]?Y A^     6o Do Do Do "
"Do IV (_     CX (Y    S (S ,[ 0[ GW4W J\\H\\ GW:W >^ :\\                %[@W   MX   ,VBV JXFSIZ :V:WEW:\\@e  (V 'V    MV BX   1X 2V $ZDZ 8X ?Z /U;] 2X GV="
"\\ EZC[ @X 7[@[ JT?[ EX -X  /Y  1Y &X 5V=bK\\7X,X&X<^ I]=Z&X=b#X -X ']:\\+X/X'X -X -X7[\"X -X&X0X7_ \\?\\%X '\\?\\%X2X&Z<\\ >X 7[?[ B^ 9^7^4Y5Y CX ?Y +W \"V +W "
"      DZB_ J_CZ I[>T G[C_ K[=W JW ,\\GXNW MW6W MW ,W ,W>Y GW ,W7W7W=W6W KZBZ I_CZ J[C_ MW /W>Z DZ .ZB^ C` 8\\>\\&X>Y =\\ AY  HW :V  MW       GZFYNY N]AZ N"
"WCX <ZBZ JZ:Q EW6W B] ?X7W K\\A^ NYFWMWFY,ZJWJY KW=X H[JWJ[ N_BZ JZBZ 8Y <ZDZ LX,X&Y .X #ZCZ >_ FX0X ?X =\\?\\   >V   5b   <d   KX .\\JSHT BX 8X2X @X :V  "
"IX   5V4U   Q?Q     AV4V            F\\A^ ;UGU        ,Q?Q 'V'U*V6W LV'U<[AW IX,X*X,X*X,X*X,X*X,X*X,X+X4X F]=Z&X -X -X -X -X -X -X -X ,X=b$X7_ \\?\\ N\\?\\"
" N\\?\\ N\\?\\ N\\?\\ X1X(`?\\ [?[ L[?[ L[?[ L[?[ BX <X -WJS@Z\"ZB_ LZB_ LZB_ LZB_ LZB_ LZB_ LZBYM\\>W;[>T F[=W J[=W J[=W J[=W LW ,W ,W ,W *ZBZ IW6W KZBZ GZBZ "
"GZBZ GZBZ GZBZ 1Z F[BZ GZB^ KZB^ KZB^ KZB^ A\\ =_CZ ?\\     3l Al Al Al Al HV (^     BX (X    NS (S ,Z .Y FW4W In GX:X ?^ 9_                (]FZ   MX   "
",VBV J[ISL\\ :V9XGX9^Fi  )W )W    MV BX   1X 3W #[H[ Et Mx MZC_ 1X GZD^ C[G\\ @Y 7^F] IXF] DX -X  ,V  1V #X 4V<^IY5X*X'y G_D^&{!y NX &`B`+X/X'X -X -X6[#"
"w LX&X0X7_ N^E^$X &^E^$X2Y'^C^ =X 7^E^ B^ 8]7]4Y3Y DX @~U&W \"W ,W       C\\HYNW JWNXG\\ H]EX F\\GXNW J]D[ JW +kMW MW6W MW ,W ,W=Y HW ,W7W7W=W6W K]H] IWNX"
"G\\ I\\GXNW MW /[E\\ Be 9[GXNW B^ 7\\>\\'X<X =\\ AX  GW :V  MW       G\\IYM^$`F\\ MWEX ;]H] J]BV EW6W A\\ ?X7X L_GaKP#ZJYMYJZ*[LWL[ KW=Y H\\LWL\\ MWNXG] J]H\\ 7a "
"C[H[ L~W'x MX 1iEi HX CX0X ?X <^E^   =V   4`   :b   JX -^MSLX Lz V0V ?X :V  HW   4V7V   MP>P     @W8W    3~W      :_GaKP @UGU        ,P>P 'V&U+V6V KV&"
"U;]GZ JX*X,X*X,X*X,X*X,X*X,Y,Y,X4y7_D^&y Ny Ny Ny NX -X -X -X ,{\"X7_ N^E^ L^E^ L^E^ L^E^ L^E^ MV/V(dE^ N^E^ L^E^ L^E^ L^E^ BX <X -WJWF[ \\HYNW K\\HYNW K"
"\\HYNW K\\HYNW K\\HYNW K\\HYNW K\\H[K^E[:]EX E]D[ I]D[ I]D[ I]D[ LW ,W ,W ,W )[F[ HW6W K]H] G]H] G]H] G]H] G]H] 1Z F]G] F[GXNW J[GXNW J[GXNW J[GXNW A\\ =WNX"
"G\\ ?\\     1h =h =h =h =h FV ']     AV &W    T )T +X -X EW4W Hl FX9W ?^ 8~R                Jp   MX   ,VCV It 9V8XIX7sLZ  *W )W    MV BX   1X 3W #n Et M"
"x Mu 0X Gs Ao @X 5t In CX -X  )S  1S  X 4V9XFU1X*X'x Ex&z y NX %|*X/X'X -X -X5[$w LX&X0X6^ Mu#X %u#X1X'y =X 6u A^ 8]7]4X1X DX @~U&W \"W ,W       ClMW J"
"WMk Fo EkMW Is JW *jMW MW6W MW ,W ,W<Y IW ,W7W7W=W6W Jp HWMk GkMW MW /q Ae 9kMW B^ 7\\=[(Y;X >\\ Av 6W :V  MW       FkL]$u LXGX 9p Hp EW6W A[ ?X6X LpN\\#"
"hKh)s JW<] Lu LWNm Hp 6` Bl K~W'x MX 1iEi HX CX0X ?X ;u   <V   3^   8`   IX ,o Lz NT.T >X :V  HW   3X=X        )X<X    2~W      :pN\\ @UGU           V&"
"U+V7i.V&U:o JX*X,X*X,X*X,X*X,X*X,X*X-X3y6x&y Ny Ny Ny NX -X -X -X ,z!X6^ Mu Ju Ju Ju Ju KT-T(} Lu Ju Ju Ju AX <X -WJk NlMW KlMW KlMW KlMW KlMW KlMW Kn"
"Is9o Ds Hs Hs Hs LW ,W ,W ,W )p HW6W Jp Ep Ep Ep Ep   Ls EkMW JkMW JkMW JkMW A\\ =WMk >\\     /c 8c 8c 8c 8c CV '\\     ?T %W    U *T *W ,V DW4W Gj EW8W "
">\\ 5~P                In   LX   -VBV Is 9V7g6qJZ  *V )V    LV BX   1X 3V !l Dt Mx Mt /X Gr ?m ?X 4r Hm BX -X  &P  1P  LX 3V 3X*X'w Cv%x My NX #x(X/X'X"
" -X -X4[%w LX&X0X5] Ls\"X $s\"X1Y(w ;X 5s ?\\ 7\\5\\5Y1Y EX @~U&W !V ,W       BjLW JWMj Dn DjMW Hr JW )hLW MW6W MW ,W ,W;Y JW ,W7W7W=W6W In GWMj EjMW MW /p"
" ?d 8iLW B^ 6Z<[)Y:Y >Z @v 6W :V  MW       EiK]$t JYLZ 7n Fo EW6W A[ ?X5W LWNfM\\\"gKg'q IW<] Ks KWMk Fn 5` Aj J~W'x MX 1iEi HX CX0X ?X :s   ;V   2\\   6"
"^   HX +n Lz MR,R =X :V  HW   1ZEZ        %ZDZ    0~W      :WNfM\\ @UGU          !V%U,V6i/V%U9n JX*X,X*X,X*X,X*X,X*X,X*X-X3y5v%y Ny Ny Ny NX -X -X -X ,"
"x NX5] Ls Hs Hs Hs Hs IR+R(WMs Js Hs Hs Hs @X <X -WJk MjLW JjLW JjLW JjLW JjLW JjLW JmHr8n Cr Gr Gr Gr LW ,W ,W ,W (n GW6W In Cn Cn Cn Cn   Ls CiLW Ii"
"LW IiLW IiLW @Z <WMj <Z     +] 2] 2] 2] 2] @V &[     >R $V    NU *U *U *U DW4W Fh DW8X ?\\ 4~                Hl   KX   -VBV Hp 8V5e4nGZ  +W +W    LV BX"
"   1X 3V  j Ct Mx Mr -X Gq =j >Y 3p Gl AX -X       2X 3W 5X(X(u ?s$v Ky NX \"v'X/X'X -X -X3[&w LX&X0X5] Kq!X #p X0X(v :X 4p =\\ 7\\5\\6Y/Y FX @~U&W !V ,W "
"      AhKW JWLh Bm ChLW Gq JW (eJW MW6W MW ,W ,W:Y KW ,W7W7W=W6W Hl FWLh ChLW MW /o >d 7gKW A\\ 5Z<Z(X8X >Z @v 6W :V  MW       DgI\\$s He 5l Dn EW6W @Y "
">W4X MWMeM\\!eIe%o HW<] Jq JWLi Dk 2_ @h J~Y(x MX 1iEi HX CX0X ?X 9q   :V   1Z   4\\   GX *m Lz LP*P <X :V  HW   0m        \"l    .~W      :WMeM\\ @UGU   "
"       !V%U,V6i/V%U8l JX(X.X(X.X(X.X(X.X(X.Y)X/X2y3s$y Ny Ny Ny NX -X -X -X ,v LX5] Kq Fq Fq Fq Fq GP)P'VKp Gp Ep Ep Ep >X <X -WJj KhKW IhKW IhKW IhKW"
" IhKW IhKW IjEq7m Bq Fq Fq Fq LW ,W ,W ,W &j EW6W Hl Al Al Al Al   Ls AgKW HgKW HgKW HgKW @Z <WLh ;Z               MV &[     =P \"U    V +V )S (S CW4W "
"De DX8X ?\\ 2|                Fh   IX   -VBV Ek 6V4c1kEZ  +V +V    KV BW   0X 4W  Mf At Mx Mq ,X Go :h =X 0l Ej ?X -W       1X 2W 6X(X(s ;o\"s Hy NX  r%"
"X/X'X -X -X2['w LX&X0X4\\ Im NX !m NX0Y(t 9X 2m ;Z 5[5[5X-X FX @~U&W !W -W       @fJW JWJe ?j AeJW En IW 'cIW MW6W MW ,W ,W9Y LW ,W7W7W=W6W Fh DWJe AeJ"
"W MW .m ;b 6eJW A\\ 5Z<Z)X6X >X ?v 6W :V  MW       CeG[$r Fc 2h Am EW6W @Y ?X3W MWMdL\\ cGc#m GW;\\ Hm HWKg Ah /] ?f I~Y(x MX 1iEi HX CX0X ?X 7m   8V   0"
"X   2Z   FX (j Kz   AX :V  HW   -g         Lh    ,~W      :WMdL\\ @UGU          \"V$U-V5i0V$U7i HX(X.X(X.X(X.X(X.X(X.X(X/X2y1o\"y Ny Ny Ny NX -X -X -X ,t"
" JX4\\ Im Bm Bm Bm Bm  %VHm Dm Bm Bm Bm =X <X -WJh HfJW HfJW HfJW HfJW HfJW HfJW HhBn4j ?n Cn Cn Cn KW ,W ,W ,W %h DW6W Fh =h =h =h =h   KVMi >eJW GeJW"
" GeJW GeJW ?X ;WJe 9X               MW &Z       =U    W ,W *R &Q BW4W B` AW6W >[ /y                Dd   GX   -VCV Af 5V2a.gBZ  ,W -W    KV CX   0X 4V "
" Kd @t Mx Km *X Ek 6d ;X .h Bh >X .X       1X 1W 7X(X(q 7j Np Ey NX  Mm\"X/X'X -X -X1[(w LX&X0X4\\ Gi LX  Ni LX/X$n 7X 0i 9Z 5[5[6Y-Y GX @~U&W  V -W    "
"   >cIW JWIb <g =bIW Ci FW %_GW MW6W MW ,W ,W8Y MW ,W7W7W=W6W Ef CWIb =bIW MW +h 8a 5cIW @Z 4Y:Y*Y5X ?X ?v 6W :V  MW       AbDY$WMf Ca 0f >k EW6W @Y ?"
"W2W MWK`I[ NaEa i EW;\\ Fi FWIc >e ,\\ =b G~Y(x MX 1iEi HX CX0X ?X 5i   6V   /V   0X   EX &f Iz   AX :V /P;W   *c         Gb    )~W      :WK`I[ @UGU    "
"      #V#U.V4i1V#U6f FX(X.X(X.X(X.X(X.X(X.X(X/X2y/j Ny Ny Ny Ny NX -X -X -X ,p FX4\\ Gi >i >i >i >i  $VEi @i >i >i >i ;X <X -WIf EcIW FcIW FcIW FcIW Fc"
"IW FcIW Fd>i0g ;i >i >i >i HW ,W ,W ,W #d BW6W Ef ;f ;f ;f ;f   JUJe ;cIW FcIW FcIW FcIW ?X ;WIb 7X               MW %Y       =T    X -X )P %P AW4W ?Z"
" >W6X ?Z ,w                B`   EX   .VBV <] 1V0]*b?[  -W -W    KV CW   /X 4V  I` >t Mx Hg 'X Bf 2` :X +d =b ;X .W       0X 1X 9X&X)m 0d Kj ?y NX  Jg "
"NX/X'X -X -X0[)w LX&X0X3[ Dc IX  Kf LX/Y!g 4X .e 7Z 5Z3Z7Y+Y HX @~U&W  V -W       =`GW JWG^ 7b 9^GW Ad CW \"YDW MW6W MW ,W ,W7Y NW ,W7W7W=W6W B` @WG^ 9"
"^GW MW (c 2] 3_GW @Z 3X:X*Y4Y @X ?v 6W :V  MW       ?_AW$WKb @^ +` 9g CW6W ?W ?X2X NWJ^GY K]B^ Ke CW:[ Dd CWG_ 9` 'Y ;^ F~[)x MX 1iEi HX CX0X ?X 2c   "
"3V   .T   .V   DX $b Gz   AX :V /R>X   &[         ?Z    %~W      :WJ^GY ?UGU          #V +V +V 1b EX&X0X&X0X&X0X&X0X&X0Y'X1X1y,d Ky Ny Ny Ny NX -X -X "
"-X ,j @X3[ Dc 8c 8c 8c 8c  !VBc ;e :e :e :e 9X <X -WFa B`GW E`GW E`GW E`GW E`GW E`GW D`:d*b 7d 9d 9d 9d EW ,W ,W ,W !` @W6W B` 5` 5` 5` 5`   HVHa 7_GW"
" D_GW D_GW D_GW ?X ;WG^ 5X               MW         7S                   @r                >Y         BS .V,W#Z   ;V -V     7W     ;W  EX     ;\\   6] "
"+Z   5\\ 5Z   <W         7X     %\\       <]    \"X         ([   4c   E]   /[          (W  W .W       :Y #X 0Z 2X *\\   $W    &W         .Z =WDX 3XDW   I["
"   0Y       8W   -W :V  MW       <Z ;WH[ 9Y &Z 1]  LW ?W   >WGXBU FX=X E` \"W >] @WDY 3Z   2X               C[           >T     :[       KV /TAY       "
"                   EWGXBU =UGU   BT       6V +V +V ,Y               ?\\                    +[ 0[ 0[ 0[ 0[   KT=[ 2[ 0[ 0[ 0[     7Z ;Y .Y .Y .Y .Y .Y -"
"Y2\\\"Z /\\ 1\\ 1\\ 1\\         CZ   3Z /Z /Z /Z /Z   FVCZ 1Y .Y .Y .Y ,W :WDX 2W               LW         7R                                             #S"
"       >W /W     8W     :V                      \"W         5X                  )X             &Z                  CW  NV .W                   :W    %W"
"           @W  :W              -X   -W :V  MW         LW        FW ?W   >W    NW   0W =W                                      3S       GV /XGZ        "
"                  DW  HUGU   AT                            %T                               'R                             JT                         "
"      #T         (X :W  NX               LW                                                       7S       =V /V     7W     :V                      \"W"
"         4X'Q                 &Y             %Z                  DW  NV .W                   :W    %W           @W  :W              -W   ,W :V  MW    "
"     LW        FW ?W   >W    NW   0W =W                                      3S       GV /j                          CW  HUGU   @T                    "
"        %T                               'P                             HT                               \"Q         'W 9W  NW               KW        "
"                                               7S       =W 1W     7V     :W                      \"V         2X)R                 &X             #Z    "
"              EW  NW /W                   :W    %W           @W  :W              -W   ,X ;V  NX         LW        FW ?W   >W    NW   0W =W            "
"                          3S       GV /j                          CW  HUGU   @U                            &U                                         "
"                    U                               \"P         'W 9W  NW               KV                                                       6S    "
"   <V 1V     6V     :V                      !V         1Y-U                 'X             \"Z                  FW  MV /W                   ;X    %W   "
"        @W  :W              .X   +W ;V  NW         KW        FW ?W   >W    NW   0W =W                                      3S       GV /h             "
"             AW  HUGU   ?T                            %T                                                             NT                               "
"          )X 9W  X               KV                                                       6S       <W 3V     6V     9V                      \"V        "
" /Z1X                 (X             !Z                  Ga (V 9a                   ;W    $W           @W  :W              .W   *W ;V  NW         KW  "
"      FW ?W   >W    NW   0W =W                                      3S       GV .f                          @W  HUGU   ?U                            &"
"U                                                             U                                         *W 8W  W               JV                     "
"                                  6S       ;V 3V     6V     :W                      \"V         .[5[                 *Y              Z                 "
" Ha (W :a                   <X    $W           @W  :W              /X   *X <V  X         KW        FW ?W   >W    NW   0W =W                           "
"           3S       GV +a                          >W  HUGU   >T                            %T                                                        "
"     NT                                         +X 8W !X              (VIV                                                       6S       :V 5V     5U"
"     9W                      \"U         +\\;]                 )X              MZ                  Ia (W :a                   =Y    %W           ?W  :W "
"             /W   )[ ?V #[         KW        FW ?W   >W    NW   0W =W                                      3S       GV 'Z                          ;W "
" HUGU   >U                            &U                                                             U                                         ,W 7W !"
"W              'VIV                                                       6S       :V 6W     6V                            4V         *_C`            "
"     )Y              LZ                  Ja   :a                  (P7Y    $W           ?W  :W              0X   (b GV +b         JW        FW ?W   >W "
"   NW   0W =W                                      3S       GV                            7W  HUGU   >U                            &U                 "
"                                            U                                         -X 7W \"X              'VJW                                      "
"                 6S       9V 7V     5U                            3U         'x                 (Z              KZ                  Ka   :a           "
"       (R:Z    $W           ?W  :W              0X   (b GV +b         JW        FW ?W   >W    NW   0W =W                                      3S      "
" GV                            7W     #U                            &U                                                             U                  "
"                       -X 7W \"X              &UJW                                                       6S       9W 9W                                "
"            Bu                 ([              IZ                  La   :a                  (T>[    $X           ?W  :W              1X   &a GV +a    "
"     IW        FW ?W   >W    NW   0W =W                                      3S       GV                            7W     $V                         "
"   'V                                                            !V                                         .X 6W #X              %VLW                "
"                                       5S                                                     2p                 -a                                   "
"                    8XE]    %Y           >W  :W              3Z   $_ GV +_         GW        FW ?W   >W    NW   0W =W                                 "
"     3S       GV                            7W     /QGW                            2QGW                                                            ,QG"
"W                                         0Z 6W %Z              %a                                                       5S                           "
"                          0l                 +a                                                       8p    +_           >W  :W              ;a   !] G"
"V +]         EW        FW ?W   >W    NW   0W =W                                      3S       GV                            7W     /`                 "
"           1`                                                            +`                                         7a 5W -a              #`          "
"                                                                                                   >e                 '`                              "
"                         7o    *^           =W  :W              ;`    KY GV +Y         AW        FW ?W   >W    NW   0W =W                             "
"         3S       GV                            7W     /`                            1`                                                            +` "
"                                        7` 4W -`              \"_                                                                                      "
"                       8\\                 #_                                       \"}              3n    )^           =W  :W              ;`     9V   "
"        BW        FW ?W   >W    NW   0W =W                                             'V                            7W     /_                        "
"    0_                                                            *_                                         6` 4W -`              !]                 "
"                                                                                                              -]                                      "
"  }              3l    ']           <W  :W              ;_     8V           BW        FW ?W   >W    NW   0W =W                                        "
"     'V                            7W     /^                            /^                                                            )^              "
"                           5_ 3W -_               N[                                                                                                  "
"                             ,[                                        M}              2j    &\\           ;W  :W              ;^     7V           BW  "
"      FW ?W   >W    NW   0W =W                                                                          7W     -Y                            *Y       "
"                                                     $Y                                         2^ 2W -^               LX                             "
"                                                                                                  *X                                        J}        "
"      /d    #Z           9W  :W              ;\\     5V           BW        FW ?W   >W    NW   0W =W                                                   "
"                       7W                                                                                                                             "
"            /\\ 0W                 HT                                                                                                                  "
"                                                      I}              *[     NW           6W  :W              ;Z     3V           BW        FW ?W   >W"
"    NW   0W =W                                                                          7W                                                            "
"                                                                             /Z .W                                                                    "
"                                                                                                                     =}                               "
"                                                                                                                                                      "
"                                                                                                                              D" };

    // Define a 40x38 'danger' color logo (used by cimg::dialog()).
    static const unsigned char logo40x38[4576] = {
      177,200,200,200,3,123,123,0,36,200,200,200,1,123,123,0,2,255,255,0,1,189,189,189,1,0,0,0,34,200,200,200,
      1,123,123,0,4,255,255,0,1,189,189,189,1,0,0,0,1,123,123,123,32,200,200,200,1,123,123,0,5,255,255,0,1,0,0,
      0,2,123,123,123,30,200,200,200,1,123,123,0,6,255,255,0,1,189,189,189,1,0,0,0,2,123,123,123,29,200,200,200,
      1,123,123,0,7,255,255,0,1,0,0,0,2,123,123,123,28,200,200,200,1,123,123,0,8,255,255,0,1,189,189,189,1,0,0,0,
      2,123,123,123,27,200,200,200,1,123,123,0,9,255,255,0,1,0,0,0,2,123,123,123,26,200,200,200,1,123,123,0,10,255,
      255,0,1,189,189,189,1,0,0,0,2,123,123,123,25,200,200,200,1,123,123,0,3,255,255,0,1,189,189,189,3,0,0,0,1,189,
      189,189,3,255,255,0,1,0,0,0,2,123,123,123,24,200,200,200,1,123,123,0,4,255,255,0,5,0,0,0,3,255,255,0,1,189,
      189,189,1,0,0,0,2,123,123,123,23,200,200,200,1,123,123,0,4,255,255,0,5,0,0,0,4,255,255,0,1,0,0,0,2,123,123,123,
      22,200,200,200,1,123,123,0,5,255,255,0,5,0,0,0,4,255,255,0,1,189,189,189,1,0,0,0,2,123,123,123,21,200,200,200,
      1,123,123,0,5,255,255,0,5,0,0,0,5,255,255,0,1,0,0,0,2,123,123,123,20,200,200,200,1,123,123,0,6,255,255,0,5,0,0,
      0,5,255,255,0,1,189,189,189,1,0,0,0,2,123,123,123,19,200,200,200,1,123,123,0,6,255,255,0,1,123,123,0,3,0,0,0,1,
      123,123,0,6,255,255,0,1,0,0,0,2,123,123,123,18,200,200,200,1,123,123,0,7,255,255,0,1,189,189,189,3,0,0,0,1,189,
      189,189,6,255,255,0,1,189,189,189,1,0,0,0,2,123,123,123,17,200,200,200,1,123,123,0,8,255,255,0,3,0,0,0,8,255,255,
      0,1,0,0,0,2,123,123,123,16,200,200,200,1,123,123,0,9,255,255,0,1,123,123,0,1,0,0,0,1,123,123,0,8,255,255,0,1,189,
      189,189,1,0,0,0,2,123,123,123,15,200,200,200,1,123,123,0,9,255,255,0,1,189,189,189,1,0,0,0,1,189,189,189,9,255,
      255,0,1,0,0,0,2,123,123,123,14,200,200,200,1,123,123,0,11,255,255,0,1,0,0,0,10,255,255,0,1,189,189,189,1,0,0,0,2,
      123,123,123,13,200,200,200,1,123,123,0,23,255,255,0,1,0,0,0,2,123,123,123,12,200,200,200,1,123,123,0,11,255,255,0,
      1,189,189,189,2,0,0,0,1,189,189,189,9,255,255,0,1,189,189,189,1,0,0,0,2,123,123,123,11,200,200,200,1,123,123,0,11,
      255,255,0,4,0,0,0,10,255,255,0,1,0,0,0,2,123,123,123,10,200,200,200,1,123,123,0,12,255,255,0,4,0,0,0,10,255,255,0,
      1,189,189,189,1,0,0,0,2,123,123,123,9,200,200,200,1,123,123,0,12,255,255,0,1,189,189,189,2,0,0,0,1,189,189,189,11,
      255,255,0,1,0,0,0,2,123,123,123,9,200,200,200,1,123,123,0,27,255,255,0,1,0,0,0,3,123,123,123,8,200,200,200,1,123,
      123,0,26,255,255,0,1,189,189,189,1,0,0,0,3,123,123,123,9,200,200,200,1,123,123,0,24,255,255,0,1,189,189,189,1,0,0,
      0,4,123,123,123,10,200,200,200,1,123,123,0,24,0,0,0,5,123,123,123,12,200,200,200,27,123,123,123,14,200,200,200,25,
      123,123,123,86,200,200,200,91,49,124,118,124,71,32,124,95,49,56,114,52,82,121,0 };

    //! Get/set default output stream for the \CImg library messages.
    /**
       \param file Desired output stream. Set to \c 0 to get the currently used output stream only.
       \return Currently used output stream.
    **/
    inline std::FILE* output(std::FILE *file) {
      cimg::mutex(1);
      static std::FILE *res = stderr;
      if (file) res = file;
      cimg::mutex(1,0);
      return res;
    }

    // Return number of available CPU cores.
    inline unsigned int nb_cpus() {
      unsigned int res = 1;
#if cimg_OS==2
      SYSTEM_INFO sysinfo;
      GetSystemInfo(&sysinfo);
      res = (unsigned int)sysinfo.dwNumberOfProcessors;
#else
      res = (unsigned int)sysconf(_SC_NPROCESSORS_ONLN);
#endif
      return res?res:1U;
    }

    // Lock/unlock mutex for CImg multi-thread programming.
    inline int mutex(const unsigned int n, const int lock_mode) {
      switch (lock_mode) {
      case 0 : cimg::Mutex_attr().unlock(n); return 0;
      case 1 : cimg::Mutex_attr().lock(n); return 0;
      default : return cimg::Mutex_attr().trylock(n);
      }
    }

    //! Display a warning message on the default output stream.
    /**
       \param format C-string containing the format of the message, as with <tt>std::printf()</tt>.
       \note If configuration macro \c cimg_strict_warnings is set, this function throws a
       \c CImgWarningException instead.
       \warning As the first argument is a format string, it is highly recommended to write
       \code
       cimg::warn("%s",warning_message);
       \endcode
       instead of
       \code
       cimg::warn(warning_message);
       \endcode
       if \c warning_message can be arbitrary, to prevent nasty memory access.
    **/
    inline void warn(const char *const format, ...) {
      if (cimg::exception_mode()>=1) {
        char *const message = new char[16384];
        std::va_list ap;
        va_start(ap,format);
        cimg_vsnprintf(message,16384,format,ap);
        va_end(ap);
#ifdef cimg_strict_warnings
        throw CImgWarningException(message);
#else
        std::fprintf(cimg::output(),"\n%s[CImg] *** Warning ***%s%s\n",cimg::t_red,cimg::t_normal,message);
#endif
        delete[] message;
      }
    }

    // Execute an external system command.
    /**
       \param command C-string containing the command line to execute.
       \param module_name Module name.
       \return Status value of the executed command, whose meaning is OS-dependent.
       \note This function is similar to <tt>std::system()</tt>
       but it does not open an extra console windows
       on Windows-based systems.
    **/
    inline int system(const char *const command, const char *const module_name=0) {
      cimg::unused(module_name);
#ifdef cimg_no_system_calls
      return -1;
#else
#if cimg_OS==1
      const unsigned int l = (unsigned int)std::strlen(command);
      if (l) {
        char *const ncommand = new char[l + 16];
        std::strncpy(ncommand,command,l);
        std::strcpy(ncommand + l," 2> /dev/null"); // Make command silent.
        const int out_val = std::system(ncommand);
        delete[] ncommand;
        return out_val;
      } else return -1;
#elif cimg_OS==2
      PROCESS_INFORMATION pi;
      STARTUPINFO si;
      std::memset(&pi,0,sizeof(PROCESS_INFORMATION));
      std::memset(&si,0,sizeof(STARTUPINFO));
      GetStartupInfo(&si);
      si.cb = sizeof(si);
      si.wShowWindow = SW_HIDE;
      si.dwFlags |= SW_HIDE | STARTF_USESHOWWINDOW;
      const BOOL res = CreateProcess((LPCTSTR)module_name,(LPTSTR)command,0,0,FALSE,0,0,0,&si,&pi);
      if (res) {
        WaitForSingleObject(pi.hProcess,INFINITE);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        return 0;
      } else return std::system(command);
#endif
#endif
    }

    //! Return a reference to a temporary variable of type T.
    template<typename T>
    inline T& temporary(const T&) {
      static T temp;
      return temp;
    }

    //! Exchange values of variables \c a and \c b.
    template<typename T>
    inline void swap(T& a, T& b) { T t = a; a = b; b = t; }

    //! Exchange values of variables (\c a1,\c a2) and (\c b1,\c b2).
    template<typename T1, typename T2>
    inline void swap(T1& a1, T1& b1, T2& a2, T2& b2) {
      cimg::swap(a1,b1); cimg::swap(a2,b2);
    }

    //! Exchange values of variables (\c a1,\c a2,\c a3) and (\c b1,\c b2,\c b3).
    template<typename T1, typename T2, typename T3>
    inline void swap(T1& a1, T1& b1, T2& a2, T2& b2, T3& a3, T3& b3) {
      cimg::swap(a1,b1,a2,b2); cimg::swap(a3,b3);
    }

    //! Exchange values of variables (\c a1,\c a2,...,\c a4) and (\c b1,\c b2,...,\c b4).
    template<typename T1, typename T2, typename T3, typename T4>
    inline void swap(T1& a1, T1& b1, T2& a2, T2& b2, T3& a3, T3& b3, T4& a4, T4& b4) {
      cimg::swap(a1,b1,a2,b2,a3,b3); cimg::swap(a4,b4);
    }

    //! Exchange values of variables (\c a1,\c a2,...,\c a5) and (\c b1,\c b2,...,\c b5).
    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    inline void swap(T1& a1, T1& b1, T2& a2, T2& b2, T3& a3, T3& b3, T4& a4, T4& b4, T5& a5, T5& b5) {
      cimg::swap(a1,b1,a2,b2,a3,b3,a4,b4); cimg::swap(a5,b5);
    }

    //! Exchange values of variables (\c a1,\c a2,...,\c a6) and (\c b1,\c b2,...,\c b6).
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    inline void swap(T1& a1, T1& b1, T2& a2, T2& b2, T3& a3, T3& b3, T4& a4, T4& b4, T5& a5, T5& b5, T6& a6, T6& b6) {
      cimg::swap(a1,b1,a2,b2,a3,b3,a4,b4,a5,b5); cimg::swap(a6,b6);
    }

    //! Exchange values of variables (\c a1,\c a2,...,\c a7) and (\c b1,\c b2,...,\c b7).
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    inline void swap(T1& a1, T1& b1, T2& a2, T2& b2, T3& a3, T3& b3, T4& a4, T4& b4, T5& a5, T5& b5, T6& a6, T6& b6,
                     T7& a7, T7& b7) {
      cimg::swap(a1,b1,a2,b2,a3,b3,a4,b4,a5,b5,a6,b6); cimg::swap(a7,b7);
    }

    //! Exchange values of variables (\c a1,\c a2,...,\c a8) and (\c b1,\c b2,...,\c b8).
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    inline void swap(T1& a1, T1& b1, T2& a2, T2& b2, T3& a3, T3& b3, T4& a4, T4& b4, T5& a5, T5& b5, T6& a6, T6& b6,
                     T7& a7, T7& b7, T8& a8, T8& b8) {
      cimg::swap(a1,b1,a2,b2,a3,b3,a4,b4,a5,b5,a6,b6,a7,b7); cimg::swap(a8,b8);
    }

    //! Return the endianness of the current architecture.
    /**
       \return \c false for <i>Little Endian</i> or \c true for <i>Big Endian</i>.
    **/
    inline bool endianness() {
      const int x = 1;
      return ((unsigned char*)&x)[0]?false:true;
    }

    //! Reverse endianness of all elements in a memory buffer.
    /**
       \param[in,out] buffer Memory buffer whose endianness must be reversed.
       \param size Number of buffer elements to reverse.
    **/
    template<typename T>
    inline void invert_endianness(T* const buffer, const cimg_ulong size) {
      if (size) switch (sizeof(T)) {
        case 1 : break;
        case 2 : { for (unsigned short *ptr = (unsigned short*)buffer + size; ptr>(unsigned short*)buffer; ) {
              const unsigned short val = *(--ptr);
              *ptr = (unsigned short)((val>>8)|((val<<8)));
            }
        } break;
        case 4 : { for (unsigned int *ptr = (unsigned int*)buffer + size; ptr>(unsigned int*)buffer; ) {
              const unsigned int val = *(--ptr);
              *ptr = (val>>24)|((val>>8)&0xff00)|((val<<8)&0xff0000)|(val<<24);
            }
        } break;
        default : { for (T* ptr = buffer + size; ptr>buffer; ) {
              unsigned char *pb = (unsigned char*)(--ptr), *pe = pb + sizeof(T);
              for (int i = 0; i<(int)sizeof(T)/2; ++i) swap(*(pb++),*(--pe));
            }
        }
        }
    }

    //! Reverse endianness of a single variable.
    /**
       \param[in,out] a Variable to reverse.
       \return Reference to reversed variable.
    **/
    template<typename T>
    inline T& invert_endianness(T& a) {
      invert_endianness(&a,1);
      return a;
    }

    // Conversion functions to get more precision when trying to store unsigned ints values as floats.
    inline unsigned int float2uint(const float f) {
      int tmp = 0;
      std::memcpy(&tmp,&f,sizeof(float));
      if (tmp>=0) return (unsigned int)f;
      unsigned int u;
      // use memcpy instead of assignment to avoid undesired optimizations by C++-compiler.
      std::memcpy(&u,&f,sizeof(float));
      return ((u)<<1)>>1; // set sign bit to 0.
    }

    inline float uint2float(const unsigned int u) {
      if (u<(1U<<19)) return (float)u;  // Consider safe storage of unsigned int as floats until 19bits (i.e 524287).
      float f;
      const unsigned int v = u|(1U<<(8*sizeof(unsigned int)-1)); // set sign bit to 1.
      // use memcpy instead of simple assignment to avoid undesired optimizations by C++-compiler.
      std::memcpy(&f,&v,sizeof(float));
      return f;
    }

    //! Return the value of a system timer, with a millisecond precision.
    /**
       \note The timer does not necessarily starts from \c 0.
    **/
    inline cimg_ulong time() {
#if cimg_OS==1
      struct timeval st_time;
      gettimeofday(&st_time,0);
      return (cimg_ulong)(st_time.tv_usec/1000 + st_time.tv_sec*1000);
#elif cimg_OS==2
      SYSTEMTIME st_time;
      GetLocalTime(&st_time);
      return (cimg_ulong)(st_time.wMilliseconds + 1000*(st_time.wSecond + 60*(st_time.wMinute + 60*st_time.wHour)));
#else
      return 0;
#endif
    }

    // Implement a tic/toc mechanism to display elapsed time of algorithms.
    inline cimg_ulong tictoc(const bool is_tic);

    //! Start tic/toc timer for time measurement between code instructions.
    /**
       \return Current value of the timer (same value as time()).
    **/
    inline cimg_ulong tic() {
      return cimg::tictoc(true);
    }

    //! End tic/toc timer and displays elapsed time from last call to tic().
    /**
       \return Time elapsed (in ms) since last call to tic().
    **/
    inline cimg_ulong toc() {
      return cimg::tictoc(false);
    }

    //! Sleep for a given numbers of milliseconds.
    /**
       \param milliseconds Number of milliseconds to wait for.
       \note This function frees the CPU ressources during the sleeping time.
       It can be used to temporize your program properly, without wasting CPU time.
    **/
    inline void sleep(const unsigned int milliseconds) {
#if cimg_OS==1
      struct timespec tv;
      tv.tv_sec = milliseconds/1000;
      tv.tv_nsec = (milliseconds%1000)*1000000;
      nanosleep(&tv,0);
#elif cimg_OS==2
      Sleep(milliseconds);
#endif
    }

    inline unsigned int _wait(const unsigned int milliseconds, cimg_ulong& timer) {
      if (!timer) timer = cimg::time();
      const cimg_ulong current_time = cimg::time();
      if (current_time>=timer + milliseconds) { timer = current_time; return 0; }
      const unsigned int time_diff = (unsigned int)(timer + milliseconds - current_time);
      timer = current_time + time_diff;
      cimg::sleep(time_diff);
      return time_diff;
    }

    //! Wait for a given number of milliseconds since the last call to wait().
    /**
       \param milliseconds Number of milliseconds to wait for.
       \return Number of milliseconds elapsed since the last call to wait().
       \note Same as sleep() with a waiting time computed with regard to the last call
       of wait(). It may be used to temporize your program properly, without wasting CPU time.
    **/
    inline cimg_long wait(const unsigned int milliseconds) {
      cimg::mutex(3);
      static cimg_ulong timer = 0;
      if (!timer) timer = cimg::time();
      cimg::mutex(3,0);
      return _wait(milliseconds,timer);
    }

    // Random number generators.
    // CImg may use its own Random Number Generator (RNG) if configuration macro 'cimg_use_rng' is set.
    // Use it for instance when you have to deal with concurrent threads trying to call std::srand()
    // at the same time!
#ifdef cimg_use_rng

#include <stdint.h>

    // Use a custom RNG.
    inline unsigned int _rand(const unsigned int seed=0, const bool set_seed=false) {
      static cimg_ulong next = 0xB16B00B5;
      cimg::mutex(4);
      if (set_seed) next = (cimg_ulong)seed;
      next = next*1103515245 + 12345U;
      cimg::mutex(4,0);
      return (unsigned int)(next&0xFFFFFFU);
    }

    inline void srand() {
      const unsigned int t = (unsigned int)cimg::time();
#if cimg_OS==1
      cimg::_rand(t + (unsigned int)getpid(),true);
#elif cimg_OS==2
      cimg::_rand(t + (unsigned int)_getpid(),true);
#else
      cimg::_rand(t,true);
#endif
    }

    inline void srand(const unsigned int seed) {
      _rand(seed,true);
    }

    inline double rand(const double val_min, const double val_max) {
      const double val = cimg::_rand()/16777215.;
      return val_min + (val_max - val_min)*val;
    }

#else

    // Use the system RNG.
    inline void srand() {
      const unsigned int t = (unsigned int)cimg::time();
#if cimg_OS==1
      std::srand(t + (unsigned int)getpid());
#elif cimg_OS==2
      std::srand(t + (unsigned int)_getpid());
#else
      std::srand(t);
#endif
    }

    inline void srand(const unsigned int seed) {
      std::srand(seed);
    }

    //! Return a random variable uniformely distributed between [val_min,val_max].
    /**
    **/
    inline double rand(const double val_min, const double val_max) {
      const double val = (double)std::rand()/RAND_MAX;
      return val_min + (val_max - val_min)*val;
    }
#endif

    //! Return a random variable uniformely distributed between [0,val_max].
    /**
     **/
    inline double rand(const double val_max=1) {
      return cimg::rand(0,val_max);
    }

    //! Return a random variable following a gaussian distribution and a standard deviation of 1.
    /**
    **/
    inline double grand() {
      double x1, w;
      do {
        const double x2 = cimg::rand(-1,1);
        x1 = cimg::rand(-1,1);
        w = x1*x1 + x2*x2;
      } while (w<=0 || w>=1.0);
      return x1*std::sqrt((-2*std::log(w))/w);
    }

    //! Return a random variable following a Poisson distribution of parameter z.
    /**
    **/
    inline unsigned int prand(const double z) {
      if (z<=1.0e-10) return 0;
      if (z>100) return (unsigned int)((std::sqrt(z) * cimg::grand()) + z);
      unsigned int k = 0;
      const double y = std::exp(-z);
      for (double s = 1.0; s>=y; ++k) s*=cimg::rand();
      return k - 1;
    }

    //! Bitwise-rotate value on the left.
    template<typename T>
    inline T rol(const T& a, const unsigned int n=1) {
      return n?(T)((a<<n)|(a>>((sizeof(T)<<3) - n))):a;
    }

    inline float rol(const float a, const unsigned int n=1) {
      return (float)rol((int)a,n);
    }

    inline double rol(const double a, const unsigned int n=1) {
      return (double)rol((cimg_long)a,n);
    }

    inline double rol(const long double a, const unsigned int n=1) {
      return (double)rol((cimg_long)a,n);
    }

    //! Bitwise-rotate value on the right.
    template<typename T>
    inline T ror(const T& a, const unsigned int n=1) {
      return n?(T)((a>>n)|(a<<((sizeof(T)<<3) - n))):a;
    }

    inline float ror(const float a, const unsigned int n=1) {
      return (float)ror((int)a,n);
    }

    inline double ror(const double a, const unsigned int n=1) {
      return (double)ror((cimg_long)a,n);
    }

    inline double ror(const long double a, const unsigned int n=1) {
      return (double)ror((cimg_long)a,n);
    }

    //! Return absolute value of a value.
    template<typename T>
    inline T abs(const T& a) {
      return a>=0?a:-a;
    }
    inline bool abs(const bool a) {
      return a;
    }
    inline int abs(const unsigned char a) {
      return (int)a;
    }
    inline int abs(const unsigned short a) {
      return (int)a;
    }
    inline int abs(const unsigned int a) {
      return (int)a;
    }
    inline int abs(const int a) {
      return std::abs(a);
    }
    inline cimg_int64 abs(const cimg_uint64 a) {
      return (cimg_int64)a;
    }
    inline double abs(const double a) {
      return std::fabs(a);
    }
    inline float abs(const float a) {
      return (float)std::fabs((double)a);
    }

    //! Return square of a value.
    template<typename T>
    inline T sqr(const T& val) {
      return val*val;
    }

    //! Return <tt>1 + log_10(x)</tt> of a value \c x.
    inline int xln(const int x) {
      return x>0?(int)(1 + std::log10((double)x)):1;
    }

    //! Return the minimum between two values.
    template<typename t1, typename t2>
    inline typename cimg::superset<t1,t2>::type min(const t1& a, const t2& b) {
      typedef typename cimg::superset<t1,t2>::type t1t2;
      return (t1t2)(a<=b?a:b);
    }

    //! Return the minimum between three values.
    template<typename t1, typename t2, typename t3>
    inline typename cimg::superset2<t1,t2,t3>::type min(const t1& a, const t2& b, const t3& c) {
      typedef typename cimg::superset2<t1,t2,t3>::type t1t2t3;
      return (t1t2t3)cimg::min(cimg::min(a,b),c);
    }

    //! Return the minimum between four values.
    template<typename t1, typename t2, typename t3, typename t4>
    inline typename cimg::superset3<t1,t2,t3,t4>::type min(const t1& a, const t2& b, const t3& c, const t4& d) {
      typedef typename cimg::superset3<t1,t2,t3,t4>::type t1t2t3t4;
      return (t1t2t3t4)cimg::min(cimg::min(a,b,c),d);
    }

    //! Return the maximum between two values.
    template<typename t1, typename t2>
    inline typename cimg::superset<t1,t2>::type max(const t1& a, const t2& b) {
      typedef typename cimg::superset<t1,t2>::type t1t2;
      return (t1t2)(a>=b?a:b);
    }

    //! Return the maximum between three values.
    template<typename t1, typename t2, typename t3>
    inline typename cimg::superset2<t1,t2,t3>::type max(const t1& a, const t2& b, const t3& c) {
      typedef typename cimg::superset2<t1,t2,t3>::type t1t2t3;
      return (t1t2t3)cimg::max(cimg::max(a,b),c);
    }

    //! Return the maximum between four values.
    template<typename t1, typename t2, typename t3, typename t4>
    inline typename cimg::superset3<t1,t2,t3,t4>::type max(const t1& a, const t2& b, const t3& c, const t4& d) {
      typedef typename cimg::superset3<t1,t2,t3,t4>::type t1t2t3t4;
      return (t1t2t3t4)cimg::max(cimg::max(a,b,c),d);
    }

    //! Return the sign of a value.
    template<typename T>
    inline T sign(const T& x) {
      return (x<0)?(T)(-1):(x==0?(T)0:(T)1);
    }

    //! Return the nearest power of 2 higher than given value.
    template<typename T>
    inline cimg_ulong nearest_pow2(const T& x) {
      cimg_ulong i = 1;
      while (x>i) i<<=1;
      return i;
    }

    //! Return the sinc of a given value.
    inline double sinc(const double x) {
      return x?std::sin(x)/x:1;
    }

    //! Return the modulo of a value.
    /**
       \param x Input value.
       \param m Modulo value.
       \note This modulo function accepts negative and floating-points modulo numbers, as well as variables of any type.
    **/
    template<typename T>
    inline T mod(const T& x, const T& m) {
      const double dx = (double)x, dm = (double)m;
      return (T)(dx - dm * std::floor(dx / dm));
    }
    inline int mod(const bool x, const bool m) {
      return m?(x?1:0):0;
    }
    inline int mod(const unsigned char x, const unsigned char m) {
      return x%m;
    }
    inline int mod(const char x, const char m) {
#if defined(CHAR_MAX) && CHAR_MAX==255
      return x%m;
#else
      return x>=0?x%m:(x%m?m + x%m:0);
#endif
    }
    inline int mod(const unsigned short x, const unsigned short m) {
      return x%m;
    }
    inline int mod(const short x, const short m) {
      return x>=0?x%m:(x%m?m + x%m:0);
    }
    inline int mod(const unsigned int x, const unsigned int m) {
      return (int)(x%m);
    }
    inline int mod(const int x, const int m) {
      return x>=0?x%m:(x%m?m + x%m:0);
    }
    inline cimg_int64 mod(const cimg_uint64 x, const cimg_uint64 m) {
      return x%m;
    }
    inline cimg_int64 mod(const cimg_int64 x, const cimg_int64 m) {
      return x>=0?x%m:(x%m?m + x%m:0);
    }

    //! Return the min-mod of two values.
    /**
       \note <i>minmod(\p a,\p b)</i> is defined to be:
       - <i>minmod(\p a,\p b) = min(\p a,\p b)</i>, if \p a and \p b have the same sign.
       - <i>minmod(\p a,\p b) = 0</i>, if \p a and \p b have different signs.
    **/
    template<typename T>
    inline T minmod(const T& a, const T& b) {
      return a*b<=0?0:(a>0?(a<b?a:b):(a<b?b:a));
    }

    //! Return base-2 logarithm of a value.
    inline double log2(const double x) {
      const double base = std::log(2.0);
      return std::log(x)/base;
    }

    //! Return rounded value.
    /**
       \param x Value to be rounded.
       \param y Rounding precision.
       \param rounding_type Type of rounding operation (\c 0 = nearest, \c -1 = backward, \c 1 = forward).
       \return Rounded value, having the same type as input value \c x.
    **/
    template<typename T>
    inline T round(const T& x, const double y=1, const int rounding_type=0) {
      if (y<=0) return x;
      const double sx = (double)x/y, floor = std::floor(sx), delta =  sx - floor;
      return (T)(y*(rounding_type<0?floor:rounding_type>0?std::ceil(sx):delta<0.5?floor:std::ceil(sx)));
    }

    inline double _pythagore(double a, double b) {
      const double absa = cimg::abs(a), absb = cimg::abs(b);
      if (absa>absb) { const double tmp = absb/absa; return absa*std::sqrt(1.0 + tmp*tmp); }
      else { const double tmp = absa/absb; return absb==0?0:absb*std::sqrt(1.0 + tmp*tmp); }
    }

    //! Return sqrt(x^2 + y^2).
    inline double hypot(const double x, const double y) {
      double nx = cimg::abs(x), ny = cimg::abs(y), t;
      if (nx<ny) { t = nx; nx = ny; } else t = ny;
      if (nx>0) { t/=nx; return nx*std::sqrt(1+t*t); }
      return 0;
    }

    //! Convert ascii character to lower case.
    inline char uncase(const char x) {
      return (char)((x<'A'||x>'Z')?x:x - 'A' + 'a');
    }

    //! Convert C-string to lower case.
    inline void uncase(char *const str) {
      if (str) for (char *ptr = str; *ptr; ++ptr) *ptr = uncase(*ptr);
    }

    //! Read value in a C-string.
    /**
       \param str C-string containing the float value to read.
       \return Read value.
       \note Same as <tt>std::atof()</tt> extended to manage the retrieval of fractions from C-strings,
       as in <em>"1/2"</em>.
    **/
    inline double atof(const char *const str) {
      double x = 0, y = 1;
      return str && cimg_sscanf(str,"%lf/%lf",&x,&y)>0?x/y:0;
    }

    //! Compare the first \p l characters of two C-strings, ignoring the case.
    /**
       \param str1 C-string.
       \param str2 C-string.
       \param l Number of characters to compare.
       \return \c 0 if the two strings are equal, something else otherwise.
       \note This function has to be defined since it is not provided by all C++-compilers (not ANSI).
    **/
    inline int strncasecmp(const char *const str1, const char *const str2, const int l) {
      if (!l) return 0;
      if (!str1) return str2?-1:0;
      const char *nstr1 = str1, *nstr2 = str2;
      int k, diff = 0; for (k = 0; k<l && !(diff = uncase(*nstr1) - uncase(*nstr2)); ++k) { ++nstr1; ++nstr2; }
      return k!=l?diff:0;
    }

    //! Compare two C-strings, ignoring the case.
    /**
       \param str1 C-string.
       \param str2 C-string.
       \return \c 0 if the two strings are equal, something else otherwise.
       \note This function has to be defined since it is not provided by all C++-compilers (not ANSI).
    **/
    inline int strcasecmp(const char *const str1, const char *const str2) {
      if (!str1) return str2?-1:0;
      const int
        l1 = (int)std::strlen(str1),
        l2 = (int)std::strlen(str2);
      return cimg::strncasecmp(str1,str2,1 + (l1<l2?l1:l2));
    }

    //! Ellipsize a string.
    /**
       \param str C-string.
       \param l Max number of characters.
       \param is_ending Tell if the dots are placed at the end or at the center of the ellipsized string.
    **/
    inline char *strellipsize(char *const str, const unsigned int l=64,
                              const bool is_ending=true) {
      if (!str) return str;
      const unsigned int nl = l<5?5:l, ls = (unsigned int)std::strlen(str);
      if (ls<=nl) return str;
      if (is_ending) std::strcpy(str + nl - 5,"(...)");
      else {
        const unsigned int ll = (nl - 5)/2 + 1 - (nl%2), lr = nl - ll - 5;
        std::strcpy(str + ll,"(...)");
        std::memmove(str + ll + 5,str + ls - lr,lr);
      }
      str[nl] = 0;
      return str;
    }

    //! Ellipsize a string.
    /**
       \param str C-string.
       \param res output C-string.
       \param l Max number of characters.
       \param is_ending Tell if the dots are placed at the end or at the center of the ellipsized string.
    **/
    inline char *strellipsize(const char *const str, char *const res, const unsigned int l=64,
                              const bool is_ending=true) {
      const unsigned int nl = l<5?5:l, ls = (unsigned int)std::strlen(str);
      if (ls<=nl) { std::strcpy(res,str); return res; }
      if (is_ending) {
        std::strncpy(res,str,nl - 5);
        std::strcpy(res + nl -5,"(...)");
      } else {
        const unsigned int ll = (nl - 5)/2 + 1 - (nl%2), lr = nl - ll - 5;
        std::strncpy(res,str,ll);
        std::strcpy(res + ll,"(...)");
        std::strncpy(res + ll + 5,str + ls - lr,lr);
      }
      res[nl] = 0;
      return res;
    }

    //! Remove delimiters on the start and/or end of a C-string.
    /**
       \param[in,out] str C-string to work with (modified at output).
       \param delimiter Delimiter character code to remove.
       \param is_symmetric Tells if the removal is done only if delimiters are symmetric
       (both at the beginning and the end of \c s).
       \param is_iterative Tells if the removal is done if several iterations are possible.
       \return \c true if delimiters have been removed, \c false otherwise.
   **/
    inline bool strpare(char *const str, const char delimiter=' ',
                        const bool is_symmetric=false, const bool is_iterative=false) {
      if (!str) return false;
      const int l = (int)std::strlen(str);
      int p, q;
      if (is_symmetric) for (p = 0, q = l - 1; p<q && str[p]==delimiter && str[q]==delimiter; ) {
          --q; ++p; if (!is_iterative) break;
        } else {
        for (p = 0; p<l && str[p]==delimiter; ) { ++p; if (!is_iterative) break; }
        for (q = l - 1; q>p && str[q]==delimiter; ) { --q; if (!is_iterative) break; }
      }
      const int n = q - p + 1;
      if (n!=l) { std::memmove(str,str + p,(unsigned int)n); str[n] = 0; return true; }
      return false;
    }

    //! Replace reserved characters (for Windows filename) by another character.
    /**
       \param[in,out] str C-string to work with (modified at output).
       \param[in] c Replacement character.
    **/
    inline void strwindows_reserved(char *const str, const char c='_') {
      for (char *s = str; *s; ++s) {
        const char i = *s;
        if (i=='<' || i=='>' || i==':' || i=='\"' || i=='/' || i=='\\' || i=='|' || i=='?' || i=='*') *s = c;
      }
    }

    //! Replace escape sequences in C-strings by their binary ascii values.
    /**
       \param[in,out] str C-string to work with (modified at output).
    **/
    inline void strunescape(char *const str) {
#define cimg_strunescape(ci,co) case ci : *nd = co; ++ns; break;
      unsigned int val = 0;
      for (char *ns = str, *nd = str; *ns || (bool)(*nd=0); ++nd) if (*ns=='\\') switch (*(++ns)) {
            cimg_strunescape('a','\a');
            cimg_strunescape('b','\b');
            cimg_strunescape('e',0x1B);
            cimg_strunescape('f','\f');
            cimg_strunescape('n','\n');
            cimg_strunescape('r','\r');
            cimg_strunescape('t','\t');
            cimg_strunescape('v','\v');
            cimg_strunescape('\\','\\');
            cimg_strunescape('\'','\'');
            cimg_strunescape('\"','\"');
            cimg_strunescape('\?','\?');
          case 0 : *nd = 0; break;
          case '0' : case '1' : case '2' : case '3' : case '4' : case '5' : case '6' : case '7' :
            cimg_sscanf(ns,"%o",&val); while (*ns>='0' && *ns<='7') ++ns;
            *nd = (char)val; break;
          case 'x' :
            cimg_sscanf(++ns,"%x",&val);
            while ((*ns>='0' && *ns<='9') || (*ns>='a' && *ns<='f') || (*ns>='A' && *ns<='F')) ++ns;
            *nd = (char)val; break;
          default : *nd = *(ns++);
          } else *nd = *(ns++);
    }

    // Return a temporary string describing the size of a memory buffer.
    inline const char *strbuffersize(const cimg_ulong size);

    // Return string that identifies the running OS.
    inline const char *stros() {
#if defined(linux) || defined(__linux) || defined(__linux__)
      static const char *const str = "Linux";
#elif defined(sun) || defined(__sun)
      static const char *const str = "Sun OS";
#elif defined(BSD) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__FreeBSD__) || defined (__DragonFly__)
      static const char *const str = "BSD";
#elif defined(sgi) || defined(__sgi)
      static const char *const str = "Irix";
#elif defined(__MACOSX__) || defined(__APPLE__)
      static const char *const str = "Mac OS";
#elif defined(unix) || defined(__unix) || defined(__unix__)
      static const char *const str = "Generic Unix";
#elif defined(_MSC_VER) || defined(WIN32)  || defined(_WIN32) || defined(__WIN32__) || \
  defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
      static const char *const str = "Windows";
#else
      const char
        *const _str1 = std::getenv("OSTYPE"),
        *const _str2 = _str1?_str1:std::getenv("OS"),
        *const str = _str2?_str2:"Unknown OS";
#endif
      return str;
    }

    //! Return the basename of a filename.
    inline const char* basename(const char *const s, const char separator=cimg_file_separator)  {
      const char *p = 0, *np = s;
      while (np>=s && (p=np)) np = std::strchr(np,separator) + 1;
      return p;
    }

    // Return a random filename.
    inline const char* filenamerand() {
      cimg::mutex(6);
      static char randomid[9];
      cimg::srand();
      for (unsigned int k = 0; k<8; ++k) {
        const int v = (int)cimg::rand(65535)%3;
        randomid[k] = (char)(v==0?('0' + ((int)cimg::rand(65535)%10)):
                             (v==1?('a' + ((int)cimg::rand(65535)%26)):('A' + ((int)cimg::rand(65535)%26))));
      }
      cimg::mutex(6,0);
      return randomid;
    }

    // Convert filename as a Windows-style filename (short path name).
    inline void winformat_string(char *const str) {
      if (str && *str) {
#if cimg_OS==2
        char *const nstr = new char[MAX_PATH];
        if (GetShortPathNameA(str,nstr,MAX_PATH)) std::strcpy(str,nstr);
        delete[] nstr;
#endif
      }
    }

    //! Open a file.
    /**
       \param path Path of the filename to open.
       \param mode C-string describing the opening mode.
       \return Opened file.
       \note Same as <tt>std::fopen()</tt> but throw a \c CImgIOException when
       the specified file cannot be opened, instead of returning \c 0.
    **/
    inline std::FILE *fopen(const char *const path, const char *const mode) {
      if (!path)
        throw CImgArgumentException("cimg::fopen(): Specified file path is (null).");
      if (!mode)
        throw CImgArgumentException("cimg::fopen(): File '%s', specified mode is (null).",
                                    path);
      std::FILE *res = 0;
      if (*path=='-' && (!path[1] || path[1]=='.')) {
        res = (*mode=='r')?stdin:stdout;
#if cimg_OS==2
        if (*mode && mode[1]=='b') { // Force stdin/stdout to be in binary mode.
          if (_setmode(_fileno(res),0x8000)==-1) res = 0;
        }
#endif
      } else res = std::fopen(path,mode);
      if (!res) throw CImgIOException("cimg::fopen(): Failed to open file '%s' with mode '%s'.",
                                      path,mode);
      return res;
    }

    //! Close a file.
    /**
       \param file File to close.
       \return \c 0 if file has been closed properly, something else otherwise.
       \note Same as <tt>std::fclose()</tt> but display a warning message if
       the file has not been closed properly.
    **/
    inline int fclose(std::FILE *file) {
      if (!file) warn("cimg::fclose(): Specified file is (null).");
      if (!file || file==stdin || file==stdout) return 0;
      const int errn = std::fclose(file);
      if (errn!=0) warn("cimg::fclose(): Error code %d returned during file closing.",
                        errn);
      return errn;
    }

    //! Version of 'fseek()' that supports >=64bits offsets everywhere (for Windows).
    inline int fseek(FILE *stream, cimg_long offset, int origin) {
#if cimg_OS==2
      return _fseeki64(stream,(__int64)offset,origin);
#else
      return std::fseek(stream,offset,origin);
#endif
    }

    //! Version of 'ftell()' that supports >=64bits offsets everywhere (for Windows).
    inline cimg_long ftell(FILE *stream) {
#if cimg_OS==2
      return (cimg_long)_ftelli64(stream);
#else
      return (cimg_long)std::ftell(stream);
#endif
    }

    //! Check if a path is a directory.
    /**
       \param path Specified path to test.
    **/
    inline bool is_directory(const char *const path) {
      if (!path || !*path) return false;
#if cimg_OS==1
      struct stat st_buf;
      return (!stat(path,&st_buf) && S_ISDIR(st_buf.st_mode));
#elif cimg_OS==2
      const unsigned int res = (unsigned int)GetFileAttributesA(path);
      return res==INVALID_FILE_ATTRIBUTES?false:(res&16);
#endif
    }

    //! Check if a path is a file.
    /**
       \param path Specified path to test.
    **/
    inline bool is_file(const char *const path) {
      if (!path || !*path) return false;
      std::FILE *const file = std::fopen(path,"rb");
      if (!file) return false;
      std::fclose(file);
      return !is_directory(path);
    }

    //! Get last write time of a given file or directory.
    /**
       \param path Specified path to get attributes from.
       \param attr Type of requested time attribute.
                   Can be { 0=year | 1=month | 2=day | 3=day of week | 4=hour | 5=minute | 6=second }
       \return -1 if requested attribute could not be read.
    **/
    inline int fdate(const char *const path, const unsigned int attr) {
      int res = -1;
      if (!path || !*path || attr>6) return -1;
      cimg::mutex(6);
#if cimg_OS==2
      HANDLE file = CreateFileA(path,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
      if (file!=INVALID_HANDLE_VALUE) {
        FILETIME _ft;
        SYSTEMTIME ft;
        if (GetFileTime(file,0,0,&_ft) && FileTimeToSystemTime(&_ft,&ft))
          res = (int)(attr==0?ft.wYear:attr==1?ft.wMonth:attr==2?ft.wDay:attr==3?ft.wDayOfWeek:
                      attr==4?ft.wHour:attr==5?ft.wMinute:ft.wSecond);
        CloseHandle(file);
      }
#else
      struct stat st_buf;
      if (!stat(path,&st_buf)) {
        const time_t _ft = st_buf.st_mtime;
        const struct tm& ft = *std::localtime(&_ft);
        res = (int)(attr==0?ft.tm_year + 1900:attr==1?ft.tm_mon + 1:attr==2?ft.tm_mday:attr==3?ft.tm_wday:
                    attr==4?ft.tm_hour:attr==5?ft.tm_min:ft.tm_sec);
      }
#endif
      cimg::mutex(6,0);
      return res;
    }

    //! Get current local time.
    /**
       \param attr Type of requested time attribute.
                   Can be { 0=year | 1=month | 2=day | 3=day of week | 4=hour | 5=minute | 6=second }
    **/
    inline int date(const unsigned int attr) {
      int res;
      cimg::mutex(6);
#if cimg_OS==2
      SYSTEMTIME st;
      GetLocalTime(&st);
      res = (int)(attr==0?st.wYear:attr==1?st.wMonth:attr==2?st.wDay:attr==3?st.wDayOfWeek:
                  attr==4?st.wHour:attr==5?st.wMinute:st.wSecond);
#else
      time_t _st;
      std::time(&_st);
      struct tm *st = std::localtime(&_st);
      res = (int)(attr==0?st->tm_year + 1900:attr==1?st->tm_mon + 1:attr==2?st->tm_mday:attr==3?st->tm_wday:
                  attr==4?st->tm_hour:attr==5?st->tm_min:st->tm_sec);
#endif
      cimg::mutex(6,0);
      return res;
    }

    // Get/set path to store temporary files.
    inline const char* temporary_path(const char *const user_path=0, const bool reinit_path=false);

    // Get/set path to the <i>Program Files/</i> directory (Windows only).
#if cimg_OS==2
    inline const char* programfiles_path(const char *const user_path=0, const bool reinit_path=false);
#endif

    // Get/set path to the ImageMagick's \c convert binary.
    inline const char* imagemagick_path(const char *const user_path=0, const bool reinit_path=false);

    // Get/set path to the GraphicsMagick's \c gm binary.
    inline const char* graphicsmagick_path(const char *const user_path=0, const bool reinit_path=false);

    // Get/set path to the XMedcon's \c medcon binary.
    inline const char* medcon_path(const char *const user_path=0, const bool reinit_path=false);

    // Get/set path to the FFMPEG's \c ffmpeg binary.
    inline const char *ffmpeg_path(const char *const user_path=0, const bool reinit_path=false);

    // Get/set path to the \c gzip binary.
    inline const char *gzip_path(const char *const user_path=0, const bool reinit_path=false);

    // Get/set path to the \c gunzip binary.
    inline const char *gunzip_path(const char *const user_path=0, const bool reinit_path=false);

    // Get/set path to the \c dcraw binary.
    inline const char *dcraw_path(const char *const user_path=0, const bool reinit_path=false);

    // Get/set path to the \c wget binary.
    inline const char *wget_path(const char *const user_path=0, const bool reinit_path=false);

    // Get/set path to the \c curl binary.
    inline const char *curl_path(const char *const user_path=0, const bool reinit_path=false);

    //! Split filename into two C-strings \c body and \c extension.
    /**
       filename and body must not overlap!
    **/
    inline const char *split_filename(const char *const filename, char *const body=0) {
      if (!filename) { if (body) *body = 0; return 0; }
      const char *p = 0; for (const char *np = filename; np>=filename && (p=np); np = std::strchr(np,'.') + 1) {}
      if (p==filename) {
        if (body) std::strcpy(body,filename);
        return filename + std::strlen(filename);
      }
      const unsigned int l = (unsigned int)(p - filename - 1);
      if (body) { if (l) std::memcpy(body,filename,l); body[l] = 0; }
      return p;
    }

    //! Generate a numbered version of a filename.
    inline char* number_filename(const char *const filename, const int number,
                                 const unsigned int digits, char *const str) {
      if (!filename) { if (str) *str = 0; return 0; }
      char *const format = new char[1024], *const body = new char[1024];
      const char *const ext = cimg::split_filename(filename,body);
      if (*ext) cimg_snprintf(format,1024,"%%s_%%.%ud.%%s",digits);
      else cimg_snprintf(format,1024,"%%s_%%.%ud",digits);
      cimg_sprintf(str,format,body,number,ext);
      delete[] format; delete[] body;
      return str;
    }

    //! Read data from file.
    /**
       \param[out] ptr Pointer to memory buffer that will contain the binary data read from file.
       \param nmemb Number of elements to read.
       \param stream File to read data from.
       \return Number of read elements.
       \note Same as <tt>std::fread()</tt> but may display warning message if all elements could not be read.
    **/
    template<typename T>
    inline size_t fread(T *const ptr, const size_t nmemb, std::FILE *stream) {
      if (!ptr || !stream)
        throw CImgArgumentException("cimg::fread(): Invalid reading request of %u %s%s from file %p to buffer %p.",
                                    nmemb,cimg::type<T>::string(),nmemb>1?"s":"",stream,ptr);
      if (!nmemb) return 0;
      const size_t wlimitT = 63*1024*1024, wlimit = wlimitT/sizeof(T);
      size_t to_read = nmemb, al_read = 0, l_to_read = 0, l_al_read = 0;
      do {
        l_to_read = (to_read*sizeof(T))<wlimitT?to_read:wlimit;
        l_al_read = std::fread((void*)(ptr + al_read),sizeof(T),l_to_read,stream);
        al_read+=l_al_read;
        to_read-=l_al_read;
      } while (l_to_read==l_al_read && to_read>0);
      if (to_read>0)
        warn("cimg::fread(): Only %lu/%lu elements could be read from file.",
             (unsigned long)al_read,(unsigned long)nmemb);
      return al_read;
    }

    //! Write data to file.
    /**
       \param ptr Pointer to memory buffer containing the binary data to write on file.
       \param nmemb Number of elements to write.
       \param[out] stream File to write data on.
       \return Number of written elements.
       \note Similar to <tt>std::fwrite</tt> but may display warning messages if all elements could not be written.
    **/
    template<typename T>
    inline size_t fwrite(const T *ptr, const size_t nmemb, std::FILE *stream) {
      if (!ptr || !stream)
        throw CImgArgumentException("cimg::fwrite(): Invalid writing request of %u %s%s from buffer %p to file %p.",
                                    nmemb,cimg::type<T>::string(),nmemb>1?"s":"",ptr,stream);
      if (!nmemb) return 0;
      const size_t wlimitT = 63*1024*1024, wlimit = wlimitT/sizeof(T);
      size_t to_write = nmemb, al_write = 0, l_to_write = 0, l_al_write = 0;
      do {
        l_to_write = (to_write*sizeof(T))<wlimitT?to_write:wlimit;
        l_al_write = std::fwrite((void*)(ptr + al_write),sizeof(T),l_to_write,stream);
        al_write+=l_al_write;
        to_write-=l_al_write;
      } while (l_to_write==l_al_write && to_write>0);
      if (to_write>0)
        warn("cimg::fwrite(): Only %lu/%lu elements could be written in file.",
             (unsigned long)al_write,(unsigned long)nmemb);
      return al_write;
    }

    //! Create an empty file.
    /**
       \param file Input file (can be \c 0 if \c filename is set).
       \param filename Filename, as a C-string (can be \c 0 if \c file is set).
    **/
    inline void fempty(std::FILE *const file, const char *const filename) {
      if (!file && !filename)
        throw CImgArgumentException("cimg::fempty(): Specified filename is (null).");
      std::FILE *const nfile = file?file:cimg::fopen(filename,"wb");
      if (!file) cimg::fclose(nfile);
    }

    // Try to guess format from an image file.
    inline const char *ftype(std::FILE *const file, const char *const filename);

    // Load file from network as a local temporary file.
    inline char *load_network(const char *const url, char *const filename_local,
                              const unsigned int timeout=0, const bool try_fallback=false,
                              const char *const referer=0);

    //! Return options specified on the command line.
    inline const char* option(const char *const name, const int argc, const char *const *const argv,
                              const char *const defaut, const char *const usage, const bool reset_static) {
      static bool first = true, visu = false;
      if (reset_static) { first = true; return 0; }
      const char *res = 0;
      if (first) {
        first = false;
        visu = cimg::option("-h",argc,argv,(char*)0,(char*)0,false)!=0;
        visu |= cimg::option("-help",argc,argv,(char*)0,(char*)0,false)!=0;
        visu |= cimg::option("--help",argc,argv,(char*)0,(char*)0,false)!=0;
      }
      if (!name && visu) {
        if (usage) {
          std::fprintf(cimg::output(),"\n %s%s%s",cimg::t_red,cimg::basename(argv[0]),cimg::t_normal);
          std::fprintf(cimg::output(),": %s",usage);
          std::fprintf(cimg::output()," (%s, %s)\n\n",__DATE__,__TIME__);
        }
        if (defaut) std::fprintf(cimg::output(),"%s\n",defaut);
      }
      if (name) {
        if (argc>0) {
          int k = 0;
          while (k<argc && std::strcmp(argv[k],name)) ++k;
          res = (k++==argc?defaut:(k==argc?argv[--k]:argv[k]));
        } else res = defaut;
        if (visu && usage) std::fprintf(cimg::output(),"    %s%-16s%s %-24s %s%s%s\n",
                                        cimg::t_bold,name,cimg::t_normal,res?res:"0",
                                        cimg::t_green,usage,cimg::t_normal);
      }
      return res;
    }

    inline const char* option(const char *const name, const int argc, const char *const *const argv,
                              const char *const defaut, const char *const usage=0) {
      return option(name,argc,argv,defaut,usage,false);
    }

    inline bool option(const char *const name, const int argc, const char *const *const argv,
                       const bool defaut, const char *const usage=0) {
      const char *const s = cimg::option(name,argc,argv,(char*)0);
      const bool res = s?(cimg::strcasecmp(s,"false") && cimg::strcasecmp(s,"off") && cimg::strcasecmp(s,"0")):defaut;
      cimg::option(name,0,0,res?"true":"false",usage);
      return res;
    }

    inline int option(const char *const name, const int argc, const char *const *const argv,
                      const int defaut, const char *const usage=0) {
      const char *const s = cimg::option(name,argc,argv,(char*)0);
      const int res = s?std::atoi(s):defaut;
      char *const tmp = new char[256];
      cimg_snprintf(tmp,256,"%d",res);
      cimg::option(name,0,0,tmp,usage);
      delete[] tmp;
      return res;
    }

    inline char option(const char *const name, const int argc, const char *const *const argv,
                       const char defaut, const char *const usage=0) {
      const char *const s = cimg::option(name,argc,argv,(char*)0);
      const char res = s?*s:defaut;
      char tmp[8];
      *tmp = res; tmp[1] = 0;
      cimg::option(name,0,0,tmp,usage);
      return res;
    }

    inline float option(const char *const name, const int argc, const char *const *const argv,
                        const float defaut, const char *const usage=0) {
      const char *const s = cimg::option(name,argc,argv,(char*)0);
      const float res = s?(float)cimg::atof(s):defaut;
      char *const tmp = new char[256];
      cimg_snprintf(tmp,256,"%g",res);
      cimg::option(name,0,0,tmp,usage);
      delete[] tmp;
      return res;
    }

    inline double option(const char *const name, const int argc, const char *const *const argv,
                         const double defaut, const char *const usage=0) {
      const char *const s = cimg::option(name,argc,argv,(char*)0);
      const double res = s?cimg::atof(s):defaut;
      char *const tmp = new char[256];
      cimg_snprintf(tmp,256,"%g",res);
      cimg::option(name,0,0,tmp,usage);
      delete[] tmp;
      return res;
    }

    //! Print information about \CImg environement variables.
    /**
       \note Output is done on the default output stream.
    **/
    inline void info() {
      std::fprintf(cimg::output(),"\n %s%sCImg Library %u.%u.%u%s, compiled %s ( %s ) with the following flags:\n\n",
                   cimg::t_red,cimg::t_bold,cimg_version/100,(cimg_version/10)%10,cimg_version%10,
                   cimg::t_normal,__DATE__,__TIME__);

      std::fprintf(cimg::output(),"  > Operating System:       %s%-13s%s %s('cimg_OS'=%d)%s\n",
                   cimg::t_bold,
                   cimg_OS==1?"Unix":(cimg_OS==2?"Windows":"Unknow"),
                   cimg::t_normal,cimg::t_green,
                   cimg_OS,
                   cimg::t_normal);

      std::fprintf(cimg::output(),"  > CPU endianness:         %s%s Endian%s\n",
                   cimg::t_bold,
                   cimg::endianness()?"Big":"Little",
                   cimg::t_normal);

      std::fprintf(cimg::output(),"  > Verbosity mode:         %s%-13s%s %s('cimg_verbosity'=%d)%s\n",
                   cimg::t_bold,
                   cimg_verbosity==0?"Quiet":
                   cimg_verbosity==1?"Console":
                   cimg_verbosity==2?"Dialog":
                   cimg_verbosity==3?"Console+Warnings":"Dialog+Warnings",
                   cimg::t_normal,cimg::t_green,
                   cimg_verbosity,
                   cimg::t_normal);

      std::fprintf(cimg::output(),"  > Stricts warnings:       %s%-13s%s %s('cimg_strict_warnings' %s)%s\n",
                   cimg::t_bold,
#ifdef cimg_strict_warnings
                   "Yes",cimg::t_normal,cimg::t_green,"defined",
#else
                   "No",cimg::t_normal,cimg::t_green,"undefined",
#endif
                   cimg::t_normal);

      std::fprintf(cimg::output(),"  > Using VT100 messages:   %s%-13s%s %s('cimg_use_vt100' %s)%s\n",
                   cimg::t_bold,
#ifdef cimg_use_vt100
                   "Yes",cimg::t_normal,cimg::t_green,"defined",
#else
                   "No",cimg::t_normal,cimg::t_green,"undefined",
#endif
                   cimg::t_normal);

      std::fprintf(cimg::output(),"  > Display type:           %s%-13s%s %s('cimg_display'=%d)%s\n",
                   cimg::t_bold,
                   cimg_display==0?"No display":cimg_display==1?"X11":cimg_display==2?"Windows GDI":"Unknown",
                   cimg::t_normal,cimg::t_green,
                   cimg_display,
                   cimg::t_normal);

#if cimg_display==1
      std::fprintf(cimg::output(),"  > Using XShm for X11:     %s%-13s%s %s('cimg_use_xshm' %s)%s\n",
                   cimg::t_bold,
#ifdef cimg_use_xshm
                   "Yes",cimg::t_normal,cimg::t_green,"defined",
#else
                   "No",cimg::t_normal,cimg::t_green,"undefined",
#endif
                   cimg::t_normal);

      std::fprintf(cimg::output(),"  > Using XRand for X11:    %s%-13s%s %s('cimg_use_xrandr' %s)%s\n",
                   cimg::t_bold,
#ifdef cimg_use_xrandr
                   "Yes",cimg::t_normal,cimg::t_green,"defined",
#else
                   "No",cimg::t_normal,cimg::t_green,"undefined",
#endif
                   cimg::t_normal);
#endif
      std::fprintf(cimg::output(),"  > Using OpenMP:           %s%-13s%s %s('cimg_use_openmp' %s)%s\n",
                   cimg::t_bold,
#ifdef cimg_use_openmp
                   "Yes",cimg::t_normal,cimg::t_green,"defined",
#else
                   "No",cimg::t_normal,cimg::t_green,"undefined",
#endif
                   cimg::t_normal);
      std::fprintf(cimg::output(),"  > Using PNG library:      %s%-13s%s %s('cimg_use_png' %s)%s\n",
                   cimg::t_bold,
#ifdef cimg_use_png
                   "Yes",cimg::t_normal,cimg::t_green,"defined",
#else
                   "No",cimg::t_normal,cimg::t_green,"undefined",
#endif
                   cimg::t_normal);
      std::fprintf(cimg::output(),"  > Using JPEG library:     %s%-13s%s %s('cimg_use_jpeg' %s)%s\n",
                   cimg::t_bold,
#ifdef cimg_use_jpeg
                   "Yes",cimg::t_normal,cimg::t_green,"defined",
#else
                   "No",cimg::t_normal,cimg::t_green,"undefined",
#endif
                   cimg::t_normal);

      std::fprintf(cimg::output(),"  > Using TIFF library:     %s%-13s%s %s('cimg_use_tiff' %s)%s\n",
                   cimg::t_bold,
#ifdef cimg_use_tiff
                   "Yes",cimg::t_normal,cimg::t_green,"defined",
#else
                   "No",cimg::t_normal,cimg::t_green,"undefined",
#endif
                   cimg::t_normal);

      std::fprintf(cimg::output(),"  > Using Magick++ library: %s%-13s%s %s('cimg_use_magick' %s)%s\n",
                   cimg::t_bold,
#ifdef cimg_use_magick
                   "Yes",cimg::t_normal,cimg::t_green,"defined",
#else
                   "No",cimg::t_normal,cimg::t_green,"undefined",
#endif
                   cimg::t_normal);

      std::fprintf(cimg::output(),"  > Using FFTW3 library:    %s%-13s%s %s('cimg_use_fftw3' %s)%s\n",
                   cimg::t_bold,
#ifdef cimg_use_fftw3
                   "Yes",cimg::t_normal,cimg::t_green,"defined",
#else
                   "No",cimg::t_normal,cimg::t_green,"undefined",
#endif
                   cimg::t_normal);

      std::fprintf(cimg::output(),"  > Using LAPACK library:   %s%-13s%s %s('cimg_use_lapack' %s)%s\n",
                   cimg::t_bold,
#ifdef cimg_use_lapack
                   "Yes",cimg::t_normal,cimg::t_green,"defined",
#else
                   "No",cimg::t_normal,cimg::t_green,"undefined",
#endif
                   cimg::t_normal);

      char *const tmp = new char[1024];
      cimg_snprintf(tmp,1024,"\"%.1020s\"",cimg::imagemagick_path());
      std::fprintf(cimg::output(),"  > Path of ImageMagick:    %s%-13s%s\n",
                   cimg::t_bold,
                   tmp,
                   cimg::t_normal);

      cimg_snprintf(tmp,1024,"\"%.1020s\"",cimg::graphicsmagick_path());
      std::fprintf(cimg::output(),"  > Path of GraphicsMagick: %s%-13s%s\n",
                   cimg::t_bold,
                   tmp,
                   cimg::t_normal);

      cimg_snprintf(tmp,1024,"\"%.1020s\"",cimg::medcon_path());
      std::fprintf(cimg::output(),"  > Path of 'medcon':       %s%-13s%s\n",
                   cimg::t_bold,
                   tmp,
                   cimg::t_normal);

      cimg_snprintf(tmp,1024,"\"%.1020s\"",cimg::temporary_path());
      std::fprintf(cimg::output(),"  > Temporary path:         %s%-13s%s\n",
                   cimg::t_bold,
                   tmp,
                   cimg::t_normal);

      std::fprintf(cimg::output(),"\n");
      delete[] tmp;
    }

    // Declare LAPACK function signatures if LAPACK support is enabled.
#ifdef cimg_use_lapack
    template<typename T>
    inline void getrf(int &N, T *lapA, int *IPIV, int &INFO) {
      dgetrf_(&N,&N,lapA,&N,IPIV,&INFO);
    }

    inline void getrf(int &N, float *lapA, int *IPIV, int &INFO) {
      sgetrf_(&N,&N,lapA,&N,IPIV,&INFO);
    }

    template<typename T>
    inline void getri(int &N, T *lapA, int *IPIV, T* WORK, int &LWORK, int &INFO) {
      dgetri_(&N,lapA,&N,IPIV,WORK,&LWORK,&INFO);
    }

    inline void getri(int &N, float *lapA, int *IPIV, float* WORK, int &LWORK, int &INFO) {
      sgetri_(&N,lapA,&N,IPIV,WORK,&LWORK,&INFO);
    }

    template<typename T>
    inline void gesvd(char &JOB, int &M, int &N, T *lapA, int &MN,
                      T *lapS, T *lapU, T *lapV, T *WORK, int &LWORK, int &INFO) {
      dgesvd_(&JOB,&JOB,&M,&N,lapA,&MN,lapS,lapU,&M,lapV,&N,WORK,&LWORK,&INFO);
    }

    inline void gesvd(char &JOB, int &M, int &N, float *lapA, int &MN,
                      float *lapS, float *lapU, float *lapV, float *WORK, int &LWORK, int &INFO) {
      sgesvd_(&JOB,&JOB,&M,&N,lapA,&MN,lapS,lapU,&M,lapV,&N,WORK,&LWORK,&INFO);
    }

    template<typename T>
    inline void getrs(char &TRANS, int &N, T *lapA, int *IPIV, T *lapB, int &INFO) {
      int one = 1;
      dgetrs_(&TRANS,&N,&one,lapA,&N,IPIV,lapB,&N,&INFO);
    }

    inline void getrs(char &TRANS, int &N, float *lapA, int *IPIV, float *lapB, int &INFO) {
      int one = 1;
      sgetrs_(&TRANS,&N,&one,lapA,&N,IPIV,lapB,&N,&INFO);
    }

    template<typename T>
    inline void syev(char &JOB, char &UPLO, int &N, T *lapA, T *lapW, T *WORK, int &LWORK, int &INFO) {
      dsyev_(&JOB,&UPLO,&N,lapA,&N,lapW,WORK,&LWORK,&INFO);
    }

    inline void syev(char &JOB, char &UPLO, int &N, float *lapA, float *lapW, float *WORK, int &LWORK, int &INFO) {
      ssyev_(&JOB,&UPLO,&N,lapA,&N,lapW,WORK,&LWORK,&INFO);
    }

    template<typename T>
    inline void sgels(char & TRANS, int &M, int &N, int &NRHS, T* lapA, int &LDA,
                      T* lapB, int &LDB, T* WORK, int &LWORK, int &INFO){
      dgels_(&TRANS, &M, &N, &NRHS, lapA, &LDA, lapB, &LDB, WORK, &LWORK, &INFO);
    }

    inline void sgels(char & TRANS, int &M, int &N, int &NRHS, float* lapA, int &LDA,
                      float* lapB, int &LDB, float* WORK, int &LWORK, int &INFO){
      sgels_(&TRANS, &M, &N, &NRHS, lapA, &LDA, lapB, &LDB, WORK, &LWORK, &INFO);
    }

#endif

    // End of the 'cimg' namespace
  }

  /*------------------------------------------------
   #
   #
   #   Definition of mathematical operators and
   #   external functions.
   #
   #
   -------------------------------------------------*/

#define _cimg_create_ext_operators(typ) \
  template<typename T> \
  inline CImg<typename cimg::superset<T,typ>::type> operator+(const typ val, const CImg<T>& img) { \
    return img + val; \
  } \
  template<typename T> \
  inline CImg<typename cimg::superset<T,typ>::type> operator-(const typ val, const CImg<T>& img) { \
    typedef typename cimg::superset<T,typ>::type Tt; \
    return CImg<Tt>(img._width,img._height,img._depth,img._spectrum,val)-=img; \
  } \
  template<typename T> \
  inline CImg<typename cimg::superset<T,typ>::type> operator*(const typ val, const CImg<T>& img) { \
    return img*val; \
  } \
  template<typename T> \
  inline CImg<typename cimg::superset<T,typ>::type> operator/(const typ val, const CImg<T>& img) { \
    return val*img.get_invert(); \
  } \
  template<typename T> \
  inline CImg<typename cimg::superset<T,typ>::type> operator&(const typ val, const CImg<T>& img) { \
    return img & val; \
  } \
  template<typename T> \
  inline CImg<typename cimg::superset<T,typ>::type> operator|(const typ val, const CImg<T>& img) { \
    return img | val; \
  } \
  template<typename T> \
  inline CImg<typename cimg::superset<T,typ>::type> operator^(const typ val, const CImg<T>& img) { \
    return img ^ val; \
  } \
  template<typename T> \
  inline bool operator==(const typ val, const CImg<T>& img) {   \
    return img == val; \
  } \
  template<typename T> \
  inline bool operator!=(const typ val, const CImg<T>& img) { \
    return img != val; \
  }

  _cimg_create_ext_operators(bool)
  _cimg_create_ext_operators(unsigned char)
  _cimg_create_ext_operators(char)
  _cimg_create_ext_operators(signed char)
  _cimg_create_ext_operators(unsigned short)
  _cimg_create_ext_operators(short)
  _cimg_create_ext_operators(unsigned int)
  _cimg_create_ext_operators(int)
  _cimg_create_ext_operators(cimg_uint64)
  _cimg_create_ext_operators(cimg_int64)
  _cimg_create_ext_operators(float)
  _cimg_create_ext_operators(double)
  _cimg_create_ext_operators(long double)

  template<typename T>
  inline CImg<_cimg_Tfloat> operator+(const char *const expression, const CImg<T>& img) {
    return img + expression;
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> operator-(const char *const expression, const CImg<T>& img) {
    return CImg<_cimg_Tfloat>(img,false).fill(expression,true)-=img;
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> operator*(const char *const expression, const CImg<T>& img) {
    return img*expression;
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> operator/(const char *const expression, const CImg<T>& img) {
    return expression*img.get_invert();
  }

  template<typename T>
  inline CImg<T> operator&(const char *const expression, const CImg<T>& img) {
    return img & expression;
  }

  template<typename T>
  inline CImg<T> operator|(const char *const expression, const CImg<T>& img) {
    return img | expression;
  }

  template<typename T>
  inline CImg<T> operator^(const char *const expression, const CImg<T>& img) {
    return img ^ expression;
  }

  template<typename T>
  inline bool operator==(const char *const expression, const CImg<T>& img) {
    return img==expression;
  }

  template<typename T>
  inline bool operator!=(const char *const expression, const CImg<T>& img) {
    return img!=expression;
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> sqr(const CImg<T>& instance) {
    return instance.get_sqr();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> sqrt(const CImg<T>& instance) {
    return instance.get_sqrt();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> exp(const CImg<T>& instance) {
    return instance.get_exp();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> log(const CImg<T>& instance) {
    return instance.get_log();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> log2(const CImg<T>& instance) {
    return instance.get_log2();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> log10(const CImg<T>& instance) {
    return instance.get_log10();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> abs(const CImg<T>& instance) {
    return instance.get_abs();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> sign(const CImg<T>& instance) {
    return instance.get_sign();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> cos(const CImg<T>& instance) {
    return instance.get_cos();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> sin(const CImg<T>& instance) {
    return instance.get_sin();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> sinc(const CImg<T>& instance) {
    return instance.get_sinc();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> tan(const CImg<T>& instance) {
    return instance.get_tan();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> acos(const CImg<T>& instance) {
    return instance.get_acos();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> asin(const CImg<T>& instance) {
    return instance.get_asin();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> atan(const CImg<T>& instance) {
    return instance.get_atan();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> cosh(const CImg<T>& instance) {
    return instance.get_cosh();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> sinh(const CImg<T>& instance) {
    return instance.get_sinh();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> tanh(const CImg<T>& instance) {
    return instance.get_tanh();
  }

  template<typename T>
  inline CImg<T> transpose(const CImg<T>& instance) {
    return instance.get_transpose();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> invert(const CImg<T>& instance) {
    return instance.get_invert();
  }

  template<typename T>
  inline CImg<_cimg_Tfloat> pseudoinvert(const CImg<T>& instance) {
    return instance.get_pseudoinvert();
  }

  /*-----------------------------------
   #
   # Define the CImgDisplay structure
   #
   ----------------------------------*/
  //! Allow the creation of windows, display images on them and manage user events (keyboard, mouse and windows events).
  /**
     CImgDisplay methods rely on a low-level graphic library to perform: it can be either \b X-Window
     (X11, for Unix-based systems) or \b GDI32 (for Windows-based systems).
     If both libraries are missing, CImgDisplay will not be able to display images on screen, and will enter
     a minimal mode where warning messages will be outputed each time the program is trying to call one of the
     CImgDisplay method.

     The configuration variable \c cimg_display tells about the graphic library used.
     It is set automatically by \CImg when one of these graphic libraries has been detected.
     But, you can override its value if necessary. Valid choices are:
     - 0: Disable display capabilities.
     - 1: Use \b X-Window (X11) library.
     - 2: Use \b GDI32 library.

     Remember to link your program against \b X11 or \b GDI32 libraries if you use CImgDisplay.
  **/
  struct CImgDisplay {
    cimg_ulong _timer, _fps_frames, _fps_timer;
    unsigned int _width, _height, _normalization;
    float _fps_fps, _min, _max;
    bool _is_fullscreen;
    char *_title;
    unsigned int _window_width, _window_height, _button, *_keys, *_released_keys;
    int _window_x, _window_y, _mouse_x, _mouse_y, _wheel;
    bool _is_closed, _is_resized, _is_moved, _is_event,
      _is_keyESC, _is_keyF1, _is_keyF2, _is_keyF3, _is_keyF4, _is_keyF5, _is_keyF6, _is_keyF7,
      _is_keyF8, _is_keyF9, _is_keyF10, _is_keyF11, _is_keyF12, _is_keyPAUSE, _is_key1, _is_key2,
      _is_key3, _is_key4, _is_key5, _is_key6, _is_key7, _is_key8, _is_key9, _is_key0,
      _is_keyBACKSPACE, _is_keyINSERT, _is_keyHOME, _is_keyPAGEUP, _is_keyTAB, _is_keyQ, _is_keyW, _is_keyE,
      _is_keyR, _is_keyT, _is_keyY, _is_keyU, _is_keyI, _is_keyO, _is_keyP, _is_keyDELETE,
      _is_keyEND, _is_keyPAGEDOWN, _is_keyCAPSLOCK, _is_keyA, _is_keyS, _is_keyD, _is_keyF, _is_keyG,
      _is_keyH, _is_keyJ, _is_keyK, _is_keyL, _is_keyENTER, _is_keySHIFTLEFT, _is_keyZ, _is_keyX,
      _is_keyC, _is_keyV, _is_keyB, _is_keyN, _is_keyM, _is_keySHIFTRIGHT, _is_keyARROWUP, _is_keyCTRLLEFT,
      _is_keyAPPLEFT, _is_keyALT, _is_keySPACE, _is_keyALTGR, _is_keyAPPRIGHT, _is_keyMENU, _is_keyCTRLRIGHT,
      _is_keyARROWLEFT, _is_keyARROWDOWN, _is_keyARROWRIGHT, _is_keyPAD0, _is_keyPAD1, _is_keyPAD2, _is_keyPAD3,
      _is_keyPAD4, _is_keyPAD5, _is_keyPAD6, _is_keyPAD7, _is_keyPAD8, _is_keyPAD9, _is_keyPADADD, _is_keyPADSUB,
      _is_keyPADMUL, _is_keyPADDIV;

    //@}
    //---------------------------
    //
    //! \name Plugins
    //@{
    //---------------------------

#ifdef cimgdisplay_plugin
#include cimgdisplay_plugin
#endif
#ifdef cimgdisplay_plugin1
#include cimgdisplay_plugin1
#endif
#ifdef cimgdisplay_plugin2
#include cimgdisplay_plugin2
#endif
#ifdef cimgdisplay_plugin3
#include cimgdisplay_plugin3
#endif
#ifdef cimgdisplay_plugin4
#include cimgdisplay_plugin4
#endif
#ifdef cimgdisplay_plugin5
#include cimgdisplay_plugin5
#endif
#ifdef cimgdisplay_plugin6
#include cimgdisplay_plugin6
#endif
#ifdef cimgdisplay_plugin7
#include cimgdisplay_plugin7
#endif
#ifdef cimgdisplay_plugin8
#include cimgdisplay_plugin8
#endif

    //@}
    //--------------------------------------------------------
    //
    //! \name Constructors / Destructor / Instance Management
    //@{
    //--------------------------------------------------------

    //! Destructor.
    /**
       \note If the associated window is visible on the screen, it is closed by the call to the destructor.
    **/
    ~CImgDisplay() {
      assign();
      delete[] _keys;
      delete[] _released_keys;
    }

    //! Construct an empty display.
    /**
       \note Constructing an empty CImgDisplay instance does not make a window appearing on the screen, until
       display of valid data is performed.
       \par Example
       \code
       CImgDisplay disp;  // Does actually nothing.
       ...
       disp.display(img); // Construct new window and display image in it.
       \endcode
    **/
    CImgDisplay():
      _width(0),_height(0),_normalization(0),
      _min(0),_max(0),
      _is_fullscreen(false),
      _title(0),
      _window_width(0),_window_height(0),_button(0),
      _keys(new unsigned int[128]),_released_keys(new unsigned int[128]),
      _window_x(0),_window_y(0),_mouse_x(-1),_mouse_y(-1),_wheel(0),
      _is_closed(true),_is_resized(false),_is_moved(false),_is_event(false) {
      assign();
    }

    //! Construct a display with specified dimensions.
    /** \param width Window width.
        \param height Window height.
        \param title Window title.
        \param normalization Normalization type
        (<tt>0</tt>=none, <tt>1</tt>=always, <tt>2</tt>=once, <tt>3</tt>=pixel type-dependent, see normalization()).
        \param is_fullscreen Tells if fullscreen mode is enabled.
        \param is_closed Tells if associated window is initially visible or not.
        \note A black background is initially displayed on the associated window.
    **/
    CImgDisplay(const unsigned int width, const unsigned int height,
                const char *const title=0, const unsigned int normalization=3,
                const bool is_fullscreen=false, const bool is_closed=false):
      _width(0),_height(0),_normalization(0),
      _min(0),_max(0),
      _is_fullscreen(false),
      _title(0),
      _window_width(0),_window_height(0),_button(0),
      _keys(new unsigned int[128]),_released_keys(new unsigned int[128]),
      _window_x(0),_window_y(0),_mouse_x(-1),_mouse_y(-1),_wheel(0),
      _is_closed(true),_is_resized(false),_is_moved(false),_is_event(false) {
      assign(width,height,title,normalization,is_fullscreen,is_closed);
    }

    //! Construct a display from an image.
    /** \param img Image used as a model to create the window.
        \param title Window title.
        \param normalization Normalization type
        (<tt>0</tt>=none, <tt>1</tt>=always, <tt>2</tt>=once, <tt>3</tt>=pixel type-dependent, see normalization()).
        \param is_fullscreen Tells if fullscreen mode is enabled.
        \param is_closed Tells if associated window is initially visible or not.
        \note The pixels of the input image are initially displayed on the associated window.
    **/
    template<typename T>
    explicit CImgDisplay(const CImg<T>& img,
                         const char *const title=0, const unsigned int normalization=3,
                         const bool is_fullscreen=false, const bool is_closed=false):
      _width(0),_height(0),_normalization(0),
      _min(0),_max(0),
      _is_fullscreen(false),
      _title(0),
      _window_width(0),_window_height(0),_button(0),
      _keys(new unsigned int[128]),_released_keys(new unsigned int[128]),
      _window_x(0),_window_y(0),_mouse_x(-1),_mouse_y(-1),_wheel(0),
      _is_closed(true),_is_resized(false),_is_moved(false),_is_event(false) {
      assign(img,title,normalization,is_fullscreen,is_closed);
    }

    //! Construct a display from an image list.
    /** \param list The images list to display.
        \param title Window title.
        \param normalization Normalization type
        (<tt>0</tt>=none, <tt>1</tt>=always, <tt>2</tt>=once, <tt>3</tt>=pixel type-dependent, see normalization()).
        \param is_fullscreen Tells if fullscreen mode is enabled.
        \param is_closed Tells if associated window is initially visible or not.
        \note All images of the list, appended along the X-axis, are initially displayed on the associated window.
    **/
    template<typename T>
    explicit CImgDisplay(const CImgList<T>& list,
                         const char *const title=0, const unsigned int normalization=3,
                         const bool is_fullscreen=false, const bool is_closed=false):
      _width(0),_height(0),_normalization(0),
      _min(0),_max(0),
      _is_fullscreen(false),
      _title(0),
      _window_width(0),_window_height(0),_button(0),
      _keys(new unsigned int[128]),_released_keys(new unsigned int[128]),
      _window_x(0),_window_y(0),_mouse_x(-1),_mouse_y(-1),_wheel(0),
      _is_closed(true),_is_resized(false),_is_moved(false),_is_event(false) {
      assign(list,title,normalization,is_fullscreen,is_closed);
    }

    //! Construct a display as a copy of an existing one.
    /**
        \param disp Display instance to copy.
        \note The pixel buffer of the input window is initially displayed on the associated window.
    **/
    CImgDisplay(const CImgDisplay& disp):
      _width(0),_height(0),_normalization(0),
      _min(0),_max(0),
      _is_fullscreen(false),
      _title(0),
      _window_width(0),_window_height(0),_button(0),
      _keys(new unsigned int[128]),_released_keys(new unsigned int[128]),
      _window_x(0),_window_y(0),_mouse_x(-1),_mouse_y(-1),_wheel(0),
      _is_closed(true),_is_resized(false),_is_moved(false),_is_event(false) {
      assign(disp);
    }

#if cimg_display==0

    static void _no_display_exception() {
      throw CImgDisplayException("CImgDisplay(): No display available.");
    }

    //! Destructor - Empty constructor \inplace.
    /**
       \note Replace the current instance by an empty display.
    **/
    CImgDisplay& assign() {
      return flush();
    }

    //! Construct a display with specified dimensions \inplace.
    /**
    **/
    CImgDisplay& assign(const unsigned int width, const unsigned int height,
                        const char *const title=0, const unsigned int normalization=3,
                        const bool is_fullscreen=false, const bool is_closed=false) {
      cimg::unused(width,height,title,normalization,is_fullscreen,is_closed);
      _no_display_exception();
      return assign();
    }

    //! Construct a display from an image \inplace.
    /**
    **/
    template<typename T>
    CImgDisplay& assign(const CImg<T>& img,
                        const char *const title=0, const unsigned int normalization=3,
                        const bool is_fullscreen=false, const bool is_closed=false) {
      _no_display_exception();
      return assign(img._width,img._height,title,normalization,is_fullscreen,is_closed);
    }

    //! Construct a display from an image list \inplace.
    /**
    **/
    template<typename T>
    CImgDisplay& assign(const CImgList<T>& list,
                        const char *const title=0, const unsigned int normalization=3,
                        const bool is_fullscreen=false, const bool is_closed=false) {
      _no_display_exception();
      return assign(list._width,list._width,title,normalization,is_fullscreen,is_closed);
    }

    //! Construct a display as a copy of another one \inplace.
    /**
    **/
    CImgDisplay& assign(const CImgDisplay &disp) {
      _no_display_exception();
      return assign(disp._width,disp._height);
    }

#endif

    //! Return a reference to an empty display.
    /**
       \note Can be useful for writing function prototypes where one of the argument (of type CImgDisplay&)
       must have a default value.
       \par Example
       \code
       void foo(CImgDisplay& disp=CImgDisplay::empty());
       \endcode
    **/
    static CImgDisplay& empty() {
      static CImgDisplay _empty;
      return _empty.assign();
    }

    //! Return a reference to an empty display \const.
    static const CImgDisplay& const_empty() {
      static const CImgDisplay _empty;
      return _empty;
    }

#define cimg_fitscreen(dx,dy,dz) CImgDisplay::_fitscreen(dx,dy,dz,128,-85,false), \
                                 CImgDisplay::_fitscreen(dx,dy,dz,128,-85,true)
    static unsigned int _fitscreen(const unsigned int dx, const unsigned int dy, const unsigned int dz,
                                   const int dmin, const int dmax,const bool return_y) {
      const unsigned int _nw = dx + (dz>1?dz:0), _nh = dy + (dz>1?dz:0);
      unsigned int nw = _nw?_nw:1, nh = _nh?_nh:1;
      const unsigned int
        sw = (unsigned int)CImgDisplay::screen_width(),
        sh = (unsigned int)CImgDisplay::screen_height(),
        mw = dmin<0?(unsigned int)(sw*-dmin/100):(unsigned int)dmin,
        mh = dmin<0?(unsigned int)(sh*-dmin/100):(unsigned int)dmin,
        Mw = dmax<0?(unsigned int)(sw*-dmax/100):(unsigned int)dmax,
        Mh = dmax<0?(unsigned int)(sh*-dmax/100):(unsigned int)dmax;
      if (nw<mw) { nh = nh*mw/nw; nh+=(nh==0?1:0); nw = mw; }
      if (nh<mh) { nw = nw*mh/nh; nw+=(nw==0?1:0); nh = mh; }
      if (nw>Mw) { nh = nh*Mw/nw; nh+=(nh==0?1:0); nw = Mw; }
      if (nh>Mh) { nw = nw*Mh/nh; nw+=(nw==0?1:0); nh = Mh; }
      if (nw<mw) nw = mw;
      if (nh<mh) nh = mh;
      return return_y?nh:nw;
    }

    //@}
    //------------------------------------------
    //
    //! \name Overloaded Operators
    //@{
    //------------------------------------------

    //! Display image on associated window.
    /**
       \note <tt>disp = img</tt> is equivalent to <tt>disp.display(img)</tt>.
    **/
    template<typename t>
    CImgDisplay& operator=(const CImg<t>& img) {
      return display(img);
    }

    //! Display list of images on associated window.
    /**
       \note <tt>disp = list</tt> is equivalent to <tt>disp.display(list)</tt>.
    **/
    template<typename t>
    CImgDisplay& operator=(const CImgList<t>& list) {
      return display(list);
    }

    //! Construct a display as a copy of another one \inplace.
    /**
       \note Equivalent to assign(const CImgDisplay&).
     **/
    CImgDisplay& operator=(const CImgDisplay& disp) {
      return assign(disp);
    }

    //! Return \c false if display is empty, \c true otherwise.
    /**
       \note <tt>if (disp) { ... }</tt> is equivalent to <tt>if (!disp.is_empty()) { ... }</tt>.
    **/
    operator bool() const {
      return !is_empty();
    }

    //@}
    //------------------------------------------
    //
    //! \name Instance Checking
    //@{
    //------------------------------------------

    //! Return \c true if display is empty, \c false otherwise.
    /**
    **/
    bool is_empty() const {
      return !(_width && _height);
    }

    //! Return \c true if display is closed (i.e. not visible on the screen), \c false otherwise.
    /**
       \note
       - When a user physically closes the associated window, the display is set to closed.
       - A closed display is not destroyed. Its associated window can be show again on the screen using show().
    **/
    bool is_closed() const {
      return _is_closed;
    }

    //! Return \c true if associated window has been resized on the screen, \c false otherwise.
    /**
    **/
    bool is_resized() const {
      return _is_resized;
    }

    //! Return \c true if associated window has been moved on the screen, \c false otherwise.
    /**
    **/
    bool is_moved() const {
      return _is_moved;
    }

    //! Return \c true if any event has occured on the associated window, \c false otherwise.
    /**
    **/
    bool is_event() const {
      return _is_event;
    }

    //! Return \c true if current display is in fullscreen mode, \c false otherwise.
    /**
    **/
    bool is_fullscreen() const {
      return _is_fullscreen;
    }

    //! Return \c true if any key is being pressed on the associated window, \c false otherwise.
    /**
       \note The methods below do the same only for specific keys.
    **/
    bool is_key() const {
      return _is_keyESC || _is_keyF1 || _is_keyF2 || _is_keyF3 ||
        _is_keyF4 || _is_keyF5 || _is_keyF6 || _is_keyF7 ||
        _is_keyF8 || _is_keyF9 || _is_keyF10 || _is_keyF11 ||
        _is_keyF12 || _is_keyPAUSE || _is_key1 || _is_key2 ||
        _is_key3 || _is_key4 || _is_key5 || _is_key6 ||
        _is_key7 || _is_key8 || _is_key9 || _is_key0 ||
        _is_keyBACKSPACE || _is_keyINSERT || _is_keyHOME ||
        _is_keyPAGEUP || _is_keyTAB || _is_keyQ || _is_keyW ||
        _is_keyE || _is_keyR || _is_keyT || _is_keyY ||
        _is_keyU || _is_keyI || _is_keyO || _is_keyP ||
        _is_keyDELETE || _is_keyEND || _is_keyPAGEDOWN ||
        _is_keyCAPSLOCK || _is_keyA || _is_keyS || _is_keyD ||
        _is_keyF || _is_keyG || _is_keyH || _is_keyJ ||
        _is_keyK || _is_keyL || _is_keyENTER ||
        _is_keySHIFTLEFT || _is_keyZ || _is_keyX || _is_keyC ||
        _is_keyV || _is_keyB || _is_keyN || _is_keyM ||
        _is_keySHIFTRIGHT || _is_keyARROWUP || _is_keyCTRLLEFT ||
        _is_keyAPPLEFT || _is_keyALT || _is_keySPACE || _is_keyALTGR ||
        _is_keyAPPRIGHT || _is_keyMENU || _is_keyCTRLRIGHT ||
        _is_keyARROWLEFT || _is_keyARROWDOWN || _is_keyARROWRIGHT ||
        _is_keyPAD0 || _is_keyPAD1 || _is_keyPAD2 ||
        _is_keyPAD3 || _is_keyPAD4 || _is_keyPAD5 ||
        _is_keyPAD6 || _is_keyPAD7 || _is_keyPAD8 ||
        _is_keyPAD9 || _is_keyPADADD || _is_keyPADSUB ||
        _is_keyPADMUL || _is_keyPADDIV;
    }

    //! Return \c true if key specified by given keycode is being pressed on the associated window, \c false otherwise.
    /**
       \param keycode Keycode to test.
       \note Keycode constants are defined in the cimg namespace and are architecture-dependent. Use them to ensure
       your code stay portable (see cimg::keyESC).
       \par Example
       \code
       CImgDisplay disp(400,400);
       while (!disp.is_closed()) {
         if (disp.key(cimg::keyTAB)) { ... }  // Equivalent to 'if (disp.is_keyTAB())'.
         disp.wait();
       }
       \endcode
    **/
    bool is_key(const unsigned int keycode) const {
#define _cimg_iskey_test(k) if (keycode==cimg::key##k) return _is_key##k;
      _cimg_iskey_test(ESC); _cimg_iskey_test(F1); _cimg_iskey_test(F2); _cimg_iskey_test(F3);
      _cimg_iskey_test(F4); _cimg_iskey_test(F5); _cimg_iskey_test(F6); _cimg_iskey_test(F7);
      _cimg_iskey_test(F8); _cimg_iskey_test(F9); _cimg_iskey_test(F10); _cimg_iskey_test(F11);
      _cimg_iskey_test(F12); _cimg_iskey_test(PAUSE); _cimg_iskey_test(1); _cimg_iskey_test(2);
      _cimg_iskey_test(3); _cimg_iskey_test(4); _cimg_iskey_test(5); _cimg_iskey_test(6);
      _cimg_iskey_test(7); _cimg_iskey_test(8); _cimg_iskey_test(9); _cimg_iskey_test(0);
      _cimg_iskey_test(BACKSPACE); _cimg_iskey_test(INSERT); _cimg_iskey_test(HOME);
      _cimg_iskey_test(PAGEUP); _cimg_iskey_test(TAB); _cimg_iskey_test(Q); _cimg_iskey_test(W);
      _cimg_iskey_test(E); _cimg_iskey_test(R); _cimg_iskey_test(T); _cimg_iskey_test(Y);
      _cimg_iskey_test(U); _cimg_iskey_test(I); _cimg_iskey_test(O); _cimg_iskey_test(P);
      _cimg_iskey_test(DELETE); _cimg_iskey_test(END); _cimg_iskey_test(PAGEDOWN);
      _cimg_iskey_test(CAPSLOCK); _cimg_iskey_test(A); _cimg_iskey_test(S); _cimg_iskey_test(D);
      _cimg_iskey_test(F); _cimg_iskey_test(G); _cimg_iskey_test(H); _cimg_iskey_test(J);
      _cimg_iskey_test(K); _cimg_iskey_test(L); _cimg_iskey_test(ENTER);
      _cimg_iskey_test(SHIFTLEFT); _cimg_iskey_test(Z); _cimg_iskey_test(X); _cimg_iskey_test(C);
      _cimg_iskey_test(V); _cimg_iskey_test(B); _cimg_iskey_test(N); _cimg_iskey_test(M);
      _cimg_iskey_test(SHIFTRIGHT); _cimg_iskey_test(ARROWUP); _cimg_iskey_test(CTRLLEFT);
      _cimg_iskey_test(APPLEFT); _cimg_iskey_test(ALT); _cimg_iskey_test(SPACE); _cimg_iskey_test(ALTGR);
      _cimg_iskey_test(APPRIGHT); _cimg_iskey_test(MENU); _cimg_iskey_test(CTRLRIGHT);
      _cimg_iskey_test(ARROWLEFT); _cimg_iskey_test(ARROWDOWN); _cimg_iskey_test(ARROWRIGHT);
      _cimg_iskey_test(PAD0); _cimg_iskey_test(PAD1); _cimg_iskey_test(PAD2);
      _cimg_iskey_test(PAD3); _cimg_iskey_test(PAD4); _cimg_iskey_test(PAD5);
      _cimg_iskey_test(PAD6); _cimg_iskey_test(PAD7); _cimg_iskey_test(PAD8);
      _cimg_iskey_test(PAD9); _cimg_iskey_test(PADADD); _cimg_iskey_test(PADSUB);
      _cimg_iskey_test(PADMUL); _cimg_iskey_test(PADDIV);
      return false;
    }

    //! Return \c true if key specified by given keycode is being pressed on the associated window, \c false otherwise.
    /**
       \param keycode C-string containing the keycode label of the key to test.
       \note Use it when the key you want to test can be dynamically set by the user.
       \par Example
       \code
       CImgDisplay disp(400,400);
       const char *const keycode = "TAB";
       while (!disp.is_closed()) {
         if (disp.is_key(keycode)) { ... }  // Equivalent to 'if (disp.is_keyTAB())'.
         disp.wait();
       }
       \endcode
    **/
    bool& is_key(const char *const keycode) {
      static bool f = false;
      f = false;
#define _cimg_iskey_test2(k) if (!cimg::strcasecmp(keycode,#k)) return _is_key##k;
      _cimg_iskey_test2(ESC); _cimg_iskey_test2(F1); _cimg_iskey_test2(F2); _cimg_iskey_test2(F3);
      _cimg_iskey_test2(F4); _cimg_iskey_test2(F5); _cimg_iskey_test2(F6); _cimg_iskey_test2(F7);
      _cimg_iskey_test2(F8); _cimg_iskey_test2(F9); _cimg_iskey_test2(F10); _cimg_iskey_test2(F11);
      _cimg_iskey_test2(F12); _cimg_iskey_test2(PAUSE); _cimg_iskey_test2(1); _cimg_iskey_test2(2);
      _cimg_iskey_test2(3); _cimg_iskey_test2(4); _cimg_iskey_test2(5); _cimg_iskey_test2(6);
      _cimg_iskey_test2(7); _cimg_iskey_test2(8); _cimg_iskey_test2(9); _cimg_iskey_test2(0);
      _cimg_iskey_test2(BACKSPACE); _cimg_iskey_test2(INSERT); _cimg_iskey_test2(HOME);
      _cimg_iskey_test2(PAGEUP); _cimg_iskey_test2(TAB); _cimg_iskey_test2(Q); _cimg_iskey_test2(W);
      _cimg_iskey_test2(E); _cimg_iskey_test2(R); _cimg_iskey_test2(T); _cimg_iskey_test2(Y);
      _cimg_iskey_test2(U); _cimg_iskey_test2(I); _cimg_iskey_test2(O); _cimg_iskey_test2(P);
      _cimg_iskey_test2(DELETE); _cimg_iskey_test2(END); _cimg_iskey_test2(PAGEDOWN);
      _cimg_iskey_test2(CAPSLOCK); _cimg_iskey_test2(A); _cimg_iskey_test2(S); _cimg_iskey_test2(D);
      _cimg_iskey_test2(F); _cimg_iskey_test2(G); _cimg_iskey_test2(H); _cimg_iskey_test2(J);
      _cimg_iskey_test2(K); _cimg_iskey_test2(L); _cimg_iskey_test2(ENTER);
      _cimg_iskey_test2(SHIFTLEFT); _cimg_iskey_test2(Z); _cimg_iskey_test2(X); _cimg_iskey_test2(C);
      _cimg_iskey_test2(V); _cimg_iskey_test2(B); _cimg_iskey_test2(N); _cimg_iskey_test2(M);
      _cimg_iskey_test2(SHIFTRIGHT); _cimg_iskey_test2(ARROWUP); _cimg_iskey_test2(CTRLLEFT);
      _cimg_iskey_test2(APPLEFT); _cimg_iskey_test2(ALT); _cimg_iskey_test2(SPACE); _cimg_iskey_test2(ALTGR);
      _cimg_iskey_test2(APPRIGHT); _cimg_iskey_test2(MENU); _cimg_iskey_test2(CTRLRIGHT);
      _cimg_iskey_test2(ARROWLEFT); _cimg_iskey_test2(ARROWDOWN); _cimg_iskey_test2(ARROWRIGHT);
      _cimg_iskey_test2(PAD0); _cimg_iskey_test2(PAD1); _cimg_iskey_test2(PAD2);
      _cimg_iskey_test2(PAD3); _cimg_iskey_test2(PAD4); _cimg_iskey_test2(PAD5);
      _cimg_iskey_test2(PAD6); _cimg_iskey_test2(PAD7); _cimg_iskey_test2(PAD8);
      _cimg_iskey_test2(PAD9); _cimg_iskey_test2(PADADD); _cimg_iskey_test2(PADSUB);
      _cimg_iskey_test2(PADMUL); _cimg_iskey_test2(PADDIV);
      return f;
    }

    //! Return \c true if specified key sequence has been typed on the associated window, \c false otherwise.
    /**
       \param keycodes_sequence Buffer of keycodes to test.
       \param length Number of keys in the \c keycodes_sequence buffer.
       \param remove_sequence Tells if the key sequence must be removed from the key history, if found.
       \note Keycode constants are defined in the cimg namespace and are architecture-dependent. Use them to ensure
       your code stay portable (see cimg::keyESC).
       \par Example
       \code
       CImgDisplay disp(400,400);
       const unsigned int key_seq[] = { cimg::keyCTRLLEFT, cimg::keyD };
       while (!disp.is_closed()) {
         if (disp.is_key_sequence(key_seq,2)) { ... }  // Test for the 'CTRL+D' keyboard event.
         disp.wait();
       }
       \endcode
    **/
    bool is_key_sequence(const unsigned int *const keycodes_sequence, const unsigned int length,
                         const bool remove_sequence=false) {
      if (keycodes_sequence && length) {
        const unsigned int
          *const ps_end = keycodes_sequence + length - 1,
          *const pk_end = (unsigned int*)_keys + 1 + 128 - length,
          k = *ps_end;
        for (unsigned int *pk = (unsigned int*)_keys; pk<pk_end; ) {
          if (*(pk++)==k) {
            bool res = true;
            const unsigned int *ps = ps_end, *pk2 = pk;
            for (unsigned int i = 1; i<length; ++i) res = (*(--ps)==*(pk2++));
            if (res) {
              if (remove_sequence) std::memset((void*)(pk - 1),0,sizeof(unsigned int)*length);
              return true;
            }
          }
        }
      }
      return false;
    }

#define _cimg_iskey_def(k) \
    bool is_key##k() const { \
      return _is_key##k; \
    }

    //! Return \c true if the \c ESC key is being pressed on the associated window, \c false otherwise.
    /**
       \note Similar methods exist for all keys managed by \CImg (see cimg::keyESC).
    **/
    _cimg_iskey_def(ESC); _cimg_iskey_def(F1); _cimg_iskey_def(F2); _cimg_iskey_def(F3);
    _cimg_iskey_def(F4); _cimg_iskey_def(F5); _cimg_iskey_def(F6); _cimg_iskey_def(F7);
    _cimg_iskey_def(F8); _cimg_iskey_def(F9); _cimg_iskey_def(F10); _cimg_iskey_def(F11);
    _cimg_iskey_def(F12); _cimg_iskey_def(PAUSE); _cimg_iskey_def(1); _cimg_iskey_def(2);
    _cimg_iskey_def(3); _cimg_iskey_def(4); _cimg_iskey_def(5); _cimg_iskey_def(6);
    _cimg_iskey_def(7); _cimg_iskey_def(8); _cimg_iskey_def(9); _cimg_iskey_def(0);
    _cimg_iskey_def(BACKSPACE); _cimg_iskey_def(INSERT); _cimg_iskey_def(HOME);
    _cimg_iskey_def(PAGEUP); _cimg_iskey_def(TAB); _cimg_iskey_def(Q); _cimg_iskey_def(W);
    _cimg_iskey_def(E); _cimg_iskey_def(R); _cimg_iskey_def(T); _cimg_iskey_def(Y);
    _cimg_iskey_def(U); _cimg_iskey_def(I); _cimg_iskey_def(O); _cimg_iskey_def(P);
    _cimg_iskey_def(DELETE); _cimg_iskey_def(END); _cimg_iskey_def(PAGEDOWN);
    _cimg_iskey_def(CAPSLOCK); _cimg_iskey_def(A); _cimg_iskey_def(S); _cimg_iskey_def(D);
    _cimg_iskey_def(F); _cimg_iskey_def(G); _cimg_iskey_def(H); _cimg_iskey_def(J);
    _cimg_iskey_def(K); _cimg_iskey_def(L); _cimg_iskey_def(ENTER);
    _cimg_iskey_def(SHIFTLEFT); _cimg_iskey_def(Z); _cimg_iskey_def(X); _cimg_iskey_def(C);
    _cimg_iskey_def(V); _cimg_iskey_def(B); _cimg_iskey_def(N); _cimg_iskey_def(M);
    _cimg_iskey_def(SHIFTRIGHT); _cimg_iskey_def(ARROWUP); _cimg_iskey_def(CTRLLEFT);
    _cimg_iskey_def(APPLEFT); _cimg_iskey_def(ALT); _cimg_iskey_def(SPACE); _cimg_iskey_def(ALTGR);
    _cimg_iskey_def(APPRIGHT); _cimg_iskey_def(MENU); _cimg_iskey_def(CTRLRIGHT);
    _cimg_iskey_def(ARROWLEFT); _cimg_iskey_def(ARROWDOWN); _cimg_iskey_def(ARROWRIGHT);
    _cimg_iskey_def(PAD0); _cimg_iskey_def(PAD1); _cimg_iskey_def(PAD2);
    _cimg_iskey_def(PAD3); _cimg_iskey_def(PAD4); _cimg_iskey_def(PAD5);
    _cimg_iskey_def(PAD6); _cimg_iskey_def(PAD7); _cimg_iskey_def(PAD8);
    _cimg_iskey_def(PAD9); _cimg_iskey_def(PADADD); _cimg_iskey_def(PADSUB);
    _cimg_iskey_def(PADMUL); _cimg_iskey_def(PADDIV);

    //@}
    //------------------------------------------
    //
    //! \name Instance Characteristics
    //@{
    //------------------------------------------

#if cimg_display==0

    //! Return width of the screen (current resolution along the X-axis).
    /**
    **/
    static int screen_width() {
      _no_display_exception();
      return 0;
    }

    //! Return height of the screen (current resolution along the Y-axis).
    /**
    **/
    static int screen_height() {
      _no_display_exception();
      return 0;
    }

#endif

    //! Return display width.
    /**
       \note The width of the display (i.e. the width of the pixel data buffer associated to the CImgDisplay instance)
       may be different from the actual width of the associated window.
    **/
    int width() const {
      return (int)_width;
    }

    //! Return display height.
    /**
       \note The height of the display (i.e. the height of the pixel data buffer associated to the CImgDisplay instance)
       may be different from the actual height of the associated window.
    **/
    int height() const {
      return (int)_height;
    }

    //! Return normalization type of the display.
    /**
       The normalization type tells about how the values of an input image are normalized by the CImgDisplay to be
       correctly displayed. The range of values for pixels displayed on screen is <tt>[0,255]</tt>.
       If the range of values of the data to display is different, a normalization may be required for displaying
       the data in a correct way. The normalization type can be one of:
       - \c 0: Value normalization is disabled. It is then assumed that all input data to be displayed by the
       CImgDisplay instance have values in range <tt>[0,255]</tt>.
       - \c 1: Value normalization is always performed (this is the default behavior).
       Before displaying an input image, its values will be (virtually) stretched
       in range <tt>[0,255]</tt>, so that the contrast of the displayed pixels will be maximum.
       Use this mode for images whose minimum and maximum values are not prescribed to known values
       (e.g. float-valued images).
       Note that when normalized versions of images are computed for display purposes, the actual values of these
       images are not modified.
       - \c 2: Value normalization is performed once (on the first image display), then the same normalization
       coefficients are kept for next displayed frames.
       - \c 3: Value normalization depends on the pixel type of the data to display. For integer pixel types,
       the normalization is done regarding the minimum/maximum values of the type (no normalization occurs then
       for <tt>unsigned char</tt>).
       For float-valued pixel types, the normalization is done regarding the minimum/maximum value of the image
       data instead.
    **/
    unsigned int normalization() const {
      return _normalization;
    }

    //! Return title of the associated window as a C-string.
    /**
       \note Window title may be not visible, depending on the used window manager or if the current display is
       in fullscreen mode.
    **/
    const char *title() const {
      return _title?_title:"";
    }

    //! Return width of the associated window.
    /**
       \note The width of the display (i.e. the width of the pixel data buffer associated to the CImgDisplay instance)
       may be different from the actual width of the associated window.
    **/
    int window_width() const {
      return (int)_window_width;
    }

    //! Return height of the associated window.
    /**
       \note The height of the display (i.e. the height of the pixel data buffer associated to the CImgDisplay instance)
       may be different from the actual height of the associated window.
    **/
    int window_height() const {
      return (int)_window_height;
    }

    //! Return X-coordinate of the associated window.
    /**
       \note The returned coordinate corresponds to the location of the upper-left corner of the associated window.
    **/
    int window_x() const {
      return _window_x;
    }

    //! Return Y-coordinate of the associated window.
    /**
       \note The returned coordinate corresponds to the location of the upper-left corner of the associated window.
    **/
    int window_y() const {
      return _window_y;
    }

    //! Return X-coordinate of the mouse pointer.
    /**
       \note
       - If the mouse pointer is outside window area, \c -1 is returned.
       - Otherwise, the returned value is in the range [0,width()-1].
    **/
    int mouse_x() const {
      return _mouse_x;
    }

    //! Return Y-coordinate of the mouse pointer.
    /**
       \note
       - If the mouse pointer is outside window area, \c -1 is returned.
       - Otherwise, the returned value is in the range [0,height()-1].
    **/
    int mouse_y() const {
      return _mouse_y;
    }

    //! Return current state of the mouse buttons.
    /**
       \note Three mouse buttons can be managed. If one button is pressed, its corresponding bit in the returned
       value is set:
       - bit \c 0 (value \c 0x1): State of the left mouse button.
       - bit \c 1 (value \c 0x2): State of the right mouse button.
       - bit \c 2 (value \c 0x4): State of the middle mouse button.

       Several bits can be activated if more than one button are pressed at the same time.
       \par Example
       \code
       CImgDisplay disp(400,400);
       while (!disp.is_closed()) {
         if (disp.button()&1) { // Left button clicked.
           ...
         }
         if (disp.button()&2) { // Right button clicked.
           ...
         }
         if (disp.button()&4) { // Middle button clicked.
           ...
         }
         disp.wait();
       }
       \endcode
    **/
    unsigned int button() const {
      return _button;
    }

    //! Return current state of the mouse wheel.
    /**
       \note
       - The returned value can be positive or negative depending on whether the mouse wheel has been scrolled
       forward or backward.
       - Scrolling the wheel forward add \c 1 to the wheel value.
       - Scrolling the wheel backward substract \c 1 to the wheel value.
       - The returned value cumulates the number of forward of backward scrolls since the creation of the display,
       or since the last reset of the wheel value (using set_wheel()). It is strongly recommended to quickly reset
       the wheel counter when an action has been performed regarding the current wheel value.
       Otherwise, the returned wheel value may be for instance \c 0 despite the fact that many scrolls have been done
       (as many in forward as in backward directions).
       \par Example
       \code
       CImgDisplay disp(400,400);
       while (!disp.is_closed()) {
         if (disp.wheel()) {
           int counter = disp.wheel();  // Read the state of the mouse wheel.
           ...                          // Do what you want with 'counter'.
           disp.set_wheel();            // Reset the wheel value to 0.
         }
         disp.wait();
       }
       \endcode
    **/
    int wheel() const {
      return _wheel;
    }

    //! Return one entry from the pressed keys history.
    /**
       \param pos Indice to read from the pressed keys history (indice \c 0 corresponds to latest entry).
       \return Keycode of a pressed key or \c 0 for a released key.
       \note
       - Each CImgDisplay stores a history of the pressed keys in a buffer of size \c 128. When a new key is pressed,
       its keycode is stored in the pressed keys history. When a key is released, \c 0 is put instead.
       This means that up to the 64 last pressed keys may be read from the pressed keys history.
       When a new value is stored, the pressed keys history is shifted so that the latest entry is always
       stored at position \c 0.
       - Keycode constants are defined in the cimg namespace and are architecture-dependent. Use them to ensure
       your code stay portable (see cimg::keyESC).
    **/
    unsigned int key(const unsigned int pos=0) const {
      return pos<128?_keys[pos]:0;
    }

    //! Return one entry from the released keys history.
    /**
       \param pos Indice to read from the released keys history (indice \c 0 corresponds to latest entry).
       \return Keycode of a released key or \c 0 for a pressed key.
       \note
       - Each CImgDisplay stores a history of the released keys in a buffer of size \c 128. When a new key is released,
       its keycode is stored in the pressed keys history. When a key is pressed, \c 0 is put instead.
       This means that up to the 64 last released keys may be read from the released keys history.
       When a new value is stored, the released keys history is shifted so that the latest entry is always
       stored at position \c 0.
       - Keycode constants are defined in the cimg namespace and are architecture-dependent. Use them to ensure
       your code stay portable (see cimg::keyESC).
    **/
    unsigned int released_key(const unsigned int pos=0) const {
      return pos<128?_released_keys[pos]:0;
    }

    //! Return keycode corresponding to the specified string.
    /**
       \note Keycode constants are defined in the cimg namespace and are architecture-dependent. Use them to ensure
       your code stay portable (see cimg::keyESC).
       \par Example
       \code
       const unsigned int keyTAB = CImgDisplay::keycode("TAB");  // Return cimg::keyTAB.
       \endcode
    **/
    static unsigned int keycode(const char *const keycode) {
#define _cimg_keycode(k) if (!cimg::strcasecmp(keycode,#k)) return cimg::key##k;
      _cimg_keycode(ESC); _cimg_keycode(F1); _cimg_keycode(F2); _cimg_keycode(F3);
      _cimg_keycode(F4); _cimg_keycode(F5); _cimg_keycode(F6); _cimg_keycode(F7);
      _cimg_keycode(F8); _cimg_keycode(F9); _cimg_keycode(F10); _cimg_keycode(F11);
      _cimg_keycode(F12); _cimg_keycode(PAUSE); _cimg_keycode(1); _cimg_keycode(2);
      _cimg_keycode(3); _cimg_keycode(4); _cimg_keycode(5); _cimg_keycode(6);
      _cimg_keycode(7); _cimg_keycode(8); _cimg_keycode(9); _cimg_keycode(0);
      _cimg_keycode(BACKSPACE); _cimg_keycode(INSERT); _cimg_keycode(HOME);
      _cimg_keycode(PAGEUP); _cimg_keycode(TAB); _cimg_keycode(Q); _cimg_keycode(W);
      _cimg_keycode(E); _cimg_keycode(R); _cimg_keycode(T); _cimg_keycode(Y);
      _cimg_keycode(U); _cimg_keycode(I); _cimg_keycode(O); _cimg_keycode(P);
      _cimg_keycode(DELETE); _cimg_keycode(END); _cimg_keycode(PAGEDOWN);
      _cimg_keycode(CAPSLOCK); _cimg_keycode(A); _cimg_keycode(S); _cimg_keycode(D);
      _cimg_keycode(F); _cimg_keycode(G); _cimg_keycode(H); _cimg_keycode(J);
      _cimg_keycode(K); _cimg_keycode(L); _cimg_keycode(ENTER);
      _cimg_keycode(SHIFTLEFT); _cimg_keycode(Z); _cimg_keycode(X); _cimg_keycode(C);
      _cimg_keycode(V); _cimg_keycode(B); _cimg_keycode(N); _cimg_keycode(M);
      _cimg_keycode(SHIFTRIGHT); _cimg_keycode(ARROWUP); _cimg_keycode(CTRLLEFT);
      _cimg_keycode(APPLEFT); _cimg_keycode(ALT); _cimg_keycode(SPACE); _cimg_keycode(ALTGR);
      _cimg_keycode(APPRIGHT); _cimg_keycode(MENU); _cimg_keycode(CTRLRIGHT);
      _cimg_keycode(ARROWLEFT); _cimg_keycode(ARROWDOWN); _cimg_keycode(ARROWRIGHT);
      _cimg_keycode(PAD0); _cimg_keycode(PAD1); _cimg_keycode(PAD2);
      _cimg_keycode(PAD3); _cimg_keycode(PAD4); _cimg_keycode(PAD5);
      _cimg_keycode(PAD6); _cimg_keycode(PAD7); _cimg_keycode(PAD8);
      _cimg_keycode(PAD9); _cimg_keycode(PADADD); _cimg_keycode(PADSUB);
      _cimg_keycode(PADMUL); _cimg_keycode(PADDIV);
      return 0;
    }

    //! Return the current refresh rate, in frames per second.
    /**
       \note Returns a significant value when the current instance is used to display successive frames.
       It measures the delay between successive calls to frames_per_second().
    **/
    float frames_per_second() {
      if (!_fps_timer) _fps_timer = cimg::time();
      const float delta = (cimg::time() - _fps_timer)/1000.0f;
      ++_fps_frames;
      if (delta>=1) {
        _fps_fps = _fps_frames/delta;
        _fps_frames = 0;
        _fps_timer = cimg::time();
      }
      return _fps_fps;
    }

    //@}
    //---------------------------------------
    //
    //! \name Window Manipulation
    //@{
    //---------------------------------------

#if cimg_display==0

    //! Display image on associated window.
    /**
       \param img Input image to display.
       \note This method returns immediately.
    **/
    template<typename T>
    CImgDisplay& display(const CImg<T>& img) {
      return assign(img);
    }

#endif

    //! Display list of images on associated window.
    /**
       \param list List of images to display.
       \param axis Axis used to append the images along, for the visualization (can be \c x, \c y, \c z or \c c).
       \param align Relative position of aligned images when displaying lists with images of different sizes
       (\c 0 for upper-left, \c 0.5 for centering and \c 1 for lower-right).
       \note This method returns immediately.
    **/
    template<typename T>
    CImgDisplay& display(const CImgList<T>& list, const char axis='x', const float align=0) {
      if (list._width==1) {
        const CImg<T>& img = list[0];
        if (img._depth==1 && (img._spectrum==1 || img._spectrum>=3) && _normalization!=1) return display(img);
      }
      CImgList<typename CImg<T>::ucharT> visu(list._width);
      unsigned int dims = 0;
      cimglist_for(list,l) {
        const CImg<T>& img = list._data[l];
        img.__get_select(*this,_normalization,(img._width - 1)/2,(img._height - 1)/2,
                         (img._depth - 1)/2).move_to(visu[l]);
        dims = cimg::max(dims,visu[l]._spectrum);
      }
      cimglist_for(list,l) if (visu[l]._spectrum<dims) visu[l].resize(-100,-100,-100,dims,1);
      visu.get_append(axis,align).display(*this);
      return *this;
    }

#if cimg_display==0

    //! Show (closed) associated window on the screen.
    /**
       \note
       - Force the associated window of a display to be visible on the screen, even if it has been closed before.
       - Using show() on a visible display does nothing.
    **/
    CImgDisplay& show() {
      return assign();
    }

    //! Close (visible) associated window and make it disappear from the screen.
    /**
       \note
       - A closed display only means the associated window is not visible anymore. This does not mean the display has
       been destroyed.
       Use show() to make the associated window reappear.
       - Using close() on a closed display does nothing.
    **/
    CImgDisplay& close() {
      return assign();
    }

    //! Move associated window to a new location.
    /**
       \param pos_x X-coordinate of the new window location.
       \param pos_y Y-coordinate of the new window location.
       \note Depending on the window manager behavior, this method may not succeed (no exceptions are thrown
       nevertheless).
    **/
    CImgDisplay& move(const int pos_x, const int pos_y) {
      return assign(pos_x,pos_y);
    }

#endif

    //! Resize display to the size of the associated window.
    /**
       \param force_redraw Tells if the previous window content must be updated and refreshed as well.
       \note
       - Calling this method ensures that width() and window_width() become equal, as well as height() and
       window_height().
       - The associated window is also resized to specified dimensions.
    **/
    CImgDisplay& resize(const bool force_redraw=true) {
      resize(window_width(),window_height(),force_redraw);
      return *this;
    }

#if cimg_display==0

    //! Resize display to the specified size.
    /**
       \param width Requested display width.
       \param height Requested display height.
       \param force_redraw Tells if the previous window content must be updated and refreshed as well.
       \note The associated window is also resized to specified dimensions.
    **/
    CImgDisplay& resize(const int width, const int height, const bool force_redraw=true) {
      return assign(width,height,0,3,force_redraw);
    }

#endif

    //! Resize display to the size of an input image.
    /**
       \param img Input image to take size from.
       \param force_redraw Tells if the previous window content must be resized and updated as well.
       \note
       - Calling this method ensures that width() and <tt>img.width()</tt> become equal, as well as height() and
       <tt>img.height()</tt>.
       - The associated window is also resized to specified dimensions.
    **/
    template<typename T>
    CImgDisplay& resize(const CImg<T>& img, const bool force_redraw=true) {
      return resize(img._width,img._height,force_redraw);
    }

    //! Resize display to the size of another CImgDisplay instance.
    /**
       \param disp Input display to take size from.
       \param force_redraw Tells if the previous window content must be resized and updated as well.
       \note
       - Calling this method ensures that width() and <tt>disp.width()</tt> become equal, as well as height() and
       <tt>disp.height()</tt>.
       - The associated window is also resized to specified dimensions.
    **/
    CImgDisplay& resize(const CImgDisplay& disp, const bool force_redraw=true) {
      return resize(disp.width(),disp.height(),force_redraw);
    }

    // [internal] Render pixel buffer with size (wd,hd) from source buffer of size (ws,hs).
    template<typename t, typename T>
    static void _render_resize(const T *ptrs, const unsigned int ws, const unsigned int hs,
                               t *ptrd, const unsigned int wd, const unsigned int hd) {
      unsigned int *const offx = new unsigned int[wd], *const offy = new unsigned int[hd + 1], *poffx, *poffy;
      float s, curr, old;
      s = (float)ws/wd;
      poffx = offx; curr = 0; for (unsigned int x = 0; x<wd; ++x) {
        old = curr; curr+=s; *(poffx++) = (unsigned int)curr - (unsigned int)old;
      }
      s = (float)hs/hd;
      poffy = offy; curr = 0; for (unsigned int y = 0; y<hd; ++y) {
        old = curr; curr+=s; *(poffy++) = ws*((unsigned int)curr - (unsigned int)old);
      }
      *poffy = 0;
      poffy = offy;
      for (unsigned int y = 0; y<hd; ) {
        const T *ptr = ptrs;
        poffx = offx;
        for (unsigned int x = 0; x<wd; ++x) { *(ptrd++) = *ptr; ptr+=*(poffx++); }
        ++y;
        unsigned int dy = *(poffy++);
        for ( ; !dy && y<hd; std::memcpy(ptrd,ptrd - wd,sizeof(t)*wd), ++y, ptrd+=wd, dy = *(poffy++)) {}
        ptrs+=dy;
      }
      delete[] offx; delete[] offy;
    }

    //! Set normalization type.
    /**
       \param normalization New normalization mode.
    **/
    CImgDisplay& set_normalization(const unsigned int normalization) {
      _normalization = normalization;
      _min = _max = 0;
      return *this;
    }

#if cimg_display==0

    //! Set title of the associated window.
    /**
       \param format C-string containing the format of the title, as with <tt>std::printf()</tt>.
       \warning As the first argument is a format string, it is highly recommended to write
       \code
       disp.set_title("%s",window_title);
       \endcode
       instead of
       \code
       disp.set_title(window_title);
       \endcode
       if \c window_title can be arbitrary, to prevent nasty memory access.
    **/
    CImgDisplay& set_title(const char *const format, ...) {
      return assign(0,0,format);
    }

#endif

    //! Enable or disable fullscreen mode.
    /**
       \param is_fullscreen Tells is the fullscreen mode must be activated or not.
       \param force_redraw Tells if the previous window content must be displayed as well.
       \note
       - When the fullscreen mode is enabled, the associated window fills the entire screen but the size of the
       current display is not modified.
       - The screen resolution may be switched to fit the associated window size and ensure it appears the largest
       as possible.
       For X-Window (X11) users, the configuration flag \c cimg_use_xrandr has to be set to allow the screen
       resolution change (requires the X11 extensions to be enabled).
    **/
    CImgDisplay& set_fullscreen(const bool is_fullscreen, const bool force_redraw=true) {
      if (is_empty() || _is_fullscreen==is_fullscreen) return *this;
      return toggle_fullscreen(force_redraw);
    }

#if cimg_display==0

    //! Toggle fullscreen mode.
    /**
       \param force_redraw Tells if the previous window content must be displayed as well.
       \note Enable fullscreen mode if it was not enabled, and disable it otherwise.
    **/
    CImgDisplay& toggle_fullscreen(const bool force_redraw=true) {
      return assign(_width,_height,0,3,force_redraw);
    }

    //! Show mouse pointer.
    /**
       \note Depending on the window manager behavior, this method may not succeed
       (no exceptions are thrown nevertheless).
    **/
    CImgDisplay& show_mouse() {
      return assign();
    }

    //! Hide mouse pointer.
    /**
       \note Depending on the window manager behavior, this method may not succeed
       (no exceptions are thrown nevertheless).
    **/
    CImgDisplay& hide_mouse() {
      return assign();
    }

    //! Move mouse pointer to a specified location.
    /**
       \note Depending on the window manager behavior, this method may not succeed
       (no exceptions are thrown nevertheless).
    **/
    CImgDisplay& set_mouse(const int pos_x, const int pos_y) {
      return assign(pos_x,pos_y);
    }

#endif

    //! Simulate a mouse button release event.
    /**
       \note All mouse buttons are considered released at the same time.
    **/
    CImgDisplay& set_button() {
      _button = 0;
      _is_event = true;
#if cimg_display==1
      pthread_cond_broadcast(&cimg::X11_attr().wait_event);
#elif cimg_display==2
      SetEvent(cimg::Win32_attr().wait_event);
#endif
      return *this;
    }

    //! Simulate a mouse button press or release event.
    /**
       \param button Buttons event code, where each button is associated to a single bit.
       \param is_pressed Tells if the mouse button is considered as pressed or released.
    **/
    CImgDisplay& set_button(const unsigned int button, const bool is_pressed=true) {
      const unsigned int buttoncode = button==1U?1U:button==2U?2U:button==3U?4U:0U;
      if (is_pressed) _button |= buttoncode; else _button &= ~buttoncode;
      _is_event = buttoncode?true:false;
      if (buttoncode) {
#if cimg_display==1
        pthread_cond_broadcast(&cimg::X11_attr().wait_event);
#elif cimg_display==2
        SetEvent(cimg::Win32_attr().wait_event);
#endif
      }
      return *this;
    }

    //! Flush all mouse wheel events.
    /**
       \note Make wheel() to return \c 0, if called afterwards.
    **/
    CImgDisplay& set_wheel() {
      _wheel = 0;
      _is_event = true;
#if cimg_display==1
      pthread_cond_broadcast(&cimg::X11_attr().wait_event);
#elif cimg_display==2
      SetEvent(cimg::Win32_attr().wait_event);
#endif
      return *this;
    }

    //! Simulate a wheel event.
    /**
       \param amplitude Amplitude of the wheel scrolling to simulate.
       \note Make wheel() to return \c amplitude, if called afterwards.
    **/
    CImgDisplay& set_wheel(const int amplitude) {
      _wheel+=amplitude;
      _is_event = amplitude?true:false;
      if (amplitude) {
#if cimg_display==1
        pthread_cond_broadcast(&cimg::X11_attr().wait_event);
#elif cimg_display==2
        SetEvent(cimg::Win32_attr().wait_event);
#endif
      }
      return *this;
    }

    //! Flush all key events.
    /**
       \note Make key() to return \c 0, if called afterwards.
    **/
    CImgDisplay& set_key() {
      std::memset((void*)_keys,0,128*sizeof(unsigned int));
      std::memset((void*)_released_keys,0,128*sizeof(unsigned int));
      _is_keyESC = _is_keyF1 = _is_keyF2 = _is_keyF3 = _is_keyF4 = _is_keyF5 = _is_keyF6 = _is_keyF7 = _is_keyF8 =
        _is_keyF9 = _is_keyF10 = _is_keyF11 = _is_keyF12 = _is_keyPAUSE = _is_key1 = _is_key2 = _is_key3 = _is_key4 =
        _is_key5 = _is_key6 = _is_key7 = _is_key8 = _is_key9 = _is_key0 = _is_keyBACKSPACE = _is_keyINSERT =
        _is_keyHOME = _is_keyPAGEUP = _is_keyTAB = _is_keyQ = _is_keyW = _is_keyE = _is_keyR = _is_keyT = _is_keyY =
        _is_keyU = _is_keyI = _is_keyO = _is_keyP = _is_keyDELETE = _is_keyEND = _is_keyPAGEDOWN = _is_keyCAPSLOCK =
        _is_keyA = _is_keyS = _is_keyD = _is_keyF = _is_keyG = _is_keyH = _is_keyJ = _is_keyK = _is_keyL =
        _is_keyENTER = _is_keySHIFTLEFT = _is_keyZ = _is_keyX = _is_keyC = _is_keyV = _is_keyB = _is_keyN =
        _is_keyM = _is_keySHIFTRIGHT = _is_keyARROWUP = _is_keyCTRLLEFT = _is_keyAPPLEFT = _is_keyALT = _is_keySPACE =
        _is_keyALTGR = _is_keyAPPRIGHT = _is_keyMENU = _is_keyCTRLRIGHT = _is_keyARROWLEFT = _is_keyARROWDOWN =
        _is_keyARROWRIGHT = _is_keyPAD0 = _is_keyPAD1 = _is_keyPAD2 = _is_keyPAD3 = _is_keyPAD4 = _is_keyPAD5 =
        _is_keyPAD6 = _is_keyPAD7 = _is_keyPAD8 = _is_keyPAD9 = _is_keyPADADD = _is_keyPADSUB = _is_keyPADMUL =
        _is_keyPADDIV = false;
      _is_event = true;
#if cimg_display==1
      pthread_cond_broadcast(&cimg::X11_attr().wait_event);
#elif cimg_display==2
      SetEvent(cimg::Win32_attr().wait_event);
#endif
      return *this;
    }

    //! Simulate a keyboard press/release event.
    /**
       \param keycode Keycode of the associated key.
       \param is_pressed Tells if the key is considered as pressed or released.
       \note Keycode constants are defined in the cimg namespace and are architecture-dependent. Use them to ensure
       your code stay portable (see cimg::keyESC).
    **/
    CImgDisplay& set_key(const unsigned int keycode, const bool is_pressed=true) {
#define _cimg_set_key(k) if (keycode==cimg::key##k) _is_key##k = is_pressed;
      _cimg_set_key(ESC); _cimg_set_key(F1); _cimg_set_key(F2); _cimg_set_key(F3);
      _cimg_set_key(F4); _cimg_set_key(F5); _cimg_set_key(F6); _cimg_set_key(F7);
      _cimg_set_key(F8); _cimg_set_key(F9); _cimg_set_key(F10); _cimg_set_key(F11);
      _cimg_set_key(F12); _cimg_set_key(PAUSE); _cimg_set_key(1); _cimg_set_key(2);
      _cimg_set_key(3); _cimg_set_key(4); _cimg_set_key(5); _cimg_set_key(6);
      _cimg_set_key(7); _cimg_set_key(8); _cimg_set_key(9); _cimg_set_key(0);
      _cimg_set_key(BACKSPACE); _cimg_set_key(INSERT); _cimg_set_key(HOME);
      _cimg_set_key(PAGEUP); _cimg_set_key(TAB); _cimg_set_key(Q); _cimg_set_key(W);
      _cimg_set_key(E); _cimg_set_key(R); _cimg_set_key(T); _cimg_set_key(Y);
      _cimg_set_key(U); _cimg_set_key(I); _cimg_set_key(O); _cimg_set_key(P);
      _cimg_set_key(DELETE); _cimg_set_key(END); _cimg_set_key(PAGEDOWN);
      _cimg_set_key(CAPSLOCK); _cimg_set_key(A); _cimg_set_key(S); _cimg_set_key(D);
      _cimg_set_key(F); _cimg_set_key(G); _cimg_set_key(H); _cimg_set_key(J);
      _cimg_set_key(K); _cimg_set_key(L); _cimg_set_key(ENTER);
      _cimg_set_key(SHIFTLEFT); _cimg_set_key(Z); _cimg_set_key(X); _cimg_set_key(C);
      _cimg_set_key(V); _cimg_set_key(B); _cimg_set_key(N); _cimg_set_key(M);
      _cimg_set_key(SHIFTRIGHT); _cimg_set_key(ARROWUP); _cimg_set_key(CTRLLEFT);
      _cimg_set_key(APPLEFT); _cimg_set_key(ALT); _cimg_set_key(SPACE); _cimg_set_key(ALTGR);
      _cimg_set_key(APPRIGHT); _cimg_set_key(MENU); _cimg_set_key(CTRLRIGHT);
      _cimg_set_key(ARROWLEFT); _cimg_set_key(ARROWDOWN); _cimg_set_key(ARROWRIGHT);
      _cimg_set_key(PAD0); _cimg_set_key(PAD1); _cimg_set_key(PAD2);
      _cimg_set_key(PAD3); _cimg_set_key(PAD4); _cimg_set_key(PAD5);
      _cimg_set_key(PAD6); _cimg_set_key(PAD7); _cimg_set_key(PAD8);
      _cimg_set_key(PAD9); _cimg_set_key(PADADD); _cimg_set_key(PADSUB);
      _cimg_set_key(PADMUL); _cimg_set_key(PADDIV);
      if (is_pressed) {
        if (*_keys)
          std::memmove((void*)(_keys + 1),(void*)_keys,127*sizeof(unsigned int));
        *_keys = keycode;
        if (*_released_keys) {
          std::memmove((void*)(_released_keys + 1),(void*)_released_keys,127*sizeof(unsigned int));
          *_released_keys = 0;
        }
      } else {
        if (*_keys) {
          std::memmove((void*)(_keys + 1),(void*)_keys,127*sizeof(unsigned int));
          *_keys = 0;
        }
        if (*_released_keys)
          std::memmove((void*)(_released_keys + 1),(void*)_released_keys,127*sizeof(unsigned int));
        *_released_keys = keycode;
      }
      _is_event = keycode?true:false;
      if (keycode) {
#if cimg_display==1
        pthread_cond_broadcast(&cimg::X11_attr().wait_event);
#elif cimg_display==2
        SetEvent(cimg::Win32_attr().wait_event);
#endif
      }
      return *this;
    }

    //! Flush all display events.
    /**
       \note Remove all passed events from the current display.
    **/
    CImgDisplay& flush() {
      set_key().set_button().set_wheel();
      _is_resized = _is_moved = _is_event = false;
      _fps_timer = _fps_frames = _timer = 0;
      _fps_fps = 0;
      return *this;
    }

    //! Wait for any user event occuring on the current display.
    CImgDisplay& wait() {
      wait(*this);
      return *this;
    }

    //! Wait for a given number of milliseconds since the last call to wait().
    /**
       \param milliseconds Number of milliseconds to wait for.
       \note Similar to cimg::wait().
    **/
    CImgDisplay& wait(const unsigned int milliseconds) {
      cimg::_wait(milliseconds,_timer);
      return *this;
    }

    //! Wait for any event occuring on the display \c disp1.
    static void wait(CImgDisplay& disp1) {
      disp1._is_event = false;
      while (!disp1._is_closed && !disp1._is_event) wait_all();
    }

    //! Wait for any event occuring either on the display \c disp1 or \c disp2.
    static void wait(CImgDisplay& disp1, CImgDisplay& disp2) {
      disp1._is_event = disp2._is_event = false;
      while ((!disp1._is_closed || !disp2._is_closed) &&
             !disp1._is_event && !disp2._is_event) wait_all();
    }

    //! Wait for any event occuring either on the display \c disp1, \c disp2 or \c disp3.
    static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3) {
      disp1._is_event = disp2._is_event = disp3._is_event = false;
      while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed) &&
             !disp1._is_event && !disp2._is_event && !disp3._is_event) wait_all();
    }

    //! Wait for any event occuring either on the display \c disp1, \c disp2, \c disp3 or \c disp4.
    static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3, CImgDisplay& disp4) {
      disp1._is_event = disp2._is_event = disp3._is_event = disp4._is_event = false;
      while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed || !disp4._is_closed) &&
             !disp1._is_event && !disp2._is_event && !disp3._is_event && !disp4._is_event) wait_all();
    }

    //! Wait for any event occuring either on the display \c disp1, \c disp2, \c disp3, \c disp4 or \c disp5.
    static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3, CImgDisplay& disp4,
                     CImgDisplay& disp5) {
      disp1._is_event = disp2._is_event = disp3._is_event = disp4._is_event = disp5._is_event = false;
      while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed || !disp4._is_closed || !disp5._is_closed) &&
             !disp1._is_event && !disp2._is_event && !disp3._is_event && !disp4._is_event && !disp5._is_event)
        wait_all();
    }

    //! Wait for any event occuring either on the display \c disp1, \c disp2, \c disp3, \c disp4, ... \c disp6.
    static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3, CImgDisplay& disp4, CImgDisplay& disp5,
                     CImgDisplay& disp6) {
      disp1._is_event = disp2._is_event = disp3._is_event = disp4._is_event = disp5._is_event =
        disp6._is_event = false;
      while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed || !disp4._is_closed || !disp5._is_closed ||
              !disp6._is_closed) &&
             !disp1._is_event && !disp2._is_event && !disp3._is_event && !disp4._is_event && !disp5._is_event &&
             !disp6._is_event) wait_all();
    }

    //! Wait for any event occuring either on the display \c disp1, \c disp2, \c disp3, \c disp4, ... \c disp7.
    static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3, CImgDisplay& disp4, CImgDisplay& disp5,
                     CImgDisplay& disp6, CImgDisplay& disp7) {
      disp1._is_event = disp2._is_event = disp3._is_event = disp4._is_event = disp5._is_event =
        disp6._is_event = disp7._is_event = false;
      while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed || !disp4._is_closed || !disp5._is_closed ||
              !disp6._is_closed || !disp7._is_closed) &&
             !disp1._is_event && !disp2._is_event && !disp3._is_event && !disp4._is_event && !disp5._is_event &&
             !disp6._is_event && !disp7._is_event) wait_all();
    }

    //! Wait for any event occuring either on the display \c disp1, \c disp2, \c disp3, \c disp4, ... \c disp8.
    static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3, CImgDisplay& disp4, CImgDisplay& disp5,
                     CImgDisplay& disp6, CImgDisplay& disp7, CImgDisplay& disp8) {
      disp1._is_event = disp2._is_event = disp3._is_event = disp4._is_event = disp5._is_event =
        disp6._is_event = disp7._is_event = disp8._is_event = false;
      while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed || !disp4._is_closed || !disp5._is_closed ||
              !disp6._is_closed || !disp7._is_closed || !disp8._is_closed) &&
             !disp1._is_event && !disp2._is_event && !disp3._is_event && !disp4._is_event && !disp5._is_event &&
             !disp6._is_event && !disp7._is_event && !disp8._is_event) wait_all();
    }

    //! Wait for any event occuring either on the display \c disp1, \c disp2, \c disp3, \c disp4, ... \c disp9.
    static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3, CImgDisplay& disp4, CImgDisplay& disp5,
                     CImgDisplay& disp6, CImgDisplay& disp7, CImgDisplay& disp8, CImgDisplay& disp9) {
      disp1._is_event = disp2._is_event = disp3._is_event = disp4._is_event = disp5._is_event =
        disp6._is_event = disp7._is_event = disp8._is_event = disp9._is_event = false;
      while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed || !disp4._is_closed || !disp5._is_closed ||
              !disp6._is_closed || !disp7._is_closed || !disp8._is_closed || !disp9._is_closed) &&
             !disp1._is_event && !disp2._is_event && !disp3._is_event && !disp4._is_event && !disp5._is_event &&
             !disp6._is_event && !disp7._is_event && !disp8._is_event && !disp9._is_event) wait_all();
    }

    //! Wait for any event occuring either on the display \c disp1, \c disp2, \c disp3, \c disp4, ... \c disp10.
    static void wait(CImgDisplay& disp1, CImgDisplay& disp2, CImgDisplay& disp3, CImgDisplay& disp4, CImgDisplay& disp5,
                     CImgDisplay& disp6, CImgDisplay& disp7, CImgDisplay& disp8, CImgDisplay& disp9,
                     CImgDisplay& disp10) {
      disp1._is_event = disp2._is_event = disp3._is_event = disp4._is_event = disp5._is_event =
        disp6._is_event = disp7._is_event = disp8._is_event = disp9._is_event = disp10._is_event = false;
      while ((!disp1._is_closed || !disp2._is_closed || !disp3._is_closed || !disp4._is_closed || !disp5._is_closed ||
              !disp6._is_closed || !disp7._is_closed || !disp8._is_closed || !disp9._is_closed || !disp10._is_closed) &&
             !disp1._is_event && !disp2._is_event && !disp3._is_event && !disp4._is_event && !disp5._is_event &&
             !disp6._is_event && !disp7._is_event && !disp8._is_event && !disp9._is_event && !disp10._is_event)
        wait_all();
    }

#if cimg_display==0

    //! Wait for any window event occuring in any opened CImgDisplay.
    static void wait_all() {
      return _no_display_exception();
    }

    //! Render image into internal display buffer.
    /**
       \param img Input image data to render.
       \note
       - Convert image data representation into the internal display buffer (architecture-dependent structure).
       - The content of the associated window is not modified, until paint() is called.
       - Should not be used for common CImgDisplay uses, since display() is more useful.
    **/
    template<typename T>
    CImgDisplay& render(const CImg<T>& img) {
      return assign(img);
    }

    //! Paint internal display buffer on associated window.
    /**
       \note
       - Update the content of the associated window with the internal display buffer, e.g. after a render() call.
       - Should not be used for common CImgDisplay uses, since display() is more useful.
    **/
    CImgDisplay& paint() {
      return assign();
    }

    //! Take a snapshot of the associated window content.
    /**
       \param[out] img Output snapshot. Can be empty on input.
    **/
    template<typename T>
    const CImgDisplay& snapshot(CImg<T>& img) const {
      cimg::unused(img);
      _no_display_exception();
      return *this;
    }
#endif

    // X11-based implementation
    //--------------------------
#if cimg_display==1

    Atom _wm_window_atom, _wm_protocol_atom;
    Window _window, _background_window;
    Colormap _colormap;
    XImage *_image;
    void *_data;
#ifdef cimg_use_xshm
    XShmSegmentInfo *_shminfo;
#endif

    static int screen_width() {
      Display *const dpy = cimg::X11_attr().display;
      int res = 0;
      if (!dpy) {
        Display *const _dpy = XOpenDisplay(0);
        if (!_dpy)
          throw CImgDisplayException("CImgDisplay::screen_width(): Failed to open X11 display.");
        res = DisplayWidth(_dpy,DefaultScreen(_dpy));
        XCloseDisplay(_dpy);
      } else {
#ifdef cimg_use_xrandr
        if (cimg::X11_attr().resolutions && cimg::X11_attr().curr_resolution)
          res = cimg::X11_attr().resolutions[cimg::X11_attr().curr_resolution].width;
        else res = DisplayWidth(dpy,DefaultScreen(dpy));
#else
        res = DisplayWidth(dpy,DefaultScreen(dpy));
#endif
      }
      return res;
    }

    static int screen_height() {
      Display *const dpy = cimg::X11_attr().display;
      int res = 0;
      if (!dpy) {
        Display *const _dpy = XOpenDisplay(0);
        if (!_dpy)
          throw CImgDisplayException("CImgDisplay::screen_height(): Failed to open X11 display.");
        res = DisplayHeight(_dpy,DefaultScreen(_dpy));
        XCloseDisplay(_dpy);
      } else {
#ifdef cimg_use_xrandr
        if (cimg::X11_attr().resolutions && cimg::X11_attr().curr_resolution)
          res = cimg::X11_attr().resolutions[cimg::X11_attr().curr_resolution].height;
        else res = DisplayHeight(dpy,DefaultScreen(dpy));
#else
        res = DisplayHeight(dpy,DefaultScreen(dpy));
#endif
      }
      return res;
    }

    static void wait_all() {
      if (!cimg::X11_attr().display) return;
      pthread_mutex_lock(&cimg::X11_attr().wait_event_mutex);
      pthread_cond_wait(&cimg::X11_attr().wait_event,&cimg::X11_attr().wait_event_mutex);
      pthread_mutex_unlock(&cimg::X11_attr().wait_event_mutex);
    }

    void _handle_events(const XEvent *const pevent) {
      Display *const dpy = cimg::X11_attr().display;
      XEvent event = *pevent;
      switch (event.type) {
      case ClientMessage : {
        if ((int)event.xclient.message_type==(int)_wm_protocol_atom &&
            (int)event.xclient.data.l[0]==(int)_wm_window_atom) {
          XUnmapWindow(cimg::X11_attr().display,_window);
          _is_closed = _is_event = true;
          pthread_cond_broadcast(&cimg::X11_attr().wait_event);
        }
      } break;
      case ConfigureNotify : {
        while (XCheckWindowEvent(dpy,_window,StructureNotifyMask,&event)) {}
        const unsigned int nw = event.xconfigure.width, nh = event.xconfigure.height;
        const int nx = event.xconfigure.x, ny = event.xconfigure.y;
        if (nw && nh && (nw!=_window_width || nh!=_window_height)) {
          _window_width = nw; _window_height = nh; _mouse_x = _mouse_y = -1;
          XResizeWindow(dpy,_window,_window_width,_window_height);
          _is_resized = _is_event = true;
          pthread_cond_broadcast(&cimg::X11_attr().wait_event);
        }
        if (nx!=_window_x || ny!=_window_y) {
          _window_x = nx; _window_y = ny; _is_moved = _is_event = true;
          pthread_cond_broadcast(&cimg::X11_attr().wait_event);
        }
      } break;
      case Expose : {
        while (XCheckWindowEvent(dpy,_window,ExposureMask,&event)) {}
        _paint(false);
        if (_is_fullscreen) {
          XWindowAttributes attr;
          XGetWindowAttributes(dpy,_window,&attr);
          while (attr.map_state!=IsViewable) XSync(dpy,0);
          XSetInputFocus(dpy,_window,RevertToParent,CurrentTime);
        }
      } break;
      case ButtonPress : {
        do {
          _mouse_x = event.xmotion.x; _mouse_y = event.xmotion.y;
          if (_mouse_x<0 || _mouse_y<0 || _mouse_x>=width() || _mouse_y>=height()) _mouse_x = _mouse_y = -1;
          switch (event.xbutton.button) {
          case 1 : set_button(1); break;
          case 3 : set_button(2); break;
          case 2 : set_button(3); break;
          }
        } while (XCheckWindowEvent(dpy,_window,ButtonPressMask,&event));
      } break;
      case ButtonRelease : {
        do {
          _mouse_x = event.xmotion.x; _mouse_y = event.xmotion.y;
          if (_mouse_x<0 || _mouse_y<0 || _mouse_x>=width() || _mouse_y>=height()) _mouse_x = _mouse_y = -1;
          switch (event.xbutton.button) {
          case 1 : set_button(1,false); break;
          case 3 : set_button(2,false); break;
          case 2 : set_button(3,false); break;
          case 4 : set_wheel(1); break;
          case 5 : set_wheel(-1); break;
          }
        } while (XCheckWindowEvent(dpy,_window,ButtonReleaseMask,&event));
      } break;
      case KeyPress : {
        char tmp = 0; KeySym ksym;
        XLookupString(&event.xkey,&tmp,1,&ksym,0);
        set_key((unsigned int)ksym,true);
      } break;
      case KeyRelease : {
        char keys_return[32];  // Check that the key has been physically unpressed.
        XQueryKeymap(dpy,keys_return);
        const unsigned int kc = event.xkey.keycode, kc1 = kc/8, kc2 = kc%8;
        const bool is_key_pressed = kc1>=32?false:(keys_return[kc1]>>kc2)&1;
        if (!is_key_pressed) {
          char tmp = 0; KeySym ksym;
          XLookupString(&event.xkey,&tmp,1,&ksym,0);
          set_key((unsigned int)ksym,false);
        }
      } break;
      case EnterNotify: {
        while (XCheckWindowEvent(dpy,_window,EnterWindowMask,&event)) {}
        _mouse_x = event.xmotion.x;
        _mouse_y = event.xmotion.y;
        if (_mouse_x<0 || _mouse_y<0 || _mouse_x>=width() || _mouse_y>=height()) _mouse_x = _mouse_y = -1;
      } break;
      case LeaveNotify : {
        while (XCheckWindowEvent(dpy,_window,LeaveWindowMask,&event)) {}
        _mouse_x = _mouse_y = -1; _is_event = true;
        pthread_cond_broadcast(&cimg::X11_attr().wait_event);
      } break;
      case MotionNotify : {
        while (XCheckWindowEvent(dpy,_window,PointerMotionMask,&event)) {}
        _mouse_x = event.xmotion.x;
        _mouse_y = event.xmotion.y;
        if (_mouse_x<0 || _mouse_y<0 || _mouse_x>=width() || _mouse_y>=height()) _mouse_x = _mouse_y = -1;
        _is_event = true;
        pthread_cond_broadcast(&cimg::X11_attr().wait_event);
      } break;
      }
    }

    static void* _events_thread(void *arg) { // Thread to manage events for all opened display windows.
      Display *const dpy = cimg::X11_attr().display;
      XEvent event;
      pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,0);
      pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,0);
      if (!arg) for ( ; ; ) {
        cimg_lock_display();
        bool event_flag = XCheckTypedEvent(dpy,ClientMessage,&event);
        if (!event_flag) event_flag = XCheckMaskEvent(dpy,
                                                      ExposureMask | StructureNotifyMask | ButtonPressMask |
                                                      KeyPressMask | PointerMotionMask | EnterWindowMask |
                                                      LeaveWindowMask | ButtonReleaseMask | KeyReleaseMask,&event);
        if (event_flag)
          for (unsigned int i = 0; i<cimg::X11_attr().nb_wins; ++i)
            if (!cimg::X11_attr().wins[i]->_is_closed && event.xany.window==cimg::X11_attr().wins[i]->_window)
              cimg::X11_attr().wins[i]->_handle_events(&event);
        cimg_unlock_display();
        pthread_testcancel();
        cimg::sleep(8);
      }
      return 0;
    }

    void _set_colormap(Colormap& _colormap, const unsigned int dim) {
      XColor *const colormap = new XColor[256];
      switch (dim) {
      case 1 : { // colormap for greyscale images
        for (unsigned int index = 0; index<256; ++index) {
          colormap[index].pixel = index;
          colormap[index].red = colormap[index].green = colormap[index].blue = (unsigned short)(index<<8);
          colormap[index].flags = DoRed | DoGreen | DoBlue;
        }
      } break;
      case 2 : { // colormap for RG images
        for (unsigned int index = 0, r = 8; r<256; r+=16)
          for (unsigned int g = 8; g<256; g+=16) {
            colormap[index].pixel = index;
            colormap[index].red = colormap[index].blue = (unsigned short)(r<<8);
            colormap[index].green = (unsigned short)(g<<8);
            colormap[index++].flags = DoRed | DoGreen | DoBlue;
          }
      } break;
      default : { // colormap for RGB images
        for (unsigned int index = 0, r = 16; r<256; r+=32)
          for (unsigned int g = 16; g<256; g+=32)
            for (unsigned int b = 32; b<256; b+=64) {
              colormap[index].pixel = index;
              colormap[index].red = (unsigned short)(r<<8);
              colormap[index].green = (unsigned short)(g<<8);
              colormap[index].blue = (unsigned short)(b<<8);
              colormap[index++].flags = DoRed | DoGreen | DoBlue;
            }
      }
      }
      XStoreColors(cimg::X11_attr().display,_colormap,colormap,256);
      delete[] colormap;
    }

    void _map_window() {
      Display *const dpy = cimg::X11_attr().display;
      bool is_exposed = false, is_mapped = false;
      XWindowAttributes attr;
      XEvent event;
      XMapRaised(dpy,_window);
      do { // Wait for the window to be mapped.
        XWindowEvent(dpy,_window,StructureNotifyMask | ExposureMask,&event);
        switch (event.type) {
        case MapNotify : is_mapped = true; break;
        case Expose : is_exposed = true; break;
        }
      } while (!is_exposed || !is_mapped);
      do { // Wait for the window to be visible.
        XGetWindowAttributes(dpy,_window,&attr);
        if (attr.map_state!=IsViewable) { XSync(dpy,0); cimg::sleep(10); }
      } while (attr.map_state!=IsViewable);
      _window_x = attr.x;
      _window_y = attr.y;
    }

    void _paint(const bool wait_expose=true) {
      if (_is_closed || !_image) return;
      Display *const dpy = cimg::X11_attr().display;
      if (wait_expose) { // Send an expose event sticked to display window to force repaint.
        XEvent event;
        event.xexpose.type = Expose;
        event.xexpose.serial = 0;
        event.xexpose.send_event = 1;
        event.xexpose.display = dpy;
        event.xexpose.window = _window;
        event.xexpose.x = 0;
        event.xexpose.y = 0;
        event.xexpose.width = width();
        event.xexpose.height = height();
        event.xexpose.count = 0;
        XSendEvent(dpy,_window,0,0,&event);
      } else { // Repaint directly (may be called from the expose event).
        GC gc = DefaultGC(dpy,DefaultScreen(dpy));
#ifdef cimg_use_xshm
        if (_shminfo) XShmPutImage(dpy,_window,gc,_image,0,0,0,0,_width,_height,1);
        else XPutImage(dpy,_window,gc,_image,0,0,0,0,_width,_height);
#else
        XPutImage(dpy,_window,gc,_image,0,0,0,0,_width,_height);
#endif
      }
    }

    template<typename T>
    void _resize(T pixel_type, const unsigned int ndimx, const unsigned int ndimy, const bool force_redraw) {
      Display *const dpy = cimg::X11_attr().display;
      cimg::unused(pixel_type);

#ifdef cimg_use_xshm
      if (_shminfo) {
        XShmSegmentInfo *const nshminfo = new XShmSegmentInfo;
        XImage *const nimage = XShmCreateImage(dpy,DefaultVisual(dpy,DefaultScreen(dpy)),
                                               cimg::X11_attr().nb_bits,ZPixmap,0,nshminfo,ndimx,ndimy);
        if (!nimage) { delete nshminfo; return; }
        else {
          nshminfo->shmid = shmget(IPC_PRIVATE,ndimx*ndimy*sizeof(T),IPC_CREAT | 0777);
          if (nshminfo->shmid==-1) { XDestroyImage(nimage); delete nshminfo; return; }
          else {
            nshminfo->shmaddr = nimage->data = (char*)shmat(nshminfo->shmid,0,0);
            if (nshminfo->shmaddr==(char*)-1) {
              shmctl(nshminfo->shmid,IPC_RMID,0); XDestroyImage(nimage); delete nshminfo; return;
            } else {
              nshminfo->readOnly = 0;
              cimg::X11_attr().is_shm_enabled = true;
              XErrorHandler oldXErrorHandler = XSetErrorHandler(_assign_xshm);
              XShmAttach(dpy,nshminfo);
              XFlush(dpy);
              XSetErrorHandler(oldXErrorHandler);
              if (!cimg::X11_attr().is_shm_enabled) {
                shmdt(nshminfo->shmaddr);
                shmctl(nshminfo->shmid,IPC_RMID,0);
                XDestroyImage(nimage);
                delete nshminfo;
                return;
              } else {
                T *const ndata = (T*)nimage->data;
                if (force_redraw) _render_resize((T*)_data,_width,_height,ndata,ndimx,ndimy);
                else std::memset(ndata,0,sizeof(T)*ndimx*ndimy);
                XShmDetach(dpy,_shminfo);
                XDestroyImage(_image);
                shmdt(_shminfo->shmaddr);
                shmctl(_shminfo->shmid,IPC_RMID,0);
                delete _shminfo;
                _shminfo = nshminfo;
                _image = nimage;
                _data = (void*)ndata;
              }
            }
          }
        }
      } else
#endif
        {
          T *ndata = (T*)std::malloc(ndimx*ndimy*sizeof(T));
          if (force_redraw) _render_resize((T*)_data,_width,_height,ndata,ndimx,ndimy);
          else std::memset(ndata,0,sizeof(T)*ndimx*ndimy);
          _data = (void*)ndata;
          XDestroyImage(_image);
          _image = XCreateImage(dpy,DefaultVisual(dpy,DefaultScreen(dpy)),
                                cimg::X11_attr().nb_bits,ZPixmap,0,(char*)_data,ndimx,ndimy,8,0);
        }
    }

    void _init_fullscreen() {
      if (!_is_fullscreen || _is_closed) return;
      Display *const dpy = cimg::X11_attr().display;
      _background_window = 0;

#ifdef cimg_use_xrandr
      int foo;
      if (XRRQueryExtension(dpy,&foo,&foo)) {
        XRRRotations(dpy,DefaultScreen(dpy),&cimg::X11_attr().curr_rotation);
        if (!cimg::X11_attr().resolutions) {
          cimg::X11_attr().resolutions = XRRSizes(dpy,DefaultScreen(dpy),&foo);
          cimg::X11_attr().nb_resolutions = (unsigned int)foo;
        }
        if (cimg::X11_attr().resolutions) {
          cimg::X11_attr().curr_resolution = 0;
          for (unsigned int i = 0; i<cimg::X11_attr().nb_resolutions; ++i) {
            const unsigned int
              nw = (unsigned int)(cimg::X11_attr().resolutions[i].width),
              nh = (unsigned int)(cimg::X11_attr().resolutions[i].height);
            if (nw>=_width && nh>=_height &&
                nw<=(unsigned int)(cimg::X11_attr().resolutions[cimg::X11_attr().curr_resolution].width) &&
                nh<=(unsigned int)(cimg::X11_attr().resolutions[cimg::X11_attr().curr_resolution].height))
              cimg::X11_attr().curr_resolution = i;
          }
          if (cimg::X11_attr().curr_resolution>0) {
            XRRScreenConfiguration *config = XRRGetScreenInfo(dpy,DefaultRootWindow(dpy));
            XRRSetScreenConfig(dpy,config,DefaultRootWindow(dpy),
                               cimg::X11_attr().curr_resolution,cimg::X11_attr().curr_rotation,CurrentTime);
            XRRFreeScreenConfigInfo(config);
            XSync(dpy,0);
          }
        }
      }
      if (!cimg::X11_attr().resolutions)
        cimg::warn(_cimgdisplay_instance
                   "init_fullscreen(): Xrandr extension not supported by the X server.",
                   cimgdisplay_instance);
#endif

      const unsigned int sx = screen_width(), sy = screen_height();
      if (sx==_width && sy==_height) return;
      XSetWindowAttributes winattr;
      winattr.override_redirect = 1;
      _background_window = XCreateWindow(dpy,DefaultRootWindow(dpy),0,0,sx,sy,0,0,
                                         InputOutput,CopyFromParent,CWOverrideRedirect,&winattr);
      const cimg_ulong buf_size = (cimg_ulong)sx*sy*(cimg::X11_attr().nb_bits==8?1:
                                                     (cimg::X11_attr().nb_bits==16?2:4));
      void *background_data = std::malloc(buf_size);
      std::memset(background_data,0,buf_size);
      XImage *background_image = XCreateImage(dpy,DefaultVisual(dpy,DefaultScreen(dpy)),cimg::X11_attr().nb_bits,
                                              ZPixmap,0,(char*)background_data,sx,sy,8,0);
      XEvent event;
      XSelectInput(dpy,_background_window,StructureNotifyMask);
      XMapRaised(dpy,_background_window);
      do XWindowEvent(dpy,_background_window,StructureNotifyMask,&event);
      while (event.type!=MapNotify);
      GC gc = DefaultGC(dpy,DefaultScreen(dpy));
#ifdef cimg_use_xshm
      if (_shminfo) XShmPutImage(dpy,_background_window,gc,background_image,0,0,0,0,sx,sy,0);
      else XPutImage(dpy,_background_window,gc,background_image,0,0,0,0,sx,sy);
#else
      XPutImage(dpy,_background_window,gc,background_image,0,0,0,0,sx,sy);
#endif
      XWindowAttributes attr;
      XGetWindowAttributes(dpy,_background_window,&attr);
      while (attr.map_state!=IsViewable) XSync(dpy,0);
      XDestroyImage(background_image);
    }

    void _desinit_fullscreen() {
      if (!_is_fullscreen) return;
      Display *const dpy = cimg::X11_attr().display;
      XUngrabKeyboard(dpy,CurrentTime);
#ifdef cimg_use_xrandr
      if (cimg::X11_attr().resolutions && cimg::X11_attr().curr_resolution) {
        XRRScreenConfiguration *config = XRRGetScreenInfo(dpy,DefaultRootWindow(dpy));
        XRRSetScreenConfig(dpy,config,DefaultRootWindow(dpy),0,cimg::X11_attr().curr_rotation,CurrentTime);
        XRRFreeScreenConfigInfo(config);
        XSync(dpy,0);
        cimg::X11_attr().curr_resolution = 0;
      }
#endif
      if (_background_window) XDestroyWindow(dpy,_background_window);
      _background_window = 0;
      _is_fullscreen = false;
    }

    static int _assign_xshm(Display *dpy, XErrorEvent *error) {
      cimg::unused(dpy,error);
      cimg::X11_attr().is_shm_enabled = false;
      return 0;
    }

    void _assign(const unsigned int dimw, const unsigned int dimh, const char *const ptitle=0,
                 const unsigned int normalization_type=3,
                 const bool fullscreen_flag=false, const bool closed_flag=false) {
      cimg::mutex(14);

      // Allocate space for window title
      const char *const nptitle = ptitle?ptitle:"";
      const unsigned int s = (unsigned int)std::strlen(nptitle) + 1;
      char *const tmp_title = s?new char[s]:0;
      if (s) std::memcpy(tmp_title,nptitle,s*sizeof(char));

      // Destroy previous display window if existing
      if (!is_empty()) assign();

      // Open X11 display and retrieve graphical properties.
      Display* &dpy = cimg::X11_attr().display;
      if (!dpy) {
        dpy = XOpenDisplay(0);
        if (!dpy)
          throw CImgDisplayException(_cimgdisplay_instance
                                     "assign(): Failed to open X11 display.",
                                     cimgdisplay_instance);

        cimg::X11_attr().nb_bits = DefaultDepth(dpy,DefaultScreen(dpy));
        if (cimg::X11_attr().nb_bits!=8 && cimg::X11_attr().nb_bits!=16 &&
            cimg::X11_attr().nb_bits!=24 && cimg::X11_attr().nb_bits!=32)
          throw CImgDisplayException(_cimgdisplay_instance
                                     "assign(): Invalid %u bits screen mode detected "
                                     "(only 8, 16, 24 and 32 bits modes are managed).",
                                     cimgdisplay_instance,
                                     cimg::X11_attr().nb_bits);
        XVisualInfo vtemplate;
        vtemplate.visualid = XVisualIDFromVisual(DefaultVisual(dpy,DefaultScreen(dpy)));
        int nb_visuals;
        XVisualInfo *vinfo = XGetVisualInfo(dpy,VisualIDMask,&vtemplate,&nb_visuals);
        if (vinfo && vinfo->red_mask<vinfo->blue_mask) cimg::X11_attr().is_blue_first = true;
        cimg::X11_attr().byte_order = ImageByteOrder(dpy);
        XFree(vinfo);

        cimg_lock_display();
        cimg::X11_attr().events_thread = new pthread_t;
        pthread_create(cimg::X11_attr().events_thread,0,_events_thread,0);
      } else cimg_lock_display();

      // Set display variables.
      _width = cimg::min(dimw,(unsigned int)screen_width());
      _height = cimg::min(dimh,(unsigned int)screen_height());
      _normalization = normalization_type<4?normalization_type:3;
      _is_fullscreen = fullscreen_flag;
      _window_x = _window_y = 0;
      _is_closed = closed_flag;
      _title = tmp_title;
      flush();

      // Create X11 window (and LUT, if 8bits display)
      if (_is_fullscreen) {
        if (!_is_closed) _init_fullscreen();
        const unsigned int sx = screen_width(), sy = screen_height();
        XSetWindowAttributes winattr;
        winattr.override_redirect = 1;
        _window = XCreateWindow(dpy,DefaultRootWindow(dpy),(sx - _width)/2,(sy - _height)/2,_width,_height,0,0,
                                InputOutput,CopyFromParent,CWOverrideRedirect,&winattr);
      } else
        _window = XCreateSimpleWindow(dpy,DefaultRootWindow(dpy),0,0,_width,_height,0,0L,0L);

      XSelectInput(dpy,_window,
                   ExposureMask | StructureNotifyMask | ButtonPressMask | KeyPressMask | PointerMotionMask |
                   EnterWindowMask | LeaveWindowMask | ButtonReleaseMask | KeyReleaseMask);

      XStoreName(dpy,_window,_title?_title:" ");
      if (cimg::X11_attr().nb_bits==8) {
        _colormap = XCreateColormap(dpy,_window,DefaultVisual(dpy,DefaultScreen(dpy)),AllocAll);
        _set_colormap(_colormap,3);
        XSetWindowColormap(dpy,_window,_colormap);
      }

      static const char *const _window_class = cimg_appname;
      XClassHint *const window_class = XAllocClassHint();
      window_class->res_name = (char*)_window_class;
      window_class->res_class = (char*)_window_class;
      XSetClassHint(dpy,_window,window_class);
      XFree(window_class);

      _window_width = _width;
      _window_height = _height;

      // Create XImage
#ifdef cimg_use_xshm
      _shminfo = 0;
      if (XShmQueryExtension(dpy)) {
        _shminfo = new XShmSegmentInfo;
        _image = XShmCreateImage(dpy,DefaultVisual(dpy,DefaultScreen(dpy)),cimg::X11_attr().nb_bits,
                                 ZPixmap,0,_shminfo,_width,_height);
        if (!_image) { delete _shminfo; _shminfo = 0; }
        else {
          _shminfo->shmid = shmget(IPC_PRIVATE,_image->bytes_per_line*_image->height,IPC_CREAT|0777);
          if (_shminfo->shmid==-1) { XDestroyImage(_image); delete _shminfo; _shminfo = 0; }
          else {
            _shminfo->shmaddr = _image->data = (char*)(_data = shmat(_shminfo->shmid,0,0));
            if (_shminfo->shmaddr==(char*)-1) {
              shmctl(_shminfo->shmid,IPC_RMID,0); XDestroyImage(_image); delete _shminfo; _shminfo = 0;
            } else {
              _shminfo->readOnly = 0;
              cimg::X11_attr().is_shm_enabled = true;
              XErrorHandler oldXErrorHandler = XSetErrorHandler(_assign_xshm);
              XShmAttach(dpy,_shminfo);
              XSync(dpy,0);
              XSetErrorHandler(oldXErrorHandler);
              if (!cimg::X11_attr().is_shm_enabled) {
                shmdt(_shminfo->shmaddr); shmctl(_shminfo->shmid,IPC_RMID,0); XDestroyImage(_image);
                delete _shminfo; _shminfo = 0;
              }
            }
          }
        }
      }
      if (!_shminfo)
#endif
        {
          const cimg_ulong buf_size = (cimg_ulong)_width*_height*(cimg::X11_attr().nb_bits==8?1:
                                                                  (cimg::X11_attr().nb_bits==16?2:4));
          _data = std::malloc(buf_size);
          _image = XCreateImage(dpy,DefaultVisual(dpy,DefaultScreen(dpy)),cimg::X11_attr().nb_bits,
                                ZPixmap,0,(char*)_data,_width,_height,8,0);
        }

      _wm_window_atom = XInternAtom(dpy,"WM_DELETE_WINDOW",0);
      _wm_protocol_atom = XInternAtom(dpy,"WM_PROTOCOLS",0);
      XSetWMProtocols(dpy,_window,&_wm_window_atom,1);

      if (_is_fullscreen) XGrabKeyboard(dpy,_window,1,GrabModeAsync,GrabModeAsync,CurrentTime);
      cimg::X11_attr().wins[cimg::X11_attr().nb_wins++]=this;
      if (!_is_closed) _map_window(); else { _window_x = _window_y = cimg::type<int>::min(); }
      cimg_unlock_display();
      cimg::mutex(14,0);
    }

    CImgDisplay& assign() {
      if (is_empty()) return flush();
      Display *const dpy = cimg::X11_attr().display;
      cimg_lock_display();

      // Remove display window from event thread list.
      unsigned int i;
      for (i = 0; i<cimg::X11_attr().nb_wins && cimg::X11_attr().wins[i]!=this; ++i) {}
      for ( ; i<cimg::X11_attr().nb_wins - 1; ++i) cimg::X11_attr().wins[i] = cimg::X11_attr().wins[i + 1];
      --cimg::X11_attr().nb_wins;

      // Destroy window, image, colormap and title.
      if (_is_fullscreen && !_is_closed) _desinit_fullscreen();
      XDestroyWindow(dpy,_window);
      _window = 0;
#ifdef cimg_use_xshm
      if (_shminfo) {
        XShmDetach(dpy,_shminfo);
        XDestroyImage(_image);
        shmdt(_shminfo->shmaddr);
        shmctl(_shminfo->shmid,IPC_RMID,0);
        delete _shminfo;
        _shminfo = 0;
      } else
#endif
        XDestroyImage(_image);
      _data = 0; _image = 0;
      if (cimg::X11_attr().nb_bits==8) XFreeColormap(dpy,_colormap);
      _colormap = 0;
      XSync(dpy,0);

      // Reset display variables.
      delete[] _title;
      _width = _height = _normalization = _window_width = _window_height = 0;
      _window_x = _window_y = 0;
      _is_fullscreen = false;
      _is_closed = true;
      _min = _max = 0;
      _title = 0;
      flush();

      cimg_unlock_display();
      return *this;
    }

    CImgDisplay& assign(const unsigned int dimw, const unsigned int dimh, const char *const title=0,
                        const unsigned int normalization_type=3,
                        const bool fullscreen_flag=false, const bool closed_flag=false) {
      if (!dimw || !dimh) return assign();
      _assign(dimw,dimh,title,normalization_type,fullscreen_flag,closed_flag);
      _min = _max = 0;
      std::memset(_data,0,(cimg::X11_attr().nb_bits==8?sizeof(unsigned char):
                           (cimg::X11_attr().nb_bits==16?sizeof(unsigned short):sizeof(unsigned int)))*
                  (size_t)_width*_height);
      return paint();
    }

    template<typename T>
    CImgDisplay& assign(const CImg<T>& img, const char *const title=0,
                        const unsigned int normalization_type=3,
                        const bool fullscreen_flag=false, const bool closed_flag=false) {
      if (!img) return assign();
      CImg<T> tmp;
      const CImg<T>& nimg = (img._depth==1)?img:(tmp=img.get_projections2d((img._width - 1)/2,
                                                                           (img._height - 1)/2,
                                                                           (img._depth - 1)/2));
      _assign(nimg._width,nimg._height,title,normalization_type,fullscreen_flag,closed_flag);
      if (_normalization==2) _min = (float)nimg.min_max(_max);
      return render(nimg).paint();
    }

    template<typename T>
    CImgDisplay& assign(const CImgList<T>& list, const char *const title=0,
                        const unsigned int normalization_type=3,
                        const bool fullscreen_flag=false, const bool closed_flag=false) {
      if (!list) return assign();
      CImg<T> tmp;
      const CImg<T> img = list>'x', &nimg = (img._depth==1)?img:(tmp=img.get_projections2d((img._width - 1)/2,
                                                                                           (img._height - 1)/2,
                                                                                           (img._depth - 1)/2));
      _assign(nimg._width,nimg._height,title,normalization_type,fullscreen_flag,closed_flag);
      if (_normalization==2) _min = (float)nimg.min_max(_max);
      return render(nimg).paint();
    }

    CImgDisplay& assign(const CImgDisplay& disp) {
      if (!disp) return assign();
      _assign(disp._width,disp._height,disp._title,disp._normalization,disp._is_fullscreen,disp._is_closed);
      std::memcpy(_data,disp._data,(cimg::X11_attr().nb_bits==8?sizeof(unsigned char):
                                    cimg::X11_attr().nb_bits==16?sizeof(unsigned short):
                                    sizeof(unsigned int))*(size_t)_width*_height);
      return paint();
    }

    CImgDisplay& resize(const int nwidth, const int nheight, const bool force_redraw=true) {
      if (!nwidth || !nheight || (is_empty() && (nwidth<0 || nheight<0))) return assign();
      if (is_empty()) return assign(nwidth,nheight);
      Display *const dpy = cimg::X11_attr().display;
      const unsigned int
        tmpdimx = (nwidth>0)?nwidth:(-nwidth*width()/100),
        tmpdimy = (nheight>0)?nheight:(-nheight*height()/100),
        dimx = tmpdimx?tmpdimx:1,
        dimy = tmpdimy?tmpdimy:1;
      if (_width!=dimx || _height!=dimy || _window_width!=dimx || _window_height!=dimy) {
        show();
        cimg_lock_display();
        if (_window_width!=dimx || _window_height!=dimy) {
          XWindowAttributes attr;
          for (unsigned int i = 0; i<10; ++i) {
            XResizeWindow(dpy,_window,dimx,dimy);
            XGetWindowAttributes(dpy,_window,&attr);
            if (attr.width==(int)dimx && attr.height==(int)dimy) break;
            cimg::wait(5);
          }
        }
        if (_width!=dimx || _height!=dimy) switch (cimg::X11_attr().nb_bits) {
          case 8 :  { unsigned char pixel_type = 0; _resize(pixel_type,dimx,dimy,force_redraw); } break;
          case 16 : { unsigned short pixel_type = 0; _resize(pixel_type,dimx,dimy,force_redraw); } break;
          default : { unsigned int pixel_type = 0; _resize(pixel_type,dimx,dimy,force_redraw); }
          }
        _window_width = _width = dimx; _window_height = _height = dimy;
        cimg_unlock_display();
      }
      _is_resized = false;
      if (_is_fullscreen) move((screen_width() - _width)/2,(screen_height() - _height)/2);
      if (force_redraw) return paint();
      return *this;
    }

    CImgDisplay& toggle_fullscreen(const bool force_redraw=true) {
      if (is_empty()) return *this;
      if (force_redraw) {
        const cimg_ulong buf_size = (cimg_ulong)_width*_height*
          (cimg::X11_attr().nb_bits==8?1:(cimg::X11_attr().nb_bits==16?2:4));
        void *image_data = std::malloc(buf_size);
        std::memcpy(image_data,_data,buf_size);
        assign(_width,_height,_title,_normalization,!_is_fullscreen,false);
        std::memcpy(_data,image_data,buf_size);
        std::free(image_data);
        return paint();
      }
      return assign(_width,_height,_title,_normalization,!_is_fullscreen,false);
    }

    CImgDisplay& show() {
      if (is_empty() || !_is_closed) return *this;
      cimg_lock_display();
      if (_is_fullscreen) _init_fullscreen();
      _map_window();
      _is_closed = false;
      cimg_unlock_display();
      return paint();
    }

    CImgDisplay& close() {
      if (is_empty() || _is_closed) return *this;
      Display *const dpy = cimg::X11_attr().display;
      cimg_lock_display();
      if (_is_fullscreen) _desinit_fullscreen();
      XUnmapWindow(dpy,_window);
      _window_x = _window_y = -1;
      _is_closed = true;
      cimg_unlock_display();
      return *this;
    }

    CImgDisplay& move(const int posx, const int posy) {
      if (is_empty()) return *this;
      if (_window_x!=posx || _window_y!=posy) {
        show();
        Display *const dpy = cimg::X11_attr().display;
        cimg_lock_display();
        XMoveWindow(dpy,_window,posx,posy);
        _window_x = posx; _window_y = posy;
        cimg_unlock_display();
      }
      _is_moved = false;
      return paint();
    }

    CImgDisplay& show_mouse() {
      if (is_empty()) return *this;
      Display *const dpy = cimg::X11_attr().display;
      cimg_lock_display();
      XUndefineCursor(dpy,_window);
      cimg_unlock_display();
      return *this;
    }

    CImgDisplay& hide_mouse() {
      if (is_empty()) return *this;
      Display *const dpy = cimg::X11_attr().display;
      cimg_lock_display();
      static const char pix_data[8] = { 0 };
      XColor col;
      col.red = col.green = col.blue = 0;
      Pixmap pix = XCreateBitmapFromData(dpy,_window,pix_data,8,8);
      Cursor cur = XCreatePixmapCursor(dpy,pix,pix,&col,&col,0,0);
      XFreePixmap(dpy,pix);
      XDefineCursor(dpy,_window,cur);
      cimg_unlock_display();
      return *this;
    }

    CImgDisplay& set_mouse(const int posx, const int posy) {
      if (is_empty() || _is_closed) return *this;
      Display *const dpy = cimg::X11_attr().display;
      cimg_lock_display();
      XWarpPointer(dpy,0L,_window,0,0,0,0,posx,posy);
      _mouse_x = posx; _mouse_y = posy;
      _is_moved = false;
      XSync(dpy,0);
      cimg_unlock_display();
      return *this;
    }

    CImgDisplay& set_title(const char *const format, ...) {
      if (is_empty()) return *this;
      char *const tmp = new char[1024];
      va_list ap;
      va_start(ap, format);
      cimg_vsnprintf(tmp,1024,format,ap);
      va_end(ap);
      if (!std::strcmp(_title,tmp)) { delete[] tmp; return *this; }
      delete[] _title;
      const unsigned int s = (unsigned int)std::strlen(tmp) + 1;
      _title = new char[s];
      std::memcpy(_title,tmp,s*sizeof(char));
      Display *const dpy = cimg::X11_attr().display;
      cimg_lock_display();
      XStoreName(dpy,_window,tmp);
      cimg_unlock_display();
      delete[] tmp;
      return *this;
    }

    template<typename T>
    CImgDisplay& display(const CImg<T>& img) {
      if (!img)
        throw CImgArgumentException(_cimgdisplay_instance
                                    "display(): Empty specified image.",
                                    cimgdisplay_instance);
      if (is_empty()) return assign(img);
      return render(img).paint(false);
    }

    CImgDisplay& paint(const bool wait_expose=true) {
      if (is_empty()) return *this;
      cimg_lock_display();
      _paint(wait_expose);
      cimg_unlock_display();
      return *this;
    }

    template<typename T>
    CImgDisplay& render(const CImg<T>& img, const bool flag8=false) {
      if (!img)
        throw CImgArgumentException(_cimgdisplay_instance
                                    "render(): Empty specified image.",
                                    cimgdisplay_instance);
      if (is_empty()) return *this;
      if (img._depth!=1) return render(img.get_projections2d((img._width - 1)/2,(img._height - 1)/2,
                                                             (img._depth - 1)/2));
      if (cimg::X11_attr().nb_bits==8 && (img._width!=_width || img._height!=_height))
        return render(img.get_resize(_width,_height,1,-100,1));
      if (cimg::X11_attr().nb_bits==8 && !flag8 && img._spectrum==3) {
        static const CImg<typename CImg<T>::ucharT> default_colormap = CImg<typename CImg<T>::ucharT>::default_LUT256();
        return render(img.get_index(default_colormap,1,false));
      }

      const T
        *data1 = img._data,
        *data2 = (img._spectrum>1)?img.data(0,0,0,1):data1,
        *data3 = (img._spectrum>2)?img.data(0,0,0,2):data1;

      if (cimg::X11_attr().is_blue_first) cimg::swap(data1,data3);
      cimg_lock_display();

      if (!_normalization || (_normalization==3 && cimg::type<T>::string()==cimg::type<unsigned char>::string())) {
        _min = _max = 0;
        switch (cimg::X11_attr().nb_bits) {
        case 8 : { // 256 colormap, no normalization
          _set_colormap(_colormap,img._spectrum);
          unsigned char
            *const ndata = (img._width==_width && img._height==_height)?(unsigned char*)_data:
            new unsigned char[(size_t)img._width*img._height],
            *ptrd = (unsigned char*)ndata;
          switch (img._spectrum) {
          case 1 :
            for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
              (*ptrd++) = (unsigned char)*(data1++);
            break;
          case 2 : for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
              const unsigned char R = (unsigned char)*(data1++), G = (unsigned char)*(data2++);
              (*ptrd++) = (R&0xf0) | (G>>4);
            } break;
          default : for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
              const unsigned char
                R = (unsigned char)*(data1++),
                G = (unsigned char)*(data2++),
                B = (unsigned char)*(data3++);
              (*ptrd++) = (R&0xe0) | ((G>>5)<<2) | (B>>6);
            }
          }
          if (ndata!=_data) {
            _render_resize(ndata,img._width,img._height,(unsigned char*)_data,_width,_height);
            delete[] ndata;
          }
        } break;
        case 16 : { // 16 bits colors, no normalization
          unsigned short *const ndata = (img._width==_width && img._height==_height)?(unsigned short*)_data:
            new unsigned short[(size_t)img._width*img._height];
          unsigned char *ptrd = (unsigned char*)ndata;
          const unsigned int M = 248;
          switch (img._spectrum) {
          case 1 :
            if (cimg::X11_attr().byte_order)
              for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                const unsigned char val = (unsigned char)*(data1++), G = val>>2;
                *(ptrd++) = (val&M) | (G>>3);
                *(ptrd++) = (G<<5) | (G>>1);
              } else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                const unsigned char val = (unsigned char)*(data1++), G = val>>2;
                *(ptrd++) = (G<<5) | (G>>1);
                *(ptrd++) = (val&M) | (G>>3);
              }
            break;
          case 2 :
            if (cimg::X11_attr().byte_order)
              for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                const unsigned char G = (unsigned char)*(data2++)>>2;
                *(ptrd++) = ((unsigned char)*(data1++)&M) | (G>>3);
                *(ptrd++) = (G<<5);
              } else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                const unsigned char G = (unsigned char)*(data2++)>>2;
                *(ptrd++) = (G<<5);
                *(ptrd++) = ((unsigned char)*(data1++)&M) | (G>>3);
              }
            break;
          default :
            if (cimg::X11_attr().byte_order)
              for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                const unsigned char G = (unsigned char)*(data2++)>>2;
                *(ptrd++) = ((unsigned char)*(data1++)&M) | (G>>3);
                *(ptrd++) = (G<<5) | ((unsigned char)*(data3++)>>3);
              } else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                const unsigned char G = (unsigned char)*(data2++)>>2;
                *(ptrd++) = (G<<5) | ((unsigned char)*(data3++)>>3);
                *(ptrd++) = ((unsigned char)*(data1++)&M) | (G>>3);
              }
          }
          if (ndata!=_data) {
            _render_resize(ndata,img._width,img._height,(unsigned short*)_data,_width,_height);
            delete[] ndata;
          }
        } break;
        default : { // 24 bits colors, no normalization
          unsigned int *const ndata = (img._width==_width && img._height==_height)?(unsigned int*)_data:
            new unsigned int[(size_t)img._width*img._height];
          if (sizeof(int)==4) { // 32 bits int uses optimized version
            unsigned int *ptrd = ndata;
            switch (img._spectrum) {
            case 1 :
              if (cimg::X11_attr().byte_order==cimg::endianness())
                for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                  const unsigned char val = (unsigned char)*(data1++);
                  *(ptrd++) = (val<<16) | (val<<8) | val;
                }
              else
                for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                 const unsigned char val = (unsigned char)*(data1++);
                  *(ptrd++) = (val<<16) | (val<<8) | val;
                }
              break;
            case 2 :
              if (cimg::X11_attr().byte_order==cimg::endianness())
                for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
                  *(ptrd++) = ((unsigned char)*(data1++)<<16) | ((unsigned char)*(data2++)<<8);
              else
                for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
                  *(ptrd++) = ((unsigned char)*(data2++)<<16) | ((unsigned char)*(data1++)<<8);
              break;
            default :
              if (cimg::X11_attr().byte_order==cimg::endianness())
                for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
                  *(ptrd++) = ((unsigned char)*(data1++)<<16) | ((unsigned char)*(data2++)<<8) |
                    (unsigned char)*(data3++);
              else
                for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
                  *(ptrd++) = ((unsigned char)*(data3++)<<24) | ((unsigned char)*(data2++)<<16) |
                    ((unsigned char)*(data1++)<<8);
            }
          } else {
            unsigned char *ptrd = (unsigned char*)ndata;
            switch (img._spectrum) {
            case 1 :
              if (cimg::X11_attr().byte_order)
                for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                  *(ptrd++) = 0;
                  *(ptrd++) = (unsigned char)*(data1++);
                  *(ptrd++) = 0;
                  *(ptrd++) = 0;
                } else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                  *(ptrd++) = 0;
                  *(ptrd++) = 0;
                  *(ptrd++) = (unsigned char)*(data1++);
                  *(ptrd++) = 0;
                }
              break;
            case 2 :
              if (cimg::X11_attr().byte_order) cimg::swap(data1,data2);
              for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                *(ptrd++) = 0;
                *(ptrd++) = (unsigned char)*(data2++);
                *(ptrd++) = (unsigned char)*(data1++);
                *(ptrd++) = 0;
              }
              break;
            default :
              if (cimg::X11_attr().byte_order)
                for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                  *(ptrd++) = 0;
                  *(ptrd++) = (unsigned char)*(data1++);
                  *(ptrd++) = (unsigned char)*(data2++);
                  *(ptrd++) = (unsigned char)*(data3++);
                } else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                  *(ptrd++) = (unsigned char)*(data3++);
                  *(ptrd++) = (unsigned char)*(data2++);
                  *(ptrd++) = (unsigned char)*(data1++);
                  *(ptrd++) = 0;
                }
            }
          }
          if (ndata!=_data) {
            _render_resize(ndata,img._width,img._height,(unsigned int*)_data,_width,_height);
            delete[] ndata;
          }
        }
        }
      } else {
        if (_normalization==3) {
          if (cimg::type<T>::is_float()) _min = (float)img.min_max(_max);
          else { _min = (float)cimg::type<T>::min(); _max = (float)cimg::type<T>::max(); }
        } else if ((_min>_max) || _normalization==1) _min = (float)img.min_max(_max);
        const float delta = _max - _min, mm = 255/(delta?delta:1.0f);
        switch (cimg::X11_attr().nb_bits) {
        case 8 : { // 256 colormap, with normalization
          _set_colormap(_colormap,img._spectrum);
          unsigned char *const ndata = (img._width==_width && img._height==_height)?(unsigned char*)_data:
            new unsigned char[(size_t)img._width*img._height];
          unsigned char *ptrd = (unsigned char*)ndata;
          switch (img._spectrum) {
          case 1 : for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
              const unsigned char R = (unsigned char)((*(data1++) - _min)*mm);
              *(ptrd++) = R;
            } break;
          case 2 : for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
              const unsigned char
                R = (unsigned char)((*(data1++) - _min)*mm),
                G = (unsigned char)((*(data2++) - _min)*mm);
            (*ptrd++) = (R&0xf0) | (G>>4);
          } break;
          default :
            for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
              const unsigned char
                R = (unsigned char)((*(data1++) - _min)*mm),
                G = (unsigned char)((*(data2++) - _min)*mm),
                B = (unsigned char)((*(data3++) - _min)*mm);
              *(ptrd++) = (R&0xe0) | ((G>>5)<<2) | (B>>6);
            }
          }
          if (ndata!=_data) {
            _render_resize(ndata,img._width,img._height,(unsigned char*)_data,_width,_height);
            delete[] ndata;
          }
        } break;
        case 16 : { // 16 bits colors, with normalization
          unsigned short *const ndata = (img._width==_width && img._height==_height)?(unsigned short*)_data:
            new unsigned short[(size_t)img._width*img._height];
          unsigned char *ptrd = (unsigned char*)ndata;
          const unsigned int M = 248;
          switch (img._spectrum) {
          case 1 :
            if (cimg::X11_attr().byte_order)
              for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                const unsigned char val = (unsigned char)((*(data1++) - _min)*mm), G = val>>2;
                *(ptrd++) = (val&M) | (G>>3);
                *(ptrd++) = (G<<5) | (val>>3);
              } else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                const unsigned char val = (unsigned char)((*(data1++) - _min)*mm), G = val>>2;
                *(ptrd++) = (G<<5) | (val>>3);
                *(ptrd++) = (val&M) | (G>>3);
              }
            break;
          case 2 :
            if (cimg::X11_attr().byte_order)
              for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                const unsigned char G = (unsigned char)((*(data2++) - _min)*mm)>>2;
                *(ptrd++) = ((unsigned char)((*(data1++) - _min)*mm)&M) | (G>>3);
                *(ptrd++) = (G<<5);
              } else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                const unsigned char G = (unsigned char)((*(data2++) - _min)*mm)>>2;
                *(ptrd++) = (G<<5);
                *(ptrd++) = ((unsigned char)((*(data1++) - _min)*mm)&M) | (G>>3);
              }
            break;
          default :
            if (cimg::X11_attr().byte_order)
              for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                const unsigned char G = (unsigned char)((*(data2++) - _min)*mm)>>2;
                *(ptrd++) = ((unsigned char)((*(data1++) - _min)*mm)&M) | (G>>3);
                *(ptrd++) = (G<<5) | ((unsigned char)((*(data3++) - _min)*mm)>>3);
              } else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                const unsigned char G = (unsigned char)((*(data2++) - _min)*mm)>>2;
                *(ptrd++) = (G<<5) | ((unsigned char)((*(data3++) - _min)*mm)>>3);
                *(ptrd++) = ((unsigned char)((*(data1++) - _min)*mm)&M) | (G>>3);
              }
          }
          if (ndata!=_data) {
            _render_resize(ndata,img._width,img._height,(unsigned short*)_data,_width,_height);
            delete[] ndata;
          }
        } break;
        default : { // 24 bits colors, with normalization
          unsigned int *const ndata = (img._width==_width && img._height==_height)?(unsigned int*)_data:
            new unsigned int[(size_t)img._width*img._height];
          if (sizeof(int)==4) { // 32 bits int uses optimized version
            unsigned int *ptrd = ndata;
            switch (img._spectrum) {
            case 1 :
              if (cimg::X11_attr().byte_order==cimg::endianness())
                for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                  const unsigned char val = (unsigned char)((*(data1++) - _min)*mm);
                  *(ptrd++) = (val<<16) | (val<<8) | val;
                }
              else
                for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                  const unsigned char val = (unsigned char)((*(data1++) - _min)*mm);
                  *(ptrd++) = (val<<24) | (val<<16) | (val<<8);
                }
              break;
            case 2 :
              if (cimg::X11_attr().byte_order==cimg::endianness())
                for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
                  *(ptrd++) =
                    ((unsigned char)((*(data1++) - _min)*mm)<<16) |
                    ((unsigned char)((*(data2++) - _min)*mm)<<8);
              else
                for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
                  *(ptrd++) =
                    ((unsigned char)((*(data2++) - _min)*mm)<<16) |
                    ((unsigned char)((*(data1++) - _min)*mm)<<8);
              break;
            default :
              if (cimg::X11_attr().byte_order==cimg::endianness())
                for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
                  *(ptrd++) =
                    ((unsigned char)((*(data1++) - _min)*mm)<<16) |
                    ((unsigned char)((*(data2++) - _min)*mm)<<8) |
                    (unsigned char)((*(data3++) - _min)*mm);
              else
                for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy)
                  *(ptrd++) =
                    ((unsigned char)((*(data3++) - _min)*mm)<<24) |
                    ((unsigned char)((*(data2++) - _min)*mm)<<16) |
                    ((unsigned char)((*(data1++) - _min)*mm)<<8);
            }
          } else {
            unsigned char *ptrd = (unsigned char*)ndata;
            switch (img._spectrum) {
            case 1 :
              if (cimg::X11_attr().byte_order)
                for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                  const unsigned char val = (unsigned char)((*(data1++) - _min)*mm);
                  (*ptrd++) = 0;
                  (*ptrd++) = val;
                  (*ptrd++) = val;
                  (*ptrd++) = val;
                } else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                  const unsigned char val = (unsigned char)((*(data1++) - _min)*mm);
                  (*ptrd++) = val;
                  (*ptrd++) = val;
                  (*ptrd++) = val;
                  (*ptrd++) = 0;
                }
              break;
            case 2 :
              if (cimg::X11_attr().byte_order) cimg::swap(data1,data2);
              for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                (*ptrd++) = 0;
                (*ptrd++) = (unsigned char)((*(data2++) - _min)*mm);
                (*ptrd++) = (unsigned char)((*(data1++) - _min)*mm);
                (*ptrd++) = 0;
              }
              break;
            default :
              if (cimg::X11_attr().byte_order)
                for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                  (*ptrd++) = 0;
                  (*ptrd++) = (unsigned char)((*(data1++) - _min)*mm);
                  (*ptrd++) = (unsigned char)((*(data2++) - _min)*mm);
                  (*ptrd++) = (unsigned char)((*(data3++) - _min)*mm);
                } else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
                  (*ptrd++) = (unsigned char)((*(data3++) - _min)*mm);
                  (*ptrd++) = (unsigned char)((*(data2++) - _min)*mm);
                  (*ptrd++) = (unsigned char)((*(data1++) - _min)*mm);
                  (*ptrd++) = 0;
                }
            }
          }
          if (ndata!=_data) {
            _render_resize(ndata,img._width,img._height,(unsigned int*)_data,_width,_height);
            delete[] ndata;
          }
        }
        }
      }
      cimg_unlock_display();
      return *this;
    }

    template<typename T>
    const CImgDisplay& snapshot(CImg<T>& img) const {
      if (is_empty()) { img.assign(); return *this; }
      const unsigned char *ptrs = (unsigned char*)_data;
      img.assign(_width,_height,1,3);
      T
        *data1 = img.data(0,0,0,0),
        *data2 = img.data(0,0,0,1),
        *data3 = img.data(0,0,0,2);
      if (cimg::X11_attr().is_blue_first) cimg::swap(data1,data3);
      switch (cimg::X11_attr().nb_bits) {
      case 8 : {
        for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
          const unsigned char val = *(ptrs++);
          *(data1++) = (T)(val&0xe0);
          *(data2++) = (T)((val&0x1c)<<3);
          *(data3++) = (T)(val<<6);
        }
      } break;
      case 16 : {
        if (cimg::X11_attr().byte_order) for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
          const unsigned char val0 = *(ptrs++), val1 = *(ptrs++);
          *(data1++) = (T)(val0&0xf8);
          *(data2++) = (T)((val0<<5) | ((val1&0xe0)>>5));
          *(data3++) = (T)(val1<<3);
          } else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
          const unsigned short val0 = *(ptrs++), val1 = *(ptrs++);
          *(data1++) = (T)(val1&0xf8);
          *(data2++) = (T)((val1<<5) | ((val0&0xe0)>>5));
          *(data3++) = (T)(val0<<3);
        }
      } break;
      default : {
        if (cimg::X11_attr().byte_order) for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
          ++ptrs;
          *(data1++) = (T)*(ptrs++);
          *(data2++) = (T)*(ptrs++);
          *(data3++) = (T)*(ptrs++);
          } else for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
            *(data3++) = (T)*(ptrs++);
            *(data2++) = (T)*(ptrs++);
            *(data1++) = (T)*(ptrs++);
            ++ptrs;
          }
      }
      }
      return *this;
    }

    // Windows-based implementation.
    //-------------------------------
#elif cimg_display==2

    bool _is_mouse_tracked, _is_cursor_visible;
    HANDLE _thread, _is_created, _mutex;
    HWND _window, _background_window;
    CLIENTCREATESTRUCT _ccs;
    unsigned int *_data;
    DEVMODE _curr_mode;
    BITMAPINFO _bmi;
    HDC _hdc;

    static int screen_width() {
      DEVMODE mode;
      mode.dmSize = sizeof(DEVMODE);
      mode.dmDriverExtra = 0;
      EnumDisplaySettings(0,ENUM_CURRENT_SETTINGS,&mode);
      return (int)mode.dmPelsWidth;
    }

    static int screen_height() {
      DEVMODE mode;
      mode.dmSize = sizeof(DEVMODE);
      mode.dmDriverExtra = 0;
      EnumDisplaySettings(0,ENUM_CURRENT_SETTINGS,&mode);
      return (int)mode.dmPelsHeight;
    }

    static void wait_all() {
      WaitForSingleObject(cimg::Win32_attr().wait_event,INFINITE);
    }

    static LRESULT APIENTRY _handle_events(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
#ifdef _WIN64
      CImgDisplay *const disp = (CImgDisplay*)GetWindowLongPtr(window,GWLP_USERDATA);
#else
      CImgDisplay *const disp = (CImgDisplay*)GetWindowLong(window,GWL_USERDATA);
#endif
      MSG st_msg;
      switch (msg) {
      case WM_CLOSE :
        disp->_mouse_x = disp->_mouse_y = -1;
        disp->_window_x = disp->_window_y = 0;
        disp->set_button().set_key(0).set_key(0,false)._is_closed = true;
        ReleaseMutex(disp->_mutex);
        ShowWindow(disp->_window,SW_HIDE);
        disp->_is_event = true;
        SetEvent(cimg::Win32_attr().wait_event);
        return 0;
      case WM_SIZE : {
        while (PeekMessage(&st_msg,window,WM_SIZE,WM_SIZE,PM_REMOVE)) {}
        WaitForSingleObject(disp->_mutex,INFINITE);
        const unsigned int nw = LOWORD(lParam),nh = HIWORD(lParam);
        if (nw && nh && (nw!=disp->_width || nh!=disp->_height)) {
          disp->_window_width = nw;
          disp->_window_height = nh;
          disp->_mouse_x = disp->_mouse_y = -1;
          disp->_is_resized = disp->_is_event = true;
          SetEvent(cimg::Win32_attr().wait_event);
        }
        ReleaseMutex(disp->_mutex);
      } break;
      case WM_MOVE : {
        while (PeekMessage(&st_msg,window,WM_SIZE,WM_SIZE,PM_REMOVE)) {}
        WaitForSingleObject(disp->_mutex,INFINITE);
        const int nx = (int)(short)(LOWORD(lParam)), ny = (int)(short)(HIWORD(lParam));
        if (nx!=disp->_window_x || ny!=disp->_window_y) {
          disp->_window_x = nx;
          disp->_window_y = ny;
          disp->_is_moved = disp->_is_event = true;
          SetEvent(cimg::Win32_attr().wait_event);
        }
        ReleaseMutex(disp->_mutex);
      } break;
      case WM_PAINT :
        disp->paint();
        cimg::mutex(15);
        if (disp->_is_cursor_visible) while (ShowCursor(TRUE)<0); else while (ShowCursor(FALSE)>=0);
        cimg::mutex(15,0);
        break;
      case WM_ERASEBKGND :
        //        return 0;
        break;
      case WM_KEYDOWN :
        disp->set_key((unsigned int)wParam);
        SetEvent(cimg::Win32_attr().wait_event);
        break;
      case WM_KEYUP :
        disp->set_key((unsigned int)wParam,false);
        SetEvent(cimg::Win32_attr().wait_event);
        break;
      case WM_MOUSEMOVE : {
        while (PeekMessage(&st_msg,window,WM_MOUSEMOVE,WM_MOUSEMOVE,PM_REMOVE)) {}
        disp->_mouse_x = LOWORD(lParam);
        disp->_mouse_y = HIWORD(lParam);
#if (_WIN32_WINNT>=0x0400) && !defined(NOTRACKMOUSEEVENT)
        if (!disp->_is_mouse_tracked) {
          TRACKMOUSEEVENT tme;
          tme.cbSize = sizeof(TRACKMOUSEEVENT);
          tme.dwFlags = TME_LEAVE;
          tme.hwndTrack = disp->_window;
          if (TrackMouseEvent(&tme)) disp->_is_mouse_tracked = true;
        }
#endif
        if (disp->_mouse_x<0 || disp->_mouse_y<0 || disp->_mouse_x>=disp->width() || disp->_mouse_y>=disp->height())
          disp->_mouse_x = disp->_mouse_y = -1;
        disp->_is_event = true;
        SetEvent(cimg::Win32_attr().wait_event);
        cimg::mutex(15);
        if (disp->_is_cursor_visible) while (ShowCursor(TRUE)<0); else while (ShowCursor(FALSE)>=0);
        cimg::mutex(15,0);
      } break;
      case WM_MOUSELEAVE : {
        disp->_mouse_x = disp->_mouse_y = -1;
        disp->_is_mouse_tracked = false;
        cimg::mutex(15);
        while (ShowCursor(TRUE)<0);
        cimg::mutex(15,0);
      } break;
      case WM_LBUTTONDOWN :
        disp->set_button(1);
        SetEvent(cimg::Win32_attr().wait_event);
        break;
      case WM_RBUTTONDOWN :
        disp->set_button(2);
        SetEvent(cimg::Win32_attr().wait_event);
        break;
      case WM_MBUTTONDOWN :
        disp->set_button(3);
        SetEvent(cimg::Win32_attr().wait_event);
        break;
      case WM_LBUTTONUP :
        disp->set_button(1,false);
        SetEvent(cimg::Win32_attr().wait_event);
        break;
      case WM_RBUTTONUP :
        disp->set_button(2,false);
        SetEvent(cimg::Win32_attr().wait_event);
        break;
      case WM_MBUTTONUP :
        disp->set_button(3,false);
        SetEvent(cimg::Win32_attr().wait_event);
        break;
      case 0x020A : // WM_MOUSEWHEEL:
        disp->set_wheel((int)((short)HIWORD(wParam))/120);
        SetEvent(cimg::Win32_attr().wait_event);
      }
      return DefWindowProc(window,msg,wParam,lParam);
    }

    static DWORD WINAPI _events_thread(void* arg) {
      CImgDisplay *const disp = (CImgDisplay*)(((void**)arg)[0]);
      const char *const title = (const char*)(((void**)arg)[1]);
      MSG msg;
      delete[] (void**)arg;
      disp->_bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      disp->_bmi.bmiHeader.biWidth = disp->width();
      disp->_bmi.bmiHeader.biHeight = -disp->height();
      disp->_bmi.bmiHeader.biPlanes = 1;
      disp->_bmi.bmiHeader.biBitCount = 32;
      disp->_bmi.bmiHeader.biCompression = BI_RGB;
      disp->_bmi.bmiHeader.biSizeImage = 0;
      disp->_bmi.bmiHeader.biXPelsPerMeter = 1;
      disp->_bmi.bmiHeader.biYPelsPerMeter = 1;
      disp->_bmi.bmiHeader.biClrUsed = 0;
      disp->_bmi.bmiHeader.biClrImportant = 0;
      disp->_data = new unsigned int[(size_t)disp->_width*disp->_height];
      if (!disp->_is_fullscreen) { // Normal window
        RECT rect;
        rect.left = rect.top = 0; rect.right = (LONG)disp->_width - 1; rect.bottom = (LONG)disp->_height - 1;
        AdjustWindowRect(&rect,WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,false);
        const int
          border1 = (int)((rect.right - rect.left + 1 - disp->_width)/2),
          border2 = (int)(rect.bottom - rect.top + 1 - disp->_height - border1);
        disp->_window = CreateWindowA("MDICLIENT",title?title:" ",
                                     WS_OVERLAPPEDWINDOW | (disp->_is_closed?0:WS_VISIBLE), CW_USEDEFAULT,CW_USEDEFAULT,
                                     disp->_width + 2*border1, disp->_height + border1 + border2,
                                     0,0,0,&(disp->_ccs));
        if (!disp->_is_closed) {
          GetWindowRect(disp->_window,&rect);
          disp->_window_x = rect.left + border1;
          disp->_window_y = rect.top + border2;
        } else disp->_window_x = disp->_window_y = 0;
      } else { // Fullscreen window
        const unsigned int
          sx = (unsigned int)screen_width(),
          sy = (unsigned int)screen_height();
        disp->_window = CreateWindowA("MDICLIENT",title?title:" ",
                                     WS_POPUP | (disp->_is_closed?0:WS_VISIBLE),
                                      (sx - disp->_width)/2,
                                      (sy - disp->_height)/2,
                                     disp->_width,disp->_height,0,0,0,&(disp->_ccs));
        disp->_window_x = disp->_window_y = 0;
      }
      SetForegroundWindow(disp->_window);
      disp->_hdc = GetDC(disp->_window);
      disp->_window_width = disp->_width;
      disp->_window_height = disp->_height;
      disp->flush();
#ifdef _WIN64
      SetWindowLongPtr(disp->_window,GWLP_USERDATA,(LONG_PTR)disp);
      SetWindowLongPtr(disp->_window,GWLP_WNDPROC,(LONG_PTR)_handle_events);
#else
      SetWindowLong(disp->_window,GWL_USERDATA,(LONG)disp);
      SetWindowLong(disp->_window,GWL_WNDPROC,(LONG)_handle_events);
#endif
      SetEvent(disp->_is_created);
      while (GetMessage(&msg,0,0,0)) DispatchMessage(&msg);
      return 0;
    }

    CImgDisplay& _update_window_pos() {
      if (_is_closed) _window_x = _window_y = -1;
      else {
        RECT rect;
        rect.left = rect.top = 0; rect.right = (LONG)_width - 1; rect.bottom = (LONG)_height - 1;
        AdjustWindowRect(&rect,WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,false);
        const int
          border1 = (int)((rect.right - rect.left + 1 - _width)/2),
          border2 = (int)(rect.bottom - rect.top + 1 - _height - border1);
        GetWindowRect(_window,&rect);
        _window_x = rect.left + border1;
        _window_y = rect.top + border2;
      }
      return *this;
    }

    void _init_fullscreen() {
      _background_window = 0;
      if (!_is_fullscreen || _is_closed) _curr_mode.dmSize = 0;
      else {
        DEVMODE mode;
        unsigned int imode = 0, ibest = 0, bestbpp = 0, bw = ~0U, bh = ~0U;
        for (mode.dmSize = sizeof(DEVMODE), mode.dmDriverExtra = 0; EnumDisplaySettings(0,imode,&mode); ++imode) {
          const unsigned int nw = mode.dmPelsWidth, nh = mode.dmPelsHeight;
          if (nw>=_width && nh>=_height && mode.dmBitsPerPel>=bestbpp && nw<=bw && nh<=bh) {
            bestbpp = mode.dmBitsPerPel;
            ibest = imode;
            bw = nw; bh = nh;
          }
        }
        if (bestbpp) {
          _curr_mode.dmSize = sizeof(DEVMODE); _curr_mode.dmDriverExtra = 0;
          EnumDisplaySettings(0,ENUM_CURRENT_SETTINGS,&_curr_mode);
          EnumDisplaySettings(0,ibest,&mode);
          ChangeDisplaySettings(&mode,0);
        } else _curr_mode.dmSize = 0;

        const unsigned int
          sx = (unsigned int)screen_width(),
          sy = (unsigned int)screen_height();
        if (sx!=_width || sy!=_height) {
          CLIENTCREATESTRUCT background_ccs;
          _background_window = CreateWindowA("MDICLIENT","",WS_POPUP | WS_VISIBLE, 0,0,sx,sy,0,0,0,&background_ccs);
          SetForegroundWindow(_background_window);
        }
      }
    }

    void _desinit_fullscreen() {
      if (!_is_fullscreen) return;
      if (_background_window) DestroyWindow(_background_window);
      _background_window = 0;
      if (_curr_mode.dmSize) ChangeDisplaySettings(&_curr_mode,0);
      _is_fullscreen = false;
    }

    CImgDisplay& _assign(const unsigned int dimw, const unsigned int dimh, const char *const ptitle=0,
                         const unsigned int normalization_type=3,
                         const bool fullscreen_flag=false, const bool closed_flag=false) {

      // Allocate space for window title
      const char *const nptitle = ptitle?ptitle:"";
      const unsigned int s = (unsigned int)std::strlen(nptitle) + 1;
      char *const tmp_title = s?new char[s]:0;
      if (s) std::memcpy(tmp_title,nptitle,s*sizeof(char));

      // Destroy previous window if existing
      if (!is_empty()) assign();

      // Set display variables
      _width = cimg::min(dimw,(unsigned int)screen_width());
      _height = cimg::min(dimh,(unsigned int)screen_height());
      _normalization = normalization_type<4?normalization_type:3;
      _is_fullscreen = fullscreen_flag;
      _window_x = _window_y = 0;
      _is_closed = closed_flag;
      _is_cursor_visible = true;
      _is_mouse_tracked = false;
      _title = tmp_title;
      flush();
      if (_is_fullscreen) _init_fullscreen();

      // Create event thread
      void *const arg = (void*)(new void*[2]);
      ((void**)arg)[0] = (void*)this;
      ((void**)arg)[1] = (void*)_title;
      _mutex = CreateMutex(0,FALSE,0);
      _is_created = CreateEvent(0,FALSE,FALSE,0);
      _thread = CreateThread(0,0,_events_thread,arg,0,0);
      WaitForSingleObject(_is_created,INFINITE);
      return *this;
    }

    CImgDisplay& assign() {
      if (is_empty()) return flush();
      DestroyWindow(_window);
      TerminateThread(_thread,0);
      delete[] _data;
      delete[] _title;
      _data = 0;
      _title = 0;
      if (_is_fullscreen) _desinit_fullscreen();
      _width = _height = _normalization = _window_width = _window_height = 0;
      _window_x = _window_y = 0;
      _is_fullscreen = false;
      _is_closed = true;
      _min = _max = 0;
      _title = 0;
      flush();
      return *this;
    }

    CImgDisplay& assign(const unsigned int dimw, const unsigned int dimh, const char *const title=0,
                        const unsigned int normalization_type=3,
                        const bool fullscreen_flag=false, const bool closed_flag=false) {
      if (!dimw || !dimh) return assign();
      _assign(dimw,dimh,title,normalization_type,fullscreen_flag,closed_flag);
      _min = _max = 0;
      std::memset(_data,0,sizeof(unsigned int)*_width*_height);
      return paint();
    }

    template<typename T>
    CImgDisplay& assign(const CImg<T>& img, const char *const title=0,
                        const unsigned int normalization_type=3,
                        const bool fullscreen_flag=false, const bool closed_flag=false) {
      if (!img) return assign();
      CImg<T> tmp;
      const CImg<T>& nimg = (img._depth==1)?img:(tmp=img.get_projections2d((img._width - 1)/2,
                                                                           (img._height - 1)/2,
                                                                           (img._depth - 1)/2));
      _assign(nimg._width,nimg._height,title,normalization_type,fullscreen_flag,closed_flag);
      if (_normalization==2) _min = (float)nimg.min_max(_max);
      return display(nimg);
    }

    template<typename T>
    CImgDisplay& assign(const CImgList<T>& list, const char *const title=0,
                        const unsigned int normalization_type=3,
                        const bool fullscreen_flag=false, const bool closed_flag=false) {
      if (!list) return assign();
      CImg<T> tmp;
      const CImg<T> img = list>'x', &nimg = (img._depth==1)?img:(tmp=img.get_projections2d((img._width - 1)/2,
                                                                                           (img._height - 1)/2,
                                                                                           (img._depth - 1)/2));
      _assign(nimg._width,nimg._height,title,normalization_type,fullscreen_flag,closed_flag);
      if (_normalization==2) _min = (float)nimg.min_max(_max);
      return display(nimg);
    }

    CImgDisplay& assign(const CImgDisplay& disp) {
      if (!disp) return assign();
      _assign(disp._width,disp._height,disp._title,disp._normalization,disp._is_fullscreen,disp._is_closed);
      std::memcpy(_data,disp._data,sizeof(unsigned int)*_width*_height);
      return paint();
    }

    CImgDisplay& resize(const int nwidth, const int nheight, const bool force_redraw=true) {
      if (!nwidth || !nheight || (is_empty() && (nwidth<0 || nheight<0))) return assign();
      if (is_empty()) return assign(nwidth,nheight);
      const unsigned int
        tmpdimx = (nwidth>0)?nwidth:(-nwidth*_width/100),
        tmpdimy = (nheight>0)?nheight:(-nheight*_height/100),
        dimx = tmpdimx?tmpdimx:1,
        dimy = tmpdimy?tmpdimy:1;
      if (_width!=dimx || _height!=dimy || _window_width!=dimx || _window_height!=dimy) {
        if (_window_width!=dimx || _window_height!=dimy) {
          RECT rect; rect.left = rect.top = 0; rect.right = (LONG)dimx - 1; rect.bottom = (LONG)dimy - 1;
          AdjustWindowRect(&rect,WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,false);
          const int cwidth = rect.right - rect.left + 1, cheight = rect.bottom - rect.top + 1;
          SetWindowPos(_window,0,0,0,cwidth,cheight,SWP_NOMOVE | SWP_NOZORDER | SWP_NOCOPYBITS);
        }
        if (_width!=dimx || _height!=dimy) {
          unsigned int *const ndata = new unsigned int[dimx*dimy];
          if (force_redraw) _render_resize(_data,_width,_height,ndata,dimx,dimy);
          else std::memset(ndata,0x80,sizeof(unsigned int)*dimx*dimy);
          delete[] _data;
          _data = ndata;
          _bmi.bmiHeader.biWidth = (LONG)dimx;
          _bmi.bmiHeader.biHeight = -(int)dimy;
          _width = dimx;
          _height = dimy;
        }
        _window_width = dimx; _window_height = dimy;
        show();
      }
      _is_resized = false;
      if (_is_fullscreen) move((screen_width() - width())/2,(screen_height() - height())/2);
      if (force_redraw) return paint();
      return *this;
    }

    CImgDisplay& toggle_fullscreen(const bool force_redraw=true) {
      if (is_empty()) return *this;
      if (force_redraw) {
        const cimg_ulong buf_size = (cimg_ulong)_width*_height*4;
        void *odata = std::malloc(buf_size);
        if (odata) {
          std::memcpy(odata,_data,buf_size);
          assign(_width,_height,_title,_normalization,!_is_fullscreen,false);
          std::memcpy(_data,odata,buf_size);
          std::free(odata);
        }
        return paint();
      }
      return assign(_width,_height,_title,_normalization,!_is_fullscreen,false);
    }

    CImgDisplay& show() {
      if (is_empty() || !_is_closed) return *this;
      _is_closed = false;
      if (_is_fullscreen) _init_fullscreen();
      ShowWindow(_window,SW_SHOW);
      _update_window_pos();
      return paint();
    }

    CImgDisplay& close() {
      if (is_empty() || _is_closed) return *this;
      _is_closed = true;
      if (_is_fullscreen) _desinit_fullscreen();
      ShowWindow(_window,SW_HIDE);
      _window_x = _window_y = 0;
      return *this;
    }

    CImgDisplay& move(const int posx, const int posy) {
      if (is_empty()) return *this;
      if (_window_x!=posx || _window_y!=posy) {
        if (!_is_fullscreen) {
          RECT rect;
          rect.left = rect.top = 0; rect.right = (LONG)_window_width - 1; rect.bottom = (LONG)_window_height - 1;
          AdjustWindowRect(&rect,WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,false);
          const int
            border1 = (int)((rect.right - rect.left + 1 -_width)/2),
            border2 = (int)(rect.bottom - rect.top + 1 - _height - border1);
          SetWindowPos(_window,0,posx - border1,posy - border2,0,0,SWP_NOSIZE | SWP_NOZORDER);
        } else SetWindowPos(_window,0,posx,posy,0,0,SWP_NOSIZE | SWP_NOZORDER);
        _window_x = posx;
        _window_y = posy;
        show();
      }
      _is_moved = false;
      return *this;
    }

    CImgDisplay& show_mouse() {
      if (is_empty()) return *this;
      _is_cursor_visible = true;
      return *this;
    }

    CImgDisplay& hide_mouse() {
      if (is_empty()) return *this;
      _is_cursor_visible = false;
      return *this;
    }

    CImgDisplay& set_mouse(const int posx, const int posy) {
      if (is_empty() || _is_closed || posx<0 || posy<0) return *this;
      _update_window_pos();
      const int res = (int)SetCursorPos(_window_x + posx,_window_y + posy);
      if (res) { _mouse_x = posx; _mouse_y = posy; }
      return *this;
    }

    CImgDisplay& set_title(const char *const format, ...) {
      if (is_empty()) return *this;
      char *const tmp = new char[1024];
      va_list ap;
      va_start(ap, format);
      cimg_vsnprintf(tmp,1024,format,ap);
      va_end(ap);
      if (!std::strcmp(_title,tmp)) { delete[] tmp; return *this; }
      delete[] _title;
      const unsigned int s = (unsigned int)std::strlen(tmp) + 1;
      _title = new char[s];
      std::memcpy(_title,tmp,s*sizeof(char));
      SetWindowTextA(_window, tmp);
      delete[] tmp;
      return *this;
    }

    template<typename T>
    CImgDisplay& display(const CImg<T>& img) {
      if (!img)
        throw CImgArgumentException(_cimgdisplay_instance
                                    "display(): Empty specified image.",
                                    cimgdisplay_instance);
      if (is_empty()) return assign(img);
      return render(img).paint();
    }

    CImgDisplay& paint() {
      if (_is_closed) return *this;
      WaitForSingleObject(_mutex,INFINITE);
      SetDIBitsToDevice(_hdc,0,0,_width,_height,0,0,0,_height,_data,&_bmi,DIB_RGB_COLORS);
      ReleaseMutex(_mutex);
      return *this;
    }

    template<typename T>
    CImgDisplay& render(const CImg<T>& img) {
      if (!img)
        throw CImgArgumentException(_cimgdisplay_instance
                                    "render(): Empty specified image.",
                                    cimgdisplay_instance);

      if (is_empty()) return *this;
      if (img._depth!=1) return render(img.get_projections2d((img._width - 1)/2,(img._height - 1)/2,
                                                             (img._depth - 1)/2));

      const T
        *data1 = img._data,
        *data2 = (img._spectrum>=2)?img.data(0,0,0,1):data1,
        *data3 = (img._spectrum>=3)?img.data(0,0,0,2):data1;

      WaitForSingleObject(_mutex,INFINITE);
      unsigned int
        *const ndata = (img._width==_width && img._height==_height)?_data:
        new unsigned int[(size_t)img._width*img._height],
        *ptrd = ndata;

      if (!_normalization || (_normalization==3 && cimg::type<T>::string()==cimg::type<unsigned char>::string())) {
        _min = _max = 0;
        switch (img._spectrum) {
        case 1 : {
          for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
            const unsigned char val = (unsigned char)*(data1++);
            *(ptrd++) = (unsigned int)((val<<16) | (val<<8) | val);
          }
        } break;
        case 2 : {
          for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
            const unsigned char
              R = (unsigned char)*(data1++),
              G = (unsigned char)*(data2++);
            *(ptrd++) = (unsigned int)((R<<16) | (G<<8));
          }
        } break;
        default : {
          for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
            const unsigned char
              R = (unsigned char)*(data1++),
              G = (unsigned char)*(data2++),
              B = (unsigned char)*(data3++);
            *(ptrd++) = (unsigned int)((R<<16) | (G<<8) | B);
          }
        }
        }
      } else {
        if (_normalization==3) {
          if (cimg::type<T>::is_float()) _min = (float)img.min_max(_max);
          else { _min = (float)cimg::type<T>::min(); _max = (float)cimg::type<T>::max(); }
        } else if ((_min>_max) || _normalization==1) _min = (float)img.min_max(_max);
        const float delta = _max - _min, mm = 255/(delta?delta:1.0f);
        switch (img._spectrum) {
        case 1 : {
          for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
            const unsigned char val = (unsigned char)((*(data1++) - _min)*mm);
            *(ptrd++) = (unsigned int)((val<<16) | (val<<8) | val);
          }
        } break;
        case 2 : {
          for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
            const unsigned char
              R = (unsigned char)((*(data1++) - _min)*mm),
              G = (unsigned char)((*(data2++) - _min)*mm);
            *(ptrd++) = (unsigned int)((R<<16) | (G<<8));
          }
        } break;
        default : {
          for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
            const unsigned char
              R = (unsigned char)((*(data1++) - _min)*mm),
              G = (unsigned char)((*(data2++) - _min)*mm),
              B = (unsigned char)((*(data3++) - _min)*mm);
            *(ptrd++) = (unsigned int)((R<<16) | (G<<8) | B);
          }
        }
        }
      }
      if (ndata!=_data) { _render_resize(ndata,img._width,img._height,_data,_width,_height); delete[] ndata; }
      ReleaseMutex(_mutex);
      return *this;
    }

    template<typename T>
    const CImgDisplay& snapshot(CImg<T>& img) const {
      if (is_empty()) { img.assign(); return *this; }
      const unsigned int *ptrs = _data;
      img.assign(_width,_height,1,3);
      T
        *data1 = img.data(0,0,0,0),
        *data2 = img.data(0,0,0,1),
        *data3 = img.data(0,0,0,2);
      for (cimg_ulong xy = (cimg_ulong)img._width*img._height; xy>0; --xy) {
        const unsigned int val = *(ptrs++);
        *(data1++) = (T)(unsigned char)(val>>16);
        *(data2++) = (T)(unsigned char)((val>>8)&0xFF);
        *(data3++) = (T)(unsigned char)(val&0xFF);
      }
      return *this;
    }
#endif

    //@}
  };

  /*
   #--------------------------------------
   #
   #
   #
   # Definition of the CImg<T> structure
   #
   #
   #
   #--------------------------------------
   */

  //! Class representing an image (up to 4 dimensions wide), each pixel being of type \c T.
  /**
     This is the main class of the %CImg Library. It declares and constructs
     an image, allows access to its pixel values, and is able to perform various image operations.

     \par Image representation

     A %CImg image is defined as an instance of the container \c CImg<T>, which contains a regular grid of pixels,
     each pixel value being of type \c T. The image grid can have up to 4 dimensions: width, height, depth
     and number of channels.
     Usually, the three first dimensions are used to describe spatial coordinates <tt>(x,y,z)</tt>,
     while the number of channels is rather used as a vector-valued dimension
     (it may describe the R,G,B color channels for instance).
     If you need a fifth dimension, you can use image lists \c CImgList<T> rather than simple images \c CImg<T>.

     Thus, the \c CImg<T> class is able to represent volumetric images of vector-valued pixels,
     as well as images with less dimensions (1d scalar signal, 2d color images, ...).
     Most member functions of the class CImg<\c T> are designed to handle this maximum case of (3+1) dimensions.

     Concerning the pixel value type \c T:
     fully supported template types are the basic C++ types: <tt>unsigned char, char, short, unsigned int, int,
     unsigned long, long, float, double, ... </tt>.
     Typically, fast image display can be done using <tt>CImg<unsigned char></tt> images,
     while complex image processing algorithms may be rather coded using <tt>CImg<float></tt> or <tt>CImg<double></tt>
     images that have floating-point pixel values. The default value for the template T is \c float.
     Using your own template types may be possible. However, you will certainly have to define the complete set
     of arithmetic and logical operators for your class.

     \par Image structure

     The \c CImg<T> structure contains \e six fields:
     - \c _width defines the number of \a columns of the image (size along the X-axis).
     - \c _height defines the number of \a rows of the image (size along the Y-axis).
     - \c _depth defines the number of \a slices of the image (size along the Z-axis).
     - \c _spectrum defines the number of \a channels of the image (size along the C-axis).
     - \c _data defines a \a pointer to the \a pixel \a data (of type \c T).
     - \c _is_shared is a boolean that tells if the memory buffer \c data is shared with
       another image.

     You can access these fields publicly although it is recommended to use the dedicated functions
     width(), height(), depth(), spectrum() and ptr() to do so.
     Image dimensions are not limited to a specific range (as long as you got enough available memory).
     A value of \e 1 usually means that the corresponding dimension is \a flat.
     If one of the dimensions is \e 0, or if the data pointer is null, the image is considered as \e empty.
     Empty images should not contain any pixel data and thus, will not be processed by CImg member functions
     (a CImgInstanceException will be thrown instead).
     Pixel data are stored in memory, in a non interlaced mode (See \ref cimg_storage).

     \par Image declaration and construction

     Declaring an image can be done by using one of the several available constructors.
     Here is a list of the most used:

     - Construct images from arbitrary dimensions:
         - <tt>CImg<char> img;</tt> declares an empty image.
         - <tt>CImg<unsigned char> img(128,128);</tt> declares a 128x128 greyscale image with
         \c unsigned \c char pixel values.
         - <tt>CImg<double> img(3,3);</tt> declares a 3x3 matrix with \c double coefficients.
         - <tt>CImg<unsigned char> img(256,256,1,3);</tt> declares a 256x256x1x3 (color) image
         (colors are stored as an image with three channels).
         - <tt>CImg<double> img(128,128,128);</tt> declares a 128x128x128 volumetric and greyscale image
         (with \c double pixel values).
         - <tt>CImg<> img(128,128,128,3);</tt> declares a 128x128x128 volumetric color image
         (with \c float pixels, which is the default value of the template parameter \c T).
         - \b Note: images pixels are <b>not automatically initialized to 0</b>. You may use the function \c fill() to
         do it, or use the specific constructor taking 5 parameters like this:
         <tt>CImg<> img(128,128,128,3,0);</tt> declares a 128x128x128 volumetric color image with all pixel values to 0.

     - Construct images from filenames:
         - <tt>CImg<unsigned char> img("image.jpg");</tt> reads a JPEG color image from the file "image.jpg".
         - <tt>CImg<float> img("analyze.hdr");</tt> reads a volumetric image (ANALYZE7.5 format) from the
         file "analyze.hdr".
         - \b Note: You need to install <a href="http://www.imagemagick.org">ImageMagick</a>
         to be able to read common compressed image formats (JPG,PNG, ...) (See \ref cimg_files_io).

     - Construct images from C-style arrays:
         - <tt>CImg<int> img(data_buffer,256,256);</tt> constructs a 256x256 greyscale image from a \c int* buffer
         \c data_buffer (of size 256x256=65536).
         - <tt>CImg<unsigned char> img(data_buffer,256,256,1,3);</tt> constructs a 256x256 color image
         from a \c unsigned \c char* buffer \c data_buffer (where R,G,B channels follow each others).

         The complete list of constructors can be found <a href="#constructors">here</a>.

     \par Most useful functions

     The \c CImg<T> class contains a lot of functions that operates on images.
     Some of the most useful are:

     - operator()(): Read or write pixel values.
     - display(): displays the image in a new window.
  **/
  template<typename T>
  struct CImg {

    unsigned int _width, _height, _depth, _spectrum;
    bool _is_shared;
    T *_data;

    //! Simple iterator type, to loop through each pixel value of an image instance.
    /**
       \note
       - The \c CImg<T>::iterator type is defined to be a <tt>T*</tt>.
       - You will seldom have to use iterators in %CImg, most classical operations
         being achieved (often in a faster way) using methods of \c CImg<T>.
       \par Example
       \code
       CImg<float> img("reference.jpg");                                         // Load image from file.
       for (CImg<float>::iterator it = img.begin(), it<img.end(); ++it) *it = 0; // Set all pixels to '0', with a CImg iterator.
       img.fill(0);                                                              // Do the same with a built-in method.
       \endcode
   **/
    typedef T* iterator;

    //! Simple const iterator type, to loop through each pixel value of a \c const image instance.
    /**
       \note
       - The \c CImg<T>::const_iterator type is defined to be a \c const \c T*.
       - You will seldom have to use iterators in %CImg, most classical operations
         being achieved (often in a faster way) using methods of \c CImg<T>.
       \par Example
       \code
       const CImg<float> img("reference.jpg");                                    // Load image from file.
       float sum = 0;
       for (CImg<float>::iterator it = img.begin(), it<img.end(); ++it) sum+=*it; // Compute sum of all pixel values, with a CImg iterator.
       const float sum2 = img.sum();                                              // Do the same with a built-in method.
       \endcode
    **/
    typedef const T* const_iterator;

    //! Pixel value type.
    /**
       Refer to the type of the pixel values of an image instance.
       \note
       - The \c CImg<T>::value_type type of a \c CImg<T> is defined to be a \c T.
       - \c CImg<T>::value_type is actually not used in %CImg methods. It has been mainly defined for
         compatibility with STL naming conventions.
    **/
    typedef T value_type;

    // Define common types related to template type T.
    typedef typename cimg::superset<T,bool>::type Tbool;
    typedef typename cimg::superset<T,unsigned char>::type Tuchar;
    typedef typename cimg::superset<T,char>::type Tchar;
    typedef typename cimg::superset<T,unsigned short>::type Tushort;
    typedef typename cimg::superset<T,short>::type Tshort;
    typedef typename cimg::superset<T,unsigned int>::type Tuint;
    typedef typename cimg::superset<T,int>::type Tint;
    typedef typename cimg::superset<T,cimg_ulong>::type Tulong;
    typedef typename cimg::superset<T,cimg_long>::type Tlong;
    typedef typename cimg::superset<T,float>::type Tfloat;
    typedef typename cimg::superset<T,double>::type Tdouble;
    typedef typename cimg::last<T,bool>::type boolT;
    typedef typename cimg::last<T,unsigned char>::type ucharT;
    typedef typename cimg::last<T,char>::type charT;
    typedef typename cimg::last<T,unsigned short>::type ushortT;
    typedef typename cimg::last<T,short>::type shortT;
    typedef typename cimg::last<T,unsigned int>::type uintT;
    typedef typename cimg::last<T,int>::type intT;
    typedef typename cimg::last<T,cimg_ulong>::type ulongT;
    typedef typename cimg::last<T,cimg_long>::type longT;
    typedef typename cimg::last<T,cimg_uint64>::type uint64T;
    typedef typename cimg::last<T,cimg_int64>::type int64T;
    typedef typename cimg::last<T,float>::type floatT;
    typedef typename cimg::last<T,double>::type doubleT;

    //@}
    //---------------------------
    //
    //! \name Plugins
    //@{
    //---------------------------
#ifdef cimg_plugin
#include cimg_plugin
#endif
#ifdef cimg_plugin1
#include cimg_plugin1
#endif
#ifdef cimg_plugin2
#include cimg_plugin2
#endif
#ifdef cimg_plugin3
#include cimg_plugin3
#endif
#ifdef cimg_plugin4
#include cimg_plugin4
#endif
#ifdef cimg_plugin5
#include cimg_plugin5
#endif
#ifdef cimg_plugin6
#include cimg_plugin6
#endif
#ifdef cimg_plugin7
#include cimg_plugin7
#endif
#ifdef cimg_plugin8
#include cimg_plugin8
#endif

    //@}
    //---------------------------------------------------------
    //
    //! \name Constructors / Destructor / Instance Management
    //@{
    //---------------------------------------------------------

    //! Destroy image.
    /**
       \note
       - The pixel buffer data() is deallocated if necessary, e.g. for non-empty and non-shared image instances.
       - Destroying an empty or shared image does nothing actually.
       \warning
       - When destroying a non-shared image, make sure that you will \e not operate on a remaining shared image
         that shares its buffer with the destroyed instance, in order to avoid further invalid memory access
         (to a deallocated buffer).
    **/
    ~CImg() {
      if (!_is_shared) delete[] _data;
    }

    //! Construct empty image.
    /**
       \note
       - An empty image has no pixel data and all of its dimensions width(), height(), depth(), spectrum()
         are set to \c 0, as well as its pixel buffer pointer data().
       - An empty image may be re-assigned afterwards, e.g. with the family of
         assign(unsigned int,unsigned int,unsigned int,unsigned int) methods,
         or by operator=(const CImg<t>&). In all cases, the type of pixels stays \c T.
       - An empty image is never shared.
       \par Example
       \code
       CImg<float> img1, img2;      // Construct two empty images.
       img1.assign(256,256,1,3);    // Re-assign 'img1' to be a 256x256x1x3 (color) image.
       img2 = img1.get_rand(0,255); // Re-assign 'img2' to be a random-valued version of 'img1'.
       img2.assign();               // Re-assign 'img2' to be an empty image again.
       \endcode
    **/
    CImg():_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {}

    //! Construct image with specified size.
    /**
       \param size_x Image width().
       \param size_y Image height().
       \param size_z Image depth().
       \param size_c Image spectrum() (number of channels).
       \note
       - It is able to create only \e non-shared images, and allocates thus a pixel buffer data()
         for each constructed image instance.
       - Setting one dimension \c size_x,\c size_y,\c size_z or \c size_c to \c 0 leads to the construction of
         an \e empty image.
       - A \c CImgInstanceException is thrown when the pixel buffer cannot be allocated
         (e.g. when requested size is too big for available memory).
       \warning
       - The allocated pixel buffer is \e not filled with a default value, and is likely to contain garbage values.
         In order to initialize pixel values during construction (e.g. with \c 0), use constructor
         CImg(unsigned int,unsigned int,unsigned int,unsigned int,T) instead.
       \par Example
       \code
       CImg<float> img1(256,256,1,3);   // Construct a 256x256x1x3 (color) image, filled with garbage values.
       CImg<float> img2(256,256,1,3,0); // Construct a 256x256x1x3 (color) image, filled with value '0'.
       \endcode
    **/
    explicit CImg(const unsigned int size_x, const unsigned int size_y=1,
                  const unsigned int size_z=1, const unsigned int size_c=1):
      _is_shared(false) {
      size_t siz = (size_t)size_x*size_y*size_z*size_c;
      if (siz) {
        _width = size_x; _height = size_y; _depth = size_z; _spectrum = size_c;
        try { _data = new T[siz]; } catch (...) {
          _width = _height = _depth = _spectrum = 0; _data = 0;
          throw CImgInstanceException(_cimg_instance
                                      "CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
                                      cimg_instance,
                                      cimg::strbuffersize(sizeof(T)*size_x*size_y*size_z*size_c),
                                      size_x,size_y,size_z,size_c);
        }
      } else { _width = _height = _depth = _spectrum = 0; _data = 0; }
    }

    //! Construct image with specified size and initialize pixel values.
    /**
       \param size_x Image width().
       \param size_y Image height().
       \param size_z Image depth().
       \param size_c Image spectrum() (number of channels).
       \param value Initialization value.
       \note
       - Similar to CImg(unsigned int,unsigned int,unsigned int,unsigned int),
         but it also fills the pixel buffer with the specified \c value.
       \warning
       - It cannot be used to construct a vector-valued image and initialize it with \e vector-valued pixels
         (e.g. RGB vector, for color images).
         For this task, you may use fillC() after construction.
    **/
    CImg(const unsigned int size_x, const unsigned int size_y,
         const unsigned int size_z, const unsigned int size_c, const T& value):
      _is_shared(false) {
      const size_t siz = (size_t)size_x*size_y*size_z*size_c;
      if (siz) {
        _width = size_x; _height = size_y; _depth = size_z; _spectrum = size_c;
        try { _data = new T[siz]; } catch (...) {
          _width = _height = _depth = _spectrum = 0; _data = 0;
          throw CImgInstanceException(_cimg_instance
                                      "CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
                                      cimg_instance,
                                      cimg::strbuffersize(sizeof(T)*size_x*size_y*size_z*size_c),
                                      size_x,size_y,size_z,size_c);
        }
        fill(value);
      } else { _width = _height = _depth = _spectrum = 0; _data = 0; }
    }

    //! Construct image with specified size and initialize pixel values from a sequence of integers.
    /**
       Construct a new image instance of size \c size_x x \c size_y x \c size_z x \c size_c,
       with pixels of type \c T, and initialize pixel
       values from the specified sequence of integers \c value0,\c value1,\c ...
       \param size_x Image width().
       \param size_y Image height().
       \param size_z Image depth().
       \param size_c Image spectrum() (number of channels).
       \param value0 First value of the initialization sequence (must be an \e integer).
       \param value1 Second value of the initialization sequence (must be an \e integer).
       \param ...
       \note
       - Similar to CImg(unsigned int,unsigned int,unsigned int,unsigned int), but it also fills
         the pixel buffer with a sequence of specified integer values.
       \warning
       - You must specify \e exactly \c size_x*\c size_y*\c size_z*\c size_c integers in the initialization sequence.
         Otherwise, the constructor may crash or fill your image pixels with garbage.
       \par Example
       \code
       const CImg<float> img(2,2,1,3,      // Construct a 2x2 color (RGB) image.
                             0,255,0,255,  // Set the 4 values for the red component.
                             0,0,255,255,  // Set the 4 values for the green component.
                             64,64,64,64); // Set the 4 values for the blue component.
       img.resize(150,150).display();
       \endcode
       \image html ref_constructor1.jpg
     **/
    CImg(const unsigned int size_x, const unsigned int size_y, const unsigned int size_z, const unsigned int size_c,
         const int value0, const int value1, ...):
      _width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
#define _CImg_stdarg(img,a0,a1,N,t) { \
        size_t _siz = (size_t)N; \
        if (_siz--) { \
          va_list ap; \
          va_start(ap,a1); \
          T *ptrd = (img)._data; \
          *(ptrd++) = (T)a0; \
          if (_siz--) { \
            *(ptrd++) = (T)a1; \
            for ( ; _siz; --_siz) *(ptrd++) = (T)va_arg(ap,t); \
          } \
          va_end(ap); \
        } \
      }
      assign(size_x,size_y,size_z,size_c);
      _CImg_stdarg(*this,value0,value1,(size_t)size_x*size_y*size_z*size_c,int);
    }

#if defined(cimg_use_cpp11) && cimg_use_cpp11!=0
    //! Construct image with specified size and initialize pixel values from an initializer list of integers.
    /**
       Construct a new image instance of size \c size_x x \c size_y x \c size_z x \c size_c,
       with pixels of type \c T, and initialize pixel
       values from the specified initializer list of integers { \c value0,\c value1,\c ... }
       \param size_x Image width().
       \param size_y Image height().
       \param size_z Image depth().
       \param size_c Image spectrum() (number of channels).
       \param { value0, value1, ... } Initialization list
       \param repeat_values Tells if the value filling process is repeated over the image.

       \note
       - Similar to CImg(unsigned int,unsigned int,unsigned int,unsigned int), but it also fills
         the pixel buffer with a sequence of specified integer values.
       \par Example
       \code
       const CImg<float> img(2,2,1,3,      // Construct a 2x2 color (RGB) image.
                             { 0,255,0,255,    // Set the 4 values for the red component.
                               0,0,255,255,    // Set the 4 values for the green component.
                               64,64,64,64 }); // Set the 4 values for the blue component.
       img.resize(150,150).display();
       \endcode
       \image html ref_constructor1.jpg
    **/
    template<typename t>
    CImg(const unsigned int size_x, const unsigned int size_y, const unsigned int size_z, const unsigned int size_c,
         const std::initializer_list<t> values,
         const bool repeat_values=true):
      _width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
#define _cimg_constructor_cpp11(repeat_values) \
  auto it = values.begin(); \
  size_t siz = size(); \
  if (repeat_values) for (T *ptrd = _data; siz--; ) { \
    *(ptrd++) = (T)(*(it++)); if (it==values.end()) it = values.begin(); } \
  else { siz = cimg::min(siz,values.size()); for (T *ptrd = _data; siz--; ) *(ptrd++) = (T)(*(it++)); }
      assign(size_x,size_y,size_z,size_c);
      _cimg_constructor_cpp11(repeat_values);
    }

    template<typename t>
    CImg(const unsigned int size_x, const unsigned int size_y, const unsigned int size_z,
         std::initializer_list<t> values,
         const bool repeat_values=true):
      _width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
      assign(size_x,size_y,size_z);
      _cimg_constructor_cpp11(repeat_values);
    }

    template<typename t>
    CImg(const unsigned int size_x, const unsigned int size_y,
         std::initializer_list<t> values,
         const bool repeat_values=true):
      _width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
      assign(size_x,size_y);
      _cimg_constructor_cpp11(repeat_values);
    }

    template<typename t>
    CImg(const unsigned int size_x,
         std::initializer_list<t> values,
         const bool repeat_values=true):_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
      assign(size_x);
      _cimg_constructor_cpp11(repeat_values);
    }

    //! Construct single channel 1D image with pixel values and width obtained from an initializer list of integers.
    /**
       Construct a new image instance of size \c width x \c 1 x \c 1 x \c 1,
       with pixels of type \c T, and initialize pixel
       values from the specified initializer list of integers { \c value0,\c value1,\c ... }. Image width is
       given by the size of the initializer list.
       \param { value0, value1, ... } Initialization list
       \note
       - Similar to CImg(unsigned int,unsigned int,unsigned int,unsigned int) with height=1, depth=1, and spectrum=1,
         but it also fills the pixel buffer with a sequence of specified integer values.
       \par Example
       \code
       const CImg<float> img = {10,20,30,20,10 }; // Construct a 5x1 image with one channel, and set its pixel values.
       img.resize(150,150).display();
       \endcode
       \image html ref_constructor1.jpg
     **/
    template<typename t>
    CImg(const std::initializer_list<t> values):
      _width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
      assign(values.size(),1,1,1);
      auto it = values.begin();
      unsigned int siz = _width;
      for (T *ptrd = _data; siz--; ) *(ptrd++) = (T)(*(it++));
    }

    template<typename t>
    CImg<T> & operator=(std::initializer_list<t> values) {
      _cimg_constructor_cpp11(siz>values.size());
      return *this;
    }
#endif

    //! Construct image with specified size and initialize pixel values from a sequence of doubles.
    /**
       Construct a new image instance of size \c size_x x \c size_y x \c size_z x \c size_c, with pixels of type \c T,
       and initialize pixel values from the specified sequence of doubles \c value0,\c value1,\c ...
       \param size_x Image width().
       \param size_y Image height().
       \param size_z Image depth().
       \param size_c Image spectrum() (number of channels).
       \param value0 First value of the initialization sequence (must be a \e double).
       \param value1 Second value of the initialization sequence (must be a \e double).
       \param ...
       \note
       - Similar to CImg(unsigned int,unsigned int,unsigned int,unsigned int,int,int,...), but
         takes a sequence of double values instead of integers.
       \warning
       - You must specify \e exactly \c dx*\c dy*\c dz*\c dc doubles in the initialization sequence.
         Otherwise, the constructor may crash or fill your image with garbage.
         For instance, the code below will probably crash on most platforms:
         \code
         const CImg<float> img(2,2,1,1, 0.5,0.5,255,255); // FAIL: The two last arguments are 'int', not 'double'!
         \endcode
     **/
    CImg(const unsigned int size_x, const unsigned int size_y, const unsigned int size_z, const unsigned int size_c,
         const double value0, const double value1, ...):
      _width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
      assign(size_x,size_y,size_z,size_c);
      _CImg_stdarg(*this,value0,value1,(size_t)size_x*size_y*size_z*size_c,double);
    }

    //! Construct image with specified size and initialize pixel values from a value string.
    /**
       Construct a new image instance of size \c size_x x \c size_y x \c size_z x \c size_c, with pixels of type \c T,
       and initializes pixel values from the specified string \c values.
       \param size_x Image width().
       \param size_y Image height().
       \param size_z Image depth().
       \param size_c Image spectrum() (number of channels).
       \param values Value string describing the way pixel values are set.
       \param repeat_values Tells if the value filling process is repeated over the image.
       \note
       - Similar to CImg(unsigned int,unsigned int,unsigned int,unsigned int), but it also fills
         the pixel buffer with values described in the value string \c values.
       - Value string \c values may describe two different filling processes:
         - Either \c values is a sequences of values assigned to the image pixels, as in <tt>"1,2,3,7,8,2"</tt>.
           In this case, set \c repeat_values to \c true to periodically fill the image with the value sequence.
         - Either, \c values is a formula, as in <tt>"cos(x/10)*sin(y/20)"</tt>.
           In this case, parameter \c repeat_values is pointless.
       - For both cases, specifying \c repeat_values is mandatory.
         It disambiguates the possible overloading of constructor
         CImg(unsigned int,unsigned int,unsigned int,unsigned int,T) with \c T being a <tt>const char*</tt>.
       - A \c CImgArgumentException is thrown when an invalid value string \c values is specified.
       \par Example
       \code
       const CImg<float> img1(129,129,1,3,"0,64,128,192,255",true),                   // Construct image filled from a value sequence.
                         img2(129,129,1,3,"if(c==0,255*abs(cos(x/10)),1.8*y)",false); // Construct image filled from a formula.
       (img1,img2).display();
       \endcode
       \image html ref_constructor2.jpg
     **/
    CImg(const unsigned int size_x, const unsigned int size_y, const unsigned int size_z, const unsigned int size_c,
         const char *const values, const bool repeat_values):_is_shared(false) {
      const size_t siz = (size_t)size_x*size_y*size_z*size_c;
      if (siz) {
        _width = size_x; _height = size_y; _depth = size_z; _spectrum = size_c;
        try { _data = new T[siz]; } catch (...) {
          _width = _height = _depth = _spectrum = 0; _data = 0;
          throw CImgInstanceException(_cimg_instance
                                      "CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
                                      cimg_instance,
                                      cimg::strbuffersize(sizeof(T)*size_x*size_y*size_z*size_c),
                                      size_x,size_y,size_z,size_c);
        }
        fill(values,repeat_values);
      } else { _width = _height = _depth = _spectrum = 0; _data = 0; }
    }

    //! Construct image with specified size and initialize pixel values from a memory buffer.
    /**
       Construct a new image instance of size \c size_x x \c size_y x \c size_z x \c size_c, with pixels of type \c T,
       and initializes pixel values from the specified \c t* memory buffer.
       \param values Pointer to the input memory buffer.
       \param size_x Image width().
       \param size_y Image height().
       \param size_z Image depth().
       \param size_c Image spectrum() (number of channels).
       \param is_shared Tells if input memory buffer must be shared by the current instance.
       \note
       - If \c is_shared is \c false, the image instance allocates its own pixel buffer,
         and values from the specified input buffer are copied to the instance buffer.
         If buffer types \c T and \c t are different, a regular static cast is performed during buffer copy.
       - Otherwise, the image instance does \e not allocate a new buffer, and uses the input memory buffer as its
         own pixel buffer. This case requires that types \c T and \c t are the same. Later, destroying such a shared
         image will not deallocate the pixel buffer, this task being obviously charged to the initial buffer allocator.
       - A \c CImgInstanceException is thrown when the pixel buffer cannot be allocated
         (e.g. when requested size is too big for available memory).
       \warning
       - You must take care when operating on a shared image, since it may have an invalid pixel buffer pointer data()
         (e.g. already deallocated).
       \par Example
       \code
       unsigned char tab[256*256] = { 0 };
       CImg<unsigned char> img1(tab,256,256,1,1,false), // Construct new non-shared image from buffer 'tab'.
                           img2(tab,256,256,1,1,true);  // Construct new shared-image from buffer 'tab'.
       tab[1024] = 255;                                 // Here, 'img2' is indirectly modified, but not 'img1'.
       \endcode
    **/
    template<typename t>
    CImg(const t *const values, const unsigned int size_x, const unsigned int size_y=1,
         const unsigned int size_z=1, const unsigned int size_c=1, const bool is_shared=false):_is_shared(false) {
      if (is_shared) {
        _width = _height = _depth = _spectrum = 0; _data = 0;
        throw CImgArgumentException(_cimg_instance
                                    "CImg(): Invalid construction request of a (%u,%u,%u,%u) shared instance "
                                    "from a (%s*) buffer (pixel types are different).",
                                    cimg_instance,
                                    size_x,size_y,size_z,size_c,CImg<t>::pixel_type());
      }
      const size_t siz = (size_t)size_x*size_y*size_z*size_c;
      if (values && siz) {
        _width = size_x; _height = size_y; _depth = size_z; _spectrum = size_c;
        try { _data = new T[siz]; } catch (...) {
          _width = _height = _depth = _spectrum = 0; _data = 0;
          throw CImgInstanceException(_cimg_instance
                                      "CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
                                      cimg_instance,
                                      cimg::strbuffersize(sizeof(T)*size_x*size_y*size_z*size_c),
                                      size_x,size_y,size_z,size_c);

        }
        const t *ptrs = values; cimg_for(*this,ptrd,T) *ptrd = (T)*(ptrs++);
      } else { _width = _height = _depth = _spectrum = 0; _data = 0; }
    }

    //! Construct image with specified size and initialize pixel values from a memory buffer \specialization.
    CImg(const T *const values, const unsigned int size_x, const unsigned int size_y=1,
         const unsigned int size_z=1, const unsigned int size_c=1, const bool is_shared=false) {
      const size_t siz = (size_t)size_x*size_y*size_z*size_c;
      if (values && siz) {
        _width = size_x; _height = size_y; _depth = size_z; _spectrum = size_c; _is_shared = is_shared;
        if (_is_shared) _data = const_cast<T*>(values);
        else {
          try { _data = new T[siz]; } catch (...) {
            _width = _height = _depth = _spectrum = 0; _data = 0;
            throw CImgInstanceException(_cimg_instance
                                        "CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
                                        cimg_instance,
                                        cimg::strbuffersize(sizeof(T)*size_x*size_y*size_z*size_c),
                                        size_x,size_y,size_z,size_c);
          }
          std::memcpy(_data,values,siz*sizeof(T));
        }
      } else { _width = _height = _depth = _spectrum = 0; _is_shared = false; _data = 0; }
    }

    //! Construct image from reading an image file.
    /**
       Construct a new image instance with pixels of type \c T, and initialize pixel values with the data read from
       an image file.
       \param filename Filename, as a C-string.
       \note
       - Similar to CImg(unsigned int,unsigned int,unsigned int,unsigned int), but it reads the image
         dimensions and pixel values from the specified image file.
       - The recognition of the image file format by %CImg higly depends on the tools installed on your system
         and on the external libraries you used to link your code against.
       - Considered pixel type \c T should better fit the file format specification, or data loss may occur during
         file load (e.g. constructing a \c CImg<unsigned char> from a float-valued image file).
       - A \c CImgIOException is thrown when the specified \c filename cannot be read, or if the file format is not
         recognized.
       \par Example
       \code
       const CImg<float> img("reference.jpg");
       img.display();
       \endcode
       \image html ref_image.jpg
    **/
    explicit CImg(const char *const filename):_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
      assign(filename);
    }

    //! Construct image copy.
    /**
       Construct a new image instance with pixels of type \c T, as a copy of an existing \c CImg<t> instance.
       \param img Input image to copy.
       \note
       - Constructed copy has the same size width() x height() x depth() x spectrum() and pixel values as the
         input image \c img.
       - If input image \c img is \e shared and if types \c T and \c t are the same, the constructed copy is also
         \e shared, and shares its pixel buffer with \c img.
         Modifying a pixel value in the constructed copy will thus also modifies it in the input image \c img.
         This behavior is needful to allow functions to return shared images.
       - Otherwise, the constructed copy allocates its own pixel buffer, and copies pixel values from the input
         image \c img into its buffer. The copied pixel values may be eventually statically casted if types \c T and
         \c t are different.
       - Constructing a copy from an image \c img when types \c t and \c T are the same is significantly faster than
         with different types.
       - A \c CImgInstanceException is thrown when the pixel buffer cannot be allocated
         (e.g. not enough available memory).
    **/
    template<typename t>
    CImg(const CImg<t>& img):_is_shared(false) {
      const size_t siz = (size_t)img.size();
      if (img._data && siz) {
        _width = img._width; _height = img._height; _depth = img._depth; _spectrum = img._spectrum;
        try { _data = new T[siz]; } catch (...) {
          _width = _height = _depth = _spectrum = 0; _data = 0;
          throw CImgInstanceException(_cimg_instance
                                      "CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
                                      cimg_instance,
                                      cimg::strbuffersize(sizeof(T)*img._width*img._height*img._depth*img._spectrum),
                                      img._width,img._height,img._depth,img._spectrum);
        }
        const t *ptrs = img._data; cimg_for(*this,ptrd,T) *ptrd = (T)*(ptrs++);
      } else { _width = _height = _depth = _spectrum = 0; _data = 0; }
    }

    //! Construct image copy \specialization.
    CImg(const CImg<T>& img) {
      const size_t siz = (size_t)img.size();
      if (img._data && siz) {
        _width = img._width; _height = img._height; _depth = img._depth; _spectrum = img._spectrum;
        _is_shared = img._is_shared;
        if (_is_shared) _data = const_cast<T*>(img._data);
        else {
          try { _data = new T[siz]; } catch (...) {
            _width = _height = _depth = _spectrum = 0; _data = 0;
            throw CImgInstanceException(_cimg_instance
                                        "CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
                                        cimg_instance,
                                        cimg::strbuffersize(sizeof(T)*img._width*img._height*img._depth*img._spectrum),
                                        img._width,img._height,img._depth,img._spectrum);

          }
          std::memcpy(_data,img._data,siz*sizeof(T));
        }
      } else { _width = _height = _depth = _spectrum = 0; _is_shared = false; _data = 0; }
    }

    //! Advanced copy constructor.
    /**
       Construct a new image instance with pixels of type \c T, as a copy of an existing \c CImg<t> instance,
       while forcing the shared state of the constructed copy.
       \param img Input image to copy.
       \param is_shared Tells about the shared state of the constructed copy.
       \note
       - Similar to CImg(const CImg<t>&), except that it allows to decide the shared state of
         the constructed image, which does not depend anymore on the shared state of the input image \c img:
         - If \c is_shared is \c true, the constructed copy will share its pixel buffer with the input image \c img.
           For that case, the pixel types \c T and \c t \e must be the same.
         - If \c is_shared is \c false, the constructed copy will allocate its own pixel buffer, whether the input
           image \c img is shared or not.
       - A \c CImgArgumentException is thrown when a shared copy is requested with different pixel types \c T and \c t.
    **/
    template<typename t>
    CImg(const CImg<t>& img, const bool is_shared):_is_shared(false) {
      if (is_shared) {
        _width = _height = _depth = _spectrum = 0; _data = 0;
        throw CImgArgumentException(_cimg_instance
                                    "CImg(): Invalid construction request of a shared instance from a "
                                    "CImg<%s> image (%u,%u,%u,%u,%p) (pixel types are different).",
                                    cimg_instance,
                                    CImg<t>::pixel_type(),img._width,img._height,img._depth,img._spectrum,img._data);
      }
      const size_t siz = (size_t)img.size();
      if (img._data && siz) {
        _width = img._width; _height = img._height; _depth = img._depth; _spectrum = img._spectrum;
        try { _data = new T[siz]; } catch (...) {
          _width = _height = _depth = _spectrum = 0; _data = 0;
          throw CImgInstanceException(_cimg_instance
                                      "CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
                                      cimg_instance,
                                      cimg::strbuffersize(sizeof(T)*img._width*img._height*img._depth*img._spectrum),
                                      img._width,img._height,img._depth,img._spectrum);
        }
        const t *ptrs = img._data; cimg_for(*this,ptrd,T) *ptrd = (T)*(ptrs++);
      } else { _width = _height = _depth = _spectrum = 0; _data = 0; }
    }

    //! Advanced copy constructor \specialization.
    CImg(const CImg<T>& img, const bool is_shared) {
      const size_t siz = (size_t)img.size();
      if (img._data && siz) {
        _width = img._width; _height = img._height; _depth = img._depth; _spectrum = img._spectrum;
        _is_shared = is_shared;
        if (_is_shared) _data = const_cast<T*>(img._data);
        else {
          try { _data = new T[siz]; } catch (...) {
            _width = _height = _depth = _spectrum = 0; _data = 0;
            throw CImgInstanceException(_cimg_instance
                                        "CImg(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
                                        cimg_instance,
                                        cimg::strbuffersize(sizeof(T)*img._width*img._height*img._depth*img._spectrum),
                                        img._width,img._height,img._depth,img._spectrum);
          }
          std::memcpy(_data,img._data,siz*sizeof(T));
        }
      } else { _width = _height = _depth = _spectrum = 0; _is_shared = false; _data = 0; }
    }

    //! Construct image with dimensions borrowed from another image.
    /**
       Construct a new image instance with pixels of type \c T, and size get from some dimensions of an existing
       \c CImg<t> instance.
       \param img Input image from which dimensions are borrowed.
       \param dimensions C-string describing the image size along the X,Y,Z and C-dimensions.
       \note
       - Similar to CImg(unsigned int,unsigned int,unsigned int,unsigned int), but it takes the image dimensions
         (\e not its pixel values) from an existing \c CImg<t> instance.
       - The allocated pixel buffer is \e not filled with a default value, and is likely to contain garbage values.
         In order to initialize pixel values (e.g. with \c 0), use constructor CImg(const CImg<t>&,const char*,T)
         instead.
       \par Example
       \code
       const CImg<float> img1(256,128,1,3),      // 'img1' is a 256x128x1x3 image.
                         img2(img1,"xyzc"),      // 'img2' is a 256x128x1x3 image.
                         img3(img1,"y,x,z,c"),   // 'img3' is a 128x256x1x3 image.
                         img4(img1,"c,x,y,3",0), // 'img4' is a 3x128x256x3 image (with pixels initialized to '0').
       \endcode
     **/
    template<typename t>
    CImg(const CImg<t>& img, const char *const dimensions):
      _width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
      assign(img,dimensions);
    }

    //! Construct image with dimensions borrowed from another image and initialize pixel values.
    /**
       Construct a new image instance with pixels of type \c T, and size get from the dimensions of an existing
       \c CImg<t> instance, and set all pixel values to specified \c value.
       \param img Input image from which dimensions are borrowed.
       \param dimensions String describing the image size along the X,Y,Z and V-dimensions.
       \param value Value used for initialization.
       \note
       - Similar to CImg(const CImg<t>&,const char*), but it also fills the pixel buffer with the specified \c value.
     **/
    template<typename t>
    CImg(const CImg<t>& img, const char *const dimensions, const T& value):
      _width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
      assign(img,dimensions).fill(value);
    }

    //! Construct image from a display window.
    /**
       Construct a new image instance with pixels of type \c T, as a snapshot of an existing \c CImgDisplay instance.
       \param disp Input display window.
       \note
       - The width() and height() of the constructed image instance are the same as the specified \c CImgDisplay.
       - The depth() and spectrum() of the constructed image instance are respectively set to \c 1 and \c 3
         (i.e. a 2d color image).
       - The image pixels are read as 8-bits RGB values.
     **/
    explicit CImg(const CImgDisplay &disp):_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
      disp.snapshot(*this);
    }

    // Constructor and assignment operator for rvalue references (c++11).
    // This avoids an additional image copy for methods returning new images. Can save RAM for big images !
#if defined(cimg_use_cpp11) && cimg_use_cpp11!=0
    CImg(CImg<T>&& img):_width(0),_height(0),_depth(0),_spectrum(0),_is_shared(false),_data(0) {
      swap(img);
    }
    CImg<T>& operator=(CImg<T>&& img) {
      if (_is_shared) return assign(img);
      return img.swap(*this);
    }
#endif

    //! Construct empty image \inplace.
    /**
       In-place version of the default constructor CImg(). It simply resets the instance to an empty image.
    **/
    CImg<T>& assign() {
      if (!_is_shared) delete[] _data;
      _width = _height = _depth = _spectrum = 0; _is_shared = false; _data = 0;
      return *this;
    }

    //! Construct image with specified size \inplace.
    /**
       In-place version of the constructor CImg(unsigned int,unsigned int,unsigned int,unsigned int).
    **/
    CImg<T>& assign(const unsigned int size_x, const unsigned int size_y=1,
                    const unsigned int size_z=1, const unsigned int size_c=1) {
      const size_t siz = (size_t)size_x*size_y*size_z*size_c;
      if (!siz) return assign();
      const size_t curr_siz = (size_t)size();
      if (siz!=curr_siz) {
        if (_is_shared)
          throw CImgArgumentException(_cimg_instance
                                      "assign(): Invalid assignement request of shared instance from specified "
                                      "image (%u,%u,%u,%u).",
                                      cimg_instance,
                                      size_x,size_y,size_z,size_c);
        else {
          delete[] _data;
          try { _data = new T[siz]; } catch (...) {
            _width = _height = _depth = _spectrum = 0; _data = 0;
            throw CImgInstanceException(_cimg_instance
                                        "assign(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
                                        cimg_instance,
                                        cimg::strbuffersize(sizeof(T)*size_x*size_y*size_z*size_c),
                                        size_x,size_y,size_z,size_c);
          }
        }
      }
      _width = size_x; _height = size_y; _depth = size_z; _spectrum = size_c;
      return *this;
    }

    //! Construct image with specified size and initialize pixel values \inplace.
    /**
       In-place version of the constructor CImg(unsigned int,unsigned int,unsigned int,unsigned int,T).
    **/
    CImg<T>& assign(const unsigned int size_x, const unsigned int size_y,
                    const unsigned int size_z, const unsigned int size_c, const T& value) {
      return assign(size_x,size_y,size_z,size_c).fill(value);
    }

    //! Construct image with specified size and initialize pixel values from a sequence of integers \inplace.
    /**
       In-place version of the constructor CImg(unsigned int,unsigned int,unsigned int,unsigned int,int,int,...).
    **/
    CImg<T>& assign(const unsigned int size_x, const unsigned int size_y,
                    const unsigned int size_z, const unsigned int size_c,
                    const int value0, const int value1, ...) {
      assign(size_x,size_y,size_z,size_c);
      _CImg_stdarg(*this,value0,value1,(size_t)size_x*size_y*size_z*size_c,int);
      return *this;
    }

    //! Construct image with specified size and initialize pixel values from a sequence of doubles \inplace.
    /**
       In-place version of the constructor CImg(unsigned int,unsigned int,unsigned int,unsigned int,double,double,...).
    **/
    CImg<T>& assign(const unsigned int size_x, const unsigned int size_y,
                    const unsigned int size_z, const unsigned int size_c,
                    const double value0, const double value1, ...) {
      assign(size_x,size_y,size_z,size_c);
      _CImg_stdarg(*this,value0,value1,(size_t)size_x*size_y*size_z*size_c,double);
      return *this;
    }

    //! Construct image with specified size and initialize pixel values from a value string \inplace.
    /**
       In-place version of the constructor CImg(unsigned int,unsigned int,unsigned int,unsigned int,const char*,bool).
    **/
    CImg<T>& assign(const unsigned int size_x, const unsigned int size_y,
                    const unsigned int size_z, const unsigned int size_c,
                    const char *const values, const bool repeat_values) {
      return assign(size_x,size_y,size_z,size_c).fill(values,repeat_values);
    }

    //! Construct image with specified size and initialize pixel values from a memory buffer \inplace.
    /**
       In-place version of the constructor CImg(const t*,unsigned int,unsigned int,unsigned int,unsigned int).
    **/
    template<typename t>
    CImg<T>& assign(const t *const values, const unsigned int size_x, const unsigned int size_y=1,
                    const unsigned int size_z=1, const unsigned int size_c=1) {
      const size_t siz = (size_t)size_x*size_y*size_z*size_c;
      if (!values || !siz) return assign();
      assign(size_x,size_y,size_z,size_c);
      const t *ptrs = values; cimg_for(*this,ptrd,T) *ptrd = (T)*(ptrs++);
      return *this;
    }

    //! Construct image with specified size and initialize pixel values from a memory buffer \specialization.
    CImg<T>& assign(const T *const values, const unsigned int size_x, const unsigned int size_y=1,
                    const unsigned int size_z=1, const unsigned int size_c=1) {
      const size_t siz = (size_t)size_x*size_y*size_z*size_c;
      if (!values || !siz) return assign();
      const size_t curr_siz = (size_t)size();
      if (values==_data && siz==curr_siz) return assign(size_x,size_y,size_z,size_c);
      if (_is_shared || values + siz<_data || values>=_data + size()) {
        assign(size_x,size_y,size_z,size_c);
        if (_is_shared) std::memmove(_data,values,siz*sizeof(T));
        else std::memcpy(_data,values,siz*sizeof(T));
      } else {
        T *new_data = 0;
        try { new_data = new T[siz]; } catch (...) {
          _width = _height = _depth = _spectrum = 0; _data = 0;
          throw CImgInstanceException(_cimg_instance
                                      "assign(): Failed to allocate memory (%s) for image (%u,%u,%u,%u).",
                                      cimg_instance,
                                      cimg::strbuffersize(sizeof(T)*size_x*size_y*size_z*size_c),
                                      size_x,size_y,size_z,size_c);
        }
        std::memcpy(new_data,values,siz*sizeof(T));
        delete[] _data; _data = new_data; _width = size_x; _height = size_y; _depth = size_z; _spectrum = size_c;
      }
      return *this;
    }

    //! Construct image with specified size and initialize pixel values from a memory buffer \overloading.
    template<typename t>
    CImg<T>& assign(const t *const values, const unsigned int size_x, const unsigned int size_y,
                    const unsigned int size_z, const unsigned int size_c, const bool is_shared) {
      if (is_shared)
        throw CImgArgumentException(_cimg_instance
                                    "assign(): Invalid assignment request of shared instance from (%s*) buffer"
                                    "(pixel types are different).",
                                    cimg_instance,
                                    CImg<t>::pixel_type());
      return assign(values,size_x,size_y,size_z,size_c);
    }

    //! Construct image with specified size and initialize pixel values from a memory buffer \overloading.
    CImg<T>& assign(const T *const values, const unsigned int size_x, const unsigned int size_y,
                    const unsigned int size_z, const unsigned int size_c, const bool is_shared) {
      const size_t siz = (size_t)size_x*size_y*size_z*size_c;
      if (!values || !siz) return assign();
      if (!is_shared) { if (_is_shared) assign(); assign(values,size_x,size_y,size_z,size_c); }
      else {
        if (!_is_shared) {
          if (values + siz<_data || values>=_data + size()) assign();
          else cimg::warn(_cimg_instance
                          "assign(): Shared image instance has overlapping memory.",
                          cimg_instance);
        }
        _width = size_x; _height = size_y; _depth = size_z; _spectrum = size_c; _is_shared = true;
        _data = const_cast<T*>(values);
      }
      return *this;
    }

    //! Construct image from reading an image file \inplace.
    /**
       In-place version of the constructor CImg(const char*).
    **/
    CImg<T>& assign(const char *const filename) {
      return load(filename);
    }

    //! Construct image copy \inplace.
    /**
       In-place version of the constructor CImg(const CImg<t>&).
    **/
    template<typename t>
    CImg<T>& assign(const CImg<t>& img) {
      return assign(img._data,img._width,img._height,img._depth,img._spectrum);
    }

    //! In-place version of the advanced copy constructor.
    /**
       In-place version of the constructor CImg(const CImg<t>&,bool).
     **/
    template<typename t>
    CImg<T>& assign(const CImg<t>& img, const bool is_shared) {
      return assign(img._data,img._width,img._height,img._depth,img._spectrum,is_shared);
    }

    //! Construct image with dimensions borrowed from another image \inplace.
    /**
       In-place version of the constructor CImg(const CImg<t>&,const char*).
    **/
    template<typename t>
    CImg<T>& assign(const CImg<t>& img, const char *const dimensions) {
      if (!dimensions || !*dimensions) return assign(img._width,img._height,img._depth,img._spectrum);
      unsigned int siz[4] = { 0,1,1,1 }, k = 0;
      CImg<charT> item(256);
      for (const char *s = dimensions; *s && k<4; ++k) {
        if (cimg_sscanf(s,"%255[^0-9%xyzvwhdcXYZVWHDC]",item._data)>0) s+=std::strlen(item);
        if (*s) {
          unsigned int val = 0; char sep = 0;
          if (cimg_sscanf(s,"%u%c",&val,&sep)>0) {
            if (sep=='%') siz[k] = val*(k==0?_width:k==1?_height:k==2?_depth:_spectrum)/100;
            else siz[k] = val;
            while (*s>='0' && *s<='9') ++s; if (sep=='%') ++s;
          } else switch (cimg::uncase(*s)) {
          case 'x' : case 'w' : siz[k] = img._width; ++s; break;
          case 'y' : case 'h' : siz[k] = img._height; ++s; break;
          case 'z' : case 'd' : siz[k] = img._depth; ++s; break;
          case 'c' : case 's' : siz[k] = img._spectrum; ++s; break;
          default :
            throw CImgArgumentException(_cimg_instance
                                        "assign(): Invalid character '%c' detected in specified dimension string '%s'.",
                                        cimg_instance,
                                        *s,dimensions);
          }
        }
      }
      return assign(siz[0],siz[1],siz[2],siz[3]);
    }

    //! Construct image with dimensions borrowed from another image and initialize pixel values \inplace.
    /**
       In-place version of the constructor CImg(const CImg<t>&,const char*,T).
    **/
    template<typename t>
    CImg<T>& assign(const CImg<t>& img, const char *const dimensions, const T& value) {
      return assign(img,dimensions).fill(value);
    }

    //! Construct image from a display window \inplace.
    /**
       In-place version of the constructor CImg(const CImgDisplay&).
    **/
    CImg<T>& assign(const CImgDisplay &disp) {
      disp.snapshot(*this);
      return *this;
    }

    //! Construct empty image \inplace.
    /**
       Equivalent to assign().
       \note
       - It has been defined for compatibility with STL naming conventions.
    **/
    CImg<T>& clear() {
      return assign();
    }

    //! Transfer content of an image instance into another one.
    /**
       Transfer the dimensions and the pixel buffer content of an image instance into another one,
       and replace instance by an empty image. It avoids the copy of the pixel buffer
       when possible.
       \param img Destination image.
       \note
       - Pixel types \c T and \c t of source and destination images can be different, though the process is
         designed to be instantaneous when \c T and \c t are the same.
       \par Example
       \code
       CImg<float> src(256,256,1,3,0), // Construct a 256x256x1x3 (color) image filled with value '0'.
                   dest(16,16);        // Construct a 16x16x1x1 (scalar) image.
       src.move_to(dest);              // Now, 'src' is empty and 'dest' is the 256x256x1x3 image.
       \endcode
    **/
    template<typename t>
    CImg<t>& move_to(CImg<t>& img) {
      img.assign(*this);
      assign();
      return img;
    }

    //! Transfer content of an image instance into another one \specialization.
    CImg<T>& move_to(CImg<T>& img) {
      if (_is_shared || img._is_shared) img.assign(*this);
      else swap(img);
      assign();
      return img;
    }

    //! Transfer content of an image instance into a new image in an image list.
    /**
       Transfer the dimensions and the pixel buffer content of an image instance
       into a newly inserted image at position \c pos in specified \c CImgList<t> instance.
       \param list Destination list.
       \param pos Position of the newly inserted image in the list.
       \note
       - When optionnal parameter \c pos is ommited, the image instance is transfered as a new
         image at the end of the specified \c list.
       - It is convenient to sequentially insert new images into image lists, with no
         additional copies of memory buffer.
       \par Example
       \code
       CImgList<float> list;             // Construct an empty image list.
       CImg<float> img("reference.jpg"); // Read image from filename.
       img.move_to(list);                // Transfer image content as a new item in the list (no buffer copy).
       \endcode
    **/
    template<typename t>
    CImgList<t>& move_to(CImgList<t>& list, const unsigned int pos=~0U) {
      const unsigned int npos = pos>list._width?list._width:pos;
      move_to(list.insert(1,npos)[npos]);
      return list;
    }

    //! Swap fields of two image instances.
    /**
      \param img Image to swap fields with.
      \note
      - It can be used to interchange the content of two images in a very fast way. Can be convenient when dealing
        with algorithms requiring two swapping buffers.
      \par Example
      \code
      CImg<float> img1("lena.jpg"),
                  img2("milla.jpg");
      img1.swap(img2);               // Now, 'img1' is 'milla' and 'img2' is 'lena'.
      \endcode
    **/
    CImg<T>& swap(CImg<T>& img) {
      cimg::swap(_width,img._width,_height,img._height,_depth,img._depth,_spectrum,img._spectrum);
      cimg::swap(_data,img._data);
      cimg::swap(_is_shared,img._is_shared);
      return img;
    }

    //! Return a reference to an empty image.
    /**
       \note
       This function is useful mainly to declare optional parameters having type \c CImg<T> in functions prototypes,
       e.g.
       \code
       void f(const int x=0, const int y=0, const CImg<float>& img=CImg<float>::empty());
       \endcode
     **/
    static CImg<T>& empty() {
      static CImg<T> _empty;
      return _empty.assign();
    }

    //! Return a reference to an empty image \const.
    static const CImg<T>& const_empty() {
      static const CImg<T> _empty;
      return _empty;
    }

    //@}
    //------------------------------------------
    //
    //! \name Overloaded Operators
    //@{
    //------------------------------------------

    //! Access to a pixel value.
    /**
       Return a reference to a located pixel value of the image instance,
       being possibly \e const, whether the image instance is \e const or not.
       This is the standard method to get/set pixel values in \c CImg<T> images.
       \param x X-coordinate of the pixel value.
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \note
       - Range of pixel coordinates start from <tt>(0,0,0,0)</tt> to
         <tt>(width() - 1,height() - 1,depth() - 1,spectrum() - 1)</tt>.
       - Due to the particular arrangement of the pixel buffers defined in %CImg, you can omit one coordinate if the
         corresponding dimension is equal to \c 1.
         For instance, pixels of a 2d image (depth() equal to \c 1) can be accessed by <tt>img(x,y,c)</tt> instead of
         <tt>img(x,y,0,c)</tt>.
       \warning
       - There is \e no boundary checking done in this operator, to make it as fast as possible.
         You \e must take care of out-of-bounds access by yourself, if necessary.
         For debuging purposes, you may want to define macro \c 'cimg_verbosity'>=3 to enable additional boundary
         checking operations in this operator. In that case, warning messages will be printed on the error output
         when accessing out-of-bounds pixels.
       \par Example
       \code
       CImg<float> img(100,100,1,3,0);                   // Construct a 100x100x1x3 (color) image with pixels set to '0'.
       const float
          valR = img(10,10,0,0),                         // Read red value at coordinates (10,10).
          valG = img(10,10,0,1),                         // Read green value at coordinates (10,10)
          valB = img(10,10,2),                           // Read blue value at coordinates (10,10) (Z-coordinate can be omitted).
          avg = (valR + valG + valB)/3;                  // Compute average pixel value.
       img(10,10,0) = img(10,10,1) = img(10,10,2) = avg; // Replace the color pixel (10,10) by the average grey value.
       \endcode
    **/
#if cimg_verbosity>=3
    T& operator()(const unsigned int x, const unsigned int y=0,
                  const unsigned int z=0, const unsigned int c=0) {
      const ulongT off = (ulongT)offset(x,y,z,c);
      if (!_data || off>=size()) {
        cimg::warn(_cimg_instance
                   "operator(): Invalid pixel request, at coordinates (%d,%d,%d,%d) [offset=%u].",
                   cimg_instance,
                   (int)x,(int)y,(int)z,(int)c,off);
        return *_data;
      }
      else return _data[off];
    }

    //! Access to a pixel value \const.
    const T& operator()(const unsigned int x, const unsigned int y=0,
                        const unsigned int z=0, const unsigned int c=0) const {
      return const_cast<CImg<T>*>(this)->operator()(x,y,z,c);
    }

    //! Access to a pixel value.
    /**
       \param x X-coordinate of the pixel value.
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \param wh Precomputed offset, must be equal to <tt>width()*\ref height()</tt>.
       \param whd Precomputed offset, must be equal to <tt>width()*\ref height()*\ref depth()</tt>.
       \note
       - Similar to (but faster than) operator()().
         It uses precomputed offsets to optimize memory access. You may use it to optimize
         the reading/writing of several pixel values in the same image (e.g. in a loop).
     **/
    T& operator()(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int c,
                  const ulongT wh, const ulongT whd=0) {
      cimg::unused(wh,whd);
      return (*this)(x,y,z,c);
    }

    //! Access to a pixel value \const.
    const T& operator()(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int c,
                        const ulongT wh, const ulongT whd=0) const {
      cimg::unused(wh,whd);
      return (*this)(x,y,z,c);
    }
#else
    T& operator()(const unsigned int x) {
      return _data[x];
    }

    const T& operator()(const unsigned int x) const {
      return _data[x];
    }

    T& operator()(const unsigned int x, const unsigned int y) {
      return _data[x + y*_width];
    }

    const T& operator()(const unsigned int x, const unsigned int y) const {
      return _data[x + y*_width];
    }

    T& operator()(const unsigned int x, const unsigned int y, const unsigned int z) {
      return _data[x + y*(ulongT)_width + z*(ulongT)_width*_height];
   }

    const T& operator()(const unsigned int x, const unsigned int y, const unsigned int z) const {
      return _data[x + y*(ulongT)_width + z*(ulongT)_width*_height];
    }

    T& operator()(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int c) {
      return _data[x + y*(ulongT)_width + z*(ulongT)_width*_height + c*(ulongT)_width*_height*_depth];
    }

    const T& operator()(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int c) const {
      return _data[x + y*(ulongT)_width + z*(ulongT)_width*_height + c*(ulongT)_width*_height*_depth];
    }

    T& operator()(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int,
                  const ulongT wh) {
      return _data[x + y*_width + z*wh];
    }

    const T& operator()(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int,
                        const ulongT wh) const {
      return _data[x + y*_width + z*wh];
    }

    T& operator()(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int c,
                  const ulongT wh, const ulongT whd) {
      return _data[x + y*_width + z*wh + c*whd];
    }

    const T& operator()(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int c,
                        const ulongT wh, const ulongT whd) const {
      return _data[x + y*_width + z*wh + c*whd];
    }
#endif

    //! Implicitely cast an image into a \c T*.
    /**
       Implicitely cast a \c CImg<T> instance into a \c T* or \c const \c T* pointer, whether the image instance
       is \e const or not. The returned pointer points on the first value of the image pixel buffer.
       \note
       - It simply returns the pointer data() to the pixel buffer.
       - This implicit conversion is convenient to test the empty state of images (data() being \c 0 in this case), e.g.
       \code
       CImg<float> img1(100,100), img2; // 'img1' is a 100x100 image, 'img2' is an empty image.
       if (img1) {                      // Test succeeds, 'img1' is not an empty image.
         if (!img2) {                   // Test succeeds, 'img2' is an empty image.
           std::printf("'img1' is not empty, 'img2' is empty.");
         }
       }
       \endcode
       - It also allows to use brackets to access pixel values, without need for a \c CImg<T>::operator[](), e.g.
       \code
       CImg<float> img(100,100);
       const float value = img[99]; // Access to value of the last pixel on the first row.
       img[510] = 255;              // Set pixel value at (10,5).
       \endcode
    **/
    operator T*() {
      return _data;
    }

    //! Implicitely cast an image into a \c T* \const.
    operator const T*() const {
      return _data;
    }

    //! Assign a value to all image pixels.
    /**
       Assign specified \c value to each pixel value of the image instance.
       \param value Value that will be assigned to image pixels.
       \note
       - The image size is never modified.
       - The \c value may be casted to pixel type \c T if necessary.
       \par Example
       \code
       CImg<char> img(100,100); // Declare image (with garbage values).
       img = 0;                 // Set all pixel values to '0'.
       img = 1.2;               // Set all pixel values to '1' (cast of '1.2' as a 'char').
       \endcode
    **/
    CImg<T>& operator=(const T& value) {
      return fill(value);
    }

    //! Assign pixels values from a specified expression.
    /**
       Initialize all pixel values from the specified string \c expression.
       \param expression Value string describing the way pixel values are set.
       \note
       - String parameter \c expression may describe different things:
         - If \c expression is a list of values (as in \c "1,2,3,8,3,2"), or a formula (as in \c "(x*y)%255"),
           the pixel values are set from specified \c expression and the image size is not modified.
         - If \c expression is a filename (as in \c "reference.jpg"), the corresponding image file is loaded and
           replace the image instance. The image size is modified if necessary.
       \par Example
       \code
       CImg<float> img1(100,100), img2(img1), img3(img1); // Declare three 100x100 scalar images with unitialized pixel values.
       img1 = "0,50,100,150,200,250,200,150,100,50";      // Set pixel values of 'img1' from a value sequence.
       img2 = "10*((x*y)%25)";                            // Set pixel values of 'img2' from a formula.
       img3 = "reference.jpg";                            // Set pixel values of 'img3' from a file (image size is modified).
       (img1,img2,img3).display();
       \endcode
       \image html ref_operator_eq.jpg
    **/
    CImg<T>& operator=(const char *const expression) {
      const unsigned int omode = cimg::exception_mode();
      cimg::exception_mode(0);
      try {
        _fill(expression,true,true,0,0,"operator=",0);
      } catch (CImgException&) {
        cimg::exception_mode(omode);
        load(expression);
      }
      cimg::exception_mode(omode);
      return *this;
    }

    //! Copy an image into the current image instance.
    /**
       Similar to the in-place copy constructor assign(const CImg<t>&).
    **/
    template<typename t>
    CImg<T>& operator=(const CImg<t>& img) {
      return assign(img);
    }

    //! Copy an image into the current image instance \specialization.
    CImg<T>& operator=(const CImg<T>& img) {
      return assign(img);
    }

    //! Copy the content of a display window to the current image instance.
    /**
       Similar to assign(const CImgDisplay&).
    **/
    CImg<T>& operator=(const CImgDisplay& disp) {
      disp.snapshot(*this);
      return *this;
    }

    //! In-place addition operator.
    /**
       Add specified \c value to all pixels of an image instance.
       \param value Value to add.
       \note
       - Resulting pixel values are casted to fit the pixel type \c T.
         For instance, adding \c 0.2 to a \c CImg<char> is possible but does nothing indeed.
       - Overflow values are treated as with standard C++ numeric types. For instance,
       \code
       CImg<unsigned char> img(100,100,1,1,255); // Construct a 100x100 image with pixel values '255'.
       img+=1;                                   // Add '1' to each pixels -> Overflow.
       // here all pixels of image 'img' are equal to '0'.
       \endcode
       - To prevent value overflow, you may want to consider pixel type \c T as \c float or \c double,
         and use cut() after addition.
       \par Example
       \code
       CImg<unsigned char> img1("reference.jpg");          // Load a 8-bits RGB image (values in [0,255]).
       CImg<float> img2(img1);                             // Construct a float-valued copy of 'img1'.
       img2+=100;                                          // Add '100' to pixel values -> goes out of [0,255] but no problems with floats.
       img2.cut(0,255);                                    // Cut values in [0,255] to fit the 'unsigned char' constraint.
       img1 = img2;                                        // Rewrite safe result in 'unsigned char' version 'img1'.
       const CImg<unsigned char> img3 = (img1 + 100).cut(0,255); // Do the same in a more simple and elegant way.
       (img1,img2,img3).display();
       \endcode
       \image html ref_operator_plus.jpg
     **/
    template<typename t>
    CImg<T>& operator+=(const t value) {
      if (is_empty()) return *this;
#ifdef cimg_use_openmp
#pragma omp parallel for cimg_openmp_if(size()>=524288)
#endif
      cimg_rof(*this,ptrd,T) *ptrd = (T)(*ptrd + value);
      return *this;
    }

    //! In-place addition operator.
    /**
       Add values to image pixels, according to the specified string \c expression.
       \param expression Value string describing the way pixel values are added.
       \note
       - Similar to operator=(const char*), except that it adds values to the pixels of the current image instance,
         instead of assigning them.
    **/
    CImg<T>& operator+=(const char *const expression) {
      return *this+=(+*this)._fill(expression,true,true,0,0,"operator+=",this);
    }

    //! In-place addition operator.
    /**
       Add values to image pixels, according to the values of the input image \c img.
       \param img Input image to add.
       \note
       - The size of the image instance is never modified.
       - It is not mandatory that input image \c img has the same size as the image instance.
         If less values are available in \c img, then the values are added periodically. For instance, adding one
         WxH scalar image (spectrum() equal to \c 1) to one WxH color image (spectrum() equal to \c 3)
         means each color channel will be incremented with the same values at the same locations.
       \par Example
       \code
       CImg<float> img1("reference.jpg");                                   // Load a RGB color image (img1.spectrum()==3)
       const CImg<float> img2(img1.width(),img.height(),1,1,"255*(x/w)^2"); // Construct a scalar shading (img2.spectrum()==1).
       img1+=img2;                                                          // Add shading to each channel of 'img1'.
       img1.cut(0,255);                                                     // Prevent [0,255] overflow.
       (img2,img1).display();
       \endcode
       \image html ref_operator_plus1.jpg
    **/
    template<typename t>
    CImg<T>& operator+=(const CImg<t>& img) {
      const ulongT siz = size(), isiz = img.size();
      if (siz && isiz) {
        if (is_overlapped(img)) return *this+=+img;
        T *ptrd = _data, *const ptre = _data + siz;
        if (siz>isiz) for (ulongT n = siz/isiz; n; --n)
          for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
            *ptrd = (T)(*ptrd + *(ptrs++));
        for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)(*ptrd + *(ptrs++));
      }
      return *this;
    }

    //! In-place increment operator (prefix).
    /**
       Add \c 1 to all image pixels, and return a reference to the current incremented image instance.
       \note
       - Writing \c ++img is equivalent to \c img+=1.
     **/
    CImg<T>& operator++() {
      if (is_empty()) return *this;
#ifdef cimg_use_openmp
#pragma omp parallel for cimg_openmp_if(size()>=524288)
#endif
      cimg_rof(*this,ptrd,T) ++*ptrd;
      return *this;
    }

    //! In-place increment operator (postfix).
    /**
       Add \c 1 to all image pixels, and return a new copy of the initial (pre-incremented) image instance.
       \note
       - Use the prefixed version operator++() if you don't need a copy of the initial
         (pre-incremented) image instance, since a useless image copy may be expensive in terms of memory usage.
     **/
    CImg<T> operator++(int) {
      const CImg<T> copy(*this,false);
      ++*this;
      return copy;
    }

    //! Return a non-shared copy of the image instance.
    /**
       \note
       - Use this operator to ensure you get a non-shared copy of an image instance with same pixel type \c T.
         Indeed, the usual copy constructor CImg<T>(const CImg<T>&) returns a shared copy of a shared input image,
         and it may be not desirable to work on a regular copy (e.g. for a resize operation) if you have no
         information about the shared state of the input image.
       - Writing \c (+img) is equivalent to \c CImg<T>(img,false).
    **/
    CImg<T> operator+() const {
      return CImg<T>(*this,false);
    }

    //! Addition operator.
    /**
       Similar to operator+=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
     **/
    template<typename t>
    CImg<_cimg_Tt> operator+(const t value) const {
      return CImg<_cimg_Tt>(*this,false)+=value;
    }

    //! Addition operator.
    /**
       Similar to operator+=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
     **/
    CImg<Tfloat> operator+(const char *const expression) const {
      return CImg<Tfloat>(*this,false)+=expression;
    }

    //! Addition operator.
    /**
       Similar to operator+=(const CImg<t>&), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
     **/
    template<typename t>
    CImg<_cimg_Tt> operator+(const CImg<t>& img) const {
      return CImg<_cimg_Tt>(*this,false)+=img;
    }

    //! In-place substraction operator.
    /**
       Similar to operator+=(const t), except that it performs a substraction instead of an addition.
     **/
    template<typename t>
    CImg<T>& operator-=(const t value) {
      if (is_empty()) return *this;
#ifdef cimg_use_openmp
#pragma omp parallel for cimg_openmp_if(size()>=524288)
#endif
      cimg_rof(*this,ptrd,T) *ptrd = (T)(*ptrd - value);
      return *this;
    }

    //! In-place substraction operator.
    /**
       Similar to operator+=(const char*), except that it performs a substraction instead of an addition.
     **/
    CImg<T>& operator-=(const char *const expression) {
      return *this-=(+*this)._fill(expression,true,true,0,0,"operator-=",this);
    }

    //! In-place substraction operator.
    /**
       Similar to operator+=(const CImg<t>&), except that it performs a substraction instead of an addition.
     **/
    template<typename t>
    CImg<T>& operator-=(const CImg<t>& img) {
      const ulongT siz = size(), isiz = img.size();
      if (siz && isiz) {
        if (is_overlapped(img)) return *this-=+img;
        T *ptrd = _data, *const ptre = _data + siz;
        if (siz>isiz) for (ulongT n = siz/isiz; n; --n)
          for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
            *ptrd = (T)(*ptrd - *(ptrs++));
        for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)(*ptrd - *(ptrs++));
      }
      return *this;
    }

    //! In-place decrement operator (prefix).
    /**
       Similar to operator++(), except that it performs a decrement instead of an increment.
    **/
    CImg<T>& operator--() {
      if (is_empty()) return *this;
#ifdef cimg_use_openmp
#pragma omp parallel for cimg_openmp_if(size()>=524288)
#endif
      cimg_rof(*this,ptrd,T) *ptrd = *ptrd - (T)1;
      return *this;
    }

    //! In-place decrement operator (postfix).
    /**
       Similar to operator++(int), except that it performs a decrement instead of an increment.
    **/
    CImg<T> operator--(int) {
      const CImg<T> copy(*this,false);
      --*this;
      return copy;
    }

    //! Replace each pixel by its opposite value.
    /**
       \note
       - If the computed opposite values are out-of-range, they are treated as with standard C++ numeric types.
         For instance, the \c unsigned \c char opposite of \c 1 is \c 255.
       \par Example
       \code
       const CImg<unsigned char>
         img1("reference.jpg"),   // Load a RGB color image.
         img2 = -img1;            // Compute its opposite (in 'unsigned char').
       (img1,img2).display();
       \endcode
       \image html ref_operator_minus.jpg
     **/
    CImg<T> operator-() const {
      return CImg<T>(_width,_height,_depth,_spectrum,(T)0)-=*this;
    }

    //! Substraction operator.
    /**
       Similar to operator-=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
    template<typename t>
    CImg<_cimg_Tt> operator-(const t value) const {
      return CImg<_cimg_Tt>(*this,false)-=value;
    }

    //! Substraction operator.
    /**
       Similar to operator-=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
    CImg<Tfloat> operator-(const char *const expression) const {
      return CImg<Tfloat>(*this,false)-=expression;
    }

    //! Substraction operator.
    /**
       Similar to operator-=(const CImg<t>&), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
    template<typename t>
    CImg<_cimg_Tt> operator-(const CImg<t>& img) const {
      return CImg<_cimg_Tt>(*this,false)-=img;
    }

    //! In-place multiplication operator.
    /**
       Similar to operator+=(const t), except that it performs a multiplication instead of an addition.
     **/
    template<typename t>
    CImg<T>& operator*=(const t value) {
      if (is_empty()) return *this;
#ifdef cimg_use_openmp
#pragma omp parallel for cimg_openmp_if(size()>=262144)
#endif
      cimg_rof(*this,ptrd,T) *ptrd = (T)(*ptrd * value);
      return *this;
    }

    //! In-place multiplication operator.
    /**
       Similar to operator+=(const char*), except that it performs a multiplication instead of an addition.
     **/
    CImg<T>& operator*=(const char *const expression) {
      return mul((+*this)._fill(expression,true,true,0,0,"operator*=",this));
    }

    //! In-place multiplication operator.
    /**
       Replace the image instance by the matrix multiplication between the image instance and the specified matrix
       \c img.
       \param img Second operand of the matrix multiplication.
       \note
       - It does \e not compute a pointwise multiplication between two images. For this purpose, use
         mul(const CImg<t>&) instead.
       - The size of the image instance can be modified by this operator.
       \par Example
       \code
       CImg<float> A(2,2,1,1, 1,2,3,4);   // Construct 2x2 matrix A = [1,2;3,4].
       const CImg<float> X(1,2,1,1, 1,2); // Construct 1x2 vector X = [1;2].
       A*=X;                              // Assign matrix multiplication A*X to 'A'.
       // 'A' is now a 1x2 vector whose values are [5;11].
       \endcode
    **/
    template<typename t>
    CImg<T>& operator*=(const CImg<t>& img) {
      return ((*this)*img).move_to(*this);
    }

    //! Multiplication operator.
    /**
       Similar to operator*=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
    template<typename t>
    CImg<_cimg_Tt> operator*(const t value) const {
      return CImg<_cimg_Tt>(*this,false)*=value;
    }

    //! Multiplication operator.
    /**
       Similar to operator*=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
    CImg<Tfloat> operator*(const char *const expression) const {
      return CImg<Tfloat>(*this,false)*=expression;
    }

    //! Multiplication operator.
    /**
       Similar to operator*=(const CImg<t>&), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
    template<typename t>
    CImg<_cimg_Tt> operator*(const CImg<t>& img) const {
      if (_width!=img._height || _depth!=1 || _spectrum!=1)
        throw CImgArgumentException(_cimg_instance
                                    "operator*(): Invalid multiplication of instance by specified "
                                    "matrix (%u,%u,%u,%u,%p)",
                                    cimg_instance,
                                    img._width,img._height,img._depth,img._spectrum,img._data);
      CImg<_cimg_Tt> res(img._width,_height);
#ifdef cimg_use_openmp
#pragma omp parallel for collapse(2) cimg_openmp_if(size()>1024 && img.size()>1024)
      cimg_forXY(res,i,j) {
        _cimg_Ttdouble value = 0; cimg_forX(*this,k) value+=(*this)(k,j)*img(i,k); res(i,j) = (_cimg_Tt)value;
      }
#else
      _cimg_Tt *ptrd = res._data;
      cimg_forXY(res,i,j) {
        _cimg_Ttdouble value = 0; cimg_forX(*this,k) value+=(*this)(k,j)*img(i,k); *(ptrd++) = (_cimg_Tt)value;
      }
#endif
      return res;
    }

    //! In-place division operator.
    /**
       Similar to operator+=(const t), except that it performs a division instead of an addition.
     **/
    template<typename t>
    CImg<T>& operator/=(const t value) {
      if (is_empty()) return *this;
#ifdef cimg_use_openmp
#pragma omp parallel for cimg_openmp_if(size()>=32768)
#endif
      cimg_rof(*this,ptrd,T) *ptrd = (T)(*ptrd / value);
      return *this;
    }

    //! In-place division operator.
    /**
       Similar to operator+=(const char*), except that it performs a division instead of an addition.
     **/
    CImg<T>& operator/=(const char *const expression) {
      return div((+*this)._fill(expression,true,true,0,0,"operator/=",this));
    }

    //! In-place division operator.
    /**
       Replace the image instance by the (right) matrix division between the image instance and the specified
       matrix \c img.
       \param img Second operand of the matrix division.
       \note
       - It does \e not compute a pointwise division between two images. For this purpose, use
         div(const CImg<t>&) instead.
       - It returns the matrix operation \c A*inverse(img).
       - The size of the image instance can be modified by this operator.
     **/
    template<typename t>
    CImg<T>& operator/=(const CImg<t>& img) {
      return (*this*img.get_invert()).move_to(*this);
    }

    //! Division operator.
    /**
       Similar to operator/=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
    template<typename t>
    CImg<_cimg_Tt> operator/(const t value) const {
      return CImg<_cimg_Tt>(*this,false)/=value;
    }

    //! Division operator.
    /**
       Similar to operator/=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
    CImg<Tfloat> operator/(const char *const expression) const {
      return CImg<Tfloat>(*this,false)/=expression;
    }

    //! Division operator.
    /**
       Similar to operator/=(const CImg<t>&), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
    template<typename t>
    CImg<_cimg_Tt> operator/(const CImg<t>& img) const {
      return (*this)*img.get_invert();
    }

    //! In-place modulo operator.
    /**
       Similar to operator+=(const t), except that it performs a modulo operation instead of an addition.
    **/
    template<typename t>
    CImg<T>& operator%=(const t value) {
      if (is_empty()) return *this;
#ifdef cimg_use_openmp
#pragma omp parallel for cimg_openmp_if(size()>=16384)
#endif
      cimg_rof(*this,ptrd,T) *ptrd = (T)cimg::mod(*ptrd,(T)value);
      return *this;
    }

    //! In-place modulo operator.
    /**
       Similar to operator+=(const char*), except that it performs a modulo operation instead of an addition.
    **/
    CImg<T>& operator%=(const char *const expression) {
      return *this%=(+*this)._fill(expression,true,true,0,0,"operator%=",this);
    }

    //! In-place modulo operator.
    /**
       Similar to operator+=(const CImg<t>&), except that it performs a modulo operation instead of an addition.
    **/
    template<typename t>
    CImg<T>& operator%=(const CImg<t>& img) {
      const ulongT siz = size(), isiz = img.size();
      if (siz && isiz) {
        if (is_overlapped(img)) return *this%=+img;
        T *ptrd = _data, *const ptre = _data + siz;
        if (siz>isiz) for (ulongT n = siz/isiz; n; --n)
          for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
            *ptrd = cimg::mod(*ptrd,(T)*(ptrs++));
        for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = cimg::mod(*ptrd,(T)*(ptrs++));
      }
      return *this;
    }

    //! Modulo operator.
    /**
       Similar to operator%=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
    template<typename t>
    CImg<_cimg_Tt> operator%(const t value) const {
      return CImg<_cimg_Tt>(*this,false)%=value;
    }

    //! Modulo operator.
    /**
       Similar to operator%=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
    CImg<Tfloat> operator%(const char *const expression) const {
      return CImg<Tfloat>(*this,false)%=expression;
    }

    //! Modulo operator.
    /**
       Similar to operator%=(const CImg<t>&), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image may be a superset of the initial pixel type \c T, if necessary.
    **/
    template<typename t>
    CImg<_cimg_Tt> operator%(const CImg<t>& img) const {
      return CImg<_cimg_Tt>(*this,false)%=img;
    }

    //! In-place bitwise AND operator.
    /**
       Similar to operator+=(const t), except that it performs a bitwise AND operation instead of an addition.
    **/
    template<typename t>
    CImg<T>& operator&=(const t value) {
      if (is_empty()) return *this;
#ifdef cimg_use_openmp
#pragma omp parallel for cimg_openmp_if(size()>=32768)
#endif
      cimg_rof(*this,ptrd,T) *ptrd = (T)((ulongT)*ptrd & (ulongT)value);
      return *this;
    }

    //! In-place bitwise AND operator.
    /**
       Similar to operator+=(const char*), except that it performs a bitwise AND operation instead of an addition.
    **/
    CImg<T>& operator&=(const char *const expression) {
      return *this&=(+*this)._fill(expression,true,true,0,0,"operator&=",this);
    }

    //! In-place bitwise AND operator.
    /**
       Similar to operator+=(const CImg<t>&), except that it performs a bitwise AND operation instead of an addition.
    **/
    template<typename t>
    CImg<T>& operator&=(const CImg<t>& img) {
      const ulongT siz = size(), isiz = img.size();
      if (siz && isiz) {
        if (is_overlapped(img)) return *this&=+img;
        T *ptrd = _data, *const ptre = _data + siz;
        if (siz>isiz) for (ulongT n = siz/isiz; n; --n)
          for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
            *ptrd = (T)((ulongT)*ptrd & (ulongT)*(ptrs++));
        for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)((ulongT)*ptrd & (ulongT)*(ptrs++));
      }
      return *this;
    }

    //! Bitwise AND operator.
    /**
       Similar to operator&=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
    template<typename t>
    CImg<T> operator&(const t value) const {
      return (+*this)&=value;
    }

    //! Bitwise AND operator.
    /**
       Similar to operator&=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
    CImg<T> operator&(const char *const expression) const {
      return (+*this)&=expression;
    }

    //! Bitwise AND operator.
    /**
       Similar to operator&=(const CImg<t>&), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
    template<typename t>
    CImg<T> operator&(const CImg<t>& img) const {
      return (+*this)&=img;
    }

    //! In-place bitwise OR operator.
    /**
       Similar to operator+=(const t), except that it performs a bitwise OR operation instead of an addition.
    **/
    template<typename t>
    CImg<T>& operator|=(const t value) {
      if (is_empty()) return *this;
#ifdef cimg_use_openmp
#pragma omp parallel for cimg_openmp_if(size()>=32768)
#endif
      cimg_rof(*this,ptrd,T) *ptrd = (T)((ulongT)*ptrd | (ulongT)value);
      return *this;
    }

    //! In-place bitwise OR operator.
    /**
       Similar to operator+=(const char*), except that it performs a bitwise OR operation instead of an addition.
    **/
    CImg<T>& operator|=(const char *const expression) {
      return *this|=(+*this)._fill(expression,true,true,0,0,"operator|=",this);
    }

    //! In-place bitwise OR operator.
    /**
       Similar to operator+=(const CImg<t>&), except that it performs a bitwise OR operation instead of an addition.
    **/
    template<typename t>
    CImg<T>& operator|=(const CImg<t>& img) {
      const ulongT siz = size(), isiz = img.size();
      if (siz && isiz) {
        if (is_overlapped(img)) return *this|=+img;
        T *ptrd = _data, *const ptre = _data + siz;
        if (siz>isiz) for (ulongT n = siz/isiz; n; --n)
          for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
            *ptrd = (T)((ulongT)*ptrd | (ulongT)*(ptrs++));
        for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)((ulongT)*ptrd | (ulongT)*(ptrs++));
      }
      return *this;
    }

    //! Bitwise OR operator.
    /**
       Similar to operator|=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
    template<typename t>
    CImg<T> operator|(const t value) const {
      return (+*this)|=value;
    }

    //! Bitwise OR operator.
    /**
       Similar to operator|=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
    CImg<T> operator|(const char *const expression) const {
      return (+*this)|=expression;
    }

    //! Bitwise OR operator.
    /**
       Similar to operator|=(const CImg<t>&), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
    template<typename t>
    CImg<T> operator|(const CImg<t>& img) const {
      return (+*this)|=img;
    }

    //! In-place bitwise XOR operator.
    /**
       Similar to operator+=(const t), except that it performs a bitwise XOR operation instead of an addition.
       \warning
       - It does \e not compute the \e power of pixel values. For this purpose, use pow(const t) instead.
    **/
    template<typename t>
    CImg<T>& operator^=(const t value) {
      if (is_empty()) return *this;
#ifdef cimg_use_openmp
#pragma omp parallel for cimg_openmp_if(size()>=32768)
#endif
      cimg_rof(*this,ptrd,T) *ptrd = (T)((ulongT)*ptrd ^ (ulongT)value);
      return *this;
    }

    //! In-place bitwise XOR operator.
    /**
       Similar to operator+=(const char*), except that it performs a bitwise XOR operation instead of an addition.
       \warning
       - It does \e not compute the \e power of pixel values. For this purpose, use pow(const char*) instead.
    **/
    CImg<T>& operator^=(const char *const expression) {
      return *this^=(+*this)._fill(expression,true,true,0,0,"operator^=",this);
    }

    //! In-place bitwise XOR operator.
    /**
       Similar to operator+=(const CImg<t>&), except that it performs a bitwise XOR operation instead of an addition.
       \warning
       - It does \e not compute the \e power of pixel values. For this purpose, use pow(const CImg<t>&) instead.
    **/
    template<typename t>
    CImg<T>& operator^=(const CImg<t>& img) {
      const ulongT siz = size(), isiz = img.size();
      if (siz && isiz) {
        if (is_overlapped(img)) return *this^=+img;
        T *ptrd = _data, *const ptre = _data + siz;
        if (siz>isiz) for (ulongT n = siz/isiz; n; --n)
          for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
            *ptrd = (T)((ulongT)*ptrd ^ (ulongT)*(ptrs++));
        for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)((ulongT)*ptrd ^ (ulongT)*(ptrs++));
      }
      return *this;
    }

    //! Bitwise XOR operator.
    /**
       Similar to operator^=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
    template<typename t>
    CImg<T> operator^(const t value) const {
      return (+*this)^=value;
    }

    //! Bitwise XOR operator.
    /**
       Similar to operator^=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
    CImg<T> operator^(const char *const expression) const {
      return (+*this)^=expression;
    }

    //! Bitwise XOR operator.
    /**
       Similar to operator^=(const CImg<t>&), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
    template<typename t>
    CImg<T> operator^(const CImg<t>& img) const {
      return (+*this)^=img;
    }

    //! In-place bitwise left shift operator.
    /**
       Similar to operator+=(const t), except that it performs a bitwise left shift instead of an addition.
    **/
    template<typename t>
    CImg<T>& operator<<=(const t value) {
      if (is_empty()) return *this;
#ifdef cimg_use_openmp
#pragma omp parallel for cimg_openmp_if(size()>=65536)
#endif
      cimg_rof(*this,ptrd,T) *ptrd = (T)(((longT)*ptrd) << (int)value);
      return *this;
    }

    //! In-place bitwise left shift operator.
    /**
       Similar to operator+=(const char*), except that it performs a bitwise left shift instead of an addition.
    **/
    CImg<T>& operator<<=(const char *const expression) {
      return *this<<=(+*this)._fill(expression,true,true,0,0,"operator<<=",this);
    }

    //! In-place bitwise left shift operator.
    /**
       Similar to operator+=(const CImg<t>&), except that it performs a bitwise left shift instead of an addition.
    **/
    template<typename t>
    CImg<T>& operator<<=(const CImg<t>& img) {
      const ulongT siz = size(), isiz = img.size();
      if (siz && isiz) {
        if (is_overlapped(img)) return *this^=+img;
        T *ptrd = _data, *const ptre = _data + siz;
        if (siz>isiz) for (ulongT n = siz/isiz; n; --n)
          for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
            *ptrd = (T)((longT)*ptrd << (int)*(ptrs++));
        for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)((longT)*ptrd << (int)*(ptrs++));
      }
      return *this;
    }

    //! Bitwise left shift operator.
    /**
       Similar to operator<<=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
    template<typename t>
    CImg<T> operator<<(const t value) const {
      return (+*this)<<=value;
    }

    //! Bitwise left shift operator.
    /**
       Similar to operator<<=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
    CImg<T> operator<<(const char *const expression) const {
      return (+*this)<<=expression;
    }

    //! Bitwise left shift operator.
    /**
       Similar to operator<<=(const CImg<t>&), except that it returns a new image instance instead of
       operating in-place.
       The pixel type of the returned image is \c T.
    **/
    template<typename t>
    CImg<T> operator<<(const CImg<t>& img) const {
      return (+*this)<<=img;
    }

    //! In-place bitwise right shift operator.
    /**
       Similar to operator+=(const t), except that it performs a bitwise right shift instead of an addition.
    **/
    template<typename t>
    CImg<T>& operator>>=(const t value) {
      if (is_empty()) return *this;
#ifdef cimg_use_openmp
#pragma omp parallel for cimg_openmp_if(size()>=65536)
#endif
      cimg_rof(*this,ptrd,T) *ptrd = (T)(((longT)*ptrd) >> (int)value);
      return *this;
    }

    //! In-place bitwise right shift operator.
    /**
       Similar to operator+=(const char*), except that it performs a bitwise right shift instead of an addition.
    **/
    CImg<T>& operator>>=(const char *const expression) {
      return *this>>=(+*this)._fill(expression,true,true,0,0,"operator>>=",this);
    }

    //! In-place bitwise right shift operator.
    /**
       Similar to operator+=(const CImg<t>&), except that it performs a bitwise right shift instead of an addition.
    **/
    template<typename t>
    CImg<T>& operator>>=(const CImg<t>& img) {
      const ulongT siz = size(), isiz = img.size();
      if (siz && isiz) {
        if (is_overlapped(img)) return *this^=+img;
        T *ptrd = _data, *const ptre = _data + siz;
        if (siz>isiz) for (ulongT n = siz/isiz; n; --n)
          for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
            *ptrd = (T)((longT)*ptrd >> (int)*(ptrs++));
        for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)((longT)*ptrd >> (int)*(ptrs++));
      }
      return *this;
    }

    //! Bitwise right shift operator.
    /**
       Similar to operator>>=(const t), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
    template<typename t>
    CImg<T> operator>>(const t value) const {
      return (+*this)>>=value;
    }

    //! Bitwise right shift operator.
    /**
       Similar to operator>>=(const char*), except that it returns a new image instance instead of operating in-place.
       The pixel type of the returned image is \c T.
    **/
    CImg<T> operator>>(const char *const expression) const {
      return (+*this)>>=expression;
    }

    //! Bitwise right shift operator.
    /**
       Similar to operator>>=(const CImg<t>&), except that it returns a new image instance instead of
       operating in-place.
       The pixel type of the returned image is \c T.
    **/
    template<typename t>
    CImg<T> operator>>(const CImg<t>& img) const {
      return (+*this)>>=img;
    }

    //! Bitwise inversion operator.
    /**
       Similar to operator-(), except that it compute the bitwise inverse instead of the opposite value.
    **/
    CImg<T> operator~() const {
      CImg<T> res(_width,_height,_depth,_spectrum);
      const T *ptrs = _data;
      cimg_for(res,ptrd,T) { const ulongT value = (ulongT)*(ptrs++); *ptrd = (T)~value; }
      return res;
    }

    //! Test if all pixels of an image have the same value.
    /**
       Return \c true is all pixels of the image instance are equal to the specified \c value.
       \param value Reference value to compare with.
    **/
    template<typename t>
    bool operator==(const t value) const {
      if (is_empty()) return false;
      typedef _cimg_Tt Tt;
      bool is_equal = true;
      for (T *ptrd = _data + size(); is_equal && ptrd>_data; is_equal = ((Tt)*(--ptrd)==(Tt)value)) {}
      return is_equal;
    }

    //! Test if all pixel values of an image follow a specified expression.
    /**
       Return \c true is all pixels of the image instance are equal to the specified \c expression.
       \param expression Value string describing the way pixel values are compared.
    **/
    bool operator==(const char *const expression) const {
      return *this==(+*this)._fill(expression,true,true,0,0,"operator==",this);
    }

    //! Test if two images have the same size and values.
    /**
       Return \c true if the image instance and the input image \c img have the same dimensions and pixel values,
       and \c false otherwise.
       \param img Input image to compare with.
       \note
       - The pixel buffer pointers data() of the two compared images do not have to be the same for operator==()
         to return \c true.
         Only the dimensions and the pixel values matter. Thus, the comparison can be \c true even for different
         pixel types \c T and \c t.
       \par Example
       \code
       const CImg<float> img1(1,3,1,1, 0,1,2); // Construct a 1x3 vector [0;1;2] (with 'float' pixel values).
       const CImg<char> img2(1,3,1,1, 0,1,2);  // Construct a 1x3 vector [0;1;2] (with 'char' pixel values).
       if (img1==img2) {                       // Test succeeds, image dimensions and values are the same.
         std::printf("'img1' and 'img2' have same dimensions and values.");
       }
       \endcode
    **/
    template<typename t>
    bool operator==(const CImg<t>& img) const {
      typedef _cimg_Tt Tt;
      const ulongT siz = size();
      bool is_equal = true;
      if (siz!=img.size()) return false;
      t *ptrs = img._data + siz;
      for (T *ptrd = _data + siz; is_equal && ptrd>_data; is_equal = ((Tt)*(--ptrd)==(Tt)*(--ptrs))) {}
      return is_equal;
    }

    //! Test if pixels of an image are all different from a value.
    /**
       Return \c true is all pixels of the image instance are different than the specified \c value.
       \param value Reference value to compare with.
    **/
    template<typename t>
    bool operator!=(const t value) const {
      return !((*this)==value);
    }

    //! Test if all pixel values of an image are different from a specified expression.
    /**
       Return \c true is all pixels of the image instance are different to the specified \c expression.
       \param expression Value string describing the way pixel values are compared.
    **/
    bool operator!=(const char *const expression) const {
      return !((*this)==expression);
    }

    //! Test if two images have different sizes or values.
    /**
       Return \c true if the image instance and the input image \c img have different dimensions or pixel values,
       and \c false otherwise.
       \param img Input image to compare with.
       \note
       - Writing \c img1!=img2 is equivalent to \c !(img1==img2).
    **/
    template<typename t>
    bool operator!=(const CImg<t>& img) const {
      return !((*this)==img);
    }

    //! Construct an image list from two images.
    /**
       Return a new list of image (\c CImgList instance) containing exactly two elements:
         - A copy of the image instance, at position [\c 0].
         - A copy of the specified image \c img, at position [\c 1].

       \param img Input image that will be the second image of the resulting list.
       \note
       - The family of operator,() is convenient to easily create list of images, but it is also \e quite \e slow
         in practice (see warning below).
       - Constructed lists contain no shared images. If image instance or input image \c img are shared, they are
         inserted as new non-shared copies in the resulting list.
       - The pixel type of the returned list may be a superset of the initial pixel type \c T, if necessary.
       \warning
       - Pipelining operator,() \c N times will perform \c N copies of the entire content of a (growing) image list.
         This may become very expensive in terms of speed and used memory. You should avoid using this technique to
         build a new CImgList instance from several images, if you are seeking for performance.
         Fast insertions of images in an image list are possible with
         CImgList<T>::insert(const CImg<t>&,unsigned int,bool) or move_to(CImgList<t>&,unsigned int).
       \par Example
       \code
       const CImg<float>
          img1("reference.jpg"),
          img2 = img1.get_mirror('x'),
          img3 = img2.get_blur(5);
       const CImgList<float> list = (img1,img2); // Create list of two elements from 'img1' and 'img2'.
       (list,img3).display();                    // Display image list containing copies of 'img1','img2' and 'img3'.
       \endcode
       \image html ref_operator_comma.jpg
    **/
    template<typename t>
    CImgList<_cimg_Tt> operator,(const CImg<t>& img) const {
      return CImgList<_cimg_Tt>(*this,img);
    }

    //! Construct an image list from image instance and an input image list.
    /**
       Return a new list of images (\c CImgList instance) containing exactly \c list.size() \c + \c 1 elements:
         - A copy of the image instance, at position [\c 0].
         - A copy of the specified image list \c list, from positions [\c 1] to [\c list.size()].

       \param list Input image list that will be appended to the image instance.
       \note
       - Similar to operator,(const CImg<t>&) const, except that it takes an image list as an argument.
    **/
    template<typename t>
    CImgList<_cimg_Tt> operator,(const CImgList<t>& list) const {
      return CImgList<_cimg_Tt>(list,false).insert(*this,0);
    }

    //! Split image along specified axis.
    /**
       Return a new list of images (\c CImgList instance) containing the splitted components
       of the instance image along the specified axis.
       \param axis Splitting axis (can be '\c x','\c y','\c z' or '\c c')
       \note
       - Similar to get_split(char,int) const, with default second argument.
       \par Example
       \code
       const CImg<unsigned char> img("reference.jpg"); // Load a RGB color image.
       const CImgList<unsigned char> list = (img<'c'); // Get a list of its three R,G,B channels.
       (img,list).display();
       \endcode
       \image html ref_operator_less.jpg
    **/
    CImgList<T> operator<(const char axis) const {
      return get_split(axis);
    }

    //@}
    //-------------------------------------
    //
    //! \name Instance Characteristics
    //@{
    //-------------------------------------

    //! Return the type of image pixel values as a C string.
    /**
       Return a \c char* string containing the usual type name of the image pixel values
       (i.e. a stringified version of the template parameter \c T).
       \note
       - The returned string may contain spaces (as in \c "unsigned char").
       - If the pixel type \c T does not correspond to a registered type, the string <tt>"unknown"</tt> is returned.
    **/
    static const char* pixel_type() {
      return cimg::type<T>::string();
    }

    //! Return the number of image columns.
    /**
       Return the image width, i.e. the image dimension along the X-axis.
       \note
       - The width() of an empty image is equal to \c 0.
       - width() is typically equal to \c 1 when considering images as \e vectors for matrix calculations.
       - width() returns an \c int, although the image width is internally stored as an \c unsigned \c int.
         Using an \c int is safer and prevents arithmetic traps possibly encountered when doing calculations involving
         \c unsigned \c int variables.
         Access to the initial \c unsigned \c int variable is possible (though not recommended) by
         <tt>(*this)._width</tt>.
    **/
    int width() const {
      return (int)_width;
    }

    //! Return the number of image rows.
    /**
       Return the image height, i.e. the image dimension along the Y-axis.
       \note
       - The height() of an empty image is equal to \c 0.
       - height() returns an \c int, although the image height is internally stored as an \c unsigned \c int.
         Using an \c int is safer and prevents arithmetic traps possibly encountered when doing calculations involving
         \c unsigned \c int variables.
         Access to the initial \c unsigned \c int variable is possible (though not recommended) by
         <tt>(*this)._height</tt>.
    **/
    int height() const {
      return (int)_height;
    }

    //! Return the number of image slices.
    /**
       Return the image depth, i.e. the image dimension along the Z-axis.
       \note
       - The depth() of an empty image is equal to \c 0.
       - depth() is typically equal to \c 1 when considering usual 2d images. When depth()\c > \c 1, the image
         is said to be \e volumetric.
       - depth() returns an \c int, although the image depth is internally stored as an \c unsigned \c int.
         Using an \c int is safer and prevents arithmetic traps possibly encountered when doing calculations involving
         \c unsigned \c int variables.
         Access to the initial \c unsigned \c int variable is possible (though not recommended) by
         <tt>(*this)._depth</tt>.
    **/
    int depth() const {
      return (int)_depth;
    }

    //! Return the number of image channels.
    /**
       Return the number of image channels, i.e. the image dimension along the C-axis.
       \note
       - The spectrum() of an empty image is equal to \c 0.
       - spectrum() is typically equal to \c 1 when considering scalar-valued images, to \c 3
         for RGB-coded color images, and to \c 4 for RGBA-coded color images (with alpha-channel).
         The number of channels of an image instance is not limited. The meaning of the pixel values is not linked
         up to the number of channels (e.g. a 4-channel image may indifferently stands for a RGBA or CMYK color image).
       - spectrum() returns an \c int, although the image spectrum is internally stored as an \c unsigned \c int.
         Using an \c int is safer and prevents arithmetic traps possibly encountered when doing calculations involving
         \c unsigned \c int variables.
         Access to the initial \c unsigned \c int variable is possible (though not recommended) by
         <tt>(*this)._spectrum</tt>.
    **/
    int spectrum() const {
      return (int)_spectrum;
    }

    //! Return the total number of pixel values.
    /**
       Return <tt>width()*\ref height()*\ref depth()*\ref spectrum()</tt>,
       i.e. the total number of values of type \c T in the pixel buffer of the image instance.
       \note
       - The size() of an empty image is equal to \c 0.
       - The allocated memory size for a pixel buffer of a non-shared \c CImg<T> instance is equal to
         <tt>size()*sizeof(T)</tt>.
       \par Example
       \code
       const CImg<float> img(100,100,1,3);               // Construct new 100x100 color image.
       if (img.size()==30000)                            // Test succeeds.
         std::printf("Pixel buffer uses %lu bytes",
                     img.size()*sizeof(float));
       \endcode
    **/
    ulongT size() const {
      return (ulongT)_width*_height*_depth*_spectrum;
    }

    //! Return a pointer to the first pixel value.
    /**
       Return a \c T*, or a \c const \c T* pointer to the first value in the pixel buffer of the image instance,
       whether the instance is \c const or not.
       \note
       - The data() of an empty image is equal to \c 0 (null pointer).
       - The allocated pixel buffer for the image instance starts from \c data()
         and goes to <tt>data()+\ref size() - 1</tt> (included).
       - To get the pointer to one particular location of the pixel buffer, use
         data(unsigned int,unsigned int,unsigned int,unsigned int) instead.
    **/
    T* data() {
      return _data;
    }

    //! Return a pointer to the first pixel value \const.
    const T* data() const {
      return _data;
    }

    //! Return a pointer to a located pixel value.
    /**
       Return a \c T*, or a \c const \c T* pointer to the value located at (\c x,\c y,\c z,\c c) in the pixel buffer
       of the image instance,
       whether the instance is \c const or not.
       \param x X-coordinate of the pixel value.
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \note
       - Writing \c img.data(x,y,z,c) is equivalent to <tt>&(img(x,y,z,c))</tt>. Thus, this method has the same
         properties as operator()(unsigned int,unsigned int,unsigned int,unsigned int).
     **/
#if cimg_verbosity>=3
    T *data(const unsigned int x, const unsigned int y=0, const unsigned int z=0, const unsigned int c=0) {
      const ulongT off = (ulongT)offset(x,y,z,c);
      if (off>=size())
        cimg::warn(_cimg_instance
                   "data(): Invalid pointer request, at coordinates (%u,%u,%u,%u) [offset=%u].",
                   cimg_instance,
                   x,y,z,c,off);
      return _data + off;
    }

    //! Return a pointer to a located pixel value \const.
    const T* data(const unsigned int x, const unsigned int y=0, const unsigned int z=0, const unsigned int c=0) const {
      return const_cast<CImg<T>*>(this)->data(x,y,z,c);
    }
#else
    T* data(const unsigned int x, const unsigned int y=0, const unsigned int z=0, const unsigned int c=0) {
      return _data + x + (ulongT)y*_width + (ulongT)z*_width*_height + (ulongT)c*_width*_height*_depth;
    }

    const T* data(const unsigned int x, const unsigned int y=0, const unsigned int z=0, const unsigned int c=0) const {
      return _data + x + (ulongT)y*_width + (ulongT)z*_width*_height + (ulongT)c*_width*_height*_depth;
    }
#endif

    //! Return the offset to a located pixel value, with respect to the beginning of the pixel buffer.
    /**
       \param x X-coordinate of the pixel value.
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \note
       - Writing \c img.data(x,y,z,c) is equivalent to <tt>&(img(x,y,z,c)) - img.data()</tt>.
         Thus, this method has the same properties as operator()(unsigned int,unsigned int,unsigned int,unsigned int).
       \par Example
       \code
       const CImg<float> img(100,100,1,3);      // Define a 100x100 RGB-color image.
       const long off = img.offset(10,10,0,2);  // Get the offset of the blue value of the pixel located at (10,10).
       const float val = img[off];              // Get the blue value of this pixel.
       \endcode
    **/
    longT offset(const int x, const int y=0, const int z=0, const int c=0) const {
      return x + (longT)y*_width + (longT)z*_width*_height + (longT)c*_width*_height*_depth;
    }

    //! Return a CImg<T>::iterator pointing to the first pixel value.
    /**
       \note
       - Equivalent to data().
       - It has been mainly defined for compatibility with STL naming conventions.
     **/
    iterator begin() {
      return _data;
    }

    //! Return a CImg<T>::iterator pointing to the first value of the pixel buffer \const.
    const_iterator begin() const {
      return _data;
    }

    //! Return a CImg<T>::iterator pointing next to the last pixel value.
    /**
       \note
       - Writing \c img.end() is equivalent to <tt>img.data() + img.size()</tt>.
       - It has been mainly defined for compatibility with STL naming conventions.
       \warning
       - The returned iterator actually points to a value located \e outside the acceptable bounds of the pixel buffer.
         Trying to read or write the content of the returned iterator will probably result in a crash.
         Use it mainly as a strict upper bound for a CImg<T>::iterator.
       \par Example
       \code
       CImg<float> img(100,100,1,3);                                     // Define a 100x100 RGB color image.
       for (CImg<float>::iterator it = img.begin(); it<img.end(); ++it)  // 'img.end()' used here as an upper bound for the iterator.
         *it = 0;
       \endcode
    **/
    iterator end() {
      return _data + size();
    }

    //! Return a CImg<T>::iterator pointing next to the last pixel value \const.
    const_iterator end() const {
      return _data + size();
    }

    //! Return a reference to the first pixel value.
    /**
       \note
       - Writing \c img.front() is equivalent to <tt>img[0]</tt>, or <tt>img(0,0,0,0)</tt>.
       - It has been mainly defined for compatibility with STL naming conventions.
    **/
    T& front() {
      return *_data;
    }

    //! Return a reference to the first pixel value \const.
    const T& front() const {
      return *_data;
    }

    //! Return a reference to the last pixel value.
    /**
       \note
       - Writing \c img.end() is equivalent to <tt>img[img.size() - 1]</tt>, or
         <tt>img(img.width() - 1,img.height() - 1,img.depth() - 1,img.spectrum() - 1)</tt>.
       - It has been mainly defined for compatibility with STL naming conventions.
    **/
    T& back() {
      return *(_data + size() - 1);
    }

    //! Return a reference to the last pixel value \const.
    const T& back() const {
      return *(_data + size() - 1);
    }

    //! Access to a pixel value at a specified offset, using Dirichlet boundary conditions.
    /**
       Return a reference to the pixel value of the image instance located at a specified \c offset,
       or to a specified default value in case of out-of-bounds access.
       \param offset Offset to the desired pixel value.
       \param out_value Default value returned if \c offset is outside image bounds.
       \note
       - Writing \c img.at(offset,out_value) is similar to <tt>img[offset]</tt>, except that if \c offset
         is outside bounds (e.g. \c offset<0 or \c offset>=img.size()), a reference to a value \c out_value
         is safely returned instead.
       - Due to the additional boundary checking operation, this method is slower than operator()(). Use it when
         you are \e not sure about the validity of the specified pixel offset.
    **/
    T& at(const int offset, const T& out_value) {
      return (offset<0 || offset>=(int)size())?(cimg::temporary(out_value)=out_value):(*this)[offset];
    }

    //! Access to a pixel value at a specified offset, using Dirichlet boundary conditions \const.
    T at(const int offset, const T& out_value) const {
      return (offset<0 || offset>=(int)size())?out_value:(*this)[offset];
    }

    //! Access to a pixel value at a specified offset, using Neumann boundary conditions.
    /**
       Return a reference to the pixel value of the image instance located at a specified \c offset,
       or to the nearest pixel location in the image instance in case of out-of-bounds access.
       \param offset Offset to the desired pixel value.
       \note
       - Similar to at(int,const T), except that an out-of-bounds access returns the value of the
         nearest pixel in the image instance, regarding the specified offset, i.e.
         - If \c offset<0, then \c img[0] is returned.
         - If \c offset>=img.size(), then \c img[img.size() - 1] is returned.
       - Due to the additional boundary checking operation, this method is slower than operator()(). Use it when
         you are \e not sure about the validity of the specified pixel offset.
       - If you know your image instance is \e not empty, you may rather use the slightly faster method \c _at(int).
     **/
    T& at(const int offset) {
      if (is_empty())
        throw CImgInstanceException(_cimg_instance
                                    "at(): Empty instance.",
                                    cimg_instance);
      return _at(offset);
    }

    T& _at(const int offset) {
      const unsigned int siz = (unsigned int)size();
      return (*this)[offset<0?0:(unsigned int)offset>=siz?siz - 1:offset];
    }

    //! Access to a pixel value at a specified offset, using Neumann boundary conditions \const.
    const T& at(const int offset) const {
      if (is_empty())
        throw CImgInstanceException(_cimg_instance
                                    "at(): Empty instance.",
                                    cimg_instance);
      return _at(offset);
    }

    const T& _at(const int offset) const {
      const unsigned int siz = (unsigned int)size();
      return (*this)[offset<0?0:(unsigned int)offset>=siz?siz - 1:offset];
    }

    //! Access to a pixel value, using Dirichlet boundary conditions for the X-coordinate.
    /**
       Return a reference to the pixel value of the image instance located at (\c x,\c y,\c z,\c c),
       or to a specified default value in case of out-of-bounds access along the X-axis.
       \param x X-coordinate of the pixel value.
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \param out_value Default value returned if \c (\c x,\c y,\c z,\c c) is outside image bounds.
       \note
       - Similar to operator()(), except that an out-of-bounds access along the X-axis returns the specified value
         \c out_value.
       - Due to the additional boundary checking operation, this method is slower than operator()(). Use it when
         you are \e not sure about the validity of the specified pixel coordinates.
       \warning
       - There is \e no boundary checking performed for the Y,Z and C-coordinates, so they must be inside image bounds.
    **/
    T& atX(const int x, const int y, const int z, const int c, const T& out_value) {
      return (x<0 || x>=width())?(cimg::temporary(out_value)=out_value):(*this)(x,y,z,c);
    }

    //! Access to a pixel value, using Dirichlet boundary conditions for the X-coordinate \const.
    T atX(const int x, const int y, const int z, const int c, const T& out_value) const {
      return (x<0 || x>=width())?out_value:(*this)(x,y,z,c);
    }

    //! Access to a pixel value, using Neumann boundary conditions for the X-coordinate.
    /**
       Return a reference to the pixel value of the image instance located at (\c x,\c y,\c z,\c c),
       or to the nearest pixel location in the image instance in case of out-of-bounds access along the X-axis.
       \param x X-coordinate of the pixel value.
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \note
       - Similar to at(int,int,int,int,const T), except that an out-of-bounds access returns the value of the
         nearest pixel in the image instance, regarding the specified X-coordinate.
       - Due to the additional boundary checking operation, this method is slower than operator()(). Use it when
         you are \e not sure about the validity of the specified pixel coordinates.
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _at(int,int,int,int).
       \warning
       - There is \e no boundary checking performed for the Y,Z and C-coordinates, so they must be inside image bounds.
     **/
    T& atX(const int x, const int y=0, const int z=0, const int c=0) {
      if (is_empty())
        throw CImgInstanceException(_cimg_instance
                                    "atX(): Empty instance.",
                                    cimg_instance);
      return _atX(x,y,z,c);
    }

    T& _atX(const int x, const int y=0, const int z=0, const int c=0) {
      return (*this)(x<0?0:(x>=width()?width() - 1:x),y,z,c);
    }

    //! Access to a pixel value, using Neumann boundary conditions for the X-coordinate \const.
    const T& atX(const int x, const int y=0, const int z=0, const int c=0) const {
      if (is_empty())
        throw CImgInstanceException(_cimg_instance
                                    "atX(): Empty instance.",
                                    cimg_instance);
      return _atX(x,y,z,c);
    }

    const T& _atX(const int x, const int y=0, const int z=0, const int c=0) const {
      return (*this)(x<0?0:(x>=width()?width() - 1:x),y,z,c);
    }

    //! Access to a pixel value, using Dirichlet boundary conditions for the X and Y-coordinates.
    /**
       Similar to atX(int,int,int,int,const T), except that boundary checking is performed both on X and Y-coordinates.
    **/
    T& atXY(const int x, const int y, const int z, const int c, const T& out_value) {
      return (x<0 || y<0 || x>=width() || y>=height())?(cimg::temporary(out_value)=out_value):(*this)(x,y,z,c);
    }

    //! Access to a pixel value, using Dirichlet boundary conditions for the X and Y coordinates \const.
    T atXY(const int x, const int y, const int z, const int c, const T& out_value) const {
      return (x<0 || y<0 || x>=width() || y>=height())?out_value:(*this)(x,y,z,c);
    }

    //! Access to a pixel value, using Neumann boundary conditions for the X and Y-coordinates.
    /**
       Similar to atX(int,int,int,int), except that boundary checking is performed both on X and Y-coordinates.
       \note
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _atXY(int,int,int,int).
     **/
    T& atXY(const int x, const int y, const int z=0, const int c=0) {
      if (is_empty())
        throw CImgInstanceException(_cimg_instance
                                    "atXY(): Empty instance.",
                                    cimg_instance);
      return _atXY(x,y,z,c);
    }

    T& _atXY(const int x, const int y, const int z=0, const int c=0) {
      return (*this)(x<0?0:(x>=width()?width() - 1:x), y<0?0:(y>=height()?height() - 1:y),z,c);
    }

    //! Access to a pixel value, using Neumann boundary conditions for the X and Y-coordinates \const.
    const T& atXY(const int x, const int y, const int z=0, const int c=0) const {
      if (is_empty())
        throw CImgInstanceException(_cimg_instance
                                    "atXY(): Empty instance.",
                                    cimg_instance);
      return _atXY(x,y,z,c);
    }

    const T& _atXY(const int x, const int y, const int z=0, const int c=0) const {
      return (*this)(x<0?0:(x>=width()?width() - 1:x), y<0?0:(y>=height()?height() - 1:y),z,c);
    }

    //! Access to a pixel value, using Dirichlet boundary conditions for the X,Y and Z-coordinates.
    /**
       Similar to atX(int,int,int,int,const T), except that boundary checking is performed both on
       X,Y and Z-coordinates.
    **/
    T& atXYZ(const int x, const int y, const int z, const int c, const T& out_value) {
      return (x<0 || y<0 || z<0 || x>=width() || y>=height() || z>=depth())?
        (cimg::temporary(out_value)=out_value):(*this)(x,y,z,c);
    }

    //! Access to a pixel value, using Dirichlet boundary conditions for the X,Y and Z-coordinates \const.
    T atXYZ(const int x, const int y, const int z, const int c, const T& out_value) const {
      return (x<0 || y<0 || z<0 || x>=width() || y>=height() || z>=depth())?out_value:(*this)(x,y,z,c);
    }

    //! Access to a pixel value, using Neumann boundary conditions for the X,Y and Z-coordinates.
    /**
       Similar to atX(int,int,int,int), except that boundary checking is performed both on X,Y and Z-coordinates.
       \note
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _atXYZ(int,int,int,int).
    **/
    T& atXYZ(const int x, const int y, const int z, const int c=0) {
      if (is_empty())
        throw CImgInstanceException(_cimg_instance
                                    "atXYZ(): Empty instance.",
                                    cimg_instance);
      return _atXYZ(x,y,z,c);
    }

    T& _atXYZ(const int x, const int y, const int z, const int c=0) {
      return (*this)(x<0?0:x>=width()?width() - 1:x,y<0?0:y>=height()?height() - 1:y,
                     z<0?0:z>=depth()?depth() - 1:z,c);
    }

    //! Access to a pixel value, using Neumann boundary conditions for the X,Y and Z-coordinates \const.
    const T& atXYZ(const int x, const int y, const int z, const int c=0) const {
      if (is_empty())
        throw CImgInstanceException(_cimg_instance
                                    "atXYZ(): Empty instance.",
                                    cimg_instance);
      return _atXYZ(x,y,z,c);
    }

    const T& _atXYZ(const int x, const int y, const int z, const int c=0) const {
      return (*this)(x<0?0:(x>=width()?width() - 1:x),y<0?0:(y>=height()?height() - 1:y),
                     z<0?0:(z>=depth()?depth() - 1:z),c);
    }

    //! Access to a pixel value, using Dirichlet boundary conditions.
    /**
       Similar to atX(int,int,int,int,const T), except that boundary checking is performed on all
       X,Y,Z and C-coordinates.
    **/
    T& atXYZC(const int x, const int y, const int z, const int c, const T& out_value) {
      return (x<0 || y<0 || z<0 || c<0 || x>=width() || y>=height() || z>=depth() || c>=spectrum())?
        (cimg::temporary(out_value)=out_value):(*this)(x,y,z,c);
    }

    //! Access to a pixel value, using Dirichlet boundary conditions \const.
    T atXYZC(const int x, const int y, const int z, const int c, const T& out_value) const {
      return (x<0 || y<0 || z<0 || c<0 || x>=width() || y>=height() || z>=depth() || c>=spectrum())?out_value:
        (*this)(x,y,z,c);
    }

    //! Access to a pixel value, using Neumann boundary conditions.
    /**
       Similar to atX(int,int,int,int), except that boundary checking is performed on all X,Y,Z and C-coordinates.
       \note
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _atXYZC(int,int,int,int).
    **/
    T& atXYZC(const int x, const int y, const int z, const int c) {
      if (is_empty())
        throw CImgInstanceException(_cimg_instance
                                    "atXYZC(): Empty instance.",
                                    cimg_instance);
      return _atXYZC(x,y,z,c);
    }

    T& _atXYZC(const int x, const int y, const int z, const int c) {
      return (*this)(x<0?0:(x>=width()?width() - 1:x), y<0?0:(y>=height()?height() - 1:y),
                     z<0?0:(z>=depth()?depth() - 1:z), c<0?0:(c>=spectrum()?spectrum() - 1:c));
    }

    //! Access to a pixel value, using Neumann boundary conditions \const.
    const T& atXYZC(const int x, const int y, const int z, const int c) const {
      if (is_empty())
        throw CImgInstanceException(_cimg_instance
                                    "atXYZC(): Empty instance.",
                                    cimg_instance);
      return _atXYZC(x,y,z,c);
    }

    const T& _atXYZC(const int x, const int y, const int z, const int c) const {
      return (*this)(x<0?0:(x>=width()?width() - 1:x), y<0?0:(y>=height()?height() - 1:y),
                     z<0?0:(z>=depth()?depth() - 1:z), c<0?0:(c>=spectrum()?spectrum() - 1:c));
    }

    //! Return pixel value, using linear interpolation and Dirichlet boundary conditions for the X-coordinate.
    /**
       Return a linearly-interpolated pixel value of the image instance located at (\c fx,\c y,\c z,\c c),
       or a specified default value in case of out-of-bounds access along the X-axis.
       \param fx X-coordinate of the pixel value (float-valued).
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \param out_value Default value returned if \c (\c fx,\c y,\c z,\c c) is outside image bounds.
       \note
       - Similar to atX(int,int,int,int,const T), except that the returned pixel value is approximated by
         a linear interpolation along the X-axis, if corresponding coordinates are not integers.
       - The type of the returned pixel value is extended to \c float, if the pixel type \c T is not float-valued.
       \warning
       - There is \e no boundary checking performed for the Y,Z and C-coordinates, so they must be inside image bounds.
    **/
    Tfloat linear_atX(const float fx, const int y, const int z, const int c, const T& out_value) const {
      const int
        x = (int)fx - (fx>=0?0:1), nx = x + 1;
      const float
        dx = fx - x;
      const Tfloat
        Ic = (Tfloat)atX(x,y,z,c,out_value), In = (Tfloat)atXY(nx,y,z,c,out_value);
      return Ic + dx*(In - Ic);
    }

    //! Return pixel value, using linear interpolation and Neumann boundary conditions for the X-coordinate.
    /**
       Return a linearly-interpolated pixel value of the image instance located at (\c fx,\c y,\c z,\c c),
       or the value of the nearest pixel location in the image instance in case of out-of-bounds access along
       the X-axis.
       \param fx X-coordinate of the pixel value (float-valued).
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \note
       - Similar to linear_atX(float,int,int,int,const T) const, except that an out-of-bounds access returns
         the value of the nearest pixel in the image instance, regarding the specified X-coordinate.
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _linear_atX(float,int,int,int).
       \warning
       - There is \e no boundary checking performed for the Y,Z and C-coordinates, so they must be inside image bounds.
    **/
    Tfloat linear_atX(const float fx, const int y=0, const int z=0, const int c=0) const {
      if (is_empty())
        throw CImgInstanceException(_cimg_instance
                                    "linear_atX(): Empty instance.",
                                    cimg_instance);

      return _linear_atX(fx,y,z,c);
    }

    Tfloat _linear_atX(const float fx, const int y=0, const int z=0, const int c=0) const {
      const float
        nfx = fx<0?0:(fx>_width - 1?_width - 1:fx);
      const unsigned int
        x = (unsigned int)nfx;
      const float
        dx = nfx - x;
      const unsigned int
        nx = dx>0?x + 1:x;
      const Tfloat
        Ic = (Tfloat)(*this)(x,y,z,c), In = (Tfloat)(*this)(nx,y,z,c);
      return Ic + dx*(In - Ic);
    }

    //! Return pixel value, using linear interpolation and Dirichlet boundary conditions for the X and Y-coordinates.
    /**
       Similar to linear_atX(float,int,int,int,const T) const, except that the linear interpolation and the
       boundary checking are achieved both for X and Y-coordinates.
    **/
    Tfloat linear_atXY(const float fx, const float fy, const int z, const int c, const T& out_value) const {
      const int
        x = (int)fx - (fx>=0?0:1), nx = x + 1,
        y = (int)fy - (fy>=0?0:1), ny = y + 1;
      const float
        dx = fx - x,
        dy = fy - y;
      const Tfloat
        Icc = (Tfloat)atXY(x,y,z,c,out_value),  Inc = (Tfloat)atXY(nx,y,z,c,out_value),
        Icn = (Tfloat)atXY(x,ny,z,c,out_value), Inn = (Tfloat)atXY(nx,ny,z,c,out_value);
      return Icc + dx*(Inc - Icc + dy*(Icc + Inn - Icn - Inc)) + dy*(Icn - Icc);
    }

    //! Return pixel value, using linear interpolation and Neumann boundary conditions for the X and Y-coordinates.
    /**
       Similar to linear_atX(float,int,int,int) const, except that the linear interpolation and the boundary checking
       are achieved both for X and Y-coordinates.
       \note
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _linear_atXY(float,float,int,int).
    **/
    Tfloat linear_atXY(const float fx, const float fy, const int z=0, const int c=0) const {
      if (is_empty())
        throw CImgInstanceException(_cimg_instance
                                    "linear_atXY(): Empty instance.",
                                    cimg_instance);

      return _linear_atXY(fx,fy,z,c);
    }

    Tfloat _linear_atXY(const float fx, const float fy, const int z=0, const int c=0) const {
      const float
        nfx = fx<0?0:(fx>_width - 1?_width - 1:fx),
        nfy = fy<0?0:(fy>_height - 1?_height - 1:fy);
      const unsigned int
        x = (unsigned int)nfx,
        y = (unsigned int)nfy;
      const float
        dx = nfx - x,
        dy = nfy - y;
      const unsigned int
        nx = dx>0?x + 1:x,
        ny = dy>0?y + 1:y;
      const Tfloat
        Icc = (Tfloat)(*this)(x,y,z,c),  Inc = (Tfloat)(*this)(nx,y,z,c),
        Icn = (Tfloat)(*this)(x,ny,z,c), Inn = (Tfloat)(*this)(nx,ny,z,c);
      return Icc + dx*(Inc - Icc + dy*(Icc + Inn - Icn - Inc)) + dy*(Icn - Icc);
    }

    //! Return pixel value, using linear interpolation and Dirichlet boundary conditions for the X,Y and Z-coordinates.
    /**
       Similar to linear_atX(float,int,int,int,const T) const, except that the linear interpolation and the
       boundary checking are achieved both for X,Y and Z-coordinates.
    **/
    Tfloat linear_atXYZ(const float fx, const float fy, const float fz, const int c, const T& out_value) const {
      const int
        x = (int)fx - (fx>=0?0:1), nx = x + 1,
        y = (int)fy - (fy>=0?0:1), ny = y + 1,
        z = (int)fz - (fz>=0?0:1), nz = z + 1;
      const float
        dx = fx - x,
        dy = fy - y,
        dz = fz - z;
      const Tfloat
        Iccc = (Tfloat)atXYZ(x,y,z,c,out_value), Incc = (Tfloat)atXYZ(nx,y,z,c,out_value),
        Icnc = (Tfloat)atXYZ(x,ny,z,c,out_value), Innc = (Tfloat)atXYZ(nx,ny,z,c,out_value),
        Iccn = (Tfloat)atXYZ(x,y,nz,c,out_value), Incn = (Tfloat)atXYZ(nx,y,nz,c,out_value),
        Icnn = (Tfloat)atXYZ(x,ny,nz,c,out_value), Innn = (Tfloat)atXYZ(nx,ny,nz,c,out_value);
      return Iccc +
        dx*(Incc - Iccc +
            dy*(Iccc + Innc - Icnc - Incc +
                dz*(Iccn + Innn + Icnc + Incc - Icnn - Incn - Iccc - Innc)) +
            dz*(Iccc + Incn - Iccn - Incc)) +
        dy*(Icnc - Iccc +
            dz*(Iccc + Icnn - Iccn - Icnc)) +
        dz*(Iccn - Iccc);
    }

    //! Return pixel value, using linear interpolation and Neumann boundary conditions for the X,Y and Z-coordinates.
    /**
       Similar to linear_atX(float,int,int,int) const, except that the linear interpolation and the boundary checking
       are achieved both for X,Y and Z-coordinates.
       \note
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _linear_atXYZ(float,float,float,int).
    **/
    Tfloat linear_atXYZ(const float fx, const float fy=0, const float fz=0, const int c=0) const {
      if (is_empty())
        throw CImgInstanceException(_cimg_instance
                                    "linear_atXYZ(): Empty instance.",
                                    cimg_instance);

      return _linear_atXYZ(fx,fy,fz,c);
    }

    Tfloat _linear_atXYZ(const float fx, const float fy=0, const float fz=0, const int c=0) const {
      const float
        nfx = fx<0?0:(fx>_width - 1?_width - 1:fx),
        nfy = fy<0?0:(fy>_height - 1?_height - 1:fy),
        nfz = fz<0?0:(fz>_depth - 1?_depth - 1:fz);
      const unsigned int
        x = (unsigned int)nfx,
        y = (unsigned int)nfy,
        z = (unsigned int)nfz;
      const float
        dx = nfx - x,
        dy = nfy - y,
        dz = nfz - z;
      const unsigned int
        nx = dx>0?x + 1:x,
        ny = dy>0?y + 1:y,
        nz = dz>0?z + 1:z;
      const Tfloat
        Iccc = (Tfloat)(*this)(x,y,z,c), Incc = (Tfloat)(*this)(nx,y,z,c),
        Icnc = (Tfloat)(*this)(x,ny,z,c), Innc = (Tfloat)(*this)(nx,ny,z,c),
        Iccn = (Tfloat)(*this)(x,y,nz,c), Incn = (Tfloat)(*this)(nx,y,nz,c),
        Icnn = (Tfloat)(*this)(x,ny,nz,c), Innn = (Tfloat)(*this)(nx,ny,nz,c);
      return Iccc +
        dx*(Incc - Iccc +
            dy*(Iccc + Innc - Icnc - Incc +
                dz*(Iccn + Innn + Icnc + Incc - Icnn - Incn - Iccc - Innc)) +
            dz*(Iccc + Incn - Iccn - Incc)) +
        dy*(Icnc - Iccc +
            dz*(Iccc + Icnn - Iccn - Icnc)) +
        dz*(Iccn - Iccc);
    }

    //! Return pixel value, using linear interpolation and Dirichlet boundary conditions for all X,Y,Z,C-coordinates.
    /**
       Similar to linear_atX(float,int,int,int,const T) const, except that the linear interpolation and the
       boundary checking are achieved for all X,Y,Z and C-coordinates.
    **/
    Tfloat linear_atXYZC(const float fx, const float fy, const float fz, const float fc, const T& out_value) const {
      const int
        x = (int)fx - (fx>=0?0:1), nx = x + 1,
        y = (int)fy - (fy>=0?0:1), ny = y + 1,
        z = (int)fz - (fz>=0?0:1), nz = z + 1,
        c = (int)fc - (fc>=0?0:1), nc = c + 1;
      const float
        dx = fx - x,
        dy = fy - y,
        dz = fz - z,
        dc = fc - c;
      const Tfloat
        Icccc = (Tfloat)atXYZC(x,y,z,c,out_value), Inccc = (Tfloat)atXYZC(nx,y,z,c,out_value),
        Icncc = (Tfloat)atXYZC(x,ny,z,c,out_value), Inncc = (Tfloat)atXYZC(nx,ny,z,c,out_value),
        Iccnc = (Tfloat)atXYZC(x,y,nz,c,out_value), Incnc = (Tfloat)atXYZC(nx,y,nz,c,out_value),
        Icnnc = (Tfloat)atXYZC(x,ny,nz,c,out_value), Innnc = (Tfloat)atXYZC(nx,ny,nz,c,out_value),
        Icccn = (Tfloat)atXYZC(x,y,z,nc,out_value), Inccn = (Tfloat)atXYZC(nx,y,z,nc,out_value),
        Icncn = (Tfloat)atXYZC(x,ny,z,nc,out_value), Inncn = (Tfloat)atXYZC(nx,ny,z,nc,out_value),
        Iccnn = (Tfloat)atXYZC(x,y,nz,nc,out_value), Incnn = (Tfloat)atXYZC(nx,y,nz,nc,out_value),
        Icnnn = (Tfloat)atXYZC(x,ny,nz,nc,out_value), Innnn = (Tfloat)atXYZC(nx,ny,nz,nc,out_value);
      return Icccc +
        dx*(Inccc - Icccc +
            dy*(Icccc + Inncc - Icncc - Inccc +
                dz*(Iccnc + Innnc + Icncc + Inccc - Icnnc - Incnc - Icccc - Inncc +
                    dc*(Iccnn + Innnn + Icncn + Inccn + Icnnc + Incnc + Icccc + Inncc -
                        Icnnn - Incnn - Icccn - Inncn - Iccnc - Innnc - Icncc - Inccc)) +
                dc*(Icccn + Inncn + Icncc + Inccc - Icncn - Inccn - Icccc - Inncc)) +
            dz*(Icccc + Incnc - Iccnc - Inccc +
                dc*(Icccn + Incnn + Iccnc + Inccc - Iccnn - Inccn - Icccc - Incnc)) +
            dc*(Icccc + Inccn - Inccc - Icccn)) +
        dy*(Icncc - Icccc +
            dz*(Icccc + Icnnc - Iccnc - Icncc +
                dc*(Icccn + Icnnn + Iccnc + Icncc - Iccnn - Icncn - Icccc - Icnnc)) +
            dc*(Icccc + Icncn - Icncc - Icccn)) +
        dz*(Iccnc - Icccc +
            dc*(Icccc + Iccnn - Iccnc - Icccn)) +
        dc*(Icccn  -Icccc);
    }

    //! Return pixel value, using linear interpolation and Neumann boundary conditions for all X,Y,Z and C-coordinates.
    /**
       Similar to linear_atX(float,int,int,int) const, except that the linear interpolation and the boundary checking
       are achieved for all X,Y,Z and C-coordinates.
       \note
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _linear_atXYZC(float,float,float,float).
    **/
    Tfloat linear_atXYZC(const float fx, const float fy=0, const float fz=0, const float fc=0) const {
      if (is_empty())
        throw CImgInstanceException(_cimg_instance
                                    "linear_atXYZC(): Empty instance.",
                                    cimg_instance);

      return _linear_atXYZC(fx,fy,fz,fc);
    }

    Tfloat _linear_atXYZC(const float fx, const float fy=0, const float fz=0, const float fc=0) const {
      const float
        nfx = fx<0?0:(fx>_width - 1?_width - 1:fx),
        nfy = fy<0?0:(fy>_height - 1?_height - 1:fy),
        nfz = fz<0?0:(fz>_depth - 1?_depth - 1:fz),
        nfc = fc<0?0:(fc>_spectrum - 1?_spectrum - 1:fc);
      const unsigned int
        x = (unsigned int)nfx,
        y = (unsigned int)nfy,
        z = (unsigned int)nfz,
        c = (unsigned int)nfc;
      const float
        dx = nfx - x,
        dy = nfy - y,
        dz = nfz - z,
        dc = nfc - c;
      const unsigned int
        nx = dx>0?x + 1:x,
        ny = dy>0?y + 1:y,
        nz = dz>0?z + 1:z,
        nc = dc>0?c + 1:c;
      const Tfloat
        Icccc = (Tfloat)(*this)(x,y,z,c), Inccc = (Tfloat)(*this)(nx,y,z,c),
        Icncc = (Tfloat)(*this)(x,ny,z,c), Inncc = (Tfloat)(*this)(nx,ny,z,c),
        Iccnc = (Tfloat)(*this)(x,y,nz,c), Incnc = (Tfloat)(*this)(nx,y,nz,c),
        Icnnc = (Tfloat)(*this)(x,ny,nz,c), Innnc = (Tfloat)(*this)(nx,ny,nz,c),
        Icccn = (Tfloat)(*this)(x,y,z,nc), Inccn = (Tfloat)(*this)(nx,y,z,nc),
        Icncn = (Tfloat)(*this)(x,ny,z,nc), Inncn = (Tfloat)(*this)(nx,ny,z,nc),
        Iccnn = (Tfloat)(*this)(x,y,nz,nc), Incnn = (Tfloat)(*this)(nx,y,nz,nc),
        Icnnn = (Tfloat)(*this)(x,ny,nz,nc), Innnn = (Tfloat)(*this)(nx,ny,nz,nc);
      return Icccc +
        dx*(Inccc - Icccc +
            dy*(Icccc + Inncc - Icncc - Inccc +
                dz*(Iccnc + Innnc + Icncc + Inccc - Icnnc - Incnc - Icccc - Inncc +
                    dc*(Iccnn + Innnn + Icncn + Inccn + Icnnc + Incnc + Icccc + Inncc -
                        Icnnn - Incnn - Icccn - Inncn - Iccnc - Innnc - Icncc - Inccc)) +
                dc*(Icccn + Inncn + Icncc + Inccc - Icncn - Inccn - Icccc - Inncc)) +
            dz*(Icccc + Incnc - Iccnc - Inccc +
                dc*(Icccn + Incnn + Iccnc + Inccc - Iccnn - Inccn - Icccc - Incnc)) +
            dc*(Icccc + Inccn - Inccc - Icccn)) +
        dy*(Icncc - Icccc +
            dz*(Icccc + Icnnc - Iccnc - Icncc +
                dc*(Icccn + Icnnn + Iccnc + Icncc - Iccnn - Icncn - Icccc - Icnnc)) +
            dc*(Icccc + Icncn - Icncc - Icccn)) +
        dz*(Iccnc - Icccc +
            dc*(Icccc + Iccnn - Iccnc - Icccn)) +
        dc*(Icccn - Icccc);
    }

    //! Return pixel value, using cubic interpolation and Dirichlet boundary conditions for the X-coordinate.
    /**
       Return a cubicly-interpolated pixel value of the image instance located at (\c fx,\c y,\c z,\c c),
       or a specified default value in case of out-of-bounds access along the X-axis.
       The cubic interpolation uses Hermite splines.
       \param fx d X-coordinate of the pixel value (float-valued).
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \param out_value Default value returned if \c (\c fx,\c y,\c z,\c c) is outside image bounds.
       \note
       - Similar to linear_atX(float,int,int,int,const T) const, except that the returned pixel value is
         approximated by a \e cubic interpolation along the X-axis.
       - The type of the returned pixel value is extended to \c float, if the pixel type \c T is not float-valued.
       \warning
       - There is \e no boundary checking performed for the Y,Z and C-coordinates, so they must be inside image bounds.
    **/
    Tfloat cubic_atX(const float fx, const int y, const int z, const int c, const T& out_value) const {
      const int
        x = (int)fx - (fx>=0?0:1), px = x - 1, nx = x + 1, ax = x + 2;
      const float
        dx = fx - x;
      const Tfloat
        Ip = (Tfloat)atX(px,y,z,c,out_value), Ic = (Tfloat)atX(x,y,z,c,out_value),
        In = (Tfloat)atX(nx,y,z,c,out_value), Ia = (Tfloat)atX(ax,y,z,c,out_value);
      return Ic + 0.5f*(dx*(-Ip + In) + dx*dx*(2*Ip - 5*Ic + 4*In - Ia) + dx*dx*dx*(-Ip + 3*Ic - 3*In + Ia));
    }

    //! Return damped pixel value, using cubic interpolation and Dirichlet boundary conditions for the X-coordinate.
    /**
       Similar to cubic_atX(float,int,int,int,const T) const, except that you can specify the authorized minimum
       and maximum of the returned value.
    **/
    Tfloat cubic_atX(const float fx, const int y, const int z, const int c, const T& out_value,
                     const Tfloat min_value, const Tfloat max_value) const {
      const Tfloat val = cubic_atX(fx,y,z,c,out_value);
      return val<min_value?min_value:val>max_value?max_value:val;
    }

    //! Return pixel value, using cubic interpolation and Neumann boundary conditions for the X-coordinate.
    /**
       Return a cubicly-interpolated pixel value of the image instance located at (\c fx,\c y,\c z,\c c),
       or the value of the nearest pixel location in the image instance in case of out-of-bounds access
       along the X-axis. The cubic interpolation uses Hermite splines.
       \param fx X-coordinate of the pixel value (float-valued).
       \param y Y-coordinate of the pixel value.
       \param z Z-coordinate of the pixel value.
       \param c C-coordinate of the pixel value.
       \note
       - Similar to cubic_atX(float,int,int,int,const T) const, except that the returned pixel value is
         approximated by a cubic interpolation along the X-axis.
       - If you know your image instance is \e not empty, you may rather use the slightly faster method
         \c _cubic_atX(float,int,int,int).
       \warning
       - There is \e no boundary checking performed for the Y,Z and C-coordinates, so