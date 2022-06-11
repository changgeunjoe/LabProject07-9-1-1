//-----------------------------------------------------------------------------
// File: CScene.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Scene.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::BuildDefaultLightsAndMaterials()
{
	m_nLights = 4;
	m_pLights = new LIGHT[m_nLights];
	::ZeroMemory(m_pLights, sizeof(LIGHT) * m_nLights);

	m_xmf4GlobalAmbient = XMFLOAT4(0.15f, 0.15f, 0.15f, 1.0f);

	m_pLights[0].m_bEnable = true;
	m_pLights[0].m_nType = POINT_LIGHT;
	m_pLights[0].m_fRange = 1000.0f;
	m_pLights[0].m_xmf4Ambient = XMFLOAT4(0.1f, 0.0f, 0.0f, 1.0f);
	m_pLights[0].m_xmf4Diffuse = XMFLOAT4(0.8f, 0.0f, 0.0f, 1.0f);
	m_pLights[0].m_xmf4Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 0.0f);
	m_pLights[0].m_xmf3Position = XMFLOAT3(30.0f, 30.0f, 30.0f);
	m_pLights[0].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_pLights[0].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.001f, 0.0001f);
	m_pLights[1].m_bEnable = true;
	m_pLights[1].m_nType = SPOT_LIGHT;
	m_pLights[1].m_fRange = 500.0f;
	m_pLights[1].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights[1].m_xmf4Diffuse = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
	m_pLights[1].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	m_pLights[1].m_xmf3Position = XMFLOAT3(-50.0f, 20.0f, -5.0f);
	m_pLights[1].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_pLights[1].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights[1].m_fFalloff = 8.0f;
	m_pLights[1].m_fPhi = (float)cos(XMConvertToRadians(40.0f));
	m_pLights[1].m_fTheta = (float)cos(XMConvertToRadians(20.0f));
	m_pLights[2].m_bEnable = true;
	m_pLights[2].m_nType = DIRECTIONAL_LIGHT;
	m_pLights[2].m_xmf4Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_pLights[2].m_xmf4Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_pLights[2].m_xmf4Specular = XMFLOAT4(0.4f, 0.4f, 0.4f, 0.0f);
	m_pLights[2].m_xmf3Direction = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_pLights[3].m_bEnable = true;
	m_pLights[3].m_nType = SPOT_LIGHT;
	m_pLights[3].m_fRange = 600.0f;
	m_pLights[3].m_xmf4Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_pLights[3].m_xmf4Diffuse = XMFLOAT4(0.3f, 0.7f, 0.0f, 1.0f);
	m_pLights[3].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	m_pLights[3].m_xmf3Position = XMFLOAT3(50.0f, 30.0f, 30.0f);
	m_pLights[3].m_xmf3Direction = XMFLOAT3(0.0f, 1.0f, 1.0f);
	m_pLights[3].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights[3].m_fFalloff = 8.0f;
	m_pLights[3].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights[3].m_fTheta = (float)cos(XMConvertToRadians(30.0f));
}

void CScene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);

	CMaterial::PrepareShaders(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);

	BuildDefaultLightsAndMaterials();

	m_nGameObjects = 1;
	m_ppGameObjects = new CGameObject * [m_nGameObjects];
	m_pParticleModel= CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/TREE.bin");
	CGameObject* pApacheModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/TREE.bin");
	m_nGameParticleObjects =20;
	//pApacheModel->m_pMesh->Set_xmBoundingBox()
	//pApacheModel->SetOOBB(CMesh);
	CApacheObject* pApacheObject = NULL;
	pApacheObject = new CApacheObject();
	pApacheObject->SetChild(pApacheModel, true);

	pApacheObject->OnInitialize();
	pApacheObject->SetPosition(-100.0f, 0.0f, -200.0f - 50);
	pApacheObject->SetScale(5.0f, 5.0f, 5.0f);
	pApacheObject->Rotate(0.0f, 90.0f, 0.0f);
	m_ppGameObjects[0] = pApacheObject;
	CreateShaderVariables(pd3dDevice, pd3dCommandList);

	// 지형을 확대할 스케일 벡터이다.x - 축과 z - 축은 8배, y - 축은 2배 확대한다.
	XMFLOAT3 xmf3Scale(8.0f, 2.0f, 8.0f);
	XMFLOAT4 xmf4Color(0.0f, 0.2f, 0.0f, 0.0f);
	//지형을 높이 맵 이미지 파일(HeightMap.raw)을 사용하여 생성한다. 높이 맵의 크기는 가로x세로(257x257)이다. 
