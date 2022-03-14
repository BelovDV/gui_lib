#pragma once

#include "blocks.hpp"
#include "objects.hpp"

namespace gui {

	using logic::BlockPtr;
	using logic::details::split::Type;
	using basic::Vector2i;
	using basic::Vector2u;

	template<class B, class... Args>
	std::unique_ptr<B> create(Args&&... args) {
		return std::make_unique<B>(std::forward<Args>(args)...);
	}

	inline auto fill_color(
		sf::RectangleShape& drawer,
		sf::Color fill,
		sf::Color outline = {},
		float outline_thickness = {}
	) {
		return std::make_unique<graphic::FillColor>(
			drawer, fill, outline, outline_thickness);
	}

	namespace detail {
		template <class Holder, class Head>
		void add(logic::Node<Holder>& to_add, Head&& head) {
			to_add.add(Holder{ std::move(head) });
		}
		template <class Holder, class Head, class... Args>
		void add(logic::Node<Holder>& to_add, Head&& head, Args&&... tail) {
			to_add.add(Holder{ std::move(head) });
			add(to_add, std::move(tail)...);
		}
		template <class Block, class Head>
		void add_block(Block& to_add, Head&& head) {
			to_add.add(std::move(head));
		}
		template <class Block, class Head, class... Args>
		void add_block(Block& to_add, Head&& head, Args&&... tail) {
			to_add.add(std::move(head));
			add_block(to_add, std::move(tail)...);
		}
	}

	template <class... Args>
	inline auto overlay(BlockPtr&& background, Args&&... args) {
		auto result = std::make_unique<logic::Overlay>(std::move(background));
		detail::add(*result, std::move(args)...);
		return result;
	}

	inline auto split_holder(float v, BlockPtr&& ptr,
		logic::details::split::Type t = logic::details::split::Type::Absolute)
	{
		return logic::details::split::Holder(t, v, std::move(ptr));
	}

	template <class... Args>
	inline auto split_vert(BlockPtr&& background, Args&&... args) {
		auto result = std::make_unique<logic::SplitVert>(std::move(background));
		detail::add(*result, std::move(args)...);
		return result;
	}

	template <class... Args>
	inline auto split_hor(BlockPtr&& background, Args&&... args) {
		auto result = std::make_unique<logic::SplitHor>(std::move(background));
		detail::add(*result, std::move(args)...);
		return result;
	}

	template <class... Args>
	inline auto unfold_list(BlockPtr&& background, Args&&... args) {
		auto result = std::make_unique<logic::UnfoldingList>(std::move(background));
		detail::add(*result, std::move(args)...);
		return result;
	}

	inline auto hightlighted(BlockPtr&& off, BlockPtr&& on) {
		return create<logic::Highlighted>(std::move(off), std::move(on));
	}

	inline auto selector(basic::Block* const* block) {
		return create<logic::Selector>(block);
	}

	inline auto padding(Vector2u offset, BlockPtr&& block) {
		return create<logic::Padding>(offset, std::move(block));
	}

	inline auto center_vert(Vector2u size, BlockPtr&& block) {
		return create<logic::CenterVert>(size, std::move(block));
	}

	inline auto box(Vector2u size, BlockPtr&& block) {
		return create<logic::Box>(size, std::move(block));
	}

	template <class... Args>
	inline auto tile(Vector2u tile_size, BlockPtr&& block, Args&&... args) {
		auto result = create<logic::Tile>(tile_size);
		detail::add_block(*result, std::move(block), std::move(args)...);
		return result;
	}

	class FillColorGenerator {
	public:
		FillColorGenerator(sf::RectangleShape& drawer) : drawer_(drawer) {}

	public:
		auto operator()(sf::Color fill, sf::Color outline = {}, float thickness = {}) {
			return create<graphic::FillColor>(drawer_, fill, outline, thickness);
		}

	private:
		sf::RectangleShape& drawer_;
	};

	class FillTextureGenerator {
	public:
		FillTextureGenerator(sf::Sprite& drawer) : drawer_(drawer) {}

	public:
		auto operator()(sf::IntRect texture_rect) {
			return create<graphic::FillTexture>(drawer_, texture_rect);
		}

	private:
		sf::Sprite& drawer_;
	};

	class ButtonGenerator {
	public:
		ButtonGenerator() {}

	public:
		auto operator()(std::function<void(void*)> action_on_pressing,
			BlockPtr&& background)
		{
			return overlay(std::move(background),
				create<graphic::Button>(std::move(action_on_pressing))
			);
		}

	private:
	};

	class TextGenerator {
	public:
		TextGenerator(sf::Text& drawer) : drawer_(drawer) {}

	public:
		auto operator()(std::string&& text) {
			return create<graphic::Text>(drawer_, std::move(text));
		}

	private:
		sf::Text& drawer_;
	};

}
