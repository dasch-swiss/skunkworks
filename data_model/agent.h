//
// Created by Lukas Rosenthaler on 27.11.20.
//

#ifndef SKUNKWORKS_AGENT_H
#define SKUNKWORKS_AGENT_H

#include <memory>

#include "external/nlohmann/json.hpp"

#include "shared/xsd_types/xsd_any_uri.h"
#include "shared/dsp_types/identifier.h"
#include "shared/dsp_types/shortname.h"
#include "external/nlohmann/json.hpp"

#include "model_item.h"
#include "subject.h"

using namespace std::string_literals;

namespace dsp {

class Domain;

class Agent : public ModelItem, public Subject {
  /*!
   * An "Agent" is an institution or an individual that is able to identify itself and
   * perform requests on the DSP repository. Typically it is a "human" user, but it also
   * can by a software deamon that acts on the data. An Agent is identfied by it's assigned
   * id and a shortname that must be unique. THe identifier is based on a V5 named uuid with
   * the domain "Agent" and the shortname.
   *
   * The class inherits from ModelItem which manages the shared pointers holding the instances.
   */
 public:

  /*!
   * Agent factory for creating managed an Agent taking a shortname as parameter
   * @param shortname
   * @return
   */
  static std::shared_ptr<Agent> Factory(const dsp::Shortname& shortname, ObserverPtr obs = {});

  /*!
   * Agent Factory for creating a managed Agent from the repository
   * @param json_obj
   * @return
   */
  static std::shared_ptr<Agent> Factory(const nlohmann::json& json_obj, ObserverPtr obs = {});

  /*!
   * Compares 2 agents for equality
   * @param other
   * @return true or false
   */
  bool operator==(const Agent& other) { return id_ == other.id_ && shortname_ == other.shortname_; }

  /*!
   * Getter for the shortname
   * @return dsp::Shortname instance
   */
  inline dsp::Shortname shortname() const { return shortname_; }

  /*!
   * Setter for the shortname
   * @param shortname
   */
  inline void shortname(const dsp::Shortname& shortname) {
    shortname_ = shortname;
    notify(ObserverAction::UPDATE, shared_from_this());
  }

  /*!
   * Serialize the Agent instance to a nlohmann::json object
   * @return
   */
  nlohmann::json to_json() override ;

  inline friend std::ostream &operator<<(std::ostream &out_stream, std::shared_ptr<Agent> agent_ptr) {
    out_stream << std::setw(4) << agent_ptr->to_json();
    return out_stream;
  }

  operator std::string() { return shortname_.to_string(); }

  inline std::string  to_string() override { return shortname_.to_string(); }


 private:
  /*!
   * Constructor taking a shortname as parameter
   * @param shortname
   */
  Agent(const dsp::Shortname& shortname);

  /*!
   * Constructor for deserializing an agant from the repository
   * @param object_description
   */
  Agent(const nlohmann::json& json_obj);

  dsp::Shortname shortname_;
};

using AgentPtr = std::shared_ptr<Agent>;

}


#endif //SKUNKWORKS_AGENT_H
