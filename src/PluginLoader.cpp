#include "org_vamp_plugins_PluginLoader.h"

#include <vamp-hostsdk/PluginLoader.h>

#include "handle.h"

using Vamp::Plugin;
using Vamp::HostExt::PluginLoader;

void
Java_org_vamp_1plugins_PluginLoader_initialise(JNIEnv *env, jobject obj)
{
    PluginLoader *inst = PluginLoader::getInstance();
    setHandle(env, obj, inst);
}

jlong
Java_org_vamp_1plugins_PluginLoader_loadPluginNative(JNIEnv *env, jobject obj,
						     jstring key, jfloat rate)
{
    PluginLoader *inst = getHandle<PluginLoader>(env, obj);
    const char *kstr = env->GetStringUTFChars(key, 0);
    Plugin *p = inst->loadPlugin(kstr, rate);
    env->ReleaseStringUTFChars(key, kstr);
    return (jlong)p;
}


    
