#pragma once

#include "duckdb/common/unique_ptr.hpp"
#include "duckdb/storage/object_cache.hpp"

namespace duckdb {

class BaseStatistics;
class ColumnList;
class ParquetReader;

class DataFileStatistics : public ObjectCacheEntry {
public:
    DataFileStatistics(ParquetReader &reader, const ColumnList &columns);

public:
    static string ObjectType() {
        return "data_file_statistics";
    }

    string GetObjectType() override {
        return ObjectType();
    }

    idx_t NumRows() {
        return num_rows;
    }

    BaseStatistics *Get(const string &name) {
        return column_stats.at(name).get();
    }

private:
    idx_t num_rows;
    unordered_map<string, unique_ptr<BaseStatistics>> column_stats;
};

extern ObjectCache columnstore_stats;

} // namespace duckdb
