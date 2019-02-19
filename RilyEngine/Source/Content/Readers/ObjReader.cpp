#include "stdafx.h"

#include "ObjReader.h"

#include "Content/Mesh.h"

#include "Resources/Files/TextFile.h"


namespace Content::Reader
{


	const std::string ObjReader::COMMENT_HEADER = "# ";
	const std::string ObjReader::VERTEX_POSITION_HEADER = "v ";
	const std::string ObjReader::VERTEX_NORMAL_HEADER = "vn";
	const std::string ObjReader::VERTEX_UV_HEADER = "vt";
	const std::string ObjReader::INDEX_HEADER = "f ";
	const unsigned int ObjReader::CONTENT_START = 3;
	const unsigned int ObjReader::FLOAT_PERCISION = 4;

	Content::Mesh* ObjReader::Read(const std::string& filePath)
	{
		Container::Vector<Graphics::Vertex::Vertex*> vertices;

		Resources::TextFile objFile(filePath);
		if (!objFile.Exists())
		{
			Debug::Log(Debug::LogType::WARNING, "Obj file with path ", filePath, " does not exists\n");
			return nullptr;
		}

		objFile.Open(std::ios::in);

		Container::Vector<Math::Vec3> positions;
		Container::Vector<Math::Vec3> normals;
		Container::Vector<Math::Vec3> texCoords;
		Container::Vector<Triangle> triangles;
		Container::Vector<uint_t> indices;


		while (!objFile.EndOfFile())
		{
			std::string line = objFile.ReadLine();
			std::string lineHeader = line.substr(0, 2);

			if (lineHeader == COMMENT_HEADER) //comment
				continue;
			else if (lineHeader == VERTEX_POSITION_HEADER) //vertex position
				positions.AddM(LineToVec3(line));
			else if (lineHeader == VERTEX_NORMAL_HEADER)
				normals.AddM(LineToVec3(line));
			else if (lineHeader == VERTEX_UV_HEADER)
				texCoords.AddM(LineToVec3(line));
			else if (lineHeader == INDEX_HEADER)
				triangles.AddM(LineToTriangle(line));
		}

		Container::Vector<UINT3> verticesidx;
		CreateVerticesAndIndices(triangles, verticesidx, indices);

		for (UINT3 idx : verticesidx)
		{
			Math::Vec3 pos = positions[idx.x - 1];

			Math::Vec3 texCoord;
			if (!texCoords.IsEmpty())
				texCoord = texCoords[idx.y - 1];

			Math::Vec3 normal;
			if (!normals.IsEmpty())
				normal = normals[idx.z - 1];

			Graphics::Vertex::Vertex* pVertex = new Graphics::Vertex::Vertex();
			pVertex->Push(Graphics::Vertex::VertexAttribute::DEFAULT_POSITION);
			pVertex->Push(Graphics::Vertex::VertexAttribute::DEFAULT_TEXCOORD);
			pVertex->Push(Graphics::Vertex::VertexAttribute::DEFAULT_NORMAL);

			float data[8]
			{
				pos.x, pos.y, pos.z,
				texCoord.x, texCoord.y,
				normal.x, normal.y, normal.z
			};

			pVertex->SetData(data, sizeof(float) * 8);
			vertices.AddC(pVertex);
		}

		return new Mesh(vertices, indices);
	}

	Math::Vec3 ObjReader::LineToVec3(const std::string& line)
	{
		uint_t xEnd = line.find(' ', CONTENT_START);
		uint_t yEnd = line.find(' ', xEnd + 1);

		std::string xStr = line.substr(CONTENT_START, xEnd - CONTENT_START);
		std::string yStr = line.substr(xEnd + 1, yEnd - xEnd);
		std::string zStr = line.substr(yEnd + 1);

		float x = std::stof(xStr);
		float y = std::stof(yStr);
		float z = std::stof(zStr);

		return Math::Vec3(x, y, z);
	}

	Triangle ObjReader::LineToTriangle(const std::string& line)
	{
		//f 1/1/1 2/2/2 3/3/3/

		int dataPos = line.find_first_of(' ') + 1;

		Triangle triangle;

		uint_t firstEnd = line.find_first_of(' ', dataPos);
		uint_t secondEnd = line.find_first_of(' ', firstEnd + 1);

		std::string first = line.substr(dataPos, firstEnd - dataPos);
		std::string second = line.substr(firstEnd + 1, secondEnd - firstEnd);
		std::string third = line.substr(secondEnd + 1);

		//pop space
		third.pop_back();

		triangle.first = ReadVertexIndices(first);
		triangle.second = ReadVertexIndices(second);
		triangle.third = ReadVertexIndices(third);

		return triangle;
	}

	UINT3 ObjReader::ReadVertexIndices(const std::string& line)
	{
		uint_t firstSlash = line.find('/');
		uint_t secondSlash = line.find('/', firstSlash + 1);

		std::string xStr = line.substr(0, firstSlash);
		std::string yStr = line.substr(firstSlash + 1, secondSlash - firstSlash - 1);
		std::string zStr = line.substr(secondSlash + 1);

		uint_t x = 1;
		uint_t y = 1;
		uint_t z = 1;

		x = std::stoul(xStr); //this is also the index

		if (!yStr.empty())
			y = std::stoul(yStr);

		if (!zStr.empty())
			z = std::stoul(zStr);

		return UINT3(x, y, z);
	}

	void ObjReader::CreateVerticesAndIndices(Container::Vector<Triangle>& triangles, Container::Vector<UINT3>& vertices, Container::Vector<uint_t>& indices)
	{
		for (Triangle triangle : triangles)
		{
			auto first = std::find_if(vertices.Begin(), vertices.End(),
				[&](UINT3 idx)
			{
				return idx == triangle.first;
			});

			if (first == vertices.End())
			{
				vertices.AddC(triangle.first);
				indices.AddM(vertices.Count() - 1);
			}

			else
				indices.AddM(std::distance(vertices.Begin(), first));

			auto second = std::find_if(vertices.Begin(), vertices.End(),
				[&](UINT3 idx)
			{
				return idx == triangle.second;
			});

			if (second == vertices.End())
			{
				vertices.AddC(triangle.second);
				indices.AddM(vertices.Count() - 1);
			}
			else
				indices.AddM(std::distance(vertices.Begin(), second));

			auto third = std::find_if(vertices.Begin(), vertices.End(),
				[&](UINT3 idx)
			{
				return idx == triangle.third;
			});

			if (third == vertices.End())
			{
				vertices.AddC(triangle.third);
				indices.AddM(vertices.Count() - 1);
			}
			else
				indices.AddM(std::distance(vertices.Begin(), third));
		}
	}

}
