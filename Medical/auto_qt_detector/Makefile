SOURCES=./src/ecg.cpp            ./src/stdafx.cpp            \
	./src/lib/cwt.cpp        ./src/lib/ecgannotation.cpp \
	./src/lib/ecgdenoise.cpp ./src/lib/fwt.cpp           \
	./src/lib/ishne.cpp      ./src/lib/signal.cpp

HEADERS=./src/lib/lib.h          ./src/stdafx.h              \
	./src/lib/cwt.h          ./src/lib/ecgannotation.h   \
	./src/lib/ecgdenoise.h   ./src/lib/fwt.h             \
	./src/lib/ishne.h        ./src/lib/signal.h

ifeq ($(OS),Windows_NT)
	BIN_NAME = ecg_ann.exe
	SOURCES += ./src/mman/mman.cpp
	HEADERS += ./src/mman/mman.h
else
	BIN_NAME = ecg_ann
endif

$(BIN_NAME)	:	$(SOURCES) $(HEADERS) Makefile
			g++ -Wall $(SOURCES) -o $@
