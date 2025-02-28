#include <Hypo/3D.h>
#include <Hypo/Window.h>
#include "Hypo/System/Util/Log.h"
#include <bullet/btBulletDynamicsCommon.h>
#include "Hypo/3D/Scene/Scene.h"
#include "Hypo/3D/Scene/Entity.h"
#include "Hypo/System/Time/Clock.h"
#include "Hypo/System/Time/FpsCounter.h"

//static constexpr float WALK_SPEED = 20;
//static constexpr float RUN_SPEED = 60;
//static constexpr float TURN_SPEED = 1;
//float speed = WALK_SPEED;

//float currentSpeed;
//float currentTurnSpeed;

//if (Hypo::Input::IsKeyPressed(HYPO_KEY_LEFT_SHIFT)) {
//	speed = RUN_SPEED;
//}
//if (Hypo::Input::IsKeyPressed(HYPO_KEY_W)) {
//	currentSpeed = speed;
//}
//else if (Hypo::Input::IsKeyPressed(HYPO_KEY_S)) {
//	currentSpeed = -speed;
//}
//else {
//	currentSpeed = 0;
//}

//if (Hypo::Input::IsKeyPressed(HYPO_KEY_D)) {
//	currentTurnSpeed = -TURN_SPEED;
//}
//else if (Hypo::Input::IsKeyPressed(HYPO_KEY_A)) {
//	currentTurnSpeed = TURN_SPEED;
//}
//else {
//	currentTurnSpeed = 0;
//}

//auto& transform = std::get<1>(m_Components.front())->transform;
//transform.Rotate(glm::vec3(0.0f, currentTurnSpeed * dt, 0.f));

//float distance = currentSpeed * dt;
//float dx = distance * sin(transform.GetRotation().y);
//float dz = distance * cos(transform.GetRotation().y);
//if (dx || dz)
//{
//	//player->applyCentralForce({ dx * 20, 5, dz* 20 });	
//}


