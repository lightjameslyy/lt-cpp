#define BOOST_TEST_MODULE Map To Pointer Test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <map>
#include <iostream>
#include <cstdint>
#include <utility>

typedef int64_t node_id_t;

struct Node {
    virtual ~Node() = default;
    virtual node_id_t get_id() const = 0;
};

class BaseNode : public Node {
  public:
    explicit BaseNode(node_id_t id): id_(id) {}
    ~BaseNode() {}
    node_id_t get_id() const override {
        return id_;
    }
  private:
    node_id_t id_;
};

class Graph {
  public:
    //explicit Graph(std::map<node_id_t, Node*> nodes) : nodes_(std::move(nodes)) {}
    explicit Graph(std::map<node_id_t, Node*> nodes) : nodes_(nodes) {}
    ~Graph() {
        for (std::map<node_id_t, Node*>::iterator it = nodes_.begin(); it != nodes_.end(); ++it) {
            Node* np = it->second;
            delete np;
            np = nullptr;
        }
        nodes_.clear();
    }
    std::map<node_id_t, Node*> get_nodes_by_val() {
        std::cout << "within get_nodes_by_val(): " << &nodes_ << std::endl;
        return nodes_;
    }
    std::map<node_id_t, Node*>& get_nodes_by_ref() {
        std::cout << "within get_nodes_by_ref(): " << &nodes_ << std::endl;
        return nodes_;
    }
  private:
    std::map<node_id_t, Node*> nodes_;
};

BOOST_AUTO_TEST_CASE(map_to_pointer) {
    std::map<node_id_t, Node*> nodeMap;
    std::cout << "nodeMap: " << &nodeMap << std::endl;
    for (node_id_t i = 0; i < 5; ++i) {
        nodeMap[i] = new BaseNode(i);
    }
    {
        Graph g(nodeMap);
        std::map<node_id_t, Node*> nv = g.get_nodes_by_val();
        std::map<node_id_t, Node*>& nr = g.get_nodes_by_ref();
        std::cout << "g.get_nodes_by_val(): " << &nv << std::endl;
        std::cout << "g.get_nodes_by_ref(): " << &nr << std::endl;
        BOOST_TEST((&nv != &nr));
    }
    //BOOST_TEST((nodeMap.empty()));
}
