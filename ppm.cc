#include <stdio.h>

#include <fmt/format.h>

#include "vec3.h"

using u32 = unsigned int;
using i32 = int;
using f32 = float;

class ray {
	public:
		ray(glm::vec3 camera, glm::vec3 dir)
		:camera(camera)
		,dir(dir)
		{}

	public:
		glm::vec3 camera;
		glm::vec3 dir;
};

glm::vec3 ray_color(ray r)
{
	return glm::vec3(0.0f, 0.0f, 0.0f);
}

int main()
{
	using fmt::print;

	/* Display setup */
	const f32 aspect_ratio = 16.0f / 9.0f;
	const u32 image_width = 400;
	const u32 image_height = image_width / aspect_ratio;

	/* Camera */
	const glm::vec3 camera(0.0f, 0.0f, 0.0f);
	const f32 focal_length = 1.0f;

	/* Viewport */
	const f32 vp_width = image_width;
	const f32 vp_height = vp_width / aspect_ratio;
	const glm::vec3 vp_u(vp_width, 0.0f, 0.0f);
	const glm::vec3 vp_v(0.0f, -vp_height, 0.0f);
	const glm::vec3 vp_udelta = vp_u / vp_width;
	const glm::vec3 vp_vdelta = vp_v / vp_height;
	const glm::vec3 vp_topleft = camera + glm::vec3(0.0f, 0.0f, focal_length) - vp_u/2.0f - vp_v/2.0f;
	const glm::vec3 pixel00_loc = vp_topleft + 0.5f * (vp_udelta + vp_vdelta);

	FILE * const output_image = fopen("image.ppm", "wb");
	if (!output_image) {
		perror("fopen");
		return 1;
	}

	print(output_image, "P3\n{} {} \n255\n", image_width, image_height);

	for (u32 j = 0; j < image_height; ++j) {
		//print(stderr, "\rScanlines remaining: {}", image_height - j);
		for (u32 i = 0; i < image_width; ++i) {
			/* Viewport pixel */
			const auto vpp = vp_topleft + f32(i) * vp_udelta + f32(j) * vp_vdelta;

			const auto dir = vpp - camera;
			const auto r = ray(camera, dir);

			if (j == image_height / 2)
				if (i == image_width / 2) {
					print("dir: {} {} {}\n", dir.x, dir.y, dir.z);
					print("vp_topleft: {} {} {}\n", vp_topleft.x, vp_topleft.y, vp_topleft.z);
					print("camera: {} {} {}\n", camera.x, camera.y, camera.z);
				}

			const auto color_u3 = ray_color(r);

			print(output_image, "{} {} {}\n", color_u3.r, color_u3.g, color_u3.b);
		}
	}

	print(stderr, "\rDone                            \n");
}
