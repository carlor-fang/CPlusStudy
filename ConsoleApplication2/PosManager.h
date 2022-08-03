#pragma once
#include <vector>
#include <set>
#include <map>

class GridCell
{
public:
    GridCell();
    GridCell(int PX, int PY);
    //GridCell(const GridCell& Cell);
    ~GridCell();
    void Add(int Id);
    void Remove(int Id);
    const int GetX() const;
    const int GetY() const;
    void GetIds(std::vector<int>& IdVector) const;
private:
    int X;
    int Y;
    std::set<int> Ids;
};

class PosManager
{
public:
    PosManager();
    ~PosManager();

    void Init(int InCellSize, int InMapSize);
    void Uninit();

    bool Add(int Id, int MapX, int MapY);
    bool Remove(int Id);
    bool Update(int Id, int MapX, int MapY);

    bool Find(int Id, std::vector<int>& Ids);
private:
    std::vector<GridCell*>& GetGridX(int X);
    GridCell* GetCell(std::vector<GridCell*>& GridX, int X, int Y);
    GridCell* GetCell(int X, int Y);

    int CellSize;
    int MapSize;
    std::vector<std::vector<GridCell*>*> GridList; //1:X;2:Y;
    std::map<int, GridCell*> IdToGridList;
};

