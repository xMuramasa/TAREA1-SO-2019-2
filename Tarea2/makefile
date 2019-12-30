JCC=javac
JVM=java
JFLAGS=-d
SOURCE_DIR= src/tarea
END_DIR= src/bin
MAIN=tarea.Main


all: Main.class %.class

Main.class:
	$(JCC) $(JFLAGS) $(END_DIR) $(SOURCE_DIR)/Main.java

%.class:
	$(JCC) $(JFLAGS) $(END_DIR) $(SOURCE_DIR)/*.java

run:
	$(JVM) -cp $(END_DIR) $(MAIN)

clean:
	rm -rf src/bin/* *~ core $(INCDIR)/*~
	touch src/bin/noborrar