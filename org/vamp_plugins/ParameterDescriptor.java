
package org.vamp_plugins;

public class ParameterDescriptor {
    public String identifier;
    public String name;
    public String description;
    public String unit;
    public float minValue;
    public float maxValue;
    public float defaultValue;
    public boolean isQuantized;
    public float quantizeStep;
    public String[] valueNames;
	
    ParameterDescriptor() {
	minValue = 0;
	maxValue = 0;
	defaultValue = 0;
	isQuantized = false;
    }
}

