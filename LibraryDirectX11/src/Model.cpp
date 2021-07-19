#include "include/Models.hpp"

Model::Model() {
    inf = {0U, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, nullptr, nullptr, nullptr};
}

void Model::setTexture(Texture* pTexture) {
    inf.pTexture = pTexture;
}

ModelInf* Model::getInf() {
    return &inf;
}
