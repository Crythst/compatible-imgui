/*
 * Target-specific JNI definitions for cross-compiling the Windows libraries.
 * Kept in-tree so the build does not need a Windows JDK.
 */
#ifndef _JAVASOFT_JNI_MD_H_
#define _JAVASOFT_JNI_MD_H_

#define JNIEXPORT __declspec(dllexport)
#define JNIIMPORT __declspec(dllimport)
/* x86_64/arm64 use the unified calling convention. jni.h also defines
 * JNICALL itself; leaving it alone avoids a macro redefinition warning. */
#ifndef JNICALL
#define JNICALL
#endif

typedef long jint;
typedef __int64 jlong;
typedef signed char jbyte;

#endif /* !_JAVASOFT_JNI_MD_H_ */
