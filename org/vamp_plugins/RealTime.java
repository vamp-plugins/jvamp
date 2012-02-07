
package org.vamp_plugins;

public class RealTime {
    public int sec;
    public int nsec;

    public RealTime(int s, int n) { sec = s; nsec = n; }

    static RealTime frame2RealTime(int frame, int sampleRate) {
	//!!! warning! doesn't support -ve frame [unlike Vamp SDK version]
	int sec = frame / sampleRate;
	frame -= sec * sampleRate;
	int nsec = (int)((((double)frame * 1000000.0) / sampleRate) * 1000.0);
	return new RealTime(sec, nsec);
    }
}


