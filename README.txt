
jVamp -- a Java host interface for Vamp audio analysis plugins
==============================================================

Chris Cannam, 2012
http://code.soundsoftware.ac.uk/projects/jvamp

jVamp is a JNI (Java Native Interface) library that permits Java
applications to load and use Vamp audio analysis plugins.

Vamp plugins are native-code plugins typically written in C++. In
order to load them into a Java application, you need a native wrapper
library (that is, jVamp) and both the wrapper and the plugin need to
be compiled natively for the machine platform you are using.

