#ifndef __XML_PER_CT_INO_HPP__
#define __XML_PER_CT_INO_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "article_string_item.hpp"
#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_charge.hpp"
#include "xml_item.hpp"
#include "xml_sum_item.hpp"
#include "xmlutl.hpp"

class XMLPerCTInfo : public XMLItem {
   public:
    XMLPerCTInfo() : root(0) {}

    XMLPerCTInfo(const rapidxml::xml_node<> *node) : root(node) { load(); }

    ~XMLPerCTInfo() { clear(); }

    void dump() const {
        assert(root);
        std::cout << "PerCTInfo: " << std::endl;
        dump_charges();
        dump_sum_items();
    }

    void load() {
        assert(root);
        load_charges();
        load_sum_items();
    }

    std::set<XMLCharge *> Charges;
    std::set<XMLSumItem *> SumItems;

    void collect(std::vector<ArticleStringItem> &asis, const char *documentId, const char *contractId) const {
        for (auto it = SumItems.begin(); it != SumItems.end(); ++it) {
            (*it)->collect(asis, documentId, contractId);
        }
    }

   private:
    const rapidxml::xml_node<> *root;

    // conditioal set of values
    void load_charges() { load_subnodes<XMLCharge>(root, "Charge", Charges); }

    void load_sum_items() { load_subnodes<XMLSumItem>(root, "SumItem", SumItems); }

    void dump_charges() const {
        const unsigned int n = Charges.size();
        if (n) {
            std::cout << "Charges: "
                      << "(" << n << ")" << std::endl;
            for (auto it = Charges.begin(); it != Charges.end(); ++it) {
                (*it)->dump();
            }
        }
    }

    void dump_sum_items() const {
        const unsigned int n = SumItems.size();
        if (n) {
            std::cout << "SumItems: "
                      << "(" << n << ")" << std::endl;
            for (auto it = SumItems.begin(); it != SumItems.end(); ++it) {
                (*it)->dump();
            }
        }
    }

    void clear() {
        for (auto it = Charges.begin(); it != Charges.end(); ++it) {
            delete *it;
        }
        Charges.clear();

        for (auto it = SumItems.begin(); it != SumItems.end(); ++it) {
            delete *it;
        }
        SumItems.clear();
    }
};

#endif  // __XML_PER_CT_INO_HPP__
