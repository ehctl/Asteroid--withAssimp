// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330


// Uniforms for world transform and view-proj
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
uniform mat4 uMatrixPalette[96];

// Attribute 0 is position, 1 is normal, 2 is tex coords.

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in uvec4 inSkinBones;
layout(location = 4) in vec4 inSkinWeights;

// Any vertex outputs (other than position)
out vec2 fragTexCoord;
// Normal (in world space)
out vec3 fragNormal;
// Position (in world space)
out vec3 fragWorldPos;

void main()
{	

	vec4 pos = vec4(inPosition, 1.0f);
	
	vec4 skinnedPos = (pos * uMatrixPalette[inSkinBones.x]) * inSkinWeights.x;
	skinnedPos += (pos * uMatrixPalette[inSkinBones.y]) * inSkinWeights.y;
	skinnedPos += (pos * uMatrixPalette[inSkinBones.z]) * inSkinWeights.z;
	skinnedPos += (pos * uMatrixPalette[inSkinBones.w]) * inSkinWeights.w;


	skinnedPos =  skinnedPos * uWorldTransform;
	//skinnedPos = pos * uWorldTransform;
	fragWorldPos = skinnedPos.xyz;

	gl_Position =  skinnedPos * uViewProj;

	vec4 skinnedNormal = vec4(inNormal, 0.0f);
	vec4 Normal = (skinnedNormal * uMatrixPalette[inSkinBones.x]) * inSkinWeights.x
		+ (skinnedNormal * uMatrixPalette[inSkinBones.y]) * inSkinWeights.y
		+ (skinnedNormal * uMatrixPalette[inSkinBones.z]) * inSkinWeights.z
		+ (skinnedNormal * uMatrixPalette[inSkinBones.w]) * inSkinWeights.w;
	// Transform normal into world space (w = 0)
	//fragNormal = (skinnedNormal * uWorldTransform).xyz;
	fragNormal = (Normal * uWorldTransform).xyz;
	// Pass along the texture coordinate to frag shader
	fragTexCoord = inTexCoord;
}
