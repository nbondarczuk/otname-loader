#ifndef __XML_INVOICE_TOTALS_HPP__
#define __XML_INVOICE_TOTALS_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_charge.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLInvoiceTotals : public XMLItem {
   public:
    XMLInvoiceTotals() : root(0) {}

    XMLInvoiceTotals(const rapidxml::xml_node<> *node) : root(node) { load(); }

    ~XMLInvoiceTotals() { clear(); }

    void dump() const {
        assert(root);
        std::cout << "InvoiceTotals: " << std::endl;
        dump_charges();
    }

    void load() {
        assert(root);
        load_charges();
    }

   private:
    const rapidxml::xml_node<> *root;
    std::set<XMLCharge *> Charges;

    // conditioal set of values
    void load_charges() { load_subnodes<XMLCharge>(root, "Charge", Charges); }

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
        for (auto it = Charges.begin(); it != Charges.end(); ++it) {
            delete *it;
        }
        Charges.clear();
    }
};

#endif  // __XML_INVOICE_TOTALS_HPP__
