
#include "pipeline.hpp"
#include "glm.hpp"

#include <iostream>

class DiffuseVS : public VertexShader {
public:
    Eigen::Matrix4f view_matrix;
    Eigen::Matrix4f model_matrix;
    Eigen::Matrix4f projection_matrix;
};

class DiffuseFS : public FragmentShader {
public:

};

int main() {
    Render render;

    Eigen::Vector3f eye;
    Eigen::Vector3f target;
    Eigen::Vector3f up;

    DiffuseVS vs;
    DiffuseFS fs;

    render.set_shader(vs, fs);
    vs.view_matrix = lookat(eye, target, up);
    vs.model_matrix = Eigen::Matrix4f::Identity();
    vs.projection_matrix = projection(800, 800, 0.01, 50);

    std::vector<VertexPayload> vertices;
    std::vector<std::array<size_t, 3>> indices;

    render.draw_triangle(vertices, indices);
}
