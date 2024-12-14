#include "../include/Gameplay/GameplayService.h"
#include "Gameplay/GameplayController.h"


namespace Gameplay
{
	GameplayService::GameplayService()
	{
		gameplay_controller = new GameplayController();
		collection_controller = new StickCollectionContoller();
	}

	GameplayService::~GameplayService()
	{
		delete (gameplay_controller);
		delete(collection_controller);
	}

	void GameplayService::initialize()
	{
		gameplay_controller->initialize();
		collection_controller->initialize();
	}

	void GameplayService::update()
	{
		gameplay_controller->update();
		collection_controller->update();
	}

	void GameplayService::render()
	{
		gameplay_controller->render();
		collection_controller->render();
	}

	void GameplayService::reset()
	{
		gameplay_controller->reset();
		collection_controller->reset();
	}
}
