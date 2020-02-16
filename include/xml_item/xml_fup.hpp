#ifndef __XML_FUP_HPP__
#define __XML_FUP_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLFup : public XMLItem {
   public:
    XMLFup() : root(0) {}

    XMLFup(const rapidxml::xml_node<> *node) : root(node) { load(); }

    void dump() const {
        assert(root);
        dump_dict();
    }

    void load() {
        assert(root);
        load_dict();
    }

   private:
    const rapidxml::xml_node<> *root;
    std::map<const char *, const char *> Dict;

    void load_dict() {
        for (rapidxml::xml_attribute<> *a = root->first_attribute(); a; a = a->next_attribute()) {
            Dict.insert(std::pair<const char *, const char *>(a->name(), a->value()));
        }
    }

    void dump_dict() const {
        const unsigned int n = Dict.size();
        if (n) {
            std::cout << "Fup: ";
            for (auto it = Dict.begin(); it != Dict.end(); ++it) {
                std::cout << " " << it->first << ": " << it->second;
            }
            std::cout << std::endl;
        }
    }
};

#endif  // __XML_FUP_HPP__
