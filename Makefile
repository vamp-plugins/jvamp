
LIBRARY := libvamp-jni.so
OBJFILES := src/org_vamp_plugins_PluginLoader.o src/org_vamp_plugins_Plugin.o
INCLUDES := -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
CXXFLAGS := $(INCLUDES)

all:	$(LIBRARY)

$(LIBRARY): $(OBJFILES)
	$(CXX) -shared -o $@ $^ -lvamp-hostsdk
