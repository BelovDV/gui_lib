#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace sf {
	class RenderTarget;
	class RenderStates;
	class Event;
}

namespace gui {
	namespace basic {

		using sf::Vector2i;
		using sf::Vector2u;

		class Block {
		public:
			Block(Vector2u size = {}, Vector2i position = {}) :
				size_(size), position_(position)
			{}
			virtual ~Block() = default;

		public:
			auto get_size() const { return size_; }
			auto get_position() const { return position_; }
			void update_(Vector2u size, Vector2i position) {
				size_ = size;
				position_ = position;
			}
			bool contains(Vector2i coord) const {
				return
					coord.x >= position_.x && coord.x < position_.x + (int)size_.x &&
					coord.y >= position_.y && coord.y < position_.y + (int)size_.y;
			}

			virtual void draw(sf::RenderTarget&) {}
			virtual bool requires_event(const sf::Event& event) {
				return event.type & event_mask_;
			}
			virtual void process_event(const sf::Event&, void* /*data*/) {}
			virtual void update(Vector2u size, Vector2i position, const void* /*data*/ = nullptr) {
				update_(size, position);
			}

		public:
			unsigned event_mask_ =
				sf::Event::EventType::MouseMoved |
				sf::Event::EventType::MouseButtonPressed
				;
			Vector2u size_;
			Vector2i position_;
		};

	}
}
