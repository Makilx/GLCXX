#pragma once

#include <GLEInterface/rendering/IMesh.hpp>

namespace gle::PrimitiveMesh {
    const backend::IMesh &Block();
    const backend::IMesh &Plane();
    const backend::IMesh &Sphere();
    const backend::IMesh &Cylinder();
    const backend::IMesh &Cone();
    const backend::IMesh &Wedge();
    const backend::IMesh &CornerWedge();
    const backend::IMesh &Pyramid();
    const backend::IMesh &Diamond();
} // namespace gle::PrimitiveMesh