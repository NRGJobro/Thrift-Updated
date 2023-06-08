#include "HookSwapChain.h"

#include "../../../Category/Module/Module.h"

#include "../../../Manager.h"
#include "../../../../Client.h"
#include "ImGui/imgui.h"
#include "ImGui/Font/Mojangles.hpp"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx12.h"

Manager* scMgr = nullptr;
bool initContext = false;
enum SwapChain_DeviceType { INVALID_DEVICE_TYPE, D3D11, D3D12 };

typedef HRESULT(__thiscall* PresentD3D12)(IDXGISwapChain3*, UINT, UINT);
PresentD3D12 oPresentD3D12;

struct FrameContext {

    ID3D12CommandAllocator* commandAllocator = nullptr;
    ID3D12Resource* main_render_target_resource = nullptr;
    D3D12_CPU_DESCRIPTOR_HANDLE main_render_target_descriptor;

};

UINT buffersCounts = -1;
FrameContext* frameContext = nullptr;

ID3D12CommandQueue* d3d12CommandQueue = nullptr;

ID3D12DescriptorHeap* d3d12DescriptorHeapImGuiRender = nullptr;
ID3D12DescriptorHeap* d3d12DescriptorHeapBackBuffers = nullptr;
ID3D12GraphicsCommandList* d3d12CommandList = nullptr;
ID3D12CommandAllocator* allocator = nullptr;

auto hookPresentD3D12(IDXGISwapChain3* ppSwapChain, UINT syncInterval, UINT flags) -> HRESULT {

    auto deviceType = SwapChain_DeviceType::INVALID_DEVICE_TYPE;

    ID3D11Device* d3d11Device = nullptr;
    ID3D12Device* d3d12Device = nullptr;

    auto window = (HWND)FindWindowA(nullptr, (LPCSTR)"Minecraft");

    auto callRender = [&]() {
        if (scMgr != nullptr) {
            for (auto category : scMgr->categories) {
                for (auto mod : category->modules) {
                    if (mod->isEnabled) mod->onImGuiRender();
                };
            };
        };
    };

    if (SUCCEEDED(ppSwapChain->GetDevice(IID_PPV_ARGS(&d3d11Device)))) {
        deviceType = SwapChain_DeviceType::D3D11;
    } else if (SUCCEEDED(ppSwapChain->GetDevice(IID_PPV_ARGS(&d3d12Device)))) {
        deviceType = SwapChain_DeviceType::D3D12;
    };

    if (deviceType == SwapChain_DeviceType::INVALID_DEVICE_TYPE)
        goto out;

    if (deviceType == SwapChain_DeviceType::D3D11) {
        if (!initContext) {
            ImGui::CreateContext();
            auto& io = ImGui::GetIO();
            io.Fonts->AddFontFromMemoryCompressedTTF(mojangles_compressed_data, mojangles_compressed_size, 22);
            io.Fonts->Build();
            initContext = true;
        }

        ID3D11DeviceContext* ppContext = nullptr;
        d3d11Device->GetImmediateContext(&ppContext);

        ID3D11Texture2D* pBackBuffer;
        ppSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&pBackBuffer));

        ID3D11RenderTargetView* mainRenderTargetView;
        d3d11Device->CreateRenderTargetView(pBackBuffer, nullptr, &mainRenderTargetView);
        pBackBuffer->Release();

        ImGui_ImplWin32_Init(window);
        ImGui_ImplDX11_Init(d3d11Device, ppContext);

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        callRender();

        ImGui::EndFrame();
        ImGui::Render();

        ppContext->OMSetRenderTargets(1, &mainRenderTargetView, nullptr);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        // D2D Rendering
        {
            // Create the D2D factory
            ID2D1Factory* factory = nullptr;
            D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

            // Set up the D2D render target using the back buffer
            IDXGISurface* dxgiBackbuffer;
            ppSwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackbuffer));
            ID2D1RenderTarget* d2dRenderTarget;
            D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
                D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)
            );
            factory->CreateDxgiSurfaceRenderTarget(dxgiBackbuffer, props, &d2dRenderTarget);
            dxgiBackbuffer->Release();

            // Create the DWrite factory
            IDWriteFactory1* writeFactory;
            DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), reinterpret_cast<IUnknown**>(&writeFactory));

            // Create the DWrite text format
            IDWriteTextFormat* textFormat;
            writeFactory->CreateTextFormat(L"Arial", nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20, L"", &textFormat);

            // Create a brush
            ID2D1SolidColorBrush* blueBrush;
            d2dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &blueBrush);

            // Draw the text
            d2dRenderTarget->BeginDraw();
            const WCHAR* text = L"This is a D2D test from NRG lol";
            d2dRenderTarget->DrawText(text, wcslen(text), textFormat, D2D1::RectF(0, 0, 800, 600), blueBrush);
            d2dRenderTarget->EndDraw();

            // Release resources
            blueBrush->Release();
            textFormat->Release();
            writeFactory->Release();
            d2dRenderTarget->Release();
            factory->Release();
        }

        mainRenderTargetView->Release();
        d3d11Device->Release();
    }
    else if (deviceType == SwapChain_DeviceType::D3D12) {
        if (!initContext) {
            static_cast<ID3D12Device5*>(d3d12Device)->RemoveDevice();
            return oPresentD3D12(ppSwapChain, syncInterval, flags);
        }
    }

    goto out;

out:
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