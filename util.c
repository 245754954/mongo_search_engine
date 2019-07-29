#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/time.h>

#include "util.h"

#define BUFFER_INIT_MIN 32 /* 分配缓冲区时的初始字节数 */

/**
 * 将错误信息输出到标准错误输出
 * @param[in] format 可以传递给函数printf的格式字符串
 * @param[in] ... 要传递给格式说明符号（format specifications）的参数
 * @return 已输出的字节数
 */
int
print_error(const char *format, ...)
{
  int r;
  va_list l;

  va_start(l, format);
  vfprintf(stderr, format, l);
  r = fprintf(stderr, "\n");
  fflush(stderr);
  va_end(l);

  return r;
}

/**
 * 分配一个缓冲区
 * @return 指向分配好的缓冲区的指针
 */
buffer *
alloc_buffer(void)
{
  buffer *buf;
  if ((buf = malloc(sizeof(buffer)))) {
    if ((buf->head = malloc(BUFFER_INIT_MIN))) {
      buf->curr = buf->head;
      buf->tail = buf->head + BUFFER_INIT_MIN;
      buf->bit = 0;
    } else {
      free(buf);
      buf = NULL;
    }
  }
  return buf;
}

/**
 * 扩大缓冲区的容量
 * @param[in,out] buf 指向待扩容的缓冲区的指针
 * @retval 0 成功
 * @retval 1 失败
 */
static int
enlarge_buffer(buffer *buf)
{
  int new_size;
  char *new_head;
  new_size = (buf->tail - buf->head) * 2;
  if ((new_head = realloc(buf->head, new_size))) {
    buf->curr = new_head + (buf->curr - buf->head);
    buf->tail = new_head + new_size;
    buf->head = new_head;
    return 0;
  } else {
    return 1;
  }
}

/**
 * 将指定了字节数的数据添加到缓冲区中
 * @param[in] buf 指向要向里面添加数据的缓冲区的指针
 * @param[in] data 指向待添加的数据的指针
 * @param[in] data_size 待添加数据的字节数
 * @return 已添加至缓冲区中的数据的字节数
 */
int
append_buffer(buffer *buf, const void *data, unsigned int data_size)
{
  if (buf->bit) { buf->curr++; buf->bit = 0; }
  if (buf->curr + data_size > buf->tail) {
    if (enlarge_buffer(buf)) { return 0; }
  }
  if (data && data_size) {
    memcpy(buf->curr, data, data_size);
    buf->curr += data_size;
  }
  return data_size;
}

/**
 * 将1个比特的数据添加到缓冲区中
 * @param[in] buf 指向要向里面添加数据的缓冲区的指针
 * @param[in] bit 待添加的比特值。0或1
 */
void
append_buffer_bit(buffer *buf, int bit)
{
  if (buf->curr >= buf->tail) {
    if (enlarge_buffer(buf)) { return; }
  }
  if (!buf->bit) { *buf->curr = 0; }
  if (bit) { *buf->curr |= 1 << (7 - buf->bit); }
  if (++(buf->bit) == 8) { buf->curr++; buf->bit = 0; }
}

/**
 * 释放缓冲区
 * @param[in] buf 指向要释放的缓冲区的指针
 */
void
free_buffer(buffer *buf)
{
  free(buf->head);
  free(buf);
}

/**
 * 计算将字符串的编码由UTF-32转换为UTF-8时所需的字节数
 * @param[in] ustr 输入的字符串（UTF-32）
 * @param[in] ustr_len 输入的字符串的长度
 * @return 用UTF-8表示该字符串时所需的字节数
 **/
int
uchar2utf8_size(const UTF32Char *ustr, int ustr_len)
{
  int size = 0;
  const UTF32Char *ustr_end;
  for (ustr_end = ustr + ustr_len; ustr < ustr_end; ustr++) {
    if (*ustr < 0x800) {
      if (*ustr < 0x80) {
        size += 1;
      } else {
        size += 2;
      }
    } else {
      if (*ustr < 0x10000) {
        size += 3;
      } else if (*ustr < 0x200000) {
        size += 4;
      } else {
        abort();
      }
    }
  }
  return size;
}

/**
 * 将指定了长度的UTF-32的字符串转换为以NULL结尾的UTF-8的字符串
 * 需要在调用该函数的地方准备缓冲区，以存放作为转换结果的UTF-8的字符串
 * @param[in] ustr 输入的字符串（UTF-32）
 * @param[in] ustr_len 输入的字符串的长度。-1表示输入的是以NULL结尾的字符串
 * @param[in,out] str 存储转换后的字符串（UTF-8）的缓冲区
 *                    该缓冲区要足够大，不得小于ustr_len * MAX_UTF8_SIZE
 * @param[out] str_size 转换后的字符串的字节数。调用时可将该参数设为NULL
 * @return 转换后的UTF-8字符串
 */
