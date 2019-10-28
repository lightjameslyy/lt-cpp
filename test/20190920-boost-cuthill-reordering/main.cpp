#include "utils.h"

using namespace boost;
using namespace std;

int main(int, char* []) {
    int numEdges = 14;
    vector<Pair> edges = { Pair(0,3), //a-d
                           Pair(0,5),  //a-f
                           Pair(1,2),  //b-c
                           Pair(1,4),  //b-e
                           Pair(1,6),  //b-g
                           Pair(1,9),  //b-j
                           Pair(2,3),  //c-d
                           Pair(2,4),  //c-e
                           Pair(3,5),  //d-f
                           Pair(3,8),  //d-i
                           Pair(4,6),  //e-g
                           Pair(5,6),  //f-g
                           Pair(5,7),  //f-h
                           Pair(6,7)  //g-h
                           // ring and duplicates
                           //Pair(1,1),
                           //Pair(2,4),
                           //Pair(2,4),
                           //Pair(5,6)
                         };

    //to_dot("orig", numEdges, &edges[0]);
    //print_matrix(10, numEdges, &edges[0]);

    Graph G(10);
    for (int i = 0; i < numEdges; ++i)
        add_edge(edges[i].first, edges[i].second, G);

    graph_to_dot("orig_g", G);
    print_graph_matrix(G);

    graph_traits<Graph>::vertex_iterator ui, ui_end;

    property_map<Graph,vertex_degree_t>::type deg = get(vertex_degree, G);
    for (boost::tie(ui, ui_end) = vertices(G); ui != ui_end; ++ui)
        deg[*ui] = degree(*ui, G);

    property_map<Graph, vertex_index_t>::type
    index_map = get(vertex_index, G);

    std::cout << "original bandwidth: " << bandwidth(G) << std::endl;

    std::vector<Vertex> inv_perm(num_vertices(G));
    std::vector<size_type> perm(num_vertices(G));
    {
        //reverse cuthill_mckee_ordering
        cuthill_mckee_ordering(G, inv_perm.rbegin(), get(vertex_color, G),
                               make_degree_map(G));

        //cout << "Reverse Cuthill-McKee ordering:" << endl;
        //cout << "  ";
        //for (std::vector<Vertex>::const_iterator i=inv_perm.begin();
        //        i != inv_perm.end(); ++i)
        //    cout << index_map[*i] << " ";
        //cout << endl;

        for (size_type c = 0; c != inv_perm.size(); ++c)
            perm[index_map[inv_perm[c]]] = c;

        cout << "inv_perm: " << endl;
        for (size_type c = 0; c != inv_perm.size(); ++c)
            cout << inv_perm[c] << ", ";
        cout << endl;
        cout << "perm: " << endl;
        for (size_type c = 0; c != perm.size(); ++c)
            cout << perm[c] << ", ";
        cout << endl;
        //std::cout << "  bandwidth: "
        //          << bandwidth(G, make_iterator_property_map(&perm[0], index_map, perm[0]))
        //          << std::endl;
    }

    // generate reordered edge list
    std::vector<Pair> reordered_edges;
    {
        graph_traits<Graph>::edge_iterator ei, ei_end;
        for (boost::tie(ei, ei_end) = boost::edges(G); ei != ei_end; ++ei) {
            reordered_edges.push_back(std::make_pair(
                                          (std::size_t)perm[source(*ei, G)],
                                          (std::size_t)perm[target(*ei, G)]));
        }
        Graph G1(10);
        for (int i = 0; i < numEdges; ++i)
            add_edge(reordered_edges[i].first, reordered_edges[i].second, G1);

        //to_dot("reordered", num_edges(G1), &reordered_edges[0]);
        //print_matrix(num_vertices(G1), num_edges(G), &reordered_edges[0]);
        graph_to_dot("reordered_g", G1);
        print_graph_matrix(G1);
        std::cout << "reordered bandwidth: " << bandwidth(G1) << std::endl;
    }

    return 0;
}

