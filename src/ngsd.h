

#include "../lib/json.hpp"

#include <string>
#include <fstream>


namespace ngsd {

	using json = nlohmann::json;
	json m_NgsdJson;




	struct Sampler {
		int32_t magFilter = -1;
		int32_t minFilter = -1;
		int32_t wrapS = -1;
		int32_t wrapT = -1;
	};






	struct Image {
		std::string uri = "";
	};








	struct Texture {
		int32_t samplerIndex = -1;
		int32_t imageIndex = -1;
	};








	struct Material {
		std::string name;
		struct {
			std::array<float, 4> baseColorFactor = {-1.0f, -1.0f, -1.0f, -1.0f};
			struct {
				int32_t index = -1;
				int32_t texCoord = -1;
			} baseColorTexture;

			float metallicFactor = -1.0f;
			float roughnessFactor = -1.0f;
			struct {
				int32_t index = -1;
				int32_t texCoord = -1;
			} metallicRoughnessTexture;

		} pbrMetallicRoughness;

		struct {
			float scale = 0.0f;
			int32_t index = -1;
			int32_t texCoord = -1;
		} normalTexture;

		std::array<float, 3> emissiveFactor = {-1.0f, -1.0f, -1.0f};

	};









	struct Primitive {
		uint32_t firstIndex;
		uint32_t indexCount;
		uint32_t materialIndex;
	};





	struct Mesh {
		std::string name;
		std::vector<Primitive> primitives;
	};





	struct Node {
		std::string name;

		std::array<float, 16> matrix4x4;

		uint32_t meshIndex;

		std::vector<uint32_t> childNodeIndices;

	};






	struct Scene {
	public:

		Scene(std::string& ngsdPath) {
			std::ifstream i(ngsdPath);
			i >> m_NgsdJson;

		}

	private:
		std::string name;
		std::vector<Node> nodes;
		std::vector<Mesh> meshes;
		std::vector<Material> materials;
		std::vector<Texture> textures;
		std::vector<Image> images;
		std::vector<Sampler> samplers;

	};



}


namespace ngsd {

	using json = nlohmann::json;

	void to_json(json& j, const ngsd::Sampler& s) {
		j = json{ {"magFilter", s.magFilter},{"minFilter", s.minFilter},{"wrapS", s.wrapS},{"wrapT", s.wrapT} };
	}

	void from_json(const json& j, ngsd::Sampler& s) {
		j.at("magFilter").get_to(s.magFilter);
		j.at("minFilter").get_to(s.minFilter);
		j.at("wrapS").get_to(s.wrapS);
		j.at("wrapT").get_to(s.wrapT);
	}



	void to_json(json& j, const ngsd::Image& i) {
		j = json{ {"uri", i.uri} };
	}

	void from_json(const json& j, ngsd::Image& i) {
		j.at("uri").get_to(i.uri);
	}




	void to_json(json& j, const ngsd::Texture& t) {
		j = json{ {"samplerIndex", t.samplerIndex},{"imageIndex", t.imageIndex} };
	}

	void from_json(const json& j, ngsd::Texture& t) {
		j.at("samplerIndex").get_to(t.samplerIndex);
		j.at("imageIndex").get_to(t.imageIndex);
	}



	void to_json(json& j, const ngsd::Material& m) {
		j = json{
			{"name", m.name},
			{"pbrMetallicRoughness",
				{"baseColorFactor", m.pbrMetallicRoughness.baseColorFactor},
				{"baseColorTexture",
					{"index", m.pbrMetallicRoughness.baseColorTexture.index},
					{"texCoord", m.pbrMetallicRoughness.baseColorTexture.texCoord}
				},
				{"metallicFactor", m.pbrMetallicRoughness.metallicFactor},
				{"roughnessFactor", m.pbrMetallicRoughness.roughnessFactor},
				{"metallicRoughnessTexture",
					{"index", m.pbrMetallicRoughness.metallicRoughnessTexture.index},
					{"texCoord", m.pbrMetallicRoughness.metallicRoughnessTexture.texCoord}
				}
			},
			{"normalTexture",
				{"scale", m.normalTexture.scale},
				{"index", m.normalTexture.index},
				{"texCoord", m.normalTexture.texCoord}
			},
			{"emissiveFactor", m.emissiveFactor}
		};
	}

	void from_json(const json& j, ngsd::Material& m) {
		j.at("name").get_to(m.name);
	}

}





