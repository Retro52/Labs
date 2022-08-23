#ifndef MODEL_H
#define MODEL_H

#define GLEW_STATIC
#include "../OpenGL/include/GLEW/glew.h"

#include "../OpenGL/include/glm/glm.hpp"
#include "../OpenGL/include/glm/gtc/matrix_transform.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.h"
#include "../Core/Actor.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

class Model : public Actor
{
public:
    explicit Model(const std::string &path, bool gamma = false);

    /**
     * Draws all model meshes
     * @param shader shader to use for drawing
     */
    void Draw(Shader &shader);

    /**
     * Loads textures from file
     * @param path path to the original model file
     * @param directory of the file
     * @param gamma
     * @return id of the loaded texture
     */
    static unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

private:
    /**
     * Loads model
     * @param path path to the model
     */
    void LoadModel(std::string const &path);

    /**
     * Recursively checks all sub nodes
     * @param node current node
     * @param scene current scene
     */
    void ProcessNode(aiNode *node, const aiScene *scene);
    /**
     *
     * @param mesh
     * @param scene
     * @return new Mesh
     */
    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);

    /**
     * Loads all model textures
     * @param mat material
     * @param type type of the texture
     * @param typeName name of the texture type
     * @return vector of loaded textures
     */
    std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);

    /**
     * Updates model every frame
     */
    void Update() override;

public:
    bool gammaCorrection;
    std::string directory;
    std::vector<Mesh> meshes;
    std::vector<Texture> textures_loaded;
};
#endif
