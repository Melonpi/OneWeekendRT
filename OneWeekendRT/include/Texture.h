#ifndef OW_TEXTURE_H
#define OW_TEXTURE_H

#include "Types.h"
#include "Misc.h"
#include "Vec3.h"
#include <memory>
#include <math.h>

namespace ow
{
	class Texture : public Noncopyable
	{
	public:
		virtual Vec3 value(real u, real v, const Vec3& p) const = 0;
	};

	class ConstantTexture : public Texture
	{
	public:
		explicit ConstantTexture(const Vec3& color)
			:color(color)
		{}

		virtual Vec3 value(real u, real v, const Vec3& p) const override
		{
			return color;
		}
	private:
		Vec3 color;
	};

	class CheckerTexture : public Texture
	{
	public:
		CheckerTexture() {}
		CheckerTexture(std::unique_ptr<Texture>&& tex_odd, std::unique_ptr<Texture>&& tex_even)
			:tex_odd_(std::move(tex_odd)), tex_even_(std::move(tex_even))
		{
		}
		virtual Vec3 value(real u, real v, const Vec3& p) const override
		{
			real sines = sin(10 * p.x) * sin(10 * p.y) * sin(10 * p.z);
			if (sines < 0)
			{
				return tex_odd_->value(u, v, p);
			}else{
				return tex_even_->value(u, v, p);
			}
		}
	private:
		std::unique_ptr<Texture> tex_odd_;
		std::unique_ptr<Texture> tex_even_;
	};
}

#endif//OW_TEXTURE_H