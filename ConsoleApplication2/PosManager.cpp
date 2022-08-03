#include <iostream>
#include "PosManager.h"

GridCell::GridCell()
{
    std::cout << "grid cell default contructor" << std::endl;
}

GridCell::GridCell(int PX, int PY)
{
    X = PX;
    Y = PY;
}

//GridCell::GridCell(const GridCell& Cell)
//{
//    std::cout << "grid cell copy contructor" << std::endl;
//}

GridCell::~GridCell()
{
    std::cout << "grid cell destructor" << std::endl;
    Ids.clear();
}

void GridCell::Add(int Id)
{
    Ids.insert(Id);
}

void GridCell::Remove(int Id)
{
    Ids.erase(Id);
}

const int GridCell::GetX() const
{
    return X;
}

const int GridCell::GetY() const
{
    return Y;
}

void GridCell::GetIds(std::vector<int>& IdVector) const
{
    for (std::set<int>::iterator Iter = Ids.begin(); Iter != Ids.end(); ++Iter)
    {
        IdVector.push_back(*Iter);
    }
}

PosManager::PosManager()
{
    Uninit();
}

PosManager::~PosManager()
{
    Uninit();
}

void PosManager::Init(int InCellSize, int InMapSize)
{
    CellSize = InCellSize;
    MapSize = InMapSize;
}

void PosManager::Uninit()
{
    for (int i = GridList.size() - 1; i >= 0; i--)
    {        
        for (int j = GridList[i]->size() - 1; j >= 0; j--)
        {
            delete GridList[i]->at(j);
        }
        GridList[i]->clear();
        delete GridList[i];
    }
    GridList.clear();
}

std::vector<GridCell*>& PosManager::GetGridX(int X)
{
    if (GridList.size() <= X)
    {
        for (int i = GridList.size(); i <= X; i++)
        {
            std::vector<GridCell*>* GridX = new std::vector<GridCell*>();
            GridList.push_back(GridX);
        }
    }

    return *GridList[X];
}

GridCell* PosManager::GetCell(std::vector<GridCell*>& GridX, int X, int Y)
{
    if (GridX.size() <= Y)
    {
        for (int i = GridX.size(); i <= Y; i++)
        {
            GridX.push_back(new GridCell(X, i));
        }
    }
    return GridX[Y];
}

GridCell* PosManager::GetCell(int X, int Y)
{
    std::vector<GridCell*>& GridX = GetGridX(X);
    return GetCell(GridX, X, Y);
}

bool PosManager::Add(int Id, int MapX, int MapY)
{
    if (MapX < 0 || MapX >= MapSize || MapY < 0 || MapY >= MapSize)
    {
        return false;
    }
    if (Update(Id, MapX, MapY))
    {
        return true;
    }

    GridCell* Cell = GetCell(MapX / CellSize, MapY / CellSize);
    Cell->Add(Id);
    IdToGridList[Id] = Cell;

    return true;
}

bool PosManager::Remove(int Id) 
{
    std::map<int, GridCell*>::iterator Iter = IdToGridList.find(Id);
    if (Iter == IdToGridList.end())
    {
        return false;
    }
    Iter->second->Remove(Id);
    IdToGridList.erase(Id);

    return true;
}

bool PosManager::Update(int Id, int MapX, int MapY)
{
    if (!Remove(Id))
    {
        return false;
    }

    GridCell* Cell = GetCell(MapX / CellSize, MapY / CellSize);
    Cell->Add(Id);
    IdToGridList[Id] = Cell;

    return true;
}

bool PosManager::Find(int Id, std::vector<int>& Ids)
{
    std::map<int, GridCell*>::iterator Iter = IdToGridList.find(Id);
    if (Iter == IdToGridList.end())
    {
        return false;
    }
    
    Ids.clear();
    int X = Iter->second->GetX();
    int Y = Iter->second->GetY();
    int MaxCell = MapSize / CellSize;
    for (int i = X - 1; i <= X + 1; i++)
    {
        if ((i < 0 || i >= MaxCell) ||
            (GridList.size() <= i))
        {
            continue;
        }
        for (int j = Y - 1; j <= Y + 1; j++)
        {
            if ((j < 0 || j >= MaxCell) ||
                (i == X && j == Y) ||
                (GridList[i]->size() <= j))
            {
                continue;
            }
            GridList[i]->at(j)->GetIds(Ids);
        }
    }

    return true;
}