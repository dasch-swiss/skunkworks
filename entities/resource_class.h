//
// Created by Ivan Subotic on 25/11/2020.
//

#include <string>

#ifndef SKUNKWORKS_RESOURCE_CLASS_H
#define SKUNKWORKS_RESOURCE_CLASS_H


class ResourceClass {
private:
    std::string class_label_;
    std::string class_description_;
    std::shared_ptr<ResourceClass> subClassOf_;

public:
    inline ResourceClass(
        const std::string class_label,
        const std::string class_description,
        const std::shared_ptr<ResourceClass> subClassOf) :
            class_label_(class_label),
            class_description_(class_description),
            subClassOf_(subClassOf) {};

};


#endif //SKUNKWORKS_RESOURCE_CLASS_H
