#ifndef OFX_ARC_ARC_HPP_
#define OFX_ARC_ARC_HPP_

#include "ofShader.h"

namespace ofx{
namespace arc{
class Renderer {
public:
    Renderer();
    void drawSolidArc(float radius, float deg_from, float deg_to, float thickness);
private:
    ofShader solid_arc_shader_;
};

void drawSolidArc(float radius, float deg_from, float deg_to, float thickness);

} // namespace arc
} // namespace ofx


#endif // OFX_ARC_ARC_HPP_
