#ifndef __XML_ENVELOP_HPP__
#define __XML_ENVELOPE_HPP__

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "xml_document.hpp"
#include "xml_part.hpp"

class XMLEnvelope : public XMLDocument {
   public:
    XMLEnvelope() : root(0) {}

    XMLEnvelope(rapidxml::xml_node<> *node) : root(node) { load(); }

    ~XMLEnvelope() {}

    virtual std::string id() const { return "Envelope"; }

    virtual XMLEnvelope *clone() const {
        XMLEnvelope *p = new XMLEnvelope(*this);
        return p;
    }

    virtual void reload() {
        root = get_document_root();
        load();
    }

    virtual void load() {
        assert(root);
        load_parts();
    }

    virtual void dump() const {
        assert(root);
        dump_parts();
    }

   private:
    rapidxml::xml_node<> *root;
    std::set<XMLPart *> Parts;

    void load_parts() { load_subnodes<XMLPart>(root, "Part", Parts); }

    void dump_parts() const {
        const unsigned int n = Parts.size();
        if (n) {
            std::cout << "Parts: "
                      << "(" << n << ")" << std::endl;
            for (auto it = Parts.begin(); it != Parts.end(); ++it) {
                (*it)->dump();
            }
        }
    }
};

#endif  // __XML_ENVELOPE_HPP__
