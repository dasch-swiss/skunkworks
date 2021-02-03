//
// Created by Lukas Rosenthaler on 12.01.21.
//

#ifndef SKUNKWORKS_DATA_MODEL_SUBJECT_H_
#define SKUNKWORKS_DATA_MODEL_SUBJECT_H_

#include <set>
#include "observer.h"

namespace dsp {

class Subject {

 public:;
  inline Subject() = default;
  inline Subject(std::shared_ptr<Observer> observer) { observers_.insert(observer); }
  inline Subject(std::set<ObserverPtr>& observers) {observers_ = observers; }
  inline void attach(std::shared_ptr<Observer> observer) { observers_.insert(observer); }
  inline void detach(std::shared_ptr<Observer> observer) { observers_.erase(observer); }
  inline void notify(ObserverAction action, std::shared_ptr<ModelItem> item) {
    for (const auto& observer: observers_) observer->update(action, item);
  }
 private:
  std::set<ObserverPtr> observers_;
};


}

#endif //SKUNKWORKS_DATA_MODEL_SUBJECT_H_
