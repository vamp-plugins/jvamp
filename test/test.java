/*
    jVamp

    A Java host interface for Vamp audio analysis plugins

    Centre for Digital Music, Queen Mary, University of London.
    Copyright 2012 Chris Cannam and QMUL.
  
    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use, copy,
    modify, merge, publish, distribute, sublicense, and/or sell copies
    of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR
    ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
    CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

    Except as contained in this notice, the names of the Centre for
    Digital Music; Queen Mary, University of London; and Chris Cannam
    shall not be used in advertising or otherwise to promote the sale,
    use or other dealings in this Software without prior written
    authorization.
*/

import java.util.Map;
import java.util.List;
import java.lang.RuntimeException;

import org.vamp_plugins.PluginLoader;
import org.vamp_plugins.Plugin;
import org.vamp_plugins.ParameterDescriptor;
import org.vamp_plugins.OutputDescriptor;
import org.vamp_plugins.Feature;
import org.vamp_plugins.RealTime;

public class test
{
    private static void printFeatures(Map<Integer, List<Feature>> features) {
	for (Map.Entry<Integer, List<Feature>> mi : features.entrySet()) {
	    System.out.print(mi.getKey() + ": ");
	    for (Feature li : mi.getValue()) {
		System.out.print("[" + li.timestamp + "= ");
		for (float v : li.values) {
		    System.out.print(v + " ");
		}
		System.out.print("] (\"");
		System.out.print(li.label);
		System.out.print("\") ");
	    }
	    System.out.println("");
	}
    }

    public static void main(String[] args) {
	
	// This is a plugin we know we have installed
//	String key = "vamp-example-plugins:percussiononsets";
	String key = "qm-vamp-plugins:qm-onsetdetector";

	PluginLoader loader = PluginLoader.getInstance();
	
	String[] plugins = loader.listPlugins();
	System.out.println("We know " + plugins.length + " plugins");
	for (int i = 0; i < plugins.length; ++i) {
	    System.out.println(i + ": " + plugins[i]);
	}

	try {
	    Plugin p = loader.loadPlugin(key, 44100, PluginLoader.AdapterFlags.ADAPT_ALL);
	    String[] cat = loader.getPluginCategory(key);
	    System.out.print("category: ");
	    for (int i = 0; i < cat.length; ++i) {
		System.out.print(cat[i]);
		if (i+1 < cat.length) System.out.print(" > ");
	    }
	    System.out.println("");
	    System.out.println("identifier: " + p.getIdentifier());
	    System.out.println("name: " + p.getName());
	    System.out.println("description: " + p.getDescription());
	    System.out.println("version: " + p.getPluginVersion());
	    Plugin.InputDomain domain = p.getInputDomain();
	    if (domain == Plugin.InputDomain.TIME_DOMAIN) {
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
		    buffers[0][0] = 0.5f;
		    buffers[0][1] = -0.5f;
		}
		RealTime timestamp = RealTime.frame2RealTime(block * 1024, 44100);
		Map<Integer, List<Feature>> features = p.process(buffers, timestamp);

		printFeatures(features);
	    }

	    Map<Integer, List<Feature>>
		features = p.getRemainingFeatures();

	    System.out.println("Results from getRemainingFeatures:");

	    printFeatures(features);
	    p.dispose();

	} catch (PluginLoader.LoadFailedException e) {
	    System.out.println("Plugin load failed");
	}
    }
}

