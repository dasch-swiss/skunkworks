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

namespace dsp {

class Domain;

class Agent : public ModelItem {
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
  static std::shared_ptr<Agent> Factory(const dsp::Shortname& shortname);

  /*!
   * Agent Factory for creating a managed Agent from the repository
   * @param json_obj
   * @return
   */
  static std::shared_ptr<Agent> Factory(const nlohmann::json& json_obj);

  /*!
   * Destructor
   */
  //inline ~Agent() override {  };

  bool operator==(const Agent& other) { return id_ == other.id_ && shortname_ == other.shortname_; }

  inline dsp::Shortname shortname() const { return shortname_; }

  /*!
   * Serialize the Agent instance to a nlohmann::json object
   * @return
   */
  nlohmann::json to_json() override ;

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
