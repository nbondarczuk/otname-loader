#include <iostream>

#include "article_string_factory.hpp"
#include "article_string_item.hpp"
#include "lexical_cast.hpp"
#include "trace.hpp"
#include "xml_document_factory.hpp"

using namespace std;

bool verbose = false;
bool save = false;

void help() {
	cout << "Use: ash [-v] verbose mode, printout on stdout" << endl;
	cout << "         [-s] save contents in ORDERCOTRAILER" << endl;
	cout << "         [-t] trace" << endl;
	exit(0);
}

int main(int argn, char **argv) {
    FRAME;

	if (argn <= 1) {
		help();
	}

    TRACE("Start loading XML");
    XMLDocumentFactory xml_factory;
    std::map<std::string, BillDocument *> docs;
    for (int i = 1; i < argn; ++i) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
			case 'h': help();
			case 'v': verbose = true; break;
			case 's': save = true; break;
			case 't': __Frame__::on(); break;
			default: help();
			}
		} else {
			const char *fn = argv[i];
			TRACE(std::string("Loading file: ") + fn);
			BillDocument *xml = xml_factory.make(fn);
			docs.insert(std::pair<std::string, BillDocument *>(xml->id(), xml));
		}
    }

    TRACE("Start loading article strings: " + lexical_cast<string>(docs.size()));
    if (!docs.empty()) {
        ArticleStringFactory factory;
        const vector<ArticleStringItem> asis = factory.make(docs);
		if (save) {
			factory.save(asis);
			TRACE("Saved records: " + lexical_cast<string>(asis.size()));
		}
		if (verbose) {
			factory.dump(asis);
		}
    }

    return 0;
}
