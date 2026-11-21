#include <imgui_moulberry92_extension_texteditor_TextEditor.h>

//@line:23

        #include "_texteditor.h"
        #define THIS ((TextEditor*)STRUCT_PTR)

        static jintArray TextEditorPaletteToArray(JNIEnv* env, const TextEditor::Palette& palette) {
            const auto size = static_cast<jsize>(palette.size());
            jintArray result = env->NewIntArray(size);
            std::vector<jint> values(static_cast<size_t>(size));
            for (size_t i = 0; i < palette.size(); ++i) {
                values[i] = static_cast<jint>(palette[i]);
            }
            env->SetIntArrayRegion(result, 0, size, values.data());
            return result;
        }

        static void TextEditorArrayToPalette(JNIEnv* env, jintArray source, TextEditor::Palette& destination) {
            const auto maxCount = static_cast<jsize>(destination.size());
            auto valueCount = env->GetArrayLength(source);
            valueCount = valueCount < maxCount ? valueCount : maxCount;
            std::vector<jint> values(static_cast<size_t>(valueCount));
            env->GetIntArrayRegion(source, 0, valueCount, values.data());
            for (jsize i = 0; i < valueCount; ++i) {
                destination[static_cast<size_t>(i)] = static_cast<ImU32>(values[static_cast<size_t>(i)]);
            }
        }
     JNIEXPORT jlong JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nCreate(JNIEnv* env, jobject object) {


//@line:50

        return (uintptr_t)(new TextEditor());
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetTabSize(JNIEnv* env, jobject object, jint value) {


//@line:58

        THIS->SetTabSize(value);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetLanguage(JNIEnv* env, jobject object, jlong languagePtr) {


//@line:66

        THIS->SetLanguage(reinterpret_cast<const TextEditor::Language*>(languagePtr));
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetTabSize(JNIEnv* env, jobject object) {


//@line:74

        return THIS->GetTabSize();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetInsertSpacesOnTabs(JNIEnv* env, jobject object, jboolean value) {


//@line:82

        THIS->SetInsertSpacesOnTabs(value);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nIsInsertSpacesOnTabs(JNIEnv* env, jobject object) {


//@line:90

        return THIS->IsInsertSpacesOnTabs();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetLineSpacing(JNIEnv* env, jobject object, jfloat value) {


//@line:98

        THIS->SetLineSpacing(value);
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetLineSpacing(JNIEnv* env, jobject object) {


//@line:106

        return THIS->GetLineSpacing();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetReadOnlyEnabled(JNIEnv* env, jobject object, jboolean value) {


//@line:114

        THIS->SetReadOnlyEnabled(value);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nIsReadOnlyEnabled(JNIEnv* env, jobject object) {


//@line:122

        return THIS->IsReadOnlyEnabled();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetAutoIndentEnabled(JNIEnv* env, jobject object, jboolean value) {


//@line:130

        THIS->SetAutoIndentEnabled(value);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nIsAutoIndentEnabled(JNIEnv* env, jobject object) {


//@line:138

        return THIS->IsAutoIndentEnabled();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetShowWhitespacesEnabled(JNIEnv* env, jobject object, jboolean value) {


//@line:146

        THIS->SetShowWhitespacesEnabled(value);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nIsShowWhitespacesEnabled(JNIEnv* env, jobject object) {


//@line:154

        return THIS->IsShowWhitespacesEnabled();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetShowSpacesEnabled(JNIEnv* env, jobject object, jboolean value) {


//@line:162

        THIS->SetShowSpacesEnabled(value);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nIsShowSpacesEnabled(JNIEnv* env, jobject object) {


//@line:170

        return THIS->IsShowSpacesEnabled();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetShowTabsEnabled(JNIEnv* env, jobject object, jboolean value) {


//@line:178

        THIS->SetShowTabsEnabled(value);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nIsShowTabsEnabled(JNIEnv* env, jobject object) {


//@line:186

        return THIS->IsShowTabsEnabled();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetShowLineNumbersEnabled(JNIEnv* env, jobject object, jboolean value) {


//@line:194

        THIS->SetShowLineNumbersEnabled(value);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nIsShowLineNumbersEnabled(JNIEnv* env, jobject object) {


//@line:202

        return THIS->IsShowLineNumbersEnabled();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetShowScrollbarMiniMapEnabled(JNIEnv* env, jobject object, jboolean value) {


//@line:210

        THIS->SetShowScrollbarMiniMapEnabled(value);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nIsShowScrollbarMiniMapEnabled(JNIEnv* env, jobject object) {


//@line:218

        return THIS->IsShowScrollbarMiniMapEnabled();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetShowPanScrollIndicatorEnabled(JNIEnv* env, jobject object, jboolean value) {


//@line:226

        THIS->SetShowPanScrollIndicatorEnabled(value);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nIsShowPanScrollIndicatorEnabled(JNIEnv* env, jobject object) {


//@line:234

        return THIS->IsShowPanScrollIndicatorEnabled();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetShowMatchingBrackets(JNIEnv* env, jobject object, jboolean value) {


//@line:242

        THIS->SetShowMatchingBrackets(value);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nIsShowingMatchingBrackets(JNIEnv* env, jobject object) {


//@line:250

        return THIS->IsShowingMatchingBrackets();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetCompletePairedGlyphs(JNIEnv* env, jobject object, jboolean value) {


//@line:258

        THIS->SetCompletePairedGlyphs(value);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nIsCompletingPairedGlyphs(JNIEnv* env, jobject object) {


//@line:266

        return THIS->IsCompletingPairedGlyphs();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetOverwriteEnabled(JNIEnv* env, jobject object, jboolean value) {


//@line:274

        THIS->SetOverwriteEnabled(value);
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nIsOverwriteEnabled(JNIEnv* env, jobject object) {


//@line:282

        return THIS->IsOverwriteEnabled();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetMiddleMousePanMode(JNIEnv* env, jobject object) {


//@line:290

        THIS->SetMiddleMousePanMode();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetMiddleMouseScrollMode(JNIEnv* env, jobject object) {


//@line:298

        THIS->SetMiddleMouseScrollMode();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nIsMiddleMousePanMode(JNIEnv* env, jobject object) {


//@line:306

        return THIS->IsMiddleMousePanMode();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetText(JNIEnv* env, jobject object, jstring obj_text) {

//@line:314

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        THIS->SetText(text);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetText(JNIEnv* env, jobject object) {


//@line:324

        return env->NewStringUTF(THIS->GetText().c_str());
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetCursorText(JNIEnv* env, jobject object, jlong cursor) {


//@line:332

        return env->NewStringUTF(THIS->GetCursorText(cursor).c_str());
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetLineText(JNIEnv* env, jobject object, jint line) {


//@line:340

        return env->NewStringUTF(THIS->GetLineText(line).c_str());
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetSectionText(JNIEnv* env, jobject object, jint startLine, jint startColumn, jint endLine, jint endColumn) {


//@line:348

        return env->NewStringUTF(THIS->GetSectionText(startLine, startColumn, endLine, endColumn).c_str());
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nReplaceSectionText(JNIEnv* env, jobject object, jint startLine, jint startColumn, jint endLine, jint endColumn, jstring obj_text) {

//@line:356

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        THIS->ReplaceSectionText(startLine, startColumn, endLine, endColumn, text);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nIsEmpty(JNIEnv* env, jobject object) {


//@line:370

        return THIS->IsEmpty();
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetLineCount(JNIEnv* env, jobject object) {


//@line:378

        return THIS->GetLineCount();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nRender__Ljava_lang_String_2(JNIEnv* env, jobject object, jstring obj_title) {

//@line:402

        auto title = obj_title == NULL ? NULL : (char*)env->GetStringUTFChars(obj_title, JNI_FALSE);
        THIS->Render(title);
        if (title != NULL) env->ReleaseStringUTFChars(obj_title, title);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nRender__Ljava_lang_String_2FF(JNIEnv* env, jobject object, jstring obj_title, jfloat sizeX, jfloat sizeY) {

//@line:408

        auto title = obj_title == NULL ? NULL : (char*)env->GetStringUTFChars(obj_title, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        THIS->Render(title, size);
        if (title != NULL) env->ReleaseStringUTFChars(obj_title, title);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nRender__Ljava_lang_String_2FFZ(JNIEnv* env, jobject object, jstring obj_title, jfloat sizeX, jfloat sizeY, jboolean border) {

//@line:415

        auto title = obj_title == NULL ? NULL : (char*)env->GetStringUTFChars(obj_title, JNI_FALSE);
        ImVec2 size = ImVec2(sizeX, sizeY);
        THIS->Render(title, size, border);
        if (title != NULL) env->ReleaseStringUTFChars(obj_title, title);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetFocus(JNIEnv* env, jobject object) {


//@line:430

        THIS->SetFocus();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nCut(JNIEnv* env, jobject object) {


//@line:438

        THIS->Cut();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nCopy(JNIEnv* env, jobject object) {


//@line:446

        THIS->Copy();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nPaste(JNIEnv* env, jobject object) {


//@line:454

        THIS->Paste();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nUndo(JNIEnv* env, jobject object) {


//@line:462

        THIS->Undo();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nRedo(JNIEnv* env, jobject object) {


//@line:470

        THIS->Redo();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nCanUndo(JNIEnv* env, jobject object) {


//@line:478

        return THIS->CanUndo();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nCanRedo(JNIEnv* env, jobject object) {


//@line:486

        return THIS->CanRedo();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetUndoIndex(JNIEnv* env, jobject object) {


//@line:494

        return THIS->GetUndoIndex();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetCursor(JNIEnv* env, jobject object, jint line, jint column) {


//@line:502

        THIS->SetCursor(line, column);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectAll(JNIEnv* env, jobject object) {


//@line:510

        THIS->SelectAll();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectLine(JNIEnv* env, jobject object, jint line) {


//@line:518

        THIS->SelectLine(line);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectLines(JNIEnv* env, jobject object, jint start, jint end) {


//@line:526

        THIS->SelectLines(start, end);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectRegion(JNIEnv* env, jobject object, jint startLine, jint startColumn, jint endLine, jint endColumn) {


//@line:534

        THIS->SelectRegion(startLine, startColumn, endLine, endColumn);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectToBrackets__(JNIEnv* env, jobject object) {


//@line:546

        THIS->SelectToBrackets();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectToBrackets__Z(JNIEnv* env, jobject object, jboolean includeBrackets) {


//@line:550

        THIS->SelectToBrackets(includeBrackets);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGrowSelectionsToCurlyBrackets(JNIEnv* env, jobject object) {


//@line:558

        THIS->GrowSelectionsToCurlyBrackets();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nShrinkSelectionsToCurlyBrackets(JNIEnv* env, jobject object) {


//@line:566

        THIS->ShrinkSelectionsToCurlyBrackets();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nAddNextOccurrence(JNIEnv* env, jobject object) {


//@line:574

        THIS->AddNextOccurrence();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectAllOccurrences(JNIEnv* env, jobject object) {


//@line:582

        THIS->SelectAllOccurrences();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nAnyCursorHasSelection(JNIEnv* env, jobject object) {


//@line:590

        return THIS->AnyCursorHasSelection();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nAllCursorsHaveSelection(JNIEnv* env, jobject object) {


//@line:598

        return THIS->AllCursorsHaveSelection();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nCurrentCursorHasSelection(JNIEnv* env, jobject object) {


//@line:606

        return THIS->CurrentCursorHasSelection();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nClearCursors(JNIEnv* env, jobject object) {


//@line:614

        THIS->ClearCursors();
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetNumberOfCursors(JNIEnv* env, jobject object) {


//@line:622

        return THIS->GetNumberOfCursors();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetMainCursorPosition(JNIEnv* env, jobject object, jobject dst) {


//@line:636

        Jni::TextEditorCursorPositionCpy(env, THIS->GetMainCursorPosition(), dst);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetCurrentCursorPosition(JNIEnv* env, jobject object, jobject dst) {


//@line:650

        Jni::TextEditorCursorPositionCpy(env, THIS->GetCurrentCursorPosition(), dst);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetCursorPosition(JNIEnv* env, jobject object, jobject dst, jlong cursor) {


//@line:664

        Jni::TextEditorCursorPositionCpy(env, THIS->GetCursorPosition(cursor), dst);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetCursorSelection(JNIEnv* env, jobject object, jobject dst, jlong cursor) {


//@line:678

        Jni::TextEditorCursorSelectionCpy(env, THIS->GetCursorSelection(cursor), dst);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetMainCursorSelection(JNIEnv* env, jobject object, jobject dst) {


//@line:692

        Jni::TextEditorCursorSelectionCpy(env, THIS->GetMainCursorSelection(), dst);
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetWordAtScreenPos(JNIEnv* env, jobject object, jfloat screenPosX, jfloat screenPosY) {

//@line:704

        ImVec2 screenPos = ImVec2(screenPosX, screenPosY);
        auto _result = env->NewStringUTF(THIS->GetWordAtScreenPos(screenPos).c_str());
        return _result;
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nScrollToLine(JNIEnv* env, jobject object, jint line, jint alignment) {


//@line:714

        THIS->ScrollToLine(line, static_cast<TextEditor::Scroll>(alignment));
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetFirstVisibleLine(JNIEnv* env, jobject object) {


//@line:726

        return THIS->GetFirstVisibleLine();
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetLastVisibleLine(JNIEnv* env, jobject object) {


//@line:734

        return THIS->GetLastVisibleLine();
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetFirstVisibleColumn(JNIEnv* env, jobject object) {


//@line:742

        return THIS->GetFirstVisibleColumn();
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetLastVisibleColumn(JNIEnv* env, jobject object) {


//@line:750

        return THIS->GetLastVisibleColumn();
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetLineHeight(JNIEnv* env, jobject object) {


//@line:758

        return THIS->GetLineHeight();
    

}

JNIEXPORT jfloat JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetGlyphWidth(JNIEnv* env, jobject object) {


//@line:766

        return THIS->GetGlyphWidth();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectFirstOccurrenceOf__Ljava_lang_String_2(JNIEnv* env, jobject object, jstring obj_text) {

//@line:782

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        THIS->SelectFirstOccurrenceOf(text);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectFirstOccurrenceOf__Ljava_lang_String_2Z(JNIEnv* env, jobject object, jstring obj_text, jboolean caseSensitive) {

//@line:788

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        THIS->SelectFirstOccurrenceOf(text, caseSensitive);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectFirstOccurrenceOf__Ljava_lang_String_2ZZ(JNIEnv* env, jobject object, jstring obj_text, jboolean caseSensitive, jboolean wholeWord) {

//@line:794

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        THIS->SelectFirstOccurrenceOf(text, caseSensitive, wholeWord);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectNextOccurrenceOf__Ljava_lang_String_2(JNIEnv* env, jobject object, jstring obj_text) {

//@line:812

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        THIS->SelectNextOccurrenceOf(text);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectNextOccurrenceOf__Ljava_lang_String_2Z(JNIEnv* env, jobject object, jstring obj_text, jboolean caseSensitive) {

//@line:818

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        THIS->SelectNextOccurrenceOf(text, caseSensitive);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectNextOccurrenceOf__Ljava_lang_String_2ZZ(JNIEnv* env, jobject object, jstring obj_text, jboolean caseSensitive, jboolean wholeWord) {

//@line:824

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        THIS->SelectNextOccurrenceOf(text, caseSensitive, wholeWord);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectAllOccurrencesOf__Ljava_lang_String_2(JNIEnv* env, jobject object, jstring obj_text) {

//@line:842

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        THIS->SelectAllOccurrencesOf(text);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectAllOccurrencesOf__Ljava_lang_String_2Z(JNIEnv* env, jobject object, jstring obj_text, jboolean caseSensitive) {

//@line:848

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        THIS->SelectAllOccurrencesOf(text, caseSensitive);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectAllOccurrencesOf__Ljava_lang_String_2ZZ(JNIEnv* env, jobject object, jstring obj_text, jboolean caseSensitive, jboolean wholeWord) {

//@line:854

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        THIS->SelectAllOccurrencesOf(text, caseSensitive, wholeWord);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nReplaceTextInCurrentCursor(JNIEnv* env, jobject object, jstring obj_text) {

//@line:864

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        THIS->ReplaceTextInCurrentCursor(text);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nReplaceTextInAllCursors(JNIEnv* env, jobject object, jstring obj_text) {

//@line:874

        auto text = obj_text == NULL ? NULL : (char*)env->GetStringUTFChars(obj_text, JNI_FALSE);
        THIS->ReplaceTextInAllCursors(text);
        if (text != NULL) env->ReleaseStringUTFChars(obj_text, text);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nOpenFindReplaceWindow(JNIEnv* env, jobject object) {


//@line:884

        THIS->OpenFindReplaceWindow();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nCloseFindReplaceWindow(JNIEnv* env, jobject object) {


//@line:892

        THIS->CloseFindReplaceWindow();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetFindButtonLabel(JNIEnv* env, jobject object, jstring obj_label) {

//@line:900

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        THIS->SetFindButtonLabel(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetFindAllButtonLabel(JNIEnv* env, jobject object, jstring obj_label) {

//@line:910

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        THIS->SetFindAllButtonLabel(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetReplaceButtonLabel(JNIEnv* env, jobject object, jstring obj_label) {

//@line:920

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        THIS->SetReplaceButtonLabel(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetReplaceAllButtonLabel(JNIEnv* env, jobject object, jstring obj_label) {

//@line:930

        auto label = obj_label == NULL ? NULL : (char*)env->GetStringUTFChars(obj_label, JNI_FALSE);
        THIS->SetReplaceAllButtonLabel(label);
        if (label != NULL) env->ReleaseStringUTFChars(obj_label, label);
    
}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nHasFindString(JNIEnv* env, jobject object) {


//@line:940

        return THIS->HasFindString();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nFindNext(JNIEnv* env, jobject object) {


//@line:948

        THIS->FindNext();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nFindAll(JNIEnv* env, jobject object) {


//@line:956

        THIS->FindAll();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nAddMarker(JNIEnv* env, jobject object, jint line, jint lineNumberColor, jint textColor, jstring obj_lineNumberTooltip, jstring obj_textTooltip) {

//@line:964

        auto lineNumberTooltip = obj_lineNumberTooltip == NULL ? NULL : (char*)env->GetStringUTFChars(obj_lineNumberTooltip, JNI_FALSE);
        auto textTooltip = obj_textTooltip == NULL ? NULL : (char*)env->GetStringUTFChars(obj_textTooltip, JNI_FALSE);
        THIS->AddMarker(line, lineNumberColor, textColor, lineNumberTooltip, textTooltip);
        if (lineNumberTooltip != NULL) env->ReleaseStringUTFChars(obj_lineNumberTooltip, lineNumberTooltip);
        if (textTooltip != NULL) env->ReleaseStringUTFChars(obj_textTooltip, textTooltip);
    
}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nClearMarkers(JNIEnv* env, jobject object) {


//@line:984

        THIS->ClearMarkers();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nHasMarkers(JNIEnv* env, jobject object) {


//@line:992

        return THIS->HasMarkers();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nIndentLines(JNIEnv* env, jobject object) {


//@line:1000

        THIS->IndentLines();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nDeindentLines(JNIEnv* env, jobject object) {


//@line:1008

        THIS->DeindentLines();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nMoveUpLines(JNIEnv* env, jobject object) {


//@line:1016

        THIS->MoveUpLines();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nMoveDownLines(JNIEnv* env, jobject object) {


//@line:1024

        THIS->MoveDownLines();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nToggleComments(JNIEnv* env, jobject object) {


//@line:1032

        THIS->ToggleComments();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectionToLowerCase(JNIEnv* env, jobject object) {


//@line:1040

        THIS->SelectionToLowerCase();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSelectionToUpperCase(JNIEnv* env, jobject object) {


//@line:1048

        THIS->SelectionToUpperCase();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nStripTrailingWhitespaces(JNIEnv* env, jobject object) {


//@line:1056

        THIS->StripTrailingWhitespaces();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nTabsToSpaces(JNIEnv* env, jobject object) {


//@line:1064

        THIS->TabsToSpaces();
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSpacesToTabs(JNIEnv* env, jobject object) {


//@line:1072

        THIS->SpacesToTabs();
    

}

JNIEXPORT jintArray JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_getPalette(JNIEnv* env, jobject object) {


//@line:1076

        return TextEditorPaletteToArray(env, THIS->GetPalette());
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetPalette(JNIEnv* env, jobject object, jintArray obj_palette) {
	int* palette = (int*)env->GetPrimitiveArrayCritical(obj_palette, 0);


//@line:1084

        auto newPalette = THIS->GetPalette();
        TextEditorArrayToPalette(env, obj_palette, newPalette);
        THIS->SetPalette(newPalette);
    
	env->ReleasePrimitiveArrayCritical(obj_palette, palette, 0);

}

JNIEXPORT jintArray JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_getDefaultPalette(JNIEnv* env, jclass clazz) {


//@line:1090

        return TextEditorPaletteToArray(env, TextEditor::GetDefaultPalette());
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetDefaultPalette(JNIEnv* env, jclass clazz, jintArray obj_palette) {
	int* palette = (int*)env->GetPrimitiveArrayCritical(obj_palette, 0);


//@line:1098

        auto newPalette = TextEditor::GetDefaultPalette();
        TextEditorArrayToPalette(env, obj_palette, newPalette);
        TextEditor::SetDefaultPalette(newPalette);
    
	env->ReleasePrimitiveArrayCritical(obj_palette, palette, 0);

}

JNIEXPORT jintArray JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_getDarkPalette(JNIEnv* env, jclass clazz) {


//@line:1104

        return TextEditorPaletteToArray(env, TextEditor::GetDarkPalette());
    

}

JNIEXPORT jintArray JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_getLightPalette(JNIEnv* env, jclass clazz) {


//@line:1108

        return TextEditorPaletteToArray(env, TextEditor::GetLightPalette());
    

}

JNIEXPORT jint JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_getPaletteColor(JNIEnv* env, jobject object, jint colorIndex) {


//@line:1120

        const auto& palette = THIS->GetPalette();
        const auto index = static_cast<size_t>(colorIndex);
        if (index >= palette.size()) {
            jclass exClass = env->FindClass("java/lang/ArrayIndexOutOfBoundsException");
            env->ThrowNew(exClass, "Invalid TextEditor color index");
            return 0;
        }
        return static_cast<jint>(palette[index]);
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_setPaletteColor(JNIEnv* env, jobject object, jint colorIndex, jint value) {


//@line:1135

        auto palette = THIS->GetPalette();
        const auto index = static_cast<size_t>(colorIndex);
        if (index >= palette.size()) {
            jclass exClass = env->FindClass("java/lang/ArrayIndexOutOfBoundsException");
            env->ThrowNew(exClass, "Invalid TextEditor color index");
            return;
        }
        palette[index] = static_cast<ImU32>(value);
        THIS->SetPalette(palette);
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetLanguage(JNIEnv* env, jobject object) {


//@line:1155

        return (uintptr_t)THIS->GetLanguage();
    

}

JNIEXPORT jboolean JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nHasLanguage(JNIEnv* env, jobject object) {


//@line:1163

        return THIS->HasLanguage();
    

}

JNIEXPORT jstring JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetLanguageName(JNIEnv* env, jobject object) {


//@line:1171

        return env->NewStringUTF(THIS->GetLanguageName().c_str());
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetImGuiContext(JNIEnv* env, jclass clazz, jlong ctx) {


//@line:1179

        TextEditor::SetImGuiContext(reinterpret_cast<ImGuiContext*>(ctx));
    

}

JNIEXPORT void JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nSetUserData(JNIEnv* env, jobject object, jint line, jlong data) {


//@line:1187

        THIS->SetUserData(line, reinterpret_cast<void*>(data));
    

}

JNIEXPORT jlong JNICALL Java_imgui_moulberry92_extension_texteditor_TextEditor_nGetUserData(JNIEnv* env, jobject object, jint line) {


//@line:1195

        return reinterpret_cast<jlong>(THIS->GetUserData(line));
    

}


//@line:1199

        #undef THIS
     