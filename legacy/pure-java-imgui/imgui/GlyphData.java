package com.noimgui.imgui;

interface GlyphData {
    int width();
    int height();
    float bearingX();
    float bearingY();
    float advance();
    byte[] alpha();
}