int main1(int, char* []) {
    Pair edges[18] = { Pair(0,3), //a-d
                       Pair(0,5),  //a-f
                       Pair(1,2),  //b-c
                       Pair(1,4),  //b-e
                       Pair(1,6),  //b-g
                       Pair(1,9),  //b-j
                       Pair(2,3),  //c-d
                       Pair(2,4),  //c-e
                       Pair(3,5),  //d-f
                       Pair(3,8),  //d-i
                       Pair(4,6),  //e-g
                       Pair(5,6),  //f-g
                       Pair(5,7),  //f-h
                       Pair(6,7),  //g-h
                       // ring and duplicates
                       Pair(1,1),
                       Pair(2,4),
                       Pair(2,4),
                       Pair(5,6)
                     };

    Graph G(10);
    for (int i = 0; i < 18; ++i)
        add_edge(edges[i].first, edges[i].second, G);

    graph_traits<Graph>::vertex_iterator ui, ui_end;

    property_map<Graph,vertex_degree_t>::type deg = get(vertex_degree, G);
    for (boost::tie(ui, ui_end) = vertices(G); ui != ui_end; ++ui)
        deg[*ui] = degree(*ui, G);

    property_map<Graph, vertex_index_t>::type
    index_map = get(vertex_index, G);

    std::cout << "original bandwidth: " << bandwidth(G) << std::endl;

    std::vector<Vertex> inv_perm(num_vertices(G));
    std::vector<size_type> perm(num_vertices(G));
    {
        Vertex s = vertex(6, G);
        //reverse cuthill_mckee_ordering
        cuthill_mckee_ordering(G, s, inv_perm.rbegin(), get(vertex_color, G),
                               get(vertex_degree, G));
        cout << "Reverse Cuthill-McKee ordering starting at: " << s << endl;
        cout << "  ";
        for (std::vector<Vertex>::const_iterator i = inv_perm.begin();
                i != inv_perm.end(); ++i)
            cout << index_map[*i] << " ";
        cout << endl;

        for (size_type c = 0; c != inv_perm.size(); ++c)
            perm[index_map[inv_perm[c]]] = c;
        std::cout << "  bandwidth: "
                  << bandwidth(G, make_iterator_property_map(&perm[0], index_map, perm[0]))
                  << std::endl;
    }
    {
        Vertex s = vertex(0, G);
        //reverse cuthill_mckee_ordering
        cuthill_mckee_ordering(G, s, inv_perm.rbegin(), get(vertex_color, G),
                               get(vertex_degree, G));
        cout << "Reverse Cuthill-McKee ordering starting at: " << s << endl;
        cout << "  ";
        for (std::vector<Vertex>::const_iterator i=inv_perm.begin();
                i != inv_perm.end(); ++i)
            cout << index_map[*i] << " ";
        cout << endl;

        for (size_type c = 0; c != inv_perm.size(); ++c)
            perm[index_map[inv_perm[c]]] = c;
        std::cout << "  bandwidth: "
                  << bandwidth(G, make_iterator_property_map(&perm[0], index_map, perm[0]))
                  << std::endl;
    }

    {
        //reverse cuthill_mckee_ordering
        cuthill_mckee_ordering(G, inv_perm.rbegin(), get(vertex_color, G),
                               make_degree_map(G));

        cout << "Reverse Cuthill-McKee ordering:" << endl;
        cout << "  ";
        for (std::vector<Vertex>::const_iterator i=inv_perm.begin();
                i != inv_perm.end(); ++i)
            cout << index_map[*i] << " ";
        cout << endl;

        for (size_type c = 0; c != inv_perm.size(); ++c)
            perm[index_map[inv_perm[c]]] = c;
        std::cout << "  bandwidth: "
                  << bandwidth(G, make_iterator_property_map(&perm[0], index_map, perm[0]))
                  << std::endl;
    }
    return 0;
}
