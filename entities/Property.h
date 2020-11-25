//
<<<<<<< HEAD
// Created by Lukas Rosenthaler on 25.11.20.
=======
// Created by Ivan Subotic on 25/11/2020.
>>>>>>> 5c98e6b8a9734b783ebaf1bff116ca1c3ba1e671
//

#ifndef SKUNKWORKS_PROPERTY_H
#define SKUNKWORKS_PROPERTY_H

<<<<<<< HEAD
#include <string>

#include "ResourceClass.h"
#include "ValueClass.h"

namespace dsp {

    class Property {
    private:
        std::string id_;
        std::string class_label_;
        std::string class_description_;
        std::shared_ptr<ResourceClass> resource_class_;
        std::shared_ptr<ValueClass> value_class_;
        std::shared_ptr<Property> sub_class_of_;

        Property(const std::string class_label,
                 const std::string class_description,
                 const std::shared_ptr <ResourceClass> resource_class,
                 const std::shared_ptr <ValueClass> value_class,
                 const std::shared_ptr <Property> sub_class_of = nullptr);

        inline std::string id() { return id_; }
    };
}
=======

class Property {

};
>>>>>>> 5c98e6b8a9734b783ebaf1bff116ca1c3ba1e671


#endif //SKUNKWORKS_PROPERTY_H
