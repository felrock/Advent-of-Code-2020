#include <algorithm>
#include <iostream>
#include <fstream>
#include <type_traits>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

#define COMBINATIONS 8
#define TOP 0
#define TOP_REVERSE 1
#define BOT 2
#define BOT_REVERSE 3
#define RIGHT 4
#define RIGHT_REVERSE 5
#define LEFT 6
#define LEFT_REVERSE 7

std::vector<std::string> rotate(const std::vector<std::string>& tile)
{
  return std::vector<std::string>();
}
std::vector<std::string> flip(const std::vector<std::string>& tile)
{
  return std::vector<std::string>();
}
std::vector<std::string> fold(const std::vector<std::string>& tile)
{
  return std::vector<std::string>();
}

std::vector<std::string> allCombinationsOfEdges(
    const std::vector<std::string>& tile)
{
  std::vector<std::string> edges(COMBINATIONS);

  std::string top   = tile[0];
  std::string bot   = tile[tile.size()-1];
  std::string right = "";
  std::string left  = "";
  for(const auto& str : tile)
  {
    left  += str[0];
    right += str[str.size()-1];
  }
  edges[TOP] = top;
  std::reverse(top.begin(), top.end());
  edges[TOP_REVERSE] = top;
  edges[BOT]         = bot;
  std::reverse(bot.begin(), bot.end());
  edges[BOT_REVERSE] = bot;
  edges[RIGHT]       = right;
  std::reverse(right.begin(), right.end());
  edges[RIGHT] = right;
  edges[LEFT]  = left;
  std::reverse(left.begin(), left.end());
  edges[LEFT_REVERSE] = left;

  return edges;
}

void addEdges(std::unordered_map<std::string, int>& edges_map,
    const std::vector<std::string>& tile)
{
  std::vector<std::string> edges = allCombinationsOfEdges(tile);
  for(const auto& edg : edges)
  {
    edges_map[edg] += 1;
  }
}

int main(int argc, char** argv)
{
  std::fstream file(argv[1]);
  std::string s;

  std::unordered_map<int, std::vector<std::string>> jigsaw;
  std::unordered_map<std::string, int> edges;

  std::vector<std::string> tile;
  int tile_id;

  while(std::getline(file, s))
  {
    if(s == "")
    {
      addEdges(edges, tile);
      jigsaw[tile_id] = tile;
      tile.clear();
    }
    else if(s.find("Tile") != std::string::npos)
    {
      tile_id = std::stoi(s.substr(5, s.size()-1));
    }
    else
    {
      tile.push_back(s);
    }
  }
  // add trailing tile
  addEdges(edges, tile);
  jigsaw[tile_id] = tile;

  std::vector<int> edge_tiles;
  std::vector<std::string> up_left;
  std::vector<std::string> up_right;
  std::vector<std::string> down_left;
  std::vector<std::string> down_right;
  for(const auto& jigsaw_pair : jigsaw)
  {
    tile = jigsaw_pair.second;
    std::vector<std::string> cmbs = allCombinationsOfEdges(tile);

    int sum_top1 = edges[cmbs[TOP]] + edges[cmbs[LEFT]];
    int sum_top2 = edges[cmbs[TOP]] + edges[cmbs[RIGHT]];
    int sum_top3 = edges[cmbs[TOP]] + edges[cmbs[LEFT_REVERSE]];
    int sum_top4 = edges[cmbs[TOP]] + edges[cmbs[RIGHT_REVERSE]];

    int sum_bot1 = edges[cmbs[BOT]] + edges[cmbs[LEFT]];
    int sum_bot2 = edges[cmbs[BOT]] + edges[cmbs[RIGHT]];
    int sum_bot3 = edges[cmbs[BOT]] + edges[cmbs[LEFT_REVERSE]];
    int sum_bot4 = edges[cmbs[BOT]] + edges[cmbs[RIGHT_REVERSE]];

    int sum_top_reversed1 = edges[cmbs[TOP_REVERSE]] + edges[cmbs[LEFT]];
    int sum_top_reversed2 = edges[cmbs[TOP_REVERSE]] + edges[cmbs[RIGHT]];

    int sum_bot_reversed1 = edges[cmbs[BOT_REVERSE]] + edges[cmbs[LEFT]];
    int sum_bot_reversed2 = edges[cmbs[BOT_REVERSE]] + edges[cmbs[RIGHT]];

    if(sum_top1 == 2 || sum_top2 == 2 || sum_top3 == 2 || sum_top4 == 2 ||
       sum_bot1 == 2 || sum_bot2 == 2 || sum_bot3 == 2 || sum_bot4 == 2 ||
       sum_top_reversed1 == 2 || sum_top_reversed2 == 2 ||
       sum_bot_reversed1 == 2 || sum_bot_reversed2 == 2)
    {
      edge_tiles.push_back(jigsaw_pair.first);
    }
  }
  long long sum = 1;
  for(const auto& id : edge_tiles)
  {
    sum *= id;
  }
  std::cout << "part 1 " <<  sum << std::endl;

  for(const auto& id : edge_tiles)
  {
      std::vector<std::string> right_upper_corner = jigsaw[id];
      // orient as right upper corner piece
      if(edges[right_upper_corner[0]] == 1)
      {

      }
      else
      {

      }
  }

  return 0;
}
