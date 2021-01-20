//
// Created by Lukas Rosenthaler on 13.01.21.
//
#include "catch2/catch.hpp"

#include "external/nlohmann/json.hpp"
#include <string>

#include "model_item.h"

using namespace std::string_literals;

 class MyModelItem : public dsp::ModelItem {
  public:;
   MyModelItem(const std::string& name) {
     id_ = dsp::Identifier("ModelItem"s, name);
     name_ = name;
   }

   std::string name() { return name_; }

   std::string to_string() override { return name_; }

   nlohmann::json to_json() override {
     nlohmann::json json_obj = {
         {"id", id_.to_string()},
         {"name", name_}
     };
     return json_obj;
   }
  private:
   std::string name_;

 };

TEST_CASE("ModelItem", "Unit") {
  REQUIRE_NOTHROW(MyModelItem("gaga"));
  std::shared_ptr<MyModelItem> my_item = std::make_shared<MyModelItem>("my_item");
  REQUIRE_NOTHROW(my_item->add_item<MyModelItem>());

  SECTION("Simple Unit tests") {
    REQUIRE(my_item->name() == "my_item"s);
    nlohmann::json json_obj = {
        {"id", my_item->id()},
        {"name", my_item->name()}
    };
    REQUIRE(dsp::ModelItem::item_exists(my_item->id()));
    std::shared_ptr<MyModelItem> same_item = dsp::ModelItem::get_item<MyModelItem>(my_item->id());
    REQUIRE(my_item == same_item);
    REQUIRE(my_item->id() == same_item->id());
    REQUIRE(my_item->name() == same_item->name());
  }

  SECTION("Internal bookkeeping") {
    REQUIRE(dsp::ModelItem::size() == 1);
    dsp::ModelItem::delete_item<MyModelItem>(my_item);
    my_item.reset();
    REQUIRE(dsp::ModelItem::size() == 0);
    REQUIRE(my_item == nullptr);
  }
}