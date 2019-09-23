#ifndef LT_CUTHILL_UTILS_H
#define LT_CUTHILL_UTILS_H

#include <boost/config.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/graph/cuthill_mckee_ordering.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/bandwidth.hpp>

#include "types.h"

// generate *.dot from edge list
// convert to png:
//      dot -Tpng 1.dot -o 1.png
void to_dot(const std::string & name, int edgeNum, Pair* edges) __attribute__ ((deprecated));
void to_dot(const std::string & name, int edgeNum, Pair* edges) {
    std::ostringstream osg;
    osg << "strict graph g" << " {\n\tconcentrate=true\n";
    for (int i = 0; i < edgeNum; ++i) {
        std::size_t v0 = edges[i].first;
        std::size_t v1 = edges[i].second;
        osg << "\t" << v0 << "--" << v1 << "\n";
    }
    osg << "}\n\n";
    std::ofstream ofs(name+".dot", std::ios::out);
    ofs << osg.str();
    ofs.close();
}

void print_matrix(int numVertices, int edgeNum, Pair* edges) __attribute__ ((deprecated));
void print_matrix(int numVertices, int edgeNum, Pair* edges) {
    vector<vector<std::size_t>> mat(numVertices,
                                    vector<std::size_t>(numVertices, 0));
    for (int i = 0; i < edgeNum; ++i) {
        mat[edges[i].first][edges[i].second] = 1;
        mat[edges[i].second][edges[i].first] = 1;
    }
    std::ostringstream oss;
    oss << "-------------------------------------------\n";
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            oss << mat[i][j] << " ";
        }
        oss << "\n";
    }
    oss << "-------------------------------------------\n";
    printf("%s", oss.str().c_str());
}

// generate *.dot from edge list
// convert to png:
//      dot -Tpng 1.dot -o 1.png
void graph_to_dot(const std::string & name, const Graph& g) {
    std::ostringstream osg;
    osg << "strict graph g" << " {\n\tconcentrate=true\n";
    graph_traits<Graph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = boost::edges(g); ei != ei_end; ++ei) {
        osg << "\t" << source(*ei, g) << "--" << target(*ei, g) << "\n";
    }
    osg << "}\n\n";
    std::ofstream ofs(name+".dot", std::ios::out);
    ofs << osg.str();
    ofs.close();
}

void print_graph_matrix(const Graph& g) {
    int numVertices = num_vertices(g);
    vector<vector<std::size_t>> mat(numVertices,
                                    vector<std::size_t>(numVertices, 0));
    graph_traits<Graph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = boost::edges(g); ei != ei_end; ++ei) {
        mat[source(*ei, g)][target(*ei, g)] = 1;
        mat[target(*ei, g)][source(*ei, g)] = 1;
    }
    std::ostringstream oss;
    oss << "-------------------------------------------\n";
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            oss << mat[i][j] << " ";
        }
        oss << "\n";
    }
    oss << "-------------------------------------------\n";
    printf("%s", oss.str().c_str());
}

#endif  // LT_CUTHILL_UTILS_H
