#include <SFML/Graphics.hpp>
#include <string>
#include <Box2D/Box2D.h>

//Escala para manejar la renderización con respecto a las medidas de box2d
constexpr float SCALE = 30.0f;

//Clase para plataformas
class Platform{
public:
    //Constructor para los parametros de las medidas de la plataforma, asi como para la asignación de tipo de cuerpo,
    // si es que rotará, el angulo en el que se encontrará y su densidad
    Platform(b2World &world, float x, float y, float hx, float hy, int dynamic = 0, bool rotate = false, float angle = 0.f, float density =1.0) {
        b2BodyDef platformBodydef;
        if (rotate == true){
            platformBodydef.fixedRotation = true;
        }
        platformBodydef.position.Set(x / SCALE, y / SCALE);
        platformBodydef.angle = angle * b2_pi / 180;

        switch (dynamic) {
            case 0:
                platformBodydef.type = b2_staticBody;
                break;
            case 1:
                platformBodydef.type = b2_dynamicBody;
                break;
            case 2:
                platformBodydef.type = b2_kinematicBody;
                break;
        }
        body = world.CreateBody(&platformBodydef);

        b2PolygonShape shape;
        shape.SetAsBox((hx / 2) / SCALE, (hy / 2) / SCALE);


        b2FixtureDef platformFixtureDef;
        platformFixtureDef.shape = &shape;
        platformFixtureDef.density = density;
        body->CreateFixture(&platformFixtureDef);
        box.setSize(sf::Vector2f(hx, hy));
        box.setOrigin(hx/2, hy/2);
        box.setFillColor(sf::Color::White);
        box.setRotation(body->GetAngle() * 180.0f/ b2_pi);

    }

    //Funcion updaate para actualizar por frame lo que pasa en pantalla
    void update() {
        box.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        box.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    //Función draw para renderizar la figura
    void draw(sf::RenderWindow &win) const {
        win.draw(box);
    }

    //Getter del cuerpo del objeto
    b2Body *getBody() {
        return body;
    }

private:
    sf::RectangleShape box;
    b2Body *body;
};

//Clase para bolas
class Ball {
public:
 //Constructor de la clase, que pide parametros para el tamaño de la fugura, asi como valores para RGB, densidad y fricción
    Ball(b2World &world, float x, float y, float h, float w, float radius, float r, float g, float b, float density =1.0, float friction = 0.005f) {
        b2BodyDef projectileBodyDef;
        projectileBodyDef.position.Set(x / SCALE, y/ SCALE);
        projectileBodyDef.type = b2_dynamicBody;
        body = world.CreateBody(&projectileBodyDef);

        b2CircleShape projectileBox;
        projectileBox.m_p.Set((h/2)/SCALE, (w/2)/SCALE);
        projectileBox.m_radius = radius/SCALE;

        b2FixtureDef projectileFixtureDef;
        projectileFixtureDef.shape = &projectileBox;
        projectileFixtureDef.density = density;
        projectileFixtureDef.friction = friction;
        body->CreateFixture(&projectileFixtureDef);

        ball.setRadius(radius);
        ball.setFillColor(sf::Color(r,g,b));
        ball.setOrigin(0.f, 0.f);
    }

    //Funcion updaate para actualizar por frame lo que pasa en pantalla
    void update() {
        ball.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        ball.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    //Función draw para renderizar la figura
    void draw(sf::RenderWindow &win) const {
        win.draw(ball);
    }

    //Función para volver a poner las bolas donde comenzaron
    void resetPosition() {
        body->SetTransform(origin, body->GetAngle());
        body->SetLinearVelocity(b2Vec2(0,0));
    }

    //Getter del cuerpo del objeto
    b2Body *getBody() {
        return body;
    }

private:
    sf::CircleShape ball;
    b2Body *body;
    b2Vec2 origin;
};
int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Rube Goldberg");

    b2Vec2 gravity(0.0f, 0.05f);
    b2World world(gravity);

    //Bolas
    Ball ball1 (world, 50, 10, 10,10,10,255,0,0);
    Ball ball2 (world, 345, 130, 10, 10, 10,0,255, 0);
    Ball ball3 (world, 830, 130, 10, 10 , 10, 0, 0, 255);

    //Plataformas
    Platform platform1(world, 50 , 100, 80, 10, 0, false ,20);
    Platform platform2(world, 220, 200, 10, 10, 0);
    Platform platform3(world, 345, 150, 10, 10, 0);
    Platform platform4(world, 500,185,150,10,0);
    Platform platform5(world, 830, 150, 10, 10, 0);
    Platform platform6(world, 720,185,80,10,0);
    Platform platform7(world, 500,350,150,10,0);
    Platform platform8(world, 350, 645, 10, 120, 0);
    Platform platform9(world, 530, 710, 500, 10, 0);
    Platform platform10(world,100,810,80,10,0);

    //Plataformas dynamicas
    Platform platform_dyn1(world, 220, 190, 150, 10, 1);
    Platform platform_dyn2(world, 345, 140, 150, 10, 1);
    Platform platform_dyn3(world, 830, 140, 150, 10, 1);

    //Polea
    Platform platformPul1(world, 900,215,80,10,1, true);
    Platform platformPul2(world, 650, 240, 80, 10, 1, true);
    Platform point1(world, 900, 50, 10, 10,0);
    Platform point2(world, 650, 50, 10, 10,0);

