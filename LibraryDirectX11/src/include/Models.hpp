#pragma once
#ifndef _Models_HPP_
#define _Models_HPP_

#include "../../directx/include/HeaderDX11.hpp"

class Model {
public:
    ModelInf inf;
    Model();
    void setTexture(Texture* pTexture);
    ModelInf* getInf();
    virtual bool init(D3DManager* pManager) = 0;
};

class ModelSquare : public Model {
public:
    bool init(D3DManager* pManager);
};

class ModelCube : public Model {
public:
    bool init(D3DManager* pManager);
};

#endif