#ifndef __BILL_DOCUMENT_VISITOR_HPP__
#define __BILL_DOCUMENT_VISITOR_HPP__

#include <assert.h>

class XMLDocumentSummary;
class XMLCustRef;
class XMLContract;
class XMLPerCTInfo;
class XMLSumItem;

class BillDocumentVisitor {
   public:
    BillDocumentVisitor(const char* id, std::vector<ArticleStringItem>& asis) : documentId(id), contractId(0), collector(asis) { assert(documentId); }

    virtual void visit(const XMLDocumentSummary* e) const {}

    virtual void visit(const XMLCustRef* e) const {}

    virtual void visit(const XMLContract* e, const char* id) { contractId = id; }

    virtual void visit(const XMLPerCTInfo* e) const {}

    virtual void visit(const XMLSumItem* e, const char* as, const char* ch) const {
        assert(contractId);
        ArticleStringItem item(documentId, contractId, as, ch);
        collector.push_back(item);
    }

    virtual void dump() {
        for (auto it = collector.begin(); it != collector.end(); ++it) {
            it->dump();
        }
    }

   private:
    const char* documentId;
    const char* contractId;
    std::vector<ArticleStringItem>& collector;
};

#endif  // __BILL_DOCUMENT_VISITOR_HPP__
