COMPILER=g++

#local environment
DEST = ~/bin
LIBDIR = /home/syusaku/lib
TARDIR = ./bin
OBJDIR = ./obj
SRCDIR = ./src

CPPFLAGS = -Wall -O0 -g -std=c++0x
INCLUDE = -I./include

#GLOG
#GLOG      = $(LIBDIR)/glog
#LDFLAGS += -L$(GLOG)/lib -lglog
#INCLUDE += -I$(GLOG)/include

#boost
#BOOST     = $(LIBDIR)/boost
#LDFLAGS += -L$(BOOST)/lib -lboost_graph 
#INCLUDE += -I$(BOOST)/include

TARGET = $(TARDIR)/run

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
DEPENDS = $(OBJECTS:.o=d)

$(TARGET): $(OBJECTS) $(LIBS)
		@[ -d $(TARDIR) ] || mkdir -p $(TARDIR)
		$(COMPILER) -o $@ $^ $(LDFLAGS) 

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
		@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
		$(COMPILER) $(CPPFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
	rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

install:$(TARGET)
	install -s $(TARGET) $(DEST)

-include $(DEPENDS)