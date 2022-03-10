#include "blocks.hpp"

void gui::logic::SplitVert::draw(sf::RenderTarget& target) {
	Drawable::draw_(target);
	Vector2i delta;
	for (auto& next : descendants) {
		if (delta.x + next.descendant->get_size().x > size_.x) break;
		next.descendant->draw(target);
		delta.x += next.descendant->get_size().x;
	}
}

void gui::logic::SplitVert::update(Vector2u size, Vector2i position, const void* data) {
	Drawable::update_(size, position, data);
	Vector2i delta;
	for (auto& next : descendants) {
		switch (next.type) {
		case Type::Absolute:
			next.descendant->update({ (unsigned)next.value, size.y }, position + delta, data);
			delta.x += next.value;
			break;
		case Type::Fill:
			next.descendant->update({ size.x - delta.x, size.y }, position + delta, data);
			delta.x = size.x;
			break;
		case Type::Ratio:
			next.descendant->update({ (unsigned)(next.value * size.x), size.y }, position + delta, data);
			delta.x += (int)(next.value * size.x);
			break;
		}
		if (delta.x >= (int)size.x) break;
	}
}

void gui::logic::SplitHor::draw(sf::RenderTarget& target) {
	Drawable::draw_(target);
	Vector2i delta;
	for (auto& next : descendants) {
		if (delta.y + next.descendant->get_size().y > size_.y) break;
		next.descendant->draw(target);
		delta.y += next.descendant->get_size().y;
	}
}

void gui::logic::SplitHor::update(Vector2u size, Vector2i position, const void* data) {
	Drawable::update_(size, position, data);
	Vector2i delta;
	for (auto& next : descendants) {
		switch (next.type) {
		case Type::Absolute:
			next.descendant->update({ size.x, (unsigned)next.value }, position + delta, data);
			delta.y += next.value;
			break;
		case Type::Fill:
			next.descendant->update({ size.x, size.y - delta.y }, position + delta, data);
			delta.y = size.y;
			break;
		case Type::Ratio:
			next.descendant->update({ size.x, (unsigned)(next.value * size.y), }, position + delta, data);
			delta.y += (int)(next.value * size.y);
			break;
		}
		if (delta.x >= (int)size.x) break;
	}
}

void gui::logic::Overlay::draw(sf::RenderTarget& target) {
	Drawable::draw_(target);
	for (auto& next : descendants) {
		next.descendant->draw(target);
	}
}

void gui::logic::Overlay::update(Vector2u size, Vector2i position, const void* data) {
	Drawable::update_(size, position, data);
	for (auto& next : descendants)
		next.descendant->update(size, position, data);
}
