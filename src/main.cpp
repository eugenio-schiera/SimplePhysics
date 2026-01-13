#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath> // Serve per sqrt e pow

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::CircleShape shape;
    float radius; 

    Particle(float x, float y, float velX, float velY) {
        position = {x, y};
        velocity = {velX, velY};
        radius = 10.f; // Raggio fisso per ora

        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Cyan);
        shape.setOrigin(radius, radius); // Centro nel mezzo
        shape.setPosition(position);
    }
};

// Funzione helper per il prodotto scalare (Dot Product)
// Restituisce un numero che indica quanto due vettori "puntano nella stessa direzione"
float dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

void solveCollisions(std::vector<Particle>& particles) {
    // Controllo lo stato di ogni particella esistente nello spazio
    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            
            Particle& p1 = particles[i];
            Particle& p2 = particles[j];

            sf::Vector2f delta = p1.position - p2.position;
            float dist2 = delta.x * delta.x + delta.y * delta.y;
            float minDistance = p1.radius + p2.radius;

            if (dist2 < minDistance * minDistance) {
                float dist = std::sqrt(dist2);
                if (dist == 0.0f) continue;

                // --- 1. RISOLUZIONE STATICA (Separazione) ---
                float overlap = minDistance - dist;
                sf::Vector2f n = delta / dist; // Normale di collisione
                
                // Spostiamo le particelle per separarle (metà ciascuna)
                p1.position += n * (overlap * 0.5f);
                p2.position -= n * (overlap * 0.5f);

                // --- 2. RISOLUZIONE DINAMICA (Impulso Reale) ---
                
                // Calcoliamo la velocità relativa (p1 vista da p2)
                sf::Vector2f relVel = p1.velocity - p2.velocity;

                // Calcoliamo la velocità lungo la normale (Dot Product)
                float velAlongNormal = dotProduct(relVel, n);

                // Se le velocità stanno già separando le particelle, non fare nulla!
                // Questo risolve il problema delle particelle che si "incollano"
                if (velAlongNormal > 0) continue;

                // Coefficiente di restituzione (Elasticità)
                // 1.0 = Rimbalzo perfetto (Superball)
                // 0.5 = Rimbalzo smorzato (Palla da tennis)
                // 0.0 = Si spiaccicano (Palla di fango)
                float e = 0.75f; 

                // Calcolo dell'impulso scalare (formula semplificata per masse uguali)
                // J = -(1 + e) * velAlongNormal
                // Diviso 2 perché in teoria sarebbe diviso (1/m1 + 1/m2)
                float j = -(1.0f + e) * velAlongNormal;
                j /= 2.0f; // Assumendo massa = 1 per entrambe

                // Applichiamo l'impulso
                sf::Vector2f impulse = n * j;
                p1.velocity += impulse;
                p2.velocity -= impulse;
            }
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Physics Engine: Collisions");
    window.setFramerateLimit(60);

    std::vector<Particle> particles;
    sf::Vector2f gravity(0.0f, 1000.0f);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                float mouseX = static_cast<float>(event.mouseButton.x);
                float mouseY = static_cast<float>(event.mouseButton.y);
                particles.emplace_back(mouseX, mouseY, (rand()%200)-100.f, (rand()%200)-100.f);
            }
        }

        sf::Time dtTime = clock.restart();
        float dt = dtTime.asSeconds();

        // --- UPDATE ---
        for (auto& p : particles) {
            p.velocity += gravity * dt;
            p.position += p.velocity * dt;

            // Muri (tieni anche il codice vecchio dei muri qui!)
            if (p.position.y > 590.f) { p.position.y = 590.f; p.velocity.y *= -0.7f; }
            if (p.position.x < 10.f) { p.position.x = 10.f; p.velocity.x *= -0.7f; }
            if (p.position.x > 790.f) { p.position.x = 790.f; p.velocity.x *= -0.7f; }
            
            p.shape.setPosition(p.position);
        }

        // --- RISOLVI COLLISIONI ---
        // Chiamiamolo DOPO aver mosso tutto, ma PRIMA di disegnare
        solveCollisions(particles);
        // NOTA: Dopo solveCollisions, le posizioni sono cambiate.
        // Dobbiamo aggiornare la grafica un'altra volta per evitare "tremolii" visivi
        for (auto& p : particles) p.shape.setPosition(p.position);

        window.clear(sf::Color::Black);
        for (const auto& p : particles) window.draw(p.shape);
        window.display();
    }
    return 0;
}