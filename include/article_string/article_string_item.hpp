#ifndef __ARTICLE_STRING_ITEM_HPP__
#define __ARTICLE_STRING_ITEM_HPP__

#include "strutl.hpp"

class ArticleStringItem {
   public:
    ArticleStringItem(const char* document_id, const char* id, const char* as, const char* ch) : invoice_id(document_id), contract_id(id), item_name(as), charge(ch) {}

    void dump() const { std::cout << invoice_id << "," << contract_id << "," << item_name << "," << charge << std::endl; }

    void save() const {}

   private:
    const std::string invoice_id;
    const std::string contract_id;
    const std::string item_name;
    const std::string charge;
};

#endif  // __ARTICLE_STRING_ITEM_HPP__
