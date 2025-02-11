#ifndef LDB_HNSW_OPTIONS_H
#define LDB_HNSW_OPTIONS_H
#include <postgres.h>

#include <utils/relcache.h>  // Relation

// todo:: add hnsw dynamic vector dimension constraints
// based on vector element size

/* 32 in faiss */
#define HNSW_DEFAULT_M 16
#define HNSW_MAX_M     128
/* 40 in faiss */
#define HNSW_DEFAULT_EF_CONSTRUCTION 128
#define HNSW_MAX_EF_CONSTRUCTION     400
/* 10 in faiss*/
#define HNSW_DEFAULT_EF               64
#define HNSW_MAX_EF                   400
#define HNSW_DEFAULT_PROVIDER         "usearch"
#define HNSW_MAX_ELEMENT_LIMIT        200000000
#define ALG_OPTION_MAX_STRING_LEN     32
#define HNSWLIB_DEFAULT_ELEMENT_LIMIT 2000000

#define LDB_HNSW_DEFAULT_K 10
#define LDB_HNSW_MAX_K     1000
/* HNSW index options */
typedef struct HnswOptions
{
    int32 vl_len_; /* varlena header (do not touch directly!) */
    // max elements the table will ever have. required for hnswlib
    int element_limit;
    int m;
    int ef_construction;
    int ef;
    int alg;
    // char[ALG_OPTION_MAX_STRING_LEN] alg;
} HnswOptions;

int   HnswGetM(Relation index);
int   HnswGetEfConstruction(Relation index);
int   HnswGetEf(Relation index);
char *HnswGetAlgorithm(Relation index);
int   HnswGetElementLimit(Relation index);

bytea *ldb_amoptions(Datum reloptions, bool validate);

#endif  // LDB_HNSW_OPTIONS_H