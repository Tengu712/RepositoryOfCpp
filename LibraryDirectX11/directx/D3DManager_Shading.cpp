#include "include/HeaderDX11.hpp"

void D3DManager::createCamera(float width, float height, Camera* camera){
    *camera = {width, height, DirectX::XM_PIDIV4, 1.0f, 2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
}

void D3DManager::applyCamera(Camera* camera) {
    inf.matView = DirectX::XMMatrixLookToLH(DirectX::XMVectorSet(camera->posX, camera->posY, camera->posZ, 0.0f),
        DirectX::XMVectorSet(camera->dirX, camera->dirY, camera->dirZ, 0.0f),
        DirectX::XMVectorSet(camera->uppX, camera->uppY, camera->uppZ, 0.0f));
    inf.matProj = DirectX::XMMatrixPerspectiveFovLH(
        camera->angle, (float)camera->width / (float)camera->height, camera->nearZ, camera->farZ);
}
