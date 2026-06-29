#include <vector>
#include <cstdint>
#include <fstream>
struct __attribute__((packed)) pixel {
	uint8_t r, g, b;
	pixel obter_invertido() const {
		return pixel{
			static_cast<uint8_t>(255 - r),
			static_cast<uint8_t>(255 - g),
			static_cast<uint8_t>(255 - b)
		};
	}
};
void ppm(const char* name, const std::vector<pixel>& pixels, int lon, int on) {
	std::ofstream fp(name, std::ios::binary);
	fp << "P6\n" << lon << " " <<on << "\n255\n";
	fp.write(reinterpret_cast<const char*>(pixels.data()), pixels.size() * sizeof(pixel));
}
std::vector<pixel> load_ppm(const std::string& filename, int width, int height) {
	std::ifstream file(filename, std::ios::binary);
	std::string magic_number;
	file >> magic_number;
	int max_val;
	file >> width >> height >> max_val;
	file.get();
	std::vector<pixel> pixels(width * height);
	file.read(reinterpret_cast<char*>(pixels.data()), pixels.size() * sizeof(pixel));
	return pixels;
}
void pintar_pixel(pixel& pixe, uint8_t cor) {
	pixe.r = cor;
	pixe.g = cor;
	pixe.b = cor;
}
int main() {
	std::vector<pixel> image_in_pixel = load_ppm("invertido.ppm", 4016, 6016);
	size_t total_pixels = image_in_pixel.size(); 
	std::vector<pixel> final_image(total_pixels); 
	for(size_t c = 0; c < total_pixels; ++c) {
		final_image[c] = image_in_pixel[c].obter_invertido();
	}
	ppm("dasdas.ppm", final_image, 4016, 6016);
}

// p6 \n 200 \n 300 \n 255 \n data
