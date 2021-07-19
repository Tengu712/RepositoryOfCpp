#include "include/Models.hpp"

bool ModelSquare::init(D3DManager* pManager) {

    const unsigned int kNumVtx = 4U;
    const unsigned int kNumIdx = 6U;
    inf.numIdx = kNumIdx;

    struct Vertex dataPCNU[kNumVtx] = {
        {-100.0f, -100.0f, +0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f},
        {-100.0f, +100.0f, +0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f},
        {+100.0f, +100.0f, +0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f},
        {+100.0f, -100.0f, +0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f},
    };
    unsigned int dataIdx[kNumIdx] = {0, 1, 2, 0, 2, 3};

    return pManager->createModelBuffers(kNumVtx, dataPCNU, dataIdx, &inf);
}
