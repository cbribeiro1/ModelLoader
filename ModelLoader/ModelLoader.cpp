#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <stdlib.h> // some memory management is done
#include <stdint.h>

#include "Model.h"

extern "C" __declspec(dllexport) Model* CreateModel(const char* path, bool gamma) {
    return new Model(path, gamma);
}

extern "C" __declspec(dllexport) void DeleteModel(Model* model) {
    delete model;
}

extern "C" __declspec(dllexport) unsigned int GetMeshCount(Model* model) {
    return model->meshes.size();
}

extern "C" __declspec(dllexport) Mesh* GetMesh(Model* model, unsigned int index) {
    if (index < model->meshes.size()) {
        return &model->meshes[index];
    }
    return nullptr;
}

extern "C" __declspec(dllexport) unsigned int GetMeshVertexCount(Mesh* mesh) {
    return mesh->vertices.size();
}

extern "C" __declspec(dllexport) void GetMeshVertices(Mesh* mesh, Vertex* vertices) {
    memcpy(vertices, mesh->vertices.data(), mesh->vertices.size() * sizeof(Vertex));
}

extern "C" __declspec(dllexport) unsigned int GetMeshIndexCount(Mesh* mesh) {
    return mesh->indices.size();
}

extern "C" __declspec(dllexport) void GetMeshIndices(Mesh* mesh, unsigned int* indices) {
    memcpy(indices, mesh->indices.data(), mesh->indices.size() * sizeof(unsigned int));
}

extern "C" __declspec(dllexport) void DeleteMesh(Mesh* mesh) {
    delete mesh;
}

extern "C" __declspec(dllexport) Vertex GetVertex(Mesh* mesh, unsigned int index) {
    if (index < mesh->vertices.size()) {
        return mesh->vertices[index];
    }
    Vertex empty = {};
    return empty;
}

extern "C" __declspec(dllexport) unsigned int GetMeshTextureCount(Mesh* mesh) {
    return mesh->textures.size();
}

extern "C" __declspec(dllexport) unsigned int GetMeshTextureId(Mesh* mesh, unsigned int index) {
    return mesh->textures[index].id;
}

extern "C" __declspec(dllexport) const char* GetMeshTexturePath(Mesh* mesh, unsigned int index) {
    return mesh->GetTexturePath(index);
}

extern "C" __declspec(dllexport) int getImageDataAlpha(const char* imagePath, unsigned char** data, int* width, int* height, int* channels) {
    *data = stbi_load(imagePath, width, height, channels, STBI_rgb_alpha);   
    if (*data == NULL) {
        return 1; // Indica erro
    }
    return 0;
    stbi_image_free(data);
}

extern "C" __declspec(dllexport) int getImageDataAsByteArrayAlpha(const char* imagePath, unsigned char** data, int64_t* dataSize) {    
    int width, height, channels;
    *data = stbi_load(imagePath, &width, &height, &channels, STBI_rgb_alpha);
    if (*data == NULL) {
        return 1; // Indica erro
    }    

    *dataSize = width * height * 4; //channels
    return 0;
    stbi_image_free(data);
}