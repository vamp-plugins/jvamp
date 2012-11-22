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

#ifndef _GETSET_H_INCLUDED_
#define _GETSET_H_INCLUDED_

#include <jni.h>

#include <string>
#include <vector>

#include <vamp-hostsdk/RealTime.h>

extern int
getIntField(JNIEnv *env, jobject obj, std::string name);

extern void
setStringField(JNIEnv *env, jobject obj, std::string name, std::string value);

extern void
setFloatField(JNIEnv *env, jobject obj, std::string name, float value);

extern void
setBooleanField(JNIEnv *env, jobject obj, std::string name, bool value);

extern void
setIntField(JNIEnv *env, jobject obj, std::string name, int value);

extern void
setRealTimeField(JNIEnv *env, jobject obj, std::string name, Vamp::RealTime value);

extern void
setObjectField(JNIEnv *env, jobject obj, std::string name, std::string type, jobject value);

extern void
setFloatArrayField(JNIEnv *env, jobject obj, std::string name, std::vector<float> value);

extern void
setStringArrayField(JNIEnv *env, jobject obj, std::string name, std::vector<std::string> value);

extern jmethodID
getEnumValueOfMethod(JNIEnv *env);

#endif
