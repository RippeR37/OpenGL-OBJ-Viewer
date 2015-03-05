#ifndef MODELS_GRID_H_INCUDED
#define MODELS_GRID_H_INCUDED

#include <Utils/GL+/Pipeline.h>
#include <Utils/GL+/Program.h>
#include <Utils/GL+/VertexArray.h>
#include <Utils/GL+/VertexBuffer.h>

namespace Model {

    class Grid {
        public:
            Grid();
            Grid(const glm::ivec2& min, const glm::ivec2& max);

            void build();
            void render(const GL::Pipeline& pipeline);

            void setMin(const glm::ivec2& min);
            void setMax(const glm::ivec2& max);

            const glm::ivec2& getMin() const;
            const glm::ivec2& getMax() const;

        private:
            glm::ivec2 _min;
            glm::ivec2 _max;

            GL::Program _program;
            GL::VertexArray _vao;
            GL::VertexBuffer _vbo;
    };

}

#endif