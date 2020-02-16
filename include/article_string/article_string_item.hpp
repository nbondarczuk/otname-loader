#ifndef __ARTICLE_STRING_ITEM_HPP__
#define __ARTICLE_STRING_ITEM_HPP__

#include "strutl.hpp"

class ArticleStringItem {
   public:
    ArticleStringItem(const char* documentId, const char* id, const char* as, const char* ch) : invoiceId(documentId), contractId(id), itemName(as), charge(ch) {}

    void dump() const { std::cout << invoiceId << "," << contractId << "," << itemName << "," << charge << std::endl; }

	void save() const {}
	
   private:
    const std::string invoiceId;
    const std::string contractId;
    const std::string itemName;
    const std::string charge;
};

#endif  // __ARTICLE_STRING_ITEM_HPP__
