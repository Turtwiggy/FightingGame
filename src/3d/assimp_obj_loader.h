#pragma once

#include "graphics/shader.h"
#include "graphics/texture.h"

//#include "assimp/"
#include "glm/glm.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

namespace fightinggame {

    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
        glm::vec3 Tangent;
        glm::vec3 Bitangent;
    };

    class Mesh {
    public:
        // mesh data
        std::vector<Vertex>         vertices;
        std::vector<unsigned int>   indices;
        std::vector<Ref<texture2D>> textures;

        Mesh
        (
            std::vector<Vertex> vertices,
            std::vector<unsigned int> indices,
            std::vector<Ref<texture2D>> textures
        );
        void Draw(Shader& shader);
        void setupMesh();

    private:
        //  render data
        unsigned int VAO, VBO, EBO;
    };

    class Model
    {
    public:
        Model(std::string path) //e.g. 'C:/model.obj'
        {
            loadModel(path);
        }
        void Draw(Shader& shader);
    private:

        void loadModel(std::string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);

        std::vector<Ref<texture2D>> loadMaterialTextures
        (
            aiMaterial* mat,
            aiTextureType type,
            std::string typeName
        );

    private:
        std::vector<Mesh> meshes;
        std::vector<Ref<texture2D>> textures_loaded;
        std::string directory;
    };
}
