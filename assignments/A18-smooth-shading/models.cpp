#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 norm;
};

typedef std::array<glm::vec3, 3> TriangleCoordinates;
typedef std::array<Vertex, 3> Triangle;

std::vector<Vertex> M1_vertices;
std::vector<Vertex> M2_vertices;
std::vector<Vertex> M3_vertices;
std::vector<Vertex> M4_vertices;

Triangle createTriangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	glm::vec3 norm;
	glm::vec3 u = p2 - p1;
	glm::vec3 v = p3 - p1;

	norm = glm::normalize(glm::cross(u, v));

	Vertex v1 = {p1, norm};
	Vertex v2 = {p2, norm};
	Vertex v3 = {p3, norm};
	return {v1, v2, v3};
}

/*
To make the creation of the cube easier I decided to first automate the generation
of the appropriate normals. It's not 100% accurate, but it's close enough.
Then I decided to use a dictionary to store the coordinates of each vertex, and lastly
I used a triangle structure to link together the vertices in a ordered manner, with normals
auto-generated. in this way the vertices are already sorted in their vector, and to setup the
normal vector I just filled it with increasing integers from zero to sizeof(vertices vector) - 1.
*/
void createCube()
{

	std::unordered_map<std::string, glm::vec3> vertMap;
	vertMap["bottom-lb"] = glm::vec3(0, 0, 0);
	vertMap["bottom-lf"] = glm::vec3(0, 0, 1);
	vertMap["bottom-rb"] = glm::vec3(1, 0, 0);
	vertMap["bottom-rf"] = glm::vec3(1, 0, 1);
	vertMap["top-lf"] = glm::vec3(0, 1, 1);
	vertMap["top-lb"] = glm::vec3(0, 1, 0);
	vertMap["top-rf"] = glm::vec3(1, 1, 1);
	vertMap["top-rb"] = glm::vec3(1, 1, 0);

	std::vector<Triangle> triangles;
	// front face
	triangles.push_back(createTriangle(vertMap["bottom-lf"], vertMap["bottom-rf"], vertMap["top-rf"]));
	triangles.push_back(createTriangle(vertMap["top-rf"], vertMap["top-lf"], vertMap["bottom-lf"]));
	// back face
	triangles.push_back(createTriangle(vertMap["bottom-rb"], vertMap["bottom-lb"], vertMap["top-lb"]));
	triangles.push_back(createTriangle(vertMap["top-lb"], vertMap["top-rb"], vertMap["bottom-rb"]));
	// left face
	triangles.push_back(createTriangle(vertMap["bottom-lb"], vertMap["bottom-lf"], vertMap["top-lf"]));
	triangles.push_back(createTriangle(vertMap["top-lf"], vertMap["top-lb"], vertMap["bottom-lb"]));
	// right face
	triangles.push_back(createTriangle(vertMap["bottom-rb"], vertMap["bottom-rf"], vertMap["top-rf"]));
	triangles.push_back(createTriangle(vertMap["top-rf"], vertMap["top-rb"], vertMap["bottom-rb"]));
	// top face
	triangles.push_back(createTriangle(vertMap["top-lf"], vertMap["top-lb"], vertMap["top-rb"]));
	triangles.push_back(createTriangle(vertMap["top-rb"], vertMap["top-rf"], vertMap["top-lf"]));
	// bottom face
	triangles.push_back(createTriangle(vertMap["bottom-lf"], vertMap["bottom-rf"], vertMap["bottom-rb"]));
	triangles.push_back(createTriangle(vertMap["bottom-rb"], vertMap["bottom-lb"], vertMap["bottom-lf"]));

	for (auto &triangle : triangles)
	{
		M1_vertices.push_back(triangle[0]);
		M1_vertices.push_back(triangle[1]);
		M1_vertices.push_back(triangle[2]);
	}

	// fill indices vector
	for (int i = 0; i < M1_vertices.size(); i++)
	{
		M1_indices.push_back(i);
	}
}

