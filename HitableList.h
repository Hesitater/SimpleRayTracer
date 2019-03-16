//
// Created by 易子沐 on 2019/3/16.
//

#ifndef SIMPLERAYTRACER_HITABLELIST_H
#define SIMPLERAYTRACER_HITABLELIST_H

#include "Hitable.h"

class HitableList: public Hitable {
public:
    Hitable** list;
    int listSize;

    HitableList() {}
    HitableList(Hitable** newList, int newListSize) {
       list = newList;
       listSize = newListSize;
    }
    virtual bool hit(const Ray &ray, float paramMin, float paramMax, HitRecord &record) const;
};

// Find nearest hitable object
bool HitableList::hit(const Ray &ray, float paramMin, float paramMax, HitRecord &record) const {
    HitRecord tempRecord;
    bool hitAnything = false;
    double closestSoFar = paramMax;
    for (int i = 0; i < this->listSize; ++i) {
        if (this->list[i]->hit(ray, paramMin, closestSoFar, tempRecord)) {
            hitAnything = true;
            closestSoFar = tempRecord.parameter;
            record = tempRecord;
        }
    }
    return hitAnything;
}

#endif //SIMPLERAYTRACER_HITABLELIST_H
