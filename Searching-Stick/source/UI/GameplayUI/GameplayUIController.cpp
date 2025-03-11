#include "UI/GameplayUI/GameplayUIController.h"
#include "Global/Config.h"
#include "Global/ServiceLocator.h"
#include "Gameplay/GameplayService.h"
#include "Sound/SoundService.h"
#include "Main/GameService.h"
#include "Gameplay/StickCollection/StickCollectionModel.h"

namespace UI
{
    namespace GameplayUI
    {
        using namespace Main;
        using namespace Sound;
        using namespace UIElement;
        using namespace Global;
        using namespace Gameplay;
        using namespace Collection;

        GameplayUIController::GameplayUIController()
        {
            createButton();
            createTexts();
        }

        GameplayUIController::~GameplayUIController()
        {
            destroy();
        }

        void GameplayUIController::initialize()
        {
            initializeButton();
            initializeTexts();
            updateSearchTypeText();
        }

        void GameplayUIController::createButton()
        {
            menu_button = new ButtonView();
        }

        void GameplayUIController::createTexts()
        {
            search_type = new TextView();
            number_of_comparisons = new TextView();
            number_of_array_access = new TextView();

            number_of_sticks = new TextView();
            delay = new TextView();
            time_complexity = new TextView();

        }

        void GameplayUIController::initializeButton()
        {
            menu_button->initialize("Menu Button",
                Config::menu_button_path,
                menu_button_width, menu_button_height,
                sf::Vector2f(menu_button_x_position, menu_button_y_position));

            registerButtonCallback();
        }

        void GameplayUIController::initializeTexts()
        {
            search_type->initialize("Search Type  :  Linear Search", sf::Vector2f(search_type_text_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size);
            number_of_comparisons->initialize("Comparisons  :  0", sf::Vector2f(comparisons_text_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size);
            number_of_array_access->initialize("Array Access  :  0", sf::Vector2f(array_access_text_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size);


            number_of_sticks->initialize("Number of Sticks  :  0", sf::Vector2f(num_sticks_text_x_position, text_y_pos2), FontType::BUBBLE_BOBBLE, font_size);


            delay->initialize("Delay  :  0 ms", sf::Vector2f(delay_text_x_position, text_y_pos2), FontType::BUBBLE_BOBBLE, font_size);


            time_complexity->initialize("Time Complexity  :  O(n)", sf::Vector2f(time_complexity_text_x_position, text_y_pos2), FontType::BUBBLE_BOBBLE, font_size);
        }

        void GameplayUIController::update()
        {
            menu_button->update();
            updateSearchTypeText();
            updateComparisonsText();
            updateArrayAccessText();

            updateNumberOfSticksText();
            updateDelayText();
            updateTimeComplexityText();

        }

        void GameplayUIController::render()
        {
            menu_button->render();
            search_type->render();
            number_of_comparisons->render();
            number_of_array_access->render();

            number_of_sticks->render();
            delay->render();
            time_complexity->render();
        }

        void GameplayUIController::show()
        {
            menu_button->show();
            search_type->show();
            number_of_comparisons->show();
            number_of_array_access->show();

            number_of_sticks->show();
            delay->show();
            time_complexity->show();
        }

        void GameplayUIController::updateSearchTypeText()
        {
            Gameplay::Collection::SearchType new_search_type = ServiceLocator::getInstance()->getGameplayService()->getSearchType();


            switch (new_search_type)
            {
            case::Gameplay::Collection::SearchType::LINEAR_SEARCH:
                search_type->setText("Linear Search");
                break;

            case::Gameplay::Collection::SearchType::BINARY_SEARCH:
                search_type->setText("Binary Search");
                break;
            }
            search_type->update();

        }

        void GameplayUIController::updateComparisonsText()
        {
            int number_of_comp = ServiceLocator::getInstance()->getGameplayService()->getNumberOfComparisons();;
            sf::String comparisons_string = "Comparisons  :  " + std::to_string(number_of_comp);

            number_of_comparisons->setText(comparisons_string);
            number_of_comparisons->update();
        }

        void GameplayUIController::updateArrayAccessText()
        {
            int number_of_access = ServiceLocator::getInstance()->getGameplayService()->getNumberOfArrayAccess();;
            sf::String array_access_string = "Array Access  :  " + std::to_string(number_of_access);

            number_of_array_access->setText(array_access_string);
            number_of_array_access->update();
        }

        void GameplayUIController::updateNumberOfSticksText()
        {
            int num_sticks = ServiceLocator::getInstance()->getGameplayService()->getNumberOfSticks();
            sf::String sticks_string = "Number of Sticks  :  " + std::to_string(num_sticks);

            number_of_sticks->setText(sticks_string);
            number_of_sticks->update();
        }

        void GameplayUIController::updateDelayText()
        {
            int delay_in_milliseconds = ServiceLocator::getInstance()->getGameplayService()->getDelayMilliseconds();
            sf::String delay_string = "Delay (ms)  :  " + std::to_string(delay_in_milliseconds);

            delay->setText(delay_string);
            delay->update();
        }

        void GameplayUIController::updateTimeComplexityText()
        {
            sf::String time_complexity_variable = ServiceLocator::getInstance()->getGameplayService()->getTimeComplexity();
            sf::String time_complexity_string = "Time Complexity  :  " + time_complexity_variable;

            time_complexity->setText(time_complexity_string);
            time_complexity->update();
        }

        void GameplayUIController::menuButtonCallback()
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            ServiceLocator::getInstance()->getGameplayService()->reset();
            GameService::setGameState(GameState::MAIN_MENU);
        }

        void GameplayUIController::registerButtonCallback()
        {
            menu_button->registerCallbackFuntion(std::bind(&GameplayUIController::menuButtonCallback, this));
        }

        void GameplayUIController::destroy()
        {
            delete (menu_button);
            delete (search_type);
            delete (number_of_comparisons);
            delete (number_of_array_access);
        }
    }
}