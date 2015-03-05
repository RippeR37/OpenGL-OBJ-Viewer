#include "Grid.h"

namespace Model {

    Grid::Grid() : Grid(glm::ivec2(0), glm::ivec2(10)) {
        
    }

    Grid::Grid(const glm::ivec2& min, const glm::ivec2& max) {
        _program.load(
            GL::Shader("assets/shaders/grid.vp", GL::Shader::Type::VertexShader),
            GL::Shader("assets/shaders/grid.fp", GL::Shader::Type::FragmentShader)
        );

        setMin(min);
        setMax(max);
    }

    void Grid::build() {
        std::vector<glm::vec2> vertices;

        vertices.push_back(glm::vec2( 0,  1));
        vertices.push_back(glm::vec2( 1,  0));

        vertices.push_back(glm::vec2( 0,  1));
        vertices.push_back(glm::vec2(-1,  0));

        vertices.push_back(glm::vec2( 0, -1));
        vertices.push_back(glm::vec2( 1,  0));

        vertices.push_back(glm::vec2( 0, -1));
        vertices.push_back(glm::vec2(-1,  0));

        for(int y = getMin().y; y <= getMax().y; ++y) {
            vertices.push_back(glm::vec2(getMin().x, y));
            vertices.push_back(glm::vec2(getMax().x, y));
        }

        for(int x = getMin().x; x <= getMax().x; ++x) {
            vertices.push_back(glm::vec2(x, getMin().y));
            vertices.push_back(glm::vec2(x, getMax().y));
        }

        _vbo.bind();
            _vbo.setData(vertices);
        _vbo.unbind();

        _vao.bind();
            _vbo.bind();
                _vao.enableAttrib(0);
                _vao.setAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
            _vbo.unbind();
        _vao.unbind();

        _vao.setDrawCount(vertices.size());
        _vao.setDrawTarget(GL::VertexArray::DrawTarget::Lines);
    }

    void Grid::render(const GL::Pipeline& pipeline) {
        _program.use();
        _program["matrixMVP"].setMatrix(pipeline.getMVP());

            _vao.bind();
            _vao.drawArrays();
            _vao.unbind();

        _program.unbind();
    }

    void Grid::setMin(const glm::ivec2& min) {
        _min = min;
    }

    void Grid::setMax(const glm::ivec2& max) {
        _max = max;
    }

    const glm::ivec2& Grid::getMin() const {
        return _min;
    }

    const glm::ivec2& Grid::getMax() const {
        return _max;
    }

}