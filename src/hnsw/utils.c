#include <postgres.h>

#include "utils.h"

#include "hnsw.h"
#include "usearch.h"
#include "options.h"

void LogUsearchOptions(usearch_init_options_t *opts)
{
    /*todo:: in usearch.h create const char arrays like
char* scalar_names = {
    usearch_scalar_f32_k: "f32",
    usearch_scalar_f64_k: "f64"
}
so below the human readable string names can be printed
*/
    elog(INFO,
         "usearch_init_options_t: metric_kind: %d, metric: %p, "
         "quantization: %d, dimensions: %ld, connectivity: %ld, "
         "expansion_add: %ld, expansion_search: %ld",
         opts->metric_kind,
         opts->metric,
         opts->quantization,
         opts->dimensions,
         opts->connectivity,
         opts->expansion_add,
         opts->expansion_search);
}

void PopulateUsearchOpts(Relation index, usearch_init_options_t *opts)
{
    opts->connectivity = HnswGetM(index);
    opts->expansion_add = HnswGetEfConstruction(index);
    opts->expansion_search = HnswGetEf(index);
    opts->metric_kind = usearch_metric_l2sq_k;
    opts->metric = NULL;
    opts->quantization = usearch_scalar_f32_k;
}
