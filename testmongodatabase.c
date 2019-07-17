#include "mongodatabase.h"
#include "myclient.h"

int main(int argc, char const *argv[])
{
    extern int optind;

    int max_index_count = -1; // 不限制参与索引构建的文档数量 /
    int ii_buffer_update_threshold = DEFAULT_II_BUFFER_UPDATE_THRESHOLD;
    int enable_phrase_search = TRUE;
    const char *compress_method_str = NULL, *wikipedia_dump_file = NULL,
               *query = NULL;
    client_env env;
    const char *path = "/data/db";
    const char *mongo_url = "mongodb://localhost:27017";
    init_env2(&env, ii_buffer_update_threshold, enable_phrase_search, mongo_url);

    int64_t _id = 1;

    //db_get_document_id2(&env, "zxx", _id);
    //char title[25];
    //db_get_document_title2(&env,_id,title);
    //printf("%s\n",title);
    // char* title="zxx";
    //char* body="you";
    //db_add_document2(&env,title,body);
    // get_id2(&env);
    //db_get_document_id2(&env,title,&_id);
    //printf("%ld\n",_id);

    //db_get_document_count2(&env);
    char *value;
    char *key="zfc";
    int doc_count=1;
    void *postings;
    //db_get_settings2(&env,key,value);
    //db_replace_settings2(&env,key,"good");
    //db_get_token_id2(&env,key,1,&doc_count);
    //db_get_token2(&env,1,&value);
   // db_get_postings2(&env,1,&doc_count,&postings);
   // printf("%d\n",doc_count);
    //printf("%s\n",value);
    //printf("%d\n",doc_count);
    fin_env2(&env);

    return 0;
}
