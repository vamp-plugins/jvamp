
#ifndef _GETSET_H_INCLUDED_
#define _GETSET_H_INCLUDED_

#include <jni.h>

#include <string>
#include <vector>

extern void
setStringField(JNIEnv *env, jobject obj, std::string name, std::string value);

extern void
setFloatField(JNIEnv *env, jobject obj, std::string name, float value);

extern void
setBooleanField(JNIEnv *env, jobject obj, std::string name, bool value);

extern void
setIntField(JNIEnv *env, jobject obj, std::string name, int value);

extern void
setObjectField(JNIEnv *env, jobject obj, std::string name, std::string type, jobject value);

extern void
setStringArrayField(JNIEnv *env, jobject obj, std::string name, std::vector<std::string> value);

extern jmethodID
getEnumValueOfMethod(JNIEnv *env);

#endif
