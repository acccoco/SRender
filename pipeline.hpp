
#ifndef SRENDER_PIPELINE_HPP
#define SRENDER_PIPELINE_HPP

#include <vector>
#include <tuple>
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>

/* 顶点着色器的输入内容 */
class VertexPayload {
public:


};

/* 片段着色器的输入内容 */
class FragmentPayload {
public:
    Eigen::Vector4f position;

private:
};


/* 顶点着色器 */
class VertexShader {
public:
    /* 主要直线 MVP 变换 */
    FragmentPayload run(const VertexPayload &in) {
        // todo
    }
};


/* 片段着色器 */
class FragmentShader {
public:
    /* 计算某个像素的颜色值 */
    Eigen::Vector4f run(const FragmentPayload &in) {
        // todo
    }
};


/* 图元类型：三角形 */
class Triangle {
public:
    FragmentPayload A;
    FragmentPayload B;
    FragmentPayload C;
};

/* 渲染器 */
class Render {
public:
    Render() = default;

    void set_shader(VertexShader _vs, FragmentShader _fs) {
        vs = _vs;
        fs = _fs;
    }

    /* 以 index 形式传递的三角形 */
    void
    draw_triangle(const std::vector<VertexPayload> &_vertices, const std::vector<std::array<size_t, 3>> &_indices) {

    }

    /* 以顺序形式传递的三角形 */
    void draw_triangle() {}


private:
    VertexShader vs;
    FragmentShader fs;
    std::vector<std::array<size_t, 3>> indices;
    std::vector<VertexPayload> vertices;
    std::vector<FragmentPayload> frags;
    std::vector<std::vector<Eigen::Vector4f>> window;

private:
    void run() {

        /* 每个顶点对应一个 fs_in */
        std::vector<FragmentPayload> vertices_out;

        /* 逐顶点运行 VS */
        for (const auto &in: vertices) {
            auto out = vs.run(in);

            /* 透视除法 */
            out.position /= out.position.w();
            vertices_out.push_back(out);
        }

        /* 图元装配 */
        std::vector<Triangle> primitives;
        primitives = primitive_assembly_triangle(vertices_out, indices);

        /* 逐三角形进行光栅化 */
        for (const auto &triangle: primitives) {
            auto frags_in_triangle = rasterize(triangle.A, triangle.B, triangle.C);
            frags.insert(frags.end(), frags_in_triangle.begin(), frags_in_triangle.end());
        }

        /* 逐片段运行 FS */
        for (const auto &frag: frags) {
            auto pixel = fs.run(frag);
            window[frag.position.x()][frag.position.y()] = pixel;
        }
    }
    /* 计算三角形的包围盒 */
    std::tuple<float, float, float, float>
    boundary_box(const Eigen::Vector2f &A, const Eigen::Vector2f &B, const Eigen::Vector2f &C) {

    }

    /* 三角形图元装配 */
    std::vector<Triangle>
    primitive_assembly_triangle(const std::vector<FragmentPayload> &_vertices,
                                const std::vector<std::array<size_t, 3>> &_indices) {

    }

    /* 三角形的光栅化 */
    std::vector<FragmentPayload>
    rasterize(const FragmentPayload &A, const FragmentPayload &B, const FragmentPayload &C) {
        std::vector<FragmentPayload> fs_ins;

        /* 三角形的包围盒 */
        auto[min_x, min_y, max_x, max_y] = boundary_box(A.position.head(2), B.position.head(2), C.position.head(2));
        for (int x = min_x; x <= max_x; ++x) {
            for (int y = min_y; y <= max_y; ++y) {
                /* 插值参数 */
                auto[alpha, beta, gamma] = barycentric(A.position.head(2), B.position.head(2), C.position.head(2),
                                                       Eigen::Vector2f(x, y));

                /* 进行插值 */
                auto fs_in = interp(A, B, C, alpha, beta, gamma);
                fs_ins.push_back(fs_in);
            }
        }

        return fs_ins;
    }

    /* 重心坐标插值 */
    static std::tuple<float, float, float>
    barycentric(const Eigen::Vector2f &A, const Eigen::Vector2f &B, const Eigen::Vector2f &C,
                const Eigen::Vector2f &P) {
        // todo
        return {0.33f, 0.33f, 0.34f};
    }

    /* 对 payload 进行插值 */
    FragmentPayload
    interp(const FragmentPayload &A, const FragmentPayload &B, const FragmentPayload &C, float alpha, float beta,
           float gamma) {
        /* 对各个属性进行插值，并透视校正 */
        // todo
    }

};

#endif //SRENDER_PIPELINE_HPP
