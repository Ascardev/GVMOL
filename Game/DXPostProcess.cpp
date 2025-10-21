#include "sinbaram\\sinlinkheader.h"

DXPostProcess::DXPostProcess()
{
	bPostProcess = TRUE;
	bPostProcessInitialized = FALSE;
	lpRenderEffect = NULL;
	lpRenderSprite = NULL;
	lpRenderTexture = NULL;
	lpRenderSurface = NULL;
	lpBackBuffer = NULL;
	hr = NULL;
}

DXPostProcess::~DXPostProcess()
{
}

void DXPostProcess::PostProcessON(EPostEffects eTechnique)
{
	bPostProcess = TRUE;
}

void DXPostProcess::SetPostProcessFloat(const char* pszVariable, const float fValue)
{
	if (bPostProcess && bPostProcessInitialized)
		if (lpRenderEffect)
			lpRenderEffect->SetFloat(pszVariable, fValue);
}

void DXPostProcess::PostProcess3D()
{
	if (bPostProcess && bPostProcessInitialized)
	{
		if (lpRenderEffect && lpRenderSprite)
		{
			//Set Dynamic Shader variables

			lpRenderEffect->SetFloat("Time", 1.0f);
			lpRenderEffect->SetFloat("DeadIntensity", fDeadIntensity);
			if (lpCurPlayer->MotionInfo && lpCurPlayer->MotionInfo->State && lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_DEAD)
			{
				fDeadIntensity += 0.007f;
				if (fDeadIntensity >= 1.0f)
					fDeadIntensity = 1.0f;
			}
			else
			{
				fDeadIntensity = 0;
			}

			//Begin Post Process Shader Pass
			UINT uPasses = 0;
			lpRenderEffect->Begin(&uPasses, D3DXFX_DONOTSAVESAMPLERSTATE);
			lpRenderSprite->Begin(0);
			lpRenderEffect->BeginPass(0);
			lpRenderSprite->Draw(lpRenderTexture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
			lpRenderEffect->EndPass();
			lpRenderSprite->End();
			lpRenderEffect->End();
		}
	}
}

BOOL DXPostProcess::CreatePostProcessBuffers()
{
	bPostProcessInitialized = FALSE;

	//Render Target
	if (FAILED(hr = d3ddev->CreateTexture(d3dpp.BackBufferWidth, d3dpp.BackBufferHeight, 1, D3DUSAGE_RENDERTARGET, d3dpp.BackBufferFormat, D3DPOOL_DEFAULT, &lpRenderTexture, NULL)))
		return TRUE;

	if (FAILED(hr = lpRenderTexture->GetSurfaceLevel(0, &lpRenderSurface)))
		return TRUE;

	bPostProcessInitialized = TRUE;

	return TRUE;
}

BOOL DXPostProcess::CreatePostProcess()
{
	LPD3DXBUFFER lpD3DErrorBuffer = NULL;

	if (FAILED(hr = D3DXCreateEffectFromFile(d3ddev, "game\\script\\shaders\\PostProcess.fx", NULL, NULL, 0, NULL, &lpRenderEffect, &lpD3DErrorBuffer)))
	{
		ExitProcess(0);
		if (lpD3DErrorBuffer)
			lpD3DErrorBuffer->Release();
		return TRUE;
	}

	if (!CreatePostProcessBuffers())
		return TRUE;

	bPostProcessInitialized = FALSE;

	if (FAILED(hr = D3DXCreateSprite(d3ddev, &lpRenderSprite)))
		return TRUE;

	bPostProcessInitialized = TRUE;

	return TRUE;
}

void DXPostProcess::OnBegin3D()
{
	if (bPostProcess && bPostProcessInitialized)
	{
		if (lpRenderSurface)
		{
			d3ddev->GetRenderTarget(0, &lpBackBuffer);
			d3ddev->SetRenderTarget(0, lpRenderSurface);
			d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
		}
	}
}

void DXPostProcess::OnEnd3D()
{
	if (bPostProcess && bPostProcessInitialized)
	{
		if (lpBackBuffer)
		{
			d3ddev->SetRenderTarget(0, lpBackBuffer);
			if (lpBackBuffer)
				lpBackBuffer->Release();
		}
	}

	PostProcessON(POSTPROCESSID_Dead);
	PostProcess3D();
}

void DXPostProcess::OnResetDevice()
{
	CreatePostProcessBuffers();

	if (lpRenderSprite && lpRenderSprite != NULL && *(DWORD*)lpRenderSprite > 0x100000)
		lpRenderSprite->OnResetDevice();
	if (lpRenderEffect && lpRenderEffect != NULL && *(DWORD*)lpRenderEffect > 0x100000)
		lpRenderEffect->OnResetDevice();
}

void DXPostProcess::OnLostDevice()
{
	bPostProcessInitialized = FALSE;
	if (lpRenderTexture && lpRenderTexture != NULL && *(DWORD*)lpRenderTexture > 0x100000)//(lpRenderTexture)
		lpRenderTexture->Release();
	if (lpRenderSurface && lpRenderSurface != NULL && *(DWORD*)lpRenderSurface > 0x100000)//(lpRenderSurface)
		lpRenderSurface->Release();
	if (lpBackBuffer && lpBackBuffer != NULL && *(DWORD*)lpBackBuffer > 0x100000)
		lpBackBuffer->Release();
	//Objects
	if (lpRenderSprite && lpRenderSprite != NULL && *(DWORD*)lpRenderSprite > 0x100000)
		lpRenderSprite->OnLostDevice();
	if (lpRenderEffect && lpRenderEffect != NULL && *(DWORD*)lpRenderEffect > 0x100000)
		lpRenderEffect->OnLostDevice();
}

BOOL DXPostProcess::Init()
{
	if (!CreatePostProcess())
	{
		return FALSE;
	}
	return TRUE;
}