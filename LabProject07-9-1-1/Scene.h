//-----------------------------------------------------------------------------
// File: Scene.h
//-----------------------------------------------------------------------------

#pragma once

#include "Shader.h"
#include "Player.h"

#define MAX_LIGHTS			16 

#define POINT_LIGHT			1
#define SPOT_LIGHT			2
#define DIRECTIONAL_LIGHT	3

struct LIGHT
{
	XMFLOAT4				m_xmf4Ambient;
	XMFLOAT4				m_xmf4Diffuse;
	XMFLOAT4				m_xmf4Specular;
	XMFLOAT3				m_xmf3Position;
	float 					m_fFalloff;
	XMFLOAT3				m_xmf3Direction;
	float 					m_fTheta; //cos(m_fTheta)
	XMFLOAT3				m_xmf3Attenuation;
	float					m_fPhi; //cos(m_fPhi)
	bool					m_bEnable;
	int						m_nType;
	float					m_fRange;
	float					padding;
};

struct LIGHTS
{
	LIGHT					m_pLights[MAX_LIGHTS];
	XMFLOAT4				m_xmf4GlobalAmbient;
	int						m_nLights;
};

class CScene
{
public:
	CScene();
	~CScene();

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void ReleaseShaderVariables();

	void BuildDefaultLightsAndMaterials();
	void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	void ReleaseObjects();

	ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);
	ID3D12RootSignature* GetGraphicsRootSignature() { return(m_pd3dGraphicsRootSignature); }

	bool ProcessInput(UCHAR* pKeysBuffer);
	void AnimateObjects(float fTimeElapsed);
	void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera = NULL);

	void CheckObjectByWallCollision();

	void ReleaseUploadBuffers();

	void Particles(XMFLOAT3 pos, int nParticles);
	void Missiles(XMFLOAT3 position, int apachobjects,XMFLOAT3 ObjectLookVector);


	CPlayer* m_pPlayer = NULL;

public:
	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;

	CGameObject** m_ppGameObjects = NULL;
	int							m_nGameObjects = 0;
	CParticleObject  ** m_ppGameParticleObjects = NULL;
	int							m_nGameParticleObjects = 0;
	CRotatingObject		**m_pprotateGameObject = NULL;

	CMissileObject ** m_ppGameMissileObjects = NULL;
	int					m_nGameMissileObjects = 4;
	LIGHT* m_pLights = NULL;
	int							m_nLights = 0;

	XMFLOAT4					m_xmf4GlobalAmbient;

	ID3D12Resource* m_pd3dcbLights = NULL;
	LIGHTS* m_pcbMappedLights = NULL;

	CGameObject* m_pParticleModel = NULL;
	CGameObject* m_pMissileObject = NULL;

	float						m_fElapsedTime = 0.0f;
	
	bool				m_bMissileon = false;
	bool				m_bGameOver = false;
	float				m_fRestartCounter = 0.0f;

	CObjectsShader* m_pShaders = NULL;
	int m_nShaders = 0;

protected:
	CHeightMapTerrain* m_pTerrain = NULL;
public:
	CHeightMapTerrain* GetTerrain() { return(m_pTerrain); }

};
