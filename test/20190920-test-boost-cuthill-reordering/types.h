#ifndef LT_CUTHILL_TYPES_H
#define LT_CUTHILL_TYPES_H

#include <boost/graph/adjacency_list.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list<vecS, vecS, undirectedS,
        property<vertex_color_t, default_color_type,
        property<vertex_degree_t,int> > > Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::vertices_size_type size_type;

typedef std::pair<std::size_t, std::size_t> Pair;

#endif  // LT_CUTHILL_TYPES_H
