#include "hypo3dpch.h"
#include "mesh.h"
#include <glm/glm.hpp>


#include <glm/gtc/constants.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Hypo/System/Util/Log.h"


#include "gsl/gsl"
#include "gsl/span_ext"

namespace Hypo
{
	AttributeLayout CreateLayoutFromVertexFlags(VertexTypeFlags flags)
	{
		std::vector<BufferElement> elements;
		if (flags & VertexPositions)
		{
			elements.push_back(BufferElement{ ShaderDataType::Float3, "a_Position" });
		}
		if (flags & VertexTexCoords)
		{
			elements.push_back(BufferElement{ ShaderDataType::Float2, "a_TexCoord" });
		}
		if (flags & VertexColors)
		{
			elements.push_back(BufferElement{ ShaderDataType::Float3, "a_Color" });
		}
		if (flags & VertexNormals)
		{
			elements.push_back(BufferElement{ ShaderDataType::Float3, "a_Normal" });
		}
		if (flags & VertexTangents)
		{
			elements.push_back(BufferElement{ ShaderDataType::Float3, "a_Tangent" });
		}
		if (flags & VertexBiTangents)
		{
			elements.push_back(BufferElement{ ShaderDataType::Float3, "a_BiTangent" });
		}
		AttributeLayout layout{ elements };
		return layout;
	}

	Mesh::Mesh(gsl::span<const ElementIndex> indices, gsl::span<const float> vertices, VertexTypeFlags vertexFlags, MeshType type)
		:m_Flags(vertexFlags), m_Type(type)
	{
		auto index = IndexBuffer::Create(indices, BufferUsage::Static);
		auto vertex = VertexBuffer::Create(vertices, BufferUsage::Static);
		vertex->SetLayout(CreateLayoutFromVertexFlags(vertexFlags));
		m_VertexArray = VertexArray::Create();
		m_VertexArray->SetIndexBuffer(index);
		m_VertexArray->AddVertexBuffer(vertex);
		UnBind();
	}

	Mesh::Mesh(const std::vector<Index>&& indices, const std::vector<Vec3F>&& positions,
		const std::vector<Vec2F>&& texCoords, MeshType type)
		: m_Flags(VertexPositions | VertexTexCoords ), m_Type(type)
	{		
		HYPO_CORE_ASSERT(positions.size() == texCoords.size(), "[Mesh] verticies components vector sizes is diffrent! Make sure the positions texCoord normal vectors have the same length!")
		struct Vertex
		{
			Vec3F position;
			Vec2F texCoord;
		};

		int count = static_cast<int>(positions.size());
		int size = count * (3 + 2);

		float* verticies = new float[size];
		Vertex* vertex = reinterpret_cast<Vertex*>(verticies);
		
		for (int i = 0; i < count; i ++)
		{
			vertex->position = positions[i];
			vertex->texCoord = texCoords[i];
			vertex++;
		}
		BufferLayout layout{
			{  ShaderDataType::Float3,"a_Position"},
			{ ShaderDataType::Float2,"a_TexCoord"}
		};
		SetupVertexArray(std::move(indices), verticies, size * sizeof(float), std::move(layout));
		
		delete[] verticies;

	}

	Mesh::Mesh(const std::vector<Index>&& indices, const std::vector<Vec3F>&& positions,
		const std::vector<Vec4F>&& colors, MeshType type)
		: m_Flags(VertexPositions | VertexColors), m_Type(type)
	{
		HYPO_CORE_ASSERT(positions.size() != colors.size(), "[Mesh] verticies components vector sizes is diffrent! Make sure the positions texCoord normal vectors have the same length!")
		struct Vertex
		{
			Vec3F position;
			Vec4F color;
		};
		int count = static_cast<int>(positions.size());
		int size = count * (3 + 4);

		float* verticies = new float[size];
		
		Vertex* vertex = reinterpret_cast<Vertex*>(verticies);

		for (int i = 0; i < count; i++)
		{
			vertex->position = positions[i];
			vertex->color = colors[i];
			vertex++;
		}
		BufferLayout layout{
			{  ShaderDataType::Float3,"a_Position"},
			{ ShaderDataType::Float4,"a_Color"}
		};
		SetupVertexArray(std::move(indices), verticies, size, std::move(layout));

	}

	Mesh::Mesh(const std::vector<Index>&& indices, const std::vector<Vec3F>&& positions,
		const std::vector<Vec3F>&& normals, const std::vector<Vec2F>&& texCoords, MeshType type)
		: m_Flags(VertexPositions | VertexNormals | VertexTexCoords), m_Type(type)
	{

		HYPO_CORE_ASSERT(positions.size() != normals.size() && positions.size() != texCoords.size(), "[Mesh] verticies components vector sizes is diffrent! Make sure the positions texCoord normal vectors have the same length!")
		struct Vertex
		{
			Vec3F position;
			Vec3F normal;
			Vec2F texCoord;
		};

	
		int count = static_cast<int>(positions.size());
		int size = count * (3 + 3 + 2);

		float* verticies = new float[size];

		Vertex* vertex = reinterpret_cast<Vertex*>(verticies);

		for (int i = 0; i < count; i++)
		{
			vertex->position = positions[i];
			vertex->normal = normals[i];
			vertex->texCoord = texCoords[i];
			vertex++;
		}
		BufferLayout layout{
			{  ShaderDataType::Float3,"a_Position"},
			{ ShaderDataType::Float3,"a_Normal"},
			{ ShaderDataType::Float2,"a_TexCoord"}
		};
		SetupVertexArray(std::move(indices), verticies, size, std::move(layout));
	}

