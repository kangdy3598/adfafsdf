#include "pch.h"
#include "ImGuiManger.h"
#include "Define.h"
#include "iostream"

IMPLEMENT_SINGLETON(CImGuiManger)

CImGuiManger::CImGuiManger()
	:testbool(false)
	,inttest(10)
	,floattest(5.5f)
	,m_pTerrainTexture(nullptr)
	,m_bshowTileTextureWindow(false)
	,iTileX(0)
	,iTileY(0)
	,fVtxItv(0)
	,m_bTerrainOnOff(false)
	,m_bWireFrameModeOnOff(false)
	,m_pGraphicDev(nullptr)
	,m_pMapTex(nullptr)
	,m_vecPickPos(0.f,0.f,0.f)
	,m_bImageButtonClick(false)
	,m_pCurTerrainTexture(nullptr)
	,m_bshowObjectTextrueWindow(false)
	,m_bshowInstalledObjectList(false)
{

}


CImGuiManger::~CImGuiManger()
{
}

void CImGuiManger::init()
{
	//�ʱ�ȭ �ϱ� 

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

	m_pGraphicDev = CGraphicDev::GetInstance()->Get_GraphicDev();


    ImGui_ImplWin32_Init(g_hWnd);
    ImGui_ImplDX9_Init(m_pGraphicDev);

	//ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("../TTF/Pretendard-Regular.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesKorean());


	ImGui::SetNextWindowSize(ImVec2(400, 400)); // Imgui â ũ�� 
	ImGui::SetNextWindowPos(ImVec2(0, 0));

	

	
	m_vecTerrainTexture.resize(14);
	


	for(int i=1; i<m_vecTerrainTexture.size()+1; i++)
	{

		char filePath[256];
		sprintf_s(filePath, "../Bin/Resource/Texture/Map/Tile%d.png", i-1);

		HRESULT hr = LoadTextureFromFile(CGraphicDev::GetInstance()->Get_GraphicDev(), filePath, &m_vecTerrainTexture[i-1]);
		if (FAILED(hr))
		{
			MSG_BOX("Terrain Texture load failed");
		}
	}

	
	// ������Ʈ �� �۾� 
	CImgui_ObjectTool::GetInstance()->init();

	// ������Ʈ �� �� ���̺� �۾�
	//CImgui_ObjectTool::GetInstance()->Save();

}

void CImGuiManger::update()
{

	// ������Ʈ 

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	if (ImGui::Begin("Map Editor", NULL, ImGuiWindowFlags_MenuBar))
	{

		// ������Ʈ �� �� ���̺� �۾�
		if (ImGui::BeginMenuBar())
		{
			// ���� , �ҷ�����. 
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem(u8"����"))
				{
					CImgui_ObjectTool::GetInstance()->Save();
				}

				else if (ImGui::MenuItem(u8"�ҷ�����"))
				{
					CImgui_ObjectTool::GetInstance()->Read();
				}
				ImGui::EndMenu();
			}
			// 
			//������ End
			ImGui::EndMenuBar();
		}


		//Tile MenuBar
		if (ImGui::BeginMenuBar())
		{
			//����..
			if (ImGui::BeginMenu("Tile"))
			{
				if (ImGui::MenuItem("Tile Texture List"))
				{
					m_bshowTileTextureWindow = true;
				}

				ImGui::EndMenu();
			}
			// 
			//������ End
			ImGui::EndMenuBar();
		}


		//Terrain MenuBar
		if (ImGui::BeginMenuBar())
		{
			// Terrain ���� Ű�� 
			if (ImGui::BeginMenu("Terrain"))
			{
				if (ImGui::MenuItem("On"))
				{
					m_bTerrainOnOff = true;
				}

				else if(ImGui::MenuItem("Off"))
				{
					m_bTerrainOnOff = false; 
				}


				else if(ImGui::MenuItem("WireFrameOn"))
				{
					m_bWireFrameModeOnOff = true;
				}

				else if (ImGui::MenuItem("WireFrameOff"))
				{
					m_bWireFrameModeOnOff = false;
				}

				ImGui::EndMenu();
			}
			// 
			//������ End
			ImGui::EndMenuBar();
		}


		// ������Ʈ �� ������Ʈ�ϱ� 
		CImgui_ObjectTool::GetInstance()->update();	
		

		// �� �ؿ��ٰ� ������� �߰�
		

		ImGui::Checkbox("Test Bool", &testbool);
		if (ImGui::Button("Click me!"))
		{
			testbool = true;
		}
		ImGui::SliderInt("Chose Int", &inttest, 1, 25);
		ImGui::SliderFloat("Chose Float", &floattest, 0.1f, 15.5f);


	}ImGui::End();


	// imgui Ÿ�� �� ����
	if (m_bshowTileTextureWindow)	
	{
		ShowTileMenuWindow();	
	}


}

