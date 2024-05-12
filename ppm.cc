#include <stdio.h>

#include <fmt/format.h>

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
			const auto r = double(i) / (image_width - 1);
			const auto g = double(j) / (image_height - 1);
			const auto b = 0.0;

			const auto ir = int(255.999 * r);
			const auto ig = int(255.999 * g);
			const auto ib = int(255.999 * b);

			print(output_image, "{} {} {}\n", ir, ig, ib);
		}
	}

	print(stderr, "\rDone                            \n");
}
