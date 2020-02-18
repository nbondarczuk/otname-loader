CC = g++
OPTIONS = -g -fpermissive -D__USE_TRACE__
TARGET = ash
INCLUDE = -I./include/rapidxml \
	-I./include \
	-I./include/xml_item \
	-I./include/xml_document \
	-I./include/utl \
	-I./include/article_string
ORAINC = -I$(ORACLE_HOME)/sdk/include
ORALDD = -L$(ORACLE_HOME)/lib -lclntsh -locci -lclntsh

$(TARGET):
	$(CC) $(INCLUDE) $(OPTIONS) -o $(TARGET) $(TARGET).cpp trace.cpp $(ORAINC) $(ORALDD)

all: $(TARGET)

clang-format:
	# LLVM, Google, Chromium, Mozilla, WebKit
	clang-format -style="{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 240}" -i \
	*.cpp ./include/*.hpp ./include/*/*.hpp

start-xe:
	docker run -d -v /var/oracle-xe-data:/u01/app/oracle -p 1521:1521 -e ORACLE_ALLOW_REMOTE=true -e ORACLE_PASSWORD=oracle -e RELAX_SECURITY=1 epiclabs/docker-oracle-xe-11g

sql: sql-xe

sql-xe:
	(cd sql; bash install-XE.sh)

clean:
	rm -f $(TARGET) *~ ./include/*~ ./include/*/*~ core.*

tar:
	tar -cvf $(HOME)/ash.tar .
	gzip $(HOME)/ash.tar
