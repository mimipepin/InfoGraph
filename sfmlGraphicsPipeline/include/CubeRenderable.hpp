#ifndef CUBE_RENDERABLE_HPP
#define CUBE_RENDERABLE_HPP

#include "Renderable.hpp"
#include <vector>
#include <glm/glm.hpp>

class CubeRenderable : public Renderable
{
    public:
        ~CubeRenderable();
        CubeRenderable( ShaderProgramPtr program ); // smart pointer to the shader program used to render the Renderable

    private:
        void do_draw();

        std::vector< glm::vec3 > m_positions;   // vector of vertex positions that describe the object, on the CPU
        unsigned int m_vBuffer; // identifier of the vertex position buffer on the GPU that stores the positions.

        std::vector< glm::vec4 > m_colors;
        unsigned int m_cBuffer;

        glm::mat4 m_model;  // model matrix to place the object in world space
};

typedef std::shared_ptr<CubeRenderable> CubeRenderablePtr;

#endif
