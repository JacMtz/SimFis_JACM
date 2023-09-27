#include <iostream>
#include <Box2D/Box2D.h>

int main() {

    //Definimos la gravedad
    b2Vec2 gravity(0.0f, -9.81f);
    b2World world(gravity);

    //Definimos el cuerpo
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    b2Body* ballBody = world.CreateBody(&ballBodyDef);

    //Definimos la figura del cuerpo
    b2CircleShape ballShape;
    ballShape.m_radius = 1.0f;

    b2FixtureDef ballFixtureDef;
    ballFixtureDef.shape = &ballShape;

    ballBody->CreateFixture(&ballFixtureDef);

    // Asignamos el angulo(x°) y la velocidad(m/s)
    float initialAngleDegrees = 75.0f;
    float initialVelocity = 5.56f;

    //Transformamos el angulo en radianes
    float initialAngleRadians = initialAngleDegrees * b2_pi / 180.0f;

    //Calculamos los componentes del vector velocidad
    float initialVelocityX = initialVelocity * cos(initialAngleRadians);
    float initialVelocityY = initialVelocity * sin(initialAngleRadians);

    //Creamos el vecto velocidad
    b2Vec2 initialVelocityVector(initialVelocityX, initialVelocityY);

    //Asignamos el vector velocidad
    ballBody->SetLinearVelocity(initialVelocityVector);

    // Definimos la frecuencia de muestreo del entorno
    float timeStep = 1.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    //Imprimimos los valores que se irán actualizando en la simulación

    for (int32 i = 0; i < 10; ++i) {
        world.Step(timeStep, velocityIterations, positionIterations);

        b2Vec2 position = ballBody->GetPosition();

        std::cout << "Time: " << i * timeStep << "s, Position: (" << position.x << ", " << position.y << ")" << std::endl;
    }

}
