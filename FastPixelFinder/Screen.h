#include "d3d11.h"
#include "dxgi1_2.h"

class Screen
{
public:
    ID3D11Device* device;
    ID3D11DeviceContext* context;
    IDXGIOutputDuplication* deskDupl;
    ID3D11Texture2D* gdiImage;
    ID3D11Texture2D* destImage;
    ID3D11Texture2D* aquiredDesktopImage;
    DXGI_OUTDUPL_DESC outputDuplDesc = {};
    IDXGIDevice* dxgiDevice;
    IDXGIAdapter* dxgiAdapter;
    IDXGIOutput* dxgiOutput;
    IDXGIOutput1* dxgiOutput1;
    IDXGIResource* desktopResource;
    IDXGISurface1* dxgiSurface1;
    DXGI_OUTPUT_DESC outputDesc;
    D3D11_MAPPED_SUBRESOURCE resource;
    DXGI_OUTDUPL_FRAME_INFO frameInfo;
    D3D11_TEXTURE2D_DESC desc = {};
    Screen();
    void Init();
    BYTE* GetPixelBuffer();
};