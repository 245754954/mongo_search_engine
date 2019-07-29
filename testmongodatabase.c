#include "mongodatabase.h"
#include "myclient.h"
<<<<<<< HEAD
#include "wiser.h"
#include "mysqldatabase.h"

 
static int
init_env1(wiser_env *env,
         int ii_buffer_update_threshold, int enable_phrase_search,
         const char *db_path)
{
  int rc;
  memset(env, 0, sizeof(wiser_env));
  rc = init_database(env, db_path);
  if (!rc)
  {
    env->token_len = N_GRAM;
    env->ii_buffer_update_threshold = ii_buffer_update_threshold;
    env->enable_phrase_search = enable_phrase_search;
  }
  return rc;
}

/**
 * 释放应用程序的运行环境
 * @param[in] env 存储着应用程序运行环境的结构体
 */
static void
fin_env1(wiser_env *env)
{
  fin_database(env);
}

=======
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f

int main(int argc, char const *argv[])
{
    extern int optind;

    int max_index_count = -1; // 不限制参与索引构建的文档数量 /
    int ii_buffer_update_threshold = DEFAULT_II_BUFFER_UPDATE_THRESHOLD;
    int enable_phrase_search = TRUE;
    const char *compress_method_str = NULL, *wikipedia_dump_file = NULL,
               *query = NULL;
<<<<<<< HEAD
    wiser_env env;
    const char *path = "/data/db";
    const char *mongo_url = "mongodb://localhost:27017";
    init_env1(&env, ii_buffer_update_threshold, enable_phrase_search, mongo_url);
=======
    client_env env;
    const char *path = "/data/db";
    const char *mongo_url = "mongodb://localhost:27017";
    init_env2(&env, ii_buffer_update_threshold, enable_phrase_search, mongo_url);
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f

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
<<<<<<< HEAD
   // char *value;
  //   char *key="st";
  //   int doc_count=1;
  // //  void *postings;
  //   //db_get_settings2(&env,key,value);
  //   //db_replace_settings2(&env,key,"good");
  //   int id =  db_get_token_id2(&env,key,1,&doc_count);
  //   printf("the value of id %d\n",id);
=======
    char *value;
    char *key="zfc";
    int doc_count=1;
    void *postings;
    //db_get_settings2(&env,key,value);
    //db_replace_settings2(&env,key,"good");
    //db_get_token_id2(&env,key,1,&doc_count);
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f
    //db_get_token2(&env,1,&value);
   // db_get_postings2(&env,1,&doc_count,&postings);
   // printf("%d\n",doc_count);
    //printf("%s\n",value);
    //printf("%d\n",doc_count);
<<<<<<< HEAD
  
db_get_document_id(&env,"hh",strlen("hh"));
    fin_env1(&env);
=======
    fin_env2(&env);
>>>>>>> deea0c630d1bb382d028c89fea826bee052e293f

    return 0;
}
