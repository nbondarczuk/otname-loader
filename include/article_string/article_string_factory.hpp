#ifndef __ARTICLE_STRING_FACTORY_HPP__
#define __ATRICLE_STRING_FACTORY_HPP__

#include <map>
#include <vector>

#include "article_string_item.hpp"
#include "bill_document_visitor.hpp"
#include "xml_document_summary.hpp"

class ArticleStringFactory {
   public:
    static void dump(const std::vector<ArticleStringItem> &asis) {
        for (auto it = asis.begin(); it != asis.end(); ++it) {
            it->dump();
        }
    }

    static void save(const std::vector<ArticleStringItem> &asis) {
        for (auto it = asis.begin(); it != asis.end(); ++it) {
            it->save();
        }
    }

    static std::vector<ArticleStringItem> make(std::map<std::string, BillDocument *> &bd) {
		// for each sum-sheet document
        const XMLDocumentSummary *summary = dynamic_cast<XMLDocumentSummary *>(bd["Document.Summary"]);
        std::vector<ArticleStringItem> asis;
        BillDocumentVisitor visitor(summary->getId(), asis);
        summary->accept(&visitor);
        return asis;
    }
};

#endif  // __ARTICLE_STRING_FACTORY_HPP__
