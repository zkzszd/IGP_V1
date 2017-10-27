#pragma once

// NanoJPEG -- KeyJ's Tiny Baseline JPEG Decoder
// version 1.1 (2010-03-05)
// by Martin J. Fiedler <martin.fiedler@gmx.net>
//
// This software is published under the terms of KeyJ's Research License,
// version 0.2. Usage of this software is subject to the following conditions:
// 0. There's no warranty whatsoever. The author(s) of this software can not
//    be held liable for any damages that occur when using this software.
// 1. This software may be used freely for both non-commercial and commercial
//    purposes.
// 2. This software may be redistributed freely as long as no fees are charged
//    for the distribution and this license information is included.
// 3. This software may be modified freely except for this license information,
//    which must not be changed in any way.
// 4. If anything other than configuration, indentation or comments have been
//    altered in the code, the original author(s) must receive a copy of the
//    modified code.

// Altered by Nilesh Patel to allow decoding of individual colour (r, g, b) channels

///////////////////////////////////////////////////////////////////////////////
// DOCUMENTATION SECTION                                                     //
// read this if you want to know what this is all about                      //
///////////////////////////////////////////////////////////////////////////////

// INTRODUCTION
// ============
//
// This is a minimal decoder for baseline JPEG images. It accepts memory dumps
// of JPEG files as input and generates either 8-bit grayscale or packed 24-bit
// RGB images as output. It does not parse JFIF or Exif headers; all JPEG files
// are assumed to be either grayscale or YCbCr. CMYK or other color spaces are
// not supported. All YCbCr subsampling schemes with power-of-two ratios are
// supported, as are restart intervals. Progressive or lossless JPEG is not
// supported.
// Summed up, NanoJPEG should be able to decode all images from digital cameras
// and most common forms of other non-progressive JPEG images.
// The decoder is not optimized for speed, it's optimized for simplicity and
// small code. Image quality should be at a reasonable level. A bicubic chroma
// upsampling filter ensures that subsampled YCbCr images are rendered in
// decent quality. The decoder is not meant to deal with broken JPEG files in
// a graceful manner; if anything is wrong with the bitstream, decoding will
// simply fail.
// The code should work with every modern C compiler without problems and
// should not emit any warnings. It uses only (at least) 32-bit integer
// arithmetic and is supposed to be endianness independent and 64-bit clean.
// However, it is not thread-safe.


// COMPILE-TIME CONFIGURATION
// ==========================
//
// The following aspects of NanoJPEG can be controlled with preprocessor
// defines:
//
// _NJ_EXAMPLE_PROGRAM     = Compile a main() function with an example
//                           program.
// _NJ_INCLUDE_HEADER_ONLY = Don't compile anything, just act as a header
//                           file for NanoJPEG. Example:
//                               #define _NJ_INCLUDE_HEADER_ONLY
//                               #include "nanojpeg.c"
//                               int main(void) {
//                                   njInit();
//                                   // your code here
//                                   njDone();
//                               }
// NJ_USE_LIBC=1           = Use the malloc(), free(), memset() and memcpy()
//                           functions from the standard C library (default).
// NJ_USE_LIBC=0           = Don't use the standard C library. In this mode,
//                           external functions njAlloc(), njFreeMem(),
//                           njFillMem() and njCopyMem() need to be defined
//                           and implemented somewhere.
// NJ_USE_WIN32=0          = Normal mode (default).
// NJ_USE_WIN32=1          = If compiling with MSVC for Win32 and
//                           NJ_USE_LIBC=0, NanoJPEG will use its own
//                           implementations of the required C library
//                           functions (default if compiling with MSVC and
//                           NJ_USE_LIBC=0).
// NJ_CHROMA_FILTER=1      = Use the bicubic chroma upsampling filter
//                           (default).
// NJ_CHROMA_FILTER=0      = Use simple pixel repetition for chroma upsampling
//                           (bad quality, but faster and less code).


// API
// ===
//
// For API documentation, read the "header section" below.


// EXAMPLE
// =======
//
// A few pages below, you can find an example program that uses NanoJPEG to
// convert JPEG files into PGM or PPM. To compile it, use something like
//     gcc -O3 -D_NJ_EXAMPLE_PROGRAM -o nanojpeg nanojpeg.c
// You may also add -std=c99 -Wall -Wextra -pedantic -Werror, if you want :)


