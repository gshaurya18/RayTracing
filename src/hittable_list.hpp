#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include "hittable.hpp"

#include <vector>
#include <memory>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable{
    std::vector< shared_ptr<hittable> > objects;
    public:
        hittable_list(shared_ptr<hittable> object) { add(object); }

        void clear() { objects.clear(); }

        void add(shared_ptr<hittable> object) {
           objects.push_back(object);
        }

        // Returns wether any object was hit
        // rec is record of last hit in objects vector
        virtual bool hit(const ray&r, double t_min, double t_max, hit_record& rec) const override{
            hit_record hr;
            bool hit_anything = false;
            auto closest_so_far = t_max;

            for (const auto& object: objects){
            if (object->hit(r, t_min, closest_so_far, hr)){
                hit_anything = true;
                closest_so_far = hr.t;
                rec = hr;
            }
            }

            return hit_anything;
        }
};

#endif