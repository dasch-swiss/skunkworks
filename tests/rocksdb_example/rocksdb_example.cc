
#include <cstdio>
#include <string>

#include "catch2/catch.hpp"

#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"


std::string kDBPath = "/tmp/rocksdb_simple_example";

TEST_CASE("rocksdb tests", "[rocksdb|") {

using namespace ROCKSDB_NAMESPACE;

DB* db;
Options options;
// Optimize RocksDB. This is the easiest way to get RocksDB to perform well
options.IncreaseParallelism();
options.OptimizeLevelStyleCompaction();
// create the DB if it's not already present
options.create_if_missing = true;

// open DB
Status s = DB::Open(options, kDBPath, &db);

CHECK(s.ok());
}