///////////////////////////////////////////////////////////////////////////////
// HEADER SECTION                                                            //
// copy and pase this into nanojpeg.h if you want                            //
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CONFIGURATION SECTION                                                     //
// adjust the default settings for the NJ_ defines here                      //
///////////////////////////////////////////////////////////////////////////////


//int main(int argc, char* argv[]) {
//	int size;
//	char *buf;
//	FILE *f;
//
//	if (argc < 2) {
//		printf("Usage: %s <input.jpg> [<output.ppm>]\n", argv[0]);
//		return 2;
//	}
//	f = fopen(argv[1], "rb");
//	if (!f) {
//		printf("Error opening the input file.\n");
//		return 1;
//	}
//	fseek(f, 0, SEEK_END);
//	size = (int)ftell(f);
//	buf = malloc(size);
//	fseek(f, 0, SEEK_SET);
//	size = (int)fread(buf, 1, size, f);
//	fclose(f);
//
//	njInit();
//	if (njDecode(buf, size)) {
//		printf("Error decoding the input file.\n");
//		return 1;
//	}
//
//	f = fopen((argc > 2) ? argv[2] : (njIsColor() ? "nanojpeg_out.ppm" : "nanojpeg_out.pgm"), "wb");
//	if (!f) {
//		printf("Error opening the output file.\n");
//		return 1;
//	}
//	fprintf(f, "P%d\n%d %d\n255\n", njIsColor() ? 6 : 5, njGetWidth(), njGetHeight());
//	fwrite(njGetImage(), 1, njGetImageSize(), f);
//	fclose(f);
//	njDone();
//	return 0;
//}

#ifndef NJ_USE_LIBC
#define NJ_USE_LIBC 1
#endif

#ifndef NJ_USE_WIN32
#ifdef _MSC_VER
#define NJ_USE_WIN32 (!NJ_USE_LIBC)
#else
#define NJ_USE_WIN32 0
#endif
#endif

#ifndef NJ_CHROMA_FILTER
#define NJ_CHROMA_FILTER 1
#endif

///////////////////////////////////////////////////////////////////////////////
// EXAMPLE PROGRAM                                                           //
// just define _NJ_EXAMPLE_PROGRAM to compile this (requires NJ_USE_LIBC)    //
///////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION SECTION                                                    //
// you may stop reading here                                                 //
///////////////////////////////////////////////////////////////////////////////

#if NJ_USE_LIBC
#include <stdlib.h>
#include <string.h>
#define njAllocMem malloc
#define njFreeMem  free
#define njFillMem  memset
#define njCopyMem  memcpy
#elif NJ_USE_WIN32
#include <windows.h>
#define njAllocMem(size) ((void*) LocalAlloc(LMEM_FIXED, (SIZE_T)(size)))
#define njFreeMem(block) ((void) LocalFree((HLOCAL) block))
NJ_INLINE void njFillMem(void* block, unsigned char value, int count) {
	__asm {
		mov edi, block
		mov al, value
		mov ecx, count
		rep stosb
	}
}
NJ_INLINE void njCopyMem(void* dest, const void* src, int count) {
	__asm {
		mov edi, dest
		mov esi, src
		mov ecx, count
		rep movsb
	}
}
#else
extern void* njAllocMem(int size);
extern void njFreeMem(void* block);
extern void njFillMem(void* block, unsigned char byte, int size);
extern void njCopyMem(void* dest, const void* src, int size);
#endif

// nj_result_t: Result codes for njDecode().
typedef enum _nj_result {
	NJ_OK = 0,        // no error, decoding successful
	NJ_NO_JPEG,       // not a JPEG file
	NJ_UNSUPPORTED,   // unsupported format
	NJ_OUT_OF_MEM,    // out of memory
	NJ_INTERNAL_ERR,  // internal error
	NJ_SYNTAX_ERROR,  // syntax error
	__NJ_FINISHED,    // used internally, will never be reported
} nj_result_t;

