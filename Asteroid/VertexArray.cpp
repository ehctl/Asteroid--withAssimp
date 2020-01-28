// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "VertexArray.h"
#include <GL/glew.h>
#include <iostream>

using namespace std;

VertexArray::VertexArray(const float* verts,int vertNum ,const float* normal, const float* textCord
	, const unsigned int* indices,int indiceNum, const void* joint)
	:mNumVerts( vertNum  )
	,mNumIndices( indiceNum )
{	
	if( joint == nullptr) {
		// Create vertex array
		glGenVertexArrays(1, &mVertexArray);
		glBindVertexArray(mVertexArray);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// Create vertex buffer
		glGenBuffers(1, &mVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertNum * 3 * sizeof(float), verts, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);


		unsigned textCordd;
		glGenBuffers(1, &textCordd);
		glBindBuffer(GL_ARRAY_BUFFER, textCordd);
		glBufferData(GL_ARRAY_BUFFER, vertNum * 2 * sizeof(float), textCord, GL_STATIC_DRAW);
		
		glVertexAttribPointer(2, 2, GL_FLOAT, 0,0,0);


		unsigned normalBuff;
		glGenBuffers(1, &normalBuff);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuff);
		glBufferData(GL_ARRAY_BUFFER, vertNum * 3 * sizeof(float), normal, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, 0,0,0);

		// Create index buffer
		glGenBuffers(1, &mIndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceNum * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}
	else {

		glGenVertexArrays(1, &mVertexArray);
		glBindVertexArray(mVertexArray);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);
		// Create vertex buffer
		glGenBuffers(1, &mVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertNum * 3 * sizeof(float), verts, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, 0,0, 0);

		unsigned textCordd;
		glGenBuffers(1, &textCordd);
		glBindBuffer(GL_ARRAY_BUFFER, textCordd);
		glBufferData(GL_ARRAY_BUFFER, vertNum * 2 * sizeof(float), textCord, GL_STATIC_DRAW);

		glVertexAttribPointer(2, 2, GL_FLOAT, 0,0, 0);

		unsigned normalBuff;
		glGenBuffers(1, &normalBuff);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuff);
		glBufferData(GL_ARRAY_BUFFER, vertNum * 3 * sizeof(float), normal, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, 0, 0, 0);

		unsigned jointBuff;
		glGenBuffers(1, &jointBuff);
		glBindBuffer(GL_ARRAY_BUFFER, jointBuff);
		glBufferData(GL_ARRAY_BUFFER, vertNum *(4 * sizeof(int) + 4 * sizeof(float)) , joint , GL_STATIC_DRAW);
		glVertexAttribIPointer(3, 4, GL_INT ,  (4 * sizeof(int) + 4 * sizeof(float)), 0);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE,  (4 * sizeof(int) + 4 * sizeof(float)), reinterpret_cast<void*>( sizeof(int) * 4) ) ;

		// Create index buffer
		glGenBuffers(1, &mIndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceNum * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}

}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
}