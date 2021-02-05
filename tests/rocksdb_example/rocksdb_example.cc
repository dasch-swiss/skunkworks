
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

  // Put key-value
  s = db->Put(WriteOptions(), "key1", "value");
  CHECK(s.ok());
  std::string value;
  // get value
  s = db->Get(ReadOptions(), "key1", &value);
  CHECK(s.ok());
  CHECK(value == "value");

  // atomically apply a set of updates
  {
    WriteBatch batch;
    batch.Delete("key1");
    batch.Put("key2", value);
    s = db->Write(WriteOptions(), &batch);
  }

  s = db->Get(ReadOptions(), "key1", &value);
  CHECK(s.IsNotFound());

  db->Get(ReadOptions(), "key2", &value);
  CHECK(value == "value");

  {
    PinnableSlice pinnable_val;
    db->Get(ReadOptions(), db->DefaultColumnFamily(), "key2", &pinnable_val);
    CHECK(pinnable_val == "value");
  }

  {
    std::string string_val;
    // If it cannot pin the value, it copies the value to its internal buffer.
    // The intenral buffer could be set during construction.
    PinnableSlice pinnable_val(&string_val);
    db->Get(ReadOptions(), db->DefaultColumnFamily(), "key2", &pinnable_val);
    CHECK(pinnable_val == "value");
    // If the value is not pinned, the internal buffer must have the value.
    CHECK(pinnable_val.IsPinned() || string_val == "value");
  }

  PinnableSlice pinnable_val;
  s = db->Get(ReadOptions(), db->DefaultColumnFamily(), "key1", &pinnable_val);
  CHECK(s.IsNotFound());
  // Reset PinnableSlice after each use and before each reuse
  pinnable_val.Reset();
  db->Get(ReadOptions(), db->DefaultColumnFamily(), "key2", &pinnable_val);
  CHECK(pinnable_val == "value");
  pinnable_val.Reset();
  // The Slice pointed by pinnable_val is not valid after this point

  delete db;
}