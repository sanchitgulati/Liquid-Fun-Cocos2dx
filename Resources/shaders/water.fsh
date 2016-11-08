
#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;


void main(void)
{
    vec4 c = texture2D(CC_Texture0, v_texCoord );
    float new_a = step(0.60,c.w);
    float new_r = step(0.20,c.r);
    float new_b = 1.0 - new_r;
    
    
    c.xyz = vec3(min(c.x,0.9) ,new_a*0.2 ,min(c.z,0.9)*new_b);
    c.w = new_a*0.9;
    
    
    gl_FragColor =  c;
}
