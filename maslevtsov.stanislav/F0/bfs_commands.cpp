#include "bfs_commands.hpp"
#include <algorithm>
#include <queue>
#include <functional>
#include <stack>

namespace {
  using distances_t = std::unordered_map< unsigned, size_t >;
  using parents_t = std::unordered_map< unsigned, unsigned >;
  using nodes_queue_t = std::queue< unsigned >;
  using node_neighbour_pair_t = std::pair< const unsigned, std::vector< unsigned > >;
  using node_distance_pair_t = std::pair< const unsigned, size_t >;

  struct PathProcessor
  {
    unsigned current_node_;
    distances_t& distances_;
    parents_t& parents_;
    nodes_queue_t& nodes_queue_;

    PathProcessor(unsigned current_node, distances_t& distances, parents_t& parents, nodes_queue_t& nodes_queue):
      current_node_(current_node),
      distances_(distances),
      parents_(parents),
      nodes_queue_(nodes_queue)
    {}

    int operator()(unsigned neighbor)
    {
      if (distances_.find(neighbor) == distances_.end()) {
        distances_[neighbor] = distances_[current_node_] + 1;
        parents_[neighbor] = current_node_;
        nodes_queue_.push(neighbor);
      }
      return 0;
    }
  };

  void get_bfs_from(const maslevtsov::Graph& graph, unsigned start, distances_t& distances, parents_t& parents)
  {
    distances_t distances_result;
    parents_t parents_result;
    const std::unordered_map< unsigned, std::vector< unsigned > >& adj_list = graph.get_adj_list();
    nodes_queue_t to_visit;
    distances_result[start] = 0;
    to_visit.push(start);
    while (!to_visit.empty()) {
      unsigned current_node = to_visit.front();
      to_visit.pop();
      auto adj_list_it = adj_list.find(current_node);
      if (adj_list_it->second.empty()) {
        continue;
      }
      std::vector< int > dump(adj_list_it->second.size());
      std::transform(adj_list_it->second.begin(), adj_list_it->second.end(), dump.begin(),
        PathProcessor(current_node, distances_result, parents_result, to_visit));
    }
    distances = std::move(distances_result);
    parents = std::move(parents_result);
  }

  bool compare_distances(const node_distance_pair_t& left, const node_distance_pair_t& right)
  {
    return left.second < right.second;
  }

  size_t get_max_distance(const maslevtsov::Graph& graph, const node_neighbour_pair_t& node_neighbour_pair)
  {
    distances_t distances;
    parents_t parents;
    get_bfs_from(graph, node_neighbour_pair.first, distances, parents);
    auto max_el_it = std::max_element(distances.begin(), distances.end(), compare_distances);
    return max_el_it != distances.end() ? max_el_it->second : 0;
  }

  unsigned get_first_component_element(const std::pair< const unsigned, unsigned >& node_parent_pair)
  {
    return node_parent_pair.first;
  }

  unsigned get_second_component_element(const std::pair< const unsigned, unsigned >& node_parent_pair)
  {
    return node_parent_pair.second;
  }

  int get_component(const maslevtsov::Graph& graph, const node_neighbour_pair_t& node_neighbour_pair,
    std::vector< std::vector< unsigned > >& components)
  {
    distances_t distances;
    parents_t parents;
    get_bfs_from(graph, node_neighbour_pair.first, distances, parents);
    std::vector< unsigned > component;
    if (parents.empty()) {
      return 0;
    }
    std::transform(parents.begin(), parents.end(), std::back_inserter(component), get_first_component_element);
    std::transform(parents.begin(), parents.end(), std::back_inserter(component), get_second_component_element);
    std::sort(component.begin(), component.end());
    auto first_to_erase = std::unique(component.begin(), component.end());
    component.erase(first_to_erase, component.end());
    if (std::find(components.begin(), components.end(), component) == components.end()) {
      components.push_back(component);
    }
    return 0;
  }
}

void maslevtsov::traverse_breadth_first(const graphs_t& graphs, std::istream& in, std::ostream& out)
{
  std::string graph_name;
  unsigned start_node = 0;
  in >> graph_name >> start_node;
  auto gr_it = graphs.find(graph_name);
  if (gr_it == graphs.cend() || gr_it->second.get_adj_list().find(start_node) == gr_it->second.get_adj_list().cend()) {
    throw std::invalid_argument("non-existing graph");
  }
  distances_t distances;
  parents_t parents;
  get_bfs_from(gr_it->second, start_node, distances, parents);
  for (auto i = distances.cbegin(); i != distances.cend(); ++i) {
    out << start_node << '-' << i->first << " : " << i->second << '\n';
  }
}

void maslevtsov::get_min_path(const graphs_t& graphs, std::istream& in, std::ostream& out)
{
  std::string graph_name;
  unsigned start_node = 0, goal_node = 0;
  in >> graph_name >> start_node >> goal_node;
  auto gr_it = graphs.find(graph_name);
  if (gr_it == graphs.cend() || gr_it->second.get_adj_list().find(start_node) == gr_it->second.get_adj_list().cend()) {
    throw std::invalid_argument("non-existing graph");
  }
  distances_t distances;
  parents_t parents;
  get_bfs_from(gr_it->second, start_node, distances, parents);
  if (distances.find(goal_node) == distances.end()) {
    throw std::invalid_argument("non-existing path");
  }
  std::stack< unsigned > restored_path;
  unsigned current_node = goal_node;
  while (current_node != start_node) {
    restored_path.push(current_node);
    current_node = parents[current_node];
  }
  out << current_node << '-' << restored_path.top();
  restored_path.pop();
  while (!restored_path.empty()) {
    out << '-' << restored_path.top();
    restored_path.pop();
  }
  out << ' ' << distances[goal_node] << '\n';
}

void maslevtsov::get_graph_width(const graphs_t& graphs, std::istream& in, std::ostream& out)
{
  std::string graph_name;
  in >> graph_name;
  auto gr_it = graphs.find(graph_name);
  if (gr_it == graphs.cend()) {
    throw std::invalid_argument("non-existing graph");
  }
  const std::unordered_map< unsigned, std::vector< unsigned > >& adj_list = gr_it->second.get_adj_list();
  std::vector< size_t > all_distances;
  using namespace std::placeholders;
  auto distance_collector = std::bind(get_max_distance, std::ref(gr_it->second), _1);
  std::transform(adj_list.begin(), adj_list.end(), std::back_inserter(all_distances), distance_collector);
  out << *std::max_element(all_distances.begin(), all_distances.end()) << '\n';
}

void maslevtsov::get_graph_components(const graphs_t& graphs, std::istream& in, std::ostream& out)
{
  std::string graph_name;
  in >> graph_name;
  auto gr_it = graphs.find(graph_name);
  if (gr_it == graphs.cend()) {
    throw std::invalid_argument("non-existing graph");
  }
  const std::unordered_map< unsigned, std::vector< unsigned > >& adj_list = gr_it->second.get_adj_list();
  std::vector< std::vector< unsigned > > all_components;
  std::vector< int > dump;
  using namespace std::placeholders;
  auto component_collector = std::bind(get_component, std::ref(gr_it->second), _1, std::ref(all_components));
  std::transform(adj_list.begin(), adj_list.end(), std::back_inserter(dump), component_collector);
  for (auto i = all_components.begin(); i != all_components.end(); ++i) {
    out << *i->begin();
    for (auto j = ++i->begin(); j != i->end(); ++j) {
      out << '-' << *j;
    }
    out << '\n';
  }
}
