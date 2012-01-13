
package org.vamp_plugins;

public class PluginLoader
{
    public class LoadFailedException extends Exception { };

    public static synchronized PluginLoader getInstance() {
	if (inst == null) {
	    inst = new PluginLoader();
	    inst.initialise();
	}
	return inst;
    }

    public Plugin loadPlugin(String key, float inputSampleRate)
	throws LoadFailedException {
	long handle = loadPluginNative(key, inputSampleRate);
	if (handle != 0) return new Plugin(handle);
	else throw new LoadFailedException();
    }

    private PluginLoader() { initialise(); }
    private native long loadPluginNative(String key, float inputSampleRate);
    private native void initialise();
    private static PluginLoader inst;
    private long nativeHandle;

    static {
	System.loadLibrary("vamp-jni");
    }
}