using namespace Hypo;
int main()
{

	Hypo::Log::Init();
	auto* window = Hypo::Window::Create(Hypo::WindowProps{ "ECS system" });

	Hypo::init(window->GetGladProc());
	Hypo::InitRenderer(window->GetGladProc());



	Hypo::Scene scene;
#if 0
	//btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	/////use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	//btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	/////btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	//btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	/////the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	//btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	//btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	//dynamicsWorld->setGravity(btVector3(0, -10, 0));

	//btAlignedObjectArray<btCollisionShape*> collisionShapes;

	//manager.AddSystem(new PhysicsSystem());
	//manager.AddSystem(new RenderSystem());
	//manager.AddSystem(new PlayerInputSystem());
	//
	//std::vector<Hypo::Vec3F> lightPositions = {
	//	{1.2f,1.1f,2.2f},
	//	{-3.f,1.5f,-3.1f},
	//	{3.4f,3.2f,-1.3f},
	//	{5.7f,2.1f,2.2f},
	//	{-2.1f,1.4f,-2.5f},
	//	{1.f,2.f,-2.5f}
	//};

	//for(int i = 0; i < 6; i++)
	//{
	//	Hypo::PointLight light;
	//	light.Position = lightPositions[i];


	//	auto* lightEntity = new Hypo::Entity(&manager);
	//	lightEntity->AddComponent<PointLightComponent>()->light = light;

	//	lightEntity->AddComponent<TransformComponent>()->transform.SetPosition(light.Position);
	//	lightEntity->AddComponent<Renderable>()->shader = meshShader;
	//	lightEntity->AddComponent<MeshComponent>()->mesh = Hypo::MeshFactory::CreateCube(Hypo::VertexPosTexNorm, 0.1);
	//	lightEntity->AddComponent<MaterialComponent>()->texture = wallTexture;

	//	manager.AddEntity(lightEntity);
	//}

	//auto* player = new Hypo::Entity(&manager);
	//{
	//	auto* playerTransformComponent = player->AddComponent<TransformComponent>();
	//	player->AddComponent<RigidBodyComponent>();
	//	player->AddComponent<InputComponent>();
	//	player->AddComponent<Renderable>()->shader = meshShader;
	//	player->AddComponent<MeshComponent>()->mesh = Hypo::MeshFactory::CreateCube(Hypo::VertexPosTexNorm, 0.5);
	//	player->AddComponent<MaterialComponent>()->texture = forestTexture;

	//	manager.AddEntity(player);
	//}



	//auto* plane = new Hypo::Entity(&manager);
	//{
	//	plane->AddComponent<TransformComponent>();
	//	plane->AddComponent<RigidBodyComponent>();
	//	plane->AddComponent<Renderable>()->shader = meshShader;
	//	plane->AddComponent<MeshComponent>()->mesh = Hypo::MeshFactory::CreatePlane(Hypo::VertexPosTexNorm, 4);
	//	plane->AddComponent<MaterialComponent>()->texture = wallTexture;

	//	manager.AddEntity(plane); 
	//}

	//Hypo::FollowCamera camera(player);
	//camera.SetViewRect({ Hypo::RectFromSize<float>(0,0,static_cast<float>(window->GetWidth()), static_cast<float>(window->GetHeight())) });
	//camera.SetFollowDistance(10.f);
	//
	//player->GetComponent<TransformComponent>()->transform.SetPosition({ 0, 4, 0 });
#endif


	auto cubeMesh = MeshFactory::CreateCube(VertexPosTexNorm);
	auto earthTexture = AssetManager::RetrieveTexture2DAsset("earth-texture", "res/textures/sun.jpg");
	auto wallTexture = AssetManager::RetrieveTexture2DAsset("wall-texture", "res/textures/wall.jpg");



	auto player = scene.CreateEntity("Player");
	player.AddComponent<MeshComponent>().Mesh = cubeMesh;
	player.AddComponent<Render3DComponent>();

	auto object = scene.CreateEntity("Object");
	object.AddComponent<MeshComponent>().Mesh = cubeMesh;
	object.AddComponent<MaterialComponent>().Texture = earthTexture;
	object.AddComponent<Render3DComponent>();
	object.GetComponent<TransformComponent>().SetPosition({ -1,1,-3 });

	auto plane = scene.CreateEntity("Object");
	plane.AddComponent<MeshComponent>().Mesh = cubeMesh;
	plane.AddComponent<MaterialComponent>().Texture = wallTexture;
	plane.AddComponent<Render3DComponent>();
	plane.GetComponent<TransformComponent>().SetPosition({ 0,-3,0 });
	plane.GetComponent<TransformComponent>().SetScaling({ 10.f,0.1f,10.f });

	{
		std::vector<Hypo::Vec3F> lightPositions = {
				{1.2f,1.1f,2.2f},
				{-3.f,1.5f,-3.1f},
				{3.4f,3.2f,-1.3f},
				{5.7f,2.1f,2.2f},
				{-2.1f,1.4f,-2.5f},
				{1.f,2.f,-2.5f}
		};

		for (int i = 0; i < lightPositions.size(); i++)
		{
			Hypo::PointLight light;
			light.Position = lightPositions[i];

			auto entity = scene.CreateEntity("Light" + std::to_string(i));
			entity.AddComponent<PointLightComponent>().Light = light;
			entity.AddComponent<MeshComponent>().Mesh = cubeMesh;
			entity.AddComponent<DebugRenderComponent>().Color = Vec4F{ 0.1f, 0.9f, 0.4f, 1.f };
			entity.GetComponent<TransformComponent>().SetScaling({ 0.1,0.1, 0.1 });
			entity.GetComponent<TransformComponent>().SetPosition(lightPositions[i]);
		}
	}

	FollowCamera camera(player);

	auto cameraEntity = scene.CreateEntity("Camera");
	cameraEntity.AddComponent<CameraComponent>(&camera);





	Clock fpsClock;
	FPSCounter frameCounter;
	window->EnableImGui();
	window->SetVSync(true);
	window->GetGraphicsContext()->EnableCullFace(CullFace::Back);
	bool running = true;
	while (running)
	{
		float dt = fpsClock.Reset().AsSeconds();
		frameCounter.Frame(dt);

		Event e;
		while (window->PollEvent(e))
		{
			if (e.type == EventType::WindowClose)
				goto quit;
		}
		RenderCommand::SetClearColor({ 0.2f,0.4f,0.2f,1.f });
		RenderCommand::Clear(RendererAPI::CLEAR_COLOR | RendererAPI::CLEAR_DEPTH);
		camera.SetViewRect(window->GetViewRect());
		camera.Update(dt);
		scene.Update(dt);


		scene.Render();

		//ImGui
		{
		window->BeginImGui();
		
		ImGui::Begin("fps");
		ImGui::Text("fps %i", frameCounter.CurrentFPS);
		ImGui::Text("peak fps %i", frameCounter.PeakFPS);
		ImGui::Text("low fps %i", frameCounter.LowFPS);
		ImGui::Text("average fps %i", frameCounter.AverageFPS);

		ImGui::Text("frame time %f", frameCounter.CurrentFrameTime);
		ImGui::Text("peak frame time %f", frameCounter.PeakFrameTime);
		ImGui::Text("low frame time %f", frameCounter.LowFrameTime);
		ImGui::Text("average frame time %f", frameCounter.AverageFrameTime);

		if (ImGui::Button("Reset"))
			frameCounter.Reset();
		ImGui::End();
		}

		window->EndImGui();

		window->Display();

	}
quit:
	window->DisableImGui();
	running = false;
	delete window;

	return 0;
}