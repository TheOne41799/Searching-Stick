#include "Gameplay/StickCollection/StickCollectionController.h"
#include "Gameplay/StickCollection/StickCollectionModel.h"
#include "Gameplay/StickCollection/StickCollectionView.h"
#include "Gameplay/StickCollection/Stick.h"
#include "Global/ServiceLocator.h"


namespace Gameplay
{
	namespace Collection
	{
		using namespace UI::UIElement;
		using namespace Global;


		Gameplay::Collection::StickCollectionContoller::StickCollectionContoller()
		{
			collection_view = new StickCollectionView();
			collection_model = new StickCollectionModel();
			initializeSticksArray();
		}

		Gameplay::Collection::StickCollectionContoller::~StickCollectionContoller()
		{
			destroy();
		}

		void Gameplay::Collection::StickCollectionContoller::initializeSticks()
		{
			float rectangle_width = calculateStickWidth();

			for (int i = 0; i < collection_model->number_of_elements; i++)
			{
				float rectangle_height = calculateStickHeight(i);

				sf::Vector2f rectangle_size = sf::Vector2f(rectangle_width, rectangle_height);

				sticks[i]->stick_view->initialize(rectangle_size, sf::Vector2f(0, 0), 0, collection_model->element_color);
			}
		}

		float Gameplay::Collection::StickCollectionContoller::calculateStickWidth()
		{
			float total_space = static_cast<float>(ServiceLocator::getInstance()->getGraphicService()->getGameWindow()->getSize().x);

			float total_spacing = collection_model->space_percentage * total_space;

			float space_between = total_spacing / (collection_model->number_of_elements - 1);
			collection_model->setElementSpacing(space_between);

			float remaining_space = total_space - total_spacing;

			float rectangle_width = remaining_space / collection_model->number_of_elements;

			return rectangle_width;
		}

		float Gameplay::Collection::StickCollectionContoller::calculateStickHeight(int array_pos)
		{
			return (static_cast<float>(array_pos + 1) / collection_model->number_of_elements) * collection_model->max_element_height;
		}

		void Gameplay::Collection::StickCollectionContoller::updateSticksPosition()
		{
			for (int i = 0; i < sticks.size(); i++)
			{
				float x_position = (i * sticks[i]->stick_view->getSize().x) + ((i + 1) * collection_model->elements_spacing);

				float y_position = collection_model->element_y_position - sticks[i]->stick_view->getSize().y;

				sticks[i]->stick_view->setPosition(sf::Vector2f(x_position, y_position));
			}
		}

		void Gameplay::Collection::StickCollectionContoller::initialize()
		{

			collection_model->initialize();
			initializeSticks();

			reset();
		}

		void Gameplay::Collection::StickCollectionContoller::update()
		{
			collection_view->update();

			for (int i = 0; i < sticks.size(); i++)
				sticks[i]->stick_view->update();
		}

		void Gameplay::Collection::StickCollectionContoller::render()
		{
			collection_view->render();
			for (int i = 0; i < sticks.size(); i++)
				sticks[i]->stick_view->render();
		}

		void Gameplay::Collection::StickCollectionContoller::initializeSticksArray()
		{
			for (int i = 0; i < collection_model->number_of_elements; i++)
				sticks.push_back(new Stick(i));
		}

		void Gameplay::Collection::StickCollectionContoller::resetSticksColor()
		{
			for (int i = 0; i < sticks.size(); i++)
				sticks[i]->stick_view->setFillColor(collection_model->element_color);
		}

		void Gameplay::Collection::StickCollectionContoller::reset()
		{
			updateSticksPosition();
			resetSticksColor();
		}

		void Gameplay::Collection::StickCollectionContoller::destroy()
		{
			for (int i = 0; i < sticks.size(); i++) delete(sticks[i]);
			sticks.clear();

			delete (collection_view);
			delete (collection_model);
		}

		/*void Gameplay::Collection::StickCollectionContoller::searchElement(SearchType search_type)
		{

		}*/

		SearchType Gameplay::Collection::StickCollectionContoller::getSearchType()
		{
			return search_type;
		}

		int Gameplay::Collection::StickCollectionContoller::getNumberOfSticks()
		{
			return collection_model->number_of_elements;
		}
	}
}