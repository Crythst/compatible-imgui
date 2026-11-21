#include <imgui_moulberry92_extension_texteditor_TextEditorLanguage.h>

//@line:10

        #include "_texteditor.h"
        #define THIS ((const TextEditor::Language*)STRUCT_PTR)
     JNIEXPORT jstring JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nGetName(JNIEnv* env, jobject object) {


//@line:19

        return env->NewStringUTF(THIS->name.c_str());
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nGetCaseSensitive(JNIEnv* env, jobject object) {


//@line:27

        return THIS->caseSensitive;
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nGetPreprocess(JNIEnv* env, jobject object) {


//@line:35

        return THIS->preprocess;
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nGetSingleLineComment(JNIEnv* env, jobject object) {


//@line:43

        return env->NewStringUTF(THIS->singleLineComment.c_str());
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nGetSingleLineCommentAlt(JNIEnv* env, jobject object) {


//@line:51

        return env->NewStringUTF(THIS->singleLineCommentAlt.c_str());
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nGetCommentStart(JNIEnv* env, jobject object) {


//@line:59

        return env->NewStringUTF(THIS->commentStart.c_str());
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nGetCommentEnd(JNIEnv* env, jobject object) {


//@line:67

        return env->NewStringUTF(THIS->commentEnd.c_str());
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nGetHasSingleQuotedStrings(JNIEnv* env, jobject object) {


//@line:75

        return THIS->hasSingleQuotedStrings;
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nGetHasDoubleQuotedStrings(JNIEnv* env, jobject object) {


//@line:83

        return THIS->hasDoubleQuotedStrings;
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nGetOtherStringStart(JNIEnv* env, jobject object) {


//@line:91

        return env->NewStringUTF(THIS->otherStringStart.c_str());
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nGetOtherStringEnd(JNIEnv* env, jobject object) {


//@line:99

        return env->NewStringUTF(THIS->otherStringEnd.c_str());
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nGetOtherStringAltStart(JNIEnv* env, jobject object) {


//@line:107

        return env->NewStringUTF(THIS->otherStringAltStart.c_str());
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nGetOtherStringAltEnd(JNIEnv* env, jobject object) {


//@line:115

        return env->NewStringUTF(THIS->otherStringAltEnd.c_str());
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nGetStringEscape(JNIEnv* env, jobject object) {


//@line:123

        return THIS->stringEscape;
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nC(JNIEnv* env, jclass clazz) {


//@line:131

        return (uintptr_t)TextEditor::Language::C();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nCpp(JNIEnv* env, jclass clazz) {


//@line:139

        return (uintptr_t)TextEditor::Language::Cpp();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nCs(JNIEnv* env, jclass clazz) {


//@line:147

        return (uintptr_t)TextEditor::Language::Cs();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nAngelScript(JNIEnv* env, jclass clazz) {


//@line:155

        return (uintptr_t)TextEditor::Language::AngelScript();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nLua(JNIEnv* env, jclass clazz) {


//@line:163

        return (uintptr_t)TextEditor::Language::Lua();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nPython(JNIEnv* env, jclass clazz) {


//@line:171

        return (uintptr_t)TextEditor::Language::Python();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nGlsl(JNIEnv* env, jclass clazz) {


//@line:179

        return (uintptr_t)TextEditor::Language::Glsl();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nHlsl(JNIEnv* env, jclass clazz) {


//@line:187

        return (uintptr_t)TextEditor::Language::Hlsl();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nJson(JNIEnv* env, jclass clazz) {


//@line:195

        return (uintptr_t)TextEditor::Language::Json();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nMarkdown(JNIEnv* env, jclass clazz) {


//@line:203

        return (uintptr_t)TextEditor::Language::Markdown();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditorLanguage_nSql(JNIEnv* env, jclass clazz) {


//@line:211

        return (uintptr_t)TextEditor::Language::Sql();
    

}


//@line:215

        #undef THIS
     