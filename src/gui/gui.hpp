#pragma once

#include "blocks.hpp"
#include "objects.hpp"

namespace gui {

	template<class B, class... Args>
	std::unique_ptr<B> create(Args&&... args) {
		return std::make_unique<B>(std::forward<Args>(args)...);
	}

	


}
