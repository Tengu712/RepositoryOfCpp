#include "include/HeaderDX11.hpp"

bool D3DManager::createModelBuffers(unsigned int numVtx, Vertex* dataPCU, unsigned int* dataIdx, ModelInf* minf) {
    D3D11_BUFFER_DESC descVBuffer = {
        sizeof(Vertex) * numVtx, D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0U, 0U, 0U};
    D3D11_SUBRESOURCE_DATA dataVBuffer = {dataPCU, 0U, 0U};
    if (FAILED(inf.pDevice->CreateBuffer(&descVBuffer, &dataVBuffer, minf->pVBuffer.GetAddressOf())))
        return false;

    D3D11_BUFFER_DESC descIndex = {
        (unsigned int)sizeof(unsigned int) * minf->numIdx, D3D11_USAGE_DEFAULT, D3D11_BIND_INDEX_BUFFER, 0U, 0U, 0U};
    D3D11_SUBRESOURCE_DATA dataIndex = {dataIdx, 0U, 0U};
    if (FAILED(inf.pDevice->CreateBuffer(&descIndex, &dataIndex, minf->pIBuffer.GetAddressOf())))
        return false;

    bool isCompleted = true;
    isCompleted &= minf->pVBuffer != nullptr;
    isCompleted &= minf->pIBuffer != nullptr;

    return isCompleted;
}

void D3DManager::drawModel(ModelInf* minf) {
    unsigned int strides = sizeof(Vertex);
    unsigned int offsets = 0U;
    inf.pImContext->IASetVertexBuffers(0U, 1U, minf->pVBuffer.GetAddressOf(), &strides, &offsets);
    inf.pImContext->IASetIndexBuffer(minf->pIBuffer.Get(), DXGI_FORMAT_R32_UINT, 0U);

    ConstantBuffer cbuffer;
    DirectX::XMStoreFloat4x4(
        &cbuffer.matScl, DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(minf->sclX, minf->sclY, minf->sclZ)));
    DirectX::XMStoreFloat4x4(&cbuffer.matRot,
        DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationRollPitchYaw(DirectX::XMConvertToRadians(minf->degX),
            DirectX::XMConvertToRadians(minf->degY), DirectX::XMConvertToRadians(minf->degZ))));
    DirectX::XMStoreFloat4x4(
        &cbuffer.matTrs, DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(minf->posX, minf->posY, minf->posZ)));
    DirectX::XMStoreFloat4x4(&cbuffer.matView, DirectX::XMMatrixTranspose(inf.matView));
    DirectX::XMStoreFloat4x4(&cbuffer.matProj, DirectX::XMMatrixTranspose(inf.matProj));
    DirectX::XMStoreFloat4(&cbuffer.vecColor, DirectX::XMVectorSet(minf->colR, minf->colG, minf->colB, minf->colA));
    DirectX::XMStoreFloat4(&cbuffer.vecLight, inf.vecLight);
    inf.pImContext->UpdateSubresource(inf.pCBuffer.Get(), 0U, nullptr, &cbuffer, 0U, 0U);
    inf.pImContext->VSSetConstantBuffers(0U, 1U, inf.pCBuffer.GetAddressOf());

    if (minf->pTexture != nullptr)
        inf.pImContext->PSSetShaderResources(0U, 1U, minf->pTexture->pSRView.GetAddressOf());

    inf.pImContext->DrawIndexed(minf->numIdx, 0U, 0U);
}
