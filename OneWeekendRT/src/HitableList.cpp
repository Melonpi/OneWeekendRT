#include "HitableList.h"

namespace ow
{
	HitableList::HitableList()
	{
	}

	HitableList::~HitableList()
	{
	}

	void HitableList::add(std::unique_ptr<Hitable> hitable)
	{
		hitable_list_.push_back(std::move(hitable));
	}

	bool HitableList::hit(const Ray& ray, real t_min, real t_max, HitInfo& hit_info) const
	{
		bool is_hit_anything = false;
		real closest_so_far = t_max;
		HitInfo object_hit_info;
		for (auto& obj : hitable_list_)
		{
			if (obj->hit(ray, t_min, closest_so_far, object_hit_info))
			{
				is_hit_anything = true;
				closest_so_far = object_hit_info.t;
				hit_info = object_hit_info;
			}
		}
		return is_hit_anything;
	}

	size_t HitableList::size() const
	{
		return hitable_list_.size();
	}
}