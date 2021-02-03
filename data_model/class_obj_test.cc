//
// Created by Lukas Rosenthaler on 14.01.21.
//
#include "catch2/catch.hpp"

#include <string>
#include <memory>
#include "external/nlohmann/json.hpp"

#include "shared/xsd_types/lang_string.h"
#include "agent.h"
#include "project.h"
#include "data_model.h"
#include "observer.h"
#include "class_obj.h"

class MyClassObj : public dsp::ClassObj {
 public:

  static std::shared_ptr<MyClassObj> Factory(
      const dsp::Identifier& created_by,
      const dsp::Identifier& in_data_model,
      const xsd::LangString& class_label,
      const xsd::LangString& class_description,
      std::shared_ptr<dsp::Observer> obs = {}) {
    std::shared_ptr<MyClassObj> tmp(new MyClassObj(created_by, in_data_model, class_label, class_description));
    if (obs) tmp->attach(obs);
    tmp->add_item<MyClassObj>();
    tmp->notify(dsp::ObserverAction::CREATE, tmp);
    return tmp;
  }

  static std::shared_ptr<MyClassObj> Factory(
      const nlohmann::json& json_obj,
      std::shared_ptr<dsp::Observer> obs = {}) {
    std::shared_ptr<MyClassObj> tmp(new MyClassObj(json_obj));
    if (obs) tmp->attach(obs);
    tmp->add_item<MyClassObj>();
    tmp->notify(dsp::ObserverAction::CREATE, tmp);
    return tmp;
  }

  void update(const dsp::Identifier agent_id) {
    last_modification_date_ = xsd::DateTimeStamp();
    modified_by_ = agent_id;
    notify(dsp::ObserverAction::UPDATE, shared_from_this());
  }

  nlohmann::json to_json() override {
    nlohmann::json json_obj = ClassObj::to_json();
    json_obj["type"] = "MyClassObj";
    return json_obj;
  }

  std::string  to_string() override { return "gaga"s; }
 private:
  MyClassObj(
      const dsp::Identifier& created_by,
      const dsp::Identifier& in_data_model,
      const xsd::LangString& class_label,
      const xsd::LangString& class_description
  ) : ClassObj(created_by, in_data_model, class_label, class_description) {
    id_ = dsp::Identifier();
  }

  MyClassObj(
      const nlohmann::json& json_obj) : ClassObj(json_obj) { }

};

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


TEST_CASE("ClassObj", "Unit") {
  dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("MyAgent"));
  dsp::ProjectPtr my_project = dsp::Project::Factory(
      my_agent->id(),
      dsp::Shortcode("4123"),
      dsp::Shortname("MyAgent"));
  dsp::DataModelPtr my_data_model = dsp::DataModel::Factory(my_agent->id(), dsp::Shortname("data_model"));
  my_project->add_data_model(my_data_model->id(), my_agent->id());
  std::shared_ptr<MyClassObj> my_class_obj = MyClassObj::Factory(
      my_agent->id(),
      my_data_model->id(),
      xsd::LangString("en", "my_label"),
      xsd::LangString("en", "my_description"));

  SECTION("ClassObj unit tests") {
    REQUIRE(my_class_obj->label() == xsd::LangString("en", "my_label"));
    REQUIRE(my_class_obj->description() == xsd::LangString("en", "my_description"));
    REQUIRE_NOTHROW(my_class_obj->label(xsd::LangString("fr", "mon label"), my_agent->id()));
    REQUIRE(my_class_obj->label() == xsd::LangString("fr", "mon label"));
    my_class_obj->label_add("en", "english_label", my_agent->id());
    REQUIRE(static_cast<std::string>(my_class_obj->label().get("fr")) == "mon label");
    REQUIRE(static_cast<std::string>(my_class_obj->label().get("en")) == "english_label");
    my_class_obj->label_remove("fr", my_agent->id());
    REQUIRE(static_cast<std::string>(my_class_obj->label().get("fr")) == "english_label");
  }

  SECTION("ClassObj JSON tests") {
    my_class_obj->update(my_agent->id());
    nlohmann::json json_obj = my_class_obj->to_json();
    REQUIRE(json_obj["version"].get<int>() == 1);
    REQUIRE(json_obj["type"].get<std::string>() == "MyClassObj");
    REQUIRE(json_obj["id"].get<std::string>() == static_cast<std::string>(my_class_obj->id()));
    REQUIRE(json_obj["creation_date"].get<std::string>() == static_cast<std::string>(my_class_obj->creation_date()));
    REQUIRE(json_obj["created_by"].get<std::string>() == static_cast<std::string>(my_class_obj->created_by_id()));
    REQUIRE(json_obj["last_modification_date"].get<std::string>() == static_cast<std::string>(my_class_obj->last_modification_date()));
    REQUIRE(json_obj["modified_by"].get<std::string>() == static_cast<std::string>(my_class_obj->modified_by_id()));
    REQUIRE(json_obj["in_data_model"].get<std::string>() == static_cast<std::string>(my_class_obj->in_data_model_id()));
    REQUIRE(json_obj["label"]["en"] == "my_label"s);
    REQUIRE(json_obj["description"]["en"] == "my_description"s);
    std::shared_ptr<MyClassObj> same = MyClassObj::Factory(json_obj);
    REQUIRE(same->id() == my_class_obj->id());
    REQUIRE(same->creation_date() == my_class_obj->creation_date());
    REQUIRE(same->created_by_id() == my_class_obj->created_by_id());
    REQUIRE(same->last_modification_date() == my_class_obj->last_modification_date());
    REQUIRE(same->modified_by_id() == my_class_obj->modified_by_id());
    REQUIRE(same->in_data_model_id() == my_class_obj->in_data_model_id());
    REQUIRE(same->label() == my_class_obj->label());
    REQUIRE(same->description() == my_class_obj->description());
  }

  SECTION("ClassObj unit tests with observer") {
    std::shared_ptr<MyObserver> observer(new MyObserver());
    dsp::ModelItem::delete_item<MyClassObj>(my_class_obj);
    my_class_obj = MyClassObj::Factory(
        my_agent->id(),
        my_data_model->id(),
        xsd::LangString("en", "my_label"s),
        xsd::LangString("en", "my_description"s),
        observer);
    REQUIRE(value_ == "CREATE"s);
    my_class_obj->label_add("fr", "french_label"s, my_agent->id());
    REQUIRE(value_ == "UPDATE"s);
    REQUIRE(static_cast<std::string>(my_class_obj->label().get("fr")) == "french_label"s);
    my_class_obj->label_remove("fr", my_agent->id());
    REQUIRE(value_ == "UPDATE"s);
    REQUIRE(static_cast<std::string>(my_class_obj->label().get("en")) == "my_label"s);
  }

}