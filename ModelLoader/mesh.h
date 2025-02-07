#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
using namespace std;

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    //glm::vec3 Tangent;
    //glm::vec3 Bitangent;
    //int m_BoneIDs[MAX_BONE_INFLUENCE];
    //float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    unsigned int id;
    string type;
    string path;  
};

class Mesh {
public:    
    vector<Vertex> vertices;    
    vector<unsigned int> indices;
    vector<Texture> textures;    

    Mesh(vector<Vertex> vertices,  vector<unsigned int> indices, vector<Texture> textures) {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;          
    }

    const char* GetTexturePath(unsigned int index) {
        if (index < textures.size()) {
            return textures[index].path.c_str();
        }
        return "";
    }

    /*
    // Function to get vertex positions
    const glm::vec3* GetVertexPositions() {
        return vertices.empty() ? nullptr : &vertices[0].Position;
    }

    unsigned int GetVertexCount() {
        return static_cast<unsigned int>(vertices.size());
    }
    */

};

// Exported functions for the DLL
extern "C" {
    __declspec(dllexport) Mesh* CreateMesh(Vertex* vertices, unsigned int vertexCount, unsigned int* indices, unsigned int indexCount);
    //__declspec(dllexport) void DeleteMesh(Mesh* mesh);
    //__declspec(dllexport) Vertex GetVertex(Mesh* mesh, unsigned int index);
    //__declspec(dllexport) const char* GetMeshTexturePath(Mesh* mesh, unsigned int index);
    //__declspec(dllexport) const float* GetVertexPositions(Mesh* mesh, unsigned int* count);
}

Mesh* CreateMesh(Vertex* vertices, unsigned int vertexCount, unsigned int* indices, unsigned int indexCount) {
    vector<Vertex> vertexVec(vertices, vertices + vertexCount);
    vector<unsigned int> indexVec(indices, indices + indexCount);
    vector<Texture> textures;  // Assuming no textures for simplicity
    return new Mesh(vertexVec, indexVec, textures);
}

#endif