#pragma once
#include "Gameplay/StickCollection/StickCollectionController.h"

namespace Gameplay
{
	class GameplayController;

	class GameplayService
	{
	private:
		GameplayController* gameplay_controller;
		Collection::StickCollectionController* collection_controller;

		void initializeRandomSeed();

	public:
		GameplayService();
		~GameplayService();

		void initialize();
		void update();
		void render();

		void reset();

		int getNumberOfComparisons();
		int getNumberOfArrayAccess();
		int getDelayMilliseconds();
		int getNumberOfSticks();
		sf::String getTimeComplexity();
		Collection::SearchType getSearchType();

		void searchElement(Collection::SearchType search_type);
	};
}