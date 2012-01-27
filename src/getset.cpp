
#include "getset.h"

#include <iostream>

int
getIntField(JNIEnv *env, jobject obj, std::string name)
{
    jclass cls = env->GetObjectClass(obj);
    return env->GetIntField(obj,
			    env->GetFieldID(cls, name.c_str(), "I"));
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
    setObjectField(env, obj, name, "[float", jarr);
}

void
setStringArrayField(JNIEnv *env, jobject obj, std::string name, std::vector<std::string> values)
{
    jclass strCls = env->FindClass("java/lang/String");
    jobjectArray jarr = env->NewObjectArray(values.size(), strCls, 0);
    for (int i = 0; i < values.size(); ++i) {
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

