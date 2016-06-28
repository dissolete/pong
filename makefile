#--------------------------#
# CODE RED ENGINE MAKEFILE #
#--------------------------#

TARGET = Pong

SRC = CRE/src
INC = CRE/include
BIN = App/bin
APPSRC = App/src
APPINC = App/include

SFML = -lsfml-graphics -lsfml-window -lsfml-system

#---------------------------------------------#
# DON'T CHANGE ANYTHING BETWEEN THESE ARROWS! #
#---------------------------------------------#
#vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv#

CRSOURCE = $(wildcard $(SRC)/*.cpp)
APPSOURCE = $(wildcard $(APPSRC)/*.cpp)
CRINCLUDES = $(wildcard $(INC)/*.hpp)
APPINCLUDES = $(wildcard $(APPINC)/*.hpp)
OBJECTS = $(patsubst %,$(BIN)/%, $(notdir $(CRSOURCE:.cpp=.o)))
APPOBJECTS = $(patsubst %,$(BIN)/%, $(notdir $(APPSOURCE:.cpp=.o)))

CC = g++ -std=c++11
CFLAGS = -I$(INC) -I$(APPINC) -c

link: $(OBJECTS) $(APPOBJECTS)
	@echo "Linking..."
	$(CC) $(OBJECTS) $(APPOBJECTS) -o $(BIN)/$(TARGET) \
	$(SFML)
	@echo "Finished!\n"

#^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^#

#----------------------------#
# ADD NEW OBJECT FILES BELOW #
#----------------------------#

$(BIN)/main.o: $(APPSRC)/main.cpp $(APPINCLUDES) $(CRINCLUDES)
	$(CC) $(CFLAGS) $(APPSRC)/main.cpp -o $(BIN)/main.o

$(BIN)/PongApp.o: $(APPSRC)/PongApp.cpp $(APPINC)/PongApp.hpp
	$(CC) $(CFLAGS) $(APPSRC)/PongApp.cpp -o $(BIN)/PongApp.o

$(BIN)/CRApp.o: $(SRC)/CRApp.cpp $(INC)/CRApp.hpp
	$(CC) $(CFLAGS) $(SRC)/CRApp.cpp -o $(BIN)/CRApp.o

$(BIN)/CRStateManager.o: $(SRC)/CRStateManager.cpp $(INC)/CRStateManager.hpp
	$(CC) $(CFLAGS) $(SRC)/CRStateManager.cpp -o $(BIN)/CRStateManager.o

$(BIN)/CRState.o: $(SRC)/CRState.cpp $(INC)/CRState.hpp
	$(CC) $(CFLAGS) $(SRC)/CRState.cpp -o $(BIN)/CRState.o

$(BIN)/SplashState.o: $(SRC)/SplashState.cpp $(INC)/SplashState.hpp
	$(CC) $(CFLAGS) $(SRC)/SplashState.cpp -o $(BIN)/SplashState.o

$(BIN)/PlayState.o: $(APPSRC)/PlayState.cpp $(APPINC)/PlayState.hpp
	$(CC) $(CFLAGS) $(APPSRC)/PlayState.cpp -o $(BIN)/PlayState.o

$(BIN)/CRTextManager.o: $(SRC)/CRTextManager.cpp $(INC)/CRTextManager.hpp
	$(CC) $(CFLAGS) $(SRC)/CRTextManager.cpp -o $(BIN)/CRTextManager.o

$(BIN)/MenuState.o: $(APPSRC)/MenuState.cpp $(APPINC)/MenuState.hpp
	$(CC) $(CFLAGS) $(APPSRC)/MenuState.cpp -o $(BIN)/MenuState.o

$(BIN)/CRStatManager.o: $(SRC)/CRStatManager.cpp $(INC)/CRStatManager.hpp
	$(CC) $(CFLAGS) $(SRC)/CRStatManager.cpp -o $(BIN)/CRStatManager.o

.PHONY: run clean clean-o git-clean help

run: $(BIN)/$(TARGET)
	$(BIN)/$(TARGET)

clean:
	rm -f $(OBJECTS) $(APPOBJECTS) $(BIN)/$(TARGET)

clean-o:
	rm -f $(OBJECTS) $(APPOBJECTS)

git-clean:
	git rm -r $(OBJECTS) $(APPOBJECTS) $(BIN)/$(TARGET)

help:
	@echo ""
	@echo "crsrc: $(CRSOURCE)\n"
	@echo "crinc: $(CRINCLUDES)\n"
	@echo "crobj: $(OBJECTS)\n"
	@echo "appsrc: $(APPSOURCE)\n"
	@echo "appinc: $(APPINCLUDES)\n"
	@echo "appobj: $(APPOBJECTS)\n"

