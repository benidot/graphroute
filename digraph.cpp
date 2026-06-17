#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace dg {

template <typename T>
class digraph {
 private:
  struct node {
    T value;
    std::unordered_set<node*> links;
  };

  std::unordered_map<T, node> graph;

  node* find(const T& val) {
    auto it = graph.find(val);
    if (it == graph.end()) {  // Not found!
      return nullptr;
    }
    return &it->second;
  }

  void visit_node(node* p, std::unordered_set<node*>& visited, int level) {
    std::cout << std::string(level, '\t') << p->value << "\n";
    visited.insert(p);
    for (auto adj : p->links) {
      if (visited.count(adj) == 0) visit_node(adj, visited, level + 1);
    }
  }

 public:
  void insert_node(const T& val) {
    if (val == "*") return;
    if (graph.count(val) != 0) return;
    node aux;
    aux.value = val;
    graph[val] = aux;
  }

  void insert_link(const T& from, const T& to) {
    auto pfrom = find(from);
    if (!pfrom) return;
    auto pto = find(to);
    if (!pto || pto->value == "*") return;

    pfrom->links.insert(pto);
  }

  void remove(const T& val) {
    auto p = find(val);
    if (!p) return;
    for (auto& [key, node] : graph) {
      node.links.erase(p);
    }
    graph.erase(val);
  }

  void show(std::string& choice) {
    std::ofstream dot("g123456.dot");
    dot << "digraph{\n";
    for (const auto& [key, node] : graph) {
      dot << "\t\"" << key << "\" -> {";
      for (const auto& link : node.links) {
        dot << "\"" << link->value << "\" ";
      }
      dot << "};\n";
    }
    dot << "}\n";
    dot.close();
    std::string final = "";
    if (choice == "-Tpng") {
      final = " -o out.png";
    } else if (choice == "-Tpdf") {
      final = " -o out.pdf";
    }
    std::string call = "dot " + choice + " g123456.dot" + final;
    system(call.c_str());
  }

  void DFS_from(const T& from) {
    auto p = find(from);
    if (!p) return;

    std::unordered_set<node*> visited;
    visit_node(p, visited, 0);
  }

  std::vector<node*> shortest_path(const T& start, const T& end) {
    std::vector<node*> path;

    auto pstart = find(start);
    if (!pstart) return path;

    auto pend = find(end);
    if (!pend) return path;

    std::queue<node*> q;
    std::unordered_set<node*> queued;
    std::unordered_map<node*, node*> origin;
    q.push(pstart);
    queued.insert(pstart);
    origin[pstart] = nullptr;
    bool found = false;

    while (!q.empty()) {
      auto current = q.front();
      q.pop();
      if (current == pend) {
        found = true;
        break;
      }
      for (auto adj : current->links) {
        if (queued.count(adj) == 0) {
          q.push(adj);
          queued.insert(adj);
          origin[adj] = current;
        }
      }
    }
    if (found) {
      auto p = pend;
      while (p) {
        path.push_back(p);
        p = origin[p];
      }
    }
    std::reverse(path.begin(), path.end());

    return path;
  }

  void load(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) return;
    int n;
    in >> n;
    in.ignore();
    std::string line, line2;
    while (n--) {
      getline(in, line);
      insert_node(line);
    }
    while (getline(in, line) && getline(in, line2)) {
      insert_link(line, line2);
    }

    in.close();
  }

  void save(const std::string& filename) {
    std::ofstream out(filename);
    out << graph.size() << "\n";
    for (const auto& [key, node] : graph) {
      out << node.value << "\n";
    }
    for (const auto& [key, node] : graph) {
      for (const auto& link : node.links) {
        out << key << '\n';
        out << link->value << '\n';
      }
    }
    out.close();
  }
};
}  // namespace dg
