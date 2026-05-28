#pragma once

#include <GLECore/pch.hpp>
#include <GLEInterface/rendering/IMesh.hpp>

namespace gle::backend::primitive {
    inline std::shared_ptr<IMesh> Block() {
        static auto mesh = [] {
            auto m = std::make_shared<IMesh>();

            m->vertices = {{{-1, -1, 1}, {0, 0}, {0, 0, 1}},   {{1, -1, 1}, {1, 0}, {0, 0, 1}},
                           {{1, 1, 1}, {1, 1}, {0, 0, 1}},     {{-1, 1, 1}, {0, 1}, {0, 0, 1}},

                           {{1, -1, -1}, {0, 0}, {0, 0, -1}},  {{-1, -1, -1}, {1, 0}, {0, 0, -1}},
                           {{-1, 1, -1}, {1, 1}, {0, 0, -1}},  {{1, 1, -1}, {0, 1}, {0, 0, -1}},

                           {{-1, -1, -1}, {0, 0}, {-1, 0, 0}}, {{-1, -1, 1}, {1, 0}, {-1, 0, 0}},
                           {{-1, 1, 1}, {1, 1}, {-1, 0, 0}},   {{-1, 1, -1}, {0, 1}, {-1, 0, 0}},

                           {{1, -1, 1}, {0, 0}, {1, 0, 0}},    {{1, -1, -1}, {1, 0}, {1, 0, 0}},
                           {{1, 1, -1}, {1, 1}, {1, 0, 0}},    {{1, 1, 1}, {0, 1}, {1, 0, 0}},

                           {{-1, 1, 1}, {0, 0}, {0, 1, 0}},    {{1, 1, 1}, {1, 0}, {0, 1, 0}},
                           {{1, 1, -1}, {1, 1}, {0, 1, 0}},    {{-1, 1, -1}, {0, 1}, {0, 1, 0}},

                           {{-1, -1, -1}, {0, 0}, {0, -1, 0}}, {{1, -1, -1}, {1, 0}, {0, -1, 0}},
                           {{1, -1, 1}, {1, 1}, {0, -1, 0}},   {{-1, -1, 1}, {0, 1}, {0, -1, 0}}};

            m->indices = {0,  1,  2,  0,  2,  3,  4,  5,  6,  4,  6,  7,  8,  9,  10, 8,  10, 11,
                          12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23};

            return m;
        }();

        return mesh;
    }

    inline std::shared_ptr<IMesh> Pyramid() {
        static auto mesh = [] {
            auto m = std::make_shared<IMesh>();

            m->vertices = {{{-1, -1, -1}, {0, 0}, {0, -1, 0}},
                           {{1, -1, -1}, {1, 0}, {0, -1, 0}},
                           {{1, -1, 1}, {1, 1}, {0, -1, 0}},
                           {{-1, -1, 1}, {0, 1}, {0, -1, 0}},

                           {{0, 1, 0}, {0.5f, 1.0f}, {0, 1, 0}}};

            m->indices = {0, 1, 2, 0, 2, 3,

                          0, 4, 1, 1, 4, 2, 2, 4, 3, 3, 4, 0};

            return m;
        }();

        return mesh;
    }

    inline std::shared_ptr<IMesh> Diamond() {
        static auto mesh = [] {
            auto m = std::make_shared<IMesh>();

            m->vertices = {{{0, 1, 0}, {0, 0}, {0, 1, 0}}, {{0, -1, 0}, {0, 0}, {0, -1, 0}},

                           {{1, 0, 0}, {0, 0}, {1, 0, 0}}, {{-1, 0, 0}, {0, 0}, {-1, 0, 0}},
                           {{0, 0, 1}, {0, 0}, {0, 0, 1}}, {{0, 0, -1}, {0, 0}, {0, 0, -1}}};

            m->indices = {0, 2, 4, 0, 4, 3, 0, 3, 5, 0, 5, 2,

                          1, 4, 2, 1, 3, 4, 1, 5, 3, 1, 2, 5};

            return m;
        }();

        return mesh;
    }

    inline std::shared_ptr<IMesh> Wedge() {
        static auto mesh = [] {
            auto m = std::make_shared<IMesh>();

            m->vertices = {{{-1, -1, -1}, {0, 0}, {0, -1, 0}},
                           {{1, -1, -1}, {1, 0}, {0, -1, 0}},
                           {{1, -1, 1}, {1, 1}, {0, -1, 0}},
                           {{-1, -1, 1}, {0, 1}, {0, -1, 0}},

                           {{-1, 1, 1}, {0.5f, 1.0f}, {0, 1, 0}}};

            m->indices = {0, 1, 2, 0, 2, 3,

                          0, 4, 3, 1, 2, 4,

                          3, 2, 4, 0, 1, 4};

            return m;
        }();

        return mesh;
    }

    inline std::shared_ptr<IMesh> CornerWedge() {
        static auto mesh = [] {
            auto m = std::make_shared<IMesh>();

            m->vertices = {{{-1, -1, -1}, {0, 0}, {0, -1, 0}},
                           {{1, -1, -1}, {1, 0}, {0, -1, 0}},
                           {{1, -1, 1}, {1, 1}, {0, -1, 0}},
                           {{-1, -1, 1}, {0, 1}, {0, -1, 0}},

                           {{-1, 1, 1}, {0.5f, 1.0f}, {0, 1, 0}}};

            m->indices = {0, 1, 2, 0, 2, 3,

                          3, 2, 4, 0, 3, 4,

                          1, 4, 2, 0, 1, 4};

            return m;
        }();

        return mesh;
    }