    //revoluciones
    Platform platformRev(world, 320, 350, 10, 10,0);
    Platform platformRev1(world, 370, 370, 30, 10,1);
    Platform platformRev2(world, 100, 350, 10, 10,0);
    Platform platformRev3(world, 150, 370, 30, 10,1);

    //Prismaticas
    Platform platformPris1(world, 650, 645, 10, 120, 0);
    Platform platformPris2(world, 680, 645, 10, 120, 0);

    //Intento de gear
    Platform platform(world, 665, 500, 10 , 50, 1);
    Platform gear(world,600,630,40,10,1);
    Platform gear1(world, 100, 800, 80, 10, 1);

//Joints

//Polea
    b2PulleyJointDef jointPul;
    jointPul.Initialize(platformPul1.getBody(), platformPul2.getBody(), point1.getBody()->GetWorldCenter(), point2.getBody()->GetWorldCenter(),
                        platformPul1.getBody()->GetWorldCenter(), platformPul2.getBody()->GetWorldCenter(), 1);
    world.CreateJoint(&jointPul);

    //Revolutes
    b2RevoluteJointDef jointRev;
    jointRev.Initialize(platformRev1.getBody(),platformRev.getBody(),platformRev.getBody()->GetWorldCenter());
    b2RevoluteJoint* jointre = (b2RevoluteJoint*)world.CreateJoint(&jointRev);

    b2RevoluteJointDef jointRev1;
    jointRev1.Initialize(platformRev3.getBody(),platformRev2.getBody(),platformRev3.getBody()->GetWorldCenter());
    b2RevoluteJoint* jointre1 = (b2RevoluteJoint*)world.CreateJoint(&jointRev1);

    b2RevoluteJointDef jointRev2;
    jointRev2.Initialize(gear.getBody(), platform.getBody(), gear.getBody()->GetWorldCenter());
    b2RevoluteJoint* jointr = (b2RevoluteJoint*)world.CreateJoint(&jointRev2);

// Distancia
    b2DistanceJointDef jointDis;
    jointDis.Initialize(platformRev.getBody(),platformRev1.getBody(),platformRev.getBody()->GetWorldCenter(),platformRev1.getBody()->GetWorldCenter());
    world.CreateJoint(&jointDis);

    b2DistanceJointDef jointDis1;
    jointDis1.Initialize(gear.getBody(),platform9.getBody(),gear.getBody()->GetWorldCenter(),platform9.getBody()->GetWorldCenter());
    world.CreateJoint(&jointDis1);

//Prismaticas

    b2PrismaticJointDef jointPris;
    jointPris.Initialize(gear1.getBody(), platform.getBody(), platform.getBody()->GetWorldCenter(), b2Vec2(1, 0));
    jointPris.enableLimit = true;
    jointPris.lowerTranslation = -20.0f;
    jointPris.upperTranslation = 1.0f;
    b2PrismaticJoint* jointp = (b2PrismaticJoint*)world.CreateJoint(&jointPris);

    //Gear
    b2GearJointDef jointGear;
    jointGear.bodyA = jointp->GetBodyA();
    jointGear.bodyB = jointr->GetBodyA();
    jointGear.joint1 = jointp;
    jointGear.joint2 = jointr;
    jointGear.ratio = 1.0f;
    world.CreateJoint(&jointGear);
  //Evento de ventana
    while (window.isOpen()) {
        sf::Event event{};

        //Aplicar impulso angular a una plataforma de revolucion para que gire con rapidez constante
        platformRev1.getBody()->ApplyAngularImpulse(.1f, true);
        while (window.pollEvent(event)) {

            //Al presionar R resetear posición de las bolas
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                ball1.resetPosition();
                ball2.resetPosition();
                ball3.resetPosition();
            }

            //Al presionar Z cerrar ventana
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                window.close();
            }
        }

        //Frecuencia

        world.Step(1 / 60.f, 8, 3);

        ball1.update();
        platform_dyn1.update();
        platform1.update();
        platform2.update();
        platform_dyn2.update();
        platform3.update();
        ball2.update();
        platform4.update();
        platformPul1.update();
        platformPul2.update();
        platform5.update();
        platform_dyn3.update();
        ball3.update();
        platform6.update();
        platform7.update();
        platformRev.update();
        platformRev1.update();
        platformRev2.update();
        platformRev3.update();
        platformPris1.update();
        platform9.update();
        platform8.update();
        gear.update();
        gear1.update();
        platform.update();
        platformPris2.update();

        window.clear();

        ball1.draw(window);
        platform_dyn1.draw(window);
        platform1.draw(window);
        platform2.draw(window);
        platform_dyn2.draw(window);
        platform3.draw(window);
        ball2.draw(window);
        platform4.draw(window);
        platformPul1.draw(window);
        platformPul2.draw(window);
        platform5.draw(window);
        platform_dyn3.draw(window);
        ball3.draw(window);
        platform6.draw(window);
        platform7.draw(window);
        platformRev.draw(window);
        platformRev1.draw(window);
        platformRev2.draw(window);
        platformRev3.draw(window);
        platformPris1.draw(window);
        platform9.draw(window);
        platform8.draw(window);
        gear.draw(window);
        gear1.draw(window);
        platform.draw(window);
        platformPris2.draw(window);

        window.display();
    }
    return 0;
}