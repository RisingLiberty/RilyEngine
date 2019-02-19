#pragma once

#include "../../Graphics/Vertex/Vertex.h"

namespace Content
{
	class Mesh;
}

struct UINT3
{
	UINT3(uint_t _x = 0, uint_t _y = 0, uint_t _z = 0) :
		x(_x),
		y(_y),
		z(_z)
	{
	}

	uint_t x;
	uint_t y;
	uint_t z;

	bool operator==(const UINT3& other) { return x == other.x && y == other.y && z == other.z; }
};

//x == position index
//y == texture index
//z == normal index
struct Triangle
{
	Triangle() = default;

	UINT3 first;
	UINT3 second;
	UINT3 third;
};

namespace Content::Reader
{

class ObjReader
{
public:
	ObjReader() = delete;
	~ObjReader() = delete;

	static Content::Mesh* Read(const std::string& filePath);
	static Math::Vec3 LineToVec3(const std::string& line);
	static Triangle LineToTriangle(const std::string& line);
	static UINT3 ReadVertexIndices(const std::string& line);

	static void CreateVerticesAndIndices(Container::Vector<Triangle>& triangles, Container::Vector<UINT3>& vertices, Container::Vector<uint_t>& indices);
private:
	static const std::string COMMENT_HEADER;
	static const std::string VERTEX_POSITION_HEADER;
	static const std::string VERTEX_NORMAL_HEADER;
	static const std::string VERTEX_UV_HEADER;
	static const std::string INDEX_HEADER;
	static const unsigned int CONTENT_START;
	static const unsigned int FLOAT_PERCISION;

};

}
