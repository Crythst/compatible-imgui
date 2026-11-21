package com.compatibleimgui.mixin.axiom;

import net.minecraft.world.phys.Vec3;
import org.spongepowered.asm.mixin.Mixin;
import org.spongepowered.asm.mixin.Shadow;
import org.spongepowered.asm.mixin.injection.At;
import org.spongepowered.asm.mixin.injection.Inject;
import org.spongepowered.asm.mixin.injection.callback.CallbackInfo;

@Mixin(targets = "com.moulberry.axiom.editor.EditorMovementControls$Rotate", remap = false)
public abstract class MixinAxiomRotate {

    @Shadow
    private Vec3 originalForwards;

    @Inject(method = "update", at = @At("HEAD"), cancellable = true, remap = false)
    private void compatibleimgui$guardNullForwards(double dx, double dy, CallbackInfo ci) {
        if (this.originalForwards == null) {
            // Axiom can construct Rotate with a null vector on the first frame
            // before the camera projection is available. Its update() already
            // handles a null current vector, but dereferences the original one.
            ci.cancel();
        }
    }
}
