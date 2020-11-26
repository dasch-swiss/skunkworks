#include <iostream>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

#include "property.h"
#include "resource_class.h"
#include "value_class.h"

TEST(EntitiesTest, GetGreet) {

    // EXPECT_EQ(get_greet("Bazel"), "Hello Bazel");

    //
    // init value classes (SYSTEM)
    //
    dsp::ValueClass text_value = dsp::ValueClass("TextValueClass", "bla bla");
    dsp::ValueClass integer_value = dsp::ValueClass("IntegerValueClass", "bla bla");


    dsp::ResourceClass my_resclass = dsp::ResourceClass("myresclass", "This is my resource class", nullptr);

    dsp::Property title = dsp::Property("hasTitle", "bla bla", my_resclass, text_value);
    dsp::Property age = dsp::Property("hasAge", "bla bla", my_resclass, integer_value);

    my_resclass.add_property(title, 1, 3);
    my_resclass.add_property(age, 0, 1);

    EXPECT_EQ(my_resclass.class_label(), "myresclass");
    EXPECT_EQ(my_resclass.class_description(), "This is my resource class");

    // finished creating/reading ontologies
    //----------------------------
    //
    // API route create resource
    /*
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

    */
}