#ifdef _WITH_TERRAIN_PARTITION
	/*하나의 격자 메쉬의 크기는 가로x세로(17x17)이다. 지형 전체는 가로 방향으로 16개, 세로 방향으로 16의 격자 메
	쉬를 가진다. 지형을 구성하는 격자 메쉬의 개수는 총 256(16x16)개가 된다.*/
	m_pTerrain = new CHeightMapTerrain(pd3dDevice, pd3dCommandList,
		m_pd3dGraphicsRootSignature, _T("Model/HeightMap.raw"), 257, 257, 17,
		17, xmf3Scale, xmf4Color);
#else
//지형을 하나의 격자 메쉬(257x257)로 생성한다. 
	m_pTerrain = new CHeightMapTerrain(pd3dDevice, pd3dCommandList, 
	m_pd3dGraphicsRootSignature, _T("Model/HeightMap.raw"), 257, 257, 257,
	257, xmf3Scale, xmf4Color);
#endif
	//m_nShaders = 1;
	//m_pShaders = new CObjectsShader[m_nShaders];
	//m_pShaders[0].CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	//m_pShaders[0].BuildObjects(pd3dDevice, pd3dCommandList, m_pTerrain);

}

void CScene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();

	if (m_ppGameObjects)
	{
		for (int i = 0; i < m_nGameObjects; i++) if (m_ppGameObjects[i]) m_ppGameObjects[i]->Release();
		delete[] m_ppGameObjects;
	}
	if (m_ppGameParticleObjects)
	{
		for (int i = 0; i < m_nGameParticleObjects; i++) if (m_ppGameParticleObjects[i]) m_ppGameParticleObjects[i]->Release();
		delete[] m_ppGameParticleObjects;
	}

	ReleaseShaderVariables();
	/*for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i].ReleaseShaderVariables();
		m_pShaders[i].ReleaseObjects();
	}*/
	if (m_pShaders) delete[] m_pShaders;

	if (m_pLights) delete[] m_pLights;

	if (m_pTerrain) delete m_pTerrain;
}

ID3D12RootSignature* CScene::CreateGraphicsRootSignature(ID3D12Device* pd3dDevice)
{
	ID3D12RootSignature* pd3dGraphicsRootSignature = NULL;

	D3D12_ROOT_PARAMETER pd3dRootParameters[3];

	pd3dRootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[0].Descriptor.ShaderRegister = 1; //Camera
	pd3dRootParameters[0].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[1].Constants.Num32BitValues = 32;
	pd3dRootParameters[1].Constants.ShaderRegister = 2; //GameObject
	pd3dRootParameters[1].Constants.RegisterSpace = 0;
	pd3dRootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[2].Descriptor.ShaderRegister = 4; //Lights
	pd3dRootParameters[2].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	

	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS | D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS | D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = 0;
	d3dRootSignatureDesc.pStaticSamplers = NULL;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;

	ID3DBlob* pd3dSignatureBlob = NULL;
	ID3DBlob* pd3dErrorBlob = NULL;
	D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pd3dSignatureBlob, &pd3dErrorBlob);
	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(), pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void**)&pd3dGraphicsRootSignature);
	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();

	return(pd3dGraphicsRootSignature);
}

void CScene::CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(LIGHTS) + 255) & ~255); //256의 배수
	m_pd3dcbLights = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbLights->Map(0, NULL, (void**)&m_pcbMappedLights);
}

