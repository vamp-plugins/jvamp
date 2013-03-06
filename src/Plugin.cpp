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

#include "org_vamp_plugins_Plugin.h"

#include <vamp-hostsdk/Plugin.h>

#include "handle.h"
#include "getset.h"

#include <iostream>

using Vamp::Plugin;
using Vamp::PluginBase;
using std::string;

JNIEXPORT void JNICALL
Java_org_vamp_1plugins_Plugin_dispose(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    setHandle<Plugin>(env, obj, 0);
    delete p;
}

JNIEXPORT jint JNICALL
Java_org_vamp_1plugins_Plugin_getVampApiVersion(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return p->getVampApiVersion();
}    

JNIEXPORT jstring JNICALL
Java_org_vamp_1plugins_Plugin_getIdentifier(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return env->NewStringUTF(p->getIdentifier().c_str());
}

JNIEXPORT jstring JNICALL
Java_org_vamp_1plugins_Plugin_getName(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return env->NewStringUTF(p->getName().c_str());
}

JNIEXPORT jstring JNICALL
Java_org_vamp_1plugins_Plugin_getDescription(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return env->NewStringUTF(p->getDescription().c_str());
}

JNIEXPORT jstring JNICALL
Java_org_vamp_1plugins_Plugin_getMaker(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return env->NewStringUTF(p->getMaker().c_str());
}

JNIEXPORT jstring JNICALL
Java_org_vamp_1plugins_Plugin_getCopyright(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return env->NewStringUTF(p->getCopyright().c_str());
}

JNIEXPORT jint JNICALL
Java_org_vamp_1plugins_Plugin_getPluginVersion(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return p->getPluginVersion();
}

JNIEXPORT jobjectArray JNICALL
Java_org_vamp_1plugins_Plugin_getParameterDescriptors(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    PluginBase::ParameterList params = p->getParameterDescriptors();
    jclass descClass = env->FindClass("org/vamp_plugins/ParameterDescriptor");
    jobjectArray result = env->NewObjectArray(params.size(), descClass, 0);
    for (int i = 0; i < (int)params.size(); ++i) {

	jmethodID ctor = env->GetMethodID(descClass, "<init>", "()V");
	jobject desc = env->NewObject(descClass, ctor);

	setStringField(env, desc, "identifier", params[i].identifier);
	setStringField(env, desc, "name", params[i].name);
	setStringField(env, desc, "description", params[i].description);
	setStringField(env, desc, "unit", params[i].unit);
	setFloatField(env, desc, "minValue", params[i].minValue);
	setFloatField(env, desc, "maxValue", params[i].maxValue);
	setFloatField(env, desc, "defaultValue", params[i].defaultValue);
	setBooleanField(env, desc, "isQuantized", params[i].isQuantized);
	setFloatField(env, desc, "quantizeStep", params[i].quantizeStep);
	setStringArrayField(env, desc, "valueNames", params[i].valueNames);

	env->SetObjectArrayElement(result, i, desc);
    }

    return result;
}

JNIEXPORT jfloat JNICALL
Java_org_vamp_1plugins_Plugin_getParameter(JNIEnv *env, jobject obj,
					   jstring param)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    const char *s = env->GetStringUTFChars(param, 0);
    jfloat f = p->getParameter(s);
    env->ReleaseStringUTFChars(param, s);
    return f;
}

JNIEXPORT void JNICALL
Java_org_vamp_1plugins_Plugin_setParameter(JNIEnv *env, jobject obj,
					   jstring param, jfloat f)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    const char *s = env->GetStringUTFChars(param, 0);
    p->setParameter(s, f);
    env->ReleaseStringUTFChars(param, s);
}

JNIEXPORT jobjectArray JNICALL
Java_org_vamp_1plugins_Plugin_getPrograms(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    PluginBase::ProgramList programs = p->getPrograms();
    jobjectArray result = env->NewObjectArray
	(programs.size(), env->FindClass("java/lang/String"), 0);
    for (int i = 0; i < (int)programs.size(); ++i) {
	env->SetObjectArrayElement(result, i,
				   env->NewStringUTF(programs[i].c_str()));
    }
    return result;
}

JNIEXPORT jstring JNICALL
Java_org_vamp_1plugins_Plugin_getCurrentProgram(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return env->NewStringUTF(p->getCurrentProgram().c_str());
}

