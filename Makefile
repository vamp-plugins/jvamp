
LIBRARY := libvamp-jni.so
OBJFILES := src/PluginLoader.o src/Plugin.o
INCLUDES := -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
CXXFLAGS := $(INCLUDES)

$(LIBRARY): $(OBJFILES)
	$(CXX) -shared -o $@ $^ -lvamp-hostsdk
