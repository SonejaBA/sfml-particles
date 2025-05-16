#include "Engine.h"


Engine::Engine() {
	m_Window.create(VideoMode(1280, 720), "Particles");
}

void Engine::run() {
	Clock clock;

	// test code
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen()) {
		float time = clock.restart().asSeconds();
		input();
		update(time);
		draw();
	}
}

void Engine::input() {
	Event event;
	while (m_Window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			m_Window.close();
		}

		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
			m_Window.close();
		}

		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
			for (int i = 0; i < NUM_OF_PARTICLES; i++) {
				Vector2i mousePos = Mouse::getPosition(m_Window);
				Particle particle(m_Window, (rand() % (250 - 150) ) + 150, mousePos);
				m_particles.push_back(particle);
			}
		}
	}
}


void Engine::update(float dtAsSeconds){

	std::vector<Particle>::iterator iterator = m_particles.begin();

	while (iterator != m_particles.end()) {
		if (iterator->getTTL() > 0) {
			iterator->update(dtAsSeconds);
			iterator++;
		}
		else {
			iterator = m_particles.erase(iterator);
		}
	}
}

void Engine::draw() {
	m_Window.clear();
	for (int i = 0; i < m_particles.size(); i++) {
		m_Window.draw(m_particles.at(i));

	}
	m_Window.display();
}