void CImGuiManger::Render()
{
	ImGui::Render();	
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());	
	ImGui::EndFrame();	
}

void CImGuiManger::Release()
{
	// ������ 
}

void CImGuiManger::ShowTileMenuWindow()
{
	// Tile Texture List â ����
	if (m_bshowTileTextureWindow)
	{
		// ���ο� â ����
		ImGui::Begin("Tile Texture List", &m_bshowTileTextureWindow);
		// ���⿡ â�� ������ �߰�
		// 
		//���� â ������ �������� 
		ImVec2 CurrentWindowSize = ImGui::GetWindowSize();


		ImVec2 imageSize(100, 100);  // ����� �̹��� ũ��

		
		for (int i = 1; i < m_vecTerrainTexture.size() + 1; i++)
		{

			char label[16];
			sprintf_s(label, "Tile%d", i);
			// �̹��� ���
			//ImGui::Image((void*)m_vecTexture[i - 1], imageSize);
			if (ImGui::ImageButton(label, (void*)m_vecTerrainTexture[i - 1], imageSize)) 
			{
				// ImageButton�� Ŭ���� ��� ȣ���� �Լ�
				OnTileImageButtonClick(i);  // ����: Ŭ���� Ÿ���� �ε����� �Լ��� ����
			};

			// ���� â���� ���� ���� ���� Ȯ��
			//ImVec2 availableSpace = ImGui::GetContentRegionAvail();

			// ���� ������ �̹��� ũ�⺸�� ũ�ٸ� ���� �ٿ� �̹��� ���
			if (i % (int)(CurrentWindowSize.x/100) != 0)
			{
				ImGui::SameLine();  // ���� �ٿ� ���
			}

			else if (i % (int)(CurrentWindowSize.x/100) == 0)
			{
				// ������ �����ϸ� ���� �ٷ� �̵�
				ImGui::NewLine();
			}
		}

		ImGui::NewLine();
		//ImGui::Text("Tile Texture List Content Here");

		if (!ImGui::CollapsingHeader(u8"Ÿ�� ����"))
		{	
			
			ImGui::Text(u8"������ Ÿ���� ��� ���� �� ����");
			ImGui::NewLine();


			ImGui::PushItemWidth(100.0f);  // �ʺ� 100�ȼ��� ����
			
			ImGui::Text("Tile X");  // ���̺� ���
			ImGui::SameLine();
			ImGui::InputInt("##Tile X", &iTileX);
			ImGui::SameLine(170.0f, 0.0f);
			ImGui::Text("Tile Y");  // ���̺� ���
			ImGui::SameLine();
			ImGui::InputInt("##Tile Y", &iTileY);
			ImGui::NewLine();
			ImGui::Text(u8"�� ����");  // ���̺� ���
			ImGui::SameLine();
			ImGui::InputFloat("##VtxItv" ,&fVtxItv);

			ImGui::NewLine();	
			if(ImGui::Button(u8"��������"))
			{
				
			}
			//ImGui::PopStyleColor(3);
			ImGui::PopItemWidth();  // ������ �ʺ� ������� ����
		}


		

		ImGui::End();
	}

}


void CImGuiManger::OnTileImageButtonClick(int tileIndex)
{
	// ���⼭ Ÿ�� �̹����� ������ 
	// ���⼭ ���� ������ �ͼ� �ش� ���콺��ǥ�� �������ǰ� �ؾ���. 

	//m_pGraphicDev->SetTexture(0, m_vecTexture[tileIndex]);
	m_bImageButtonClick = true; 
	m_pCurTerrainTexture = m_vecTerrainTexture[tileIndex - 1];

}


