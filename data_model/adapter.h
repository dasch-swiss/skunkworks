//
// Created by Lukas Rosenthaler on 21.12.20.
//

#ifndef SKUNKWORKS_ENTITIES_ADAPTER_H_
#define SKUNKWORKS_ENTITIES_ADAPTER_H_

#include "helpers/xsd_types/xsd.h"

namespace dsp {

template <typename T>
class Adapter {
  T read(const T &obj) = 0;
  T create(const T &obj) = 0;
  T update(const T &obj) = 0;
  T remove(const T &obj) = 0;
};

}


#endif //SKUNKWORKS_ENTITIES_ADAPTER_H_
