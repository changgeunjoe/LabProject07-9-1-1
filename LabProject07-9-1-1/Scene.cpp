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

	m_nGameObjects = 65;
	m_ppGameObjects = new CGameObject * [m_nGameObjects];
	m_pParticleModel= CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/TREE.bin");
	CGameObject* pApacheModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/TREE.bin");
	m_nGameParticleObjects =1;
	//pApacheModel->m_pMesh->Set_xmBoundingBox()
	//pApacheModel->SetOOBB(CMesh);
	CApacheObject* pApacheObject = NULL;
	for (int i = 0; i < 60; i++) {
		pApacheObject = new CApacheObject();
		pApacheObject->SetChild(pApacheModel, true);

		pApacheObject->OnInitialize();
		if (i < 30)
			pApacheObject->SetPosition(-100.0f, 0.0f, -200.0f - (i - 30) * 50);

		else
			pApacheObject->SetPosition(100.0f, 0.0f, -200.0f + (i - 30) * 50);
		pApacheObject->SetScale(5.0f, 5.0f, 5.0f);
		pApacheObject->Rotate(0.0f, 90.0f, 0.0f);
		pApacheObject->m_xmOOBB = BoundingOrientedBox(pApacheObject->GetPosition(), XMFLOAT3(5.0f, 5.0f, 5.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
		pApacheObject->SetOOBB();
		m_ppGameObjects[i] = pApacheObject;
	}
	CGameObject* pOldCarModel = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/OldCar.bin");
	CGunshipObject* pGunshipObject = NULL;
	pApacheObject = new CApacheObject();
	pApacheObject->SetChild(pOldCarModel, true);
	pApacheObject->OnInitialize();
	pApacheObject->SetPosition(-75.0f, 0.0f, 80.0f);
	pApacheObject->SetScale(5.0f, 5.0f, 5.0f);
	pApacheObject->Rotate(0.0f, 0.0f, 0.0f);
	pApacheObject->m_xmOOBB = BoundingOrientedBox(pApacheObject->GetPosition(), XMFLOAT3(5.0f, 5.0f, 7.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	pApacheObject->SetOOBB();
	m_ppGameObjects[60] = pApacheObject;

	pApacheObject = new CApacheObject();
	pApacheObject->SetChild(pOldCarModel, true);
	pApacheObject->OnInitialize();
	pApacheObject->SetPosition(-35.0f, 0.0f, 80.0f);
	pApacheObject->SetScale(5.0f, 5.0f, 5.0f);
	pApacheObject->Rotate(0.0f, 0.0f, 0.0f);

	m_ppGameObjects[61] = pApacheObject;
	m_ppGameObjects[61]->m_xmOOBB = BoundingOrientedBox(pApacheObject->GetPosition(), XMFLOAT3(5.0f, 5.0f, 7.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	pApacheObject->SetOOBB();

	pApacheObject = new CApacheObject();
	pApacheObject->SetChild(pOldCarModel, true);
	pApacheObject->OnInitialize();
	pApacheObject->SetPosition(-0.0f, 0.0f, 80.0f);
	pApacheObject->SetScale(5.0f, 5.0f, 5.0f);
	pApacheObject->Rotate(0.0f, 0.0f, 0.0f);

	m_ppGameObjects[62] = pApacheObject;
	m_ppGameObjects[62]->m_xmOOBB = BoundingOrientedBox(pApacheObject->GetPosition(), XMFLOAT3(5.0f, 5.0f, 7.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	pApacheObject->SetOOBB();


	pApacheObject = new CApacheObject();
	pApacheObject->SetChild(pOldCarModel, true);
	pApacheObject->OnInitialize();
	pApacheObject->SetPosition(35.0f, 0.0f, 80.0f);
	pApacheObject->SetScale(5.0f, 5.0f, 5.0f);
	pApacheObject->Rotate(0.0f, 0.0f, 0.0f);
	m_ppGameObjects[63] = pApacheObject;
	m_ppGameObjects[63]->m_xmOOBB = BoundingOrientedBox(pApacheObject->GetPosition(), XMFLOAT3(5.0f, 5.0f, 7.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	pApacheObject->SetOOBB();

	pApacheObject = new CApacheObject();
	pApacheObject->SetChild(pOldCarModel, true);
	pApacheObject->OnInitialize();
	pApacheObject->SetPosition(70.0f, 0.0f, 80.0f);
	pApacheObject->SetScale(5.0f, 5.0f, 5.0f);
	pApacheObject->Rotate(0.0f, 0.0f, 0.0f);
	m_ppGameObjects[64] = pApacheObject;
	m_ppGameObjects[64]->m_xmOOBB = BoundingOrientedBox(pApacheObject->GetPosition(), XMFLOAT3(5.0f, 5.0f, 7.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	pApacheObject->SetOOBB();

	/*m_ppGameParticleObjects = new CParticleObject * [m_nGameParticleObjects];
	CParticleObject* pParticleObject = NULL;

	pParticleObject = new CParticleObject();
	pParticleObject->SetChild(m_pParticleModel, true);
	pParticleObject->OnInitialize();
	pParticleObject->SetPosition(35.0f, 0.0f, 80.0f);
	pParticleObject->SetScale(5.0f, 5.0f, 5.0f);
	pParticleObject->Rotate(0.0f, 0.0f, 0.0f);
	m_ppGameParticleObjects[0] = pParticleObject;*/
	//m_ppGameObjects[63]->m_xmOOBB = BoundingOrientedBox(pApacheObject->GetPosition(), XMFLOAT3(5.0f, 5.0f, 7.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//pApacheObject->SetOOBB();

	Particles(XMFLOAT3(0.0f,0.0f,0.0f), 1);


	//pApacheObject = new CApacheObject();
	//pApacheObject->SetChild(pOldCarModel, true);
	//pApacheObject->OnInitialize();
	//pApacheObject->SetPosition(75.0f, 0.0f, 80.0f);
	//pApacheObject->SetScale(5.0f, 5.0f, 5.0f);
	//pApacheObject->Rotate(0.0f, 0.0f, 0.0f);
	//m_ppGameObjects[64] = pApacheObject;
	//m_ppGameObjects[64]->m_xmOOBB = BoundingOrientedBox(pApacheObject->GetPosition(), XMFLOAT3(5.0f, 5.0f, 7.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//pApacheObject->SetOOBB();

	CreateShaderVariables(pd3dDevice, pd3dCommandList);

	/*m_pShaders[ObjectTag::Particle].CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pnObjects[ObjectTag::Particle] = 500;
	m_pppObjects[ObjectTag::Particle] =
		new CGameObject * [m_pnObjects[ObjectTag::Particle]];
	CCubeMeshDiffused* pParticleMeshs =
		new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < m_pnObjects[ObjectTag::Particle]; ++i)
	{
		CRotatingObject* Cube = new CRotatingObject();
		Cube->SetObjectType(CGameObject::ObjectType::Particle);
		Cube->SetPosition(0.0f, 100.0f, 0.0f);
		Cube->SetOOBB(pParticleMeshs->GetBoundingBox());
		Cube->SetRotationAxis(XMFLOAT3(
			(float)RANDOM_NUM(-1000, 1000),
			(float)RANDOM_NUM(-1000, 1000),
			(float)RANDOM_NUM(-1000, 1000)));
		Cube->SetRotationSpeed((float)RANDOM_NUM(50, 100));
		Cube->SetMovingSpeed(100.0f);
		Cube->Sleep();
		m_pppObjects[ObjectTag::Particle][i] = Cube;
	}
	m_pppObjects[ObjectTag::Particle][0]->SetMesh(pParticleMeshs);
	m_pShaders[ObjectTag::Particle].BuildObjects(
		pd3dDevice, pd3dCommandList,
		m_pppObjects[ObjectTag::Particle], m_pnObjects[ObjectTag::Particle]);*/
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

	if (m_pLights) delete[] m_pLights;
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
	UINT ncbElementBytes = ((sizeof(LIGHTS) + 255) & ~255); //256ÀÇ ¹è¼ö
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
//	for (int i = 0; i < m_nGameParticleObjects; i++) m_ppGameParticleObjects[i]->ReleaseUploadBuffers();
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
	for (int i = 60; i < 65; i++)
	{
		if (m_ppGameObjects[i]->GetPosition().z < -40.0f)
		{
			m_ppGameObjects[i]->SetPositionZ(RANDOM_NUM(400, 700));
		}
		m_ppGameObjects[i]->MoveForward(-0.2f);
		//m_ppGameObjects[i]->m_xmOOBB = BoundingOrientedBox(m_ppGameObjects[i]->GetPosition(), m_ppGameObjects[i]->m_xmOOBB.Extents, XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	}
	for (int i = 60; i < m_nGameObjects; i++) m_ppGameObjects[i]->Animate(fTimeElapsed, NULL);
	for (int i = 0; i < m_nGameParticleObjects; i++)
	{
		if (m_ppGameParticleObjects[i]->IsActive())
		{
		}
	}

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
	for (int i = 0; i < m_nGameParticleObjects; i++)
	{
		if (m_ppGameParticleObjects[i])
		{
			m_ppGameParticleObjects[i]->Animate(m_fElapsedTime, NULL);
			m_ppGameParticleObjects[i]->UpdateTransform(NULL);
			m_ppGameParticleObjects[i]->Render(pd3dCommandList, pCamera);
		}
	}
}

void CScene::CheckObjectByWallCollision()
{
	for (int i = 0; i < m_nGameObjects; i++)
	{
		BoundingOrientedBox wmPlayerOOBB = m_pPlayer->m_xmOOBB;
		ContainmentType containType = m_ppGameObjects[i]->m_xmOOBB.Contains(wmPlayerOOBB);
		if (m_ppGameObjects[i]->m_xmOOBB.Intersects(wmPlayerOOBB))
			m_pPlayer->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
			//Particles(m_pPlayer->GetPosition(), 300);
		//else
			//m_pPlayer->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));
	}

}

void CScene::Particles(XMFLOAT3 pos, int nParticles)
{
	//m_ppGameParticleObjects = new CParticleObject * [m_nGameParticleObjects];
	//CParticleObject* pParticleObject = NULL;
	//for (int i = 0; i < m_nGameParticleObjects; i++)
	//{
	//	pParticleObject = new CParticleObject();
	//	pParticleObject->SetChild(m_pParticleModel, true);
	//	pParticleObject->OnInitialize();
	//	pParticleObject->Awake();
	//	pParticleObject->SetMovingDirection(XMFLOAT3(
	//		(float)RANDOM_NUM(-1000, 1000),
	//		(float)RANDOM_NUM(-1000, 1000),
	//		(float)RANDOM_NUM(-1000, 1000)));
	//	pParticleObject->SetPosition(pos);
	//	pParticleObject->SetScale(5.0f, 5.0f, 5.0f);
	//	pParticleObject->SetMovingRange(1.0f);
	//	pParticleObject->SetRotationAxis(XMFLOAT3(
	//		(float)RANDOM_NUM(-1000, 1000),
	//		(float)RANDOM_NUM(-1000, 1000),
	//		(float)RANDOM_NUM(-1000, 1000)));
	//	pParticleObject->SetRotationSpeed((float)RANDOM_NUM(50, 100));
	//	pParticleObject->SetMovingSpeed(2.0f);
	//	m_ppGameParticleObjects[i] = pParticleObject;
	//}
	m_ppGameParticleObjects = new CParticleObject * [m_nGameParticleObjects];
	CParticleObject* pParticleObject = NULL;

	pParticleObject = new CParticleObject();
	pParticleObject->SetChild(m_pParticleModel, true);
	pParticleObject->OnInitialize();
	pParticleObject->SetPosition(35.0f, 0.0f, 80.0f);
	pParticleObject->SetScale(5.0f, 5.0f, 5.0f);
	pParticleObject->Rotate(0.0f, 0.0f, 0.0f);
	m_ppGameParticleObjects[0] = pParticleObject;
}

