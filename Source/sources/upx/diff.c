diff --git a/src_orig/compress_lzma.cpp b/src/compress_lzma.cpp
index 688a5de..9a3cc7c 100644
--- a/src_orig/compress_lzma.cpp
+++ b/src/compress_lzma.cpp
@@ -94,11 +94,11 @@ int compress_lzma_dummy = 0;
 
 
 #if (WITH_LZMA >= 0x461)
-#include "C/7zVersion.h"
+#include "LZMA/C/7zVersion.h"
 #if (WITH_LZMA != (0x100 * MY_VER_MAJOR) + (0x10 * (MY_VER_MINOR / 10)) + (MY_VER_MINOR % 10))
 #  error "WITH_LZMA version mismatch"
 #endif
-#include "C/Types.h"
+#include "LZMA/C/Types.h"
 static void *cb_alloc(void *, size_t size) {
     return malloc(size);
 }
@@ -231,9 +231,11 @@ error:
 
 #if (WITH_LZMA >= 0x461)
 #define kLiteralNextStates kLiteralNextStates_enc
-#include "C/LzmaEnc.h"
-#include "C/LzmaEnc.c"
-#include "C/LzFind.c"
+#include "LZMA/C/LzmaEnc.h"
+#include "LZMA/C/LzmaEnc.c"
+#include "LZMA/C/LzFind.c"
+#include "LZMA/C/LzFindMt.c"
+#include "LZMA/C/Threads.c"
 #undef kLiteralNextStates
 #undef kNumFullDistances
 
@@ -562,8 +564,8 @@ error:
 #if (WITH_LZMA >= 0x461)
 
 #undef _LZMA_PROB32
-#include "C/LzmaDec.h"
-#include "C/LzmaDec.c"
+#include "LZMA/C/LzmaDec.h"
+#include "LZMA/C/LzmaDec.c"
 
 
 int upx_lzma_decompress    ( const upx_bytep src, unsigned  src_len,
diff --git a/src_orig/compress_ucl.cpp b/src/compress_ucl.cpp
index fadba7f..c2a91f2 100644
--- a/src_orig/compress_ucl.cpp
+++ b/src/compress_ucl.cpp
@@ -44,6 +44,10 @@ int compress_ucl_dummy = 0;
 #if (ACC_CFG_NO_UNALIGNED)
 #  undef UCL_USE_ASM
 #endif
+/*
+#undef  UCL_USE_ASM
+#define UCL_USE_ASM 0
+*/
 #if 1 && (UCL_USE_ASM)
 #  include <ucl/ucl_asm.h>
 #  define ucl_nrv2b_decompress_safe_8       ucl_nrv2b_decompress_asm_safe_8
diff --git a/src_orig/conf.h b/src/conf.h
index 963576d..44bdea2 100644
--- a/src_orig/conf.h
+++ b/src/conf.h
@@ -31,6 +31,9 @@
 
 #include "version.h"
 
+#pragma warning(disable:583)
+#define WITH_ZLIB 1
+#define WITH_LZMA 0x920
 
 /*************************************************************************
 // ACC
@@ -107,6 +110,7 @@
 #  if (_MSC_VER < 1100)
 #    error "need Visual C++ 5.0 or newer"
 #  endif
+
 #  pragma warning(error: 4096)          // W2: '__cdecl' must be used with '...'
 #  pragma warning(error: 4138)          // Wx: '*/' found outside of comment
 #  pragma warning(disable: 4097)        // W3: typedef-name 'A' used as synonym for class-name 'B'
@@ -183,14 +187,16 @@
 #  define WITH_UCL 1
 #endif
 #if 0 && !defined(WITH_LZMA)
-#  define WITH_LZMA 1
+#  define WITH_LZMA 0x920
+#  define WITH_NRV  1
 #endif
 #if 1 && (ACC_CC_WATCOMC)
 #  undef WITH_LZMA
 #endif
+
 #if defined(UPX_OFFICIAL_BUILD)
 #  if !(WITH_LZMA) || !(WITH_NRV) || !(WITH_UCL)
-#    error
+//#    error
 #  endif
 #endif
 #if (WITH_NRV)
@@ -326,7 +332,8 @@
 
 #if (ACC_CC_INTELC && (__INTEL_COMPILER < 800))
 #elif (0 && (ACC_ARCH_AMD64 || ACC_ARCH_I386))
-#elif (ACC_CC_GNUC || ACC_CC_INTELC || ACC_CC_PATHSCALE)
+//#elif (ACC_CC_GNUC || ACC_CC_INTELC || ACC_CC_PATHSCALE)
+#elif (ACC_CC_GNUC || ACC_CC_PATHSCALE)
 #  define __packed_struct(s)        struct s {
 #  define __packed_struct_end()     } __attribute__((__packed__,__aligned__(1)));
 #elif (ACC_CC_WATCOMC)
diff --git a/src_orig/file.cpp b/src/file.cpp
index aff42bf..9c7ac02 100644
--- a/src_orig/file.cpp
+++ b/src/file.cpp
@@ -106,7 +106,7 @@ bool FileBase::do_sopen()
     }
     if (_fd < 0)
         return false;
-    if (::fstat(_fd, &st) != 0)
+    if (_fstat(_fd, (struct _stat *)&st) != 0)
         throwIOException(_name, errno);
     _length = st.st_size;
     return true;
@@ -367,7 +367,7 @@ off_t OutputFile::st_size() const
     }
     struct stat my_st;
     my_st.st_size = 0;
-    if (::fstat(_fd, &my_st) != 0)
+    if (_fstat(_fd, (struct _stat *)&my_st) != 0)
         throwIOException(_name, errno);
     return my_st.st_size;
 }
@@ -415,7 +415,7 @@ void OutputFile::set_extent(off_t offset, off_t length)
     super::set_extent(offset, length);
     bytes_written = 0;
     if (0==offset && (off_t)~0u==length) {
-        if (::fstat(_fd, &st) != 0)
+        if (_fstat(_fd, (struct _stat *)&st) != 0)
             throwIOException(_name, errno);
         _length = st.st_size - offset;
     }
diff --git a/src_orig/main.cpp b/src/main.cpp
index e232e4b..e820b51 100644
--- a/src_orig/main.cpp
+++ b/src/main.cpp
@@ -50,7 +50,7 @@ void options_t::reset()
 
     o->cmd = CMD_NONE;
     o->method = M_NONE;
-    o->level = -1;
+    o->level = 10;
     o->filter = FT_NONE;
 
     o->backup = -1;
@@ -922,6 +922,7 @@ static const struct mfx_option longopts[] =
     {"best",             0x10, 0, 900},     // compress best
     {"brute",            0x10, 0, 901},     // compress best, brute force
     {"ultra-brute",      0x10, 0, 902},     // compress best, brute force
+    {"ub",               0x10, 0, 902},     // compress best, brute force
     {"decompress",          0, 0, 'd'},     // decompress
     {"fast",             0x10, 0, '1'},     // compress faster
     {"fileinfo",         0x10, 0, 909},     // display info about file
diff --git a/src_orig/msg.cpp b/src/msg.cpp
index e8acb22..728bfe1 100644
--- a/src_orig/msg.cpp
+++ b/src/msg.cpp
@@ -113,6 +113,7 @@ void printErr(const char *iname, const Throwable *e)
     size_t l;
 
     upx_snprintf(buf, sizeof(buf), "%s", prettyName(typeid(*e).name()));
+//    upx_snprintf(buf, sizeof(buf), "%s", e->getMsg());
     l = strlen(buf);
     if (l < sizeof(buf) && e->getMsg())
         upx_snprintf(buf+l, sizeof(buf)-l, ": %s", e->getMsg());
diff --git a/src_orig/p_vmlinz.cpp b/src/p_vmlinz.cpp
index 58293bc..42d61ea 100644
--- a/src_orig/p_vmlinz.cpp
+++ b/src/p_vmlinz.cpp
@@ -927,6 +927,8 @@ static const
 static const
 #include "stub/armel-linux.kernel.vmlinuz-head.h"
 
+#undef small
+
 void PackVmlinuzARMEL::buildLoader(const Filter *ft)
 {
     // prepare loader; same as vmlinux (with 'x')
diff --git a/src_orig/p_w32pe.cpp b/src/p_w32pe.cpp
index f3ad5ed..58fb9d2 100644
--- a/src_orig/p_w32pe.cpp
+++ b/src/p_w32pe.cpp
@@ -340,12 +340,17 @@ void PackW32Pe::processImports(unsigned myimport, unsigned) // pass 2
 unsigned PackW32Pe::processImports() // pass 1
 {
     static const unsigned char kernel32dll[] = "KERNEL32.DLL";
+#if defined(MOD)
+    static const char llgpa[] = "\x0\x0""GetModuleHandleExA\x0\x0"
+                                "GetProcAddress\x0\x0\x0";
+#else
     static const char llgpa[] = "\x0\x0""LoadLibraryA\x0\x0"
                                 "GetProcAddress\x0\x0"
                                 "VirtualProtect\x0\x0"
                                 "VirtualAlloc\x0\x0"
                                 "VirtualFree\x0\x0\x0";
     static const char exitp[] = "ExitProcess\x0\x0\x0";
+#endif
 
     unsigned dllnum = 0;
     import_desc *im = (import_desc*) (ibuf + IDADDR(PEDIR_IMPORT));
@@ -432,6 +437,9 @@ unsigned PackW32Pe::processImports() // pass 1
 
     unsigned dllnamelen = sizeof (kernel32dll);
     unsigned dllnum2 = 1;
+
+#if !defined(MOD)
+
     for (ic = 0; ic < dllnum; ic++)
         if (!idlls[ic]->isk32 && (ic == 0 || strcasecmp(idlls[ic - 1]->name,idlls[ic]->name)))
         {
@@ -440,24 +448,41 @@ unsigned PackW32Pe::processImports() // pass 1
         }
     //fprintf(stderr,"dllnum=%d dllnum2=%d soimport=%d\n",dllnum,dllnum2,soimport); //
 
+#endif
+
     info("Processing imports: %d DLLs", dllnum);
 
     // create the new import table
     im = (import_desc*) oimpdlls;
-
+#if defined(MOD)
+    LE32 *ordinals = (LE32*) (oimpdlls + (dllnum2 + 1) * sizeof(import_desc));
+    LE32 *lookuptable = ordinals + 3 + k32o;
+    upx_byte *dllnames = ((upx_byte*) lookuptable) + (dllnum2 - 1) * 8;
+    upx_byte *importednames = dllnames + (dllnamelen & ~1);
+#else
     LE32 *ordinals = (LE32*) (oimpdlls + (dllnum2 + 1) * sizeof(import_desc));
     LE32 *lookuptable = ordinals + 6 + k32o + (isdll ? 0 : 1);
     upx_byte *dllnames = ((upx_byte*) lookuptable) + (dllnum2 - 1) * 8;
-    upx_byte *importednames = dllnames + (dllnamelen &~ 1);
+    upx_byte *importednames = dllnames + (dllnamelen & ~1);
+#endif
 
     unsigned k32namepos = ptr_diff(dllnames,oimpdlls);
 
     memcpy(importednames, llgpa, sizeof(llgpa));
+
+#if !defined(MOD)
     if (!isdll)
         memcpy(importednames + sizeof(llgpa) - 1, exitp, sizeof(exitp));
+#endif
+
     strcpy(dllnames,kernel32dll);
     im->dllname = k32namepos;
     im->iat = ptr_diff(ordinals,oimpdlls);
+
+#if defined(MOD)
+    *ordinals++ = ptr_diff(importednames,oimpdlls);             // GetModuleHandleExA
+    *ordinals++ = ptr_diff(importednames,oimpdlls) + 20;        // GetProcAddress
+#else
     *ordinals++ = ptr_diff(importednames,oimpdlls);             // LoadLibraryA
     *ordinals++ = ptr_diff(importednames,oimpdlls) + 14;        // GetProcAddress
     *ordinals++ = ptr_diff(importednames,oimpdlls) + 14 + 16;   // VirtualProtect
@@ -465,10 +490,31 @@ unsigned PackW32Pe::processImports() // pass 1
     *ordinals++ = ptr_diff(importednames,oimpdlls) + 14 + 16 + 16 + 14;   // VirtualFree
     if (!isdll)
         *ordinals++ = ptr_diff(importednames,oimpdlls) + sizeof(llgpa) - 3; // ExitProcess
+#endif
     dllnames += sizeof(kernel32dll);
+
+#if defined(MOD)
+    importednames += sizeof(llgpa) - 2;
+#else
     importednames += sizeof(llgpa) - 2 + (isdll ? 0 : sizeof(exitp) - 1);
+#endif
 
     im++;
+#if defined(MOD)
+    for (ic = 0; ic < dllnum; ic++)
+    {
+        if (idlls[ic]->isk32)
+        {
+            idlls[ic]->npos = k32namepos;
+        }
+        else if (ic && strcasecmp(idlls[ic-1]->name,idlls[ic]->name) == 0)
+            idlls[ic]->npos = idlls[ic-1]->npos;
+        else
+        {
+            idlls[ic]->npos = ptr_diff(dllnames,oimpdlls);
+        }
+    }
+#else
     for (ic = 0; ic < dllnum; ic++)
         if (idlls[ic]->isk32)
         {
@@ -501,6 +547,7 @@ unsigned PackW32Pe::processImports() // pass 1
             lookuptable += 2;
             im++;
         }
+#endif
     soimpdlls = ALIGN_UP(ptr_diff(importednames,oimpdlls),4);
 
     Interval names(ibuf),iats(ibuf),lookups(ibuf);
@@ -515,6 +562,15 @@ unsigned PackW32Pe::processImports() // pass 1
         set_le32(ppi,idlls[ic]->npos);
         set_le32(ppi+4,idlls[ic]->iat - rvamin);
         ppi += 8;
+
+#if defined(MOD)
+        {
+            unsigned len = strlen(idlls[ic]->name) + 1;
+            memcpy(ppi, idlls[ic]->name, len);
+            ppi += len;
+        }
+#endif
+
         for (; *tarr; tarr++)
             if (*tarr & 0x80000000)
             {
@@ -670,7 +726,8 @@ void PackW32Pe::buildLoader(const Filter *ft)
         tmp_tlsindex = 0;
 
     // prepare loader
-    initLoader(stub_i386_win32_pe, sizeof(stub_i386_win32_pe), 2);
+    initLoader(stub_i386_win32_pe2, STUB_I386_WIN32_PE_SIZE, 2);
+#if defined(MOD1)
     addLoader(isdll ? "PEISDLL1" : "",
               "PEMAIN01",
               icondir_count > 1 ? (icondir_count == 2 ? "PEICONS1" : "PEICONS2") : "",
@@ -681,7 +738,20 @@ void PackW32Pe::buildLoader(const Filter *ft)
               /*multipass ? "PEMULTIP" :  */  "",
               "PEMAIN10",
               NULL
-             );
+              );
+#else
+    addLoader(isdll ? "PEISDLL1" : "",
+              "PEMAIN01",
+              icondir_count > 1 ? (icondir_count == 2 ? "PEICONS1" : "PEICONS2") : "",
+              tmp_tlsindex ? "PETLSHAK" : "",
+              "PEMAIN02",
+              ph.first_offset_found == 1 ? "PEMAIN03" : "",
+              getDecompressorSections(),
+              /*multipass ? "PEMULTIP" :  */  "",
+              "PEMAIN10",
+              NULL
+              );
+#endif
     if (ft->id)
     {
         const unsigned texv = ih.codebase - rvamin;
@@ -690,6 +760,17 @@ void PackW32Pe::buildLoader(const Filter *ft)
         addFilter32(ft->id);
     }
     if (soimport)
+#if defined(MOD)
+        addLoader("MYPEIMPORT", "MYPEIMPORT_2",
+                  importbyordinal ? "PEIBYORD" : "",
+                  kernel32ordinal ? "MYPEK32ORD" : "",
+                  importbyordinal ? "PEIMORD1" : "",
+                  "MYPEIMPOR2",
+                  isdll ? "PEIERDLL" : "MYPEIEREXE",
+                  "PEIMDONE",
+                  NULL
+                  );
+#else
         addLoader("PEIMPORT",
                   importbyordinal ? "PEIBYORD" : "",
                   kernel32ordinal ? "PEK32ORD" : "",
@@ -698,7 +779,8 @@ void PackW32Pe::buildLoader(const Filter *ft)
                   isdll ? "PEIERDLL" : "PEIEREXE",
                   "PEIMDONE",
                   NULL
-                 );
+                  );
+#endif
     if (sorelocs)
     {
         addLoader(soimport == 0 || soimport + cimports != crelocs ? "PERELOC1" : "PERELOC2",
@@ -715,15 +797,26 @@ void PackW32Pe::buildLoader(const Filter *ft)
                  );
     }
     if (use_dep_hack)
+#if defined(MOD)
+        addLoader("MYPEDEPHAK", NULL);
+#else
         addLoader("PEDEPHAK", NULL);
+#endif
 
     //NEW: TLS callback support PART 1, the callback handler installation - Stefan Widmann
     if(use_tls_callbacks)
         addLoader("PETLSC", NULL);
 
     addLoader("PEMAIN20", NULL);
+
+#if defined(MOD)
+    if (use_clear_dirty_stack)
+        addLoader("MYCLEARSTACK", NULL);
+#else
     if (use_clear_dirty_stack)
         addLoader("CLEARSTACK", NULL);
+#endif
+
     addLoader("PEMAIN21", NULL);
 #if 0
     addLoader(ih.entry ? "PEDOJUMP" : "PERETURN",
@@ -882,7 +975,20 @@ void PackW32Pe::pack(OutputFile *fo)
     if (ih.filealign < 0x200)
         throwCantPack("filealign < 0x200 is not yet supported");
 
+#if defined(MOD)
+    pe_offset = 0x80;
+    {
+        ByteArray(stub, pe_offset);
+        fi->seek(0,SEEK_SET);
+        fi->readx(stub,pe_offset);
+        *(int *)&stub[0x3C] = 0x80;
+        fo->seek(0, SEEK_SET);
+        fo->write(stub,pe_offset);
+    }
+#else
     handleStub(fi,fo,pe_offset);
+#endif
+
     const unsigned usize = ih.imagesize;
     const unsigned xtrasize = UPX_MAX(ih.datasize, 65536u) + IDSIZE(PEDIR_IMPORT) + IDSIZE(PEDIR_BOUNDIM) + IDSIZE(PEDIR_IAT) + IDSIZE(PEDIR_DELAYIMP) + IDSIZE(PEDIR_RELOC);
     ibuf.alloc(usize + xtrasize);
@@ -978,6 +1084,7 @@ void PackW32Pe::pack(OutputFile *fo)
     //fprintf(stderr,"newvsize=%x objs=%d\n",newvsize,objs);
     if (newvsize + soimport + sorelocs > ibuf.getSize())
          throwInternalError("buffer too small 2");
+
     memcpy(ibuf+newvsize,oimport,soimport);
     memcpy(ibuf+newvsize+soimport,orelocs,sorelocs);
 
@@ -986,6 +1093,9 @@ void PackW32Pe::pack(OutputFile *fo)
 
     ph.u_len = newvsize + soimport + sorelocs;
 
+#if defined(MOD)
+    (dllstrings);
+#else
     // some extra data for uncompression support
     unsigned s = 0;
     upx_byte * const p1 = ibuf + ph.u_len;
@@ -1014,6 +1124,8 @@ void PackW32Pe::pack(OutputFile *fo)
     set_le32(p1 + s,ptr_diff(p1,ibuf) - rvamin);
     s += 4;
     ph.u_len += s;
+#endif
+
     obuf.allocForCompression(ph.u_len);
 
     // prepare packheader
@@ -1057,6 +1169,7 @@ void PackW32Pe::pack(OutputFile *fo)
 
     // identsplit - number of ident + (upx header) bytes to put into the PE header
     int identsplit = pe_offset + sizeof(osection) + sizeof(oh);
+
     if ((identsplit & 0x1ff) == 0)
         identsplit = 0;
     else if (((identsplit + identsize) ^ identsplit) < 0x200)
@@ -1104,14 +1217,26 @@ void PackW32Pe::pack(OutputFile *fo)
         linker->defineSymbol("vp_size", ((addr & 0xfff) + 0x28 >= 0x1000) ?
                              0x2000 : 0x1000);          // 2 pages or 1 page
         linker->defineSymbol("vp_base", addr &~ 0xfff); // page mask
+#if !defined(MOD)
         linker->defineSymbol("VirtualProtect", myimport + get_le32(oimpdlls + 16) + 8);
+#endif
     }
     linker->defineSymbol("reloc_delt", 0u - (unsigned) ih.imagebase - rvamin);
     linker->defineSymbol("start_of_relocs", crelocs);
+
+#if !defined(MOD)
     linker->defineSymbol("ExitProcess", myimport + get_le32(oimpdlls + 16) + 20);
+#endif
+
     linker->defineSymbol("GetProcAddress", myimport + get_le32(oimpdlls + 16) + 4);
     linker->defineSymbol("kernel32_ordinals", myimport);
+
+#if defined(MOD)
+    linker->defineSymbol("GetModuleHandleExA", myimport + get_le32(oimpdlls + 16));
+#else
     linker->defineSymbol("LoadLibraryA", myimport + get_le32(oimpdlls + 16));
+#endif
+
     linker->defineSymbol("start_of_imports", myimport);
     linker->defineSymbol("compressed_imports", cimports);
 #if 0
@@ -1236,8 +1361,14 @@ void PackW32Pe::pack(OutputFile *fo)
     const unsigned ncsize_virt_increase = (ncsize & oam1) == 0 ? 8 : 0;
 
     // fill the sections
+#if !defined(MOD)
     strcpy(osection[0].name,"UPX0");
     strcpy(osection[1].name,"UPX1");
+#else
+    strcpy(osection[0].name,DEFAULT_SECTION_NAME);
+    strcpy(osection[1].name,DEFAULT_SECTION_NAME);
+    strcpy(osection[2].name,DEFAULT_SECTION_NAME);
+#endif
     // after some windoze debugging I found that the name of the sections
     // DOES matter :( .rsrc is used by oleaut32.dll (TYPELIBS)
     // and because of this lame dll, the resource stuff must be the
@@ -1246,7 +1377,9 @@ void PackW32Pe::pack(OutputFile *fo)
     // ... even worse: exploder.exe in NiceTry also depends on this to
     // locate version info
 
+#if !defined(MOD)
     strcpy(osection[2].name,soresources ? ".rsrc" : "UPX2");
+#endif
 
     osection[0].vaddr = rvamin;
     osection[1].vaddr = s1addr;
@@ -1261,6 +1394,7 @@ void PackW32Pe::pack(OutputFile *fo)
     osection[2].vsize = (osection[2].size + ncsize_virt_increase + oam1) &~ oam1;
 
     osection[0].rawdataptr = (pe_offset + sizeof(oh) + sizeof(osection) + ic) &~ ic;
+
     osection[1].rawdataptr = osection[0].rawdataptr;
     osection[2].rawdataptr = osection[1].rawdataptr + osection[1].size;
 
@@ -1301,6 +1435,11 @@ void PackW32Pe::pack(OutputFile *fo)
         assert(n <= oh.filealign);
         fo->write(ibuf, n);
     }
