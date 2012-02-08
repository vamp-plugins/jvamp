
LIBRARY := libvamp-jni.so
OBJFILES := src/PluginLoader.o src/Plugin.o src/RealTime.o src/getset.o
INCLUDES := -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
CXXFLAGS := $(INCLUDES) -g -fPIC

$(LIBRARY): $(OBJFILES)
	$(CXX) -shared -o $@ $^ -lvamp-hostsdk

clean:
	rm -f $(OBJFILES)
