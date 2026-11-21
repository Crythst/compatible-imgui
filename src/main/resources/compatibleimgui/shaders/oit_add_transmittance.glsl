#ifndef MINECRAFT_OIT_ADD_TRANSMITTANCE_GLSL
#define MINECRAFT_OIT_ADD_TRANSMITTANCE_GLSL

layout(location = 0) out vec4 coeff[OIT_COEFF_ATTACHMENT_COUNT];

void addTransmittance(float transmittance) {
    float coefficients[OIT_COEFF_COUNT];
    for (int i = 0; i < OIT_COEFF_COUNT; i++) {
        coefficients[i] = 0;
    }

    float absorbance = toAbsorbance(transmittance);

    float originalDepth = normalizeDepth(gl_FragCoord.z);
    float depth = originalDepth * float(OIT_NUMBER_OF_DEPTH_BINS - 1) / OIT_NUMBER_OF_DEPTH_BINS;

    float averageAbsorbance = absorbance * (1 - depth);
    coefficients[0] = averageAbsorbance;

    int depthBinIndex = int(floor(originalDepth * (OIT_NUMBER_OF_DEPTH_BINS - 1)));
    // The tree starts at the coefficient 1
    int treeIndex = depthBinIndex + OIT_COEFF_COUNT;

    for (int waveletLevel = 0; waveletLevel <= OIT_WAVELET_RANK; waveletLevel++) {
        int power = OIT_WAVELET_RANK - waveletLevel;
        int parentIndex = treeIndex >> 1;
        float indexAtParentLevel = float(parentIndex & ((1 << power) - 1));

        int isRightHalf = treeIndex & 1;
        int waveletSign = 1 - (isRightHalf << 1);
        float waveletWidth = exp2(-power);
        float waveletHeightScale = exp2(power * 0.5);
        float depthOffsetRelativeToWavelet = depth - waveletWidth * indexAtParentLevel;
        float distanceFromWaveletEdge = isRightHalf * waveletWidth + waveletSign * depthOffsetRelativeToWavelet;
        float differenceCoefficient = distanceFromWaveletEdge * waveletHeightScale * absorbance;
        coefficients[parentIndex] = differenceCoefficient;

        treeIndex = parentIndex;
    }

    // GLSL ES requires fragment output array indices to be constant integral
    // expressions. Unroll the write loop instead of indexing coeff[...] with
    // a loop variable; MobileGlues/ANGLE otherwise rejects the shader with
    // "array indexes for fragment outputs must be constant integral expressions".
#if OIT_COEFF_ATTACHMENT_COUNT > 0
    coeff[0] = vec4(coefficients[0], coefficients[1], coefficients[2], coefficients[3]);
#endif
#if OIT_COEFF_ATTACHMENT_COUNT > 1
    coeff[1] = vec4(coefficients[4], coefficients[5], coefficients[6], coefficients[7]);
#endif
#if OIT_COEFF_ATTACHMENT_COUNT > 2
    coeff[2] = vec4(coefficients[8], coefficients[9], coefficients[10], coefficients[11]);
#endif
#if OIT_COEFF_ATTACHMENT_COUNT > 3
    coeff[3] = vec4(coefficients[12], coefficients[13], coefficients[14], coefficients[15]);
#endif
#if OIT_COEFF_ATTACHMENT_COUNT > 4
    coeff[4] = vec4(coefficients[16], coefficients[17], coefficients[18], coefficients[19]);
#endif
#if OIT_COEFF_ATTACHMENT_COUNT > 5
    coeff[5] = vec4(coefficients[20], coefficients[21], coefficients[22], coefficients[23]);
#endif
#if OIT_COEFF_ATTACHMENT_COUNT > 6
    coeff[6] = vec4(coefficients[24], coefficients[25], coefficients[26], coefficients[27]);
#endif
#if OIT_COEFF_ATTACHMENT_COUNT > 7
    coeff[7] = vec4(coefficients[28], coefficients[29], coefficients[30], coefficients[31]);
#endif
    #ifdef RENDERPEARL_EXPLICIT_DEPTH_INVARIANCE
    gl_FragDepth = gl_FragCoord.z;
    #endif
}

#endif
