#include "org_vamp_plugins_RealTime.h"

#include <vamp-hostsdk/RealTime.h>

#include "handle.h"

using Vamp::RealTime;
using std::string;

void
Java_org_vamp_1plugins_RealTime_dispose(JNIEnv *env, jobject obj)
{
    RealTime *rt = getHandle<RealTime>(env, obj);
    setHandle<RealTime>(env, obj, 0);
    delete rt;
}

jint
Java_org_vamp_1plugins_RealTime_sec(JNIEnv *env, jobject obj)
{
    RealTime *rt = getHandle<RealTime>(env, obj);
    return rt->sec;
}

jint
Java_org_vamp_1plugins_RealTime_nsec(JNIEnv *env, jobject obj)
{
    RealTime *rt = getHandle<RealTime>(env, obj);
    return rt->nsec;
}    

jint
Java_org_vamp_1plugins_RealTime_usec(JNIEnv *env, jobject obj)
{
    RealTime *rt = getHandle<RealTime>(env, obj);
    return rt->usec();
}

jint
Java_org_vamp_1plugins_RealTime_msec(JNIEnv *env, jobject obj)
{
    RealTime *rt = getHandle<RealTime>(env, obj);
    return rt->msec();
}

jstring
Java_org_vamp_1plugins_RealTime_toString(JNIEnv *env, jobject obj)
{
    RealTime *rt = getHandle<RealTime>(env, obj);
    return env->NewStringUTF(rt->toString().c_str());
}

jstring
Java_org_vamp_1plugins_RealTime_toText(JNIEnv *env, jobject obj)
{
    RealTime *rt = getHandle<RealTime>(env, obj);
    return env->NewStringUTF(rt->toText().c_str());
}    

jobject
Java_org_vamp_1plugins_RealTime_fromSeconds(JNIEnv *env, jclass cls, jdouble s)
{
    
}

jobject Java_org_vamp_1plugins_RealTime_fromMilliseconds
  (JNIEnv *env, jclass cls, jint);

jobject Java_org_vamp_1plugins_RealTime_frame2RealTime
  (JNIEnv *env, jclass cls, jlong, jint);

jlong Java_org_vamp_1plugins_RealTime_realTime2Frame
  (JNIEnv *env, jclass cls, jobject, jint);

void Java_org_vamp_1plugins_RealTime_init(JNIEnv *env, jobject obj, jint sec, jint nsec)
{
}