char *
utf32toutf8(const UTF32Char *ustr, int ustr_len, char *str,
            int *str_size)
{
  int sbuf_size;
  sbuf_size = uchar2utf8_size(ustr, ustr_len);
  if (str_size) {
    *str_size = sbuf_size;
  }
  if (!str) {
    return NULL;
  } else {
    char *sbuf;
    const UTF32Char *ustr_end;
    for (sbuf = str, ustr_end = ustr + ustr_len; ustr < ustr_end;
         ustr++) {
      if (*ustr < 0x800) {
        if (*ustr < 0x80) {
          *sbuf++ = *ustr;
        } else {
          *sbuf++ = ((*ustr & 0x7c0) >> 6) | 0xc0;
          *sbuf++ = (*ustr & 0x3f) | 0x80;
        }
      } else {
        if (*ustr < 0x10000) {
          *sbuf++ = ((*ustr & 0xf000) >> 12) | 0xe0;
          *sbuf++ = ((*ustr & 0xfc0) >> 6) | 0x80;
          *sbuf++ = (*ustr & 0x3f) | 0x80;
        } else if (*ustr < 0x200000) {
          *sbuf++ = ((*ustr & 0x1c0000) >> 18) | 0xf0;
          *sbuf++ = ((*ustr & 0x3f000) >> 12) | 0x80;
          *sbuf++ = ((*ustr & 0xfc0) >> 6) | 0x80;
          *sbuf++ = (*ustr & 0x3f) | 0x80;
        } else {
          abort();
        }
      }
    }
    *sbuf = '\0';
  }
  return str;
}

/**
 * 首字节在0x80～0xFF中的UTF-8字符所需的字节数。0表示错误
 **/
const static unsigned char utf8_skip_table[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 80-8F */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 90-9F */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* A0-AF */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* B0-BF */
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /* C0-CF */
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /* D0-DF */
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, /* E0-EF */
  4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 0, 0, /* F0-FF */
};

/**
 * 计算UTF-8字符串的长度
 * @param[in] str 输入的字符串（UTF-8）
 * @param[in] str_size 输入的字符串的字节数
 * @return UTF-8字符串的长度
 **/
static int
utf8_len(const char *str, int str_size)
{
  int len = 0;
  const char *str_end;
  for (str_end = str + str_size; str < str_end;) {
    if (*str >= 0) {
      str += 1;
      len++;
    } else {
      unsigned char s = utf8_skip_table[*str + 0x80];
      if (!s) { abort(); }
      str += s;
      len++;
    }
  }
  return len;
}

/**
 * 将UTF-8的字符串转换为UTF-32的字符串
 * UTF-32的字符串存储在新分配的缓冲区中
 * @param[in] str 输入的字符串（UTF-8）
 * @param[in] str_size 输入的字符串的字节数。-1表示输入的是以NULL结尾的字符串
 * @param[out] ustr 转换后的字符串（UTF-32）。由调用方释放
 * @param[out] ustr_len 转换后的字符串的长度。调用时可将该参数设为NULL
 * @retval 0 成功
 */
int
utf8toutf32(const char *str, int str_size, UTF32Char **ustr,
            int *ustr_len)
{
  int ulen;
  ulen = utf8_len(str, str_size);
  if (ustr_len) { *ustr_len = ulen; }
  if (!ustr) { return 0; }
  if ((*ustr = malloc(sizeof(UTF32Char) * ulen))) {
    UTF32Char *u;
    const char *str_end;
    for (u = *ustr, str_end = str + str_size; str < str_end;) {
      if (*str >= 0) {
        *u++ = *str;
        str += 1;
      } else {
        unsigned char s = utf8_skip_table[*str + 0x80];
        if (!s) { abort(); }
        /* 从n字节的UTF-8字符的首字节取出后(7 - n)个比特 */
        *u = *str & ((1 << (7 - s)) - 1);
        /* 从n字节的UTF-8字符的剩余字节序列中每次取出6个比特 */
        for (str++, s--; s--; str++) {
          *u = *u << 6;
          *u |= *str & 0x3f;
        }
        u++;
      }
    }
  } else {
    print_error("cannot allocate memory on utf8toutf32.");
  }
  return 0;
}

/**
 * 将struct timeval转换成表示时刻的字符串
 * 缓冲区buffer的长度应为37个字节
 */
void
timeval_to_str(struct timeval *clock, char *const buffer)
{
  struct tm result;
  localtime_r(&clock->tv_sec, &result);
  sprintf(buffer, "%04d/%02d/%02d %02d:%02d:%02d.%06d",
          result.tm_year + 1900,
          result.tm_mon + 1,
          result.tm_mday,
          result.tm_hour,
          result.tm_min,
          result.tm_sec,
          (int)(clock->tv_usec / 100000)
         );
}
#define TIMEVAL_TO_STR_BUFFER_SIZE 37

/**
 * 用浮点数表示struct timeval
 * @return 用浮点数表示的struct timeval
 */
double
timeval_to_double(struct timeval *tv)
{
  return ((double)(tv->tv_sec) + (double)(tv->tv_usec) * 0.000001);
}

/**
 * 获取当前时间，计算其与上一次获取的当前时间的差值，并输出这两个数据
 */
