#include <new>
#include "AssetManager.hpp"
#include "../Math.hpp"
#include "../Memory/MemoryManager.hpp"

namespace KFTG
{

// AssetRegistry

AssetRegistry* AssetRegistry::instance ()
{
	static AssetRegistry _instance;
	return &_instance;
}

void AssetRegistry::addAsset (const GUID &uid, void *asset)
{
	_registry.add (uid, asset);
}

void AssetRegistry::deleteAsset (GUID uid)
{
	_registry.remove (uid);
}

void* AssetRegistry::queryAsset (const GUID &uid)
{
	return _registry.query (uid);
}

// AssetLoader

AssetLoader::AssetLoader ()
{
	_fs = Filesystem::instance ();
	_assetRegistry = AssetRegistry::instance ();
}

AssetLoader::~AssetLoader ()
{
	delete _fs;
}

AssetLoader* AssetLoader::instance ()
{
	static AssetLoader _instance;
	return &_instance;
}

// TODO: load asset from data files

void AssetLoader::loadAsset (const string &path)
{
	u32 dataSize = _fs->getFileSize (path);
	char *data = (char*) MemoryManager::instance ()->allocAsset (dataSize);
	_fs->syncRead (path + ".index", data, dataSize);

	u32 indexSize = _fs->getFileSize (path + ".index");
	char *index = (char*) MemoryManager::instance ()->allocScene (indexSize);
	_fs->syncRead (path + ".index", index, indexSize);

	u8 state = 0;
	for (u32 i = 0; i < indexSize; ++i)
	{
		while (index[i] != '[')
			++i;
		while (index[i] != '"')
			++i;
		++i;

		u32 len = 0;
		while (index[i] != '"')
		{
			++i;
			++len;
		}
		string uid = string (index + i - len, len);
		while (index[i] != ',')
			++i;
		while (index[i] == ' ' || index[i] == '\t' || index[i] == '\n')
			++i;
		u8 type = 0;
		while (index[i] >= '0' && index[i] <= '9')
		{
			type = type * 10 + index[i] - 48;
			++i;
		}
		while (index[i] != ',')
			++i;
		while (index[i] == ' ' || index[i] == '\t' || index[i] == '\n')
			++i;
		u32 pointer = 0;
		while (index[i] >= '0' && index[i] <= '9')
		{
			pointer = pointer * 10 + index[i] - 48;
			++i;
		}
		while (index[i] != ']')
			++i;
		++i;

		void *asset = data + pointer;
		_assetRegistry->addAsset (uid, asset);
		switch (type)
		{
			case (u8) AssetType::IMAGE:
				initImage ((Image*) asset, data);
				break;
			case (u8) AssetType::ANIMATION:
				initAnimation ((Animation*) asset, data);
				break;
			case (u8) AssetType::AUDIO:
				initAudio ((Audio*) asset, data);
				break;
			case (u8) AssetType::XML:
				initXML ((XML*) asset, data);
				break;
			default:
				break;
		}
	}

	MemoryManager::instance ()->freeScene ();
}

void AssetLoader::initImage (Image *asset, char *o)
{
}

void AssetLoader::initAnimation (Animation *asset, char *o)
{
	for (int i = 0; i < asset->len; ++i)
		asset->ani[i].img = (Image*) (o + (u64) asset->ani[i].img);
}

void AssetLoader::initAudio (Audio *asset, char *o)
{
}

void AssetLoader::initXML (XML *asset, char *o)
{
	asset->root = (XML::Node*) (o + (u64) asset->root);
	initXMLNode (asset->root, o);
}

void AssetLoader::initXMLNode (XML::Node *asset, char *o)
{
	typedef XML::Node::Attribute Attr;
	Attr *attr = asset->attrs;
	if (attr != nullptr)
		asset->attrs = (Attr*) (o + (u64) asset->attrs);
	while (attr != nullptr)
	{
		if (attr->type == Attr::Type::STRING)
			attr->value.s.setCStr (o + (u64) attr->value.s.getCStr ());
		attr->next = (Attr*) (o + (u64) attr->next);
		attr = attr->next;
	}
	asset->tag.setCStr (o + (u64) asset->tag.getCStr ());
	asset->value.setCStr (o + (u64) asset->value.getCStr ());
	if (asset->parent != nullptr)
		asset->parent = (XML::Node*) (o + (u64) asset->parent);
	if (asset->firstChild != nullptr)
		asset->firstChild = (XML::Node*) (o + (u64) asset->firstChild);
	if (asset->lastChild != nullptr)
		asset->lastChild = (XML::Node*) (o + (u64) asset->lastChild);
	if (asset->prevSibling != nullptr)
		asset->prevSibling = (XML::Node*) (o + (u64) asset->prevSibling);
	if (asset->nextSibling != nullptr)
		asset->nextSibling = (XML::Node*) (o + (u64) asset->nextSibling);

	if (asset->firstChild)
		initXMLNode (asset->firstChild, o);
	if (asset->nextSibling)
		initXMLNode (asset->nextSibling, o);
}

// RawAssetLoader
// TODO: load asset from raw asset files

RawAssetLoader::RawAssetLoader ()
{
}

RawAssetLoader::~RawAssetLoader ()
{
}

// AssetPacker
// TODO: Pack cooked assets into data files

AssetPacker::AssetPacker ()
{
}

AssetPacker::~AssetPacker ()
{
}

// AssetManager

AssetManager* AssetManager::instance ()
{
	static AssetManager _instance;
	return &_instance;
}

void AssetManager::init ()
{
	_assetRegistry = AssetRegistry::instance ();
	_assetLoader = AssetLoader::instance ();
	_assetLoader->loadAsset ("asset.data");
}

void AssetManager::exit ()
{
	delete _assetLoader;
	delete _assetRegistry;
}

void AssetManager::registerAsset (const GUID &uid, void *asset)
{
	_assetRegistry->addAsset (uid, asset);
}

void AssetManager::unregisterAsset (const GUID &uid)
{
	_assetRegistry->deleteAsset (uid);
}

void* AssetManager::queryAsset (const string &guid)
{
	return _assetRegistry->queryAsset (guid);
}

}