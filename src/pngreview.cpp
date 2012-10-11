/*
  pngreview.cpp

  > cl pngreview.cpp zlib.lib -EHsc -I. -link -LIBPATH:.
*/

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdarg>
#include <cstdlib>
#include <cstdio>

// #include <stdint.h> // *** for int32_t but is not supported before C99 ***

#include <GL/zlib.h> // for crc32

using namespace std;

typedef unsigned int uint32_t; // *** assume int to be int32_t ***
typedef unsigned short uint16_t; // *** assume short to be int16_t ***
typedef unsigned char uchar;

// *** assume that this machine is little endian processor ***
// may be get the same effect to use U4 in crc32()
#define l2b32(d) (((d) & 0x0ff) << 24 | ((d) & 0x0ff00) << 8 \
                   | ((d) >> 8) & 0x0ff00 | ((d) >> 24) & 0x0ff)
#define l2b32v(b, o) (l2b32(*(uint32_t *)&(b)[(o)]))
#define l2b16(d) (((d) & 0x0ff) << 8 | ((d) >> 8) & 0x0ff)
#define l2b16v(b, o) (l2b16(*(uint16_t *)&(b)[(o)]))

#define __ERROR_ALLOC "cannot allocate buffer"
#define __PNG_SIG "\x89PNG\x0d\x0a\x1a\x0a"
#define __PNG_LEN_LEN 4
#define __PNG_TYPE_LEN 4
#define __PNG_CRC_LEN 4
#define __PNG_ENV_LEN (__PNG_TYPE_LEN + __PNG_CRC_LEN)
#define __PNG_IHDR_LEN 13
#define __PNG_IHDR_SIZE (__PNG_LEN_LEN + __PNG_ENV_LEN + __PNG_IHDR_LEN)

uchar *usage(int r, char **av, char *fmt=0, ...)
{
  va_list ap;
  va_start(ap, fmt);
  if(fmt){
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, ap); // va_arg(ap, ...);
  }
  if(r) fprintf(stderr, "Usage: %s file.png\n", av[0]);
  va_end(ap);
  return (uchar *)r;
}

uchar *read_chunk(char **av, FILE *fp, uchar *chunkname, size_t *buflen)
{
  *buflen = 0;
  uint32_t len, crc;
  size_t rlen = fread(&len, __PNG_LEN_LEN, 1, fp);
  if(rlen < 1) return usage(0, av, "%s cannot read length\n", chunkname);
  uchar chunktype[__PNG_TYPE_LEN + 1] = {0};
  rlen = fread(chunktype, __PNG_TYPE_LEN, 1, fp);
  if(rlen < 1) return usage(0, av, "%s cannot read chunktype\n", chunkname);
  fprintf(stdout, "%s: %08x bytes ", chunktype, len=l2b32(len));
  strncpy((char *)chunkname, (char *)chunktype, __PNG_TYPE_LEN);
  uchar *buf = new uchar[len];
  if(!buf) return usage(0, av, __ERROR_ALLOC);
  if(len){
    rlen = fread(buf, len, 1, fp);
    if(rlen < 1) return usage(0, av, "%s cannot read data\n", chunktype);
  }
  rlen = fread(&crc, __PNG_CRC_LEN, 1, fp);
  if(rlen < 1) return usage(0, av, "%s cannot read crc\n", chunktype);
  fprintf(stdout, "(crc32: %08x) ... ", crc=l2b32(crc));
  if(crc32(crc32(0, chunktype, __PNG_TYPE_LEN), buf, len) == crc){
    fprintf(stdout, "ok\n");
  }else{
    delete[] buf; buf = 0;
    return usage(0, av, "%s crc of data is not match\n", chunktype);
  }
  *buflen = len;
  return buf;
}

void display_data(uchar *buf, size_t len, size_t expect, size_t cols)
{
  for(int remain = len; len - remain < expect && remain > 0; remain -= cols){
    int cut = remain < cols ? remain : cols;
    for(int i = 0; i < cut; i++)
      fprintf(stdout, " %02x", buf[(len - remain) + i]);
    fprintf(stdout, "\n");
  }
  if(len > expect) fprintf(stdout, " ...\n");
}

