CC = g++
OPTIONS = -g -fpermissive -D__USE_TRACE__
TARGET = ash
INCLUDE = -I./include/rapidxml \
	-I./include \
	-I./include/xml_item \
	-I./include/xml_document \
	-I./include/utl \
	-I./include/article_string

$(TARGET):
	$(CC) $(INCLUDE) $(OPTIONS) -o $(TARGET) $(TARGET).cpp trace.cpp

all: $(TARGET)

clang-format:
	# LLVM, Google, Chromium, Mozilla, WebKit
	clang-format -style="{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 240}" -i \
	*.cpp ./include/*.hpp ./include/*/*.hpp

clean:
	rm -f $(TARGET) *~ ./include/*~ ./include/*/*~ core.*

tar:
	tar -cvf $(HOME)/ash.tar .
	gzip $(HOME)/ash.tar
