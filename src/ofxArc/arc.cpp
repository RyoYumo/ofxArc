#include "arc.hpp"
#include <memory>
#include "ofMain.h"

namespace {

std::shared_ptr<ofx::arc::Renderer> getRenderer(){
    static std::shared_ptr<ofx::arc::Renderer> renderer = std::make_shared<ofx::arc::Renderer>();
    return renderer;
}
}

namespace ofx{
namespace arc{

Renderer::Renderer(){
    ofShaderSettings solid_arc_settings;
    solid_arc_settings.shaderSources[GL_VERTEX_SHADER] = R"(
        #version 400
        uniform mat4 modelViewProjectionMatrix;
        layout(location = 0) in vec4 position;
        out vec4 v_position;
        void main(){
            v_position  = position;
            gl_Position = modelViewProjectionMatrix * position;
        }
    )";
    
    solid_arc_settings.shaderSources[GL_FRAGMENT_SHADER] = R"(
        #version 400
        const float PI  = 3.141592653589793;
        const float PI2 = PI * 2.0;
        
        out vec4 output_color;
        in  vec4 v_position;
        uniform vec2  u_angle;
        uniform float u_radius;
        uniform float u_thickness;
        uniform vec4  globalColor;
        void main(){
            float theta      = 360 * (1.0 - fract(atan(v_position.x, v_position.y) / PI2 + 0.5));
            float r = step(u_radius-u_thickness, length(v_position));
            float d = step(u_angle.x, theta) - step(u_angle.y, theta);
            output_color     = vec4(globalColor.rgb, r * d);
        }
    )";
    
    solid_arc_shader_.setup(solid_arc_settings);
}


void Renderer::drawSolidArc(float radius, float deg_from, float deg_to, float thickness){
    solid_arc_shader_.begin();
    solid_arc_shader_.setUniform1f("u_radius", radius);
    solid_arc_shader_.setUniform1f("u_thickness", thickness);
    solid_arc_shader_.setUniform2f("u_angle", deg_from, deg_to);
    ofDrawCircle(0, 0, radius);
    solid_arc_shader_.end();
}


void drawSolidArc(float radius, float deg_from, float deg_to, float thickness){
    getRenderer()->drawSolidArc(radius, deg_from, deg_to, thickness);
}



} // namespace arc
} // namespace ofx