bool chunk_IHDR(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  bool result = true;
  fprintf(stdout, " size: (%d, %d), bit depth: %d, color type: %d\n",
    l2b32v(buf, 0), l2b32v(buf, 4), buf[8], buf[9]);
  fprintf(stdout, " compress: %d, filter: %d, interlace: %d\n",
    buf[10], buf[11], buf[12]);
  if(*state){
    fprintf(stderr, "--- %s is found after ---\n", chunkname);
    result = false;
  }
  *state = 1;
  return result;
}

bool chunk_PLTE(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  bool result = true;
  display_data(buf, len, 384, 24); // (1 + (125 * 3) / 24) * 24
  if(*state >= 2){
    fprintf(stderr, "--- %s is found after ---\n", chunkname);
    result = false;
  }
  *state = 2;
  return result;
}

bool chunk_IDAT(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  display_data(buf, len, 96, 24);
  *state = 3;
  return true;
}

bool chunk_IEND(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  fprintf(stdout, "end\n");
  *state = -1;
  return true;
}

bool chunk_tRNS(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  display_data(buf, len, 24, 24);
  return true;
}

bool chunk_gAMA(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  display_data(buf, len, 4, 4);
  return true;
}

bool chunk_cHRM(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  fprintf(stdout, " white(%d, %d), red(%d, %d), green(%d, %d), blue(%d, %d)\n",
    l2b32v(buf, 0), l2b32v(buf, 4), l2b32v(buf, 8), l2b32v(buf, 12),
    l2b32v(buf, 16), l2b32v(buf, 20), l2b32v(buf, 24), l2b32v(buf, 28));
  return true;
}

bool chunk_sRGB(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  display_data(buf, len, 1, 1);
  return true;
}

bool chunk_iCCP(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  int slen = strlen((char *)buf);
  fprintf(stdout, " %s: ", buf);
  uLongf ebuf_size = len * 100;
  uchar *ebuf = new uchar[ebuf_size];
  if(!ebuf){
    fprintf(stderr, "(cannot extract text)\n");
    return false;
  }
  uncompress(ebuf, &ebuf_size, &buf[slen + 2], len - (slen + 2));
  fprintf(stdout, "%.*s\n", ebuf_size, ebuf);
  delete[] ebuf;
  return true;
}

bool chunk_tEXt(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  int slen = strlen((char *)buf);
  fprintf(stdout, " %s: %.*s\n", buf,
    slen + 1 == len ? 6 : len - (slen + 1),
    slen + 1 == len ? "(none)" : (char *)&buf[slen + 1]);
  return true;
}

bool chunk_zTXt(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  int slen = strlen((char *)buf);
  fprintf(stdout, " %s: ", buf);
  uLongf ebuf_size = len * 100;
  uchar *ebuf = new uchar[ebuf_size];
  if(!ebuf){
    fprintf(stderr, "(cannot extract text)\n");
    return false;
  }
  uncompress(ebuf, &ebuf_size, &buf[slen + 2], len - (slen + 2));
  fprintf(stdout, "%.*s\n", ebuf_size, ebuf);
  delete[] ebuf;
  return true;
}

bool chunk_iTXt(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  fprintf(stdout, " %s: (...)", buf);
  display_data(buf, len, 96, 24);
  return true;
}

bool chunk_bKGD(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  display_data(buf, len, 6, 6);
  return true;
}

bool chunk_pHYs(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  fprintf(stdout, " pixels per unit(%d, %d), unit(%d)\n",
    l2b32v(buf, 0), l2b32v(buf, 4), buf[8]);
  return true;
}

bool chunk_sBIT(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  display_data(buf, len, 4, 4);
  return true;
}

bool chunk_sPLT(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  fprintf(stdout, " %s: (...)", buf);
  display_data(buf, len, 96, 24);
  return true;
}

bool chunk_hIST(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  display_data(buf, len, 96, 24);
  return true;
}

bool chunk_tIME(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  fprintf(stdout, " %04d-%02d-%02d %02d:%02d:%02d\n",
    l2b16v(buf, 0), buf[2], buf[3], buf[4], buf[5], buf[6]);
  return true;
}

bool chunk_fRAc(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  display_data(buf, len, 96, 24);
  return true;
}

bool chunk_gIFg(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  display_data(buf, len, 96, 24);
  return true;
}

bool chunk_gIFt(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  display_data(buf, len, 96, 24);
  return true;
}

bool chunk_gIFx(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  display_data(buf, len, 96, 24);
  return true;
}

