#include "MeshLoader.h"
#include <Runtime/Platform/PlatformFile.h>
#include <Runtime/Platform/PlatformDirectory.h>
#include <Libs/Assimp/include/assimp/scene.h>
#include <Libs/Assimp/include/assimp/Importer.hpp>
#include <Libs/Assimp/include/assimp/postprocess.h>
#include "MeshLoadResult.h"
#include <Runtime/Memory/Memory.h>

namespace Portakal
{
	void MeshLoader::Load(const String& path, const MeshLoadFlags loadFlags,Array<MeshLoadResult>& results)
	{
		if (!PlatformFile::IsExist(path))
			return;

		/*
		* Build importer
		*/
		Assimp::Importer importer;

		/*
		* Build process flags
		*/

		/*
		* Load file
		*/
		std::string stdPath = *path;
		const aiScene* pScene = importer.ReadFile(stdPath, (unsigned int)loadFlags);
		if (pScene == nullptr)
			return;

		/*
		* Collect meshes
		*/
		if (pScene->HasMeshes())
		{
			const unsigned int meshCount = pScene->mNumMeshes;
			for (unsigned int i = 0; i < meshCount; i++)
			{
				const aiMesh* pMesh = pScene->mMeshes[i];
				results.Add({});
				MeshLoadResult& result = results[results.GetCursor() - 1];

				/*
				* Allocate and set memory
				*/
				if (pMesh->HasPositions())
				{
					result.Positions.Reserve(pMesh->mNumVertices);
					Memory::Copy(pMesh->mVertices, result.Positions.GetData(),sizeof(Vector3F)*pMesh->mNumVertices);
				}
				if (pMesh->HasNormals())
				{
					result.Normals.Reserve(pMesh->mNumVertices);
					Memory::Copy(pMesh->mNormals, result.Normals.GetData(), sizeof(Vector3F) * pMesh->mNumVertices);
				}
				if (pMesh->HasTangentsAndBitangents())
				{
					result.Tangents.Reserve(pMesh->mNumVertices);
					result.Bitangents.Reserve(pMesh->mNumVertices);
					Memory::Copy(pMesh->mTangents, result.Tangents.GetData(), sizeof(Vector3F) * pMesh->mNumVertices);
					Memory::Copy(pMesh->mBitangents, result.Bitangents.GetData(), sizeof(Vector3F) * pMesh->mNumVertices);
				}
				if (pMesh->HasTextureCoords(0))
				{
					result.TextureCoordinates.Reserve(pMesh->mNumVertices);
					Memory::Copy(pMesh->mTextureCoords[0], result.TextureCoordinates.GetData(), sizeof(Vector2F) * pMesh->mNumVertices);
				}
			}
		}

		/*
		* Collect textures
		*/
		if (pScene->HasTextures())
		{
			const unsigned int textureCount = pScene->mNumTextures;
			for (unsigned int i = 0; i < textureCount; i++)
			{
				const aiTexture* pTexture = pScene->mTextures[i];
			}
		}
	}
}