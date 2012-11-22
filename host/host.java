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

import java.util.ArrayList;
import java.util.TreeMap;
import java.util.Map;
import java.util.List;
import java.lang.RuntimeException;

import org.vamp_plugins.PluginLoader;
import org.vamp_plugins.Plugin;
import org.vamp_plugins.ParameterDescriptor;
import org.vamp_plugins.OutputDescriptor;
import org.vamp_plugins.Feature;
import org.vamp_plugins.RealTime;

import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.UnsupportedAudioFileException;

import java.io.File;
import java.io.IOException;

public class host
{
    private static void printFeatures(RealTime frameTime, Integer output,
				      Map<Integer, ArrayList<Feature>> features)
    {
	if (!features.containsKey(output)) return;

	for (Feature f : features.get(output)) {
	    if (f.hasTimestamp) {
		System.out.print(f.timestamp);
	    } else {
		System.out.print(frameTime);
	    }
	    if (f.hasDuration) {
		System.out.print("," + f.duration);
	    }
	    System.out.print(":");
	    for (float v : f.values) {
		System.out.print(" " + v);
	    }
	    System.out.print(" " + f.label);
	    System.out.println("");
	}
    }

    private static void usage() {
	System.err.println("Usage: host pluginlibrary:plugin:output file.wav");
    }

    private static int readBlock(AudioFormat format, AudioInputStream stream,
				 float[][] buffers)
	throws java.io.IOException
    {
	// 16-bit LE signed PCM only
	int channels = format.getChannels();
	byte[] raw = new byte[buffers[0].length * channels * 2];
	int read = stream.read(raw);
	if (read < 0) return read;
	int frames = read / (channels * 2);
	for (int i = 0; i < frames; ++i) {
	    for (int c = 0; c < channels; ++c) {
		int ix = i * channels + c;
		int ival = (raw[ix*2] & 0xff) | (raw[ix*2 + 1] << 8);
		float fval = ival / 32768.0f;
		buffers[c][i] = fval;
	    }
	}
	return frames;
    }

    public static void main(String[] args)
    {
	if (args.length < 2) {
	    usage();
	    return;
	}

	PluginLoader loader = PluginLoader.getInstance();

	String key = args[0];
	String filename = args[1];

	String[] keyparts = key.split(":");
	if (keyparts.length < 3) {
	    usage();
	    return;
	}
	
	String pluginKey = keyparts[0] + ":" + keyparts[1];
	String outputKey = keyparts[2];

	try {
	    File f = new File(filename);
	    AudioInputStream stream = AudioSystem.getAudioInputStream(f);
	    AudioFormat format = stream.getFormat();

	    if (format.getSampleSizeInBits() != 16 ||
		format.getEncoding() != AudioFormat.Encoding.PCM_SIGNED ||
		format.isBigEndian()) {
		System.err.println("Sorry, only 16-bit signed little-endian PCM files supported");
		return;
	    }

	    float rate = format.getFrameRate();
	    int channels = format.getChannels();
	    int bytesPerFrame = format.getFrameSize();
	    int blockSize = 1024; // frames

	    Plugin p = loader.loadPlugin
		(pluginKey, rate, PluginLoader.AdapterFlags.ADAPT_ALL);

	    OutputDescriptor[] outputs = p.getOutputDescriptors();
	    int outputNumber = -1;
	    for (int i = 0; i < outputs.length; ++i) {
		if (outputs[i].identifier.equals(outputKey)) outputNumber = i;
	    }
	    if (outputNumber < 0) {
		System.err.println("Plugin lacks output id: " + outputKey);
		System.err.print("Outputs are:");
		for (int i = 0; i < outputs.length; ++i) {
		    System.err.print(" " + outputs[i].identifier);
		}
		System.err.println("");
		return;
	    }
	    
	    boolean b = p.initialise(channels, blockSize, blockSize);
	    if (!b) {
		System.err.println("Plugin initialise failed");
		return;
	    }
	    
	    float[][] buffers = new float[channels][blockSize];

	    boolean done = false;
	    boolean incomplete = false;
	    int block = 0;

	    while (!done) {

		for (int c = 0; c < channels; ++c) {
		    for (int i = 0; i < blockSize; ++i) {
			buffers[c][i] = 0.0f;
		    }
		}

		int read = readBlock(format, stream, buffers);

		if (read < 0) {
		    done = true;
		} else {

		    if (incomplete) {
			// An incomplete block is only OK if it's the
			// last one -- so if the previous block was
			// incomplete, we have trouble
			System.err.println("Audio file read incomplete! Short buffer detected at " + block * blockSize);
			return;
		    }
		    
		    incomplete = (read < buffers[0].length);

		    RealTime timestamp = RealTime.frame2RealTime
			(block * blockSize, (int)(rate + 0.5));

		    TreeMap<Integer, ArrayList<Feature>>
			features = p.process(buffers, timestamp);

		    printFeatures(timestamp, outputNumber, features);

		    timestamp.dispose();
		}
		
		++block;
	    }

	    TreeMap<Integer, ArrayList<Feature>>
		features = p.getRemainingFeatures();

	    RealTime timestamp = RealTime.frame2RealTime
		(block * blockSize, (int)(rate + 0.5));
	    printFeatures(timestamp, outputNumber, features);
	    timestamp.dispose();

	    p.dispose();

	} catch (java.io.IOException e) {
	    System.err.println("Failed to read audio file: " + e.getMessage());

	} catch (javax.sound.sampled.UnsupportedAudioFileException e) {
	    System.err.println("Unsupported audio file format: " + e.getMessage());

	} catch (PluginLoader.LoadFailedException e) {
	    System.err.println("Plugin load failed (unknown plugin?): key is " +
			       key);
	}
    }
}

