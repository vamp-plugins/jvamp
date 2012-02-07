
package org.vamp_plugins;

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

