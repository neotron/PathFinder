#pragma once

#include "PathAlgorithm.h"
#include "Node.h"
#include <vector>

class DijkstraNode : public Node {
    static const float infinity;

public:
    DijkstraNode() : distance(infinity), closed(false) { }

    void setClosed(bool value) {
        closed = value;
    }

    void setDistance(float value) {
        distance = value;
    }

    inline bool isClosed() const {
        return closed;
    }

    inline float getDistance() const {
        return distance;
    }

    void release() {
        distance = infinity;
        closed = false;
        m_parent = nullptr;
    }

    virtual ~DijkstraNode();

protected:
    float distance;
    bool closed;
};


struct CompareNodes {
    bool operator()(const DijkstraNode *n1, const DijkstraNode *n2) {
        return n1->getDistance() < n2->getDistance();
    }
};


class Dijkstra : public PathAlgorithm<DijkstraNode> {
public:

    static Dijkstra getInstance() {
        return Dijkstra();
    }

    bool getPath(DijkstraNode *start, DijkstraNode *goal, std::vector<DijkstraNode *> &path);

    void clear();

private:

    Dijkstra();

    ~Dijkstra();

    void pushOpen(DijkstraNode *node);

    void popOpen(DijkstraNode *node);

    void releaseNodes();

    std::vector<DijkstraNode *> open, closed;
};
