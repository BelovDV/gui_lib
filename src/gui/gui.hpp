#pragma once

#include "blocks.hpp"
#include "objects.hpp"

namespace gui {

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
	}

	template <class... Args>
	inline auto overlay(logic::BlockPtr&& background, Args&&... args) {
		auto result = std::make_unique<logic::Overlay>(std::move(background));
		detail::add(*result, std::move(args)...);
		return result;
	}

	inline auto split_holder(float v, logic::BlockPtr&& ptr,
		logic::details::split::Type t = logic::details::split::Type::Absolute)
	{
		return logic::details::split::Holder(t, v, std::move(ptr));
	}

	template <class... Args>
	inline auto split_vert(logic::BlockPtr&& background, Args&&... args) {
		auto result = std::make_unique<logic::SplitVert>(std::move(background));
		detail::add(*result, std::move(args)...);
		return result;
	}

	template <class... Args>
	inline auto split_hor(logic::BlockPtr&& background, Args&&... args) {
		auto result = std::make_unique<logic::SplitHor>(std::move(background));
		detail::add(*result, std::move(args)...);
		return result;
	}

	inline auto hightlighted(logic::BlockPtr&& off, logic::BlockPtr&& on) {
		return create<logic::Highlighted>(std::move(off), std::move(on));
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
		auto operator()(void (*action_on_pressing)(void* additional_data)) {
			return create<graphic::Button>(action_on_pressing);
		}

	private:
	};


}
