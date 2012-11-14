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

jobjectArray
Java_org_vamp_1plugins_PluginLoader_listPlugins(JNIEnv *env, jobject obj)
{
    PluginLoader *inst = getHandle<PluginLoader>(env, obj);
    PluginLoader::PluginKeyList plugins = inst->listPlugins();
    jobjectArray result = env->NewObjectArray
	(plugins.size(), env->FindClass("java/lang/String"), 0);
    for (int i = 0; i < plugins.size(); ++i) {
	env->SetObjectArrayElement(result, i,
				   env->NewStringUTF(plugins[i].c_str()));
    }
    return result;
}    

jlong
Java_org_vamp_1plugins_PluginLoader_loadPluginNative(JNIEnv *env, jobject obj,
						     jstring key, jfloat rate)
{
    PluginLoader *inst = getHandle<PluginLoader>(env, obj);
    const char *kstr = env->GetStringUTFChars(key, 0);
    Plugin *p = inst->loadPlugin(kstr, rate, PluginLoader::ADAPT_ALL); //!!! args!
    env->ReleaseStringUTFChars(key, kstr);
    return (jlong)p;
}


    
//!!! todo: loadPlugin adapters
//!!! todo: getPluginCategory

