//
// Created by Lukas Rosenthaler on 25.11.20.
//

#ifndef SKUNKWORKS_VALUECLASS_H
#define SKUNKWORKS_VALUECLASS_H

#include <string>

namespace dsp {


    class ValueClass {
        std::string id_;
        std::string class_label_;
        std::string class_description_;

        ValueClass(const std::string class_label,
                   const std::string class_description);

        inline std::string id() { return id_; }

    };

    class Value {
        std::string creation_date;
    };

    class TextValue : public Value {
        std::string stringval;
    };

    class IntegerValue : public Value

}


#endif //SKUNKWORKS_VALUECLASS_H
