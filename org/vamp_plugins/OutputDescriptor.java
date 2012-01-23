
package org.vamp_plugins;

public class OutputDescriptor {
    public String identifier;
    public String name;
    public String description;
    public String unit;
    public boolean hasFixedBinCount;
    public int binCount;
    public String[] binNames;
    public boolean hasKnownExtents;
    public float minValue;
    public float maxValue;
    public boolean isQuantized;
    public float quantizeStep;
    public static enum SampleType {
	OneSamplePerStep, FixedSampleRate, VariableSampleRate
    };
    public SampleType sampleType;
    public float sampleRate;
    public boolean hasDuration;

    OutputDescriptor() {
	hasFixedBinCount = false;
	hasKnownExtents = false;
	isQuantized = false;
	sampleType = SampleType.OneSamplePerStep;
	hasDuration = false;
    }
}
