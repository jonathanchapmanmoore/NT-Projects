//------------------------------------------------------------------------------
// File: PlaneScene.cpp
//
// Desc: DirectShow sample code - implementation of the CPlaneScene class
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "util.h"
#include "PlaneScene.h"

#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlaneScene::CPlaneScene()
{
    m_vertices[0].position = CUSTOMVERTEX::Position(-1.0f,  1.0f, 0.0f); // top left
    m_vertices[1].position = CUSTOMVERTEX::Position(-1.0f, -1.0f, 0.0f); // bottom left
    m_vertices[2].position = CUSTOMVERTEX::Position( 1.0f,  1.0f, 0.0f); // top right
    m_vertices[3].position = CUSTOMVERTEX::Position( 1.0f, -1.0f, 0.0f); // bottom right

    // set up diffusion:
    m_vertices[0].color = 0xffffffff;
    m_vertices[1].color = 0xff0000ff;
    m_vertices[2].color = 0xffffffff;
    m_vertices[3].color = 0xff0000ff;

    // set up texture coordinates
    m_vertices[0].tu = 0.0f; m_vertices[0].tv = 0.0f; // low left
    m_vertices[1].tu = 0.0f; m_vertices[1].tv = 1.0f; // high left
    m_vertices[2].tu = 1.0f; m_vertices[2].tv = 0.0f; // low right
    m_vertices[3].tu = 1.0f; m_vertices[3].tv = 1.0f; // high right
}

CPlaneScene::~CPlaneScene()
{

}

HRESULT 
CPlaneScene::Init(IDirect3DDevice9* d3ddev)
{
    HRESULT hr;

    if( ! d3ddev )
        return E_POINTER;

    FAIL_RET(hr = d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE));
    FAIL_RET(hr = d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE));
    FAIL_RET(hr = d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE));
    FAIL_RET(hr = d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA));
    FAIL_RET(hr = d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA));
    FAIL_RET(hr = d3ddev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE));
    FAIL_RET(hr = d3ddev->SetRenderState(D3DRS_ALPHAREF, 0x10));
    FAIL_RET(hr = d3ddev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER));

    FAIL_RET(hr = d3ddev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP));
    FAIL_RET(hr = d3ddev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP));
    FAIL_RET(hr = d3ddev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR));
    FAIL_RET(hr = d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR));
    FAIL_RET(hr = d3ddev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR));

    m_vertexBuffer = NULL;

    d3ddev->CreateVertexBuffer(sizeof(m_vertices),D3DUSAGE_WRITEONLY,D3DFVF_CUSTOMVERTEX,D3DPOOL_MANAGED,& m_vertexBuffer, NULL );

    SmartPtr<IDirect3DSurface9> backBuffer;
    FAIL_RET( d3ddev->GetBackBuffer( 0, 0,
                                    D3DBACKBUFFER_TYPE_MONO,
                                    & backBuffer ) );

    D3DSURFACE_DESC backBufferDesc;
    backBuffer->GetDesc( & backBufferDesc );

    // Set the projection matrix
    D3DXMATRIX matProj;
    FLOAT fAspect = backBufferDesc.Width / 
                    (float)backBufferDesc.Height;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, fAspect, 
                                1.0f, 100.0f );
    FAIL_RET( d3ddev->SetTransform( D3DTS_PROJECTION, &matProj ) );

    
    D3DXVECTOR3 from( 1.0f, 1.0f, -3.0f );
    D3DXVECTOR3 at( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 up( 0.0f, 1.0f, 0.0f );

    D3DXMATRIX matView;
    D3DXMatrixLookAtLH( &matView, & from, & at, & up);
    FAIL_RET( d3ddev->SetTransform( D3DTS_VIEW, &matView ) );

    m_time = GetTickCount();

    return hr;
}


HRESULT 
CPlaneScene::DrawScene( IDirect3DDevice9* d3ddev,
                        IDirect3DTexture9* texture ) 
{
    HRESULT hr;

    if( !( d3ddev && texture ) )
    {
        return E_POINTER;
    }

    if( m_vertexBuffer == NULL )
    {
        return D3DERR_INVALIDCALL;
    }

    // get the difference in time
    DWORD dwCurrentTime;
    dwCurrentTime = GetTickCount();
    double difference = m_time - dwCurrentTime ;
    
    // figure out the rotation of the plane
    float x = (float) ( -cos(difference / 2000.0 ) ) ;
    float y = (float) ( cos(difference / 2000.0 ) ) ;
    float z = (float) ( sin(difference / 2000.0 ) ) ;

    // update the two rotating vertices with the new position
    m_vertices[0].position = CUSTOMVERTEX::Position(x,  y, z);   // top left
    m_vertices[3].position = CUSTOMVERTEX::Position(-x, -y, -z); // bottom right

    // Adjust the color so the blue is always on the bottom.
    // As the corner approaches the bottom, get rid of all the other
    // colors besides blue
    DWORD mask0 = (DWORD) (255 * ( ( y + 1.0  )/ 2.0 ));
    DWORD mask3 = (DWORD) (255 * ( ( -y + 1.0  )/ 2.0 ));
    m_vertices[0].color = 0xff0000ff | ( mask0 << 16 ) | ( mask0 << 8 );
    m_vertices[3].color = 0xff0000ff | ( mask3 << 16 ) | ( mask3 << 8 );

    // write the new vertex information into the buffer
    void* pData;
    FAIL_RET( m_vertexBuffer->Lock(0,sizeof(pData), &pData,0) );
    memcpy(pData,m_vertices,sizeof(m_vertices));                            
    FAIL_RET( m_vertexBuffer->Unlock() );  

    // clear the scene so we don't have any articats left
    d3ddev->Clear( 0L, NULL, D3DCLEAR_TARGET, 
                   D3DCOLOR_XRGB(255,255,255), 1.0f, 0L );

    FAIL_RET( d3ddev->BeginScene() );
    FAIL_RET( d3ddev->SetTexture( 0, texture));

    FAIL_RET(hr = d3ddev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE));
    FAIL_RET(hr = d3ddev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE));
    FAIL_RET(hr = d3ddev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE));
    FAIL_RET(hr = d3ddev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE));

    FAIL_RET( d3ddev->SetStreamSource(0, m_vertexBuffer, 0, sizeof(CPlaneScene::CUSTOMVERTEX)  ) );            //set next source ( NEW )
    FAIL_RET( d3ddev->SetFVF( D3DFVF_CUSTOMVERTEX ) );
    FAIL_RET( d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2) );  //draw quad 
    FAIL_RET( d3ddev->SetTexture( 0, NULL));
    FAIL_RET( d3ddev->EndScene());

    return hr;
}

void
CPlaneScene::SetSrcRect( float fTU, float fTV )
{
    m_vertices[0].tu = 0.0f; m_vertices[0].tv = 0.0f; // low left
    m_vertices[1].tu = 0.0f; m_vertices[1].tv = fTV;  // high left
    m_vertices[2].tu = fTU;  m_vertices[2].tv = 0.0f; // low right
    m_vertices[3].tu = fTU;  m_vertices[3].tv = fTV;  // high right
}