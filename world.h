#ifndef PROJEKT1CPP_WORLD_H
#define PROJEKT1CPP_WORLD_H

#include <vector>
#include <list>
#include <memory>

#include "console.h"
#include "log.h"
#include "creatures/creature.h"

class Creature;

class World {
    int worldHeight, worldWidth;
    int minSpeciesCount, maxSpeciesCount;
    std::vector<std::vector<std::vector<std::shared_ptr<Creature> > > > map;
    std::list<std::shared_ptr<Creature> > creatures;

    void resizeMap();

//    static inline void drawMapCell(Console &console, const std::vector<Creature *> &cell);
    static inline void drawMapCell(Console &console, const std::vector<std::shared_ptr<Creature>> &cell);

    Point<int> getRandomFreeCell();

    /**
     * @tparam S has to derive from Creature and have a constructor that takes a Point<int> as an argument
     */
    template<class S>
    void createSpecies();

    void createCreatures();

    void sortCreaturesByPriority();

    void removeDeadCreatures();

public:
    World(int worldHeight, int worldWidth);

    World(int worldHeight, int worldWidth, int minSpeciesCount, int maxSpeciesCount);

    [[maybe_unused]] void startLoopNoInput(Console &console, int turns = 10);

    std::shared_ptr<Creature> getTile(Point<int> position);

    bool isOccupied(Point<int> point);

    void drawMap(Console &console, int y, int x);

    void doTurn();

    [[nodiscard]] Point<int> getDimensions() const;

    void moveCreature(const std::shared_ptr<Creature> &creature, Point<int> point);

    void addCreature(const std::shared_ptr<Creature> &creature);

    [[maybe_unused]] [[nodiscard]] int getHeight() const;

    [[maybe_unused]] [[nodiscard]] int getWidth() const;

//    void load();
//
//    void save();

};


#endif //PROJEKT1CPP_WORLD_H