    inline std::shared_ptr<IMesh> Sphere(uint32_t lod) {
        static std::unordered_map<uint32_t, std::shared_ptr<IMesh>> cache;

        lod = std::max(3u, lod);

        if (auto it = cache.find(lod); it != cache.end())
            return it->second;

        auto mesh = std::make_shared<IMesh>();

        const uint32_t stacks = lod;
        const uint32_t slices = lod * 2;

        for (uint32_t y = 0; y <= stacks; ++y) {
            float v = static_cast<float>(y) / stacks;
            float phi = v * static_cast<float>(M_PI);

            for (uint32_t x = 0; x <= slices; ++x) {
                float u = static_cast<float>(x) / slices;
                float theta = u * static_cast<float>(M_PI * 2.0);

                float sx = std::sin(phi) * std::cos(theta);
                float sy = std::cos(phi);
                float sz = std::sin(phi) * std::sin(theta);

                mesh->vertices.push_back({{sx, sy, sz}, {u, v}, {sx, sy, sz}});
            }
        }

        for (uint32_t y = 0; y < stacks; ++y) {
            for (uint32_t x = 0; x < slices; ++x) {
                uint32_t a = y * (slices + 1) + x;
                uint32_t b = a + slices + 1;
                uint32_t c = a + 1;
                uint32_t d = b + 1;

                mesh->indices.insert(mesh->indices.end(), {a, b, c, c, b, d});
            }
        }

        cache[lod] = mesh;
        return mesh;
    }

    inline std::shared_ptr<IMesh> HalfSphere(uint32_t lod) {
        static std::unordered_map<uint32_t, std::shared_ptr<IMesh>> cache;

        lod = std::max(3u, lod);

        if (auto it = cache.find(lod); it != cache.end())
            return it->second;

        auto mesh = std::make_shared<IMesh>();

        const uint32_t stacks = lod;
        const uint32_t slices = lod * 2;

        for (uint32_t y = 0; y <= stacks; ++y) {
            float v = static_cast<float>(y) / stacks;
            float phi = v * static_cast<float>(M_PI * 0.5);

            for (uint32_t x = 0; x <= slices; ++x) {
                float u = static_cast<float>(x) / slices;
                float theta = u * static_cast<float>(M_PI * 2.0);

                float sx = std::sin(phi) * std::cos(theta);
                float sy = std::cos(phi);
                float sz = std::sin(phi) * std::sin(theta);

                mesh->vertices.push_back({{sx, sy, sz}, {u, v}, {sx, sy, sz}});
            }
        }

        for (uint32_t y = 0; y < stacks; ++y) {
            for (uint32_t x = 0; x < slices; ++x) {
                uint32_t a = y * (slices + 1) + x;
                uint32_t b = a + slices + 1;
                uint32_t c = a + 1;
                uint32_t d = b + 1;

                mesh->indices.insert(mesh->indices.end(), {a, b, c, c, b, d});
            }
        }

        uint32_t centerIndex = static_cast<uint32_t>(mesh->vertices.size());

        mesh->vertices.push_back({{0, 0, 0}, {0.5f, 0.5f}, {0, -1, 0}});

        uint32_t ringStart = stacks * (slices + 1);

        for (uint32_t i = 0; i < slices; ++i) {
            mesh->indices.insert(mesh->indices.end(), {centerIndex, ringStart + i + 1, ringStart + i});
        }

        cache[lod] = mesh;
        return mesh;
    }

    inline std::shared_ptr<IMesh> Cylinder(uint32_t lod) {
        static std::unordered_map<uint32_t, std::shared_ptr<IMesh>> cache;

        lod = std::max(3u, lod);

        if (auto it = cache.find(lod); it != cache.end())
            return it->second;

        auto mesh = std::make_shared<IMesh>();

        const float halfHeight = 1.0f;

        for (uint32_t i = 0; i <= lod; ++i) {
            float u = static_cast<float>(i) / lod;
            float angle = u * static_cast<float>(M_PI * 2.0);

            float x = std::cos(angle);
            float z = std::sin(angle);

            mesh->vertices.push_back({{x, -halfHeight, z}, {u, 1}, {x, 0, z}});

            mesh->vertices.push_back({{x, halfHeight, z}, {u, 0}, {x, 0, z}});
        }

        for (uint32_t i = 0; i < lod; ++i) {
            uint32_t a = i * 2;
            uint32_t b = a + 1;
            uint32_t c = a + 2;
            uint32_t d = a + 3;

            mesh->indices.insert(mesh->indices.end(), {a, b, c, c, b, d});
        }

        uint32_t topCenter = static_cast<uint32_t>(mesh->vertices.size());

        mesh->vertices.push_back({{0, halfHeight, 0}, {0.5f, 0.5f}, {0, 1, 0}});

        uint32_t bottomCenter = static_cast<uint32_t>(mesh->vertices.size());

        mesh->vertices.push_back({{0, -halfHeight, 0}, {0.5f, 0.5f}, {0, -1, 0}});

        uint32_t ringVertexCount = (lod + 1) * 2;

        for (uint32_t i = 0; i < lod; ++i) {
            uint32_t topA = i * 2 + 1;
            uint32_t topB = ((i + 1) * 2 + 1);

            mesh->indices.insert(mesh->indices.end(), {topCenter, topA, topB});

            uint32_t botA = i * 2;
            uint32_t botB = ((i + 1) * 2);

            mesh->indices.insert(mesh->indices.end(), {bottomCenter, botB, botA});
        }

        cache[lod] = mesh;
        return mesh;
    }

    inline std::shared_ptr<IMesh> Sphere() {
        return Sphere(16);
    }

    inline std::shared_ptr<IMesh> HalfSphere() {
        return HalfSphere(16);
    }

    inline std::shared_ptr<IMesh> Cylinder() {
        return Cylinder(16);
    }
} // namespace gle::backend::primitive