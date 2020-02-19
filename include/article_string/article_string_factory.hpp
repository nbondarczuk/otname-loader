#ifndef __ARTICLE_STRING_FACTORY_HPP__
#define __ATRICLE_STRING_FACTORY_HPP__

#include <assert.h>
#include <occi.h>

#include <map>
#include <vector>

#include "article_string_item.hpp"
#include "bill_document_visitor.hpp"
#include "xml_document_summary.hpp"

using namespace oracle::occi;

static const char* sql = "INSERT INTO ORDERCOTRAILER (DOCUMENT_ID, CUSTOMER_ID, CO_ID, OTNAME, CHARGE) VALUES (:1, :2, :3, :4, :5)";

class ArticleStringFactory {
   public:
	ArticleStringFactory(Connection* c) : connection(c) {
	  if (connection) {
	    statement = connection->createStatement(sql);
	  }
	}
	
    void dump(const std::vector<ArticleStringItem> &asis) {
        for (auto it = asis.begin(); it != asis.end(); ++it) {
            it->dump();
        }
    }

    void save(const std::vector<ArticleStringItem> &asis) {
      if (connection) {
	return;
      }

      statement->setAutoCommit(false);
        for (auto it = asis.begin(); it != asis.end(); ++it) {
            it->save(connection, statement);
        }
		connection->commit();
    }

	// get otname noes from sum-sheed documents
    std::vector<ArticleStringItem> make(std::map<std::string, BillDocument *> &bd) {
        std::vector<ArticleStringItem> asis; //expected rvo
		// for each sum-sheet document
		std::map<std::string, BillDocument *>::iterator it = bd.begin();
		while (it != bd.end()) {
			XMLDocumentSummary *summary = dynamic_cast<XMLDocumentSummary *>(it->second);
			BillDocumentVisitor visitor(summary->getId(), asis);
			summary->accept(&visitor);
			it++;
		}
		
        return asis;
    }

private:
	Connection* connection;
	Statement* statement;
};

#endif  // __ARTICLE_STRING_FACTORY_HPP__
