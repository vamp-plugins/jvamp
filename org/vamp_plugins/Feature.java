
package org.vamp_plugins;

/**
 * Feature contains a single result returned from Plugin.process() or
 * Plugin.getRemainingFeatures().
 */
public class Feature {
    /**
     * True if an output feature has its own timestamp.  This is
     * mandatory if the output has VariableSampleRate, optional if
     * the output has FixedSampleRate, and unused if the output
     * has OneSamplePerStep.
     */
    public boolean hasTimestamp;

    /**
     * Timestamp of the output feature.  This is mandatory if the
     * output has VariableSampleRate or if the output has
     * FixedSampleRate and hasTimestamp is true, and unused
     * otherwise.
     */
    public RealTime timestamp;

    /**
     * True if an output feature has a specified duration.  This
     * is optional if the output has VariableSampleRate or
     * FixedSampleRate, and and unused if the output has
     * OneSamplePerStep.
     */
    public boolean hasDuration;

    /**
     * Duration of the output feature.  This is mandatory if the
     * output has VariableSampleRate or FixedSampleRate and
     * hasDuration is true, and unused otherwise.
     */
    public RealTime duration;
	
    /**
     * Results for a single sample of this feature.  If the output
     * hasFixedBinCount, there must be the same number of values
     * as the output's binCount count.
     */
    public float[] values;

    /**
     * Label for the sample of this feature.
     */
    public String label;

    Feature() {
	hasTimestamp = false; hasDuration = false;
    }
};

