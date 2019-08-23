#ifndef KFTG_ASSET_MANAGER
#define KFTG_ASSET_MANAGER

#include "../types.hpp"
#include "../Module.hpp"
#include "../Singleton.hpp"
#include "../string.hpp"
#include "../map.hpp"
#include "../Asset/AssetTypes.hpp"
#include "Filesystem.hpp"

#define ASSET_TABLE_SIZE 2000

namespace KFTG
{

class AssetRegistry : public Singleton
{
public:
	static AssetRegistry* instance ();
	~AssetRegistry () {}

	void addAsset (const GUID &uid, void *asset);
	void deleteAsset (GUID uid);
	void* queryAsset (const GUID &uid);

private:
	AssetRegistry () : _registry (false) {}

	map<void*> _registry;
};

class AssetLoader : public Singleton
{
public:
	static AssetLoader* instance ();
	~AssetLoader ();
	void loadAsset (const string &path);

private:
	AssetLoader ();

	void initImage (Image *asset, char *o);
	void initAnimation (Animation *asset, char *o);
	void initAudio (Audio *asset, char *o);
	void initXML (XML *asset, char *o);
	void initXMLNode (XML::Node *asset, char *o);

	AssetRegistry *_assetRegistry;
	Filesystem *_fs;
};

// May only be used by editor

class RawAssetLoader
{
public:
	RawAssetLoader ();
	~RawAssetLoader ();

private:
};

// May only be used by editor

class AssetPacker
{
public:
	AssetPacker ();
	~AssetPacker ();

private:
};

class AssetManager : public Module, public Singleton
{
public:
	static AssetManager* instance ();
	~AssetManager () {}
	virtual void init () override;
	virtual void exit () override;
	void registerAsset (const GUID &uid, void *asset);
	void unregisterAsset (const GUID &uid);
	void* queryAsset (const string &guid);

private:
	AssetManager () {}

	AssetLoader *_assetLoader;
	AssetRegistry *_assetRegistry;
};

}

#endif // ASSET_MANAGER