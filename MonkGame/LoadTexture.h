#include <d3d11.h>
#pragma once
bool LoadTextureFromFile(ID3D11Device* g_pd3dDevice, const char* path, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);