	Mesh::Mesh(const std::vector<Index>&& indices, const std::vector<Vec3F>&& positions,
		const std::vector<Vec3F>&& normals, const std::vector<Vec2F>&& texCoords, const std::vector<Vec3F>&& tangents, MeshType type)
		: m_Flags(VertexPositions | VertexNormals | VertexTexCoords | VertexTangents), m_Type(type)
	{
		HYPO_CORE_ASSERT(positions.size() != normals.size() && positions.size() != texCoords.size(), "[Mesh] verticies components vector sizes is diffrent! Make sure the positions texCoord normal vectors have the same length!")
			struct Vertex
		{
			Vec3F position;
			Vec3F normal;
			Vec2F texCoord;
			Vec3F tangent;
		};
		int count = static_cast<int>(positions.size());
		int size = count * (3 + 3 + 2 + 3);

		float* verticies = new float[size];

		Vertex* vertex = reinterpret_cast<Vertex*>(verticies);

		for (int i = 0; i < count; i++)
		{
			vertex->position = positions[i];
			vertex->normal = normals[i];
			vertex->texCoord = texCoords[i];
			vertex->tangent = tangents[i];
			vertex++;
		}
		BufferLayout layout{
			{  ShaderDataType::Float3,"a_Position"},
			{ ShaderDataType::Float3,"a_Normal"},
			{ ShaderDataType::Float2,"a_TexCoord"},
			{ ShaderDataType::Float3,"a_Tangent"}
		};
		SetupVertexArray(std::move(indices), verticies, size, std::move(layout));

	}

	Mesh::Mesh(const std::vector<Index>&& indices, const std::vector<Vec3F>&& positions,
		const std::vector<Vec3F>&& normals, const std::vector<Vec2F>&& texCoords, const std::vector<Vec3F>&& tangents,
		const std::vector<Vec3F>&& biTangents, MeshType type)
		: m_Flags(VertexPositions | VertexNormals | VertexTexCoords | VertexTangents | VertexBiTangents), m_Type(type)
	{
		HYPO_CORE_ASSERT(positions.size() != normals.size() && positions.size() != texCoords.size(), "[Mesh] verticies components vector sizes is diffrent! Make sure the positions texCoord normal vectors have the same length!")
			struct Vertex
		{
			Vec3F position;
			Vec3F normal;
			Vec2F texCoord;
			Vec3F tangent;
			Vec3F biTangent;
		};
		int count = static_cast<int>(positions.size());
		int size = count * (3 + 3 + 2 + 3 + 3);

		float* verticies = new float[size];

		Vertex* vertex = reinterpret_cast<Vertex*>(verticies);

		for (int i = 0; i < count; i++)
		{
			vertex->position = positions[i];
			vertex->normal = normals[i];
			vertex->texCoord = texCoords[i];
			vertex->tangent = tangents[i];
			vertex->biTangent = biTangents[i];
			vertex++;
		}
		BufferLayout layout{
			{  ShaderDataType::Float3,"a_Position"},
			{ ShaderDataType::Float3,"a_Normal"},
			{ ShaderDataType::Float2,"a_TexCoord"},
			{ ShaderDataType::Float3,"a_Tangent"},
			{ ShaderDataType::Float3,"a_BiTangent"}
		};
		SetupVertexArray(std::move(indices), verticies, size, std::move(layout));
	}

	Mesh::Mesh(VertexArray::Ptr va, VertexTypeFlags flags)
		: m_VertexArray(va), m_Flags(flags), m_Type(MeshType::Triangles)
	{}

	void Mesh::Bind() const
	{
		m_VertexArray->Bind();
	}

	void Mesh::UnBind()
	{
	}

	void Mesh::SetupVertexArray(const std::vector<Index>&& indices, float* vertices, std::size_t size,
		BufferLayout&& layout)
	{
		
		auto index = IndexBuffer::Create(gsl::span<const ElementIndex>(indices.data(), indices.size()), BufferUsage::Static);
		
		auto vertex = VertexBuffer::Create(gsl::span<const float>(vertices, size), BufferUsage::Static);

		vertex->SetLayout(layout);
		m_VertexArray = VertexArray::Create();
		m_VertexArray->SetIndexBuffer(index);
		m_VertexArray->AddVertexBuffer(vertex);
		UnBind();
	}

