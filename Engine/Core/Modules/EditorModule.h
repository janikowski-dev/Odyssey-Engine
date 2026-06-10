#pragma once

#include "../IModule.h"
#include "../Events/CreateEntity.h"
#include "../Events/SaveScene.h"
#include "../Events/LoadScene.h"
#include "../Events/Ping.h"
#include "../Components/Transform.h"
#include "../Components/MeshRenderer.h"
#include "../Components/Spin.h"

namespace Core
{
    class EditorModule final : public IModule
    {
    public:
        EditorModule() = default;
        ~EditorModule() override = default;

        void Init(const ApplicationConfig Config, Context& Context) override
        {
            Context.EditorBridge = MakeUnique<Editor::Bridge>();

		    Context.EditorBridge->On<Events::PingRequest, Events::PingResponse>(Events::PingKey, [](const Events::PingRequest&)
    	    {
    	        return Events::PingResponse();
    	    });
        
		    Context.EditorBridge->On<Events::CreateEntiryRequest, Events::CreateEntityResponse>(Events::CreateEntityKey, [&Context](const Events::CreateEntiryRequest&)
    	    {
	        	Core::ECS::Entity E = Context.World->Create();
	        	Context.World->Add<Components::Transform>(E, Components::Transform{ {-2, 0, 0}, {0, 0, 0}, {1, 1, 1} });
	        	Context.World->Add<Components::MeshRenderer>(E, Components::MeshRenderer{ {0.85f, 0.30f, 0.22f} });
	        	Context.World->Add<Components::Spin>(E, Components::Spin{ {0.0f, 0.8f, 0.0f} });
    	        return Events::CreateEntityResponse();
    	    });
        
		    Context.EditorBridge->On<Events::SaveSceneRequest, Events::SaveSceneResponse>(Events::SaveSceneKey, [&Context](const Events::SaveSceneRequest& Request)
    	    {
		    	Context.SceneSerializer->SaveToFile(*Context.World, Request.Path);
    	        return Events::SaveSceneResponse();
    	    });
        
		    Context.EditorBridge->On<Events::LoadSceneRequest, Events::LoadSceneResponse>(Events::LoadSceneKey, [&Context](const Events::LoadSceneRequest& Request)
    	    {
		    	Context.SceneSerializer->LoadFromFile(Request.Path, *Context.World);
    	        return Events::LoadSceneResponse();
    	    });

		    Context.EditorBridge->Start(Config.EditorPort);
        }

        void Tick(const Context& Context) override
        {
		    Context.EditorBridge->Tick();
        }
    };
}