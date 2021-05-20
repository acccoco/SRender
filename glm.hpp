
#ifndef SRENDER_GLM_HPP
#define SRENDER_GLM_HPP

#include <eigen3/Eigen/Eigen>

/* 获得 view 矩阵 */
Eigen::Matrix4f lookat(const Eigen::Vector3f &eye, const Eigen::Vector3f &target, const Eigen::Vector3f &up) {
    // todo
    return Eigen::Matrix4f();
}


/* 获得 projection 矩阵 */
Eigen::Matrix4f projection(int width, int height, float near, float far) {
    // todo
    return Eigen::Matrix4f();
}


#endif //SRENDER_GLM_HPP
