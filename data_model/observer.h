//
// Created by Lukas Rosenthaler on 11.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_OBSERVER_H_
#define SKUNKWORKS_DATA_MODEL_OBSERVER_H_

#include <memory>

#include "model_item.h"

namespace dsp {

enum class ObserverAction {
  CREATE, READ, UPDATE, REMOVE
};

class Observer {
 public:
  virtual ~Observer() {};

  virtual void update(ObserverAction action, std::shared_ptr<ModelItem> item) const = 0;
};



}
#endif //SKUNKWORKS_DATA_MODEL_OBSERVER_H_