bool chunk_oFFs(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  bool result = true;
  display_data(buf, len, 96, 24);
  if(*state >= 3){
    fprintf(stderr, "--- %s is found after ---\n", chunkname);
    result = false;
  }
  return result;
}

bool chunk_pCAL(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  bool result = true;
  display_data(buf, len, 96, 24);
  if(*state >= 3){
    fprintf(stderr, "--- %s is found after ---\n", chunkname);
    result = false;
  }
  return result;
}

bool chunk_sCAL(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  bool result = true;
  display_data(buf, len, 96, 24);
  if(*state >= 3){
    fprintf(stderr, "--- %s is found after ---\n", chunkname);
    result = false;
  }
  return result;
}

bool chunk_sTER(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  display_data(buf, len, 96, 24);
  return true;
}

bool chunk_vpAg(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  display_data(buf, len, 96, 24);
  return true;
}

typedef struct _chunkfunc {
  uchar chunktype[__PNG_TYPE_LEN + 1];
  bool (*func)(int *state, uchar *chunkname, uchar *buf, size_t len);
} chunkfunc;
chunkfunc arraychunkfunc[] = {
  {"IHDR", chunk_IHDR}, // IHDR index must be 0
  {"PLTE", chunk_PLTE}, {"IDAT", chunk_IDAT}, {"IEND", chunk_IEND},
  {"tRNS", chunk_tRNS}, {"gAMA", chunk_gAMA},
  {"cHRM", chunk_cHRM}, {"sRGB", chunk_sRGB},
  {"iCCP", chunk_iCCP}, {"tEXt", chunk_tEXt},
  {"zTXt", chunk_zTXt}, {"iTXt", chunk_iTXt},
  {"bKGD", chunk_bKGD}, {"pHYs", chunk_pHYs},
  {"sBIT", chunk_sBIT}, {"sPLT", chunk_sPLT},
  {"hIST", chunk_hIST}, {"tIME", chunk_tIME}, {"fRAc", chunk_fRAc},
  {"gIFg", chunk_gIFg}, {"gIFt", chunk_gIFt}, {"gIFx", chunk_gIFx},
  {"oFFs", chunk_oFFs}, {"pCAL", chunk_pCAL}, {"sCAL", chunk_sCAL},
  {"sTER", chunk_sTER}, {"vpAg", chunk_vpAg}
};

bool check_head(int state, uchar *chunkname)
{
  if(!state){
    fprintf(stderr, "--- %s is found before IHDR ---\n", chunkname);
    return false;
  }
  return true;
}

bool chunk_process(int *state, uchar *chunkname, uchar *buf, size_t len)
{
  for(int i = 0; i < sizeof(arraychunkfunc) / sizeof(arraychunkfunc[0]); i++)
    if(!strncmp((char *)chunkname, (char *)arraychunkfunc[i].chunktype,
      __PNG_TYPE_LEN)){
      bool result = true;
      if(i) result = check_head(*state, chunkname);
      return result && arraychunkfunc[i].func(state, chunkname, buf, len);
    }
  fprintf(stderr, "--- unknown chunktype [%s] ---\n", chunkname);
  return false;
}

int main(int ac, char **av)
{
  if(ac < 2) return (int)usage(1, av);
  FILE *fp = fopen(av[1], "rb");
  if(!fp) return (int)usage(1, av, "cannot read file: %s\n", av[1]);
  size_t size = sizeof(__PNG_SIG) - 1;
  uchar *buf = new uchar[size];
  if(!buf) return (int)usage(1, av, __ERROR_ALLOC);
  size_t rlen = fread(buf, size, 1, fp);
  if(rlen < 1) return (int)usage(1, av, "not PNG file?\n");
  if(memcmp(buf, __PNG_SIG, size)) return (int)usage(1, av, "PNG sig.\n");
  delete[] buf;
  int state = 0; // 0: IHDR, 1: PLTE, 2: IDAT, 3: IEND, -1: break
  while(state >= 0){ // state should be changed in chunk_process
    uchar chunkname[__PNG_TYPE_LEN + 1] = {0};
    size_t len = 0;
    uchar *buf = read_chunk(av, fp, chunkname, &len);
    if(!buf) return 1;
    bool result = chunk_process(&state, chunkname, buf, len);
    delete[] buf;
  }
  fclose(fp);
  return 0;
}
