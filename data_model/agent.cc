//
// Created by Lukas Rosenthaler on 06.01.21.
//

#include "shared/error/error.h"
#include "agent.h"

static const char file_[] = __FILE__;

namespace dsp {

Agent::Agent(const dsp::Shortname& shortname) : ModelItem() {
  id_ = dsp::Identifier("Agent", shortname.to_string());
  shortname_ = shortname;
}

std::shared_ptr<Agent> Agent::Factory(const dsp::Shortname& shortname, std::shared_ptr<Observer> obs) {
  std::shared_ptr<Agent> tmp(new Agent(shortname));
  if (obs) tmp->attach(obs);
  tmp->add_item<Agent>();
  tmp->notify(ObserverAction::CREATE, tmp);
  return tmp;
}

Agent::Agent(const nlohmann::json &json_obj) : ModelItem() {
  if (json_obj.contains("version") && (json_obj["version"] == 1) && json_obj.contains("type")
      && (json_obj["type"] == "Agent")) {

    if (!json_obj.contains("id")) throw Error(file_, __LINE__, R"("Agent" serialization has no "id".)");
    id_ = dsp::Identifier(json_obj["id"].get<std::string>());

    if (!json_obj.contains("shortname")) throw Error(file_, __LINE__, R"("Agent" serialization has no "shortname".)");
    shortname_ = dsp::Shortname(json_obj["shortname"].get<std::string>());
  } else {
    throw Error(file_, __LINE__, R"(Agent {} serialization not consistent.)");
  }
}

std::shared_ptr<Agent> Agent::Factory(const nlohmann::json &json_obj, std::shared_ptr<Observer> obs) {
  std::shared_ptr<Agent> tmp(new Agent(json_obj)); // construct Agent object using private constructor
  if (ModelItem::item_exists(tmp->id())) { //
    throw Error(file_, __LINE__, fmt::format(R"(Agent "{}" with same id={} already exists!)",
        tmp->shortname().to_string(), tmp->id().to_string()));
  }
  if (obs) tmp->attach(obs);
  tmp->add_item<Agent>();
  tmp->notify(ObserverAction::CREATE, tmp);
  return tmp;
}


nlohmann::json Agent::to_json() {
  nlohmann::json json_obj = {
      {"version", 1},
      {"type", "Agent"},
      {"id", id_.to_string()},
      {"shortname", shortname_.to_string()},
  };
  return json_obj;
}


}