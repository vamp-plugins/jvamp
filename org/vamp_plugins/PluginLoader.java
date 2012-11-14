
package org.vamp_plugins;

/**
 * PluginLoader loads a Vamp plugin by searching the standard Vamp
 * installation path, and returns a Plugin object wrapping the native
 * plugin.
 *
 * To load a plugin call PluginLoader.getInstance().loadPlugin(key,
 * rate), where rate is the processing sample rate and key is the
 * plugin key consisting of the plugin's library base name and its
 * identifier, colon-separated. For example,
 *
 * Plugin p = PluginLoader.getInstance().loadPlugin("vamp-example-plugins:percussiononsets", 44100);
 */
public class PluginLoader
{
    public class LoadFailedException extends Exception { };

    /**
     * PluginLoader is a singleton. Return the instance of it.
     */
    public static synchronized PluginLoader getInstance() {
	if (inst == null) {
	    inst = new PluginLoader();
	    inst.initialise();
	}
	return inst;
    }

    /**
     * Search for all available Vamp plugins, and return a list of
     * their plugin keys (suitable for passing to loadPlugin) in the
     * order in which they were found.
     */
    public native ArrayList<String> listPlugins();

    /**
     * Load a native Vamp plugin from the plugin path. If the plugin
     * cannot be loaded, throw LoadFailedException.
     * 
     * key is the plugin key consisting of the plugin's library base
     * name and its identifier, colon-separated; inputSampleRate is
     * the processing sample rate for input audio.
     *
     *!!! todo: adapter flags
     */
    public Plugin loadPlugin(String key, float inputSampleRate)
	throws LoadFailedException {
	long handle = loadPluginNative(key, inputSampleRate);
	if (handle != 0) return new Plugin(handle);
	else throw new LoadFailedException();
    }

    /**
     * Return the category hierarchy for a Vamp plugin, given its
     * identifying key. The hierarchy is a sequence of category names
     * giving the location of a plugin within a category forest,
     * containing the human-readable names of the plugin's category
     * tree root, followed by each of the nodes down to the leaf
     * containing the plugin.
     *
     * If the plugin has no category information, return an empty
     * list.
     */
    public native ArrayList<String> getPluginCategory(String key);

    private PluginLoader() { initialise(); }
    private native long loadPluginNative(String key, float inputSampleRate);
    private native void initialise();
    private static PluginLoader inst;
    private long nativeHandle;

    static {
	System.loadLibrary("vamp-jni");
    }
}

