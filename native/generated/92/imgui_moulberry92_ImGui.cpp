#include <imgui_moulberry92_ImGuiViewport.h>
#include <imgui_moulberry92_ImGuiIO.h>
#include <imgui_moulberry92_ImGui.h>
#include <imgui_moulberry92_ImGuiListClipper.h>
#include <imgui_moulberry92_ImGuiTableSortSpecs.h>
#include <imgui_moulberry92_ImGuiPlatformMonitor.h>
#include <imgui_moulberry92_ImGuiInputTextCallbackData.h>
#include <imgui_moulberry92_ImGuiOnceUponAFrame.h>

//@line:124

        #include "_common.h"
     JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nInitJni(JNIEnv* env, jclass clazz) {


//@line:128

        Jni::InitJvm(env);
        Jni::InitCommon(env);
        Jni::InitAssertion(env);
        Jni::InitCallbacks(env);
        Jni::InitBindingStruct(env);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_setAssertCallback(JNIEnv* env, jclass clazz, jobject callback) {


//@line:144

        Jni::SetAssertionCallback(callback);
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nCreateContext__(JNIEnv* env, jclass clazz) {


//@line:161

        return (uintptr_t)ImGui::CreateContext();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nCreateContext__J(JNIEnv* env, jclass clazz, jlong sharedFontAtlas) {


//@line:165

        return (uintptr_t)ImGui::CreateContext(reinterpret_cast<ImFontAtlas*>(sharedFontAtlas));
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nDestroyContext__(JNIEnv* env, jclass clazz) {


//@line:177

        ImGui::DestroyContext();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nDestroyContext__J(JNIEnv* env, jclass clazz, jlong ctx) {


//@line:181

        ImGui::DestroyContext(reinterpret_cast<ImGuiContext*>(ctx));
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nGetCurrentContext(JNIEnv* env, jclass clazz) {


//@line:189

        return (uintptr_t)ImGui::GetCurrentContext();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetCurrentContext(JNIEnv* env, jclass clazz, jlong ctx) {


//@line:197

        ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nGetIO(JNIEnv* env, jclass clazz) {


//@line:213

        return (uintptr_t)&ImGui::GetIO();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nGetStyle(JNIEnv* env, jclass clazz) {


//@line:227

        return (uintptr_t)&ImGui::GetStyle();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nNewFrame(JNIEnv* env, jclass clazz) {


//@line:238

        ImGui::NewFrame();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nEndFrame(JNIEnv* env, jclass clazz) {


//@line:250

        ImGui::EndFrame();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nRender(JNIEnv* env, jclass clazz) {


//@line:261

        ImGui::Render();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nGetDrawData(JNIEnv* env, jclass clazz) {


//@line:275

        return (uintptr_t)ImGui::GetDrawData();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nShowDemoWindow__(JNIEnv* env, jclass clazz) {


//@line:295

        ImGui::ShowDemoWindow();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nShowDemoWindow___3Z(JNIEnv* env, jclass clazz, jbooleanArray obj_pOpen) {

//@line:299

        auto pOpen = obj_pOpen == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pOpen, JNI_FALSE);
        ImGui::ShowDemoWindow((pOpen != NULL ? &pOpen[0] : NULL));
        if (pOpen != NULL) env->ReleasePrimitiveArrayCritical(obj_pOpen, pOpen, JNI_FALSE);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nShowMetricsWindow__(JNIEnv* env, jclass clazz) {


//@line:319

        ImGui::ShowMetricsWindow();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nShowMetricsWindow___3Z(JNIEnv* env, jclass clazz, jbooleanArray obj_pOpen) {

//@line:323

        auto pOpen = obj_pOpen == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pOpen, JNI_FALSE);
        ImGui::ShowMetricsWindow((pOpen != NULL ? &pOpen[0] : NULL));
        if (pOpen != NULL) env->ReleasePrimitiveArrayCritical(obj_pOpen, pOpen, JNI_FALSE);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nShowDebugLogWindow__(JNIEnv* env, jclass clazz) {


//@line:343

        ImGui::ShowDebugLogWindow();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nShowDebugLogWindow___3Z(JNIEnv* env, jclass clazz, jbooleanArray obj_pOpen) {

//@line:347

        auto pOpen = obj_pOpen == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pOpen, JNI_FALSE);
        ImGui::ShowDebugLogWindow((pOpen != NULL ? &pOpen[0] : NULL));
        if (pOpen != NULL) env->ReleasePrimitiveArrayCritical(obj_pOpen, pOpen, JNI_FALSE);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nShowIDStackToolWindow__(JNIEnv* env, jclass clazz) {


//@line:367

        ImGui::ShowIDStackToolWindow();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nShowIDStackToolWindow___3Z(JNIEnv* env, jclass clazz, jbooleanArray obj_pOpen) {

//@line:371

        auto pOpen = obj_pOpen == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pOpen, JNI_FALSE);
        ImGui::ShowIDStackToolWindow((pOpen != NULL ? &pOpen[0] : NULL));
        if (pOpen != NULL) env->ReleasePrimitiveArrayCritical(obj_pOpen, pOpen, JNI_FALSE);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nShowAboutWindow__(JNIEnv* env, jclass clazz) {


//@line:391

        ImGui::ShowAboutWindow();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nShowAboutWindow___3Z(JNIEnv* env, jclass clazz, jbooleanArray obj_pOpen) {

//@line:395

        auto pOpen = obj_pOpen == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pOpen, JNI_FALSE);
        ImGui::ShowAboutWindow((pOpen != NULL ? &pOpen[0] : NULL));
        if (pOpen != NULL) env->ReleasePrimitiveArrayCritical(obj_pOpen, pOpen, JNI_FALSE);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nShowStyleEditor__(JNIEnv* env, jclass clazz) {


//@line:417

        ImGui::ShowStyleEditor();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nShowStyleEditor__J(JNIEnv* env, jclass clazz, jlong ref) {


//@line:421

        ImGui::ShowStyleEditor(reinterpret_cast<ImGuiStyle*>(ref));
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nShowStyleSelector(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:432

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::ShowStyleSelector(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nShowFontSelector(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:446

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        ImGui::ShowFontSelector(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nShowUserGuide(JNIEnv* env, jclass clazz) {


//@line:459

        ImGui::ShowUserGuide();
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_ImGui_nGetVersion(JNIEnv* env, jclass clazz) {


//@line:470

        return env->NewStringUTF(ImGui::GetVersion());
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nStyleColorsDark__(JNIEnv* env, jclass clazz) {


//@line:490

        ImGui::StyleColorsDark();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nStyleColorsDark__J(JNIEnv* env, jclass clazz, jlong style) {


//@line:494

        ImGui::StyleColorsDark(reinterpret_cast<ImGuiStyle*>(style));
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nStyleColorsLight__(JNIEnv* env, jclass clazz) {


//@line:512

        ImGui::StyleColorsLight();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nStyleColorsLight__J(JNIEnv* env, jclass clazz, jlong style) {


//@line:516

        ImGui::StyleColorsLight(reinterpret_cast<ImGuiStyle*>(style));
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nStyleColorsClassic__(JNIEnv* env, jclass clazz) {


//@line:534

        ImGui::StyleColorsClassic();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nStyleColorsClassic__J(JNIEnv* env, jclass clazz, jlong style) {


//@line:538

        ImGui::StyleColorsClassic(reinterpret_cast<ImGuiStyle*>(style));
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBegin__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_title) {

//@line:571

        auto title = obj_title == NULL ? NULL : (char*)env->GetStringUTFChars(obj_title, JNI_FALSE);
        auto _result = ImGui::Begin(title);
        if (title != NULL) env->ReleaseStringUTFChars(obj_title, title);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBegin__Ljava_lang_String_2_3Z(JNIEnv* env, jclass clazz, jstring obj_title, jbooleanArray obj_pOpen) {

//@line:578

        auto title = obj_title == NULL ? NULL : (char*)env->GetStringUTFChars(obj_title, JNI_FALSE);
        auto pOpen = obj_pOpen == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pOpen, JNI_FALSE);
        auto _result = ImGui::Begin(title, (pOpen != NULL ? &pOpen[0] : NULL));
        if (title != NULL) env->ReleaseStringUTFChars(obj_title, title);
        if (pOpen != NULL) env->ReleasePrimitiveArrayCritical(obj_pOpen, pOpen, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBegin__Ljava_lang_String_2_3ZI(JNIEnv* env, jclass clazz, jstring obj_title, jbooleanArray obj_pOpen, jint imGuiWindowFlags) {

//@line:587

        auto title = obj_title == NULL ? NULL : (char*)env->GetStringUTFChars(obj_title, JNI_FALSE);
        auto pOpen = obj_pOpen == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pOpen, JNI_FALSE);
        auto _result = ImGui::Begin(title, (pOpen != NULL ? &pOpen[0] : NULL), imGuiWindowFlags);
        if (title != NULL) env->ReleaseStringUTFChars(obj_title, title);
        if (pOpen != NULL) env->ReleasePrimitiveArrayCritical(obj_pOpen, pOpen, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBegin__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_title, jint imGuiWindowFlags) {

//@line:596

        auto title = obj_title == NULL ? NULL : (char*)env->GetStringUTFChars(obj_title, JNI_FALSE);
        auto _result = ImGui::Begin(title, NULL, imGuiWindowFlags);
        if (title != NULL) env->ReleaseStringUTFChars(obj_title, title);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nEnd(JNIEnv* env, jclass clazz) {


//@line:607

        ImGui::End();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginChild__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_strId) {

//@line:666

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto _result = ImGui::BeginChild(strId);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginChild__Ljava_lang_String_2FF(JNIEnv* env, jclass clazz, jstring obj_strId, jfloat sizeX, jfloat sizeY) {

//@line:673

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::BeginChild(strId, size);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginChild__Ljava_lang_String_2FFI(JNIEnv* env, jclass clazz, jstring obj_strId, jfloat sizeX, jfloat sizeY, jint childFlags) {

//@line:681

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::BeginChild(strId, size, childFlags);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginChild__Ljava_lang_String_2FFII(JNIEnv* env, jclass clazz, jstring obj_strId, jfloat sizeX, jfloat sizeY, jint childFlags, jint windowFlags) {

//@line:689

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::BeginChild(strId, size, childFlags, windowFlags);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginChild__Ljava_lang_String_2II(JNIEnv* env, jclass clazz, jstring obj_strId, jint childFlags, jint windowFlags) {

//@line:697

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto _result = ImGui::BeginChild(strId, ImVec2(0,0), childFlags, windowFlags);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginChild__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_strId, jint windowFlags) {

//@line:704

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto _result = ImGui::BeginChild(strId, ImVec2(0,0), 0, windowFlags);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginChild__I(JNIEnv* env, jclass clazz, jint id) {


//@line:747

        return ImGui::BeginChild(id);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginChild__IFF(JNIEnv* env, jclass clazz, jint id, jfloat sizeX, jfloat sizeY) {

//@line:751

        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::BeginChild(id, size);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginChild__IFFI(JNIEnv* env, jclass clazz, jint id, jfloat sizeX, jfloat sizeY, jint childFlags) {

//@line:757

        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::BeginChild(id, size, childFlags);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginChild__IFFII(JNIEnv* env, jclass clazz, jint id, jfloat sizeX, jfloat sizeY, jint childFlags, jint windowFlags) {

//@line:763

        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::BeginChild(id, size, childFlags, windowFlags);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginChild__III(JNIEnv* env, jclass clazz, jint id, jint childFlags, jint windowFlags) {


//@line:769

        return ImGui::BeginChild(id, ImVec2(0,0), childFlags, windowFlags);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginChild__II(JNIEnv* env, jclass clazz, jint id, jint windowFlags) {


//@line:773

        return ImGui::BeginChild(id, ImVec2(0,0), 0, windowFlags);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginChild__Ljava_lang_String_2FFZ(JNIEnv* env, jclass clazz, jstring obj_strId, jfloat sizeX, jfloat sizeY, jboolean border) {

//@line:793

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::BeginChild(strId, size, static_cast<ImGuiChildFlags>(border));
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginChild__Ljava_lang_String_2FFZI(JNIEnv* env, jclass clazz, jstring obj_strId, jfloat sizeX, jfloat sizeY, jboolean border, jint windowFlags) {

//@line:801

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::BeginChild(strId, size, static_cast<ImGuiChildFlags>(border), windowFlags);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginChild__IFFZ(JNIEnv* env, jclass clazz, jint id, jfloat sizeX, jfloat sizeY, jboolean border) {

//@line:845

        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::BeginChild(id, size, static_cast<ImGuiChildFlags>(border));
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginChild__IFFZI(JNIEnv* env, jclass clazz, jint id, jfloat sizeX, jfloat sizeY, jboolean border, jint windowFlags) {

//@line:851

        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::BeginChild(id, size, static_cast<ImGuiChildFlags>(border), windowFlags);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nEndChild(JNIEnv* env, jclass clazz) {


//@line:861

        ImGui::EndChild();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsWindowAppearing(JNIEnv* env, jclass clazz) {


//@line:872

        return ImGui::IsWindowAppearing();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsWindowCollapsed(JNIEnv* env, jclass clazz) {


//@line:880

        return ImGui::IsWindowCollapsed();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsWindowFocused__(JNIEnv* env, jclass clazz) {


//@line:898

        return ImGui::IsWindowFocused();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsWindowFocused__I(JNIEnv* env, jclass clazz, jint imGuiFocusedFlags) {


//@line:902

        return ImGui::IsWindowFocused(imGuiFocusedFlags);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsWindowHovered__(JNIEnv* env, jclass clazz) {


//@line:926

        return ImGui::IsWindowHovered();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsWindowHovered__I(JNIEnv* env, jclass clazz, jint imGuiHoveredFlags) {


//@line:930

        return ImGui::IsWindowHovered(imGuiHoveredFlags);
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nGetWindowDrawList(JNIEnv* env, jclass clazz) {


//@line:941

        return (uintptr_t)ImGui::GetWindowDrawList();
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetWindowDpiScale(JNIEnv* env, jclass clazz) {


//@line:952

        return ImGui::GetWindowDpiScale();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetWindowPos(JNIEnv* env, jclass clazz, jobject dst) {


//@line:990

        Jni::ImVec2Cpy(env, ImGui::GetWindowPos(), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetWindowPosX(JNIEnv* env, jclass clazz) {


//@line:994

        return ImGui::GetWindowPos().x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetWindowPosY(JNIEnv* env, jclass clazz) {


//@line:998

        return ImGui::GetWindowPos().y;
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetWindowSize(JNIEnv* env, jclass clazz, jobject dst) {


//@line:1032

        Jni::ImVec2Cpy(env, ImGui::GetWindowSize(), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetWindowSizeX(JNIEnv* env, jclass clazz) {


//@line:1036

        return ImGui::GetWindowSize().x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetWindowSizeY(JNIEnv* env, jclass clazz) {


//@line:1040

        return ImGui::GetWindowSize().y;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetWindowWidth(JNIEnv* env, jclass clazz) {


//@line:1051

        return ImGui::GetWindowWidth();
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetWindowHeight(JNIEnv* env, jclass clazz) {


//@line:1062

        return ImGui::GetWindowHeight();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nGetWindowViewport(JNIEnv* env, jclass clazz) {


//@line:1073

        return (uintptr_t)ImGui::GetWindowViewport();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextWindowPos__FF(JNIEnv* env, jclass clazz, jfloat posX, jfloat posY) {

//@line:1135

        ImVec2 pos = ImVec2(posX, posY);
        ImGui::SetNextWindowPos(pos);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextWindowPos__FFI(JNIEnv* env, jclass clazz, jfloat posX, jfloat posY, jint cond) {

//@line:1140

        ImVec2 pos = ImVec2(posX, posY);
        ImGui::SetNextWindowPos(pos, cond);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextWindowPos__FFIFF(JNIEnv* env, jclass clazz, jfloat posX, jfloat posY, jint cond, jfloat pivotX, jfloat pivotY) {

//@line:1145

        ImVec2 pos = ImVec2(posX, posY);
        ImVec2 pivot = ImVec2(pivotX, pivotY);
        ImGui::SetNextWindowPos(pos, cond, pivot);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextWindowPos__FFFF(JNIEnv* env, jclass clazz, jfloat posX, jfloat posY, jfloat pivotX, jfloat pivotY) {

//@line:1151

        ImVec2 pos = ImVec2(posX, posY);
        ImVec2 pivot = ImVec2(pivotX, pivotY);
        ImGui::SetNextWindowPos(pos, ImGuiCond_None, pivot);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextWindowSize__FF(JNIEnv* env, jclass clazz, jfloat sizeX, jfloat sizeY) {

//@line:1185

        ImVec2 size = ImVec2(sizeX, sizeY);
        ImGui::SetNextWindowSize(size);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextWindowSize__FFI(JNIEnv* env, jclass clazz, jfloat sizeX, jfloat sizeY, jint cond) {

//@line:1190

        ImVec2 size = ImVec2(sizeX, sizeY);
        ImGui::SetNextWindowSize(size, cond);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextWindowSizeConstraints(JNIEnv* env, jclass clazz, jfloat sizeMinX, jfloat sizeMinY, jfloat sizeMaxX, jfloat sizeMaxY) {

//@line:1211

        ImVec2 sizeMin = ImVec2(sizeMinX, sizeMinY);
        ImVec2 sizeMax = ImVec2(sizeMaxX, sizeMaxY);
        ImGui::SetNextWindowSizeConstraints(sizeMin, sizeMax);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextWindowContentSize(JNIEnv* env, jclass clazz, jfloat sizeX, jfloat sizeY) {

//@line:1233

        ImVec2 size = ImVec2(sizeX, sizeY);
        ImGui::SetNextWindowContentSize(size);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextWindowCollapsed__Z(JNIEnv* env, jclass clazz, jboolean collapsed) {


//@line:1252

        ImGui::SetNextWindowCollapsed(collapsed);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextWindowCollapsed__ZI(JNIEnv* env, jclass clazz, jboolean collapsed, jint cond) {


//@line:1256

        ImGui::SetNextWindowCollapsed(collapsed, cond);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextWindowFocus(JNIEnv* env, jclass clazz) {


//@line:1267

        ImGui::SetNextWindowFocus();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextWindowScroll(JNIEnv* env, jclass clazz, jfloat scrollX, jfloat scrollY) {

//@line:1285

        ImVec2 scroll = ImVec2(scrollX, scrollY);
        ImGui::SetNextWindowScroll(scroll);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextWindowBgAlpha(JNIEnv* env, jclass clazz, jfloat alpha) {


//@line:1298

        ImGui::SetNextWindowBgAlpha(alpha);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextWindowViewport(JNIEnv* env, jclass clazz, jint viewportId) {


//@line:1309

        ImGui::SetNextWindowViewport(viewportId);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetWindowPos__FF(JNIEnv* env, jclass clazz, jfloat posX, jfloat posY) {

//@line:1345

        ImVec2 pos = ImVec2(posX, posY);
        ImGui::SetWindowPos(pos);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetWindowPos__FFI(JNIEnv* env, jclass clazz, jfloat posX, jfloat posY, jint cond) {

//@line:1350

        ImVec2 pos = ImVec2(posX, posY);
        ImGui::SetWindowPos(pos, cond);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetWindowSize__FF(JNIEnv* env, jclass clazz, jfloat sizeX, jfloat sizeY) {

//@line:1387

        ImVec2 size = ImVec2(sizeX, sizeY);
        ImGui::SetWindowSize(size);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetWindowSize__FFI(JNIEnv* env, jclass clazz, jfloat sizeX, jfloat sizeY, jint cond) {

//@line:1392

        ImVec2 size = ImVec2(sizeX, sizeY);
        ImGui::SetWindowSize(size, cond);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetWindowCollapsed__Z(JNIEnv* env, jclass clazz, jboolean collapsed) {


//@line:1411

        ImGui::SetWindowCollapsed(collapsed);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetWindowCollapsed__ZI(JNIEnv* env, jclass clazz, jboolean collapsed, jint cond) {


//@line:1415

        ImGui::SetWindowCollapsed(collapsed, cond);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetWindowFocus__(JNIEnv* env, jclass clazz) {


//@line:1426

        ImGui::SetWindowFocus();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetWindowFontScale(JNIEnv* env, jclass clazz, jfloat scale) {


//@line:1438

        ImGui::SetWindowFontScale(scale);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetWindowPos__Ljava_lang_String_2FF(JNIEnv* env, jclass clazz, jstring obj_name, jfloat posX, jfloat posY) {

//@line:1470

        auto name = obj_name == NULL ? NULL : (char*)env->GetStringUTFChars(obj_name, JNI_FALSE);
        ImVec2 pos = ImVec2(posX, posY);
        ImGui::SetWindowPos(name, pos);
        if (name != NULL) env->ReleaseStringUTFChars(obj_name, name);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetWindowPos__Ljava_lang_String_2FFI(JNIEnv* env, jclass clazz, jstring obj_name, jfloat posX, jfloat posY, jint cond) {

//@line:1477

        auto name = obj_name == NULL ? NULL : (char*)env->GetStringUTFChars(obj_name, JNI_FALSE);
        ImVec2 pos = ImVec2(posX, posY);
        ImGui::SetWindowPos(name, pos, cond);
        if (name != NULL) env->ReleaseStringUTFChars(obj_name, name);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetWindowSize__Ljava_lang_String_2FF(JNIEnv* env, jclass clazz, jstring obj_name, jfloat sizeX, jfloat sizeY) {

//@line:1512

        auto name = obj_name == NULL ? NULL : (char*)env->GetStringUTFChars(obj_name, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        ImGui::SetWindowSize(name, size);
        if (name != NULL) env->ReleaseStringUTFChars(obj_name, name);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetWindowSize__Ljava_lang_String_2FFI(JNIEnv* env, jclass clazz, jstring obj_name, jfloat sizeX, jfloat sizeY, jint cond) {

//@line:1519

        auto name = obj_name == NULL ? NULL : (char*)env->GetStringUTFChars(obj_name, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        ImGui::SetWindowSize(name, size, cond);
        if (name != NULL) env->ReleaseStringUTFChars(obj_name, name);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetWindowCollapsed__Ljava_lang_String_2Z(JNIEnv* env, jclass clazz, jstring obj_name, jboolean collapsed) {

//@line:1540

        auto name = obj_name == NULL ? NULL : (char*)env->GetStringUTFChars(obj_name, JNI_FALSE);
        ImGui::SetWindowCollapsed((const char *)name, (bool)collapsed);
        if (name != NULL) env->ReleaseStringUTFChars(obj_name, name);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetWindowCollapsed__Ljava_lang_String_2ZI(JNIEnv* env, jclass clazz, jstring obj_name, jboolean collapsed, jint cond) {

//@line:1546

        auto name = obj_name == NULL ? NULL : (char*)env->GetStringUTFChars(obj_name, JNI_FALSE);
        ImGui::SetWindowCollapsed((const char *)name, (bool)collapsed, cond);
        if (name != NULL) env->ReleaseStringUTFChars(obj_name, name);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetWindowFocus__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_name) {

//@line:1559

        auto name = obj_name == NULL ? NULL : (char*)env->GetStringUTFChars(obj_name, JNI_FALSE);
        ImGui::SetWindowFocus(name);
        if (name != NULL) env->ReleaseStringUTFChars(obj_name, name);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetContentRegionAvail(JNIEnv* env, jclass clazz, jobject dst) {


//@line:1599

        Jni::ImVec2Cpy(env, ImGui::GetContentRegionAvail(), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetContentRegionAvailX(JNIEnv* env, jclass clazz) {


//@line:1603

        return ImGui::GetContentRegionAvail().x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetContentRegionAvailY(JNIEnv* env, jclass clazz) {


//@line:1607

        return ImGui::GetContentRegionAvail().y;
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetContentRegionMax(JNIEnv* env, jclass clazz, jobject dst) {


//@line:1641

        Jni::ImVec2Cpy(env, ImGui::GetContentRegionMax(), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetContentRegionMaxX(JNIEnv* env, jclass clazz) {


//@line:1645

        return ImGui::GetContentRegionMax().x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetContentRegionMaxY(JNIEnv* env, jclass clazz) {


//@line:1649

        return ImGui::GetContentRegionMax().y;
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetWindowContentRegionMin(JNIEnv* env, jclass clazz, jobject dst) {


//@line:1683

        Jni::ImVec2Cpy(env, ImGui::GetWindowContentRegionMin(), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetWindowContentRegionMinX(JNIEnv* env, jclass clazz) {


//@line:1687

        return ImGui::GetWindowContentRegionMin().x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetWindowContentRegionMinY(JNIEnv* env, jclass clazz) {


//@line:1691

        return ImGui::GetWindowContentRegionMin().y;
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetWindowContentRegionMax(JNIEnv* env, jclass clazz, jobject dst) {


//@line:1725

        Jni::ImVec2Cpy(env, ImGui::GetWindowContentRegionMax(), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetWindowContentRegionMaxX(JNIEnv* env, jclass clazz) {


//@line:1729

        return ImGui::GetWindowContentRegionMax().x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetWindowContentRegionMaxY(JNIEnv* env, jclass clazz) {


//@line:1733

        return ImGui::GetWindowContentRegionMax().y;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetScrollX(JNIEnv* env, jclass clazz) {


//@line:1748

        return ImGui::GetScrollX();
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetScrollY(JNIEnv* env, jclass clazz) {


//@line:1759

        return ImGui::GetScrollY();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetScrollX(JNIEnv* env, jclass clazz, jfloat scrollX) {


//@line:1770

        ImGui::SetScrollX(scrollX);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetScrollY(JNIEnv* env, jclass clazz, jfloat scrollY) {


//@line:1781

        ImGui::SetScrollY(scrollY);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetScrollMaxX(JNIEnv* env, jclass clazz) {


//@line:1792

        return ImGui::GetScrollMaxX();
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetScrollMaxY(JNIEnv* env, jclass clazz) {


//@line:1803

        return ImGui::GetScrollMaxY();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetScrollHereX__(JNIEnv* env, jclass clazz) {


//@line:1823

        ImGui::SetScrollHereX();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetScrollHereX__F(JNIEnv* env, jclass clazz, jfloat centerXRatio) {


//@line:1827

        ImGui::SetScrollHereX(centerXRatio);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetScrollHereY__(JNIEnv* env, jclass clazz) {


//@line:1847

        ImGui::SetScrollHereY();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetScrollHereY__F(JNIEnv* env, jclass clazz, jfloat centerYRatio) {


//@line:1851

        ImGui::SetScrollHereY(centerYRatio);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetScrollFromPosX__F(JNIEnv* env, jclass clazz, jfloat localX) {


//@line:1869

        ImGui::SetScrollFromPosX(localX);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetScrollFromPosX__FF(JNIEnv* env, jclass clazz, jfloat localX, jfloat centerXRatio) {


//@line:1873

        ImGui::SetScrollFromPosX(localX, centerXRatio);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetScrollFromPosY__F(JNIEnv* env, jclass clazz, jfloat localY) {


//@line:1891

        ImGui::SetScrollFromPosY(localY);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetScrollFromPosY__FF(JNIEnv* env, jclass clazz, jfloat localY, jfloat centerYRatio) {


//@line:1895

        ImGui::SetScrollFromPosY(localY, centerYRatio);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPushFont(JNIEnv* env, jclass clazz, jlong font, jfloat size) {


//@line:1910

        ImGui::PushFont(reinterpret_cast<ImFont*>(font), size);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPopFont(JNIEnv* env, jclass clazz) {


//@line:1918

        ImGui::PopFont();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_pushStyleColor(JNIEnv* env, jclass clazz, jint imGuiCol, jint r, jint g, jint b, jint a) {


//@line:1925

        ImGui::PushStyleColor(imGuiCol, (ImU32)ImColor((int)r, (int)g, (int)b, (int)a));
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPushStyleColor__IFFFF(JNIEnv* env, jclass clazz, jint imGuiCol, jfloat colX, jfloat colY, jfloat colZ, jfloat colW) {

//@line:1943

        ImVec4 col = ImVec4(colX, colY, colZ, colW);
        ImGui::PushStyleColor(imGuiCol, col);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPushStyleColor__II(JNIEnv* env, jclass clazz, jint imGuiCol, jint col) {


//@line:1955

        ImGui::PushStyleColor(imGuiCol, col);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPopStyleColor__(JNIEnv* env, jclass clazz) {


//@line:1967

        ImGui::PopStyleColor();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPopStyleColor__I(JNIEnv* env, jclass clazz, jint count) {


//@line:1971

        ImGui::PopStyleColor(count);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPushStyleVar__IF(JNIEnv* env, jclass clazz, jint imGuiStyleVar, jfloat val) {


//@line:1982

        ImGui::PushStyleVar(imGuiStyleVar, val);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPushStyleVar__IFF(JNIEnv* env, jclass clazz, jint imGuiStyleVar, jfloat valX, jfloat valY) {

//@line:2000

        ImVec2 val = ImVec2(valX, valY);
        ImGui::PushStyleVar(imGuiStyleVar, val);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPopStyleVar__(JNIEnv* env, jclass clazz) {


//@line:2013

        ImGui::PopStyleVar();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPopStyleVar__I(JNIEnv* env, jclass clazz, jint count) {


//@line:2017

        ImGui::PopStyleVar(count);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPushTabStop(JNIEnv* env, jclass clazz, jboolean tabStop) {


//@line:2028

        ImGui::PushTabStop(tabStop);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPopTabStop(JNIEnv* env, jclass clazz) {


//@line:2036

        ImGui::PopTabStop();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPushButtonRepeat(JNIEnv* env, jclass clazz, jboolean repeat) {


//@line:2048

        ImGui::PushButtonRepeat(repeat);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPopButtonRepeat(JNIEnv* env, jclass clazz) {


//@line:2056

        ImGui::PopButtonRepeat();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPushItemWidth(JNIEnv* env, jclass clazz, jfloat itemWidth) {


//@line:2070

        ImGui::PushItemWidth(itemWidth);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPopItemWidth(JNIEnv* env, jclass clazz) {


//@line:2078

        ImGui::PopItemWidth();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextItemWidth(JNIEnv* env, jclass clazz, jfloat itemWidth) {


//@line:2090

        ImGui::SetNextItemWidth(itemWidth);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nCalcItemWidth(JNIEnv* env, jclass clazz) {


//@line:2101

        return ImGui::CalcItemWidth();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPushTextWrapPos__(JNIEnv* env, jclass clazz) {


//@line:2121

        ImGui::PushTextWrapPos();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPushTextWrapPos__F(JNIEnv* env, jclass clazz, jfloat wrapLocalPosX) {


//@line:2125

        ImGui::PushTextWrapPos(wrapLocalPosX);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPopTextWrapPos(JNIEnv* env, jclass clazz) {


//@line:2133

        ImGui::PopTextWrapPos();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nGetFont(JNIEnv* env, jclass clazz) {


//@line:2150

        return (uintptr_t)ImGui::GetFont();
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nGetFontSize(JNIEnv* env, jclass clazz) {


//@line:2161

        return ImGui::GetFontSize();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetFontTexUvWhitePixel(JNIEnv* env, jclass clazz, jobject dst) {


//@line:2195

        Jni::ImVec2Cpy(env, ImGui::GetFontTexUvWhitePixel(), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetFontTexUvWhitePixelX(JNIEnv* env, jclass clazz) {


//@line:2199

        return ImGui::GetFontTexUvWhitePixel().x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetFontTexUvWhitePixelY(JNIEnv* env, jclass clazz) {


//@line:2203

        return ImGui::GetFontTexUvWhitePixel().y;
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nGetColorU32__I(JNIEnv* env, jclass clazz, jint idx) {


//@line:2221

        return ImGui::GetColorU32(static_cast<ImGuiCol>(idx));
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nGetColorU32__IF(JNIEnv* env, jclass clazz, jint idx, jfloat alphaMul) {


//@line:2225

        return ImGui::GetColorU32(static_cast<ImGuiCol>(idx), alphaMul);
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nGetColorU32__FFFF(JNIEnv* env, jclass clazz, jfloat colX, jfloat colY, jfloat colZ, jfloat colW) {

//@line:2243

        ImVec4 col = ImVec4(colX, colY, colZ, colW);
        auto _result = ImGui::GetColorU32(col);
        return _result;
    
}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nGetColorU32i__I(JNIEnv* env, jclass clazz, jint col) {


//@line:2263

        return ImGui::GetColorU32(static_cast<ImU32>(col));
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nGetColorU32i__IF(JNIEnv* env, jclass clazz, jint col, jfloat alphaMul) {


//@line:2267

        return ImGui::GetColorU32(static_cast<ImU32>(col), alphaMul);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetStyleColorVec4(JNIEnv* env, jclass clazz, jobject dst, jint imGuiColIdx) {


//@line:2321

        Jni::ImVec4Cpy(env, ImGui::GetStyleColorVec4(imGuiColIdx), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetStyleColorVec4X(JNIEnv* env, jclass clazz, jint imGuiColIdx) {


//@line:2325

        return ImGui::GetStyleColorVec4(imGuiColIdx).x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetStyleColorVec4Y(JNIEnv* env, jclass clazz, jint imGuiColIdx) {


//@line:2329

        return ImGui::GetStyleColorVec4(imGuiColIdx).y;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetStyleColorVec4Z(JNIEnv* env, jclass clazz, jint imGuiColIdx) {


//@line:2333

        return ImGui::GetStyleColorVec4(imGuiColIdx).z;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetStyleColorVec4W(JNIEnv* env, jclass clazz, jint imGuiColIdx) {


//@line:2337

        return ImGui::GetStyleColorVec4(imGuiColIdx).w;
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetCursorScreenPos(JNIEnv* env, jclass clazz, jobject dst) {


//@line:2380

        Jni::ImVec2Cpy(env, ImGui::GetCursorScreenPos(), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetCursorScreenPosX(JNIEnv* env, jclass clazz) {


//@line:2384

        return ImGui::GetCursorScreenPos().x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetCursorScreenPosY(JNIEnv* env, jclass clazz) {


//@line:2388

        return ImGui::GetCursorScreenPos().y;
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetCursorScreenPos(JNIEnv* env, jclass clazz, jfloat posX, jfloat posY) {

//@line:2406

        ImVec2 pos = ImVec2(posX, posY);
        ImGui::SetCursorScreenPos(pos);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetCursorPos(JNIEnv* env, jclass clazz, jobject dst) {


//@line:2441

        Jni::ImVec2Cpy(env, ImGui::GetCursorPos(), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetCursorPosX(JNIEnv* env, jclass clazz) {


//@line:2445

        return ImGui::GetCursorPos().x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetCursorPosY(JNIEnv* env, jclass clazz) {


//@line:2449

        return ImGui::GetCursorPos().y;
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetCursorPos(JNIEnv* env, jclass clazz, jfloat localPosX, jfloat localPosY) {

//@line:2467

        ImVec2 localPos = ImVec2(localPosX, localPosY);
        ImGui::SetCursorPos(localPos);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetCursorPosX(JNIEnv* env, jclass clazz, jfloat localX) {


//@line:2479

        ImGui::SetCursorPosX(localX);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetCursorPosY(JNIEnv* env, jclass clazz, jfloat localY) {


//@line:2490

        ImGui::SetCursorPosY(localY);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetCursorStartPos(JNIEnv* env, jclass clazz, jobject dst) {


//@line:2524

        Jni::ImVec2Cpy(env, ImGui::GetCursorStartPos(), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetCursorStartPosX(JNIEnv* env, jclass clazz) {


//@line:2528

        return ImGui::GetCursorStartPos().x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetCursorStartPosY(JNIEnv* env, jclass clazz) {


//@line:2532

        return ImGui::GetCursorStartPos().y;
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSeparator(JNIEnv* env, jclass clazz) {


//@line:2545

        ImGui::Separator();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSameLine__(JNIEnv* env, jclass clazz) {


//@line:2570

        ImGui::SameLine();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSameLine__F(JNIEnv* env, jclass clazz, jfloat offsetFromStartX) {


//@line:2574

        ImGui::SameLine(offsetFromStartX);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSameLine__FF(JNIEnv* env, jclass clazz, jfloat offsetFromStartX, jfloat spacing) {


//@line:2578

        ImGui::SameLine(offsetFromStartX, spacing);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nNewLine(JNIEnv* env, jclass clazz) {


//@line:2589

        ImGui::NewLine();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSpacing(JNIEnv* env, jclass clazz) {


//@line:2600

        ImGui::Spacing();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nDummy(JNIEnv* env, jclass clazz, jfloat sizeX, jfloat sizeY) {

//@line:2618

        ImVec2 size = ImVec2(sizeX, sizeY);
        ImGui::Dummy(size);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nIndent__(JNIEnv* env, jclass clazz) {


//@line:2637

        ImGui::Indent();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nIndent__F(JNIEnv* env, jclass clazz, jfloat indentW) {


//@line:2641

        ImGui::Indent(indentW);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nUnindent__(JNIEnv* env, jclass clazz) {


//@line:2659

        ImGui::Unindent();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nUnindent__F(JNIEnv* env, jclass clazz, jfloat indentW) {


//@line:2663

        ImGui::Unindent(indentW);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nBeginGroup(JNIEnv* env, jclass clazz) {


//@line:2674

        ImGui::BeginGroup();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nEndGroup(JNIEnv* env, jclass clazz) {


//@line:2685

        ImGui::EndGroup();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nAlignTextToFramePadding(JNIEnv* env, jclass clazz) {


//@line:2701

        ImGui::AlignTextToFramePadding();
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetTextLineHeight(JNIEnv* env, jclass clazz) {


//@line:2712

        return ImGui::GetTextLineHeight();
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetTextLineHeightWithSpacing(JNIEnv* env, jclass clazz) {


//@line:2723

        return ImGui::GetTextLineHeightWithSpacing();
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetFrameHeight(JNIEnv* env, jclass clazz) {


//@line:2734

        return ImGui::GetFrameHeight();
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetFrameHeightWithSpacing(JNIEnv* env, jclass clazz) {


//@line:2745

        return ImGui::GetFrameHeightWithSpacing();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPushID__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_strId) {

//@line:2768

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImGui::PushID(strId);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPushID__Ljava_lang_String_2Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_strIdBegin, jstring obj_strIdEnd) {

//@line:2781

        auto strIdBegin = obj_strIdBegin == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strIdBegin, JNI_FALSE);
        auto strIdEnd = obj_strIdEnd == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strIdEnd, JNI_FALSE);
        ImGui::PushID(strIdBegin, strIdEnd);
        if (strIdBegin != NULL) env->ReleaseStringUTFChars(obj_strIdBegin, strIdBegin);
        if (strIdEnd != NULL) env->ReleaseStringUTFChars(obj_strIdEnd, strIdEnd);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPushID__J(JNIEnv* env, jclass clazz, jlong ptrId) {


//@line:2796

        ImGui::PushID((void*)ptrId);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPushID__I(JNIEnv* env, jclass clazz, jint intId) {


//@line:2807

        ImGui::PushID(intId);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPopID(JNIEnv* env, jclass clazz) {


//@line:2818

        ImGui::PopID();
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nGetID__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_strId) {

//@line:2829

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto _result = ImGui::GetID(strId);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nGetID__Ljava_lang_String_2Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_strIdBegin, jstring obj_strIdEnd) {

//@line:2843

        auto strIdBegin = obj_strIdBegin == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strIdBegin, JNI_FALSE);
        auto strIdEnd = obj_strIdEnd == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strIdEnd, JNI_FALSE);
        auto _result = ImGui::GetID(strIdBegin, strIdEnd);
        if (strIdBegin != NULL) env->ReleaseStringUTFChars(obj_strIdBegin, strIdBegin);
        if (strIdEnd != NULL) env->ReleaseStringUTFChars(obj_strIdEnd, strIdEnd);
        return _result;
    
}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nGetID__J(JNIEnv* env, jclass clazz, jlong ptrId) {


//@line:2859

        return ImGui::GetID((void*)ptrId);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTextUnformatted__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_text) {

//@line:2883

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        ImGui::TextUnformatted(text);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTextUnformatted__Ljava_lang_String_2Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_text, jstring obj_textEnd) {

//@line:2889

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        auto textEnd = obj_textEnd == NULL ? NULL : (char*)env->GetStringUTFChars(obj_textEnd, JNI_FALSE);
        ImGui::TextUnformatted(text, textEnd);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
        if (textEnd != NULL) env->ReleaseStringUTFChars(obj_textEnd, textEnd);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nText(JNIEnv* env, jclass clazz, jstring obj_text) {

//@line:2904

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        ImGui::Text(text, NULL);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTextColored(JNIEnv* env, jclass clazz, jfloat colX, jfloat colY, jfloat colZ, jfloat colW, jstring obj_text) {

//@line:2924

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        ImVec4 col = ImVec4(colX, colY, colZ, colW);
        ImGui::TextColored(col, text, NULL);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_textColored__IIIILjava_lang_String_2(JNIEnv* env, jclass clazz, jint r, jint g, jint b, jint a, jstring obj_text) {
	char* text = (char*)env->GetStringUTFChars(obj_text, 0);


//@line:2934

        ImGui::TextColored(ImColor((int)r, (int)g, (int)b, (int)a), text, NULL);
    
	env->ReleaseStringUTFChars(obj_text, text);

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_textColored__ILjava_lang_String_2(JNIEnv* env, jclass clazz, jint col, jstring obj_text) {
	char* text = (char*)env->GetStringUTFChars(obj_text, 0);


//@line:2941

        ImGui::TextColored(ImColor(col), text, NULL);
    
	env->ReleaseStringUTFChars(obj_text, text);

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTextDisabled(JNIEnv* env, jclass clazz, jstring obj_text) {

//@line:2952

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        ImGui::TextDisabled(text, NULL);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTextWrapped(JNIEnv* env, jclass clazz, jstring obj_text) {

//@line:2967

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        ImGui::TextWrapped(text, NULL);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nLabelText(JNIEnv* env, jclass clazz, jstring obj_label, jstring obj_text) {

//@line:2980

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        ImGui::LabelText(label, text, NULL);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nBulletText(JNIEnv* env, jclass clazz, jstring obj_text) {

//@line:2995

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        ImGui::BulletText(text, NULL);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nTextLink(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:3008

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::TextLink(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nTextLinkOpenURL__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:3031

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::TextLinkOpenURL(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nTextLinkOpenURL__Ljava_lang_String_2Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jstring obj_url) {

//@line:3038

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto url = obj_url == NULL ? NULL : (char*)env->GetStringUTFChars(obj_url, JNI_FALSE);
        auto _result = ImGui::TextLinkOpenURL(label, url);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (url != NULL) env->ReleaseStringUTFChars(obj_url, url);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSeparatorText(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:3054

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        ImGui::SeparatorText(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nButton__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:3085

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::Button(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nButton__Ljava_lang_String_2FF(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY) {

//@line:3092

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::Button(label, size);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSmallButton(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:3107

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::SmallButton(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInvisibleButton__Ljava_lang_String_2FF(JNIEnv* env, jclass clazz, jstring obj_strId, jfloat sizeX, jfloat sizeY) {

//@line:3142

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::InvisibleButton(strId, size);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInvisibleButton__Ljava_lang_String_2FFI(JNIEnv* env, jclass clazz, jstring obj_strId, jfloat sizeX, jfloat sizeY, jint imGuiButtonFlags) {

//@line:3150

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::InvisibleButton(strId, size, imGuiButtonFlags);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nArrowButton(JNIEnv* env, jclass clazz, jstring obj_strId, jint dir) {

//@line:3165

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto _result = ImGui::ArrowButton(strId, static_cast<ImGuiDir>(dir));
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

static inline jboolean wrapped_Java_imgui_moulberry92_ImGui_nCheckbox__Ljava_lang_String_2Z
(JNIEnv* env, jclass clazz, jstring obj_label, jboolean active, char* label) {

//@line:3176

        bool flag = (bool)active;
        return ImGui::Checkbox(label, &flag);
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nCheckbox__Ljava_lang_String_2Z(JNIEnv* env, jclass clazz, jstring obj_label, jboolean active) {
	char* label = (char*)env->GetStringUTFChars(obj_label, 0);

	jboolean JNI_returnValue = wrapped_Java_imgui_moulberry92_ImGui_nCheckbox__Ljava_lang_String_2Z(env, clazz, obj_label, active, label);

	env->ReleaseStringUTFChars(obj_label, label);

	return JNI_returnValue;
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nCheckbox__Ljava_lang_String_2_3Z(JNIEnv* env, jclass clazz, jstring obj_label, jbooleanArray obj_data) {

//@line:3185

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto data = obj_data == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_data, JNI_FALSE);
        auto _result = ImGui::Checkbox(label, (data != NULL ? &data[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (data != NULL) env->ReleasePrimitiveArrayCritical(obj_data, data, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nCheckboxFlags(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_flags, jint flagsValue) {

//@line:3198

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto flags = obj_flags == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_flags, JNI_FALSE);
        auto _result = ImGui::CheckboxFlags(label, (flags != NULL ? &flags[0] : NULL), flagsValue);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (flags != NULL) env->ReleasePrimitiveArrayCritical(obj_flags, flags, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nRadioButton__Ljava_lang_String_2Z(JNIEnv* env, jclass clazz, jstring obj_label, jboolean active) {

//@line:3214

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::RadioButton(label, active);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nRadioButton__Ljava_lang_String_2_3II(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint vButton) {

//@line:3228

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::RadioButton(label, (v != NULL ? &v[0] : NULL), vButton);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nProgressBar__F(JNIEnv* env, jclass clazz, jfloat fraction) {


//@line:3261

        ImGui::ProgressBar(fraction);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nProgressBar__FFF(JNIEnv* env, jclass clazz, jfloat fraction, jfloat sizeX, jfloat sizeY) {

//@line:3265

        ImVec2 size = ImVec2(sizeX, sizeY);
        ImGui::ProgressBar(fraction, size);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nProgressBar__FFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jfloat fraction, jfloat sizeX, jfloat sizeY, jstring obj_overlay) {

//@line:3270

        auto overlay = obj_overlay == NULL ? NULL : (char*)env->GetStringUTFChars(obj_overlay, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        ImGui::ProgressBar(fraction, size, overlay);
        if (overlay != NULL) env->ReleaseStringUTFChars(obj_overlay, overlay);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nProgressBar__FLjava_lang_String_2(JNIEnv* env, jclass clazz, jfloat fraction, jstring obj_overlay) {

//@line:3277

        auto overlay = obj_overlay == NULL ? NULL : (char*)env->GetStringUTFChars(obj_overlay, JNI_FALSE);
        ImGui::ProgressBar(fraction, ImVec2(-FLT_MIN,0), overlay);
        if (overlay != NULL) env->ReleaseStringUTFChars(obj_overlay, overlay);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nBullet(JNIEnv* env, jclass clazz) {


//@line:3290

        ImGui::Bullet();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nImage__JFF(JNIEnv* env, jclass clazz, jlong userTextureId, jfloat imageSizeX, jfloat imageSizeY) {

//@line:3323

        ImVec2 imageSize = ImVec2(imageSizeX, imageSizeY);
        ImGui::Image((ImTextureID)(uintptr_t)userTextureId, imageSize);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nImage__JFFFF(JNIEnv* env, jclass clazz, jlong userTextureId, jfloat imageSizeX, jfloat imageSizeY, jfloat uv0X, jfloat uv0Y) {

//@line:3328

        ImVec2 imageSize = ImVec2(imageSizeX, imageSizeY);
        ImVec2 uv0 = ImVec2(uv0X, uv0Y);
        ImGui::Image((ImTextureID)(uintptr_t)userTextureId, imageSize, uv0);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nImage__JFFFFFF(JNIEnv* env, jclass clazz, jlong userTextureId, jfloat imageSizeX, jfloat imageSizeY, jfloat uv0X, jfloat uv0Y, jfloat uv1X, jfloat uv1Y) {

//@line:3334

        ImVec2 imageSize = ImVec2(imageSizeX, imageSizeY);
        ImVec2 uv0 = ImVec2(uv0X, uv0Y);
        ImVec2 uv1 = ImVec2(uv1X, uv1Y);
        ImGui::Image((ImTextureID)(uintptr_t)userTextureId, imageSize, uv0, uv1);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nImageWithBg__JFF(JNIEnv* env, jclass clazz, jlong userTextureId, jfloat imageSizeX, jfloat imageSizeY) {

//@line:3381

        ImVec2 imageSize = ImVec2(imageSizeX, imageSizeY);
        ImGui::ImageWithBg((ImTextureID)(uintptr_t)userTextureId, imageSize);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nImageWithBg__JFFFF(JNIEnv* env, jclass clazz, jlong userTextureId, jfloat imageSizeX, jfloat imageSizeY, jfloat uv0X, jfloat uv0Y) {

//@line:3386

        ImVec2 imageSize = ImVec2(imageSizeX, imageSizeY);
        ImVec2 uv0 = ImVec2(uv0X, uv0Y);
        ImGui::ImageWithBg((ImTextureID)(uintptr_t)userTextureId, imageSize, uv0);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nImageWithBg__JFFFFFF(JNIEnv* env, jclass clazz, jlong userTextureId, jfloat imageSizeX, jfloat imageSizeY, jfloat uv0X, jfloat uv0Y, jfloat uv1X, jfloat uv1Y) {

//@line:3392

        ImVec2 imageSize = ImVec2(imageSizeX, imageSizeY);
        ImVec2 uv0 = ImVec2(uv0X, uv0Y);
        ImVec2 uv1 = ImVec2(uv1X, uv1Y);
        ImGui::ImageWithBg((ImTextureID)(uintptr_t)userTextureId, imageSize, uv0, uv1);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nImageWithBg__JFFFFFFFFFF(JNIEnv* env, jclass clazz, jlong userTextureId, jfloat imageSizeX, jfloat imageSizeY, jfloat uv0X, jfloat uv0Y, jfloat uv1X, jfloat uv1Y, jfloat bgColX, jfloat bgColY, jfloat bgColZ, jfloat bgColW) {

//@line:3399

        ImVec2 imageSize = ImVec2(imageSizeX, imageSizeY);
        ImVec2 uv0 = ImVec2(uv0X, uv0Y);
        ImVec2 uv1 = ImVec2(uv1X, uv1Y);
        ImVec4 bgCol = ImVec4(bgColX, bgColY, bgColZ, bgColW);
        ImGui::ImageWithBg((ImTextureID)(uintptr_t)userTextureId, imageSize, uv0, uv1, bgCol);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nImageWithBg__JFFFFFFFFFFFFFF(JNIEnv* env, jclass clazz, jlong userTextureId, jfloat imageSizeX, jfloat imageSizeY, jfloat uv0X, jfloat uv0Y, jfloat uv1X, jfloat uv1Y, jfloat bgColX, jfloat bgColY, jfloat bgColZ, jfloat bgColW, jfloat tintColX, jfloat tintColY, jfloat tintColZ, jfloat tintColW) {

//@line:3407

        ImVec2 imageSize = ImVec2(imageSizeX, imageSizeY);
        ImVec2 uv0 = ImVec2(uv0X, uv0Y);
        ImVec2 uv1 = ImVec2(uv1X, uv1Y);
        ImVec4 bgCol = ImVec4(bgColX, bgColY, bgColZ, bgColW);
        ImVec4 tintCol = ImVec4(tintColX, tintColY, tintColZ, tintColW);
        ImGui::ImageWithBg((ImTextureID)(uintptr_t)userTextureId, imageSize, uv0, uv1, bgCol, tintCol);
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nImageButton__Ljava_lang_String_2JFF(JNIEnv* env, jclass clazz, jstring obj_strId, jlong userTextureId, jfloat imageSizeX, jfloat imageSizeY) {

//@line:3456

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImVec2 imageSize = ImVec2(imageSizeX, imageSizeY);
        auto _result = ImGui::ImageButton(strId, (ImTextureID)(uintptr_t)userTextureId, imageSize);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nImageButton__Ljava_lang_String_2JFFFF(JNIEnv* env, jclass clazz, jstring obj_strId, jlong userTextureId, jfloat imageSizeX, jfloat imageSizeY, jfloat uv0X, jfloat uv0Y) {

//@line:3464

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImVec2 imageSize = ImVec2(imageSizeX, imageSizeY);
        ImVec2 uv0 = ImVec2(uv0X, uv0Y);
        auto _result = ImGui::ImageButton(strId, (ImTextureID)(uintptr_t)userTextureId, imageSize, uv0);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nImageButton__Ljava_lang_String_2JFFFFFF(JNIEnv* env, jclass clazz, jstring obj_strId, jlong userTextureId, jfloat imageSizeX, jfloat imageSizeY, jfloat uv0X, jfloat uv0Y, jfloat uv1X, jfloat uv1Y) {

//@line:3473

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImVec2 imageSize = ImVec2(imageSizeX, imageSizeY);
        ImVec2 uv0 = ImVec2(uv0X, uv0Y);
        ImVec2 uv1 = ImVec2(uv1X, uv1Y);
        auto _result = ImGui::ImageButton(strId, (ImTextureID)(uintptr_t)userTextureId, imageSize, uv0, uv1);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nImageButton__Ljava_lang_String_2JFFFFFFFFFF(JNIEnv* env, jclass clazz, jstring obj_strId, jlong userTextureId, jfloat imageSizeX, jfloat imageSizeY, jfloat uv0X, jfloat uv0Y, jfloat uv1X, jfloat uv1Y, jfloat bgColX, jfloat bgColY, jfloat bgColZ, jfloat bgColW) {

//@line:3483

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImVec2 imageSize = ImVec2(imageSizeX, imageSizeY);
        ImVec2 uv0 = ImVec2(uv0X, uv0Y);
        ImVec2 uv1 = ImVec2(uv1X, uv1Y);
        ImVec4 bgCol = ImVec4(bgColX, bgColY, bgColZ, bgColW);
        auto _result = ImGui::ImageButton(strId, (ImTextureID)(uintptr_t)userTextureId, imageSize, uv0, uv1, bgCol);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nImageButton__Ljava_lang_String_2JFFFFFFFFFFFFFF(JNIEnv* env, jclass clazz, jstring obj_strId, jlong userTextureId, jfloat imageSizeX, jfloat imageSizeY, jfloat uv0X, jfloat uv0Y, jfloat uv1X, jfloat uv1Y, jfloat bgColX, jfloat bgColY, jfloat bgColZ, jfloat bgColW, jfloat tintColX, jfloat tintColY, jfloat tintColZ, jfloat tintColW) {

//@line:3494

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImVec2 imageSize = ImVec2(imageSizeX, imageSizeY);
        ImVec2 uv0 = ImVec2(uv0X, uv0Y);
        ImVec2 uv1 = ImVec2(uv1X, uv1Y);
        ImVec4 bgCol = ImVec4(bgColX, bgColY, bgColZ, bgColW);
        ImVec4 tintCol = ImVec4(tintColX, tintColY, tintColZ, tintColW);
        auto _result = ImGui::ImageButton(strId, (ImTextureID)(uintptr_t)userTextureId, imageSize, uv0, uv1, bgCol, tintCol);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginCombo__Ljava_lang_String_2Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jstring obj_previewValue) {

//@line:3519

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto previewValue = obj_previewValue == NULL ? NULL : (char*)env->GetStringUTFChars(obj_previewValue, JNI_FALSE);
        auto _result = ImGui::BeginCombo(label, previewValue);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (previewValue != NULL) env->ReleaseStringUTFChars(obj_previewValue, previewValue);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginCombo__Ljava_lang_String_2Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jstring obj_previewValue, jint imGuiComboFlags) {

//@line:3528

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto previewValue = obj_previewValue == NULL ? NULL : (char*)env->GetStringUTFChars(obj_previewValue, JNI_FALSE);
        auto _result = ImGui::BeginCombo(label, previewValue, imGuiComboFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (previewValue != NULL) env->ReleaseStringUTFChars(obj_previewValue, previewValue);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nEndCombo(JNIEnv* env, jclass clazz) {


//@line:3544

        ImGui::EndCombo();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nCombo__Ljava_lang_String_2_3I_3Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_currentItem, jobjectArray obj_items, jint itemsCount) {

//@line:3556

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto currentItem = obj_currentItem == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_currentItem, JNI_FALSE);
        const char* items[itemsCount];
        for (int i = 0; i < itemsCount; i++) {
            const jstring str = (jstring)env->GetObjectArrayElement(obj_items, i);
            auto rawStr = (char*)env->GetStringUTFChars(str, JNI_FALSE);
            items[i] = rawStr;
        };
        auto _result = ImGui::Combo(label, (currentItem != NULL ? &currentItem[0] : NULL), items, itemsCount);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (currentItem != NULL) env->ReleasePrimitiveArrayCritical(obj_currentItem, currentItem, JNI_FALSE);
        for (int i = 0; i < itemsCount; i++) {
            const jstring str = (jstring)env->GetObjectArrayElement(obj_items, i);
            env->ReleaseStringUTFChars(str, items[i]);
        };
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nCombo__Ljava_lang_String_2_3I_3Ljava_lang_String_2II(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_currentItem, jobjectArray obj_items, jint itemsCount, jint popupMaxHeightInItems) {

//@line:3575

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto currentItem = obj_currentItem == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_currentItem, JNI_FALSE);
        const char* items[itemsCount];
        for (int i = 0; i < itemsCount; i++) {
            const jstring str = (jstring)env->GetObjectArrayElement(obj_items, i);
            auto rawStr = (char*)env->GetStringUTFChars(str, JNI_FALSE);
            items[i] = rawStr;
        };
        auto _result = ImGui::Combo(label, (currentItem != NULL ? &currentItem[0] : NULL), items, itemsCount, popupMaxHeightInItems);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (currentItem != NULL) env->ReleasePrimitiveArrayCritical(obj_currentItem, currentItem, JNI_FALSE);
        for (int i = 0; i < itemsCount; i++) {
            const jstring str = (jstring)env->GetObjectArrayElement(obj_items, i);
            env->ReleaseStringUTFChars(str, items[i]);
        };
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nCombo__Ljava_lang_String_2_3ILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_currentItem, jstring obj_itemsSeparatedByZeros) {

//@line:3608

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto currentItem = obj_currentItem == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_currentItem, JNI_FALSE);
        auto itemsSeparatedByZeros = obj_itemsSeparatedByZeros == NULL ? NULL : (char*)env->GetStringUTFChars(obj_itemsSeparatedByZeros, JNI_FALSE);
        auto _result = ImGui::Combo(label, (currentItem != NULL ? &currentItem[0] : NULL), itemsSeparatedByZeros);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (currentItem != NULL) env->ReleasePrimitiveArrayCritical(obj_currentItem, currentItem, JNI_FALSE);
        if (itemsSeparatedByZeros != NULL) env->ReleaseStringUTFChars(obj_itemsSeparatedByZeros, itemsSeparatedByZeros);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nCombo__Ljava_lang_String_2_3ILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_currentItem, jstring obj_itemsSeparatedByZeros, jint popupMaxHeightInItems) {

//@line:3619

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto currentItem = obj_currentItem == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_currentItem, JNI_FALSE);
        auto itemsSeparatedByZeros = obj_itemsSeparatedByZeros == NULL ? NULL : (char*)env->GetStringUTFChars(obj_itemsSeparatedByZeros, JNI_FALSE);
        auto _result = ImGui::Combo(label, (currentItem != NULL ? &currentItem[0] : NULL), itemsSeparatedByZeros, popupMaxHeightInItems);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (currentItem != NULL) env->ReleasePrimitiveArrayCritical(obj_currentItem, currentItem, JNI_FALSE);
        if (itemsSeparatedByZeros != NULL) env->ReleaseStringUTFChars(obj_itemsSeparatedByZeros, itemsSeparatedByZeros);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat__Ljava_lang_String_2_3F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v) {

//@line:3692

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat(label, &v[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat__Ljava_lang_String_2_3FF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed) {

//@line:3701

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat(label, &v[0], vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat__Ljava_lang_String_2_3FFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin) {

//@line:3710

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat(label, &v[0], vSpeed, vMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat__Ljava_lang_String_2_3FFFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin, jfloat vMax) {

//@line:3719

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat(label, &v[0], vSpeed, vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat__Ljava_lang_String_2_3FFFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin, jfloat vMax, jstring obj_format) {

//@line:3728

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragFloat(label, &v[0], vSpeed, vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat__Ljava_lang_String_2_3FFFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin, jfloat vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:3739

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragFloat(label, &v[0], vSpeed, vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat__Ljava_lang_String_2_3FFFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin, jfloat vMax, jint imGuiSliderFlags) {

//@line:3750

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat(label, &v[0], vSpeed, vMin, vMax, "%.3f", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat2__Ljava_lang_String_2_3F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v) {

//@line:3787

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat2(label, &v[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat2__Ljava_lang_String_2_3FF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed) {

//@line:3796

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat2(label, &v[0], vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat2__Ljava_lang_String_2_3FFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin) {

//@line:3805

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat2(label, &v[0], vSpeed, vMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat2__Ljava_lang_String_2_3FFFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin, jfloat vMax) {

//@line:3814

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat2(label, &v[0], vSpeed, vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat2__Ljava_lang_String_2_3FFFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin, jfloat vMax, jstring obj_format) {

//@line:3823

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragFloat2(label, &v[0], vSpeed, vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat2__Ljava_lang_String_2_3FFFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin, jfloat vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:3834

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragFloat2(label, &v[0], vSpeed, vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat2__Ljava_lang_String_2_3FFFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin, jfloat vMax, jint imGuiSliderFlags) {

//@line:3845

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat2(label, &v[0], vSpeed, vMin, vMax, "%.3f", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat3__Ljava_lang_String_2_3F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v) {

//@line:3882

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat3(label, &v[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat3__Ljava_lang_String_2_3FF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed) {

//@line:3891

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat3(label, &v[0], vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat3__Ljava_lang_String_2_3FFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin) {

//@line:3900

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat3(label, &v[0], vSpeed, vMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat3__Ljava_lang_String_2_3FFFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin, jfloat vMax) {

//@line:3909

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat3(label, &v[0], vSpeed, vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat3__Ljava_lang_String_2_3FFFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin, jfloat vMax, jstring obj_format) {

//@line:3918

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragFloat3(label, &v[0], vSpeed, vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat3__Ljava_lang_String_2_3FFFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin, jfloat vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:3929

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragFloat3(label, &v[0], vSpeed, vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat3__Ljava_lang_String_2_3FFFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin, jfloat vMax, jint imGuiSliderFlags) {

//@line:3940

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat3(label, &v[0], vSpeed, vMin, vMax, "%.3f", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat4__Ljava_lang_String_2_3F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v) {

//@line:3977

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat4(label, &v[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat4__Ljava_lang_String_2_3FF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed) {

//@line:3986

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat4(label, &v[0], vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat4__Ljava_lang_String_2_3FFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin) {

//@line:3995

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat4(label, &v[0], vSpeed, vMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat4__Ljava_lang_String_2_3FFFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin, jfloat vMax) {

//@line:4004

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat4(label, &v[0], vSpeed, vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat4__Ljava_lang_String_2_3FFFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin, jfloat vMax, jstring obj_format) {

//@line:4013

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragFloat4(label, &v[0], vSpeed, vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat4__Ljava_lang_String_2_3FFFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin, jfloat vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:4024

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragFloat4(label, &v[0], vSpeed, vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloat4__Ljava_lang_String_2_3FFFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vSpeed, jfloat vMin, jfloat vMax, jint imGuiSliderFlags) {

//@line:4035

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragFloat4(label, &v[0], vSpeed, vMin, vMax, "%.3f", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloatRange2__Ljava_lang_String_2_3F_3FF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_vCurrentMin, jfloatArray obj_vCurrentMax, jfloat vSpeed) {

//@line:4068

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vCurrentMin = obj_vCurrentMin == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vCurrentMin, JNI_FALSE);
        auto vCurrentMax = obj_vCurrentMax == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vCurrentMax, JNI_FALSE);
        auto _result = ImGui::DragFloatRange2(label, &vCurrentMin[0], &vCurrentMax[0], vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vCurrentMin != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMin, vCurrentMin, JNI_FALSE);
        if (vCurrentMax != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMax, vCurrentMax, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloatRange2__Ljava_lang_String_2_3F_3FFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_vCurrentMin, jfloatArray obj_vCurrentMax, jfloat vSpeed, jfloat vMin) {

//@line:4079

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vCurrentMin = obj_vCurrentMin == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vCurrentMin, JNI_FALSE);
        auto vCurrentMax = obj_vCurrentMax == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vCurrentMax, JNI_FALSE);
        auto _result = ImGui::DragFloatRange2(label, &vCurrentMin[0], &vCurrentMax[0], vSpeed, vMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vCurrentMin != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMin, vCurrentMin, JNI_FALSE);
        if (vCurrentMax != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMax, vCurrentMax, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloatRange2__Ljava_lang_String_2_3F_3FFFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_vCurrentMin, jfloatArray obj_vCurrentMax, jfloat vSpeed, jfloat vMin, jfloat vMax) {

//@line:4090

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vCurrentMin = obj_vCurrentMin == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vCurrentMin, JNI_FALSE);
        auto vCurrentMax = obj_vCurrentMax == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vCurrentMax, JNI_FALSE);
        auto _result = ImGui::DragFloatRange2(label, &vCurrentMin[0], &vCurrentMax[0], vSpeed, vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vCurrentMin != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMin, vCurrentMin, JNI_FALSE);
        if (vCurrentMax != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMax, vCurrentMax, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloatRange2__Ljava_lang_String_2_3F_3FFFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_vCurrentMin, jfloatArray obj_vCurrentMax, jfloat vSpeed, jfloat vMin, jfloat vMax, jstring obj_format) {

//@line:4101

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vCurrentMin = obj_vCurrentMin == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vCurrentMin, JNI_FALSE);
        auto vCurrentMax = obj_vCurrentMax == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vCurrentMax, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragFloatRange2(label, &vCurrentMin[0], &vCurrentMax[0], vSpeed, vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vCurrentMin != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMin, vCurrentMin, JNI_FALSE);
        if (vCurrentMax != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMax, vCurrentMax, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloatRange2__Ljava_lang_String_2_3F_3FFFFLjava_lang_String_2Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_vCurrentMin, jfloatArray obj_vCurrentMax, jfloat vSpeed, jfloat vMin, jfloat vMax, jstring obj_format, jstring obj_formatMax) {

//@line:4114

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vCurrentMin = obj_vCurrentMin == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vCurrentMin, JNI_FALSE);
        auto vCurrentMax = obj_vCurrentMax == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vCurrentMax, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto formatMax = obj_formatMax == NULL ? NULL : (char*)env->GetStringUTFChars(obj_formatMax, JNI_FALSE);
        auto _result = ImGui::DragFloatRange2(label, &vCurrentMin[0], &vCurrentMax[0], vSpeed, vMin, vMax, format, formatMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vCurrentMin != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMin, vCurrentMin, JNI_FALSE);
        if (vCurrentMax != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMax, vCurrentMax, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        if (formatMax != NULL) env->ReleaseStringUTFChars(obj_formatMax, formatMax);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragFloatRange2__Ljava_lang_String_2_3F_3FFFFLjava_lang_String_2Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_vCurrentMin, jfloatArray obj_vCurrentMax, jfloat vSpeed, jfloat vMin, jfloat vMax, jstring obj_format, jstring obj_formatMax, jint imGuiSliderFlags) {

//@line:4129

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vCurrentMin = obj_vCurrentMin == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vCurrentMin, JNI_FALSE);
        auto vCurrentMax = obj_vCurrentMax == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vCurrentMax, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto formatMax = obj_formatMax == NULL ? NULL : (char*)env->GetStringUTFChars(obj_formatMax, JNI_FALSE);
        auto _result = ImGui::DragFloatRange2(label, &vCurrentMin[0], &vCurrentMax[0], vSpeed, vMin, vMax, format, formatMax, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vCurrentMin != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMin, vCurrentMin, JNI_FALSE);
        if (vCurrentMax != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMax, vCurrentMax, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        if (formatMax != NULL) env->ReleaseStringUTFChars(obj_formatMax, formatMax);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt__Ljava_lang_String_2_3I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v) {

//@line:4193

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt(label, &v[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt__Ljava_lang_String_2_3IF(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed) {

//@line:4202

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt(label, &v[0], vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt__Ljava_lang_String_2_3IFI(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin) {

//@line:4211

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt(label, &v[0], vSpeed, vMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt__Ljava_lang_String_2_3IFII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin, jint vMax) {

//@line:4220

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt(label, &v[0], vSpeed, vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt__Ljava_lang_String_2_3IFIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin, jint vMax, jstring obj_format) {

//@line:4229

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragInt(label, &v[0], vSpeed, vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt__Ljava_lang_String_2_3IFIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin, jint vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:4240

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragInt(label, &v[0], vSpeed, vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt__Ljava_lang_String_2_3IFIII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin, jint vMax, jint imGuiSliderFlags) {

//@line:4251

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt(label, &v[0], vSpeed, vMin, vMax, "%d", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt2__Ljava_lang_String_2_3I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v) {

//@line:4288

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt2(label, &v[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt2__Ljava_lang_String_2_3IF(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed) {

//@line:4297

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt2(label, &v[0], vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt2__Ljava_lang_String_2_3IFI(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin) {

//@line:4306

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt2(label, &v[0], vSpeed, vMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt2__Ljava_lang_String_2_3IFII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin, jint vMax) {

//@line:4315

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt2(label, &v[0], vSpeed, vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt2__Ljava_lang_String_2_3IFIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin, jint vMax, jstring obj_format) {

//@line:4324

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragInt2(label, &v[0], vSpeed, vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt2__Ljava_lang_String_2_3IFIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin, jint vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:4335

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragInt2(label, &v[0], vSpeed, vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt2__Ljava_lang_String_2_3IFIII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin, jint vMax, jint imGuiSliderFlags) {

//@line:4346

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt2(label, &v[0], vSpeed, vMin, vMax, "%d", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt3__Ljava_lang_String_2_3I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v) {

//@line:4383

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt3(label, &v[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt3__Ljava_lang_String_2_3IF(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed) {

//@line:4392

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt3(label, &v[0], vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt3__Ljava_lang_String_2_3IFI(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin) {

//@line:4401

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt3(label, &v[0], vSpeed, vMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt3__Ljava_lang_String_2_3IFII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin, jint vMax) {

//@line:4410

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt3(label, &v[0], vSpeed, vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt3__Ljava_lang_String_2_3IFIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin, jint vMax, jstring obj_format) {

//@line:4419

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragInt3(label, &v[0], vSpeed, vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt3__Ljava_lang_String_2_3IFIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin, jint vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:4430

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragInt3(label, &v[0], vSpeed, vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt3__Ljava_lang_String_2_3IFIII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin, jint vMax, jint imGuiSliderFlags) {

//@line:4441

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt3(label, &v[0], vSpeed, vMin, vMax, "%d", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt4__Ljava_lang_String_2_3I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v) {

//@line:4478

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt4(label, &v[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt4__Ljava_lang_String_2_3IF(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed) {

//@line:4487

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt4(label, &v[0], vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt4__Ljava_lang_String_2_3IFI(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin) {

//@line:4496

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt4(label, &v[0], vSpeed, vMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt4__Ljava_lang_String_2_3IFII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin, jint vMax) {

//@line:4505

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt4(label, &v[0], vSpeed, vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt4__Ljava_lang_String_2_3IFIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin, jint vMax, jstring obj_format) {

//@line:4514

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragInt4(label, &v[0], vSpeed, vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt4__Ljava_lang_String_2_3IFIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin, jint vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:4525

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragInt4(label, &v[0], vSpeed, vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragInt4__Ljava_lang_String_2_3IFIII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jfloat vSpeed, jint vMin, jint vMax, jint imGuiSliderFlags) {

//@line:4536

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::DragInt4(label, &v[0], vSpeed, vMin, vMax, "%d", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragIntRange2__Ljava_lang_String_2_3I_3I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_vCurrentMin, jintArray obj_vCurrentMax) {

//@line:4573

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vCurrentMin = obj_vCurrentMin == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_vCurrentMin, JNI_FALSE);
        auto vCurrentMax = obj_vCurrentMax == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_vCurrentMax, JNI_FALSE);
        auto _result = ImGui::DragIntRange2(label, &vCurrentMin[0], &vCurrentMax[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vCurrentMin != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMin, vCurrentMin, JNI_FALSE);
        if (vCurrentMax != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMax, vCurrentMax, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragIntRange2__Ljava_lang_String_2_3I_3IF(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_vCurrentMin, jintArray obj_vCurrentMax, jfloat vSpeed) {

//@line:4584

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vCurrentMin = obj_vCurrentMin == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_vCurrentMin, JNI_FALSE);
        auto vCurrentMax = obj_vCurrentMax == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_vCurrentMax, JNI_FALSE);
        auto _result = ImGui::DragIntRange2(label, &vCurrentMin[0], &vCurrentMax[0], vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vCurrentMin != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMin, vCurrentMin, JNI_FALSE);
        if (vCurrentMax != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMax, vCurrentMax, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragIntRange2__Ljava_lang_String_2_3I_3IFI(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_vCurrentMin, jintArray obj_vCurrentMax, jfloat vSpeed, jint vMin) {

//@line:4595

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vCurrentMin = obj_vCurrentMin == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_vCurrentMin, JNI_FALSE);
        auto vCurrentMax = obj_vCurrentMax == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_vCurrentMax, JNI_FALSE);
        auto _result = ImGui::DragIntRange2(label, &vCurrentMin[0], &vCurrentMax[0], vSpeed, vMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vCurrentMin != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMin, vCurrentMin, JNI_FALSE);
        if (vCurrentMax != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMax, vCurrentMax, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragIntRange2__Ljava_lang_String_2_3I_3IFII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_vCurrentMin, jintArray obj_vCurrentMax, jfloat vSpeed, jint vMin, jint vMax) {

//@line:4606

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vCurrentMin = obj_vCurrentMin == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_vCurrentMin, JNI_FALSE);
        auto vCurrentMax = obj_vCurrentMax == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_vCurrentMax, JNI_FALSE);
        auto _result = ImGui::DragIntRange2(label, &vCurrentMin[0], &vCurrentMax[0], vSpeed, vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vCurrentMin != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMin, vCurrentMin, JNI_FALSE);
        if (vCurrentMax != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMax, vCurrentMax, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragIntRange2__Ljava_lang_String_2_3I_3IFIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_vCurrentMin, jintArray obj_vCurrentMax, jfloat vSpeed, jint vMin, jint vMax, jstring obj_format) {

//@line:4617

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vCurrentMin = obj_vCurrentMin == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_vCurrentMin, JNI_FALSE);
        auto vCurrentMax = obj_vCurrentMax == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_vCurrentMax, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragIntRange2(label, &vCurrentMin[0], &vCurrentMax[0], vSpeed, vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vCurrentMin != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMin, vCurrentMin, JNI_FALSE);
        if (vCurrentMax != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMax, vCurrentMax, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragIntRange2__Ljava_lang_String_2_3I_3IFIILjava_lang_String_2Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_vCurrentMin, jintArray obj_vCurrentMax, jfloat vSpeed, jint vMin, jint vMax, jstring obj_format, jstring obj_formatMax) {

//@line:4630

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vCurrentMin = obj_vCurrentMin == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_vCurrentMin, JNI_FALSE);
        auto vCurrentMax = obj_vCurrentMax == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_vCurrentMax, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto formatMax = obj_formatMax == NULL ? NULL : (char*)env->GetStringUTFChars(obj_formatMax, JNI_FALSE);
        auto _result = ImGui::DragIntRange2(label, &vCurrentMin[0], &vCurrentMax[0], vSpeed, vMin, vMax, format, formatMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vCurrentMin != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMin, vCurrentMin, JNI_FALSE);
        if (vCurrentMax != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMax, vCurrentMax, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        if (formatMax != NULL) env->ReleaseStringUTFChars(obj_formatMax, formatMax);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragIntRange2__Ljava_lang_String_2_3I_3IFIILjava_lang_String_2Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_vCurrentMin, jintArray obj_vCurrentMax, jfloat vSpeed, jint vMin, jint vMax, jstring obj_format, jstring obj_formatMax, jint imGuiSliderFlags) {

//@line:4645

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vCurrentMin = obj_vCurrentMin == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_vCurrentMin, JNI_FALSE);
        auto vCurrentMax = obj_vCurrentMax == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_vCurrentMax, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto formatMax = obj_formatMax == NULL ? NULL : (char*)env->GetStringUTFChars(obj_formatMax, JNI_FALSE);
        auto _result = ImGui::DragIntRange2(label, &vCurrentMin[0], &vCurrentMax[0], vSpeed, vMin, vMax, format, formatMax, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vCurrentMin != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMin, vCurrentMin, JNI_FALSE);
        if (vCurrentMax != NULL) env->ReleasePrimitiveArrayCritical(obj_vCurrentMax, vCurrentMax, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        if (formatMax != NULL) env->ReleaseStringUTFChars(obj_formatMax, formatMax);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3S(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData) {

//@line:4684

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S16, &pData[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3SF(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jfloat vSpeed) {

//@line:4693

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S16, &pData[0], vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3SFS(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jfloat vSpeed, jshort pMin) {

//@line:4702

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S16, &pData[0], vSpeed, &pMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3SFSS(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jfloat vSpeed, jshort pMin, jshort pMax) {

//@line:4711

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S16, &pData[0], vSpeed, &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3SFSSLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jfloat vSpeed, jshort pMin, jshort pMax, jstring obj_format) {

//@line:4720

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S16, &pData[0], vSpeed, &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3SFSSLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jfloat vSpeed, jshort pMin, jshort pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:4731

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S16, &pData[0], vSpeed, &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData) {

//@line:4766

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S32, &pData[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3IF(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jfloat vSpeed) {

//@line:4775

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S32, &pData[0], vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3IFI(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jfloat vSpeed, jint pMin) {

//@line:4784

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S32, &pData[0], vSpeed, &pMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3IFII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jfloat vSpeed, jint pMin, jint pMax) {

//@line:4793

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S32, &pData[0], vSpeed, &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3IFIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jfloat vSpeed, jint pMin, jint pMax, jstring obj_format) {

//@line:4802

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S32, &pData[0], vSpeed, &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3IFIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jfloat vSpeed, jint pMin, jint pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:4813

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S32, &pData[0], vSpeed, &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3J(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData) {

//@line:4848

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S64, &pData[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3JF(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jfloat vSpeed) {

//@line:4857

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S64, &pData[0], vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3JFJ(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jfloat vSpeed, jlong pMin) {

//@line:4866

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S64, &pData[0], vSpeed, &pMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3JFJJ(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jfloat vSpeed, jlong pMin, jlong pMax) {

//@line:4875

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S64, &pData[0], vSpeed, &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3JFJJLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jfloat vSpeed, jlong pMin, jlong pMax, jstring obj_format) {

//@line:4884

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S64, &pData[0], vSpeed, &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3JFJJLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jfloat vSpeed, jlong pMin, jlong pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:4895

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_S64, &pData[0], vSpeed, &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData) {

//@line:4930

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_Float, &pData[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3FF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jfloat vSpeed) {

//@line:4939

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_Float, &pData[0], vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3FFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jfloat vSpeed, jfloat pMin) {

//@line:4948

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_Float, &pData[0], vSpeed, &pMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3FFFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jfloat vSpeed, jfloat pMin, jfloat pMax) {

//@line:4957

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_Float, &pData[0], vSpeed, &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3FFFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jfloat vSpeed, jfloat pMin, jfloat pMax, jstring obj_format) {

//@line:4966

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_Float, &pData[0], vSpeed, &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3FFFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jfloat vSpeed, jfloat pMin, jfloat pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:4977

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_Float, &pData[0], vSpeed, &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3D(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData) {

//@line:5012

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_Double, &pData[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3DF(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jfloat vSpeed) {

//@line:5021

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_Double, &pData[0], vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3DFD(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jfloat vSpeed, jdouble pMin) {

//@line:5030

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_Double, &pData[0], vSpeed, &pMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3DFDD(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jfloat vSpeed, jdouble pMin, jdouble pMax) {

//@line:5039

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_Double, &pData[0], vSpeed, &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3DFDDLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jfloat vSpeed, jdouble pMin, jdouble pMax, jstring obj_format) {

//@line:5048

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_Double, &pData[0], vSpeed, &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalar__Ljava_lang_String_2_3DFDDLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jfloat vSpeed, jdouble pMin, jdouble pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:5059

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalar(label, ImGuiDataType_Double, &pData[0], vSpeed, &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3SI(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jint components) {

//@line:5094

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S16, &pData[0], components);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3SIF(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jint components, jfloat vSpeed) {

//@line:5103

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S16, &pData[0], components, vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3SIFS(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jint components, jfloat vSpeed, jshort pMin) {

//@line:5112

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S16, &pData[0], components, vSpeed, &pMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3SIFSS(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jint components, jfloat vSpeed, jshort pMin, jshort pMax) {

//@line:5121

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S16, &pData[0], components, vSpeed, &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3SIFSSLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jint components, jfloat vSpeed, jshort pMin, jshort pMax, jstring obj_format) {

//@line:5130

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S16, &pData[0], components, vSpeed, &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3SIFSSLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jint components, jfloat vSpeed, jshort pMin, jshort pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:5141

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S16, &pData[0], components, vSpeed, &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3II(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint components) {

//@line:5176

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S32, &pData[0], components);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3IIF(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint components, jfloat vSpeed) {

//@line:5185

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S32, &pData[0], components, vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3IIFI(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint components, jfloat vSpeed, jint pMin) {

//@line:5194

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S32, &pData[0], components, vSpeed, &pMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3IIFII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint components, jfloat vSpeed, jint pMin, jint pMax) {

//@line:5203

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S32, &pData[0], components, vSpeed, &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3IIFIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint components, jfloat vSpeed, jint pMin, jint pMax, jstring obj_format) {

//@line:5212

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S32, &pData[0], components, vSpeed, &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3IIFIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint components, jfloat vSpeed, jint pMin, jint pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:5223

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S32, &pData[0], components, vSpeed, &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3JI(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jint components) {

//@line:5258

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S64, &pData[0], components);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3JIF(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jint components, jfloat vSpeed) {

//@line:5267

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S64, &pData[0], components, vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3JIFJ(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jint components, jfloat vSpeed, jlong pMin) {

//@line:5276

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S64, &pData[0], components, vSpeed, &pMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3JIFJJ(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jint components, jfloat vSpeed, jlong pMin, jlong pMax) {

//@line:5285

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S64, &pData[0], components, vSpeed, &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3JIFJJLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jint components, jfloat vSpeed, jlong pMin, jlong pMax, jstring obj_format) {

//@line:5294

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S64, &pData[0], components, vSpeed, &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3JIFJJLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jint components, jfloat vSpeed, jlong pMin, jlong pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:5305

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_S64, &pData[0], components, vSpeed, &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3FI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jint components) {

//@line:5340

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_Float, &pData[0], components);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3FIF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jint components, jfloat vSpeed) {

//@line:5349

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_Float, &pData[0], components, vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3FIFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jint components, jfloat vSpeed, jfloat pMin) {

//@line:5358

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_Float, &pData[0], components, vSpeed, &pMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3FIFFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jint components, jfloat vSpeed, jfloat pMin, jfloat pMax) {

//@line:5367

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_Float, &pData[0], components, vSpeed, &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3FIFFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jint components, jfloat vSpeed, jfloat pMin, jfloat pMax, jstring obj_format) {

//@line:5376

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_Float, &pData[0], components, vSpeed, &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3FIFFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jint components, jfloat vSpeed, jfloat pMin, jfloat pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:5387

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_Float, &pData[0], components, vSpeed, &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3DI(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jint components) {

//@line:5422

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_Double, &pData[0], components);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3DIF(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jint components, jfloat vSpeed) {

//@line:5431

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_Double, &pData[0], components, vSpeed);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3DIFD(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jint components, jfloat vSpeed, jdouble pMin) {

//@line:5440

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_Double, &pData[0], components, vSpeed, &pMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3DIFDD(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jint components, jfloat vSpeed, jdouble pMin, jdouble pMax) {

//@line:5449

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_Double, &pData[0], components, vSpeed, &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3DIFDDLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jint components, jfloat vSpeed, jdouble pMin, jdouble pMax, jstring obj_format) {

//@line:5458

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_Double, &pData[0], components, vSpeed, &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDragScalarN__Ljava_lang_String_2_3DIFDDLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jint components, jfloat vSpeed, jdouble pMin, jdouble pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:5469

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::DragScalarN(label, ImGuiDataType_Double, &pData[0], components, vSpeed, &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderFloat__Ljava_lang_String_2_3FFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vMin, jfloat vMax) {

//@line:5515

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::SliderFloat(label, &v[0], vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderFloat__Ljava_lang_String_2_3FFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vMin, jfloat vMax, jstring obj_format) {

//@line:5524

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderFloat(label, &v[0], vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderFloat__Ljava_lang_String_2_3FFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vMin, jfloat vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:5535

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderFloat(label, &v[0], vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderFloat__Ljava_lang_String_2_3FFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vMin, jfloat vMax, jint imGuiSliderFlags) {

//@line:5546

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::SliderFloat(label, &v[0], vMin, vMax, "%.3f", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderFloat2__Ljava_lang_String_2_3FFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vMin, jfloat vMax) {

//@line:5571

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::SliderFloat2(label, &v[0], vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderFloat2__Ljava_lang_String_2_3FFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vMin, jfloat vMax, jstring obj_format) {

//@line:5580

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderFloat2(label, &v[0], vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderFloat2__Ljava_lang_String_2_3FFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vMin, jfloat vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:5591

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderFloat2(label, &v[0], vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderFloat2__Ljava_lang_String_2_3FFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vMin, jfloat vMax, jint imGuiSliderFlags) {

//@line:5602

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::SliderFloat2(label, &v[0], vMin, vMax, "%.3f", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderFloat3__Ljava_lang_String_2_3FFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vMin, jfloat vMax) {

//@line:5627

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::SliderFloat3(label, &v[0], vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderFloat3__Ljava_lang_String_2_3FFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vMin, jfloat vMax, jstring obj_format) {

//@line:5636

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderFloat3(label, &v[0], vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderFloat3__Ljava_lang_String_2_3FFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vMin, jfloat vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:5647

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderFloat3(label, &v[0], vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderFloat3__Ljava_lang_String_2_3FFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vMin, jfloat vMax, jint imGuiSliderFlags) {

//@line:5658

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::SliderFloat3(label, &v[0], vMin, vMax, "%.3f", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderFloat4__Ljava_lang_String_2_3FFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vMin, jfloat vMax) {

//@line:5683

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::SliderFloat4(label, &v[0], vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderFloat4__Ljava_lang_String_2_3FFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vMin, jfloat vMax, jstring obj_format) {

//@line:5692

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderFloat4(label, &v[0], vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderFloat4__Ljava_lang_String_2_3FFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vMin, jfloat vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:5703

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderFloat4(label, &v[0], vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderFloat4__Ljava_lang_String_2_3FFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat vMin, jfloat vMax, jint imGuiSliderFlags) {

//@line:5714

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::SliderFloat4(label, &v[0], vMin, vMax, "%.3f", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderAngle__Ljava_lang_String_2_3F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_vRad) {

//@line:5747

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vRad = obj_vRad == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vRad, JNI_FALSE);
        auto _result = ImGui::SliderAngle(label, &vRad[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vRad != NULL) env->ReleasePrimitiveArrayCritical(obj_vRad, vRad, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderAngle__Ljava_lang_String_2_3FF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_vRad, jfloat vDegreesMin) {

//@line:5756

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vRad = obj_vRad == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vRad, JNI_FALSE);
        auto _result = ImGui::SliderAngle(label, &vRad[0], vDegreesMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vRad != NULL) env->ReleasePrimitiveArrayCritical(obj_vRad, vRad, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderAngle__Ljava_lang_String_2_3FFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_vRad, jfloat vDegreesMin, jfloat vDegreesMax) {

//@line:5765

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vRad = obj_vRad == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vRad, JNI_FALSE);
        auto _result = ImGui::SliderAngle(label, &vRad[0], vDegreesMin, vDegreesMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vRad != NULL) env->ReleasePrimitiveArrayCritical(obj_vRad, vRad, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderAngle__Ljava_lang_String_2_3FFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_vRad, jfloat vDegreesMin, jfloat vDegreesMax, jstring obj_format) {

//@line:5774

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vRad = obj_vRad == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vRad, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderAngle(label, &vRad[0], vDegreesMin, vDegreesMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vRad != NULL) env->ReleasePrimitiveArrayCritical(obj_vRad, vRad, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderAngle__Ljava_lang_String_2_3FFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_vRad, jfloat vDegreesMin, jfloat vDegreesMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:5785

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vRad = obj_vRad == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vRad, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderAngle(label, &vRad[0], vDegreesMin, vDegreesMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vRad != NULL) env->ReleasePrimitiveArrayCritical(obj_vRad, vRad, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderAngle__Ljava_lang_String_2_3FFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_vRad, jfloat vDegreesMin, jfloat vDegreesMax, jint imGuiSliderFlags) {

//@line:5796

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto vRad = obj_vRad == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_vRad, JNI_FALSE);
        auto _result = ImGui::SliderAngle(label, &vRad[0], vDegreesMin, vDegreesMax, "%.0f deg", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (vRad != NULL) env->ReleasePrimitiveArrayCritical(obj_vRad, vRad, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderInt__Ljava_lang_String_2_3III(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint vMin, jint vMax) {

//@line:5821

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::SliderInt(label, &v[0], vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderInt__Ljava_lang_String_2_3IIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint vMin, jint vMax, jstring obj_format) {

//@line:5830

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderInt(label, &v[0], vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderInt__Ljava_lang_String_2_3IIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint vMin, jint vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:5841

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderInt(label, &v[0], vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderInt__Ljava_lang_String_2_3IIII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint vMin, jint vMax, jint imGuiSliderFlags) {

//@line:5852

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::SliderInt(label, &v[0], vMin, vMax, "%d", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderInt2__Ljava_lang_String_2_3III(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint vMin, jint vMax) {

//@line:5877

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::SliderInt2(label, &v[0], vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderInt2__Ljava_lang_String_2_3IIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint vMin, jint vMax, jstring obj_format) {

//@line:5886

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderInt2(label, &v[0], vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderInt2__Ljava_lang_String_2_3IIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint vMin, jint vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:5897

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderInt2(label, &v[0], vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderInt2__Ljava_lang_String_2_3IIII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint vMin, jint vMax, jint imGuiSliderFlags) {

//@line:5908

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::SliderInt2(label, &v[0], vMin, vMax, "%d", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderInt3__Ljava_lang_String_2_3III(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint vMin, jint vMax) {

//@line:5933

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::SliderInt3(label, &v[0], vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderInt3__Ljava_lang_String_2_3IIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint vMin, jint vMax, jstring obj_format) {

//@line:5942

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderInt3(label, &v[0], vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderInt3__Ljava_lang_String_2_3IIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint vMin, jint vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:5953

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderInt3(label, &v[0], vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderInt3__Ljava_lang_String_2_3IIII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint vMin, jint vMax, jint imGuiSliderFlags) {

//@line:5964

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::SliderInt3(label, &v[0], vMin, vMax, "%d", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderInt4__Ljava_lang_String_2_3III(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint vMin, jint vMax) {

//@line:5989

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::SliderInt4(label, &v[0], vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderInt4__Ljava_lang_String_2_3IIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint vMin, jint vMax, jstring obj_format) {

//@line:5998

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderInt4(label, &v[0], vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderInt4__Ljava_lang_String_2_3IIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint vMin, jint vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6009

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderInt4(label, &v[0], vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderInt4__Ljava_lang_String_2_3IIII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint vMin, jint vMax, jint imGuiSliderFlags) {

//@line:6020

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::SliderInt4(label, &v[0], vMin, vMax, "%d", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalar__Ljava_lang_String_2_3SSS(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jshort pMin, jshort pMax) {

//@line:6041

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::SliderScalar(label, ImGuiDataType_S16, &pData[0], &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalar__Ljava_lang_String_2_3SSSLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jshort pMin, jshort pMax, jstring obj_format) {

//@line:6050

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalar(label, ImGuiDataType_S16, &pData[0], &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalar__Ljava_lang_String_2_3SSSLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jshort pMin, jshort pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6061

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalar(label, ImGuiDataType_S16, &pData[0], &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalar__Ljava_lang_String_2_3III(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint pMin, jint pMax) {

//@line:6084

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::SliderScalar(label, ImGuiDataType_S32, &pData[0], &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalar__Ljava_lang_String_2_3IIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint pMin, jint pMax, jstring obj_format) {

//@line:6093

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalar(label, ImGuiDataType_S32, &pData[0], &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalar__Ljava_lang_String_2_3IIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint pMin, jint pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6104

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalar(label, ImGuiDataType_S32, &pData[0], &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalar__Ljava_lang_String_2_3JJJ(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jlong pMin, jlong pMax) {

//@line:6127

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::SliderScalar(label, ImGuiDataType_S64, &pData[0], &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalar__Ljava_lang_String_2_3JJJLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jlong pMin, jlong pMax, jstring obj_format) {

//@line:6136

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalar(label, ImGuiDataType_S64, &pData[0], &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalar__Ljava_lang_String_2_3JJJLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jlong pMin, jlong pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6147

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalar(label, ImGuiDataType_S64, &pData[0], &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalar__Ljava_lang_String_2_3FFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jfloat pMin, jfloat pMax) {

//@line:6170

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::SliderScalar(label, ImGuiDataType_Float, &pData[0], &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalar__Ljava_lang_String_2_3FFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jfloat pMin, jfloat pMax, jstring obj_format) {

//@line:6179

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalar(label, ImGuiDataType_Float, &pData[0], &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalar__Ljava_lang_String_2_3FFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jfloat pMin, jfloat pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6190

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalar(label, ImGuiDataType_Float, &pData[0], &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalar__Ljava_lang_String_2_3DDD(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jdouble pMin, jdouble pMax) {

//@line:6213

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::SliderScalar(label, ImGuiDataType_Double, &pData[0], &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalar__Ljava_lang_String_2_3DDDLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jdouble pMin, jdouble pMax, jstring obj_format) {

//@line:6222

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalar(label, ImGuiDataType_Double, &pData[0], &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalar__Ljava_lang_String_2_3DDDLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jdouble pMin, jdouble pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6233

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalar(label, ImGuiDataType_Double, &pData[0], &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalarN__Ljava_lang_String_2_3SISS(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jint components, jshort pMin, jshort pMax) {

//@line:6256

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::SliderScalarN(label, ImGuiDataType_S16, &pData[0], components, &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalarN__Ljava_lang_String_2_3SISSLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jint components, jshort pMin, jshort pMax, jstring obj_format) {

//@line:6265

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalarN(label, ImGuiDataType_S16, &pData[0], components, &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalarN__Ljava_lang_String_2_3SISSLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jint components, jshort pMin, jshort pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6276

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalarN(label, ImGuiDataType_S16, &pData[0], components, &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalarN__Ljava_lang_String_2_3IIII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint components, jint pMin, jint pMax) {

//@line:6299

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::SliderScalarN(label, ImGuiDataType_S32, &pData[0], components, &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalarN__Ljava_lang_String_2_3IIIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint components, jint pMin, jint pMax, jstring obj_format) {

//@line:6308

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalarN(label, ImGuiDataType_S32, &pData[0], components, &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalarN__Ljava_lang_String_2_3IIIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint components, jint pMin, jint pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6319

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalarN(label, ImGuiDataType_S32, &pData[0], components, &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalarN__Ljava_lang_String_2_3JIJJ(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jint components, jlong pMin, jlong pMax) {

//@line:6342

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::SliderScalarN(label, ImGuiDataType_S64, &pData[0], components, &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalarN__Ljava_lang_String_2_3JIJJLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jint components, jlong pMin, jlong pMax, jstring obj_format) {

//@line:6351

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalarN(label, ImGuiDataType_S64, &pData[0], components, &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalarN__Ljava_lang_String_2_3JIJJLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jint components, jlong pMin, jlong pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6362

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalarN(label, ImGuiDataType_S64, &pData[0], components, &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalarN__Ljava_lang_String_2_3FIFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jint components, jfloat pMin, jfloat pMax) {

//@line:6385

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::SliderScalarN(label, ImGuiDataType_Float, &pData[0], components, &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalarN__Ljava_lang_String_2_3FIFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jint components, jfloat pMin, jfloat pMax, jstring obj_format) {

//@line:6394

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalarN(label, ImGuiDataType_Float, &pData[0], components, &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalarN__Ljava_lang_String_2_3FIFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jint components, jfloat pMin, jfloat pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6405

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalarN(label, ImGuiDataType_Float, &pData[0], components, &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalarN__Ljava_lang_String_2_3DIDD(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jint components, jdouble pMin, jdouble pMax) {

//@line:6428

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::SliderScalarN(label, ImGuiDataType_Double, &pData[0], components, &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalarN__Ljava_lang_String_2_3DIDDLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jint components, jdouble pMin, jdouble pMax, jstring obj_format) {

//@line:6437

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalarN(label, ImGuiDataType_Double, &pData[0], components, &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSliderScalarN__Ljava_lang_String_2_3DIDDLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jint components, jdouble pMin, jdouble pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6448

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::SliderScalarN(label, ImGuiDataType_Double, &pData[0], components, &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderFloat__Ljava_lang_String_2FF_3FFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jfloatArray obj_v, jfloat vMin, jfloat vMax) {

//@line:6491

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderFloat(label, size, &v[0], vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderFloat__Ljava_lang_String_2FF_3FFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jfloatArray obj_v, jfloat vMin, jfloat vMax, jstring obj_format) {

//@line:6501

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderFloat(label, size, &v[0], vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderFloat__Ljava_lang_String_2FF_3FFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jfloatArray obj_v, jfloat vMin, jfloat vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6513

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderFloat(label, size, &v[0], vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderFloat__Ljava_lang_String_2FF_3FFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jfloatArray obj_v, jfloat vMin, jfloat vMax, jint imGuiSliderFlags) {

//@line:6525

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderFloat(label, size, &v[0], vMin, vMax, "%.3f", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderInt__Ljava_lang_String_2FF_3III(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jintArray obj_v, jint vMin, jint vMax) {

//@line:6567

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderInt(label, size, &v[0], vMin, vMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderInt__Ljava_lang_String_2FF_3IIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jintArray obj_v, jint vMin, jint vMax, jstring obj_format) {

//@line:6577

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderInt(label, size, &v[0], vMin, vMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderInt__Ljava_lang_String_2FF_3IIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jintArray obj_v, jint vMin, jint vMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6589

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderInt(label, size, &v[0], vMin, vMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderInt__Ljava_lang_String_2FF_3IIII(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jintArray obj_v, jint vMin, jint vMax, jint imGuiSliderFlags) {

//@line:6601

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderInt(label, size, &v[0], vMin, vMax, "%d", imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderScalar__Ljava_lang_String_2FF_3SSS(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jshortArray obj_pData, jshort pMin, jshort pMax) {

//@line:6635

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderScalar(label, size, ImGuiDataType_S16, &pData[0], &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderScalar__Ljava_lang_String_2FF_3SSSLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jshortArray obj_pData, jshort pMin, jshort pMax, jstring obj_format) {

//@line:6645

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderScalar(label, size, ImGuiDataType_S16, &pData[0], &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderScalar__Ljava_lang_String_2FF_3SSSLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jshortArray obj_pData, jshort pMin, jshort pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6657

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderScalar(label, size, ImGuiDataType_S16, &pData[0], &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderScalar__Ljava_lang_String_2FF_3III(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jintArray obj_pData, jint pMin, jint pMax) {

//@line:6693

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderScalar(label, size, ImGuiDataType_S32, &pData[0], &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderScalar__Ljava_lang_String_2FF_3IIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jintArray obj_pData, jint pMin, jint pMax, jstring obj_format) {

//@line:6703

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderScalar(label, size, ImGuiDataType_S32, &pData[0], &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderScalar__Ljava_lang_String_2FF_3IIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jintArray obj_pData, jint pMin, jint pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6715

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderScalar(label, size, ImGuiDataType_S32, &pData[0], &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderScalar__Ljava_lang_String_2FF_3JJJ(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jlongArray obj_pData, jlong pMin, jlong pMax) {

//@line:6751

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderScalar(label, size, ImGuiDataType_S64, &pData[0], &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderScalar__Ljava_lang_String_2FF_3JJJLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jlongArray obj_pData, jlong pMin, jlong pMax, jstring obj_format) {

//@line:6761

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderScalar(label, size, ImGuiDataType_S64, &pData[0], &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderScalar__Ljava_lang_String_2FF_3JJJLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jlongArray obj_pData, jlong pMin, jlong pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6773

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderScalar(label, size, ImGuiDataType_S64, &pData[0], &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderScalar__Ljava_lang_String_2FF_3FFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jfloatArray obj_pData, jfloat pMin, jfloat pMax) {

//@line:6809

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderScalar(label, size, ImGuiDataType_Float, &pData[0], &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderScalar__Ljava_lang_String_2FF_3FFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jfloatArray obj_pData, jfloat pMin, jfloat pMax, jstring obj_format) {

//@line:6819

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderScalar(label, size, ImGuiDataType_Float, &pData[0], &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderScalar__Ljava_lang_String_2FF_3FFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jfloatArray obj_pData, jfloat pMin, jfloat pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6831

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderScalar(label, size, ImGuiDataType_Float, &pData[0], &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderScalar__Ljava_lang_String_2FF_3DDD(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jdoubleArray obj_pData, jdouble pMin, jdouble pMax) {

//@line:6867

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderScalar(label, size, ImGuiDataType_Double, &pData[0], &pMin, &pMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderScalar__Ljava_lang_String_2FF_3DDDLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jdoubleArray obj_pData, jdouble pMin, jdouble pMax, jstring obj_format) {

//@line:6877

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderScalar(label, size, ImGuiDataType_Double, &pData[0], &pMin, &pMax, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nVSliderScalar__Ljava_lang_String_2FF_3DDDLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY, jdoubleArray obj_pData, jdouble pMin, jdouble pMax, jstring obj_format, jint imGuiSliderFlags) {

//@line:6889

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::VSliderScalar(label, size, ImGuiDataType_Double, &pData[0], &pMin, &pMax, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}


//@line:6905

        jmethodID jImStringResizeInternalMID;
        jmethodID jInputTextCallbackMID;

        jfieldID inputDataSizeID;
        jfieldID inputDataIsDirtyID;
        jfieldID inputDataIsResizedID;

        struct InputTextCallbackUserData {
            JNIEnv* env;
            jobject* imString;
            int maxSize;
            jbyteArray jResizedBuf;
            char* resizedBuf;
            jobject* textInputData;
            char* allowedChars;
            jobject* handler;
        };

        static int TextEditCallbackStub(ImGuiInputTextCallbackData* data) {
            InputTextCallbackUserData* userData = (InputTextCallbackUserData*)data->UserData;

            if (data->EventFlag == ImGuiInputTextFlags_CallbackCharFilter) {
                int allowedCharLength = strlen(userData->allowedChars);
                if(allowedCharLength > 0) {
                    bool found = false;
                    for(int i = 0; i < allowedCharLength; i++) {
                        if(userData->allowedChars[i] == data->EventChar) {
                            found = true;
                            break;
                        }
                    }
                    return found ? 0 : 1;
                }
            } else if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
                int newSize = data->BufTextLen;
                if (newSize >= userData->maxSize) {
                    JNIEnv* env = userData->env;

                    jbyteArray newBufArr = (jbyteArray)env->CallObjectMethod(*userData->imString, jImStringResizeInternalMID, newSize);
                    char* newBuf = (char*)env->GetPrimitiveArrayCritical(newBufArr, 0);

                    data->Buf = newBuf;

                    userData->jResizedBuf = newBufArr;
                    userData->resizedBuf = newBuf;
                }
            }

            if (userData->handler != NULL) {
                JNIEnv* env = userData->env;
                env->CallObjectMethod(*userData->handler, jInputTextCallbackMID, data);
            }

            return 0;
        }
    JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nInitInputTextData(JNIEnv* env, jclass clazz) {


//@line:6963

        jclass jInputDataClass = env->FindClass("imgui/moulberry92/type/ImString$InputData");
        inputDataSizeID = env->GetFieldID(jInputDataClass, "size", "I");
        inputDataIsDirtyID = env->GetFieldID(jInputDataClass, "isDirty", "Z");
        inputDataIsResizedID = env->GetFieldID(jInputDataClass, "isResized", "Z");

        jclass jImString = env->FindClass("imgui/moulberry92/type/ImString");
        jImStringResizeInternalMID = env->GetMethodID(jImString, "resizeInternal", "(I)[B");

        jclass jCallback = env->FindClass("imgui/moulberry92/callback/ImGuiInputTextCallback");
        jInputTextCallbackMID = env->GetMethodID(jCallback, "accept", "(J)V");
    

}

static inline jboolean wrapped_Java_imgui_moulberry92_ImGui_nInputText
(JNIEnv* env, jclass clazz, jboolean multiline, jboolean hint, jstring obj_label, jstring obj_hintLabel, jobject imString, jbyteArray obj_buf, jint maxSize, jfloat width, jfloat height, jint flagsV, jobject textInputData, jstring obj_allowedChars, jboolean isResizable, jobject callback, char* label, char* hintLabel, char* allowedChars, char* buf) {

//@line:7077

        InputTextCallbackUserData userData;
        userData.imString = &imString;
        userData.maxSize = maxSize;
        userData.jResizedBuf = NULL;
        userData.resizedBuf = NULL;
        userData.textInputData = &textInputData;
        userData.env = env;
        userData.allowedChars = allowedChars;
        userData.handler = callback != NULL ? &callback : NULL;

        int flags = flagsV;
        if (isResizable) {
            flags |= ImGuiInputTextFlags_CallbackResize;
        }
        if (strlen(allowedChars) > 0) {
            flags |= ImGuiInputTextFlags_CallbackCharFilter;
        }

        bool valueChanged;

        if (multiline) {
            valueChanged = ImGui::InputTextMultiline(label, buf, maxSize, ImVec2(width, height), flags, &TextEditCallbackStub, &userData);
        } else if (hint) {
            valueChanged = ImGui::InputTextWithHint(label, hintLabel, buf, maxSize, flags, &TextEditCallbackStub, &userData);
        } else {
            valueChanged = ImGui::InputText(label, buf, maxSize, flags, &TextEditCallbackStub, &userData);
        }

        if (valueChanged) {
            int size;

            if (userData.jResizedBuf != NULL) {
                size = strlen(userData.resizedBuf);
                env->ReleasePrimitiveArrayCritical(userData.jResizedBuf, userData.resizedBuf, 0);
            } else {
                size = strlen(buf);
            }

            env->SetIntField(textInputData, inputDataSizeID, size);
            env->SetBooleanField(textInputData, inputDataIsDirtyID, true);
        }

        return valueChanged;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputText(JNIEnv* env, jclass clazz, jboolean multiline, jboolean hint, jstring obj_label, jstring obj_hintLabel, jobject imString, jbyteArray obj_buf, jint maxSize, jfloat width, jfloat height, jint flagsV, jobject textInputData, jstring obj_allowedChars, jboolean isResizable, jobject callback) {
	char* label = (char*)env->GetStringUTFChars(obj_label, 0);
	char* hintLabel = (char*)env->GetStringUTFChars(obj_hintLabel, 0);
	char* allowedChars = (char*)env->GetStringUTFChars(obj_allowedChars, 0);
	char* buf = (char*)env->GetPrimitiveArrayCritical(obj_buf, 0);

	jboolean JNI_returnValue = wrapped_Java_imgui_moulberry92_ImGui_nInputText(env, clazz, multiline, hint, obj_label, obj_hintLabel, imString, obj_buf, maxSize, width, height, flagsV, textInputData, obj_allowedChars, isResizable, callback, label, hintLabel, allowedChars, buf);

	env->ReleasePrimitiveArrayCritical(obj_buf, buf, 0);
	env->ReleaseStringUTFChars(obj_label, label);
	env->ReleaseStringUTFChars(obj_hintLabel, hintLabel);
	env->ReleaseStringUTFChars(obj_allowedChars, allowedChars);

	return JNI_returnValue;
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat__Ljava_lang_String_2_3F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v) {

//@line:7147

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputFloat(label, (v != NULL ? &v[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat__Ljava_lang_String_2_3FF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat step) {

//@line:7156

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputFloat(label, (v != NULL ? &v[0] : NULL), step);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat__Ljava_lang_String_2_3FFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat step, jfloat stepFast) {

//@line:7165

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputFloat(label, (v != NULL ? &v[0] : NULL), step, stepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat__Ljava_lang_String_2_3FFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat step, jfloat stepFast, jstring obj_format) {

//@line:7174

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputFloat(label, (v != NULL ? &v[0] : NULL), step, stepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat__Ljava_lang_String_2_3FFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat step, jfloat stepFast, jstring obj_format, jint imGuiInputTextFlags) {

//@line:7185

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputFloat(label, (v != NULL ? &v[0] : NULL), step, stepFast, format, imGuiInputTextFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat__Ljava_lang_String_2_3FFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jfloat step, jfloat stepFast, jint imGuiInputTextFlags) {

//@line:7196

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputFloat(label, (v != NULL ? &v[0] : NULL), step, stepFast, "%.3f", imGuiInputTextFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat2__Ljava_lang_String_2_3F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v) {

//@line:7221

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputFloat2(label, &v[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat2__Ljava_lang_String_2_3FLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jstring obj_format) {

//@line:7230

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputFloat2(label, &v[0], format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat2__Ljava_lang_String_2_3FLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jstring obj_format, jint imGuiInputTextFlags) {

//@line:7241

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputFloat2(label, &v[0], format, imGuiInputTextFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat2__Ljava_lang_String_2_3FI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jint imGuiInputTextFlags) {

//@line:7252

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputFloat2(label, &v[0], "%.3f", imGuiInputTextFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat3__Ljava_lang_String_2_3F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v) {

//@line:7277

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputFloat3(label, &v[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat3__Ljava_lang_String_2_3FLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jstring obj_format) {

//@line:7286

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputFloat3(label, &v[0], format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat3__Ljava_lang_String_2_3FLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jstring obj_format, jint imGuiInputTextFlags) {

//@line:7297

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputFloat3(label, &v[0], format, imGuiInputTextFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat3__Ljava_lang_String_2_3FI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jint imGuiInputTextFlags) {

//@line:7308

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputFloat3(label, &v[0], "%.3f", imGuiInputTextFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat4__Ljava_lang_String_2_3F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v) {

//@line:7333

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputFloat4(label, &v[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat4__Ljava_lang_String_2_3FLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jstring obj_format) {

//@line:7342

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputFloat4(label, &v[0], format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat4__Ljava_lang_String_2_3FLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jstring obj_format, jint imGuiInputTextFlags) {

//@line:7353

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputFloat4(label, &v[0], format, imGuiInputTextFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputFloat4__Ljava_lang_String_2_3FI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_v, jint imGuiInputTextFlags) {

//@line:7364

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputFloat4(label, &v[0], "%.3f", imGuiInputTextFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputInt__Ljava_lang_String_2_3I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v) {

//@line:7389

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputInt(label, (v != NULL ? &v[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputInt__Ljava_lang_String_2_3II(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint step) {

//@line:7398

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputInt(label, (v != NULL ? &v[0] : NULL), step);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputInt__Ljava_lang_String_2_3III(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint step, jint stepFast) {

//@line:7407

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputInt(label, (v != NULL ? &v[0] : NULL), step, stepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputInt__Ljava_lang_String_2_3IIII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint step, jint stepFast, jint imGuiInputTextFlags) {

//@line:7416

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputInt(label, (v != NULL ? &v[0] : NULL), step, stepFast, imGuiInputTextFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputInt2__Ljava_lang_String_2_3I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v) {

//@line:7433

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputInt2(label, &v[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputInt2__Ljava_lang_String_2_3II(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint imGuiInputTextFlags) {

//@line:7442

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputInt2(label, &v[0], imGuiInputTextFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputInt3__Ljava_lang_String_2_3I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v) {

//@line:7459

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputInt3(label, &v[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputInt3__Ljava_lang_String_2_3II(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint imGuiInputTextFlags) {

//@line:7468

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputInt3(label, &v[0], imGuiInputTextFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputInt4__Ljava_lang_String_2_3I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v) {

//@line:7485

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputInt4(label, &v[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputInt4__Ljava_lang_String_2_3II(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_v, jint imGuiInputTextFlags) {

//@line:7494

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputInt4(label, &v[0], imGuiInputTextFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputDouble__Ljava_lang_String_2_3D(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_v) {

//@line:7527

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputDouble(label, (v != NULL ? &v[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputDouble__Ljava_lang_String_2_3DD(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_v, jdouble step) {

//@line:7536

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputDouble(label, (v != NULL ? &v[0] : NULL), step);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputDouble__Ljava_lang_String_2_3DDD(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_v, jdouble step, jdouble stepFast) {

//@line:7545

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputDouble(label, (v != NULL ? &v[0] : NULL), step, stepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputDouble__Ljava_lang_String_2_3DDDLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_v, jdouble step, jdouble stepFast, jstring obj_format) {

//@line:7554

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputDouble(label, (v != NULL ? &v[0] : NULL), step, stepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputDouble__Ljava_lang_String_2_3DDDLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_v, jdouble step, jdouble stepFast, jstring obj_format, jint imGuiInputTextFlags) {

//@line:7565

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputDouble(label, (v != NULL ? &v[0] : NULL), step, stepFast, format, imGuiInputTextFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputDouble__Ljava_lang_String_2_3DDDI(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_v, jdouble step, jdouble stepFast, jint imGuiInputTextFlags) {

//@line:7576

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto v = obj_v == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_v, JNI_FALSE);
        auto _result = ImGui::InputDouble(label, (v != NULL ? &v[0] : NULL), step, stepFast, "%.6f", imGuiInputTextFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (v != NULL) env->ReleasePrimitiveArrayCritical(obj_v, v, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3S(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData) {

//@line:7605

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_S16, (pData != NULL ? &pData[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3SS(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jshort pStep) {

//@line:7614

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_S16, (pData != NULL ? &pData[0] : NULL), &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3SSS(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jshort pStep, jshort pStepFast) {

//@line:7623

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_S16, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3SSSLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jshort pStep, jshort pStepFast, jstring obj_format) {

//@line:7632

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_S16, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3SSSLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jshort pStep, jshort pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:7643

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_S16, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData) {

//@line:7674

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_S32, (pData != NULL ? &pData[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3II(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint pStep) {

//@line:7683

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_S32, (pData != NULL ? &pData[0] : NULL), &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3III(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint pStep, jint pStepFast) {

//@line:7692

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_S32, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3IIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint pStep, jint pStepFast, jstring obj_format) {

//@line:7701

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_S32, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3IIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint pStep, jint pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:7712

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_S32, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3J(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData) {

//@line:7743

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_S64, (pData != NULL ? &pData[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3JJ(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jlong pStep) {

//@line:7752

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_S64, (pData != NULL ? &pData[0] : NULL), &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3JJJ(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jlong pStep, jlong pStepFast) {

//@line:7761

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_S64, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3JJJLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jlong pStep, jlong pStepFast, jstring obj_format) {

//@line:7770

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_S64, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3JJJLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jlong pStep, jlong pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:7781

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_S64, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData) {

//@line:7812

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_Float, (pData != NULL ? &pData[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3FF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jfloat pStep) {

//@line:7821

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_Float, (pData != NULL ? &pData[0] : NULL), &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3FFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jfloat pStep, jfloat pStepFast) {

//@line:7830

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_Float, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3FFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jfloat pStep, jfloat pStepFast, jstring obj_format) {

//@line:7839

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_Float, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3FFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jfloat pStep, jfloat pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:7850

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_Float, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3D(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData) {

//@line:7881

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_Double, (pData != NULL ? &pData[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3DD(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jdouble pStep) {

//@line:7890

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_Double, (pData != NULL ? &pData[0] : NULL), &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3DDD(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jdouble pStep, jdouble pStepFast) {

//@line:7899

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_Double, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3DDDLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jdouble pStep, jdouble pStepFast, jstring obj_format) {

//@line:7908

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_Double, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2_3DDDLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jdouble pStep, jdouble pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:7919

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, ImGuiDataType_Double, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3S(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jshortArray obj_pData) {

//@line:7950

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3SS(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jshortArray obj_pData, jshort pStep) {

//@line:7959

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3SSS(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jshortArray obj_pData, jshort pStep, jshort pStepFast) {

//@line:7968

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3SSSLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jshortArray obj_pData, jshort pStep, jshort pStepFast, jstring obj_format) {

//@line:7977

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3SSSLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jshortArray obj_pData, jshort pStep, jshort pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:7988

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3I(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jintArray obj_pData) {

//@line:8019

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3II(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jintArray obj_pData, jint pStep) {

//@line:8028

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3III(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jintArray obj_pData, jint pStep, jint pStepFast) {

//@line:8037

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3IIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jintArray obj_pData, jint pStep, jint pStepFast, jstring obj_format) {

//@line:8046

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3IIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jintArray obj_pData, jint pStep, jint pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:8057

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3J(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jlongArray obj_pData) {

//@line:8088

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3JJ(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jlongArray obj_pData, jlong pStep) {

//@line:8097

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3JJJ(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jlongArray obj_pData, jlong pStep, jlong pStepFast) {

//@line:8106

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3JJJLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jlongArray obj_pData, jlong pStep, jlong pStepFast, jstring obj_format) {

//@line:8115

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3JJJLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jlongArray obj_pData, jlong pStep, jlong pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:8126

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3F(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jfloatArray obj_pData) {

//@line:8157

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3FF(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jfloatArray obj_pData, jfloat pStep) {

//@line:8166

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3FFF(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jfloatArray obj_pData, jfloat pStep, jfloat pStepFast) {

//@line:8175

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3FFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jfloatArray obj_pData, jfloat pStep, jfloat pStepFast, jstring obj_format) {

//@line:8184

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3FFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jfloatArray obj_pData, jfloat pStep, jfloat pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:8195

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3D(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jdoubleArray obj_pData) {

//@line:8226

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3DD(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jdoubleArray obj_pData, jdouble pStep) {

//@line:8235

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3DDD(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jdoubleArray obj_pData, jdouble pStep, jdouble pStepFast) {

//@line:8244

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3DDDLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jdoubleArray obj_pData, jdouble pStep, jdouble pStepFast, jstring obj_format) {

//@line:8253

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalar__Ljava_lang_String_2I_3DDDLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jdoubleArray obj_pData, jdouble pStep, jdouble pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:8264

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalar(label, dataType, (pData != NULL ? &pData[0] : NULL), &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3SI(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jint components) {

//@line:8295

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_S16, &pData[0], components);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3SIS(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jint components, jshort pStep) {

//@line:8304

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_S16, &pData[0], components, &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3SISS(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jint components, jshort pStep, jshort pStepFast) {

//@line:8313

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_S16, &pData[0], components, &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3SISSLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jint components, jshort pStep, jshort pStepFast, jstring obj_format) {

//@line:8322

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_S16, &pData[0], components, &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3SISSLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jshortArray obj_pData, jint components, jshort pStep, jshort pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:8333

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_S16, &pData[0], components, &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3II(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint components) {

//@line:8364

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_S32, &pData[0], components);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3III(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint components, jint pStep) {

//@line:8373

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_S32, &pData[0], components, &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3IIII(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint components, jint pStep, jint pStepFast) {

//@line:8382

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_S32, &pData[0], components, &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3IIIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint components, jint pStep, jint pStepFast, jstring obj_format) {

//@line:8391

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_S32, &pData[0], components, &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3IIIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_pData, jint components, jint pStep, jint pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:8402

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_S32, &pData[0], components, &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3JI(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jint components) {

//@line:8433

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_S64, &pData[0], components);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3JIJ(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jint components, jlong pStep) {

//@line:8442

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_S64, &pData[0], components, &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3JIJJ(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jint components, jlong pStep, jlong pStepFast) {

//@line:8451

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_S64, &pData[0], components, &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3JIJJLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jint components, jlong pStep, jlong pStepFast, jstring obj_format) {

//@line:8460

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_S64, &pData[0], components, &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3JIJJLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jlongArray obj_pData, jint components, jlong pStep, jlong pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:8471

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_S64, &pData[0], components, &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3FI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jint components) {

//@line:8502

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_Float, &pData[0], components);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3FIF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jint components, jfloat pStep) {

//@line:8511

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_Float, &pData[0], components, &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3FIFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jint components, jfloat pStep, jfloat pStepFast) {

//@line:8520

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_Float, &pData[0], components, &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3FIFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jint components, jfloat pStep, jfloat pStepFast, jstring obj_format) {

//@line:8529

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_Float, &pData[0], components, &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3FIFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_pData, jint components, jfloat pStep, jfloat pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:8540

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_Float, &pData[0], components, &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3DI(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jint components) {

//@line:8571

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_Double, &pData[0], components);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3DID(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jint components, jdouble pStep) {

//@line:8580

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_Double, &pData[0], components, &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3DIDD(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jint components, jdouble pStep, jdouble pStepFast) {

//@line:8589

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_Double, &pData[0], components, &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3DIDDLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jint components, jdouble pStep, jdouble pStepFast, jstring obj_format) {

//@line:8598

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_Double, &pData[0], components, &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2_3DIDDLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jdoubleArray obj_pData, jint components, jdouble pStep, jdouble pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:8609

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, ImGuiDataType_Double, &pData[0], components, &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3SI(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jshortArray obj_pData, jint components) {

//@line:8640

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3SIS(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jshortArray obj_pData, jint components, jshort pStep) {

//@line:8649

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3SISS(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jshortArray obj_pData, jint components, jshort pStep, jshort pStepFast) {

//@line:8658

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3SISSLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jshortArray obj_pData, jint components, jshort pStep, jshort pStepFast, jstring obj_format) {

//@line:8667

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3SISSLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jshortArray obj_pData, jint components, jshort pStep, jshort pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:8678

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (short*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3II(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jintArray obj_pData, jint components) {

//@line:8709

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3III(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jintArray obj_pData, jint components, jint pStep) {

//@line:8718

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3IIII(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jintArray obj_pData, jint components, jint pStep, jint pStepFast) {

//@line:8727

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3IIIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jintArray obj_pData, jint components, jint pStep, jint pStepFast, jstring obj_format) {

//@line:8736

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3IIIILjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jintArray obj_pData, jint components, jint pStep, jint pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:8747

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3JI(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jlongArray obj_pData, jint components) {

//@line:8778

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3JIJ(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jlongArray obj_pData, jint components, jlong pStep) {

//@line:8787

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3JIJJ(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jlongArray obj_pData, jint components, jlong pStep, jlong pStepFast) {

//@line:8796

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3JIJJLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jlongArray obj_pData, jint components, jlong pStep, jlong pStepFast, jstring obj_format) {

//@line:8805

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3JIJJLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jlongArray obj_pData, jint components, jlong pStep, jlong pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:8816

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (long*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3FI(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jfloatArray obj_pData, jint components) {

//@line:8847

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3FIF(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jfloatArray obj_pData, jint components, jfloat pStep) {

//@line:8856

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3FIFF(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jfloatArray obj_pData, jint components, jfloat pStep, jfloat pStepFast) {

//@line:8865

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3FIFFLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jfloatArray obj_pData, jint components, jfloat pStep, jfloat pStepFast, jstring obj_format) {

//@line:8874

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3FIFFLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jfloatArray obj_pData, jint components, jfloat pStep, jfloat pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:8885

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3DI(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jdoubleArray obj_pData, jint components) {

//@line:8916

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3DID(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jdoubleArray obj_pData, jint components, jdouble pStep) {

//@line:8925

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3DIDD(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jdoubleArray obj_pData, jint components, jdouble pStep, jdouble pStepFast) {

//@line:8934

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep, &pStepFast);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3DIDDLjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jdoubleArray obj_pData, jint components, jdouble pStep, jdouble pStepFast, jstring obj_format) {

//@line:8943

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep, &pStepFast, format);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nInputScalarN__Ljava_lang_String_2I_3DIDDLjava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jint dataType, jdoubleArray obj_pData, jint components, jdouble pStep, jdouble pStepFast, jstring obj_format, jint imGuiSliderFlags) {

//@line:8954

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pData = obj_pData == NULL ? NULL : (double*)env->GetPrimitiveArrayCritical(obj_pData, JNI_FALSE);
        auto format = obj_format == NULL ? NULL : (char*)env->GetStringUTFChars(obj_format, JNI_FALSE);
        auto _result = ImGui::InputScalarN(label, dataType, &pData[0], components, &pStep, &pStepFast, format, imGuiSliderFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pData != NULL) env->ReleasePrimitiveArrayCritical(obj_pData, pData, JNI_FALSE);
        if (format != NULL) env->ReleaseStringUTFChars(obj_format, format);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorEdit3__Ljava_lang_String_2_3F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_col) {

//@line:8977

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto col = obj_col == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_col, JNI_FALSE);
        auto _result = ImGui::ColorEdit3(label, &col[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (col != NULL) env->ReleasePrimitiveArrayCritical(obj_col, col, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorEdit3__Ljava_lang_String_2_3FI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_col, jint imGuiColorEditFlags) {

//@line:8986

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto col = obj_col == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_col, JNI_FALSE);
        auto _result = ImGui::ColorEdit3(label, &col[0], imGuiColorEditFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (col != NULL) env->ReleasePrimitiveArrayCritical(obj_col, col, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorEdit4__Ljava_lang_String_2_3F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_col) {

//@line:9003

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto col = obj_col == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_col, JNI_FALSE);
        auto _result = ImGui::ColorEdit4(label, &col[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (col != NULL) env->ReleasePrimitiveArrayCritical(obj_col, col, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorEdit4__Ljava_lang_String_2_3FI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_col, jint imGuiColorEditFlags) {

//@line:9012

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto col = obj_col == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_col, JNI_FALSE);
        auto _result = ImGui::ColorEdit4(label, &col[0], imGuiColorEditFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (col != NULL) env->ReleasePrimitiveArrayCritical(obj_col, col, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorPicker3__Ljava_lang_String_2_3F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_col) {

//@line:9029

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto col = obj_col == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_col, JNI_FALSE);
        auto _result = ImGui::ColorPicker3(label, &col[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (col != NULL) env->ReleasePrimitiveArrayCritical(obj_col, col, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorPicker3__Ljava_lang_String_2_3FI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_col, jint imGuiColorEditFlags) {

//@line:9038

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto col = obj_col == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_col, JNI_FALSE);
        auto _result = ImGui::ColorPicker3(label, &col[0], imGuiColorEditFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (col != NULL) env->ReleasePrimitiveArrayCritical(obj_col, col, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorPicker4__Ljava_lang_String_2_3F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_col) {

//@line:9063

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto col = obj_col == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_col, JNI_FALSE);
        auto _result = ImGui::ColorPicker4(label, &col[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (col != NULL) env->ReleasePrimitiveArrayCritical(obj_col, col, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorPicker4__Ljava_lang_String_2_3FI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_col, jint imGuiColorEditFlags) {

//@line:9072

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto col = obj_col == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_col, JNI_FALSE);
        auto _result = ImGui::ColorPicker4(label, &col[0], imGuiColorEditFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (col != NULL) env->ReleasePrimitiveArrayCritical(obj_col, col, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorPicker4__Ljava_lang_String_2_3FI_3F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_col, jint imGuiColorEditFlags, jfloatArray obj_refCol) {

//@line:9081

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto col = obj_col == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_col, JNI_FALSE);
        auto refCol = obj_refCol == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_refCol, JNI_FALSE);
        auto _result = ImGui::ColorPicker4(label, &col[0], imGuiColorEditFlags, &refCol[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (col != NULL) env->ReleasePrimitiveArrayCritical(obj_col, col, JNI_FALSE);
        if (refCol != NULL) env->ReleasePrimitiveArrayCritical(obj_refCol, refCol, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorPicker4__Ljava_lang_String_2_3F_3F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_col, jfloatArray obj_refCol) {

//@line:9092

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto col = obj_col == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_col, JNI_FALSE);
        auto refCol = obj_refCol == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_refCol, JNI_FALSE);
        auto _result = ImGui::ColorPicker4(label, &col[0], 0, &refCol[0]);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (col != NULL) env->ReleasePrimitiveArrayCritical(obj_col, col, JNI_FALSE);
        if (refCol != NULL) env->ReleasePrimitiveArrayCritical(obj_refCol, refCol, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorButton__Ljava_lang_String_2FFFF(JNIEnv* env, jclass clazz, jstring obj_descId, jfloat colX, jfloat colY, jfloat colZ, jfloat colW) {

//@line:9159

        auto descId = obj_descId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_descId, JNI_FALSE);
        ImVec4 col = ImVec4(colX, colY, colZ, colW);
        auto _result = ImGui::ColorButton(descId, col);
        if (descId != NULL) env->ReleaseStringUTFChars(obj_descId, descId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorButton__Ljava_lang_String_2FFFFI(JNIEnv* env, jclass clazz, jstring obj_descId, jfloat colX, jfloat colY, jfloat colZ, jfloat colW, jint imGuiColorEditFlags) {

//@line:9167

        auto descId = obj_descId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_descId, JNI_FALSE);
        ImVec4 col = ImVec4(colX, colY, colZ, colW);
        auto _result = ImGui::ColorButton(descId, col, imGuiColorEditFlags);
        if (descId != NULL) env->ReleaseStringUTFChars(obj_descId, descId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorButton__Ljava_lang_String_2FFFFIFF(JNIEnv* env, jclass clazz, jstring obj_descId, jfloat colX, jfloat colY, jfloat colZ, jfloat colW, jint imGuiColorEditFlags, jfloat sizeX, jfloat sizeY) {

//@line:9175

        auto descId = obj_descId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_descId, JNI_FALSE);
        ImVec4 col = ImVec4(colX, colY, colZ, colW);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::ColorButton(descId, col, imGuiColorEditFlags, size);
        if (descId != NULL) env->ReleaseStringUTFChars(obj_descId, descId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorButton__Ljava_lang_String_2FFFFFF(JNIEnv* env, jclass clazz, jstring obj_descId, jfloat colX, jfloat colY, jfloat colZ, jfloat colW, jfloat sizeX, jfloat sizeY) {

//@line:9184

        auto descId = obj_descId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_descId, JNI_FALSE);
        ImVec4 col = ImVec4(colX, colY, colZ, colW);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::ColorButton(descId, col, 0, size);
        if (descId != NULL) env->ReleaseStringUTFChars(obj_descId, descId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorButton__Ljava_lang_String_2_3F(JNIEnv* env, jclass clazz, jstring obj_descId, jfloatArray obj_col) {

//@line:9253

        auto descId = obj_descId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_descId, JNI_FALSE);
        auto col = obj_col == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_col, JNI_FALSE);
        auto _result = ImGui::ColorButton(descId, ImVec4(col[0], col[1], col[2], col[3]));
        if (descId != NULL) env->ReleaseStringUTFChars(obj_descId, descId);
        if (col != NULL) env->ReleasePrimitiveArrayCritical(obj_col, col, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorButton__Ljava_lang_String_2_3FI(JNIEnv* env, jclass clazz, jstring obj_descId, jfloatArray obj_col, jint imGuiColorEditFlags) {

//@line:9262

        auto descId = obj_descId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_descId, JNI_FALSE);
        auto col = obj_col == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_col, JNI_FALSE);
        auto _result = ImGui::ColorButton(descId, ImVec4(col[0], col[1], col[2], col[3]), imGuiColorEditFlags);
        if (descId != NULL) env->ReleaseStringUTFChars(obj_descId, descId);
        if (col != NULL) env->ReleasePrimitiveArrayCritical(obj_col, col, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorButton__Ljava_lang_String_2_3FIFF(JNIEnv* env, jclass clazz, jstring obj_descId, jfloatArray obj_col, jint imGuiColorEditFlags, jfloat sizeX, jfloat sizeY) {

//@line:9271

        auto descId = obj_descId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_descId, JNI_FALSE);
        auto col = obj_col == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_col, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::ColorButton(descId, ImVec4(col[0], col[1], col[2], col[3]), imGuiColorEditFlags, size);
        if (descId != NULL) env->ReleaseStringUTFChars(obj_descId, descId);
        if (col != NULL) env->ReleasePrimitiveArrayCritical(obj_col, col, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nColorButton__Ljava_lang_String_2_3FFF(JNIEnv* env, jclass clazz, jstring obj_descId, jfloatArray obj_col, jfloat sizeX, jfloat sizeY) {

//@line:9281

        auto descId = obj_descId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_descId, JNI_FALSE);
        auto col = obj_col == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_col, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::ColorButton(descId, ImVec4(col[0], col[1], col[2], col[3]), 0, size);
        if (descId != NULL) env->ReleaseStringUTFChars(obj_descId, descId);
        if (col != NULL) env->ReleasePrimitiveArrayCritical(obj_col, col, JNI_FALSE);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetColorEditOptions(JNIEnv* env, jclass clazz, jint imGuiColorEditFlags) {


//@line:9299

        ImGui::SetColorEditOptions(imGuiColorEditFlags);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nTreeNode__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:9310

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::TreeNode(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nTreeNode__Ljava_lang_String_2Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_strId, jstring obj_label) {

//@line:9325

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::TreeNode(strId, label, NULL);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nTreeNode__JLjava_lang_String_2(JNIEnv* env, jclass clazz, jlong ptrId, jstring obj_label) {

//@line:9338

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::TreeNode((void*)ptrId, label, NULL);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nTreeNodeEx__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:9353

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::TreeNodeEx(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nTreeNodeEx__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jint flags) {

//@line:9360

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::TreeNodeEx(label, flags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nTreeNodeEx__Ljava_lang_String_2ILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_strId, jint flags, jstring obj_label) {

//@line:9371

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::TreeNodeEx(strId, flags, label, NULL);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nTreeNodeEx__JILjava_lang_String_2(JNIEnv* env, jclass clazz, jlong ptrId, jint flags, jstring obj_label) {

//@line:9384

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::TreeNodeEx((void*)ptrId, flags, label, NULL);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTreePush__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_strId) {

//@line:9398

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImGui::TreePush(strId);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTreePush__J(JNIEnv* env, jclass clazz, jlong ptrId) {


//@line:9411

        ImGui::TreePush((void*)ptrId);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTreePop(JNIEnv* env, jclass clazz) {


//@line:9422

        ImGui::TreePop();
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetTreeNodeToLabelSpacing(JNIEnv* env, jclass clazz) {


//@line:9433

        return ImGui::GetTreeNodeToLabelSpacing();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nCollapsingHeader__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:9451

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::CollapsingHeader(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nCollapsingHeader__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jint imGuiTreeNodeFlags) {

//@line:9458

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::CollapsingHeader(label, imGuiTreeNodeFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nCollapsingHeader__Ljava_lang_String_2_3Z(JNIEnv* env, jclass clazz, jstring obj_label, jbooleanArray obj_pVisible) {

//@line:9481

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pVisible = obj_pVisible == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pVisible, JNI_FALSE);
        auto _result = ImGui::CollapsingHeader(label, (pVisible != NULL ? &pVisible[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pVisible != NULL) env->ReleasePrimitiveArrayCritical(obj_pVisible, pVisible, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nCollapsingHeader__Ljava_lang_String_2_3ZI(JNIEnv* env, jclass clazz, jstring obj_label, jbooleanArray obj_pVisible, jint imGuiTreeNodeFlags) {

//@line:9490

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pVisible = obj_pVisible == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pVisible, JNI_FALSE);
        auto _result = ImGui::CollapsingHeader(label, (pVisible != NULL ? &pVisible[0] : NULL), imGuiTreeNodeFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pVisible != NULL) env->ReleasePrimitiveArrayCritical(obj_pVisible, pVisible, JNI_FALSE);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextItemOpen__Z(JNIEnv* env, jclass clazz, jboolean isOpen) {


//@line:9513

        ImGui::SetNextItemOpen(isOpen);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextItemOpen__ZI(JNIEnv* env, jclass clazz, jboolean isOpen, jint cond) {


//@line:9517

        ImGui::SetNextItemOpen(isOpen, cond);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSelectable__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:9569

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::Selectable(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSelectable__Ljava_lang_String_2Z(JNIEnv* env, jclass clazz, jstring obj_label, jboolean selected) {

//@line:9576

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::Selectable(label, selected);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSelectable__Ljava_lang_String_2ZI(JNIEnv* env, jclass clazz, jstring obj_label, jboolean selected, jint imGuiSelectableFlags) {

//@line:9583

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::Selectable(label, selected, imGuiSelectableFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSelectable__Ljava_lang_String_2ZIFF(JNIEnv* env, jclass clazz, jstring obj_label, jboolean selected, jint imGuiSelectableFlags, jfloat sizeX, jfloat sizeY) {

//@line:9590

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::Selectable(label, selected, imGuiSelectableFlags, size);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSelectable__Ljava_lang_String_2IFF(JNIEnv* env, jclass clazz, jstring obj_label, jint imGuiSelectableFlags, jfloat sizeX, jfloat sizeY) {

//@line:9598

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::Selectable(label, false, imGuiSelectableFlags, size);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSelectable__Ljava_lang_String_2FF(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY) {

//@line:9606

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::Selectable(label, false, 0, size);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSelectable__Ljava_lang_String_2ZFF(JNIEnv* env, jclass clazz, jstring obj_label, jboolean selected, jfloat sizeX, jfloat sizeY) {

//@line:9614

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::Selectable(label, selected, 0, size);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSelectable__Ljava_lang_String_2_3Z(JNIEnv* env, jclass clazz, jstring obj_label, jbooleanArray obj_pSelected) {

//@line:9646

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pSelected = obj_pSelected == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pSelected, JNI_FALSE);
        auto _result = ImGui::Selectable(label, (pSelected != NULL ? &pSelected[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pSelected != NULL) env->ReleasePrimitiveArrayCritical(obj_pSelected, pSelected, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSelectable__Ljava_lang_String_2_3ZI(JNIEnv* env, jclass clazz, jstring obj_label, jbooleanArray obj_pSelected, jint imGuiSelectableFlags) {

//@line:9655

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pSelected = obj_pSelected == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pSelected, JNI_FALSE);
        auto _result = ImGui::Selectable(label, (pSelected != NULL ? &pSelected[0] : NULL), imGuiSelectableFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pSelected != NULL) env->ReleasePrimitiveArrayCritical(obj_pSelected, pSelected, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSelectable__Ljava_lang_String_2_3ZIFF(JNIEnv* env, jclass clazz, jstring obj_label, jbooleanArray obj_pSelected, jint imGuiSelectableFlags, jfloat sizeX, jfloat sizeY) {

//@line:9664

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pSelected = obj_pSelected == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pSelected, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::Selectable(label, (pSelected != NULL ? &pSelected[0] : NULL), imGuiSelectableFlags, size);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pSelected != NULL) env->ReleasePrimitiveArrayCritical(obj_pSelected, pSelected, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSelectable__Ljava_lang_String_2_3ZFF(JNIEnv* env, jclass clazz, jstring obj_label, jbooleanArray obj_pSelected, jfloat sizeX, jfloat sizeY) {

//@line:9674

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pSelected = obj_pSelected == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pSelected, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::Selectable(label, (pSelected != NULL ? &pSelected[0] : NULL), 0, size);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pSelected != NULL) env->ReleasePrimitiveArrayCritical(obj_pSelected, pSelected, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginListBox__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:9712

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::BeginListBox(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginListBox__Ljava_lang_String_2FF(JNIEnv* env, jclass clazz, jstring obj_label, jfloat sizeX, jfloat sizeY) {

//@line:9719

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::BeginListBox(label, size);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nEndListBox(JNIEnv* env, jclass clazz) {


//@line:9734

        ImGui::EndListBox();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nListBox__Ljava_lang_String_2_3I_3Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_currentItem, jobjectArray obj_items, jint itemsCount) {

//@line:9746

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto currentItem = obj_currentItem == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_currentItem, JNI_FALSE);
        const char* items[itemsCount];
        for (int i = 0; i < itemsCount; i++) {
            const jstring str = (jstring)env->GetObjectArrayElement(obj_items, i);
            auto rawStr = (char*)env->GetStringUTFChars(str, JNI_FALSE);
            items[i] = rawStr;
        };
        ImGui::ListBox(label, (currentItem != NULL ? &currentItem[0] : NULL), items, itemsCount);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (currentItem != NULL) env->ReleasePrimitiveArrayCritical(obj_currentItem, currentItem, JNI_FALSE);
        for (int i = 0; i < itemsCount; i++) {
            const jstring str = (jstring)env->GetObjectArrayElement(obj_items, i);
            env->ReleaseStringUTFChars(str, items[i]);
        };
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nListBox__Ljava_lang_String_2_3I_3Ljava_lang_String_2II(JNIEnv* env, jclass clazz, jstring obj_label, jintArray obj_currentItem, jobjectArray obj_items, jint itemsCount, jint heightInItems) {

//@line:9764

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto currentItem = obj_currentItem == NULL ? NULL : (int*)env->GetPrimitiveArrayCritical(obj_currentItem, JNI_FALSE);
        const char* items[itemsCount];
        for (int i = 0; i < itemsCount; i++) {
            const jstring str = (jstring)env->GetObjectArrayElement(obj_items, i);
            auto rawStr = (char*)env->GetStringUTFChars(str, JNI_FALSE);
            items[i] = rawStr;
        };
        ImGui::ListBox(label, (currentItem != NULL ? &currentItem[0] : NULL), items, itemsCount, heightInItems);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (currentItem != NULL) env->ReleasePrimitiveArrayCritical(obj_currentItem, currentItem, JNI_FALSE);
        for (int i = 0; i < itemsCount; i++) {
            const jstring str = (jstring)env->GetObjectArrayElement(obj_items, i);
            env->ReleaseStringUTFChars(str, items[i]);
        };
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotLines__Ljava_lang_String_2_3FI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount) {

//@line:9849

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        ImGui::PlotLines(label, &values[0], valuesCount);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotLines__Ljava_lang_String_2_3FII(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jint valuesOffset) {

//@line:9857

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        ImGui::PlotLines(label, &values[0], valuesCount, valuesOffset);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotLines__Ljava_lang_String_2_3FIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jint valuesOffset, jstring obj_overlayText) {

//@line:9865

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        auto overlayText = obj_overlayText == NULL ? NULL : (char*)env->GetStringUTFChars(obj_overlayText, JNI_FALSE);
        ImGui::PlotLines(label, &values[0], valuesCount, valuesOffset, overlayText);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
        if (overlayText != NULL) env->ReleaseStringUTFChars(obj_overlayText, overlayText);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotLines__Ljava_lang_String_2_3FIILjava_lang_String_2F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jint valuesOffset, jstring obj_overlayText, jfloat scaleMin) {

//@line:9875

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        auto overlayText = obj_overlayText == NULL ? NULL : (char*)env->GetStringUTFChars(obj_overlayText, JNI_FALSE);
        ImGui::PlotLines(label, &values[0], valuesCount, valuesOffset, overlayText, scaleMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
        if (overlayText != NULL) env->ReleaseStringUTFChars(obj_overlayText, overlayText);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotLines__Ljava_lang_String_2_3FIILjava_lang_String_2FF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jint valuesOffset, jstring obj_overlayText, jfloat scaleMin, jfloat scaleMax) {

//@line:9885

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        auto overlayText = obj_overlayText == NULL ? NULL : (char*)env->GetStringUTFChars(obj_overlayText, JNI_FALSE);
        ImGui::PlotLines(label, &values[0], valuesCount, valuesOffset, overlayText, scaleMin, scaleMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
        if (overlayText != NULL) env->ReleaseStringUTFChars(obj_overlayText, overlayText);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotLines__Ljava_lang_String_2_3FIILjava_lang_String_2FFFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jint valuesOffset, jstring obj_overlayText, jfloat scaleMin, jfloat scaleMax, jfloat graphSizeX, jfloat graphSizeY) {

//@line:9895

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        auto overlayText = obj_overlayText == NULL ? NULL : (char*)env->GetStringUTFChars(obj_overlayText, JNI_FALSE);
        ImVec2 graphSize = ImVec2(graphSizeX, graphSizeY);
        ImGui::PlotLines(label, &values[0], valuesCount, valuesOffset, overlayText, scaleMin, scaleMax, graphSize);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
        if (overlayText != NULL) env->ReleaseStringUTFChars(obj_overlayText, overlayText);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotLines__Ljava_lang_String_2_3FIILjava_lang_String_2FFFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jint valuesOffset, jstring obj_overlayText, jfloat scaleMin, jfloat scaleMax, jfloat graphSizeX, jfloat graphSizeY, jint stride) {

//@line:9906

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        auto overlayText = obj_overlayText == NULL ? NULL : (char*)env->GetStringUTFChars(obj_overlayText, JNI_FALSE);
        ImVec2 graphSize = ImVec2(graphSizeX, graphSizeY);
        ImGui::PlotLines(label, &values[0], valuesCount, valuesOffset, overlayText, scaleMin, scaleMax, graphSize, stride);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
        if (overlayText != NULL) env->ReleaseStringUTFChars(obj_overlayText, overlayText);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotLines__Ljava_lang_String_2_3FILjava_lang_String_2FFFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jstring obj_overlayText, jfloat scaleMin, jfloat scaleMax, jfloat graphSizeX, jfloat graphSizeY, jint stride) {

//@line:9917

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        auto overlayText = obj_overlayText == NULL ? NULL : (char*)env->GetStringUTFChars(obj_overlayText, JNI_FALSE);
        ImVec2 graphSize = ImVec2(graphSizeX, graphSizeY);
        ImGui::PlotLines(label, &values[0], valuesCount, 0, overlayText, scaleMin, scaleMax, graphSize, stride);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
        if (overlayText != NULL) env->ReleaseStringUTFChars(obj_overlayText, overlayText);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotLines__Ljava_lang_String_2_3FIFFFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jfloat scaleMin, jfloat scaleMax, jfloat graphSizeX, jfloat graphSizeY, jint stride) {

//@line:9928

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        ImVec2 graphSize = ImVec2(graphSizeX, graphSizeY);
        ImGui::PlotLines(label, &values[0], valuesCount, 0, NULL, scaleMin, scaleMax, graphSize, stride);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotLines__Ljava_lang_String_2_3FIIFFFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jint valuesOffset, jfloat scaleMin, jfloat scaleMax, jfloat graphSizeX, jfloat graphSizeY, jint stride) {

//@line:9937

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        ImVec2 graphSize = ImVec2(graphSizeX, graphSizeY);
        ImGui::PlotLines(label, &values[0], valuesCount, valuesOffset, NULL, scaleMin, scaleMax, graphSize, stride);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotLines__Ljava_lang_String_2_3FIILjava_lang_String_2FFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jint valuesOffset, jstring obj_overlayText, jfloat scaleMin, jfloat scaleMax, jint stride) {

//@line:9946

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        auto overlayText = obj_overlayText == NULL ? NULL : (char*)env->GetStringUTFChars(obj_overlayText, JNI_FALSE);
        ImGui::PlotLines(label, &values[0], valuesCount, valuesOffset, overlayText, scaleMin, scaleMax, ImVec2(0,0), stride);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
        if (overlayText != NULL) env->ReleaseStringUTFChars(obj_overlayText, overlayText);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotHistogram__Ljava_lang_String_2_3FI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount) {

//@line:10020

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        ImGui::PlotHistogram(label, &values[0], valuesCount);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotHistogram__Ljava_lang_String_2_3FII(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jint valuesOffset) {

//@line:10028

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        ImGui::PlotHistogram(label, &values[0], valuesCount, valuesOffset);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotHistogram__Ljava_lang_String_2_3FIILjava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jint valuesOffset, jstring obj_overlayText) {

//@line:10036

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        auto overlayText = obj_overlayText == NULL ? NULL : (char*)env->GetStringUTFChars(obj_overlayText, JNI_FALSE);
        ImGui::PlotHistogram(label, &values[0], valuesCount, valuesOffset, overlayText);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
        if (overlayText != NULL) env->ReleaseStringUTFChars(obj_overlayText, overlayText);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotHistogram__Ljava_lang_String_2_3FIILjava_lang_String_2F(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jint valuesOffset, jstring obj_overlayText, jfloat scaleMin) {

//@line:10046

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        auto overlayText = obj_overlayText == NULL ? NULL : (char*)env->GetStringUTFChars(obj_overlayText, JNI_FALSE);
        ImGui::PlotHistogram(label, &values[0], valuesCount, valuesOffset, overlayText, scaleMin);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
        if (overlayText != NULL) env->ReleaseStringUTFChars(obj_overlayText, overlayText);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotHistogram__Ljava_lang_String_2_3FIILjava_lang_String_2FF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jint valuesOffset, jstring obj_overlayText, jfloat scaleMin, jfloat scaleMax) {

//@line:10056

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        auto overlayText = obj_overlayText == NULL ? NULL : (char*)env->GetStringUTFChars(obj_overlayText, JNI_FALSE);
        ImGui::PlotHistogram(label, &values[0], valuesCount, valuesOffset, overlayText, scaleMin, scaleMax);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
        if (overlayText != NULL) env->ReleaseStringUTFChars(obj_overlayText, overlayText);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotHistogram__Ljava_lang_String_2_3FIILjava_lang_String_2FFFF(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jint valuesOffset, jstring obj_overlayText, jfloat scaleMin, jfloat scaleMax, jfloat graphSizeX, jfloat graphSizeY) {

//@line:10066

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        auto overlayText = obj_overlayText == NULL ? NULL : (char*)env->GetStringUTFChars(obj_overlayText, JNI_FALSE);
        ImVec2 graphSize = ImVec2(graphSizeX, graphSizeY);
        ImGui::PlotHistogram(label, &values[0], valuesCount, valuesOffset, overlayText, scaleMin, scaleMax, graphSize);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
        if (overlayText != NULL) env->ReleaseStringUTFChars(obj_overlayText, overlayText);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotHistogram__Ljava_lang_String_2_3FIILjava_lang_String_2FFFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jint valuesOffset, jstring obj_overlayText, jfloat scaleMin, jfloat scaleMax, jfloat graphSizeX, jfloat graphSizeY, jint stride) {

//@line:10077

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        auto overlayText = obj_overlayText == NULL ? NULL : (char*)env->GetStringUTFChars(obj_overlayText, JNI_FALSE);
        ImVec2 graphSize = ImVec2(graphSizeX, graphSizeY);
        ImGui::PlotHistogram(label, &values[0], valuesCount, valuesOffset, overlayText, scaleMin, scaleMax, graphSize, stride);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
        if (overlayText != NULL) env->ReleaseStringUTFChars(obj_overlayText, overlayText);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotHistogram__Ljava_lang_String_2_3FILjava_lang_String_2FFFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jstring obj_overlayText, jfloat scaleMin, jfloat scaleMax, jfloat graphSizeX, jfloat graphSizeY, jint stride) {

//@line:10088

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        auto overlayText = obj_overlayText == NULL ? NULL : (char*)env->GetStringUTFChars(obj_overlayText, JNI_FALSE);
        ImVec2 graphSize = ImVec2(graphSizeX, graphSizeY);
        ImGui::PlotHistogram(label, &values[0], valuesCount, 0, overlayText, scaleMin, scaleMax, graphSize, stride);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
        if (overlayText != NULL) env->ReleaseStringUTFChars(obj_overlayText, overlayText);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotHistogram__Ljava_lang_String_2_3FIFFFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jfloat scaleMin, jfloat scaleMax, jfloat graphSizeX, jfloat graphSizeY, jint stride) {

//@line:10099

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        ImVec2 graphSize = ImVec2(graphSizeX, graphSizeY);
        ImGui::PlotHistogram(label, &values[0], valuesCount, 0, NULL, scaleMin, scaleMax, graphSize, stride);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotHistogram__Ljava_lang_String_2_3FIIFFFFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jint valuesOffset, jfloat scaleMin, jfloat scaleMax, jfloat graphSizeX, jfloat graphSizeY, jint stride) {

//@line:10108

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        ImVec2 graphSize = ImVec2(graphSizeX, graphSizeY);
        ImGui::PlotHistogram(label, &values[0], valuesCount, valuesOffset, NULL, scaleMin, scaleMax, graphSize, stride);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPlotHistogram__Ljava_lang_String_2_3FIILjava_lang_String_2FFI(JNIEnv* env, jclass clazz, jstring obj_label, jfloatArray obj_values, jint valuesCount, jint valuesOffset, jstring obj_overlayText, jfloat scaleMin, jfloat scaleMax, jint stride) {

//@line:10117

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto values = obj_values == NULL ? NULL : (float*)env->GetPrimitiveArrayCritical(obj_values, JNI_FALSE);
        auto overlayText = obj_overlayText == NULL ? NULL : (char*)env->GetStringUTFChars(obj_overlayText, JNI_FALSE);
        ImGui::PlotHistogram(label, &values[0], valuesCount, valuesOffset, overlayText, scaleMin, scaleMax, ImVec2(0,0), stride);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (values != NULL) env->ReleasePrimitiveArrayCritical(obj_values, values, JNI_FALSE);
        if (overlayText != NULL) env->ReleaseStringUTFChars(obj_overlayText, overlayText);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nValue(JNIEnv* env, jclass clazz, jstring obj_prefix, jstring obj_value) {
	char* prefix = (char*)env->GetStringUTFChars(obj_prefix, 0);
	char* value = (char*)env->GetStringUTFChars(obj_value, 0);


//@line:10138

        ImGui::Value(prefix, value);
    
	env->ReleaseStringUTFChars(obj_prefix, prefix);
	env->ReleaseStringUTFChars(obj_value, value);

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginMenuBar(JNIEnv* env, jclass clazz) {


//@line:10154

        return ImGui::BeginMenuBar();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nEndMenuBar(JNIEnv* env, jclass clazz) {


//@line:10165

        ImGui::EndMenuBar();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginMainMenuBar(JNIEnv* env, jclass clazz) {


//@line:10176

        return ImGui::BeginMainMenuBar();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nEndMainMenuBar(JNIEnv* env, jclass clazz) {


//@line:10187

        ImGui::EndMainMenuBar();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginMenu__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:10205

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::BeginMenu(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginMenu__Ljava_lang_String_2Z(JNIEnv* env, jclass clazz, jstring obj_label, jboolean enabled) {

//@line:10212

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::BeginMenu(label, enabled);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nEndMenu(JNIEnv* env, jclass clazz) {


//@line:10226

        ImGui::EndMenu();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nMenuItem__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:10251

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::MenuItem(label, NULL);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nMenuItem__Ljava_lang_String_2Z(JNIEnv* env, jclass clazz, jstring obj_label, jboolean selected) {

//@line:10258

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::MenuItem(label, NULL, selected);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nMenuItem__Ljava_lang_String_2ZZ(JNIEnv* env, jclass clazz, jstring obj_label, jboolean selected, jboolean enabled) {

//@line:10265

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::MenuItem(label, NULL, selected, enabled);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nMenuItem__Ljava_lang_String_2Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label, jstring obj_shortcut) {

//@line:10293

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto shortcut = obj_shortcut == NULL ? NULL : (char*)env->GetStringUTFChars(obj_shortcut, JNI_FALSE);
        auto _result = ImGui::MenuItem(label, shortcut);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (shortcut != NULL) env->ReleaseStringUTFChars(obj_shortcut, shortcut);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nMenuItem__Ljava_lang_String_2Ljava_lang_String_2Z(JNIEnv* env, jclass clazz, jstring obj_label, jstring obj_shortcut, jboolean selected) {

//@line:10302

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto shortcut = obj_shortcut == NULL ? NULL : (char*)env->GetStringUTFChars(obj_shortcut, JNI_FALSE);
        auto _result = ImGui::MenuItem(label, shortcut, selected);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (shortcut != NULL) env->ReleaseStringUTFChars(obj_shortcut, shortcut);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nMenuItem__Ljava_lang_String_2Ljava_lang_String_2ZZ(JNIEnv* env, jclass clazz, jstring obj_label, jstring obj_shortcut, jboolean selected, jboolean enabled) {

//@line:10311

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto shortcut = obj_shortcut == NULL ? NULL : (char*)env->GetStringUTFChars(obj_shortcut, JNI_FALSE);
        auto _result = ImGui::MenuItem(label, shortcut, selected, enabled);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (shortcut != NULL) env->ReleaseStringUTFChars(obj_shortcut, shortcut);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nMenuItem__Ljava_lang_String_2Ljava_lang_String_2_3Z(JNIEnv* env, jclass clazz, jstring obj_label, jstring obj_shortcut, jbooleanArray obj_pSelected) {

//@line:10334

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto shortcut = obj_shortcut == NULL ? NULL : (char*)env->GetStringUTFChars(obj_shortcut, JNI_FALSE);
        auto pSelected = obj_pSelected == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pSelected, JNI_FALSE);
        auto _result = ImGui::MenuItem(label, shortcut, (pSelected != NULL ? &pSelected[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (shortcut != NULL) env->ReleaseStringUTFChars(obj_shortcut, shortcut);
        if (pSelected != NULL) env->ReleasePrimitiveArrayCritical(obj_pSelected, pSelected, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nMenuItem__Ljava_lang_String_2Ljava_lang_String_2_3ZZ(JNIEnv* env, jclass clazz, jstring obj_label, jstring obj_shortcut, jbooleanArray obj_pSelected, jboolean enabled) {

//@line:10345

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto shortcut = obj_shortcut == NULL ? NULL : (char*)env->GetStringUTFChars(obj_shortcut, JNI_FALSE);
        auto pSelected = obj_pSelected == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pSelected, JNI_FALSE);
        auto _result = ImGui::MenuItem(label, shortcut, (pSelected != NULL ? &pSelected[0] : NULL), enabled);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (shortcut != NULL) env->ReleaseStringUTFChars(obj_shortcut, shortcut);
        if (pSelected != NULL) env->ReleasePrimitiveArrayCritical(obj_pSelected, pSelected, JNI_FALSE);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nBeginTooltip(JNIEnv* env, jclass clazz) {


//@line:10368

        ImGui::BeginTooltip();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nEndTooltip(JNIEnv* env, jclass clazz) {


//@line:10379

        ImGui::EndTooltip();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetTooltip(JNIEnv* env, jclass clazz, jstring obj_text) {

//@line:10390

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        ImGui::SetTooltip(text, NULL);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginItemTooltip(JNIEnv* env, jclass clazz) {


//@line:10408

        return ImGui::BeginItemTooltip();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetItemTooltip(JNIEnv* env, jclass clazz, jstring obj_text) {

//@line:10419

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        ImGui::SetItemTooltip(text, NULL);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopup__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_strId) {

//@line:10450

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto _result = ImGui::BeginPopup(strId);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopup__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_strId, jint imGuiWindowFlags) {

//@line:10457

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto _result = ImGui::BeginPopup(strId, imGuiWindowFlags);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopupModal__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_name) {

//@line:10492

        auto name = obj_name == NULL ? NULL : (char*)env->GetStringUTFChars(obj_name, JNI_FALSE);
        auto _result = ImGui::BeginPopupModal(name);
        if (name != NULL) env->ReleaseStringUTFChars(obj_name, name);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopupModal__Ljava_lang_String_2_3Z(JNIEnv* env, jclass clazz, jstring obj_name, jbooleanArray obj_pOpen) {

//@line:10499

        auto name = obj_name == NULL ? NULL : (char*)env->GetStringUTFChars(obj_name, JNI_FALSE);
        auto pOpen = obj_pOpen == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pOpen, JNI_FALSE);
        auto _result = ImGui::BeginPopupModal(name, (pOpen != NULL ? &pOpen[0] : NULL));
        if (name != NULL) env->ReleaseStringUTFChars(obj_name, name);
        if (pOpen != NULL) env->ReleasePrimitiveArrayCritical(obj_pOpen, pOpen, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopupModal__Ljava_lang_String_2_3ZI(JNIEnv* env, jclass clazz, jstring obj_name, jbooleanArray obj_pOpen, jint imGuiWindowFlags) {

//@line:10508

        auto name = obj_name == NULL ? NULL : (char*)env->GetStringUTFChars(obj_name, JNI_FALSE);
        auto pOpen = obj_pOpen == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pOpen, JNI_FALSE);
        auto _result = ImGui::BeginPopupModal(name, (pOpen != NULL ? &pOpen[0] : NULL), imGuiWindowFlags);
        if (name != NULL) env->ReleaseStringUTFChars(obj_name, name);
        if (pOpen != NULL) env->ReleasePrimitiveArrayCritical(obj_pOpen, pOpen, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopupModal__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_name, jint imGuiWindowFlags) {

//@line:10517

        auto name = obj_name == NULL ? NULL : (char*)env->GetStringUTFChars(obj_name, JNI_FALSE);
        auto _result = ImGui::BeginPopupModal(name, NULL, imGuiWindowFlags);
        if (name != NULL) env->ReleaseStringUTFChars(obj_name, name);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nEndPopup(JNIEnv* env, jclass clazz) {


//@line:10531

        ImGui::EndPopup();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nOpenPopup__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_strId) {

//@line:10556

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImGui::OpenPopup(strId);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nOpenPopup__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_strId, jint imGuiPopupFlags) {

//@line:10562

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImGui::OpenPopup(strId, imGuiPopupFlags);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nOpenPopup__I(JNIEnv* env, jclass clazz, jint id) {


//@line:10582

        ImGui::OpenPopup((ImGuiID)id);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nOpenPopup__II(JNIEnv* env, jclass clazz, jint id, jint imGuiPopupFlags) {


//@line:10586

        ImGui::OpenPopup((ImGuiID)id, imGuiPopupFlags);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nOpenPopupOnItemClick__(JNIEnv* env, jclass clazz) {


//@line:10618

        ImGui::OpenPopupOnItemClick();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nOpenPopupOnItemClick__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_strId) {

//@line:10622

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImGui::OpenPopupOnItemClick(strId);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nOpenPopupOnItemClick__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_strId, jint imGuiPopupFlags) {

//@line:10628

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        ImGui::OpenPopupOnItemClick(strId, imGuiPopupFlags);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nOpenPopupOnItemClick__I(JNIEnv* env, jclass clazz, jint imGuiPopupFlags) {


//@line:10634

        ImGui::OpenPopupOnItemClick(NULL, imGuiPopupFlags);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nCloseCurrentPopup(JNIEnv* env, jclass clazz) {


//@line:10645

        ImGui::CloseCurrentPopup();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopupContextItem__(JNIEnv* env, jclass clazz) {


//@line:10687

        return ImGui::BeginPopupContextItem();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopupContextItem__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_strId) {

//@line:10691

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto _result = ImGui::BeginPopupContextItem(strId);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopupContextItem__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_strId, jint imGuiPopupFlags) {

//@line:10698

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto _result = ImGui::BeginPopupContextItem(strId, imGuiPopupFlags);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopupContextItem__I(JNIEnv* env, jclass clazz, jint imGuiPopupFlags) {


//@line:10705

        return ImGui::BeginPopupContextItem(NULL, imGuiPopupFlags);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopupContextWindow__(JNIEnv* env, jclass clazz) {


//@line:10737

        return ImGui::BeginPopupContextWindow();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopupContextWindow__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_strId) {

//@line:10741

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto _result = ImGui::BeginPopupContextWindow(strId);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopupContextWindow__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_strId, jint imGuiPopupFlags) {

//@line:10748

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto _result = ImGui::BeginPopupContextWindow(strId, imGuiPopupFlags);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopupContextWindow__I(JNIEnv* env, jclass clazz, jint imGuiPopupFlags) {


//@line:10755

        return ImGui::BeginPopupContextWindow(NULL, imGuiPopupFlags);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopupContextVoid__(JNIEnv* env, jclass clazz) {


//@line:10787

        return ImGui::BeginPopupContextVoid();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopupContextVoid__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_strId) {

//@line:10791

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto _result = ImGui::BeginPopupContextVoid(strId);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopupContextVoid__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_strId, jint imGuiPopupFlags) {

//@line:10798

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto _result = ImGui::BeginPopupContextVoid(strId, imGuiPopupFlags);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginPopupContextVoid__I(JNIEnv* env, jclass clazz, jint imGuiPopupFlags) {


//@line:10805

        return ImGui::BeginPopupContextVoid(NULL, imGuiPopupFlags);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsPopupOpen__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_strId) {

//@line:10828

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto _result = ImGui::IsPopupOpen(strId);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsPopupOpen__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_strId, jint imGuiPopupFlags) {

//@line:10835

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto _result = ImGui::IsPopupOpen(strId, imGuiPopupFlags);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginTable__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_id, jint columns) {

//@line:10904

        auto id = obj_id == NULL ? NULL : (char*)env->GetStringUTFChars(obj_id, JNI_FALSE);
        auto _result = ImGui::BeginTable(id, columns);
        if (id != NULL) env->ReleaseStringUTFChars(obj_id, id);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginTable__Ljava_lang_String_2II(JNIEnv* env, jclass clazz, jstring obj_id, jint columns, jint imGuiTableFlags) {

//@line:10911

        auto id = obj_id == NULL ? NULL : (char*)env->GetStringUTFChars(obj_id, JNI_FALSE);
        auto _result = ImGui::BeginTable(id, columns, imGuiTableFlags);
        if (id != NULL) env->ReleaseStringUTFChars(obj_id, id);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginTable__Ljava_lang_String_2IIFF(JNIEnv* env, jclass clazz, jstring obj_id, jint columns, jint imGuiTableFlags, jfloat outerSizeX, jfloat outerSizeY) {

//@line:10918

        auto id = obj_id == NULL ? NULL : (char*)env->GetStringUTFChars(obj_id, JNI_FALSE);
        ImVec2 outerSize = ImVec2(outerSizeX, outerSizeY);
        auto _result = ImGui::BeginTable(id, columns, imGuiTableFlags, outerSize);
        if (id != NULL) env->ReleaseStringUTFChars(obj_id, id);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginTable__Ljava_lang_String_2IIFFF(JNIEnv* env, jclass clazz, jstring obj_id, jint columns, jint imGuiTableFlags, jfloat outerSizeX, jfloat outerSizeY, jfloat innerWidth) {

//@line:10926

        auto id = obj_id == NULL ? NULL : (char*)env->GetStringUTFChars(obj_id, JNI_FALSE);
        ImVec2 outerSize = ImVec2(outerSizeX, outerSizeY);
        auto _result = ImGui::BeginTable(id, columns, imGuiTableFlags, outerSize, innerWidth);
        if (id != NULL) env->ReleaseStringUTFChars(obj_id, id);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginTable__Ljava_lang_String_2IFFF(JNIEnv* env, jclass clazz, jstring obj_id, jint columns, jfloat outerSizeX, jfloat outerSizeY, jfloat innerWidth) {

//@line:10934

        auto id = obj_id == NULL ? NULL : (char*)env->GetStringUTFChars(obj_id, JNI_FALSE);
        ImVec2 outerSize = ImVec2(outerSizeX, outerSizeY);
        auto _result = ImGui::BeginTable(id, columns, 0, outerSize, innerWidth);
        if (id != NULL) env->ReleaseStringUTFChars(obj_id, id);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginTable__Ljava_lang_String_2IF(JNIEnv* env, jclass clazz, jstring obj_id, jint columns, jfloat innerWidth) {

//@line:10942

        auto id = obj_id == NULL ? NULL : (char*)env->GetStringUTFChars(obj_id, JNI_FALSE);
        auto _result = ImGui::BeginTable(id, columns, 0, ImVec2(0,0), innerWidth);
        if (id != NULL) env->ReleaseStringUTFChars(obj_id, id);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginTable__Ljava_lang_String_2IIF(JNIEnv* env, jclass clazz, jstring obj_id, jint columns, jint imGuiTableFlags, jfloat innerWidth) {

//@line:10949

        auto id = obj_id == NULL ? NULL : (char*)env->GetStringUTFChars(obj_id, JNI_FALSE);
        auto _result = ImGui::BeginTable(id, columns, imGuiTableFlags, ImVec2(0,0), innerWidth);
        if (id != NULL) env->ReleaseStringUTFChars(obj_id, id);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nEndTable(JNIEnv* env, jclass clazz) {


//@line:10963

        ImGui::EndTable();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTableNextRow__(JNIEnv* env, jclass clazz) {


//@line:10995

        ImGui::TableNextRow();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTableNextRow__I(JNIEnv* env, jclass clazz, jint imGuiTableRowFlags) {


//@line:10999

        ImGui::TableNextRow(imGuiTableRowFlags);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTableNextRow__IF(JNIEnv* env, jclass clazz, jint imGuiTableRowFlags, jfloat minRowHeight) {


//@line:11003

        ImGui::TableNextRow(imGuiTableRowFlags, minRowHeight);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTableNextRow__F(JNIEnv* env, jclass clazz, jfloat minRowHeight) {


//@line:11007

        ImGui::TableNextRow(0, minRowHeight);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nTableNextColumn(JNIEnv* env, jclass clazz) {


//@line:11018

        return ImGui::TableNextColumn();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nTableSetColumnIndex(JNIEnv* env, jclass clazz, jint columnN) {


//@line:11029

        return ImGui::TableSetColumnIndex(columnN);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTableSetupColumn__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:11066

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        ImGui::TableSetupColumn(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTableSetupColumn__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jint imGuiTableColumnFlags) {

//@line:11072

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        ImGui::TableSetupColumn(label, imGuiTableColumnFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTableSetupColumn__Ljava_lang_String_2IF(JNIEnv* env, jclass clazz, jstring obj_label, jint imGuiTableColumnFlags, jfloat initWidthOrWeight) {

//@line:11078

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        ImGui::TableSetupColumn(label, imGuiTableColumnFlags, initWidthOrWeight);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTableSetupColumn__Ljava_lang_String_2IFI(JNIEnv* env, jclass clazz, jstring obj_label, jint imGuiTableColumnFlags, jfloat initWidthOrWeight, jint userId) {

//@line:11084

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        ImGui::TableSetupColumn(label, imGuiTableColumnFlags, initWidthOrWeight, userId);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTableSetupColumn__Ljava_lang_String_2FI(JNIEnv* env, jclass clazz, jstring obj_label, jfloat initWidthOrWeight, jint userId) {

//@line:11090

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        ImGui::TableSetupColumn(label, 0, initWidthOrWeight, userId);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTableSetupColumn__Ljava_lang_String_2II(JNIEnv* env, jclass clazz, jstring obj_label, jint imGuiTableColumnFlags, jint userId) {

//@line:11096

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        ImGui::TableSetupColumn(label, imGuiTableColumnFlags, 0.0f, userId);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTableSetupScrollFreeze(JNIEnv* env, jclass clazz, jint cols, jint rows) {


//@line:11109

        ImGui::TableSetupScrollFreeze(cols, rows);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTableHeader(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:11120

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        ImGui::TableHeader(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTableHeadersRow(JNIEnv* env, jclass clazz) {


//@line:11133

        ImGui::TableHeadersRow();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTableAngledHeadersRow(JNIEnv* env, jclass clazz) {


//@line:11144

        ImGui::TableAngledHeadersRow();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nTableGetSortSpecs(JNIEnv* env, jclass clazz) {


//@line:11163

        return (uintptr_t)ImGui::TableGetSortSpecs();
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nTableGetColumnCount(JNIEnv* env, jclass clazz) {


//@line:11177

        return ImGui::TableGetColumnCount();
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nTableGetColumnIndex(JNIEnv* env, jclass clazz) {


//@line:11188

        return ImGui::TableGetColumnIndex();
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nTableGetRowIndex(JNIEnv* env, jclass clazz) {


//@line:11199

        return ImGui::TableGetRowIndex();
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_ImGui_nTableGetColumnName__(JNIEnv* env, jclass clazz) {


//@line:11217

        return env->NewStringUTF(ImGui::TableGetColumnName());
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_ImGui_nTableGetColumnName__I(JNIEnv* env, jclass clazz, jint columnN) {


//@line:11221

        return env->NewStringUTF(ImGui::TableGetColumnName(columnN));
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nTableGetColumnFlags__(JNIEnv* env, jclass clazz) {


//@line:11239

        return ImGui::TableGetColumnFlags();
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nTableGetColumnFlags__I(JNIEnv* env, jclass clazz, jint columnN) {


//@line:11243

        return ImGui::TableGetColumnFlags(columnN);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTableSetColumnEnabled(JNIEnv* env, jclass clazz, jint columnN, jboolean value) {


//@line:11255

        ImGui::TableSetColumnEnabled(columnN, value);
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nTableGetHoveredColumn(JNIEnv* env, jclass clazz) {


//@line:11266

        return ImGui::TableGetHoveredColumn();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTableSetBgColor__II(JNIEnv* env, jclass clazz, jint imGuiTableBgTarget, jint color) {


//@line:11284

        ImGui::TableSetBgColor(imGuiTableBgTarget, color);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nTableSetBgColor__III(JNIEnv* env, jclass clazz, jint imGuiTableBgTarget, jint color, jint columnN) {


//@line:11288

        ImGui::TableSetBgColor(imGuiTableBgTarget, color, columnN);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nColumns__(JNIEnv* env, jclass clazz) {


//@line:11324

        ImGui::Columns();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nColumns__I(JNIEnv* env, jclass clazz, jint count) {


//@line:11328

        ImGui::Columns(count);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nColumns__ILjava_lang_String_2(JNIEnv* env, jclass clazz, jint count, jstring obj_id) {

//@line:11332

        auto id = obj_id == NULL ? NULL : (char*)env->GetStringUTFChars(obj_id, JNI_FALSE);
        ImGui::Columns(count, id);
        if (id != NULL) env->ReleaseStringUTFChars(obj_id, id);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nColumns__ILjava_lang_String_2Z(JNIEnv* env, jclass clazz, jint count, jstring obj_id, jboolean border) {

//@line:11338

        auto id = obj_id == NULL ? NULL : (char*)env->GetStringUTFChars(obj_id, JNI_FALSE);
        ImGui::Columns(count, id, border);
        if (id != NULL) env->ReleaseStringUTFChars(obj_id, id);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nColumns__Ljava_lang_String_2Z(JNIEnv* env, jclass clazz, jstring obj_id, jboolean border) {

//@line:11344

        auto id = obj_id == NULL ? NULL : (char*)env->GetStringUTFChars(obj_id, JNI_FALSE);
        ImGui::Columns(1, id, border);
        if (id != NULL) env->ReleaseStringUTFChars(obj_id, id);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nColumns__Z(JNIEnv* env, jclass clazz, jboolean border) {


//@line:11350

        ImGui::Columns(1, NULL, border);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nColumns__IZ(JNIEnv* env, jclass clazz, jint count, jboolean border) {


//@line:11354

        ImGui::Columns(count, NULL, border);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nNextColumn(JNIEnv* env, jclass clazz) {


//@line:11365

        ImGui::NextColumn();
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nGetColumnIndex(JNIEnv* env, jclass clazz) {


//@line:11376

        return ImGui::GetColumnIndex();
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetColumnWidth__(JNIEnv* env, jclass clazz) {


//@line:11394

        return ImGui::GetColumnWidth();
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetColumnWidth__I(JNIEnv* env, jclass clazz, jint columnIndex) {


//@line:11398

        return ImGui::GetColumnWidth(columnIndex);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetColumnWidth(JNIEnv* env, jclass clazz, jint columnIndex, jfloat width) {


//@line:11409

        ImGui::SetColumnWidth(columnIndex, width);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetColumnOffset__(JNIEnv* env, jclass clazz) {


//@line:11427

        return ImGui::GetColumnOffset();
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetColumnOffset__I(JNIEnv* env, jclass clazz, jint columnIndex) {


//@line:11431

        return ImGui::GetColumnOffset(columnIndex);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetColumnOffset(JNIEnv* env, jclass clazz, jint columnIndex, jfloat offsetX) {


//@line:11442

        ImGui::SetColumnOffset(columnIndex, offsetX);
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nGetColumnsCount(JNIEnv* env, jclass clazz) {


//@line:11450

        return ImGui::GetColumnsCount();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginTabBar__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_strId) {

//@line:11471

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto _result = ImGui::BeginTabBar(strId);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginTabBar__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_strId, jint imGuiTabBarFlags) {

//@line:11478

        auto strId = obj_strId == NULL ? NULL : (char*)env->GetStringUTFChars(obj_strId, JNI_FALSE);
        auto _result = ImGui::BeginTabBar(strId, imGuiTabBarFlags);
        if (strId != NULL) env->ReleaseStringUTFChars(obj_strId, strId);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nEndTabBar(JNIEnv* env, jclass clazz) {


//@line:11492

        ImGui::EndTabBar();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginTabItem__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:11524

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::BeginTabItem(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginTabItem__Ljava_lang_String_2_3Z(JNIEnv* env, jclass clazz, jstring obj_label, jbooleanArray obj_pOpen) {

//@line:11531

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pOpen = obj_pOpen == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pOpen, JNI_FALSE);
        auto _result = ImGui::BeginTabItem(label, (pOpen != NULL ? &pOpen[0] : NULL));
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pOpen != NULL) env->ReleasePrimitiveArrayCritical(obj_pOpen, pOpen, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginTabItem__Ljava_lang_String_2_3ZI(JNIEnv* env, jclass clazz, jstring obj_label, jbooleanArray obj_pOpen, jint imGuiTabItemFlags) {

//@line:11540

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto pOpen = obj_pOpen == NULL ? NULL : (bool*)env->GetPrimitiveArrayCritical(obj_pOpen, JNI_FALSE);
        auto _result = ImGui::BeginTabItem(label, (pOpen != NULL ? &pOpen[0] : NULL), imGuiTabItemFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        if (pOpen != NULL) env->ReleasePrimitiveArrayCritical(obj_pOpen, pOpen, JNI_FALSE);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginTabItem__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jint imGuiTabItemFlags) {

//@line:11549

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::BeginTabItem(label, NULL, imGuiTabItemFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nEndTabItem(JNIEnv* env, jclass clazz) {


//@line:11563

        ImGui::EndTabItem();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nTabItemButton__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_label) {

//@line:11581

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::TabItemButton(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nTabItemButton__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_label, jint imGuiTabItemFlags) {

//@line:11588

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        auto _result = ImGui::TabItemButton(label, imGuiTabItemFlags);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetTabItemClosed(JNIEnv* env, jclass clazz, jstring obj_tabOrDockedWindowLabel) {

//@line:11603

        auto tabOrDockedWindowLabel = obj_tabOrDockedWindowLabel == NULL ? NULL : (char*)env->GetStringUTFChars(obj_tabOrDockedWindowLabel, JNI_FALSE);
        ImGui::SetTabItemClosed(tabOrDockedWindowLabel);
        if (tabOrDockedWindowLabel != NULL) env->ReleaseStringUTFChars(obj_tabOrDockedWindowLabel, tabOrDockedWindowLabel);
    
}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nDockSpace__I(JNIEnv* env, jclass clazz, jint dockspaceId) {


//@line:11667

        return ImGui::DockSpace(dockspaceId);
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nDockSpace__IFF(JNIEnv* env, jclass clazz, jint dockspaceId, jfloat sizeX, jfloat sizeY) {

//@line:11671

        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::DockSpace(dockspaceId, size);
        return _result;
    
}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nDockSpace__IFFI(JNIEnv* env, jclass clazz, jint dockspaceId, jfloat sizeX, jfloat sizeY, jint imGuiDockNodeFlags) {

//@line:11677

        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::DockSpace(dockspaceId, size, imGuiDockNodeFlags);
        return _result;
    
}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nDockSpace__IFFIJ(JNIEnv* env, jclass clazz, jint dockspaceId, jfloat sizeX, jfloat sizeY, jint imGuiDockNodeFlags, jlong windowClass) {

//@line:11683

        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::DockSpace(dockspaceId, size, imGuiDockNodeFlags, reinterpret_cast<ImGuiWindowClass*>(windowClass));
        return _result;
    
}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nDockSpace__IIJ(JNIEnv* env, jclass clazz, jint dockspaceId, jint imGuiDockNodeFlags, jlong windowClass) {


//@line:11689

        return ImGui::DockSpace(dockspaceId, ImVec2(0,0), imGuiDockNodeFlags, reinterpret_cast<ImGuiWindowClass*>(windowClass));
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nDockSpace__IJ(JNIEnv* env, jclass clazz, jint dockspaceId, jlong windowClass) {


//@line:11693

        return ImGui::DockSpace(dockspaceId, ImVec2(0,0), 0, reinterpret_cast<ImGuiWindowClass*>(windowClass));
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nDockSpace__IFFJ(JNIEnv* env, jclass clazz, jint dockspaceId, jfloat sizeX, jfloat sizeY, jlong windowClass) {

//@line:11697

        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::DockSpace(dockspaceId, size, 0, reinterpret_cast<ImGuiWindowClass*>(windowClass));
        return _result;
    
}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nDockSpaceOverViewport__(JNIEnv* env, jclass clazz) {


//@line:11731

        return ImGui::DockSpaceOverViewport();
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nDockSpaceOverViewport__I(JNIEnv* env, jclass clazz, jint dockspaceId) {


//@line:11735

        return ImGui::DockSpaceOverViewport(dockspaceId);
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nDockSpaceOverViewport__IJ(JNIEnv* env, jclass clazz, jint dockspaceId, jlong viewport) {


//@line:11739

        return ImGui::DockSpaceOverViewport(dockspaceId, reinterpret_cast<ImGuiViewport*>(viewport));
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nDockSpaceOverViewport__IJI(JNIEnv* env, jclass clazz, jint dockspaceId, jlong viewport, jint imGuiDockNodeFlags) {


//@line:11743

        return ImGui::DockSpaceOverViewport(dockspaceId, reinterpret_cast<ImGuiViewport*>(viewport), imGuiDockNodeFlags);
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nDockSpaceOverViewport__IJIJ(JNIEnv* env, jclass clazz, jint dockspaceId, jlong viewport, jint imGuiDockNodeFlags, jlong windowClass) {


//@line:11747

        return ImGui::DockSpaceOverViewport(dockspaceId, reinterpret_cast<ImGuiViewport*>(viewport), imGuiDockNodeFlags, reinterpret_cast<ImGuiWindowClass*>(windowClass));
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nDockSpaceOverViewport__JIJ(JNIEnv* env, jclass clazz, jlong viewport, jint imGuiDockNodeFlags, jlong windowClass) {


//@line:11751

        return ImGui::DockSpaceOverViewport(0, reinterpret_cast<ImGuiViewport*>(viewport), imGuiDockNodeFlags, reinterpret_cast<ImGuiWindowClass*>(windowClass));
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nDockSpaceOverViewport__IJJ(JNIEnv* env, jclass clazz, jint dockspaceId, jlong viewport, jlong windowClass) {


//@line:11755

        return ImGui::DockSpaceOverViewport(dockspaceId, reinterpret_cast<ImGuiViewport*>(viewport), 0, reinterpret_cast<ImGuiWindowClass*>(windowClass));
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextWindowDockID__I(JNIEnv* env, jclass clazz, jint dockId) {


//@line:11773

        ImGui::SetNextWindowDockID(dockId);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextWindowDockID__II(JNIEnv* env, jclass clazz, jint dockId, jint imGuiCond) {


//@line:11777

        ImGui::SetNextWindowDockID(dockId, imGuiCond);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextWindowClass(JNIEnv* env, jclass clazz, jlong windowClass) {


//@line:11788

        ImGui::SetNextWindowClass(reinterpret_cast<ImGuiWindowClass*>(windowClass));
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nGetWindowDockID(JNIEnv* env, jclass clazz) {


//@line:11796

        return ImGui::GetWindowDockID();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsWindowDocked(JNIEnv* env, jclass clazz) {


//@line:11807

        return ImGui::IsWindowDocked();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nLogToTTY__(JNIEnv* env, jclass clazz) {


//@line:11828

        ImGui::LogToTTY();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nLogToTTY__I(JNIEnv* env, jclass clazz, jint autoOpenDepth) {


//@line:11832

        ImGui::LogToTTY(autoOpenDepth);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nLogToFile__(JNIEnv* env, jclass clazz) {


//@line:11864

        ImGui::LogToFile();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nLogToFile__I(JNIEnv* env, jclass clazz, jint autoOpenDepth) {


//@line:11868

        ImGui::LogToFile(autoOpenDepth);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nLogToFile__ILjava_lang_String_2(JNIEnv* env, jclass clazz, jint autoOpenDepth, jstring obj_filename) {

//@line:11872

        auto filename = obj_filename == NULL ? NULL : (char*)env->GetStringUTFChars(obj_filename, JNI_FALSE);
        ImGui::LogToFile(autoOpenDepth, filename);
        if (filename != NULL) env->ReleaseStringUTFChars(obj_filename, filename);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nLogToFile__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_filename) {

//@line:11878

        auto filename = obj_filename == NULL ? NULL : (char*)env->GetStringUTFChars(obj_filename, JNI_FALSE);
        ImGui::LogToFile(-1, filename);
        if (filename != NULL) env->ReleaseStringUTFChars(obj_filename, filename);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nLogToClipboard__(JNIEnv* env, jclass clazz) {


//@line:11898

        ImGui::LogToClipboard();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nLogToClipboard__I(JNIEnv* env, jclass clazz, jint autoOpenDepth) {


//@line:11902

        ImGui::LogToClipboard(autoOpenDepth);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nLogFinish(JNIEnv* env, jclass clazz) {


//@line:11913

        ImGui::LogFinish();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nLogButtons(JNIEnv* env, jclass clazz) {


//@line:11924

        ImGui::LogButtons();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nLogText(JNIEnv* env, jclass clazz, jstring obj_text) {

//@line:11935

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        ImGui::LogText(text, NULL);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginDragDropSource__(JNIEnv* env, jclass clazz) {


//@line:11958

        return ImGui::BeginDragDropSource();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginDragDropSource__I(JNIEnv* env, jclass clazz, jint imGuiDragDropFlags) {


//@line:11962

        return ImGui::BeginDragDropSource(imGuiDragDropFlags);
    

}

static inline jboolean wrapped_Java_imgui_moulberry92_ImGui_nSetDragDropPayload
(JNIEnv* env, jclass clazz, jstring obj_dataType, jbyteArray obj_data, jint sz, jint imGuiCond, char* dataType, char* data) {

//@line:12008

        return ImGui::SetDragDropPayload(dataType, &data[0], sz, imGuiCond);
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nSetDragDropPayload(JNIEnv* env, jclass clazz, jstring obj_dataType, jbyteArray obj_data, jint sz, jint imGuiCond) {
	char* dataType = (char*)env->GetStringUTFChars(obj_dataType, 0);
	char* data = (char*)env->GetPrimitiveArrayCritical(obj_data, 0);

	jboolean JNI_returnValue = wrapped_Java_imgui_moulberry92_ImGui_nSetDragDropPayload(env, clazz, obj_dataType, obj_data, sz, imGuiCond, dataType, data);

	env->ReleasePrimitiveArrayCritical(obj_data, data, 0);
	env->ReleaseStringUTFChars(obj_dataType, dataType);

	return JNI_returnValue;
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nEndDragDropSource(JNIEnv* env, jclass clazz) {


//@line:12019

        ImGui::EndDragDropSource();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nBeginDragDropTarget(JNIEnv* env, jclass clazz) {


//@line:12030

        return ImGui::BeginDragDropTarget();
    

}

static inline jboolean wrapped_Java_imgui_moulberry92_ImGui_nAcceptDragDropPayload
(JNIEnv* env, jclass clazz, jstring obj_dataType, jint imGuiDragDropFlags, char* dataType) {

//@line:12085

        return ImGui::AcceptDragDropPayload(dataType, imGuiDragDropFlags) != NULL;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nAcceptDragDropPayload(JNIEnv* env, jclass clazz, jstring obj_dataType, jint imGuiDragDropFlags) {
	char* dataType = (char*)env->GetStringUTFChars(obj_dataType, 0);

	jboolean JNI_returnValue = wrapped_Java_imgui_moulberry92_ImGui_nAcceptDragDropPayload(env, clazz, obj_dataType, imGuiDragDropFlags, dataType);

	env->ReleaseStringUTFChars(obj_dataType, dataType);

	return JNI_returnValue;
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nEndDragDropTarget(JNIEnv* env, jclass clazz) {


//@line:12096

        ImGui::EndDragDropTarget();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nHasDragDropPayload__(JNIEnv* env, jclass clazz) {


//@line:12135

        const ImGuiPayload* payload = ImGui::GetDragDropPayload();
        return payload != NULL && payload->Data != NULL;
    

}

static inline jboolean wrapped_Java_imgui_moulberry92_ImGui_nHasDragDropPayload__Ljava_lang_String_2
(JNIEnv* env, jclass clazz, jstring obj_dataType, char* dataType) {

//@line:12140

        const ImGuiPayload* payload = ImGui::GetDragDropPayload();
        return payload != NULL && payload->IsDataType(dataType);
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nHasDragDropPayload__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_dataType) {
	char* dataType = (char*)env->GetStringUTFChars(obj_dataType, 0);

	jboolean JNI_returnValue = wrapped_Java_imgui_moulberry92_ImGui_nHasDragDropPayload__Ljava_lang_String_2(env, clazz, obj_dataType, dataType);

	env->ReleaseStringUTFChars(obj_dataType, dataType);

	return JNI_returnValue;
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nBeginDisabled__(JNIEnv* env, jclass clazz) {


//@line:12169

        ImGui::BeginDisabled();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nBeginDisabled__Z(JNIEnv* env, jclass clazz, jboolean disabled) {


//@line:12173

        ImGui::BeginDisabled(disabled);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nEndDisabled(JNIEnv* env, jclass clazz) {


//@line:12181

        ImGui::EndDisabled();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPushClipRect(JNIEnv* env, jclass clazz, jfloat clipRectMinX, jfloat clipRectMinY, jfloat clipRectMaxX, jfloat clipRectMaxY, jboolean intersectWithCurrentClipRect) {

//@line:12196

        ImVec2 clipRectMin = ImVec2(clipRectMinX, clipRectMinY);
        ImVec2 clipRectMax = ImVec2(clipRectMaxX, clipRectMaxY);
        ImGui::PushClipRect(clipRectMin, clipRectMax, intersectWithCurrentClipRect);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nPopClipRect(JNIEnv* env, jclass clazz) {


//@line:12206

        ImGui::PopClipRect();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetItemDefaultFocus(JNIEnv* env, jclass clazz) {


//@line:12220

        ImGui::SetItemDefaultFocus();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetKeyboardFocusHere__(JNIEnv* env, jclass clazz) {


//@line:12238

        ImGui::SetKeyboardFocusHere();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetKeyboardFocusHere__I(JNIEnv* env, jclass clazz, jint offset) {


//@line:12242

        ImGui::SetKeyboardFocusHere(offset);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextItemAllowOverlap(JNIEnv* env, jclass clazz) {


//@line:12257

        ImGui::SetNextItemAllowOverlap();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsItemHovered__(JNIEnv* env, jclass clazz) {


//@line:12279

        return ImGui::IsItemHovered();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsItemHovered__I(JNIEnv* env, jclass clazz, jint imGuiHoveredFlags) {


//@line:12283

        return ImGui::IsItemHovered(imGuiHoveredFlags);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsItemActive(JNIEnv* env, jclass clazz) {


//@line:12296

        return ImGui::IsItemActive();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsItemFocused(JNIEnv* env, jclass clazz) {


//@line:12307

        return ImGui::IsItemFocused();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsItemClicked__(JNIEnv* env, jclass clazz) {


//@line:12327

        return ImGui::IsItemClicked();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsItemClicked__I(JNIEnv* env, jclass clazz, jint mouseButton) {


//@line:12331

        return ImGui::IsItemClicked(mouseButton);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsItemVisible(JNIEnv* env, jclass clazz) {


//@line:12342

        return ImGui::IsItemVisible();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsItemEdited(JNIEnv* env, jclass clazz) {


//@line:12353

        return ImGui::IsItemEdited();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsItemActivated(JNIEnv* env, jclass clazz) {


//@line:12364

        return ImGui::IsItemActivated();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsItemDeactivated(JNIEnv* env, jclass clazz) {


//@line:12375

        return ImGui::IsItemDeactivated();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsItemDeactivatedAfterEdit(JNIEnv* env, jclass clazz) {


//@line:12388

        return ImGui::IsItemDeactivatedAfterEdit();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsItemToggledOpen(JNIEnv* env, jclass clazz) {


//@line:12399

        return ImGui::IsItemToggledOpen();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsItemToggledSelection(JNIEnv* env, jclass clazz) {


//@line:12411

        return ImGui::IsItemToggledSelection();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextItemSelectionUserData(JNIEnv* env, jclass clazz, jlong selectionUserData) {


//@line:12424

        ImGui::SetNextItemSelectionUserData(selectionUserData);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsAnyItemHovered(JNIEnv* env, jclass clazz) {


//@line:12435

        return ImGui::IsAnyItemHovered();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsAnyItemActive(JNIEnv* env, jclass clazz) {


//@line:12446

        return ImGui::IsAnyItemActive();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsAnyItemFocused(JNIEnv* env, jclass clazz) {


//@line:12456

        return ImGui::IsAnyItemFocused();
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nGetItemID(JNIEnv* env, jclass clazz) {


//@line:12467

        return ImGui::GetItemID();
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nGetItemFlags(JNIEnv* env, jclass clazz) {


//@line:12478

        return ImGui::GetItemFlags();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetItemRectMin(JNIEnv* env, jclass clazz, jobject dst) {


//@line:12512

        Jni::ImVec2Cpy(env, ImGui::GetItemRectMin(), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetItemRectMinX(JNIEnv* env, jclass clazz) {


//@line:12516

        return ImGui::GetItemRectMin().x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetItemRectMinY(JNIEnv* env, jclass clazz) {


//@line:12520

        return ImGui::GetItemRectMin().y;
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetItemRectMax(JNIEnv* env, jclass clazz, jobject dst) {


//@line:12554

        Jni::ImVec2Cpy(env, ImGui::GetItemRectMax(), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetItemRectMaxX(JNIEnv* env, jclass clazz) {


//@line:12558

        return ImGui::GetItemRectMax().x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetItemRectMaxY(JNIEnv* env, jclass clazz) {


//@line:12562

        return ImGui::GetItemRectMax().y;
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetItemRectSize(JNIEnv* env, jclass clazz, jobject dst) {


//@line:12596

        Jni::ImVec2Cpy(env, ImGui::GetItemRectSize(), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetItemRectSizeX(JNIEnv* env, jclass clazz) {


//@line:12600

        return ImGui::GetItemRectSize().x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetItemRectSizeY(JNIEnv* env, jclass clazz) {


//@line:12604

        return ImGui::GetItemRectSize().y;
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nGetMainViewport(JNIEnv* env, jclass clazz) {


//@line:12623

        return (uintptr_t)ImGui::GetMainViewport();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nGetBackgroundDrawList__(JNIEnv* env, jclass clazz) {


//@line:12645

        return (uintptr_t)ImGui::GetBackgroundDrawList();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nGetBackgroundDrawList__J(JNIEnv* env, jclass clazz, jlong viewport) {


//@line:12649

        return (uintptr_t)ImGui::GetBackgroundDrawList(reinterpret_cast<ImGuiViewport*>(viewport));
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nGetForegroundDrawList__(JNIEnv* env, jclass clazz) {


//@line:12669

        return (uintptr_t)ImGui::GetForegroundDrawList();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nGetForegroundDrawList__J(JNIEnv* env, jclass clazz, jlong viewport) {


//@line:12673

        return (uintptr_t)ImGui::GetForegroundDrawList(reinterpret_cast<ImGuiViewport*>(viewport));
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsRectVisible__FF(JNIEnv* env, jclass clazz, jfloat sizeX, jfloat sizeY) {

//@line:12693

        ImVec2 size = ImVec2(sizeX, sizeY);
        auto _result = ImGui::IsRectVisible(size);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsRectVisible__FFFF(JNIEnv* env, jclass clazz, jfloat rectMinX, jfloat rectMinY, jfloat rectMaxX, jfloat rectMaxY) {

//@line:12713

        ImVec2 rectMin = ImVec2(rectMinX, rectMinY);
        ImVec2 rectMax = ImVec2(rectMaxX, rectMaxY);
        auto _result = ImGui::IsRectVisible(rectMin, rectMax);
        return _result;
    
}

JNIEXPORT jdouble JNICALL Java_imgui_moulberry92_ImGui_nGetTime(JNIEnv* env, jclass clazz) {


//@line:12727

        return ImGui::GetTime();
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nGetFrameCount(JNIEnv* env, jclass clazz) {


//@line:12738

        return ImGui::GetFrameCount();
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_ImGui_nGetStyleColorName(JNIEnv* env, jclass clazz, jint imGuiColIdx) {


//@line:12753

        return env->NewStringUTF(ImGui::GetStyleColorName(imGuiColIdx));
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetStateStorage(JNIEnv* env, jclass clazz, jlong storage) {


//@line:12764

        ImGui::SetStateStorage(reinterpret_cast<ImGuiStorage*>(storage));
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nGetStateStorage(JNIEnv* env, jclass clazz) {


//@line:12772

        return (uintptr_t)ImGui::GetStateStorage();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nCalcTextSize__Limgui_moulberry92_ImVec2_2Ljava_lang_String_2(JNIEnv* env, jclass clazz, jobject dst, jstring obj_text) {

//@line:12850

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        Jni::ImVec2Cpy(env, ImGui::CalcTextSize(text, NULL), dst);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nCalcTextSizeX__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_text) {

//@line:12856

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        auto _result = ImGui::CalcTextSize(text, NULL).x;
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
        return _result;
    
}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nCalcTextSizeY__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_text) {

//@line:12863

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        auto _result = ImGui::CalcTextSize(text, NULL).y;
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nCalcTextSize__Limgui_moulberry92_ImVec2_2Ljava_lang_String_2Z(JNIEnv* env, jclass clazz, jobject dst, jstring obj_text, jboolean hideTextAfterDoubleHash) {

//@line:12870

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        Jni::ImVec2Cpy(env, ImGui::CalcTextSize(text, NULL, hideTextAfterDoubleHash), dst);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nCalcTextSizeX__Ljava_lang_String_2Z(JNIEnv* env, jclass clazz, jstring obj_text, jboolean hideTextAfterDoubleHash) {

//@line:12876

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        auto _result = ImGui::CalcTextSize(text, NULL, hideTextAfterDoubleHash).x;
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
        return _result;
    
}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nCalcTextSizeY__Ljava_lang_String_2Z(JNIEnv* env, jclass clazz, jstring obj_text, jboolean hideTextAfterDoubleHash) {

//@line:12883

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        auto _result = ImGui::CalcTextSize(text, NULL, hideTextAfterDoubleHash).y;
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nCalcTextSize__Limgui_moulberry92_ImVec2_2Ljava_lang_String_2ZF(JNIEnv* env, jclass clazz, jobject dst, jstring obj_text, jboolean hideTextAfterDoubleHash, jfloat wrapWidth) {

//@line:12890

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        Jni::ImVec2Cpy(env, ImGui::CalcTextSize(text, NULL, hideTextAfterDoubleHash, wrapWidth), dst);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nCalcTextSizeX__Ljava_lang_String_2ZF(JNIEnv* env, jclass clazz, jstring obj_text, jboolean hideTextAfterDoubleHash, jfloat wrapWidth) {

//@line:12896

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        auto _result = ImGui::CalcTextSize(text, NULL, hideTextAfterDoubleHash, wrapWidth).x;
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
        return _result;
    
}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nCalcTextSizeY__Ljava_lang_String_2ZF(JNIEnv* env, jclass clazz, jstring obj_text, jboolean hideTextAfterDoubleHash, jfloat wrapWidth) {

//@line:12903

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        auto _result = ImGui::CalcTextSize(text, NULL, hideTextAfterDoubleHash, wrapWidth).y;
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nCalcTextSize__Limgui_moulberry92_ImVec2_2Ljava_lang_String_2F(JNIEnv* env, jclass clazz, jobject dst, jstring obj_text, jfloat wrapWidth) {

//@line:12910

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        Jni::ImVec2Cpy(env, ImGui::CalcTextSize(text, NULL, false, wrapWidth), dst);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nCalcTextSizeX__Ljava_lang_String_2F(JNIEnv* env, jclass clazz, jstring obj_text, jfloat wrapWidth) {

//@line:12916

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        auto _result = ImGui::CalcTextSize(text, NULL, false, wrapWidth).x;
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
        return _result;
    
}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nCalcTextSizeY__Ljava_lang_String_2F(JNIEnv* env, jclass clazz, jstring obj_text, jfloat wrapWidth) {

//@line:12923

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        auto _result = ImGui::CalcTextSize(text, NULL, false, wrapWidth).y;
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nColorConvertU32ToFloat4(JNIEnv* env, jclass clazz, jobject dst, jint in) {


//@line:12958

        Jni::ImVec4Cpy(env, ImGui::ColorConvertU32ToFloat4(in), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nColorConvertU32ToFloat4X(JNIEnv* env, jclass clazz, jint in) {


//@line:12962

        return ImGui::ColorConvertU32ToFloat4(in).x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nColorConvertU32ToFloat4Y(JNIEnv* env, jclass clazz, jint in) {


//@line:12966

        return ImGui::ColorConvertU32ToFloat4(in).y;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nColorConvertU32ToFloat4Z(JNIEnv* env, jclass clazz, jint in) {


//@line:12970

        return ImGui::ColorConvertU32ToFloat4(in).z;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nColorConvertU32ToFloat4W(JNIEnv* env, jclass clazz, jint in) {


//@line:12974

        return ImGui::ColorConvertU32ToFloat4(in).w;
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nColorConvertFloat4ToU32(JNIEnv* env, jclass clazz, jfloat inX, jfloat inY, jfloat inZ, jfloat inW) {

//@line:12986

        ImVec4 in = ImVec4(inX, inY, inZ, inW);
        auto _result = ImGui::ColorConvertFloat4ToU32(in);
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nColorConvertRGBtoHSV(JNIEnv* env, jclass clazz, jfloatArray obj_rgb, jfloatArray obj_hsv) {
	float* rgb = (float*)env->GetPrimitiveArrayCritical(obj_rgb, 0);
	float* hsv = (float*)env->GetPrimitiveArrayCritical(obj_hsv, 0);


//@line:12996

        ImGui::ColorConvertRGBtoHSV(rgb[0], rgb[1], rgb[2], hsv[0], hsv[1], hsv[2]);
    
	env->ReleasePrimitiveArrayCritical(obj_rgb, rgb, 0);
	env->ReleasePrimitiveArrayCritical(obj_hsv, hsv, 0);

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nColorConvertHSVtoRGB(JNIEnv* env, jclass clazz, jfloatArray obj_hsv, jfloatArray obj_rgb) {
	float* hsv = (float*)env->GetPrimitiveArrayCritical(obj_hsv, 0);
	float* rgb = (float*)env->GetPrimitiveArrayCritical(obj_rgb, 0);


//@line:13004

        ImGui::ColorConvertHSVtoRGB(hsv[0], hsv[1], hsv[2], rgb[0], rgb[1], rgb[2]);
    
	env->ReleasePrimitiveArrayCritical(obj_hsv, hsv, 0);
	env->ReleasePrimitiveArrayCritical(obj_rgb, rgb, 0);

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsKeyDown(JNIEnv* env, jclass clazz, jint key) {


//@line:13021

        return ImGui::IsKeyDown(static_cast<ImGuiKey>(key));
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsKeyPressed__I(JNIEnv* env, jclass clazz, jint key) {


//@line:13039

        return ImGui::IsKeyPressed(static_cast<ImGuiKey>(key));
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsKeyPressed__IZ(JNIEnv* env, jclass clazz, jint key, jboolean repeat) {


//@line:13043

        return ImGui::IsKeyPressed(static_cast<ImGuiKey>(key), repeat);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsKeyReleased(JNIEnv* env, jclass clazz, jint key) {


//@line:13054

        return ImGui::IsKeyReleased(static_cast<ImGuiKey>(key));
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsKeyChordPressed(JNIEnv* env, jclass clazz, jint keyChord) {


//@line:13066

        return ImGui::IsKeyChordPressed(static_cast<ImGuiKeyChord>(keyChord));
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nGetKeyPressedAmount(JNIEnv* env, jclass clazz, jint key, jfloat repeatDelay, jfloat rate) {


//@line:13078

        return ImGui::GetKeyPressedAmount(static_cast<ImGuiKey>(key), repeatDelay, rate);
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_ImGui_nGetKeyName(JNIEnv* env, jclass clazz, jint key) {


//@line:13089

        return env->NewStringUTF(ImGui::GetKeyName(static_cast<ImGuiKey>(key)));
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextFrameWantCaptureKeyboard(JNIEnv* env, jclass clazz, jboolean wantCaptureKeyboard) {


//@line:13102

        ImGui::SetNextFrameWantCaptureKeyboard(wantCaptureKeyboard);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nShortcut__I(JNIEnv* env, jclass clazz, jint keyChord) {


//@line:13130

        return ImGui::Shortcut(static_cast<ImGuiKeyChord>(keyChord));
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nShortcut__II(JNIEnv* env, jclass clazz, jint keyChord, jint flags) {


//@line:13134

        return ImGui::Shortcut(static_cast<ImGuiKeyChord>(keyChord), flags);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextItemShortcut__I(JNIEnv* env, jclass clazz, jint keyChord) {


//@line:13146

        ImGui::SetNextItemShortcut(static_cast<ImGuiKeyChord>(keyChord));
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextItemShortcut__II(JNIEnv* env, jclass clazz, jint keyChord, jint flags) {


//@line:13150

        ImGui::SetNextItemShortcut(static_cast<ImGuiKeyChord>(keyChord), flags);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsMouseDown(JNIEnv* env, jclass clazz, jint button) {


//@line:13166

        return ImGui::IsMouseDown(button);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsMouseClicked__I(JNIEnv* env, jclass clazz, jint button) {


//@line:13184

        return ImGui::IsMouseClicked(button);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsMouseClicked__IZ(JNIEnv* env, jclass clazz, jint button, jboolean repeat) {


//@line:13188

        return ImGui::IsMouseClicked(button, repeat);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsMouseReleased(JNIEnv* env, jclass clazz, jint button) {


//@line:13199

        return ImGui::IsMouseReleased(button);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsMouseDoubleClicked(JNIEnv* env, jclass clazz, jint button) {


//@line:13210

        return ImGui::IsMouseDoubleClicked(button);
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nGetMouseClickedCount(JNIEnv* env, jclass clazz, jint button) {


//@line:13221

        return ImGui::GetMouseClickedCount(button);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsMouseHoveringRect__FFFF(JNIEnv* env, jclass clazz, jfloat rMinX, jfloat rMinY, jfloat rMaxX, jfloat rMaxY) {

//@line:13253

        ImVec2 rMin = ImVec2(rMinX, rMinY);
        ImVec2 rMax = ImVec2(rMaxX, rMaxY);
        auto _result = ImGui::IsMouseHoveringRect(rMin, rMax);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsMouseHoveringRect__FFFFZ(JNIEnv* env, jclass clazz, jfloat rMinX, jfloat rMinY, jfloat rMaxX, jfloat rMaxY, jboolean clip) {

//@line:13260

        ImVec2 rMin = ImVec2(rMinX, rMinY);
        ImVec2 rMax = ImVec2(rMaxX, rMaxY);
        auto _result = ImGui::IsMouseHoveringRect(rMin, rMax, clip);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsMousePosValid__(JNIEnv* env, jclass clazz) {


//@line:13288

        return ImGui::IsMousePosValid();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsMousePosValid__FF(JNIEnv* env, jclass clazz, jfloat mousePosX, jfloat mousePosY) {

//@line:13292

        ImVec2 mousePos = ImVec2(mousePosX, mousePosY);
        auto _result = ImGui::IsMousePosValid(&mousePos);
        return _result;
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsAnyMouseDown(JNIEnv* env, jclass clazz) {


//@line:13305

        return ImGui::IsAnyMouseDown();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetMousePos(JNIEnv* env, jclass clazz, jobject dst) {


//@line:13339

        Jni::ImVec2Cpy(env, ImGui::GetMousePos(), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetMousePosX(JNIEnv* env, jclass clazz) {


//@line:13343

        return ImGui::GetMousePos().x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetMousePosY(JNIEnv* env, jclass clazz) {


//@line:13347

        return ImGui::GetMousePos().y;
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetMousePosOnOpeningCurrentPopup(JNIEnv* env, jclass clazz, jobject dst) {


//@line:13381

        Jni::ImVec2Cpy(env, ImGui::GetMousePosOnOpeningCurrentPopup(), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetMousePosOnOpeningCurrentPopupX(JNIEnv* env, jclass clazz) {


//@line:13385

        return ImGui::GetMousePosOnOpeningCurrentPopup().x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetMousePosOnOpeningCurrentPopupY(JNIEnv* env, jclass clazz) {


//@line:13389

        return ImGui::GetMousePosOnOpeningCurrentPopup().y;
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsMouseDragging__I(JNIEnv* env, jclass clazz, jint button) {


//@line:13407

        return ImGui::IsMouseDragging(button);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nIsMouseDragging__IF(JNIEnv* env, jclass clazz, jint button, jfloat lockThreshold) {


//@line:13411

        return ImGui::IsMouseDragging(button, lockThreshold);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetMouseDragDelta__Limgui_moulberry92_ImVec2_2(JNIEnv* env, jclass clazz, jobject dst) {


//@line:13517

        Jni::ImVec2Cpy(env, ImGui::GetMouseDragDelta(), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetMouseDragDeltaX__(JNIEnv* env, jclass clazz) {


//@line:13521

        return ImGui::GetMouseDragDelta().x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetMouseDragDeltaY__(JNIEnv* env, jclass clazz) {


//@line:13525

        return ImGui::GetMouseDragDelta().y;
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetMouseDragDelta__Limgui_moulberry92_ImVec2_2I(JNIEnv* env, jclass clazz, jobject dst, jint button) {


//@line:13529

        Jni::ImVec2Cpy(env, ImGui::GetMouseDragDelta(button), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetMouseDragDeltaX__I(JNIEnv* env, jclass clazz, jint button) {


//@line:13533

        return ImGui::GetMouseDragDelta(button).x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetMouseDragDeltaY__I(JNIEnv* env, jclass clazz, jint button) {


//@line:13537

        return ImGui::GetMouseDragDelta(button).y;
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nGetMouseDragDelta__Limgui_moulberry92_ImVec2_2IF(JNIEnv* env, jclass clazz, jobject dst, jint button, jfloat lockThreshold) {


//@line:13541

        Jni::ImVec2Cpy(env, ImGui::GetMouseDragDelta(button, lockThreshold), dst);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetMouseDragDeltaX__IF(JNIEnv* env, jclass clazz, jint button, jfloat lockThreshold) {


//@line:13545

        return ImGui::GetMouseDragDelta(button, lockThreshold).x;
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_ImGui_nGetMouseDragDeltaY__IF(JNIEnv* env, jclass clazz, jint button, jfloat lockThreshold) {


//@line:13549

        return ImGui::GetMouseDragDelta(button, lockThreshold).y;
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nResetMouseDragDelta__(JNIEnv* env, jclass clazz) {


//@line:13561

        ImGui::ResetMouseDragDelta();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nResetMouseDragDelta__I(JNIEnv* env, jclass clazz, jint button) {


//@line:13565

        ImGui::ResetMouseDragDelta(button);
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_ImGui_nGetMouseCursor(JNIEnv* env, jclass clazz) {


//@line:13577

        return ImGui::GetMouseCursor();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetMouseCursor(JNIEnv* env, jclass clazz, jint type) {


//@line:13588

        ImGui::SetMouseCursor(type);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetNextFrameWantCaptureMouse(JNIEnv* env, jclass clazz, jboolean wantCaptureMouse) {


//@line:13601

        ImGui::SetNextFrameWantCaptureMouse(wantCaptureMouse);
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_ImGui_nGetClipboardText(JNIEnv* env, jclass clazz) {


//@line:13612

        return env->NewStringUTF(ImGui::GetClipboardText());
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSetClipboardText(JNIEnv* env, jclass clazz, jstring obj_text) {

//@line:13620

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        ImGui::SetClipboardText(text);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nLoadIniSettingsFromDisk(JNIEnv* env, jclass clazz, jstring obj_iniFilename) {

//@line:13637

        auto iniFilename = obj_iniFilename == NULL ? NULL : (char*)env->GetStringUTFChars(obj_iniFilename, JNI_FALSE);
        ImGui::LoadIniSettingsFromDisk(iniFilename);
        if (iniFilename != NULL) env->ReleaseStringUTFChars(obj_iniFilename, iniFilename);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nLoadIniSettingsFromMemory__Ljava_lang_String_2(JNIEnv* env, jclass clazz, jstring obj_iniData) {

//@line:13657

        auto iniData = obj_iniData == NULL ? NULL : (char*)env->GetStringUTFChars(obj_iniData, JNI_FALSE);
        ImGui::LoadIniSettingsFromMemory(iniData);
        if (iniData != NULL) env->ReleaseStringUTFChars(obj_iniData, iniData);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nLoadIniSettingsFromMemory__Ljava_lang_String_2I(JNIEnv* env, jclass clazz, jstring obj_iniData, jint iniSize) {

//@line:13663

        auto iniData = obj_iniData == NULL ? NULL : (char*)env->GetStringUTFChars(obj_iniData, JNI_FALSE);
        ImGui::LoadIniSettingsFromMemory(iniData, iniSize);
        if (iniData != NULL) env->ReleaseStringUTFChars(obj_iniData, iniData);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nSaveIniSettingsToDisk(JNIEnv* env, jclass clazz, jstring obj_iniFilename) {

//@line:13676

        auto iniFilename = obj_iniFilename == NULL ? NULL : (char*)env->GetStringUTFChars(obj_iniFilename, JNI_FALSE);
        ImGui::SaveIniSettingsToDisk(iniFilename);
        if (iniFilename != NULL) env->ReleaseStringUTFChars(obj_iniFilename, iniFilename);
    
}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_ImGui_nSaveIniSettingsToMemory__(JNIEnv* env, jclass clazz) {


//@line:13698

        return env->NewStringUTF(ImGui::SaveIniSettingsToMemory());
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_ImGui_nSaveIniSettingsToMemory__J(JNIEnv* env, jclass clazz, jlong outIniSize) {


//@line:13702

        return env->NewStringUTF(ImGui::SaveIniSettingsToMemory((size_t*)&outIniSize));
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nDebugTextEncoding(JNIEnv* env, jclass clazz, jstring obj_text) {

//@line:13713

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        ImGui::DebugTextEncoding(text);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nDebugFlashStyleColor(JNIEnv* env, jclass clazz, jint idx) {


//@line:13723

        ImGui::DebugFlashStyleColor(static_cast<ImGuiCol>(idx));
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nDebugStartItemPicker(JNIEnv* env, jclass clazz) {


//@line:13731

        ImGui::DebugStartItemPicker();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_ImGui_nDebugCheckVersionAndDataLayout(JNIEnv* env, jclass clazz, jstring obj_versionStr, jint szIo, jint szStyle, jint szVec2, jint szVec4, jint szDrawVert, jint szDrawIdx) {

//@line:13739

        auto versionStr = obj_versionStr == NULL ? NULL : (char*)env->GetStringUTFChars(obj_versionStr, JNI_FALSE);
        auto _result = ImGui::DebugCheckVersionAndDataLayout(versionStr, szIo, szStyle, szVec2, szVec4, szDrawVert, szDrawIdx);
        if (versionStr != NULL) env->ReleaseStringUTFChars(obj_versionStr, versionStr);
        return _result;
    
}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nGetPlatformIO(JNIEnv* env, jclass clazz) {


//@line:13760

        return (uintptr_t)&ImGui::GetPlatformIO();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nUpdatePlatformWindows(JNIEnv* env, jclass clazz) {


//@line:13771

        ImGui::UpdatePlatformWindows();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nRenderPlatformWindowsDefault(JNIEnv* env, jclass clazz) {


//@line:13783

        ImGui::RenderPlatformWindowsDefault();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_ImGui_nDestroyPlatformWindows(JNIEnv* env, jclass clazz) {


//@line:13796

        ImGui::DestroyPlatformWindows();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nFindViewportByID(JNIEnv* env, jclass clazz, jint imGuiID) {


//@line:13807

        return (uintptr_t)ImGui::FindViewportByID(imGuiID);
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_ImGui_nFindViewportByPlatformHandle(JNIEnv* env, jclass clazz, jlong platformHandle) {


//@line:13818

        return (uintptr_t)ImGui::FindViewportByPlatformHandle((void*)platformHandle);
    

}

