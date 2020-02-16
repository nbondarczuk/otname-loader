#include <iostream>

#include "article_string_factory.hpp"
#include "article_string_item.hpp"
#include "lexical_cast.hpp"
#include "trace.hpp"
#include "xml_document_factory.hpp"

using namespace std;

int main(int argn, char **argv) {
    FRAME;

    TRACE("Start loading XML");
    XMLDocumentFactory xml_factory;
    std::map<std::string, BillDocument *> docs;
    for (int i = 1; i < argn; ++i) {
        char *fn = argv[i];
        TRACE(std::string("Loading file: ") + fn);
        BillDocument *xml = xml_factory.make(fn);
        docs.insert(std::pair<std::string, BillDocument *>(xml->id(), xml));
    }

    TRACE("Start loading article strings: " + lexical_cast<string>(docs.size()));
    if (!docs.empty()) {
        ArticleStringFactory factory;
        const vector<ArticleStringItem> asis = factory.make(docs);
        factory.dump(asis);
        factory.save(asis);
    }

    return 0;
}
