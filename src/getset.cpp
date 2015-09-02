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

#include "getset.h"

#include <iostream>

int
getIntField(JNIEnv *env, jobject obj, std::string name)
{
    jclass cls = env->GetObjectClass(obj);
    return env->GetIntField(obj,
			    env->GetFieldID(cls, name.c_str(), "I"));
}

Vamp::RealTime
getRealTime(JNIEnv *env, jobject obj)
{
    int s = getIntField(env, obj, "m_s");
    int n = getIntField(env, obj, "m_n");
    return Vamp::RealTime(s, n);
}

void
setStringField(JNIEnv *env, jobject obj, std::string name, std::string value)
{
    jclass cls = env->GetObjectClass(obj);
    env->SetObjectField(obj,
			env->GetFieldID(cls, name.c_str(), "Ljava/lang/String;"),
			env->NewStringUTF(value.c_str()));
}

void
setFloatField(JNIEnv *env, jobject obj, std::string name, float value)
{
    jclass cls = env->GetObjectClass(obj);
    env->SetFloatField(obj,
		       env->GetFieldID(cls, name.c_str(), "F"),
		       value);
}

void
setBooleanField(JNIEnv *env, jobject obj, std::string name, bool value)
{
    jclass cls = env->GetObjectClass(obj);
    env->SetBooleanField(obj,
			 env->GetFieldID(cls, name.c_str(), "Z"),
			 value);
}

void
setIntField(JNIEnv *env, jobject obj, std::string name, int value)
{
    jclass cls = env->GetObjectClass(obj);
    env->SetIntField(obj,
		     env->GetFieldID(cls, name.c_str(), "I"),
		     value);
}

void
setRealTimeField(JNIEnv *env, jobject obj, std::string name, Vamp::RealTime rt)
{
    jclass rtClass = env->FindClass("org/vamp_plugins/RealTime");
    jmethodID ctor = env->GetMethodID(rtClass, "<init>", "(II)V");
    jobject jrt = env->NewObject(rtClass, ctor, rt.sec, rt.nsec);
    setObjectField(env, obj, name, "Lorg/vamp_plugins/RealTime;", jrt);
}

void
setObjectField(JNIEnv *env, jobject obj, std::string name, std::string type, jobject value)
{
    jclass cls = env->GetObjectClass(obj);
    jfieldID field = env->GetFieldID(cls, name.c_str(), type.c_str());
    env->SetObjectField(obj, field, value);
}

void
setFloatArrayField(JNIEnv *env, jobject obj, std::string name, std::vector<float> values)
{
    jfloatArray jarr = env->NewFloatArray(values.size());
    env->SetFloatArrayRegion(jarr, 0, values.size(), values.data());
    setObjectField(env, obj, name, "[F", jarr);
}

void
setStringArrayField(JNIEnv *env, jobject obj, std::string name, std::vector<std::string> values)
{
    jclass strCls = env->FindClass("java/lang/String");
    jobjectArray jarr = env->NewObjectArray(values.size(), strCls, 0);
    for (int i = 0; i < (int)values.size(); ++i) {
	env->SetObjectArrayElement(jarr, i, env->NewStringUTF(values[i].c_str()));
    }
    setObjectField(env, obj, name, "[Ljava/lang/String;", jarr);
}

jmethodID
getEnumValueOfMethod(JNIEnv *env)
{
    jclass enumClass = env->FindClass("java/lang/Enum");

    // Enum.valueOf(Class, String) returns Enum
    jmethodID valueOfMethod = env->GetStaticMethodID
	(enumClass, "valueOf",
	 "(Ljava/lang/Class;Ljava/lang/String;)Ljava/lang/Enum;");

    return valueOfMethod;
}

