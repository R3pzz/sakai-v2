// dear imgui: FreeType font builder (used as a replacement for the stb_truetype builder)
// (headers)

#pragma once

#include "imgui.h"      // IMGUI_API

enum ImGuiFreeTypeBuilderFlags
{
    ImGuiFreeTypeBuilderFlags_NoHinting     = 1 << 0,   // Disable hinting. This generally generates 'blurrier' bitmap glyphs when the glyph are rendered in any of the anti-aliased modes.
    ImGuiFreeTypeBuilderFlags_NoAutoHint    = 1 << 1,   // Disable auto-hinter.
    ImGuiFreeTypeBuilderFlags_ForceAutoHint = 1 << 2,   // Indicates that the auto-hinter is preferred over the font's native hinter.
    ImGuiFreeTypeBuilderFlags_LightHinting  = 1 << 3,   // A lighter hinting algorithm for gray-level modes. Many generated glyphs are fuzzier but better resemble their original shape. This is achieved by snapping glyphs to the pixel grid only vertically (Y-axis), as is done by Microsoft's ClearType and Adobe's proprietary font renderer. This preserves inter-glyph spacing in horizontal text.
    ImGuiFreeTypeBuilderFlags_MonoHinting   = 1 << 4,   // Strong hinting algorithm that should only be used for monochrome output.
    ImGuiFreeTypeBuilderFlags_Bold          = 1 << 5,   // Styling: Should we artificially embolden the font?
    ImGuiFreeTypeBuilderFlags_Oblique       = 1 << 6,   // Styling: Should we slant the font, emulating italic style?
    ImGuiFreeTypeBuilderFlags_Monochrome    = 1 << 7,   // Disable anti-aliasing. Combine this with MonoHinting for best results!
    ImGuiFreeTypeBuilderFlags_LoadColor     = 1 << 8,   // Enable FreeType color-layered glyphs
    ImGuiFreeTypeBuilderFlags_Bitmap        = 1 << 9    // Enable FreeType bitmap glyphs
};
