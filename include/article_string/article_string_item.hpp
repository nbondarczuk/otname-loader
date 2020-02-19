#ifndef __ARTICLE_STRING_ITEM_HPP__
#define __ARTICLE_STRING_ITEM_HPP__

#include <occi.h>

#include "strutl.hpp"

using namespace oracle::occi;

class ArticleStringItem {
   public:
    ArticleStringItem(const char* docid, const char* cuid, const char* coid, const char* as, const char* ch) : invoice_id(docid), customer_id(cuid), contract_id(coid), item_name(as), charge(ch) {}

    void dump() const { std::cout << invoice_id << "," << contract_id << "," << item_name << "," << charge << std::endl; }

    void save(Connection* c, Statement* s) const {
        s->setString(1, invoice_id);
        s->setString(2, customer_id);
        s->setString(3, contract_id);
        s->setString(4, item_name);
        s->setString(5, charge);
        s->executeUpdate();
    }

   private:
    std::string invoice_id;
    std::string customer_id;
    std::string contract_id;
    std::string item_name;
    std::string charge;
};

#endif  // __ARTICLE_STRING_ITEM_HPP__
