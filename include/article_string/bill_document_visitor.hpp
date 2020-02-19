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
    BillDocumentVisitor(const char* id, std::vector<ArticleStringItem>& asis) : document_id(id), customer_id(0), contract_id(0), collector(asis) { assert(document_id); }

    virtual void visit(const XMLDocumentSummary* e) {}

    virtual void visit(const XMLCustRef* e, const char* id) { customer_id = id; }

    virtual void visit(const XMLContract* e, const char* id) { contract_id = id; }

    virtual void visit(const XMLPerCTInfo* e) {}

    virtual void visit(const XMLSumItem* e, const char* as, const char* ch) {
        assert(document_id);
        assert(customer_id);
        assert(contract_id);
        assert(as);
        assert(ch);
        ArticleStringItem item(document_id, customer_id, contract_id, as, ch);
        collector.push_back(item);
    }

    virtual void dump() {
        for (auto it = collector.begin(); it != collector.end(); ++it) {
            it->dump();
        }
    }

   private:
    const char* document_id;
    const char* customer_id;
    const char* contract_id;
    std::vector<ArticleStringItem>& collector;
};

#endif  // __BILL_DOCUMENT_VISITOR_HPP__
