#ifndef __XML_DOCUMENT_COMPLEMENT_HPP__
#define __XML_DOCUMENT_COMPLEMENT_HPP__

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "rapidxml.hpp"
#include "xml_document.hpp"

class XMLDocumentComplement : public XMLDocument {
   public:
    XMLDocumentComplement() : root(0) {}

    XMLDocumentComplement(rapidxml::xml_node<> *node) : root(node) { load(); }

    ~XMLDocumentComplement() {}

    std::string id() const { return "Document.Complement"; }

    XMLDocumentComplement *clone() const {
        XMLDocumentComplement *p = new XMLDocumentComplement(*this);
        return p;
    }

    void reload(const rapidxml::xml_node<> *node = 0) {
        const rapidxml::xml_node<> *document_root = get_document_root();
        root = document_root->first_node("Complement");
        load();
    }

    void load() {
        // assert(root);
    }

    void dump() const {
        // assert(root);
    }

   private:
    rapidxml::xml_node<> *root;
};

#endif  // __XML_DOCUMENT_COMPLEMENT_HPP__
