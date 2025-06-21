#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct Graph
{
  unordered_map<string, unordered_map<string, vector<int>>> edges;
  set<string> vertexes;
};

unordered_map<string, Graph> graphs;

vector<string> split(const string & line)
{
  vector<string> result;
  size_t start = 0;
  while (start < line.length())
  {
    size_t space = line.find(' ', start);
    if (space == string::npos) space = line.length();
    result.push_back(line.substr(start, space - start));
    start = space + 1;
  }
  return result;
}

void cmd_graphs()
{
  if (graphs.empty())
  {
    cout << "\n";
    return;
  }

  map<string, Graph *> sorted;
  for (unordered_map<string, Graph>::iterator it = graphs.begin(); it != graphs.end(); ++it)
  {
    sorted[it->first] = &it->second;
  }

  for (map<string, Graph *>::iterator it = sorted.begin(); it != sorted.end(); ++it)
  {
    cout << it->first << '\n';
  }
}

void cmd_vertexes(const vector<string> & args)
{
  if (args.size() < 2)
  {
    cout << "<INVALID COMMAND>\n";
    return;
  }

  const string & name = args[1];
  if (graphs.find(name) == graphs.end())
  {
    cout << "<INVALID COMMAND>\n";
    return;
  }

  for (set<string>::const_iterator it = graphs[name].vertexes.begin();
       it != graphs[name].vertexes.end(); ++it)
  {
    cout << *it << '\n';
  }
}

void cmd_outbound(const vector<string> & args)
{
  if (args.size() < 3)
  {
    cout << "<INVALID COMMAND>\n";
    return;
  }

  const string & g = args[1];
  const string & v = args[2];

  if (graphs.find(g) == graphs.end() ||
      graphs[g].vertexes.find(v) == graphs[g].vertexes.end())
  {
    cout << "<INVALID COMMAND>\n";
    return;
  }

  map<string, vector<int>> out;
  unordered_map<string, unordered_map<string, vector<int>>>::iterator targets = graphs[g].edges.find(v);
  if (targets != graphs[g].edges.end())
  {
    for (unordered_map<string, vector<int>>::iterator jt = targets->second.begin();
         jt != targets->second.end(); ++jt)
    {
      out[jt->first] = jt->second;
      sort(out[jt->first].begin(), out[jt->first].end());
    }
  }

  if (out.empty())
  {
    cout << "\n";
    return;
  }

  for (map<string, vector<int>>::iterator it = out.begin(); it != out.end(); ++it)
  {
    cout << it->first;
    for (vector<int>::iterator wt = it->second.begin(); wt != it->second.end(); ++wt)
    {
      cout << ' ' << *wt;
    }
    cout << '\n';
  }
}

void cmd_inbound(const vector<string> & args)
{
  if (args.size() < 3)
  {
    cout << "<INVALID COMMAND>\n";
    return;
  }

  const string & g = args[1];
  const string & v = args[2];

  if (graphs.find(g) == graphs.end() ||
      graphs[g].vertexes.find(v) == graphs[g].vertexes.end())
  {
    cout << "<INVALID COMMAND>\n";
    return;
  }

  map<string, vector<int>> in;
  for (unordered_map<string, unordered_map<string, vector<int>>>::iterator it = graphs[g].edges.begin();
       it != graphs[g].edges.end(); ++it)
  {
    unordered_map<string, vector<int>>::iterator jt = it->second.find(v);
    if (jt != it->second.end())
    {
      in[it->first] = jt->second;
      sort(in[it->first].begin(), in[it->first].end());
    }
  }

  for (map<string, vector<int>>::iterator it = in.begin(); it != in.end(); ++it)
  {
    cout << it->first;
    for (vector<int>::iterator wt = it->second.begin(); wt != it->second.end(); ++wt)
    {
      cout << ' ' << *wt;
    }
    cout << '\n';
  }
}

void cmd_bind(const vector<string> & args)
{
  if (args.size() < 5)
  {
    cout << "<INVALID COMMAND>\n";
    return;
  }

  const string & g = args[1];
  if (graphs.find(g) == graphs.end())
  {
    cout << "<INVALID COMMAND>\n";
    return;
  }

  const string & a = args[2];
  const string & b = args[3];
  int w = atoi(args[4].c_str());

  graphs[g].vertexes.insert(a);
  graphs[g].vertexes.insert(b);
  graphs[g].edges[a][b].push_back(w);
}

void cmd_cut(const vector<string> & args)
{
  if (args.size() < 5)
  {
    cout << "<INVALID COMMAND>\n";
    return;
  }

  const string & g = args[1];
  const string & a = args[2];
  const string & b = args[3];
  int w = atoi(args[4].c_str());

  if (graphs.find(g) == graphs.end() ||
      graphs[g].edges.find(a) == graphs[g].edges.end() ||
      graphs[g].edges[a].find(b) == graphs[g].edges[a].end())
  {
    cout << "<INVALID COMMAND>\n";
    return;
  }

  vector<int> & weights = graphs[g].edges[a][b];
  vector<int>::iterator it = find(weights.begin(), weights.end(), w);
  if (it == weights.end())
  {
    cout << "<INVALID COMMAND>\n";
    return;
  }

  weights.erase(it);
  if (weights.empty())
  {
    graphs[g].edges[a].erase(b);
  }
}

