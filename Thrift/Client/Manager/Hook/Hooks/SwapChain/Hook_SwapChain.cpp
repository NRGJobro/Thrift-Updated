#include "HookSwapChain.h"

#include "../../../Category/Module/Module.h"

#include "../../../Manager.h"
#include "../../../../Client.h"

Manager* scMgr = nullptr;


enum DirectXDeviceType {
    UnknownVersion = 0,
    Dx11 = 1,
    Dx12 = 2,
};

using Microsoft::WRL::ComPtr;

ComPtr<ID3D12CommandQueue> d3d12CommandQueue;

typedef HRESULT(__thiscall* PresentD3D12)(IDXGISwapChain3*, UINT, UINT);
PresentD3D12 oPresentD3D12;

auto hookPresentD3D12(IDXGISwapChain3* ppSwapChain, UINT syncInterval, UINT flags) -> HRESULT {

    auto window = (HWND)FindWindowA(nullptr, (LPCSTR)"Minecraft");

    ComPtr<ID3D12Device> d3d12Device;
    ComPtr<ID3D11Device> d3d11Device;

    if (SUCCEEDED(ppSwapChain->GetDevice(IID_PPV_ARGS(&d3d12Device)))) {

        ComPtr<ID3D11DeviceContext> ppContext;
        ComPtr<ID2D1Factory3> d2dFactory;
        ComPtr<ID3D11On12Device> d3d11On12Device;
        
        if (d3d12CommandQueue != nullptr) {

            HRESULT hr;

            hr = D3D11On12CreateDevice(d3d12Device.Get(), flags, nullptr, 0, (IUnknown**)(d3d12CommandQueue.GetAddressOf()), 1, 0, &d3d11Device, &ppContext, nullptr);

            if (FAILED(hr)) {

                Utils::debugOutput("Failed to create D3D11 on D3D12 Device!");
                goto end;

            };

            hr = d3d11Device.As(&d3d11On12Device);

            if (FAILED(hr)) {

                Utils::debugOutput("Failed to query ID3D11On12Device");
                goto end;

            };

            D2D1_FACTORY_OPTIONS options;
            options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;

            hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory3), &options, &d2dFactory);

            if (FAILED(hr)) {

                Utils::debugOutput("Failed to create ID2D1Factory3");
                goto end;

            };

            ComPtr<IDXGIDevice> dxgiDevice;
            hr = d3d11On12Device.As(&dxgiDevice);

            if (FAILED(hr)) {

                Utils::debugOutput("Failed to query IDXGIDevice");
                goto end;

            };

            ComPtr<ID2D1Device2> D2DDevice;
            hr = d2dFactory->CreateDevice(dxgiDevice.Get(), &D2DDevice);

            if (FAILED(hr)) {

                Utils::debugOutput("Failed to create ID2D1Device2");
                goto end;

            };

            Utils::debugOutput("!!");

        };

    };

end:
    return oPresentD3D12(ppSwapChain, syncInterval, flags);

};

typedef void(__thiscall* ExecuteCommandListsD3D12)(ID3D12CommandQueue*, UINT, ID3D12CommandList*);
ExecuteCommandListsD3D12 oExecuteCommandListsD3D12;

auto hookExecuteCommandListsD3D12(ID3D12CommandQueue* queue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists) -> void {
    if (!d3d12CommandQueue)
        d3d12CommandQueue = queue;

    oExecuteCommandListsD3D12(queue, NumCommandLists, ppCommandLists);
};

auto Hook_SwapChain::init(void) -> StatusData {

	scMgr = this->mgr;

    if (kiero::init(kiero::RenderType::D3D12) != kiero::Status::Success)
        return StatusData(MethodStatus::Error, "[Kiero] Failed to initialize!");

    if (kiero::bind(140, (void**)&oPresentD3D12, hookPresentD3D12) != kiero::Status::Success)
        return StatusData(MethodStatus::Error, "[Kiero Present D3D12 Hook] Failed to hook!");

    if (kiero::bind(54, (void**)&oExecuteCommandListsD3D12, hookExecuteCommandListsD3D12) != kiero::Status::Success)
        return StatusData(MethodStatus::Error, "[Kiero ExecuteCommandLists D3D12 Hook] Failed to hook!");

    return StatusData(MethodStatus::Error, "[Kiero] Successfully hooked methods!");

};