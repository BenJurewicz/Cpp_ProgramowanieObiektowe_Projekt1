#ifndef PROJEKT1CPP_CREATURE_H
#define PROJEKT1CPP_CREATURE_H

#include "../Point.h"
#include "../world.h"

class World;

class Creature : public std::enable_shared_from_this<Creature> {
protected:
    bool isAlive;
    int age;
    int strength;
    int initiative;
    Point<int> position;
    World *world;

    Creature(int strength, int initiative, Point<int> position, World *world);

    /**
     * @return a random neighbour of the creature's position that is within bounds of the world (may be occupied by another creature)
     * @note returns (-1, -1) if no free neighbour was found
     */
    Point<int> getRandomCorrectNeighbour(bool squareMustBeFree) const;

    virtual std::vector<Point<int>> getNeighbours() const;

    void fight(Creature *creature);

public:

    virtual void doTurn() = 0;

    virtual void collide(Creature *creature);

    virtual void handleCollision(Creature *collider);

    virtual bool didDeflectAttack(Creature *creature);

    /**
     * @return true if the creature ran away, false otherwise
     */
    virtual bool tryRunningAway(Creature *creature);

    //TODO
//    virtual void createChild(Point<int> position) = 0;

    [[nodiscard]] int getStrength() const;

    void setStrength(int newStrength);

    [[nodiscard]] int getInitiative() const;

    [[nodiscard]] int getAge() const;

    [[nodiscard]] bool getIsAlive() const;

    void kill();

    [[nodiscard]] virtual char getIcon() const = 0;


//    virtual ~Creature() = default;

    std::string toString() const;

    Point<int> getPosition();

    void setPosition(Point<int> point);

};

Console &operator<<(Console &console, const Creature &creature);

#endif //PROJEKT1CPP_CREATURE_H
