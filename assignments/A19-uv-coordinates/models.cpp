#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <string>

std::vector<Vertex> M1_vertices;
std::vector<Vertex> M2_vertices;

struct Coordinate
{
	float x;
	float y;
	float z;
};

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 UV;
};

struct UVFace
{
	glm::vec2 topL;
	glm::vec2 topR;
	glm::vec2 botL;
	glm::vec2 botR;
};

UVFace UVcoordGen(glm::vec2 botL, float faceLength)
{
	glm::vec2 topL = glm::vec2(botL.x, botL.y + faceLength);
	glm::vec2 topR = glm::vec2(botL.x + faceLength, botL.y + faceLength);
	glm::vec2 botR = glm::vec2(botL.x + faceLength, botL.y);
	glm::vec2 botL = glm::vec2(botL.x, botL.y);
	return {topL, topR, botL, botR};
}

void createCube()
{
	float faceLength = 0.5f / 4;

	// vertex coordinates of the cube
	// we'll then add three of these to the vertex buffer
	// each with different normal and UV coordinates
	std::vector<glm::vec3> vertPos = {
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 1, 1),
		glm::vec3(0, 1, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 1, 1),
		glm::vec3(1, 1, 0),
	};

	// UV coordinates of the faces
	// this map now contains 6 arrays of 4 UV coordinates each
	// each coordinate represent respectively the top left, top right,
	// bottom left, bottom right coordinate of its specific face
	std::map<std::string, UVFace> cubeFaces = {
		{"left", UVcoordGen(glm::vec2(0, 1 - 3 * faceLength), faceLength)},
		{"right", UVcoordGen(glm::vec2(2 * faceLength, 1 - 3 * faceLength), faceLength)},
		{"top", UVcoordGen(glm::vec2(faceLength, 1 - 2 * faceLength), faceLength)},
		{"bottom", UVcoordGen(glm::vec2(faceLength, 1 - 4 * faceLength), faceLength)},
		{"front", UVcoordGen(glm::vec2(faceLength, 1 - 3 * faceLength), faceLength)},
		{"back", UVcoordGen(glm::vec2(faceLength, 1 - faceLength), faceLength)},
	};

	// normals of the vertices
	std::map<std::string, glm::vec3> vertNorms = {
		{"back", glm::vec3(0, 0, -1)},
		{"front", glm::vec3(0, 0, 1)},
		{"top", glm::vec3(0, 1, 0)},
		{"bottom", glm::vec3(0, -1, 0)},
		{"left", glm::vec3(1, 0, 0)},
		{"right", glm::vec3(-1, 0, 0)},
	};

	// now we need to put all of this together in the
	// cube vertices buffer. we'll have 8*3 vertices
	M1_vertices.push_back({vertPos[0], vertNorms["back"], cubeFaces["back"].topL});
	M1_vertices.push_back({vertPos[0], vertNorms["bottom"], cubeFaces["bottom"].botL});
	M1_vertices.push_back({vertPos[0], vertNorms["left"], cubeFaces["left"].botR});

	M1_vertices.push_back({vertPos[1], vertNorms["front"], cubeFaces["front"].botL});
	M1_vertices.push_back({vertPos[1], vertNorms["bottom"], cubeFaces["bottom"].topL});
	M1_vertices.push_back({vertPos[1], vertNorms["left"], cubeFaces["left"].botR});

	M1_vertices.push_back({vertPos[2], vertNorms["top"], cubeFaces["top"].botL});
	M1_vertices.push_back({vertPos[2], vertNorms["left"], cubeFaces["left"].topL});
	M1_vertices.push_back({vertPos[2], vertNorms["front"], cubeFaces["front"].topL});

	M1_vertices.push_back({vertPos[3], vertNorms["top"], cubeFaces["top"].topL});
	M1_vertices.push_back({vertPos[3], vertNorms["left"], cubeFaces["left"].topL});
	M1_vertices.push_back({vertPos[3], vertNorms["back"], cubeFaces["back"].topL});

	M1_vertices.push_back({vertPos[4], vertNorms["bottom"], cubeFaces["bottom"].botR});
	M1_vertices.push_back({vertPos[4], vertNorms["back"], cubeFaces["back"].botR});
	M1_vertices.push_back({vertPos[4], vertNorms["right"], cubeFaces["right"].botR});

	M1_vertices.push_back({vertPos[5], vertNorms["front"], cubeFaces["front"].botR});
	M1_vertices.push_back({vertPos[5], vertNorms["front"], cubeFaces["bottom"].topR});
	M1_vertices.push_back({vertPos[5], vertNorms["right"], cubeFaces["right"].botL});

	M1_indices.resize(36);
	M1_indices = {
		0, 1, 2,
		0, 2, 3,
		4, 5, 6,
		4, 6, 7,
		8, 9, 10,
		8, 10, 11,
		12, 13, 14,
		12, 14, 15,
		16, 17, 18,
		16, 18, 19,
		20, 21, 22,
		20, 22, 23};
}

// this function creates the geometries to be shown, and output them
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices
void makeModels()
{
	// M1 : Cube
	createCube();

	//// M2 : Cylinder
	// Replace the code below, that creates a simple rotated square, with the one to create a cylinder.

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices
	M2_vertices.resize(4);

	// Vertices definitions
	M2_vertices[0].pos = glm::vec3(0.0, -1.0, -1.1);
	M2_vertices[0].norm = glm::vec3(0.0, 0.0, 1.0);
	M2_vertices[0].UV = glm::vec2(0.0, 1.0);

	M2_vertices[1].pos = glm::vec3(1.0, 0.0, -1.1);
	M2_vertices[1].norm = glm::vec3(0.0, 0.0, 1.0);
	M2_vertices[1].UV = glm::vec2(1.0, 1.0);

	M2_vertices[2].pos = glm::vec3(0.0, 1.0, -1.1);
	M2_vertices[2].norm = glm::vec3(0.0, 0.0, 1.0);
	M2_vertices[2].UV = glm::vec2(1.0, 0.0);

	M2_vertices[3].pos = glm::vec3(-1.0, 0.0, -1.1);
	M2_vertices[3].norm = glm::vec3(0.0, 0.0, 1.0);
	M2_vertices[3].UV = glm::vec2(0.0, 0.0);

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M2_indices.resize(6);

	// indices definitions
	M2_indices[0] = 0;
	M2_indices[1] = 1;
	M2_indices[2] = 2;
	M2_indices[3] = 2;
	M2_indices[4] = 3;
	M2_indices[5] = 0;
}