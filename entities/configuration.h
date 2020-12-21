//
// Created by Lukas Rosenthaler on 21.12.20.
//

#ifndef SKUNKWORKS_ENTITIES_CONFIGURATION_H_
#define SKUNKWORKS_ENTITIES_CONFIGURATION_H_

#include <string>

namespace dsp {

class Configuration {
  /*!
   * Configuration singleton
   */
 public:

  /*!
   * Get the configuration instance
   * @return Configuration instance
   */
  static Configuration *init();

  inline std::string resclass_prefix() const { return resclass_prefix_; }
  inline std::string property_prefix() const { return property_prefix_; }

 private:
  Configuration();

  static Configuration *config_ptr;
  std::string resclass_prefix_;
  std::string  property_prefix_;
};

}


#endif //SKUNKWORKS_ENTITIES_CONFIGURATION_H_
