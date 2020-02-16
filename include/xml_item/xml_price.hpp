#ifndef __XML_PRICE_HPP__
#define __XML_PRICE_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLPrice : public XMLItem {
   public:
    XMLPrice() : root(0) {}

    XMLPrice(const rapidxml::xml_node<> *node) : root(node) { load(); }

    void dump() const {
        assert(root);
        std::cout << "Price:"
                  << " Price: " << Price << " CurrCode: " << CurrCode << std::endl;
    }

    void load() {
        assert(root);
        load_attributes();
    }

   private:
    const rapidxml::xml_node<> *root;
    const char *Price;
    const char *CurrCode;

    // mandatory values
    void load_attributes() {
        Price = find_attribute_value("Price", root);
        CurrCode = find_attribute_value("CurrCode", root);
    }
};

#endif  // __XML_PRICE_HPP__
