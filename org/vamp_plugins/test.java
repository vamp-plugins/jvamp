
package org.vamp_plugins;

public class test
{
    public static void main(String[] args) {
	
	// This is a plugin we know we have installed
//	String key = "vamp-example-plugins:percussiononsets";
	String key = "qm-vamp-plugins:qm-onsetdetector";

	PluginLoader loader = PluginLoader.getInstance();
	
	try {
	    Plugin p = loader.loadPlugin(key, 44100);
	    System.out.println("identifier: " + p.getIdentifier());
	    System.out.println("name: " + p.getName());
	    System.out.println("description: " + p.getDescription());
	    System.out.println("version: " + p.getPluginVersion());
	    Plugin.InputDomain domain = p.getInputDomain();
	    if (domain == Plugin.InputDomain.TimeDomain) {
		System.out.println("This is a time-domain plugin");
	    } else {
		System.out.println("This is a frequency-domain plugin");
	    }
	    ParameterDescriptor[] params = p.getParameterDescriptors();
	    System.out.println("Plugin has " + params.length + " parameters(s)");
	    for (int i = 0; i < params.length; ++i) {
		System.out.println(i + ": " + params[i].identifier + " (" + params[i].name + ")");
	    }
	    String[] progs = p.getPrograms();
	    System.out.println("Plugin has " + progs.length + " program(s)");
	    for (int i = 0; i < progs.length; ++i) {
		System.out.println(i + ": " + progs[i]);
	    }
	    OutputDescriptor[] outputs = p.getOutputDescriptors();
	    System.out.println("Plugin has " + outputs.length + " output(s)");
	    for (int i = 0; i < outputs.length; ++i) {
		System.out.println(i + ": " + outputs[i].identifier + " (sample type: " + outputs[i].sampleType + ")");
	    }
	} catch (PluginLoader.LoadFailedException e) {
	    System.out.println("Plugin load failed");
	}
    }
}