void CScene::UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList)
{
	::memcpy(m_pcbMappedLights->m_pLights, m_pLights, sizeof(LIGHT) * m_nLights);
	::memcpy(&m_pcbMappedLights->m_xmf4GlobalAmbient, &m_xmf4GlobalAmbient, sizeof(XMFLOAT4));
	::memcpy(&m_pcbMappedLights->m_nLights, &m_nLights, sizeof(int));
}

void CScene::ReleaseShaderVariables()
{
	if (m_pd3dcbLights)
	{
		m_pd3dcbLights->Unmap(0, NULL);
		m_pd3dcbLights->Release();
	}
}

void CScene::ReleaseUploadBuffers()
{
	for (int i = 0; i < m_nGameObjects; i++) m_ppGameObjects[i]->ReleaseUploadBuffers();
	if (m_pTerrain) m_pTerrain->ReleaseUploadBuffers();
	//for (int i = 0; i < m_nShaders; i++) m_pShaders[i].ReleaseUploadBuffers();
	//for (int i = 0; i < m_nGameParticleObjects; i++) m_ppGameParticleObjects[i]->ReleaseUploadBuffers();
}

bool CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'W': m_ppGameObjects[0]->MoveForward(+1.0f); break;
		case 'S': m_ppGameObjects[0]->MoveForward(-1.0f); break;
		case 'A': m_ppGameObjects[0]->MoveStrafe(-1.0f); break;
		case 'D': m_ppGameObjects[0]->MoveStrafe(+1.0f); break;
		case 'Q': m_ppGameObjects[0]->MoveUp(+1.0f); break;
		case 'R': m_ppGameObjects[0]->MoveUp(-1.0f); break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return(false);
}

bool CScene::ProcessInput(UCHAR* pKeysBuffer)
{
	return(false);
}

void CScene::AnimateObjects(float fTimeElapsed)
{
	m_fElapsedTime = fTimeElapsed;

	if (m_bGameOver) {
		m_pPlayer->Sleep();
		m_fRestartCounter += fTimeElapsed;
		if (m_fRestartCounter > 2)
		{
			m_fRestartCounter = 0.0f;
			m_bGameOver = false;
			m_pPlayer->Awake();
			m_pPlayer->Reset();
		}
	}
		//for (int i = 60; i < 65; i++)
		//{
		//	if (m_ppGameObjects[i]->GetPosition().z < -40.0f)
		//	{
		//		m_ppGameObjects[i]->SetPositionZ(RANDOM_NUM(400, 700));
		//	}
		//	m_ppGameObjects[i]->MoveForward(-0.2f);
		//	//m_ppGameObjects[i]->m_xmOOBB = BoundingOrientedBox(m_ppGameObjects[i]->GetPosition(), m_ppGameObjects[i]->m_xmOOBB.Extents, XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
		//}
	/*	for (int i = 60; i < m_nGameObjects; i++) m_ppGameObjects[i]->Animate(fTimeElapsed, NULL);*/
		/*for (int i = 0; i < m_nGameParticleObjects; i++)
		{
			if (m_ppGameParticleObjects[i]->IsActive())
			{
			}
		}*/

		m_pPlayer->Animate(fTimeElapsed, NULL);
		if (m_pLights)
		{
			m_pLights[1].m_xmf3Position = m_pPlayer->GetPosition();
			m_pLights[1].m_xmf3Direction = m_pPlayer->GetLookVector();
			//m_ppGameObjects[0]->SetPositionZ( m_pPlayer->GetPosition().z);


		}
		CheckObjectByWallCollision();
	
}

