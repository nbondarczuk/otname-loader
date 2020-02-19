#ifndef __XML_CUST_REF_HPP__
#define __XML_CUST_REF_HPP__

#include <assert.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bill_document_visitor.hpp"
#include "rapidxml.hpp"
#include "strutl.hpp"
#include "xml_addr.hpp"
#include "xml_charge.hpp"
#include "xml_contract.hpp"
#include "xml_item.hpp"
#include "xmlutl.hpp"

class XMLCustRef : public XMLItem {
   public:
    XMLCustRef() : root(0) {}

    XMLCustRef(const rapidxml::xml_node<> *node) : root(node) { load(); }

    void dump() const {
        assert(root);
        std::cout << "CustRef:"
                  << " Id: " << Id << " CustCode: " << CustCode << " Reseller: " << Reseller << " PartyType: " << PartyType << std::endl;
        dump_addr();
        dump_charges();
        dump_contracts();
    }

    void load() {
        assert(root);
        load_attributes();
        load_addr();
        load_charges();
        load_contracts();
    }

    void accept(BillDocumentVisitor *v) const {
        v->visit(this, Id);
        for (auto it = Contracts.begin(); it != Contracts.end(); ++it) {
            (*it)->accept(v);
        }
    }

   private:
    const rapidxml::xml_node<> *root;
    const char *Id;
    const char *CustCode;
    const char *Reseller;
    const char *PartyType;
    XMLAddr *Addr;
    std::set<XMLCharge *> Charges;
    std::set<XMLContract *> Contracts;

    // mandatory values
    void load_attributes() {
        Id = find_attribute_value("Id", root);
        CustCode = find_attribute_value("CustCode", root);
        Reseller = find_attribute_value("Reseller", root);
        PartyType = find_attribute_value("PartyType", root);
    }

    void load_addr() { Addr = find_subnode<XMLAddr>(root, "Addr"); }

    void load_charges() { load_subnodes<XMLCharge>(root, "Charge", Charges); }

    void load_contracts() { load_subnodes<XMLContract>(root, "Contract", Contracts); }

    void dump_addr() const {
        if (Addr) {
            Addr->dump();
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

    void dump_contracts() const {
        const unsigned int n = Contracts.size();
        if (n) {
            std::cout << "Contracts: "
                      << "(" << n << ")" << std::endl;
            for (auto it = Contracts.begin(); it != Contracts.end(); ++it) {
                (*it)->dump();
            }
        }
    }
};

#endif  // __XML_CUST_REF_HPP__
