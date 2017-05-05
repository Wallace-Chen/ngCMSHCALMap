IDIR       = .
ODIR       = obj

#CXX       = ~/.vim/bundle/ClangComplete/bin/cc_args.py g++
CXX        = g++

#CXXFLAGS  += -Iinc -std=c++0x -I${CMSSW_BASE}/src/
CXXFLAGS  += -I. -std=c++0x -I$(CMSSW_BASE)/src/ -I$(LHAPDF_DATA_PATH)/../../include

## Optimization flag
CXXFLAGS += -g #-O3
## Enable the maximun warning
##CXXFLAGS += -Wall -Wextra -Weffc++ -g

## Include ROOT
CXXFLAGS  += $(shell root-config --cflags)

CXXDEPFLAGS = -MMD -MP

LD       = g++
LDFLAGS  =

LIBS     = $(shell root-config --glibs)

PROGRAMS = HCALLMapAnalyzer HCALLMapProducer

all: mkobj $(PROGRAMS)

mkobj:
	@mkdir -p obj

#code to compile shared library to link samples to python

$(ODIR)/%.o : $(IDIR)/%.C
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

$(ODIR)/%.o : $(IDIR)/%.cc
	$(CXX) $(CXXFLAGS) $(CXXDEPFLAGS) -o $@ -c $<

HCALLMapAnalyzer: $(ODIR)/HCALLMapAnalyzer.o $(ODIR)/HCALLMapDumper.o $(ODIR)/HCALLMapLoader.o $(ODIR)/HBHEAnalyzer.o $(ODIR)/HFAnalyzer.o $(ODIR)/HOAnalyzer.o $(ODIR)/ngHBAnalyzer.o $(ODIR)/ngHEAnalyzer.o $(ODIR)/ngHFAnalyzer.o
	$(LD) $^ $(LIBS)  -o $@

HCALLMapProducer: $(ODIR)/HCALLMapProducer.o $(ODIR)/HCALLMapDumper.o $(ODIR)/HCALLMapLoader.o
	$(LD) $^ $(LIBS)  -o $@

clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.d $(ODIR)/*.so $(PROGRAMS) core 
