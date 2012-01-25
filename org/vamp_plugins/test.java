
package org.vamp_plugins;

public class test
{
    public static void main(String[] args) {
	
	// This is a plugin we know we have installed
//	String key = "vamp-example-plugins:percussiononsets";
	String key = "qm-vamp-plugins:qm-onsets";

	PluginLoader loader = PluginLoader.getInstance();
	
	try {
	    Plugin p = loader.loadPlugin(key, 44100);
	    System.out.println("identifier: " + p.getIdentifier() + "; " +
			       "name: " + p.getName() + "; " + 
			       "description: " + p.getDescription() + "; " +
			       "version: " + p.getPluginVersion());
	    Plugin.InputDomain domain = p.getInputDomain();
	    if (domain == Plugin.InputDomain.TimeDomain) {
		System.out.println("This is a time-domain plugin");
	    } else {
		System.out.println("This is a frequency-domain plugin");
	    }
	    String[] progs = p.getPrograms();
	    System.out.println("Plugin has " + progs.length + " program(s)");
	    for (int i = 0; i < progs.length; ++i) {
		System.out.println(i + ": " + progs[i]);
	    }
	} catch (PluginLoader.LoadFailedException e) {
	    System.out.println("Plugin load failed");
	}
    }
}