void
print_time_diff(void)
{
  char datetime_buf[TIMEVAL_TO_STR_BUFFER_SIZE];
  static double pre_time = 0.0;

  struct timeval tv;
  gettimeofday(&tv, NULL);
  timeval_to_str(&tv, datetime_buf);
  double current_time = timeval_to_double(&tv);

  if (pre_time) {
    double time_diff = current_time - pre_time;
    print_error("[time] %s (diff %10.6lf)", datetime_buf, time_diff);
  } else {
    print_error("[time] %s", datetime_buf);
  }
  pre_time = current_time;
}



// base64 转换表, 共64个
static const char base64_alphabet[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '+', '/'};

// 解码时使用
static const unsigned char base64_suffix_map[256] = {
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 253, 255,
    255, 253, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 253, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255,  62, 255, 255, 255,  63,
    52,  53,  54,  55,  56,  57,  58,  59,  60,  61, 255, 255,
    255, 254, 255, 255, 255,   0,   1,   2,   3,   4,   5,   6,
    7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,
    19,  20,  21,  22,  23,  24,  25, 255, 255, 255, 255, 255,
    255,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,
    37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,
    49,  50,  51, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255 };

static char cmove_bits(unsigned char src, unsigned lnum, unsigned rnum) {
    src <<= lnum; // src = src << lnum;
    src >>= rnum; // src = src >> rnum;
    return src;
}

int base64_encode(const char *indata, int inlen, char *outdata, int *outlen) {
    
    int ret = 0; // return value
    if (indata == NULL || inlen == 0) {
        return ret = -1;
    }
    
    int in_len = 0; // 源字符串长度, 如果in_len不是3的倍数, 那么需要补成3的倍数
    int pad_num = 0; // 需要补齐的字符个数, 这样只有2, 1, 0(0的话不需要拼接, )
    if (inlen % 3 != 0) {
        pad_num = 3 - inlen % 3;
    }
    in_len = inlen + pad_num; // 拼接后的长度, 实际编码需要的长度(3的倍数)
    
    int out_len = in_len * 8 / 6; // 编码后的长度
    
    char *p = outdata; // 定义指针指向传出data的首地址
    
    //编码, 长度为调整后的长度, 3字节一组
    for (int i = 0; i < in_len; i+=3) {
        int value = *indata >> 2; // 将indata第一个字符向右移动2bit(丢弃2bit)
        char c = base64_alphabet[value]; // 对应base64转换表的字符
        *p = c; // 将对应字符(编码后字符)赋值给outdata第一字节
        
        //处理最后一组(最后3字节)的数据
        if (i == inlen + pad_num - 3 && pad_num != 0) {
            if(pad_num == 1) {
                *(p + 1) = base64_alphabet[(int)(cmove_bits(*indata, 6, 2) + cmove_bits(*(indata + 1), 0, 4))];
                *(p + 2) = base64_alphabet[(int)cmove_bits(*(indata + 1), 4, 2)];
                *(p + 3) = '=';
            } else if (pad_num == 2) { // 编码后的数据要补两个 '='
                *(p + 1) = base64_alphabet[(int)cmove_bits(*indata, 6, 2)];
                *(p + 2) = '=';
                *(p + 3) = '=';
            }
        } else { // 处理正常的3字节的数据
            *(p + 1) = base64_alphabet[cmove_bits(*indata, 6, 2) + cmove_bits(*(indata + 1), 0, 4)];
            *(p + 2) = base64_alphabet[cmove_bits(*(indata + 1), 4, 2) + cmove_bits(*(indata + 2), 0, 6)];
            *(p + 3) = base64_alphabet[*(indata + 2) & 0x3f];
        }
        
        p += 4;
        indata += 3;
    }
    
    if(outlen != NULL) {
        *outlen = out_len;
    }
    
    return ret;
}


int base64_decode(const char *indata, int inlen, char *outdata, int *outlen) {
    
    int ret = 0;
    if (indata == NULL || inlen <= 0 || outdata == NULL || outlen == NULL) {
        return ret = -1;
    }
    if (inlen % 4 != 0) { // 需要解码的数据不是4字节倍数
        return ret = -2;
    }
    
    int t = 0, x = 0, y = 0, i = 0;
    unsigned char c = 0;
    int g = 3;
    
    while (indata[x] != 0) {
        // 需要解码的数据对应的ASCII值对应base64_suffix_map的值
        c = base64_suffix_map[indata[x++]];
        if (c == 255) return -1;// 对应的值不在转码表中
        if (c == 253) continue;// 对应的值是换行或者回车
        if (c == 254) { c = 0; g--; }// 对应的值是'='
        t = (t<<6) | c; // 将其依次放入一个int型中占3字节
        if (++y == 4) {
            outdata[i++] = (unsigned char)((t>>16)&0xff);
            if (g > 1) outdata[i++] = (unsigned char)((t>>8)&0xff);
            if (g > 2) outdata[i++] = (unsigned char)(t&0xff);
            y = t = 0;
        }
    }
    if (outlen != NULL) {
        *outlen = i;
    }
    return ret;
}