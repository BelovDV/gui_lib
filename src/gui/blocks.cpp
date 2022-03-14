#if 0
#define MAKE_LOG
#endif
#include "log.hpp"

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
			next.descendant->update({ (unsigned)(next.value * size.x), size.y },
				position + delta, data);
			delta.x += (int)(next.value * size.x);
			break;
		case Type::Float:
			next.descendant->update({ size.x - delta.x, size.y }, position + delta, data);
			delta.x += (int)next.descendant->get_size().x;
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
			next.descendant->update({ size.x, (unsigned)(next.value * size.y), },
				position + delta, data);
			delta.y += (int)(next.value * size.y);
			break;
		case Type::Float:
			next.descendant->update({ size.x, size.y - delta.y }, position + delta, data);
			delta.y += (int)next.descendant->get_size().y;
		}
		if (delta.y >= (int)size.y) break;
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

void gui::logic::Highlighted::process_event(const sf::Event& event, void* data) {
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

void gui::logic::Highlighted::update(Vector2u size, Vector2i position, const void* data) {
	Block::update_(size, position);
	if (active_) active_->update(size, position, data);
}

void gui::logic::Selector::update(Vector2u size, Vector2i position, const void* data) {
	Block::update_(size, position);
	if (*block_) (*block_)->update(size_, position_, data);
}

void gui::logic::Padding::draw(sf::RenderTarget& target) {
	if (size_.x >= padding_.x * 2 && size_.y >= padding_.y * 2)
		Drawable::draw_(target);
}

void gui::logic::Padding::update(Vector2u size, Vector2i position, const void* data) {
	Drawable::update_(
		size - Vector2u{ padding_.x, padding_.y },
		position + Vector2i{ (int)padding_.x, (int)padding_.y }, data);
}

void gui::logic::CenterVert::draw(sf::RenderTarget& target) {
	if (self_ &&
		(self_->get_size().x <= size_.x) && (self_->get_size().y <= size_.y) &&
		(self_->get_position().x >= position_.x && (self_->get_position().y >= position_.y)))
		Drawable::draw_(target);
}

void gui::logic::CenterVert::update(Vector2u size, Vector2i position, const void* data) {
	Block::update_(size, position);
	if (self_) {
		auto under_size = under_size_;
		under_size.y = size_.y;
		self_->update(under_size, position + Vector2i{ (int)(size.x - under_size.x) / 2, 0 }, data);
		size_.y = self_ ? self_->get_size().y : 0;
	}
	else
		size_ = {};
}

void gui::logic::UnfoldingList::draw(sf::RenderTarget& target) {
	if (folded_) {
		if (self_) self_->draw(target);
	}
	else {
		for (auto& next : descendants) {
			next.descendant->draw(target);
		}
	}
}

void gui::logic::UnfoldingList::process_event(const sf::Event& event, void* data) {
	if (folded_)
		Node<details::holder::Holder>::process_event_(event, data);
	else
		for (auto& next : descendants)
			next.descendant->process_event(event, data);
	if (event.type == sf::Event::EventType::MouseButtonPressed &&
		contains({ event.mouseButton.x, event.mouseButton.y })) {
		folded_ = !folded_;
	}
}

void gui::logic::UnfoldingList::update(Vector2u size, Vector2i position, const void* data) {
	Block::update_(size, position);
	if (folded_) {
		if (self_) self_->update(size, position, data);
		size_ = self_ ? self_->get_size() : Vector2u{};
	}
	else {
		Vector2u new_size{};
		for (auto& next : descendants) {
			next.descendant->update(size, position, data);
			position.y += next.descendant->get_size().y;
			if (size.y < next.descendant->get_size().y) break;
			else size.y -= next.descendant->get_size().y;
			new_size.x = std::max(new_size.x, next.descendant->get_size().x);
			new_size.y += next.descendant->get_size().y;
		}
		size_ = new_size;
	}
}

void gui::logic::Box::update(Vector2u, Vector2i position, const void* data) {
	Drawable::update_(fixed_size_, position, data);
	size_ = self_ ? self_->get_size() : Vector2u{};
}

void gui::logic::Tile::draw(sf::RenderTarget& target) {
	Vector2i delta{};
	for (auto& next : descendants) {
		if (delta.x + tile_size_.x > size_.x && delta.y + tile_size_.y > size_.y) break;
		next->draw(target);
		if (delta.x + 2 * tile_size_.x <= size_.x) delta.x += tile_size_.x;
		else {
			delta.x = 0;
			delta.y += tile_size_.y;
		}
	}
}

void gui::logic::Tile::process_event(const sf::Event& event, void* data) {
	for (auto& next : descendants) next->process_event(event, data);
}

void gui::logic::Tile::update(Vector2u size, Vector2i position, const void* data) {
	Block::update_(size, position);
	Vector2i delta{};
	for (auto& next : descendants) {
		if (delta.x + tile_size_.x > size.x && delta.y + tile_size_.y > size.y) break;
		next->update(tile_size_, position + delta, data);
		if (delta.x + 2 * tile_size_.x <= size.x) delta.x += tile_size_.x;
		else {
			delta.x = 0;
			delta.y += tile_size_.y;
		}
	}
}
