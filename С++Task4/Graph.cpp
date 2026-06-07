#include "pch.h"
#include "Graph.h"
#include "Logger.h"
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <cctype>

void Graph::LoadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file: " + filename);

    m_adjList.clear();
    m_edgeCount = 0;

    std::string line;

    // First line: number of vertices
    if (!std::getline(file, line))
        throw std::runtime_error("File is empty");

    // Trim whitespace
    auto trim = [](std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isspace(c); }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char c) { return !std::isspace(c); }).base(), s.end());
    };
    trim(line);

    int vertexCount = 0;
    try {
        vertexCount = std::stoi(line);
    }
    catch (const std::exception&) {
        throw std::runtime_error("Invalid vertex count in first line");
    }

    if (vertexCount <= 0)
        throw std::runtime_error("Vertex count must be positive");

    m_adjList.resize(vertexCount);

    // Read each vertex and its adjacency list
    for (int i = 0; i < vertexCount; ++i)
    {
        if (!std::getline(file, line))
            throw std::runtime_error("Unexpected end of file at vertex " + std::to_string(i));

        trim(line);
        if (line.empty())
            continue; // skip empty lines

        std::istringstream iss(line);

        // Read vertex number
        int v;
        char colon;
        iss >> v >> colon;

        if (iss.fail() || colon != ':')
            throw std::runtime_error("Invalid format at line " + std::to_string(i + 2) + ". Expected 'N: v1 v2 ...'");

        int neighbor;
        while (iss >> neighbor)
        {
            if (neighbor < 0 || neighbor >= vertexCount)
                throw std::runtime_error("Vertex " + std::to_string(neighbor) + " out of range (0.." + std::to_string(vertexCount - 1) + ")");

            // Check for duplicate (linear search — lists are small)
            auto& adj = m_adjList[v];
            if (std::find(adj.begin(), adj.end(), neighbor) == adj.end())
            {
                adj.push_back(neighbor);
                ++m_edgeCount;
            }
        }
    }

    // Undirected graph: for each edge (u, v) we added it once from u's line.
    // For an undirected graph, each edge appears twice in adjacency lists.
    // We counted each direction separately, so divide by 2.
    m_edgeCount /= 2;

    Logger::Instance().Log(LogLevel::INFO,
        "Graph loaded: " + std::to_string(vertexCount) + " vertices, " +
        std::to_string(m_edgeCount) + " edges");
}

std::vector<std::list<int>> Graph::ComputeLayers(int startVertex) const
{
    if (m_adjList.empty())
        throw std::logic_error("Graph is empty. Load a graph first.");

    int n = GetVertexCount();
    if (startVertex < 0 || startVertex >= n)
        throw std::out_of_range("Start vertex " + std::to_string(startVertex) +
                                " is out of range (0.." + std::to_string(n - 1) + ")");

    // BFS using STL containers: queue for traversal, vector for distances
    std::vector<int> distance(n, -1);
    std::queue<int> bfsQueue;

    distance[startVertex] = 0;
    bfsQueue.push(startVertex);

    while (!bfsQueue.empty())
    {
        int current = bfsQueue.front();
        bfsQueue.pop();

        for (int neighbor : m_adjList[current])
        {
            if (distance[neighbor] == -1)
            {
                distance[neighbor] = distance[current] + 1;
                bfsQueue.push(neighbor);
            }
        }
    }

    // Build layers: group vertices by their distance (layer number)
    int maxLayer = *std::max_element(distance.begin(), distance.end());
    std::vector<std::list<int>> layers(maxLayer + 1);

    for (int v = 0; v < n; ++v)
    {
        if (distance[v] != -1)
            layers[distance[v]].push_back(v);
    }

    Logger::Instance().Log(LogLevel::INFO,
        "Layers computed from vertex " + std::to_string(startVertex) +
        ": " + std::to_string(layers.size()) + " layers");

    return layers;
}

void Graph::SaveLayersToFile(const std::string& filename,
                              int startVertex,
                              const std::vector<std::list<int>>& layers)
{
    std::ofstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Cannot create output file: " + filename);

    file << "BFS Layering starting from vertex " << startVertex << "\n";
    file << "Total layers: " << layers.size() << "\n\n";

    for (size_t i = 0; i < layers.size(); ++i)
    {
        file << "Layer " << i << ": ";
        bool first = true;
        for (int v : layers[i])
        {
            if (!first) file << ", ";
            file << v;
            first = false;
        }
        file << "\n";
    }

    Logger::Instance().Log(LogLevel::INFO,
        "Results saved to " + filename);
}
