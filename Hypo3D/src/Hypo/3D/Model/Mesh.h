#pragma once
#include "Hypo/3D/Exports.h"
#include "Hypo/Graphics/BufferLayout.h"
#include "Hypo/Graphics/Buffers.h"

namespace Hypo
{
	enum VertexTypes : uInt8
	{
		VertexNone = BIT(0),
		VertexPositions = BIT(1),
		VertexTexCoords = BIT(2),
		VertexColors = BIT(3),
		VertexNormals = BIT(4),
		VertexTangents = BIT(5),
		VertexBiTangents = BIT(6),

		VertexPosCol = VertexPositions | VertexColors,
		VertexPosTex = VertexPositions | VertexTexCoords,
		VertexPosTexNorm = VertexPosTex | VertexNormals,
		VertexPosTexNormTang = VertexPosTexNorm | VertexTangents,
		VertexPosTexNormTangBiTang = VertexPosTexNormTang | VertexBiTangents,
	};


	enum class MeshType
	{
		Triangles,
		TriangleFan,
		TriangleStrip,
		Quads,
		Lines,
		LineStrip,
		Points
	};

using VertexTypeFlags = uInt8;	

	AttributeLayout CreateLayoutFromVertexFlags(VertexTypeFlags flags);

	//WARNING: When passing in raw data pointer the alignment of the diffrent vertex properties must follow the MeshTypes order or
	// Position -> TexCoord -> Color ->Normals -> Tangents -> BiTangents
	class HYPO_3D_API Mesh
	{
	public:
		friend class Renderer;
		friend class Scene;
		explicit Mesh() = default;
		Mesh(gsl::span<const ElementIndex> indices, gsl::span<const float> vertices, VertexTypeFlags vertexFlags, MeshType type = MeshType::Triangles);
		
		// TODO: All constructors except the position and tex coord needs to be update  
		Mesh( std::vector<Index>&& indices, const std::vector<Vec3F>&& positions, const std::vector<Vec2F>&& texCoords, MeshType type = MeshType::Triangles);
		Mesh(const std::vector<Index>&& indices, const std::vector<Vec3F>&& positions, const std::vector<Vec4F>&& colors, MeshType type = MeshType::Triangles);
		Mesh(const std::vector<Index>&& indices, const std::vector<Vec3F>&& positions, const std::vector<Vec3F>&& normals, const std::vector<Vec2F>&& texCoords, MeshType type = MeshType::Triangles);
		Mesh(const std::vector<Index>&& indices, const std::vector<Vec3F>&& positions, const std::vector<Vec3F>&& normals, const std::vector<Vec2F>&& texCoords, const std::vector<Vec3F>&& tangents, MeshType type = MeshType::Triangles);
		Mesh(const std::vector<Index>&& indices, const std::vector<Vec3F>&& positions, const std::vector<Vec3F>&& normals, const std::vector<Vec2F>&& texCoords, const std::vector<Vec3F>&& tangents, const std::vector<Vec3F>&& biTangents, MeshType type = MeshType::Triangles);
		explicit Mesh(VertexArray::Ptr va, VertexTypeFlags flags);

		void Bind() const;
		void UnBind() const;

		inline void SetMeshType(MeshType type) { m_Type = type; }
		inline MeshType GetMeshType() const { return m_Type; }
		inline VertexTypeFlags GetFlags() const { return m_Flags; }
	private:
		void SetupVertexArray(const std::vector<Index>&& indices, float* vertices, std::size_t size, BufferLayout&& layout);

		MeshType m_Type = MeshType::Triangles;
		VertexTypeFlags m_Flags;
		VertexArray::Ptr m_VertexArray;
	};

	class HYPO_3D_API MeshFactory
	{
	public:
		//TODO: Implement more geometry shapes and include things such as normals and tangents for the meshes
		static Mesh CreatePlane(VertexTypeFlags flags = VertexPosTex, float size = 0.5, std::array<Vec4F,4> colors = { Vec4F{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1} });
		static Mesh CreateUVSphere(VertexTypeFlags flags, unsigned short slices, unsigned short stacks, float radius);
		static Mesh CreateCube(VertexTypeFlags flags = VertexPosTex, float size = 0.5, std::array<Vec4F, 4> colors = { Vec4F{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1} });
		
	};
}
