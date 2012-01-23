#include "org_vamp_plugins_Plugin.h"

#include <vamp-hostsdk/Plugin.h>

#include "handle.h"

using Vamp::Plugin;
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

jboolean
Java_org_vamp_1plugins_Plugin_initialise(JNIEnv *env, jobject obj,
					 jint inputChannels, jint stepSize,
					 jint blockSize)
{
    Plugin *p = getHandle<Plugin>(env, obj);
    return p->initialise(inputChannels, stepSize, blockSize);
}

