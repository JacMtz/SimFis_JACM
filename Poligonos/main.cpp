#include <Box2D/Box2D.h>
#include <iostream>

int main() {
    // Crear un mundo Box2D
    b2Vec2 gravity(0.0f, -9.81f); // Gravedad hacia abajo
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);

    // Triángulo Rectángulo
    b2Vec2 verticesTriangulo[3];
    verticesTriangulo[0].Set(0.0f, 0.0f);
    verticesTriangulo[1].Set(1.0f, 0.0f);
    verticesTriangulo[2].Set(0.0f, 1.5f);
    b2BodyDef bodyDef1;
    bodyDef1.position.Set(2.0f, 3.0f); // Posición del triángulo rectángulo
    b2Body* triangulo = world.CreateBody(&bodyDef1);
    b2PolygonShape polygonShape1;
    polygonShape1.Set(verticesTriangulo, 3);
    triangulo->CreateFixture(&polygonShape1, 1.0f);

    // Cuadrado
    b2Vec2 verticesCuadrado[4];
    verticesCuadrado[0].Set(0.0f, 0.0f);
    verticesCuadrado[1].Set(1.0f, 0.0f);
    verticesCuadrado[2].Set(1.0f, 1.0f);
    verticesCuadrado[3].Set(0.0f, 1.0f);
    b2BodyDef bodyDef2;
    bodyDef2.position.Set(5.0f, 3.0f); // Posición del cuadrado
    b2Body* cuadrado = world.CreateBody(&bodyDef2);
    b2PolygonShape polygonShape2;
    polygonShape2.Set(verticesCuadrado, 4);
    cuadrado->CreateFixture(&polygonShape2, 1.0f);

    // Crear el cuerpo del pentágono
    b2Vec2 verticesPentagono[5];
    for (int i = 0; i < 5; ++i) {
        float angle = i * 2 * b2_pi / 6.0f; // Ángulo igualmente espaciado
        verticesPentagono[i].Set(2.0f * cos(angle), 2.0f * sin(angle)); // Radio de 2 unidades
    }
    b2BodyDef bodyDef3;
    bodyDef1.position.Set(2.0f, 8.0f); // Posición del pentágono
    b2Body* pentagono = world.CreateBody(&bodyDef1);
    b2PolygonShape polygonShape3;
    polygonShape1.Set(verticesPentagono, 5);
    pentagono->CreateFixture(&polygonShape1, 1.0f);

    // Definir vértices para el hexágono
    b2Vec2 verticesHexagono[6];
    for (int i = 0; i < 6; ++i) {
        float angle = i * 2 * b2_pi / 6.0f; // Ángulo igualmente espaciado
        verticesHexagono[i].Set(2.0f * cos(angle), 2.0f * sin(angle)); // Radio de 2 unidades
    }

    // Crear el cuerpo del hexágono
    b2BodyDef bodyDef4;
    bodyDef2.position.Set(6.0f, 8.0f); // Posición del hexágono
    b2Body* hexagono = world.CreateBody(&bodyDef2);
    b2PolygonShape polygonShape4;
    polygonShape2.Set(verticesHexagono, 6);
    hexagono->CreateFixture(&polygonShape2, 1.0f);

    // Definir vértices para el octágono
    b2Vec2 verticesOctagono[8];
    for (int i = 0; i < 8; ++i) {
        float angle = i * 2 * b2_pi / 8.0f; // Ángulo igualmente espaciado
        verticesOctagono[i].Set(2.0f * cos(angle), 2.0f * sin(angle)); // Radio de 2 unidades
    }

    // Crear el cuerpo del octágono
    b2BodyDef bodyDef5;
    bodyDef3.position.Set(10.0f, 8.0f); // Posición del octágono
    b2Body* octagono = world.CreateBody(&bodyDef3);
    b2PolygonShape polygonShape5;
    polygonShape3.Set(verticesOctagono, 8);
    octagono->CreateFixture(&polygonShape3, 1.0f);

}