+
+#if defined(MOD)
+    memset(loader + codesize, 0, identsize);
+#endif
+
     fo->write(loader + codesize,identsize);
     infoWriting("loader", fo->getBytesWritten());
     fo->write(obuf,c_len);
diff --git a/src_orig/packer.cpp b/src/packer.cpp
index b58ab18..95513c9 100644
--- a/src_orig/packer.cpp
+++ b/src/packer.cpp
@@ -290,10 +290,11 @@ bool Packer::compress(upx_bytep i_ptr, unsigned i_len, upx_bytep o_ptr,
             throwInternalError("decompression failed");
         if (new_len != ph.u_len)
             throwInternalError("decompression failed (size error)");
-
+/*
         // verify decompression
         if (ph.u_adler != upx_adler32(i_ptr, ph.u_len, ph.saved_u_adler))
             throwInternalError("decompression failed (checksum error)");
+*/
     }
     return true;
 }
@@ -353,7 +354,11 @@ void ph_decompress(PackHeader &ph, const upx_bytep in, upx_bytep out,
     unsigned adler;
 
     // verify checksum of compressed data
+#if defined(MOD1)
+    if (0)
+#else
     if (verify_checksum)
+#endif
     {
         adler = upx_adler32(in, ph.c_len, ph.saved_c_adler);
         if (adler != ph.c_adler)
@@ -369,7 +374,11 @@ void ph_decompress(PackHeader &ph, const upx_bytep in, upx_bytep out,
         throwCompressedDataViolation();
 
     // verify checksum of decompressed data
+#if defined(MOD1)
+    if (0)
+#else
     if (verify_checksum)
+#endif
     {
         if (ft)
             ft->unfilter(out, ph.u_len);
diff --git a/src_orig/packmast.cpp b/src/packmast.cpp
index 7855733..f326295 100644
--- a/src_orig/packmast.cpp
+++ b/src/packmast.cpp
@@ -32,6 +32,11 @@
 #include "packer.h"
 #include "lefile.h"
 #include "pefile.h"
+
+#if defined(MOD)
+#include "p_w32pe.h"
+#else
+
 #include "p_elf.h"
 
 #include "p_com.h"
@@ -56,6 +61,8 @@
 #include "p_mach.h"
 #include "p_armpe.h"
 
+#endif
+
 
 /*************************************************************************
 //
@@ -149,6 +156,28 @@ static Packer* try_unpack(Packer *p, void *user)
 //
 **************************************************************************/
 
+#if defined(MOD)
+
+Packer* PackMaster::visitAllPackers(visit_func_t func, InputFile *f, const options_t *o, void *user)
+{
+    Packer *p = NULL;
+
+    // note: order of tries is important !
+
+    //
+    // .exe
+    //
+    if (!o->dos_exe.force_stub)
+    {
+        if ((p = func(new PackW32Pe(f), user)) != NULL)
+            return p;
+        delete p; p = NULL;
+    }
+    return NULL;
+}
+
+#else
+
 Packer* PackMaster::visitAllPackers(visit_func_t func, InputFile *f, const options_t *o, void *user)
 {
     Packer *p = NULL;
@@ -339,6 +368,8 @@ Packer* PackMaster::visitAllPackers(visit_func_t func, InputFile *f, const optio
     return NULL;
 }
 
+#endif /* MOD */
+
 
 Packer *PackMaster::getPacker(InputFile *f)
 {
diff --git a/src_orig/stub/i386-win32.pe.h b/src/stub/i386-win32.pe.h
index 795822b..a17b600 100644
--- a/src_orig/stub/i386-win32.pe.h
+++ b/src/stub/i386-win32.pe.h
@@ -31,10 +31,1134 @@
  */
 
 
-#define STUB_I386_WIN32_PE_SIZE    32851
+//#define STUB_I386_WIN32_PE_SIZE    32851
+#define STUB_I386_WIN32_PE_SIZE    (sizeof(stub_i386_win32_pe2) - 1)
 #define STUB_I386_WIN32_PE_ADLER32 0xce14e90a
 #define STUB_I386_WIN32_PE_CRC32   0xd3f22752
 
+unsigned char stub_i386_win32_pe2[] =
+{
+    "\x7F\x45\x4C\x46\x01\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00"
+    "\x01\x00\x03\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
+    "\x90\x20\x00\x00\x00\x00\x00\x00\x34\x00\x00\x00\x00\x00\x28\x00"
+    "\xC2\x00\xBF\x00\x80\x7C\x24\x08\x01\x0F\x85\xFC\xFF\xFF\xFF\x60"
+    "\xBE\x00\x00\x00\x00\x8D\xBE\x00\x00\x00\x00\x66\xFF\x87\x00\x00"
+    "\x00\x00\x66\x81\x87\x00\x00\x00\x00\x00\x00\xC7\x87\x00\x00\x00"
+    "\x00\x00\x00\x00\x00\x57\x83\xCD\xFF\xEB\x03\xA4\xEB\x03\x8A\x06"
+    "\x46\x88\x07\x47\x01\xDB\x75\x07\x8B\x1E\x83\xEE\xFC\x11\xDB\x72"
+    "\x01\x31\xC0\x40\x72\xFF\xB8\x01\x00\x00\x00\x01\xDB\x75\x07\x8B"
+    "\x1E\x83\xEE\xFC\x11\xDB\x11\xC0\x01\xDB\x75\x07\x8B\x1E\x83\xEE"
+    "\xFC\x11\xDB\x73\xFF\x01\xDB\x73\xFF\x75\x09\x8B\x1E\x83\xEE\xFC"
+    "\x11\xDB\x73\xFF\x31\xC9\x83\xE8\x03\x72\x0D\xC1\xE0\x08\x8A\x06"
+    "\x46\x83\xF0\xFF\x74\xFF\x89\xC5\x01\xDB\x75\x07\x8B\x1E\x83\xEE"
+    "\xFC\x11\xDB\x11\xC9\x01\xDB\x75\x07\x8B\x1E\x83\xEE\xFC\x11\xDB"
+    "\x11\xC9\x75\xFF\x41\x01\xDB\x75\x07\x8B\x1E\x83\xEE\xFC\x11\xDB"
+    "\x11\xC9\x01\xDB\x75\x07\x8B\x1E\x83\xEE\xFC\x11\xDB\x73\x30\x01"
+    "\xDB\x73\x30\x75\x09\x8B\x1E\x83\xEE\xFC\x11\xDB\x73\x30\x41\x41"
+    "\x83\xC1\x02\x81\xFD\x00\xF3\xFF\xFF\x83\xD1\x01\x89\xF2\x8D\x34"
+    "\x2F\xF3\xA4\x89\xD6\xE9\xFC\xFF\xFF\xFF\x8D\x14\x2F\x83\xFD\xFC"
+    "\x76\xFF\x8A\x02\x42\x88\x07\x47\x49\x75\xF7\xE9\xFC\xFF\xFF\xFF"
+    "\x8B\x02\x83\xC2\x04\x89\x07\x83\xC7\x04\x83\xE9\x04\x77\xF1\x01"
+    "\xCF\xE9\xFC\xFF\xFF\xFF\xEB\x03\xA4\xEB\x03\x8A\x06\x46\x88\x07"
+    "\x47\x01\xDB\x75\x07\x8B\x1E\x83\xEE\xFC\x11\xDB\x72\x01\x31\xC0"
+    "\x40\x72\xFF\xB8\x01\x00\x00\x00\x01\xDB\x75\x07\x8B\x1E\x83\xEE"
+    "\xFC\x11\xDB\x11\xC0\x01\xDB\x75\x07\x8B\x1E\x83\xEE\xFC\x11\xDB"
+    "\x72\x0F\x01\xDB\x73\x0B\x75\x0F\x8B\x1E\x83\xEE\xFC\x11\xDB\x72"
+    "\x0F\x48\x01\xDB\x75\x07\x8B\x1E\x83\xEE\xFC\x11\xDB\x11\xC0\xEB"
+    "\xFF\x31\xC9\x83\xE8\x03\x72\x11\xC1\xE0\x08\x8A\x06\x46\x83\xF0"
+    "\xFF\x74\xFF\xD1\xF8\x89\xC5\xEB\x0B\x01\xDB\x75\x07\x8B\x1E\x83"
+    "\xEE\xFC\x11\xDB\x11\xC9\x01\xDB\x75\x07\x8B\x1E\x83\xEE\xFC\x11"
+    "\xDB\x11\xC9\x75\xFF\x41\x01\xDB\x75\x07\x8B\x1E\x83\xEE\xFC\x11"
+    "\xDB\x11\xC9\x01\xDB\x75\x07\x8B\x1E\x83\xEE\xFC\x11\xDB\x73\x44"
+    "\x01\xDB\x73\x44\x75\x09\x8B\x1E\x83\xEE\xFC\x11\xDB\x73\x44\x41"
+    "\x41\x83\xC1\x02\x81\xFD\x00\xFB\xFF\xFF\x83\xD1\x01\x89\xF2\x8D"
+    "\x34\x2F\xF3\xA4\x89\xD6\xE9\xFC\xFF\xFF\xFF\x8D\x14\x2F\x83\xFD"
+    "\xFC\x76\xFF\x8A\x02\x42\x88\x07\x47\x49\x75\xF7\xE9\xFC\xFF\xFF"
+    "\xFF\x8B\x02\x83\xC2\x04\x89\x07\x83\xC7\x04\x83\xE9\x04\x77\xF1"
+    "\x01\xCF\xE9\xFC\xFF\xFF\xFF\xEB\x03\xA4\xEB\x03\x8A\x06\x46\x88"
+    "\x07\x47\x01\xDB\x75\x07\x8B\x1E\x83\xEE\xFC\x11\xDB\x72\x01\x31"
+    "\xC0\x40\x72\xFF\xB8\x01\x00\x00\x00\x01\xDB\x75\x07\x8B\x1E\x83"
+    "\xEE\xFC\x11\xDB\x11\xC0\x01\xDB\x75\x07\x8B\x1E\x83\xEE\xFC\x11"
+    "\xDB\x72\x1E\x01\xDB\x73\x0B\x75\x1E\x8B\x1E\x83\xEE\xFC\x11\xDB"
+    "\x72\x1E\x48\x01\xDB\x75\x07\x8B\x1E\x83\xEE\xFC\x11\xDB\x11\xC0"
+    "\xEB\xFF\x01\xDB\x75\x07\x8B\x1E\x83\xEE\xFC\x11\xDB\x11\xC9\xEB"
+    "\xFF\x31\xC9\x83\xE8\x03\x72\x11\xC1\xE0\x08\x8A\x06\x46\x83\xF0"
+    "\xFF\x74\xFF\xD1\xF8\x89\xC5\xEB\x0B\x01\xDB\x75\x07\x8B\x1E\x83"
+    "\xEE\xFC\x11\xDB\x72\xCC\x41\x01\xDB\x75\x07\x8B\x1E\x83\xEE\xFC"
+    "\x11\xDB\x72\xBE\x01\xDB\x75\x07\x8B\x1E\x83\xEE\xFC\x11\xDB\x11"
+    "\xC9\x01\xDB\x75\x07\x8B\x1E\x83\xEE\xFC\x11\xDB\x73\x51\x01\xDB"
+    "\x73\x51\x75\x09\x8B\x1E\x83\xEE\xFC\x11\xDB\x73\x51\x41\x41\x83"
+    "\xC1\x02\x81\xFD\x00\xFB\xFF\xFF\x83\xD1\x02\x89\xF2\x8D\x34\x2F"
+    "\xF3\xA4\x89\xD6\xE9\xFC\xFF\xFF\xFF\x8D\x14\x2F\x83\xFD\xFC\x76"
+    "\xFF\x8A\x02\x42\x88\x07\x47\x49\x75\xF7\xE9\xFC\xFF\xFF\xFF\x8B"
+    "\x02\x83\xC2\x04\x89\x07\x83\xC7\x04\x83\xE9\x04\x77\xF1\x01\xCF"
+    "\xE9\xFC\xFF\xFF\xFF\x89\xE5\x8D\x9C\x24\x00\x00\x00\x00\x31\xC0"
+    "\x50\x39\xDC\x75\xFB\x46\x46\x53\x68\x00\x00\x00\x00\x57\x83\xC3"
+    "\x04\x53\x68\x00\x00\x00\x00\x56\x83\xC3\x04\x53\x50\xC7\x03\x00"
+    "\x00\x00\x00\x89\xE5\x8B\x55\x00\xAC\x4A\x88\xC1\x24\x07\xC0\xE9"
+    "\x03\xBB\x00\xFD\xFF\xFF\xD3\xE3\x8D\xA4\x5C\x90\xF1\xFF\xFF\x83"
+    "\xE4\xE0\x6A\x00\x6A\x00\x89\xE3\x53\x83\xC3\x04\x8B\x4D\x00\xFF"
+    "\x31\x57\x53\x83\xC3\x04\x88\x43\x02\xAC\x4A\x88\xC1\x24\x0F\x88"
+    "\x03\xC0\xE9\x04\x88\x4B\x01\x52\x56\x53\x50\x55\x57\x56\x53\x83"
+    "\xEC\x7C\x8B\x94\x24\x90\x00\x00\x00\xC7\x44\x24\x74\x00\x00\x00"
+    "\x00\xC6\x44\x24\x73\x00\x8B\xAC\x24\x9C\x00\x00\x00\x8D\x42\x04"
+    "\x89\x44\x24\x78\xB8\x01\x00\x00\x00\x0F\xB6\x4A\x02\x89\xC3\xD3"
+    "\xE3\x89\xD9\x49\x89\x4C\x24\x6C\x0F\xB6\x4A\x01\xD3\xE0\x48\x89"
+    "\x44\x24\x68\x8B\x84\x24\xA8\x00\x00\x00\x0F\xB6\x32\xC7\x45\x00"
+    "\x00\x00\x00\x00\xC7\x44\x24\x60\x00\x00\x00\x00\xC7\x00\x00\x00"
+    "\x00\x00\xB8\x00\x03\x00\x00\x89\x74\x24\x64\xC7\x44\x24\x5C\x01"
+    "\x00\x00\x00\xC7\x44\x24\x58\x01\x00\x00\x00\xC7\x44\x24\x54\x01"
+    "\x00\x00\x00\xC7\x44\x24\x50\x01\x00\x00\x00\x0F\xB6\x4A\x01\x01"
+    "\xF1\xD3\xE0\x8D\x88\x36\x07\x00\x00\x39\x4C\x24\x74\x73\x0E\x8B"
+    "\x44\x24\x78\x66\xC7\x00\x00\x04\x83\xC0\x02\xE2\xF6\x8B\x9C\x24"
+    "\x94\x00\x00\x00\x31\xFF\xC7\x44\x24\x48\xFF\xFF\xFF\xFF\x89\xDA"
+    "\x03\x94\x24\x98\x00\x00\x00\x89\x54\x24\x4C\x31\xD2\x3B\x5C\x24"
+    "\x4C\x0F\x84\x7C\x09\x00\x00\x0F\xB6\x03\xC1\xE7\x08\x42\x43\x09"
+    "\xC7\x83\xFA\x04\x7E\xE7\x8B\x8C\x24\xA4\x00\x00\x00\x39\x4C\x24"
+    "\x74\x0F\x83\x64\x09\x00\x00\x8B\x74\x24\x74\x23\x74\x24\x6C\x8B"
+    "\x44\x24\x60\x8B\x54\x24\x78\xC1\xE0\x04\x89\x74\x24\x44\x01\xF0"
+    "\x81\x7C\x24\x48\xFF\xFF\xFF\x00\x8D\x2C\x42\x77\x18\x3B\x5C\x24"
+    "\x4C\x0F\x84\x2C\x09\x00\x00\xC1\x64\x24\x48\x08\x0F\xB6\x03\xC1"
+    "\xE7\x08\x43\x09\xC7\x8B\x44\x24\x48\x66\x8B\x55\x00\xC1\xE8\x0B"
+    "\x0F\xB7\xCA\x0F\xAF\xC1\x39\xC7\x0F\x83\xDD\x01\x00\x00\x89\x44"
+    "\x24\x48\xB8\x00\x08\x00\x00\x29\xC8\x8A\x4C\x24\x64\xC1\xF8\x05"
+    "\xBE\x01\x00\x00\x00\x8D\x04\x02\x0F\xB6\x54\x24\x73\x66\x89\x45"
+    "\x00\x8B\x44\x24\x74\x23\x44\x24\x68\x8B\x6C\x24\x78\xD3\xE0\xB9"
+    "\x08\x00\x00\x00\x2B\x4C\x24\x64\xD3\xFA\x01\xD0\x69\xC0\x00\x06"
+    "\x00\x00\x83\x7C\x24\x60\x06\x8D\x84\x05\x6C\x0E\x00\x00\x89\x44"
+    "\x24\x14\x0F\x8E\xCA\x00\x00\x00\x8B\x44\x24\x74\x2B\x44\x24\x5C"
+    "\x8B\x94\x24\xA0\x00\x00\x00\x0F\xB6\x04\x02\x89\x44\x24\x40\xD1"
+    "\x64\x24\x40\x8B\x4C\x24\x40\x8D\x14\x36\x8B\x6C\x24\x14\x81\xE1"
+    "\x00\x01\x00\x00\x81\x7C\x24\x48\xFF\xFF\xFF\x00\x8D\x44\x4D\x00"
+    "\x89\x4C\x24\x3C\x8D\x2C\x10\x77\x18\x3B\x5C\x24\x4C\x0F\x84\x60"
+    "\x08\x00\x00\xC1\x64\x24\x48\x08\x0F\xB6\x03\xC1\xE7\x08\x43\x09"
+    "\xC7\x8B\x44\x24\x48\x66\x8B\x8D\x00\x02\x00\x00\xC1\xE8\x0B\x0F"
+    "\xB7\xF1\x0F\xAF\xC6\x39\xC7\x73\x23\x89\x44\x24\x48\xB8\x00\x08"
+    "\x00\x00\x29\xF0\x89\xD6\xC1\xF8\x05\x83\x7C\x24\x3C\x00\x8D\x04"
+    "\x01\x66\x89\x85\x00\x02\x00\x00\x74\x22\xEB\x2E\x29\x44\x24\x48"
+    "\x29\xC7\x89\xC8\x8D\x72\x01\x66\xC1\xE8\x05\x66\x29\xC1\x83\x7C"
+    "\x24\x3C\x00\x66\x89\x8D\x00\x02\x00\x00\x74\x0E\x81\xFE\xFF\x00"
+    "\x00\x00\x0F\x8E\x57\xFF\xFF\xFF\xEB\x79\x81\xFE\xFF\x00\x00\x00"
+    "\x7F\x71\x8D\x14\x36\x8B\x6C\x24\x14\x01\xD5\x81\x7C\x24\x48\xFF"
+    "\xFF\xFF\x00\x77\x18\x3B\x5C\x24\x4C\x0F\x84\xC4\x07\x00\x00\xC1"
+    "\x64\x24\x48\x08\x0F\xB6\x03\xC1\xE7\x08\x43\x09\xC7\x8B\x44\x24"
+    "\x48\x66\x8B\x4D\x00\xC1\xE8\x0B\x0F\xB7\xF1\x0F\xAF\xC6\x39\xC7"
+    "\x73\x19\x89\x44\x24\x48\xB8\x00\x08\x00\x00\x29\xF0\x89\xD6\xC1"
+    "\xF8\x05\x8D\x04\x01\x66\x89\x45\x00\xEB\x9F\x29\x44\x24\x48\x29"
+    "\xC7\x89\xC8\x8D\x72\x01\x66\xC1\xE8\x05\x66\x29\xC1\x66\x89\x4D"
+    "\x00\xEB\x87\x8B\x54\x24\x74\x89\xF0\x8B\x8C\x24\xA0\x00\x00\x00"
+    "\x88\x44\x24\x73\x88\x04\x0A\x42\x83\x7C\x24\x60\x03\x89\x54\x24"
+    "\x74\x7F\x0D\xC7\x44\x24\x60\x00\x00\x00\x00\xE9\x1B\x07\x00\x00"
+    "\x83\x7C\x24\x60\x09\x7F\x0A\x83\x6C\x24\x60\x03\xE9\x0A\x07\x00"
+    "\x00\x83\x6C\x24\x60\x06\xE9\x00\x07\x00\x00\x8B\x4C\x24\x48\x29"
+    "\xC7\x8B\x74\x24\x60\x29\xC1\x89\xD0\x66\xC1\xE8\x05\x66\x29\xC2"
+    "\x81\xF9\xFF\xFF\xFF\x00\x66\x89\x55\x00\x8B\x6C\x24\x78\x8D\x74"
+    "\x75\x00\x89\x74\x24\x38\x77\x16\x3B\x5C\x24\x4C\x0F\x84\xF1\x06"
+    "\x00\x00\x0F\xB6\x03\xC1\xE7\x08\xC1\xE1\x08\x43\x09\xC7\x8B\x6C"
+    "\x24\x38\x89\xC8\xC1\xE8\x0B\x66\x8B\x95\x80\x01\x00\x00\x0F\xB7"
+    "\xEA\x0F\xAF\xC5\x39\xC7\x73\x52\x89\xC6\xB8\x00\x08\x00\x00\x29"
+    "\xE8\x8B\x6C\x24\x58\xC1\xF8\x05\x8B\x4C\x24\x54\x8D\x04\x02\x8B"
+    "\x54\x24\x38\x89\x4C\x24\x50\x8B\x4C\x24\x78\x66\x89\x82\x80\x01"
+    "\x00\x00\x8B\x44\x24\x5C\x89\x6C\x24\x54\x89\x44\x24\x58\x31\xC0"
+    "\x83\x7C\x24\x60\x06\x0F\x9F\xC0\x81\xC1\x64\x06\x00\x00\x8D\x04"
+    "\x40\x89\x44\x24\x60\xE9\x74\x02\x00\x00\x89\xCE\x29\xC7\x29\xC6"
+    "\x89\xD0\x66\xC1\xE8\x05\x8B\x4C\x24\x38\x66\x29\xC2\x81\xFE\xFF"
+    "\xFF\xFF\x00\x66\x89\x91\x80\x01\x00\x00\x77\x16\x3B\x5C\x24\x4C"
+    "\x0F\x84\x4D\x06\x00\x00\x0F\xB6\x03\xC1\xE7\x08\xC1\xE6\x08\x43"
+    "\x09\xC7\x8B\x6C\x24\x38\x89\xF2\xC1\xEA\x0B\x66\x8B\x8D\x98\x01"
+    "\x00\x00\x0F\xB7\xC1\x0F\xAF\xD0\x39\xD7\x0F\x83\xE3\x00\x00\x00"
+    "\xBD\x00\x08\x00\x00\x89\xD6\x29\xC5\xC7\x44\x24\x34\x00\x08\x00"
+    "\x00\x89\xE8\xC1\xF8\x05\x8D\x04\x01\x8B\x4C\x24\x38\x66\x89\x81"
+    "\x98\x01\x00\x00\x8B\x44\x24\x60\x8B\x4C\x24\x44\xC1\xE0\x05\x03"
+    "\x44\x24\x78\x81\xFA\xFF\xFF\xFF\x00\x8D\x2C\x48\x77\x16\x3B\x5C"
+    "\x24\x4C\x0F\x84\xDB\x05\x00\x00\x0F\xB6\x03\xC1\xE7\x08\xC1\xE6"
+    "\x08\x43\x09\xC7\x66\x8B\x95\xE0\x01\x00\x00\x89\xF0\xC1\xE8\x0B"
+    "\x0F\xB7\xCA\x0F\xAF\xC1\x39\xC7\x73\x60\x29\x4C\x24\x34\xC1\x7C"
+    "\x24\x34\x05\x8B\x74\x24\x34\x89\x44\x24\x48\x83\x7C\x24\x74\x00"
+    "\x8D\x04\x32\x66\x89\x85\xE0\x01\x00\x00\x0F\x84\x93\x05\x00\x00"
+    "\x31\xC0\x83\x7C\x24\x60\x06\x8B\xAC\x24\xA0\x00\x00\x00\x8B\x54"
+    "\x24\x74\x0F\x9F\xC0\x8D\x44\x00\x09\x89\x44\x24\x60\x8B\x44\x24"
+    "\x74\x2B\x44\x24\x5C\x8A\x44\x05\x00\x88\x44\x24\x73\x88\x04\x2A"
+    "\x42\x89\x54\x24\x74\xE9\x31\x05\x00\x00\x29\xC6\x29\xC7\x89\xD0"
+    "\x66\xC1\xE8\x05\x66\x29\xC2\x66\x89\x95\xE0\x01\x00\x00\xE9\x1F"
+    "\x01\x00\x00\x89\xC8\x29\xD6\x66\xC1\xE8\x05\x8B\x6C\x24\x38\x66"
+    "\x29\xC1\x29\xD7\x81\xFE\xFF\xFF\xFF\x00\x66\x89\x8D\x98\x01\x00"
+    "\x00\x77\x16\x3B\x5C\x24\x4C\x0F\x84\x16\x05\x00\x00\x0F\xB6\x03"
+    "\xC1\xE7\x08\xC1\xE6\x08\x43\x09\xC7\x8B\x4C\x24\x38\x89\xF0\xC1"
+    "\xE8\x0B\x66\x8B\x91\xB0\x01\x00\x00\x0F\xB7\xCA\x0F\xAF\xC1\x39"
+    "\xC7\x73\x23\x89\xC6\xB8\x00\x08\x00\x00\x29\xC8\x8B\x6C\x24\x38"
+    "\xC1\xF8\x05\x8D\x04\x02\x66\x89\x85\xB0\x01\x00\x00\x8B\x44\x24"
+    "\x58\xE9\xA0\x00\x00\x00\x89\xF1\x29\xC7\x29\xC1\x89\xD0\x66\xC1"
+    "\xE8\x05\x66\x29\xC2\x8B\x44\x24\x38\x81\xF9\xFF\xFF\xFF\x00\x66"
+    "\x89\x90\xB0\x01\x00\x00\x77\x16\x3B\x5C\x24\x4C\x0F\x84\xA1\x04"
+    "\x00\x00\x0F\xB6\x03\xC1\xE7\x08\xC1\xE1\x08\x43\x09\xC7\x8B\x74"
+    "\x24\x38\x89\xC8\xC1\xE8\x0B\x66\x8B\x96\xC8\x01\x00\x00\x0F\xB7"
+    "\xEA\x0F\xAF\xC5\x39\xC7\x73\x20\x89\xC6\xB8\x00\x08\x00\x00\x29"
+    "\xE8\x8B\x6C\x24\x38\xC1\xF8\x05\x8D\x04\x02\x66\x89\x85\xC8\x01"
+    "\x00\x00\x8B\x44\x24\x54\xEB\x26\x89\xCE\x29\xC7\x29\xC6\x89\xD0"
+    "\x66\xC1\xE8\x05\x66\x29\xC2\x8B\x44\x24\x38\x66\x89\x90\xC8\x01"
+    "\x00\x00\x8B\x54\x24\x54\x8B\x44\x24\x50\x89\x54\x24\x50\x8B\x4C"
+    "\x24\x58\x89\x4C\x24\x54\x8B\x6C\x24\x5C\x89\x44\x24\x5C\x89\x6C"
+    "\x24\x58\x31\xC0\x83\x7C\x24\x60\x06\x8B\x4C\x24\x78\x0F\x9F\xC0"
+    "\x81\xC1\x68\x0A\x00\x00\x8D\x44\x40\x08\x89\x44\x24\x60\x81\xFE"
+    "\xFF\xFF\xFF\x00\x77\x16\x3B\x5C\x24\x4C\x0F\x84\xF3\x03\x00\x00"
+    "\x0F\xB6\x03\xC1\xE7\x08\xC1\xE6\x08\x43\x09\xC7\x66\x8B\x11\x89"
+    "\xF0\xC1\xE8\x0B\x0F\xB7\xEA\x0F\xAF\xC5\x39\xC7\x73\x2F\x89\x44"
+    "\x24\x48\xB8\x00\x08\x00\x00\x29\xE8\xC1\x64\x24\x44\x04\xC1\xF8"
+    "\x05\xC7\x44\x24\x2C\x00\x00\x00\x00\x8D\x04\x02\x66\x89\x01\x8B"
+    "\x44\x24\x44\x8D\x4C\x01\x04\x89\x4C\x24\x10\xEB\x72\x29\xC6\x29"
+    "\xC7\x89\xD0\x66\xC1\xE8\x05\x66\x29\xC2\x81\xFE\xFF\xFF\xFF\x00"
+    "\x66\x89\x11\x77\x16\x3B\x5C\x24\x4C\x0F\x84\x84\x03\x00\x00\x0F"
+    "\xB6\x03\xC1\xE7\x08\xC1\xE6\x08\x43\x09\xC7\x66\x8B\x51\x02\x89"
+    "\xF0\xC1\xE8\x0B\x0F\xB7\xEA\x0F\xAF\xC5\x39\xC7\x73\x3B\x89\x44"
+    "\x24\x48\xB8\x00\x08\x00\x00\x29\xE8\xC1\x64\x24\x44\x04\xC1\xF8"
+    "\x05\xC7\x44\x24\x2C\x08\x00\x00\x00\x8D\x04\x02\x8B\x54\x24\x44"
+    "\x66\x89\x41\x02\x8D\x8C\x11\x04\x01\x00\x00\x89\x4C\x24\x10\xC7"
+    "\x44\x24\x30\x03\x00\x00\x00\xEB\x2F\x29\xC6\x29\xC7\x89\xD0\x89"
+    "\x74\x24\x48\x66\xC1\xE8\x05\xC7\x44\x24\x2C\x10\x00\x00\x00\x66"
+    "\x29\xC2\xC7\x44\x24\x30\x08\x00\x00\x00\x66\x89\x51\x02\x81\xC1"
+    "\x04\x02\x00\x00\x89\x4C\x24\x10\x8B\x4C\x24\x30\xBA\x01\x00\x00"
+    "\x00\x89\x4C\x24\x28\x8D\x2C\x12\x8B\x74\x24\x10\x01\xEE\x81\x7C"
+    "\x24\x48\xFF\xFF\xFF\x00\x77\x18\x3B\x5C\x24\x4C\x0F\x84\xD1\x02"
+    "\x00\x00\xC1\x64\x24\x48\x08\x0F\xB6\x03\xC1\xE7\x08\x43\x09\xC7"
+    "\x8B\x44\x24\x48\x66\x8B\x16\xC1\xE8\x0B\x0F\xB7\xCA\x0F\xAF\xC1"
+    "\x39\xC7\x73\x18\x89\x44\x24\x48\xB8\x00\x08\x00\x00\x29\xC8\xC1"
+    "\xF8\x05\x8D\x04\x02\x89\xEA\x66\x89\x06\xEB\x15\x29\x44\x24\x48"
+    "\x29\xC7\x89\xD0\x66\xC1\xE8\x05\x66\x29\xC2\x66\x89\x16\x8D\x55"
+    "\x01\x8B\x74\x24\x28\x4E\x89\x74\x24\x28\x75\x89\x8A\x4C\x24\x30"
+    "\xB8\x01\x00\x00\x00\xD3\xE0\x29\xC2\x03\x54\x24\x2C\x83\x7C\x24"
+    "\x60\x03\x89\x54\x24\x0C\x0F\x8F\xE7\x01\x00\x00\x83\x44\x24\x60"
+    "\x07\x83\xFA\x03\x89\xD0\x7E\x05\xB8\x03\x00\x00\x00\x8B\x74\x24"
+    "\x78\xC1\xE0\x07\xC7\x44\x24\x24\x06\x00\x00\x00\x8D\x84\x06\x60"
+    "\x03\x00\x00\x89\x44\x24\x08\xB8\x01\x00\x00\x00\x8D\x2C\x00\x8B"
+    "\x74\x24\x08\x01\xEE\x81\x7C\x24\x48\xFF\xFF\xFF\x00\x77\x18\x3B"
+    "\x5C\x24\x4C\x0F\x84\x0A\x02\x00\x00\xC1\x64\x24\x48\x08\x0F\xB6"
+    "\x03\xC1\xE7\x08\x43\x09\xC7\x8B\x44\x24\x48\x66\x8B\x16\xC1\xE8"
+    "\x0B\x0F\xB7\xCA\x0F\xAF\xC1\x39\xC7\x73\x18\x89\x44\x24\x48\xB8"
+    "\x00\x08\x00\x00\x29\xC8\xC1\xF8\x05\x8D\x04\x02\x66\x89\x06\x89"
+    "\xE8\xEB\x15\x29\x44\x24\x48\x29\xC7\x89\xD0\x66\xC1\xE8\x05\x66"
+    "\x29\xC2\x8D\x45\x01\x66\x89\x16\x8B\x6C\x24\x24\x4D\x89\x6C\x24"
+    "\x24\x75\x89\x8D\x50\xC0\x83\xFA\x03\x89\x14\x24\x0F\x8E\x27\x01"
+    "\x00\x00\x89\xD0\x89\xD6\xD1\xF8\x83\xE6\x01\x8D\x48\xFF\x83\xCE"
+    "\x02\x83\xFA\x0D\x89\x4C\x24\x20\x7F\x1C\x8B\x6C\x24\x78\xD3\xE6"
+    "\x01\xD2\x89\x34\x24\x8D\x44\x75\x00\x29\xD0\x05\x5E\x05\x00\x00"
+    "\x89\x44\x24\x04\xEB\x56\x8D\x50\xFB\x81\x7C\x24\x48\xFF\xFF\xFF"
+    "\x00\x77\x18\x3B\x5C\x24\x4C\x0F\x84\x56\x01\x00\x00\xC1\x64\x24"
+    "\x48\x08\x0F\xB6\x03\xC1\xE7\x08\x43\x09\xC7\xD1\x6C\x24\x48\x01"
+    "\xF6\x3B\x7C\x24\x48\x72\x07\x2B\x7C\x24\x48\x83\xCE\x01\x4A\x75"
+    "\xC8\x8B\x44\x24\x78\xC1\xE6\x04\x89\x34\x24\x05\x44\x06\x00\x00"
+    "\xC7\x44\x24\x20\x04\x00\x00\x00\x89\x44\x24\x04\xC7\x44\x24\x1C"
+    "\x01\x00\x00\x00\xB8\x01\x00\x00\x00\x8B\x6C\x24\x04\x01\xC0\x89"
+    "\x44\x24\x18\x01\xC5\x81\x7C\x24\x48\xFF\xFF\xFF\x00\x77\x18\x3B"
+    "\x5C\x24\x4C\x0F\x84\xEA\x00\x00\x00\xC1\x64\x24\x48\x08\x0F\xB6"
+    "\x03\xC1\xE7\x08\x43\x09\xC7\x8B\x44\x24\x48\x66\x8B\x55\x00\xC1"
+    "\xE8\x0B\x0F\xB7\xF2\x0F\xAF\xC6\x39\xC7\x73\x1B\x89\x44\x24\x48"
+    "\xB8\x00\x08\x00\x00\x29\xF0\xC1\xF8\x05\x8D\x04\x02\x66\x89\x45"
+    "\x00\x8B\x44\x24\x18\xEB\x1F\x29\x44\x24\x48\x29\xC7\x89\xD0\x66"
+    "\xC1\xE8\x05\x66\x29\xC2\x8B\x44\x24\x18\x66\x89\x55\x00\x8B\x54"
+    "\x24\x1C\x40\x09\x14\x24\x8B\x4C\x24\x20\xD1\x64\x24\x1C\x49\x89"
+    "\x4C\x24\x20\x0F\x85\x70\xFF\xFF\xFF\x8B\x34\x24\x46\x89\x74\x24"
+    "\x5C\x74\x59\x8B\x4C\x24\x0C\x8B\x6C\x24\x74\x83\xC1\x02\x39\x6C"
+    "\x24\x5C\x77\x5F\x8B\x84\x24\xA0\x00\x00\x00\x89\xEA\x2B\x44\x24"
+    "\x5C\x03\x94\x24\xA0\x00\x00\x00\x8D\x34\x28\x8A\x06\x46\x88\x44"
+    "\x24\x73\x88\x02\x42\xFF\x44\x24\x74\x49\x74\x0F\x8B\xAC\x24\xA4"
+    "\x00\x00\x00\x39\x6C\x24\x74\x72\xE2\xEB\x11\x8B\x84\x24\xA4\x00"
+    "\x00\x00\x39\x44\x24\x74\x0F\x82\xBB\xF6\xFF\xFF\x81\x7C\x24\x48"
+    "\xFF\xFF\xFF\x00\x77\x15\x3B\x5C\x24\x4C\xB8\x01\x00\x00\x00\x74"
+    "\x29\xEB\x07\xB8\x01\x00\x00\x00\xEB\x20\x43\x2B\x9C\x24\x94\x00"
+    "\x00\x00\x31\xC0\x8B\x94\x24\x9C\x00\x00\x00\x8B\x4C\x24\x74\x89"
+    "\x1A\x8B\x9C\x24\xA8\x00\x00\x00\x89\x0B\x83\xC4\x7C\x5B\x5E\x5F"
+    "\x5D\x55\x57\x56\x53\x83\xEC\x7C\x8B\x94\x24\x90\x00\x00\x00\xC7"
+    "\x44\x24\x74\x00\x00\x00\x00\xC6\x44\x24\x73\x00\x8B\xAC\x24\x9C"
+    "\x00\x00\x00\x8D\x42\x04\x89\x44\x24\x78\xB8\x01\x00\x00\x00\x0F"
+    "\xB6\x4A\x02\x89\xC3\xD3\xE3\x89\xD9\x49\x89\x4C\x24\x6C\x0F\xB6"
+    "\x4A\x01\xD3\xE0\x48\x89\x44\x24\x68\x8B\x84\x24\xA8\x00\x00\x00"
+    "\x0F\xB6\x32\xC7\x45\x00\x00\x00\x00\x00\xC7\x44\x24\x60\x00\x00"
+    "\x00\x00\xC7\x00\x00\x00\x00\x00\xB8\x00\x03\x00\x00\x89\x74\x24"
+    "\x64\xC7\x44\x24\x5C\x01\x00\x00\x00\xC7\x44\x24\x58\x01\x00\x00"
+    "\x00\xC7\x44\x24\x54\x01\x00\x00\x00\xC7\x44\x24\x50\x01\x00\x00"
+    "\x00\x0F\xB6\x4A\x01\x01\xF1\xD3\xE0\x8D\x88\x36\x07\x00\x00\x39"
+    "\x4C\x24\x74\x73\x0E\x8B\x44\x24\x78\x66\xC7\x00\x00\x04\x83\xC0"
+    "\x02\xE2\xF6\x8B\x9C\x24\x94\x00\x00\x00\x31\xFF\xC7\x44\x24\x48"
+    "\xFF\xFF\xFF\xFF\x89\xDA\x03\x94\x24\x98\x00\x00\x00\x89\x54\x24"
+    "\x4C\x31\xD2\x3B\x5C\x24\x4C\x0F\x84\x7C\x09\x00\x00\x0F\xB6\x03"
+    "\xC1\xE7\x08\x42\x43\x09\xC7\x83\xFA\x04\x7E\xE7\x8B\x8C\x24\xA4"
+    "\x00\x00\x00\x39\x4C\x24\x74\x0F\x83\x64\x09\x00\x00\x8B\x74\x24"
+    "\x74\x23\x74\x24\x6C\x8B\x44\x24\x60\x8B\x54\x24\x78\xC1\xE0\x04"
+    "\x89\x74\x24\x44\x01\xF0\x81\x7C\x24\x48\xFF\xFF\xFF\x00\x8D\x2C"
+    "\x42\x77\x18\x3B\x5C\x24\x4C\x0F\x84\x2C\x09\x00\x00\xC1\x64\x24"
+    "\x48\x08\x0F\xB6\x03\xC1\xE7\x08\x43\x09\xC7\x8B\x44\x24\x48\x66"
+    "\x8B\x55\x00\xC1\xE8\x0B\x0F\xB7\xCA\x0F\xAF\xC1\x39\xC7\x0F\x83"
+    "\xDD\x01\x00\x00\x89\x44\x24\x48\xB8\x00\x08\x00\x00\x29\xC8\x8A"
+    "\x4C\x24\x64\xC1\xF8\x05\xBE\x01\x00\x00\x00\x8D\x04\x02\x0F\xB6"
+    "\x54\x24\x73\x66\x89\x45\x00\x8B\x44\x24\x74\x23\x44\x24\x68\x8B"
+    "\x6C\x24\x78\xD3\xE0\xB9\x08\x00\x00\x00\x2B\x4C\x24\x64\xD3\xFA"
+    "\x01\xD0\x69\xC0\x00\x06\x00\x00\x83\x7C\x24\x60\x06\x8D\x84\x05"
+    "\x6C\x0E\x00\x00\x89\x44\x24\x14\x0F\x8E\xCA\x00\x00\x00\x8B\x44"
+    "\x24\x74\x2B\x44\x24\x5C\x8B\x94\x24\xA0\x00\x00\x00\x0F\xB6\x04"
+    "\x02\x89\x44\x24\x40\xD1\x64\x24\x40\x8B\x4C\x24\x40\x8D\x14\x36"
+    "\x8B\x6C\x24\x14\x81\xE1\x00\x01\x00\x00\x81\x7C\x24\x48\xFF\xFF"
+    "\xFF\x00\x8D\x44\x4D\x00\x89\x4C\x24\x3C\x8D\x2C\x10\x77\x18\x3B"
+    "\x5C\x24\x4C\x0F\x84\x60\x08\x00\x00\xC1\x64\x24\x48\x08\x0F\xB6"
+    "\x03\xC1\xE7\x08\x43\x09\xC7\x8B\x44\x24\x48\x66\x8B\x8D\x00\x02"
+    "\x00\x00\xC1\xE8\x0B\x0F\xB7\xF1\x0F\xAF\xC6\x39\xC7\x73\x23\x89"
+    "\x44\x24\x48\xB8\x00\x08\x00\x00\x29\xF0\x89\xD6\xC1\xF8\x05\x83"
+    "\x7C\x24\x3C\x00\x8D\x04\x01\x66\x89\x85\x00\x02\x00\x00\x74\x22"
+    "\xEB\x2E\x29\x44\x24\x48\x29\xC7\x89\xC8\x8D\x72\x01\x66\xC1\xE8"
+    "\x05\x66\x29\xC1\x83\x7C\x24\x3C\x00\x66\x89\x8D\x00\x02\x00\x00"
+    "\x74\x0E\x81\xFE\xFF\x00\x00\x00\x0F\x8E\x57\xFF\xFF\xFF\xEB\x79"
+    "\x81\xFE\xFF\x00\x00\x00\x7F\x71\x8D\x14\x36\x8B\x6C\x24\x14\x01"
+    "\xD5\x81\x7C\x24\x48\xFF\xFF\xFF\x00\x77\x18\x3B\x5C\x24\x4C\x0F"
+    "\x84\xC4\x07\x00\x00\xC1\x64\x24\x48\x08\x0F\xB6\x03\xC1\xE7\x08"
+    "\x43\x09\xC7\x8B\x44\x24\x48\x66\x8B\x4D\x00\xC1\xE8\x0B\x0F\xB7"
+    "\xF1\x0F\xAF\xC6\x39\xC7\x73\x19\x89\x44\x24\x48\xB8\x00\x08\x00"
+    "\x00\x29\xF0\x89\xD6\xC1\xF8\x05\x8D\x04\x01\x66\x89\x45\x00\xEB"
+    "\x9F\x29\x44\x24\x48\x29\xC7\x89\xC8\x8D\x72\x01\x66\xC1\xE8\x05"
+    "\x66\x29\xC1\x66\x89\x4D\x00\xEB\x87\x8B\x54\x24\x74\x89\xF0\x8B"
+    "\x8C\x24\xA0\x00\x00\x00\x88\x44\x24\x73\x88\x04\x0A\x42\x83\x7C"
+    "\x24\x60\x03\x89\x54\x24\x74\x7F\x0D\xC7\x44\x24\x60\x00\x00\x00"
+    "\x00\xE9\x1B\x07\x00\x00\x83\x7C\x24\x60\x09\x7F\x0A\x83\x6C\x24"
+    "\x60\x03\xE9\x0A\x07\x00\x00\x83\x6C\x24\x60\x06\xE9\x00\x07\x00"
+    "\x00\x8B\x4C\x24\x48\x29\xC7\x8B\x74\x24\x60\x29\xC1\x89\xD0\x66"
+    "\xC1\xE8\x05\x66\x29\xC2\x81\xF9\xFF\xFF\xFF\x00\x66\x89\x55\x00"
+    "\x8B\x6C\x24\x78\x8D\x74\x75\x00\x89\x74\x24\x38\x77\x16\x3B\x5C"
+    "\x24\x4C\x0F\x84\xF1\x06\x00\x00\x0F\xB6\x03\xC1\xE7\x08\xC1\xE1"
+    "\x08\x43\x09\xC7\x8B\x6C\x24\x38\x89\xC8\xC1\xE8\x0B\x66\x8B\x95"
+    "\x80\x01\x00\x00\x0F\xB7\xEA\x0F\xAF\xC5\x39\xC7\x73\x52\x89\xC6"
+    "\xB8\x00\x08\x00\x00\x29\xE8\x8B\x6C\x24\x58\xC1\xF8\x05\x8B\x4C"
+    "\x24\x54\x8D\x04\x02\x8B\x54\x24\x38\x89\x4C\x24\x50\x8B\x4C\x24"
+    "\x78\x66\x89\x82\x80\x01\x00\x00\x8B\x44\x24\x5C\x89\x6C\x24\x54"
+    "\x89\x44\x24\x58\x31\xC0\x83\x7C\x24\x60\x06\x0F\x9F\xC0\x81\xC1"
+    "\x64\x06\x00\x00\x8D\x04\x40\x89\x44\x24\x60\xE9\x74\x02\x00\x00"
+    "\x89\xCE\x29\xC7\x29\xC6\x89\xD0\x66\xC1\xE8\x05\x8B\x4C\x24\x38"
+    "\x66\x29\xC2\x81\xFE\xFF\xFF\xFF\x00\x66\x89\x91\x80\x01\x00\x00"
+    "\x77\x16\x3B\x5C\x24\x4C\x0F\x84\x4D\x06\x00\x00\x0F\xB6\x03\xC1"
+    "\xE7\x08\xC1\xE6\x08\x43\x09\xC7\x8B\x6C\x24\x38\x89\xF2\xC1\xEA"
+    "\x0B\x66\x8B\x8D\x98\x01\x00\x00\x0F\xB7\xC1\x0F\xAF\xD0\x39\xD7"
+    "\x0F\x83\xE3\x00\x00\x00\xBD\x00\x08\x00\x00\x89\xD6\x29\xC5\xC7"
+    "\x44\x24\x34\x00\x08\x00\x00\x89\xE8\xC1\xF8\x05\x8D\x04\x01\x8B"
+    "\x4C\x24\x38\x66\x89\x81\x98\x01\x00\x00\x8B\x44\x24\x60\x8B\x4C"
+    "\x24\x44\xC1\xE0\x05\x03\x44\x24\x78\x81\xFA\xFF\xFF\xFF\x00\x8D"
+    "\x2C\x48\x77\x16\x3B\x5C\x24\x4C\x0F\x84\xDB\x05\x00\x00\x0F\xB6"
+    "\x03\xC1\xE7\x08\xC1\xE6\x08\x43\x09\xC7\x66\x8B\x95\xE0\x01\x00"
+    "\x00\x89\xF0\xC1\xE8\x0B\x0F\xB7\xCA\x0F\xAF\xC1\x39\xC7\x73\x60"
+    "\x29\x4C\x24\x34\xC1\x7C\x24\x34\x05\x8B\x74\x24\x34\x89\x44\x24"
+    "\x48\x83\x7C\x24\x74\x00\x8D\x04\x32\x66\x89\x85\xE0\x01\x00\x00"
+    "\x0F\x84\x93\x05\x00\x00\x31\xC0\x83\x7C\x24\x60\x06\x8B\xAC\x24"
+    "\xA0\x00\x00\x00\x8B\x54\x24\x74\x0F\x9F\xC0\x8D\x44\x00\x09\x89"
+    "\x44\x24\x60\x8B\x44\x24\x74\x2B\x44\x24\x5C\x8A\x44\x05\x00\x88"
+    "\x44\x24\x73\x88\x04\x2A\x42\x89\x54\x24\x74\xE9\x31\x05\x00\x00"
+    "\x29\xC6\x29\xC7\x89\xD0\x66\xC1\xE8\x05\x66\x29\xC2\x66\x89\x95"
+    "\xE0\x01\x00\x00\xE9\x1F\x01\x00\x00\x89\xC8\x29\xD6\x66\xC1\xE8"
+    "\x05\x8B\x6C\x24\x38\x66\x29\xC1\x29\xD7\x81\xFE\xFF\xFF\xFF\x00"
+    "\x66\x89\x8D\x98\x01\x00\x00\x77\x16\x3B\x5C\x24\x4C\x0F\x84\x16"
+    "\x05\x00\x00\x0F\xB6\x03\xC1\xE7\x08\xC1\xE6\x08\x43\x09\xC7\x8B"
+    "\x4C\x24\x38\x89\xF0\xC1\xE8\x0B\x66\x8B\x91\xB0\x01\x00\x00\x0F"
+    "\xB7\xCA\x0F\xAF\xC1\x39\xC7\x73\x23\x89\xC6\xB8\x00\x08\x00\x00"
+    "\x29\xC8\x8B\x6C\x24\x38\xC1\xF8\x05\x8D\x04\x02\x66\x89\x85\xB0"
+    "\x01\x00\x00\x8B\x44\x24\x58\xE9\xA0\x00\x00\x00\x89\xF1\x29\xC7"
+    "\x29\xC1\x89\xD0\x66\xC1\xE8\x05\x66\x29\xC2\x8B\x44\x24\x38\x81"
+    "\xF9\xFF\xFF\xFF\x00\x66\x89\x90\xB0\x01\x00\x00\x77\x16\x3B\x5C"
+    "\x24\x4C\x0F\x84\xA1\x04\x00\x00\x0F\xB6\x03\xC1\xE7\x08\xC1\xE1"
+    "\x08\x43\x09\xC7\x8B\x74\x24\x38\x89\xC8\xC1\xE8\x0B\x66\x8B\x96"
+    "\xC8\x01\x00\x00\x0F\xB7\xEA\x0F\xAF\xC5\x39\xC7\x73\x20\x89\xC6"
+    "\xB8\x00\x08\x00\x00\x29\xE8\x8B\x6C\x24\x38\xC1\xF8\x05\x8D\x04"
+    "\x02\x66\x89\x85\xC8\x01\x00\x00\x8B\x44\x24\x54\xEB\x26\x89\xCE"
+    "\x29\xC7\x29\xC6\x89\xD0\x66\xC1\xE8\x05\x66\x29\xC2\x8B\x44\x24"
+    "\x38\x66\x89\x90\xC8\x01\x00\x00\x8B\x54\x24\x54\x8B\x44\x24\x50"
+    "\x89\x54\x24\x50\x8B\x4C\x24\x58\x89\x4C\x24\x54\x8B\x6C\x24\x5C"
+    "\x89\x44\x24\x5C\x89\x6C\x24\x58\x31\xC0\x83\x7C\x24\x60\x06\x8B"
+    "\x4C\x24\x78\x0F\x9F\xC0\x81\xC1\x68\x0A\x00\x00\x8D\x44\x40\x08"
+    "\x89\x44\x24\x60\x81\xFE\xFF\xFF\xFF\x00\x77\x16\x3B\x5C\x24\x4C"
+    "\x0F\x84\xF3\x03\x00\x00\x0F\xB6\x03\xC1\xE7\x08\xC1\xE6\x08\x43"
+    "\x09\xC7\x66\x8B\x11\x89\xF0\xC1\xE8\x0B\x0F\xB7\xEA\x0F\xAF\xC5"
+    "\x39\xC7\x73\x2F\x89\x44\x24\x48\xB8\x00\x08\x00\x00\x29\xE8\xC1"
+    "\x64\x24\x44\x04\xC1\xF8\x05\xC7\x44\x24\x2C\x00\x00\x00\x00\x8D"
+    "\x04\x02\x66\x89\x01\x8B\x44\x24\x44\x8D\x4C\x01\x04\x89\x4C\x24"
+    "\x10\xEB\x72\x29\xC6\x29\xC7\x89\xD0\x66\xC1\xE8\x05\x66\x29\xC2"
+    "\x81\xFE\xFF\xFF\xFF\x00\x66\x89\x11\x77\x16\x3B\x5C\x24\x4C\x0F"
+    "\x84\x84\x03\x00\x00\x0F\xB6\x03\xC1\xE7\x08\xC1\xE6\x08\x43\x09"
+    "\xC7\x66\x8B\x51\x02\x89\xF0\xC1\xE8\x0B\x0F\xB7\xEA\x0F\xAF\xC5"
+    "\x39\xC7\x73\x3B\x89\x44\x24\x48\xB8\x00\x08\x00\x00\x29\xE8\xC1"
+    "\x64\x24\x44\x04\xC1\xF8\x05\xC7\x44\x24\x2C\x08\x00\x00\x00\x8D"
+    "\x04\x02\x8B\x54\x24\x44\x66\x89\x41\x02\x8D\x8C\x11\x04\x01\x00"
+    "\x00\x89\x4C\x24\x10\xC7\x44\x24\x30\x03\x00\x00\x00\xEB\x2F\x29"
+    "\xC6\x29\xC7\x89\xD0\x89\x74\x24\x48\x66\xC1\xE8\x05\xC7\x44\x24"
+    "\x2C\x10\x00\x00\x00\x66\x29\xC2\xC7\x44\x24\x30\x08\x00\x00\x00"
+    "\x66\x89\x51\x02\x81\xC1\x04\x02\x00\x00\x89\x4C\x24\x10\x8B\x4C"
+    "\x24\x30\xBA\x01\x00\x00\x00\x89\x4C\x24\x28\x8D\x2C\x12\x8B\x74"
+    "\x24\x10\x01\xEE\x81\x7C\x24\x48\xFF\xFF\xFF\x00\x77\x18\x3B\x5C"
+    "\x24\x4C\x0F\x84\xD1\x02\x00\x00\xC1\x64\x24\x48\x08\x0F\xB6\x03"
+    "\xC1\xE7\x08\x43\x09\xC7\x8B\x44\x24\x48\x66\x8B\x16\xC1\xE8\x0B"
+    "\x0F\xB7\xCA\x0F\xAF\xC1\x39\xC7\x73\x18\x89\x44\x24\x48\xB8\x00"
+    "\x08\x00\x00\x29\xC8\xC1\xF8\x05\x8D\x04\x02\x89\xEA\x66\x89\x06"
+    "\xEB\x15\x29\x44\x24\x48\x29\xC7\x89\xD0\x66\xC1\xE8\x05\x66\x29"
+    "\xC2\x66\x89\x16\x8D\x55\x01\x8B\x74\x24\x28\x4E\x89\x74\x24\x28"
+    "\x75\x89\x8A\x4C\x24\x30\xB8\x01\x00\x00\x00\xD3\xE0\x29\xC2\x03"
+    "\x54\x24\x2C\x83\x7C\x24\x60\x03\x89\x54\x24\x0C\x0F\x8F\xE7\x01"
+    "\x00\x00\x83\x44\x24\x60\x07\x83\xFA\x03\x89\xD0\x7E\x05\xB8\x03"
+    "\x00\x00\x00\x8B\x74\x24\x78\xC1\xE0\x07\xC7\x44\x24\x24\x06\x00"
+    "\x00\x00\x8D\x84\x06\x60\x03\x00\x00\x89\x44\x24\x08\xB8\x01\x00"
+    "\x00\x00\x8D\x2C\x00\x8B\x74\x24\x08\x01\xEE\x81\x7C\x24\x48\xFF"
+    "\xFF\xFF\x00\x77\x18\x3B\x5C\x24\x4C\x0F\x84\x0A\x02\x00\x00\xC1"
+    "\x64\x24\x48\x08\x0F\xB6\x03\xC1\xE7\x08\x43\x09\xC7\x8B\x44\x24"
+    "\x48\x66\x8B\x16\xC1\xE8\x0B\x0F\xB7\xCA\x0F\xAF\xC1\x39\xC7\x73"
+    "\x18\x89\x44\x24\x48\xB8\x00\x08\x00\x00\x29\xC8\xC1\xF8\x05\x8D"
+    "\x04\x02\x66\x89\x06\x89\xE8\xEB\x15\x29\x44\x24\x48\x29\xC7\x89"
+    "\xD0\x66\xC1\xE8\x05\x66\x29\xC2\x8D\x45\x01\x66\x89\x16\x8B\x6C"
+    "\x24\x24\x4D\x89\x6C\x24\x24\x75\x89\x8D\x50\xC0\x83\xFA\x03\x89"
+    "\x14\x24\x0F\x8E\x27\x01\x00\x00\x89\xD0\x89\xD6\xD1\xF8\x83\xE6"
+    "\x01\x8D\x48\xFF\x83\xCE\x02\x83\xFA\x0D\x89\x4C\x24\x20\x7F\x1C"
+    "\x8B\x6C\x24\x78\xD3\xE6\x01\xD2\x89\x34\x24\x8D\x44\x75\x00\x29"
+    "\xD0\x05\x5E\x05\x00\x00\x89\x44\x24\x04\xEB\x56\x8D\x50\xFB\x81"
+    "\x7C\x24\x48\xFF\xFF\xFF\x00\x77\x18\x3B\x5C\x24\x4C\x0F\x84\x56"
+    "\x01\x00\x00\xC1\x64\x24\x48\x08\x0F\xB6\x03\xC1\xE7\x08\x43\x09"
+    "\xC7\xD1\x6C\x24\x48\x01\xF6\x3B\x7C\x24\x48\x72\x07\x2B\x7C\x24"
+    "\x48\x83\xCE\x01\x4A\x75\xC8\x8B\x44\x24\x78\xC1\xE6\x04\x89\x34"
+    "\x24\x05\x44\x06\x00\x00\xC7\x44\x24\x20\x04\x00\x00\x00\x89\x44"
+    "\x24\x04\xC7\x44\x24\x1C\x01\x00\x00\x00\xB8\x01\x00\x00\x00\x8B"
+    "\x6C\x24\x04\x01\xC0\x89\x44\x24\x18\x01\xC5\x81\x7C\x24\x48\xFF"
+    "\xFF\xFF\x00\x77\x18\x3B\x5C\x24\x4C\x0F\x84\xEA\x00\x00\x00\xC1"
+    "\x64\x24\x48\x08\x0F\xB6\x03\xC1\xE7\x08\x43\x09\xC7\x8B\x44\x24"
+    "\x48\x66\x8B\x55\x00\xC1\xE8\x0B\x0F\xB7\xF2\x0F\xAF\xC6\x39\xC7"
+    "\x73\x1B\x89\x44\x24\x48\xB8\x00\x08\x00\x00\x29\xF0\xC1\xF8\x05"
+    "\x8D\x04\x02\x66\x89\x45\x00\x8B\x44\x24\x18\xEB\x1F\x29\x44\x24"
+    "\x48\x29\xC7\x89\xD0\x66\xC1\xE8\x05\x66\x29\xC2\x8B\x44\x24\x18"
+    "\x66\x89\x55\x00\x8B\x54\x24\x1C\x40\x09\x14\x24\x8B\x4C\x24\x20"
+    "\xD1\x64\x24\x1C\x49\x89\x4C\x24\x20\x0F\x85\x70\xFF\xFF\xFF\x8B"
+    "\x34\x24\x46\x89\x74\x24\x5C\x74\x59\x8B\x4C\x24\x0C\x8B\x6C\x24"
+    "\x74\x83\xC1\x02\x39\x6C\x24\x5C\x77\x5F\x8B\x84\x24\xA0\x00\x00"
+    "\x00\x89\xEA\x2B\x44\x24\x5C\x03\x94\x24\xA0\x00\x00\x00\x8D\x34"
+    "\x28\x8A\x06\x46\x88\x44\x24\x73\x88\x02\x42\xFF\x44\x24\x74\x49"
+    "\x74\x0F\x8B\xAC\x24\xA4\x00\x00\x00\x39\x6C\x24\x74\x72\xE2\xEB"
+    "\x11\x8B\x84\x24\xA4\x00\x00\x00\x39\x44\x24\x74\x0F\x82\xBB\xF6"
+    "\xFF\xFF\x81\x7C\x24\x48\xFF\xFF\xFF\x00\x77\x15\x3B\x5C\x24\x4C"
+    "\xB8\x01\x00\x00\x00\x74\x29\xEB\x07\xB8\x01\x00\x00\x00\xEB\x20"
+    "\x43\x2B\x9C\x24\x94\x00\x00\x00\x31\xC0\x8B\x94\x24\x9C\x00\x00"
+    "\x00\x8B\x4C\x24\x74\x89\x1A\x8B\x9C\x24\xA8\x00\x00\x00\x89\x0B"
+    "\x83\xC4\x7C\x5B\x5E\x5F\x5D\x03\x73\xFC\x03\x7B\xF8\x31\xC0\x8D"
+    "\x8C\x24\x00\xFF\xFF\xFF\x89\xEC\x50\x39\xCC\x75\xFB\x89\xEC\x31"
+    "\xC9\x5E\x8D\xBE\x00\x00\x00\x00\x89\xF7\xB9\x00\x00\x00\x00\x8A"
+    "\x07\x47\x2C\xE8\x3C\x01\x77\xF7\x80\x3F\x00\x75\x04\x8B\x07\x8A"
+    "\x5F\x04\x66\xC1\xE8\x08\x86\xC4\xC1\xC0\x10\x86\xC4\x29\xF8\x80"
+    "\xEB\xE8\x01\xF0\x89\x07\x83\xC7\x05\x88\xD8\xE2\x09\xB9\x00\x00"
+    "\x00\x00\xB0\xE8\xB0\xE9\xF2\xAE\x75\x06\x80\x3F\x00\x75\xFF\x8B"
+    "\x07\x66\xC1\xE8\x08\x86\xC4\xC1\xC0\x10\x86\xC4\x29\xF8\x01\xF0"
+    "\xAB\xEB\x04\xB9\x00\x00\x00\x00\xEB\x1E\x8A\x07\x83\xC7\x01\x3C"
+    "\x80\x72\x0A\x3C\x8F\x77\x06\x80\x7F\xFE\x0F\x74\x05\x2C\xE8\x3C"
+    "\x01\x77\xFF\x80\x3F\x00\x75\xFF\x8B\x07\x66\xC1\xE8\x08\xC1\xC0"
+    "\x10\x86\xC4\x29\xF8\x01\xF0\x89\x07\x83\xC7\x04\x83\xE9\x04\x8A"
+    "\x07\x83\xC7\x01\xE2\x0D\x83\xE9\x01\x7F\x06\x8D\xBE\x00\x00\x00"
+    "\x00\x8B\x07\x09\xC0\x74\xFF\x8B\x5F\x04\x8D\x84\x30\x00\x00\x00"
+    "\x00\x01\xF3\x50\x83\xC7\x08\xFF\x96\x00\x00\x00\x00\x95\x8A\x07"
+    "\x47\x08\xC0\x74\xDC\x89\xF9\x79\x06\x7A\x0E\x8B\x07\x83\xC7\x04"
+    "\x8B\x84\x30\x00\x00\x00\x00\xEB\x0E\x0F\xB7\x07\x47\x50\x47\xB9"
+    "\x57\x48\xF2\xAE\x55\xFF\x96\x00\x00\x00\x00\x09\xC0\x74\x07\x89"
+    "\x03\x83\xC3\x04\xEB\x22\x61\x31\xC0\xC2\x0C\x00\xFF\x96\x00\x00"
+    "\x00\x00\x8D\xBE\x00\x00\x00\x00\x83\xC7\x04\x8D\x5E\xFC\x31\xC0"
+    "\x8A\x07\x47\x09\xC0\x74\x01\x3C\xEF\x77\x11\x01\xC3\x8B\x03\x86"
+    "\xC4\xC1\xC0\x10\x86\xC4\x01\xF0\x89\x03\xEB\xE2\x24\x0F\xC1\xE0"
+    "\x10\x66\x8B\x07\x83\xC7\x02\x09\xC0\x75\x0C\x8B\x07\x83\xC7\x04"
+    "\xEB\x0C\x87\xF7\x8D\x8F\x00\x00\x00\x00\xA9\x66\x01\x0C\x07\xAD"
+    "\x09\xC0\x75\xF7\xC1\xE9\x10\xA9\x66\x01\x0C\x07\xAD\x09\xC0\x75"
+    "\xF7\x8B\xAE\x00\x00\x00\x00\x8D\xBE\x00\x00\x00\x00\xBB\x00\x00"
+    "\x00\x00\x50\x54\x6A\x04\x53\x57\xFF\xD5\x8D\x87\x00\x00\x00\x00"
+    "\x80\x20\x7F\x80\x60\x28\x7F\x58\x50\x54\x50\x53\x57\xFF\xD5\x58"
+    "\x8D\x9E\x00\x00\x00\x00\x8D\xBB\x01\x00\x00\x00\x57\x31\xC0\xAA"
+    "\x59\x49\x50\x6A\x01\x53\xFF\xD1\x61\x8D\x44\x24\x80\x6A\x00\x39"
+    "\xC4\x75\xFA\x83\xEC\x80\x31\xC0\x40\xC2\x0C\x00\xE9\xFC\xFF\xFF"
+    "\xFF\xEB\x1A\x56\xBE\x00\x00\x00\x00\xFC\xAD\x85\xC0\x74\x0D\x6A"
+    "\x03\x59\xFF\x74\x24\x10\xE2\xFA\xFF\xD0\xEB\xEE\x5E\xC2\x0C\x00"
+    "\x55\x50\x58\x21\xA1\xD8\xD0\xD5\x00\x00\x00\x00\x00\x00\x00\x00"
+    "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x2D"
+
+#if defined(MOD)
+    // MYPEMAIN01
+    "\x53\x55\x56\x57\xBE\x00\x00\x00\x00\x8D\xBE\x00\x00\x00\x00"
+
+    // MYPEMAIN20
+    "\x5F\x5E\x5D\x5B"
+
+    // MYPEIEREXE
+    "\xE8\x0C\x00\x00\x00\x45\x78\x69\x74\x50\x72\x6F\x63\x65\x73\x73"
+    "\x00\xFF\x74\x24\x08\xFF\x96\x00\x00\x00\x00\x6A\x00\xFF\xD0"
+
+    // MYPEDEPHAK
+    "\x8D\xBE\x00\x00\x00\x00\xE8\x0F\x00\x00\x00\x56\x69\x72\x74\x75"
+    "\x61\x6C\x50\x72\x6F\x74\x65\x63\x74\x00\xFF\x74\x24\x08\xFF\x96"
+    "\x00\x00\x00\x00\x95\xBB\x00\x00\x00\x00\x33\xC0\x50\x54\x6A\x04"
+    "\x53\x57\xFF\xD5\x8D\x87\x00\x00\x00\x00\x80\x20\x7F\x80\x60\x28"
+    "\x7F\x58\x50\x54\x50\x53\x57\xFF\xD5\x83\xC4\x0C"
+
+    // MYPEIMPORT
+
+    "\x8D\xBE\x00\x00\x00\x00\x8D\x46\x34\x8D\x80\x00\x00\x00\x00\x50"
+    "\x54\x50\x6A\x00\xFF\x96\x00\x00\x00\x00\x58\x50\xE8\x0D\x00\x00"
+    "\x00\x4C\x6F\x61\x64\x4C\x69\x62\x72\x61\x72\x79\x41\x00\x50\xFF"
+    "\x96\x00\x00\x00\x00\x50\x8B\x07\x09\xC0\x0F\x84\xFC\xFF\xFF\xFF"
+    "\x8B\x5F\x04\x03\xDE\x83\xC7\x08\x57\xFF\x54\x24\x04\x50\x54\x57"
+    "\x6A\x01\xFF\x96\x00\x00\x00\x00\x5D\x33\xC0\x8B\xCF\xF2\xAE"
+
+    // MYPEIMPORT_2
+    "\x8A\x07\x47\x08\xC0\x74\xD0\x8B\xCF"
+
+    // MYPEIMPOR2
+    "\x57\x48\xF2\xAE\x55\xFF\x96\x00\x00\x00\x00\x09\xC0\x74\x07\x89"
+    "\x03\x83\xC3\x04\xEB\xFF"
+
+    // MYCLEARSTACK
+    "\x6A\x20\x59\x33\xC0\x50\xE2\xFD\x83\xEC\x80"
+
+#endif
+
+    "file format elf32-i386\n"
+    "\n"
+    "Sections:\n"
+    "Idx Name          Size      VMA       LMA       File off  Algn  Flags\n"
+    "  0 PEISDLL1      0000000b  00000000  00000000  00000034  2**0  CONTENTS, RELOC, READONLY\n"
+    "  1 PEMAIN01      0000000c  00000000  00000000  0000003f  2**0  CONTENTS, RELOC, READONLY\n"
+    "  2 PEICONS1      00000007  00000000  00000000  0000004b  2**0  CONTENTS, RELOC, READONLY\n"
+    "  3 PEICONS2      00000009  00000000  00000000  00000052  2**0  CONTENTS, RELOC, READONLY\n"
+    "  4 PETLSHAK      0000000a  00000000  00000000  0000005b  2**0  CONTENTS, RELOC, READONLY\n"
+    "  5 PEMAIN02      00000001  00000000  00000000  00000065  2**0  CONTENTS, READONLY\n"
+    "  6 PEMAIN03      00000003  00000000  00000000  00000066  2**0  CONTENTS, READONLY\n"
+    "  7 N2BSMA10      00000003  00000000  00000000  00000069  2**0  CONTENTS, RELOC, READONLY\n"
+    "  8 N2BFAS10      00000002  00000000  00000000  0000006c  2**0  CONTENTS, RELOC, READONLY\n"
+    "  9 N2BFAS11      00000006  00000000  00000000  0000006e  2**0  CONTENTS, READONLY\n"
+    " 10 N2BDEC10      0000000b  00000000  00000000  00000074  2**0  CONTENTS, READONLY\n"
+    " 11 N2BSMA20      00000005  00000000  00000000  0000007f  2**0  CONTENTS, RELOC, READONLY\n"
+    " 12 N2BFAS20      00000007  00000000  00000000  00000084  2**0  CONTENTS, RELOC, READONLY\n"
+    " 13 N2BDEC20      0000000d  00000000  00000000  0000008b  2**0  CONTENTS, READONLY\n"
+    " 14 N2BSMA30      0000000d  00000000  00000000  00000098  2**0  CONTENTS, RELOC, READONLY\n"
+    " 15 N2BFAS30      0000000f  00000000  00000000  000000a5  2**0  CONTENTS, RELOC, READONLY\n"
+    " 16 N2BDEC30      0000003e  00000000  00000000  000000b4  2**0  CONTENTS, RELOC, READONLY\n"
+    " 17 N2BSMA40      0000000d  00000000  00000000  000000f2  2**0  CONTENTS, RELOC, READONLY\n"
+    " 18 N2BFAS40      0000000f  00000000  00000000  000000ff  2**0  CONTENTS, RELOC, READONLY\n"
+    " 19 N2BSMA50      00000002  00000000  00000000  0000010e  2**0  CONTENTS, READONLY\n"
+    " 20 N2BFAS50      00000003  00000000  00000000  00000110  2**0  CONTENTS, READONLY\n"
+    " 21 N2BDEC50      00000009  00000000  00000000  00000113  2**0  CONTENTS, READONLY\n"
+    " 22 N2BSMA60      0000000e  00000000  00000000  0000011c  2**0  CONTENTS, RELOC, READONLY\n"
+    " 23 N2BFAS60      00000016  00000000  00000000  0000012a  2**0  CONTENTS, RELOC, READONLY\n"
+    " 24 N2BFAS61      00000016  00000000  00000000  00000140  2**0  CONTENTS, RELOC, READONLY\n"
+    " 25 N2BDEC60      00000000  00000000  00000000  00000156  2**0  CONTENTS, READONLY\n"
+    " 26 N2DSMA10      00000003  00000000  00000000  00000156  2**0  CONTENTS, RELOC, READONLY\n"
+    " 27 N2DFAS10      00000002  00000000  00000000  00000159  2**0  CONTENTS, RELOC, READONLY\n"
+    " 28 N2DFAS11      00000006  00000000  00000000  0000015b  2**0  CONTENTS, READONLY\n"
+    " 29 N2DDEC10      0000000b  00000000  00000000  00000161  2**0  CONTENTS, READONLY\n"
+    " 30 N2DSMA20      00000005  00000000  00000000  0000016c  2**0  CONTENTS, RELOC, READONLY\n"
+    " 31 N2DFAS20      00000007  00000000  00000000  00000171  2**0  CONTENTS, RELOC, READONLY\n"
+    " 32 N2DDEC20      0000000d  00000000  00000000  00000178  2**0  CONTENTS, READONLY\n"
+    " 33 N2DSMA30      0000000d  00000000  00000000  00000185  2**0  CONTENTS, RELOC, READONLY\n"
+    " 34 N2DFAS30      0000000f  00000000  00000000  00000192  2**0  CONTENTS, RELOC, READONLY\n"
+    " 35 N2DDEC30      00000052  00000000  00000000  000001a1  2**0  CONTENTS, RELOC, READONLY\n"
+    " 36 N2DSMA40      0000000d  00000000  00000000  000001f3  2**0  CONTENTS, RELOC, READONLY\n"
+    " 37 N2DFAS40      0000000f  00000000  00000000  00000200  2**0  CONTENTS, RELOC, READONLY\n"
+    " 38 N2DSMA50      00000002  00000000  00000000  0000020f  2**0  CONTENTS, READONLY\n"
+    " 39 N2DFAS50      00000003  00000000  00000000  00000211  2**0  CONTENTS, READONLY\n"
+    " 40 N2DDEC50      00000009  00000000  00000000  00000214  2**0  CONTENTS, READONLY\n"
+    " 41 N2DSMA60      0000000e  00000000  00000000  0000021d  2**0  CONTENTS, RELOC, READONLY\n"
+    " 42 N2DFAS60      00000016  00000000  00000000  0000022b  2**0  CONTENTS, RELOC, READONLY\n"
+    " 43 N2DFAS61      00000016  00000000  00000000  00000241  2**0  CONTENTS, RELOC, READONLY\n"
+    " 44 N2DDEC60      00000000  00000000  00000000  00000257  2**0  CONTENTS, READONLY\n"
+    " 45 N2ESMA10      00000003  00000000  00000000  00000257  2**0  CONTENTS, RELOC, READONLY\n"
+    " 46 N2EFAS10      00000002  00000000  00000000  0000025a  2**0  CONTENTS, RELOC, READONLY\n"
+    " 47 N2EFAS11      00000006  00000000  00000000  0000025c  2**0  CONTENTS, READONLY\n"
+    " 48 N2EDEC10      0000000b  00000000  00000000  00000262  2**0  CONTENTS, READONLY\n"
+    " 49 N2ESMA20      00000005  00000000  00000000  0000026d  2**0  CONTENTS, RELOC, READONLY\n"
+    " 50 N2EFAS20      00000007  00000000  00000000  00000272  2**0  CONTENTS, RELOC, READONLY\n"
+    " 51 N2EDEC20      0000000d  00000000  00000000  00000279  2**0  CONTENTS, READONLY\n"
+    " 52 N2ESMA30      0000000d  00000000  00000000  00000286  2**0  CONTENTS, RELOC, READONLY\n"
+    " 53 N2EFAS30      0000000f  00000000  00000000  00000293  2**0  CONTENTS, RELOC, READONLY\n"
+    " 54 N2EDEC30      0000005f  00000000  00000000  000002a2  2**0  CONTENTS, RELOC, READONLY\n"
+    " 55 N2ESMA40      0000000d  00000000  00000000  00000301  2**0  CONTENTS, RELOC, READONLY\n"
+    " 56 N2EFAS40      0000000f  00000000  00000000  0000030e  2**0  CONTENTS, RELOC, READONLY\n"
+    " 57 N2ESMA50      00000002  00000000  00000000  0000031d  2**0  CONTENTS, READONLY\n"
+    " 58 N2EFAS50      00000003  00000000  00000000  0000031f  2**0  CONTENTS, READONLY\n"
+    " 59 N2EDEC50      00000009  00000000  00000000  00000322  2**0  CONTENTS, READONLY\n"
+    " 60 N2ESMA60      0000000e  00000000  00000000  0000032b  2**0  CONTENTS, RELOC, READONLY\n"
+    " 61 N2EFAS60      00000016  00000000  00000000  00000339  2**0  CONTENTS, RELOC, READONLY\n"
+    " 62 N2EFAS61      00000016  00000000  00000000  0000034f  2**0  CONTENTS, RELOC, READONLY\n"
+    " 63 N2EDEC60      00000000  00000000  00000000  00000365  2**0  CONTENTS, READONLY\n"
+    " 64 LZMA_DEC00    0000002e  00000000  00000000  00000365  2**0  CONTENTS, RELOC, READONLY\n"
+    " 65 LZMA_ELF00    00000048  00000000  00000000  00000393  2**0  CONTENTS, READONLY\n"
+    " 66 LZMA_DEC10    00000a86  00000000  00000000  000003db  2**0  CONTENTS, READONLY\n"
+    " 67 LZMA_DEC20    00000a86  00000000  00000000  00000e61  2**0  CONTENTS, READONLY\n"
+    " 68 LZMA_DEC30    0000001a  00000000  00000000  000018e7  2**0  CONTENTS, READONLY\n"
+    " 69 PEMAIN10      00000001  00000000  00000000  00001901  2**0  CONTENTS, READONLY\n"
+    " 70 PECTTPOS      00000006  00000000  00000000  00001902  2**0  CONTENTS, RELOC, READONLY\n"
+    " 71 PECTTNUL      00000002  00000000  00000000  00001908  2**0  CONTENTS, READONLY\n"
+    " 72 CALLTR00      0000000e  00000000  00000000  0000190a  2**0  CONTENTS, RELOC, READONLY\n"
+    " 73 CTCLEVE1      00000005  00000000  00000000  00001918  2**0  CONTENTS, RELOC, READONLY\n"
+    " 74 CALLTR01      00000005  00000000  00000000  0000191d  2**0  CONTENTS, READONLY\n"
+    " 75 CTBSHR01      00000004  00000000  00000000  00001922  2**0  CONTENTS, READONLY\n"
+    " 76 CTBROR01      00000002  00000000  00000000  00001926  2**0  CONTENTS, READONLY\n"
+    " 77 CTBSWA01      00000005  00000000  00000000  00001928  2**0  CONTENTS, READONLY\n"
+    " 78 CALLTR02      00000010  00000000  00000000  0000192d  2**0  CONTENTS, RELOC, READONLY\n"
+    " 79 CALLTR10      00000005  00000000  00000000  0000193d  2**0  CONTENTS, RELOC, READONLY\n"
+    " 80 CALLTRE8      00000002  00000000  00000000  00001942  2**0  CONTENTS, READONLY\n"
+    " 81 CALLTRE9      00000002  00000000  00000000  00001944  2**0  CONTENTS, READONLY\n"
+    " 82 CALLTR11      00000004  00000000  00000000  00001946  2**0  CONTENTS, RELOC, READONLY\n"
+    " 83 CTCLEVE2      00000005  00000000  00000000  0000194a  2**0  CONTENTS, RELOC, READONLY\n"
+    " 84 CALLTR12      00000002  00000000  00000000  0000194f  2**0  CONTENTS, READONLY\n"
+    " 85 CTBSHR11      00000004  00000000  00000000  00001951  2**0  CONTENTS, READONLY\n"
+    " 86 CTBROR11      00000002  00000000  00000000  00001955  2**0  CONTENTS, READONLY\n"
+    " 87 CTBSWA11      00000005  00000000  00000000  00001957  2**0  CONTENTS, READONLY\n"
+    " 88 CALLTR13      00000007  00000000  00000000  0000195c  2**0  CONTENTS, RELOC, READONLY\n"
+    " 89 ctok32.00     0000000c  00000000  00000000  00001963  2**0  CONTENTS, RELOC, READONLY\n"
+    " 90 ctok32.10     0000000e  00000000  00000000  0000196f  2**0  CONTENTS, RELOC, READONLY\n"
+    " 91 ctok32.20     00000022  00000000  00000000  0000197d  2**0  CONTENTS, RELOC, READONLY\n"
+    " 92 ctok32.30     00000007  00000000  00000000  0000199f  2**0  CONTENTS, RELOC, READONLY\n"
+    " 93 ctok32.40     00000005  00000000  00000000  000019a6  2**0  CONTENTS, RELOC, READONLY\n"
+    " 94 PEIMPORT      0000002c  00000000  00000000  000019ab  2**0  CONTENTS, RELOC, READONLY\n"
+    " 95 PEIBYORD      00000002  00000000  00000000  000019d7  2**0  CONTENTS, RELOC, READONLY\n"
+    " 96 PEK32ORD      00000010  00000000  00000000  000019d9  2**0  CONTENTS, RELOC, READONLY\n"
+    " 97 PEIMORD1      00000007  00000000  00000000  000019e9  2**0  CONTENTS, READONLY\n"
+    " 98 PEIMPOR2      00000016  00000000  00000000  000019f0  2**0  CONTENTS, RELOC, READONLY\n"
+    " 99 PEIERDLL      00000006  00000000  00000000  00001a06  2**0  CONTENTS, READONLY\n"
+    "100 PEIEREXE      00000006  00000000  00000000  00001a0c  2**0  CONTENTS, RELOC, READONLY\n"
+    "101 PEIMDONE      00000000  00000000  00000000  00001a12  2**0  CONTENTS, READONLY\n"
+    "102 PERELOC1      00000006  00000000  00000000  00001a12  2**0  CONTENTS, RELOC, READONLY\n"
+    "103 PERELOC2      00000003  00000000  00000000  00001a18  2**0  CONTENTS, READONLY\n"
+    "104 PERELOC3      00000003  00000000  00000000  00001a1b  2**0  CONTENTS, READONLY\n"
+    "105 RELOC320      00000029  00000000  00000000  00001a1e  2**0  CONTENTS, RELOC, READONLY\n"
+    "106 REL32BIG      00000009  00000000  00000000  00001a47  2**0  CONTENTS, RELOC, READONLY\n"
+    "107 RELOC32J      00000002  00000000  00000000  00001a50  2**0  CONTENTS, RELOC, READONLY\n"
+    "108 REL32END      00000000  00000000  00000000  00001a52  2**0  CONTENTS, READONLY\n"
+    "109 PERLOHI0      00000008  00000000  00000000  00001a52  2**0  CONTENTS, RELOC, READONLY\n"
+    "110 PERELLO0      0000000a  00000000  00000000  00001a5a  2**0  CONTENTS, READONLY\n"
+    "111 PERELHI0      0000000d  00000000  00000000  00001a64  2**0  CONTENTS, READONLY\n"
+    "112 PEDEPHAK      0000002f  00000000  00000000  00001a71  2**0  CONTENTS, RELOC, READONLY\n"
+    "113 PETLSC        00000018  00000000  00000000  00001aa0  2**0  CONTENTS, RELOC, READONLY\n"
+    "114 PEMAIN20      00000001  00000000  00000000  00001ab8  2**0  CONTENTS, READONLY\n"
+    "115 CLEARSTACK    0000000d  00000000  00000000  00001ab9  2**0  CONTENTS, READONLY\n"
+    "116 PEMAIN21      00000000  00000000  00000000  00001ac6  2**0  CONTENTS, READONLY\n"
+    "117 PERETURN      00000006  00000000  00000000  00001ac6  2**0  CONTENTS, READONLY\n"
+    "118 PEDOJUMP      00000005  00000000  00000000  00001acc  2**0  CONTENTS, RELOC, READONLY\n"
+    "119 PETLSC2       0000001f  00000000  00000000  00001ad1  2**0  CONTENTS, RELOC, READONLY\n"
+    "120 UPX1HEAD      00000020  00000000  00000000  00001af0  2**0  CONTENTS, READONLY\n"
+#if defined(MOD)
+    "129 MYPEK32ORD    00000010  00000000  00000000  000019d9  2**0  CONTENTS, RELOC, READONLY\n"
+
+    "200 MYPEMAIN01    0000000f  00000000  00000000  00001b10  2**0  CONTENTS, RELOC, READONLY\n"
+    "201 MYPEMAIN20    00000004  00000000  00000000  00001b1f  2**0  CONTENTS, READONLY\n"
+    "202 MYPEIEREXE    0000001f  00000000  00000000  00001b23  2**0  CONTENTS, RELOC, READONLY\n"
+    "203 MYPEDEPHAK    0000004c  00000000  00000000  00001b42  2**0  CONTENTS, RELOC, READONLY\n"
+    "204 MYPEIMPORT    0000005f  00000000  00000000  00001b8e  2**0  CONTENTS, RELOC, READONLY\n"
+    "205 MYPEIMPORT_2  00000009  00000000  00000000  00001bed  2**0  CONTENTS, RELOC, READONLY\n"
+    "206 MYPEIMPOR2    00000016  00000000  00000000  00001bf6  2**0  CONTENTS, RELOC, READONLY\n"
+    "207 MYCLEARSTACK  0000000b  00000000  00000000  00001c0c  2**0  CONTENTS, READONLY\n"
+#endif
+    "SYMBOL TABLE:\n"
+    "00000000 l    d  N2BSMA10	00000000 N2BSMA10\n"
+    "00000000 l    d  N2BFAS11	00000000 N2BFAS11\n"
+    "00000000 l    d  N2BDEC10	00000000 N2BDEC10\n"
+    "00000000 l    d  N2BDEC20	00000000 N2BDEC20\n"
+    "00000000 l    d  N2BDEC30	00000000 N2BDEC30\n"
+    "00000000 l    d  N2BDEC50	00000000 N2BDEC50\n"
+    "00000000 l    d  N2BFAS61	00000000 N2BFAS61\n"
+    "00000000 l    d  N2BDEC60	00000000 N2BDEC60\n"
+    "00000000 l    d  N2DSMA10	00000000 N2DSMA10\n"
+    "00000000 l    d  N2DFAS11	00000000 N2DFAS11\n"
+    "00000000 l    d  N2DDEC10	00000000 N2DDEC10\n"
+    "00000000 l    d  N2DDEC20	00000000 N2DDEC20\n"
+    "00000000 l    d  N2DDEC30	00000000 N2DDEC30\n"
+    "00000000 l    d  N2DDEC50	00000000 N2DDEC50\n"
+    "00000000 l    d  N2DFAS61	00000000 N2DFAS61\n"
+    "00000000 l    d  N2DDEC60	00000000 N2DDEC60\n"
+    "00000000 l    d  N2ESMA10	00000000 N2ESMA10\n"
+    "00000000 l    d  N2EFAS11	00000000 N2EFAS11\n"
+    "00000000 l    d  N2EDEC10	00000000 N2EDEC10\n"
+    "00000000 l    d  N2EDEC20	00000000 N2EDEC20\n"
+    "00000000 l    d  N2EDEC30	00000000 N2EDEC30\n"
+    "00000000 l    d  N2EDEC50	00000000 N2EDEC50\n"
+    "00000000 l    d  N2EFAS61	00000000 N2EFAS61\n"
+    "00000000 l    d  N2EDEC60	00000000 N2EDEC60\n"
+    "00000000 l    d  CALLTR00	00000000 CALLTR00\n"
+    "00000000 l    d  CALLTR10	00000000 CALLTR10\n"
+    "00000000 l    d  CALLTR11	00000000 CALLTR11\n"
+    "00000000 l    d  CALLTR13	00000000 CALLTR13\n"
+    "00000000 l    d  ctok32.00	00000000 ctok32.00\n"
+    "00000000 l    d  ctok32.10	00000000 ctok32.10\n"
+    "00000000 l    d  ctok32.20	00000000 ctok32.20\n"
+    "00000000 l    d  ctok32.40	00000000 ctok32.40\n"
+    "00000000 l    d  PEIMPORT	00000000 PEIMPORT\n"
+    "00000000 l    d  PEIMORD1	00000000 PEIMORD1\n"
+    "00000000 l    d  PEIMPOR2	00000000 PEIMPOR2\n"
+    "00000000 l    d  PEIMDONE	00000000 PEIMDONE\n"
+    "00000000 l    d  RELOC320	00000000 RELOC320\n"
+    "00000000 l    d  RELOC32J	00000000 RELOC32J\n"
+    "00000000 l    d  PEMAIN21	00000000 PEMAIN21\n"
+    "00000000 l    d  PETLSC2	00000000 PETLSC2\n"
+    "00000000 l    d  PEISDLL1	00000000 PEISDLL1\n"
+    "00000000 l    d  PEMAIN01	00000000 PEMAIN01\n"
+    "00000000 l    d  PEICONS1	00000000 PEICONS1\n"
+    "00000000 l    d  PEICONS2	00000000 PEICONS2\n"
+    "00000000 l    d  PETLSHAK	00000000 PETLSHAK\n"
+    "00000000 l    d  PEMAIN02	00000000 PEMAIN02\n"
+    "00000000 l    d  PEMAIN03	00000000 PEMAIN03\n"
+    "00000000 l    d  N2BFAS10	00000000 N2BFAS10\n"
+    "00000000 l    d  N2BSMA20	00000000 N2BSMA20\n"
+    "00000000 l    d  N2BFAS20	00000000 N2BFAS20\n"
+    "00000000 l    d  N2BSMA30	00000000 N2BSMA30\n"
+    "00000000 l    d  N2BFAS30	00000000 N2BFAS30\n"
+    "00000000 l    d  N2BSMA40	00000000 N2BSMA40\n"
+    "00000000 l    d  N2BFAS40	00000000 N2BFAS40\n"
+    "00000000 l    d  N2BSMA50	00000000 N2BSMA50\n"
+    "00000000 l    d  N2BFAS50	00000000 N2BFAS50\n"
+    "00000000 l    d  N2BSMA60	00000000 N2BSMA60\n"
+    "00000000 l    d  N2BFAS60	00000000 N2BFAS60\n"
+    "00000000 l    d  N2DFAS10	00000000 N2DFAS10\n"
+    "00000000 l    d  N2DSMA20	00000000 N2DSMA20\n"
+    "00000000 l    d  N2DFAS20	00000000 N2DFAS20\n"
+    "00000000 l    d  N2DSMA30	00000000 N2DSMA30\n"
+    "00000000 l    d  N2DFAS30	00000000 N2DFAS30\n"
+    "00000000 l    d  N2DSMA40	00000000 N2DSMA40\n"
+    "00000000 l    d  N2DFAS40	00000000 N2DFAS40\n"
+    "00000000 l    d  N2DSMA50	00000000 N2DSMA50\n"
+    "00000000 l    d  N2DFAS50	00000000 N2DFAS50\n"
+    "00000000 l    d  N2DSMA60	00000000 N2DSMA60\n"
+    "00000000 l    d  N2DFAS60	00000000 N2DFAS60\n"
+    "00000000 l    d  N2EFAS10	00000000 N2EFAS10\n"
+    "00000000 l    d  N2ESMA20	00000000 N2ESMA20\n"
+    "00000000 l    d  N2EFAS20	00000000 N2EFAS20\n"
+    "00000000 l    d  N2ESMA30	00000000 N2ESMA30\n"
+    "00000000 l    d  N2EFAS30	00000000 N2EFAS30\n"
+    "00000000 l    d  N2ESMA40	00000000 N2ESMA40\n"
+    "00000000 l    d  N2EFAS40	00000000 N2EFAS40\n"
+    "00000000 l    d  N2ESMA50	00000000 N2ESMA50\n"
+    "00000000 l    d  N2EFAS50	00000000 N2EFAS50\n"
+    "00000000 l    d  N2ESMA60	00000000 N2ESMA60\n"
+    "00000000 l    d  N2EFAS60	00000000 N2EFAS60\n"
+    "00000000 l    d  LZMA_DEC00	00000000 LZMA_DEC00\n"
+    "00000000 l    d  LZMA_ELF00	00000000 LZMA_ELF00\n"
+    "00000000 l    d  LZMA_DEC10	00000000 LZMA_DEC10\n"
+    "00000000 l    d  LZMA_DEC20	00000000 LZMA_DEC20\n"
+    "00000000 l    d  LZMA_DEC30	00000000 LZMA_DEC30\n"
+    "00000000 l    d  PEMAIN10	00000000 PEMAIN10\n"
+    "00000000 l    d  PECTTPOS	00000000 PECTTPOS\n"
+    "00000000 l    d  PECTTNUL	00000000 PECTTNUL\n"
+    "00000000 l    d  CTCLEVE1	00000000 CTCLEVE1\n"
+    "00000000 l    d  CALLTR01	00000000 CALLTR01\n"
+    "00000000 l    d  CTBSHR01	00000000 CTBSHR01\n"
+    "00000000 l    d  CTBROR01	00000000 CTBROR01\n"
+    "00000000 l    d  CTBSWA01	00000000 CTBSWA01\n"
+    "00000000 l    d  CALLTR02	00000000 CALLTR02\n"
+    "00000000 l    d  CALLTRE8	00000000 CALLTRE8\n"
+    "00000000 l    d  CALLTRE9	00000000 CALLTRE9\n"
+    "00000000 l    d  CTCLEVE2	00000000 CTCLEVE2\n"
+    "00000000 l    d  CALLTR12	00000000 CALLTR12\n"
+    "00000000 l    d  CTBSHR11	00000000 CTBSHR11\n"
+    "00000000 l    d  CTBROR11	00000000 CTBROR11\n"
+    "00000000 l    d  CTBSWA11	00000000 CTBSWA11\n"
+    "00000000 l    d  ctok32.30	00000000 ctok32.30\n"
+    "00000000 l    d  PEIBYORD	00000000 PEIBYORD\n"
+    "00000000 l    d  PEK32ORD	00000000 PEK32ORD\n"
+    "00000000 l    d  PEIERDLL	00000000 PEIERDLL\n"
+    "00000000 l    d  PEIEREXE	00000000 PEIEREXE\n"
+    "00000000 l    d  PERELOC1	00000000 PERELOC1\n"
+    "00000000 l    d  PERELOC2	00000000 PERELOC2\n"
+    "00000000 l    d  PERELOC3	00000000 PERELOC3\n"
+    "00000000 l    d  REL32BIG	00000000 REL32BIG\n"
+    "00000000 l    d  REL32END	00000000 REL32END\n"
+    "00000000 l    d  PERLOHI0	00000000 PERLOHI0\n"
+    "00000000 l    d  PERELLO0	00000000 PERELLO0\n"
+    "00000000 l    d  PERELHI0	00000000 PERELHI0\n"
+    "00000000 l    d  PEDEPHAK	00000000 PEDEPHAK\n"
+    "00000000 l    d  PETLSC	00000000 PETLSC\n"
+    "00000000 l    d  PEMAIN20	00000000 PEMAIN20\n"
+    "00000000 l    d  CLEARSTACK	00000000 CLEARSTACK\n"
+    "00000000 l    d  PERETURN	00000000 PERETURN\n"
+    "00000000 l    d  PEDOJUMP	00000000 PEDOJUMP\n"
+    "00000000 l    d  UPX1HEAD	00000000 UPX1HEAD\n"
+#if defined(MOD)
+    "00000000 l    d  MYPEMAIN01	00000000 MYPEMAIN01\n"
+    "00000000 l    d  MYPEMAIN20	00000000 MYPEMAIN20\n"
+    "00000000 l    d  MYPEIMPORT	00000000 MYPEIMPORT\n"
+    "00000000 l    d  MYPEIMPORT_2	00000000 MYPEIMPORT_2\n"
+    "00000000 l    d  MYPEIMPOR2	00000000 MYPEIMPOR2\n"
+    "00000000 l    d  MYPEDEPHAK	00000000 MYPEDEPHAK\n"
+    "00000000 l    d  MYPEIEREXE	00000000 MYPEIEREXE\n"
+    "00000000 l    d  MYPEK32ORD	00000000 MYPEK32ORD\n"
+    "00000000 l    d  MYCLEARSTACK	00000000 MYCLEARSTACK\n"
+#endif
+    "00000000         *UND*	00000000 start_of_compressed\n"
+    "00000000         *UND*	00000000 start_of_uncompressed\n"
+    "00000000         *UND*	00000000 icon_offset\n"
+    "00000000         *UND*	00000000 icon_delta\n"
+    "00000000         *UND*	00000000 tls_address\n"
+    "00000000         *UND*	00000000 tls_value\n"
+    "00000000         *UND*	00000000 lzma_stack_adjust\n"
+    "00000000         *UND*	00000000 lzma_u_len\n"
+    "00000000         *UND*	00000000 lzma_c_len\n"
+    "00000000         *UND*	00000000 lzma_properties\n"
+    "00000000         *UND*	00000000 filter_buffer_start\n"
+    "00000000         *UND*	00000000 filter_length\n"
+    "00000000         *UND*	00000000 filter_cto\n"
+    "00000000         *UND*	00000000 compressed_imports\n"
+    "00000000         *UND*	00000000 start_of_imports\n"
+    "00000000         *UND*	00000000 GetModuleHandleExA\n"
+    "00000000         *UND*	00000000 kernel32_ordinals\n"
+    "00000000         *UND*	00000000 GetProcAddress\n"
+    "00000000         *UND*	00000000 ExitProcess\n"
+    "00000000         *UND*	00000000 start_of_relocs\n"
+    "00000000         *UND*	00000000 reloc_delt\n"
+    "00000000         *UND*	00000000 VirtualProtect\n"
+    "00000000         *UND*	00000000 vp_base\n"
+    "00000000         *UND*	00000000 vp_size\n"
+    "00000000         *UND*	00000000 swri\n"
+    "00000000         *UND*	00000000 tls_module_base\n"
+    "00000000         *UND*	00000000 original_entry\n"
+    "00000000         *UND*	00000000 tls_callbacks_ptr\n"
+    "\n"
+    "RELOCATION RECORDS FOR [PEISDLL1]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000007 R_386_PC32        PEMAIN21\n"
+    "\n"
+    "RELOCATION RECORDS FOR [PEMAIN01]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000002 R_386_32          start_of_compressed\n"
+    "00000008 R_386_32          start_of_uncompressed\n"
+    "\n"
+    "RELOCATION RECORDS FOR [PEICONS1]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000003 R_386_32          icon_offset\n"
+    "\n"
+    "RELOCATION RECORDS FOR [PEICONS2]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000003 R_386_32          icon_offset\n"
+    "00000007 R_386_16          icon_delta\n"
+    "\n"
+    "RELOCATION RECORDS FOR [PETLSHAK]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000002 R_386_32          tls_address\n"
+    "00000006 R_386_32          tls_value\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2BSMA10]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_PC8         N2BDEC10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2BFAS10]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_PC8         N2BDEC10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2BSMA20]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_PC8         N2BSMA10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2BFAS20]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_PC8         N2BFAS11\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2BSMA30]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "0000000c R_386_PC8         N2BDEC20\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2BFAS30]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000003 R_386_PC8         N2BDEC20\n"
+    "0000000e R_386_PC8         N2BDEC20\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2BDEC30]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000011 R_386_PC8         N2BDEC60\n"
+    "0000002f R_386_PC8         N2BDEC50\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2BSMA40]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "0000000c R_386_PC8         N2BDEC30\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2BFAS40]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000003 R_386_PC8         N2BDEC30\n"
+    "0000000e R_386_PC8         N2BDEC30\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2BSMA60]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "0000000a R_386_PC32        N2BDEC10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2BFAS60]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000007 R_386_PC8         N2BFAS61\n"
+    "00000012 R_386_PC32        N2BDEC10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2BFAS61]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000012 R_386_PC32        N2BDEC10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2DSMA10]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_PC8         N2DDEC10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2DFAS10]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_PC8         N2DDEC10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2DSMA20]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_PC8         N2DSMA10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2DFAS20]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_PC8         N2DFAS11\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2DSMA30]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "0000000c R_386_PC8         N2DDEC30\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2DFAS30]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000005 R_386_PC8         N2DDEC30\n"
+    "0000000e R_386_PC8         N2DDEC30\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2DDEC30]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "0000000f R_386_PC8         N2DDEC20\n"
+    "00000021 R_386_PC8         N2DDEC60\n"
+    "00000043 R_386_PC8         N2DDEC50\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2DSMA40]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "0000000c R_386_PC8         N2DDEC30\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2DFAS40]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000003 R_386_PC8         N2DDEC30\n"
+    "0000000e R_386_PC8         N2DDEC30\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2DSMA60]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "0000000a R_386_PC32        N2DDEC10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2DFAS60]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000007 R_386_PC8         N2DFAS61\n"
+    "00000012 R_386_PC32        N2DDEC10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2DFAS61]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000012 R_386_PC32        N2DDEC10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2ESMA10]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_PC8         N2EDEC10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2EFAS10]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_PC8         N2EDEC10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2ESMA20]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_PC8         N2ESMA10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2EFAS20]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_PC8         N2EFAS11\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2ESMA30]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "0000000c R_386_PC8         N2EDEC30\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2EFAS30]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000005 R_386_PC8         N2EDEC30\n"
+    "0000000e R_386_PC8         N2EDEC30\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2EDEC30]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "0000000f R_386_PC8         N2EDEC20\n"
+    "0000001e R_386_PC8         N2EDEC50\n"
+    "00000030 R_386_PC8         N2EDEC60\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2ESMA40]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "0000000c R_386_PC8         N2EDEC30\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2EFAS40]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000003 R_386_PC8         N2EDEC30\n"
+    "0000000e R_386_PC8         N2EDEC30\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2ESMA60]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "0000000a R_386_PC32        N2EDEC10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2EFAS60]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000007 R_386_PC8         N2EFAS61\n"
+    "00000012 R_386_PC32        N2EDEC10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [N2EFAS61]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000012 R_386_PC32        N2EDEC10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [LZMA_DEC00]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000005 R_386_32          lzma_stack_adjust\n"
+    "00000014 R_386_32          lzma_u_len\n"
+    "0000001e R_386_32          lzma_c_len\n"
+    "0000002a R_386_32          lzma_properties\n"
+    "\n"
+    "RELOCATION RECORDS FOR [PECTTPOS]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000002 R_386_32          filter_buffer_start\n"
+    "\n"
+    "RELOCATION RECORDS FOR [CALLTR00]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_32          filter_length\n"
+    "\n"
+    "RELOCATION RECORDS FOR [CTCLEVE1]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000002 R_386_8           filter_cto\n"
+    "00000004 R_386_PC8         CALLTR00\n"
+    "\n"
+    "RELOCATION RECORDS FOR [CALLTR02]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "0000000f R_386_PC8         CALLTR00\n"
+    "\n"
+    "RELOCATION RECORDS FOR [CALLTR10]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_32          filter_length\n"
+    "\n"
+    "RELOCATION RECORDS FOR [CALLTR11]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000003 R_386_PC8         CALLTR13\n"
+    "\n"
+    "RELOCATION RECORDS FOR [CTCLEVE2]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000002 R_386_8           filter_cto\n"
+    "00000004 R_386_PC8         CALLTR11\n"
+    "\n"
+    "RELOCATION RECORDS FOR [CALLTR13]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000006 R_386_PC8         CALLTR10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [ctok32.00]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_32          filter_length\n"
+    "00000006 R_386_PC8         ctok32.20\n"
+    "\n"
+    "RELOCATION RECORDS FOR [ctok32.10]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "0000000d R_386_PC8         ctok32.20\n"
+    "\n"
+    "RELOCATION RECORDS FOR [ctok32.20]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000005 R_386_PC8         ctok32.40\n"
+    "00000008 R_386_8           filter_cto\n"
+    "0000000a R_386_PC8         ctok32.40\n"
+    "\n"
+    "RELOCATION RECORDS FOR [ctok32.30]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000006 R_386_PC8         ctok32.10\n"
+    "\n"
+    "RELOCATION RECORDS FOR [ctok32.40]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000004 R_386_PC8         ctok32.00\n"
+    "\n"
+    "RELOCATION RECORDS FOR [PEIMPORT]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000002 R_386_32          compressed_imports\n"
+    "0000000b R_386_PC8         PEIMDONE\n"
+    "00000012 R_386_32          start_of_imports\n"
+    "0000001e R_386_32          GetModuleHandleExA\n"
+    "\n"
+    "RELOCATION RECORDS FOR [PEIBYORD]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_PC8         PEIMORD1\n"
+    "\n"
+    "RELOCATION RECORDS FOR [PEK32ORD]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "0000000a R_386_32          kernel32_ordinals\n"
+    "0000000f R_386_PC8         PEIMPOR2\n"
+    "\n"
+    "RELOCATION RECORDS FOR [PEIMPOR2]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000007 R_386_32          GetProcAddress\n"
+    "00000015 R_386_PC8         PEIMPORT\n"
+    "\n"
+    "RELOCATION RECORDS FOR [PEIEREXE]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000002 R_386_32          ExitProcess\n"
+    "\n"
+    "RELOCATION RECORDS FOR [PERELOC1]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000002 R_386_32          start_of_relocs\n"
+    "\n"
+    "RELOCATION RECORDS FOR [RELOC320]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000008 R_386_PC8         RELOC32J\n"
+    "\n"
+    "RELOCATION RECORDS FOR [REL32BIG]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000003 R_386_PC8         RELOC320\n"
+    "\n"
+    "RELOCATION RECORDS FOR [RELOC32J]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_PC8         RELOC320\n"
+    "\n"
+    "RELOCATION RECORDS FOR [PERLOHI0]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000004 R_386_32          reloc_delt\n"
+    "\n"
+    "RELOCATION RECORDS FOR [PEDEPHAK]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000002 R_386_32          VirtualProtect\n"
+    "00000008 R_386_32          vp_base\n"
+    "0000000d R_386_32          vp_size\n"
+    "0000001b R_386_32          swri\n"
+    "\n"
+    "RELOCATION RECORDS FOR [PETLSC]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000002 R_386_32          tls_module_base\n"
+    "00000008 R_386_32          PETLSC2\n"
+    "\n"
+    "RELOCATION RECORDS FOR [PEDOJUMP]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000001 R_386_PC32        original_entry\n"
+    "\n"
+    "RELOCATION RECORDS FOR [PETLSC2]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000004 R_386_32          tls_callbacks_ptr\n"
+#if defined(MOD)
+    "\n"
+    "RELOCATION RECORDS FOR [MYPEMAIN01]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000005 R_386_32          start_of_compressed\n"
+    "0000000b R_386_32          start_of_uncompressed\n"
+    "\n"
+    "RELOCATION RECORDS FOR [MYPEIMPORT]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000002 R_386_32          compressed_imports\n"
+    "0000000b R_386_32          start_of_imports\n"
+    "00000016 R_386_32          GetModuleHandleExA\n"
+    "00000031 R_386_32          GetProcAddress\n"
+    "0000003c R_386_PC32        PEIMDONE\n"
+    "00000054 R_386_32          GetModuleHandleExA\n"
+    "\n"
+    "RELOCATION RECORDS FOR [MYPEK32ORD]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "0000000a R_386_32          kernel32_ordinals\n"
+    "0000000f R_386_PC8         MYPEIMPOR2\n"
+    "\n"
+    "RELOCATION RECORDS FOR [MYPEIMPOR2]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000007 R_386_32          GetProcAddress\n"
+    "00000015 R_386_PC8         MYPEIMPORT_2\n"
+    "\n"
+    "RELOCATION RECORDS FOR [MYPEDEPHAK]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000002 R_386_32          vp_base\n"
+    "00000020 R_386_32          GetProcAddress\n"
+    "00000026 R_386_32          vp_size\n"
+    "00000036 R_386_32          swri\n"
+    "\n"
+    "RELOCATION RECORDS FOR [MYPEIEREXE]:\n"
+    "OFFSET   TYPE              VALUE\n"
+    "00000017 R_386_32          GetProcAddress\n"
+#endif
+    "\n"
+};
+
 unsigned char stub_i386_win32_pe[32851] = {
 /* 0x0000 */ 127, 69, 76, 70,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,
 /* 0x0010 */   1,  0,  3,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
diff --git a/src_orig/util.cpp b/src/util.cpp
index 90f7b2e..155ebc5 100644
--- a/src_orig/util.cpp
+++ b/src/util.cpp
@@ -463,7 +463,7 @@ bool file_exists(const char *name)
 
     /* return true if we can stat it */
     //memset(&st, 0, sizeof(st));
-    r = stat(name, &st);
+    r = _stat(name, (struct _stat *)&st);
     if (r != -1)
         return true;
 
diff --git a/src_orig/version.h b/src/version.h
index e9a3d71..a7e56d7 100644
--- a/src_orig/version.h
+++ b/src/version.h
@@ -4,3 +4,5 @@
 #define UPX_VERSION_DATE        "Sep 08th 2010"
 #define UPX_VERSION_DATE_ISO    "2010-09-08"
 #define UPX_VERSION_YEAR        "2010"
+#define DEFAULT_SECTION_NAME    ".Amano"
+#define MOD
\ No newline at end of file
diff --git a/src_orig/work.cpp b/src/work.cpp
index a273777..cb86a83 100644
--- a/src_orig/work.cpp
+++ b/src/work.cpp
@@ -67,7 +67,7 @@ void do_one_file(const char *iname, char *oname)
 #if (HAVE_LSTAT)
     r = lstat(iname,&st);
 #else
-    r = stat(iname,&st);
+    r = _stat(iname,(struct _stat *)&st);
 #endif
 
     if (r != 0)
