
package org.vamp_plugins;

public class Plugin
{
    private long nativeHandle;
    protected Plugin(long handle) { nativeHandle = handle; }

    public native String getIdentifier();
    public native String getName();
    public native String getDescription();
    public native int getPluginVersion();
}

