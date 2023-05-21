# Sample Makefile for wx applications
WX_CONFIG := wx-config
WX_CXXFLAGS := $(shell $(WX_CONFIG) --cxxflags)
WX_LIBS := $(shell $(WX_CONFIG) --libs)

APPLICATION := convert
OBJECTS := App.o mainFrame.o # enter the .o files or generate this list

all: $(APPLICATION)

$(APPLICATION): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS) $(WX_LIBS) $(LIBS)

$(OBJECTS): %.o: %.cpp
	$(CXX) -c -o $@ $(WX_CXXFLAGS) $(CXXFLAGS) $<

.PHONY: clean
clean:
	find . -name '*~' -o -name '*.o' -o -name $(APPLICATION) | xargs rm

