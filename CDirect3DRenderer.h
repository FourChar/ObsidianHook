#pragma once

typedef long					(__stdcall* tEndScene)						( IDirect3DDevice9 *pDevice );
long __stdcall					hkEndScene									( IDirect3DDevice9 *pDevice );
extern tEndScene				oEndScene;

extern void						( *oSwapChain_Present )						( );
void							hkSwapChain_Present							( );

struct Vertex
{
    float X;
	float Y;
	float Z;
    DWORD Diffuse;
};

class CDirect3DRenderer
{
public:
	void							InitiateDirect3D						( );
	void							InitiateDirect3DObjects					( );

	void							Direct3DPreRenderThread					( );
	void							Direct3DRenderThread					( );

	IDirect3DDevice9		*&		GetRenderDevice							( );
	void							SetRenderDevice							( IDirect3DDevice9 *pDevice );

	D3DVIEWPORT9			&		GetViewPort								( );
	void							SetViewPort								( D3DVIEWPORT9 pViewPort );

	CDirect3DHooks					Hooks;
	CTextWriter						TextWriter;
	CShapeDrawer					ShapeDrawer;
	CESPDrawer						ESPDrawer;

	DWORD					*		VTable;

private:
	IDirect3DDevice9		*		RenderDevice;
	D3DVIEWPORT9					pViewport;
};

extern CDirect3DRenderer			D3DRenderer;