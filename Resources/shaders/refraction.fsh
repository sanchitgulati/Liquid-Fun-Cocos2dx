
#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
varying mediump vec2 v_texCoordRefraction;


void main(void)
{
    
    
    mediump vec4 refractionColor = texture2D(CC_Texture1,v_texCoordRefraction);
    mediump vec4 texColor = texture2D(CC_Texture0, v_texCoord + vec2(refractionColor.r   ,refractionColor.g   ));
    
    //you can also use the blue color to change the alpha ...
    gl_FragColor = vec4(v_fragmentColor.rgb * texColor.rgb  , texColor.a + refractionColor.b);
}
