#version 330 core
out vec4 FragColor;
 in float vHeight;

 uniform float maxHeight;

void main()
{
	float n = vHeight / maxHeight;

	vec3 color;

	if(n <= 0.45){color = vec3(0.761, 0.698, 0.502);} // sand
	else if(n <= 0.50){color = vec3(0.124, 0.252, 0.000);} // grass
	else if(n <= 0.60){color = vec3(0.5);} // rock
	else{color = vec3(1.0);}

	FragColor = vec4(color, 1.0);
}

