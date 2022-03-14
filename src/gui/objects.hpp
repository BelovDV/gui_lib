#pragma once

#include "basic.hpp"

#include <memory>
#include <functional>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace sf {
	class RectangleShape;
	class Sprite;
	class Text;
}

namespace gui {
	namespace graphic {
		using gui::basic::Block;
		using gui::basic::Vector2i;
		using gui::basic::Vector2u;

		class FillColor : public Block {
		public:
			FillColor(
				sf::RectangleShape& drawer,
				sf::Color fill_color,
				sf::Color outline_color = sf::Color::Transparent,
				float outline_thickness = 0
			) :
				drawer_(drawer),
				fill_color_(fill_color),
				outline_color_(outline_color),
				outline_thickness_(outline_thickness)
			{}
			virtual ~FillColor() = default;

		public:
			virtual void draw(sf::RenderTarget&) override;

		private:
			sf::RectangleShape& drawer_;
			sf::Color fill_color_;
			sf::Color outline_color_;
			float outline_thickness_;
		};

		class FillTexture : public Block {
		public:
			FillTexture(sf::Sprite& drawer, sf::IntRect texture_rect) :
				drawer_(drawer), texture_rect_(texture_rect)
			{}
			virtual ~FillTexture() = default;

		public:
			virtual void draw(sf::RenderTarget&) override;

		private:
			sf::Sprite& drawer_;
			sf::IntRect texture_rect_;
		};

		class Button : public Block {
		public:
			Button(std::function<void(void*)>&& action_on_pressing) :
				action_(std::move(action_on_pressing))
			{}
			virtual ~Button() = default;

		public:
			virtual void process_event(const sf::Event& event, void* data) override {
				if (event.type == sf::Event::EventType::MouseButtonPressed &&
					contains({ event.mouseButton.x, event.mouseButton.y }))
					action_(data);
			}
		private:
			std::function<void(void*)> action_;
		};

		class Text : public Block {
		public:
			Text(sf::Text& drawer, std::string&& text) :
				text_(std::move(text)), drawer_(drawer)
			{}
			virtual ~Text() = default;

		public:
			virtual void draw(sf::RenderTarget&) override;

		private:
			std::string text_;
			sf::Text& drawer_;
		};

	}
}
