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

#include "org_vamp_plugins_PluginLoader.h"

#include <vamp-hostsdk/PluginLoader.h>
#include <vamp-hostsdk/PluginHostAdapter.h>

#include "handle.h"

using Vamp::Plugin;
using Vamp::HostExt::PluginLoader;

JNIEXPORT void JNICALL
Java_org_vamp_1plugins_PluginLoader_initialise(JNIEnv *env, jobject obj)
{
    PluginLoader *inst = PluginLoader::getInstance();
    setHandle(env, obj, inst);
}

JNIEXPORT jobjectArray JNICALL
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

JNIEXPORT jlong JNICALL
Java_org_vamp_1plugins_PluginLoader_loadPluginNative(JNIEnv *env, jobject obj,
						     jstring key, jfloat rate,
						     jint flags)
{
    PluginLoader *inst = getHandle<PluginLoader>(env, obj);
    const char *kstr = env->GetStringUTFChars(key, 0);
    Plugin *p = inst->loadPlugin(kstr, rate, flags);
    env->ReleaseStringUTFChars(key, kstr);
    return (jlong)p;
}

JNIEXPORT jobjectArray JNICALL
Java_org_vamp_1plugins_PluginLoader_getPluginCategory(JNIEnv *env, jobject obj,
						      jstring key)
{
    PluginLoader *inst = getHandle<PluginLoader>(env, obj);
    const char *kstr = env->GetStringUTFChars(key, 0);
    PluginLoader::PluginCategoryHierarchy cat = inst->getPluginCategory(kstr);
    jobjectArray result = env->NewObjectArray
	(cat.size(), env->FindClass("java/lang/String"), 0);
    for (int i = 0; i < cat.size(); ++i) {
	env->SetObjectArrayElement(result, i,
				   env->NewStringUTF(cat[i].c_str()));
    }
    return result;
}    

JNIEXPORT jobjectArray JNICALL
Java_org_vamp_1plugins_PluginLoader_getPluginPath(JNIEnv *env, jobject obj)
{
    std::vector<std::string> path = Vamp::PluginHostAdapter::getPluginPath();
    jobjectArray result = env->NewObjectArray
	(path.size(), env->FindClass("java/lang/String"), 0);
    for (int i = 0; i < path.size(); ++i) {
	env->SetObjectArrayElement(result, i,
				   env->NewStringUTF(path[i].c_str()));
    }
    return result;
}    

