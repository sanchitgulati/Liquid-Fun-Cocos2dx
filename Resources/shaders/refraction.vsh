attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
varying mediump vec2 v_texCoordRefraction;


void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_fragmentColor = a_color;
    v_texCoord = a_texCoord;
    
    v_texCoordRefraction = a_texCoord + vec2(sin(CC_Time[1]),cos(CC_Time[1])) / vec2(32.0,32.0);
}