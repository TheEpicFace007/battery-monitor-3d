/**
 * @file material.hpp
 * @brief Defines the Material-class
 */
#ifndef MATERIAL_H
#define MATERIAL_H

#pragma once
#include <citro3d.h>
#include "color.hpp"

namespace m3d {
    /**
     * @brief A material that can be applied to meshes
     */
    class Material {
    public:
        /**
         * @brief Default constructor
         */
        Material();

        /**
         * @brief Initializes the material with a C3D_Material
         * @param t_material The material to initialize from
         */
        Material(C3D_Material t_material);

        /**
         * @brief Copy constructor
         * @param t_source Material to copy
         */
        Material(const m3d::Material& t_source);

        /**
         * @brief Destructs the material
         */
        virtual ~Material();

        /**
         * @brief Sets the material with C3D_Material
         * @param t_material The material to copy
         */
        void setMaterial(C3D_Material t_material);

        /**
         * @brief Returns the C3D_Material of this material
         * @return The C3D_Material
         */
        C3D_Material* getMaterial() const;

        /**
         * @brief Sets the ambient-color of the material
         * @param t_color The ambient-color
         */
        void setAmbient(m3d::Color t_color);

        /**
         * @brief Sets the ambient-color of the material
         * @param t_r The red component
         * @param t_g The green component
         * @param t_b The blue component
         */
        void setAmbient(int t_r, int t_g, int t_b);

        /**
         * @brief Returns the ambient-color of the material
         * @return The ambient-color
         */
        m3d::Color getAmbient();

        /**
         * @brief Sets the diffuse-color of the material
         * @param t_color The diffuse-color
         */
        void setDiffuse(m3d::Color t_color);

        /**
         * @brief Sets the diffuse-color of the material
         * @param t_r The red component
         * @param t_g The green component
         * @param t_b The blue component
         */
        void setDiffuse(int t_r, int t_g, int t_b);

        /**
         * @brief Returns the diffuse-color of the material
         * @return The diffuse-color
         */
        m3d::Color getDiffuse();

        /**
         * @brief Sets the specular0-color of the material
         * @param t_color The specular0-color
         */
        void setSpecular0(m3d::Color t_color);

        /**
         * @brief Sets the specular0-color of the material
         * @param t_r The red component
         * @param t_g The green component
         * @param t_b The blue component
         */
        void setSpecular0(int t_r, int t_g, int t_b);

        /**
         * @brief Returns the specular0-color of the material
         * @return The specular0-color
         */
        m3d::Color getSpecular0();

        /**
         * @brief Sets the specular1-color of the material
         * @param t_color The specular1-color
         */
        void setSpecular1(m3d::Color t_color);

        /**
         * @brief Sets the specular1-color of the material
         * @param t_r The red component
         * @param t_g The green component
         * @param t_b The blue component
         */
        void setSpecular1(int t_r, int t_g, int t_b);

        /**
         * @brief Returns the specular1-color of the material
         * @return The specular1-color
         */
        m3d::Color getSpecular1();

        /**
         * @brief Sets the emission-color of the material
         * @param t_color The emission-color
         */
        void setEmission(m3d::Color t_color);

        /**
         * @brief Sets the emission-color of the material
         * @param t_r The red component
         * @param t_g The green component
         * @param t_b The blue component
         */
        void setEmission(int t_r, int t_g, int t_b);

        /**
         * @brief Returns the emission-color of the material
         * @return The emission-color
         */
        m3d::Color getEmission();

        /**
         * @brief Overloads the assignment operator
         * @param  rhs The material to copy
         * @return     A reference to this material
         */
        m3d::Material& operator=(const m3d::Material& rhs);

    private:
        void updateMaterial();

        /* data */
        m3d::Color m_ambient, m_diffuse, m_specular0, m_specular1, m_emission;
        C3D_Material* m_material;
    };
} /* m3d */


#endif /* end of include guard: MATERIAL_H */
