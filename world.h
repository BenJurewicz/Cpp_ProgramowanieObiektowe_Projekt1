#ifndef PROJEKT1CPP_WORLD_H
#define PROJEKT1CPP_WORLD_H

#include <vector>
#include <list>
#include <memory>

#include "console.h"
#include "log.h"
#include "creatures/creature.h"

class Creature;

/**
 * Describes how many of a single species can be present in the world.
 * Maximum number of species = maxSpeciesCountMultiplier * worldHeight * worldWidth
 */
constexpr double maxSpeciesCountMultiplier = 0.05;

class World {
    int worldHeight, worldWidth;
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
    void createSpecies(int minSpeciesCount, int maxSpeciesCount);

    void createCreatures();

public:
    World(int worldHeight, int worldWidth);

    [[maybe_unused]] void startLoopNoInput(Console &console, int turns = 10);

    [[nodiscard]] std::function<Console &(Console &)> moveCursorToLogPoint() const;

    void clearLog(Console &console) const;

    std::shared_ptr<Creature> getTile(Point<int> position);

    bool isOccupied(Point<int> point);

    void drawMap(Console &console, int y, int x);

    void doTurn();

    [[nodiscard]] Point<int> getDimensions() const;

    void moveCreature(const std::shared_ptr<Creature> &creature, Point<int> point);
};


#endif //PROJEKT1CPP_WORLD_H