void createCylinder(int nSlices, float radius, float height)
{
	// resolution of the cylinder
	float res = 2.0 * M_PI / nSlices;

	// center of the bottom face circumcircle
	float cx = 0, cy = 0, cz = 0;

	std::vector<Triangle> triangles;

	// bottom face
	for (int i = 0; i < nSlices; i++)
	{
		glm::vec3 p1 = glm::vec3(cx + radius * cos(i * res), cy, cz + radius * sin(i * res));
		glm::vec3 p2 = glm::vec3(cx + radius * cos(i + 1 * res), cy, cz + radius * sin(i + 1 * res));
		glm::vec3 p3 = glm::vec3(cx, cy, cz);
		triangles.push_back(createTriangle(p1, p2, p3));
	}

	// top face
	for (int i = 0; i < nSlices; i++)
	{
		glm::vec3 p1 = glm::vec3(cx + radius * cos(i * res), cy + height, cz + radius * sin(i * res));
		glm::vec3 p2 = glm::vec3(cx + radius * cos(i + 1 * res), cy + height, cz + radius * sin(i + 1 * res));
		glm::vec3 p3 = glm::vec3(cx, cy, cz);
		triangles.push_back(createTriangle(p1, p2, p3));
	}

	// side faces
	// for (int i = 0; i < nSlices; i++)
	// {
	// 	glm::vec3 p1 = glm::vec3(cx + radius * cos(i * res), cy, cz + radius * sin(i * res));
	// 	glm::vec3 p2 = glm::vec3(cx + radius * cos(i + 1 * res), cy, cz + radius * sin(i + 1 * res));
	// 	glm::vec3 p3 = glm::vec3(cx + radius * cos(i + 1 * res), cy + height, cz + radius * sin(i + 1 * res));
	// 	triangles.push_back(createTriangle(p1, p2, p3));
	// 	glm::vec3 p4 = glm::vec3(cx + radius * cos(i * res), cy, cz + radius * sin(i * res));
	// 	glm::vec3 p5 = glm::vec3(cx + radius * cos(i + 1 * res), cy + height, cz + radius * sin(i + 1 * res));
	// 	glm::vec3 p6 = glm::vec3(cx + radius * cos(i * res), cy + height, cz + radius * sin(i * res));
	// 	triangles.push_back(createTriangle(p4, p5, p6));
	// }

	for (auto &triangle : triangles)
	{
		M1_vertices.push_back(triangle[0]);
		M1_vertices.push_back(triangle[1]);
		M1_vertices.push_back(triangle[2]);
	}

	// int k1 = 0;			  // 1st vertex index at base
	// int k2 = nSlices + 1; // 1st vertex index at top

	// // M2_indices for the side surface
	// for (int i = 0; i < nSlices; ++i, ++k1, ++k2)
	// {
	// 	// 2 triangles per sector
	// 	// k1 => k1+1 => k2
	// 	M2_indices.push_back(k1);
	// 	M2_indices.push_back(k1 + 1);
	// 	M2_indices.push_back(k2);

	// 	// k2 => k1+1 => k2+1
	// 	M2_indices.push_back(k2);
	// 	M2_indices.push_back(k1 + 1);
	// 	M2_indices.push_back(k2 + 1);
	// }

	// 	int baseCenterIndex = 0;
	// 	int topCenterIndex = nSlices + 1;

	// 	// M2_indices for bottom surfaces
	// 	for (int i = 0, k = baseCenterIndex + 1; i < nSlices; ++i, ++k)
	// 	{
	// 		if (i < nSlices - 1)
	// 		{
	// 			M2_indices.push_back(baseCenterIndex);
	// 			M2_indices.push_back(k + 1);
	// 			M2_indices.push_back(k);
	// 		}
	// 		else // last triangle
	// 		{
	// 			M2_indices.push_back(baseCenterIndex);
	// 			M2_indices.push_back(baseCenterIndex + 1);
	// 			M2_indices.push_back(k);
	// 		}
	// 	}

	// 	// M2_indices for the top surface
	// 	for (int i = 0, k = topCenterIndex + 1; i < nSlices; ++i, ++k)
	// 	{
	// 		if (i < nSlices - 1)
	// 		{
	// 			M2_indices.push_back(topCenterIndex);
	// 			M2_indices.push_back(k);
	// 			M2_indices.push_back(k + 1);
	// 		}
	// 		else // last triangle
	// 		{
	// 			M2_indices.push_back(topCenterIndex);
	// 			M2_indices.push_back(k);
	// 			M2_indices.push_back(topCenterIndex + 1);
	// 		}
	// 	}
}