void cmd_create(const vector<string> & args)
{
  if (args.size() < 2)
  {
    cout << "<INVALID COMMAND>\n";
    return;
  }

  const string & g = args[1];
  if (graphs.find(g) != graphs.end())
  {
    cout << "<INVALID COMMAND>\n";
    return;
  }

  Graph newg;
  if (args.size() > 2)
  {
    for (size_t i = 2; i < args.size(); ++i)
    {
      newg.vertexes.insert(args[i]);
    }
  }
  graphs[g] = newg;
}

void cmd_merge(const vector<string> & args)
{
  if (args.size() < 4)
  {
    cout << "<INVALID COMMAND>\n";
    return;
  }

  const string & newg = args[1];
  const string & g1 = args[2];
  const string & g2 = args[3];

  if (graphs.find(newg) != graphs.end() ||
      graphs.find(g1) == graphs.end() ||
      graphs.find(g2) == graphs.end())
  {
    cout << "<INVALID COMMAND>\n";
    return;
  }

  Graph g;
  const string gs[2] = {g1, g2};
  for (size_t i = 0; i < 2; ++i)
  {
    for (set<string>::const_iterator it = graphs[gs[i]].vertexes.begin();
         it != graphs[gs[i]].vertexes.end(); ++it)
    {
      g.vertexes.insert(*it);
    }

    for (unordered_map<string, unordered_map<string, vector<int>>>::const_iterator et = graphs[gs[i]].edges.begin();
         et != graphs[gs[i]].edges.end(); ++et)
    {
      for (unordered_map<string, vector<int>>::const_iterator jt = et->second.begin();
           jt != et->second.end(); ++jt)
      {
        g.edges[et->first][jt->first].insert(
          g.edges[et->first][jt->first].end(),
          jt->second.begin(),
          jt->second.end()
        );
      }
    }
  }

  graphs[newg] = g;
}

void cmd_extract(const vector<string> & args)
{
  if (args.size() < 5)
  {
    cout << "<INVALID COMMAND>\n";
    return;
  }

  const string & newg = args[1];
  const string & oldg = args[2];
  size_t count = atoi(args[3].c_str());

  if (graphs.find(newg) != graphs.end() ||
      graphs.find(oldg) == graphs.end() ||
      args.size() < 4 + count)
  {
    cout << "<INVALID COMMAND>\n";
    return;
  }

  Graph g;
  for (size_t i = 0; i < count; ++i)
  {
    const string & vertex = args[4 + i];
    if (graphs[oldg].vertexes.find(vertex) == graphs[oldg].vertexes.end())
    {
      cout << "<INVALID COMMAND>\n";
      return;
    }
    g.vertexes.insert(vertex);
  }

  for (size_t i = 0; i < count; ++i)
  {
    const string & src = args[4 + i];
    for (size_t j = 0; j < count; ++j)
    {
      const string & dst = args[4 + j];
      if (graphs[oldg].edges.find(src) != graphs[oldg].edges.end() &&
          graphs[oldg].edges[src].find(dst) != graphs[oldg].edges[src].end())
      {
        g.edges[src][dst] = graphs[oldg].edges[src][dst];
      }
    }
  }

  graphs[newg] = g;
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "Missing input file\n";
    return 1;
  }

  ifstream file(argv[1]);
  if (!file)
  {
    cerr << "Cannot open file\n";
    return 1;
  }

  string line;
  while (getline(file, line))
  {
    if (line.empty()) continue;
    vector<string> header = split(line);
    if (header.size() != 2) continue;

    string name = header[0];
    int count = atoi(header[1].c_str());
    Graph g;

    for (int i = 0; i < count; ++i)
    {
      getline(file, line);
      if (line.empty()) continue;
      vector<string> e = split(line);
      if (e.size() != 3) continue;

      string a = e[0], b = e[1];
      int w = atoi(e[2].c_str());
      g.vertexes.insert(a);
      g.vertexes.insert(b);
      g.edges[a][b].push_back(w);
    }

    graphs[name] = g;
  }

  unordered_map<string, function<void(const vector<string>&)>> cmd_map;
  cmd_map["graphs"] = bind(cmd_graphs);
  cmd_map["vertexes"] = bind(cmd_vertexes, placeholders::_1);
  cmd_map["outbound"] = bind(cmd_outbound, placeholders::_1);
  cmd_map["inbound"] = bind(cmd_inbound, placeholders::_1);
  cmd_map["bind"] = bind(cmd_bind, placeholders::_1);
  cmd_map["cut"] = bind(cmd_cut, placeholders::_1);
  cmd_map["create"] = bind(cmd_create, placeholders::_1);
  cmd_map["merge"] = bind(cmd_merge, placeholders::_1);
  cmd_map["extract"] = bind(cmd_extract, placeholders::_1);

  string input;
  while (getline(cin, input))
  {
    if (input.empty()) continue;
    vector<string> args = split(input);
    if (args.empty()) continue;

    try
    {
      cmd_map.at(args[0])(args);
    }
    catch (const out_of_range&)
    {
      cout << "<INVALID COMMAND>\n";
    }
    catch (...)
    {
      cout << "<INVALID COMMAND>\n";
    }
  }

  return 0;
}