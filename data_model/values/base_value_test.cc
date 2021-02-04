//
// Created by Lukas Rosenthaler on 18.12.20.
//

#include "catch2/catch.hpp"
#include "data_model/observer.h"
#include "shared/xsd_types/lang_string.h"

#include "base_value.h"

//#include "simple_text_value.h"

class MyBaseValue : public dsp::BaseValue {
 public:
  static std::shared_ptr<MyBaseValue> Factory(
      const dsp::Identifier &created_by,
      std::shared_ptr<dsp::Observer> obs = {}
      ) {
    std::shared_ptr<MyBaseValue> tmp (new MyBaseValue(created_by));
    if (obs) tmp->attach(obs);
    tmp->add_item<MyBaseValue>();
    tmp->notify(dsp::ObserverAction::CREATE, tmp);
    return tmp;
  }

  static std::shared_ptr<MyBaseValue> Factory(
      const xsd::LangString &comment,
      const dsp::Identifier &created_by,
      std::shared_ptr<dsp::Observer> obs = {}
      ) {
    std::shared_ptr<MyBaseValue> tmp (new MyBaseValue(comment, created_by));
    if (obs) tmp->attach(obs);
    tmp->add_item<MyBaseValue>();
    tmp->notify(dsp::ObserverAction::CREATE, tmp);
    return tmp;
  }

  static std::shared_ptr<MyBaseValue> Factory(const nlohmann::json& json_obj, std::shared_ptr<dsp::Observer> obs = {}) {
    std::shared_ptr<MyBaseValue> tmp(new MyBaseValue(json_obj));
    if (obs) tmp->attach(obs);
    tmp->add_item<MyBaseValue>();
    tmp->notify(dsp::ObserverAction::CREATE, tmp);
    return tmp;
  }

  void update(const dsp::Identifier agent_id) {
    last_modification_date_ = xsd::DateTimeStamp();
    modified_by_ = agent_id;
    notify(dsp::ObserverAction::UPDATE, shared_from_this());
  }

  nlohmann::json to_json() override {
    nlohmann::json json_obj = BaseValue::to_json();
    json_obj["type"] = "MyBaseValue";
    return json_obj;
  }


  std::string to_string() override { return "gaga"s; }

 private:
  MyBaseValue(const dsp::Identifier &created_by) : BaseValue(created_by) {
    id_ = dsp::Identifier();
  }

  MyBaseValue(const xsd::LangString &comment, const dsp::Identifier &created_by) : BaseValue(comment, created_by) {
    id_ = dsp::Identifier();
  }

  MyBaseValue(const nlohmann::json& json_obj) :BaseValue(json_obj) { }

};

using MyBaseValuePtr = std::shared_ptr<MyBaseValue>;

static std::string value_;

class MyObserver: public dsp::Observer {
 public:
  inline void update(dsp::ObserverAction action, std::shared_ptr<dsp::ModelItem> item)  override {
    switch (action) {
      case dsp::ObserverAction::CREATE: value_ = "CREATE"s; break;
      case dsp::ObserverAction::READ: value_ = "READ"s; break;
      case dsp::ObserverAction::UPDATE:  value_ = "UPDATE"s; break;
      case dsp::ObserverAction::REMOVE: value_ = "REMOVE"; break;
    }
  }
};


TEST_CASE("Simple catch2 tests", "[catch2|") {
  dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("MyAgent"));
  xsd::LangString lang_string {"en", "Waseliwas"};
  CHECK_NOTHROW(MyBaseValue::Factory(my_agent->id()));
  CHECK_NOTHROW(MyBaseValue::Factory(lang_string, my_agent->id()));

  SECTION("BaseValue unit tests") {
    xsd::DateTimeStamp before{};
    MyBaseValuePtr base_value_ptr(MyBaseValue::Factory(lang_string, my_agent->id()));
    CHECK(base_value_ptr->comment("en") == xsd::String("Waseliwas"));
    CHECK(base_value_ptr->id() != dsp::Identifier::empty_identifier());
    CHECK(base_value_ptr->created_by() == my_agent->id());
    CHECK(base_value_ptr->creation_date() > before);
    xsd::LangString delcomment {"en", "was useless!"};
    base_value_ptr->remove(delcomment, my_agent->id());
    CHECK(base_value_ptr->is_deleted());
    CHECK(base_value_ptr->deleted_by() == my_agent->id());
    CHECK(base_value_ptr->delete_date() > before);
  }

  SECTION("BaseValue JSON tests") {
    MyBaseValuePtr base_value_ptr(MyBaseValue::Factory(lang_string, my_agent->id()));
    base_value_ptr->update(my_agent->id());
    xsd::LangString delcomment {"en", "was useless!"};
    base_value_ptr->remove(delcomment, my_agent->id());
    nlohmann::json json_obj = base_value_ptr->to_json();
    REQUIRE(json_obj["version"].get<int>() == 1);
    REQUIRE(json_obj["type"].get<std::string>() == "MyBaseValue");
    REQUIRE(json_obj["id"].get<std::string>() == static_cast<std::string>(base_value_ptr->id()));
    REQUIRE(json_obj["creation_date"].get<std::string>() == static_cast<std::string>(base_value_ptr->creation_date()));
    REQUIRE(json_obj["created_by"].get<std::string>() == static_cast<std::string>(base_value_ptr->created_by()));
    REQUIRE(json_obj["last_modification_date"].get<std::string>() == static_cast<std::string>(base_value_ptr->last_modification_date()));
    REQUIRE(json_obj["modified_by"].get<std::string>() == static_cast<std::string>(base_value_ptr->modified_by()));
    REQUIRE(json_obj["delete_date"].get<std::string>() == static_cast<std::string>(base_value_ptr->delete_date()));
    REQUIRE(json_obj["deleted_by"].get<std::string>() == static_cast<std::string>(base_value_ptr->deleted_by()));
    REQUIRE(json_obj["delete_comment"]["en"] == "was useless!"s);
    MyBaseValuePtr same = MyBaseValue::Factory(json_obj);
    REQUIRE(same->id() == base_value_ptr->id());
    REQUIRE(same->creation_date() == base_value_ptr->creation_date());
    REQUIRE(same->created_by() == base_value_ptr->created_by());
    REQUIRE(same->last_modification_date() == base_value_ptr->last_modification_date());
    REQUIRE(same->modified_by() == base_value_ptr->modified_by());
    REQUIRE(same->delete_date() == base_value_ptr->delete_date());
    REQUIRE(same->deleted_by() == base_value_ptr->deleted_by());
    REQUIRE(same->comment() == base_value_ptr->comment());
    REQUIRE(same->comment() == base_value_ptr->comment());
  }

  SECTION("BaseValue with observer") {
    std::shared_ptr<MyObserver> observer(new MyObserver());
    MyBaseValuePtr base_value_ptr(MyBaseValue::Factory(lang_string, my_agent->id(), observer));
    REQUIRE(value_ == "CREATE"s);
    base_value_ptr->comment_add("fr"s, "français"s, my_agent->id());
    REQUIRE(value_ == "UPDATE"s);
    base_value_ptr->remove(my_agent->id());
    REQUIRE(value_ == "REMOVE"s);
  }
}

