#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "Gameplay/StickCollection/StickCollectionModel.h"
#include <thread>

namespace Gameplay
{
	namespace Collection
	{
		class StickCollectionView;
		class StickCollectionModel;
		enum class SearchType;
		struct Stick;

		class StickCollectionController
		{
		private:
			StickCollectionView* collection_view;
			StickCollectionModel* collection_model;
			Stick* stick_to_search;
			std::thread search_thread;

			std::vector<Stick*> sticks;
			Collection::SearchType search_type;

			int number_of_comparisons;
			int number_of_array_access;
			int current_operation_delay;

			void initializeSticks();
			float calculateStickWidth();
			void updateSticksPosition();
			void shuffleSticks();
			void resetSearchStick();
			void resetSticksColor();
			void processLinearSearch();
			void initializeSticksArray();
			void resetVariables();
			void joinThreads(); 
			void processSearchThreadState();
			float calculateStickHeight(int array_pos);

		public:
			StickCollectionController();
			~StickCollectionController();

			void initialize();
			void update();
			void render();

			void reset();

			int getNumberOfComparisons();
			int getNumberOfArrayAccess();
			int getDelayMilliseconds();

			void searchElement(SearchType search_type);

			SearchType getSearchType();
			int getNumberOfSticks();
		};
	}
}