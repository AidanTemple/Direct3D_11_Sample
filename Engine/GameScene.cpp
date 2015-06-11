#pragma region Includes

#include "GameScene.h"

#pragma endregion

#pragma region Initialization

GameScene::GameScene()
{
	// Initialize all objects.

	m_D3D = 0;
	m_Camera = 0;
	m_BumpMapShader = 0;
	m_SpecularShader = 0;
	m_AlphaMapShader = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_Input = 0;
	m_GameTime = 0;
	m_SkyDome = 0;
	m_SkyDomeShader = 0;
	m_Grass = 0;
	m_Floor = 0;
	m_Coloumns = 0;
	m_IvyExterior = 0;
	m_IvyInterior = 0;
	m_Rock = 0;
	m_Planks = 0;
	m_Wall = 0;
	m_WallsLower = 0;
	m_WallsUpper = 0;
	m_Beams = 0;
	m_Table = 0;
	m_Tree = 0;
	m_Roof = 0;
	m_RoofSupports = 0;
	m_HangingCauldron = 0;
	m_Counter = 0;
}

GameScene::GameScene(const GameScene& other)
{

}

GameScene::~GameScene()
{

}

bool GameScene::Initialize(HINSTANCE hInstance, int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	float cameraX;
	float cameraY;
	float cameraZ;

	D3DXMATRIX baseViewMatrix;

	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new Input;
	
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hInstance, hwnd, screenWidth, screenHeight);
	
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_D3D = new Direct3D;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new Camera;

	if(!m_Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Set the initial position of the camera.
	cameraX = 0.0f;
	cameraY = -100.0f;
	cameraZ = -1500.0f;

	m_Camera->SetPosition(cameraX, cameraY, cameraZ);

	// Create game timer object.
	m_GameTime = new GameTime;

	if(!m_GameTime)
	{
		return false;
	}

	// Initialize the game timer.
	result = m_GameTime->Initialize();

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the GameTime object.", L"Error", MB_OK);
		return false;
	}

	// Create the model objects.
	
	m_Grass = new ModelClass;

	if(!m_Grass)
	{
		return false;
	}

	m_Floor = new ModelClass;

	if(!m_Floor)
	{
		return false;
	}

	m_Coloumns = new ModelClass;

	if(!m_Coloumns)
	{
		return false;
	}

	m_IvyExterior = new ModelClass;

	if(!m_IvyExterior)
	{
		return false;
	}

	m_IvyInterior = new ModelClass;

	if(!m_IvyInterior)
	{
		return false;
	}

	m_Planks = new ModelClass;

	if(!m_Planks)
	{
		return false;
	}

	m_Wall = new ModelClass;

	if(!m_Wall)
	{
		return false;
	}

	m_WallsLower = new ModelClass;

	if(!m_WallsLower)
	{
		return false;
	}

	m_WallsUpper = new ModelClass;

	if(!m_WallsUpper)
	{
		return false;
	}

	m_Beams = new ModelClass;

	if(!m_Beams)
	{
		return false;
	}

	m_Table = new ModelClass;

	if(!m_Table)
	{
		return false;
	}

	m_Roof = new ModelClass;

	if(!m_Roof)
	{
		return false;
	}

	m_RoofSupports = new ModelClass;

	if(!m_RoofSupports)
	{
		return false;
	}

	m_HangingCauldron = new ModelClass;

	if(!m_HangingCauldron)
	{
		return false;
	}

	m_Rock = new ModelClass;

	if(!m_Rock)
	{
		return false;
	}

	m_Tree = new ModelClass;

	if(!m_Tree)
	{
		return false;
	}

	// Initialize the model objects.

	result = m_Grass->Initialize(m_D3D->GetDevice(),
		"../Engine/Content/Models/TXT/Grass.txt",
		L"../Engine/Content/Textures/Terrain/Grass_Diffuse.png",
		L"../Engine/Content/Textures/Terrain/Grass_Diffuse.png");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the grass object.", L"Error", MB_OK);
		return false;
	}

	result = m_Floor->Initialize(m_D3D->GetDevice(),
		"../Engine/Content/Models/TXT/Floor.txt",
		L"../Engine/Content/Textures/Buildings/Paving_Diffuse.png",
		L"../Engine/Content/Textures/Buildings/Paving_Normal.png");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the floor object.", L"Error", MB_OK);
		return false;
	}

	result = m_Coloumns->Initialize(m_D3D->GetDevice(), 
		"../Engine/Content/Models/TXT/ArchColoumns.txt",
		L"../Engine/Content/Textures/Buildings/WoodOld_01_Diffuse.png",
		L"../Engine/Content/Textures/Buildings/WoodOld_Normal.png");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the coloumns object.", L"Error", MB_OK);
		return false;
	}

	result = m_IvyExterior->Initialize(m_D3D->GetDevice(),
		"../Engine/Content/Models/TXT/IvyExterior.txt",
		L"../Engine/Content/Textures/Trees/Ivy_Diff.png",
		L"../Engine/Content/Textures/Trees/Ivy_Normal.png",
		L"../Engine/Content/Textures/Trees/Ivy_Alpha.png");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the ivy exterior object.", L"Error", MB_OK);
		return false;
	}

	result = m_IvyInterior->Initialize(m_D3D->GetDevice(),
		"../Engine/Content/Models/TXT/IvyInterior.txt",
		L"../Engine/Content/Textures/Trees/Ivy_Diff.png",
		L"../Engine/Content/Textures/Trees/Ivy_Normal.png",
		L"../Engine/Content/Textures/Trees/Ivy_Alpha.png");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the ivy interior object.", L"Error", MB_OK);
		return false;
	}

	result = m_Beams->Initialize(m_D3D->GetDevice(),
		"../Engine/Content/Models/TXT/SupportBeams.txt",
		L"../Engine/Content/Textures/Buildings/WoodOld_01_Diffuse.png",
		L"../Engine/Content/Textures/Buildings/WoodOld_Normal.png");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the beams object.", L"Error", MB_OK);
		return false;
	}

	result = m_Planks->Initialize(m_D3D->GetDevice(),
		"../Engine/Content/Models/TXT/RoughWoodenPlanks.txt",
		L"../Engine/Content/Textures/Buildings/RoughWoodPlanks_Diffuse.png",
		L"../Engine/Content/Textures/Buildings/RoughWoodPlanks_Normal.png");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the planks object.", L"Error", MB_OK);
		return false;
	}

	result = m_Wall->Initialize(m_D3D->GetDevice(),
		"../Engine/Content/Models/TXT/StoneWall.txt", 
		L"../Engine/Content/Textures/Buildings/RockWall_Diffuse.png", 
		L"../Engine/Content/Textures/Buildings/RockWall_Normal.png");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the wall object.", L"Error", MB_OK);
		return false;
	}

	result = m_WallsLower->Initialize(m_D3D->GetDevice(),
		"../Engine/Content/Models/TXT/WallsLower.txt", 
		L"../Engine/Content/Textures/Buildings/WallsLower_Diffuse.png", 
		L"../Engine/Content/Textures/Buildings/WallsLower_Normal.png");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the walls lower object.", L"Error", MB_OK);
		return false;
	}

	result = m_WallsUpper->Initialize(m_D3D->GetDevice(),
		"../Engine/Content/Models/TXT/WallsUpper.txt",
		L"../Engine/Content/Textures/Buildings/WallUpper_Diffuse.png",
		L"../Engine/Content/Textures/Buildings/WallUpper_Normal.png");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the walls upper object.", L"Error", MB_OK);
		return false;
	}

	result = m_Roof->Initialize(m_D3D->GetDevice(), 
		"../Engine/Content/Models/TXT/WoodenRoof.txt", 
		L"../Engine/Content/Textures/Buildings/WoodenRoof_Diffuse.png", 
		L"../Engine/Content/Textures/Buildings/WoodenRoof_Normal.png");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the roof object.", L"Error", MB_OK);
		return false;
	}

	result = m_RoofSupports->Initialize(m_D3D->GetDevice(), 
		"../Engine/Content/Models/TXT/WoodSupports.txt", 
		L"../Engine/Content/Textures/Buildings/WoodOld_01_Diffuse.png",
		L"../Engine/Content/Textures/Buildings/WoodOld_Normal.png");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the roof support object.", L"Error", MB_OK);
		return false;
	}

	result = m_Table->Initialize(m_D3D->GetDevice(),
		"../Engine/Content/Models/TXT/Table.txt",
		L"../Engine/Content/Textures/Props/Table_Diffuse.png",
		L"../Engine/Content/Textures/Props/Table_Normal.png",
		L"../Engine/Content/Textures/Props/Table_Specular.png");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the table object.", L"Error", MB_OK);
		return false;
	}

	result = m_HangingCauldron->Initialize(m_D3D->GetDevice(),
		"../Engine/Content/Models/TXT/Cauldron_Hanging.txt",
		L"../Engine/Content/Textures/Props/Cauldron_Diffuse.png",
		L"../Engine/Content/Textures/Props/Cauldron_Normal.png",
		L"../Engine/Content/Textures/Props/Cauldron_Specular.png");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the cauldron object.", L"Error", MB_OK);
		return false;
	}

	result = m_Rock->Initialize(m_D3D->GetDevice(),
		"../Engine/Content/Models/TXT/Rock.txt",
		L"../Engine/Content/Textures/Rocks/Rock_Diffuse.png",
		L"../Engine/Content/Textures/Rocks/Rock_Normal.png");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the rock object.", L"Error", MB_OK);
		return false;
	}

	result = m_Tree->Initialize(m_D3D->GetDevice(),
		"../Engine/Content/Models/TXT/Tree.txt",
		L"../Engine/Content/Textures/Trees/Tree_Diffuse.png",
		L"../Engine/Content/Textures/Trees/Tree_Normal.png");

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the tree object.", L"Error", MB_OK);
		return false;
	}

	// Create the bump map shader object.
	m_BumpMapShader = new BumpMapShader;

	if(!m_BumpMapShader)
	{
		return false;
	}

	// Initialize the bump map shader object.
	result = m_BumpMapShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the bump map shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the specular map shader object.
	m_SpecularShader = new SpecularMapShader;

	if(!m_SpecularShader)
	{
		return false;
	}

	// Initialize the specular map shader object.
	result = m_SpecularShader->Initialize(m_D3D->GetDevice(), hwnd);
	
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the specular map shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the alpha map shader object.
	m_AlphaMapShader = new AlphaMapShader;
	if(!m_AlphaMapShader)
	{
		return false;
	}

	// Initialize the alpha map shader object.
	result = m_AlphaMapShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the alpha map shader object.", L"Error", MB_OK);
		return false;
	}

	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Create the sky dome object.
	m_SkyDome = new SkyDome;
	
	if(!m_SkyDome)
	{
		return false;
	}

	// Initialize the sky dome object.
	result = m_SkyDome->Initialize(m_D3D->GetDevice());
	
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky dome shader object.
	m_SkyDomeShader = new SkyDomeShader;
	
	if(!m_SkyDomeShader)
	{
		return false;
	}

	// Initialize the sky dome shader object.
	result = m_SkyDomeShader->Initialize(m_D3D->GetDevice(), hwnd);
	
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome shader object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	return true;
}