	Mesh MeshFactory::CreatePlane(VertexTypeFlags flags, float size, std::array<Vec4F,4> color)
	{
		std::vector<Vec3F> positions = { {size,  size, 0.f },{size, -size, 0.f }, {-size,-size,0.f}, {-size, size, 0.f} };
		static std::vector<Vec2F> texCoord = {{1.f, 1.f}, {1.f,0.f}, {0.f,0.f}, {0.f,1.f} };

		static std::vector<Index> indices = { 0,1,3,  1,2,3 };

		switch (flags)						   
		{									   
		case VertexPosTex:					
			{
				Mesh mesh{ std::move(indices), std::move(positions), std::move(texCoord) };
				return mesh;
			}
		case VertexPosCol:
		{

		}
		case VertexPosTexNorm:
		{

		}
		case VertexPosTexNormTang:
		{

		}
		case VertexPosTexNormTangBiTang:
		{

		}
		}
		HYPO_CORE_WARN("Could not create plane!");
		return Mesh{};
	}

	Mesh MeshFactory::CreateUVSphere(VertexTypeFlags flags, unsigned short slices, unsigned short stacks, float radius)
	{
		size_t vertexCount = static_cast<std::size_t>((stacks + 1) * (slices + 1));
		std::vector<Vec3F> vertices(vertexCount);
		std::vector<Vec2F> uvs(vertexCount);
		std::vector<Vec3F> normals(vertexCount);
		std::vector<Vec4F> colors(vertexCount);
		std::vector<Index> indices;

		int index = 0;
		// create vertices
		for (unsigned short j = 0; j <= stacks; j++) {
			float latitude1 = (glm::pi<float>() / stacks) * j - (glm::pi<float>() / 2);
			float sinLat1 = sin(latitude1);
			float cosLat1 = cos(latitude1);
			for (int i = 0; i <= slices; i++) {
				float longitude = ((glm::pi<float>() * 2) / slices) * i;
				float sinLong = sin(longitude);
				float cosLong = cos(longitude);
				Vec3F normal{ cosLong * cosLat1,
					sinLat1,
					sinLong * cosLat1 };
				normal.Normalize();
				normals[index] = normal;
			uvs[index] = Vec2F{ 1 - i / (float)slices, j / (float)stacks };
			vertices[index] = normal * radius;
			colors[index] = Vec4F(normal * 0.5f + Vec3F(0.5f), 1.0f);
			index++;
		}
		}
		// create indices
		for (int j = 0; j < stacks; j++) {
			if (j > 0) {
				indices.push_back(j * (slices + 1)); // make degenerate
			}
			for (int i = 0; i <= slices; i++) {
				index = j * (slices + 1) + i;
				indices.push_back(index);
				indices.push_back(index + slices + 1);
			}
			if (j + 1 < stacks) {
				indices.push_back(index + slices + 1); // make degenerate
			}
		}
		switch (flags)
		{
			case VertexPosTex:
			{
				return Mesh(std::move(indices), std::move(vertices), std::move(uvs), MeshType::TriangleStrip);
				}
			case VertexPosCol:
			{

			}
			case VertexPosTexNorm:
			{

			}
			case VertexPosTexNormTang:
			{

			}
			case VertexPosTexNormTangBiTang:
			{

			}
		}
		HYPO_CORE_WARN("Could not create sphere!");
		return Mesh{};

	}

	Mesh MeshFactory::CreateCube(VertexTypeFlags flags, float size, std::array<Vec4F, 4> colors)
	{
		float vertices[] = { 
			size, size, size,   1,1,
			-size, size, size,  0, 1,
			- size, -size, size, 0, 0,
			size, -size, size,  1, 0 ,  // v0-v1-v2-v3
			size, size, size,	0, 1,
			size, -size, size,	0, 0,
			size, -size, -size,	1, 0,
			size, size, -size,  1, 1,   // v0-v3-v4-v5
			size, size, size,	1, 0,
			size, size, -size,	1, 1,
			- size, size, -size,	0, 1,
			- size, size, size,  0, 0,    // v0-v5-v6-v1
			- size, size, size,	1, 1,
			- size, size, -size,	0, 1,
			- size, -size, -size,0, 0,
			- size, -size, size, 1, 0,    // v1-v6-v7-v2
			- size, -size, -size,1, 1,
			size, -size, -size,	0, 1,
			size, -size, size,	0, 0,
			- size, -size, size, 1, 0,    // v7-v4-v3-v2
			size, -size, -size,	0, 0,
			- size, -size, -size,1, 0,
			- size, size, -size,	1, 1,
			size, size, -size ,  0, 1    // v4-v7-v6-v5
		};

		Index indices[] = {
			 0, 1, 2,
			0, 2, 3,
			4, 5, 6,
			4, 6, 7,
			8, 9, 10,
			8, 10, 11,
			12, 13, 14,
			12, 14, 15,
			16, 17, 18,
			16, 18, 19,
			20, 21, 22,
			20, 22, 23
		};
		flags = VertexPosTex;
		return Mesh(indices, vertices, flags);

		switch (flags)
		{
		case VertexPositions:
		{
		}
		case VertexPosCol:
		{

		}
		case VertexPosTexNorm:
		{

		}
		case VertexPosTexNormTang:
		{

		}
		case VertexPosTexNormTangBiTang:
		{

		}
		}
		HYPO_CORE_WARN("Could not create cube!");
		return Mesh{};

	}
}


/*
   // normals         
 0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,

	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,

	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,*/