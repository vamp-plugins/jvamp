
package org.vamp_plugins;

/**
 * ParameterDescriptor describes the properties of a configurable
 * parameter of a Plugin.
 */
public class ParameterDescriptor {

    /**
     * The name of the parameter, in computer-usable form.  Will
     * contain only the characters [a-zA-Z0-9_-].
     */
    public String identifier;

    /**
     * The human-readable name of the parameter.
     */
    public String name;

    /**
     * A human-readable short text describing the parameter.  May be
     * empty if the name has said it all already.
     */
    public String description;

    /**
     * The unit of the parameter, in human-readable form.
     */
    public String unit;

    /**
     * The minimum value of the parameter.
     */
    public float minValue;

    /**
     * The maximum value of the parameter.
     */
    public float maxValue;

    /**
     * The default value of the parameter.  The plugin should
     * ensure that parameters have this value on initialisation
     * (i.e. the host is not required to explicitly set parameters
     * if it wants to use their default values).
     */
    public float defaultValue;
	
    /**
     * True if the parameter values are quantized to a particular
     * resolution.
     */
    public boolean isQuantized;

    /**
     * Quantization resolution of the parameter values (e.g. 1.0
     * if they are all integers).  Undefined if isQuantized is
     * false.
     */
    public float quantizeStep;

    /**
     * Names for the quantized values.  If isQuantized is true,
     * this may either be empty or contain one string for each of
     * the quantize steps from minValue up to maxValue inclusive.
     * Undefined if isQuantized is false.
     *
     * If these names are provided, they should be shown to the
     * user in preference to the values themselves.  The user may
     * never see the actual numeric values unless they are also
     * encoded in the names.
     */
    public String[] valueNames;
	
    ParameterDescriptor() {
	minValue = 0;
	maxValue = 0;
	defaultValue = 0;
	isQuantized = false;
    }
}

