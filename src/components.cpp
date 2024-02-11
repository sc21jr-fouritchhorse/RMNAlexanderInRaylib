//
// Created by qiaojun on 10/02/24.
//
#include "components.h"


template <typename T>
void ComponentArray<T>::InsertData(Entity e, T component)
{
    static_assert(mEnt2Ind.find(e) == mEnt2Ind.end() && "Already added this component to the entitiy");

    size_t newIndex = mNumAvailableInds;
    mEnt2Ind[e] = newIndex;


    mInd2Ent[newIndex] = e;
    mComponentArray[newIndex] = component;
    ++mNumAvailableInds;
}

template <typename T>
void ComponentArray<T>::RemoveData(Entity e)
{
    static_assert(mEnt2Ind.find(e) == mEnt2Ind.end() && "Removing component that doesn't exist");

    size_t e_i = mEnt2Ind[e];
    size_t last_i = mNumAvailableInds - 1;
    mComponentArray[e_i] = mComponentArray[e_i];

    Entity last_e = mInd2Ent[last_i];
    mEnt2Ind[last_e] = e_i;
    mEnt2Ind[e_i] = last_e;

    mEnt2Ind.erase(e);
    mInd2Ent.erase(last_e);

    --mNumAvailableInds;
}

template <typename T>
T& ComponentArray<T>::GetData(Entity e)
{
    static_assert(mEnt2Ind.find(e) != mEnt2Ind.end() && "Retrieving non-existent component.");
    return mComponentArray[mEnt2Ind[e]];
}



