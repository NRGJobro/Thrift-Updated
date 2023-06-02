#include "RenderUtils.h"

// Define
class MinecraftUIRenderContext* RenderUtils::context;
// Colors
struct Color RenderUtils::white = Color(255, 255, 255);
struct Color RenderUtils::black = Color(0, 0, 0);
struct Color RenderUtils::red = Color(255, 0, 0);
struct Color RenderUtils::lime = Color(0, 255, 0);
struct Color RenderUtils::blue = Color(0, 0, 255);
struct Color RenderUtils::yellow = Color(255, 255, 0);
struct Color RenderUtils::cyan = Color(0, 255, 255);
struct Color RenderUtils::purple = Color(255, 0, 255);
RenderUtils* renderUtils;