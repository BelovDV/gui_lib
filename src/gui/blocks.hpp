#pragma once

#if 1
#define MAKE_LOG
#endif
#include "log.hpp"

#include "basic.hpp"

#include <vector>
#include <memory>

#include <SFML/Window/Event.hpp>

namespace gui {
	namespace logic {
		using gui::basic::Block;
		using gui::basic::Vector2i;
		using gui::basic::Vector2u;

		using BlockPtr = std::unique_ptr<Block>;

		class Drawable : public Block {
		public:
			Drawable(BlockPtr&& self) : self(std::move(self)) {}

		public:
			void draw_(sf::RenderTarget& target) {
				if (self) self->draw(target);
			}
			void process_event_(const sf::Event& event, void* data) {
				if (self && self->requires_event(event))
					self->process_event(event, data);
			}
			void update_(Vector2u size, Vector2i position, const void* data) {
				Block::update_(size, position);
				if (self) self->update(size, position, data);
			}

			virtual void draw(sf::RenderTarget& target) override {
				draw_(target);
			}
			virtual void process_event(const sf::Event& event, void* data) override {
				process_event_(event, data);
			}
			virtual void update(Vector2u size_, Vector2i position_, const void* data) override {
				update_(size_, position_, data);
			}

		protected:
			BlockPtr self;
		};

		template <class Holder>
		class Node : public gui::logic::Drawable {
		public:
			template <class... Args>
			Node(BlockPtr&& self, Args&&... args) : gui::logic::Drawable(std::move(self)) {
				descendants.reserve(sizeof...(args));
				generate(std::move(args)...);
			}
			virtual ~Node() = default;

		private:
			template <class Head, class... Holders>
			void generate(Head&& head, Holders&&... tail) {
				static_assert(std::is_same<Head, Holder>::value);
				descendants.emplace_back(std::move(head));
				generate(std::move(tail)...);
			}
			void generate() {}

		public:
			virtual void draw(sf::RenderTarget& target) override {
				Drawable::draw_(target);
				for (auto& next : descendants)
					next.descendant->draw(target);
			}
			virtual void process_event(const sf::Event& event, void* data) override {
				Drawable::process_event_(event, data);
				for (auto& next : descendants)
					if (next.descendant->requires_event(event))
						next.descendant->process_event(event, data);
			}
			virtual void update(Vector2u size, Vector2i position, const void* data) override {
				Drawable::update(size, position, data);
				for (auto& next : descendants)
					next.descendant->update(size, position, data);
			}
		public:
			void add(Holder&& next) {
				descendants.emplace_back(std::move(next));
			}

		protected:
			std::vector<Holder> descendants;
		};

		namespace details {
			namespace split {
				enum Type {
					Ratio,
					Absolute,
					Fill,
				};
				struct Holder {
					Holder(Type t, float v, BlockPtr&& ptr) :
						type(t), value(v), descendant(std::move(ptr))
					{}
					Type type;
					float value;
					BlockPtr descendant;
				};
			}
		}
		class SplitVert : public Node<details::split::Holder> {
		public:
			using Type = details::split::Type;
			using Holder = details::split::Holder;

		public:
			template <class... Args>
			SplitVert(Args&&... args) :
				Node<Holder>(std::move(args)...)
			{}

		public:
			void clear() { descendants.clear(); }
			virtual void draw(sf::RenderTarget&) override;
			virtual void update(Vector2u size_, Vector2i position_, const void* data) override;
		};
		class SplitHor : public Node<details::split::Holder> {
		public:
			using Type = details::split::Type;
			using Holder = details::split::Holder;

		public:
			template <class... Args>
			SplitHor(Args&&... args) :
				Node<Holder>(std::move(args)...)
			{}

		public:
			void clear() { descendants.clear(); }
			virtual void draw(sf::RenderTarget&) override;
			virtual void update(Vector2u size_, Vector2i position_, const void* data) override;
		};

		namespace details {
			namespace overlay {
				struct Holder {
					Holder(BlockPtr&& ptr) : descendant(std::move(ptr)) {}
					BlockPtr descendant;
				};
			}
		}
		class Overlay : public Node<details::overlay::Holder> {
		public:
			using Holder = details::overlay::Holder;

		public:
			template <class... Args>
			Overlay(Args&&... args) :
				Node<Holder>(std::move(args)...)
			{}

		public:
			void add(BlockPtr&& next) {
				descendants.emplace_back(std::move(next));
			}
			virtual void draw(sf::RenderTarget&) override;
			virtual void update(Vector2u size_, Vector2i position_, const void* data) override;
		};

		class Highlighted : public Block {
		public:
			Highlighted(BlockPtr&& off, BlockPtr&& on) : active_(std::move(off)), reserve_(std::move(on)) {}

		public:
			virtual void draw(sf::RenderTarget& target) override {
				if (active_) active_->draw(target);
			}
			virtual void process_event(const sf::Event& event, void* data) override {
				if (event.type == sf::Event::EventType::MouseMoved) {
					auto new_high = contains({ event.mouseMove.x, event.mouseMove.y });
					if (new_high != hightlighted) {
						hightlighted = new_high;
						std::swap(active_, reserve_);
					}
				}
				if (active_ && active_->requires_event(event))
					active_->process_event(event, data);
			}
			virtual void update(Vector2u size, Vector2i position, const void* data) override {
				Block::update_(size, position);
				if (active_) active_->update(size, position, data);
			}

		private:
			BlockPtr active_;
			BlockPtr reserve_;
			bool hightlighted{ false };
		};

		using Type = logic::details::split::Type;

	}
}