void makeModels()
{
	// M1 : Cube
	createCube();

	// M2 : Cylinder
	createCylinder(36, 1.0f, 2.0f);

	//// M3 : Sphere
	// Replace the code below, that creates a simple triangle, with the one to create a sphere.

	// Resizes the vertices array. Repalce the values with the correct number of
	// vertices
	M3_vertices.resize(3);

	// Vertices definitions
	M3_vertices[0].pos = glm::vec3(0.0, 1.0, -1.2);
	M3_vertices[0].norm = glm::vec3(0.0, 0.0, 1.0);
	M3_vertices[1].pos = glm::vec3(-0.866, -0.5, -1.2);
	M3_vertices[1].norm = glm::vec3(0.0, 0.0, 1.0);
	M3_vertices[2].pos = glm::vec3(0.866, -0.5, -1.2);
	M3_vertices[2].norm = glm::vec3(0.0, 0.0, 1.0);

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M3_indices.resize(3);

	// indices definitions
	M3_indices[0] = 0;
	M3_indices[1] = 1;
	M3_indices[2] = 2;

	//// M4 : Spring
	// Replace the code below, that creates a simple octahedron, with the one to create a spring.
	M4_vertices.resize(6);

	// Vertices definitions
	M4_vertices[0].pos = glm::vec3(0.0, 1.414, -1.0);
	M4_vertices[0].norm = glm::vec3(0.0, 0.0, 1.0);
	M4_vertices[1].pos = glm::vec3(0.0, -1.414, -1.0);
	M4_vertices[1].norm = glm::vec3(0.0, 0.0, 1.0);
	M4_vertices[2].pos = glm::vec3(-1.0, 0.0, -2.0);
	M4_vertices[2].norm = glm::vec3(0.0, 0.0, 1.0);
	M4_vertices[3].pos = glm::vec3(-1.0, 0.0, 0.0);
	M4_vertices[3].norm = glm::vec3(0.0, -1.0, 0.0);
	M4_vertices[4].pos = glm::vec3(1.0, 0.0, 0.0);
	M4_vertices[4].norm = glm::vec3(0.0, -1.0, 0.0);
	M4_vertices[5].pos = glm::vec3(1.0, 0.0, -2.0);
	M4_vertices[5].norm = glm::vec3(0.0, -1.0, 0.0);

	// Resizes the indices array. Repalce the values with the correct number of
	// indices (3 * number of triangles)
	M4_indices.resize(3 * 8);

	// indices definitions
	M4_indices[0] = 0;
	M4_indices[1] = 2;
	M4_indices[2] = 3;
	M4_indices[3] = 1;
	M4_indices[4] = 3;
	M4_indices[5] = 2;
	M4_indices[6] = 0;
	M4_indices[7] = 3;
	M4_indices[8] = 4;
	M4_indices[9] = 1;
	M4_indices[10] = 4;
	M4_indices[11] = 3;
	M4_indices[12] = 0;
	M4_indices[13] = 4;
	M4_indices[14] = 5;
	M4_indices[15] = 1;
	M4_indices[16] = 5;
	M4_indices[17] = 4;
	M4_indices[18] = 0;
	M4_indices[19] = 5;
	M4_indices[20] = 2;
	M4_indices[21] = 1;
	M4_indices[22] = 2;
	M4_indices[23] = 5;
}