
package org.vamp_plugins;

public class RealTime
{
    public RealTime(int s, int n) { initialise(s, n); }

    public native void dispose();

    public native int sec();
    public native int nsec();

    public native int usec();
    public native int msec();

    /// Return a debug-type string to full precision
    public native String toString();

    /// Return a user-readable formatted string to the nearest millisecond
    public native String toText();

    public native static RealTime fromSeconds(double sec);
    public native static RealTime fromMilliseconds(int msec);
    
    public native static RealTime frame2RealTime(long frame, int sampleRate);
    public native static long realTime2Frame(RealTime r, int sampleRate);

    private native void initialise(int s, int n);
    private long nativeHandle;
}


