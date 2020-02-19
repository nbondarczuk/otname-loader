CC = g++

OPTIONS = -std=c++0x -g -fpermissive -D__USE_TRACE__

TARGET = ash

INCLUDE = -I./include/rapidxml \
	-I./include \
	-I./include/xml_item \
	-I./include/xml_document \
	-I./include/utl \
	-I./include/article_string

ORAINC = -I$(ORACLE_CLIENT)/sdk/include

ORALDD = -L$(ORACLE_CLIENT) -lclntsh -locci -lclntsh

INCLUDE_HPP = include/bill_document.hpp \
	include/bill_document_factory.hpp \
	include/xml_document/xml_document_address_page.hpp \
	include/xml_document/xml_document_balance_page.hpp \
	include/xml_document/xml_document_call_details.hpp \
	include/xml_document/xml_document_complement.hpp \
	include/xml_document/xml_document_contracts.hpp \
	include/xml_document/xml_document_factory.hpp \
	include/xml_document/xml_document.hpp \
	include/xml_document/xml_document_invoice.hpp \
	include/xml_document/xml_document_invoice_info.hpp \
	include/xml_document/xml_document_legend.hpp \
	include/xml_document/xml_document_summary.hpp \
	include/xml_document/xml_envelope.hpp \
	include/xml_item/xml_account.hpp \
	include/xml_item/xml_addr.hpp \
	include/xml_item/xml_adv_txt.hpp \
	include/xml_item/xml_agg_set.hpp \
	include/xml_item/xml_att.hpp \
	include/xml_item/xml_bank.hpp \
	include/xml_item/xml_bill_acc.hpp \
	include/xml_item/xml_call.hpp \
	include/xml_item/xml_cash_discount.hpp \
	include/xml_item/xml_cccontact.hpp \
	include/xml_item/xml_charge.hpp \
	include/xml_item/xml_contract.hpp \
	include/xml_item/xml_customer.hpp \
	include/xml_item/xml_cust_ref.hpp \
	include/xml_item/xml_date.hpp \
	include/xml_item/xml_dn.hpp \
	include/xml_item/xml_fi_cont.hpp \
	include/xml_item/xml_fup.hpp \
	include/xml_item/xml_invoice_item.hpp \
	include/xml_item/xml_invoice_totals.hpp \
	include/xml_item/xml_inv_party.hpp \
	include/xml_item/xml_item.hpp \
	include/xml_item/xml_part.hpp \
	include/xml_item/xml_per_ct_info.hpp \
	include/xml_item/xml_price.hpp \
	include/xml_item/xml_src_status.hpp \
	include/xml_item/xml_srv_params.hpp \
	include/xml_item/xml_srv_status.hpp \
	include/xml_item/xml_sum_item.hpp \
	include/xml_item/xml_sums.hpp \
	include/xml_item/xml_tax.hpp \
	include/xml_item/xml_type_desc.hpp \
	include/xml_item/xml_xcd.hpp \
	include/utl/amtutl.hpp \
	include/utl/dateutl.hpp \
	include/utl/lexical_cast.hpp \
	include/utl/lock_guard.hpp \
	include/utl/strutl.hpp \
	include/utl/trace.hpp \
	include/utl/xmlutl.hpp \
	include/utl/dbutl.hpp \
	include/article_string/article_string_factory.hpp \
	include/article_string/article_string_item.hpp \
	include/article_string/bill_document_visitor.hpp

$(TARGET): $(INCLUDE_HPP) $(TARGET).cpp trace.cpp
	$(CC) $(INCLUDE) $(OPTIONS) -o $(TARGET) $(TARGET).cpp trace.cpp $(ORAINC) $(ORALDD)

all: $(TARGET)

clang-format:
	clang-format -style="{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 240}" -i \
	*.cpp ./include/*.hpp ./include/*/*.hpp

run:
	ash -v examples/xml/SUM2877963.43824.xml.xml

test: $(TARGET)
	ash -v examples/xml/SUM2877963.43824.xml.xml > examples/xml/SUM2877963.43824.1
	diff examples/xml/SUM2877963.43824.0 examples/xml/SUM2877963.43824.1

test-db:
	ash -s -v examples/xml/SUM2877963.43824.xml.xml

install:
	(cd sql; bash install.sh)

clean:
	rm -f $(TARGET) *~ ./include/*~ ./include/*/*~ core.*

tar:
	tar -cvf $(HOME)/ash.tar .
	gzip $(HOME)/ash.tar

.PHONY=sql
