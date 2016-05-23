#ifndef OW_HITABLE_LIST_H
#define OW_HITABLE_LIST_H

#include "Hitable.h"
#include <memory>
#include <vector>

namespace ow
{
	class HitableList final : public Hitable
	{
	public:
		HitableList();
		~HitableList();

		virtual bool hit(const Ray& ray, real t_min, real t_max, HitInfo& hit_info) const override;
		void add(std::unique_ptr<Hitable> hitable);
		size_t size() const;
	private:
		std::vector< std::unique_ptr<Hitable> > hitable_list_;
	};
}

#endif//OW_HITABLE_LIST_H