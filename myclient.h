#ifndef __MYCLIENT_H__
#define __MYCLIENT_H__

#include "include/utlist.h"
#include "include/uthash.h"
#include "include/utarray.h"
#include <mongoc/mongoc.h>
#include <openssl/md5.h>



/* bi-gram */
#define N_GRAM 2

/* 倒排列表（以文档编号和位置信息为元素的链表结构）*/
typedef struct _postings_list {
  int document_id;             /* 文档编号 */
  UT_array *positions;         /* 位置信息的数组 */
  int positions_count;         /* 位置信息的条数 */
  struct _postings_list *next; /* 指向下一个倒排列表的指针 */
} postings_list1;

/* 倒排索引（以词元编号为键，以倒排列表为值的关联数组） */
typedef struct {
  int token_id;                 /* 词元编号（Token ID）*/
  postings_list1 *postings_list; /* 指向包含该词元的倒排列表的指针 */
  int docs_count;               /* 出现过该词元的文档数 */
  int positions_count;          /* 该词元在所有文档中的出现次数之和 */
  UT_hash_handle hh;            /* 用于将该结构体转化为哈希表 */
} inverted_index_hash1, inverted_index_value1;

/* 压缩倒排列表等数据的方法 */
typedef enum {
  compress_none,  /* 不压缩 */
  compress_golomb /* 使用Golomb编码压缩 */
} compress_method1;

/* 应用程序的全局配置 */
typedef struct _wiser_env {

    mongoc_collection_t *documentcountcollections;
    mongoc_collection_t *tokencountcollections;
    mongoc_collection_t *settings;
    mongoc_collection_t *documents;
    mongoc_collection_t *tokens;

    mongoc_client_t *client;
    mongoc_database_t *database;
    
            /* 数据库的路径*/
  
  int token_len;                  /* 词元的长度。N-gram中N的取值 */
  compress_method1 compress;       /* 压缩倒排列表等数据的方法 */
  int enable_phrase_search;       /* 是否进行短语检索 */

  inverted_index_hash1 *ii_buffer; /* 用于更新倒排索引的缓冲区（Buffer） */
  int ii_buffer_count;            /* 用于更新倒排索引的缓冲区中的文档数 */
  int ii_buffer_update_threshold; /* 缓冲区中文档数的阈值 */
  int indexed_count;  
  
   MD5_CTX ctx;            /* 建立了索引的文档数 */

} wiser_env1;


typedef struct
{
  int document_id;   /* 检索出的文档编号 */
  double score;      /* 检索得分 */
  UT_hash_handle hh; /* 用于将该结构体转化为哈希表 */
} search_results1;

/* TRUE/FALSE */
#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

#define DEFAULT_II_BUFFER_UPDATE_THRESHOLD 2048

void query_reply(char *term,search_results1 *result);

#endif