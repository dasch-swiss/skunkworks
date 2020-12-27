//
// Created by Lukas Rosenthaler on 21.12.20.
//

#ifndef SKUNKWORKS_ENTITIES_CONFIGURATION_H_
#define SKUNKWORKS_ENTITIES_CONFIGURATION_H_

#include <string>

namespace dsp {

class DataModel;
class Project;

class Configuration {
  /*!
   * Configuration singleton
   */
 public:

  /*!
   * Get the configuration instance
   * @return Configuration instance
   */
  static Configuration* init();

  std::string resclass_prefix(const std::shared_ptr<DataModel> &in_data_model) const ;
  std::string property_prefix(const std::shared_ptr<DataModel> &in_data_model) const ;
  std::string value_prefix(const std::shared_ptr<Project> &project) const ;

 private:
  Configuration();

  static Configuration *config_ptr;
  std::string data_model_prefix_;
  std::string resclass_prefix_;
  std::string property_prefix_;
  std::string value_prefix_;
};

}


#endif //SKUNKWORKS_ENTITIES_CONFIGURATION_H_
