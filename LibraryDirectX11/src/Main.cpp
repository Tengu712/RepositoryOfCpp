#include "../directx/include/HeaderDX11.hpp"
#include "include/Models.hpp"
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "mydx.lib")

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPInst, LPSTR pCmd, int cmdShow) {
    LPCWSTR kNameWnd = L"Test DX11";
    LPCWSTR kNameWndClass = L"DX11_CLASS";
    const unsigned int kWidth = 1920U;
    const unsigned int kHeight = 1080U;
    const bool kWindowed = MessageBoxW(nullptr, L"フルスクリーンで起動しますか", L"確認", MB_YESNO) == IDNO;

    HWND hWnd = nullptr;
    D3DManager dmgr = D3DManager();
    if (!dmgr.init(hInst, cmdShow, kNameWnd, kNameWndClass, kWidth, kHeight, kWindowed, &hWnd))
        return 1;

    Camera camera = Camera();
    dmgr.createCamera((float)kWidth, (float)kHeight, &camera);
    camera.posZ = -500.0f;

    Texture tex = Texture();
    if (!dmgr.createTexture(0, &tex))
        return 1;

    Model* square = new ModelSquare();
    if (!square->init(&dmgr))
        return 1;
    square->setTexture(&tex);

    MSG msg;
    while (true) {
        if (PeekMessageW(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        } else {
            square->inf.degX++;
            dmgr.applyCamera(&camera);
            dmgr.drawBegin();
            dmgr.drawModel(square->getInf());
            dmgr.drawEnd();
        }
    }

    delete square;

    UnregisterClassW(kNameWndClass, hInst);
    return 0;
}