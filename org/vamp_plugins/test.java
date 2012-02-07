
package org.vamp_plugins;

import java.util.ArrayList;
import java.util.TreeMap;
import java.lang.RuntimeException;

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

	    boolean b = p.initialise(1, 1024, 1024);
	    System.out.println("Plugin initialise returned " + b);
	    if (!b) {
		throw new RuntimeException("Plugin initialise failed");
	    }
	    
	    float[][] buffers = new float[1][1024];
	    for (int block = 0; block < 1024; ++block) {
		for (int i = 0; i < 1024; ++i) {
		    buffers[0][i] = 0.0f;
		}
		if (block == 512) {
		    buffers[0][0] = 1.0f;
		}
		RealTime timestamp = RealTime.frame2RealTime(block * 1024, 44100);
		TreeMap<Integer, ArrayList<Feature>>
		    features = p.process(buffers, timestamp);
		System.out.println("Plugin process returned features on " + features.size() + " different output(s)");
	    }

	    TreeMap<Integer, ArrayList<Feature>>
		features = p.getRemainingFeatures();
	    System.out.println("Plugin getRemainingFeatures returned features on " + features.size() + " different output(s)");

	} catch (PluginLoader.LoadFailedException e) {
	    System.out.println("Plugin load failed");
	}
    }
}

