#include "org_vamp_plugins_Plugin.h"

#include <vamp-hostsdk/Plugin.h>

#include "handle.h"
#include "getset.h"

#include <iostream>

using Vamp::Plugin;
using Vamp::PluginBase;
using std::string;

jint
Java_org_vamp_1plugins_Plugin_getVampApiVersion(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return p->getVampApiVersion();
}    

jstring
Java_org_vamp_1plugins_Plugin_getIdentifier(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return env->NewStringUTF(p->getIdentifier().c_str());
}

jstring
Java_org_vamp_1plugins_Plugin_getName(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return env->NewStringUTF(p->getName().c_str());
}

jstring
Java_org_vamp_1plugins_Plugin_getDescription(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return env->NewStringUTF(p->getDescription().c_str());
}

jstring
Java_org_vamp_1plugins_Plugin_getMaker(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return env->NewStringUTF(p->getMaker().c_str());
}

jstring
Java_org_vamp_1plugins_Plugin_getCopyright(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return env->NewStringUTF(p->getCopyright().c_str());
}

jint
Java_org_vamp_1plugins_Plugin_getPluginVersion(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return p->getPluginVersion();
}

jobjectArray
Java_org_vamp_1plugins_Plugin_getParameterDescriptors(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    PluginBase::ParameterList params = p->getParameterDescriptors();
    jclass descClass = env->FindClass("org/vamp_plugins/ParameterDescriptor");
    jobjectArray result = env->NewObjectArray(params.size(), descClass, 0);
    for (int i = 0; i < params.size(); ++i) {

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

jfloat
Java_org_vamp_1plugins_Plugin_getParameter(JNIEnv *env, jobject obj,
					   jstring param)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    const char *s = env->GetStringUTFChars(param, 0);
    jfloat f = p->getParameter(s);
    env->ReleaseStringUTFChars(param, s);
    return f;
}

void
Java_org_vamp_1plugins_Plugin_setParameter(JNIEnv *env, jobject obj,
					   jstring param, jfloat f)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    const char *s = env->GetStringUTFChars(param, 0);
    p->setParameter(s, f);
    env->ReleaseStringUTFChars(param, s);
}

jobjectArray
Java_org_vamp_1plugins_Plugin_getPrograms(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    PluginBase::ProgramList programs = p->getPrograms();
    jobjectArray result = env->NewObjectArray
	(programs.size(), env->FindClass("java/lang/String"), 0);
    for (int i = 0; i < programs.size(); ++i) {
	env->SetObjectArrayElement(result, i,
				   env->NewStringUTF(programs[i].c_str()));
    }
    return result;
}

jstring
Java_org_vamp_1plugins_Plugin_getCurrentProgram(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return env->NewStringUTF(p->getCurrentProgram().c_str());
}

void 
Java_org_vamp_1plugins_Plugin_selectProgram(JNIEnv *env, jobject obj,
					    jstring program)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    const char *s = env->GetStringUTFChars(program, 0);
    p->selectProgram(s);
    env->ReleaseStringUTFChars(program, s);
}

jboolean
Java_org_vamp_1plugins_Plugin_initialise(JNIEnv *env, jobject obj,
					 jint inputChannels, jint stepSize,
					 jint blockSize)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return p->initialise(inputChannels, stepSize, blockSize);
}

void
Java_org_vamp_1plugins_Plugin_reset(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    p->reset();
}

jobject
Java_org_vamp_1plugins_Plugin_getInputDomain(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    Plugin::InputDomain d = p->getInputDomain();

    jclass ourEnumClass = env->FindClass("org/vamp_plugins/Plugin$InputDomain");

    std::string dname = "TimeDomain";
    if (d == Plugin::FrequencyDomain) dname = "FrequencyDomain";

    return env->CallStaticObjectMethod
	(ourEnumClass, getEnumValueOfMethod(env), ourEnumClass,
	 env->NewStringUTF(dname.c_str())); //!!! string leaked!
}

jint
Java_org_vamp_1plugins_Plugin_getPreferredBlockSize(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return p->getPreferredBlockSize();
}

jint
Java_org_vamp_1plugins_Plugin_getPreferredStepSize(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return p->getPreferredStepSize();
}

jint
Java_org_vamp_1plugins_Plugin_getMinChannelCount(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return p->getMinChannelCount();
}

jint
Java_org_vamp_1plugins_Plugin_getMaxChannelCount(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return p->getMaxChannelCount();
}

jobjectArray
Java_org_vamp_1plugins_Plugin_getOutputDescriptors(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    Plugin::OutputList outputs = p->getOutputDescriptors();
    jclass descClass = env->FindClass("org/vamp_plugins/OutputDescriptor");
    jobjectArray result = env->NewObjectArray(outputs.size(), descClass, 0);
    for (int i = 0; i < outputs.size(); ++i) {

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

	jobject sampleType = env->CallStaticObjectMethod
    	    (sampleTypeClass, getEnumValueOfMethod(env),
	     sampleTypeClass, env->NewStringUTF(stype));//!!! string leaked!

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

jobject
Java_org_vamp_1plugins_Plugin_process(JNIEnv *env, jobject obj, jobjectArray data, jobject timestamp)
{
    Plugin *p = getHandle<Plugin>(env, obj);

    Vamp::RealTime rt;
    rt.sec = getIntField(env, timestamp, "sec");
    rt.nsec = getIntField(env, timestamp, "nsec");
    
    int channels = env->GetArrayLength(data);
    float **input = new float *[channels];
    for (int c = 0; c < channels; ++c) {
        jfloatArray cdata = (jfloatArray)env->GetObjectArrayElement(data, c);
        input[c] = env->GetFloatArrayElements(cdata, 0);
    }

    Plugin::FeatureSet features = p->process(input, rt);

    for (int c = 0; c < channels; ++c) {
        jfloatArray cdata = (jfloatArray)env->GetObjectArrayElement(data, c);
        env->ReleaseFloatArrayElements(cdata, input[c], 0);
    }

    delete[] input;

    return convertFeatures(env, features);
}

jobject
Java_org_vamp_1plugins_Plugin_getRemainingFeatures(JNIEnv *env, jobject obj)
{
    Plugin *p = getHandle<Plugin>(env, obj);

    Plugin::FeatureSet features = p->getRemainingFeatures();

    return convertFeatures(env, features);
}

