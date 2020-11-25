#include <iostream>
#include <string>
#include <unordered_map>

#include "Property.h"
#include "ResourceClass.h"
#include "ValueClass.h"

int main(int argc, char *argv[]) {

    //
    // init value classes (SYSTEM)
    //
    ValueClass text_value = new ValueClass("TextValueClass", "bla bla");
    ValueClass integer_value = new ValueClass("IntegerValueClass", "bla bla");


    ResourceClass my_resclass = new ResourceClass("myresclass", "This is my resource class", nullptr);

    Property title = new Property("hasTitle", "bla bla", my_resclass, text_value);
    Property age = new Property("hasAge", "bla bla", my_resclass, integer_value);

    my_resclass.add_property(title, 1, 3);
    my_resclass.add_property(age, 0, 1);

    // finished creating/reading ontologies
    //----------------------------
    //
    // API route create resource
    try {
        Resource narrenschiff = my_resclass.create_instance(
                makeprop("hasTitle", "Das Narrenschiff"),
                makeprop("hasTitle", "Stultivera Navis"),
                makeprop("hasAge", 82));
    } catch (const CreateError &err) {
        api << err;
        return;
    }
    try {
        statestore << narrenschiff;
    } catch (const StateError &err) {
        api << err;
        return;
    }
    try {
        eventsource << narrenchiff;
    } catch (const EventSourceError) {
        api << err;
        return
    }
    api << narrenschiff;

}