#pragma endregion

#pragma region Shutdown

void GameScene::Shutdown()
{
	// Release the sky dome shader object.
	if(m_SkyDomeShader)
	{
		m_SkyDomeShader->Shutdown();
		delete m_SkyDomeShader;
		m_SkyDomeShader = 0;
	}

	// Release the sky dome object.
	if(m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the alpha map shader object.
	if(m_AlphaMapShader)
	{
		m_AlphaMapShader->Shutdown();
		delete m_AlphaMapShader;
		m_AlphaMapShader = 0;
	}

	// Release the specular map shader object.
	if(m_SpecularShader)
	{
		m_SpecularShader->Shutdown();
		delete m_SpecularShader;
		m_SpecularShader = 0;
	}

	// Release the bump map shader object.
	if(m_BumpMapShader)
	{
		m_BumpMapShader->Shutdown();
		delete m_BumpMapShader;
		m_BumpMapShader = 0;
	}

	// Release the model object.

	if(m_Tree)
	{
		m_Tree->Shutdown();
		delete m_Tree;
		m_Tree = 0;
	}

	if(m_Rock)
	{
		m_Rock->Shutdown();
		delete m_Rock;
		m_Rock = 0;
	}

	if(m_HangingCauldron)
	{
		m_HangingCauldron->Shutdown();
		delete m_HangingCauldron;
		m_HangingCauldron= 0;
	}

	if(m_RoofSupports)
	{
		m_RoofSupports->Shutdown();
		delete m_RoofSupports;
		m_RoofSupports = 0;
	}
	
	if(m_Roof)
	{
		m_Roof->Shutdown();
		delete m_Roof;
		m_Roof = 0;
	}

	if(m_Table)
	{
		m_Table->Shutdown();
		delete m_Table;
		m_Table = 0;
	}

	if(m_Beams)
	{
		m_Beams->Shutdown();
		delete m_Beams;
		m_Beams = 0;
	}

	if(m_WallsUpper)
	{
		m_WallsUpper->Shutdown();
		delete m_WallsUpper;
		m_WallsUpper = 0;
	}

	if(m_WallsLower)
	{
		m_WallsLower->Shutdown();
		delete m_WallsLower;
		m_WallsLower = 0;
	}

	if(m_Wall)
	{
		m_Wall->Shutdown();
		delete m_Wall;
		m_Wall = 0;
	}

	if(m_Planks)
	{
		m_Planks->Shutdown();
		delete m_Planks;
		m_Planks = 0;
	}

	if(m_IvyInterior)
	{
		m_IvyInterior->Shutdown();
		delete m_IvyInterior;
		m_IvyInterior = 0;
	}

	if(m_IvyExterior)
	{
		m_IvyExterior->Shutdown();
		delete m_IvyExterior;
		m_IvyExterior = 0;
	}

	if(m_Coloumns)
	{
		m_Coloumns->Shutdown();
		delete m_Coloumns;
		m_Coloumns = 0;
	}

	if(m_Floor)
	{
		m_Floor->Shutdown();
		delete m_Floor;
		m_Floor = 0;
	}

	if(m_Grass)
	{
		m_Grass->Shutdown();
		delete m_Grass;
		m_Grass = 0;
	}

	if(m_GameTime)
	{
		delete m_GameTime;
		m_GameTime = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the input object.
	if(m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}

#pragma endregion

#pragma region Update

bool GameScene::Frame(float gameTime, int frameRate)
{
	bool result;

	// Read user input
	result = m_Input->Frame();
	
	if(!result)
	{
		return false;
	}

	// Update game time
	m_GameTime->Frame();

	// Update position
	result = UpdateInput(m_GameTime->GetTime());

	if(!result)
	{
		return false;
	}

	// Render the graphics scene.
	result = Render();

	if(!result)
	{
		return false;
	}

	return true;
}

bool GameScene::UpdateInput(float frameTime)
{
	bool IsKeyPressed;

	float posX, posY, posZ, rotX, rotY, rotZ;

	// Set the frame time for calculating the updated position.
	m_Camera->SetFrameTime(frameTime);

	// Check if the user is pressing a key. If they are
	// then move them in the corresponding direction.

	if(IsKeyPressed = m_Input->IsQPressed())
	{
		m_Camera->LookUp(IsKeyPressed);
	}

	if(IsKeyPressed = m_Input->IsEPressed())
	{
		m_Camera->LookDown(IsKeyPressed);
	}

	if(IsKeyPressed = m_Input->IsWPressed() 
		|| m_Input->IsUpPressed())
	{
		m_Camera->MoveForward(IsKeyPressed);
	}
	
	if(IsKeyPressed = m_Input->IsSPressed() 
		|| m_Input->IsDownPressed())
	{
		m_Camera->MoveBack(IsKeyPressed);
	}

	if(IsKeyPressed = m_Input->IsAPressed() 
		|| m_Input->IsLeftPressed())
	{
		m_Camera->TurnLeft(IsKeyPressed);
	}

	if(IsKeyPressed = m_Input->IsDPressed() 
		|| m_Input->IsRightPressed())
	{
		m_Camera->TurnRight(IsKeyPressed);
	}

	// Get the position of the camera
	m_Camera->GetPosition(posX, posY, posZ);
	m_Camera->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	return true;
}

#pragma endregion

#pragma region Render

bool GameScene::Render()
{
	D3DXMATRIX worldMatrix; 
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;
	D3DXMATRIX orthoMatrix;

	D3DXVECTOR3 cameraPosition;

	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

	// Translate the sky dome to be centered around the camera position.
	D3DXMatrixTranslation(&worldMatrix, cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Turn off back face culling.
	m_D3D->TurnOffCulling();

	// Turn off the Z buffer.
	m_D3D->TurnZBufferOff();

	// Render the sky dome using the sky dome shader.
	m_SkyDome->Render(m_D3D->GetDeviceContext());

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
				       m_SkyDome->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
					   m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	// Turn back face culling back on.
	m_D3D->TurnOnCulling();

	// Turn the Z buffer back on.
	m_D3D->TurnZBufferOn();

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Render grass using bump map shader
	m_Grass->Render(m_D3D->GetDeviceContext());

	m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_Grass->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Grass->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

	// Render rock using bump map shader
	m_Rock->Render(m_D3D->GetDeviceContext());

	m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_Rock->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Rock->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

	// Render tree using bump map shader
	m_Tree->Render(m_D3D->GetDeviceContext());

	m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_Tree->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Tree->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

	// Render floor using bump map shader
	m_Floor->Render(m_D3D->GetDeviceContext());

	m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_Floor->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Floor->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

	// Render roof supports using bump map shader
	m_RoofSupports->Render(m_D3D->GetDeviceContext());

	m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_RoofSupports->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_RoofSupports->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Roof->Render(m_D3D->GetDeviceContext());

	//// Render the model using the bump map shader.
	m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_Roof->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Roof->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

	// Render beams using bump map shader
	m_Beams->Render(m_D3D->GetDeviceContext());

	m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_Beams->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Beams->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

	// Render wall using bump map shader
	m_Wall->Render(m_D3D->GetDeviceContext());

	m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_Wall->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Wall->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

	// Render walls lowerusing bump map shader
	m_WallsLower->Render(m_D3D->GetDeviceContext());

	m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_WallsLower->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_WallsLower->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

	// Render walls upper using bump map shader
	m_WallsUpper->Render(m_D3D->GetDeviceContext());

	m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_WallsUpper->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_WallsUpper->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

	// Render planks using bump map shader
	m_Planks->Render(m_D3D->GetDeviceContext());

	m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_Planks->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Planks->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

	// Render coloumns using bump map shader
	m_Coloumns->Render(m_D3D->GetDeviceContext());

	m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_Coloumns->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Coloumns->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

	// Render table using specular map shader
	m_Table->Render(m_D3D->GetDeviceContext());

	m_SpecularShader->Render(m_D3D->GetDeviceContext(), m_Table->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Table->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), 
				m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	// Render cauldron using specular map shader
	m_HangingCauldron->Render(m_D3D->GetDeviceContext());

	m_SpecularShader->Render(m_D3D->GetDeviceContext(), m_HangingCauldron->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_HangingCauldron->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), 
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	// Turn on alpha blending for the transparency to work.
	m_D3D->TurnOnAlphaBlending();

	// Render ivy using alpa map shader
	m_IvyInterior->Render(m_D3D->GetDeviceContext());

	m_AlphaMapShader->Render(m_D3D->GetDeviceContext(), m_IvyInterior->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				 m_IvyInterior->GetTextureArray(), 1.0f);

	m_IvyExterior->Render(m_D3D->GetDeviceContext());

	m_AlphaMapShader->Render(m_D3D->GetDeviceContext(), m_IvyExterior->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				 m_IvyExterior->GetTextureArray(), 1.0f);

	// Turn off alpha blending.
	m_D3D->TurnOffAlphaBlending();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

#pragma endregion