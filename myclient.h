#ifndef __MYCLIENT_H__
#define __MYCLIENT_H__
#include <mongoc/mongoc.h>
#include "wiser.h"
typedef struct
{
   
    mongoc_collection_t *documentcountcollections;
    mongoc_collection_t *tokencountcollections;
    mongoc_collection_t *settings;
    mongoc_collection_t *documents;
    mongoc_collection_t *tokens;

    mongoc_client_t *client;
    mongoc_database_t *database;

    int token_len;            /* 词元的长度。N-gram中N的取值 */
    compress_method compress; /* 压缩倒排列表等数据的方法 */
    int enable_phrase_search; /* 是否进行短语检索 */

    inverted_index_hash *ii_buffer; /* 用于更新倒排索引的缓冲区（Buffer） */
    int ii_buffer_count;            /* 用于更新倒排索引的缓冲区中的文档数 */
    int ii_buffer_update_threshold; /* 缓冲区中文档数的阈值 */
    int indexed_count;              /* 建立了索引的文档数 */

} client_env;

void query1(char *term);


int init_env2(client_env *env,int ii_buffer_update_threshold, int enable_phrase_search,const char *db_path);

void fin_env2(client_env *env);

#endif