JNIEXPORT void  JNICALL
Java_org_vamp_1plugins_Plugin_selectProgram(JNIEnv *env, jobject obj,
					    jstring program)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    const char *s = env->GetStringUTFChars(program, 0);
    p->selectProgram(s);
    env->ReleaseStringUTFChars(program, s);
}

JNIEXPORT jboolean JNICALL
Java_org_vamp_1plugins_Plugin_initialise(JNIEnv *env, jobject obj,
					 jint inputChannels, jint stepSize,
					 jint blockSize)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return p->initialise(inputChannels, stepSize, blockSize);
}

JNIEXPORT void JNICALL
Java_org_vamp_1plugins_Plugin_reset(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    p->reset();
}

JNIEXPORT jobject JNICALL
Java_org_vamp_1plugins_Plugin_getInputDomain(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    Plugin::InputDomain d = p->getInputDomain();

    jclass ourEnumClass = env->FindClass("org/vamp_plugins/Plugin$InputDomain");

    std::string dname = "TIME_DOMAIN";
    if (d == Plugin::FrequencyDomain) dname = "FREQUENCY_DOMAIN";

    jstring sn = env->NewStringUTF(dname.c_str());
    jobject e = env->CallStaticObjectMethod
	(ourEnumClass, getEnumValueOfMethod(env), ourEnumClass, sn);

    env->DeleteLocalRef(sn);
    return e;
}

JNIEXPORT jint JNICALL
Java_org_vamp_1plugins_Plugin_getPreferredBlockSize(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return p->getPreferredBlockSize();
}

JNIEXPORT jint JNICALL
Java_org_vamp_1plugins_Plugin_getPreferredStepSize(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return p->getPreferredStepSize();
}

JNIEXPORT jint JNICALL
Java_org_vamp_1plugins_Plugin_getMinChannelCount(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return p->getMinChannelCount();
}

JNIEXPORT jint JNICALL
Java_org_vamp_1plugins_Plugin_getMaxChannelCount(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return p->getMaxChannelCount();
}

JNIEXPORT jobjectArray JNICALL
Java_org_vamp_1plugins_Plugin_getOutputDescriptors(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    Plugin::OutputList outputs = p->getOutputDescriptors();
    jclass descClass = env->FindClass("org/vamp_plugins/OutputDescriptor");
    jobjectArray result = env->NewObjectArray(outputs.size(), descClass, 0);
    for (int i = 0; i < (int)outputs.size(); ++i) {

	jmethodID ctor = env->GetMethodID(descClass, "<init>", "()V");
	jobject desc = env->NewObject(descClass, ctor);

	setStringField(env, desc, "identifier", outputs[i].identifier);
	setStringField(env, desc, "name", outputs[i].name);
	setStringField(env, desc, "description", outputs[i].description);
	setStringField(env, desc, "unit", outputs[i].unit);
	setBooleanField(env, desc, "hasFixedBinCount", outputs[i].hasFixedBinCount);
	setIntField(env, desc, "binCount", outputs[i].binCount);
	setStringArrayField(env, desc, "binNames", outputs[i].binNames);
	setBooleanField(env, desc, "hasKnownExtents", outputs[i].hasKnownExtents);
	setFloatField(env, desc, "minValue", outputs[i].minValue);
	setFloatField(env, desc, "maxValue", outputs[i].maxValue);
	setBooleanField(env, desc, "isQuantized", outputs[i].isQuantized);
	setFloatField(env, desc, "quantizeStep", outputs[i].quantizeStep);
	setFloatField(env, desc, "sampleRate", outputs[i].sampleRate);
	setBooleanField(env, desc, "hasDuration", outputs[i].hasDuration);

	jclass sampleTypeClass = env->FindClass
	    ("org/vamp_plugins/OutputDescriptor$SampleType");

	const char *stype;
	switch (outputs[i].sampleType) {
	case Plugin::OutputDescriptor::OneSamplePerStep:
	    stype = "OneSamplePerStep";
	    break;
	case Plugin::OutputDescriptor::FixedSampleRate:
	    stype = "FixedSampleRate";
	    break;
	case Plugin::OutputDescriptor::VariableSampleRate:
	    stype = "VariableSampleRate";
	    break;
	}

	jstring sn = env->NewStringUTF(stype);
	jobject sampleType = env->CallStaticObjectMethod
    	    (sampleTypeClass, getEnumValueOfMethod(env), sampleTypeClass, sn);
	env->DeleteLocalRef(sn);

	setObjectField(env, desc, "sampleType",
		       "Lorg/vamp_plugins/OutputDescriptor$SampleType;",
		       sampleType);

	env->SetObjectArrayElement(result, i, desc);
    }

    return result;
}

