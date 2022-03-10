#include "menu.hpp"
#include "window.hpp"

#ifndef PATH_SAVING
#define PATH_SAVING "./tmp/data"
#endif

#ifndef PATH_RESOURSE
#define PATH_RESOURSE "./data"
#endif

int main() {
	Settings settings(PATH_SAVING "/settings", PATH_RESOURSE);
	Graphic::Window window(settings);
	Menu menu(settings);

	sf::Event event;
	bool active = true;
	while (active) {
		window.draw(menu);
		while (window.poll_event(event))
			active &= menu.process_event(event);
	}
}
