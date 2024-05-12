#include <stdio.h>

#include <fmt/format.h>

#include "vec3.h"

int main()
{
	using fmt::print;

	const int image_width = 256;
	const int image_height = 256;

	FILE * const output_image = fopen("image.ppm", "wb");
	if (!output_image) {
		perror("fopen");
		return 1;
	}

	print(output_image, "P3\n{} {} \n255\n", image_width, image_height);

	for (int j = 0; j < image_height; ++j) {
		print(stderr, "\rScanlines remaining: {}", image_height - j);
		for (int i = 0; i < image_width; ++i) {
			auto color = glm::vec3 {
				float(i) / (image_width - 1),
				float(j) / (image_height - 1),
				0.0f
			};

			color *= 255.999f;

			const auto color_u3 = glm::uvec3(color);

			print(output_image, "{} {} {}\n", color_u3.r, color_u3.g, color_u3.b);
		}
	}

	print(stderr, "\rDone                            \n");
}
