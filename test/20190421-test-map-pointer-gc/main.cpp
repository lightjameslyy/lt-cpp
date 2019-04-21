#define BOOST_TEST_MODULE Map To Pointer Test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <map>
#include <iostream>
#include <cstdint>

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

BOOST_AUTO_TEST_CASE(map_to_pointer) {
    std::map<node_id_t, Node*> nodeMap;
    nodeMap[1] = new BaseNode(1);
    Node* nd = nodeMap[1];
    BOOST_TEST((nd->get_id() == 1));
    nodeMap.clear();
    BOOST_TEST((nd->get_id() == 1));
}
