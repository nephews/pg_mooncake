#include "duckdb/common/file_system.hpp"

extern "C" {
#include "postgres.h"

#include "fmgr.h"
}

void MooncakeInitGUC();
void DuckdbInitHooks();

bool mooncake_allow_local_tables = false;
char *mooncake_default_bucket = strdup("");
bool mooncake_enable_local_cache = true;

extern "C" {
PG_MODULE_MAGIC;

void DuckdbInitNode();

void _PG_init() {
    MooncakeInitGUC();
    DuckdbInitHooks();
    DuckdbInitNode();

    auto local_fs = duckdb::FileSystem::CreateLocal();
    local_fs->CreateDirectory("mooncake_local_cache");
    local_fs->CreateDirectory("mooncake_local_tables");
}
}
