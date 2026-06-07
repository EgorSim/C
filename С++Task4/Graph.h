#pragma once
#include <vector>
#include <list>
#include <string>
#include <stdexcept>

class Graph {
public:
    Graph() = default;

    void LoadFromFile(const std::string& filename);
    std::vector<std::list<int>> ComputeLayers(int startVertex) const;

    int GetVertexCount() const { return static_cast<int>(m_adjList.size()); }
    int GetEdgeCount() const  { return m_edgeCount; }
    bool IsEmpty() const      { return m_adjList.empty(); }

    static void SaveLayersToFile(const std::string& filename,
                                 int startVertex,
                                 const std::vector<std::list<int>>& layers);

private:
    std::vector<std::list<int>> m_adjList;
    int m_edgeCount = 0;
};
