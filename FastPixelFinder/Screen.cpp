#include "Screen.h"

Screen::Screen()
{
    Init();
}

void Screen::Init()
{
    D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_VIDEO_SUPPORT, 0, 0,
        D3D11_SDK_VERSION, &device, 0, &context);

    if (device == NULL)
    {
        return;
    }

    device->QueryInterface(&dxgiDevice);

    dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
    dxgiAdapter->EnumOutputs(0, &dxgiOutput);
    dxgiOutput->GetDesc(&outputDesc);
    dxgiOutput->QueryInterface(__uuidof(IDXGIOutput1), reinterpret_cast<void**>(&dxgiOutput1));
    dxgiOutput1->DuplicateOutput(device, &deskDupl);
    deskDupl->GetDesc(&outputDuplDesc);

    desc.Width = outputDuplDesc.ModeDesc.Width;
    desc.Height = outputDuplDesc.ModeDesc.Height;
    desc.Format = outputDuplDesc.ModeDesc.Format;
    desc.ArraySize = 1;
    desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET;
    desc.MiscFlags = D3D11_RESOURCE_MISC_GDI_COMPATIBLE;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.MipLevels = 1;
    desc.CPUAccessFlags = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;

    device->CreateTexture2D(&desc, NULL, &gdiImage);

    desc.Width = outputDuplDesc.ModeDesc.Width;
    desc.Height = outputDuplDesc.ModeDesc.Height;
    desc.Format = outputDuplDesc.ModeDesc.Format;
    desc.ArraySize = 1;
    desc.BindFlags = 0;
    desc.MiscFlags = 0;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.MipLevels = 1;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
    desc.Usage = D3D11_USAGE_STAGING;

    device->CreateTexture2D(&desc, NULL, &destImage);
}

BYTE* Screen::GetPixelBuffer()
{
    deskDupl->AcquireNextFrame(0, &frameInfo, &desktopResource);
    desktopResource->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&aquiredDesktopImage));

    if (aquiredDesktopImage == NULL)
    {
        return NULL;
    }

    context->CopyResource(gdiImage, aquiredDesktopImage);
    gdiImage->QueryInterface(&dxgiSurface1);
    context->CopyResource(destImage, gdiImage);
    context->Map(destImage, 0, D3D11_MAP_READ_WRITE, 0, &resource);

    deskDupl->ReleaseFrame();

    return reinterpret_cast<BYTE*>(resource.pData);
}