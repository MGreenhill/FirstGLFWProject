#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 ourColor;
uniform float xOffset;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor=gl_Position.xyz;
};

//Q: Why is the bottom-left side of our triangle black?
//A:
//When using coordinates for fragment colors, xyz become rgb.
//x = red, y = green, z = blue
//The top and bottom-right vertices have at least 1 positive coordinate making
//either red and green poisitive.
//Negative coordinate values are rounded to zero and the z coordinate is zero in all 
//the used vectors.
//The bottom-left vertex does not have any positive coordinates, so it's colors are all
//negative or zero.
//This makes the vertex absent of color and thus black.