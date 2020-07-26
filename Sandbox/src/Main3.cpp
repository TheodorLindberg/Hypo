#include <Hypo/3D.h>
#include <Hypo/Window.h>
#include "Hypo/System/Util/Log.h"
#include "Hypo/3D/ECS/Components.h"
#include <bullet/btBulletDynamicsCommon.h>

using namespace Hypo;
class PerspectiveCameraComponent : public Hypo::Component
{
public:
	void Init(void* pData) override {}
	static constexpr Hypo::ComponentID COMPONENT_ID = 5;

	Hypo::PerspectiveCamera camera;
};

class FollowCameraComponent : public Hypo::Component
{
public:
	void Init(void* pData) override {}
	static constexpr Hypo::ComponentID COMPONENT_ID = 7;

	Hypo::Entity* target;

	float followDistance;
	float angleAroundPlayer;

};

class PointLightComponent : public Hypo::Component
{
public:
	void Init(void* pData) override {}
	static constexpr Hypo::ComponentID COMPONENT_ID = 6;

	Hypo::PointLight light;
};

class PhysicsSystem : public Hypo::ComponentSystem<Hypo::RigidBodyComponent, Hypo::TransformComponent>
{
public:
	void Update(float dt) override
	{
		for (auto& component : m_Components)
		{
			auto it = 10;
		}
	}
	void Render() override
	{
		
	}
};
class RenderSystem : public Hypo::ComponentSystem<Hypo::Renderable, Hypo::TransformComponent, Hypo::MeshComponent, Hypo::MaterialComponent>
{
public:
	void Update(float dt) override
	{

	}

	void Render() override
	{
		for (auto& component : m_Components)
		{
			auto [render, transform, mesh, material] = component;
			Hypo::Renderer::Submit(render->shader, transform->transform.GetTransform(), mesh->mesh, material->texture, "texture1");
		}
	}
};

class PlayerInputSystem : public Hypo::ComponentSystem<Hypo::InputComponent, Hypo::TransformComponent>
{
public:
	void Update(float dt) override
	{

		static constexpr float WALK_SPEED = 20;
		static constexpr float RUN_SPEED = 60;
		static constexpr float TURN_SPEED = 1;
		float speed = WALK_SPEED;

		float currentSpeed;
		float currentTurnSpeed;

		if (Hypo::Input::IsKeyPressed(HYPO_KEY_LEFT_SHIFT)) {
			speed = RUN_SPEED;
		}
		if (Hypo::Input::IsKeyPressed(HYPO_KEY_W)) {
			currentSpeed = speed;
		}
		else if (Hypo::Input::IsKeyPressed(HYPO_KEY_S)) {
			currentSpeed = -speed;
		}
		else {
			currentSpeed = 0;
		}

		if (Hypo::Input::IsKeyPressed(HYPO_KEY_D)) {
			currentTurnSpeed = -TURN_SPEED;
		}
		else if (Hypo::Input::IsKeyPressed(HYPO_KEY_A)) {
			currentTurnSpeed = TURN_SPEED;
		}
		else {
			currentTurnSpeed = 0;
		}

		auto& transform = std::get<1>(m_Components.front())->transform;
		transform.Rotate(glm::vec3(0.0f, currentTurnSpeed * dt, 0.f));

		float distance = currentSpeed * dt;
		float dx = distance * sin(transform.GetRotation().y);
		float dz = distance * cos(transform.GetRotation().y);
		if (dx || dz)
		{
			//player->applyCentralForce({ dx * 20, 5, dz* 20 });	
		}
	}

	void Render() override
	{
	}
};


