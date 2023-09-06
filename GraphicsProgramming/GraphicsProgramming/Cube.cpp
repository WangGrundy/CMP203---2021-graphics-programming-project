#include "Cube.h"

extern float vertsCube[] = {
	//-1.0, -1.0, -1.0, // vertex #0
	//1.0, -1.0, -1.0, // vertex #1
	//1.0, 1.0, -1.0, // Vertex #2
	//-1.0, 1.0, -1.0, // Vertex #3
	//-1.0, -1.0, 1.0, // Vertex #4
	//1.0, -1.0, 1.0, // Vertex #5
	//1.0, 1.0, 1.0, // Vertex #6
	//-1.0, 1.0, 1.0,  // Vertex #7
	0,0,0,
	0,1,0,
	1,1,0,
	1,0,0,

	1,0,0,
	1,1,0,
	1,1,1,
	1,0,1,

	0,0,1,
	0,1,1,
	0,1,0,
	0,0,0,

	0,0,1,
	1,0,1,
	1,1,1,
	0,1,1,
	
	1,1,1,
	1,1,0,
	0,1,0,
	0,1,1,

	0,0,0,
	1,0,0,
	1,0,1,
	0,0,1

};

extern float normsCube[] = { 
						0.0, 0.0, -1.0,		//1 //front
						0.0, 0.0, -1.0,		//2
						0.0, 0.0, -1.0,		//3
						0.0, 0.0, -1.0,		//4

						1.0, 0.0, 0.0,		//5 //left
						1.0, 0.0, 0.0,		//6
						1.0, 0.0, 0.0,		//7
						1.0, 0.0, 0.0,		//8

						-1.0, 0.0, 0,		//9 //right
						-1.0, 0.0, 0,		//10
						-1.0, 0.0, 0,		//11
						-1.0, 0.0, 0,		//12

						0.0, 0.0, 1.0,		//3 //back
						0.0, 0.0, 1.0,		//3
						0.0, 0.0, 1.0,		//3
						0.0, 0.0, 1.0,		//3

						0.0, 1.0, 0,		//3 //top
						0.0, 1.0, 0,		//3
						0.0, 1.0, 0,		//3
						0.0, 1.0, 0,		//3

						0.0, -1.0, 0,		//3 //bottom
						0.0, -1.0, 0,		//3
						0.0, -1.0, 0,		//3
						0.0, -1.0, 0,		//3
};

extern float texcoordsCube[] = { 
							0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3

							0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3

							0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3

							0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3

							0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3

							0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3
};

GLubyte indicesCube[] = {
	0,1,2,3,//FRONT
	4,5,6,7,//RIGHT
	8,9,10,11,//LEFT
	12,13,14,15,//BOTTOM
	16,17,18,19, //BACK
	20,21,22,23,//TOP
};


void Cube::RenderCube() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertsCube);
	glNormalPointer(GL_FLOAT, 0, normsCube);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoordsCube);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indicesCube);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);
	////glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glVertexPointer(, GL_FLOAT, 0, vertsCube);
	//glNormalPointer(GL_FLOAT, 0, norms);
	////glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	//glBegin(GL_QUADS);
	//glArrayElement(0);
	//glArrayElement(1);
	//glArrayElement(2);
	//glArrayElement(3);
	//glEnd();

	//glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);
	////glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


