

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
		struct PbrMetallicRoughness {
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

		struct NormalTexture {
			float scale = 0.0f;
			int32_t index = -1;
			int32_t texCoord = -1;
		} normalTexture;

		std::array<float, 3> emissiveFactor = {-1.0f, -1.0f, -1.0f};
	};


	struct Primitive {
		int32_t firstIndex = -1;
		int32_t indexCount = -1;
		int32_t materialIndex = -1;
	};


	struct Mesh {
		std::string name;
		std::vector<Primitive> primitives;
	};


	struct Node {
		std::string name;

		std::array<float, 16> matrix4x4;

		int32_t meshIndex;

		std::vector<int32_t> childNodeIndices;

	};


	struct Scene {
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
		//j = json{ {"magFilter", s.magFilter},{"minFilter", s.minFilter},{"wrapS", s.wrapS},{"wrapT", s.wrapT} };
		j["magFilter"] = s.magFilter;
		j["minFilter"] = s.minFilter;
		j["wrapS"] = s.wrapS;
		j["wrapT"] = s.wrapT;
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
				{
					{"baseColorFactor", m.pbrMetallicRoughness.baseColorFactor},
					{"baseColorTexture",
						{
							{"index", m.pbrMetallicRoughness.baseColorTexture.index},
							{"texCoord", m.pbrMetallicRoughness.baseColorTexture.texCoord}
						}
					},
					{"metallicFactor", m.pbrMetallicRoughness.metallicFactor},
					{"roughnessFactor", m.pbrMetallicRoughness.roughnessFactor},
					{"metallicRoughnessTexture", 
						{
							{"index", m.pbrMetallicRoughness.metallicRoughnessTexture.index},
							{"texCoord", m.pbrMetallicRoughness.metallicRoughnessTexture.texCoord}
						}
					}
				}
			},
			{"normalTexture", 
				{
					{"scale", m.normalTexture.scale},
					{"index", m.normalTexture.index},
					{"texCoord", m.normalTexture.texCoord}
				}
			},
			{"emissiveFactor", m.emissiveFactor}
		};
	}

	void from_json(const json& j, ngsd::Material& m) {
		j.at("name").get_to(m.name);

		// metallicRoughness
		{
			auto& pbrm = m.pbrMetallicRoughness;
			auto jpbr = j["pbrMetallicRoughness"];
			jpbr.at("baseColorFactor").get_to(pbrm.baseColorFactor);

			jpbr.at("baseColorTexture").at("index").get_to(pbrm.baseColorTexture.index);
			jpbr.at("baseColorTexture").at("texCoord").get_to(pbrm.baseColorTexture.texCoord);

			jpbr.at("metallicFactor").get_to(pbrm.metallicFactor);
			jpbr.at("roughnessFactor").get_to(pbrm.roughnessFactor);

			jpbr.at("metallicRoughnessTexture").at("index").get_to(pbrm.metallicRoughnessTexture.index);
			jpbr.at("metallicRoughnessTexture").at("texCoord").get_to(pbrm.metallicRoughnessTexture.texCoord);
		}

		j.at("normalTexture").at("scale").get_to(m.normalTexture.scale);
		j.at("normalTexture").at("index").get_to(m.normalTexture.index);
		j.at("normalTexture").at("texCoord").get_to(m.normalTexture.texCoord);

		j.at("emissiveFactor").get_to(m.emissiveFactor);
	}



	void to_json(json& j, const ngsd::Primitive& p) {
		j = json{ {"firstIndex", p.firstIndex}, {"indexCount", p.indexCount}, {"materialIndex", p.materialIndex} };
	}

	void from_json(const json& j, ngsd::Primitive& p) {
		j.at("firstIndex").get_to(p.firstIndex);
		j.at("indexCount").get_to(p.indexCount);
		j.at("materialIndex").get_to(p.materialIndex);
	}


	void to_json(json& j, const ngsd::Mesh& m) {
		j = json{ {"name", m.name}, {"primitives", m.primitives} };
	}

	void from_json(const json& j, ngsd::Mesh& m) {
		j.at("name").get_to(m.name);
		j.at("primitives").get_to(m.primitives);
	}



	void to_json(json& j, const ngsd::Node& n) {
		j = json{ {"name", n.name}, {"matrix4x4", n.matrix4x4}, 
			{"meshIndex", n.meshIndex}, {"childNodeIndices", n.childNodeIndices} };
	}

	void from_json(const json& j, ngsd::Node& n) {
		j.at("name").get_to(n.name);
		j.at("matrix4x4").get_to(n.matrix4x4);
		j.at("meshIndex").get_to(n.meshIndex);
		j.at("childNodeIndices").get_to(n.childNodeIndices);
	}



	void to_json(json& j, const ngsd::Scene& s) {
		j = json{ {"name", s.name}, {"nodes", s.nodes}, {"meshes", s.meshes}, {"materials", s.materials},
			{"textures", s.textures}, {"images", s.images}, {"samplers", s.samplers} };
	}

	void from_json(const json& j, ngsd::Scene& s) {
		j.at("name").get_to(s.name);
		j.at("nodes").get_to(s.nodes);
		j.at("meshes").get_to(s.meshes);
		j.at("materials").get_to(s.materials);
		j.at("textures").get_to(s.textures);
		j.at("images").get_to(s.images);
		j.at("samplers").get_to(s.samplers);
	}




}





