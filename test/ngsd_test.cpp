
#include "../src/ngsd.h"

#include <iostream>
#include <iomanip>
#include <istream>
#include <ostream>

void addNGSD() {
	ngsd::json j;
	//ngsd::Material m;
	//ngsd::to_json(j, m);

	ngsd::Scene scene;

	//Sampler
	{
		ngsd::Sampler sampler;
		sampler.magFilter = 2;
		sampler.wrapS = 10;
		scene.samplers.push_back(sampler);
	}

	//Images
	{
		ngsd::Image image;
		image.uri = "hello1.ktx";
		scene.images.push_back(image);
		image.uri = "gello2.ktx";
		scene.images.push_back(image);
		image.uri = "fello3.ktx";
		scene.images.push_back(image);
	}

	//Textures
	{
		ngsd::Texture texture;
		texture.samplerIndex = 0;
		texture.imageIndex = 1;
		scene.textures.push_back(texture);
		texture.imageIndex = 2;
		scene.textures.push_back(texture);
	}

	//Materials
	{
		ngsd::Material material;
		material.name = "gold_0";
		material.emissiveFactor[0] = 3;
		scene.materials.emplace_back(material);
	}

	//Meshes
	{
		ngsd::Primitive prim;
		prim.firstIndex = 0;

		ngsd::Mesh mesh;
		mesh.name = "mesh1";
		mesh.primitives.push_back(prim);
		prim.indexCount = 10;
		mesh.primitives.push_back(prim);
		scene.meshes.push_back(mesh);
		mesh.primitives.pop_back();
		mesh.name = "mesh2";
		scene.meshes.push_back(mesh);
	}

	//Nodes
	{
		ngsd::Node node;
		node.name = "node1";
		node.meshIndex = 0;
		scene.nodes.push_back(node);
	}

	//Scene properties
	scene.name = "scene1";

	j["scene"] = scene;
	j["header"] = "NGSD is a file format for storing scene information for NextGengine";


	std::string str = j.dump(1, '\t');

	std::cout << str << std::endl;
	
	std::ofstream o("test.ngsd");
	o << std::setw(4) << j << std::endl;

}

void loadNGSD() {
	std::ifstream i("test.ngsd");
	ngsd::json j;
	i >> j;

	ngsd::Scene s = j["scene"];

	int a = 10;

}

int main() {
	addNGSD();
	loadNGSD();
}