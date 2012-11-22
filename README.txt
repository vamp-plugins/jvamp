
jVamp -- a Java host interface for Vamp audio analysis plugins
==============================================================

Chris Cannam, 2012
http://code.soundsoftware.ac.uk/projects/jvamp

jVamp is a JNI (Java Native Interface) library that permits Java
applications to load and use Vamp audio analysis plugins.

See http://vamp-plugins.org/ for more information about Vamp plugins
and for plugin downloads.

Note that jVamp is intended to be compatible with the Android NDK as
well as desktop Java, though it hasn't been tested there (and existing
binary distributions of plugins do not usually include ARM builds).

Vamp plugins are native-code plugins typically written in C++. In
order to load them into a Java application, you need a native wrapper
library (that is, jVamp) and both the wrapper and the plugin need to
be compiled natively for the machine platform you are using.


In this directory
-----------------

org/vamp_plugins -> Java interface for jVamp 
src/ -> C++ source code for jVamp JNI wrapper
host/ -> Simple Vamp host implemented as Java application
test/ -> Self-contained basic exercise test


Example
-------

On Linux:

1. Run "make", to build the Java code (as jvamp.jar) and JNI wrapper
   (as libvamp-jni.so).

2. Build the host:

   $ javac -classpath jvamp.jar host/host.java

3. Pick a Vamp plugin (which must be installed in the Vamp plugin
   path) and a 16-bit PCM WAV file, and run the host.  For example:

   $ java -classpath jvamp.jar:host host vamp-example-plugins:fixedtempo:tempo testfile.wav

   You should see some output -- in the case of the above plugin,
   it will be one line of the form

   0.002902494, 9.999092970: 142.07474 142.1 bpm


Note that you need the native-code libvamp-jni.so in your Java load
path in order to run a host using jVamp, and it must have been built
for the proper platform. Bear this in mind when planning to distribute
software using jVamp!


License
-------

This code is freely redistributable under a "new-style BSD" licence.
See the file COPYING for more details.


Any questions? Contact me at cannam@all-day-breakfast.com.

