
JAR := jvamp.jar
LIBRARY := libvamp-jni.so

HOST	:= host/host.class
TEST	:= test/test.class

all: $(JAR) $(LIBRARY) $(HOST)
test:	$(TEST)
	java -classpath $(JAR):test test

OBJFILES := src/PluginLoader.o src/Plugin.o src/RealTime.o src/getset.o

JAVAFILES := org/vamp_plugins/Feature.java org/vamp_plugins/OutputDescriptor.java org/vamp_plugins/ParameterDescriptor.java org/vamp_plugins/Plugin.java org/vamp_plugins/PluginLoader.java org/vamp_plugins/RealTime.java

CLASSFILES := $(patsubst %.java,%.class,$(JAVAFILES))

INCLUDES := -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
CXXFLAGS := $(INCLUDES) -g -fPIC

$(JAR):	$(JAVAFILES)
	javac $^
	jar cf $@ org/vamp_plugins

$(LIBRARY): $(OBJFILES)
	$(CXX) -shared -o $@ $^ -lvamp-hostsdk

$(HOST):	host/host.java $(JAR)
	javac -classpath $(JAR) $<

$(TEST):	test/test.java $(JAR)
	javac -classpath $(JAR) $<

clean:
	rm -f $(OBJFILES) $(CLASSFILES) $(HOST) $(TEST)

distclean:	clean
	rm $(JAR) $(LIBRARY)
