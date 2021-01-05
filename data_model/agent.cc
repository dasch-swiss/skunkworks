//
// Created by Lukas Rosenthaler on 27.11.20.
//

#include "shared/error/error.h"
#include "agent.h"

static const char file_[] = __FILE__;

namespace dsp {

Agent::Agent() {
  id_ = Identifier();
}

Agent::Agent(const GenericObjectDescription& object_description) {
  if (object_description.object_type() != "Agent") {
    throw Error(file_, __LINE__, "GenericObjectDescription is not from \"Agent\" class.");
  }
  if (!object_description.has_member("id"))
    throw Error(file_, __LINE__, "GenericObjectDescription for \"Agent\" has no \"id\".");
  id_ = dsp::Identifier(object_description.member<xsd::String>("id"));
}

GenericObjectDescription Agent::get_generic_object_description() {
  GenericObjectDescription object_description(1, "Agent");
  object_description.member("id", id_);
}

}