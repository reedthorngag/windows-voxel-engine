#version 460 core
  
out vec4 FragColor;
in vec3 color;

void main()
{
    FragColor = vec4(color.xyz, 1.0);
    //if (FragColor == vec4(0,0,0,1))
    //    discard;
}