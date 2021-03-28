#define CATCH_CONFIG_MAIN
#include <set>

#include "boost/graph/adjacency_list.hpp"
#include "catch.hpp"

TEST_CASE("boost::adjacency_list stores data") {
  boost::adjacency_list<> graph{};
  auto vertex_1 = boost::add_vertex(graph);
  auto vertex_2 = boost::add_vertex(graph);
  auto vertex_3 = boost::add_vertex(graph);
  auto vertex_4 = boost::add_vertex(graph);
  auto edge_12 = boost::add_edge(vertex_1, vertex_2, graph);
  auto edge_13 = boost::add_edge(vertex_1, vertex_3, graph);
  auto edge_21 = boost::add_edge(vertex_2, vertex_1, graph);
  auto edge_24 = boost::add_edge(vertex_2, vertex_4, graph);
  auto edge_43 = boost::add_edge(vertex_4, vertex_3, graph);

  REQUIRE(boost::num_vertices(graph) == 4);
  REQUIRE(boost::num_edges(graph) == 5);

  auto [begin, end] = boost::adjacent_vertices(vertex_1, graph);
  std::set<decltype(vertex_1)> neighbors_1{begin, end};
  REQUIRE(neighbors_1.count(vertex_2) == 1);
  REQUIRE(neighbors_1.count(vertex_3) == 1);
  REQUIRE(neighbors_1.count(vertex_4) == 0);
}

// how to run
// clang++ -std=c++2a boost-graph.cpp -o boost-graph
// /usr/local/lib/libboost_graph.a && ./boost-graph or clang++ -std=c++2a
// boost-graph.cpp -o boost-graph -lboost_graph && ./boost-graph