static jobject
convertFeature(JNIEnv *env, const Plugin::Feature &feature)
{
    jclass featClass = env->FindClass("org/vamp_plugins/Feature");
    jmethodID ctor = env->GetMethodID(featClass, "<init>", "()V");
    jobject jfeature = env->NewObject(featClass, ctor);

    setBooleanField(env, jfeature, "hasTimestamp", feature.hasTimestamp);
    setRealTimeField(env, jfeature, "timestamp", feature.timestamp);
    setBooleanField(env, jfeature, "hasDuration", feature.hasDuration);
    setRealTimeField(env, jfeature, "duration", feature.duration);
    setFloatArrayField(env, jfeature, "values", feature.values);
    setStringField(env, jfeature, "label", feature.label);

    return jfeature;
}

static jobject
convertFeatures(JNIEnv *env, const Plugin::FeatureSet &features)
{
    jobject result;
    
    // FeatureSet is map<int, vector<Feature> > where Feature is a struct.
    // We need to return a TreeMap<Integer, ArrayList<Feature>>

    jclass treeMapClass = env->FindClass("java/util/TreeMap");
    jmethodID treeMapCtor = env->GetMethodID(treeMapClass, "<init>", "()V");
    jmethodID inserter = env->GetMethodID
	(treeMapClass, "put",
	 "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    jclass listClass = env->FindClass("java/util/ArrayList");
    jmethodID listCtor = env->GetMethodID(listClass, "<init>", "()V");
    jmethodID adder = env->GetMethodID
	(listClass, "add", "(Ljava/lang/Object;)Z");

    jclass intClass = env->FindClass("java/lang/Integer");
    jmethodID intCtor = env->GetMethodID(intClass, "<init>", "(I)V");

    result = env->NewObject(treeMapClass, treeMapCtor);

    for (Plugin::FeatureSet::const_iterator i = features.begin();
	 i != features.end(); ++i) {
	
	int output = i->first;
	const Plugin::FeatureList &fl = i->second;

	jobject listObject = env->NewObject(listClass, listCtor);

	for (Plugin::FeatureList::const_iterator j = fl.begin();
	     j != fl.end(); ++j) {
	    jobject feature = convertFeature(env, *j);
	    (void)env->CallBooleanMethod(listObject, adder, feature);
	}

	jobject integer = env->NewObject(intClass, intCtor, output);

	(void)env->CallObjectMethod(result, inserter, integer, listObject);
    }

    return result;
}

JNIEXPORT jobject JNICALL
Java_org_vamp_1plugins_Plugin_process(JNIEnv *env, jobject obj, jobjectArray data, jint offset, jobject timestamp)
{
    Plugin *p = getHandle<Plugin>(env, obj);

    const Vamp::RealTime *const rt = getHandle<Vamp::RealTime>(env, timestamp);
    
    int channels = env->GetArrayLength(data);
    float **arr = new float *[channels];
    float **input = new float *[channels];
    for (int c = 0; c < channels; ++c) {
        jfloatArray cdata = (jfloatArray)env->GetObjectArrayElement(data, c);
        arr[c] = env->GetFloatArrayElements(cdata, 0);
	input[c] = arr[c] + offset;
    }

    Plugin::FeatureSet features = p->process(input, *rt);

    for (int c = 0; c < channels; ++c) {
        jfloatArray cdata = (jfloatArray)env->GetObjectArrayElement(data, c);
        env->ReleaseFloatArrayElements(cdata, input[c], 0);
    }

    delete[] input;
    delete[] arr;

    return convertFeatures(env, features);
}

JNIEXPORT jobject JNICALL
Java_org_vamp_1plugins_Plugin_getRemainingFeatures(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);

    Plugin::FeatureSet features = p->getRemainingFeatures();

    return convertFeatures(env, features);
}

