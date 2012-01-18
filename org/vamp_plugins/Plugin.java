
package org.vamp_plugins;

import java.util.TreeMap;
import java.util.ArrayList;

public class Plugin
{
    private long nativeHandle;
    protected Plugin(long handle) { nativeHandle = handle; }

    public native String getIdentifier();
    public native String getName();
    public native String getDescription();
    public native int getPluginVersion();

    public native boolean initialise(int inputChannels,
				     int stepSize,
				     int blockSize);

    public native void reset();
    
    public static enum InputDomain { TimeDomain, FrequencyDomain };
    public native InputDomain getInputDomain();
    
    public native int getPreferredBlockSize();
    public native int getPreferredStepSize();
    public native int getMinChannelCount();
    public native int getMaxChannelCount();

    public native OutputDescriptor[] getOutputDescriptors();

    public class Feature {
	public boolean hasTimestamp;
	public RealTime timestamp;
	public boolean hasDuration;
	public RealTime duration;
	public float[] values;
	public String label;
	Feature() {
	    hasTimestamp = false; hasDuration = false;
	}
    };

// "Pseudo-typedef antipattern - don't do this": http://www.ibm.com/developerworks/java/library/j-jtp02216/index.html
// (I would like to!)
//    public class FeatureList extends ArrayList<Feature>;
//    public class FeatureSet extends TreeMap<Integer, FeatureList>;

    public native TreeMap<Integer, ArrayList<Feature>>
	process(float[][] inputBuffers,
		RealTime timestamp);

    public native TreeMap<Integer, ArrayList<Feature>>
	getRemainingFeatures();
}

