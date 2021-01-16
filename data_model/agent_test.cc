//
// Created by Lukas Rosenthaler on 13.01.21.
//
#include "catch2/catch.hpp"

#include "external/nlohmann/json.hpp"
#include <string>

#include "model_item.h"
#include "agent.h"

using namespace std::string_literals;

static std::string value_;

class MyObserver: public dsp::Observer {
 public:
  inline void update(dsp::ObserverAction action, std::shared_ptr<dsp::ModelItem> item) override {
    switch (action) {
      case dsp::ObserverAction::CREATE: value_ = "CREATE"s; break;
      case dsp::ObserverAction::READ: value_ = "READ"s; break;
      case dsp::ObserverAction::UPDATE:  value_ = "UPDATE"s; break;
      case dsp::ObserverAction::REMOVE: value_ = "REMOVE"; break;
    }
  }
};


TEST_CASE("Agent", "Unit") {
  REQUIRE(dsp::Agent::Factory(dsp::Shortname("shortAgent")));
  dsp::AgentPtr my_agent = dsp::Agent::Factory(dsp::Shortname("shortAgent"));

  SECTION("Simple tests") {
    REQUIRE(static_cast<std::string>(*my_agent) == "shortAgent"s);
    REQUIRE(my_agent->shortname() == "shortAgent"s);

    INFO("Setting member variables...");
    my_agent->shortname("longAgent"s);
    REQUIRE(my_agent->shortname() == "longAgent"s);
  }

  SECTION("ModelItem part") {
    dsp::AgentPtr my_agent2 = dsp::ModelItem::get_item<dsp::Agent>(my_agent->id());
    REQUIRE(my_agent == my_agent2);
  }

  SECTION("Checking to_json()...") {
    nlohmann::json json_obj = my_agent->to_json();
    REQUIRE(json_obj["shortname"].get<std::string>() == "shortAgent"s);
    REQUIRE(json_obj["shortname"].get<std::string>() == static_cast<std::string>(my_agent->shortname()));
    REQUIRE(json_obj["id"].get<std::string>() == static_cast<std::string>(my_agent->id()));
  }


  SECTION("Checking factory from json object...") {
    nlohmann::json json_obj = my_agent->to_json();
    dsp::Identifier id = my_agent->id();
    dsp::Shortname shortname = my_agent->shortname();
    dsp::ModelItem::delete_item<dsp::Agent>(my_agent);
    REQUIRE(dsp::ModelItem::size() == 0);

    REQUIRE(my_agent == nullptr);
    my_agent = dsp::Agent::Factory(json_obj);
    REQUIRE(my_agent->id() == id);
    REQUIRE(my_agent->shortname() == shortname);
    dsp::ModelItem::delete_item<dsp::Agent>(my_agent);

  }

  SECTION("Checking observer pattern") {
    std::shared_ptr<MyObserver> observer(new MyObserver());
    my_agent = dsp::Agent::Factory(dsp::Shortname("shortAgent"), observer);
    nlohmann::json json_obj = my_agent->to_json();
    REQUIRE(value_ == "CREATE"s);
    my_agent->shortname("NotSoShortName"s);
    REQUIRE(value_ == "UPDATE"s);
    dsp::ModelItem::delete_item<dsp::Agent>(my_agent);
    my_agent = dsp::Agent::Factory(json_obj, observer);
    REQUIRE(value_ == "CREATE"s);
  }
}