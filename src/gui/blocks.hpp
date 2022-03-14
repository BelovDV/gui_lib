#pragma once

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
			Drawable(BlockPtr&& self) : self_(std::move(self)) {}
			virtual ~Drawable() = default;

		public:
			void draw_(sf::RenderTarget& target) {
				if (self_) self_->draw(target);
			}
			void process_event_(const sf::Event& event, void* data) {
				if (self_ && self_->requires_event(event))
					self_->process_event(event, data);
			}
			void update_(Vector2u size, Vector2i position, const void* data) {
				Block::update_(size, position);
				if (self_) self_->update(size, position, data);
			}

			virtual void draw(sf::RenderTarget& target) override {
				draw_(target);
			}
			virtual void process_event(const sf::Event& event, void* data) override {
				process_event_(event, data);
			}
			virtual void update(Vector2u size, Vector2i position, const void* data) override {
				update_(size, position, data);
			}

		protected:
			BlockPtr self_;
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
					Float,
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
			virtual ~SplitVert() = default;

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
			virtual ~SplitHor() = default;

		public:
			void clear() { descendants.clear(); }
			virtual void draw(sf::RenderTarget&) override;
			virtual void update(Vector2u size_, Vector2i position_, const void* data) override;
		};

		namespace details {
			namespace holder {
				struct Holder {
					Holder(BlockPtr&& ptr) : descendant(std::move(ptr)) {}
					BlockPtr descendant;
				};
			}
		}
		class Overlay : public Node<details::holder::Holder> {
		public:
			using Holder = details::holder::Holder;

		public:
			template <class... Args>
			Overlay(Args&&... args) :
				Node<Holder>(std::move(args)...)
			{}
			virtual ~Overlay() = default;

		public:
			void add(BlockPtr&& next) {
				descendants.emplace_back(std::move(next));
			}
			virtual void draw(sf::RenderTarget&) override;
			virtual void update(Vector2u size_, Vector2i position_, const void* data) override;
		};

		class Highlighted : public Block {
		public:
			Highlighted(BlockPtr&& off, BlockPtr&& on) :
				active_(std::move(off)), reserve_(std::move(on))
			{}
			virtual ~Highlighted() = default;

		public:
			virtual void draw(sf::RenderTarget& target) override {
				if (active_) active_->draw(target);
			}
			virtual void process_event(const sf::Event& event, void* data) override;
			virtual void update(Vector2u size, Vector2i position, const void* data) override;

		private:
			BlockPtr active_;
			BlockPtr reserve_;
			bool hightlighted{ false };
		};

		class Selector : public Block {
		public:
			Selector(Block* const* block_ptr) : block_(block_ptr) {}
			virtual ~Selector() = default;

		public:
			virtual void draw(sf::RenderTarget& target) override {
				if (*block_) (*block_)->draw(target);
			}
			virtual void process_event(const sf::Event& event, void* data) override {
				if (*block_) (*block_)->process_event(event, data);
			}
			virtual void update(Vector2u size, Vector2i position, const void* data) override;

		private:
			Block* const* block_;
		};

		class Padding : public Drawable {
		public:
			Padding(Vector2u padding, BlockPtr&& self) :
				Drawable(std::move(self)), padding_(padding)
			{}
			virtual ~Padding() = default;

		public:
			virtual void draw(sf::RenderTarget& target) override;
			virtual void update(Vector2u size, Vector2i position, const void* data) override;

		protected:
			Vector2u padding_;
		};

		class CenterVert : public Drawable {
		public:
			CenterVert(Vector2u under_size, BlockPtr&& self) :
				Drawable(std::move(self)), under_size_(under_size)
			{}
			virtual ~CenterVert() = default;

		public:
			virtual void draw(sf::RenderTarget& target) override;
			virtual void update(Vector2u size, Vector2i position, const void* data) override;

		protected:
			Vector2u under_size_;
		};

		class UnfoldingList : public Node<details::holder::Holder> {
		public:
			using Holder = details::holder::Holder;

		public:
			template <class... Args>
			UnfoldingList(Args&&... args) : Node<Holder>(std::move(args)...) {}
			virtual ~UnfoldingList() = default;

		public:
			virtual void draw(sf::RenderTarget&) override;
			virtual void process_event(const sf::Event& event, void* data) override;
			virtual void update(Vector2u size_, Vector2i position_, const void* data) override;

		protected:
			bool folded_{ true };
		};

		class Box : public Drawable {
		public:
			Box(Vector2u size, BlockPtr&& self) :
				Drawable(std::move(self)), fixed_size_(size)
			{}
			virtual ~Box() = default;

		public:
			virtual void update(Vector2u, Vector2i position, const void* data) override;

		protected:
			Vector2u fixed_size_;
		};

		class Tile : public Block {
		public:
			Tile(Vector2u tile_size) : tile_size_(tile_size) {}
			virtual ~Tile() = default;

		public:
			virtual void draw(sf::RenderTarget& target) override;
			virtual void process_event(const sf::Event& event, void* data) override;
			virtual void update(Vector2u size, Vector2i position, const void* data) override;
			void add(BlockPtr&& next) {
				descendants.emplace_back(std::move(next));
			}

		protected:
			Vector2u tile_size_;
			std::vector<BlockPtr> descendants;
		};

	}
}