void CScene::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pCamera->UpdateShaderVariables(pd3dCommandList);

	UpdateShaderVariables(pd3dCommandList);

	D3D12_GPU_VIRTUAL_ADDRESS d3dcbLightsGpuVirtualAddress = m_pd3dcbLights->GetGPUVirtualAddress();
	pd3dCommandList->SetGraphicsRootConstantBufferView(2, d3dcbLightsGpuVirtualAddress); //Lights

	for (int i = 0; i < m_nGameObjects; i++)
	{
		if (m_ppGameObjects[i])
		{
			m_ppGameObjects[i]->Animate(m_fElapsedTime, NULL);
			m_ppGameObjects[i]->UpdateTransform(NULL);
			m_ppGameObjects[i]->Render(pd3dCommandList, pCamera);
		}
	}
	/*for (int i = 0; i < m_nGameParticleObjects; i++)
	{
		if (m_ppGameParticleObjects[i]&& m_bGameOver)
		{
			m_ppGameParticleObjects[i]->Animate(m_fElapsedTime, NULL);
			m_ppGameParticleObjects[i]->UpdateTransform(NULL);
			m_ppGameParticleObjects[i]->Render(pd3dCommandList, pCamera);
		}
	}*/
	if (m_pTerrain) m_pTerrain->Render(pd3dCommandList, pCamera);
	/*for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i].Render(pd3dCommandList, pCamera);
	}*/
}

void CScene::CheckObjectByWallCollision()
{
	//for (int i = 0; i < m_nGameObjects; i++)
	//{
	//	BoundingOrientedBox wmPlayerOOBB = m_pPlayer->m_xmOOBB;
	//	ContainmentType containType = m_ppGameObjects[i]->m_xmOOBB.Contains(wmPlayerOOBB);
	//	
	//	if (m_ppGameObjects[i]->m_xmOOBB.Intersects(wmPlayerOOBB))
	//	{
	//		XMFLOAT3 CameraPosition= m_pPlayer->GetCamera()->GetPosition();
	//		m_bGameOver=true;
	//		//m_pPlayer->Release();
	//	for (int i = 0; i < m_nGameParticleObjects; i++)
	//	{
	//		m_ppGameParticleObjects[i]->SetMovingSpeed(20.0f);
	//		m_ppGameParticleObjects[i]->SetPosition(m_pPlayer->GetPosition());
	//	}
	////	m_pPlayer->SetPosition(XMFLOAT3(50.0f, 500.0f, 0.0f));
	////m_pPlayer->GetCamera()->SetPosition(CameraPosition);
	//	}
	//	//else
	//		//m_pPlayer->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
	//}

}

void CScene::Particles(XMFLOAT3 pos, int nParticles)
{
	m_ppGameParticleObjects = new CParticleObject * [m_nGameParticleObjects];
	CParticleObject* pParticleObject = NULL;
	for (int i = 0; i < m_nGameParticleObjects; i++)
	{
		pParticleObject = new CParticleObject();
		pParticleObject->SetChild(m_pParticleModel, true);
		pParticleObject->OnInitialize();
		pParticleObject->Awake();
		pParticleObject->SetMovingDirection(XMFLOAT3(
			(float)RANDOM_NUM(-1000, 1000),
			(float)RANDOM_NUM(-1000, 1000),
			(float)RANDOM_NUM(-1000, 1000)));
		pParticleObject->SetPosition(pos);
		pParticleObject->SetScale(5.0f, 5.0f, 5.0f);
		pParticleObject->SetMovingRange(1.0f);
		pParticleObject->SetRotationAxis(XMFLOAT3(
			(float)RANDOM_NUM(-1000, 1000),
			(float)RANDOM_NUM(-1000, 1000),
			(float)RANDOM_NUM(-1000, 1000)));
		pParticleObject->SetRotationSpeed((float)RANDOM_NUM(50, 100));
		pParticleObject->SetMovingSpeed(2.0f);
		m_ppGameParticleObjects[i] = pParticleObject;
	}

	////////////////////////////////////////////
	/*m_ppGameParticleObjects = new CParticleObject * [m_nGameParticleObjects];
	CParticleObject* pParticleObject = NULL;

	pParticleObject = new CParticleObject();
	pParticleObject->SetChild(m_pParticleModel, true);
	pParticleObject->OnInitialize();
	pParticleObject->SetPosition(35.0f, 0.0f, 80.0f);
	pParticleObject->SetScale(5.0f, 5.0f, 5.0f);
	pParticleObject->Rotate(0.0f, 0.0f, 0.0f);
	m_ppGameParticleObjects[0] = pParticleObject;*/
}

