#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <Box2D/b2_time_of_impact.h>
#include <iostream>

// Factor de conversión de metros a píxeles (ajusta según tu escala)
const float METERS_TO_PIXELS = 50.0f;

int main() {
    // Configuración de SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bala");
    window.setFramerateLimit(60);

    // Configuración de Box2D
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

    // Crear un suelo estático
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 0.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(1000000000.0f, 1.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);

    // Crear el proyectil
    b2BodyDef projectileBodyDef;
    projectileBodyDef.type = b2_dynamicBody;
    projectileBodyDef.position.Set(0.0f, 5.0f);
    b2Body* projectileBody = world.CreateBody(&projectileBodyDef);

    b2PolygonShape projectileBox;
    projectileBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef projectileFixtureDef;
    projectileFixtureDef.shape = &projectileBox;
    projectileFixtureDef.density = 1.0f;
    projectileFixtureDef.friction = 0.5f;
    projectileBody->CreateFixture(&projectileFixtureDef);

    // Inicializar la ventana de SFML
    sf::CircleShape projectileShape(10.0f);
    projectileShape.setFillColor(sf::Color::Red);

    // Setear la velocidad inicial del proyectil

    projectileBody->SetLinearVelocity(b2Vec2(5.0f, 0.0f));

    // Calcular el tiempo de impacto con el suelo usando el método de barrido (Sweep)
    b2DistanceInput distInput;
    distInput.proxyA.Set(&projectileBox, 0);
    distInput.proxyB.Set(&groundBox, 0);
    distInput.transformA = projectileBody->GetTransform();
    distInput.transformB = groundBody->GetTransform();
    distInput.useRadii = true;

    b2DistanceOutput distOutput;
    b2SimplexCache cache;

    // reset cache
    cache.count = 0;

    // calculate the distance
    b2Distance(&distOutput, &cache, &distInput);

    // print the calculated distance
    printf("Distance between bodies: %4.2f m\n", distOutput.distance);

    b2Sweep sweepA;
    sweepA.c0 = projectileBody->GetPosition();
    sweepA.a0 = projectileBody->GetAngle();
    sweepA.c = projectileBody->GetWorldCenter() + projectileBody->GetLinearVelocity();
    sweepA.a = sweepA.a0;
    sweepA.localCenter.SetZero();

    b2Sweep sweepB;
    sweepB.c0 = groundBody->GetPosition();
    sweepB.a0 = groundBody->GetAngle();
    sweepB.c = groundBody->GetWorldCenter() + groundBody->GetLinearVelocity();
    sweepB.a = sweepB.a0;
    sweepB.localCenter.SetZero();

    b2TOIInput toiInput;
    toiInput.proxyA.Set(&projectileBox, 0);
    toiInput.proxyB.Set(&groundBox, 0);
    toiInput.sweepA = sweepA;
    toiInput.sweepB = sweepB;


    b2TOIOutput toiOutput{};
    b2TimeOfImpact(&toiOutput, &toiInput);

    float timeOfImpact = toiOutput.t;
    printf("Time of impact: %4.2f s\n", timeOfImpact);

    // Bucle principal de SFML
    while (window.isOpen()) {
        // Manejar eventos de SFML
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Simular el mundo Box2D (avanzar un paso de tiempo)
        world.Step(1.0f / 60.0f, 6, 2);

        // Actualizar la posición y la apariencia del proyectil en SFML
        b2Vec2 position = projectileBody->GetPosition();
        projectileShape.setPosition(position.x * METERS_TO_PIXELS, window.getSize().y - position.y * METERS_TO_PIXELS);

        // Limpiar la ventana
        window.clear(sf::Color::White);

        // Dibujar el proyectil en la ventana de SFML
        window.draw(projectileShape);

        // Mostrar la ventana
        window.display();
    }

    return 0;
}
