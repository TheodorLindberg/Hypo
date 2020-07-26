//	#include "Hypo/Hypo.h"
//#include "Hypo/Config.h"
//#include "imgui.h"
//#include "Hypo/System/Util/Log.h"
//#include "Hypo/Window/Window.h"
//
//
//#include <iostream>
//
//#include "Hypo/Graphics/Buffers.h"
//#include "Platform/OpenGL/OpenGLIndexBuffer.h"
//#include "Hypo/Graphics/Shader/Shader.h"
//#include "Hypo/Graphics/Shader/UniformBinder.h"
//#include "Hypo/Graphics/Texture/TextureAsset.h"
//#include "Hypo/Graphics/Texture/Texture.h"
//#include "Hypo/3D/Renderer/RendererAPI.h"
//#include "Hypo/3D/Renderer/RenderCommand.h"
//#include "Hypo/3D/Renderer/Renderer.h"
//#include "Hypo/3D/Model/Model.h"
//#include "Hypo/3D/Camera/CameraController.h"
//#include "Hypo/Graphics/BufferLayout.h"
//#include <glm/ext/scalar_constants.inl>
//#include "Hypo/3D/Asset/AssetManager.h"
//#include "Hypo/3D/Asset/Light.h"
//#include "Hypo/Graphics/NestedBufferLayout.h"
//#include <Hypo/Network/Packet/Packet.h>
//#include "SolarSystem.h"
//
//#include <Hypo/3D/ComponentModel/ComponentModel.h>
//
//#include <bullet/btBulletDynamicsCommon.h>
//#include <bullet/BulletCollision/CollisionShapes/btConvexShape.h>
//#include "Hypo/Window/Input.h"
//static constexpr float G = 1.f;
//
//class PlanetEntity : public Hypo::Entity
//{
//public:
//	PlanetEntity() = default;
//	~PlanetEntity() = default;
//};
//
//class TransformComponent : public Hypo::Transformable, public Hypo::Component
//{
//public:
//	TransformComponent() = default;
//	~TransformComponent() = default;
//
//	void Update(float dt) override {};
//	void Render() override {};
//};
//class MeshComponent : public Hypo::Component
//{
//public:
//	MeshComponent() = default;
//	~MeshComponent() = default;
//
//	void Update(float dt) override {};
//	void Render() override {};
//
//	Hypo::Mesh& GetMesh() { return m_Mesh; }
//	void SetMesh(Hypo::Mesh& mesh) { m_Mesh = mesh; }
//private:
//	Hypo::Mesh m_Mesh;
//};
//
//class TextureComponent : public Hypo::Component
//{
//public:
//	TextureComponent() = default;
//	~TextureComponent() = default;
//
//	void Update(float dt) override {};
//	void Render() override {};
//
//	Hypo::Texture2D::Ptr& GetTexture() { return m_Texture; }
//	void SetTexture(Hypo::Texture2D::Ptr& texture) { m_Texture = texture; }
//private:
//	Hypo::Texture2D::Ptr m_Texture;
//};
//
//class RenderComponent : public Hypo::Component
//{
//public:
//	RenderComponent() = default;
//	~RenderComponent() = default;
//
//	void Update(float dt) override {}
//	void Render() override
//	{
//		Hypo::Renderer::Submit(m_Shader, GetEntity()->GetComponent<TransformComponent>().GetTransform(), GetEntity()->GetComponent<MeshComponent>().GetMesh(), GetEntity()->GetComponent<TextureComponent>().GetTexture(), "texture1");
//	}
//
//	Hypo::Shader::Ptr& GetShader() { return m_Shader; }
//	void SetShader(Hypo::Shader::Ptr& shader) { m_Shader = shader; }
//private:
//	Hypo::Shader::Ptr m_Shader;
//};
//
//int main()
//{
//
//
//	int i;
//	///-----initialization_start-----
//
//	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
//	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
//
//	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
//	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
//
//	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
//	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
//
//	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
//	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
//
//	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
//
//	dynamicsWorld->setGravity(btVector3(0, -10, 0));
//
//	///-----initialization_end-----
//
//	//keep track of the shapes, we release memory at exit.
//	//make sure to re-use collision shapes among rigid bodies whenever possible!
//	btAlignedObjectArray<btCollisionShape*> collisionShapes;
//
//	///create a few basic rigid bodies
//
//	//the ground is a cube of side 100 at position y = -56.
//	//the sphere will hit it at y = -6, with center at -5
//	btRigidBody* ground;
//	btRigidBody* shape;
//	btRigidBody* shape2;
//	btRigidBody* player;
//	{
//		btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(3), btScalar(0), btScalar(3)));
//
//		collisionShapes.push_back(groundShape);
//
//		btTransform groundTransform;
//		groundTransform.setIdentity();
//		groundTransform.setOrigin(btVector3(0, 0, 0));
//
//		btScalar mass(0.);
//
//		//rigidbody is dynamic if and only if mass is non zero, otherwise static
//		bool isDynamic = (mass != 0.f);
//
//		btVector3 localInertia(0, 0, 0);
//		if (isDynamic)
//			groundShape->calculateLocalInertia(mass, localInertia);
//
//		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
//		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
//		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
//		btRigidBody* body = new btRigidBody(rbInfo);
//
//		//add the body to the dynamics world
//		dynamicsWorld->addRigidBody(body);
//		ground = body;
//	}
//
//	{
//		//create a dynamic rigidbody
//
//		//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
//		btCollisionShape* colShape = new btSphereShape(btScalar(1.));
//		collisionShapes.push_back(colShape);
//
//		/// Create Dynamic Objects
//		btTransform startTransform;
//		startTransform.setIdentity();
//
//		btScalar mass(1.f);
//
//		//rigidbody is dynamic if and only if mass is non zero, otherwise static
//		bool isDynamic = (mass != 0.f);
//
//		btVector3 localInertia(0, 0, 0);
//		if (isDynamic)
//			colShape->calculateLocalInertia(mass, localInertia);
//
//		startTransform.setOrigin(btVector3(2, 10, 0));
//
//		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
//		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
//		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
//		btRigidBody* body = new btRigidBody(rbInfo);
//		body->activate(true);
//
//		dynamicsWorld->addRigidBody(body);
//		shape = body;
//	}
//	{
//		//create a dynamic rigidbody
//
//		//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
//		btCollisionShape* colShape = new btSphereShape(btScalar(1.));
//		collisionShapes.push_back(colShape);
//
//		/// Create Dynamic Objects
//		btTransform startTransform;
//		startTransform.setIdentity();
//
//		btScalar mass(1.f);
//
//		//rigidbody is dynamic if and only if mass is non zero, otherwise static
//		bool isDynamic = (mass != 0.f);
//
//		btVector3 localInertia(0, 0, 0);
//		if (isDynamic)
//			colShape->calculateLocalInertia(mass, localInertia);
//
//		startTransform.setOrigin(btVector3(-2, 4, 0));
//
//		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
//		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
//		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
//		btRigidBody* body = new btRigidBody(rbInfo);
//		body->activate(true);
//
//		dynamicsWorld->addRigidBody(body);
//		shape2 = body;
//	}
//	{
//		//create a dynamic rigidbody
//
//		//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
//		btCollisionShape* colShape = new btSphereShape(btScalar(.5));
//		collisionShapes.push_back(colShape);
//
//		/// Create Dynamic Objects
//		btTransform startTransform;
//		startTransform.setIdentity();
//
//		btScalar mass(0.5f);
//
//		//rigidbody is dynamic if and only if mass is non zero, otherwise static
//		bool isDynamic = (mass != 0.f);
//
//		btVector3 localInertia(0, 0, 0);
//		if (isDynamic)
//			colShape->calculateLocalInertia(mass, localInertia);
//
//		startTransform.setOrigin(btVector3(0, 5, 0));
//
//		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
//		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
//		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
//		btRigidBody* body = new btRigidBody(rbInfo);
//		body->activate(true);
//
//		dynamicsWorld->addRigidBody(body);
//		body->setFriction(10.f);
//		player = body;
//	}
//	
//
//	///-----stepsimulation_end-----
//
//	//cleanup in the reverse order of creation/initialization
//
//	///-----cleanup_start-----
//
//
//
//
//
//
//	Hypo::Log::Init();
//	Hypo::Window* window = Hypo::Window::Create();
//	window->SetVSync(false);
//	Hypo::init(window->GetGladProc());
//	Hypo::InitRenderer(window->GetGladProc());
//
//	auto meshShader = Hypo::AssetManager::RetrieveShaderAsset("MeshShader", "res\\shaders\\lightShader.glsl");
//	
//	auto wallTexture = Hypo::AssetManager::RetrieveTexture2DAsset("brick_wall","res\\textures\\wall.jpg" );
//	auto forestTexture = Hypo::AssetManager::RetrieveTexture2DAsset("forrest", "res\\textures\\references-outerra2.jpg");
//
//	Hypo::FollowCamera camera;
//
//	camera.SetViewRect({ Hypo::RectFromSize<float>(0,0,static_cast<float>(window->GetWidth()), static_cast<float>(window->GetHeight())) });
//	camera.SetPosition({ -6,8, 0 });
//	camera.SetOrientation({ -30,0,0 });
//	window->SetVSync(true);
//
//
//	
//
//
//	Hypo::Mesh planeMesh = Hypo::MeshFactory::CreatePlane(Hypo::VertexPosTexNorm, 1.f);//Hypo::Mesh(vertexArray, Hypo::VertexTypes::VertexPosTexNorm);
//
//
//	std::vector<Hypo::Vec3F> lightPositions = {
//		{1.2f,1.1f,2.2f},
//		{-3.f,1.5f,-3.1f},
//		{3.4f,3.2f,-1.3f},
//		{5.7f,2.1f,2.2f},
//		{-2.1f,1.4f,-2.5f}
//	};
//
//	Hypo::SceneLights lights;
//	for(int i = 0; i < 5; i++)
//	{
//		Hypo::PointLight light;
//		light.Position = lightPositions[i];
//
//		lights.PointLights.push_back(light);
//	}
//
//
//
//	Hypo::Vec3F rotation = {glm::pi<float>() / 2,0,0};
//
//	window->EnableImGui();
//
//	Hypo::Texture2D::Ptr sunTexture = Hypo::AssetManager::RetrieveTexture2DAsset("sun", "res/textures/sun.jpg");
//	Hypo::Texture2D::Ptr earthTexture = Hypo::AssetManager::RetrieveTexture2DAsset("earth", "res/textures/earth.jpg");
//	Hypo::Texture2D::Ptr venusTexture = Hypo::AssetManager::RetrieveTexture2DAsset("venus", "res/textures/venus.jpg");
//
//	SolarSystem system;
//	system.AddPlanet({ 0,3,0 }, { 0,0,0 }, 2000, 0.2, sunTexture);
//	system.AddPlanet({ 1,3,0 }, { 5,0,45 },1.5 , 0.05, earthTexture);
//	system.AddPlanet({ 0,3,2 }, { 100,0,20 }, 3, 0.1, venusTexture);
//
//
//	Hypo::GameModel game;
//	auto* planet1 = new PlanetEntity();
//	auto* planet2 = new PlanetEntity();
//
//	auto cubeMesh = Hypo::MeshFactory::CreateCube(Hypo::VertexPosTexNorm);
//
//
//	planet1->GetComponent<TransformComponent>().SetPosition({ 2,2,2 });
//	planet2->GetComponent<TransformComponent>().SetPosition({ 3,2,2 });
//	planet1->GetComponent<MeshComponent>().SetMesh(cubeMesh);
//	planet2->GetComponent<MeshComponent>().SetMesh(cubeMesh);
//	planet1->GetComponent<TextureComponent>().SetTexture(sunTexture);
//	planet2->GetComponent<TextureComponent>().SetTexture(earthTexture);
//	planet1->GetComponent<RenderComponent>().SetShader(meshShader);
//	planet2->GetComponent<RenderComponent>().SetShader(meshShader);
//
//	game.AddEntity(planet1);
//	game.AddEntity(planet2);
//
//	Hypo::SimpleModel shapeModel = Hypo::SimpleModel(Hypo::MeshFactory::CreateUVSphere(Hypo::VertexPosTexNorm, 10,10,1.f),meshShader, wallTexture);
//	Hypo::SimpleModel playerModel = Hypo::SimpleModel(Hypo::MeshFactory::CreateCube(Hypo::VertexPosTexNorm, 0.5), meshShader, forestTexture);
//
//	float dt = 1.f/60;
//	bool running = true;
//	while (running)
//	{
//		Hypo::Event event;
//		while (window->PollEvent(event))
//		{
//			if (event.type == Hypo::EventType::WindowClose)
//			{
//				running = false;
//			}
//			if (event.type == Hypo::EventType::KeyPressed)
//			{
//				if (event.key.key == HYPO_KEY_F)
//				{
//					shape2->applyCentralForce((btVector3(btScalar(100.), btScalar(1), btScalar(0.))));
//				}
//			}
//		}
//		static constexpr float WALK_SPEED = 20;
//		static constexpr float RUN_SPEED = 60;
//		static constexpr float TURN_SPEED = 3.1;
//		float speed = WALK_SPEED;
//
//		float currentSpeed;
//		float currentTurnSpeed;
//
//		if (Hypo::Input::IsKeyPressed(HYPO_KEY_LEFT_SHIFT)) {
//			speed = RUN_SPEED;
//		}
//		if (Hypo::Input::IsKeyPressed(HYPO_KEY_W)) {
//			currentSpeed = speed;
//		}
//		else if (Hypo::Input::IsKeyPressed(HYPO_KEY_S)) {
//			currentSpeed = -speed;
//		}
//		else {
//			currentSpeed = 0;
//		}
//
//		if (Hypo::Input::IsKeyPressed(HYPO_KEY_D)) {
//			currentTurnSpeed = -TURN_SPEED;
//		}
//		else if (Hypo::Input::IsKeyPressed(HYPO_KEY_A)) {
//			currentTurnSpeed = TURN_SPEED;
//		}
//		else {
//			currentTurnSpeed = 0;
//		}
//
//
//		playerModel.Rotate(glm::vec3(0.0f, currentTurnSpeed* dt, 0.f));
//
//		float distance = currentSpeed * dt;
//		float dx = distance * sin(playerModel.GetRotation().y);
//		float dz = distance * cos(playerModel.GetRotation().y);
//		if(dx || dz)
//		{
//			player->applyCentralForce({ dx * 20, 5, dz* 20 });	
//		}
//		
//
//		if (!running)
//		{
//			break;
//		}
//		//Update
//
//
//
//		system.Update(dt);
//
//		playerModel.SetPosition({ player->getWorldTransform().getOrigin().x(),player->getWorldTransform().getOrigin().y(),player->getWorldTransform().getOrigin().z() });
//		player->getWorldTransform().setRotation({ playerModel.GetRotation().x, playerModel.GetRotation().y, playerModel.GetRotation().z });
//		//playerModel.SetRotation({player->getWorldTransform().getRotation().x(), player->getWorldTransform().getRotation().y(), player->getWorldTransform().getRotation().z()});
//
//
//		camera.UpdatePlayerPosition(playerModel.GetPosition());
//		camera.UpdatePlayerOrientation(playerModel.GetRotation());
//		camera.SetFollowDistance(5.f);
//		camera.Update(1.f / 60.f);
//
//		dynamicsWorld->stepSimulation(dt, 10);
//		
//
//
//		shapeModel.SetPosition({ shape->getWorldTransform().getOrigin().x(),shape->getWorldTransform().getOrigin().y(),shape->getWorldTransform().getOrigin().z() });
//
//		game.Update(1.f / 60.f); 
//		planet1->GetComponent<TransformComponent>().Move(Hypo::Vec3F{ 0.5,0,0 } *dt);
//
//		//Rendering
//		Hypo::RenderCommand::SetClearColor({ 0.5,0,0,1 });
//		Hypo::RenderCommand::Clear(Hypo::RendererAPI::CLEAR_COLOR | Hypo::RendererAPI::CLEAR_DEPTH);
//
//		
//		Hypo::Renderer::BeginScene(&camera, lights);
//		
//		window->GetGraphicsContext()->ResetState();
//		window->GetGraphicsContext()->EnableCullFace(Hypo::CullFace::Disabled);
//		window->GetGraphicsContext()->EnableDepthTest(true);
//
//		game.Render();
//
//		auto transform = Hypo::Transform::CreateTransform({ground->getWorldTransform().getOrigin().x(),ground->getWorldTransform().getOrigin().y(),ground->getWorldTransform().getOrigin().z()},{3,1,3}, rotation, {0,0,0});
//
//		Hypo::Renderer::Submit(meshShader, transform, planeMesh, wallTexture, "texture1");
//
//		Hypo::Renderer::Submit(shapeModel);
//		for (auto& light : lights.PointLights)
//		{
//			Hypo::Renderer::RenderCube(light.Position, { 0.1,0.1,0.1 }, { 1.f,0.5f,1.f, 1.f });
//		}
//		Hypo::Renderer::Submit(playerModel);
//		system.Render();
//
//		//print positions of all objects
//		for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
//		{
//			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
//			btRigidBody* body = btRigidBody::upcast(obj);
//			btTransform trans;
//			if (body && body->getMotionState())
//			{
//				body->getMotionState()->getWorldTransform(trans);
//			}
//			else
//			{
//				trans = obj->getWorldTransform();
//			}
//			printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
//
//			Hypo::Renderer::RenderCube({ float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()) }, { 0.1,0.1,0.1 }, Hypo::Vec4F{1,1,1,1}, trans.getRotation().x(), trans.getRotation().y(), trans.getRotation().z());
//
//		}
//
//
//		Hypo::Renderer::EndScene();
//		
//		window->BeginImGui();
//		window->EndImGui();
//		
//		
//		window->Display();
//	}
//	window->DisableImGui();
//
//
//	//remove the rigidbodies from the dynamics world and delete them
//	for (i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
//	{
//		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
//		btRigidBody* body = btRigidBody::upcast(obj);
//		if (body && body->getMotionState())
//		{
//			delete body->getMotionState();
//		}
//		dynamicsWorld->removeCollisionObject(obj);
//		delete obj;
//	}
//
//	//delete collision shapes
//	for (int j = 0; j < collisionShapes.size(); j++)
//	{
//		btCollisionShape* shape = collisionShapes[j];
//		collisionShapes[j] = 0;
//		delete shape;
//	}
//
//	//delete dynamics world
//	delete dynamicsWorld;
//
//	//delete solver
//	delete solver;
//
//	//delete broadphase
//	delete overlappingPairCache;
//
//	//delete dispatcher
//	delete dispatcher;
//
//	delete collisionConfiguration;
//
//	//next line is optional: it will be cleared by the destructor when the array goes out of scope
//	collisionShapes.clear();
//
//
//
//	Hypo::Log::Shutdown();
//	return 0;
//
//}