int main()
{
	
	Hypo::EntityManager manager;
	Hypo::Log::Init();
	auto* window = Hypo::Window::Create(Hypo::WindowProps{"ECS system"});

	window->SetVSync(false);
	Hypo::init(window->GetGladProc());
	Hypo::InitRenderer(window->GetGladProc());

	

	auto meshShader = Hypo::AssetManager::RetrieveShaderAsset("MeshShader", "res\\shaders\\lightShader.glsl");
	auto wallTexture = Hypo::AssetManager::RetrieveTexture2DAsset("brick_wall","res\\textures\\wall.jpg" );
	auto forestTexture = Hypo::AssetManager::RetrieveTexture2DAsset("forrest", "res\\textures\\references-outerra2.jpg");

	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -10, 0));

	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	manager.AddSystem(new PhysicsSystem());
	manager.AddSystem(new RenderSystem());
	manager.AddSystem(new PlayerInputSystem());
	
	std::vector<Hypo::Vec3F> lightPositions = {
		{1.2f,1.1f,2.2f},
		{-3.f,1.5f,-3.1f},
		{3.4f,3.2f,-1.3f},
		{5.7f,2.1f,2.2f},
		{-2.1f,1.4f,-2.5f},
		{1.f,2.f,-2.5f}
	};

	for(int i = 0; i < 6; i++)
	{
		Hypo::PointLight light;
		light.Position = lightPositions[i];


		auto* lightEntity = new Hypo::Entity(&manager);
		lightEntity->AddComponent<PointLightComponent>()->light = light;

		lightEntity->AddComponent<TransformComponent>()->transform.SetPosition(light.Position);
		lightEntity->AddComponent<Renderable>()->shader = meshShader;
		lightEntity->AddComponent<MeshComponent>()->mesh = Hypo::MeshFactory::CreateCube(Hypo::VertexPosTexNorm, 0.1);
		lightEntity->AddComponent<MaterialComponent>()->texture = wallTexture;

		manager.AddEntity(lightEntity);
	}

	auto* player = new Hypo::Entity(&manager);
	{
		auto* playerTransformComponent = player->AddComponent<TransformComponent>();
		player->AddComponent<RigidBodyComponent>();
		player->AddComponent<InputComponent>();
		player->AddComponent<Renderable>()->shader = meshShader;
		player->AddComponent<MeshComponent>()->mesh = Hypo::MeshFactory::CreateCube(Hypo::VertexPosTexNorm, 0.5);
		player->AddComponent<MaterialComponent>()->texture = forestTexture;

		manager.AddEntity(player);
	}



	auto* plane = new Hypo::Entity(&manager);
	{
		plane->AddComponent<TransformComponent>();
		plane->AddComponent<RigidBodyComponent>();
		plane->AddComponent<Renderable>()->shader = meshShader;
		plane->AddComponent<MeshComponent>()->mesh = Hypo::MeshFactory::CreatePlane(Hypo::VertexPosTexNorm, 4);
		plane->AddComponent<MaterialComponent>()->texture = wallTexture;

		manager.AddEntity(plane); 
	}

	Hypo::FollowCamera camera(player);
	camera.SetViewRect({ Hypo::RectFromSize<float>(0,0,static_cast<float>(window->GetWidth()), static_cast<float>(window->GetHeight())) });
	camera.SetFollowDistance(10.f);
	
	player->GetComponent<TransformComponent>()->transform.SetPosition({ 0, 4, 0 });

	bool running = true;
	float dt = 1.f / 60.f;
	while (running)
	{
		Hypo::Event event;
		while (window->PollEvent(event))
		{
			if (event.type == Hypo::EventType::WindowClose)
			{
				running = false;
				goto end;
			}
		}


		if (!running)
		{
			break;
		}


		manager.Update(dt);

		camera.Update(1.f / 60.f);

		Hypo::RenderCommand::SetClearColor({ 0.1,0.3,0.1,1.f });
		Hypo::RenderCommand::Clear(Hypo::RendererAPI::CLEAR_COLOR | Hypo::RendererAPI::CLEAR_DEPTH);

		window->GetGraphicsContext()->ResetState();
		window->GetGraphicsContext()->EnableCullFace(Hypo::CullFace::Disabled);
		window->GetGraphicsContext()->EnableDepthTest(true);

		/*LIGHTS*/
		Hypo::SceneLights lights;

		for(auto& pointLight : manager.GetAllComponentOfType<PointLightComponent>())
		{
			lights.PointLights.push_back(dynamic_cast<PointLightComponent*>(pointLight)->light);
		}

		/*RENDER SCENE*/
		Hypo::Renderer::BeginScene(&camera, lights);

		manager.Render();

		Hypo::Renderer::EndScene();

		window->Display();
	}

	end:

	delete window;


}