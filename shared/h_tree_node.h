//
// Created by Lukas Rosenthaler on 26.11.20.
//

#ifndef SKUNKWORKS_H_TREE_NODE_H
#define SKUNKWORKS_H_TREE_NODE_H

#include <string>

class HTreeNode {
    std::string id;
    std::string label;
    std::string name;
    HTreeNode *parent;
    int left_index;
    int right_index;
};


#endif //SKUNKWORKS_H_TREE_NODE_H
