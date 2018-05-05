CC = g++
CCFLAGS = -g -Wall -std=c++11

rd_view: libcs680.a rd_direct.o pnm_display.o data_structures.o globals.o shapes.o xforms.o pipelines.o clipping.o fill.o plot.o scan_conversion.o shaders.o lighting.o
	$(CC) -o rd_view $(CCFLAGS) libcs680.a rd_direct.o pnm_display.o data_structures.o globals.o shapes.o xforms.o pipelines.o clipping.o fill.o plot.o scan_conversion.o shaders.o lighting.o -lm -lX11

# Add whatever additional files you want with a rule here, and also
# in the final linking rule above.

rd_direct.o: rd_direct.cc rd_direct.h
	$(CC) $(CCFLAGS) -c rd_direct.cc

pnm_display.o: pnm_display.cc pnm_display.h
	$(CC) $(CCFLAGS) -c pnm_display.cc

data_structures.o: data_structures.cc data_structures.h
	$(CC) $(CCFLAGS) -c data_structures.cc

globals.o: globals.cc globals.h
	$(CC) $(CCFLAGS) -c globals.cc

shapes.o: shapes.cc shapes.h
	$(CC) $(CCFLAGS) -c shapes.cc

xforms.o: xforms.cc xforms.h
	$(CC) $(CCFLAGS) -c xforms.cc

pipelines.o: pipelines.cc pipelines.h
	$(CC) $(CCFLAGS) -c pipelines.cc

clipping.o: clipping.cc clipping.h
	$(CC) $(CCFLAGS) -c clipping.cc

fill.o: fill.cc fill.h
	$(CC) $(CCFLAGS) -c fill.cc

plot.o: plot.cc plot.h
	$(CC) $(CCFLAGS) -c plot.cc

scan_conversion.o: scan_conversion.cc scan_conversion.h
	$(CC) $(CCFLAGS) -c scan_conversion.cc

shaders.o: shaders.cc shaders.h
	$(CC) $(CCFLAGS) -c shaders.cc

lighting.o: lighting.cc lighting.h
	$(CC) $(CCFLAGS) -c lighting.cc

clean:
	-rm *.o rd_view
