
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif

void main()
{
    gl_Position = CC_PMatrix * a_position;
    float time = mod(CC_Time.x * 0.5,1.0);
    v_fragmentColor = a_color;
    v_texCoord = a_texCoord;
    v_texCoord.x += time;
}
