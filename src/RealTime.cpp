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

#include "org_vamp_plugins_RealTime.h"

#include <vamp-hostsdk/RealTime.h>

#include "getset.h"

using Vamp::RealTime;
using std::string;

JNIEXPORT jint JNICALL
Java_org_vamp_1plugins_RealTime_sec(JNIEnv *env, jobject obj)
{
    RealTime rt = getRealTime(env, obj);
    return rt.sec;
}

JNIEXPORT jint JNICALL
Java_org_vamp_1plugins_RealTime_nsec(JNIEnv *env, jobject obj)
{
    RealTime rt = getRealTime(env, obj);
    return rt.nsec;
}    

JNIEXPORT jint JNICALL
Java_org_vamp_1plugins_RealTime_usec(JNIEnv *env, jobject obj)
{
    RealTime rt = getRealTime(env, obj);
    return rt.usec();
}

JNIEXPORT jint JNICALL
Java_org_vamp_1plugins_RealTime_msec(JNIEnv *env, jobject obj)
{
    RealTime rt = getRealTime(env, obj);
    return rt.msec();
}

JNIEXPORT jstring JNICALL
Java_org_vamp_1plugins_RealTime_toString(JNIEnv *env, jobject obj)
{
    RealTime rt = getRealTime(env, obj);
    return env->NewStringUTF(rt.toString().c_str());
}

JNIEXPORT jstring JNICALL
Java_org_vamp_1plugins_RealTime_toText(JNIEnv *env, jobject obj)
{
    RealTime rt = getRealTime(env, obj);
    return env->NewStringUTF(rt.toText().c_str());
}    

JNIEXPORT jobject JNICALL
Java_org_vamp_1plugins_RealTime_fromSeconds(JNIEnv *env, jclass cls, jdouble s)
{
    jclass rtClass = env->FindClass("org/vamp_plugins/RealTime");
    jmethodID rtCtor = env->GetMethodID(rtClass, "<init>", "(II)V");
    RealTime rt = RealTime::fromSeconds(s);
    return env->NewObject(rtClass, rtCtor, rt.sec, rt.nsec);
}

JNIEXPORT jobject JNICALL
Java_org_vamp_1plugins_RealTime_fromMilliseconds(JNIEnv *env, jclass cls, jint ms)
{
    jclass rtClass = env->FindClass("org/vamp_plugins/RealTime");
    jmethodID rtCtor = env->GetMethodID(rtClass, "<init>", "(II)V");
    RealTime rt = RealTime::fromMilliseconds(ms);
    return env->NewObject(rtClass, rtCtor, rt.sec, rt.nsec);
}

JNIEXPORT jobject JNICALL
Java_org_vamp_1plugins_RealTime_frame2RealTime(JNIEnv *env, jclass cls, jlong frame, jint sampleRate)
{
    jclass rtClass = env->FindClass("org/vamp_plugins/RealTime");
    jmethodID rtCtor = env->GetMethodID(rtClass, "<init>", "(II)V");
    RealTime rt = RealTime::frame2RealTime(long(frame), sampleRate);
    return env->NewObject(rtClass, rtCtor, rt.sec, rt.nsec);
}

JNIEXPORT jlong JNICALL
Java_org_vamp_1plugins_RealTime_realTime2Frame(JNIEnv *env, jclass cls, jobject obj, jint sampleRate)
{
    RealTime rt = getRealTime(env, obj);
    return RealTime::realTime2Frame(rt, sampleRate);
}

JNIEXPORT void JNICALL
Java_org_vamp_1plugins_RealTime_initialise(JNIEnv *env, jobject obj, jint sec, jint nsec)
{
    setIntField(env, obj, "m_s", sec);
    setIntField(env, obj, "m_n", nsec);
}

