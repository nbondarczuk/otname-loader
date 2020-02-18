#ifndef __XML_SUM_ITEM_HPP__
#define __XML_SUM_ITEM_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "bill_document_visitor.hpp"
#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_agg_set.hpp"
#include "xml_charge.hpp"
#include "xml_item.hpp"
#include "xml_srv_status.hpp"
#include "xmlutl.hpp"

class XMLSumItem : public XMLItem {
   public:
    XMLSumItem() : root(0) {}

    XMLSumItem(const rapidxml::xml_node<> *node) : root(node) { load(); }

    ~XMLSumItem() { clear(); }

    void dump() const {
        assert(root);
        std::cout << "SumItem:"
                  << " PT: " << PT << " ArticleString: " << ArticleString << std::endl;
        dump_agg_set();
        dump_srv_statuses();
        dump_charges();
    }

    void load() {
        assert(root);
        load_attributes();
        load_agg_set();
        load_srv_statuses();
        load_charges();
    }

    void accept(BillDocumentVisitor *v) const {
        auto it = Charges.begin();
        const char *charge = (*it)->getAmount();
        v->visit(this, ArticleString, charge);
    }

   private:
    const rapidxml::xml_node<> *root;
    const char *PT;
    const char *ArticleString;
    XMLAggSet *AggSet;
    std::set<XMLSrvStatus *> SrvStatuses;
    std::set<XMLCharge *> Charges;

    // mandatory values
    void load_attributes() {
        PT = find_attribute_value("PT", root);
        ArticleString = find_attribute_value("ArticleString", root);
    }

    // optional value
    void load_agg_set() { AggSet = find_subnode<XMLAggSet>(root, "AggSet"); }

    // conditional set of values
    void load_srv_statuses() { load_subnodes<XMLSrvStatus>(root, "SrvStatus", SrvStatuses); }

    // mandatory set of values
    void load_charges() { load_subnodes<XMLCharge>(root, "Charge", Charges); }

    void dump_agg_set() const {
        if (AggSet) {
            AggSet->dump();
        }
    }

    void dump_srv_statuses() const {
        const unsigned int n = SrvStatuses.size();
        if (n) {
            std::cout << "SrvStatuses: "
                      << "(" << n << ")" << std::endl;
            for (auto it = SrvStatuses.begin(); it != SrvStatuses.end(); ++it) {
                (*it)->dump();
            }
        }
    }

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

    void clear() {
        clear_agg_set();
        clear_srv_statuses();
        clear_charges();
    }

    void clear_agg_set() {
        if (AggSet) {
            delete AggSet;
        }
    }

    void clear_srv_statuses() {
        for (auto it = SrvStatuses.begin(); it != SrvStatuses.end(); ++it) {
            delete *it;
        }
        SrvStatuses.clear();
    }

    void clear_charges() {
        for (auto it = Charges.begin(); it != Charges.end(); ++it) {
            delete *it;
        }
        Charges.clear();
    }
};

#endif  // __XML_SUM_ITEM_HPP__
