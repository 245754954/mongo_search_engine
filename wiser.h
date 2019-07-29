#ifndef __WISER_H__
#define __WISER_H__

#include "include/utlist.h"
#include "include/uthash.h"
#include "include/utarray.h"
<<<<<<< HEAD
#include <openssl/md5.h>
#include <mysql/mysql.h>
=======
#include <sqlite3.h>
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f

/* bi-gram */
#define N_GRAM 2

/* 倒排列表（以文档编号和位置信息为元素的链表结构）*/
<<<<<<< HEAD
typedef struct _postings_list
{
=======
typedef struct _postings_list {
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
  int document_id;             /* 文档编号 */
  UT_array *positions;         /* 位置信息的数组 */
  int positions_count;         /* 位置信息的条数 */
  struct _postings_list *next; /* 指向下一个倒排列表的指针 */
} postings_list;

/* 倒排索引（以词元编号为键，以倒排列表为值的关联数组） */
<<<<<<< HEAD
typedef struct
{
=======
typedef struct {
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
  int token_id;                 /* 词元编号（Token ID）*/
  postings_list *postings_list; /* 指向包含该词元的倒排列表的指针 */
  int docs_count;               /* 出现过该词元的文档数 */
  int positions_count;          /* 该词元在所有文档中的出现次数之和 */
  UT_hash_handle hh;            /* 用于将该结构体转化为哈希表 */
} inverted_index_hash, inverted_index_value;

/* 压缩倒排列表等数据的方法 */
<<<<<<< HEAD
typedef enum
{
=======
typedef enum {
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
  compress_none,  /* 不压缩 */
  compress_golomb /* 使用Golomb编码压缩 */
} compress_method;

/* 应用程序的全局配置 */
<<<<<<< HEAD
typedef struct _wiser_env
{

  // mongoc_collection_t *documentcountcollections;
  // mongoc_collection_t *tokencountcollections;
  // mongoc_collection_t *settings;
  // mongoc_collection_t *documents;
  // mongoc_collection_t *tokens;

  // mongoc_client_t *client;
  // mongoc_database_t *database;

  /* 数据库的路径*/

  int token_len;            /* 词元的长度。N-gram中N的取值 */
  compress_method compress; /* 压缩倒排列表等数据的方法 */
  int enable_phrase_search; /* 是否进行短语检索 */
=======
typedef struct _wiser_env {
  const char *db_path;            /* 数据库的路径*/

  int token_len;                  /* 词元的长度。N-gram中N的取值 */
  compress_method compress;       /* 压缩倒排列表等数据的方法 */
  int enable_phrase_search;       /* 是否进行短语检索 */
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f

  inverted_index_hash *ii_buffer; /* 用于更新倒排索引的缓冲区（Buffer） */
  int ii_buffer_count;            /* 用于更新倒排索引的缓冲区中的文档数 */
  int ii_buffer_update_threshold; /* 缓冲区中文档数的阈值 */
<<<<<<< HEAD
  int indexed_count;

  MD5_CTX ctx; /* 建立了索引的文档数 */

  MYSQL *conn = NULL;
  char *server = "localhost";
  char *user = "root";
  char *password = "123456"; /* 此处改成你的密码 */
  char *database = "invertindex";



    /* sqlite3的准备语句 */
  MYSQL_STMT *get_document_id_st;
  MYSQL_STMT *get_document_title_st;
  MYSQL_STMT *insert_document_st;
  MYSQL_STMT *update_document_st;
  MYSQL_STMT *get_token_id_st;
  MYSQL_STMT *get_token_st;
  MYSQL_STMT *store_token_st;
  MYSQL_STMT *get_postings_st;
  MYSQL_STMT *update_postings_st;
  MYSQL_STMT *get_settings_st;
  MYSQL_STMT *replace_settings_st;
  MYSQL_STMT *get_document_count_st;
  MYSQL_STMT *begin_st;
  MYSQL_STMT *commit_st;
  MYSQL_STMT *rollback_st;

=======
  int indexed_count;              /* 建立了索引的文档数 */

  /* 与sqlite3相关的配置 */
  sqlite3 *db; /* sqlite3的实例 */
  /* sqlite3的准备语句 */
  sqlite3_stmt *get_document_id_st;
  sqlite3_stmt *get_document_title_st;
  sqlite3_stmt *insert_document_st;
  sqlite3_stmt *update_document_st;
  sqlite3_stmt *get_token_id_st;
  sqlite3_stmt *get_token_st;
  sqlite3_stmt *store_token_st;
  sqlite3_stmt *get_postings_st;
  sqlite3_stmt *update_postings_st;
  sqlite3_stmt *get_settings_st;
  sqlite3_stmt *replace_settings_st;
  sqlite3_stmt *get_document_count_st;
  sqlite3_stmt *begin_st;
  sqlite3_stmt *commit_st;
  sqlite3_stmt *rollback_st;
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
} wiser_env;

/* TRUE/FALSE */
#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

#define DEFAULT_II_BUFFER_UPDATE_THRESHOLD 2048
<<<<<<< HEAD
#define STRING_SIZE 4096
=======

>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
#endif /* __WISER_H__ */