class IGPJpeg
{
public:
	IGPJpeg();
	~IGPJpeg();
	int njGetWidth(void) { return nj.width; }
	int njGetHeight(void) { return nj.height; }
	int njIsColor(void) { return (nj.ncomp != 1); }
	unsigned char* njGetRedImage(void) { return (nj.ncomp == 1) ? nj.comp[0].pixels : nj.rchannel; }
	unsigned char* njGetGreenImage(void) { return (nj.ncomp == 1) ? nj.comp[0].pixels : nj.gchannel; }
	unsigned char* njGetBlueImage(void) { return (nj.ncomp == 1) ? nj.comp[0].pixels : nj.bchannel; }
	int njGetImageSize(void) { return nj.width * nj.height * nj.ncomp; }

private:
	typedef struct _nj_code {
		unsigned char bits, code;
	} nj_vlc_code_t;

	typedef struct _nj_cmp {
		int cid;
		int ssx, ssy;
		int width, height;
		int stride;
		int qtsel;
		int actabsel, dctabsel;
		int dcpred;
		unsigned char *pixels;
	} nj_component_t;

	typedef struct _nj_ctx {
		nj_result_t error;
		const unsigned char *pos;
		int size;
		int length;
		int width, height;
		int mbwidth, mbheight;
		int mbsizex, mbsizey;
		int ncomp;
		nj_component_t comp[3];
		int qtused, qtavail;
		unsigned char qtab[4][64];
		nj_vlc_code_t vlctab[4][65536];
		int buf, bufbits;
		int block[64];
		int rstinterval;
		unsigned char *rchannel;
		unsigned char *gchannel;
		unsigned char *bchannel;
	} nj_context_t;

#if NJ_CHROMA_FILTER

#define CF4A (-9)
#define CF4B (111)
#define CF4C (29)
#define CF4D (-3)
#define CF3A (28)
#define CF3B (109)
#define CF3C (-9)
#define CF3X (104)
#define CF3Y (27)
#define CF3Z (-3)
#define CF2A (139)
#define CF2B (-11)
#define CF(x) njClip(((x) + 64) >> 7)
	inline void njUpsampleH(nj_component_t* c);
	inline void njUpsampleV(nj_component_t* c);
#else
	inline void njUpsample(nj_component_t* c);
#endif

#define W1 2841
#define W2 2676
#define W3 2408
#define W5 1609
#define W6 1108
#define W7 565
#define njThrow(e) do { nj.error = e; return; } while (0)
#define njCheckError() do { if (nj.error) return; } while (0)
private:
	inline unsigned char njClip(const int x) {
		return (x < 0) ? 0 : ((x > 0xFF) ? 0xFF : (unsigned char)x);
	}
	inline void njRowIDCT(int* blk);
	inline void njColIDCT(const int* blk, unsigned char *out, int stride);
	int njShowBits(int bits);
	inline void njSkipBits(int bits);
	inline int njGetBits(int bits);
	inline void njByteAlign(void);
	void njSkip(int count);
	inline unsigned short njDecode16(const unsigned char *pos);
	void njDecodeLength(void);
	inline void njSkipMarker(void);
	inline void njDecodeSOF(int decodeRed, int decodeGreen, int decodeBlue);
	inline void njDecodeDHT(void);
	inline void njDecodeDQT(void);
	inline void njDecodeDRI(void);
	int njGetVLC(nj_vlc_code_t* vlc, unsigned char* code);
	inline void njDecodeBlock(nj_component_t* c, unsigned char* out);
	inline void njDecodeScan(void);
	inline void njConvert(int decodeRed, int decodeGreen, int decodeBlue);
	void njInit(void);
	void njDone(void);
	void njDoneLeaveRGBData(void);
	nj_result_t njDecode(const void* jpeg, const int size, int decodeRed, int decodeGreen, int decodeBlue);
private:
	nj_context_t nj;
	const char njZZ[64] = { 0, 1, 8, 16, 9, 2, 3, 10, 17, 24, 32, 25, 18,
		11, 4, 5, 12, 19, 26, 33, 40, 48, 41, 34, 27, 20, 13, 6, 7, 14, 21, 28, 35,
		42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23, 30, 37, 44, 51, 58, 59, 52, 45,
		38, 31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63 };
};
