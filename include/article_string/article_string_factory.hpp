#ifndef __ARTICLE_STRING_FACTORY_HPP__
#define __ATRICLE_STRING_FACTORY_HPP__

#include <map>
#include <vector>

#include "article_string_item.hpp"
#include "bill_document.hpp"
#include "xml_document_summary.hpp"

class ArticleStringFactory {
   public:
    ArticleStringFactory() {}

    ~ArticleStringFactory() {}

    void dump() const {}

    std::vector<ArticleStringItem> make(std::map<std::string, BillDocument *> &bd) {
        const XMLDocumentSummary *summary = dynamic_cast<XMLDocumentSummary *>(bd["Document.Summary"]);
        std::vector<ArticleStringItem> asis;
        summary->collect(asis, summary->Id);
        return asis;
    }
};

#endif  // __ARTICLE_STRING_FACTORY_HPP__
