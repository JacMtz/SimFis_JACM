#include <iostream>
#include <Box2d/Box2d.h>


int main() {

    b2Vec2 gravity(0.0f, -1.62f);
    b2World world(gravity);

    // Definimos y creamos el ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);

    // Definimos y creamos el objeto

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 15.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Definimos y creamos la figura

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 15600.0f;
    fixtureDef.friction = 0.0f;

    body->CreateFixture(&fixtureDef);

    // Definimos la frecuencia de muestreo del entorno

    body->CreateFixture(&fixtureDef);
    float timeStep = 1.0f / 1.0f;

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    // Actualización de la smulación

    for (int32 i = 0; i < 8; ++i)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    }
}
